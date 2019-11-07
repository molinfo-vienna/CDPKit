/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDCreateImpl.cpp
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


#include <cstdlib>
#include <algorithm>
#include <iterator>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Util/FileRemover.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Lib/HelperFunctions.hpp"

#include "PSDCreateImpl.hpp"


using namespace PSDCreate;


class PSDCreateImpl::InputScanProgressCallback
{

public:
	class Terminated : public std::exception {};

	InputScanProgressCallback(PSDCreateImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (PSDCreateImpl::termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
	}

private:
	PSDCreateImpl* parent;
	double         offset;
	double         scale;
};

struct PSDCreateImpl::MergeDBsProgressCallback
{

	MergeDBsProgressCallback(PSDCreateImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	bool operator()(double progress) const {
		if (PSDCreateImpl::termSignalCaught())
			return false;

		parent->printProgress("Merging Temporary Databases... ", offset + scale * progress);
		return true;
	}

	PSDCreateImpl* parent;
	double         offset;
	double         scale;
};

struct PSDCreateImpl::DBCreationWorker
{

	typedef CDPL::Pharm::ScreeningDBCreator::SharedPointer ScrenningDBCreatorPtr;

	DBCreationWorker(PSDCreateImpl* parent, const ScrenningDBCreatorPtr& db_creator):
		parent(parent), dbCreator(db_creator) {}

	void operator()() {
		try {
			CDPL::Chem::BasicMolecule mol;

			while (parent->readNextMolecule(mol)) {
				perceiveComponents(mol, false);
				perceiveSSSR(mol, false);
				setRingFlags(mol, false);
				calcImplicitHydrogenCounts(mol, false);
				perceiveHybridizationStates(mol, false);
				setAromaticityFlags(mol, false);
				calcCIPPriorities(mol, false);
				calcAtomCIPConfigurations(mol, false);
				calcBondCIPConfigurations(mol, false);

				dbCreator->process(mol);
			}

		} catch (const std::exception& e) {
			parent->setErrorMessage(std::string("error while creating database: ") + e.what());

		} catch (...) {
			parent->setErrorMessage("error while creating database");
		}
	}

	PSDCreateImpl*        parent;
	ScrenningDBCreatorPtr dbCreator;
};


PSDCreateImpl::PSDCreateImpl(): 
	dropDuplicates(false), multiThreading(false), numThreads(boost::thread::hardware_concurrency()), 
	creationMode(CDPL::Pharm::ScreeningDBCreator::CREATE), inputHandler(), addSourceFileProp(false)
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output database file.", 
			  value<std::string>(&outputDatabase)->required());
	addOption("mode,m", "Database creation mode (CREATE, APPEND, UPDATE, default: CREATE).", 
			  value<std::string>()->notifier(boost::bind(&PSDCreateImpl::setCreationMode, this, _1)));
	addOption("drop-duplicates,d", "Drop duplicate molecules (default: false).", 
			  value<bool>(&dropDuplicates)->implicit_value(true));
	addOption("multi-threading,t", "Enable multi-threaded processing (default: false).", 
			  value<bool>(&multiThreading)->implicit_value(true));
	addOption("num-threads,n", "Number of parallel threads (default: " + boost::lexical_cast<std::string>(numThreads) + " threads, must be > 0).", 
			  value<unsigned int>()->notifier(boost::bind(&PSDCreateImpl::setMaxNumThreads, this, _1)));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&PSDCreateImpl::setInputFormat, this, _1)));
	addOption("tmp-file-dir,T", "Temporary file directory (default: '" + boost::filesystem::temp_directory_path().string() + "')", 
			  value<std::string>()->notifier(boost::bind(&PSDCreateImpl::setTmpFileDirectory, this, _1)));
	addOption("add-src-file-prop,s", "Add a source-file property to output molecules (default: false).", 
			  value<bool>(&addSourceFileProp)->implicit_value(true));

	addOptionLongDescriptions();
}

const char* PSDCreateImpl::getProgName() const
{
    return "PSDCreate";
}

const char* PSDCreateImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* PSDCreateImpl::getProgAboutText() const
{
	return "Creates a pharmacophore-screening database file from one or more molecule input files.";
}

void PSDCreateImpl::addOptionLongDescriptions()
{
	StringList formats;
	std::string formats_str = "Supported Input Formats:\n";

	AppUtils::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("input", 
							 "Specifies one or more input file(s) with molecules that shall be stored in the created database.\n\n" +
							 formats_str +
							 "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

	addOptionLongDescription("input-format", 
							 "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).\n"
							 "Note that only storage formats make sense that allow to store atom 3D-coordinates!");
}

void PSDCreateImpl::setCreationMode(const std::string& mode)
{
	using namespace CDPL::Pharm;

	std::string uc_mode = mode;
	boost::to_upper(uc_mode);

	if (uc_mode == "CREATE")
		creationMode = ScreeningDBCreator::CREATE;
	else if (uc_mode == "APPEND")
		creationMode = ScreeningDBCreator::APPEND;
	else if (uc_mode == "UPDATE")
		creationMode = ScreeningDBCreator::UPDATE;
	else
		throwValidationError("mode");
}

void PSDCreateImpl::setInputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	inputHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

	if (!inputHandler)
		throwValidationError("input-format");
}

