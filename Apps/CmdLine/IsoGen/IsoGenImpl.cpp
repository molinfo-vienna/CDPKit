/* 
 * IsoGenImpl.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <algorithm>
#include <chrono>
#include <iterator>
#include <functional>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/StereoisomerGenerator.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "IsoGenImpl.hpp"


using namespace IsoGen;


class IsoGenImpl::InputScanProgressCallback
{

public:
    class Terminated : public std::exception {};

    InputScanProgressCallback(IsoGenImpl* parent, double offset, double scale): 
        parent(parent), offset(offset), scale(scale) {}

    void operator()(const CDPL::Base::DataIOBase&, double progress) const {
        if (IsoGenImpl::termSignalCaught())
            throw Terminated();

        parent->printProgress("Scanning Input File(s)...  ", offset + scale * progress);
    }

  private:
    IsoGenImpl* parent;
    double      offset;
    double      scale;
};


class IsoGenImpl::IsomerGenerationWorker
{

public:
    IsomerGenerationWorker(IsoGenImpl* parent):
        parent(parent) {}

    void operator()() {
        try {
            init();
    
            while (processNextMolecule());
    
        } catch (const std::exception& e) {
            parent->setErrorMessage(std::string("unexpected exception while generating stereoisomers: ") + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while generating stereoisomers");
        }
    }

private:
    void init() {
        using namespace CDPL;
        using namespace Chem;
        
        isoGen.enumerateAtomConfig(parent->enumAtomConfig);
        isoGen.enumerateBondConfig(parent->enumBondConfig);
        isoGen.includeSpecifiedCenters(parent->incSpecCtrs);
        isoGen.includeSymmetricCenters(parent->incSymCtrs);
        isoGen.includeBridgeheadAtoms(parent->incBridgeheads);
        isoGen.includeInvertibleNitrogens(parent->incInvNitrogens);
        isoGen.includeRingBonds(parent->incRingBonds);
        isoGen.setMinRingSize(parent->minRingSize);
    }

    void perceiveUnspecConfigs(std::size_t dim)
    {
        using namespace CDPL;
        using namespace Chem;
        
        for (auto& atom: molecule.getAtoms())
            switch (getStereoDescriptor(atom).getConfiguration()) {

                case AtomConfiguration::EITHER:
                case AtomConfiguration::UNDEF:
                    setStereoDescriptor(atom, calcStereoDescriptor(atom, molecule, dim));
            }
        
        for (auto& bond: molecule.getBonds())
             switch (getStereoDescriptor(bond).getConfiguration()) {

                case BondConfiguration::EITHER:
                case BondConfiguration::UNDEF:
                    setStereoDescriptor(bond, calcStereoDescriptor(bond, molecule, dim));
             }
    }
    
    bool processNextMolecule() {
        using namespace CDPL;
        
        std::size_t rec_idx = parent->readNextMolecule(molecule);

        if (!rec_idx)
            return false;

        std::string orig_mol_name = getName(molecule);

        try {
            calcImplicitHydrogenCounts(molecule, false);
            setRingFlags(molecule, false);
            perceiveHybridizationStates(molecule, false);
            perceiveSSSR(molecule, false);
            setAromaticityFlags(molecule, false);

            perceiveAtomStereoCenters(molecule, false, false, !parent->incInvNitrogens,
                                      !parent->incInvNitrogens);
            perceiveBondStereoCenters(molecule, false, false, true, true,
                                      std::min(std::size_t(8), parent->minRingSize));
            calcAtomStereoDescriptors(molecule, false, 0);
            calcBondStereoDescriptors(molecule, false, 0);
          
            if (parent->use2DCoords && hasCoordinates(molecule, 2))
                perceiveUnspecConfigs(2);

            if (parent->use3DCoords && hasCoordinates(molecule, 3))
                perceiveUnspecConfigs(3);

            calcCIPPriorities(molecule, false);
            perceiveComponents(molecule, false);
            setAtomSymbolsFromTypes(molecule, false);

            isoGen.setup(molecule);

            std::size_t gen_iso_cnt = 0;

            for ( ; parent->maxNumIsomers == 0 || gen_iso_cnt < parent->maxNumIsomers; ) {
                Util::forEachPair(molecule.getAtomsBegin(), molecule.getAtomsEnd(),
                                  isoGen.getAtomDescriptors().getElementsBegin(),
                                  static_cast<void (*)(Chem::Atom&, const Chem::StereoDescriptor&)>(&Chem::setStereoDescriptor));
                Util::forEachPair(molecule.getBondsBegin(), molecule.getBondsEnd(),
                                  isoGen.getBondDescriptors().getElementsBegin(),
                                  static_cast<void (*)(Chem::Bond&, const Chem::StereoDescriptor&)>(&Chem::setStereoDescriptor));
                
                if (parent->titleSuffix)
                    setName(molecule, orig_mol_name + '_' + std::to_string(gen_iso_cnt + 1));

                parent->writeMolecule(molecule);
                gen_iso_cnt++;
                
                if (!isoGen.generate())
                    break;
            }

            parent->printMessage(VERBOSE, "Molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name) + ": " +
                                 std::to_string(gen_iso_cnt) + (gen_iso_cnt == 1 ? " stereoisomer" : " stereoisomers"));
            parent->numProcMols++;
            
            return true;

        } catch (const std::exception& e) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name) + ": " + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name));
        }

        return false;
    }

    IsoGenImpl*                       parent;
    CDPL::Chem::StereoisomerGenerator isoGen;
    CDPL::Chem::BasicMolecule         molecule;
};


IsoGenImpl::IsoGenImpl(): 
    maxNumIsomers(0), inputFormat(), outputFormat(), enumAtomConfig(true), enumBondConfig(true),
    incSpecCtrs(false), incSymCtrs(false), incInvNitrogens(false), incBridgeheads(false), incRingBonds(false), 
    use2DCoords(true), use3DCoords(false), minRingSize(8), titleSuffix(false), outputWriter(), numProcMols(0),
    numOutIsomers(0)
{
    using namespace std::placeholders;
    
    addOption("input,i", "Input file(s).", 
              value<StringList>(&inputFiles)->multitoken()->required());
    addOption("output,o", "Stereoisomer output file.", 
              value<std::string>(&outputFile)->required());
    addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&IsoGenImpl::setInputFormat, this, _1)));
    addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&IsoGenImpl::setOutputFormat, this, _1)));
    addOption("max-num-isomers,m", "Maximum number of output stereoisomers per molecule (default: 0, must be >= 0, 0 disables limit).",
              value<std::size_t>(&maxNumIsomers));
    addOption("enum-atom-cfg,a", "Enumerate configurations of atom stereocenters (default: true).",
              value<bool>(&enumAtomConfig)->implicit_value(true));
    addOption("enum-bond-cfg,b", "Enumerate configurations of bond stereocenters (default: true).",
              value<bool>(&enumBondConfig)->implicit_value(true));
    addOption("inc-spec-ctrs,s", "Include specified atom/bond stereocenters (default: false).",
              value<bool>(&incSpecCtrs)->implicit_value(true));
    addOption("inc-sym-ctrs,x", "Include atom/bond stereocenters with topological symmetry (default: false).",
              value<bool>(&incSymCtrs)->implicit_value(true));
    addOption("inc-inv-nitrogens,n", "Include invertible nitrogen stereocenters (default: false).",
              value<bool>(&incInvNitrogens)->implicit_value(true));
    addOption("inc-bh-atoms,g", "Include bridgehead atom stereocenters (default: false).",
              value<bool>(&incBridgeheads)->implicit_value(true));
    addOption("inc-ring-bonds,r", "Include ring bond stereocenters (default: false).",
              value<bool>(&incRingBonds)->implicit_value(true));
    addOption("min-ring-size,R", "Minimum size of rings below which the configuration of member bonds shall not be altered "
              "(only effective if option -r is true; default: 8).",
              value<std::size_t>(&minRingSize));
    addOption("use-2d-coords,u", "If present, use atom 2D coordinates and stereo bonds to perceive the configuration "
              "of otherwise unspecified stereocenters (default: true).",
              value<bool>(&use2DCoords)->implicit_value(true));
    addOption("use-3d-coords,y", "If present, use atom 3D coordinates to perceive the configuration of otherwise "
              "unspecified stereocenters (default: false).",
              value<bool>(&use3DCoords)->implicit_value(true));
    addOption("title-suffix,S", "Append stereoisomer number to the title of the output molecules (default: false).", 
              value<bool>(&titleSuffix)->implicit_value(true));
    addOptionLongDescriptions();
}

const char* IsoGenImpl::getProgName() const
{
    return "IsoGen";
}

const char* IsoGenImpl::getProgAboutText() const
{
    return "Performs stereoisomer enumeration for a set of input molecules.";
}

void IsoGenImpl::addOptionLongDescriptions()
{
    StringList formats;
    std::string formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (const auto& fmt : formats)
        formats_str.append("\n - ").append(fmt);

    addOptionLongDescription("input-format", 
                             "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("input", 
                             "Specifies one or more input file(s) with molecules for which stereoisomers have to be generated.\n\n" +
                             formats_str);

    formats.clear();
    formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (const auto& fmt : formats)
        formats_str.append("\n - ").append(fmt);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("output", 
                             "Specifies the output file where the generated stereoisomers will be stored.\n\n" +
                             formats_str);
}

void IsoGenImpl::setInputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("input-format");

    inputFormat = file_ext;
}

void IsoGenImpl::setOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    outputFormat = file_ext;
}

int IsoGenImpl::process()
{
    timer.reset();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

    checkInputFiles();
    printOptionSummary();

    initInputReader();
    initOutputWriter();

    if (termSignalCaught())
        return EXIT_FAILURE;

    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Generating Steroisomers...", true, true);
    } else
        printMessage(INFO, "Generating Steroisomers...");

    genIsomers();

    if (haveErrorMessage()) {
        printMessage(ERROR, "Error: " + errorMessage); 
        return EXIT_FAILURE;
    }

    if (termSignalCaught())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void IsoGenImpl::genIsomers()
{
    using namespace CDPL;

    IsomerGenerationWorker(this)();

    printMessage(INFO, "");

    if (haveErrorMessage())
        return;

    if (termSignalCaught())
        return;

    printStatistics();
}

void IsoGenImpl::setErrorMessage(const std::string& msg)
{
    if (errorMessage.empty())
        errorMessage = msg;
}

bool IsoGenImpl::haveErrorMessage()
{
    return !errorMessage.empty();
}

void IsoGenImpl::printStatistics()
{
    std::size_t proc_time = std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed()).count();
    
    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Processed Molecules:     " + std::to_string(numProcMols));
    printMessage(INFO, " Generated Stereoisomers: " + std::to_string(numOutIsomers));
    printMessage(INFO, " Processing Time:         " + CmdLineLib::formatTimeDuration(proc_time));
    printMessage(INFO, "");
}

std::size_t IsoGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
    if (termSignalCaught())
        return 0;

    if (haveErrorMessage())
        return 0;

    while (true) {
        try {
            printProgress("Generating Steroisomers... ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

            if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
                return 0;

            if (!inputReader.read(mol)) {
                printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + " failed");            
                
                inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
                continue;
            }
            
            return inputReader.getRecordIndex();

        } catch (const std::exception& e) {
            printMessage(ERROR, "Error while reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + ": " + e.what());

        } catch (...) {
            printMessage(ERROR, "Unspecified error while reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1));
        }

        inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
    }

    return 0;
}

void IsoGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol)
{
    if (!outputWriter->write(mol))
        throw CDPL::Base::IOError("could not write generated stereoisomer");

    numOutIsomers++;
}

void IsoGenImpl::checkInputFiles() const
{
    using namespace CDPL;
    using namespace std::placeholders;
    
    StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
                                                 std::bind(std::logical_not<bool>(), 
                                                           std::bind(Util::fileExists, _1)));
    if (it != inputFiles.end())
        throw Base::IOError("file '" + *it + "' does not exist");

    if (std::find_if(inputFiles.begin(), inputFiles.end(),
                     std::bind(Util::checkIfSameFile, boost::ref(outputFile),
                               _1)) != inputFiles.end())
        throw Base::ValueError("output file must not occur in list of input files");
}

void IsoGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    CmdLineBase::printMessage(level, msg, nl, file_only);
}

void IsoGenImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Input File(s):                         " + inputFiles[0]);
    
    for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
        printMessage(VERBOSE, std::string(40, ' ') + *it);

    printMessage(VERBOSE, " Output File:                           " + outputFile);
    printMessage(VERBOSE, " Input File Format:                     " + (!inputFormat.empty() ? inputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Output File Format:                    " + (!outputFormat.empty() ? outputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Max. Num. Stereoisomers:               " + std::to_string(maxNumIsomers));
    printMessage(VERBOSE, " Enum. atom configurations:             " + std::string(enumAtomConfig ? "Yes" : "No"));
    printMessage(VERBOSE, " Enum. bond configurations:             " + std::string(enumBondConfig ? "Yes" : "No"));
    printMessage(VERBOSE, " Include specified stereocenters:       " + std::string(incSpecCtrs ? "Yes" : "No"));
    printMessage(VERBOSE, " Include stereocenters with top. sym.   " + std::string(incSymCtrs ? "Yes" : "No"));
    printMessage(VERBOSE, " Include invertible nitrogens:          " + std::string(incInvNitrogens ? "Yes" : "No"));
    printMessage(VERBOSE, " Include bridgehead atoms:              " + std::string(incBridgeheads ? "Yes" : "No"));
    printMessage(VERBOSE, " Include. ring bonds:                   " + std::string(incRingBonds ? "Yes" : "No"));
    printMessage(VERBOSE, " Min. ring size for bond stereocenters: " + std::to_string(minRingSize));
    printMessage(VERBOSE, " Perceive config. from 2D structure:    " + std::string(use2DCoords ? "Yes" : "No"));
    printMessage(VERBOSE, " Perceive config. from 3D structure:    " + std::string(use3DCoords ? "Yes" : "No"));
    printMessage(VERBOSE, " Append Stereoisomer No. to Mol. Title: " + std::string(titleSuffix ? "Yes" : "No"));
    printMessage(VERBOSE, "");
}

void IsoGenImpl::initInputReader()
{
    using namespace CDPL;

    std::size_t num_in_files = inputFiles.size();
    
    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Scanning Input File(s)...", true, true);
    } else
        printMessage(INFO, "Scanning Input File(s)...");

    setMultiConfImportParameter(inputReader, false);
    setSMILESRecordFormatParameter(inputReader, "SN");

    for (std::size_t i = 0; i < num_in_files; i++) {
        if (termSignalCaught())
            return;

        const std::string& file_path = inputFiles[i];
        Chem::MoleculeReader::SharedPointer reader_ptr;
        
        try {
            reader_ptr.reset(inputFormat.empty() ? new Chem::MoleculeReader(file_path) :
                             new Chem::MoleculeReader(file_path, inputFormat));

        } catch (const Base::IOError& e) {
            throw Base::IOError("no input handler found for file '" + file_path + '\'');
        }
        
        setMultiConfImportParameter(*reader_ptr, false);

        std::size_t cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

        try {
            inputReader.addReader(reader_ptr);

        } catch (const InputScanProgressCallback::Terminated&) {
            reader_ptr->unregisterIOCallback(cb_id);
            break;
        }
       
        reader_ptr->unregisterIOCallback(cb_id);
    }

    if (IsoGenImpl::termSignalCaught())
        return;

    printMessage(INFO, " - Found " + std::to_string(inputReader.getNumRecords()) + " input molecule(s)");
    printMessage(INFO, "");
}

void IsoGenImpl::initOutputWriter()
{
    using namespace CDPL;

    try {
        outputWriter.reset(outputFormat.empty() ? new Chem::MolecularGraphWriter(outputFile) :
                           new Chem::MolecularGraphWriter(outputFile, outputFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + outputFile + '\'');
    }

    setSMILESRecordFormatParameter(*outputWriter, "SN");
    setSMILESOutputCanonicalFormParameter(*outputWriter, true);
    setMultiConfExportParameter(*outputWriter, false);
}

std::string IsoGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const std::string& mol_name)
{
    if (!mol_name.empty())
        return ('\'' + mol_name + "' (" + createMoleculeIdentifier(rec_idx) + ')');

    return createMoleculeIdentifier(rec_idx);
}

std::string IsoGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (std::to_string(rec_idx) + '/' + std::to_string(inputReader.getNumRecords()));
}
