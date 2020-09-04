/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ShapeScreenImpl.hpp
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


#ifndef SHAPESCREEN_SHAPESCREENIMPL_HPP
#define SHAPESCREEN_SHAPESCREENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>

#include <boost/thread.hpp>
#include <boost/chrono/chrono.hpp>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Shape/ScreeningSettings.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace CDPL
{

	namespace Chem
	{

		class Molecule;
		class MolecularGraph;
	}
}


namespace ShapeScreen
{

    class ShapeScreenImpl : public CmdLineLib::CmdLineBase
    {

    public:
		ShapeScreenImpl();

    private:
		typedef CDPL::Base::DataOutputHandler<CDPL::Chem::MolecularGraph> OutputHandler;
		typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
		typedef InputHandler::SharedPointer InputHandlerPtr;
		typedef OutputHandler::SharedPointer OutputHandlerPtr;

		const char* getProgName() const;
		const char* getProgCopyright() const;
		const char* getProgAboutText() const;

		int process();

		void processSingleThreaded();
		void processMultiThreaded();

		std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
		std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

		void writeMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed);
		void doWriteMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed);

		void setErrorMessage(const std::string& msg);
		bool haveErrorMessage();

		void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

		void printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols, std::size_t num_gen_confs, std::size_t proc_time);

		void checkInputFiles() const;
		void printOptionSummary();
		void initInputReader();
		void initOutputWriters();

		InputHandlerPtr getInputHandler(const std::string& file_path) const;
		OutputHandlerPtr getOutputHandler(const std::string& file_path) const;

		void addOptionLongDescriptions();

		class InputScanProgressCallback;
		class ScreeningWorker;

		typedef std::vector<std::string> StringList;
		typedef CDPL::Base::DataReader<CDPL::Chem::Molecule> MoleculeReader;
		typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
		typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer MoleculeWriterPtr;
		typedef boost::chrono::system_clock Clock;
		typedef CDPL::Shape::ScreeningSettings ScreeningSettings;
	
		StringList                     inputFiles;
		std::string                    outputFile;
		std::size_t                    numThreads;
		ScreeningSettings              settings;
		boost::mutex                   readMolMutex;
		boost::mutex                   writeMolMutex;
		std::string                    errorMessage;
		Clock::time_point              startTime;
    };
}

#endif // SHAPESCREEN_SHAPESCREENIMPL_HPP
