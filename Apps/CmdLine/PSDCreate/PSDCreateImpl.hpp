/* 
 * PSDCreateImpl.hpp
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


#ifndef PSDCREATE_PSDCREATEIMPL_HPP
#define PSDCREATE_PSDCREATEIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <mutex>

#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }
} // namespace CDPL


namespace PSDCreate
{

    class PSDCreateImpl : public CmdLineLib::CmdLineBase
    {

      public:
        PSDCreateImpl();

      private:
        const char* getProgName() const;
        const char* getProgAboutText() const;

        void setCreationMode(const std::string& mode_str);
        void setInputFormat(const std::string& file_ext);
        void setTmpFileDirectory(const std::string& dir_path);

        int process();

        void processSingleThreaded();
        void processMultiThreaded();

        std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
        std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printStatistics(std::size_t num_proc, std::size_t num_rej, std::size_t num_del,
                             std::size_t num_ins);

        void checkInputFiles() const;
        void printOptionSummary();
        void initInputReader();

        std::string getCreationModeString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        void addOptionLongDescriptions();

        struct InputScanProgressCallback;
        struct MergeDBsProgressCallback;
        struct DBCreationWorker;

        typedef std::vector<std::string>                             StringList;
        typedef CDPL::Pharm::ScreeningDBCreator::Mode                CreationMode;
        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Internal::Timer                                Timer;

        StringList         inputFiles;
        std::string        outputDatabase;
        bool               dropDuplicates;
        std::size_t        numThreads;
        CreationMode       creationMode;
        std::string        inputFormat;
        CompMoleculeReader inputReader;
        std::mutex         mutex;
        std::mutex         molReadMutex;
        std::string        errorMessage;
        bool               addSourceFileProp;
        Timer              timer;
    };
} // namespace PSDCreate

#endif // PSDCREATE_PSDCREATEIMPL_HPP
