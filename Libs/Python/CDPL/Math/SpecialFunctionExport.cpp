/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorFunctionExport.cpp 
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


#include <boost/python.hpp>
#include <boost/math/special_functions/prime.hpp>

#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Base/IntegerTypes.hpp"

#include "FunctionExports.hpp"


namespace
{

	std::size_t prime(std::size_t i)
	{
		return boost::math::prime(i);
	}
}


void CDPLPythonMath::exportSpecialFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("prime", &prime, python::arg("i"));
	python::def("factorial", &Math::factorial<Base::uint64>, python::arg("n"));
	python::def("pythag", &Math::pythag<double>, (python::arg("a"), python::arg("b")));
	python::def("sign", &Math::sign<double, double>, (python::arg("a"), python::arg("b")));
	python::def("lnGamma", &Math::lnGamma<double>, python::arg("z"));
	python::def("gammaQ", &Math::gammaQ<double>, (python::arg("a"), python::arg("x")));
	python::def("generalizedBell", &Math::generalizedBell<double>, (python::arg("x"), python::arg("a"), 
																	python::arg("b"), python::arg("c")));
}
