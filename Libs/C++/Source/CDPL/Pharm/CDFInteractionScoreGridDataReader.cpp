/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFInteractionScoreGridDataReader.cpp 
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

#include "CDPL/Base/IntTypes.hpp"
#include "CDPL/Pharm/InteractionScoreGrid.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFInteractionScoreGridDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Pharm::CDFInteractionScoreGridDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::INTERACTION_SCORE_GRID_RECORD_ID, true, dataBuffer);
}

bool Pharm::CDFInteractionScoreGridDataReader::readGrid(std::istream& is, InteractionScoreGrid& grid)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::INTERACTION_SCORE_GRID_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

    readGridData(grid, dataBuffer);

	return true;
}

bool Pharm::CDFInteractionScoreGridDataReader::skipGrid(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::INTERACTION_SCORE_GRID_RECORD_ID, dataBuffer);
}

void Pharm::CDFInteractionScoreGridDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
}

bool Pharm::CDFInteractionScoreGridDataReader::readGrid(InteractionScoreGrid& grid, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

    return doReadGrid(grid, bbuf);
}

bool Pharm::CDFInteractionScoreGridDataReader::doReadGrid(InteractionScoreGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::INTERACTION_SCORE_GRID_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFInteractionScoreGridDataReader: trying to read a non-interaction score grid record");

		return false;
	}

    readGridData(grid, bbuf);

	return true;
}

void Pharm::CDFInteractionScoreGridDataReader::readGridData(InteractionScoreGrid& grid, Internal::ByteBuffer& bbuf) const
{
	CDF::UIntType uint_val;

	bbuf.getInt(uint_val);
	grid.setFeatureType(uint_val);

	bbuf.getInt(uint_val);
	grid.setTargetFeatureType(uint_val);

	Base::uint8 fp_len;

	bbuf.getInt(fp_len);

	if (fp_len != sizeof(InteractionScoreGrid::CoordinatesValueType)) {
		if (fp_len == sizeof(float)) {
			float fp_val;

			bbuf.getFloat(fp_val);
			grid.setXStepSize(fp_val);

			bbuf.getFloat(fp_val);
			grid.setYStepSize(fp_val);

			bbuf.getFloat(fp_val);
			grid.setZStepSize(fp_val);
		
		} else
			throw Base::IOError("CDFInteractionScoreGridDataReader: value type size mismatch");

	} else {
		InteractionScoreGrid::CoordinatesValueType fp_val;

		bbuf.getFloat(fp_val);
		grid.setXStepSize(fp_val);
		
		bbuf.getFloat(fp_val);
		grid.setYStepSize(fp_val);
		
		bbuf.getFloat(fp_val);
		grid.setZStepSize(fp_val);
	}

	getGrid(grid, bbuf, fp_len);

	InteractionScoreGrid::CoordinatesTransformType xform;

	getCMatrix(xform, bbuf, fp_len);
}
