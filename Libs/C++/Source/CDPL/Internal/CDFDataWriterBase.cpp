/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriterBase.cpp 
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


#include <ostream>

#include <boost/numeric/conversion/cast.hpp>

#include "CDFDataWriterBase.hpp"


using namespace CDPL;


bool Internal::CDFDataWriterBase::writeHeader(std::ostream& os, const CDF::Header& header)
{
	hdrBuffer.setIOPointer(0);
	hdrBuffer.putInt(CDF::FORMAT_ID, false);
	hdrBuffer.putInt(header.recordTypeID, false);
	hdrBuffer.putInt(header.recordFormatVersion, false);
	hdrBuffer.putInt(header.recordDataLength, false);
	hdrBuffer.writeBuffer(os);

	return os.good();
}

void Internal::CDFDataWriterBase::putStringProperty(unsigned int prop_id, const std::string& str, ByteBuffer& bbuf) const
{
	std::size_t last_pos = bbuf.getIOPointer();

	bbuf.setIOPointer(last_pos + 1);

	std::size_t num_bytes = bbuf.putInt(boost::numeric_cast<CDF::SizeType>(str.length()), true);

	bbuf.setIOPointer(last_pos);
	bbuf.putInt(composePropertySpec(prop_id, num_bytes), false);
	bbuf.setIOPointer(last_pos + 1 + num_bytes);
	bbuf.putBytes(str.c_str(), str.length());
}

Internal::CDF::PropertySpec Internal::CDFDataWriterBase::composePropertySpec(unsigned int prop_id, std::size_t length) const
{
	CDF::PropertySpec prop_byte = (prop_id << CDF::NUM_PROP_VALUE_LENGTH_BITS);

	prop_byte += length - 1;

	return prop_byte;
}

bool Internal::CDFDataWriterBase::strictErrorChecking() const
{
	return strictErrorChecks;
}

void Internal::CDFDataWriterBase::strictErrorChecking(bool strict)
{
	strictErrorChecks = strict;
}
