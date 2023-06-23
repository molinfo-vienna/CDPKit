/* 
 * ConstHomogenousCoordsAdapterExport.cpp 
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

#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/IO.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ExpressionAdapterWrapper.hpp"
#include "VectorExpression.hpp"
#include "VectorVisitor.hpp"
#include "WrappedDataVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename ExpressionType>
	struct ConstHomogenousCoordsAdapterExport
	{
	
		typedef CDPL::Math::HomogenousCoordsAdapter<const ExpressionType> HomogenousCoordsAdapterType;
		typedef CDPLPythonMath::ExpressionAdapterWrapper<ExpressionType, HomogenousCoordsAdapterType> HomogenousCoordsAdapterWrapper;
		typedef typename HomogenousCoordsAdapterWrapper::ExpressionPointerType ExpressionPointerType;
		typedef typename HomogenousCoordsAdapterWrapper::SharedPointer WrapperPointerType;

		ConstHomogenousCoordsAdapterExport(const char* name) {
			using namespace boost;
			using namespace CDPLPythonMath;
		
			python::class_<HomogenousCoordsAdapterWrapper, WrapperPointerType, boost::noncopyable>(name, python::no_init)
				.def(python::init<const HomogenousCoordsAdapterWrapper&>((python::arg("self"), python::arg("a"))))
				.def(python::init<const ExpressionPointerType&>((python::arg("self"), python::arg("e"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<HomogenousCoordsAdapterType>())
				.def(ConstVectorVisitor<HomogenousCoordsAdapterType>("a"))
				.def(WrappedDataVisitor<HomogenousCoordsAdapterWrapper>());

			python::def("homog", &homog, python::arg("e"));
		}

		static WrapperPointerType homog(const ExpressionPointerType& e) {
			return WrapperPointerType(new HomogenousCoordsAdapterWrapper(e));
		}
	};
}


void CDPLPythonMath::exportConstHomogenousCoordsAdapterTypes()
{
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<float> >("ConstFHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<double> >("ConstDHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<long> >("ConstLHomogenousCoordsAdapter");
	ConstHomogenousCoordsAdapterExport<ConstVectorExpression<unsigned long> >("ConstULHomogenousCoordsAdapter");
}
