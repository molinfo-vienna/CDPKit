/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BoostFunctionWrapperExport.cpp 
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


#include <boost/function.hpp>


#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"

#include "Base/BoostFunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportBoostFunctionWrappers()
{
    using namespace CDPL;
    using namespace Pharm;

    CDPLPythonBase::BoostFunction1Export<boost::function1<bool, const FeatureMapping&> >("BoolFeatureMappingFunctor");
    CDPLPythonBase::BoostFunction1Export<boost::function1<Math::Vector3D&, const Feature&>, Feature&, 
					 boost::python::return_internal_reference<2> >("Vector3DFeatureFunctor");
    
    CDPLPythonBase::BoostFunction2Export<boost::function2<bool, const Chem::MolecularGraph&, Pharmacophore&> >("VoidMolGraphPharmacophoreFunctor");
    CDPLPythonBase::BoostFunction2Export<boost::function2<bool, const Feature&, const Feature&>, Feature&, Feature&>("BoolFeature2Functor");
 
    CDPLPythonBase::BoostFunction3Export<boost::function3<bool, const Feature&, const Feature&, const Math::Matrix4D&>,
					 Feature&, Feature&>("BoolFeature2Matrix4DFunctor");

    CDPLPythonBase::BoostFunction4Export<boost::function4<bool, const Feature&, const Feature&, const Feature&, const Feature&>,
					 Feature&, Feature&, Feature&, Feature&>("BoolFeature4Functor");
}
