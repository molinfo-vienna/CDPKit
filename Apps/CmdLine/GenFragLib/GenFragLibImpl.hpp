/* 
 * GenFragLibImpl.hpp
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


#ifndef GENFRAGLIB_GENFRAGLIBIMPL_HPP
#define GENFRAGLIB_GENFRAGLIBIMPL_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
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


namespace GenFragLib
{

    class GenFragLibImpl : public CmdLineLib::CmdLineBase
    {

      public:
        GenFragLibImpl();

      private:
        typedef CDPL::ConfGen::FragmentLibrary FragmentLibrary;

        enum Mode
        {

            CREATE,
            UPDATE,
            MERGE
        };

        typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
        typedef InputHandler::SharedPointer                        InputHandlerPtr;

        const char* getProgName() const;
        const char* getProgCopyright() const;
        const char* getProgAboutText() const;

        void applyPreset(const std::string& pres_str);
        void setTimeout(std::size_t timeout);
        void setStrictParameterization(bool strict);
        void setDielectricConst(double de_const);
        void setDistExponent(double exp);
        void setPreserveBondingGeometry(bool preserve);
        void setRMSD(double rmsd);
        void setEnergyWindow(double ewin);
        void setSmallRingSystemSamplingFactor(std::size_t factor);
        void setForceFieldType(const std::string& type_str);
        void setMode(const std::string& mode_str);
        void setInputFormat(const std::string& file_ext);

        int process();

        void mergeFragmentLibraries();
        void processSingleThreaded();
        void processMultiThreaded();

        void loadFragmentLibrary(const std::string& fname, FragmentLibrary& lib);
        int  saveFragmentLibrary();

        std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);
        std::size_t doReadNextMolecule(CDPL::Chem::Molecule& mol);

        void updateOccurrenceCount(std::uint64_t hash_code);

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

        void printStatistics(std::size_t num_proc_mols, std::size_t num_proc_frags, std::size_t num_error_frags,
                             std::size_t num_added_frags, std::size_t num_gen_confs);

        void checkInputFiles() const;
        void printOptionSummary();
        void initInputReader();

        std::string getModeString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        InputHandlerPtr getInputHandler(const std::string& file_path) const;

        void addOptionLongDescriptions();

        class InputScanProgressCallback;
        class FragLibGenerationWorker;

        typedef std::vector<std::string>                             StringList;
        typedef std::unordered_map<std::uint64_t, std::size_t>       FragmentFrequencyMap;
        typedef CDPL::Base::DataReader<CDPL::Chem::Molecule>         MoleculeReader;
        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Internal::Timer                                Timer;
        typedef CDPL::ConfGen::FragmentConformerGeneratorSettings    ConformerGeneratorSettings;

        StringList                     inputFiles;
        std::string                    outputFile;
        std::size_t                    numThreads;
        Mode                           mode;
        ConformerGeneratorSettings     settings;
        std::string                    preset;
        std::size_t                    maxLibSize;
        InputHandlerPtr                inputHandler;
        CompMoleculeReader             inputReader;
        FragmentLibrary::SharedPointer fragmentLibPtr;
        FragmentFrequencyMap           fragmentOccCounts;
        std::mutex                     mutex;
        std::mutex                     molReadMutex;
        std::string                    errorMessage;
        Timer                          timer;
    };
} // namespace GenFragLib

#endif // GENFRAGLIB_GENFRAGLIBIMPL_HPP
