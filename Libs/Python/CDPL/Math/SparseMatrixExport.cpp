/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SparseMatrixExport.cpp 
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
	struct SparseMatrixExport
	{

		SparseMatrixExport(const char* name) {
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
					 (python::arg("self"), python::arg("m"), python::arg("n"), python::arg("preserve") = true))
				.def("clear", &MatrixType::clear, (python::arg("self"), python::arg("v") = ValueType()))
				.def("getNumElements", &MatrixType::getNumElements, python::arg("self"))
				.def("getDefaultValue", &getDefaultValue, python::arg("self"))
				.def("setDefaultValue", &setDefaultValue, (python::arg("self"), python::arg("d")))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MatrixType>())
				.def(InitFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<MatrixType, ConstMatrixExpression>("e"))
				.def(ConstMatrixVisitor<MatrixType>())
				.def(MatrixAssignAndSwapVisitor<MatrixType>())
				.def(MatrixVisitor<MatrixType>())
				.add_property("numElements", &MatrixType::getNumElements)
				.add_property("defValue", &getDefaultValue, &setDefaultValue);
		}

		static typename MatrixType::ValueType getDefaultValue(MatrixType& m) {
			return m.getDefaultValue();
		}

		static void setDefaultValue(MatrixType& m, const typename MatrixType::ValueType& d) {
			m.getDefaultValue() = d;
		}
	};
}       


void CDPLPythonMath::exportSparseMatrixTypes()
{
	using namespace CDPL;

	SparseMatrixExport<Math::SparseFMatrix>("SparseFMatrix");
	SparseMatrixExport<Math::SparseDMatrix>("SparseDMatrix");
	SparseMatrixExport<Math::SparseLMatrix>("SparseLMatrix");
	SparseMatrixExport<Math::SparseULMatrix>("SparseULMatrix");
}
