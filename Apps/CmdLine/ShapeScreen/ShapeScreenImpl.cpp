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
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Shape/ScreeningProcessor.hpp"
#include "CDPL/Shape/ScoringFunctors.hpp"
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

    InputScanProgressCallback(ShapeScreenImpl* parent): parent(parent) {}

    void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (ShapeScreenImpl::termSignalCaught())
			throw Terminated();

		parent->printInfiniteProgress("Scanning Input File(s)");
    }

private:
    ShapeScreenImpl* parent;
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
    scoringFunc("TANIMOTO_COMBO"), numThreads(0), settings(), scoringOnly(false), mergeHitLists(false), 
	splitOutFiles(true), reportAll(false), outputQuery(true), scoreSDTags(true), queryNameSDTags(false), 
	queryMolIdxSDTags(false), queryConfIdxSDTags(true), dbMolIdxSDTags(false), dbConfIdxSDTags(true),
	colorCenterStarts(false), atomCenterStarts(false), shapeCenterStarts(true),
	hitNamePattern("@D@_@q@_@d@"), numBestHits(1000), maxNumHits(0), shapeScoreCutoff(0.0)
{
   	addOption("query,q", "Query molecule file.", 
			  value<std::string>(&queryFile)->required());
    addOption("database,d", "Screened database file(s).", 
			  value<std::string>(&databaseFile)->required());
    addOption("output,o", "Screening hit output file.", 
			  value<std::string>(&outputFile));
	addOption("report,r", "Report output file.", 
			  value<std::string>(&reportFile));
	addOption("mode,m", "Screening mode specifying which of the obtained results for the query molecule are of interest "
			  "(BEST_OVERALL, BEST_PER_QUERY, BEST_PER_QUERY_CONF, default: BEST_PER_QUERY).",
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setScreeningMode, this, _1)));
	addOption("score,s", "Primary scoring function that will be in effect for hit identification and ranking operations "
			  "(TOTAL_OVERLAP_TANIMOTO, SHAPE_TANIMOTO, COLOR_TANIMOTO, TANIMOTO_COMBO, TOTAL_OVERLAP_TVERSKY, SHAPE_TVERSKY, "
			  "COLOR_TVERSKY, TVERSKY_COMBO, QUERY_TOTAL_OVERLAP_TVERSKY, QUERY_SHAPE_TVERSKY, QUERY_COLOR_TVERSKY, "
			  "QUERY_TVERSKY_COMBO, DB_TOTAL_OVERLAP_TVERSKY, DB_SHAPE_TVERSKY, DB_COLOR_TVERSKY, DB_TVERSKY_COMBO, "
			  "default: " + scoringFunc + ")",
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
	addOption("merge-hits,M", "If true, identified hits are merged into a single, combined hit list. "
			  "If false, a separate hit list for every query molecule will be maintained (default: false).", 
			  value<bool>(&mergeHitLists)->implicit_value(true));
	addOption("split-output,P", "If true, for every query molecule a separate report and hit output file will be written (default: true).", 
			  value<bool>(&splitOutFiles)->implicit_value(true));
	addOption("report-all,e", "If specified, best overlay results of ALL database molecules get written to the report file "
			  "(default: false, i.e. only records for hit molecules are output).", 
			  value<bool>(&reportAll)->implicit_value(true));
	addOption("score-only,y", "If specified, no shape overlay of the query and database molecules will be performed and the input "
			  "poses get scored as they are (default: false).",
			  value<bool>(&scoringOnly)->implicit_value(true));
	addOption("opt-overlay,a", "Specifies whether or not to perform an overlay optimization of the generated starting poses "
			  "(only in effect if option 'score-only' is false, default: true).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::performOverlayOptimization, this, _1)));
	addOption("thorough-overlay-opt,z", "Specifies whether or not to perform a thorough overlay optimization of the generated starting poses "
			  "(note: the screening time will increase significantly, default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::performThoroughOverlayOptimization, this, _1)));
	addOption("output-query,u", "If specified, query molecules will be written at the beginning of the hit output file (default: true).",
			  value<bool>(&outputQuery)->implicit_value(true));
	addOption("single-conf-db,g", "If specified, conformers of the database molecules are treated as individual single conf. molecules (default: false).",
			  value<bool>()->notifier(boost::bind(&ShapeScreenImpl::performSingleConformerSearch, this, _1)));
	addOption("color-ftr-type,f", "Specifies which type of color features to generate and score "
			  "(NONE, EXP_PHARM, IMP_PHARM, default: IMP_PHARM).",
			  value<std::string>()->notifier(boost::bind(&ShapeScreenImpl::setColorFeatureType, this, _1)));
	addOption("all-carbon,C", "If specified, every heavy atom is interpreted as carbon (default: false).",
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ShapeScreenImpl::enableAllCarbonMode, this, _1)));
	addOption("shape-center-starts,S", "If specified, principal axes aligned starting poses will be generated where both shape centers are located at"
			  "origin the coordinates system (default: true).",
			  value<bool>(&shapeCenterStarts)->implicit_value(true));
	addOption("atom-center-starts,A", "If specified, principal axes aligned starting poses will be generated so that the center of the smaller "
			  "shape is located at all the heavy atom centers of the larger shape (default: false).",
			  value<bool>(&atomCenterStarts)->implicit_value(true));
	addOption("color-center-starts,C", "If specified, principal axes aligned starting poses will be generated so that the center of the smaller "
			  "shape is located at the color feature centers of the larger shape (default: false).",
			  value<bool>(&colorCenterStarts)->implicit_value(true));
	addOption("random-starts,R", "Generates the specified number of principal axes aligned starting poses with randomized shape center displacements"
			  "shape is located at all the heavy atom centers of the larger shape (default: 0).",
			  value<std::size_t>()->notifier(boost::bind(&ShapeScreenImpl::setNumRandomStarts, this, _1)));
	addOption("score-sd-tags,E", "If true, score values will be appended as SD-block entries of the output hit molecules (default: true).",
			  value<bool>(&scoreSDTags)->implicit_value(true));
	addOption("query-name-sd-tags,N", "If true, the query molecule name will be appended to the SD-block of the output hit molecules (default: false).",
			  value<bool>(&queryNameSDTags)->implicit_value(true));
	addOption("query-idx-sd-tags,G", "If true, the query molecule index will be appended to the SD-block of the output hit molecules (default: false).",
			  value<bool>(&queryMolIdxSDTags)->implicit_value(true));
	addOption("query-conf-sd-tags,F", "If true, the query conformer index will be appended to the SD-block of the output hit molecules (default: true).",
			  value<bool>(&queryConfIdxSDTags)->implicit_value(true));
	addOption("db-idx-sd-tags,B", "If true, the database molecule index will be appended to the SD-block of the output hit molecules (default: false).",
			  value<bool>(&dbMolIdxSDTags)->implicit_value(true));
	addOption("db-conf-sd-tags,Y", "If true, the database conformer index will be appended to the SD-block of the output hit molecules (default: true).",
			  value<bool>(&dbConfIdxSDTags)->implicit_value(true));
	addOption("hit-name-ptn,T", "Pattern for composing the names of output hit molecules by variable substitution (supported variables: @Q@ = query molecule name, "
			  "@D@ = database molecule name, @C@ = query molecule conformer index, @c@ = database molecule conformer index, @I@ = query molecule index "
			  "and @i@ = database molecule index, default: @D@_@q@_@d@).",
			  value<std::string>(&hitNamePattern));
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
    return "Performs a fast shape-based similarity screening of molecule databases.\n\n";
}

