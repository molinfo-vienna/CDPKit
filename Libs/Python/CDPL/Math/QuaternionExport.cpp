/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QuaternionExport.cpp 
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

#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "QuaternionExpression.hpp"
#include "QuaternionVisitor.hpp"
#include "InitFunctionGeneratorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename QuaternionType>
	struct QuaternionExport
	{

		QuaternionExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename QuaternionType::ValueType ValueType;
		
			python::class_<QuaternionType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const QuaternionType&>((python::arg("self"), python::arg("q"))))
				.def(python::init<const ValueType&, const ValueType&, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("c1"), python::arg("c2") = ValueType(), 
						  python::arg("c3") = ValueType(), python::arg("c4") = ValueType())))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<QuaternionType>())
				.def(InitFunctionGeneratorVisitor<QuaternionType, ConstQuaternionExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<QuaternionType, ConstQuaternionExpression>("e"))
				.def(ConstQuaternionVisitor<QuaternionType>())
				.def(QuaternionAssignAndSwapVisitor<QuaternionType>())
				.def(QuaternionNDArrayInitVisitor<QuaternionType>())
				.def(QuaternionNDArrayAssignVisitor<QuaternionType>())
				.def(QuaternionVisitor<QuaternionType>());
		}
	};
}


void CDPLPythonMath::exportQuaternionTypes()
{
	using namespace CDPL;

	QuaternionExport<Math::FQuaternion>("FQuaternion");
	QuaternionExport<Math::DQuaternion>("DQuaternion");
	QuaternionExport<Math::LQuaternion>("LQuaternion");
	QuaternionExport<Math::ULQuaternion>("ULQuaternion");
}
