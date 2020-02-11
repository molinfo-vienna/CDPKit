/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConfGenImpl.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/ConformerGenerator.hpp"
#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Lib/HelperFunctions.hpp"

#include "ConfGenImpl.hpp"


using namespace ConfGen;


class ConfGenImpl::InputScanProgressCallback
{

public:
	class Terminated : public std::exception {};

	InputScanProgressCallback(ConfGenImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (ConfGenImpl::termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
	}

private:
	ConfGenImpl* parent;
	double       offset;
	double       scale;
};


class ConfGenImpl::ConformerGenerationWorker
{

public:
	ConformerGenerationWorker(ConfGenImpl* parent):
		parent(parent), verbLevel(parent->getVerbosityLevel()), numProcMols(0),
		numFailedMols(0), numGenConfs(0) {

		confGen.setAbortCallback(boost::bind(&ConformerGenerationWorker::abort, this));
		confGen.getSettings() = parent->settings;

		if (parent->getVerbosityLevel() >= DEBUG)  
			confGen.setLogMessageCallback(boost::bind(&ConformerGenerationWorker::appendToLogRecord, this, _1));
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

	std::size_t getNumGenConformers() const {
		return numGenConfs;
	}

private:
	bool processNextMolecule() {
		using namespace CDPL::ConfGen;

		timer.start();

		std::size_t rec_idx = parent->readNextMolecule(molecule);

		if (!rec_idx)
			return false;

		try {
			logRecordStream.str(std::string());

			if (verbLevel >= DEBUG) 
				logRecordStream << std::endl << "- Molecule " << 
					parent->createMoleculeIdentifier(rec_idx, molecule) << ':' << std::endl;	

			prepareForConformerGeneration(molecule, parent->canonicalize);

			unsigned int ret_code = confGen.generate(molecule);

			switch (ret_code) {

				case ReturnCode::ABORTED:
					return false;

				case ReturnCode::SUCCESS:
				case ReturnCode::TIMEOUT:
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

		std::size_t num_confs = confGen.getNumConformers();

		if (verbLevel == VERBOSE || (verbLevel == INFO && ret_code == ReturnCode::TIMEOUT)) {
			logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << 
				num_confs << (num_confs == 1 ? " conf., " : " confs., ") << timer.format(3, "%w") << 's';

			if (ret_code == ReturnCode::TIMEOUT)
				logRecordStream << " (time limit exceeded)";

			logRecordStream << std::endl;
		}

		confGen.setConformers(molecule);

		parent->writeMolecule(molecule);

		numGenConfs += num_confs;
	}

	void handleError(std::size_t rec_idx, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		numFailedMols++;

		if (verbLevel < ERROR || verbLevel >= DEBUG)
			return;

		std::string err_msg;

		switch (ret_code) {

			case ReturnCode::FORCEFIELD_SETUP_FAILED:
				err_msg = "force field setup failed";
				break;

			case ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
				err_msg = "structure refinement failed";
				break;

			case ReturnCode::CONF_GEN_FAILED:
				err_msg = "could not generate any conformers";
				break;

			default:
				err_msg = "unspecified error";
				break;
		}

		logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << err_msg << std::endl; 
	}

	void appendToLogRecord(const std::string& msg) {
		logRecordStream << msg;
	}

	bool abort() const {
		if (parent->haveErrorMessage() || ConfGenImpl::termSignalCaught())
			return true;

		return false;
	}

	typedef boost::chrono::system_clock Clock;

	ConfGenImpl*                         parent;
	CDPL::ConfGen::ConformerGenerator    confGen;
	CDPL::Chem::BasicMolecule            molecule;
	std::stringstream                    logRecordStream;
	VerbosityLevel                       verbLevel;
	boost::timer::cpu_timer              timer;
	std::size_t                          numProcMols;
	std::size_t                          numFailedMols;
	std::size_t                          numGenConfs;
};


ConfGenImpl::ConfGenImpl(): 
	numThreads(0), settings(ConformerGeneratorSettings::MEDIUM_SET_DIVERSE), 
	confGenPreset("MEDIUM_SET_DIVERSE"), fragBuildPreset("FAST"),
	canonicalize(false), inputHandler(), outputHandler(), outputWriter(), 
	failedOutputHandler(), failedOutputWriter()
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output file.", 
			  value<std::string>(&outputFile)->required());
	addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(boost::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(boost::thread::hardware_concurrency()));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setInputFormat, this, _1)));
	addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setOutputFormat, this, _1)));
	addOption("conf-gen-preset,S", "Conformer generation preset to use (SMALL_SET_DIVERSE, MEDIUM_SET_DIVERSE, " 
			  "LARGE_SET_DIVERSE, SMALL_SET_DENSE, MEDIUM_SET_DENSE, LARGE_SET_DENSE, default: MEDIUM_SET_DIVERSE).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::applyConfGenPreset, this, _1)));
	addOption("frag-build-preset,F", "Fragment build preset to use (FAST, THOROUGH, default: FAST).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::applyFragBuildPreset, this, _1)));
	addOption("rmsd,r", "Minimum RMSD for output conformer selection (default: " + 
			  (boost::format("%.4f") % settings.getMinRMSD()).str() + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setRMSD, this, _1)));
	addOption("timeout,T", "Time in seconds after which conformer generation will be stopped (default: " + 
			  boost::lexical_cast<std::string>(settings.getTimeout() / 1000) + "s, must be >= 0, 0 disables timeout).",
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setTimeout, this, _1)));
	addOption("max-num_confs,n", "Maximum number of output conformers per molecule (default: " + 
			  boost::lexical_cast<std::string>(settings.getMaxNumOutputConformers()) + ", must be >= 0, 0 disables limit).",
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMaxNumConfs, this, _1)));
	addOption("e-window,e", "Output energy window for generated conformers (default: " + 
			  boost::lexical_cast<std::string>(settings.getEnergyWindow()) + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setEnergyWindow, this, _1)));
	addOption("search-forcefield,f", "Conformer search force field type (MMFF94, MMFF94_NO_ESTAT, MMFF94S, MMFF94S_EXT, MMFF94S_NO_ESTAT, MMFF94S_EXT_NO_ESTAT, default: " +
			  getForceFieldTypeString(settings.getForceFieldType()) + ").", value<std::string>()->notifier(boost::bind(&ConfGenImpl::setForceFieldType, this, _1)));
	addOption("strict-param,s", "Perform strict MMFF94 parameterization (default: true).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setStrictParameterization, this, _1)));
	addOption("sampling-mode,m", "Conformer sampling mode (AUTO, STOCHASTIC, SYSTEMATIC default: " + getSamplingModeString() + ").", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setSamplingMode, this, _1)));
	addOption("canonicalize,C", "Canonicalize input molecules (default: false).", 
			  value<bool>(&canonicalize)->implicit_value(true));

	addOptionLongDescriptions();
}

