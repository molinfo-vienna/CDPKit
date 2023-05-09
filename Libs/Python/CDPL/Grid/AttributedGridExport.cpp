/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AttributedGridExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Grid/AttributedGrid.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AttributedGridVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    struct AttributedGridWrapper : CDPL::Grid::AttributedGrid, boost::python::wrapper<CDPL::Grid::AttributedGrid> 
    {
	
		typedef boost::shared_ptr<AttributedGridWrapper> SharedPointer;

		ATTRIBUTEDGRID_IMPL()

		PROPERTYCONTAINER_IMPL(AttributedGridWrapper)
    };
}


void CDPLPythonGrid::exportAttributedGrid()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<AttributedGridWrapper, AttributedGridWrapper::SharedPointer,
										 python::bases<Base::PropertyContainer>,
										 boost::noncopyable>("AttributedGrid", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonGrid::AttributedGridVirtualFunctionsVisitor())
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<AttributedGridWrapper>())
		.def(CDPLPythonGrid::AttributedGridSpecialFunctionsVisitor())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("numElements", &Grid::AttributedGrid::getNumElements);

    python::register_ptr_to_python<Grid::AttributedGrid::SharedPointer>();
}
