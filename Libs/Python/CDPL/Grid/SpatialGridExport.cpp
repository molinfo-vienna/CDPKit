/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpatialGridExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Grid/SpatialGrid.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "AttributedGridVisitor.hpp"
#include "SpatialGridVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    template <typename GridType>
    struct SpatialGridWrapper : GridType, boost::python::wrapper<GridType> 
    {
	
		typedef boost::shared_ptr<SpatialGridWrapper> SharedPointer;
		typedef typename GridType::ValueType ValueType;
		typedef typename GridType::CoordinatesType CoordinatesType;

		ATTRIBUTEDGRID_IMPL()
		SPATIALGRID_IMPL()

		PROPERTYCONTAINER_IMPL(SpatialGridWrapper<GridType>)
    };

    template <typename GridType>
    struct SpatialGridExport
    {
		SpatialGridExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::scope scope = python::class_<SpatialGridWrapper<GridType>, typename SpatialGridWrapper<GridType>::SharedPointer,
												 python::bases<Grid::AttributedGrid>,
												 boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(CDPLPythonGrid::AttributedGridVirtualFunctionsVisitor())
				.def(CDPLPythonGrid::SpatialGridVirtualFunctionsVisitor<GridType>())
				.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<SpatialGridWrapper<GridType> >())
				.def(CDPLPythonGrid::AttributedGridSpecialFunctionsVisitor())
				.def(CDPLPythonGrid::SpatialGridSpecialFunctionsVisitor<GridType>())
				.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor());

			python::register_ptr_to_python<typename GridType::SharedPointer>();
		}
    };
}


void CDPLPythonGrid::exportSpatialGrid()
{
	using namespace CDPL;

    SpatialGridExport<Grid::FSpatialGrid>("FSpatialGrid");
    SpatialGridExport<Grid::DSpatialGrid>("DSpatialGrid");
}
