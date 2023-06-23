/* 
 * RegularGridExport.cpp 
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

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/PropertyContainerVisitor.hpp"
#include "Math/GridVisitor.hpp"
#include "Math/GridExpression.hpp"
#include "Math/AssignFunctionGeneratorVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename GridType>
    struct RegularGridExport
    {
		RegularGridExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef typename GridType::ValueType ValueType;
			typedef typename GridType::CoordinatesValueType CoordinatesValueType;
			typedef typename GridType::GridDataType GridDataType;
			typedef Math::RegularSpatialGrid<ValueType, ValueType> MathGridType;
			typedef typename MathGridType::SSizeType SSizeType;

			python::class_<GridType, typename GridType::SharedPointer, python::bases<Grid::SpatialGrid<ValueType, ValueType>, MathGridType> >(name, python::no_init)
				.def(python::init<const GridType&>((python::arg("self"), python::arg("grid"))))
				.def(python::init<const GridDataType&, const CoordinatesValueType&, const CoordinatesValueType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("data"), python::arg("xs"), python::arg("ys"), python::arg("zs"))))
				.def(python::init<const GridDataType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("data"), python::arg("s"))))
				.def(python::init<const CoordinatesValueType&, const CoordinatesValueType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("xs"), python::arg("ys"), python::arg("zs"))))
				.def(python::init<const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("s"))))
				.def("getCoordinates", static_cast<void (GridType::*)(SSizeType, SSizeType, SSizeType, python::object&) const>(&GridType::template getCoordinates<python::object>), 
					 (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k"), python::arg("coords"))) 
				.def("getCoordinates", static_cast<void (GridType::*)(std::size_t, python::object&) const>(&GridType::template getCoordinates<python::object>), 
					 (python::arg("self"), python::arg("i"), python::arg("coords"))) 
				.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
				.def(CDPLPythonMath::AssignFunctionGeneratorVisitor<MathGridType, CDPLPythonMath::ConstGridExpression>("e"))
				.def(CDPLPythonMath::ConstGridVisitor<MathGridType>())
				.def(CDPLPythonMath::ConstGridContainerVisitor<MathGridType>())
				.def(CDPLPythonMath::GridAssignAndSwapVisitor<MathGridType>())
				.def(CDPLPythonMath::GridVisitor<MathGridType>())
				.def(CDPLPythonMath::GridNDArrayAssignVisitor<MathGridType, true>())
				.def(CDPLPythonMath::GridContainerVisitor<MathGridType>());
		}
    };
}


void CDPLPythonGrid::exportRegularGrid()
{
	using namespace CDPL;

    RegularGridExport<Grid::FRegularGrid>("FRegularGrid");
    RegularGridExport<Grid::DRegularGrid>("DRegularGrid");
}
