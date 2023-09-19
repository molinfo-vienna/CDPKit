/* 
 * ShapeScreenImpl.hpp
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


#ifndef SHAPESCREEN_SHAPESCREENIMPL_HPP
#define SHAPESCREEN_SHAPESCREENIMPL_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <set>
#include <iosfwd>
#include <mutex>
#include <memory>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphWriter.hpp"
#include "CDPL/Shape/ScreeningSettings.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace ShapeScreen
{

    class ShapeScreenImpl : public CmdLineLib::CmdLineBase
    {

      public:
        ShapeScreenImpl();

      private:
        typedef CDPL::Shape::ScreeningSettings                  ScreeningSettings;
        typedef CDPL::Chem::Molecule::SharedPointer             MoleculePtr;
        typedef CDPL::Chem::MolecularGraphWriter::SharedPointer MoleculeWriterPtr;

        class ScreeningWorker;

        struct HitMoleculeData
        {

            HitMoleculeData(std::size_t db_mol_idx, const std::string& db_mol_name, const CDPL::Shape::AlignmentResult& res):
                dbMolIndex(db_mol_idx), dbMolName(db_mol_name), almntResult(res), dbMolecule() {}

            HitMoleculeData(std::size_t db_mol_idx, const std::string& db_mol_name,
                            const CDPL::Shape::AlignmentResult& res, const MoleculePtr& db_mol):
                dbMolIndex(db_mol_idx),
                dbMolName(db_mol_name), almntResult(res), dbMolecule(db_mol) {}

            bool operator<(const HitMoleculeData& rhs) const
            {
                return (almntResult.getScore() > rhs.almntResult.getScore());
            }

            std::size_t                  dbMolIndex;
            std::string                  dbMolName;
            CDPL::Shape::AlignmentResult almntResult;
            MoleculePtr                  dbMolecule;
        };

        const char* getProgName() const;
        const char* getProgAboutText() const;

        void addOptionLongDescriptions();

        void setNumRandomStarts(std::size_t num_starts);

        void setColorFeatureType(const std::string& type);
        void setScoringFunction(const std::string& func);
        void setScreeningMode(const std::string& mode);

        void enableAllCarbonMode(bool all_c);
        void performOverlayOptimization(bool opt);
        void performThoroughOverlayOptimization(bool thorough);
        void performSingleConformerSearch(bool single_conf);

        void setScoreCutoff(double cutoff);

        void setQueryFormat(const std::string& file_ext);
        void setDatabaseFormat(const std::string& file_ext);
        void setHitOutputFormat(const std::string& file_ext);

        void setAlignmentMode();
        void checkInputFiles() const;
        void checkOutputFileOptions() const;

        void initQueryReader();
        void initDatabaseReader();
        void initHitLists();
        void initReportFileStreams();
        void initHitMoleculeWriters();

        int process();

        void processSingleThreaded();
        void processMultiThreaded();

        bool processHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                        const MoleculePtr& db_mol, const CDPL::Shape::AlignmentResult& res);
        bool doProcessHit(std::size_t db_mol_idx, const std::string& db_mol_name,
                          const MoleculePtr& db_mol, const CDPL::Shape::AlignmentResult& res);

        void readQueryMolecules();

        void setupMolecule(CDPL::Chem::Molecule& mol) const;

        void outputHitLists();
        void outputReportFiles();
        void outputHitMoleculeFiles();

        void outputReportFileHeader(std::ostream& os) const;
        void outputReportFileHitData(std::ostream& os, const HitMoleculeData& hit_data);

        void outputQueryMolecule(const MoleculeWriterPtr& writer, std::size_t query_mol_idx);
        void outputHitMolecule(const MoleculeWriterPtr& writer, const HitMoleculeData& hit_data);

        std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
        std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

        void printStatistics();

        void printOptionSummary();

        std::string screeningModeToString(ScreeningSettings::ScreeningMode mode) const;
        ScreeningSettings::ScreeningMode stringToScreeningMode(const std::string& mode_str) const;

        std::string colorFeatureTypeToString(ScreeningSettings::ColorFeatureType type) const;
        ScreeningSettings::ColorFeatureType stringToColorFeatureType(const std::string& type_str) const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        std::string getOutputFileName(const std::string& file_name_tmplt, std::size_t query_mol_idx) const;

        typedef std::shared_ptr<std::ostream>             OStreamPtr;
        typedef CDPL::Chem::MoleculeReader::SharedPointer MoleculeReaderPtr;
        typedef std::vector<MoleculePtr>                  QueryMoleculeList;
        typedef std::multiset<HitMoleculeData>            HitList;
        typedef std::vector<HitList>                      HitListArray;
        typedef std::vector<OStreamPtr>                   OStreamArray;
        typedef std::vector<MoleculeWriterPtr>            MoleculeWriterArray;
        typedef CDPL::Internal::Timer                     Timer;

        std::string         queryFile;
        std::string         databaseFile;
        std::string         hitOutputFile;
        std::string         reportFile;
        std::string         scoringFunc;
        std::size_t         numThreads;
        ScreeningSettings   settings;
        bool                scoringOnly;
        bool                mergeHitLists;
        bool                splitOutFiles;
        bool                outputQuery;
        bool                scoreSDTags;
        bool                queryNameSDTags;
        bool                queryMolIdxSDTags;
        bool                queryConfIdxSDTags;
        bool                dbMolIdxSDTags;
        bool                dbConfIdxSDTags;
        bool                colorCenterStarts;
        bool                atomCenterStarts;
        bool                shapeCenterStarts;
        std::string         hitNamePattern;
        std::size_t         numBestHits;
        std::size_t         maxNumHits;
        double              shapeScoreCutoff;
        std::string         queryFormat;
        MoleculeReaderPtr   queryReader;
        std::string         databaseFormat;
        MoleculeReaderPtr   databaseReader;
        std::string         hitOutputFormat;
        QueryMoleculeList   queryMolecules;
        HitListArray        hitLists;
        OStreamArray        reportOStreams;
        MoleculeWriterArray hitMolWriters;
        Timer               timer;
        std::size_t         numProcMols;
        std::size_t         numHits;
        std::size_t         numSavedHits;
        std::mutex          mutex;
        std::mutex          molReadMutex;
        std::mutex          hitProcMutex;
        std::string         errorMessage;
    };
} // namespace ShapeScreen

#endif // SHAPESCREEN_SHAPESCREENIMPL_HPP
