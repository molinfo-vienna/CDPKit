/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * OptimolLogReader.cpp
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


#include <sstream>

#include "CDPL/Internal/StringDataIOUtilities.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "OptimolLogReader.hpp"


using namespace CDPL;
using namespace TestUtils;


OptimolLogReader::OptimolLogReader(const std::string& log_file): logIStream(log_file.c_str()) 
{
    buildIndex();
}

bool OptimolLogReader::getSymbolicAtomTypes(const std::string& mol_name, SymbolicAtomTypeArray& sym_types)
{
    if (!seekToRecord(mol_name))
		return false;

    std::string line;

    if (!skipToLine(line, "ATOM NAME SYMBOL"))
		return false;

    sym_types.clear();

    std::string atom_name;
    std::string atom_type;
	std::string atom_idx;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!(iss >> atom_name))
				break;
	    
			if (!(iss >> atom_idx))
				break;
	    
			if (!(iss >> atom_type))
				break;
	    
			sym_types.push_back(atom_type);
		}
    }

    return !sym_types.empty();
}

bool OptimolLogReader::getNumericAtomTypes(const std::string& mol_name, NumericAtomTypeArray& num_types)
{
    if (!seekToRecord(mol_name))
		return false;

    std::string line;

    if (!skipToLine(line, "ATOM NAME  TYPE"))
		return false;

    num_types.clear();

    std::string atom_name;
	std::string atom_idx;
    unsigned int atom_type;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!(iss >> atom_name))
				break;
	    
			if (!(iss >> atom_idx))
				break;
	    
			if (!(iss >> atom_type))
				break;
	    
			num_types.push_back(atom_type);
		}
    }

    return !num_types.empty();
}

void OptimolLogReader::buildIndex()
{
    std::string line;

    while (skipToLine(line, "Structure Name")) {
		std::string::size_type colon_idx = line.find(':');
	
		if (colon_idx == std::string::npos)
			continue;

		std::string mol_name = line.substr(colon_idx + 1, std::string::npos);

		Internal::trimString(mol_name);
	
		recordOffsets.insert(RecordFileOffsetMap::value_type(mol_name, logIStream.tellg()));
    }
}

bool OptimolLogReader::skipToLine(std::string& line, const char* srch_str)
{
    while (readLine(line)) {
		if (line.find(srch_str) != std::string::npos)
			return true;
    }

    return false;
}

bool OptimolLogReader::readLine(std::string& line)
{
    if (!std::istream::sentry(logIStream, false))
		return false;

    line.clear();

    Internal::readLine(logIStream, line, "Error while reading MMFF94 log-file", true);

    return true;
}

bool OptimolLogReader::seekToRecord(const std::string& mol_name)
{
    RecordFileOffsetMap::const_iterator it = recordOffsets.find(mol_name);

    if (it == recordOffsets.end())
		return false;

    logIStream.clear();
    logIStream.seekg(it->second);

    return true;
}