void ShapeScreenImpl::addOptionLongDescriptions()
{
	
	typedef std::vector<std::string> StringList;

	StringList formats;
    std::string formats_str = "Supported Input Formats:\n";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

    addOptionLongDescription("query-format", 
							 "Allows to explicitly specify the format of the query molecule file by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported).");
    addOptionLongDescription("database-format", 
							 "Allows to explicitly specify the format of the screening database file by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");
    formats_str.pop_back();

    addOptionLongDescription("query", 
							 "The query molecule input file.\n\n" +
							 formats_str +
							 "\nNote that atom 3D-coordinates are required for shape screening!");
    addOptionLongDescription("database", 
							 "The screened database input file.\n\n" +
							 formats_str +
							 "\nNote that atomic 3D-coordinates are required for shape screening!");

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
							 "Screening hit output file.\n\n" + formats_str);
}

void ShapeScreenImpl::setNumRandomStarts(std::size_t num_starts)
{
	settings.setNumRandomStarts(num_starts);
}

void ShapeScreenImpl::setColorFeatureType(const std::string& type)
{
	settings.setColorFeatureType(stringToColorFeatureType(type));
}

void ShapeScreenImpl::setScoringFunction(const std::string& func)
{
    using namespace CDPL::Shape;
	namespace po = boost::program_options;

	scoringFunc = func;
	boost::to_upper(scoringFunc);

	if (scoringFunc == "TOTAL_OVERLAP_TANIMOTO")
		settings.setScoringFunction(TotalOverlapTanimotoScore());

	else if (scoringFunc == "SHAPE_TANIMOTO")
		settings.setScoringFunction(ShapeTanimotoScore());

	else if (scoringFunc == "COLOR_TANIMOTO")
		settings.setScoringFunction(ColorTanimotoScore());

	else if (scoringFunc == "TANIMOTO_COMBO")
		settings.setScoringFunction(TanimotoComboScore());

	else if (scoringFunc == "TOTAL_OVERLAP_TVERSKY")
		settings.setScoringFunction(TotalOverlapTverskyScore());

	else if (scoringFunc == "SHAPE_TVERSKY")
		settings.setScoringFunction(ShapeTverskyScore());

	else if (scoringFunc == "COLOR_TVERSKY")
		settings.setScoringFunction(ColorTverskyScore());

	else if (scoringFunc == "TVERSKY_COMBO")
		settings.setScoringFunction(TverskyComboScore());

	else if (scoringFunc == "QUERY_TOTAL_OVERLAP_TVERSKY")
		settings.setScoringFunction(ReferenceTotalOverlapTverskyScore());

	else if (scoringFunc == "QUERY_SHAPE_TVERSKY")
		settings.setScoringFunction(ReferenceShapeTverskyScore());

	else if (scoringFunc == "QUERY_COLOR_TVERSKY")
		settings.setScoringFunction(ReferenceColorTverskyScore());

	else if (scoringFunc == "QUERY_TVERSKY_COMBO")
		settings.setScoringFunction(ReferenceTverskyComboScore());

	else if (scoringFunc == "DB_TOTAL_OVERLAP_TVERSKY")
		settings.setScoringFunction(AlignedTotalOverlapTverskyScore());

	else if (scoringFunc == "DB_SHAPE_TVERSKY")
		settings.setScoringFunction(AlignedShapeTverskyScore());

	else if (scoringFunc == "DB_COLOR_TVERSKY")
		settings.setScoringFunction(AlignedColorTverskyScore());

	else if (scoringFunc == "DB_TVERSKY_COMBO")		
		settings.setScoringFunction(AlignedTverskyComboScore());

	else
		throwValidationError("score");
}

