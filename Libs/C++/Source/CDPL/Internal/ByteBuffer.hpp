/* 
 * ByteBuffer.hpp
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


#ifndef CDPL_INTERNAL_BYTEBUFFER_HPP
#define CDPL_INTERNAL_BYTEBUFFER_HPP

#include <cstddef>
#include <vector>
#include <iosfwd>
#include <limits>
#include <algorithm>

#include <boost/static_assert.hpp>


namespace CDPL
{

    namespace Internal
    {

		class ByteBuffer
		{

		public:
			ByteBuffer(std::size_t size = 1024);

			std::size_t getIOPointer() const;

			void setIOPointer(std::size_t pos);
	    
			void reserve(std::size_t size);

			void resize(std::size_t size, char value = 0);

            std::size_t getSize() const;
	
			template <typename T>
			std::size_t putInt(const T& value, bool compress);

			template <typename T>
			void getInt(T& value);

			template <typename T>
			void getInt(T& value, std::size_t num_bytes);

			template <typename T>
			void putFloat(const T& value);

			template <typename T>
			void getFloat(T& value);

			void putBytes(const char* bytes, std::size_t num_bytes);
	
			void putBytes(const ByteBuffer& buffer);
	
			void getBytes(char* bytes, std::size_t num_bytes);

			std::size_t readBuffer(std::istream& is, std::size_t num_bytes);

			void writeBuffer(std::ostream& os) const;

			const char* getData() const;

			char* getData();

		private:
			void reserveWriteSpace(std::size_t num_bytes);
			void checkReadSpace(std::size_t num_bytes) const;

			std::size_t putValueBytes(const char* bytes, std::size_t num_bytes, bool compress);
			void getValueBytes(char* bytes, std::size_t type_size, std::size_t num_bytes);

			typedef std::vector<char> StorageType;

			StorageType data;
			std::size_t ioPointer;
		};
    }
}


// Implementation

template <typename T>
std::size_t CDPL::Internal::ByteBuffer::putInt(const T& value, bool compress)
{
	BOOST_STATIC_ASSERT_MSG(sizeof(T) > 0, 
							"ByteBuffer: byte size of integer type is zero");

	return putValueBytes(reinterpret_cast<const char*>(&value), sizeof(T), compress);
}

template <typename T>
void CDPL::Internal::ByteBuffer::getInt(T& value)
{
	getValueBytes(reinterpret_cast<char*>(&value), sizeof(T), sizeof(T));
}

template <typename T>
void CDPL::Internal::ByteBuffer::getInt(T& value, std::size_t num_bytes)
{
	value = T();
	num_bytes = std::min(num_bytes, sizeof(T));

	getValueBytes(reinterpret_cast<char*>(&value), sizeof(T), num_bytes);
}

template <typename T>
void CDPL::Internal::ByteBuffer::putFloat(const T& value)
{
	BOOST_STATIC_ASSERT_MSG(std::numeric_limits<T>::is_iec559, 
							"ByteBuffer: floating-point types must adhere to the IEC-559 standard");

	putValueBytes(reinterpret_cast<const char*>(&value), sizeof(T), false);
}

template <typename T>
void CDPL::Internal::ByteBuffer::getFloat(T& value)
{
	BOOST_STATIC_ASSERT_MSG(std::numeric_limits<T>::is_iec559, 
							"ByteBuffer: floating-point types must adhere to the IEC-559 standard");

	getValueBytes(reinterpret_cast<char*>(&value), sizeof(T), sizeof(T));
}

#endif // CDPL_INTERNAL_BYTEBUFFER_HPP
