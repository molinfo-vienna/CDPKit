/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixExport.cpp 
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

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "InitFunctionGeneratorVisitor.hpp"
#include "AssignFunctionGeneratorVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename MatrixType>
	struct MatrixExport
	{

		MatrixExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::SizeType SizeType;
			typedef typename MatrixType::ValueType ValueType;

			python::class_<MatrixType, typename MatrixType::SharedPointer>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, SizeType>(
						 (python::arg("self"), python::arg("m"), python::arg("n"))))
				.def(python::init<SizeType, SizeType, const ValueType&>(
						 (python::arg("self"), python::arg("m"), python::arg("n"), python::arg("v"))))
				.def("resize", &MatrixType::resize, 
					 (python::arg("self"), python::arg("m"), python::arg("n"), python::arg("preserve") = true,
					  python::arg("v") = ValueType()))
				.def("clear", &MatrixType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(InitFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>())
				.def(MatrixVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct CMatrixExport
	{

		CMatrixExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::ValueType ValueType;
	
			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const ValueType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def("clear", &MatrixType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(InitFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>())
				.def(MatrixVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct TranslationExport
	{

		TranslationExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::ValueType ValueType;
			typedef typename MatrixType::SizeType SizeType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, const ValueType&, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("n"), python::arg("tx") = ValueType(), python::arg("ty") = ValueType(), 
						  python::arg("tz") = ValueType())))
				.def("set", &MatrixType::set,
					 (python::arg("self"), python::arg("tx") = ValueType(), python::arg("ty") = ValueType(), 
					  python::arg("tz") = ValueType()))
				.def("resize", &MatrixType::resize, python::arg("n"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct ScalingExport
	{

		ScalingExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::ValueType ValueType;
			typedef typename MatrixType::SizeType SizeType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, const ValueType&, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("n"), python::arg("sx") = ValueType(1), python::arg("sy") = ValueType(1), 
						  python::arg("sz") = ValueType(1))))
				.def("set", &MatrixType::set,
					 (python::arg("self"), python::arg("sx") = ValueType(1), python::arg("sy") = ValueType(1), 
					  python::arg("sz") = ValueType(1)))
				.def("resize", &MatrixType::resize, python::arg("n"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct RotationExport
	{

		RotationExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::ValueType ValueType;
			typedef typename MatrixType::SizeType SizeType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, const double&, const ValueType&, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("n"), python::arg("w"), python::arg("ux"), python::arg("uy"), python::arg("uz"))))
				.def("set", &MatrixType::template set<ValueType, ValueType, ValueType, ValueType>,
					 (python::arg("self"), python::arg("w"), python::arg("ux"), python::arg("uy"), python::arg("uz")))
				.def("resize", &MatrixType::resize, python::arg("n"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct ZeroMatrixExport
	{

		ZeroMatrixExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::SizeType SizeType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, SizeType>((python::arg("self"), python::arg("m"), python::arg("n"))))
				.def("resize", &MatrixType::resize, (python::arg("self"), python::arg("m"), python::arg("n")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct IdentityMatrixExport
	{

		IdentityMatrixExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::SizeType SizeType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, SizeType>((python::arg("self"), python::arg("m"), python::arg("n"))))
				.def("resize", &MatrixType::resize, (python::arg("self"), python::arg("m"), python::arg("n")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};

	template <typename MatrixType>
	struct ScalarMatrixExport
	{

		ScalarMatrixExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename MatrixType::SizeType SizeType;
			typedef typename MatrixType::ValueType ValueType;

			python::class_<MatrixType>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const MatrixType&>((python::arg("self"), python::arg("m"))))
				.def(python::init<SizeType, SizeType, const ValueType&>(
						 (python::arg("self"), python::arg("m"), python::arg("n"), python::arg("v") = ValueType())))
				.def("resize", &MatrixType::resize, (python::arg("self"), python::arg("m"), python::arg("n")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>());
		}
	};
}       


void CDPLPythonMath::exportMatrixTypes()
{
	using namespace CDPL;

	TranslationExport<Math::FTranslationMatrix>("FTranslationMatrix");
	TranslationExport<Math::DTranslationMatrix>("DTranslationMatrix");
	TranslationExport<Math::LTranslationMatrix>("LTranslationMatrix");
	TranslationExport<Math::ULTranslationMatrix>("ULTranslationMatrix");

	ScalingExport<Math::FScalingMatrix>("FScalingMatrix");
	ScalingExport<Math::DScalingMatrix>("DScalingMatrix");
	ScalingExport<Math::LScalingMatrix>("LScalingMatrix");
	ScalingExport<Math::ULScalingMatrix>("ULScalingMatrix");

	RotationExport<Math::FRotationMatrix>("FRotationMatrix");
	RotationExport<Math::DRotationMatrix>("DRotationMatrix");
	RotationExport<Math::LRotationMatrix>("LRotationMatrix");
	RotationExport<Math::ULRotationMatrix>("ULRotationMatrix");
	
	CMatrixExport<Math::Matrix2F>("Matrix2F");
	CMatrixExport<Math::Matrix2D>("Matrix2D");
	CMatrixExport<Math::Matrix2L>("Matrix2L");
	CMatrixExport<Math::Matrix2UL>("Matrix2UL");

	CMatrixExport<Math::Matrix3F>("Matrix3F");
	CMatrixExport<Math::Matrix3D>("Matrix3D");
	CMatrixExport<Math::Matrix3L>("Matrix3L");
	CMatrixExport<Math::Matrix3UL>("Matrix3UL");

	CMatrixExport<Math::Matrix4F>("Matrix4F");
	CMatrixExport<Math::Matrix4D>("Matrix4D");
	CMatrixExport<Math::Matrix4L>("Matrix4L");
	CMatrixExport<Math::Matrix4UL>("Matrix4UL");

	MatrixExport<Math::FMatrix>("FMatrix");
	MatrixExport<Math::DMatrix>("DMatrix");
	MatrixExport<Math::LMatrix>("LMatrix");
	MatrixExport<Math::ULMatrix>("ULMatrix");

	ZeroMatrixExport<Math::FZeroMatrix>("FZeroMatrix");
	ZeroMatrixExport<Math::DZeroMatrix>("DZeroMatrix");
	ZeroMatrixExport<Math::LZeroMatrix>("LZeroMatrix");
	ZeroMatrixExport<Math::ULZeroMatrix>("ULZeroMatrix");

	IdentityMatrixExport<Math::FIdentityMatrix>("FIdentityMatrix");
	IdentityMatrixExport<Math::DIdentityMatrix>("DIdentityMatrix");
	IdentityMatrixExport<Math::LIdentityMatrix>("LIdentityMatrix");
	IdentityMatrixExport<Math::ULIdentityMatrix>("ULIdentityMatrix");

	ScalarMatrixExport<Math::FScalarMatrix>("FScalarMatrix");
	ScalarMatrixExport<Math::DScalarMatrix>("DScalarMatrix");
	ScalarMatrixExport<Math::LScalarMatrix>("LScalarMatrix");
	ScalarMatrixExport<Math::ULScalarMatrix>("ULScalarMatrix");
}
