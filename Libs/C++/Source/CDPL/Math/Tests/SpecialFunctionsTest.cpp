/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpecialFunctionsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/SpecialFunctions.hpp"


BOOST_AUTO_TEST_CASE(SpecialFunctionsTest)
{
	using namespace CDPL;
	using namespace Math;

	BOOST_CHECK_CLOSE(std::exp(lnGamma(1.0)), 1.0, 0.0001);                                // std::exp(lnGamma(1.0)) == 0! ?
	BOOST_CHECK_CLOSE(std::exp(lnGamma(2.0)), 1.0, 0.0001);                                // std::exp(lnGamma(2.0)) == 1! ?
	BOOST_CHECK_CLOSE(std::exp(lnGamma(8.0)), 2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0, 0.0001);  // std::exp(lnGamma(8.0)) == 7! ?

//----

	BOOST_CHECK(-0.0 == 0.0);
	BOOST_CHECK(0.0 == -0.0);

	BOOST_CHECK(sign(0, 0) == 0);
	BOOST_CHECK(sign(0.0, -0.0) == 0.0);
	BOOST_CHECK(sign(0.0, -7.0) == 0.0);
	BOOST_CHECK(sign(0, 10) == 0);

	BOOST_CHECK(sign(-0.0, 0.0) == 0.0);
	BOOST_CHECK(sign(-0.0, -0.0) == 0.0);
	BOOST_CHECK(sign(-0.0, -7.0) == 0.0);
	BOOST_CHECK(sign(-0.0, 10.0) == 0.0);

	BOOST_CHECK(sign(-5, 0) == 5);
	BOOST_CHECK(sign(-5.0, -0.0) == 5.0);
	BOOST_CHECK(sign(-5, -7) == -5);
	BOOST_CHECK(sign(-5, 10) == 5);

	BOOST_CHECK(sign(6, 0) == 6);
	BOOST_CHECK(sign(6.0, -0.0) == 6.0);
	BOOST_CHECK(sign(6, -7) == -6);
	BOOST_CHECK(sign(6, 10) == 6);

//----

	BOOST_CHECK_CLOSE(pythag(-4.0, -5.0), std::sqrt(16.0 + 25.0), 0.00001); 
	BOOST_CHECK_CLOSE(pythag(-4.0, 0.0), 4.0, 0.00001); 
	BOOST_CHECK_CLOSE(pythag(-4.0, 3.0), std::sqrt(16.0 + 9.0), 0.00001); 

	BOOST_CHECK_CLOSE(pythag(0.0, -5.0), 5.0, 0.00001); 
	BOOST_CHECK_SMALL(pythag(0.0, 0.0), 0.00001); 
	BOOST_CHECK_CLOSE(pythag(0.0, 3.0), 3.0, 0.00001); 

	BOOST_CHECK_CLOSE(pythag(7.0, -5.0), std::sqrt(49.0 + 25.0), 0.00001); 
	BOOST_CHECK_CLOSE(pythag(7.0, 0.0), 7.0, 0.00001); 
	BOOST_CHECK_CLOSE(pythag(7.0, 3.0), std::sqrt(49.0 + 9.0), 0.00001); 

//----

	BOOST_CHECK_SMALL(gammaQ(0.5, 10.0), 0.0001); 
	BOOST_CHECK_CLOSE(gammaQ(0.2, 0.0), 1.0, 0.00001); 

	BOOST_CHECK(std::isnan(gammaQ(0.2, -1.0)));
	BOOST_CHECK(std::isnan(gammaQ(0.0, 1.0)));
	BOOST_CHECK(std::isnan(gammaQ(0.0, -1.0)));
	BOOST_CHECK(std::isnan(gammaQ(-0.1, 1.0)));
	BOOST_CHECK(std::isnan(gammaQ(-0.1, -1.0)));

//----

	BOOST_CHECK(factorial<unsigned int>(0) == 1); 
	BOOST_CHECK(factorial<int>(1) == 1); 
	BOOST_CHECK(factorial<short>(2) == 2); 
	BOOST_CHECK(factorial<float>(3) == 6.0f); 
	BOOST_CHECK(factorial<double>(4) == 24.0); 
	BOOST_CHECK(factorial<std::size_t>(5) == 120); 
}
