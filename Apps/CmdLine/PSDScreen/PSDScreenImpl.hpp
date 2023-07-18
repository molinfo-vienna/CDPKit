/* 
 * PSDScreenImpl.hpp
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


#ifndef PSDSCREEN_PSDSCREENIMPL_HPP
#define PSDSCREEN_PSDSCREENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <mutex>
#include <memory>

#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Pharm/PharmacophoreReader.hpp"
#include "CDPL/Chem/MolecularGraphWriter.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Pharm
    {

        class Pharmacophore;
        class FileScreeningHitCollector;
    } // namespace Pharm
} // namespace CDPL


namespace PSDScreen
{

    class PSDScreenImpl : public CmdLineLib::CmdLineBase
    {

      public:
        PSDScreenImpl();

      private:
        struct ScreeningWorker;

        typedef CDPL::Pharm::ScreeningProcessor::SearchHit SearchHit;

        const char* getProgName() const;
        const char* getProgCopyright() const;
        const char* getProgAboutText() const;

        void setHitOutputFormat(const std::string& file_ext);
        void setQueryInputFormat(const std::string& file_ext);
        void setMatchingMode(const std::string& mode_str);

        int process();

        void processSingleThreaded();
        void processMultiThreaded();

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printStatistics();
        void printOptionSummary();

        void checkInputFiles() const;
        void initQueryPharmReader();
        void initHitCollector();
        void analyzeInputFiles();

        bool getQueryPharmacophore(std::size_t idx, CDPL::Pharm::Pharmacophore& pharm);
        bool doGetQueryPharmacophore(std::size_t idx, CDPL::Pharm::Pharmacophore& pharm);

        bool collectHit(const SearchHit& hit, double score);
        bool doCollectHit(const SearchHit& hit, double score);

        bool printProgress(std::size_t worker_idx, double progress);
        bool doPrintProgress(std::size_t worker_idx, double progress);

        std::string getMatchingModeString() const;

        void addOptionLongDescriptions();

        typedef CDPL::Pharm::ScreeningProcessor::HitReportMode          MatchingMode;
        typedef std::shared_ptr<CDPL::Pharm::FileScreeningHitCollector> HitCollectorPtr;
        typedef CDPL::Internal::Timer                                   Timer;
        typedef std::vector<double>                                     WorkerProgressArray;
        typedef CDPL::Pharm::PharmacophoreReader::SharedPointer         PharmReaderPtr;
        typedef CDPL::Chem::MolecularGraphWriter::SharedPointer         MoleculeWriterPtr;

        std::string         queryPharmFile;
        std::string         screeningDB;
        std::string         hitOutputFile;
        bool                checkXVols;
        bool                alignConfs;
        bool                bestAlignments;
        bool                outputScore;
        bool                outputMolIndex;
        bool                outputConfIndex;
        bool                outputDBName;
        bool                outputPharmName;
        bool                outputPharmIndex;
        std::size_t         numThreads;
        std::size_t         startMolIndex;
        std::size_t         endMolIndex;
        std::size_t         maxOmittedFtrs;
        MatchingMode        matchingMode;
        std::string         hitOutputFormat;
        std::string         queryInputFormat;
        MoleculeWriterPtr   hitMolWriter;
        PharmReaderPtr      queryPharmReader;
        HitCollectorPtr     hitCollector;
        std::mutex          mutex;
        std::mutex          collHitMutex;
        std::string         errorMessage;
        Timer               timer;
        std::size_t         numQueryPharms;
        std::size_t         numDBMolecules;
        std::size_t         numDBPharms;
        std::size_t         numHits;
        std::size_t         maxNumHits;
        int                 lastProgValue;
        WorkerProgressArray workerProgArray;
    };
} // namespace PSDScreen

#endif // PSDSCREEN_PSDSCREENIMPL_HPP
