/* 
 * CDFDataWriterBase.cpp 
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


#include "CDFDataWriterBase.hpp"


using namespace CDPL;


void Internal::CDFDataWriterBase::putHeader(const CDF::Header& header, ByteBuffer& bbuf) const
{
	bbuf.putInt(CDF::FORMAT_ID, false);
	bbuf.putInt(header.recordTypeID, false);
	bbuf.putInt(header.recordFormatVersion, false);
	bbuf.putInt(header.recordDataLength, false);
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

void Internal::CDFDataWriterBase::putString(const std::string& str, ByteBuffer& bbuf) const
{
	std::size_t last_pos = bbuf.getIOPointer();

	bbuf.setIOPointer(last_pos + 1);

	std::uint8_t num_bytes = bbuf.putInt(boost::numeric_cast<CDF::SizeType>(str.length()), true);

	bbuf.setIOPointer(last_pos);
	bbuf.putInt(num_bytes, false);
	bbuf.setIOPointer(last_pos + 1 + num_bytes);
	bbuf.putBytes(str.c_str(), str.length());
}

void Internal::CDFDataWriterBase::putPropertyListMarker(unsigned int prop_id, ByteBuffer& bbuf) const
{
	bbuf.putInt(composePropertySpec(prop_id, 1), false);
}

Internal::CDF::PropertySpec Internal::CDFDataWriterBase::composePropertySpec(unsigned int prop_id, std::size_t length) const
{
	return ((prop_id << CDF::NUM_PROP_VALUE_LENGTH_BITS) + length - 1);
}

bool Internal::CDFDataWriterBase::strictErrorChecking() const
{
	return strictErrorChecks;
}

void Internal::CDFDataWriterBase::strictErrorChecking(bool strict)
{
	strictErrorChecks = strict;
}

bool Internal::CDFDataWriterBase::singlePrecisionFloats() const
{
	return singlePrecFloats;
}

void Internal::CDFDataWriterBase::singlePrecisionFloats(bool spf)
{
	singlePrecFloats = spf;
}
