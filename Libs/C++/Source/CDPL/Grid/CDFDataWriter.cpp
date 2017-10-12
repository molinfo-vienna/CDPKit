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

#include <algorithm>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/bind.hpp>

#include "CDPL/Grid/AttributedGridFunctions.hpp"

#include "CDFDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


Grid::CDFDataWriter::PropertyHandlerList Grid::CDFDataWriter::extPropertyHandlers;


void Grid::CDFDataWriter::registerExternalPropertyHandler(const PropertyHandler& handler)
{
	extPropertyHandlers.push_back(handler);
}

void Grid::CDFDataWriter::outputProperties(const AttributedGrid& grid, Internal::ByteBuffer& bbuf)
{
	if (hasName(grid))
		putStringProperty(CDF::AttributedGridProperty::NAME, getName(grid), bbuf);

	outputExternalProperties(grid, bbuf);

	putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
}

void Grid::CDFDataWriter::outputExternalProperties(const AttributedGrid& grid, Internal::ByteBuffer& bbuf)
{
	std::for_each(extPropertyHandlers.begin(), extPropertyHandlers.end(),
				  boost::bind(&CDFDataWriter::outputExternalProperties, 
							  this, _1, boost::ref(grid), boost::ref(bbuf)));
}

void Grid::CDFDataWriter::outputExternalProperties(const PropertyHandler& handler, const AttributedGrid& grid, Internal::ByteBuffer& bbuf)
{
	extDataBuffer.setIOPointer(0);

	unsigned int handler_id = handler(*this, grid, extDataBuffer);

	if (extDataBuffer.getIOPointer() == 0)
		return;

	putPropertyListMarker(CDF::PROP_LIST_END, extDataBuffer);

	std::size_t ext_data_len = extDataBuffer.getIOPointer();

	extDataBuffer.resize(ext_data_len);

	putIntProperty(CDF::EXTENDED_PROP_LIST, boost::numeric_cast<CDF::SizeType>(ext_data_len), bbuf);
	putPropertyListMarker(handler_id, bbuf);

	bbuf.putBytes(extDataBuffer);
}