void ShapeScreenImpl::setScreeningMode(const std::string& mode)
{
    settings.setScreeningMode(stringToScreeningMode(mode));
}

void ShapeScreenImpl::enableAllCarbonMode(bool all_c)
{
	settings.allCarbonMode(all_c);
}

void ShapeScreenImpl::performOverlayOptimization(bool opt)
{
	settings.optimizeOverlap(opt);
}

void ShapeScreenImpl::performThoroughOverlayOptimization(bool thorough)
{
	settings.greedyOptimization(!thorough);
}

void ShapeScreenImpl::performSingleConformerSearch(bool single_conf)
{
	settings.singleConformerSearch(single_conf);
}

void ShapeScreenImpl::setScoreCutoff(double cutoff)
{
	settings.setScoreCutoff(cutoff);
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

void ShapeScreenImpl::setAlignmentMode()
{
	if (scoringOnly)
		settings.setAlignmentMode(ScreeningSettings::NO_ALIGNMENT);

	else {
		int mode = 0;

		if (shapeCenterStarts) 
			mode |= ScreeningSettings::SHAPE_CENTROID;

		if (atomCenterStarts)
			mode |= ScreeningSettings::ATOM_CENTERS;

		if (colorCenterStarts)
			mode |= ScreeningSettings::COLOR_FEATURE_CENTERS;

		if (settings.getNumRandomStarts() > 0)
			mode |= ScreeningSettings::RANDOM;

		settings.setAlignmentMode(ScreeningSettings::AlignmentMode(mode));
	}
}

int ShapeScreenImpl::process()
{
    startTime = Clock::now();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

	checkOutputFileOptions();
    checkInputFiles();
    printOptionSummary();

	initQueryReader();
    initDatabaseReader();
	setAlignmentMode();

    if (termSignalCaught())
		return EXIT_FAILURE;

    if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Screening Molecules", true, true);
    } else
		printMessage(INFO, "Screening Molecules");

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
			if (databaseReader->getRecordIndex() >= databaseReader->getNumRecords()) 
				return 0;

			if (!databaseReader->read(mol)) {
				printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(databaseReader->getRecordIndex() + 1) + " failed");			
				
				databaseReader->setRecordIndex(databaseReader->getRecordIndex() + 1);
				continue;
			}

			printInfiniteProgress("Screening Molecules");

			return databaseReader->getRecordIndex();

		} catch (const std::exception& e) {
			printMessage(ERROR, "Error while reading molecule " + createMoleculeIdentifier(databaseReader->getRecordIndex() + 1) + ": " + e.what());

		} catch (...) {
			printMessage(ERROR, "Unspecified error while reading molecule " + createMoleculeIdentifier(databaseReader->getRecordIndex() + 1));
		}

		databaseReader->setRecordIndex(databaseReader->getRecordIndex() + 1);
    }

    return 0;
}

