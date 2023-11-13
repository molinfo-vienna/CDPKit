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
#include "CDPL/Util/FileFunctions.hpp"
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

        parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
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

        // TODO apply settings
    }

    bool processNextMolecule() {
        std::size_t rec_idx = parent->readNextMolecule(molecule);

        if (!rec_idx)
            return false;

        try {
            calcImplicitHydrogenCounts(molecule, false);
            setRingFlags(molecule, false);
            perceiveHybridizationStates(molecule, false);
            perceiveSSSR(molecule, false);
            setAromaticityFlags(molecule, false);
            calcAtomStereoDescriptors(molecule, false);
            calcBondStereoDescriptors(molecule, false);
            perceiveComponents(molecule, false);
            setAtomSymbolsFromTypes(molecule, false);

            // TODO

            parent->writeMolecule(molecule);

            parent->numProcMols++;
            
            return true;

        } catch (const std::exception& e) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule) + ": " + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule));
        }

        return false;
    }

    IsoGenImpl*                       parent;
    CDPL::Chem::StereoisomerGenerator isoGen;
    CDPL::Chem::BasicMolecule         molecule;
};


IsoGenImpl::IsoGenImpl(): 
    maxNumIsomers(0), inputFormat(), outputFormat(), titleSuffix(false), outputWriter(), numProcMols(0), numOutIsomers(0)
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
    addOption("max-num-isomers,n", "Maximum number of output stereoisomers for each molecule (default: 0, must be >= 0, 0 disables limit).",
              value<std::size_t>(&maxNumIsomers));
    addOption("title-suffix,S", "Append stereoisomer number to the title of output molecules (default: false).", 
              value<bool>(&titleSuffix)->implicit_value(true));
    addOptionLongDescriptions();
}

const char* IsoGenImpl::getProgName() const
{
    return "IsoGen";
}

const char* IsoGenImpl::getProgAboutText() const
{
    return "Performs stereoisomer generation for a set of input molecules.";
}

void IsoGenImpl::addOptionLongDescriptions()
{
    StringList formats;
    std::string formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
        formats_str.append("\n - ").append(*it);

    addOptionLongDescription("input-format", 
                             "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
                             "(because missing, misleading or not supported).");

    formats_str.pop_back();

    addOptionLongDescription("input", 
                             "Specifies one or more input file(s) with molecules for which stereoisomers have to be generated.\n\n" +
                             formats_str);

    formats.clear();
    formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
        formats_str.append("\n - ").append(*it);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    formats_str.pop_back();

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
        printMessage(INFO, "Processing Input Molecules...", true, true);
    } else
        printMessage(INFO, "Processing Input Molecules...");

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
            if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
                return 0;

            if (!inputReader.read(mol)) {
                printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + " failed");            
                
                inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
                continue;
            }

            printProgress("Generating Steroisomers...   ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());
            
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
        printMessage(VERBOSE, std::string(36, ' ') + *it);

    printMessage(VERBOSE, " Output File:                           " + outputFile);
    printMessage(VERBOSE, " Input File Format:                     " + (!inputFormat.empty() ? inputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Output File Format:                    " + (!outputFormat.empty() ? outputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Max. Num. Stereoisomers:               " + std::to_string(maxNumIsomers));
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
    setSMILESWriteCanonicalFormParameter(*outputWriter, true);
    setMultiConfExportParameter(*outputWriter, false);
}

std::string IsoGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
    if (!getName(mol).empty())
        return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

    return createMoleculeIdentifier(rec_idx);
}

std::string IsoGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (std::to_string(rec_idx) + '/' + std::to_string(inputReader.getNumRecords()));
}
