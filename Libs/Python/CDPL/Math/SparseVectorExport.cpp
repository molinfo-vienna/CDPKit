/* 
 * SparseVectorExport.cpp 
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
	struct SparseVectorExport
	{

		SparseVectorExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;

			typedef typename VectorType::SizeType SizeType;
		
			python::class_<VectorType, typename VectorType::SharedPointer>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const VectorType&>((python::arg("self"), python::arg("v"))))
				.def(python::init<SizeType>((python::arg("self"), python::arg("n"))))
				.def("resize", &VectorType::resize, (python::arg("self"), python::arg("n")))
				.def("clear", &VectorType::clear, python::arg("self"))
				.def("getNumElements", &VectorType::getNumElements, python::arg("self"))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VectorType>())
				.def(InitFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(AssignFunctionGeneratorVisitor<VectorType, ConstVectorExpression>("e"))
				.def(ConstVectorVisitor<VectorType>())
				.def(VectorAssignAndSwapVisitor<VectorType>())
				.def(VectorVisitor<VectorType>())
				.def(VectorNDArrayInitVisitor<VectorType, true>())
				.def(VectorNDArrayAssignVisitor<VectorType, true>())
				.add_property("numElements", &VectorType::getNumElements);
		}
	};
}


void CDPLPythonMath::exportSparseVectorTypes()
{
	using namespace CDPL;

	SparseVectorExport<Math::SparseFVector>("SparseFVector");
	SparseVectorExport<Math::SparseDVector>("SparseDVector");
	SparseVectorExport<Math::SparseLVector>("SparseLVector");
	SparseVectorExport<Math::SparseULVector>("SparseULVector");
}
