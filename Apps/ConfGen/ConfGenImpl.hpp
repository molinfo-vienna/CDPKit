/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConfGenImpl.hpp
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


#ifndef CONFGEN_CONFGENIMPL_HPP
#define CONFGEN_CONFGENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>

#include <boost/thread.hpp>
#include <boost/chrono/chrono.hpp>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"

#include "Lib/CmdLineBase.hpp"


namespace CDPL
{

	namespace Chem
	{

		class Molecule;
		class MolecularGraph;
	}
}


namespace ConfGen
{

    class ConfGenImpl : public AppUtils::CmdLineBase
    {

    public:
		ConfGenImpl();

    private:
		typedef CDPL::Base::DataOutputHandler<CDPL::Chem::MolecularGraph> OutputHandler;
		typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
		typedef InputHandler::SharedPointer InputHandlerPtr;
		typedef OutputHandler::SharedPointer OutputHandlerPtr;

		const char* getProgName() const;
		const char* getProgCopyright() const;
		const char* getProgAboutText() const;

		void applyConfGenPreset(const std::string& pres_str);
		void applyFragBuildPreset(const std::string& pres_str);
		void setSamplingMode(const std::string& mode_str);
		void setTimeout(std::size_t timeout);
		void setStrictParameterization(bool strict);
		void setForceFieldType(const std::string& type_str);
		void setRMSD(double rmsd);
		void setEnergyWindow(double ewin);
		void setMaxNumConfs(std::size_t max_confs);
		void setInputFormat(const std::string& file_ext);
		void setOutputFormat(const std::string& file_ext);

		int process();

		void processSingleThreaded();
		void processMultiThreaded();

		std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
		std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

		void writeMolecule(const CDPL::Chem::MolecularGraph& mol);
		void doWriteMolecule(const CDPL::Chem::MolecularGraph& mol);

		void setErrorMessage(const std::string& msg);
		bool haveErrorMessage();

		void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

		void printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols, std::size_t num_gen_confs, std::size_t proc_time);

		void checkInputFiles() const;
		void printOptionSummary();
		void initInputReader();
		void initOutputWriters();

		std::string getForceFieldTypeString(unsigned int ff_type) const;
		std::string getSamplingModeString() const;

		std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
		std::string createMoleculeIdentifier(std::size_t rec_idx);

		InputHandlerPtr getInputHandler(const std::string& file_path) const;
		OutputHandlerPtr getOutputHandler(const std::string& file_path) const;

		void addOptionLongDescriptions();

		class InputScanProgressCallback;
		class ConformerGenerationWorker;

		typedef std::vector<std::string> StringList;
		typedef CDPL::Base::DataReader<CDPL::Chem::Molecule> MoleculeReader;
		typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
		typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer MoleculeWriterPtr;
		typedef boost::chrono::system_clock Clock;
		typedef CDPL::ConfGen::ConformerGeneratorSettings ConformerGeneratorSettings;
		typedef CDPL::ConfGen::FragmentConformerGeneratorSettings FragmentConformerGeneratorSettings;

		StringList                     inputFiles;
		std::string                    outputFile;
		std::string                    failedFile;
		std::size_t                    numThreads;
		ConformerGeneratorSettings     settings;
		std::string                    confGenPreset;              
		std::string                    fragBuildPreset;              
		bool                           canonicalize;
		InputHandlerPtr                inputHandler;
		CompMoleculeReader             inputReader;
		OutputHandlerPtr               outputHandler;
		MoleculeWriterPtr              outputWriter;
		OutputHandlerPtr               failedOutputHandler;
		MoleculeWriterPtr              failedOutputWriter;
		boost::mutex                   mutex;
		boost::mutex                   readMolMutex;
		boost::mutex                   writeMolMutex;
		std::string                    errorMessage;
		Clock::time_point              startTime;
    };
}

#endif // CONFGEN_CONFGENIMPL_HPP
