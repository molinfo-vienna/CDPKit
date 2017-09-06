/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFInteractionScoreGridSetDataReader.cpp 
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

#include "CDPL/Pharm/InteractionScoreGridSet.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFInteractionScoreGridSetDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Pharm::CDFInteractionScoreGridSetDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::INTERACTION_SCORE_GRID_SET_RECORD_ID, true, dataBuffer);
}

bool Pharm::CDFInteractionScoreGridSetDataReader::readGridSet(std::istream& is, InteractionScoreGridSet& grid_set)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::INTERACTION_SCORE_GRID_SET_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);

	CDF::SizeType num_grids;

	dataBuffer.getInt(num_grids);

	for (std::size_t i = 0; i < num_grids; i++) {
		InteractionScoreGrid::SharedPointer grid_ptr(new InteractionScoreGrid());

		if (!readGrid(is, *grid_ptr))
			return false;

		grid_set.addElement(grid_ptr);
	}

	return true;
}

bool Pharm::CDFInteractionScoreGridSetDataReader::skipGridSet(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::INTERACTION_SCORE_GRID_SET_RECORD_ID, dataBuffer);
}

bool Pharm::CDFInteractionScoreGridSetDataReader::readGridSet(InteractionScoreGridSet& grid_set, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	return doReadGridSet(grid_set, bbuf);
}

bool Pharm::CDFInteractionScoreGridSetDataReader::doReadGridSet(InteractionScoreGridSet& grid_set, Internal::ByteBuffer& bbuf) const
{
	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::INTERACTION_SCORE_GRID_SET_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFInteractionScoreGridSetDataReader: trying to read a non-interaction score grid set record");

		return false;
	}

	CDF::SizeType num_grids;

	bbuf.getInt(num_grids);

	for (std::size_t i = 0; i < num_grids; i++) {
		InteractionScoreGrid::SharedPointer grid_ptr(new InteractionScoreGrid());

		if (!doReadGrid(*grid_ptr, bbuf))
			return false;

		grid_set.addElement(grid_ptr);
	}

	return true;
}
