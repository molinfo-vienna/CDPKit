/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFRegularGridDataWriter.cpp 
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

#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"

#include "CDFRegularGridDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Grid::CDFRegularGridDataWriter::writeGrid(std::ostream& os, const DRegularGrid& grid)
{
	writeGrid(grid, dataBuffer);

	return writeRecordData(os);
}

void Grid::CDFRegularGridDataWriter::writeGrid(const DRegularGrid& grid, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	appendGrid(grid, bbuf);

	bbuf.resize(bbuf.getIOPointer());
}

void Grid::CDFRegularGridDataWriter::appendGrid(const DRegularGrid& grid, Internal::ByteBuffer& bbuf)
{
	std::size_t init_pos = bbuf.getIOPointer();

	bbuf.setIOPointer(init_pos + CDF::HEADER_SIZE);

	outputGridData(grid, bbuf);

	std::size_t saved_pos = bbuf.getIOPointer();

	bbuf.setIOPointer(init_pos);

	outputGridHeader(grid, bbuf, saved_pos - init_pos - CDF::HEADER_SIZE);

	bbuf.setIOPointer(saved_pos);
}

void Grid::CDFRegularGridDataWriter::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
	singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ctrlParams));
}

void Grid::CDFRegularGridDataWriter::outputGridHeader(const DRegularGrid& grid, Internal::ByteBuffer& bbuf, std::size_t rec_size) const
{
	CDF::Header cdf_header;

	cdf_header.recordDataLength = boost::numeric_cast<Base::uint64>(rec_size);
	cdf_header.recordTypeID = CDF::DREGULAR_GRID_RECORD_ID;
	cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	putHeader(cdf_header, bbuf);
}

void Grid::CDFRegularGridDataWriter::outputGridData(const DRegularGrid& grid, Internal::ByteBuffer& bbuf)
{	
	bbuf.putInt(CDF::BoolType(grid.getDataMode() == DRegularGrid::CELL), false);

	if (singlePrecisionFloats()) {
		bbuf.putInt(boost::numeric_cast<Base::uint8>(sizeof(float)), false);				
		bbuf.putFloat(float(grid.getXStepSize()));
		bbuf.putFloat(float(grid.getYStepSize()));
		bbuf.putFloat(float(grid.getZStepSize()));

	} else {
		bbuf.putInt(boost::numeric_cast<Base::uint8>(sizeof(typename DRegularGrid::CoordinatesValueType)), false);	
		bbuf.putFloat(grid.getXStepSize());
		bbuf.putFloat(grid.getYStepSize());
		bbuf.putFloat(grid.getZStepSize());
	}

	putGrid(grid, bbuf, false);
	putCMatrix(grid.getCoordinatesTransform(), bbuf, false);

	outputProperties(grid, bbuf);
}

bool Grid::CDFRegularGridDataWriter::writeRecordData(std::ostream& os) const
{
	dataBuffer.writeBuffer(os);

	return os.good();
}
