/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReader.cpp 
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
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Math/Vector.hpp"

#include "CDFDataReader.hpp"


using namespace CDPL;


bool Pharm::CDFDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::PHARMACOPHORE_RECORD_ID, true);
}

bool Pharm::CDFDataReader::readPharmacophore(std::istream& is, Pharmacophore& pharm)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::PHARMACOPHORE_RECORD_ID, false))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

	CDF::SizeType num_ftrs;

	dataBuffer.getInt(num_ftrs);

	startFeatureIdx = pharm.getNumFeatures();

	readFeatures(pharm, num_ftrs);
	readPharmProperties(pharm);

	return true;
}

bool Pharm::CDFDataReader::skipPharmacophore(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::PHARMACOPHORE_RECORD_ID);
}

void Pharm::CDFDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ioBase)); 
}

void Pharm::CDFDataReader::readFeatures(Pharmacophore& pharm, std::size_t num_ftrs)
{
	CDF::PropertySpec prop_spec;
	CDF::UIntType uint_val;
	CDF::LongType long_val;
	CDF::SizeType size_val;
	CDF::BoolType bool_val;
	std::string str_val;
	Math::Vector3D coords_3d_val;

	for (std::size_t i = 0; i < num_ftrs; i++) {
		Feature& feature = pharm.addFeature();

		while (true) {
			dataBuffer.getInt(prop_spec);

			if (prop_spec == CDF::PROP_LIST_END)
				break;

			switch (extractPropertyID(prop_spec)) {

				default:
					throw Base::IOError("CDFDataReader: unsupported feature property");
			}
		}
	}
}

void Pharm::CDFDataReader::readPharmProperties(Pharmacophore& pharm)
{
	CDF::PropertySpec prop_spec;
	CDF::SizeType size_val;
	std::string str_val;
	double double_val;

	while (true) {
		dataBuffer.getInt(prop_spec);

		if (prop_spec == CDF::PROP_LIST_END)
			break;

		switch (extractPropertyID(prop_spec)) {
	
			default:
				throw Base::IOError("CDFDataReader: unsupported pharmacophore property");
		}
	}
}
