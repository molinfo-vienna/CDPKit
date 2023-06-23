/* 
 * PSDMergeImpl.hpp
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


#ifndef PSDMERGE_PSDMERGEIMPL_HPP
#define PSDMERGE_PSDMERGEIMPL_HPP

#include <cstddef>
#include <vector>
#include <string>

#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Internal/Timer.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace PSDMerge
{

    class PSDMergeImpl : public CmdLineLib::CmdLineBase
    {

    public:
        PSDMergeImpl();

    private:
        const char* getProgName() const;
        const char* getProgCopyright() const;
        const char* getProgAboutText() const;

        void setCreationMode(const std::string& mode);
    
        int process();
        int mergeDatabases();
    
        void checkInputFiles() const;
        void printOptionSummary();
        
        void printStatistics(std::size_t num_proc, std::size_t num_rej, std::size_t num_del,
                             std::size_t num_ins);

        std::string getModeString() const;

        struct MergeDBsProgressCallback;

        typedef std::vector<std::string> StringList;
        typedef CDPL::Pharm::ScreeningDBCreator::Mode CreationMode;
        typedef CDPL::Internal::Timer Timer;

        StringList         inputDatabases;
        std::string        outputDatabase;
        bool               dropDuplicates;
        CreationMode       creationMode;
        Timer              timer;
    };
}

#endif // PSDMERGE_PSDMERGEIMPL_HPP