const char* ConfGenImpl::getProgName() const
{
    return "ConfGen";
}

const char* ConfGenImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* ConfGenImpl::getProgAboutText() const
{
	return "Performs conformer generation for a set of input molecules.";
}

void ConfGenImpl::addOptionLongDescriptions()
{
	StringList formats;
	std::string formats_str = "Supported Input Formats:\n";

	AppUtils::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("input-format", 
							 "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");

	formats_str.pop_back();

	addOptionLongDescription("input", 
							 "Specifies one or more input file(s) with molecules for which conformers have to be generated.\n\n" +
							 formats_str);

	formats.clear();
	formats_str = "Supported Output Formats:\n";

	AppUtils::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("output-format", 
							 "Allows to explicitly specify the output format by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported)." +
							 "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

	formats_str.pop_back();

	addOptionLongDescription("output", 
							 "Specifies the output file where the generated conformers will be stored.\n\n" +
							 formats_str +
							 "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");
}

void ConfGenImpl::applyConfGenPreset(const std::string& pres_str)
{
	using namespace CDPL::ConfGen;

	std::string pres = pres_str;
	boost::to_upper(pres);

	if (pres == "SMALL_SET_DIVERSE")
		settings = ConformerGeneratorSettings::SMALL_SET_DIVERSE;
	else if (pres == "MEDIUM_SET_DIVERSE")
		settings = ConformerGeneratorSettings::MEDIUM_SET_DIVERSE;
	else if (pres == "LARGE_SET_DIVERSE")
		settings = ConformerGeneratorSettings::LARGE_SET_DIVERSE;
	else if (pres == "SMALL_SET_DENSE")
		settings = ConformerGeneratorSettings::SMALL_SET_DENSE;
	else if (pres == "MEDIUM_SET_DENSE")
		settings = ConformerGeneratorSettings::MEDIUM_SET_DENSE;
	else if (pres == "LARGE_SET_DENSE")
		settings = ConformerGeneratorSettings::LARGE_SET_DENSE;
	else 
		throwValidationError("conf-gen-preset");

	confGenPreset = pres;
}

void ConfGenImpl::applyFragBuildPreset(const std::string& pres_str)
{
	std::string pres = pres_str;
	boost::to_upper(pres);

	if (pres == "FAST")
		settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::FAST;
	else if (pres == "THOROUGH")
		settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::THOROUGH;
	else
		throwValidationError("frag-build-preset");

	fragBuildPreset = pres;
}

void ConfGenImpl::setSamplingMode(const std::string& mode_str)
{
	using namespace CDPL::ConfGen;

	std::string smpl_mode = mode_str;
	boost::to_upper(smpl_mode);

	if (smpl_mode == "AUTO")
		settings.setConformerSamplingMode(ConformerSamplingMode::AUTO);
	else if (smpl_mode == "SYSTEMATIC")
		settings.setConformerSamplingMode(ConformerSamplingMode::SYSTEMATIC);
	else if (smpl_mode == "STOCHASTIC")
		settings.setConformerSamplingMode(ConformerSamplingMode::STOCHASTIC);
	else
		throwValidationError("sampling-mode");
}

void ConfGenImpl::setTimeout(std::size_t timeout)
{
	settings.setTimeout(timeout * 1000);
}

void ConfGenImpl::setStrictParameterization(bool strict)
{
	settings.strictForceFieldParameterization(strict);
}

void ConfGenImpl::setForceFieldType(const std::string& type_str)
{
	using namespace CDPL::ConfGen;

	std::string uc_type = type_str;
	boost::to_upper(uc_type);

	if (uc_type == "MMFF94")
		settings.setForceFieldType(ForceFieldType::MMFF94);
	else if (uc_type == "MMFF94_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94_NO_ESTAT);
	else if (uc_type == "MMFF94S")
		settings.setForceFieldType(ForceFieldType::MMFF94S);
	else if (uc_type == "MMFF94S_EXT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_EXT);
	else if (uc_type == "MMFF94S_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_NO_ESTAT);
	else if (uc_type == "MMFF94S_EXT_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_EXT_NO_ESTAT);
	else
		throwValidationError("forcefield");
}

void ConfGenImpl::setRMSD(double rmsd)
{
	if (rmsd < 0)
		throwValidationError("rmsd");

	settings.setMinRMSD(rmsd);
}

void ConfGenImpl::setEnergyWindow(double ewin)
{
	if (ewin < 0)
		throwValidationError("e-window");

	settings.setEnergyWindow(ewin);
}

void ConfGenImpl::setMaxNumConfs(std::size_t max_confs)
{
	settings.setMaxNumOutputConformers( max_confs);
}

void ConfGenImpl::setInputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	inputHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

	if (!inputHandler)
		throwValidationError("input-format");
}

void ConfGenImpl::setOutputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	outputHandler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext);

	if (!outputHandler)
		throwValidationError("output-format");
}

int ConfGenImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	initInputReader();
	initOutputWriters();

	if (termSignalCaught())
		return EXIT_FAILURE;

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

void ConfGenImpl::processSingleThreaded()
{
	using namespace CDPL;

	ConformerGenerationWorker worker(this);

	worker();

	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;

	printStatistics(worker.getNumProcMolecules(), worker.getNumFailedMolecules(), worker.getNumGenConformers(),
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void ConfGenImpl::processMultiThreaded()
{
	using namespace CDPL;

	typedef boost::shared_ptr<ConformerGenerationWorker> ConformerGenerationWorkerPtr;
	typedef std::vector<ConformerGenerationWorkerPtr> ConformerGenerationWorkerList;

	boost::thread_group thread_grp;
	ConformerGenerationWorkerList worker_list;

	try {
		for (std::size_t i = 0; i < numThreads; i++) {
			if (termSignalCaught())
				break;

			ConformerGenerationWorkerPtr worker_ptr(new ConformerGenerationWorker(this));

			thread_grp.create_thread(boost::bind(&ConformerGenerationWorker::operator(), worker_ptr));
			worker_list.push_back(worker_ptr);
		}

	} catch (const std::exception& e) {
		setErrorMessage(std::string("error while creating worker-threads: ") + e.what());

	} catch (...) {
		setErrorMessage("unspecified error while creating worker-threads");
	}

	try {
		thread_grp.join_all();

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
	std::size_t num_gen_confs = 0;

	for (std::size_t i = 0; i < numThreads; i++) {
		const ConformerGenerationWorker& worker = *worker_list[i];

		num_proc_mols += worker.getNumProcMolecules();
		num_failed_mols += worker.getNumFailedMolecules();
		num_gen_confs += worker.getNumGenConformers();
	}

	printStatistics(num_proc_mols, num_failed_mols, num_gen_confs,
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());

}

void ConfGenImpl::setErrorMessage(const std::string& msg)
{
	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(mutex);

		if (errorMessage.empty())
			errorMessage = msg;
		return;
	}

	if (errorMessage.empty())
		errorMessage = msg;
}

bool ConfGenImpl::haveErrorMessage()
{
	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(mutex);
		return !errorMessage.empty();
	}

	return !errorMessage.empty();
}

void ConfGenImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols, std::size_t num_gen_confs, std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules:  " + boost::lexical_cast<std::string>(num_proc_mols));
	printMessage(INFO, " Molecules Failed:     " + boost::lexical_cast<std::string>(num_failed_mols));
	printMessage(INFO, " Generated Conformers: " + boost::lexical_cast<std::string>(num_gen_confs));
	printMessage(INFO, " Processing Time:      " + AppUtils::formatTimeDuration(proc_time));
	printMessage(INFO, "");
}

std::size_t ConfGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return 0;

	if (haveErrorMessage())
		return 0;

	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(readMolMutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

std::size_t ConfGenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
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

void ConfGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol)
{
	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(writeMolMutex);

		doWriteMolecule(mol);

	} else
		doWriteMolecule(mol);
}

void ConfGenImpl::doWriteMolecule(const CDPL::Chem::MolecularGraph& mol)
{
	if (!outputWriter->write(mol))
		throw CDPL::Base::IOError("could not write generated conformers");
}

void ConfGenImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");
}

void ConfGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
	if (numThreads == 0) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
	}

	boost::lock_guard<boost::mutex> lock(mutex);

	CmdLineBase::printMessage(level, msg, nl, file_only);
}

void ConfGenImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input File(s):                       " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(38, ' ') + *it);

	printMessage(VERBOSE, " Output File:                         " + outputFile);
	printMessage(VERBOSE, " Failed Molecule Output File:         " + (failedFile.empty() ? std::string("None") : failedFile));
 	printMessage(VERBOSE, " Conformer Generation Preset:         " + confGenPreset);
 	printMessage(VERBOSE, " Fragment Build Preset:               " + fragBuildPreset);
 	printMessage(VERBOSE, " Conformer Sampling Mode:             " + getSamplingModeString());
	printMessage(VERBOSE, " Max. Num. Output Conformers:         " + boost::lexical_cast<std::string>(settings.getMaxNumOutputConformers()));
	printMessage(VERBOSE, " Timeout:                             " + boost::lexical_cast<std::string>(settings.getTimeout() / 1000) + "s");
	printMessage(VERBOSE, " Min. RMSD:                           " + (boost::format("%.4f") % settings.getMinRMSD()).str());
	printMessage(VERBOSE, " Energy Window:                       " + boost::lexical_cast<std::string>(settings.getEnergyWindow()));
	printMessage(VERBOSE, " Strict Force Field Parameterization: " + std::string(settings.strictForceFieldParameterization() ? "Yes" : "No"));
	printMessage(VERBOSE, " Search Force Field Type:             " + getForceFieldTypeString(settings.getForceFieldType()));
	printMessage(VERBOSE, " Canonicalize Input Molecules:        " + std::string(canonicalize ? "Yes" : "No"));
	printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

	if (numThreads > 0)
		printMessage(VERBOSE, " Number of Threads:                   " + boost::lexical_cast<std::string>(numThreads));

	printMessage(VERBOSE, " Input File Format:                   " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Output File Format:                  " + (outputHandler ? outputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, "");
}

