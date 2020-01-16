/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriterBase.hpp 
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


#ifndef CDPL_INTERNAL_CDFDATAWRITERBASE_HPP
#define CDPL_INTERNAL_CDFDATAWRITERBASE_HPP

#include <cstddef>
#include <string>

#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Math/VectorArray.hpp"

#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Internal/CDFFormatData.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL 
{

	namespace Internal
	{

		class CDFDataWriterBase
		{

		public:
			CDFDataWriterBase(): strictErrorChecks(true), singlePrecFloats(false) {}

			virtual ~CDFDataWriterBase() {}

			void putHeader(const CDF::Header& header, ByteBuffer& bbuf) const;

			template <typename T>
			void putIntProperty(unsigned int prop_id, const T& value, ByteBuffer& bbuf, bool compress = true) const;

			template <typename T>
			void putFloatProperty(unsigned int prop_id, const T& value, ByteBuffer& bbuf) const;

			template <typename Array>
			void putFloatArrayProperty(unsigned int prop_id, const Array& array, ByteBuffer& bbuf) const;

			void putStringProperty(unsigned int prop_id, const std::string& str, ByteBuffer& bbuf) const;

            template <typename Vec, typename ValueType = typename Vec::ValueType>
			void putVectorProperty(unsigned int prop_id, const Vec& vec, ByteBuffer& bbuf) const;
 
            template <typename Vec>
			void putCVectorProperty(unsigned int prop_id, const Vec& vec, ByteBuffer& bbuf) const;

            template <typename Vec>
			void putCVectorArrayProperty(unsigned int prop_id, const Math::VectorArray<Vec>& vey_array, ByteBuffer& bbuf) const;
 
			template <typename Mtx>
			void putCMatrix(const Mtx& mtx, ByteBuffer& bbuf, bool write_fp_len) const;

			template <typename Grid>
			void putGrid(const Grid& grid, ByteBuffer& bbuf, bool write_fp_len) const;

			void putString(const std::string& str, ByteBuffer& bbuf) const;

			bool strictErrorChecking() const;

			void strictErrorChecking(bool strict);

			bool singlePrecisionFloats() const;

			void singlePrecisionFloats(bool spf);

			void putPropertyListMarker(unsigned int prop_id, ByteBuffer& bbuf) const;

		private:
            CDF::PropertySpec composePropertySpec(unsigned int prop_id, std::size_t length) const;

			bool strictErrorChecks;
			bool singlePrecFloats;
		};
	}
}


// Implementation