void ShapeScreenImpl::checkOutputFileOptions() const
{
	if (outputFile.empty() && reportFile.empty())
		throw CDPL::Base::ValueError("A hit output and/or report file has to be specified");
}

void ShapeScreenImpl::checkInputFiles() const
{
    using namespace CDPL;

    if (!Util::fileExists(queryFile))
		throw Base::IOError("query file '" + queryFile + "' does not exist");

    if (!Util::fileExists(databaseFile))
		throw Base::IOError("database file '" + databaseFile + "' does not exist");

	if (!splitOutFiles) {
		if (queryFile == outputFile)
			throw Base::ValueError("hit output file must not be identical to query molecule file");

		if (queryFile == reportFile)
			throw Base::ValueError("report output file must not be identical to query molecule file");

		if (databaseFile == outputFile)
			throw Base::ValueError("hit output file must not be identical to screening database file");

		if (databaseFile == reportFile)
			throw Base::ValueError("report output file must not be identical to screening database file");
	}
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
    printMessage(VERBOSE, " Query File:                          " + queryFile);
    printMessage(VERBOSE, " Database File:                       " + databaseFile);
    printMessage(VERBOSE, " Hit Output File:                     " + (outputFile.empty() ? std::string("None") : outputFile));
    printMessage(VERBOSE, " Report Output File:                  " + (reportFile.empty() ? std::string("None") : reportFile));
	printMessage(VERBOSE, " Screening Mode:                      " + screeningModeToString(settings.getScreeningMode()));
	printMessage(VERBOSE, " Scoring Function:                    " + scoringFunc);
	printMessage(VERBOSE, " Num. saved best Hits:                " + (numBestHits > 0 ? boost::lexical_cast<std::string>(numBestHits) : std::string("All Hits")));
	printMessage(VERBOSE, " Max. Num. Hits:                      " + (maxNumHits > 0 ? boost::lexical_cast<std::string>(maxNumHits) : std::string("No Limit")));
	printMessage(VERBOSE, " Score Cutoff:                        " + (settings.getScoreCutoff() == ScreeningSettings::NO_CUTOFF ? boost::lexical_cast<std::string>(settings.getScoreCutoff()) : std::string("None")));
	printMessage(VERBOSE, " Shape Tanimoto Cutoff:               " + (shapeScoreCutoff > 0.0 ? boost::lexical_cast<std::string>(shapeScoreCutoff) : std::string("None")));
	printMessage(VERBOSE, " Hit List Merging:                    " + std::string(mergeHitLists ? "Yes" : "No"));
	printMessage(VERBOSE, " Output File Splitting:               " + std::string(splitOutFiles ? "Yes" : "No"));
	printMessage(VERBOSE, " Report File Mode:                    " + std::string(reportAll ? "All best Results" : "Hits only"));
	printMessage(VERBOSE, " Alignment Performed:                 " + std::string(scoringOnly ? "No" : "Yes"));
	printMessage(VERBOSE, " Overlay Optimization                 " + std::string(settings.optimizeOverlap() ? "Yes" : "No"));
	printMessage(VERBOSE, " Thorough Overlay Optimization        " + std::string(settings.greedyOptimization() ? "No" : "Yes"));
	printMessage(VERBOSE, " Output Query Molecules:              " + std::string(outputQuery ? "Yes" : "No"));
	printMessage(VERBOSE, " Single Conformer DB-Mode:            " + std::string(settings.singleConformerSearch() ? "Yes" : "No"));
	printMessage(VERBOSE, " Color Feature Type:                  " + colorFeatureTypeToString(settings.getColorFeatureType()));
	printMessage(VERBOSE, " All Carbon-Mode:                     " + std::string(settings.allCarbonMode() ? "Yes" : "No"));
	printMessage(VERBOSE, " Gen. Shape Center Starts:            " + std::string(shapeCenterStarts ? "Yes" : "No"));
	printMessage(VERBOSE, " Gen. Atom Center Starts:             " + std::string(atomCenterStarts ? "Yes" : "No"));
	printMessage(VERBOSE, " Gen. Color Feature Center Starts:    " + std::string(colorCenterStarts ? "Yes" : "No"));
	printMessage(VERBOSE, " Num gen. Random Starts:              " + boost::lexical_cast<std::string>(settings.getNumRandomStarts()));
	printMessage(VERBOSE, " Output Score SD-Tags:                " + std::string(scoreSDTags ? "Yes" : "No"));
	printMessage(VERBOSE, " Output Query Mol. Name SD-Tags:      " + std::string(queryNameSDTags ? "Yes" : "No"));
	printMessage(VERBOSE, " Output Query Mol. Index SD-Tags:     " + std::string(queryMolIdxSDTags ? "Yes" : "No"));
	printMessage(VERBOSE, " Output Query Conf. Index SD-Tags:    " + std::string(queryConfIdxSDTags ? "Yes" : "No"));

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

	if (termSignalCaught())
		return;

     if (progressEnabled()) {
		initInfiniteProgress();
		printMessage(INFO, "Scanning Query File", true, true);
    } else
		printMessage(INFO, "Scanning Query File");

	InputHandlerPtr query_handler = getQueryHandler(queryFile);

	if (!query_handler)
		throw Base::IOError("no input handler found for query molecule file '" + queryFile + '\'');

	queryReader = query_handler->createReader(queryFile);

	setMultiConfImportParameter(*queryReader, true);

	std::size_t cb_id = queryReader->registerIOCallback(InputScanProgressCallback(this));

	try {
		queryReader->getNumRecords();

	} catch (const InputScanProgressCallback::Terminated&) {}

	queryReader->unregisterIOCallback(cb_id);

	if (termSignalCaught())
		return;

    printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(queryReader->getNumRecords()) + " query molecule(s)");
    printMessage(INFO, "");
}

