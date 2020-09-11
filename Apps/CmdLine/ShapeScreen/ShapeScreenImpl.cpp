/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ShapeScreenImpl.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include "CDPL/Shape/ScreeningProcessor.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "ShapeScreenImpl.hpp"


using namespace ShapeScreen;


class ShapeScreenImpl::InputScanProgressCallback
{

public:
    class Terminated : public std::exception {};

    InputScanProgressCallback(ShapeScreenImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

    void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (ShapeScreenImpl::termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
    }

private:
    ShapeScreenImpl* parent;
    double           offset;
    double           scale;
};


class ShapeScreenImpl::ScreeningWorker
{

public:
    ScreeningWorker(ShapeScreenImpl* parent): parent(parent) {}

    void operator()() {
    }

private:

    ShapeScreenImpl*                     parent;
    CDPL::Shape::ScreeningProcessor      screeningProc;
    CDPL::Chem::BasicMolecule            molecule;
};


ShapeScreenImpl::ShapeScreenImpl(): 
    numThreads(0), settings(), reportAll(false), outputQuery(true), scoreSDTags(true), queryNameSDTags(false), 
	queryMolIdxSDTags(true), queryConfIdxSDTags(true), dbMolIdxSDTags(false), dbConfIdxSDTags(true), 
	numBestHits(1000), maxNumHits(0), shapeScoreCutoff(0.0)
{
    addOption("query,q", "Query input file(s).", 
			  value<StringList>(&queryFiles)->multitoken()->required());
    addOption("database,d", "Screening database input file(s).", 
			  value<StringList>(&databaseFiles)->multitoken()->required());
    addOption("output,o", "Hit output file.", 
			  value<std::string>(&outputFile));
	addOption("report,r", "Report output file.", 
			  value<std::string>(&reportFile));
	addOption("report-all,e", "If specified, best overlay results of ALL database molecules get written to the report file "
			  "(default: false, i.e. only records for hit molecules are output).", 
			  value<bool>(&reportAll)->implicit_value(true));
	addOption("mode,m", "Screening mode specifying which of the obtained results for the query molecule are of interest.", // TODO
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setScreeningMode, this, _1)));
	addOption("score,s", "Primary scoring function that will be in effect for hit ranking and filtering operations.",  // TODO
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setScoringFunction, this, _1)));
	addOption("best-hits,b", "Maximum number of best scoring hits to output (default: " +
			  boost::lexical_cast<std::string>(numBestHits) + ").",
			  value<std::size_t>(&numBestHits));
	addOption("max-hits,n", "Maximum number of found hits at which the search will terminate (overrides the 'best-hits' option, default: 0 - no limit).",
			  value<std::size_t>(&maxNumHits));
	addOption("cutoff,x", "Score cutoff value which determines whether a database molecule is considered as a hit (default: 0.0 - no cutoff).",
			  value<double>()->notifier(boost::bind(&ShapeScreenImpl::setScoreCutoff, this, _1)));
	addOption("shape-tanimoto-cutoff,X", "Shape tanimoto score cutoff that will be used for hit identifiaction in addition to the value specified by the 'cutoff' "
			  "option (default: 0.0 - no cutoff).",
			  value<double>(&shapeScoreCutoff));
	addOption("score-only,y", "If specified, no shape overlay of the query and database molecules will be performed and the input "
			  "poses get scored as they are (default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setScoringOnly, this, _1)));
	addOption("opt-overlay,a", "Specifies whether or not to perform an overlay optimization of the generated starting poses "
			  "(only in effect if option 'score-only' is false, default: true).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setOverlayOptimization, this, _1)));
	addOption("output-query,u", "If specified, query molecules will be written at the beginning of the hit output file (default: true).",
			  value<bool>(&outputQuery)->implicit_value(true));
	addOption("single-conf-db,g", "If specified, conformers of the database molecules are treated as individual single conf. molecules (default: false).",
			  value<bool>()->notifier(boost::bind(&ShapeScreenImpl::setSingleConformerSearch, this, _1)));
	addOption("color-ftr-type,f", "Specifies which type of color features to generate and score (default: ).", // TODO
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setColorFeatureType, this, _1)));
	addOption("all-carbon,C", "If specified, every heavy atom is interpreted as carbon (default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setAllCarbonMode, this, _1)));
	addOption("shape-center-starts,S", "If specified, principal axes aligned starting poses will be generated where both shape centers are located at"
			  "origin the coordinates system (default: true).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setShapeCenterStarts, this, _1)));
	addOption("atom-center-starts,A", "If specified, principal axes aligned starting poses will be generated so that the center of the smaller "
			  "shape is located at all the heavy atom centers of the larger shape (default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setAtomCenterStarts, this, _1)));
	addOption("color-center-starts,C", "If specified, principal axes aligned starting poses will be generated so that the center of the smaller "
			  "shape is located at the color feature centers of the larger shape (default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::setColorFeatureCenterStarts, this, _1)));
	addOption("random-starts,R", "Generates the specified number of principal axes aligned starting poses with randomized shape center displacements"
			  "shape is located at all the heavy atom centers of the larger shape (default: false).",
			  value<std::size_t>()->notifier(boost::bind(&ShapeScreenImpl::setNumRandomStarts, this, _1)));
	addOption("score-sd-tags,E", "If true, score values will be appended as SD-block entries of the output hit molecules (default: true).",
			  value<bool>(&scoreSDTags)->implicit_value(true));
	addOption("query-name-sd-tags,N", "If true, the query molecule name will be appended to the SD-block of the output hit molecules (default: false).",
			  value<bool>(&queryNameSDTags)->implicit_value(true));
	addOption("query-idx-sd-tags,G", "If true, the query molecule index will be appended to the SD-block of the output hit molecules (default: true).",
			  value<bool>(&queryMolIdxSDTags)->implicit_value(true));
	addOption("query-conf-sd-tags,F", "If true, the query conformer index will be appended to the SD-block of the output hit molecules (default: true).",
			  value<bool>(&queryConfIdxSDTags)->implicit_value(true));
	addOption("db-idx-sd-tags,B", "If true, the database molecule index will be appended to the SD-block of the output hit molecules (default: false).",
			  value<bool>(&dbMolIdxSDTags)->implicit_value(true));
	addOption("db-conf-sd-tags,Y", "If true, the database conformer index will be appended to the SD-block of the output hit molecules (default: true).",
			  value<bool>(&dbConfIdxSDTags)->implicit_value(true));

    addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(boost::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(boost::thread::hardware_concurrency()));
	addOption("query-format,Q", "Query input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setQueryFormat, this, _1)));
	addOption("database-format,D", "Screening database input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setDatabaseFormat, this, _1)));
    addOption("output-format,O", "Hit output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setOutputFormat, this, _1)));
 
    addOptionLongDescriptions();
}

const char* ShapeScreenImpl::getProgName() const
{
    return "ShapeScreen";
}

const char* ShapeScreenImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* ShapeScreenImpl::getProgAboutText() const
{
    return "Performs a fast shape-based similarity screening of a set of query molecules against one or more molecule databases.\n\n";
}

void ShapeScreenImpl::addOptionLongDescriptions()
{
    StringList formats;
    std::string formats_str = "Supported Input Formats:\n";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

    addOptionLongDescription("query-format", 
							 "Allows to explicitly specify the format of the query molecule input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");
    addOptionLongDescription("database-format", 
							 "Allows to explicitly specify the format of the screening database input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");
    formats_str.pop_back();

    addOptionLongDescription("query", 
							 "Specifies one or more query molecule input file(s).\n\n" +
							 formats_str +
							 "\nNote that atom 3D-coordinates are required for the specified query molecules!");
    addOptionLongDescription("database", 
							 "Specifies one or more screening database input file(s).\n\n" +
							 formats_str +
							 "\nNote that atom 3D-coordinates are required for the screened database molecules!");

    formats.clear();
    formats_str = "Supported Output Formats:\n";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

    addOptionLongDescription("output-format", 
							 "Allows to explicitly specify the hit output file format by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported).");
    formats_str.pop_back();

    addOptionLongDescription("output", 
							 "Specifies the screening hit output file.\n\n" + formats_str);
}

void ShapeScreenImpl::setColorFeatureType(const std::string& type)
{
    using namespace CDPL;

    std::string lc_type = type;
    boost::to_lower(lc_type);

	// TODO
}

void ShapeScreenImpl::setScoringFunction(const std::string& func)
{
    using namespace CDPL;

    std::string lc_func = func;
    boost::to_lower(lc_func);

	// TODO
}

void ShapeScreenImpl::setScreeningMode(const std::string& mode)
{
    using namespace CDPL;

    std::string lc_mode = mode;
    boost::to_lower(lc_mode);

	// TODO
}

void ShapeScreenImpl::setNumRandomStarts(std::size_t num_starts)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setColorFeatureCenterStarts(bool col_ctr_starts)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setAtomCenterStarts(bool atom_ctr_starts)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setShapeCenterStarts(bool shp_ctr_starts)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setAllCarbonMode(bool all_c)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setOverlayOptimization(bool opt)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setScoringOnly(bool score_only)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setSingleConformerSearch(bool single_conf)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setScoreCutoff(double cutoff)
{
    using namespace CDPL;

	// TODO
}

void ShapeScreenImpl::setQueryFormat(const std::string& file_ext)
{
    using namespace CDPL;

    std::string lc_file_ext = file_ext;
    boost::to_lower(lc_file_ext);

    queryHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

    if (!queryHandler)
		throwValidationError("query-format");
}

void ShapeScreenImpl::setDatabaseFormat(const std::string& file_ext)
{
    using namespace CDPL;

    std::string lc_file_ext = file_ext;
    boost::to_lower(lc_file_ext);

    databaseHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

    if (!databaseHandler)
		throwValidationError("database-format");
}

void ShapeScreenImpl::setOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    std::string lc_file_ext = file_ext;
    boost::to_lower(lc_file_ext);

    outputHandler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext);

    if (!outputHandler)
		throwValidationError("output-format");
}

int ShapeScreenImpl::process()
{
    startTime = Clock::now();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

	checkOutputOptions();
    checkInputFiles();
    printOptionSummary();

	initQueryReader();
    initDatabaseReader();
    initOutputWriters();

    if (termSignalCaught())
		return EXIT_FAILURE;

    if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Screening Molecules...", true, true);
    } else
		printMessage(INFO, "Screening Molecules...");

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

void ShapeScreenImpl::processSingleThreaded()
{
    using namespace CDPL;

    ScreeningWorker worker(this);

    worker();

    printMessage(INFO, "");

    if (haveErrorMessage())
		return;

    if (termSignalCaught())
		return;

    printStatistics(boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void ShapeScreenImpl::processMultiThreaded()
{
    using namespace CDPL;

    typedef boost::shared_ptr<ScreeningWorker> ScreeningWorkerPtr;
    typedef std::vector<ScreeningWorkerPtr> ScreeningWorkerList;

    boost::thread_group thread_grp;
    ScreeningWorkerList worker_list;

    try {
		for (std::size_t i = 0; i < numThreads; i++) {
			if (termSignalCaught())
				break;

			ScreeningWorkerPtr worker_ptr(new ScreeningWorker(this));

			thread_grp.create_thread(boost::bind(&ScreeningWorker::operator(), worker_ptr));
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
	
    printStatistics(boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void ShapeScreenImpl::setErrorMessage(const std::string& msg)
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

bool ShapeScreenImpl::haveErrorMessage()
{
    if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(mutex);
		return !errorMessage.empty();
    }

    return !errorMessage.empty();
}

void ShapeScreenImpl::printStatistics(std::size_t proc_time)
{
    printMessage(INFO, "Statistics:");
  
    printMessage(INFO, " Processing Time:      " + CmdLineLib::formatTimeDuration(proc_time));

    printMessage(INFO, "");
}

std::size_t ShapeScreenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
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

std::size_t ShapeScreenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
    while (true) {
		try {
			if (databaseReader.getRecordIndex() >= databaseReader.getNumRecords()) 
				return 0;

			if (!databaseReader.read(mol)) {
				printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(databaseReader.getRecordIndex() + 1) + " failed");			
				
				databaseReader.setRecordIndex(databaseReader.getRecordIndex() + 1);
				continue;
			}

			printProgress("Screening Molecules...        ", double(databaseReader.getRecordIndex()) / databaseReader.getNumRecords());

			return databaseReader.getRecordIndex();

		} catch (const std::exception& e) {
			printMessage(ERROR, "Error while reading molecule " + createMoleculeIdentifier(databaseReader.getRecordIndex() + 1) + ": " + e.what());

		} catch (...) {
			printMessage(ERROR, "Unspecified error while reading molecule " + createMoleculeIdentifier(databaseReader.getRecordIndex() + 1));
		}

		databaseReader.setRecordIndex(databaseReader.getRecordIndex() + 1);
    }

    return 0;
}

void ShapeScreenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol)
{
    if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(writeMolMutex);

		doWriteMolecule(mol);

    } else
		doWriteMolecule(mol);
}

void ShapeScreenImpl::doWriteMolecule(const CDPL::Chem::MolecularGraph& mol)
{
    if (!outputWriter->write(mol))
		throw CDPL::Base::IOError("could not write hit molecule");
}

void ShapeScreenImpl::checkOutputOptions() const
{
}

void ShapeScreenImpl::checkInputFiles() const
{
    using namespace CDPL;

    StringList::const_iterator it = std::find_if(queryFiles.begin(), queryFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
    if (it != queryFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");

    if (std::find_if(queryFiles.begin(), queryFiles.end(),
					 boost::bind(Util::checkIfSameFile, boost::ref(outputFile),
								 _1)) != queryFiles.end())
		throw Base::ValueError("output file must not occur in list of query files");

	it = std::find_if(databaseFiles.begin(), databaseFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
    if (it != databaseFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");

    if (std::find_if(databaseFiles.begin(), databaseFiles.end(),
					 boost::bind(Util::checkIfSameFile, boost::ref(outputFile),
								 _1)) != databaseFiles.end())
		throw Base::ValueError("output file must not occur in list of database files");
}

void ShapeScreenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    if (numThreads == 0) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
    }

    boost::lock_guard<boost::mutex> lock(mutex);

    CmdLineBase::printMessage(level, msg, nl, file_only);
}

void ShapeScreenImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Query File(s):                       " + queryFiles[0]);
	
    for (StringList::const_iterator it = ++queryFiles.begin(), end = queryFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(38, ' ') + *it);

    printMessage(VERBOSE, " Database File(s):                    " + queryFiles[0]);
	
    for (StringList::const_iterator it = ++databaseFiles.begin(), end = databaseFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(38, ' ') + *it);

    printMessage(VERBOSE, " Hit Output File:                     " + outputFile);
    printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

    if (numThreads > 0)
		printMessage(VERBOSE, " Number of Threads:                   " + boost::lexical_cast<std::string>(numThreads));

	printMessage(VERBOSE, " Query File Format:                   " + (queryHandler ? queryHandler->getDataFormat().getName() : std::string("Auto-detect")));
    printMessage(VERBOSE, " Database File Format:                " + (databaseHandler ? databaseHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Hit File Format:                     " + (outputHandler ? outputHandler->getDataFormat().getName() : std::string("Auto-detect")));
    printMessage(VERBOSE, "");
}

void ShapeScreenImpl::initQueryReader()
{
    using namespace CDPL;

    std::size_t num_in_files = queryFiles.size();
	
    if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Scanning Query File(s)...", true, true);
    } else
		printMessage(INFO, "Scanning Query File(s)...");

    setMultiConfImportParameter(queryReader, true);
 
    for (std::size_t i = 0; i < num_in_files; i++) {
		if (termSignalCaught())
			return;

		const std::string& file_path = queryFiles[i];
		InputHandlerPtr query_handler = getQueryHandler(file_path);

		if (!query_handler)
			throw Base::IOError("no input handler found for file '" + file_path + '\'');

		MoleculeReader::SharedPointer reader_ptr = query_handler->createReader(file_path);

		setMultiConfImportParameter(*reader_ptr, true);

		std::size_t cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

		try {
			queryReader.addReader(reader_ptr);

		} catch (const InputScanProgressCallback::Terminated&) {
			reader_ptr->unregisterIOCallback(cb_id);
			break;
		}

		reader_ptr->unregisterIOCallback(cb_id);
    }

    if (ShapeScreenImpl::termSignalCaught())
		return;

    printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(queryReader.getNumRecords()) + " query molecule(s)");
    printMessage(INFO, "");
}

void ShapeScreenImpl::initDatabaseReader()
{
    using namespace CDPL;

    std::size_t num_in_files = databaseFiles.size();
	
    if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Scanning Database File(s)...", true, true);
    } else
		printMessage(INFO, "Scanning Database File(s)...");

    setMultiConfImportParameter(databaseReader, true);

    for (std::size_t i = 0; i < num_in_files; i++) {
		if (termSignalCaught())
			return;

		const std::string& file_path = databaseFiles[i];
		InputHandlerPtr database_handler = getDatabaseHandler(file_path);

		if (!database_handler)
			throw Base::IOError("no input handler found for file '" + file_path + '\'');

		MoleculeReader::SharedPointer reader_ptr = database_handler->createReader(file_path);

		setMultiConfImportParameter(*reader_ptr, true);

		std::size_t cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

		try {
			databaseReader.addReader(reader_ptr);

		} catch (const InputScanProgressCallback::Terminated&) {
			reader_ptr->unregisterIOCallback(cb_id);
			break;
		}

		reader_ptr->unregisterIOCallback(cb_id);
    }

    if (ShapeScreenImpl::termSignalCaught())
		return;

    printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(databaseReader.getNumRecords()) + " database molecule(s)");
    printMessage(INFO, "");
}

void ShapeScreenImpl::initOutputWriters()
{
    using namespace CDPL;

    OutputHandlerPtr output_handler = getOutputHandler(outputFile);

    if (!output_handler)
		throw Base::IOError("no output handler found for file '" + outputFile + '\'');

    outputWriter = output_handler->createWriter(outputFile);

    setMultiConfExportParameter(*outputWriter, false);
    setSMILESRecordFormatParameter(*outputWriter, "SN");
}

ShapeScreenImpl::InputHandlerPtr ShapeScreenImpl::getQueryHandler(const std::string& file_path) const
{
    if (queryHandler)
		return queryHandler;

    return CmdLineLib::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

ShapeScreenImpl::InputHandlerPtr ShapeScreenImpl::getDatabaseHandler(const std::string& file_path) const
{
    if (databaseHandler)
		return databaseHandler;

    return CmdLineLib::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

ShapeScreenImpl::OutputHandlerPtr ShapeScreenImpl::getOutputHandler(const std::string& file_path) const
{
    if (outputHandler)
		return outputHandler;

    return CmdLineLib::getOutputHandler<CDPL::Chem::MolecularGraph>(file_path);
}

std::string ShapeScreenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(databaseReader.getNumRecords()));
}
