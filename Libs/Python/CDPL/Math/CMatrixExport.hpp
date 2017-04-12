/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CMatrixExport.hpp 
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


#ifndef CDPL_PYTHON_MATH_CMATRIXEXPORT_HPP
#define CDPL_PYTHON_MATH_CMATRIXEXPORT_HPP

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


namespace CDPLPythonMath
{

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
}       

#endif // CDPL_PYTHON_MATH_CMATRIXEXPORT_HPP
