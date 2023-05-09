/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDPharmacophoreReader.cpp 
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


#include "StaticInit.hpp"

#include <fstream>

#include <boost/lexical_cast.hpp>
#include <boost/iostreams/copy.hpp>

#include "CDPL/Pharm/PSDPharmacophoreReader.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Util/FileRemover.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Pharm::PSDPharmacophoreReader::PSDPharmacophoreReader(std::istream& is): 
	recordIndex(0), state(false)
{
	Util::FileRemover tmp_file_rem(Util::genCheckedTempFilePath());

	try {
		std::ofstream tmp_fs(tmp_file_rem.getPath().c_str());

		boost::iostreams::copy(is, tmp_fs);

		if (!is.good() || !tmp_fs.good())
			throw Base::IOError("copying input data failed");

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDPharmacophoreReader: could not create temporary database file: ") + e.what());
	}

	try {
		accessor.open(tmp_file_rem.getPath());

		numRecords = accessor.getNumPharmacophores();
		state = true;

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDPharmacophoreReader: could not open database: ") + e.what());
	}
}

Pharm::PSDPharmacophoreReader::PSDPharmacophoreReader(const std::string& file_name):
	recordIndex(0), state(false)
{
	try {
		accessor.open(file_name);

		numRecords = accessor.getNumPharmacophores();
		state = true;

	} catch (const std::exception& e) {
		throw Base::IOError(std::string("PSDPharmacophoreReader: could not open database: ") + e.what());
	}
}

Pharm::PSDPharmacophoreReader::~PSDPharmacophoreReader() 
{
	try { accessor.close(); } catch (...) {}
}

Pharm::PSDPharmacophoreReader& Pharm::PSDPharmacophoreReader::read(Pharmacophore& pharm, bool overwrite)
{
	state = false;

	if (recordIndex >= numRecords)
		return *this;

	try {
		accessor.getPharmacophore(recordIndex, pharm, overwrite);

	} catch (const std::exception& e) {
		throw Base::IOError("PSDPharmacophoreReader: while reading record " + boost::lexical_cast<std::string>(recordIndex) + 
							": " + e.what());
	}

	recordIndex++;
	state = true;

	invokeIOCallbacks(1.0);

    return *this;
}

Pharm::PSDPharmacophoreReader& Pharm::PSDPharmacophoreReader::read(std::size_t idx, Pharmacophore& pharm, bool overwrite)
{
	setRecordIndex(idx);

	return read(pharm, overwrite);
}

Pharm::PSDPharmacophoreReader& Pharm::PSDPharmacophoreReader::skip()
{
 	state = false;

	if (recordIndex >= numRecords)
		return *this;

	recordIndex++;
	state = true;

	invokeIOCallbacks(1.0);

	return *this;
}

bool Pharm::PSDPharmacophoreReader::hasMoreData()
{
	return (recordIndex < numRecords);
}

std::size_t Pharm::PSDPharmacophoreReader::getRecordIndex() const
{
    return recordIndex;
}

void Pharm::PSDPharmacophoreReader::setRecordIndex(std::size_t idx)
{
	if (idx >= numRecords)
		throw Base::IndexError("StreamDataReader: record index out of bounds");

	recordIndex = idx;
}

std::size_t Pharm::PSDPharmacophoreReader::getNumRecords()
{
	invokeIOCallbacks(1.0);
    return numRecords;
}

Pharm::PSDPharmacophoreReader::operator const void*() const
{
    return (state ? this : 0);
}

bool Pharm::PSDPharmacophoreReader::operator!() const
{
    return !state;
}
