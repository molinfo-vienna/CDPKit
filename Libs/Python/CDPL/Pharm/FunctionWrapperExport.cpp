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


#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "Base/FunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportFunctionWrappers()
{
    using namespace boost;
    using namespace CDPL;
    using namespace Pharm;

    CDPLPythonBase::Function1Export<const Math::Vector3D&(const Feature&), Feature&, python::return_internal_reference<> >("Feature3DCoordinatesFunction");
       CDPLPythonBase::Function1Export<double(const ScreeningProcessor::SearchHit&) >("DoubleSearchHitFunctor");
    CDPLPythonBase::Function1Export<double(const Feature&), Feature&>("DoubleFeatureFunctor");
    CDPLPythonBase::Function1Export<bool(double), double, python::return_value_policy<python::return_by_value> >("BoolDoubleFunctor"); 
    CDPLPythonBase::Function1Export<double(double), double,    python::return_value_policy<python::return_by_value> >("DoubleDoubleFunctor"); 
    CDPLPythonBase::Function1Export<bool(const Feature&), Feature&>("BoolFeatureFunctor");

    CDPLPythonBase::Function2Export<bool(const Feature&, const Feature&), Feature&, Feature&>("BoolFeature2Functor");
    CDPLPythonBase::Function2Export<double(const Feature&, const Feature&), Feature&, Feature&>("DoubleFeature2Functor");
    CDPLPythonBase::Function2Export<bool(const ScreeningProcessor::SearchHit&, double),    const ScreeningProcessor::SearchHit&, double, python::return_value_policy<python::return_by_value> >("BoolSearchHitDoubleFunctor");
    CDPLPythonBase::Function2Export<bool(std::size_t, std::size_t), std::size_t, std::size_t, python::return_value_policy<python::return_by_value> >("BoolSizeType2Functor");
    CDPLPythonBase::Function2Export<double(double, double), double, double, python::return_value_policy<python::return_by_value> >("DoubleDouble2Functor");

    CDPLPythonBase::Function3Export<bool(const Feature&, const Feature&, const Math::Matrix4D&), Feature&, Feature&>("BoolFeature2Matrix4DFunctor");
    CDPLPythonBase::Function3Export<double(const Feature&, const Feature&, const Math::Matrix4D&), Feature&, Feature&>("DoubleFeature2Matrix4DFunctor");
    CDPLPythonBase::Function3Export<double(const Feature&, const Feature&, unsigned int), Feature&, Feature&>("DoubleFeature2UIntFunctor");     

    CDPLPythonBase::Function4Export<bool(const Feature&, const Feature&, const Feature&, const Feature&),Feature&, Feature&, Feature&, Feature&>("BoolFeature4Functor");
}