void ShapeScreenImpl::initDatabaseReader()
{
    using namespace CDPL;

	if (termSignalCaught())
		return;

    if (progressEnabled()) {
		initInfiniteProgress();
		printMessage(INFO, "Scanning Database File", true, true);
    } else
		printMessage(INFO, "Scanning Database File");

	InputHandlerPtr database_handler = getDatabaseHandler(databaseFile);

	if (!database_handler)
		throw Base::IOError("no input handler found for screening database file '" + databaseFile + '\'');

	databaseReader = database_handler->createReader(databaseFile);

	setMultiConfImportParameter(*databaseReader, true);

	std::size_t cb_id = databaseReader->registerIOCallback(InputScanProgressCallback(this));

	try {
		databaseReader->getNumRecords();

	} catch (const InputScanProgressCallback::Terminated&) {}

	databaseReader->unregisterIOCallback(cb_id);

	if (termSignalCaught())
		return;

    printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(databaseReader->getNumRecords()) + " screening database molecule(s)");
    printMessage(INFO, "");
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

std::string ShapeScreenImpl::screeningModeToString(ScreeningSettings::ScreeningMode mode) const
{
	switch (mode) {
		
		case ScreeningSettings::BEST_OVERALL_MATCH:
			return "BEST_OVERALL";

		case ScreeningSettings::BEST_MATCH_PER_QUERY:
			return "BEST_PER_QUERY";

		case ScreeningSettings::BEST_MATCH_PER_QUERY_CONF:
			return "BEST_PER_QUERY_CONF";

		default:
			break;
	}

	return "UNKNOWN";
}

