/* 
 * SubSearchImpl.hpp
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


#ifndef SUBSEARCH_SUBSEARCHIMPL_HPP
#define SUBSEARCH_SUBSEARCHIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>

#include "CDPL/Util/CompoundDataReader.hpp"
#include "CDPL/Chem/MolecularGraphWriter.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace SubSearch
{

    class SubSearchImpl : public CmdLineLib::CmdLineBase
    {

      public:
        SubSearchImpl();

      private:
        typedef std::vector<std::string> StringList;

        const char* getProgName() const;
        const char* getProgAboutText() const;

        void setInputFormat(const std::string& file_ext);
        void setOutputFormat(const std::string& file_ext);
        
        int process();
        void findMatches();

        std::size_t readNextMolecule(CDPL::Chem::Molecule& mol);

        void writeMolecule(const CDPL::Chem::MolecularGraph& mol);

        void setErrorMessage(const std::string& msg);
        bool haveErrorMessage();

        void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

        void printStatistics();

        void checkInputFiles() const;
        void checkMatchExpression() const;

        void parseSubstructPatterns();
        
        void printOptionSummary();
        void initInputReader();
        void initOutputWriter();

        std::string createMoleculeIdentifier(std::size_t rec_idx, const std::string& mol_name);
        std::string createMoleculeIdentifier(std::size_t rec_idx);

        void addOptionLongDescriptions();

        class InputScanProgressCallback;
        class SubSearchWorker;

        typedef std::vector<CDPL::Chem::Molecule::SharedPointer>     MoleculeList;
        typedef CDPL::Util::CompoundDataReader<CDPL::Chem::Molecule> CompMoleculeReader;
        typedef CDPL::Chem::MolecularGraphWriter::SharedPointer      MoleculeWriterPtr;
        typedef CDPL::Internal::Timer                                Timer;

        StringList         inputFiles;
        std::string        outputFile;
        StringList         substrSMARTSPatterns;
        MoleculeList       substrPatterns;
        std::string        matchExpression;
        std::string        inputFormat;
        std::string        outputFormat;
        CompMoleculeReader inputReader;
        MoleculeWriterPtr  outputWriter;
        std::string        errorMessage;
        Timer              timer;
        std::size_t        numProcMols;
        std::size_t        numMatches;
    };
} // namespace SubSearch

#endif // SUBSEARCH_SUBSEARCHIMPL_HPP
