/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
#include <chrono>
#include <mutex>

#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Base/DataReader.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"

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
	}
}


namespace PSDScreen
{

    class PSDScreenImpl : public CmdLineLib::CmdLineBase
    {

    public:
		PSDScreenImpl();

    private:
		struct ScreeningWorker;

		typedef CDPL::Base::DataOutputHandler<CDPL::Chem::MolecularGraph> HitOutputHandler;
		typedef CDPL::Base::DataInputHandler<CDPL::Pharm::Pharmacophore> QueryInputHandler;
		typedef HitOutputHandler::SharedPointer HitOutputHandlerPtr;
		typedef QueryInputHandler::SharedPointer QueryInputHandlerPtr;
		typedef CDPL::Pharm::ScreeningProcessor::SearchHit SearchHit;

		const char* getProgName() const;
		const char* getProgCopyright() const;
		const char* getProgAboutText() const;

		void setHitOutputFormat(const std::string& file_ext);
		void setQueryInputFormat(const std::string& file_ext);
		void setMatchingMode(const std::string& mode);

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

		HitOutputHandlerPtr getHitOutputHandler(const std::string& file_path) const;
		QueryInputHandlerPtr getQueryInputHandler(const std::string& file_path) const;

		void addOptionLongDescriptions();
	
		typedef CDPL::Pharm::ScreeningProcessor::HitReportMode MatchingMode;
		typedef std::chrono::system_clock Clock;
		typedef boost::shared_ptr<CDPL::Pharm::FileScreeningHitCollector> HitCollectorPtr;
		typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer HitWriterPtr;
		typedef CDPL::Base::DataReader<CDPL::Pharm::Pharmacophore>::SharedPointer QueryReaderPtr;
		typedef std::vector<double> WorkerProgressArray;

		std::string              queryPharmFile;
		std::string              screeningDB;
		std::string              hitOutputFile;
		bool                     checkXVols;
		bool                     alignConfs;
		bool                     bestAlignments;
		bool                     outputScore;
		bool                     outputMolIndex;
		bool                     outputConfIndex;
		bool                     outputDBName;
		bool                     outputPharmName;
		bool                     outputPharmIndex;
		std::size_t              numThreads;
		std::size_t              startMolIndex;
		std::size_t              endMolIndex;
		std::size_t              maxOmittedFtrs;
		MatchingMode             matchingMode;
		HitOutputHandlerPtr      hitOutputHandler;
		QueryInputHandlerPtr     queryInputHandler;
		HitWriterPtr             hitMolWriter;
		QueryReaderPtr           queryPharmReader;
		HitCollectorPtr          hitCollector;
		std::mutex               mutex;
		std::mutex               collHitMutex;
		std::string              errorMessage;
		Clock::time_point        startTime;
		std::size_t              numQueryPharms;
		std::size_t              numDBMolecules;
		std::size_t              numDBPharms;
		std::size_t              numHits;
		std::size_t              maxNumHits;
		int                      lastProgValue;
		WorkerProgressArray      workerProgArray;
    };
}

#endif // PSDSCREEN_PSDSCREENIMPL_HPP
