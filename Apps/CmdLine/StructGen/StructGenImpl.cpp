/* 
 * StructGenImpl.cpp
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
#include <iterator>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <ratio>
#include <functional>

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/ConfGen/StructureGenerator.hpp"
#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/StructureGenerationMode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"
#include "CmdLine/ConfGen/CommonFunctions.hpp"

#include "StructGenImpl.hpp"


using namespace StructGen;


class StructGenImpl::InputScanProgressCallback
{

public:
    class Terminated : public std::exception {};

    InputScanProgressCallback(StructGenImpl* parent, double offset, double scale): 
        parent(parent), offset(offset), scale(scale) {}

    void operator()(const CDPL::Base::DataIOBase&, double progress) const {
        if (StructGenImpl::termSignalCaught())
            throw Terminated();

        parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
    }

private:
    StructGenImpl* parent;
    double         offset;
    double         scale;
};


class StructGenImpl::StructureGenerationWorker
{

public:
    StructureGenerationWorker(StructGenImpl* parent):
        parent(parent), verbLevel(parent->getVerbosityLevel()), numProcMols(0), numFailedMols(0) {

        structGen.setAbortCallback(std::bind(&StructureGenerationWorker::abort, this));
        structGen.getSettings() = parent->settings;

        if (parent->getVerbosityLevel() >= DEBUG)  
            structGen.setLogMessageCallback(std::bind(&StructureGenerationWorker::appendToLogRecord, this,
                                                      std::placeholders::_1));

        if (parent->torsionLib) {
            if (parent->replaceBuiltinTorLib)
                structGen.clearTorsionLibraries();

            structGen.addTorsionLibrary(parent->torsionLib);
        }

        if (parent->fragmentLib) {
            if (parent->replaceBuiltinFragLib)
                structGen.clearFragmentLibraries();

            structGen.addFragmentLibrary(parent->fragmentLib);
        }
    }

    void operator()() {
        try {
            while (processNextMolecule());
        
        } catch (const std::exception& e) {
            parent->setErrorMessage(std::string("unexpected exception while generating conformers: ") + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while generating conformers");
        }
    }

    std::size_t getNumProcMolecules() const {
        return numProcMols;
    }

    std::size_t getNumFailedMolecules() const {
        return numFailedMols;
    }

private:
    bool processNextMolecule() {
        using namespace CDPL::ConfGen;

        timer.reset();

        std::size_t rec_idx = parent->readNextMolecule(molecule);

        if (!rec_idx)
            return false;

        try {
            logRecordStream.str(std::string());

            if (verbLevel >= DEBUG) 
                logRecordStream << std::endl << "- Molecule " << 
                    parent->createMoleculeIdentifier(rec_idx, molecule) << ':' << std::endl;    

            if (parent->failedOutputWriter) 
                origMolecule = molecule;

            prepareForConformerGeneration(molecule, parent->canonicalize);
                    
            unsigned int ret_code = structGen.generate(molecule);

            switch (ret_code) {

                case ReturnCode::ABORTED:
                    return false;

                case ReturnCode::TIMEOUT:
                    if (parent->hardTimeout) {
                        handleError(rec_idx, ret_code);
                        break;
                    }

                case ReturnCode::SUCCESS:
                    outputConformers(rec_idx, ret_code);
                    break;

                default:
                    handleError(rec_idx, ret_code);
            }
        
            std::string log_rec = logRecordStream.str();

            if (!log_rec.empty()) 
                parent->printMessage(verbLevel, log_rec, false);

            numProcMols++;

            return true;

        } catch (const std::exception& e) {
            parent->setErrorMessage("unexpected exception while processing molecule " + 
                                    parent->createMoleculeIdentifier(rec_idx, molecule) + ": " + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while processing molecule " + 
                                    parent->createMoleculeIdentifier(rec_idx, molecule));
        }

        return false;
    }

    void outputConformers(std::size_t rec_idx, unsigned int ret_code) {
        using namespace CDPL::ConfGen;

        setMDLDimensionality(molecule, 3);

        if (verbLevel == VERBOSE || (verbLevel == INFO && ret_code == ReturnCode::TIMEOUT)) {
            logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": Success, " << 
                timer.format<3>() << 's';

            if (ret_code == ReturnCode::TIMEOUT)
                logRecordStream << " (time limit exceeded)";

            logRecordStream << std::endl;
        }

        structGen.setCoordinates(molecule);

        parent->writeMolecule(molecule, false);
    }

    void handleError(std::size_t rec_idx, unsigned int ret_code) {
        using namespace CDPL::ConfGen;

        numFailedMols++;

        if (parent->failedOutputWriter) {
            calcImplicitHydrogenCounts(origMolecule, true);
            perceiveComponents(origMolecule, true);
            perceiveSSSR(origMolecule, true);

            try {
                parent->writeMolecule(origMolecule, true);

            } catch (const std::exception& e) {
                if (verbLevel >= ERROR)
                    logRecordStream << "Error while writing failed molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) <<
                        ": " << e.what() << std::endl;
            }
        }

        if (verbLevel < ERROR)
            return;

        if (verbLevel >= DEBUG) {
            if (parent->hardTimeout)
                logRecordStream << "Structure generation failed due to hard timeout setting!" << std::endl;
            
            return;
        }

        std::string err_msg;

        switch (ret_code) {

            case ReturnCode::FORCEFIELD_SETUP_FAILED:
                err_msg = "force field setup failed";
                break;

            case ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
                err_msg = "structure refinement failed";
                break;

            case ReturnCode::CONF_GEN_FAILED:
                err_msg = "could not generate 3D-structure";
                break;

            case ReturnCode::FRAGMENT_CONF_GEN_FAILED:
                err_msg = "fragment build failed";
                break;

            case ReturnCode::TIMEOUT:
                err_msg = "time limit exceeded";
                break;

            default:
                err_msg = "unspecified error: " + std::to_string(ret_code);
                break;
        }

        logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << err_msg << std::endl; 
    }

    void appendToLogRecord(const std::string& msg) {
        logRecordStream << msg;
    }

    bool abort() const {
        if (parent->haveErrorMessage() || StructGenImpl::termSignalCaught())
            return true;

        return false;
    }

    StructGenImpl*                       parent;
    CDPL::ConfGen::StructureGenerator    structGen;
    CDPL::Chem::BasicMolecule            molecule;
    CDPL::Chem::Fragment                 origMolecule;
    std::stringstream                    logRecordStream;
    VerbosityLevel                       verbLevel;
    CDPL::Internal::Timer                timer;
    std::size_t                          numProcMols;
    std::size_t                          numFailedMols;
};


StructGenImpl::StructGenImpl(): 
    numThreads(0), fragBuildPreset("FAST"), canonicalize(false),
    hardTimeout(false), torsionLib(), fragmentLib(), inputFormat(), 
    outputFormat(), outputWriter(), failedOutputFormat(), failedOutputWriter()
{
    using namespace std::placeholders;
    
    settings.getFragmentBuildSettings() =  CDPL::ConfGen::FragmentConformerGeneratorSettings::FAST;

    addOption("input,i", "Input file(s).", 
              value<StringList>(&inputFiles)->multitoken()->required());
    addOption("output,o", "Output file.", 
              value<std::string>(&outputFile)->required());
    addOption("failed,f", "Failed molecule output file.", 
              value<std::string>(&failedFile));
    addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
              std::to_string(std::thread::hardware_concurrency()) + 
              " threads, must be >= 0, 0 disables multithreading).", 
              value<std::size_t>(&numThreads)->implicit_value(std::thread::hardware_concurrency()));
    addOption("mode,m", "Structure generation method to use (AUTO, DG, FRAGMENT, default: " + getGenerationModeString() + ").", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setGenerationMode, this, _1)));
    addOption("tol-range-sampling,A", "Additionally generate conformers for angles at the boundaries of the first "
              "torsion angle tolerance range (only effective for fragment-based structure generation, default: true).", 
              value<bool>()->implicit_value(true)->notifier(std::bind(&StructGenImpl::setSampleAngleTolRanges, this, _1)));
    addOption("from-scratch,S", "Discard input 3D-coordinates and generate structures from scratch (default: true).", 
              value<bool>()->implicit_value(true)->notifier(std::bind(&StructGenImpl::setGenerateFromScratch, this, _1)));
    addOption("frag-force-field,d", "Force field used for fragment-based structure generation (MMFF94, MMFF94_NO_ESTAT, "
              "MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: " +
              ConfGen::getForceFieldTypeString(settings.getFragmentModeForceFieldType()) + ").", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setFragBasedForceFieldType, this, _1)));
    addOption("dg-force-field,q", "Force field used for DG-based structure generation (MMFF94, MMFF94_NO_ESTAT, "
              "MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: " +
              ConfGen::getForceFieldTypeString(settings.getDGModeForceFieldType()) + ").", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setDGBasedForceFieldType, this, _1)));
    addOption("strict-param,s", "Perform strict MMFF94 parameterization (default: true).", 
              value<bool>()->implicit_value(true)->notifier(std::bind(&StructGenImpl::setStrictParameterization, this, _1)));
    addOption("dielectric-const,D", "Dielectric constant used for the calculation of electrostatic interaction energies (default: " +
              (boost::format("%.4f") % settings.getDielectricConstant()).str() + ").", 
              value<double>()->notifier(std::bind(&StructGenImpl::setDielectricConst, this, _1)));
    addOption("dist-exponent,E", "Distance exponent used for the calculation of electrostatic interaction energies (default: " +
              (boost::format("%.4f") % settings.getDistanceExponent()).str() + ").", 
              value<double>()->notifier(std::bind(&StructGenImpl::setDistExponent, this, _1)));
    addOption("timeout,T", "Time in seconds after which structure generation will be stopped (default: " + 
              std::to_string(settings.getTimeout() / 1000) + " s, must be >= 0, 0 disables timeout).",
              value<std::size_t>()->notifier(std::bind(&StructGenImpl::setTimeout, this, _1)));
    addOption("mc-rot-bond-count-thresh,Z", "Number of rotatable bonds in a ring above which DG-based structure generation will be performed"
              "(only effective in generation mode AUTO, default: " +
              std::to_string(settings.getMacrocycleRotorBondCountThreshold()) + ", must be > 0).", 
              value<std::size_t>()->notifier(std::bind(&StructGenImpl::setMacrocycleRotorBondCountThreshold, this, _1)));
    addOption("ref-tol,P", "Energy tolerance at which force field structure refinement stops (only effective in DG-based structure generation, default: " +
              (boost::format("%.4f") % settings.getRefinementTolerance()).str() + ", must be >= 0, 0 results in refinement until convergence).",
              value<double>()->notifier(std::bind(&StructGenImpl::setRefTolerance, this, _1)));
    addOption("max-ref-iter,w", "Maximum number of force field structure refinement iterations (only effective in DG-based structure generation, default: " +
              std::to_string(settings.getMaxNumRefinementIterations()) + ", must be >= 0, 0 disables limit).", 
              value<std::size_t>()->notifier(std::bind(&StructGenImpl::setMaxNumRefIterations, this, _1)));
    addOption("add-tor-lib,k", "Torsion library to be used in addition to the built-in library (only effective for fragment-based structure generation).",
              value<std::string>()->notifier(std::bind(&StructGenImpl::addTorsionLib, this, _1)));
    addOption("set-tor-lib,K", "Torsion library used as a replacement for the built-in library (only effective for fragment-based structure generation).",
              value<std::string>()->notifier(std::bind(&StructGenImpl::setTorsionLib, this, _1)));
    addOption("frag-build-preset,B", "Fragment build preset to use (FAST, THOROUGH, only effective for fragment-based structure generation, default: FAST).", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::applyFragBuildPreset, this, _1)));
    addOption("add-frag-lib,g", "Fragment library to be used in addition to the built-in library (only effective for fragment-based structure generation).",
              value<std::string>()->notifier(std::bind(&StructGenImpl::addFragmentLib, this, _1)));
    addOption("set-frag-lib,G", "Fragment library used as a replacement for the built-in library (only effective for fragment-based structure generation).",
              value<std::string>()->notifier(std::bind(&StructGenImpl::setFragmentLib, this, _1)));
    addOption("canonicalize,z", "Canonicalize input molecules (default: false).", 
              value<bool>(&canonicalize)->implicit_value(true));
    addOption("hard-timeout,U", "Specifies that exceeding the time limit shall be considered as an error and cause "
              "structure generation to fail (default: false).", 
              value<bool>(&hardTimeout)->implicit_value(true));
    addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setInputFormat, this, _1)));
    addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setOutputFormat, this, _1)));
    addOption("failed-format,F", "Failed molecule output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&StructGenImpl::setFailedOutputFormat, this, _1)));

    addOptionLongDescriptions();
}

const char* StructGenImpl::getProgName() const
{
    return "StructGen";
}

const char* StructGenImpl::getProgAboutText() const
{
    return "Performs 3D structure generation for a set of input molecules.\n\n"
        "Built-in torsion rules are based on the torsion library jointly developed by the\n"
        "University of Hamburg, Center for Bioinformatics, Hamburg, Germany and\n"
        "F. Hoffmann-La-Roche Ltd., Basel, Switzerland.\n\n"
        "References:\n"
        " -  Schaerfer, C., Schulz-Gasch, T., Ehrlich, H.C., Guba, W., Rarey, M.,\n"
        "    Stahl, M. (2013). Torsion Angle Preferences in Drug-like Chemical Space:\n"
        "    A Comprehensive Guide. Journal of Medicinal Chemistry, 56(6):2016-28.\n"
        " -  Guba, W., Meyder, A., Rarey, M., and Hert, J. (2015). Torsion Library Reloaded:\n"
        "    A New Version of Expert-Derived SMARTS Rules for Assessing Conformations of\n"
        "    Small Molecules. Journal of Chemical Information and Modeling, 56(1):1-5.";
}

void StructGenImpl::addOptionLongDescriptions()
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
                             "Specifies one or more input file(s) with molecules for which conformers have to be generated.\n\n" +
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
                             "(because missing, misleading or not supported)." +
                             "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

    addOptionLongDescription("failed-format", 
                             "Allows to explicitly specify the output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    formats_str.pop_back();

    addOptionLongDescription("output", 
                             "Specifies the output file where the generated structures will be stored.\n\n" +
                             formats_str +
                             "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

    addOptionLongDescription("failed", 
                             "Specifies the output file for molecules where structure generation failed.\n\n" +
                             formats_str);
}

void StructGenImpl::applyFragBuildPreset(const std::string& pres_str)
{
    fragBuildPreset = boost::to_upper_copy(pres_str);
    
    if (fragBuildPreset == "FAST")
        settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::FAST;
    else if (fragBuildPreset == "THOROUGH")
        settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::THOROUGH;
    else
        throwValidationError("frag-build-preset");
}

void StructGenImpl::setGenerationMode(const std::string& mode_str)
{
    using namespace CDPL::ConfGen;
    using namespace CDPL;

    if (Internal::isEqualCI(mode_str, "AUTO"))
        settings.setGenerationMode(StructureGenerationMode::AUTO);
    else if (Internal::isEqualCI(mode_str, "FRAGMENT"))
        settings.setGenerationMode(StructureGenerationMode::FRAGMENT);
    else if (Internal::isEqualCI(mode_str, "DG"))
        settings.setGenerationMode(StructureGenerationMode::DISTANCE_GEOMETRY);
    else
        throwValidationError("mode");
}

void StructGenImpl::setTimeout(std::size_t timeout)
{
    settings.setTimeout(timeout * 1000);
}

void StructGenImpl::setDielectricConst(double de_const)
{
    settings.setDielectricConstant(de_const);
}

void StructGenImpl::setDistExponent(double exp)
{
    settings.setDistanceExponent(exp);
}

void StructGenImpl::setMacrocycleRotorBondCountThreshold(std::size_t min_count)
{
    if (min_count == 0)
        throwValidationError("mc-rot-bond-count-thresh");

    settings.setMacrocycleRotorBondCountThreshold(min_count);
}

void StructGenImpl::setRefTolerance(double tol)
{
    if (tol < 0.0)
        throwValidationError("ref-tol");

    settings.setRefinementTolerance(tol);
}

void StructGenImpl::setMaxNumRefIterations(std::size_t num_iter)
{
    settings.setMaxNumRefinementIterations(num_iter);
}

void StructGenImpl::setStrictParameterization(bool strict)
{
    settings.strictForceFieldParameterization(strict);
    settings.getFragmentBuildSettings().strictForceFieldParameterization(strict);
}

void StructGenImpl::setFragBasedForceFieldType(const std::string& type_str)
{
    unsigned int ff_type = ConfGen::stringToForceFieldType(type_str, "frag-force-field");

    settings.setFragmentModeForceFieldType(ff_type);
    settings.getFragmentBuildSettings().setForceFieldType(ff_type);
}

void StructGenImpl::setDGBasedForceFieldType(const std::string& type_str)
{
    unsigned int ff_type = ConfGen::stringToForceFieldType(type_str, "dg-force-field");

    settings.setDGModeForceFieldType(ff_type);
}

void StructGenImpl::setSampleAngleTolRanges(bool sample)
{
    settings.sampleAngleToleranceRanges(sample);
}

void StructGenImpl::setGenerateFromScratch(bool from_scratch)
{
    settings.generateCoordinatesFromScratch(from_scratch);
}

void StructGenImpl::setInputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("input-format");

    inputFormat = file_ext;
}

void StructGenImpl::setOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    outputFormat = file_ext;
}

void StructGenImpl::setFailedOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("failed-output-format");

    failedOutputFormat = file_ext;
}

void StructGenImpl::addTorsionLib(const std::string& lib_file)
{
    torsionLibName = lib_file;
    replaceBuiltinTorLib = false;
}

void StructGenImpl::setTorsionLib(const std::string& lib_file)
{
    torsionLibName = lib_file;
    replaceBuiltinTorLib = true;
}

void StructGenImpl::addFragmentLib(const std::string& lib_file)
{
    fragmentLibName = lib_file;
    replaceBuiltinFragLib = false;
}

void StructGenImpl::setFragmentLib(const std::string& lib_file)
{
    fragmentLibName = lib_file;
    replaceBuiltinFragLib = true;
}

int StructGenImpl::process()
{
    timer.reset();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

    checkInputFiles();
    printOptionSummary();

    initInputReader();
    initOutputWriters();

    if (termSignalCaught())
        return EXIT_FAILURE;

    loadTorsionLibrary();

    if (termSignalCaught())
        return EXIT_FAILURE;

    loadFragmentLibrary();

    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Processing Input Molecules...", true, true);
    } else
        printMessage(INFO, "Processing Input Molecules...");

    if (numThreads > 0)
        processMultiThreaded();
    else
        processSingleThreaded();

    if (haveErrorMessage()) {
        printMessage(ERROR, "Error: " + errorMessage); 
        return EXIT_FAILURE;
    }

    if (termSignalCaught())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void StructGenImpl::processSingleThreaded()
{
    using namespace CDPL;

    StructureGenerationWorker worker(this);

    worker();

    printMessage(INFO, "");

    if (haveErrorMessage())
        return;

    if (termSignalCaught())
        return;

    printStatistics(worker.getNumProcMolecules(), worker.getNumFailedMolecules());
}

void StructGenImpl::processMultiThreaded()
{
    using namespace CDPL;

    typedef std::shared_ptr<StructureGenerationWorker> StructureGenerationWorkerPtr;
    typedef std::vector<StructureGenerationWorkerPtr> StructureGenerationWorkerList;
    typedef std::vector<std::thread> ThreadGroup;
    
    ThreadGroup thread_grp;
    StructureGenerationWorkerList worker_list;

    try {
        for (std::size_t i = 0; i < numThreads; i++) {
            if (termSignalCaught())
                break;

            StructureGenerationWorkerPtr worker_ptr(new StructureGenerationWorker(this));

            thread_grp.emplace_back(std::bind(&StructureGenerationWorker::operator(), worker_ptr));
            worker_list.push_back(worker_ptr);
        }

    } catch (const std::exception& e) {
        setErrorMessage(std::string("error while creating worker-threads: ") + e.what());

    } catch (...) {
        setErrorMessage("unspecified error while creating worker-threads");
    }

    try {
        for (auto& thread : thread_grp)
            thread.join();

    } catch (const std::exception& e) {
        setErrorMessage(std::string("error while waiting for worker-threads to finish: ") + e.what());

    } catch (...) {
        setErrorMessage("unspecified error while waiting for worker-threads to finish");
    }
    
    printMessage(INFO, "");

    if (haveErrorMessage())
        return;

    if (termSignalCaught())
        return;
    
    std::size_t num_proc_mols = 0;
    std::size_t num_failed_mols = 0;

    for (std::size_t i = 0; i < numThreads; i++) {
        const StructureGenerationWorker& worker = *worker_list[i];

        num_proc_mols += worker.getNumProcMolecules();
        num_failed_mols += worker.getNumFailedMolecules();
    }

    printStatistics(num_proc_mols, num_failed_mols);

}

void StructGenImpl::setErrorMessage(const std::string& msg)
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);

        if (errorMessage.empty())
            errorMessage = msg;
        return;
    }

    if (errorMessage.empty())
        errorMessage = msg;
}

bool StructGenImpl::haveErrorMessage()
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);
        return !errorMessage.empty();
    }

    return !errorMessage.empty();
}

void StructGenImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols)
{
    double proc_time = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1> > >(timer.elapsed()).count();
    
    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Processed Molecules:  " + std::to_string(num_proc_mols));
    printMessage(INFO, " Molecules Failed:     " + std::to_string(num_failed_mols));

    if (num_proc_mols > 0)
        printMessage(INFO, " Processing Time:      " + CmdLineLib::formatTimeDuration(proc_time) + 
                     " (" + (boost::format("%.3f") % (proc_time / num_proc_mols)).str() + " s/Mol.)");
    else
        printMessage(INFO, " Processing Time:      " + CmdLineLib::formatTimeDuration(proc_time));

    printMessage(INFO, "");
}

std::size_t StructGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
    if (termSignalCaught())
        return 0;

    if (haveErrorMessage())
        return 0;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(readMolMutex);

        return doReadNextMolecule(mol);
    }

    return doReadNextMolecule(mol);
}

std::size_t StructGenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
    while (true) {
        try {
            if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
                return 0;

            if (!inputReader.read(mol)) {
                printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + " failed");            
                
                inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
                continue;
            }

            printProgress("Processing Molecules...        ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

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

void StructGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed)
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(writeMolMutex);

        doWriteMolecule(mol, failed);

    } else
        doWriteMolecule(mol, failed);
}

void StructGenImpl::doWriteMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed)
{
    if (failed) {
        if (!failedOutputWriter->write(mol))
            throw CDPL::Base::IOError("could not output molecule");

        return;
    }

    if (!outputWriter->write(mol))
        throw CDPL::Base::IOError("could not write generated conformers");
}

void StructGenImpl::checkInputFiles() const
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

    if (!failedFile.empty() && std::find_if(inputFiles.begin(), inputFiles.end(),
                                            std::bind(Util::checkIfSameFile, boost::ref(failedFile),
                                                      _1)) != inputFiles.end())
        throw Base::ValueError("failed output file must not occur in list of input files");

    if (!torsionLibName.empty() && !Util::fileExists(torsionLibName))
        throw Base::IOError("torsion library file '" + torsionLibName + "' does not exist");

    if (!fragmentLibName.empty() && !Util::fileExists(fragmentLibName))
        throw Base::IOError("fragment library file '" + fragmentLibName + "' does not exist");
}

void StructGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    if (numThreads == 0) {
        CmdLineBase::printMessage(level, msg, nl, file_only);
        return;
    }

    std::lock_guard<std::mutex> lock(mutex);

    CmdLineBase::printMessage(level, msg, nl, file_only);
}

void StructGenImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Input File(s):                       " + inputFiles[0]);
    
    for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
        printMessage(VERBOSE, std::string(38, ' ') + *it);

    printMessage(VERBOSE, " Output File:                         " + outputFile);
    printMessage(VERBOSE, " Failed Molecule Output File:         " + (failedFile.empty() ? std::string("None") : failedFile));
    printMessage(VERBOSE, " Fragment Build Preset:               " + fragBuildPreset);
    printMessage(VERBOSE, " Structure Generation Mode:           " + getGenerationModeString());
    printMessage(VERBOSE, " Sample Whole Tor. Angle Tol. Range:  " + std::string(settings.sampleAngleToleranceRanges() ? "Yes" : "No"));
    printMessage(VERBOSE, " Generate Coordinates From Scratch:   " + std::string(settings.generateCoordinatesFromScratch() ? "Yes" : "No"));
    printMessage(VERBOSE, " Fragment Mode Force Field Type:      " + ConfGen::getForceFieldTypeString(settings.getFragmentModeForceFieldType()));
    printMessage(VERBOSE, " Dist. Geom. Mode Force Field Type:   " + ConfGen::getForceFieldTypeString(settings.getDGModeForceFieldType()));
    printMessage(VERBOSE, " Strict Force Field Parameterization: " + std::string(settings.strictForceFieldParameterization() ? "Yes" : "No"));
    printMessage(VERBOSE, " Dielectric Constant:                 " + (boost::format("%.3f") % settings.getDielectricConstant()).str());
    printMessage(VERBOSE, " Distance Exponent:                   " + (boost::format("%.3f") % settings.getDistanceExponent()).str());
    printMessage(VERBOSE, " Macrocycle Rot. Bond Count Theshold: " + std::to_string(settings.getMacrocycleRotorBondCountThreshold()));
    printMessage(VERBOSE, " Refinement Energy Tolerance:         " + (boost::format("%.4f") % settings.getRefinementTolerance()).str());
    printMessage(VERBOSE, " Max. Num. Refinement Iterations:     " + std::to_string(settings.getMaxNumRefinementIterations()));
    printMessage(VERBOSE, " Timeout:                             " + std::to_string(settings.getTimeout() / 1000) + "s");
    printMessage(VERBOSE, " Hard Timeout:                        " + std::string(hardTimeout ? "Yes" : "No"));
    printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

    if (numThreads > 0)
        printMessage(VERBOSE, " Number of Threads:                   " + std::to_string(numThreads));

    printMessage(VERBOSE, " Torsion Library:                     " + (torsionLibName.empty() ? std::string("Built-in") :
                                                                      replaceBuiltinTorLib ? torsionLibName : torsionLibName + " + Built-in"));
    printMessage(VERBOSE, " Fragment Library:                    " + (fragmentLibName.empty() ? std::string("Built-in") :
                                                                      replaceBuiltinFragLib ? fragmentLibName : fragmentLibName + " + Built-in"));
    printMessage(VERBOSE, " Input File Format:                   " + (!inputFormat.empty() ? inputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Output File Format:                  " + (!outputFormat.empty() ? outputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Failed Molecule File Format:         " + (!failedOutputFormat.empty() ? failedOutputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Canonicalize Input Molecules:        " + std::string(canonicalize ? "Yes" : "No"));
    printMessage(VERBOSE, "");
}

void StructGenImpl::loadTorsionLibrary()
{
    using namespace CDPL;
    using namespace CDPL::ConfGen;

    if (torsionLibName.empty())
        return;

    std::ifstream is(torsionLibName);

    if (!is) 
        throw Base::IOError("opening torsion library '" + torsionLibName + "' failed");

    printMessage(INFO, "Loading Torsion Library '" + torsionLibName + "'...");

    torsionLib.reset(new TorsionLibrary());
    torsionLib->load(is);

    if (StructGenImpl::termSignalCaught())
        return;

    if (!is)
        throw Base::IOError("loading torsion library '" + torsionLibName + "' failed");

    printMessage(INFO, " - Loaded " + std::to_string(torsionLib->getNumRules(true)) + " torsion rules in " +
                 std::to_string(torsionLib->getNumCategories(true)) + " categories");
    printMessage(INFO, "");
}

void StructGenImpl::loadFragmentLibrary()
{
    using namespace CDPL;
    using namespace CDPL::ConfGen;

    if (fragmentLibName.empty())
        return;

    std::ifstream is(fragmentLibName);

    if (!is) 
        throw Base::IOError("opening fragment library '" + fragmentLibName + "' failed");

    printMessage(INFO, "Loading Fragment Library '" + fragmentLibName + "'...");

    fragmentLib.reset(new FragmentLibrary());
    fragmentLib->load(is);

    if (StructGenImpl::termSignalCaught())
        return;

    if (!is)
        throw Base::IOError("loading fragment library '" + fragmentLibName + "' failed");

    printMessage(INFO, " - Loaded " + std::to_string(fragmentLib->getNumEntries()) + " fragments");
    printMessage(INFO, "");
}

void StructGenImpl::initInputReader()
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

    if (StructGenImpl::termSignalCaught())
        return;

    printMessage(INFO, " - Found " + std::to_string(inputReader.getNumRecords()) + " input molecule(s)");
    printMessage(INFO, "");
}

void StructGenImpl::initOutputWriters()
{
    using namespace CDPL;

    try {
        outputWriter.reset(outputFormat.empty() ? new Chem::MolecularGraphWriter(outputFile) :
                           new Chem::MolecularGraphWriter(outputFile, outputFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + outputFile + '\'');
    }

    setMultiConfExportParameter(*outputWriter, false);
    setSMILESRecordFormatParameter(*outputWriter, "SN");

    if (!failedFile.empty()) {
        try {
            failedOutputWriter.reset(failedOutputFormat.empty() ? new Chem::MolecularGraphWriter(failedFile) :
                                     new Chem::MolecularGraphWriter(failedFile, failedOutputFormat));

        } catch (const Base::IOError& e) {
            throw Base::IOError("no output handler found for file '" + outputFile + '\'');
        }
        
        setMultiConfExportParameter(*failedOutputWriter, false);
        setSMILESRecordFormatParameter(*failedOutputWriter, "SN");
    }
}

std::string StructGenImpl::getGenerationModeString() const
{
    using namespace CDPL::ConfGen;

    unsigned int mode = settings.getGenerationMode();

    if (mode == StructureGenerationMode::AUTO)
        return "AUTO";
    
    if (mode == StructureGenerationMode::FRAGMENT)
        return "FRAGMENT";

    if (mode == StructureGenerationMode::DISTANCE_GEOMETRY)
        return "DG";
    
    return "UNKNOWN";
}

std::string StructGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
    if (!getName(mol).empty())
        return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

    return createMoleculeIdentifier(rec_idx);
}

std::string StructGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (std::to_string(rec_idx) + '/' + std::to_string(inputReader.getNumRecords()));
}
