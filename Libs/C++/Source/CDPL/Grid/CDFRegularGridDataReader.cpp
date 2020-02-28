/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFRegularGridDataReader.cpp 
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

#include "CDPL/Grid/ControlParameterFunctions.hpp"
#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFRegularGridDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Grid::CDFRegularGridDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::DREGULAR_GRID_RECORD_ID, true, dataBuffer);
}

bool Grid::CDFRegularGridDataReader::readGrid(std::istream& is, DRegularGrid& grid)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::DREGULAR_GRID_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

    readGridData(grid, dataBuffer);

	return true;
}

bool Grid::CDFRegularGridDataReader::skipGrid(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::DREGULAR_GRID_RECORD_ID, dataBuffer);
}

void Grid::CDFRegularGridDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
}

bool Grid::CDFRegularGridDataReader::readGrid(DRegularGrid& grid, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

    return doReadGrid(grid, bbuf);
}

bool Grid::CDFRegularGridDataReader::doReadGrid(DRegularGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::DREGULAR_GRID_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFRegularGridDataReader: trying to read a non-interaction score grid record");

		return false;
	}

    readGridData(grid, bbuf);

	return true;
}

void Grid::CDFRegularGridDataReader::readGridData(DRegularGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::BoolType cell_data_mode;
	Base::uint8 fp_len;

	bbuf.getInt(cell_data_mode);
	grid.setDataMode(cell_data_mode ? DRegularGrid::CELL : DRegularGrid::POINT);

	bbuf.getInt(fp_len);

	if (fp_len != sizeof(DRegularGrid::CoordinatesValueType)) {
		if (fp_len == sizeof(float)) {
			float fp_val;

			bbuf.getFloat(fp_val);
			grid.setXStepSize(fp_val);

			bbuf.getFloat(fp_val);
			grid.setYStepSize(fp_val);

			bbuf.getFloat(fp_val);
			grid.setZStepSize(fp_val);
		
		} else
			throw Base::IOError("CDFRegularGridDataReader: value type size mismatch");

	} else {
		DRegularGrid::CoordinatesValueType fp_val;

		bbuf.getFloat(fp_val);
		grid.setXStepSize(fp_val);
		
		bbuf.getFloat(fp_val);
		grid.setYStepSize(fp_val);
		
		bbuf.getFloat(fp_val);
		grid.setZStepSize(fp_val);
	}

	getGrid(grid, bbuf, fp_len);

	DRegularGrid::CoordinatesTransformType xform;

	getCMatrix(xform, bbuf, fp_len);

	grid.setCoordinatesTransform(xform);

    readProperties(grid, bbuf);
}
