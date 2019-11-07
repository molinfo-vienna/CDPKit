/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDCreateImpl.hpp
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


#ifndef PSDCREATE_PSDCREATEIMPL_HPP
#define PSDCREATE_PSDCREATEIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>

#include <boost/thread.hpp>
#include <boost/chrono/chrono.hpp>

#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataInputHandler.hpp"

#include "Lib/CmdLineBase.hpp"


namespace CDPL
{

	namespace Chem
	{

		class Molecule;
	}
}


namespace PSDCreate
{

    class PSDCreateImpl : public AppUtils::CmdLineBase
    {

    public:
		PSDCreateImpl();

    private:
		typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
		typedef InputHandler::SharedPointer InputHandlerPtr;

		const char* getProgName() const;
		const char* getProgCopyright() const;
		const char* getProgAboutText() const;

		void setCreationMode(const std::string& mode);
		void setInputFormat(const std::string& file_ext);
		void setMaxNumThreads(unsigned int num_threads);
		void setTmpFileDirectory(const std::string& dir_path);

		int process();

		void processSingleThreaded();
		void processMultiThreaded();

		bool readNextMolecule(CDPL::Chem::Molecule& mol);
		bool doReadNextMolecule(CDPL::Chem::Molecule& mol);

		void setErrorMessage(const std::string& msg);
		bool haveErrorMessage();

		void printStatistics(std::size_t num_proc, std::size_t num_rej, 
							 std::size_t num_del, std::size_t num_ins,
							 std::size_t proc_time);

		void checkInputFiles() const;
		void printOptionSummary();
		void initInputReader();

		std::string getCreationModeString() const;

		InputHandlerPtr getInputHandler(const std::string& file_path) const;

		void addOptionLongDescriptions();

		struct InputScanProgressCallback;
		struct MergeDBsProgressCallback;
		struct DBCreationWorker;

		typedef std::vector<std::string> StringList;
		typedef CDPL::Pharm::ScreeningDBCreator::Mode CreationMode;
		typedef CDPL::Base::DataReader<CDPL::Chem::Molecule> MoleculeReader;
		typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
		typedef boost::chrono::system_clock Clock;

		StringList             inputFiles;
		std::string            outputDatabase;
		bool                   dropDuplicates;
		bool                   multiThreading;
		std::size_t            numThreads;
		CreationMode           creationMode;
		InputHandlerPtr        inputHandler;
		CompMoleculeReader     inputReader;   
		boost::mutex           mutex;
		boost::mutex           molReadMutex;
		std::string            errorMessage;
		bool                   addSourceFileProp;
		Clock::time_point      startTime;
    };
}

#endif // PSDCREATE_PSDCREATEIMPL_HPP
