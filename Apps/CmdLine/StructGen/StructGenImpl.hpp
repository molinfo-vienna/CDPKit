/* 
 * StructGenImpl.hpp
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


#ifndef STRUCTGEN_STRUCTGENIMPL_HPP
#define STRUCTGEN_STRUCTGENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <mutex>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/ConfGen/StructureGeneratorSettings.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
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


namespace StructGen
{

    class StructGenImpl : public CmdLineLib::CmdLineBase
    {

    public:
        StructGenImpl();

    private:
        typedef CDPL::Base::DataOutputHandler<CDPL::Chem::MolecularGraph> OutputHandler;
        typedef CDPL::Base::DataInputHandler<CDPL::Chem::Molecule> InputHandler;
        typedef InputHandler::SharedPointer InputHandlerPtr;
        typedef OutputHandler::SharedPointer OutputHandlerPtr;

        const char* getProgName() const;
        const char* getProgCopyright() const;
        const char* getProgAboutText() const;

        void applyFragBuildPreset(const std::string& pres_str);
        void setGenerationMode(const std::string& mode_str);
        void setTimeout(std::size_t timeout);
        void setDielectricConst(double de_const);
        void setDistExponent(double exp);
        void setConvergenceIterCount(std::size_t iter_count);
        void setMacrocycleRotorBondCountThreshold(std::size_t min_count);
        void setRefTolerance(double tol);
        void setMaxNumRefIterations(std::size_t num_iter);
        void setStrictParameterization(bool strict);
        void setFragBasedForceFieldType(const std::string& type_str);
        void setDGBasedForceFieldType(const std::string& type_str);
        void setSampleAngleTolRanges(bool sample);
        void setGenerateFromScratch(bool from_scratch);
        void setInputFormat(const std::string& file_ext);
        void setOutputFormat(const std::string& file_ext);
        void setFailedOutputFormat(const std::string& file_ext);
        void addTorsionLib(const std::string& lib_file);
        void setTorsionLib(const std::string& lib_file);
        void addFragmentLib(const std::string& lib_file);
        void setFragmentLib(const std::string& lib_file);

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

        void printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols);

        void checkInputFiles() const;
        void printOptionSummary();
        void loadTorsionLibrary();
        void loadFragmentLibrary();
        void initInputReader();
        void initOutputWriters();

        std::string getGenerationModeString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        InputHandlerPtr getInputHandler(const std::string& file_path) const;
        OutputHandlerPtr getOutputHandler(const std::string& file_path) const;
        OutputHandlerPtr getFailedOutputHandler(const std::string& file_path) const;

        void addOptionLongDescriptions();

        class InputScanProgressCallback;
        class StructureGenerationWorker;

        typedef std::vector<std::string> StringList;
        typedef CDPL::Base::DataReader<CDPL::Chem::Molecule> MoleculeReader;
        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Base::DataWriter<CDPL::Chem::MolecularGraph>::SharedPointer MoleculeWriterPtr;
        typedef CDPL::Internal::Timer Timer;
        typedef CDPL::ConfGen::StructureGeneratorSettings StructureGeneratorSettings;
        typedef CDPL::ConfGen::FragmentConformerGeneratorSettings FragmentConformerGeneratorSettings;
        typedef CDPL::ConfGen::TorsionLibrary::SharedPointer TorsionLibraryPtr;
        typedef CDPL::ConfGen::FragmentLibrary::SharedPointer FragmentLibraryPtr;

        StringList                     inputFiles;
        std::string                    outputFile;
        std::string                    failedFile;
        std::size_t                    numThreads;
        StructureGeneratorSettings     settings;
        std::string                    fragBuildPreset;              
        bool                           canonicalize;
        bool                           hardTimeout;
        long                           maxNumRotorBonds;
        std::string                    torsionLibName;
        TorsionLibraryPtr              torsionLib;
        bool                           replaceBuiltinTorLib;
        std::string                    fragmentLibName;
        FragmentLibraryPtr             fragmentLib;
        bool                           replaceBuiltinFragLib;
        InputHandlerPtr                inputHandler;
        CompMoleculeReader             inputReader;
        OutputHandlerPtr               outputHandler;
        MoleculeWriterPtr              outputWriter;
        OutputHandlerPtr               failedOutputHandler;
        MoleculeWriterPtr              failedOutputWriter;
        std::mutex                     mutex;
        std::mutex                     readMolMutex;
        std::mutex                     writeMolMutex;
        std::string                    errorMessage;
        Timer                          timer;
    };
}

#endif // STRUCTUGEN_STRUCTUGENIMPL_HPP
