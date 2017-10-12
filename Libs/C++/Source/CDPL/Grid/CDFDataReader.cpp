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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFDataReader.hpp"


using namespace CDPL;


Grid::CDFDataReader::PropertyHandlerList Grid::CDFDataReader::extPropertyHandlers;


void Grid::CDFDataReader::registerExternalPropertyHandler(const PropertyHandler& handler)
{
	extPropertyHandlers.push_back(handler);
}

void Grid::CDFDataReader::readProperties(AttributedGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::PropertySpec prop_spec;
	std::string str_val;

	while (true) {
		unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

		if (prop_id == CDF::PROP_LIST_END)
			break;

		switch (prop_id) {

			case CDF::EXTENDED_PROP_LIST:
				readExternalProperties(prop_spec, grid, bbuf);
				continue;

			case CDF::AttributedGridProperty::NAME:
				getStringProperty(prop_spec, str_val, bbuf);
				setName(grid, str_val);
				continue;

			default:
				throw Base::IOError("CDFRegularGridDataReader: unsupported property");
		}
	}
}

void Grid::CDFDataReader::readExternalProperties(CDF::PropertySpec prop_spec, AttributedGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::SizeType size_val;

	getIntProperty(prop_spec, size_val, bbuf);
	
	unsigned int handler_id = getPropertySpec(prop_spec, bbuf);

	if (!readExternalProperties(handler_id, grid, bbuf))
		bbuf.setIOPointer(bbuf.getIOPointer() + size_val);
}

bool Grid::CDFDataReader::readExternalProperties(unsigned int handler_id, AttributedGrid& grid, Internal::ByteBuffer& bbuf) const
{
	return (std::find_if(extPropertyHandlers.begin(), extPropertyHandlers.end(),
						 boost::bind(&PropertyHandler::operator(), _1, handler_id, boost::ref(*this), boost::ref(grid), boost::ref(bbuf)))
			!= extPropertyHandlers.end());
}
