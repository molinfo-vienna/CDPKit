/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PMLPharmacophoreReader.cpp 
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

#include <boost/lexical_cast.hpp>

#include "CDPL/Pharm/PMLPharmacophoreReader.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "PMLDataReader.hpp"


using namespace CDPL;


Pharm::PMLPharmacophoreReader::PMLPharmacophoreReader(std::istream& is): 
	Util::StreamDataReader<Pharmacophore, PMLPharmacophoreReader>(is), reader(new PMLDataReader(*this)) {}

Pharm::PMLPharmacophoreReader::~PMLPharmacophoreReader() {}

bool Pharm::PMLPharmacophoreReader::readData(std::istream& is, Pharmacophore& pharm, bool overwrite)
{
	try {
		if (overwrite)
			pharm.clear();

		return reader->readPharmacophore(is, pharm);

	} catch (const std::exception& e) {
		throw Base::IOError("PMLPharmacophoreReader: while reading record " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Pharm::PMLPharmacophoreReader::skipData(std::istream& is)
{
	try {
		return reader->skipPharmacophore(is);

	} catch (const std::exception& e) {
		throw Base::IOError("PMLPharmacophoreReader: while skipping record " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Pharm::PMLPharmacophoreReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
