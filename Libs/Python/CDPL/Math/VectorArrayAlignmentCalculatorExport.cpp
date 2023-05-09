/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorArrayAlignmentCalculatorExport.cpp 
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

#include "CDPL/Math/VectorArrayAlignmentCalculator.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "VectorExpression.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename VA>
	struct VectorArrayAlignmentCalculatorExport
	{

		typedef VA VectorArrayType;
		typedef CDPL::Math::VectorArrayAlignmentCalculator<VA> CalculatorType;

		VectorArrayAlignmentCalculatorExport(const char* name) {
			using namespace boost;

			python::class_<CalculatorType >(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const CalculatorType&>((python::arg("self"), python::arg("algo"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<CalculatorType >())
				.def("assign", CDPLPythonBase::copyAssOp(&CalculatorType::operator=), (python::arg("self"), python::arg("algo")),
					 python::return_self<>())
				.def("getTransform", &CalculatorType::getTransform, python::arg("self"), 
					 python::return_internal_reference<>())
				.def("calculate", &calculate, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.def("calculate", &calculateWeighted<float>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), python::arg("weights"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.def("calculate", &calculateWeighted<double>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), python::arg("weights"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.add_property("transform", python::make_function(&CalculatorType::getTransform, 
																 python::return_internal_reference<>()));
		}

		static bool calculate(CalculatorType& calculator, const VectorArrayType& points, const VectorArrayType& ref_points,
							  bool do_center, std::size_t max_svd_iter) {

			return calculator.calculate(points, ref_points, do_center, max_svd_iter);
		}
	
		template <typename T>
		static bool calculateWeighted(CalculatorType& calculator, const VectorArrayType& points, const VectorArrayType& ref_points,
									  const typename CDPLPythonMath::ConstVectorExpression<T>::SharedPointer& weights,
									  bool do_center, std::size_t max_svd_iter) {

			return calculator.calculate(points, ref_points, *weights, do_center, max_svd_iter);
		}
	};
}


void CDPLPythonMath::exportVectorArrayAlignmentCalculatorTypes()
{
	using namespace CDPL;

	VectorArrayAlignmentCalculatorExport<Math::Vector2FArray>("Vector2FArrayAlignmentCalculator");
	VectorArrayAlignmentCalculatorExport<Math::Vector2DArray>("Vector2DArrayAlignmentCalculator");
	VectorArrayAlignmentCalculatorExport<Math::Vector3FArray>("Vector3FArrayAlignmentCalculator");
	VectorArrayAlignmentCalculatorExport<Math::Vector3DArray>("Vector3DArrayAlignmentCalculator");
}
