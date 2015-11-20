/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	template <typename V, typename T>
	void checkValues3(typename V::SizeType size, V& vec, T values[])
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());

		for (typename V::SizeType i = 0; i < size; i++) {
			BOOST_CHECK_EQUAL(vec(i), values[i]);
			BOOST_CHECK_EQUAL(vec[i], values[i]);

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), values[i]);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], values[i]);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}

	template <typename V, typename T>
	void checkValues3(typename V::SizeType size, V& vec, const T& value)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());

		for (typename V::SizeType i = 0; i < size; i++) {
			BOOST_CHECK_EQUAL(vec(i), value);
			BOOST_CHECK_EQUAL(vec[i], value);

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), value);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], value);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}

	template <typename V, typename T>
	void checkValues2(typename V::SizeType size, V& vec, T values[])
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());

		for (typename V::SizeType i = 0; i < size; i++) {
			BOOST_CHECK_EQUAL(vec(i), values[i]);
			BOOST_CHECK_EQUAL(vec[i], values[i]);
			BOOST_CHECK_EQUAL(vec.getData()[i], values[i]);

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), values[i]);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], values[i]);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec).getData()[i], values[i]);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}

	template <typename V, typename T>
	void checkValues2(typename V::SizeType size, V& vec, const T& value)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());

		for (typename V::SizeType i = 0; i < size; i++) {
			BOOST_CHECK_EQUAL(vec(i), value);
			BOOST_CHECK_EQUAL(vec[i], value);
			BOOST_CHECK_EQUAL(vec.getData()[i], value);

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), value);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], value);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec).getData()[i], value);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}

	template <typename V, typename T>
	void checkValues1(typename V::SizeType size, const V& vec, T values[])
	{
		checkValues2(size, vec, values);

		BOOST_CHECK(!vec.getData().empty());
		BOOST_CHECK(!const_cast<const V&>(vec).getData().empty());
	}

	template <typename V, typename T>
	void checkValues1(typename V::SizeType size, V& vec, const T& value)
	{
		checkValues2(size, vec, value);

		BOOST_CHECK(!vec.getData().empty());
		BOOST_CHECK(!const_cast<const V&>(vec).getData().empty());
	}

	template <typename V>
	void checkEmpty2(V& vec)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), 0);
		BOOST_CHECK(vec.isEmpty());

		BOOST_CHECK_THROW(vec(0), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(0), Base::IndexError);

		BOOST_CHECK_THROW(vec[0], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[0], Base::IndexError);
	}

	template <typename V>
	void checkEmpty1(V& vec)
	{
		checkEmpty2(vec);

		BOOST_CHECK(vec.getData().empty());
		BOOST_CHECK(const_cast<const V&>(vec).getData().empty());
	}

	template <typename V>
	void checkSize(typename V::SizeType size, V& vec)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());

		for (typename V::SizeType i = 0; i < size; i++) {
			BOOST_CHECK_EQUAL(vec[i], vec(i));
			BOOST_CHECK_EQUAL(vec.getData()[i], vec[i]);

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), vec(i));
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], vec[i]);
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec).getData()[i], vec[i]);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}

	template <typename V>
	void checkUnitVector(typename V::SizeType size, typename V::SizeType idx, V& vec)
	{
		using namespace CDPL;

		BOOST_CHECK_EQUAL(vec.getSize(), size);
		BOOST_CHECK(!vec.isEmpty());
		BOOST_CHECK_EQUAL(vec.getIndex(), idx);

		typedef typename V::ValueType ValueType;

		for (typename V::SizeType i = 0; i < size; i++) {
			if (i == idx) {
				BOOST_CHECK_EQUAL(vec(i), ValueType(1));
				BOOST_CHECK_EQUAL(vec[i], ValueType(1));
			} else {
				BOOST_CHECK_EQUAL(vec(i), ValueType());
				BOOST_CHECK_EQUAL(vec[i], ValueType());
			}

			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)(i), vec(i));
			BOOST_CHECK_EQUAL(const_cast<const V&>(vec)[i], vec[i]);
		}

		BOOST_CHECK_THROW(vec(size), Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)(size), Base::IndexError);

		BOOST_CHECK_THROW(vec[size], Base::IndexError);
		BOOST_CHECK_THROW(const_cast<const V&>(vec)[size], Base::IndexError);
	}
}


