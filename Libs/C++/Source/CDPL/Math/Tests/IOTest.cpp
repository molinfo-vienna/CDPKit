/* 
 * IOTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/IO.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Quaternion.hpp"


namespace
{

	struct ThrowingVectorExpression : public CDPL::Math::VectorExpression<ThrowingVectorExpression>
	{

		typedef std::size_t SizeType;
		typedef int ValueType;

		SizeType getSize() const {
			return 6;
		}

		ValueType operator()(SizeType i) const {
			if (i == 4)
				throw std::runtime_error("Test Exception");

			return i;
		}

		ValueType operator[](SizeType i) const {
			return (*this)(i);
		}
	};

	struct ThrowingMatrixExpression : public CDPL::Math::MatrixExpression<ThrowingMatrixExpression>
	{

		typedef std::size_t SizeType;
		typedef int ValueType;

		SizeType getSize1() const {
			return 6;
		}

		SizeType getSize2() const {
			return 3;
		}

		ValueType operator()(SizeType i, SizeType j) const {
			if (i == 4 && j == 2)
				throw std::runtime_error("Test Exception");

			return (i * 3 + j);
		}
	};

	struct ThrowingQuaternionExpression : public CDPL::Math::QuaternionExpression<ThrowingQuaternionExpression>
	{

		typedef int ValueType;

		ValueType getC1() const {
			return 1;
		}

		ValueType getC2() const {
			throw std::runtime_error("Test Exception");
			return 2;
		}

		ValueType getC3() const {
			return 3;
		}

		ValueType getC4() const {
			return 4;
		}
	};
}


BOOST_AUTO_TEST_CASE(VectorOutputTest)
{
	using namespace CDPL;
	using namespace Math;

	std::ostringstream oss;

	oss.imbue(std::locale::classic());
	oss.precision(4);
	oss.setf(std::ios::fixed, std::ios::floatfield);

	Vector<double> v1;

	BOOST_CHECK((oss << v1));
	BOOST_CHECK_EQUAL(oss.str(), "[0]()");

	v1.resize(4, 1.1234567);
	v1(2) = -2.1234567;

	oss.str(std::string());

	BOOST_CHECK((oss << v1));
	BOOST_CHECK_EQUAL(oss.str(), "[4](1.1235,1.1235,-2.1235,1.1235)");

	oss.precision(5);
	oss.setf(std::ios::scientific, std::ios::floatfield);
	oss.setf(std::ios::right, std::ios::adjustfield);
	oss.fill('X');
	oss.width(60);
	oss.str(std::string());

	BOOST_CHECK((oss << v1));
	BOOST_CHECK_EQUAL(oss.str(), "XXXXXXX[4](1.12346e+00,1.12346e+00,-2.12346e+00,1.12346e+00)");

	BOOST_CHECK_THROW((oss << ThrowingVectorExpression()), std::runtime_error);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "XXXXXXX[4](1.12346e+00,1.12346e+00,-2.12346e+00,1.12346e+00)");

	oss.clear();
	oss.exceptions(std::ostringstream::failbit | std::ostringstream::badbit);

	BOOST_CHECK(oss.good());

	BOOST_CHECK_THROW((oss << ThrowingVectorExpression()), std::exception);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "XXXXXXX[4](1.12346e+00,1.12346e+00,-2.12346e+00,1.12346e+00)");
}

BOOST_AUTO_TEST_CASE(MatrixOutputTest)
{
	using namespace CDPL;
	using namespace Math;

	std::ostringstream oss;

	oss.imbue(std::locale::classic());
	oss.precision(4);
	oss.setf(std::ios::fixed, std::ios::floatfield);

	Matrix<double> m1;

	BOOST_CHECK((oss << m1));
	BOOST_CHECK_EQUAL(oss.str(), "[0,0]()");

	m1.resize(3, 0);

	oss.str(std::string());

	BOOST_CHECK((oss << m1));
	BOOST_CHECK_EQUAL(oss.str(), "[3,0]()");

	m1.resize(0, 5);

	oss.str(std::string());

	BOOST_CHECK((oss << m1));
	BOOST_CHECK_EQUAL(oss.str(), "[0,5]()");

	m1.resize(4, 4, false, 1.1234567);
	m1(2, 3) = -2.1234567;

	oss.str(std::string());

	BOOST_CHECK((oss << m1));
	BOOST_CHECK_EQUAL(oss.str(), "[4,4]((1.1235,1.1235,1.1235,1.1235),(1.1235,1.1235,1.1235,1.1235),"
					  "(1.1235,1.1235,1.1235,-2.1235),(1.1235,1.1235,1.1235,1.1235))");

	oss.precision(2);
	oss.setf(std::ios::scientific, std::ios::floatfield);
	oss.setf(std::ios::right, std::ios::adjustfield);
	oss.fill('X');
	oss.width(170);
	oss.str(std::string());

	BOOST_CHECK((oss << m1));
	BOOST_CHECK_EQUAL(oss.str(), "XXXXXXXXXXX[4,4]((1.12e+00,1.12e+00,1.12e+00,1.12e+00),(1.12e+00,1.12e+00,1.12e+00,1.12e+00),"
					  "(1.12e+00,1.12e+00,1.12e+00,-2.12e+00),(1.12e+00,1.12e+00,1.12e+00,1.12e+00))");

	oss.str("Empty");

	BOOST_CHECK_THROW((oss << ThrowingMatrixExpression()), std::runtime_error);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "Empty");

	oss.clear();
	oss.exceptions(std::ostringstream::failbit | std::ostringstream::badbit);

	BOOST_CHECK(oss.good());

	BOOST_CHECK_THROW((oss << ThrowingMatrixExpression()), std::exception);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "Empty");
}

BOOST_AUTO_TEST_CASE(QuaternionOutputTest)
{
	using namespace CDPL;
	using namespace Math;

	std::ostringstream oss;

	oss.imbue(std::locale::classic());
	oss.precision(4);
	oss.setf(std::ios::fixed, std::ios::floatfield);

	Quaternion<double> q1(-1.234, 0.12345, 1.0, -7.77777777);

	BOOST_CHECK((oss << q1));
	BOOST_CHECK_EQUAL(oss.str(), "(-1.2340,0.1235,1.0000,-7.7778)");

	oss.precision(2);
	oss.setf(std::ios::scientific, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);
	oss.fill('Q');
	oss.width(60);
	oss.str(std::string());

	BOOST_CHECK((oss << q1));
	BOOST_CHECK_EQUAL(oss.str(), "(-1.23e+00,1.23e-01,1.00e+00,-7.78e+00)QQQQQQQQQQQQQQQQQQQQQ");

	BOOST_CHECK_THROW((oss << ThrowingQuaternionExpression()), std::runtime_error);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "(-1.23e+00,1.23e-01,1.00e+00,-7.78e+00)QQQQQQQQQQQQQQQQQQQQQ");

	oss.clear();
	oss.exceptions(std::ostringstream::failbit | std::ostringstream::badbit);

	BOOST_CHECK(oss.good());

	BOOST_CHECK_THROW((oss << ThrowingQuaternionExpression()), std::exception);
	BOOST_CHECK(oss.fail());
	BOOST_CHECK_EQUAL(oss.str(), "(-1.23e+00,1.23e-01,1.00e+00,-7.78e+00)QQQQQQQQQQQQQQQQQQQQQ");
}