void PSDCreateImpl::setMaxNumThreads(unsigned int num_threads)
{
	if (num_threads < 1)
		throwValidationError("num-threads");

	numThreads = num_threads;
}

void PSDCreateImpl::setTmpFileDirectory(const std::string& dir_path)
{
	namespace bfs = boost::filesystem;

	if (!bfs::exists(dir_path) || !bfs::is_directory(dir_path))
		throwValidationError("tmp-file-dir");

#ifdef _WIN32
	_putenv_s("TMPDIR", dir_path.c_str());
	_putenv_s("TMP", dir_path.c_str());
	_putenv_s("TEMP", dir_path.c_str());
	_putenv_s("TEMPDIR", dir_path.c_str());
#else
	setenv("TMPDIR", dir_path.c_str(), 1);
	setenv("TMP", dir_path.c_str(), 1);
	setenv("TEMP", dir_path.c_str(), 1);
	setenv("TEMPDIR", dir_path.c_str(), 1);
#endif
}

int PSDCreateImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();
	initInputReader();

	if (termSignalCaught())
		return EXIT_FAILURE;

	if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Creating Database(s)...", true, true);
	} else
		printMessage(INFO, "Creating Database(s)...");

	if (multiThreading)
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

void PSDCreateImpl::processSingleThreaded()
{
	using namespace CDPL;

	Pharm::ScreeningDBCreator::SharedPointer db_creator(
		new Pharm::PSDScreeningDBCreator(outputDatabase, creationMode, !dropDuplicates));

	DBCreationWorker(this, db_creator)();

	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;

	printStatistics(db_creator->getNumProcessed(), db_creator->getNumRejected(),
					db_creator->getNumDeleted(), db_creator->getNumInserted(),
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void PSDCreateImpl::processMultiThreaded()
{
	using namespace CDPL;

	typedef Pharm::ScreeningDBCreator::SharedPointer DBCreatorPtr;
	typedef std::vector<Util::FileRemover> DBFileList;
	typedef std::vector<DBCreatorPtr> DBCreatorList;

	boost::thread_group thread_grp;
	DBCreatorList tmp_db_creators;
	DBFileList tmp_db_files(numThreads - 1, Util::FileRemover(""));

	DBCreatorPtr main_db_creator(new Pharm::PSDScreeningDBCreator(outputDatabase, creationMode, !dropDuplicates));
	
	try {
		thread_grp.create_thread(DBCreationWorker(this, main_db_creator));

		for (std::size_t i = 0; i < numThreads - 1; i++) {
			if (termSignalCaught())
				break;

			std::string tmp_db_name = Util::genCheckedTempFilePath();

			tmp_db_files[i].reset(tmp_db_name);

			DBCreatorPtr tmp_db_creator(new Pharm::PSDScreeningDBCreator(tmp_db_name, creationMode, !dropDuplicates));

			thread_grp.create_thread(DBCreationWorker(this, tmp_db_creator));
			tmp_db_creators.push_back(tmp_db_creator);
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
	
	std::size_t num_proc = main_db_creator->getNumProcessed();
	std::size_t num_rej = 0;

	if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Merging Temporary Databases...", true, true);
	} else
		printMessage(INFO, "Merging Temporary Databases...");

	for (std::size_t i = 0; i < numThreads - 1; i++) {
		if (termSignalCaught())
			return;

		num_proc += tmp_db_creators[i]->getNumProcessed();
		num_rej  += tmp_db_creators[i]->getNumRejected();

		tmp_db_creators[i]->close();

		Pharm::PSDScreeningDBAccessor db_acc(tmp_db_files[i].getPath());

		main_db_creator->merge(db_acc, MergeDBsProgressCallback(this, i * 1.0 / (numThreads - 1), 1.0 / (numThreads - 1)));
	}

	printMessage(INFO, "");

	if (termSignalCaught())
		return;

	std::size_t num_del = main_db_creator->getNumDeleted();
	std::size_t num_ins = main_db_creator->getNumInserted();

	num_rej += main_db_creator->getNumRejected();

	printStatistics(num_proc, num_rej, num_del, num_ins,
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void PSDCreateImpl::setErrorMessage(const std::string& msg)
{
	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);

		if (errorMessage.empty())
			errorMessage = msg;
		return;
	}

	if (errorMessage.empty())
		errorMessage = msg;
}

bool PSDCreateImpl::haveErrorMessage()
{
	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);
		return !errorMessage.empty();
	}

	return !errorMessage.empty();
}

void PSDCreateImpl::printStatistics(std::size_t num_proc, std::size_t num_rej, 
									std::size_t num_del, std::size_t num_ins,
									std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules: " + boost::lexical_cast<std::string>(num_proc));
	printMessage(INFO, " Rejected  Molecules: " + boost::lexical_cast<std::string>(num_rej));
	printMessage(INFO, " Deleted Molecules:   " + boost::lexical_cast<std::string>(num_del));
	printMessage(INFO, " Inserted Molecules:  " + boost::lexical_cast<std::string>(num_ins));
	printMessage(INFO, " Processing Time:     " + AppUtils::formatTimeDuration(proc_time));
}

bool PSDCreateImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return false;

	if (haveErrorMessage())
		return false;

	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(molReadMutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

bool PSDCreateImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
	while (true) {
		try {
			if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
				return false;

			printMessage(DEBUG, "Starting to process molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) +  '/' +
						 boost::lexical_cast<std::string>(inputReader.getNumRecords()) + "...");

			if (!inputReader.read(mol)) {
				printMessage(ERROR, "Reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
							 boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " failed");			
				
				inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
				return false;
			}

			if (addSourceFileProp) {
				std::size_t reader_id = inputReader.getReaderIDForRecordIndex(inputReader.getRecordIndex() - 1);

				if (reader_id != 0) {
					CDPL::Chem::StringDataBlock::SharedPointer sd_ptr = getStructureData(mol);

					sd_ptr->addEntry("<Source File>", boost::filesystem::path(inputFiles[reader_id - 1]).filename().string());
				}
			}

			std::string msg;

			if (!multiThreading)
				msg = "Creating Database...           ";
			else
				msg = "Creating Temporary Databases...";

			printProgress(msg, double(inputReader.getRecordIndex()) / inputReader.getNumRecords());
			return true;

		} catch (const std::exception& e) {
			printMessage(ERROR, "Error while reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
						 boost::lexical_cast<std::string>(inputReader.getNumRecords()) + ": " + e.what());

		} catch (...) {
			printMessage(ERROR, "Error while reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
						 boost::lexical_cast<std::string>(inputReader.getNumRecords()));
		}

		inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
	}

	return false;
}

void PSDCreateImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");
			
														 
	if (std::find_if(inputFiles.begin(), inputFiles.end(),
					 boost::bind(Util::checkIfSameFile, boost::ref(outputDatabase),
								 _1)) != inputFiles.end())
		throw Base::ValueError("output file must not occur in list of input files");
}

void PSDCreateImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input File(s):            " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(27, ' ') + *it);

	printMessage(VERBOSE, " Output Database:          " + outputDatabase);
 	printMessage(VERBOSE, " Creation Mode:            " + getCreationModeString());
 	printMessage(VERBOSE, " Drop Duplicates:          " + std::string(dropDuplicates ? "Yes" : "No"));
	printMessage(VERBOSE, " Multi-threading:          " + std::string(multiThreading ? "Yes" : "No"));
	printMessage(VERBOSE, " Number of Threads:        " + boost::lexical_cast<std::string>(numThreads));
	printMessage(VERBOSE, " Input File Format:        " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
 	printMessage(VERBOSE, " Add Source-File Property: " + std::string(addSourceFileProp ? "Yes" : "No"));

	if (wasOptionSet("tmp-file-dir"))
		printMessage(VERBOSE, " Temp. File Directory:     " + getOptionValue<std::string>("tmp-file-dir"));

	printMessage(VERBOSE, "");
}

void PSDCreateImpl::initInputReader()
{
	using namespace CDPL;

	std::size_t num_in_files = inputFiles.size();

	if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Scanning Input File(s)...", true, true);
	} else
		printMessage(INFO, "Scanning Input File(s)...");

	setMultiConfImportParameter(inputReader, true);

	for (std::size_t i = 0; i < num_in_files; i++) {
		if (termSignalCaught())
			return;

		const std::string& file_path = inputFiles[i];
		InputHandlerPtr input_handler = getInputHandler(file_path);

		if (!input_handler)
			throw Base::IOError("no input handler found for file '" + file_path + '\'');

		MoleculeReader::SharedPointer reader_ptr = input_handler->createReader(file_path);
		std::size_t cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

		try {
			inputReader.addReader(reader_ptr);

		} catch (const InputScanProgressCallback::Terminated&) {
			reader_ptr->unregisterIOCallback(cb_id);
			break;
		}

		reader_ptr->unregisterIOCallback(cb_id);
	}

	if (PSDCreateImpl::termSignalCaught())
		return;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " input molecule(s)");
	printMessage(INFO, "");
}

PSDCreateImpl::InputHandlerPtr PSDCreateImpl::getInputHandler(const std::string& file_path) const
{
	if (inputHandler)
		return inputHandler;

	return AppUtils::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

std::string PSDCreateImpl::getCreationModeString() const
{
	using namespace CDPL;

	if (creationMode == Pharm::ScreeningDBCreator::CREATE)
		return "CREATE";

	if (creationMode == Pharm::ScreeningDBCreator::APPEND)
		return "APPEND";

	if (creationMode == Pharm::ScreeningDBCreator::UPDATE)
		return "UPDATE";
	
	return "UNKNOWN";
}