void ConfGenImpl::initInputReader()
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
		InputHandlerPtr input_handler = getInputHandler(file_path);

		if (!input_handler)
			throw Base::IOError("no input handler found for file '" + file_path + '\'');

		MoleculeReader::SharedPointer reader_ptr = input_handler->createReader(file_path);

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

	if (ConfGenImpl::termSignalCaught())
		return;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " input molecule(s)");
	printMessage(INFO, "");
}

void ConfGenImpl::initOutputWriters()
{
	using namespace CDPL;

	OutputHandlerPtr output_handler = getOutputHandler(outputFile);

	if (!output_handler)
		throw Base::IOError("no output handler found for file '" + outputFile + '\'');

	outputWriter = output_handler->createWriter(outputFile);

	setMultiConfExportParameter(*outputWriter, true);
}

ConfGenImpl::InputHandlerPtr ConfGenImpl::getInputHandler(const std::string& file_path) const
{
	if (inputHandler)
		return inputHandler;

	return AppUtils::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

ConfGenImpl::OutputHandlerPtr ConfGenImpl::getOutputHandler(const std::string& file_path) const
{
	if (outputHandler)
		return outputHandler;

	return AppUtils::getOutputHandler<CDPL::Chem::MolecularGraph>(file_path);
}

std::string ConfGenImpl::getForceFieldTypeString(unsigned int ff_type) const
{
	using namespace CDPL::ConfGen;

	if (ff_type == ForceFieldType::MMFF94)
		return "MMFF94";
	
	if (ff_type == ForceFieldType::MMFF94_NO_ESTAT)
		return "MMFF94_NO_ESTAT";

	if (ff_type == ForceFieldType::MMFF94S)
		return "MMFF94S";

	if (ff_type == ForceFieldType::MMFF94S_EXT)
		return "MMFF94S_EXT";
	
	if (ff_type == ForceFieldType::MMFF94S_NO_ESTAT)
		return "MMFF94S_NO_ESTAT";

	if (ff_type == ForceFieldType::MMFF94S_EXT_NO_ESTAT)
		return "MMFF94S_EXT_NO_ESTAT";
	
	return "UNKNOWN";
}

std::string ConfGenImpl::getSamplingModeString() const
{
	using namespace CDPL::ConfGen;

	unsigned int mode = settings.getConformerSamplingMode();

	if (mode == ConformerSamplingMode::AUTO)
		return "AUTO";
	
	if (mode == ConformerSamplingMode::SYSTEMATIC)
		return "SYSTEMATIC";

	if (mode == ConformerSamplingMode::STOCHASTIC)
		return "STOCHASTIC";
	
	return "UNKNOWN";
}

std::string ConfGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
	if (!getName(mol).empty())
		return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

	return createMoleculeIdentifier(rec_idx);
}

std::string ConfGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
	return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(inputReader.getNumRecords()));
}