BOOST_AUTO_TEST_CASE(VectorTest)
{
	using namespace CDPL;
	using namespace Math;

	Vector<double> v1;

	// ---------

	BOOST_CHECK_EQUAL(v1.getMaxSize(), v1.getData().max_size());

	// ---------

	checkEmpty1(v1);

	// ---------

	v1.resize(4, 2.2);

	checkValues1(4, v1, 2.2);

	// ---------

	v1[0] = 2.0;
	v1(3) = 3.0;
	v1.getData()[2] = -1.0;

	double values1[] = { 2.0, 2.2, -1.0, 3.0 };

	checkValues1(4, v1, values1);

	// ---------

	Vector<double> v2(v1);

	checkValues1(4, v2, values1);

	// ---------

	Vector<double> v3(v1.getData());

	checkValues1(4, v3, values1);

	// ---------

	Vector<double> v4(4);

	checkValues1(4, v4, 0.0);

	// ---------

	Vector<double> v5(4, 2.2);

	checkValues1(4, v5, 2.2);

	// ---------

	Vector<double> v6(static_cast<const VectorExpression<Vector<double> >&>(v1));

	checkValues1(4, v6, values1);

	// ---------

	double values2[] = { 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 };

	Vector<double> v7;

	checkEmpty1(v7);

	v7.resize(1, 2.0);

	checkValues1(1, v7, values2);

	v7.resize(2, -1.2);

	checkValues1(2, v7, values2);

	v7.resize(3, 5.0);

	checkValues1(3, v7, values2);

	v7.resize(5);

	checkValues1(5, v7, values2);

	v7.resize(6, 1.0);

	checkValues1(6, v7, values2);

	v7.resize(3, -1.0);

	checkValues1(3, v7, values2);

	v7.resize(1, 1.95);

	checkValues1(1, v7, values2);

	v7.resize(0);

	checkEmpty1(v7);

	v7.resize(1, 2.0);

	checkValues1(1, v7, values2);

	v7.resize(6, 1.0);

	for (std::size_t i = 1; i < 6; i++)
		values2[i] = 1.0;

	checkValues1(6, v7, values2);

	// ---------

	v7.clear();

	checkValues1(6, v7, 0.0);

	v7.clear(2.0);

	checkValues1(6, v7, 2.0);

	Vector<double> v8;

	checkEmpty1(v8);

	v8.clear();

	checkEmpty1(v8);

	v8.clear(-2);

	checkEmpty1(v8);

	// ---------

	BOOST_CHECK(&(v1 *= -2.0) == &v1);

	double values3[] = { 2.0 * -2.0, 2.2 * -2.0, -1.0 * -2.0, 3.0 * -2.0 };

	checkValues1(4, v1, values3);

	// ---------

	BOOST_CHECK(&(v1 /= -2.0) == &v1);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<Vector<double> >&>(v1)) == &v1);

	double values4[] = { 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0 };

	checkValues1(4, v1, values4);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorContainer<Vector<double> >&>(v7), Base::SizeError);

	checkValues1(4, v1, values4);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues1(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<Vector<double> >&>(v2)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorContainer<Vector<double> >&>(v7), Base::SizeError);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<Vector<double> >&>(v2)) == &v1);

	checkValues1(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<Vector<double> >&>(v1)) == &v1);

	checkValues1(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<Vector<double> >&>(v2)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorExpression<Vector<double> >&>(v7), Base::SizeError);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorExpression<Vector<int> >&>(Vector<int>()), Base::SizeError);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<Vector<double> >&>(v1)) == &v1);

	checkValues1(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<Vector<double> >&>(v2)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorExpression<Vector<double> >&>(v7), Base::SizeError);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorExpression<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<Vector<double> >&>(v1)) == &v1);

	checkValues1(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v2) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(v7), Base::SizeError);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(Vector<float>()), Base::SizeError);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v1) == &v1);

	checkValues1(4, v1, values4);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v2) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(v7), Base::SizeError);

	checkValues1(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(Vector<int>()), Base::SizeError);

	checkValues1(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v1) == &v1);

	checkValues1(4, v1, 0.0);

	// ---------

	// checkValues1(4, v2, values1);
	// checkValues1(4, v3, values1);
	// checkValues1(4, v4, 0.0);
	// checkValues1(4, v5, 2.2);
	// checkValues1(4, v6, values1);

	// ---------

	for (Vector<double>::SizeType i = 0; i < 6; i++)
		v7(i) = values2[i];

	v1.resize(2);

	checkValues1(2, v1, 0.0);

	BOOST_CHECK(&(v1 = v2) == &v1);

	checkValues1(4, v1, values1);
	
	v1.resize(0);

	checkEmpty1(v1);

	BOOST_CHECK(&(v1 = v5) == &v1);

	checkValues1(4, v1, 2.2);

	BOOST_CHECK(&(v1 = v7) == &v1);

	checkValues1(6, v1, values2);

	BOOST_CHECK(&(v1 = v1) == &v1);

	checkValues1(6, v1, values2);

	BOOST_CHECK(&(v1 = Vector<double>()) == &v1);

	checkEmpty1(v1);

	BOOST_CHECK(&(v1 = v7) == &v1);

	checkValues1(6, v1, values2);

	// ---------

	v1.resize(1);

	checkValues1(1, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(v5)) == &v1);

	checkValues1(4, v1, 2.2);

	v1.resize(0);

	checkEmpty1(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(v7)) == &v1);

	checkValues1(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(v6)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(v1)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<int> >&>(Vector<int>())) == &v1);

	checkEmpty1(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(v6)) == &v1);

	checkValues1(4, v1, values1);

	// ---------

	v1.resize(3);

	checkValues1(3, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(v5)) == &v1);

	checkValues1(4, v1, 2.2);

	v1.resize(0);

	checkEmpty1(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(v3)) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(v7)) == &v1);

	checkValues1(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(v1)) == &v1);

	checkValues1(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<long double> >&>(Vector<long double>())) == &v1);

	checkEmpty1(v1);
	
	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(v7)) == &v1);

	checkValues1(6, v1, values2);

	// ---------

	BOOST_CHECK(&v1.assign(v3) == &v1);

	checkValues1(4, v1, values1);

	v1.resize(0);

	checkEmpty1(v1);

	BOOST_CHECK(&v1.assign(v5) == &v1);

	checkValues1(4, v1, 2.2);

	BOOST_CHECK(&v1.assign(v6) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK(&v1.assign(v1) == &v1);

	checkValues1(4, v1, values1);

	BOOST_CHECK(&v1.assign(Vector<float>()) == &v1);

	checkEmpty1(v1);

	BOOST_CHECK(&v1.assign(v6) == &v1);

	checkValues1(4, v1, values1);

	// ---------
	
	swap(v1, v7);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);

	swap(v1, v7);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);

	swap(v7, v1);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);

	swap(v7, v1);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);

	v1.swap(v7);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);

	v1.swap(v7);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);

	v7.swap(v1);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);

	v7.swap(v1);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);

	v1.resize(0);

	checkEmpty1(v1);

	v1.swap(v7);

	checkEmpty1(v7);
	checkValues1(6, v1, values2);

	swap(v7, v7);

	checkEmpty1(v7);

	v7.swap(v7);

	checkEmpty1(v7);

	swap(v1, v1);

	checkValues1(6, v1, values2);

	v1.swap(v1);

	checkValues1(6, v1, values2);
}

