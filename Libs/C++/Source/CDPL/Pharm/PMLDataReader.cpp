/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PMLDataReader.cpp 
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

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "PMLDataReader.hpp"
#include "PMLFormatData.hpp"


using namespace CDPL;


namespace
{

	const std::string PHARMACOPHORE_START_TAG = '<' + Pharm::PML::PHARMACOPHORE_TAG;
	const std::string PHARMACOPHORE_END_TAG   = "</" + Pharm::PML::PHARMACOPHORE_TAG + '>';
}


Pharm::PMLDataReader::PMLDataReader(const Base::DataIOBase& io_base): 
	ioBase(io_base), strictErrorChecking(true) 
{}

bool Pharm::PMLDataReader::hasMoreData(std::istream& is)
{
	return Internal::skipToString(is, PHARMACOPHORE_START_TAG, "PMLDataReader:", false);
}

bool Pharm::PMLDataReader::readPharmacophore(std::istream& is, Pharmacophore& pharm)
{
	init();

	if (!Internal::skipToString(is, PHARMACOPHORE_START_TAG, "PMLDataReader:", false))
		return false;

	pharmData.clear();

	if (!Internal::readToString(is, PHARMACOPHORE_END_TAG, pharmData, "PMLDataReader:", true)) {
		if (strictErrorChecking)
			throw Base::IOError("PMLDataReader: error while reading pharmacophore, no closing pharmacophore tag found");

		return false;
	}

	try {
		pharmDocument.parse<0>(&pharmData[0]);

	} catch (const rapidxml::parse_error& e) {
		throw Base::IOError(std::string("PMLDataReader: ") + e.what());
	}

	return true;
}

bool Pharm::PMLDataReader::skipPharmacophore(std::istream& is)
{
	init();

	if (!Internal::skipToString(is, PHARMACOPHORE_START_TAG, "PMLDataReader:", false))
		return false;

	if (!Internal::skipToString(is, PHARMACOPHORE_END_TAG, "PMLDataReader:", true)) {
		if (strictErrorChecking)
			throw Base::IOError("PMLDataReader: error while skipping input pharmacophore, no closing pharmacophore tag found");

		return false;
	}

	return true;
}

void Pharm::PMLDataReader::init()
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
}
