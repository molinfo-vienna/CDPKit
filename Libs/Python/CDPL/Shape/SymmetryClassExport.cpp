/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SymmetryClassExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Shape/SymmetryClass.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct SymmetryClass {};
}


void CDPLPythonShape::exportSymmetryClasses()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<SymmetryClass, boost::noncopyable>("SymmetryClass", python::no_init)
	.def_readonly("UNDEF", &Shape::SymmetryClass::UNDEF)
	.def_readonly("ASYMMETRIC", &Shape::SymmetryClass::ASYMMETRIC)
	.def_readonly("OBLATE", &Shape::SymmetryClass::OBLATE)
	.def_readonly("PROLATE", &Shape::SymmetryClass::PROLATE)
	.def_readonly("SPHERICAL", &Shape::SymmetryClass::SPHERICAL);
}
