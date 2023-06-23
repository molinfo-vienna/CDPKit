/* 
 * TranslationMatrixExport.cpp 
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

#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "MatrixExpression.hpp"
#include "MatrixVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

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
}       


void CDPLPythonMath::exportTranslationMatrixTypes()
{
	using namespace CDPL;

	TranslationExport<Math::FTranslationMatrix>("FTranslationMatrix");
	TranslationExport<Math::DTranslationMatrix>("DTranslationMatrix");
	TranslationExport<Math::LTranslationMatrix>("LTranslationMatrix");
	TranslationExport<Math::ULTranslationMatrix>("ULTranslationMatrix");
}