BOOST_AUTO_TEST_CASE(BoundedVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	BoundedVector<double, 6> v1;

	// ---------

	BOOST_CHECK_EQUAL(v1.getMaxSize(), 6);
	BOOST_CHECK_EQUAL((BoundedVector<double, 0>().getMaxSize()), 0);
	BOOST_CHECK_EQUAL((BoundedVector<double, 4>::MaxSize), 4);

	// ---------

	checkEmpty2(v1);

	// ---------

	v1.resize(4, 2.2);

	checkValues2(4, v1, 2.2);

	// ---------

	v1[0] = 2.0;
	v1(3) = 3.0;
	v1.getData()[2] = -1.0;

	double values1[] = { 2.0, 2.2, -1.0, 3.0 };

	checkValues2(4, v1, values1);

	// ---------

	BoundedVector<double, 6> v2(v1);

	checkValues2(4, v2, values1);

	// ---------

	BoundedVector<double, 6> v3(4);

	checkSize(4, v3);

	// ---------

	BoundedVector<double, 6> v4(4, 2.2);

	checkValues2(4, v4, 2.2);

	// ---------

	BoundedVector<double, 6> v5(static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v1));

	checkValues2(4, v5, values1);

	// ---------

	BOOST_CHECK_THROW((BoundedVector<double, 6>(7)), Base::RangeError);
	BOOST_CHECK_THROW((BoundedVector<double, 6>(8, 1.2)), Base::RangeError);
	BOOST_CHECK_THROW((BoundedVector<double, 3>(v1)), Base::RangeError);

	// ---------

	double values2[] = { 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 };

	BoundedVector<double, 6> v6;

	checkEmpty2(v6);

	v6.resize(1, 2.0);

	checkValues2(1, v6, values2);

	v6.resize(2, -1.2);

	checkValues2(2, v6, values2);

	v6.resize(3, 5.0);

	checkValues2(3, v6, values2);

	v6.resize(5, 0.0);

	checkValues2(5, v6, values2);

	v6.resize(6, 1.0);

	checkValues2(6, v6, values2);

	v6.resize(0);

	checkEmpty2(v6);

	v6.resize(6);

	checkValues2(6, v6, values2);

	v6.resize(3, -1.0);

	checkValues2(3, v6, values2);

	v6.resize(1, 1.95);

	checkValues2(1, v6, values2);

	v6.resize(0);

	checkEmpty2(v6);

	v6.resize(1, 2.0);

	checkValues2(1, v6, values2);

	v6.resize(6, 1.0);

	for (std::size_t i = 1; i < 6; i++)
		values2[i] = 1.0;

	checkValues2(6, v6, values2);

	BOOST_CHECK_THROW(v6.resize(7), Base::RangeError);

	checkValues2(6, v6, values2);

	BOOST_CHECK_THROW(v1.resize(8, 2.37), Base::RangeError);

	checkValues2(4, v1, values1);

	// ---------

	v6.clear();

	checkValues2(6, v6, 0.0);

	v6.clear(2.0);

	checkValues2(6, v6, 2.0);

	BoundedVector<double, 6> v8;

	checkEmpty2(v8);

	v8.clear();

	checkEmpty2(v8);

	v8.clear(-2);

	checkEmpty2(v8);

	// ---------

	BOOST_CHECK(&(v1 *= -2.0) == &v1);

	double values3[] = { 2.0 * -2.0, 2.2 * -2.0, -1.0 * -2.0, 3.0 * -2.0 };

	checkValues2(4, v1, values3);

	// ---------

	BOOST_CHECK(&(v1 /= -2.0) == &v1);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v1)) == &v1);

	double values4[] = { 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0 };

	checkValues2(4, v1, values4);

	BOOST_CHECK_THROW((v1 += static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v6)), Base::SizeError);

	checkValues2(4, v1, values4);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 -= static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v6)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v2)) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v1)) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 += static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v6)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorExpression<Vector<int> >&>(Vector<int>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v1)) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 -= static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v6)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorExpression<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v1)) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v2) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(v6), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v1) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v2) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(v6), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(Vector<int>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v1) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	// checkValues2(4, v2, values1);
	// checkValues2(4, v3, 0.0);
	// checkValues2(4, v4, 2.2);
	// checkValues2(4, v5, values1);

	// ---------

	for (Vector<double>::SizeType i = 0; i < 6; i++)
		v6(i) = values2[i];

	v1.resize(2);

	checkSize(2, v1);

	BOOST_CHECK(&(v1 = v2) == &v1);

	checkValues2(4, v1, values1);
	
	v1.resize(0);

	checkEmpty2(v1);

	BOOST_CHECK(&(v1 = v4) == &v1);

	checkValues2(4, v1, 2.2);

	BOOST_CHECK(&(v1 = v6) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK(&(v1 = v1) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK(&(v1 = BoundedVector<double, 6>()) == &v1);

	checkEmpty2(v1);

	BOOST_CHECK(&(v1 = v6) == &v1);

	checkValues2(6, v1, values2);

	// ---------

	v1.resize(1);

	checkValues2(1, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v4)) == &v1);

	checkValues2(4, v1, 2.2);

	v1.resize(0);

	checkEmpty2(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v6)) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v5)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v1)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<int, 8> >&>(BoundedVector<int, 8>())) == &v1);

	checkEmpty2(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<BoundedVector<double, 6> >&>(v5)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 = static_cast<const VectorExpression<Vector<float> >&>(Vector<float>(7))), Base::RangeError);

	checkValues2(4, v1, values1);

	// ---------

	v1.resize(3);

	checkValues2(3, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v4)) == &v1);

	checkValues2(4, v1, 2.2);

	v1.resize(0);

	checkEmpty2(v1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v5)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v6)) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v1)) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<long double> >&>(Vector<long double>())) == &v1);

	checkEmpty2(v1);
	
	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<BoundedVector<double, 6> >&>(v6)) == &v1);

	checkValues2(6, v1, values2);

	BOOST_CHECK_THROW((v1 = static_cast<const VectorContainer<Vector<int> >&>(Vector<int>(30))), Base::RangeError);

	checkValues2(6, v1, values2);

	// ---------

	BOOST_CHECK(&v1.assign(v5) == &v1);

	checkValues2(4, v1, values1);

	v1.resize(0);

	checkEmpty2(v1);

	BOOST_CHECK(&v1.assign(v4) == &v1);

	checkValues2(4, v1, 2.2);

	BOOST_CHECK(&v1.assign(v5) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&v1.assign(v1) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&v1.assign(Vector<float>()) == &v1);

	checkEmpty2(v1);

	BOOST_CHECK(&v1.assign(v5) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.assign(BoundedVector<double, 7>(7)), Base::RangeError);

	checkValues2(4, v1, values1);

	// ---------
	
	swap(v1, v6);

	checkValues2(4, v6, values1);
	checkValues2(6, v1, values2);

	swap(v1, v6);

	checkValues2(6, v6, values2);
	checkValues2(4, v1, values1);

	swap(v6, v1);

	checkValues2(4, v6, values1);
	checkValues2(6, v1, values2);

	swap(v6, v1);

	checkValues2(6, v6, values2);
	checkValues2(4, v1, values1);

	v1.swap(v6);

	checkValues2(4, v6, values1);
	checkValues2(6, v1, values2);

	v1.swap(v6);

	checkValues2(6, v6, values2);
	checkValues2(4, v1, values1);

	v6.swap(v1);

	checkValues2(4, v6, values1);
	checkValues2(6, v1, values2);

	v6.swap(v1);

	checkValues2(6, v6, values2);
	checkValues2(4, v1, values1);

	v1.resize(0);

	checkEmpty2(v1);

	v1.swap(v6);

	checkEmpty2(v6);
	checkValues2(6, v1, values2);

	swap(v6, v6);

	checkEmpty2(v6);

	v6.swap(v6);

	checkEmpty2(v6);

	swap(v1, v1);

	checkValues2(6, v1, values2);

	v1.swap(v1);

	checkValues2(6, v1, values2);
}

