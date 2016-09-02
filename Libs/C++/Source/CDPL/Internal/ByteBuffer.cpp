/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringUtilities.cpp
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
#include <ostream>
#include <cstring>

#include <boost/detail/endian.hpp>

#include "CDPL/Base/Exceptions.hpp"

#include "ByteBuffer.hpp"


using namespace CDPL;


Internal::ByteBuffer::ByteBuffer(std::size_t reserve): ioPointer(0)
{
    data.reserve(reserve);
}

std::size_t Internal::ByteBuffer::getIOPointer() const
{
    return ioPointer;
}

void Internal::ByteBuffer::setIOPointer(std::size_t pos)
{
    ioPointer = pos;
}
 
void Internal::ByteBuffer::reserve(std::size_t size)
{
    data.reserve(size);
}

void Internal::ByteBuffer::resize(std::size_t size, char value)
{
    data.resize(size, value);
}

std::size_t Internal::ByteBuffer::getSize() const
{
    return data.size();
}

void Internal::ByteBuffer::putBytes(const char* bytes, std::size_t num_bytes)
{
	reserveWriteSpace(num_bytes);

	std::memcpy(&data[ioPointer], bytes, num_bytes);
	ioPointer += num_bytes;
}

void Internal::ByteBuffer::putBytes(const ByteBuffer& buffer)
{
	putBytes(&buffer.data[0], buffer.getSize());
}

void Internal::ByteBuffer::getBytes(char* bytes, std::size_t num_bytes)
{
	checkReadSpace(num_bytes);

	std::memcpy(bytes, &data[ioPointer], num_bytes);
	ioPointer += num_bytes;
}

std::size_t Internal::ByteBuffer::readBuffer(std::istream& is, std::size_t num_bytes)
{
    data.resize(num_bytes);
    is.read(&data[0], num_bytes);

    return is.gcount();
}

void Internal::ByteBuffer::writeBuffer(std::ostream& os) const
{
    os.write(&data[0], data.size());
}

void Internal::ByteBuffer::reserveWriteSpace(std::size_t num_bytes)
{
    std::size_t req_size = ioPointer + num_bytes;

    if (req_size > data.size())
		data.resize(req_size);
}

void Internal::ByteBuffer::checkReadSpace(std::size_t num_bytes) const
{
    std::size_t req_size = ioPointer + num_bytes;

    if (req_size > data.size())
		throw Base::IOError("ByteBuffer: attempting to read beyond the end of data");
}

std::size_t Internal::ByteBuffer::putValueBytes(const char* bytes, std::size_t num_bytes, bool compress)
{
#if defined(BOOST_BIG_ENDIAN)

	if (compress) {
		std::size_t nz_offs = 0;

		for ( ; nz_offs < (num_bytes - 1) && bytes[nz_offs] == 0; nz_offs++);

		bytes += num_bytes;
		num_bytes -= nz_offs;
	
	} else
		bytes += num_bytes;	

	reserveWriteSpace(num_bytes);

	for (std::size_t i = 0; i < num_bytes; i++)
		data[ioPointer++] = *(--bytes);

	return num_bytes;

#elif defined(BOOST_LITTLE_ENDIAN)

	if (compress)
		for ( ; num_bytes > 1 && bytes[num_bytes - 1] == 0; num_bytes--);

	reserveWriteSpace(num_bytes);

	std::memcpy(&data[ioPointer], bytes, num_bytes);
	ioPointer += num_bytes;

	return num_bytes;

#else
# error "ByteBuffer: BOOST_LITTLE_ENDIAN or BOOST_BIG_ENDIAN needs to be defined"
#endif
}

void Internal::ByteBuffer::getValueBytes(char* bytes, std::size_t type_size, std::size_t num_bytes)
{
	checkReadSpace(num_bytes);

#if defined(BOOST_BIG_ENDIAN)

	bytes += type_size;

	for (std::size_t i = 0; i < num_bytes; i++)
		*(--bytes) = data[ioPointer++];

#elif defined(BOOST_LITTLE_ENDIAN)

	std::memcpy(bytes, &data[ioPointer], num_bytes);
	ioPointer += num_bytes;

#else
# error "ByteBuffer: BOOST_LITTLE_ENDIAN or BOOST_BIG_ENDIAN needs to be defined"
#endif
}
