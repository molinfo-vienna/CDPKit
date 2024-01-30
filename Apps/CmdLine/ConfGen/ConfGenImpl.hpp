/* 
 * ConfGenImpl.hpp
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


#ifndef CONFGEN_CONFGENIMPL_HPP
#define CONFGEN_CONFGENIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>
#include <mutex>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Chem/MolecularGraphWriter.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
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
    } // namespace Chem
} // namespace CDPL


namespace ConfGen
{

    class ConfGenImpl : public CmdLineLib::CmdLineBase
    {

      public:
        ConfGenImpl();

      private:
        typedef std::vector<std::string> StringList;

        const char* getProgName() const;
        const char* getProgAboutText() const;

        void applyConfGenPreset(const std::string& pres_str);
        void applyFragBuildPreset(const std::string& pres_str);
        void setSamplingMode(const std::string& mode_str);
        void setTimeout(std::size_t timeout);
        void setDielectricConst(double de_const);
        void setDistExponent(double exp);
        void setMaxNumSampledConfs(std::size_t max_confs);
        void setConvergenceCheckCycleSize(std::size_t size);
        void setMacrocycleRotorBondCountThreshold(std::size_t min_count);
        void setRefTolerance(double tol);
        void setMaxNumRefIterations(std::size_t num_iter);
        void setStrictParameterization(bool strict);
        void setSystematicSearchForceFieldType(const std::string& type_str);
        void setStochasticSearchForceFieldType(const std::string& type_str);
        void setBuildForceFieldType(const std::string& type_str);
        void setRMSD(const StringList& args);
        void setEnergyWindow(const StringList& args);
        void setNitrogenEnumMode(const std::string& mode_str);
        void setEnumRings(bool enumerate);
        void setSampleHetAtomHydrogens(bool sample);
        void setSampleAngleTolRanges(bool sample);
        void setIncludeInput(bool include);
        void setGenerateFromScratch(bool from_scratch);
        void setMaxNumConfs(const StringList& args);
        void setMaxPoolSize(std::size_t max_confs);
        void setMaxRotBondCount(long max_count);
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

        void printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols, std::size_t num_gen_confs);

        void checkInputFiles() const;
        void procFixedSubstructData();
        void printOptionSummary();
        void loadTorsionLibrary();
        void loadFragmentLibrary();
        void initInputReader();
        void initOutputWriters();

        std::string getSamplingModeString() const;
        std::string getNitrogenEnumModeString() const;

        std::string createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        void addOptionLongDescriptions();

        template <typename T>
        static std::string toString(const StringList& list, const T& def_val);
        
        class InputScanProgressCallback;
        class ConformerGenerationWorker;

        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Chem::MolecularGraphWriter::SharedPointer      MoleculeWriterPtr;
        typedef CDPL::Chem::Molecule::SharedPointer                  MoleculePtr;
        typedef CDPL::Internal::Timer                                Timer;
        typedef CDPL::ConfGen::ConformerGeneratorSettings            ConformerGeneratorSettings;
        typedef CDPL::ConfGen::FragmentConformerGeneratorSettings    FragmentConformerGeneratorSettings;
        typedef CDPL::ConfGen::TorsionLibrary::SharedPointer         TorsionLibraryPtr;
        typedef CDPL::ConfGen::FragmentLibrary::SharedPointer        FragmentLibraryPtr;

        StringList                 inputFiles;
        std::string                outputFile;
        std::string                failedFile;
        std::size_t                numThreads;
        ConformerGeneratorSettings settings;
        StringList                 maxNumConfsOptArgs;
        StringList                 minRMSDOptArgs;
        StringList                 eWindowOptArgs;
        std::string                confGenPreset;
        std::string                fragBuildPreset;
        bool                       canonicalize;
        bool                       energySDEntry;
        bool                       energyComment;
        bool                       confIndexSuffix;
        std::string                torsionLibName;
        TorsionLibraryPtr          torsionLib;
        bool                       replaceBuiltinTorLib;
        std::string                fragmentLibName;
        FragmentLibraryPtr         fragmentLib;
        bool                       replaceBuiltinFragLib;
        std::string                fixedSubstructFile;
        std::string                fixedSubstructPtn;
        bool                       fixedSubstructUseMCSS;
        bool                       fixedSubstructAlign;
        bool                       fixedSubstructDelH;
        std::size_t                fixedSubstructMCSSMinNumAtoms;
        std::size_t                fixedSubstructMaxNumMatches;
        MoleculePtr                fixedSubstruct;
        bool                       haveFixedSubstruct3DCoords;
        std::string                inputFormat;
        CompMoleculeReader         inputReader;
        std::string                outputFormat;
        MoleculeWriterPtr          outputWriter;
        std::string                failedOutputFormat;
        MoleculeWriterPtr          failedOutputWriter;
        std::mutex                 mutex;
        std::mutex                 readMolMutex;
        std::mutex                 writeMolMutex;
        std::string                errorMessage;
        Timer                      timer;
    };
} // namespace ConfGen

#endif // CONFGEN_CONFGENIMPL_HPP
