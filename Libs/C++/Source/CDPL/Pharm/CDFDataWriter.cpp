/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriter.cpp 
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

#include <ostream>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "CDFDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Pharm::CDFDataWriter::writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr)
{
	writeFeatureContainer(cntnr, dataBuffer);

	return writeRecordData(os);
}

void Pharm::CDFDataWriter::writeFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(CDF::HEADER_SIZE);

	outputFeatures(cntnr, bbuf);
	outputFtrContainerProperties(cntnr, bbuf);

	bbuf.resize(bbuf.getIOPointer());

	outputFtrContainerHeader(cntnr, bbuf);
}

void Pharm::CDFDataWriter::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
	singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ctrlParams));
}

void Pharm::CDFDataWriter::outputFtrContainerHeader(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
	CDF::Header cdf_header;

	cdf_header.recordDataLength = boost::numeric_cast<CDF::SizeType>(bbuf.getSize() - CDF::HEADER_SIZE);
	cdf_header.recordTypeID = CDF::PHARMACOPHORE_RECORD_ID;
	cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	bbuf.setIOPointer(0);

	putHeader(cdf_header, bbuf);
}

void Pharm::CDFDataWriter::outputFeatures(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(cntnr.getNumFeatures()), false);

	for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); 
		 it != end; ++it) {

		const Feature& feature = *it;
	
		if (hasType(feature))
			putIntProperty(CDF::FeatureProperty::TYPE, boost::numeric_cast<CDF::UIntType>(getType(feature)), bbuf);

		if (has3DCoordinates(feature))
			putVectorProperty(CDF::FeatureProperty::COORDINATES_3D, get3DCoordinates(feature), bbuf);

		if (hasOrientation(feature))
			putVectorProperty(CDF::FeatureProperty::ORIENTATION, getOrientation(feature), bbuf);

		if (hasGeometry(feature))
			putIntProperty(CDF::FeatureProperty::GEOMETRY, boost::numeric_cast<CDF::UIntType>(getGeometry(feature)), bbuf);

		if (hasLength(feature))
			putFloatProperty(CDF::FeatureProperty::LENGTH, getLength(feature), bbuf);

		if (hasTolerance(feature))
			putFloatProperty(CDF::FeatureProperty::TOLERANCE, getTolerance(feature), bbuf);

		if (hasDisabledFlag(feature))
			putIntProperty(CDF::FeatureProperty::DISABLED_FLAG, CDF::BoolType(getDisabledFlag(feature)), bbuf);

		if (hasOptionalFlag(feature))
			putIntProperty(CDF::FeatureProperty::OPTIONAL_FLAG, CDF::BoolType(getOptionalFlag(feature)), bbuf);

		putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
	}
}

void Pharm::CDFDataWriter::outputFtrContainerProperties(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
	if (hasName(cntnr))
		putStringProperty(CDF::PharmacophoreProperty::NAME, getName(cntnr), bbuf);

	putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
}

bool Pharm::CDFDataWriter::writeRecordData(std::ostream& os) const
{
	dataBuffer.writeBuffer(os);

	return os.good();
}
