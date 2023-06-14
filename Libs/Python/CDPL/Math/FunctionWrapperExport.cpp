/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FunctionWrapperExport.cpp 
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


#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "Base/FunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonMath::exportFunctionWrappers()
{
	using namespace CDPL;
	using namespace Math;

	CDPLPythonBase::Function1Export<float(const FVector&)>("FloatFVectorFunctor");
	CDPLPythonBase::Function1Export<float(const Vector2FArray&)>("FloatVector2FArrayFunctor");
	CDPLPythonBase::Function1Export<float(const Vector3FArray&)>("FloatVector3FArrayFunctor");
	CDPLPythonBase::Function1Export<double(const DVector&)>("DoubleDVectorFunctor");
	CDPLPythonBase::Function1Export<double(const Vector2DArray&)>("DoubleVector2DArrayFunctor");
	CDPLPythonBase::Function1Export<double(const Vector3DArray&)>("DoubleVector3DArrayFunctor");

	CDPLPythonBase::Function2Export<float(const FVector&, const FVector&)>("FloatFVector2Functor");
	CDPLPythonBase::Function2Export<float(const Vector2FArray&, const Vector2FArray&)>("FloatVector2FArray2Functor");
	CDPLPythonBase::Function2Export<float(const Vector3FArray&, const Vector3FArray&)>("FloatVector3FArray2Functor");
	CDPLPythonBase::Function2Export<double(const DVector&, const DVector&)>("DoubleDVector2Functor");
	CDPLPythonBase::Function2Export<double(const Vector2DArray&, const Vector2DArray&)>("DoubleVector2DArray2Functor");
	CDPLPythonBase::Function2Export<double(const Vector3DArray&, const Vector3DArray&)>("DoubleVector3DArray2Functor");
}
