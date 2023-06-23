/* 
 * CDFPharmacophoreDataWriter.cpp 
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

#include <ostream>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"

#include "CDFPharmacophoreDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Pharm::CDFPharmacophoreDataWriter::writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr)
{
    writeFeatureContainer(cntnr, dataBuffer);

    return writeRecordData(os);
}

void Pharm::CDFPharmacophoreDataWriter::writeFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf)
{
    init();

    bbuf.setIOPointer(CDF::HEADER_SIZE);

    outputFeatures(cntnr, bbuf);
    outputFtrContainerProperties(cntnr, bbuf);

    bbuf.resize(bbuf.getIOPointer());

    outputFtrContainerHeader(cntnr, bbuf);
}

void Pharm::CDFPharmacophoreDataWriter::init()
{
    strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
    singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ctrlParams));
}

void Pharm::CDFPharmacophoreDataWriter::outputFtrContainerHeader(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
    CDF::Header cdf_header;

    cdf_header.recordDataLength = boost::numeric_cast<std::uint64_t>(bbuf.getSize() - CDF::HEADER_SIZE);
    cdf_header.recordTypeID = CDF::PHARMACOPHORE_RECORD_ID;
    cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

    bbuf.setIOPointer(0);

    putHeader(cdf_header, bbuf);
}

void Pharm::CDFPharmacophoreDataWriter::outputFeatures(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
    bbuf.putInt(boost::numeric_cast<CDF::SizeType>(cntnr.getNumFeatures()), false);

    for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); 
         it != end; ++it) {

        const Feature& feature = *it;
    
        if (hasType(feature))
            putIntProperty(CDF::FeatureProperty::TYPE, boost::numeric_cast<CDF::UIntType>(getType(feature)), bbuf);

        if (has3DCoordinates(feature))
            putCVectorProperty(CDF::FeatureProperty::COORDINATES_3D, get3DCoordinates(feature), bbuf);

        if (hasOrientation(feature))
            putCVectorProperty(CDF::FeatureProperty::ORIENTATION, getOrientation(feature), bbuf);

        if (hasGeometry(feature))
            putIntProperty(CDF::FeatureProperty::GEOMETRY, boost::numeric_cast<CDF::UIntType>(getGeometry(feature)), bbuf);

        if (hasLength(feature))
            putFloatProperty(CDF::FeatureProperty::LENGTH, getLength(feature), bbuf);

        if (hasTolerance(feature))
            putFloatProperty(CDF::FeatureProperty::TOLERANCE, getTolerance(feature), bbuf);

        if (hasWeight(feature))
            putFloatProperty(CDF::FeatureProperty::WEIGHT, getWeight(feature), bbuf);

        if (hasDisabledFlag(feature))
            putIntProperty(CDF::FeatureProperty::DISABLED_FLAG, CDF::BoolType(getDisabledFlag(feature)), bbuf);

        if (hasOptionalFlag(feature))
            putIntProperty(CDF::FeatureProperty::OPTIONAL_FLAG, CDF::BoolType(getOptionalFlag(feature)), bbuf);

        if (hasHydrophobicity(feature))
            putFloatProperty(CDF::FeatureProperty::HYDROPHOBICITY, getHydrophobicity(feature), bbuf);

        putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
    }
}

void Pharm::CDFPharmacophoreDataWriter::outputFtrContainerProperties(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
    if (hasName(cntnr))
        putStringProperty(CDF::PharmacophoreProperty::NAME, getName(cntnr), bbuf);

    putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
}

bool Pharm::CDFPharmacophoreDataWriter::writeRecordData(std::ostream& os) const
{
    dataBuffer.writeBuffer(os);

    return os.good();
}
