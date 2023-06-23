/* 
 * TautGenImpl.hpp
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


#ifndef TAUTGEN_TAUTGENIMPL_HPP
#define TAUTGEN_TAUTGENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <mutex>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Chem/ProtonationStateStandardizer.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
        class MolecularGraph;
    }
}


namespace TautGen
{

    class TautGenImpl : public CmdLineLib::CmdLineBase
    {

    public:
        TautGenImpl();

    private:
        enum Mode 
        {

          STANDARDIZE,
          TOPOLOGICALLY_UNIQUE,
          GEOMETRICALLY_UNIQUE,
          EXHAUSTIVE
        };

        typedef CDPL::Base::DataOutputHandler<CDPL::Chem::MolecularGraph> OutputHandler;
        typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
        typedef InputHandler::SharedPointer InputHandlerPtr;
        typedef OutputHandler::SharedPointer OutputHandlerPtr;

        const char* getProgName() const;
        const char* getProgCopyright() const;
        const char* getProgAboutText() const;

        void setMode(const std::string& mode_str);
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

        void printStatistics(std::size_t num_proc_mols, std::size_t num_gen_taut);

        void checkInputFiles() const;
        void printOptionSummary();
        void initInputReader();
        void initOutputWriter();

        std::string getModeString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        InputHandlerPtr getInputHandler(const std::string& file_path) const;
        OutputHandlerPtr getOutputHandler(const std::string& file_path) const;

        void addOptionLongDescriptions();

        class InputScanProgressCallback;
        class TautGenerationWorker;

        typedef std::vector<std::string> StringList;
        typedef CDPL::Base::DataReader<CDPL::Chem::Molecule> MoleculeReader;
        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer MoleculeWriterPtr;
        typedef CDPL::Chem::ProtonationStateStandardizer ChargeNeutralizer;
        typedef CDPL::Internal::Timer Timer;
        
        StringList         inputFiles;
        std::string        outputFile;
        bool               regardStereo;
        bool               regardIsotopes;
        bool               neutralize;
        bool               ketoEnol;
        bool               imineEnamine;
        bool               nitrosoOxime;
        bool               amideImidicAcid;
        bool               lactamLactim;
        bool               keteneYnol;
        bool               nitroAci;
        bool               phosphinicAcid;
        bool               sulfenicAcid;
        bool               genericH13Shift;
        bool               genericH15Shift;
        std::size_t        numThreads;
        std::size_t        maxNumTautomers;
        Mode               mode;
        InputHandlerPtr    inputHandler;
        CompMoleculeReader inputReader;
        OutputHandlerPtr   outputHandler;
        MoleculeWriterPtr  outputWriter;
        std::mutex         mutex;
        std::mutex         readMolMutex;
        std::mutex         writeMolMutex;
        std::string        errorMessage;
        Timer              timer;
        std::size_t        numOutTautomers;
        ChargeNeutralizer  neutralizer;
    };
}

#endif // TAUTGEN_TAUTGENIMPL_HPP
