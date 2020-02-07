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
		parent(parent), numProcMols(0),	numFailedMols(0), numGenConfs(0) {

		confGen.setAbortCallback(boost::bind(&ConformerGenerationWorker::abort, this));
		confGen.getSettings() = parent->settings;

		if (parent->getVerbosityLevel() >= DEBUG)  
			confGen.setLogMessageCallback(boost::bind(&ConformerGenerationWorker::addToLogRecord, this, _1));
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

		std::size_t rec_idx = parent->readNextMolecule(molecule);

		if (!rec_idx)
			return false;

		try {
			timer.start();
			logRecordStream.str(std::string());
			verbLevel = parent->getVerbosityLevel();

			if (verbLevel >= DEBUG) 
				logRecordStream << std::endl << "- Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ':' << std::endl;	

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
			parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule) + ": " + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule));
		}

		return false;
	}

	void outputConformers(std::size_t rec_idx, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		std::size_t num_confs = confGen.getNumConformers();

		if (verbLevel == VERBOSE || (verbLevel == INFO && ret_code == ReturnCode::TIMEOUT)) {
			logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << 
				num_confs << (num_confs == 1 ? " Conf., " : " Confs., ") << timer.format(3, "%w") << 's';

			if (ret_code == ReturnCode::TIMEOUT)
				logRecordStream << ", timeout exceeded";

			logRecordStream << std::endl;
		}

		setMDLDimensionality(molecule, 3);

		confGen.setConformers(molecule);

		parent->writeMolecule(molecule);

		numGenConfs += num_confs;
	}

	void handleError(std::size_t rec_idx, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		numFailedMols++;

		if (verbLevel < ERROR || verbLevel >= DEBUG)
			return;

		verbLevel = ERROR;

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
				logRecordStream << "Unspecified error while processing molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << std::endl;
				return;
		}

		logRecordStream << "Error while processing molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << err_msg << std::endl;
	}

	void addToLogRecord(const std::string& msg) {
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
	inputHandler(), outputHandler(), outputWriter()
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output fragment library file.", 
			  value<std::string>(&outputFile)->required());
	addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(boost::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(boost::thread::hardware_concurrency()));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setInputFormat, this, _1)));
	addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setOutputFormat, this, _1)));
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

void ConfGenImpl::setNumThreads(std::size_t num_threads)
{
	std::cerr << "num_threads = " << std::endl;

	numThreads = num_threads;
}

int ConfGenImpl::process()
{
	startTime = Clock::now();

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
	printMessage(VERBOSE, " Input File(s):                     " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(36, ' ') + *it);

	printMessage(VERBOSE, " Output File:                       " + outputFile);
	printMessage(VERBOSE, " Multithreading:                    " + std::string(numThreads > 0 ? "Yes" : "No"));

	if (numThreads > 0)
		printMessage(VERBOSE, " Number of Threads:                 " + boost::lexical_cast<std::string>(numThreads));

	printMessage(VERBOSE, " Input File Format:                 " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Output File Format:                " + (outputHandler ? outputHandler->getDataFormat().getName() : std::string("Auto-detect")));
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

void ConfGenImpl::initOutputWriter()
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
