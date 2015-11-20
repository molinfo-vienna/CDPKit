/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorExport.cpp 
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

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "InitFunctionGeneratorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename VectorType>
	struct VectorExport
	{

		VectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::ValueType ValueType;
			typedef typename VectorType::SizeType SizeType;
		
			python::class_<VectorType, typename VectorType::SharedPointer>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<SizeType>((python::arg("self"), python::arg("n"))))
				.def(python::init<SizeType, const ValueType&>((python::arg("self"), python::arg("n"), python::arg("v"))))
				.def("resize", &VectorType::resize, (python::arg("self"), python::arg("n"), python::arg("v") = ValueType()))
				.def("clear", &VectorType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(InitFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>())
				.def(VectorVisitor<VectorType>());
		}
	};

	template <typename VectorType>
	struct CVectorExport
	{

		CVectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::ValueType ValueType;
			
			python::class_<VectorType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<const ValueType&>((python::arg("self"), python::arg("v"))))
				.def("clear", &VectorType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(InitFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>())
				.def(VectorVisitor<VectorType>());
		}
	};

	template <typename VectorType>
	struct ScalarVectorExport
	{

		ScalarVectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::ValueType ValueType;
			typedef typename VectorType::SizeType SizeType;
		
			python::class_<VectorType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<SizeType, const ValueType&>((python::arg("self"), python::arg("n"), python::arg("v") = ValueType())))
				.def("resize", &VectorType::resize, (python::arg("self"), python::arg("n")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>());
		}
	};

	template <typename VectorType>
	struct ZeroVectorExport
	{

		ZeroVectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::SizeType SizeType;
		
			python::class_<VectorType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<SizeType>((python::arg("self"), python::arg("n"))))
				.def("resize", &VectorType::resize, (python::arg("self"), python::arg("n")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>());
		}
	};

	template <typename VectorType>
	struct UnitVectorExport
	{

		UnitVectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::SizeType SizeType;
		
			python::class_<VectorType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<SizeType, SizeType>((python::arg("self"), python::arg("n"), python::arg("i"))))
				.def("resize", &VectorType::resize, (python::arg("self"), python::arg("n")))
				.def("getIndex", &VectorType::getIndex)
				.add_property("index", &VectorType::getIndex)
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>());
		}
	};
}


void CDPLPythonMath::exportVectorTypes()
{
	using namespace CDPL;

	CVectorExport<Math::Vector2F>("Vector2F");
	CVectorExport<Math::Vector2D>("Vector2D");
	CVectorExport<Math::Vector2L>("Vector2L");
	CVectorExport<Math::Vector2UL>("Vector2UL");

	CVectorExport<Math::Vector3F>("Vector3F");
	CVectorExport<Math::Vector3D>("Vector3D");
	CVectorExport<Math::Vector3L>("Vector3L");
	CVectorExport<Math::Vector3UL>("Vector3UL");

	CVectorExport<Math::Vector4F>("Vector4F");
	CVectorExport<Math::Vector4D>("Vector4D");
	CVectorExport<Math::Vector4L>("Vector4L");
	CVectorExport<Math::Vector4UL>("Vector4UL");

	VectorExport<Math::FVector>("FVector");
	VectorExport<Math::DVector>("DVector");
	VectorExport<Math::LVector>("LVector");
	VectorExport<Math::ULVector>("ULVector");

	ScalarVectorExport<Math::FScalarVector>("FScalarVector");
	ScalarVectorExport<Math::DScalarVector>("DScalarVector");
	ScalarVectorExport<Math::LScalarVector>("LScalarVector");
	ScalarVectorExport<Math::ULScalarVector>("ULScalarVector");

	ZeroVectorExport<Math::FZeroVector>("FZeroVector");
	ZeroVectorExport<Math::DZeroVector>("DZeroVector");
	ZeroVectorExport<Math::LZeroVector>("LZeroVector");
	ZeroVectorExport<Math::ULZeroVector>("ULZeroVector");

	UnitVectorExport<Math::FUnitVector>("FUnitVector");
	UnitVectorExport<Math::DUnitVector>("DUnitVector");
	UnitVectorExport<Math::LUnitVector>("LUnitVector");
	UnitVectorExport<Math::ULUnitVector>("ULUnitVector");
}
