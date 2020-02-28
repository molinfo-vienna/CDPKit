/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConstVectorRangeExport.cpp 
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

#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionProxyWrapper.hpp"
#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstVectorRangeExport
	{
	
		typedef CDPL::Math::Range<std::size_t> RangeType;
		typedef CDPL::Math::VectorRange<const ExpressionType> VectorRangeType;
		typedef CDPLPythonMath::VectorExpressionProxyWrapper<ExpressionType, RangeType, VectorRangeType> VectorRangeWrapper;
		typedef typename VectorRangeWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename VectorRangeWrapper::SharedPointer WrapperPointerType;

		ConstVectorRangeExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<VectorRangeWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const VectorRangeWrapper&>((python::arg("self"), python::arg("r"))))
				.def(python::init<const ExpressionPointerType&, const RangeType&>((python::arg("self"), python::arg("e"), python::arg("r"))))
				.def("getStart", &VectorRangeType::getStart, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorRangeType>())
				.def(ConstVectorVisitor<VectorRangeType>("r"))
				.def(WrappedDataVisitor<VectorRangeWrapper>())
				.add_property("start", &VectorRangeType::getStart);

			python::def("range", &range1, (python::arg("e"), python::arg("r")));
			python::def("range", &range2, (python::arg("e"), python::arg("start"), python::arg("stop")));
		}

		static WrapperPointerType range1(const ExpressionPointerType& e, const RangeType& r) {
			return WrapperPointerType(new VectorRangeWrapper(e, r));
		}

		static WrapperPointerType range2(const ExpressionPointerType& e, std::size_t start, std::size_t stop) {
			return WrapperPointerType(new VectorRangeWrapper(e, RangeType(start, stop)));
		}
	};
}


void CDPLPythonMath::exportConstVectorRangeTypes()
{
	ConstVectorRangeExport<ConstVectorExpression<float> >("ConstFVectorRange");
	ConstVectorRangeExport<ConstVectorExpression<double> >("ConstDVectorRange");
	ConstVectorRangeExport<ConstVectorExpression<long> >("ConstLVectorRange");
	ConstVectorRangeExport<ConstVectorExpression<unsigned long> >("ConstULVectorRange");
}