template <typename T>
void CDPL::Internal::CDFDataWriterBase::putIntProperty(unsigned int prop_id, const T& value, 
													   ByteBuffer& bbuf, bool compress) const
{
    BOOST_STATIC_ASSERT_MSG((sizeof(T) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
							"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

	std::size_t last_pos = bbuf.getIOPointer();

	bbuf.setIOPointer(last_pos + 1);

	std::size_t num_bytes = bbuf.putInt(value, compress);

	bbuf.setIOPointer(last_pos);
	bbuf.putInt(composePropertySpec(prop_id, num_bytes), false);
	bbuf.setIOPointer(last_pos + 1 + num_bytes);
}

template <typename T>
void CDPL::Internal::CDFDataWriterBase::putFloatProperty(unsigned int prop_id, const T& value, ByteBuffer& bbuf) const
{
	if (singlePrecFloats) {
		BOOST_STATIC_ASSERT_MSG((sizeof(float) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
								"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

		bbuf.putInt(composePropertySpec(prop_id, sizeof(float)), false);
		bbuf.putFloat(float(value));
		return;
	}
 
    BOOST_STATIC_ASSERT_MSG((sizeof(T) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
							"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

	bbuf.putInt(composePropertySpec(prop_id, sizeof(T)), false);
	bbuf.putFloat(value);
}

template <typename Array>
void CDPL::Internal::CDFDataWriterBase::putFloatArrayProperty(unsigned int prop_id, const Array& array, ByteBuffer& bbuf) const
{
	putVectorProperty<Array, typename Array::ElementType>(prop_id, array, bbuf);
}

template <typename Vec, typename ValueType>
void CDPL::Internal::CDFDataWriterBase::putVectorProperty(unsigned int prop_id, const Vec& vec, ByteBuffer& bbuf) const
{
	if (singlePrecFloats) {
		BOOST_STATIC_ASSERT_MSG((sizeof(float) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
								"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

		bbuf.putInt(composePropertySpec(prop_id, sizeof(float)), false);
		bbuf.putInt(boost::numeric_cast<CDF::SizeType>(vec.getSize()), false);

		for (std::size_t i = 0; i < vec.getSize(); i++)
			bbuf.putFloat(float(vec[i]));

		return;
	}
 
    BOOST_STATIC_ASSERT_MSG((sizeof(ValueType) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
							"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

	bbuf.putInt(composePropertySpec(prop_id, sizeof(ValueType)), false);
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(vec.getSize()), false);

	for (std::size_t i = 0; i < vec.getSize(); i++)
		bbuf.putFloat(vec[i]);
}

template <typename Vec>
void CDPL::Internal::CDFDataWriterBase::putCVectorProperty(unsigned int prop_id, const Vec& vec, ByteBuffer& bbuf) const
{
	if (singlePrecFloats) {
		BOOST_STATIC_ASSERT_MSG((sizeof(float) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
								"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

		bbuf.putInt(composePropertySpec(prop_id, sizeof(float)), false);

		for (std::size_t i = 0; i < Vec::Size; i++)
			bbuf.putFloat(float(vec[i]));

		return;
	}
 
    typedef typename Vec::ValueType T;

    BOOST_STATIC_ASSERT_MSG((sizeof(T) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
							"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

	bbuf.putInt(composePropertySpec(prop_id, sizeof(T)), false);

	for (std::size_t i = 0; i < Vec::Size; i++)
		bbuf.putFloat(vec[i]);
}

template <typename Vec>
void CDPL::Internal::CDFDataWriterBase::putCVectorArrayProperty(unsigned int prop_id, const Math::VectorArray<Vec>& vec_array, ByteBuffer& bbuf) const
{
	if (singlePrecFloats) {
		BOOST_STATIC_ASSERT_MSG((sizeof(float) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
								"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

		bbuf.putInt(composePropertySpec(prop_id, sizeof(float)), false);
		bbuf.putInt(boost::numeric_cast<CDF::SizeType>(vec_array.getSize()), false);

		for (std::size_t i = 0; i < vec_array.getSize(); i++)
			for (std::size_t j = 0; j < Vec::Size; j++)
				bbuf.putFloat(float(vec_array[i][j]));

		return;
	}
 
    typedef typename Vec::ValueType T;

    BOOST_STATIC_ASSERT_MSG((sizeof(T) - 1) < (1 << CDF::NUM_PROP_VALUE_LENGTH_BITS), 
							"CDFDataWriterBase: maximum size of primitive IO data type exceeded");

	bbuf.putInt(composePropertySpec(prop_id, sizeof(T)), false);
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(vec_array.getSize()), false);

	for (std::size_t i = 0; i < vec_array.getSize(); i++)
		for (std::size_t j = 0; j < Vec::Size; j++)
			bbuf.putFloat(vec_array[i][j]);
}

template <typename Mtx>
void CDPL::Internal::CDFDataWriterBase::putCMatrix(const Mtx& mtx, ByteBuffer& bbuf, bool write_fp_len) const
{
	if (write_fp_len)
		bbuf.putInt(boost::numeric_cast<Base::uint8>(singlePrecFloats ? sizeof(float) : sizeof(typename Mtx::ValueType)), false);
	
	if (singlePrecFloats) {
		for (std::size_t i = 0; i < Mtx::Size1; i++)
			for (std::size_t j = 0; j < Mtx::Size2; j++)
				bbuf.putFloat(float(mtx(i, j)));
		return;
	}
  
	for (std::size_t i = 0; i < Mtx::Size1; i++)
		for (std::size_t j = 0; j < Mtx::Size2; j++)
			bbuf.putFloat(mtx(i, j));
}

template <typename Grid>
void CDPL::Internal::CDFDataWriterBase::putGrid(const Grid& grid, ByteBuffer& bbuf, bool write_fp_len) const
{
	if (write_fp_len)
		bbuf.putInt(boost::numeric_cast<Base::uint8>(singlePrecFloats ? sizeof(float) : sizeof(typename Grid::ValueType)), false);

	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(grid.getSize1()), false);
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(grid.getSize2()), false);
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(grid.getSize3()), false);

	if (singlePrecFloats) {
		for (std::size_t i = 0; i < grid.getSize1(); i++)
			for (std::size_t j = 0; j < grid.getSize2(); j++)
				for (std::size_t k = 0; k < grid.getSize3(); k++)
					bbuf.putFloat(float(grid(i, j, k)));

		return;
	}

	for (std::size_t i = 0; i < grid.getSize1(); i++)
		for (std::size_t j = 0; j < grid.getSize2(); j++)
			for (std::size_t k = 0; k < grid.getSize3(); k++)
				bbuf.putFloat(grid(i, j, k));
}


#endif // CDPL_INTERNAL_CDFDATAWRITERBASE_HPP
