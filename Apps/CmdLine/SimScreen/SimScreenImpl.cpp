/* 
 * SimScreenImpl.cpp
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
#include <iomanip>
#include <thread>
#include <chrono>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "SimScreenImpl.hpp"
#include "TanimotoSimilarity.hpp"
#include "ECFPCalculator.hpp"


using namespace SimScreen;


class SimScreenImpl::ScreeningWorker
{

  public:
    ScreeningWorker(SimScreenImpl* parent):
        parent(parent), screeningProc(*parent->screeningProc, *parent->scoringFunc, *parent->descrCalculator,
                                      [this](const ScreeningProcessor::Result& res) {
                                          this->processResult(res);
                                      }),
        molecule(new CDPL::Chem::BasicMolecule()), terminate(false) {}

    void operator()()
    {
        using namespace CDPL;
        
        while (!terminate) {
            if (!molecule.unique())
                molecule.reset(new CDPL::Chem::BasicMolecule());

            if (!(dbMolIndex = parent->readNextMolecule(*molecule)))
                return;

            try {
                if (!screeningProc.process(*molecule, parent->screeningMode, parent->singleConfSearch))
                    parent->printMessage(ERROR, "Processing of database molecule " + parent->createMoleculeIdentifier(dbMolIndex, *molecule) + " failed: " + screeningProc.getError());

                continue;

            } catch (const std::exception& e) {
                parent->setErrorMessage("unexpected exception while processing database molecule " + parent->createMoleculeIdentifier(dbMolIndex, *molecule) + ": " + e.what());

            } catch (...) {
                parent->setErrorMessage("unexpected exception while processing database molecule " + parent->createMoleculeIdentifier(dbMolIndex, *molecule));
            }

            return;
        }
    }

  private:
    void processResult(const ScreeningProcessor::Result& res)
    {
        if (terminate)
            return;

        terminate = !parent->processHit(dbMolIndex - 1, getName(*molecule), molecule, res);
    }

    SimScreenImpl*     parent;
    ScreeningProcessor screeningProc;
    MoleculePtr        molecule;
    std::size_t        dbMolIndex;
    bool               terminate;
};


SimScreenImpl::SimScreenImpl(): 
    numThreads(0), singleConfSearch(false), mergeHitLists(false), 
    splitOutFiles(true), outputQuery(true), scoreSDTags(true), queryNameSDTags(false), 
    queryMolIdxSDTags(false), queryConfIdxSDTags(true), dbMolIdxSDTags(false), dbConfIdxSDTags(true),
    hitNamePattern("@D@_@c@_@Q@_@C@"), numBestHits(1000), maxNumHits(0), scoreCutoff(-1.0), 
    screeningMode(ScreeningProcessor::BEST_MATCH_PER_QUERY), numProcMols(0), numHits(0), numSavedHits(0)
{
    initScoringFunctions();
    initDescriptorCalculators();
    
    addOption("query,q", "Query molecule file.", 
              value<std::string>(&queryFile)->required());
    addOption("database,d", "Molecule database file to screen.", 
              value<std::string>(&databaseFile)->required());
    addOption("output,o", "Molecule output file.", 
              value<std::string>(&hitOutputFile));
    addOption("report,r", "Report output file.", 
              value<std::string>(&reportFile));
    addOption("mode,m", "Specifies which kind of obtained results for the query/input molecule pairings are of interest "
              "(BEST_OVERALL, BEST_PER_QUERY, BEST_PER_QUERY_CONF, default: BEST_PER_QUERY).",
              value<std::string>()->notifier([this](const std::string& mode) { this->setScreeningMode(mode); }));
    addOption("func,f", "Function to use for molecule similarity/distance calculation and ranking operations (" + // TODO
              getScoringFunctionIDs() + ", default: TANIMOTO)",
              value<std::string>()->notifier([this](const std::string& id) { this->setScoringFunction(id); }));
    addOption("descr,e", "Type of molecule descriptor to use for similarity/distance calculations (" +
              getDescriptorCalculatorIDs() + ", default: ECFP)",
              value<std::string>()->notifier([this](const std::string& id) { this->setDescriptorCalculator(id); }));
    addOption("best-hits,b", "Maximum number of best scoring hits to output (default: " +
              std::to_string(numBestHits) + ").",
              value<std::size_t>(&numBestHits));
    addOption("max-hits,n", "Maximum number of found hits at which the screen will terminate (overrides the --best-hits option, default: 0 - no limit).",
              value<std::size_t>(&maxNumHits));
    addOption("cutoff,x", "Similarity/distance cutoff value which determines whether an database molecule is considered as a hit (default: -1.0 -> no cutoff).",
              value<double>(&scoreCutoff));
    addOption("merge-hits,M", "If true, identified hits are merged into a single, combined hit list. "
              "If false, a separate hit list for every query molecule will be maintained (default: false).", 
              value<bool>(&mergeHitLists)->implicit_value(true));
    addOption("split-output,T", "If true, for every query molecule a separate report and hit output file will be generated (default: true).", 
              value<bool>(&splitOutFiles)->implicit_value(true));
    addOption("output-query,u", "If specified, query molecules will be written at the beginning of the hit molecule output file (default: true).",
              value<bool>(&outputQuery)->implicit_value(true));
    addOption("single-conf,g", "If specified, conformers of the database molecules are treated as individual single conformer molecules (default: false).",
              value<bool>(&singleConfSearch)->implicit_value(true));
    addOption("score-sd-tags,S", "If true, similarity/distance score values will be appended as SD-block entries of the output hit molecules (default: true).",
              value<bool>(&scoreSDTags)->implicit_value(true));
    addOption("query-name-sd-tags,N", "If true, the query molecule name will be appended to the SD-block of the output hit molecules (default: false).",
              value<bool>(&queryNameSDTags)->implicit_value(true));
    addOption("query-idx-sd-tags,G", "If true, the query molecule index will be appended to the SD-block of the output hit molecules (default: false).",
              value<bool>(&queryMolIdxSDTags)->implicit_value(true));
    addOption("query-conf-sd-tags,F", "If true, the query molecule conformer index will be appended to the SD-block of the output hit molecules (default: true).",
              value<bool>(&queryConfIdxSDTags)->implicit_value(true));
    addOption("db-idx-sd-tags,B", "If true, the database molecule index will be appended to the SD-block of the output hit molecules (default: false).",
              value<bool>(&dbMolIdxSDTags)->implicit_value(true));
    addOption("db-conf-sd-tags,Y", "If true, the database molecule conformer index will be appended to the SD-block of the output hit molecules (default: true).",
              value<bool>(&dbConfIdxSDTags)->implicit_value(true));
    addOption("hit-name-ptn,P", "Pattern for composing the names of written hit molecules by variable substitution (supported variables: @Q@ = query molecule name, "
              "@D@ = database molecule name, @C@ = query molecule conformer index, @c@ = database molecule conformer index, @I@ = query molecule index "
              "and @i@ = database molecule index, default: " + hitNamePattern + ").",
              value<std::string>(&hitNamePattern));
    addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
              std::to_string(std::thread::hardware_concurrency()) + 
              " threads, must be >= 0, 0 disables multithreading).", 
              value<std::size_t>(&numThreads)->implicit_value(std::thread::hardware_concurrency()));
    addOption("query-format,Q", "Query molecule file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { this->setQueryFormat(fmt); }));
    addOption("database-format,D", "Molecule database file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { this->setDatabaseFormat(fmt); }));
    addOption("output-format,O", "Molecule output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { this->setHitOutputFormat(fmt); }));
 
    addOptionLongDescriptions();

    for (auto& func : scoringFuncs)
        func.addOptions(*this);
 
    for (auto& calc : descrCalculators)
        calc.addOptions(*this);

    scoringFunc = getScoringFunction("TANIMOTO");
    descrCalculator = getDescriptorCalculator("ECFP"); 
}

SimScreenImpl::~SimScreenImpl()
{}

const char* SimScreenImpl::getProgName() const
{
    return "SimScreen";
}

const char* SimScreenImpl::getProgAboutText() const
{
    return "Performs a descriptor-/fingerprint-based similarity screening of molecule databases.";
}

void SimScreenImpl::addOptionLongDescriptions()
{
    typedef std::vector<std::string> StringList;

    StringList formats;
    std::string formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (auto& format : formats)
        formats_str.append("\n - ").append(format);

    addOptionLongDescription("query-format", 
                             "Allows to explicitly specify the format of the query molecule file by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");
    addOptionLongDescription("database-format", 
                             "Allows to explicitly specify the format of the screening database file by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("query", 
                             "The query molecule input file.\n\n" + formats_str);
    addOptionLongDescription("database", 
                             "The molecule database file to screen.\n\n" + formats_str);

    formats.clear();
    formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (auto& format : formats)
        formats_str.append("\n - ").append(format);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the hit molecule output file format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("output", 
                             "Hit molecule output file.\n\n" + formats_str);
}

void SimScreenImpl::setScoringFunction(const std::string& id)
{
    if (!(scoringFunc = getScoringFunction(id)))
        throwValidationError("func");
}

void SimScreenImpl::setDescriptorCalculator(const std::string& id)
{
    if (!(descrCalculator = getDescriptorCalculator(id)))
        throwValidationError("descr");
}

void SimScreenImpl::setScreeningMode(const std::string& mode)
{
    using namespace CDPL;
    
    if (Internal::isEqualCI(mode, "BEST_OVERALL"))
        screeningMode = ScreeningProcessor::BEST_OVERALL_MATCH;
    
    else if (Internal::isEqualCI(mode, "BEST_PER_QUERY"))
        screeningMode = ScreeningProcessor::BEST_MATCH_PER_QUERY;

    else if (Internal::isEqualCI(mode, "BEST_PER_QUERY_CONF"))
        screeningMode = ScreeningProcessor::BEST_MATCH_PER_QUERY_CONF;

    else
        throwValidationError("mode");
}

void SimScreenImpl::setQueryFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("query-format");

    queryFormat = file_ext;
}

void SimScreenImpl::setDatabaseFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("database-format");

    databaseFormat = file_ext;
}

void SimScreenImpl::setHitOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;

    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    hitOutputFormat = file_ext;
}

void SimScreenImpl::processOptions()
{
    for (auto& func : scoringFuncs)
        func.processOptions(*this);
 
    for (auto& calc : descrCalculators)
        calc.processOptions(*this);
}

int SimScreenImpl::process()
{
    timer.reset();
    
    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

    checkOutputFileOptions();
    checkInputFiles();
    printOptionSummary();

    initQueryReader();
    initDatabaseReader();

    if (termSignalCaught())
        return EXIT_FAILURE;

    readQueryMolecules();
    procQueryMolecules();
    initReportFileStreams();
    initHitMoleculeWriters();
    initHitLists();
    
    if (progressEnabled()) {
        initInfiniteProgress();
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

    outputHitLists();

    if (termSignalCaught())
        return EXIT_FAILURE;

    printStatistics();

    return EXIT_SUCCESS;
}

void SimScreenImpl::processSingleThreaded()
{
    using namespace CDPL;

    ScreeningWorker worker(this);

    worker();
}

void SimScreenImpl::processMultiThreaded()
{
    using namespace CDPL;

    typedef std::shared_ptr<ScreeningWorker> ScreeningWorkerPtr;
    typedef std::vector<ScreeningWorkerPtr> ScreeningWorkerList;
    typedef std::vector<std::thread> ThreadGroup;
    
    ThreadGroup thread_grp;
    ScreeningWorkerList worker_list;

    try {
        for (std::size_t i = 0; i < numThreads; i++) {
            if (termSignalCaught())
                break;

            ScreeningWorkerPtr worker_ptr(new ScreeningWorker(this));

            thread_grp.emplace_back(std::bind(&ScreeningWorker::operator(), worker_ptr));
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
}

bool SimScreenImpl::processHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                               const MoleculePtr& db_mol, const ScreeningProcessor::Result& res)
{
    if (scoreCutoff >= 0.0 && scoringFunc->compare(res.score, scoreCutoff))
        return true;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(hitProcMutex);

        return doProcessHit(db_mol_idx, db_mol_name, db_mol, res);
    }

    return doProcessHit(db_mol_idx, db_mol_name, db_mol, res);
}

bool SimScreenImpl::doProcessHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                                 const MoleculePtr& db_mol, const ScreeningProcessor::Result& res)
{
    if (maxNumHits > 0 && numHits >= maxNumHits)
        return false;

    numHits++;

    if (numBestHits == 0) {
        HitMoleculeData hit_data(db_mol_idx, db_mol_name, res, db_mol);

        if (!hitOutputFile.empty())
            outputHitMolecule(splitOutFiles ? hitMolWriters[res.queryMolIdx] : hitMolWriters[0], hit_data);

        if (!reportFile.empty())
            outputReportFileHitData(splitOutFiles ? reportOStreams[res.queryMolIdx] : reportOStreams[0], hit_data);

        return true;
    }

    auto& hit_list = (mergeHitLists ? hitLists[0] : hitLists[res.queryMolIdx]);
        
    if (numBestHits > 0) {
        if (hit_list.size() >= numBestHits) {
            if (scoringFunc->compare(res.score, hit_list.rbegin()->screeningResult.score))
                return true;

            hit_list.erase(--hit_list.end());
        }
    }

    hit_list.insert(HitMoleculeData(db_mol_idx, db_mol_name, res, db_mol));
    return true;
}

void SimScreenImpl::readQueryMolecules()
{
    using namespace CDPL;
    
    printMessage(INFO, "Reading Query Molecules...");

    while (!termSignalCaught()) {
        std::auto_ptr<Chem::Molecule> query_mol(new Chem::BasicMolecule());

        if (!queryReader->read(*query_mol))
            break;
 
        queryMolecules.push_back(query_mol);
    }

    if (termSignalCaught())
        return;

    printMessage(INFO, " - Read " + std::to_string(queryMolecules.size()) + " query molecule(s)");
    printMessage(INFO, "");
}

void SimScreenImpl::procQueryMolecules()
{
    printMessage(INFO, "Processing Query Molecules...");
    
    screeningProc.reset(new ScreeningProcessor(*scoringFunc, *descrCalculator));

    for (std::size_t i = 0; i < queryMolecules.size(); i++)
        if (!screeningProc->addQuery(queryMolecules[i]))
            printMessage(ERROR, "Processing of query molecule " + createMoleculeIdentifier(i + 1, queryMolecules[i]) + " failed: " + screeningProc->getError());
}

void SimScreenImpl::initHitLists()
{
    hitLists.resize(mergeHitLists ? 1 : queryMolecules.size(),
                    HitList([this](const HitMoleculeData& lhs, const HitMoleculeData& rhs) -> bool {
                                return this->scoringFunc->compare(rhs.screeningResult.score, lhs.screeningResult.score);
                    }));
}

void SimScreenImpl::initReportFileStreams()
{
    if (reportFile.empty())
        return;

    if (!splitOutFiles) 
        reportOStreams.push_back(new std::ofstream(reportFile));

    else 
        for (std::size_t i = 0, num_query_mols = queryMolecules.size(); i < num_query_mols; i++)
            reportOStreams.push_back(new std::ofstream(getOutputFileName(reportFile, i)));
    
    for (auto& os : reportOStreams) {
        if (!os.good())
            throw CDPL::Base::IOError("opening report file failed");
    
        outputReportFileHeader(os);
    }
}

void SimScreenImpl::initHitMoleculeWriters()
{
    using namespace CDPL;
    
    if (hitOutputFile.empty())
        return;

    if (!splitOutFiles) {
        try {
            hitMolWriters.push_back(hitOutputFormat.empty() ? new Chem::MolecularGraphWriter(hitOutputFile) :
                                    new Chem::MolecularGraphWriter(hitOutputFile, hitOutputFormat));

        } catch (const Base::IOError& e) {
            throw Base::IOError("no output handler found for hit molecule file '" + hitOutputFile + '\'');
        }

        if (outputQuery && (numBestHits == 0 || mergeHitLists)) {
            setMultiConfExportParameter(hitMolWriters.back(), true);

            for (std::size_t i = 0, num_query_mols = queryMolecules.size(); i < num_query_mols; i++)
                outputQueryMolecule(hitMolWriters.back(), i);
        }

    } else {
        for (std::size_t i = 0, num_query_mols = queryMolecules.size(); i < num_query_mols; i++) {
            auto file_name = getOutputFileName(hitOutputFile, i);

            try {
                hitMolWriters.push_back(hitOutputFormat.empty() ? new Chem::MolecularGraphWriter(file_name) :
                                        new Chem::MolecularGraphWriter(file_name, hitOutputFormat));

            } catch (const Base::IOError& e) {
                throw Base::IOError("no output handler found for hit molecule file '" + file_name + '\'');
            }
            
            if (outputQuery) {
                setMultiConfExportParameter(hitMolWriters.back(), true);
                outputQueryMolecule(hitMolWriters.back(), i);
            }
        }
    }
}

void SimScreenImpl::outputHitLists()
{
    if (numBestHits == 0)
        return;

    printMessage(INFO, "");

    if (progressEnabled()) {
        initInfiniteProgress();
        printMessage(INFO, "Writing Output Files...", true, true);
    } else
        printMessage(INFO, "Writing Output Files...");

    if (!reportFile.empty())
        outputReportFiles();
    
    if (termSignalCaught())
        return;

    if (!hitOutputFile.empty())
        outputHitMoleculeFiles();
}

void SimScreenImpl::outputReportFiles()
{
    if (splitOutFiles) {
        for (std::size_t i = 0, num_query_mols = queryMolecules.size(); i < num_query_mols; i++) {
            auto& os = reportOStreams[i];
            auto& hit_list = (mergeHitLists ? hitLists[0] : hitLists[i]);

            for (auto& hit_data : hit_list) {
                if (mergeHitLists && hit_data.screeningResult.queryMolIdx != i)
                    continue;

                printInfiniteProgress("Writing Output Files");
                outputReportFileHitData(os, hit_data);
            }
        }

    } else {
        auto& os = reportOStreams[0];

        for (auto& hit_list : hitLists) {
            for (auto& hit_data : hit_list) {
                printInfiniteProgress("Writing Output Files");
                outputReportFileHitData(os, hit_data);
            }
        }
    }
}

void SimScreenImpl::outputReportFileHeader(std::ostream& os) const
{
    os << "Database Mol. Name\t" << "Database Mol. Index\t" << "Database Conf. Index\t";

    if (!splitOutFiles)
        os << "Query Mol. Name\t" << "Query Mol. Index\t";
    
    os << "Query Conf. Index\t" << scoringFunc->getDisplayName() << '\n';

    if (!os.good())
        throw CDPL::Base::IOError("writing to report file failed");
}

void SimScreenImpl::outputReportFileHitData(std::ostream& os, const HitMoleculeData& hit_data)
{
    numSavedHits++;

    os << hit_data.dbMolName << '\t'
       << (hit_data.dbMolIndex + 1) << '\t'
       << (hit_data.screeningResult.dbMolConfIdx + 1) << '\t';

    if (!splitOutFiles) {
        os << getName(queryMolecules[hit_data.screeningResult.queryMolIdx]) << '\t'
           << (hit_data.screeningResult.queryMolIdx + 1) << '\t';
    }
    
    os << (hit_data.screeningResult.queryMolConfIdx + 1) << '\t'
       << (boost::format("%.3f") % hit_data.screeningResult.score).str() << '\n';

    if (!os.good())
        throw CDPL::Base::IOError("writing to report file failed");
}

void SimScreenImpl::outputHitMoleculeFiles()
{
    if (splitOutFiles) {
        for (std::size_t i = 0, num_query_mols = queryMolecules.size(); i < num_query_mols; i++) {
            auto& writer = hitMolWriters[i];
            auto& hit_list = (mergeHitLists ? hitLists[0] : hitLists[i]);

            for (auto& hit_data : hit_list) {
                if (mergeHitLists && hit_data.screeningResult.queryMolIdx != i)
                    continue;

                printInfiniteProgress("Writing Output Files");
                outputHitMolecule(writer, hit_data);
            }
        }

    } else {
        auto& writer = hitMolWriters[0];
        std::size_t i = 0;

        for (auto& hit_list : hitLists) {
            if (outputQuery && !mergeHitLists) {
                setMultiConfExportParameter(writer, true);
                outputQueryMolecule(writer, i);
            }

            for (auto& hit_data : hit_list) {
                printInfiniteProgress("Writing Output Files");
                outputHitMolecule(writer, hit_data);
            }
        }
    }
}

void SimScreenImpl::outputQueryMolecule(CDPL::Chem::MolecularGraphWriter& writer, std::size_t query_mol_idx)
{
    using namespace CDPL;

    auto& query_mol = queryMolecules[query_mol_idx];

    try {
        if (writer.write(query_mol))
            return;

    } catch (const std::exception& e) {
        throw Base::IOError("writing query molecule " + createMoleculeIdentifier(query_mol_idx + 1, query_mol) + " failed: " + e.what());

    } catch (...) {}

    throw Base::IOError("unspecified error while writing query molecule " + createMoleculeIdentifier(query_mol_idx + 1, query_mol));
}

void SimScreenImpl::outputHitMolecule(CDPL::Chem::MolecularGraphWriter& writer, const HitMoleculeData& hit_data)
{
    using namespace CDPL;

    if (reportFile.empty())
        numSavedHits++;

    try {
        auto name = hitNamePattern;

        boost::replace_all(name, "@Q@", getName(queryMolecules[hit_data.screeningResult.queryMolIdx]));
        boost::replace_all(name, "@D@", hit_data.dbMolName);
        boost::replace_all(name, "@C@", std::to_string(hit_data.screeningResult.queryMolConfIdx + 1));
        boost::replace_all(name, "@c@", std::to_string(hit_data.screeningResult.dbMolConfIdx + 1));
        boost::replace_all(name, "@I@", std::to_string(hit_data.screeningResult.queryMolIdx + 1));
        boost::replace_all(name, "@i@", std::to_string(hit_data.dbMolIndex + 1));

        setName(*hit_data.dbMolecule, name);

        if (descrCalculator->requires3DCoordinates())
            applyConformation(*hit_data.dbMolecule, hit_data.screeningResult.dbMolConfIdx);

        setMultiConfExportParameter(writer, false);

        if (scoreSDTags || queryNameSDTags || queryMolIdxSDTags || queryConfIdxSDTags || dbMolIdxSDTags || dbConfIdxSDTags) {
            Chem::StringDataBlock::SharedPointer old_sd_block;
            Chem::StringDataBlock::SharedPointer new_sd_block;

            if (hasStructureData(*hit_data.dbMolecule)) {
                old_sd_block = getStructureData(*hit_data.dbMolecule);
                new_sd_block.reset(new Chem::StringDataBlock(*old_sd_block));

            } else
                new_sd_block.reset(new Chem::StringDataBlock());

            if (dbConfIdxSDTags)
                new_sd_block->addEntry("<Conf. Index>", std::to_string(hit_data.screeningResult.dbMolConfIdx + 1));

            if (dbMolIdxSDTags)
                new_sd_block->addEntry("<Mol. Index>", std::to_string(hit_data.dbMolIndex + 1));

            if (queryConfIdxSDTags)
                new_sd_block->addEntry("<Query Conf. Index>", std::to_string(hit_data.screeningResult.queryMolConfIdx + 1));

            if (queryMolIdxSDTags)
                new_sd_block->addEntry("<Query Mol. Index>", std::to_string(hit_data.screeningResult.queryMolIdx + 1));

            if (queryNameSDTags)
                new_sd_block->addEntry("<Query Name>", getName(queryMolecules[hit_data.screeningResult.queryMolIdx]));
            
            if (scoreSDTags)
                new_sd_block->addEntry('<' + scoringFunc->getDisplayName() + '>', (boost::format("%.3f") % hit_data.screeningResult.score).str());

            setStructureData(*hit_data.dbMolecule, new_sd_block);

            if (writer.write(*hit_data.dbMolecule)) {
                if (old_sd_block)
                    setStructureData(*hit_data.dbMolecule, old_sd_block);
                else
                    clearStructureData(*hit_data.dbMolecule);

                return;
            }

        } else if (writer.write(*hit_data.dbMolecule))
            return;

    } catch (const std::exception& e) {
        throw CDPL::Base::IOError("writing hit molecule " + createMoleculeIdentifier(hit_data.dbMolIndex + 1, *hit_data.dbMolecule) + " failed: " + e.what());

    } catch (...) {}

    throw CDPL::Base::IOError("unspecified error while writing hit molecule " + createMoleculeIdentifier(hit_data.dbMolIndex + 1, *hit_data.dbMolecule));
}

void SimScreenImpl::setErrorMessage(const std::string& msg)
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

std::size_t SimScreenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
    if (termSignalCaught())
        return 0;

    if (haveErrorMessage())
        return 0;

    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(molReadMutex);

        return doReadNextMolecule(mol);
    }

    return doReadNextMolecule(mol);
}

std::size_t SimScreenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
    while (true) {
        try {
            if (!databaseReader->read(mol)) {
                printInfiniteProgress("Screening Molecules (" + std::to_string(numProcMols) + " passed)", true);
                return 0;
            }

            numProcMols++;
            printInfiniteProgress("Screening Molecules (" + std::to_string(numProcMols) + " passed)");

            return databaseReader->getRecordIndex();

        } catch (const std::exception& e) {
            printMessage(ERROR, "Error while reading database molecule " + createMoleculeIdentifier(databaseReader->getRecordIndex() + 1) + ": " + e.what());

        } catch (...) {
            printMessage(ERROR, "Unspecified error while reading database molecule " + createMoleculeIdentifier(databaseReader->getRecordIndex() + 1));
        }

        numProcMols++;

        databaseReader->setRecordIndex(databaseReader->getRecordIndex() + 1);
    }

    return 0;
}

bool SimScreenImpl::haveErrorMessage()
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);
        
        return !errorMessage.empty();
    }

    return !errorMessage.empty();
}

void SimScreenImpl::printStatistics()
{
    std::size_t proc_time = std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed()).count();

    printMessage(INFO, "");
    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Num. processed Molecules: " + std::to_string(numProcMols));
    printMessage(INFO, " Num. Hit Molecules:       " + std::to_string(numHits));
    printMessage(INFO, " Num. saved Hits:          " + std::to_string(numSavedHits));
    printMessage(INFO, " Processing Time:          " + CmdLineLib::formatTimeDuration(proc_time));
}

void SimScreenImpl::checkOutputFileOptions() const
{
    if (hitOutputFile.empty() && reportFile.empty())
        throw CDPL::Base::ValueError("A hit output and/or report file has to be specified");
}

void SimScreenImpl::checkInputFiles() const
{
    using namespace CDPL;

    if (!Util::fileExists(queryFile))
        throw Base::IOError("query molecule file '" + queryFile + "' does not exist");

    if (!Util::fileExists(databaseFile))
        throw Base::IOError("molecule database file '" + databaseFile + "' does not exist");

    if (!splitOutFiles) {
        if (Util::checkIfSameFile(queryFile, hitOutputFile))
            throw Base::ValueError("hit output file must not be identical to query molecule file");

        if (Util::checkIfSameFile(queryFile, reportFile))
            throw Base::ValueError("report output file must not be identical to query molecule file");

        if (Util::checkIfSameFile(databaseFile, hitOutputFile))
            throw Base::ValueError("hit output file must not be identical to screening database file");

        if (Util::checkIfSameFile(databaseFile, reportFile))
            throw Base::ValueError("report output file must not be identical to screening database file");
    }
}

void SimScreenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    if (numThreads == 0) {
        CmdLineBase::printMessage(level, msg, nl, file_only);
        return;
    }

    std::lock_guard<std::mutex> lock(mutex);

    CmdLineBase::printMessage(level, msg, nl, file_only);
}

void SimScreenImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Query File:                          " + queryFile);
    printMessage(VERBOSE, " Database File:                       " + databaseFile);
    printMessage(VERBOSE, " Hit Output File:                     " + (hitOutputFile.empty() ? std::string("None") : hitOutputFile));
    printMessage(VERBOSE, " Report Output File:                  " + (reportFile.empty() ? std::string("None") : reportFile));
    printMessage(VERBOSE, " Screening Mode:                      " + screeningModeToString());
    printMessage(VERBOSE, " Descriptor Type:                     " + descrCalculator->getID());

    std::string ext_summary_str;

    descrCalculator->getOptionSummary(ext_summary_str);

    printOptionSummary(ext_summary_str);
    
    printMessage(VERBOSE, " Scoring Function:                    " + scoringFunc->getID());

    ext_summary_str.clear();
    scoringFunc->getOptionSummary(ext_summary_str);

    printOptionSummary(ext_summary_str);
    
    printMessage(VERBOSE, " Num. saved best Hits:                " + (numBestHits > 0 ? std::to_string(numBestHits) : std::string("All Hits")));
    printMessage(VERBOSE, " Max. Num. Hits:                      " + (maxNumHits > 0 ? std::to_string(maxNumHits) : std::string("No Limit")));
    printMessage(VERBOSE, " Score Cutoff:                        " + (scoreCutoff < 0.0 ? std::string("None") : (boost::format("%.3f") % scoreCutoff).str()));
    printMessage(VERBOSE, " Merge Hit Lists:                     " + std::string(mergeHitLists ? "Yes" : "No"));
    printMessage(VERBOSE, " Output File Splitting:               " + std::string(splitOutFiles ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Query Molecules:              " + std::string(outputQuery ? "Yes" : "No"));
    printMessage(VERBOSE, " Single Conformer DB-Mode:            " + std::string(singleConfSearch ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Score SD-Tags:                " + std::string(scoreSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Query Mol. Name SD-Tags:      " + std::string(queryNameSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Query Mol. Index SD-Tags:     " + std::string(queryMolIdxSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Query Conf. Index SD-Tags:    " + std::string(queryConfIdxSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Database Mol. Index SD-Tags:  " + std::string(dbMolIdxSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Output Database Conf. Index SD-Tags: " + std::string(dbConfIdxSDTags ? "Yes" : "No"));
    printMessage(VERBOSE, " Hit Output Mol. Name Pattern:        " + hitNamePattern);
    printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

    if (numThreads > 0)
        printMessage(VERBOSE, " Number of Threads:                   " + std::to_string(numThreads));

    printMessage(VERBOSE, " Query File Format:                   " + (!queryFormat.empty() ? queryFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Database File Format:                " + (!databaseFormat.empty() ? databaseFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Hit File Format:                     " + (!hitOutputFormat.empty() ? hitOutputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, "");
}

void SimScreenImpl::printOptionSummary(const std::string& summary)
{
    for (std::string::size_type i = 0; ; ) {
        auto title_end = summary.find_first_of(';', i);

        if (title_end == std::string::npos)
            break;

        auto value_end = summary.find_first_of(';', title_end + 1);

        if (value_end == std::string::npos)
            break;

        printMessage(VERBOSE, ' ' + summary.substr(i, title_end - i) + ':' + std::string((title_end - i) < 36 ? 36 - (title_end - i) : 0, ' ') +
                     summary.substr(title_end + 1, value_end - title_end - 1));

        i = value_end + 1;
    }
}
    
void SimScreenImpl::initQueryReader()
{
    using namespace CDPL;

    if (termSignalCaught())
        return;

    try {
        queryReader.reset(queryFormat.empty() ? new Chem::MoleculeReader(queryFile) :
                                                new Chem::MoleculeReader(queryFile, queryFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no input handler found for query molecule file '" + queryFile + '\'');
    }

    setMultiConfImportParameter(*queryReader, true);
}

void SimScreenImpl::initDatabaseReader()
{
    using namespace CDPL;

    if (termSignalCaught())
        return;

    try {
        databaseReader.reset(databaseFormat.empty() ? new Chem::MoleculeReader(databaseFile) :
                                                      new Chem::MoleculeReader(databaseFile, databaseFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no input handler found for molecule database file '" + databaseFile + '\'');
    }
   
    setMultiConfImportParameter(*databaseReader, true);
}

void SimScreenImpl::initScoringFunctions()
{
    scoringFuncs.push_back(new TanimotoSimilarity());
    
    // TODO
}

void SimScreenImpl::initDescriptorCalculators()
{
    descrCalculators.push_back(new ECFPCalculator());
    
    // TODO
}
        
std::string SimScreenImpl::screeningModeToString() const
{
    switch (screeningMode) {
        
        case ScreeningProcessor::BEST_OVERALL_MATCH:
            return "BEST_OVERALL";

        case ScreeningProcessor::BEST_MATCH_PER_QUERY:
            return "BEST_PER_QUERY";

        case ScreeningProcessor::BEST_MATCH_PER_QUERY_CONF:
            return "BEST_PER_QUERY_CONF";

        default:
            break;
    }
 
    return "UNKNOWN";
}

std::string SimScreenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
    if (!getName(mol).empty())
        return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

    return createMoleculeIdentifier(rec_idx);
}

std::string SimScreenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return std::to_string(rec_idx);
}

std::string SimScreenImpl::getOutputFileName(const std::string& file_name_tmplt, std::size_t query_mol_idx) const
{
    auto suffix_pos = file_name_tmplt.find_last_of('.');
    auto file_name = file_name_tmplt;
        
    if (suffix_pos != std::string::npos)
        return file_name.insert(suffix_pos, "_" + std::to_string(query_mol_idx + 1));

    return file_name.append("_" + std::to_string(query_mol_idx + 1));
}

ScoringFunction* SimScreenImpl::getScoringFunction(const std::string& id)
{
    for (auto& func : scoringFuncs)
        if (CDPL::Internal::isEqualCI(id, func.getID()))
            return &func;
    
    return nullptr;
}

DescriptorCalculator* SimScreenImpl::getDescriptorCalculator(const std::string& id)
{
    for (auto& calc : descrCalculators)
        if (CDPL::Internal::isEqualCI(id, calc.getID()))
            return &calc;
    
    return nullptr;
}

std::string SimScreenImpl::getScoringFunctionIDs() const
{
    std::string ids;

    for (auto& func : scoringFuncs) {
        if (!ids.empty())
            ids.append(", ");

        ids.append(func.getID());
    }
    
    return ids;
}

std::string SimScreenImpl::getDescriptorCalculatorIDs() const
{
    std::string ids;

    for (auto& calc : descrCalculators) {
        if (!ids.empty())
            ids.append(", ");

        ids.append(calc.getID());
    }
    
    return ids;
}
