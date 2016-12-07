/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDMoleculeReader.cpp 
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


#include "StaticInit.hpp"

#include <fstream>

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>

#include "CDPL/Pharm/PSDMoleculeReader.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Pharm::PSDMoleculeReader::PSDMoleculeReader(std::istream& is): 
	recordIndex(0), state(false)
{
	try {
		boost::filesystem::path tmp_file = boost::filesystem::temp_directory_path() / boost::filesystem::unique_path();
		tmpFile = tmp_file.native();

		std::ofstream tmp_fs(tmpFile.c_str());

		boost::iostreams::copy(is, tmp_fs);

		if (!is.good() || !tmp_fs.good())
			throw Base::IOError("copying input data failed");

	} catch (const std::exception& e) {
		removeTmpFile();
		throw Base::IOError(std::string("PSDMoleculeReader: could not create temporary database file: ") + e.what());
	}

	try {
		accessor.open(tmpFile);

		numRecords = accessor.getNumMolecules();
		state = true;

	} catch (const std::exception& e) {
		removeTmpFile();
		throw Base::IOError(std::string("PSDMoleculeReader: could not open database: ") + e.what());
	}
}

Pharm::PSDMoleculeReader::PSDMoleculeReader(const std::string& file_name):
	recordIndex(0), state(false)
{
	try {
		accessor.open(file_name);

		numRecords = accessor.getNumMolecules();
		state = true;

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDMoleculeReader: could not open database: ") + e.what());
	}
}

Pharm::PSDMoleculeReader::~PSDMoleculeReader() 
{
	try { accessor.close(); } catch (...) {}
	removeTmpFile();
}

Pharm::PSDMoleculeReader& Pharm::PSDMoleculeReader::read(Chem::Molecule& mol)
{
	state = false;

	if (recordIndex >= numRecords)
		return *this;

	try {
		accessor.getMolecule(recordIndex, mol);

	} catch (const std::exception& e) {
		throw Base::IOError("PSDMoleculeReader: while reading record " + boost::lexical_cast<std::string>(recordIndex) + 
							": " + e.what());
	}

	recordIndex++;
	state = true;

	invokeIOCallbacks(1.0);

    return *this;
}

Pharm::PSDMoleculeReader& Pharm::PSDMoleculeReader::read(std::size_t idx, Chem::Molecule& mol)
{
	setRecordIndex(idx);

	return read(mol);
}

Pharm::PSDMoleculeReader& Pharm::PSDMoleculeReader::skip()
{
 	state = false;

	if (recordIndex >= numRecords)
		return *this;

	recordIndex++;
	state = true;

	invokeIOCallbacks(1.0);

	return *this;
}

bool Pharm::PSDMoleculeReader::hasMoreData()
{
	return (recordIndex < numRecords);
}

std::size_t Pharm::PSDMoleculeReader::getRecordIndex() const
{
    return recordIndex;
}

void Pharm::PSDMoleculeReader::setRecordIndex(std::size_t idx)
{
	if (idx >= numRecords)
		throw Base::IndexError("StreamDataReader: record index out of bounds");

	recordIndex = idx;
}

std::size_t Pharm::PSDMoleculeReader::getNumRecords()
{
    return numRecords;
}

Pharm::PSDMoleculeReader::operator const void*() const
{
    return (state ? this : 0);
}

bool Pharm::PSDMoleculeReader::operator!() const
{
    return !state;
}

void Pharm::PSDMoleculeReader::removeTmpFile()
{
	try {
		if (!tmpFile.empty())
			boost::filesystem::remove(tmpFile);
	} catch (...) {}
}