ShapeScreenImpl::ScreeningSettings::ScreeningMode ShapeScreenImpl::stringToScreeningMode(const std::string& mode_str) const
{
	std::string uc_mode = mode_str;
	boost::to_upper(uc_mode);

	if (uc_mode == "BEST_OVERALL")
		return ScreeningSettings::BEST_OVERALL_MATCH;
	
	if (uc_mode == "BEST_PER_QUERY")
		return ScreeningSettings::BEST_MATCH_PER_QUERY;

	if (uc_mode == "BEST_PER_QUERY_CONF")
		return ScreeningSettings::BEST_MATCH_PER_QUERY_CONF;

	throwValidationError("mode");

	return ScreeningSettings::BEST_MATCH_PER_QUERY;
}

std::string ShapeScreenImpl::colorFeatureTypeToString(ScreeningSettings::ColorFeatureType type) const
{
	switch (type) {
		
		case ScreeningSettings::NO_FEATURES:
			return "NONE";

		case ScreeningSettings::PHARMACOPHORE_EXP_CHARGES:
			return "EXP_PHARM";

		case ScreeningSettings::PHARMACOPHORE_IMP_CHARGES:
			return "IMP_PHARM";

		default:
			break;
	}

	return "UNKNOWN";
}

ShapeScreenImpl::ScreeningSettings::ColorFeatureType ShapeScreenImpl::stringToColorFeatureType(const std::string& type_str) const
{
	std::string uc_type = type_str;
	boost::to_upper(uc_type);

	if (uc_type == "NONE")
		return ScreeningSettings::NO_FEATURES;

	if (uc_type == "EXP_PHARM")
		return ScreeningSettings::PHARMACOPHORE_EXP_CHARGES;

	if (uc_type == "IMP_PHARM")
		return ScreeningSettings::PHARMACOPHORE_IMP_CHARGES;

	throwValidationError("color-ftr-type");

	return ScreeningSettings::PHARMACOPHORE_IMP_CHARGES;
}

std::string ShapeScreenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(databaseReader->getNumRecords()));
}
