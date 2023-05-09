/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFPharmacophoreDataReader.cpp 
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

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Math/Vector.hpp"

#include "CDFPharmacophoreDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Pharm::CDFPharmacophoreDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::PHARMACOPHORE_RECORD_ID, true, dataBuffer);
}

bool Pharm::CDFPharmacophoreDataReader::readPharmacophore(std::istream& is, Pharmacophore& pharm)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::PHARMACOPHORE_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

    readFeatures(pharm, dataBuffer);
	readPharmProperties(pharm, dataBuffer);

	return true;
}

bool Pharm::CDFPharmacophoreDataReader::skipPharmacophore(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::PHARMACOPHORE_RECORD_ID, dataBuffer);
}

void Pharm::CDFPharmacophoreDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
}

bool Pharm::CDFPharmacophoreDataReader::readPharmacophore(Pharmacophore& pharm, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::PHARMACOPHORE_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFPharmacophoreDataReader: trying to read a non-pharmacophore record");

		return false;
	}

	readFeatures(pharm, bbuf);
	readPharmProperties(pharm, bbuf);

	return true;
}

void Pharm::CDFPharmacophoreDataReader::readFeatures(Pharmacophore& pharm, Internal::ByteBuffer& bbuf) const
{
	CDF::PropertySpec prop_spec;
	CDF::UIntType uint_val;
	CDF::BoolType bool_val;
	std::string str_val;
	double double_val;
	Math::Vector3D coords_3d_val;
	CDF::SizeType num_ftrs;

	bbuf.getInt(num_ftrs);

	for (std::size_t i = 0; i < num_ftrs; i++) {
		Feature& feature = pharm.addFeature();

		while (true) {
			unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

			if (prop_id == CDF::PROP_LIST_END)
				break;

			switch (prop_id) {

				case CDF::FeatureProperty::TYPE:
					getIntProperty(prop_spec, uint_val, bbuf);
					setType(feature, uint_val);
					continue;

				case CDF::FeatureProperty::COORDINATES_3D:
					getCVectorProperty(prop_spec, coords_3d_val, bbuf);
					set3DCoordinates(feature, coords_3d_val);
					continue;

				case CDF::FeatureProperty::GEOMETRY:
					getIntProperty(prop_spec, uint_val, bbuf);
					setGeometry(feature, uint_val);
					continue;

				case CDF::FeatureProperty::LENGTH:
					getFloatProperty(prop_spec, double_val, bbuf);
					setLength(feature, double_val);
					continue;

				case CDF::FeatureProperty::ORIENTATION:
					getCVectorProperty(prop_spec, coords_3d_val, bbuf);
					setOrientation(feature, coords_3d_val);
					continue;

				case CDF::FeatureProperty::TOLERANCE:
					getFloatProperty(prop_spec, double_val, bbuf);
					setTolerance(feature, double_val);
					continue;
	
				case CDF::FeatureProperty::WEIGHT:
					getFloatProperty(prop_spec, double_val, bbuf);
					setWeight(feature, double_val);
					continue;

				case CDF::FeatureProperty::DISABLED_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setDisabledFlag(feature, bool_val);
					continue;

				case CDF::FeatureProperty::OPTIONAL_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setOptionalFlag(feature, bool_val);
					continue;

				case CDF::FeatureProperty::HYDROPHOBICITY:
					getFloatProperty(prop_spec, double_val, bbuf);
					setHydrophobicity(feature, double_val);
					continue;

				default:
					throw Base::IOError("CDFPharmacophoreDataReader: unsupported feature property");
			}
		}
	}
}

void Pharm::CDFPharmacophoreDataReader::readPharmProperties(Pharmacophore& pharm, Internal::ByteBuffer& bbuf) const
{
	CDF::PropertySpec prop_spec;
	std::string str_val;

	while (true) {
		unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

		if (prop_id == CDF::PROP_LIST_END)
			break;

		switch (prop_id) {

			case CDF::PharmacophoreProperty::NAME:
				getStringProperty(prop_spec, str_val, bbuf);
				setName(pharm, str_val);
				continue;

			default:
				throw Base::IOError("CDFPharmacophoreDataReader: unsupported pharmacophore property");
		}
	}
}
