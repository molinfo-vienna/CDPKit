/* 
 * SimSearchImpl.hpp
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


#ifndef SIMSEARCH_SIMSEARCHIMPL_HPP
#define SIMSEARCH_SIMSEARCHIMPL_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <set>
#include <iosfwd>
#include <mutex>
#include <memory>
#include <functional>

#include <boost/ptr_container/ptr_vector.hpp>

#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphWriter.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"

#include "ScreeningProcessor.hpp"


namespace SimSearch
{

    class ScoringFunction;
    class DescriptorCalculator;

    class SimSearchImpl : public CmdLineLib::CmdLineBase
    {

      public:
        SimSearchImpl();

        ~SimSearchImpl();
        
      private:
        typedef std::shared_ptr<CDPL::Chem::Molecule> MoleculePtr;

        class ScreeningWorker;

        struct HitMoleculeData
        {

            HitMoleculeData(std::size_t db_mol_idx, const std::string& db_mol_name, const ScreeningProcessor::Result& res):
                dbMolIndex(db_mol_idx), dbMolName(db_mol_name), screeningResult(res), dbMolecule() {}

            HitMoleculeData(std::size_t db_mol_idx, const std::string& db_mol_name,
                            const ScreeningProcessor::Result& res, const MoleculePtr& db_mol):
                dbMolIndex(db_mol_idx), dbMolName(db_mol_name), screeningResult(res), dbMolecule(db_mol) {}
            
            std::size_t                dbMolIndex;
            std::string                dbMolName;
            ScreeningProcessor::Result screeningResult;
            MoleculePtr                dbMolecule;
        };

        const char* getProgName() const;
        const char* getProgAboutText() const;

        void addOptionLongDescriptions();

        void setScoringFunction(const std::string& id);
        void setDescriptorCalculator(const std::string& id);
        void setScreeningMode(const std::string& mode);

        void setQueryFormat(const std::string& file_ext);
        void setDatabaseFormat(const std::string& file_ext);
        void setHitOutputFormat(const std::string& file_ext);

        void checkInputFiles() const;
        void checkOutputFileOptions() const;

        void initQueryReader();
        void initDatabaseReader();
        void initHitLists();
        void initReportFileStreams();
        void initHitMoleculeWriters();
        void initScoringFunctions();
        void initDescriptorCalculators();

        void processOptions();
        int process();

        void processSingleThreaded();
        void processMultiThreaded();

        bool processHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                        const MoleculePtr& db_mol, const ScreeningProcessor::Result& res);
        bool doProcessHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                          const MoleculePtr& db_mol, const ScreeningProcessor::Result& res);

        void readQueryMolecules();

        void outputHitLists();
        void outputReportFiles();
        void outputHitMoleculeFiles();

        void outputReportFileHeader(std::ostream& os) const;
        void outputReportFileHitData(std::ostream& os, const HitMoleculeData& hit_data);

        void outputQueryMolecule(CDPL::Chem::MolecularGraphWriter& writer, std::size_t query_mol_idx);
        void outputHitMolecule(CDPL::Chem::MolecularGraphWriter& writer, const HitMoleculeData& hit_data);

        std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
        std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

        void printStatistics();

        void printOptionSummary();

        std::string screeningModeToString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        std::string getOutputFileName(const std::string& file_name_tmplt, std::size_t query_mol_idx) const;

        ScoringFunction* getScoringFunction(const std::string& id);
        DescriptorCalculator* getDescriptorCalculator(const std::string& id);

        std::string getScoringFunctionIDs() const;
        std::string getDescriptorCalculatorIDs() const;
        
        typedef std::shared_ptr<CDPL::Chem::MoleculeReader>                                                          MoleculeReaderPtr;
        typedef boost::ptr_vector<CDPL::Chem::Molecule>                                                              QueryMoleculeList;
        typedef std::multiset<HitMoleculeData, std::function<bool(const HitMoleculeData&, const HitMoleculeData&)> > HitList;
        typedef std::vector<HitList>                                                                                 HitListArray;
        typedef boost::ptr_vector<std::ostream>                                                                      OStreamArray;
        typedef boost::ptr_vector<CDPL::Chem::MolecularGraphWriter>                                                  MoleculeWriterArray;
        typedef boost::ptr_vector<ScoringFunction>                                                                   ScoringFunctionList;
        typedef boost::ptr_vector<DescriptorCalculator>                                                              DescriptorCalculatorList;
        typedef CDPL::Internal::Timer                                                                                Timer;

        std::string                       queryFile;
        std::string                       databaseFile;
        std::string                       hitOutputFile;
        std::string                       reportFile;
        ScoringFunction*                  scoringFunc;
        DescriptorCalculator*             descrCalculator;
        std::size_t                       numThreads;
        bool                              singleConfSearch;
        bool                              mergeHitLists;
        bool                              splitOutFiles;
        bool                              outputQuery;
        bool                              scoreSDTags;
        bool                              queryNameSDTags;
        bool                              queryMolIdxSDTags;
        bool                              queryConfIdxSDTags;
        bool                              dbMolIdxSDTags;
        bool                              dbConfIdxSDTags;
        std::string                       hitNamePattern;
        std::size_t                       numBestHits;
        std::size_t                       maxNumHits;
        double                            scoreCutoff;
        ScreeningProcessor::ScreeningMode screeningMode;
        std::string                       queryFormat;
        MoleculeReaderPtr                 queryReader;
        std::string                       databaseFormat;
        MoleculeReaderPtr                 databaseReader;
        std::string                       hitOutputFormat;
        QueryMoleculeList                 queryMolecules;
        HitListArray                      hitLists;
        OStreamArray                      reportOStreams;
        MoleculeWriterArray               hitMolWriters;
        ScoringFunctionList               scoringFuncs;
        DescriptorCalculatorList          descrCalculators;
        Timer                             timer;
        std::size_t                       numProcMols;
        std::size_t                       numHits;
        std::size_t                       numSavedHits;
        std::mutex                        mutex;
        std::mutex                        molReadMutex;
        std::mutex                        hitProcMutex;
        std::string                       errorMessage;
    };
} // namespace SimSearch

#endif // SIMSEARCH_SIMSEARCHIMPL_HPP
