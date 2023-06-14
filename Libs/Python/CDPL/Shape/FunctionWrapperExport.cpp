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


#include <cstddef>

#include "CDPL/Shape/AlignmentResult.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/FunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportFunctionWrappers()
{
	using namespace boost;
	using namespace CDPL;

	CDPLPythonBase::Function1Export<double(const Shape::AlignmentResult&)>("DoubleAlignmentResultFunctor");
	CDPLPythonBase::Function1Export<bool(std::size_t)>("BoolSizeTypeFunctor");

	CDPLPythonBase::Function2Export<bool(const Shape::AlignmentResult&, const Shape::AlignmentResult&)>("BoolAlignmentResult2Functor");
	CDPLPythonBase::Function2Export<bool(std::size_t, std::size_t)>("BoolSizeType2Functor");

	CDPLPythonBase::Function3Export<void(const Chem::MolecularGraph&, const Chem::MolecularGraph&, const Shape::AlignmentResult&)>("VoidMolecularGraph2AlignmentResultFunctor");
}
