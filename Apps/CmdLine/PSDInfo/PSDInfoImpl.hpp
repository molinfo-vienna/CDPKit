/* 
 * PSDInfoImpl.hpp
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


#ifndef PSDINFO_PSDINFOIMPL_HPP
#define PSDINFO_PSDINFOIMPL_HPP

#include <vector>
#include <string>
#include <iosfwd>

#include "CmdLine/Lib/CmdLineBase.hpp"


namespace PSDInfo
{

    class PSDInfoImpl : public CmdLineLib::CmdLineBase
    {

    public:
		PSDInfoImpl();

    private:
		const char* getProgName() const;
		const char* getProgCopyright() const;
		const char* getProgAboutText() const;

		int process();

		int printStatistics();
		void printStatistics(const std::string& db_name);
	
		void checkInputFiles() const;
		void printOptionSummary();

		void printTableRow(std::ostream& os, const std::string& stat_type, 
						   std::size_t min, double avg, std::size_t max) const;

		typedef std::vector<std::string> StringList;

		StringList  inputDatabases;
		bool        printConfStats;
		bool        printPharmStats;
		bool        printFeatureStats;
    };
}

#endif // PSDINFO_PSDINFOIMPL_HPP
