/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFAttributedGridPropertyReader.cpp 
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

#include "CDPL/GRAIL/AttributedGridFunctions.hpp"
#include "CDPL/Grid/CDFDataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFAttributedGridPropertyReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


void GRAIL::CDFAttributedGridPropertyReader::registerExternalPropertyHandlers()
{
    Grid::CDFDataReader::registerExternalPropertyHandler(&readProperties);
}

bool GRAIL::CDFAttributedGridPropertyReader::readProperties(unsigned int handler_id, const Grid::CDFDataReader& reader, 
															 Grid::AttributedGrid& grid, Internal::ByteBuffer& data)
{
    if (handler_id != CDF::AttributedGridProperty::PROPERTY_HANDLER_ID)
		return false;

    CDF::PropertySpec prop_spec;
    CDF::UIntType uint_val;

    while (true) {
		unsigned int prop_id = reader.getPropertySpec(prop_spec, data);

		if (prop_id == CDF::PROP_LIST_END)
			return true;

		switch (prop_id) {

			case CDF::AttributedGridProperty::FEATURE_TYPE:
				reader.getIntProperty(prop_spec, uint_val, data);
				setFeatureType(grid, uint_val);
				continue;
  
			case CDF::AttributedGridProperty::TARGET_FEATURE_TYPE:
				reader.getIntProperty(prop_spec, uint_val, data);
				setTargetFeatureType(grid, uint_val);
				continue;

			default:
				throw Base::IOError("CDFAttributedGridPropertyReader: unsupported grid property");
		}
    }
}
