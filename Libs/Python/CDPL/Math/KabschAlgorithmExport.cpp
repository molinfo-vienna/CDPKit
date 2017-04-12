/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * KabschAlgorithmExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/KabschAlgorithm.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "VectorExpression.hpp"
#include "MatrixExpression.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename T>
	struct KabschAlgorithmExport
	{

		typedef CDPL::Math::KabschAlgorithm<T> AlgoType;
		typedef typename CDPL::Math::KabschAlgorithm<T>::MatrixType MatrixType;

		KabschAlgorithmExport(const char* name) {
			using namespace boost;

			python::class_<AlgoType >(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const AlgoType&>((python::arg("self"), python::arg("algo"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<AlgoType >())
				.def("assign", CDPLPythonBase::copyAssOp(&AlgoType::operator=), (python::arg("self"), python::arg("algo")),
					 python::return_self<>())
				.def("getTransform", &AlgoType::getTransform, python::arg("self"), 
					 python::return_internal_reference<>())
				.def("align", &align<float>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.def("align", &align<double>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.def("align", &calcWeightedTransform<float>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), python::arg("weights"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.def("align", &calcWeightedTransform<double>, 
					 (python::arg("self"), python::arg("points"), python::arg("ref_points"), python::arg("weights"), 
					  python::arg("do_center") = true, python::arg("max_svd_iter") = 0))
				.add_property("transform", python::make_function(&AlgoType::getTransform, 
																 python::return_internal_reference<>()));
		}

		template <typename T1>
		static bool align(AlgoType& algo,  
								  const typename CDPLPythonMath::ConstMatrixExpression<T1>::SharedPointer& points,
								  const typename CDPLPythonMath::ConstMatrixExpression<T1>::SharedPointer& ref_points,
								  bool do_center, std::size_t max_svd_iter) {

			return algo.align(*points, *ref_points, do_center, max_svd_iter);
		}
	
		template <typename T1>
		static bool calcWeightedTransform(AlgoType& algo,  
										  const typename CDPLPythonMath::ConstMatrixExpression<T1>::SharedPointer& points,
										  const typename CDPLPythonMath::ConstMatrixExpression<T1>::SharedPointer& ref_points,
										  const typename CDPLPythonMath::ConstVectorExpression<T1>::SharedPointer& weights,
										  bool do_center, std::size_t max_svd_iter) {

			return algo.align(*points, *ref_points, *weights, do_center, max_svd_iter);
		}
	};
}


void CDPLPythonMath::exportKabschAlgorithmTypes()
{
	KabschAlgorithmExport<float>("FKabschAlgorithm");
	KabschAlgorithmExport<double>("DKabschAlgorithm");
}
