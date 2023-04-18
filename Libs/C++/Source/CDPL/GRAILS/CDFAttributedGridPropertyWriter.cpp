/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFAttributedGridPropertyWriter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/GRAILS/AttributedGridFunctions.hpp"
#include "CDPL/Grid/CDFDataWriter.hpp"

#include "CDFAttributedGridPropertyWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


void GRAILS::CDFAttributedGridPropertyWriter::registerExternalPropertyHandlers()
{
	Grid::CDFDataWriter::registerExternalPropertyHandler(&outputProperties);
}

unsigned int GRAILS::CDFAttributedGridPropertyWriter::outputProperties(const Grid::CDFDataWriter& writer, const Grid::AttributedGrid& grid, Internal::ByteBuffer& data) 
{
	if (hasFeatureType(grid))
		writer.putIntProperty(CDF::AttributedGridProperty::FEATURE_TYPE, boost::numeric_cast<CDF::UIntType>(getFeatureType(grid)), data);

	if (hasTargetFeatureType(grid))
		writer.putIntProperty(CDF::AttributedGridProperty::TARGET_FEATURE_TYPE, boost::numeric_cast<CDF::UIntType>(getTargetFeatureType(grid)), data);

	return CDF::AttributedGridProperty::PROPERTY_HANDLER_ID;
}
