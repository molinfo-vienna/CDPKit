/* 
 * PSDScreenImpl.cpp
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


#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <functional>

#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Pharm/FileScreeningHitCollector.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "PSDScreenImpl.hpp"


using namespace PSDScreen;


namespace
{

    typedef std::vector<std::string> StringList;

    const std::string PHARM_IDX_PROPERTY_NAME  = "<Query Pharm. Index>";
    const std::string PHARM_NAME_PROPERTY_NAME = "<Query Pharm. Name>";
}


struct PSDScreenImpl::ScreeningWorker
{

    ScreeningWorker(PSDScreenImpl* parent, std::size_t worker_idx, std::size_t start_mol_idx, 
                    std::size_t end_mol_idx): 
        parent(parent), workerIndex(worker_idx), startMolIndex(start_mol_idx), endMolIndex(end_mol_idx) {}

    void operator()() {
        using namespace CDPL;
        using namespace Pharm;
        using namespace std::placeholders;
        
        try {
            PSDScreeningDBAccessor db_acc(parent->screeningDB);
            ScreeningProcessor scr_proc(db_acc);
            BasicPharmacophore query_pharm;
        
            scr_proc.setHitReportMode(parent->matchingMode);
            scr_proc.setMaxNumOmittedFeatures(parent->maxOmittedFtrs);
            scr_proc.checkXVolumeClashes(parent->checkXVols);
            scr_proc.seekBestAlignments(parent->bestAlignments);
            scr_proc.setHitCallback(std::bind(&ScreeningWorker::reportHit, this, _1, _2));
            scr_proc.setProgressCallback(std::bind(&ScreeningWorker::reportProgress, this, _1, _2));

            for (queryIndex = 0; queryIndex < parent->numQueryPharms; queryIndex++) {
                if (PSDScreenImpl::termSignalCaught() || parent->haveErrorMessage())
                    return;

                if (!parent->getQueryPharmacophore(queryIndex, query_pharm))
                    return;
                
                scr_proc.searchDB(query_pharm, startMolIndex, endMolIndex);
            }

        } catch (const std::exception& e) {
            parent->setErrorMessage("unexpected exception while screening database '" + parent->screeningDB + "':" + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while screening database '" + parent->screeningDB + '\'');
        }
    }

    bool reportHit(const CDPL::Pharm::ScreeningProcessor::SearchHit& hit, double score) {
        using namespace CDPL;

        if (parent->outputPharmIndex || parent->outputPharmName) {
            hitMol.copy(hit.getHitMolecule());

            Chem::StringDataBlock::SharedPointer struc_data;

            if (hasStructureData(hitMol)) 
                struc_data.reset(new Chem::StringDataBlock(*getStructureData(hitMol)));
            else
                struc_data.reset(new Chem::StringDataBlock());

            if (parent->outputPharmIndex)
                struc_data->addEntry(PHARM_IDX_PROPERTY_NAME, 
                                     std::to_string(queryIndex));
            if (parent->outputPharmName)
                struc_data->addEntry(PHARM_NAME_PROPERTY_NAME, 
                                     getName(hit.getHitPharmacophore()));

            setStructureData(hitMol, struc_data);

            return parent->collectHit(Pharm::ScreeningProcessor::SearchHit(hit.getHitProvider(),
                                                                           hit.getQueryPharmacophore(),
                                                                           hit.getHitPharmacophore(),
                                                                           hitMol,
                                                                           hit.getHitAlignmentTransform(),
                                                                           hit.getHitPharmacophoreIndex(),
                                                                           hit.getHitMoleculeIndex(),
                                                                           hit.getHitConformationIndex()),
                                      score);
        }

        return parent->collectHit(hit, score);
    }

    bool reportProgress(std::size_t i, std::size_t max_val) {
        double progress = double(i) / max_val;

        return parent->printProgress(workerIndex, (queryIndex + progress) / parent->numQueryPharms);
    }

    PSDScreenImpl*            parent;
    std::size_t               workerIndex;
    std::size_t               startMolIndex;
    std::size_t               endMolIndex;
    std::size_t               queryIndex;
    CDPL::Chem::BasicMolecule hitMol;
};

PSDScreenImpl::PSDScreenImpl(): 
    checkXVols(true), alignConfs(true), bestAlignments(false), outputScore(true), outputMolIndex(false), 
    outputConfIndex(false), outputDBName(false), outputPharmName(false), outputPharmIndex(false),  
    numThreads(0), startMolIndex(0), endMolIndex(0), maxOmittedFtrs(0),
    matchingMode(CDPL::Pharm::ScreeningProcessor::FIRST_MATCHING_CONF), hitOutputFormat(), 
    queryInputFormat(), numQueryPharms(0), numDBMolecules(0), numDBPharms(0), numHits(0), maxNumHits(0),
    lastProgValue(-1)
{
    using namespace std::placeholders;
    
    addOption("database,d", "Screening database file.", 
              value<std::string>(&screeningDB)->required());
    addOption("query,q", "Query pharmacophore file(s).", 
              value<std::string>(&queryPharmFile)->required());
    addOption("output,o", "Hit output file.", 
              value<std::string>(&hitOutputFile)->required());
    addOption("mode,m", "Molecule conformation matching mode (FIRST-MATCH, BEST-MATCH, ALL-MATCHES, default: FIRST-MATCH).", 
              value<std::string>()->notifier(std::bind(&PSDScreenImpl::setMatchingMode, this, _1)));
    addOption("start-index,s", "Screening range start molecule index (zero-based!, default: 0).", 
              value<std::size_t>(&startMolIndex)->default_value(0));
    addOption("end-index,e", "Screening range end molecule index (zero-based and not included"
              " in screening!, default: one after last molecule).", 
              value<std::size_t>(&endMolIndex)->default_value(0));
    addOption("max-num-hits,n", "Maxmimum number of hits to report (default: no limit).", 
              value<std::size_t>(&maxNumHits)->default_value(0));
    addOption("max-omitted,M", "Maximum number of allowed unmatched features.", 
              value<std::size_t>(&maxOmittedFtrs)->default_value(0));
    addOption("check-xvols,x", "Check for exclusion volume clashes (default: true).", 
              value<bool>(&checkXVols)->implicit_value(true));
    addOption("align-hits,a", "Align matching conformations to pharmacophore for output (default: true).", 
              value<bool>(&alignConfs)->implicit_value(true));
    addOption("best-alignments,b", "Seek best alignments with highest score (default: false).", 
              value<bool>(&bestAlignments)->implicit_value(true));
    addOption("output-score,S", "Output score property for hit molecule (default: true).", 
              value<bool>(&outputScore)->implicit_value(true));
    addOption("output-mol-index,I", "Output database molecule index property for hit molecule (default: false).", 
              value<bool>(&outputMolIndex)->implicit_value(true));
    addOption("output-conf-index,C", "Output conformation index property for hit molecule (default: false).", 
              value<bool>(&outputConfIndex)->implicit_value(true));
    addOption("output-db-name,D", "Output database name property for hit molecule (default: false).", 
              value<bool>(&outputDBName)->implicit_value(true));
    addOption("output-pharm-name,N", "Output query pharmacophore name property for hit molecule (default: false).", 
              value<bool>(&outputPharmName)->implicit_value(true));
    addOption("output-pharm-index,P", "Output query pharmacophore index property for hit molecule (default: false).", 
              value<bool>(&outputPharmIndex)->implicit_value(true));
    addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
              std::to_string(std::thread::hardware_concurrency()) + 
              " threads, must be >= 0, 0 disables multithreading).", 
              value<std::size_t>(&numThreads)->implicit_value(std::thread::hardware_concurrency()));
    addOption("output-format,O", "Hit molecule output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&PSDScreenImpl::setHitOutputFormat, this, _1)));
    addOption("query-format,Q", "Query pharmacophore input file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&PSDScreenImpl::setQueryInputFormat, this, _1)));

    addOptionLongDescriptions();
}

const char* PSDScreenImpl::getProgName() const
{
    return "PSDScreen";
}

const char* PSDScreenImpl::getProgCopyright() const
{
    return "Thomas Seidel";
}

const char* PSDScreenImpl::getProgAboutText() const
{
    return "Performs a pharmacophore-based virtual screening of molecule databases.";
}

void PSDScreenImpl::addOptionLongDescriptions()
{
    StringList pharm_formats;
    std::string pharm_formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Pharm::Pharmacophore>(std::back_inserter(pharm_formats));

    for (StringList::const_iterator it = pharm_formats.begin(), end = pharm_formats.end(); it != end; ++it)
        pharm_formats_str.append("\n - ").append(*it);

    addOptionLongDescription("query", 
                             "Specifies the file containing one or more pharmacophore(s) that shall be used as a query"
                             "for the database search.\n\n" + pharm_formats_str);

    addOptionLongDescription("query-format", 
                             "Allows to explicitly specify the format of the query pharmacophore file by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             pharm_formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    StringList mol_formats;
    std::string mol_formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(mol_formats));

    for (StringList::const_iterator it = mol_formats.begin(), end = mol_formats.end(); it != end; ++it)
        mol_formats_str.append("\n - ").append(*it);

    addOptionLongDescription("output", 
                             "Specifies the output file where database molecules matching the query pharmacophore(s) shall be stored.\n\n" +
                             mol_formats_str);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the format of the hit molecule output file by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             mol_formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");
}

void PSDScreenImpl::setHitOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    hitOutputFormat = file_ext;
}

void PSDScreenImpl::setQueryInputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Pharm::Pharmacophore>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("query-format");

    queryInputFormat = file_ext;
}

void PSDScreenImpl::setMatchingMode(const std::string& mode_str)
{
    using namespace CDPL::Pharm;
    using namespace CDPL;

    if (Internal::isEqualCI(mode_str, "FIRST-MATCH"))
        matchingMode = ScreeningProcessor::FIRST_MATCHING_CONF;
    else if (Internal::isEqualCI(mode_str, "BEST-MATCH"))
        matchingMode = ScreeningProcessor::BEST_MATCHING_CONF;
    else if (Internal::isEqualCI(mode_str, "ALL-MATCHES"))
        matchingMode = ScreeningProcessor::ALL_MATCHING_CONFS;
    else
        throwValidationError("mode");
}

int PSDScreenImpl::process()
{
    timer.reset();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

    checkInputFiles();
    printOptionSummary();
    initQueryPharmReader();
    initHitCollector();
    analyzeInputFiles();

    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Screening Database...", true, true);
    } else 
        printMessage(INFO, "Screening Database...");

    if (termSignalCaught())
        return EXIT_FAILURE;

    if (numThreads > 0)
        processMultiThreaded();
    else
        processSingleThreaded();

    printMessage(INFO, "");

    if (haveErrorMessage()) {
        printMessage(ERROR, "Error: " + errorMessage); 
        return EXIT_FAILURE;
    }

    if (termSignalCaught())
        return EXIT_FAILURE;

    printStatistics();

    return EXIT_SUCCESS;
}

void PSDScreenImpl::processSingleThreaded()
{
    using namespace CDPL;

    workerProgArray.resize(1, 0.0);

    ScreeningWorker(this, 0, startMolIndex, endMolIndex)();
}

void PSDScreenImpl::processMultiThreaded()
{
    using namespace CDPL;

    workerProgArray.resize(numThreads, 0.0);

    typedef std::vector<std::thread> ThreadGroup;
    
    ThreadGroup thread_grp;

    try {
        std::size_t num_mols_per_thread = (endMolIndex - startMolIndex) / numThreads;

        for (std::size_t i = 0, start_mol_idx = startMolIndex; i < numThreads; i++, start_mol_idx += num_mols_per_thread) {
            if (termSignalCaught())
                break;

            thread_grp.emplace_back(ScreeningWorker(this, i, start_mol_idx, 
                                                    i == numThreads - 1 ? endMolIndex : 
                                                    start_mol_idx + num_mols_per_thread));
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
}

bool PSDScreenImpl::collectHit(const SearchHit& hit, double score)
{
    if (termSignalCaught())
        return false;

    if (haveErrorMessage())
        return false;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(collHitMutex);

        return doCollectHit(hit, score);
    }

    return doCollectHit(hit, score);
}

bool PSDScreenImpl::doCollectHit(const SearchHit& hit, double score)
{
    try {
        if (maxNumHits > 0 && numHits >= maxNumHits)
            return false;

        numHits++;

        printMessage(VERBOSE, "Found matching molecule '" + getName(hit.getHitMolecule()) + 
                     "' - DB: '" + hit.getHitProvider().getDBAccessor().getDatabaseName() + 
                     "', Mol. Index: " + std::to_string(hit.getHitMoleculeIndex()) + 
                     ", Conf. Index: " + std::to_string(hit.getHitConformationIndex()) +
                     ", Score: " + std::to_string(score));

        return (*hitCollector)(hit, score);

    } catch (const std::exception& e) {
        printMessage(ERROR, std::string("Collecting hit molecule failed: ") + e.what());

    } catch (...) {
        printMessage(ERROR, "Collecting hit molecule failed");
    }

    return true;
}

bool PSDScreenImpl::getQueryPharmacophore(std::size_t idx, CDPL::Pharm::Pharmacophore& pharm)
{
    if (termSignalCaught())
        return false;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);

        return doGetQueryPharmacophore(idx, pharm);
    }

    return doGetQueryPharmacophore(idx, pharm);
}

bool PSDScreenImpl::doGetQueryPharmacophore(std::size_t idx, CDPL::Pharm::Pharmacophore& pharm)
{
    try {
        return queryPharmReader->read(idx, pharm);

    } catch (const std::exception& e) {
        errorMessage = std::string("reading query pharmacophore failed: ") + e.what();

    } catch (...) {
        errorMessage = "reading query pharmacophore failed";
    }

    return false;
}

bool PSDScreenImpl::printProgress(std::size_t worker_idx, double progress)
{
    if (termSignalCaught())
        return false;

    if (!progressEnabled())
        return true;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);

        return doPrintProgress(worker_idx, progress);
    }

    return doPrintProgress(worker_idx, progress);
}

bool PSDScreenImpl::doPrintProgress(std::size_t worker_idx, double progress)
{
    try {
        workerProgArray[worker_idx] = progress;

        double total_prog = std::accumulate(workerProgArray.begin(), workerProgArray.end(), 0.0) / workerProgArray.size();
        int new_prog_val = total_prog * 1000;

        if (new_prog_val <= lastProgValue)
            return true;

        lastProgValue = new_prog_val;

        std::string prog_prefix = "Screening Database (" + std::to_string(numHits) + 
            " Hit" + (numHits != 1 ? "s" : "") + ")...";

        if (prog_prefix.size() < 35)
            prog_prefix.resize(35, ' ');

        CmdLineBase::printProgress(prog_prefix, total_prog);
        return true;

    } catch (const std::exception& e) {
        errorMessage = std::string("printing progress failed: ") + e.what();

    } catch (...) {
        errorMessage = "printing progress failed";
    }

    return false;
}

void PSDScreenImpl::setErrorMessage(const std::string& msg)
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

bool PSDScreenImpl::haveErrorMessage()
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);
        return !errorMessage.empty();
    }

    return !errorMessage.empty();
}

void PSDScreenImpl::printStatistics()
{
    using namespace CDPL;
    using namespace Pharm;

    std::size_t proc_time = std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed()).count();

    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Num. Screened Molecules: " + std::to_string(endMolIndex - startMolIndex));
    printMessage(INFO, " Num. Reported Hits:      " + std::to_string(numHits));

    if (matchingMode == ScreeningProcessor::FIRST_MATCHING_CONF || 
        matchingMode == ScreeningProcessor::BEST_MATCHING_CONF || 
        (numDBMolecules == (endMolIndex - startMolIndex))) {

        double hit_rate = double(numHits) * 100;

        if (matchingMode == ScreeningProcessor::ALL_MATCHING_CONFS)
            hit_rate /= numDBPharms;
        else
            hit_rate /= (endMolIndex - startMolIndex);

        std::ostringstream oss;

        oss.unsetf(std::ios::floatfield);
        oss << std::setprecision(4) << hit_rate << '%';

        printMessage(INFO, " Hit Rate:                " + oss.str());
    }

    printMessage(INFO, " Processing Time:         " + CmdLineLib::formatTimeDuration(proc_time));
}

void PSDScreenImpl::checkInputFiles() const
{
    using namespace CDPL;

    if (!Util::fileExists(queryPharmFile))
        throw Base::IOError("query pharmacophore file '" + queryPharmFile + "' does not exist");

    if (!Util::fileExists(screeningDB))
        throw Base::IOError("screening database '" + screeningDB + "' does not exist");
}

void PSDScreenImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Pharm. Query File(s):         " + queryPharmFile);
    printMessage(VERBOSE, " Screening Database:           " + screeningDB);
    printMessage(VERBOSE, " Hit Output File:              " + hitOutputFile);
    printMessage(VERBOSE, " Conformation Matching Mode:   " + getMatchingModeString());
    printMessage(VERBOSE, " Max. Num. Omitted Features:   " + std::to_string(maxOmittedFtrs));
    printMessage(VERBOSE, " Screening Start Molecule:     " + std::to_string(startMolIndex));
    printMessage(VERBOSE, " Screening End Molecule:       " + (endMolIndex != 0 ? std::to_string(startMolIndex) : std::string("Last")));
    printMessage(VERBOSE, " Maximum Number of Hits:       " + (maxNumHits != 0 ? std::to_string(maxNumHits) : std::string("No Limit")));
    printMessage(VERBOSE, " Check X-Volume Clashes:       " + std::string(checkXVols ? "Yes" : "No"));
    printMessage(VERBOSE, " Align Hit Molecules:          " + std::string(alignConfs ? "Yes" : "No"));
    printMessage(VERBOSE, " Seek Best Alignments:         " + std::string(bestAlignments ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Score Property:        " + std::string(outputScore ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Mol. Index Property:   " + std::string(outputMolIndex ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Conf. Index Property:  " + std::string(outputConfIndex ? "Yes" : "No"));
    printMessage(VERBOSE, " Output DB-Name Property:      " + std::string(outputDBName ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Pharm. Name Property:  " + std::string(outputPharmName ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Pharm. Index Property: " + std::string(outputPharmIndex ? "Yes" : "No"));
    printMessage(VERBOSE, " Multithreading:               " + std::string(numThreads > 0 ? "Yes" : "No"));

    if (numThreads > 0)
        printMessage(VERBOSE, " Number of Threads:            " + std::to_string(numThreads));

    printMessage(VERBOSE, " Hit Output File Format:       " + (!hitOutputFormat.empty() ? hitOutputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Query Input File Format:      " + (!queryInputFormat.empty() ? queryInputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, "");
}

void PSDScreenImpl::initHitCollector()
{
    using namespace CDPL;

    try {
        hitMolWriter.reset(hitOutputFormat.empty() ? new Chem::MolecularGraphWriter(hitOutputFile) :
                                                     new Chem::MolecularGraphWriter(hitOutputFile, hitOutputFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + hitOutputFile + '\'');
    }

    setMultiConfExportParameter(*hitMolWriter, false);

    hitCollector.reset(new Pharm::FileScreeningHitCollector(*hitMolWriter));

    hitCollector->alignHitMolecule(alignConfs);
    hitCollector->writeScoreProperty(outputScore);
    hitCollector->writeDBNameProperty(outputDBName);
    hitCollector->writeDBMoleculeIndexProperty(outputMolIndex);
    hitCollector->writeMoleculeConfIndexProperty(outputConfIndex);
}

void PSDScreenImpl::initQueryPharmReader()
{
    using namespace CDPL;

    try {
        queryPharmReader.reset(queryInputFormat.empty() ? new Pharm::PharmacophoreReader(queryPharmFile) :
                                                          new Pharm::PharmacophoreReader(queryPharmFile, queryInputFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no input handler found for file '" + queryPharmFile + '\'');
    }
}

void PSDScreenImpl::analyzeInputFiles()
{
    using namespace CDPL;

    printMessage(INFO, "Scanning Input Files...  ");

    Pharm::PSDScreeningDBAccessor db_acc(screeningDB);

    numDBMolecules = db_acc.getNumMolecules();
    numDBPharms = db_acc.getNumPharmacophores();
    numQueryPharms = queryPharmReader->getNumRecords();

    if (endMolIndex == 0)
        endMolIndex = numDBMolecules;
    else
        endMolIndex = std::min(endMolIndex, numDBMolecules);

    startMolIndex = std::min(startMolIndex, numDBMolecules);

    printMessage(INFO, "- " + std::to_string(numQueryPharms) + " Query pharmacophore" + (numQueryPharms != 1 ? "s" : ""));
    printMessage(INFO, "- " + std::to_string(numDBMolecules) + " Molecule" + (numDBMolecules != 1 ? "s/" : "/") + 
                 std::to_string(numDBPharms) + " pharmacophore" + (numDBPharms != 1 ? "s" : "")+ " in database");

    std::size_t num_screened = endMolIndex - startMolIndex;

    printMessage(VERBOSE, "-> Screening " + std::to_string(num_screened) + " molecule" + (num_screened != 1 ? "s" : ""));
    printMessage(INFO, "");
}

std::string PSDScreenImpl::getMatchingModeString() const
{
    using namespace CDPL;

    if (matchingMode == Pharm::ScreeningProcessor::FIRST_MATCHING_CONF)
        return "FIRST-MATCH";

    if (matchingMode == Pharm::ScreeningProcessor::BEST_MATCHING_CONF)
        return "BEST-MATCH";

    if (matchingMode == Pharm::ScreeningProcessor::ALL_MATCHING_CONFS)
        return "ALL-MATCHES";
    
    return "UNKNOWN";
}
