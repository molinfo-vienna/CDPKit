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


#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"

#include "Base/FunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonDescr::exportFunctionWrappers()
{
    using namespace boost;
    using namespace CDPL;

    CDPLPythonBase::Function2Export<double(const Util::BitSet&, const Util::BitSet&)>("DoubleBitSet2Functor");
    CDPLPythonBase::Function2Export<double(const Math::FVector&, const Math::FVector&)>("DoubleFVector2Functor");
    CDPLPythonBase::Function2Export<double(const Math::DVector&, const Math::DVector&)>("DoubleDVector2Functor");
    CDPLPythonBase::Function2Export<double(const Math::ULVector&, const Math::ULVector&)>("DoubleULVector2Functor");
    CDPLPythonBase::Function2Export<double(const Math::LVector&, const Math::LVector&)>("DoubleLVector2Functor");
}
