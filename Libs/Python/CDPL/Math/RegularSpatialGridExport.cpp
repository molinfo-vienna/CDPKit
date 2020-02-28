/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularSpatialGridExport.cpp 
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

#include "CDPL/Math/RegularSpatialGrid.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "GridExpression.hpp"
#include "GridVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "VectorExpression.hpp"
#include "ClassExports.hpp"


namespace
{

    template <typename GridType>
    struct RegularSpatialGridExport
    {

		RegularSpatialGridExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
			using namespace CDPL;

			typedef typename GridType::SizeType SizeType;
			typedef typename GridType::SSizeType SSizeType;
			typedef typename GridType::ValueType ValueType;
			typedef typename GridType::GridDataType GridDataType;
			typedef typename GridType::CoordinatesValueType CoordinatesValueType;
			typedef typename GridType::CoordinatesTransformType CoordinatesTransformType;

			python::class_<GridType, typename GridType::SharedPointer> cls(name, python::no_init);

			python::scope scope = cls;

			python::enum_<typename GridType::DataMode>("DataMode")
				.value("CELL", GridType::CELL)
				.value("POINT", GridType::POINT)
				.export_values();

			cls
				.def(python::init<const GridType&>((python::arg("self"), python::arg("grid"))))
				.def(python::init<const GridDataType&, const CoordinatesValueType&, const CoordinatesValueType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("data"), python::arg("xs"), python::arg("ys"), python::arg("zs"))))
				.def(python::init<const GridDataType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("data"), python::arg("s"))))
				.def(python::init<const CoordinatesValueType&, const CoordinatesValueType&, const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("xs"), python::arg("ys"), python::arg("zs"))))
				.def(python::init<const CoordinatesValueType&>(
						 (python::arg("self"), python::arg("s"))))
				.def("resize", &GridType::resize, 
					 (python::arg("self"), python::arg("m"), python::arg("n"), python::arg("o"), python::arg("preserve") = true,
					  python::arg("v") = ValueType()))
				.def("clear", &GridType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def("getDataMode", &GridType::getDataMode, python::arg("self"))
				.def("setDataMode", &GridType::setDataMode, (python::arg("self"), python::arg("mode")))
				.def("getXExtent", &GridType::getXExtent, python::arg("self"))
				.def("getYExtent", &GridType::getYExtent, python::arg("self"))
				.def("getZExtent", &GridType::getZExtent, python::arg("self"))
				.def("getXStepSize", &GridType::getXStepSize, python::arg("self"))
				.def("getYStepSize", &GridType::getYStepSize, python::arg("self"))
				.def("getZStepSize", &GridType::getZStepSize, python::arg("self"))
				.def("setXStepSize", &GridType::setXStepSize, (python::arg("self"), python::arg("xs")))
				.def("setYStepSize", &GridType::setYStepSize, (python::arg("self"), python::arg("ys")))
				.def("setZStepSize", &GridType::setZStepSize, (python::arg("self"), python::arg("zs")))
				.def("getData", static_cast<const GridDataType& (GridType::*)() const>(&GridType::getData), python::arg("self"), 
					 python::return_internal_reference<>())
				.def("setCoordinatesTransform", &GridType::template setCoordinatesTransform<CoordinatesTransformType>,
					 (python::arg("self"), python::arg("xform")))
				.def("getCoordinatesTransform", &GridType::getCoordinatesTransform, python::arg("self"), 
					 python::return_internal_reference<>())
				.def("getCoordinates", static_cast<void (GridType::*)(SSizeType, SSizeType, SSizeType, python::object&) const>(&GridType::template getCoordinates<python::object>), 
					 (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k"), python::arg("coords"))) 
				.def("getCoordinates", static_cast<void (GridType::*)(SizeType, python::object&) const>(&GridType::template getCoordinates<python::object>), 
					 (python::arg("self"), python::arg("i"), python::arg("coords"))) 
				.def("getLocalCoordinates", static_cast<void (GridType::*)(SSizeType, SSizeType, SSizeType, python::object&) const>(&GridType::template getLocalCoordinates<python::object>), 
					 (python::arg("self"), python::arg("i"), python::arg("j"), python::arg("k"), python::arg("coords"))) 
				.def("getLocalCoordinates", static_cast<void (GridType::*)(const Math::CVector<CoordinatesValueType, 3>&, python::object&) const>
					 (&GridType::template getLocalCoordinates<Math::CVector<CoordinatesValueType, 3>, python::object>), 
					 (python::arg("self"), python::arg("world_coords"), python::arg("local_coords"))) 
				.def("containsPoint", &GridType::template containsPoint<Math::Vector3F>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &containsPointExpr<float>, (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &GridType::template containsLocalPoint<Math::Vector3F>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &containsLocalPointExpr<float>, (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &GridType::template containsPoint<Math::Vector3D>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &containsPointExpr<double>, (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &GridType::template containsLocalPoint<Math::Vector3D>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &containsLocalPointExpr<double>, (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &GridType::template containsPoint<Math::Vector3L>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &containsPointExpr<long>, (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &GridType::template containsLocalPoint<Math::Vector3L>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &containsLocalPointExpr<long>, (python::arg("self"), python::arg("pos"))) 
					.def("containsPoint", &GridType::template containsPoint<Math::Vector3UL>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsPoint", &containsPointExpr<unsigned long>, (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &GridType::template containsLocalPoint<Math::Vector3UL>, 
					 (python::arg("self"), python::arg("pos"))) 
				.def("containsLocalPoint", &containsLocalPointExpr<unsigned long>, (python::arg("self"), python::arg("pos"))) 
				.def("getContainingCell", &GridType::template getContainingCell<Math::Vector3F, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &getContainingCellExpr<float>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &GridType::template getLocalContainingCell<Math::Vector3F, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &getLocalContainingCellExpr<float>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &GridType::template getContainingCell<Math::Vector3D, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &getContainingCellExpr<double>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &GridType::template getLocalContainingCell<Math::Vector3D, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &getLocalContainingCellExpr<double>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &GridType::template getContainingCell<Math::Vector3L, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &getContainingCellExpr<long>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &GridType::template getLocalContainingCell<Math::Vector3L, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &getLocalContainingCellExpr<long>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
					 .def("getContainingCell", &GridType::template getContainingCell<Math::Vector3UL, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getContainingCell", &getContainingCellExpr<unsigned long>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &GridType::template getLocalContainingCell<Math::Vector3UL, python::object>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.def("getLocalContainingCell", &getLocalContainingCellExpr<unsigned long>,
					 (python::arg("self"), python::arg("pos"), python::arg("indices")))
				.add_property("data", python::make_function(static_cast<const GridDataType& (GridType::*)() const>(&GridType::getData), 
															python::return_internal_reference<>()))
				.add_property("coordsTransform", python::make_function(&GridType::getCoordinatesTransform, python::return_internal_reference<>()), 
							  &GridType::template setCoordinatesTransform<CoordinatesTransformType>)
				.add_property("dataMode", &GridType::getDataMode, &GridType::setDataMode)
				.add_property("xStepSize", &GridType::getXStepSize, &GridType::setXStepSize)
				.add_property("yStepSize", &GridType::getYStepSize, &GridType::setYStepSize)
				.add_property("zStepSize", &GridType::getZStepSize, &GridType::setZStepSize)
				.add_property("xExtent", &GridType::getXExtent)
				.add_property("yExtent", &GridType::getYExtent)
				.add_property("zExtent", &GridType::getZExtent)
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GridType>())
				.def(AssignFunctionGeneratorVisitor<GridType, ConstGridExpression>("e"))
				.def(ConstGridVisitor<GridType>())
				.def(ConstGridContainerVisitor<GridType>())
				.def(GridAssignAndSwapVisitor<GridType>())
				.def(GridVisitor<GridType>())
				.def(GridContainerVisitor<GridType>());
		}

		template <typename T>
		static bool containsLocalPointExpr(GridType& grid, const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& pos) {
			return grid.containsLocalPoint(*pos);
		}

		template <typename T>
		static bool containsPointExpr(GridType& grid, const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& pos) {
			return grid.containsPoint(*pos);
		}

		template <typename T>
		static void getLocalContainingCellExpr(GridType& grid, const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& pos, 
											   boost::python::object& indices) {
			grid.getLocalContainingCell(*pos, indices);
		}

		template <typename T>
		static void getContainingCellExpr(GridType& grid, const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& pos, 
										  boost::python::object& indices) {
			grid.getContainingCell(*pos, indices);
		}
    };
}       


void CDPLPythonMath::exportRegularSpatialGridTypes()
{
    using namespace CDPL;

    RegularSpatialGridExport<Math::RegularSpatialGrid<float> >("FRegularSpatialGrid");
    RegularSpatialGridExport<Math::RegularSpatialGrid<double> >("DRegularSpatialGrid");
}
