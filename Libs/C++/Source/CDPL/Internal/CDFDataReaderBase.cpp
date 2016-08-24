/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReaderBase.cpp 
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


#include <istream>

#include "CDFDataReaderBase.hpp"


using namespace CDPL; 


bool Internal::CDFDataReaderBase::skipToRecord(std::istream& is, CDF::Header& header, Base::uint8 rec_type, bool seek_beg)
{
    while (true) {
		std::istream::pos_type last_spos = is.tellg();

		if (std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof())) 
			break;

		if (!readHeader(is, header))
			return false;

		if (header.recordTypeID == rec_type) {
			if (seek_beg)
				is.seekg(last_spos);

			return true;
		}

		is.seekg(last_spos + std::istream::pos_type(header.recordDataLength) + std::istream::pos_type(CDF::HEADER_SIZE));
	}

	return false;
}

bool Internal::CDFDataReaderBase::skipNextRecord(std::istream& is, Base::uint8 rec_type)
{
	CDF::Header header;

    while (true) {
		std::istream::pos_type last_spos = is.tellg();

		if (std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof()))
			break;

		if (!readHeader(is, header))
			return false;

		is.seekg(last_spos + std::istream::pos_type(header.recordDataLength) + std::istream::pos_type(CDF::HEADER_SIZE));

		if (header.recordTypeID == rec_type)
			return true;
	}

	return false;
}

bool Internal::CDFDataReaderBase::readHeader(std::istream& is, CDF::Header& header)
{	
	std::size_t num_read = hdrBuffer.readBuffer(is, CDF::HEADER_SIZE);

	if (!is.good())
		throw Base::IOError("CDFDataReaderBase: could not read CDF-header, input stream read error");

	if (num_read != CDF::HEADER_SIZE) {
		if (strictErrorChecks)
			throw Base::IOError("CDFDataReaderBase: could not read CDF-header, unexpected end of input");

		return false;
	}

	hdrBuffer.setIOPointer(0);
	hdrBuffer.getInt(header.formatID);
	hdrBuffer.getInt(header.recordTypeID);
	hdrBuffer.getInt(header.recordFormatVersion);
	hdrBuffer.getInt(header.recordDataLength);

	if (header.formatID == CDF::FORMAT_ID)
		return true;
 
	if (strictErrorChecks)
		throw Base::IOError("CDFDataReaderBase: invalid CDF-header, format-ID mismatch");

	return false;
}

void Internal::CDFDataReaderBase::readData(std::istream& is, std::size_t length, ByteBuffer& bbuf) const
{
	std::size_t num_read = bbuf.readBuffer(is, length);

	if (!is.good())
		throw Base::IOError("CDFDataReaderBase: could not read CDF-record data, input stream read error");

	if (num_read != length)
		throw Base::IOError("CDFDataReaderBase: could not read CDF-record data, unexpected end of input");
}

void Internal::CDFDataReaderBase::getStringProperty(CDF::PropertySpec prop_spec, std::string& str, ByteBuffer& bbuf) const
{
	CDF::SizeType str_len; 

	getIntProperty(prop_spec, str_len, bbuf);

	str.resize(str_len);
	bbuf.getBytes(&str[0], str_len);
}

bool Internal::CDFDataReaderBase::strictErrorChecking() const
{
	return strictErrorChecks;
}

void Internal::CDFDataReaderBase::strictErrorChecking(bool strict)
{
	strictErrorChecks = strict;
}
