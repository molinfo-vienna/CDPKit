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
#include <istream>
#include <ostream>
#include <limits>
#include <algorithm>
#include <cstring>

#include <boost/static_assert.hpp>
#include <boost/version.hpp>

#if (BOOST_VERSION < 105800)
# include <boost/detail/endian.hpp>
# if defined(BOOST_BIG_ENDIAN)
#  define CDPL_BIG_ENDIAN_NATIVE_ORDER true
# elif defined(BOOST_LITTLE_ENDIAN)
#  define CDPL_BIG_ENDIAN_NATIVE_ORDER false
# else
#  error "ByteBuffer: BOOST_LITTLE_ENDIAN or BOOST_BIG_ENDIAN needs to be defined"
# endif
#else
# include <boost/endian/conversion.hpp>
# define CDPL_BIG_ENDIAN_NATIVE_ORDER (boost::endian::order::native == boost::endian::order::big)
#endif

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Internal
    {

        class ByteBuffer
        {

          public:
            inline
            ByteBuffer(std::size_t size = 1024);

            inline
            std::size_t getIOPointer() const;

            inline
            void setIOPointer(std::size_t pos);

            inline
            void reserve(std::size_t size);

            inline
            void resize(std::size_t size, char value = 0);

            inline
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

            inline
            void putBytes(const char* bytes, std::size_t num_bytes);

            inline
            void putBytes(const ByteBuffer& buffer);

            inline
            void getBytes(char* bytes, std::size_t num_bytes);

            inline
            std::size_t readBuffer(std::istream& is, std::size_t num_bytes);

            inline
            void writeBuffer(std::ostream& os) const;

            inline
            const char* getData() const;

            inline
            char* getData();

          private:
            inline
            void reserveWriteSpace(std::size_t num_bytes);
            inline
            void checkReadSpace(std::size_t num_bytes) const;

            inline
            std::size_t putValueBytes(const char* bytes, std::size_t num_bytes, bool compress);
            inline
            void getValueBytes(char* bytes, std::size_t type_size, std::size_t num_bytes);

            typedef std::vector<char> StorageType;

            StorageType data;
            std::size_t ioPointer;
        };
    } // namespace Internal
} // namespace CDPL


// Implementation

CDPL::Internal::ByteBuffer::ByteBuffer(std::size_t reserve): ioPointer(0)
{
    data.reserve(reserve);
}

std::size_t CDPL::Internal::ByteBuffer::getIOPointer() const
{
    return ioPointer;
}

void CDPL::Internal::ByteBuffer::setIOPointer(std::size_t pos)
{
    ioPointer = pos;
}
 
void CDPL::Internal::ByteBuffer::reserve(std::size_t size)
{
    data.reserve(size);
}

void CDPL::Internal::ByteBuffer::resize(std::size_t size, char value)
{
    data.resize(size, value);
}

std::size_t CDPL::Internal::ByteBuffer::getSize() const
{
    return data.size();
}

void CDPL::Internal::ByteBuffer::putBytes(const char* bytes, std::size_t num_bytes)
{
    reserveWriteSpace(num_bytes);

    std::memcpy(&data[ioPointer], bytes, num_bytes);
    ioPointer += num_bytes;
}

void CDPL::Internal::ByteBuffer::putBytes(const ByteBuffer& buffer)
{
    putBytes(&buffer.data[0], buffer.getSize());
}

void CDPL::Internal::ByteBuffer::getBytes(char* bytes, std::size_t num_bytes)
{
    checkReadSpace(num_bytes);

    std::memcpy(bytes, &data[ioPointer], num_bytes);
    ioPointer += num_bytes;
}

std::size_t CDPL::Internal::ByteBuffer::readBuffer(std::istream& is, std::size_t num_bytes)
{
    data.resize(num_bytes);
    is.read(&data[0], num_bytes);

    return is.gcount();
}

void CDPL::Internal::ByteBuffer::writeBuffer(std::ostream& os) const
{
    os.write(&data[0], data.size());
}

void CDPL::Internal::ByteBuffer::reserveWriteSpace(std::size_t num_bytes)
{
    std::size_t req_size = ioPointer + num_bytes;

    if (req_size > data.size())
        data.resize(req_size);
}

void CDPL::Internal::ByteBuffer::checkReadSpace(std::size_t num_bytes) const
{
    std::size_t req_size = ioPointer + num_bytes;

    if (req_size > data.size())
        throw Base::IOError("ByteBuffer: attempting to read beyond the end of data");
}

std::size_t CDPL::Internal::ByteBuffer::putValueBytes(const char* bytes, std::size_t num_bytes, bool compress)
{
    if (CDPL_BIG_ENDIAN_NATIVE_ORDER) {
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
    } 

    if (compress)
        for ( ; num_bytes > 1 && bytes[num_bytes - 1] == 0; num_bytes--);

    reserveWriteSpace(num_bytes);

    std::memcpy(&data[ioPointer], bytes, num_bytes);
    ioPointer += num_bytes;

    return num_bytes;
}

void CDPL::Internal::ByteBuffer::getValueBytes(char* bytes, std::size_t type_size, std::size_t num_bytes)
{
    checkReadSpace(num_bytes);

    if (CDPL_BIG_ENDIAN_NATIVE_ORDER) {
        bytes += type_size;

        for (std::size_t i = 0; i < num_bytes; i++)
            *(--bytes) = data[ioPointer++];

    } else {
        std::memcpy(bytes, &data[ioPointer], num_bytes);
        ioPointer += num_bytes;
    }
}

const char* CDPL::Internal::ByteBuffer::getData() const
{
    return &data[0];
}

char* CDPL::Internal::ByteBuffer::getData()
{
    return &data[0];
}

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
    value     = T();
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
