/* 
 * CDFRegularGridSetDataReader.cpp 
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

#include "CDPL/Base/Exceptions.hpp"

#include "CDFRegularGridSetDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Grid::CDFRegularGridSetDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::DREGULAR_GRID_SET_RECORD_ID, true, dataBuffer);
}

bool Grid::CDFRegularGridSetDataReader::readGridSet(std::istream& is, DRegularGridSet& grid_set)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::DREGULAR_GRID_SET_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

	CDF::SizeType num_grids;

	dataBuffer.getInt(num_grids);

	for (std::size_t i = 0; i < num_grids; i++) {
		DRegularGrid::SharedPointer grid_ptr(new DRegularGrid(0));

		if (!readGrid(is, *grid_ptr))
			return false;

		grid_set.addElement(grid_ptr);
	}

	return true;
}

bool Grid::CDFRegularGridSetDataReader::skipGridSet(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::DREGULAR_GRID_SET_RECORD_ID, dataBuffer);
}

bool Grid::CDFRegularGridSetDataReader::readGridSet(DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	return doReadGridSet(grid_set, bbuf);
}

bool Grid::CDFRegularGridSetDataReader::doReadGridSet(DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf) const
{
	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::DREGULAR_GRID_SET_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFRegularGridSetDataReader: trying to read a non-interaction score grid set record");

		return false;
	}

	CDF::SizeType num_grids;

	bbuf.getInt(num_grids);

	for (std::size_t i = 0; i < num_grids; i++) {
		DRegularGrid::SharedPointer grid_ptr(new DRegularGrid(0));

		if (!doReadGrid(*grid_ptr, bbuf))
			return false;

		grid_set.addElement(grid_ptr);
	}

	return true;
}