BOOST_AUTO_TEST_CASE(CVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	CVector<double, 4> v1;

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK_EQUAL(v1.getMaxSize(), 4);
	BOOST_CHECK_EQUAL((CVector<double, 0>().getMaxSize()), 0);
	BOOST_CHECK_EQUAL((CVector<double, 0>().getSize()), 0);
	BOOST_CHECK_EQUAL((CVector<double, 6>::Size), 6);

	// ---------

	v1[0] = 2.0;
	v1(3) = 3.0;
	v1(1) = 2.2;
	v1.getData()[2] = -1.0;

	double values1[] = { 2.0, 2.2, -1.0, 3.0 };

	checkValues2(4, v1, values1);

	// ---------

	CVector<double, 4> v2(v1);

	checkValues2(4, v2, values1);

	// ---------

	CVector<double, 4> v3(2.2);

	checkValues2(4, v3, 2.2);

	// ---------

	CVector<double, 6> v4(ScalarVector<float>(6, -1.12f));

	checkValues2(6, v4, -1.12f);

	// ---------

	BOOST_CHECK_THROW((CVector<double, 3>(v1)), Base::SizeError);
	BOOST_CHECK_THROW((CVector<double, 0>(v1)), Base::SizeError);

	// ---------

	v4.clear();

	checkValues2(6, v4, 0.0);

	v4.clear(2.0);

	checkValues2(6, v4, 2.0);

	// ---------

	BOOST_CHECK(&(v1 *= -2.0) == &v1);

	double values3[] = { 2.0 * -2.0, 2.2 * -2.0, -1.0 * -2.0, 3.0 * -2.0 };

	checkValues2(4, v1, values3);

	// ---------

	BOOST_CHECK(&(v1 /= -2.0) == &v1);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<CVector<double, 4> >&>(v1)) == &v1);

	double values4[] = { 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0 };

	checkValues2(4, v1, values4);

	BOOST_CHECK_THROW((v1 += static_cast<const VectorContainer<CVector<double, 6> >&>(v4)), Base::SizeError);

	checkValues2(4, v1, values4);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 -= static_cast<const VectorContainer<CVector<double, 6> >&>(v4)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorContainer<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorContainer<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorContainer<CVector<double, 4> >&>(v1)) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 += static_cast<const VectorExpression<CVector<double, 6> >&>(v4)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 += static_cast<const VectorExpression<Vector<int> >&>(Vector<int>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 += static_cast<const VectorExpression<CVector<double, 4> >&>(v1)) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 -= static_cast<const VectorExpression<CVector<double, 6> >&>(v4)), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1 -= static_cast<const VectorExpression<Vector<float> >&>(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 -= static_cast<const VectorExpression<CVector<double, 4> >&>(v1)) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v2) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(v4), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.plusAssign(Vector<float>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.plusAssign(v1) == &v1);

	checkValues2(4, v1, values4);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v2) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(v4), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.minusAssign(Vector<int>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.minusAssign(v1) == &v1);

	checkValues2(4, v1, 0.0);

	// ---------

	BOOST_CHECK(&(v1 = v2) == &v1);

	checkValues2(4, v1, values1);
	
	// ---------

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<Vector<double> >&>(Vector<double>(4, 2.3))) == &v1);

	checkValues2(4, v1, 2.3);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorExpression<CVector<double, 4> >&>(v1)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 = static_cast<const VectorExpression<Vector<float> >&>(Vector<float>(7))), Base::SizeError);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 = static_cast<const VectorExpression<Vector<double> >&>(Vector<double>())), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<Vector<double> >&>(Vector<double>(4, 2.2))) == &v1);

	checkValues2(4, v1, 2.2);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<CVector<double, 4> >&>(v2)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&(v1 = static_cast<const VectorContainer<CVector<double, 4> >&>(v1)) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW((v1 = static_cast<const VectorContainer<Vector<int> >&>(Vector<int>(30))), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------

	BOOST_CHECK(&v1.assign(Vector<double>(4, -2.03)) == &v1);

	checkValues2(4, v1, -2.03);

	BOOST_CHECK(&v1.assign(v2) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK(&v1.assign(v1) == &v1);

	checkValues2(4, v1, values1);

	BOOST_CHECK_THROW(v1.assign(CVector<double, 7>()), Base::SizeError);

	checkValues2(4, v1, values1);

	// ---------
	
	v1.clear(7.0);

	checkValues2(4, v1, 7.0);

	swap(v1, v2);

	checkValues2(4, v2, 7.0);
	checkValues2(4, v1, values1);

	swap(v1, v2);

	checkValues2(4, v1, 7.0);
	checkValues2(4, v2, values1);

	swap(v2, v1);

	checkValues2(4, v2, 7.0);
	checkValues2(4, v1, values1);

	swap(v2, v1);

	checkValues2(4, v1, 7.0);
	checkValues2(4, v2, values1);

	v1.swap(v2);

	checkValues2(4, v2, 7.0);
	checkValues2(4, v1, values1);

	v1.swap(v2);

	checkValues2(4, v1, 7.0);
	checkValues2(4, v2, values1);

	v2.swap(v1);

	checkValues2(4, v2, 7.0);
	checkValues2(4, v1, values1);

	v2.swap(v1);

	checkValues2(4, v1, 7.0);
	checkValues2(4, v2, values1);

	// --

	v1.swap(v1);

	checkValues2(4, v1, 7.0);

	swap(v1, v1);

	checkValues2(4, v1, 7.0);
}

BOOST_AUTO_TEST_CASE(ZeroVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	ZeroVector<float> v1;

	checkEmpty2(v1);

	BOOST_CHECK_EQUAL(v1.getMaxSize(), std::numeric_limits<ZeroVector<float>::SizeType>::max());

	// ---------

	ZeroVector<float> v2(13);

	checkValues3(13, v2, 0);

	// ---------

	ZeroVector<float> v3(v2);

	checkValues3(13, v3, 0);

	// ---------

	ZeroVector<float> v4(0);

	checkEmpty2(v4);

	// ---------

	v1 = v1;

	checkEmpty2(v1);

	v1 = v2;

	checkValues3(13, v1, 0);

	v1 = v1;

	checkValues3(13, v1, 0);
	
	// ---------

	v1.resize(7);

	checkValues3(7, v1, 0);

	v1.resize(0);

	checkEmpty2(v1);

	// ---------

	v1.swap(v3);

	checkValues3(13, v1, 0);
	checkEmpty2(v3);

	v1.swap(v3);

	checkValues3(13, v3, 0);
	checkEmpty2(v1);

	v3.swap(v1);

	checkValues3(13, v1, 0);
	checkEmpty2(v3);

	v3.swap(v1);

	checkValues3(13, v3, 0);
	checkEmpty2(v1);
	
	swap(v1, v3);

	checkValues3(13, v1, 0);
	checkEmpty2(v3);

	swap(v1, v3);

	checkValues3(13, v3, 0);
	checkEmpty2(v1);

	swap(v3, v1);

	checkValues3(13, v1, 0);
	checkEmpty2(v3);

	swap(v3, v1);

	checkValues3(13, v3, 0);
	checkEmpty2(v1);

	v1.resize(5);

	checkValues3(5, v1, 0);

	v1.swap(v3);

	checkValues3(13, v1, 0);
	checkValues3(5, v3, 0);

	swap(v3, v1);

	checkValues3(13, v3, 0);
	checkValues3(5, v1, 0);

	// ----

	v1.swap(v1);

	checkValues3(5, v1, 0);

	swap(v1, v1);

	checkValues3(5, v1, 0);
}

BOOST_AUTO_TEST_CASE(UnitVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	UnitVector<double> v1;

	checkEmpty2(v1);

	BOOST_CHECK_EQUAL(v1.getMaxSize(), std::numeric_limits<UnitVector<double>::SizeType>::max());
	BOOST_CHECK_EQUAL(v1.getIndex(), 0);

	// ---------

	UnitVector<double> v2(13, 1);

	checkUnitVector(13, 1, v2);

	// ---------

	UnitVector<double> v3(v2);

	checkUnitVector(13, 1, v3);

	// ---------

	UnitVector<double> v4(0, 10);

	checkEmpty2(v4);

	BOOST_CHECK_EQUAL(v4.getIndex(), 10);

	// ---------

	UnitVector<double> v5(5, 6);

	checkUnitVector(5, 6, v5);

	// ---------

	v1 = v1;

	checkEmpty2(v1);

	v1 = v2;

	checkUnitVector(13, 1, v1);
	checkUnitVector(13, 1, v2);

	v1 = v1;

	checkUnitVector(13, 1, v1);

	v1 = v3;
	
	checkUnitVector(13, 1, v1);

	// ---------

	v1.resize(7);

	checkUnitVector(7, 1, v1);

	v1.resize(0);

	checkEmpty2(v1);

	v1.resize(3);

	checkUnitVector(3, 1, v1);

	// ---------

	v5.resize(0);
	BOOST_CHECK_EQUAL(v5.getIndex(), 6);

	checkEmpty2(v5);

	v1.swap(v5);

	checkUnitVector(3, 1, v5);
	checkEmpty2(v1);
	BOOST_CHECK_EQUAL(v1.getIndex(), 6);

	v1.swap(v5);

	checkUnitVector(3, 1, v1);
	checkEmpty2(v5);
	BOOST_CHECK_EQUAL(v5.getIndex(), 6);

	v5.swap(v1);

	checkUnitVector(3, 1, v5);
	checkEmpty2(v1);
	BOOST_CHECK_EQUAL(v1.getIndex(), 6);

	v5.swap(v1);

	checkUnitVector(3, 1, v1);
	checkEmpty2(v5);
	BOOST_CHECK_EQUAL(v5.getIndex(), 6);

	swap(v1, v5);

	checkUnitVector(3, 1, v5);
	checkEmpty2(v1);
	BOOST_CHECK_EQUAL(v1.getIndex(), 6);
	
	swap(v1, v5);

	checkUnitVector(3, 1, v1);
	checkEmpty2(v5);
	BOOST_CHECK_EQUAL(v5.getIndex(), 6);

	swap(v5, v1);

	checkUnitVector(3, 1, v5);
	checkEmpty2(v1);
	BOOST_CHECK_EQUAL(v1.getIndex(), 6);

	swap(v5, v1);

	checkUnitVector(3, 1, v1);
	checkEmpty2(v5);
	BOOST_CHECK_EQUAL(v5.getIndex(), 6);

	// --

	v5 = UnitVector<double>(6, 0);

	checkUnitVector(6, 0, v5);

	v1.swap(v5);

	checkUnitVector(3, 1, v5);
	checkUnitVector(6, 0, v1);

	v1.swap(v5);

	checkUnitVector(3, 1, v1);
	checkUnitVector(6, 0, v5);

	v5.swap(v1);

	checkUnitVector(3, 1, v5);
	checkUnitVector(6, 0, v1);

	v5.swap(v1);

	checkUnitVector(3, 1, v1);
	checkUnitVector(6, 0, v5);

	swap(v1, v5);

	checkUnitVector(3, 1, v5);
	checkUnitVector(6, 0, v1);

	swap(v1, v5);

	checkUnitVector(3, 1, v1);
	checkUnitVector(6, 0, v5);

	swap(v5, v1);

	checkUnitVector(3, 1, v5);
	checkUnitVector(6, 0, v1);

	swap(v5, v1);

	checkUnitVector(3, 1, v1);
	checkUnitVector(6, 0, v5);

	// --

	v1.swap(v1);

	checkUnitVector(3, 1, v1);

	swap(v1, v1);

	checkUnitVector(3, 1, v1);

	v1.resize(0);
	BOOST_CHECK_EQUAL(v1.getIndex(), 1);

	v1.swap(v1);

	checkEmpty2(v1);

	swap(v1, v1);

	checkEmpty2(v1);
}

BOOST_AUTO_TEST_CASE(ScalarVectorTest)
{
	using namespace CDPL;
	using namespace Math;

	ScalarVector<double> v1;

	checkEmpty2(v1);

	BOOST_CHECK_EQUAL(v1.getMaxSize(), std::numeric_limits<ScalarVector<double>::SizeType>::max());

	// ---------

	ScalarVector<double> v2(13, -1.372);

	checkValues3(13, v2, -1.372);

	// ---------

	ScalarVector<double> v3(v2);

	checkValues3(13, v3, -1.372);

	// ---------

	ScalarVector<double> v4(10);

	checkValues3(10, v4, 0);

	// ---------

	ScalarVector<double> v5(0, 1.2);

	checkEmpty2(v5);

	// ---------

	v1 = v1;

	checkEmpty2(v1);

	v1 = v2;

	checkValues3(13, v1, -1.372);
	checkValues3(13, v2, -1.372);

	v1 = v1;

	checkValues3(13, v1, -1.372);
	
	// ---------

	v1.resize(7);

	checkValues3(7, v1, -1.372);

	v1.resize(0);

	checkEmpty2(v1);

	v1.resize(3);

	checkValues3(3, v1, -1.372);

	// ---------

	v1.swap(v5);

	checkValues3(3, v5, -1.372);
	checkEmpty2(v1);

	v1.swap(v5);

	checkValues3(3, v1, -1.372);
	checkEmpty2(v5);

	v5.swap(v1);

	checkValues3(3, v5, -1.372);
	checkEmpty2(v1);

	v5.swap(v1);

	checkValues3(3, v1, -1.372);
	checkEmpty2(v5);

	swap(v1, v5);

	checkValues3(3, v5, -1.372);
	checkEmpty2(v1);

	swap(v1, v5);

	checkValues3(3, v1, -1.372);
	checkEmpty2(v5);

	swap(v5, v1);

	checkValues3(3, v5, -1.372);
	checkEmpty2(v1);

	swap(v5, v1);

	checkValues3(3, v1, -1.372);
	checkEmpty2(v5);

	// --

	v5.resize(6);

	checkValues3(6, v5, 1.2);

	v1.swap(v5);

	checkValues3(3, v5, -1.372);
	checkValues3(6, v1, 1.2);

	v1.swap(v5);

	checkValues3(3, v1, -1.372);
	checkValues3(6, v5, 1.2);

	v5.swap(v1);

	checkValues3(3, v5, -1.372);
	checkValues3(6, v1, 1.2);

	v5.swap(v1);

	checkValues3(3, v1, -1.372);
	checkValues3(6, v5, 1.2);

	swap(v1, v5);

	checkValues3(3, v5, -1.372);
	checkValues3(6, v1, 1.2);

	swap(v1, v5);

	checkValues3(3, v1, -1.372);
	checkValues3(6, v5, 1.2);

	swap(v5, v1);

	checkValues3(3, v5, -1.372);
	checkValues3(6, v1, 1.2);

	swap(v5, v1);

	checkValues3(3, v1, -1.372);
	checkValues3(6, v5, 1.2);

	// --

	v1.swap(v1);

	checkValues3(3, v1, -1.372);

	swap(v1, v1);

	checkValues3(3, v1, -1.372);
}

BOOST_AUTO_TEST_CASE(VectorReferenceTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK(typeid(Vector<double>) == typeid(VectorReference<Vector<double> >::VectorType));
	BOOST_CHECK(typeid(Vector<double>::ValueType) == typeid(VectorReference<Vector<double> >::ValueType));
	BOOST_CHECK(typeid(Vector<double>::SizeType) == typeid(VectorReference<Vector<double> >::SizeType));
	BOOST_CHECK(typeid(Vector<double>::DifferenceType) == typeid(VectorReference<Vector<double> >::DifferenceType));
	BOOST_CHECK(typeid(Vector<double>::Reference) == typeid(VectorReference<Vector<double> >::Reference));
	BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorReference<Vector<double> >::ConstReference));
	BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorReference<const Vector<double> >::Reference));
	BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorReference<const Vector<double> >::ConstReference));

	// ---------

	Vector<double> v1;
	VectorReference<Vector<double> > v1_ref(v1);

	// ---------

	BOOST_CHECK_EQUAL(v1_ref.getMaxSize(), v1.getData().max_size());
	BOOST_CHECK(&v1_ref.getData() == &v1);
	BOOST_CHECK(&const_cast<const VectorReference<Vector<double> >&>(v1_ref).getData() == &v1);

	// ---------

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	// ---------

	v1_ref.getData().resize(4, 2.2);

	checkValues1(4, v1, 2.2);
	checkValues2(4, v1_ref, 2.2);

	// ---------

	v1_ref[0] = 2.0;
	v1_ref(3) = 3.0;
	v1_ref.getData().getData()[2] = -1.0;

	double values1[] = { 2.0, 2.2, -1.0, 3.0 };

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	Vector<double> v2(v1_ref);
	VectorReference<Vector<double> > v2_ref(v2);

	checkValues1(4, v2, values1);
	checkValues2(4, v2_ref, values1);

	// ---------

	Vector<double> v3(v1.getData());
	VectorReference<Vector<double> > v3_ref(v3);

	checkValues1(4, v3, values1);
	checkValues2(4, v3_ref, values1);

	// ---------

	Vector<double> v4(4);
	VectorReference<Vector<double> > v4_ref(v4);

	checkValues1(4, v4, 0.0);
	checkValues2(4, v4_ref, 0.0);

	// ---------

	Vector<double> v5(4, 2.2);
	VectorReference<const Vector<double> > v5_ref(v5);

	checkValues1(4, v5, 2.2);
	checkValues2(4, v5_ref, 2.2);

	// ---------

	Vector<double> v6(static_cast<const VectorExpression<Vector<double> >&>(v1));
	VectorReference<const Vector<double> > v6_ref(v6);

	checkValues1(4, v6, values1);
	checkValues2(4, v6_ref, values1);

	// ---------

	double values2[] = { 2.0, -1.2, 5.0, 0.0, 0.0, 1.0 };

	Vector<double> v7;
	VectorReference<Vector<double> > v7_ref(v7);

	checkEmpty1(v7);
	checkEmpty2(v7_ref);

	v7_ref.getData().resize(1, 2.0);

	checkValues1(1, v7, values2);
	checkValues2(1, v7_ref, values2);

	v7.resize(2, -1.2);

	checkValues1(2, v7, values2);
	checkValues2(2, v7_ref, values2);

	v7_ref.getData().resize(3, 5.0);

	checkValues1(3, v7, values2);
	checkValues2(3, v7_ref, values2);

	v7.resize(5);

	checkValues1(5, v7, values2);
	checkValues2(5, v7_ref, values2);

	v7_ref.getData().resize(6, 1.0);

	checkValues1(6, v7, values2);
	checkValues2(6, v7_ref, values2);

	v7.resize(3, -1.0);

	checkValues1(3, v7, values2);
	checkValues2(3, v7_ref, values2);

	v7_ref.getData().resize(1, 1.95);

	checkValues1(1, v7, values2);
	checkValues2(1, v7_ref, values2);

	v7.resize(0);

	checkEmpty1(v7);
	checkEmpty2(v7);

	v7_ref.getData().resize(1, 2.0);

	checkValues1(1, v7, values2);
	checkValues2(1, v7_ref, values2);

	v7.resize(6, 1.0);

	for (std::size_t i = 1; i < 6; i++)
		values2[i] = 1.0;

	checkValues1(6, v7, values2);
	checkValues2(6, v7_ref, values2);

	// ---------

	v7_ref.getData().clear();

	checkValues1(6, v7, 0.0);
	checkValues2(6, v7_ref, 0.0);

	v7_ref.getData().clear(2.0);

	checkValues1(6, v7, 2.0);
	checkValues2(6, v7_ref, 2.0);

	Vector<double> v8;
	VectorReference<Vector<double> > v8_ref(v8);

	checkEmpty1(v8);
	checkEmpty2(v8_ref);

	v8_ref.getData().clear();

	checkEmpty1(v8);
	checkEmpty2(v8_ref);

	v8_ref.getData().clear(-2);

	checkEmpty1(v8);
	checkEmpty2(v8_ref);

	// ---------

	BOOST_CHECK(&(v1_ref *= -2.0) == &v1_ref);

	double values3[] = { 2.0 * -2.0, 2.2 * -2.0, -1.0 * -2.0, 3.0 * -2.0 };

	checkValues1(4, v1, values3);
	checkValues2(4, v1_ref, values3);

	// ---------

	BOOST_CHECK(&(v1_ref /= -2.0) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&(v1_ref += v1_ref) == &v1_ref);

	double values4[] = { 2.0 + 2.0, 2.2 + 2.2, -1.0 - 1.0, 3.0 + 3.0 };

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	BOOST_CHECK_THROW(v1_ref += v7, Base::SizeError);

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	BOOST_CHECK_THROW(v1_ref += Vector<float>(), Base::SizeError);

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	// ---------

	BOOST_CHECK(&(v1_ref -= v2) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref -= v7, Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref -= Vector<float>(), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&(v1_ref += v2_ref) == &v1_ref);

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	// ---------

	BOOST_CHECK(&(v1_ref -= v1_ref) == &v1_ref);

	checkValues1(4, v1, 0.0);
	checkValues2(4, v1_ref, 0.0);

	// ---------

	BOOST_CHECK(&(v1_ref += v2_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref += v7, Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref += Vector<int>(), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&(v1_ref += v1) == &v1_ref);

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	// ---------

	BOOST_CHECK(&(v1_ref -= v2_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref -= v7, Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref -= Vector<float>(), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&(v1_ref -= v1_ref) == &v1_ref);

	checkValues1(4, v1, 0.0);
	checkValues2(4, v1_ref, 0.0);

	// ---------

	BOOST_CHECK(&v1_ref.plusAssign(v2_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref.plusAssign(v7_ref), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref.plusAssign(Vector<float>()), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&v1_ref.plusAssign(v1_ref) == &v1_ref);

	checkValues1(4, v1, values4);
	checkValues2(4, v1_ref, values4);

	// ---------

	BOOST_CHECK(&v1_ref.minusAssign(v2_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref.minusAssign(v7), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK_THROW(v1_ref.minusAssign(Vector<int>()), Base::SizeError);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------

	BOOST_CHECK(&v1_ref.minusAssign(v1) == &v1_ref);

	checkValues1(4, v1, 0.0);
	checkValues2(4, v1_ref, 0.0);

	// ---------

	for (Vector<double>::SizeType i = 0; i < 6; i++)
		v7(i) = values2[i];

	v1.resize(2);

	checkValues1(2, v1, 0.0);
	checkValues2(2, v1_ref, 0.0);

	BOOST_CHECK(&(v1_ref = v2_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);
	
	v1.resize(0);

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	BOOST_CHECK(&(v1_ref = v5) == &v1_ref);

	checkValues1(4, v1, 2.2);
	checkValues2(4, v1_ref, 2.2);

	BOOST_CHECK(&(v1_ref = v7) == &v1_ref);

	checkValues1(6, v1, values2);
	checkValues2(6, v1_ref, values2);

	BOOST_CHECK(&(v1_ref = v1_ref) == &v1_ref);

	checkValues1(6, v1, values2);
	checkValues2(6, v1_ref, values2);

	BOOST_CHECK(&(v1_ref = Vector<double>()) == &v1_ref);

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	BOOST_CHECK(&(v1 = v7) == &v1);

	checkValues1(6, v1, values2);
	checkValues2(6, v1_ref, values2);

	// ---------

	BOOST_CHECK(&v1_ref.assign(v3) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	v1.resize(0);

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	BOOST_CHECK(&v1_ref.assign(v5_ref) == &v1_ref);

	checkValues1(4, v1, 2.2);
	checkValues2(4, v1_ref, 2.2);

	BOOST_CHECK(&v1_ref.assign(v6) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK(&v1_ref.assign(v1_ref) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	BOOST_CHECK(&v1_ref.assign(Vector<float>()) == &v1_ref);

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	BOOST_CHECK(&v1_ref.assign(v6) == &v1_ref);

	checkValues1(4, v1, values1);
	checkValues2(4, v1_ref, values1);

	// ---------
	
	swap(v1_ref, v7_ref);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);
	checkValues2(4, v7_ref, values1);
	checkValues2(6, v1_ref, values2);

	swap(v1_ref, v7_ref);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);
	checkValues2(6, v7_ref, values2);
	checkValues2(4, v1_ref, values1);

	swap(v7_ref, v1_ref);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);
	checkValues2(4, v7_ref, values1);
	checkValues2(6, v1_ref, values2);

	swap(v7_ref, v1_ref);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);
	checkValues2(6, v7_ref, values2);
	checkValues2(4, v1_ref, values1);

	v1_ref.swap(v7_ref);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);
	checkValues2(4, v7_ref, values1);
	checkValues2(6, v1_ref, values2);

	v1_ref.swap(v7_ref);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);
	checkValues2(6, v7_ref, values2);
	checkValues2(4, v1_ref, values1);

	v7_ref.swap(v1_ref);

	checkValues1(4, v7, values1);
	checkValues1(6, v1, values2);
	checkValues2(4, v7_ref, values1);
	checkValues2(6, v1_ref, values2);

	v7_ref.swap(v1_ref);

	checkValues1(6, v7, values2);
	checkValues1(4, v1, values1);
	checkValues2(6, v7_ref, values2);
	checkValues2(4, v1_ref, values1);

	v1.resize(0);

	checkEmpty1(v1);
	checkEmpty2(v1_ref);

	v1_ref.swap(v7_ref);

	checkEmpty1(v7);
	checkValues1(6, v1, values2);
	checkEmpty2(v7_ref);
	checkValues2(6, v1_ref, values2);

	swap(v7_ref, v7_ref);

	checkEmpty1(v7);
	checkEmpty2(v7_ref);

	v7_ref.swap(v7_ref);

	checkEmpty1(v7);
	checkEmpty2(v7_ref);

	swap(v1_ref, v1_ref);

	checkValues1(6, v1, values2);
	checkValues2(6, v1_ref, values2);

	v1_ref.swap(v1_ref);

	checkValues1(6, v1, values2);
	checkValues2(6, v1_ref, values2);
}

BOOST_AUTO_TEST_CASE(VecFunctionTest)
{
	using namespace CDPL;
	using namespace Math;

	double values1[] = { -1.2f, 4, 2.26f, 1.44 };

	checkValues2<const CVector<double, 4> >(4, vec(-1.2f, 4, 2.26f, 1.44), values1);

	checkValues2<const CVector<float, 3> >(3, vec(-1.2f, 4, 2.26f), values1);

	checkValues2<const CVector<float, 2> >(2, vec(-1.2f, 4), values1);

	checkValues2<const CVector<double, 4> >(4, vec(-2.0f, int(-2), short(-2), -2.0), -2.0);

	checkValues2<const CVector<double, 3> >(3, vec(0, 0.0f, 0.0), 0);

	checkValues2<const CVector<int, 2> >(2, vec(1, 1), 1);

	Vector<double> v(vec(-1.2f, 4, 2.26f, 1.44));

	checkValues1(4, v, values1);

	v.resize(0);

	checkEmpty1(v);

	v = vec(-1.2f, 4, 2.26f);

	checkValues1(3, v, values1);

	v.resize(0);

	checkEmpty1(v);

	v.assign(vec(-1.2f, 4));

	checkValues1(2, v, values1);
}
