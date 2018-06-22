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

#include "CDPL/Chem/Entity3DMapping.hpp"
#include "CDPL/Chem/AtomMapping.hpp"
#include "CDPL/Chem/Entity3D.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Chem/AtomPredicate.hpp"
#include "CDPL/Chem/BondPredicate.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/IntTypes.hpp"

#include "Base/BoostFunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportBoostFunctionWrappers()
{
	using namespace boost;
    using namespace CDPL;
    using namespace Chem;

    CDPLPythonBase::BoostFunction1Export<boost::function1<Base::uint64, const Atom&>, Atom& >("UInt64AtomFunctor");
    CDPLPythonBase::BoostFunction1Export<boost::function1<Base::uint64, const Bond&>, Bond& >("UInt64BondFunctor");
    CDPLPythonBase::BoostFunction1Export<boost::function1<bool, const Entity3DMapping&> >("BoolEntity3DMappingFunctor");
    CDPLPythonBase::BoostFunction1Export<boost::function1<bool, const AtomMapping&> >("BoolAtomMappingFunctor");
	CDPLPythonBase::BoostFunction1Export<boost::function1<const Math::Vector2D&, const Atom&>, Atom&, 
										 python::return_internal_reference<> >("Vector2DAtomFunctor");
    CDPLPythonBase::BoostFunction1Export<boost::function1<const Math::Vector3D&, const Entity3D&>, Entity3D&, 
										 python::return_internal_reference<> >("Vector3DEntity3DFunctor");
    CDPLPythonBase::BoostFunction1Export<Atom3DCoordinatesFunction, Atom&, 
										 python::return_internal_reference<> >("Atom3DCoordinatesFunction");
    CDPLPythonBase::BoostFunction1Export<boost::function1<double, const Atom&>, Atom&>("DoubleAtomFunctor");
	CDPLPythonBase::BoostFunction1Export<boost::function1<double, const Entity3D&>, Entity3D&>("DoubleEntity3DFunctor");
	CDPLPythonBase::BoostFunction1Export<AtomPredicate, Atom&>("AtomPredicate");
	CDPLPythonBase::BoostFunction1Export<BondPredicate, Bond&>("BondPredicate");
	CDPLPythonBase::BoostFunction1Export<boost::function1<double, const Math::DVector&> >("DoubleDVectorFunctor"); 
	CDPLPythonBase::BoostFunction1Export<boost::function1<bool, const MolecularGraph&> >("BoolMolecularGraphFunctor");
	CDPLPythonBase::BoostFunction1Export<boost::function1<void, MolecularGraph&> >("VoidMolecularGraphFunctor");

    CDPLPythonBase::BoostFunction2Export<boost::function2<bool, const Entity3D&, const Entity3D&>, Entity3D&, Entity3D&>("BoolEntity3D2Functor");
    CDPLPythonBase::BoostFunction2Export<boost::function2<double, const Entity3D&, const Entity3D&>, Entity3D&, Entity3D&>("DoubleEntity3D2Functor");
    CDPLPythonBase::BoostFunction2Export<boost::function2<bool, const Atom&, const Atom&>, Atom&, Atom&>("BoolAtom2Functor");
    CDPLPythonBase::BoostFunction2Export<boost::function2<double, const Atom&, const Atom&>, Atom&, Atom&>("DoubleAtom2Functor");
    CDPLPythonBase::BoostFunction2Export<boost::function2<Base::uint64, const Atom&, const MolecularGraph&>, Atom&, MolecularGraph&>("UInt64AtomMolecularGraphFunctor");

	CDPLPythonBase::BoostFunction3Export<boost::function3<double, const Math::Vector3D&, const Math::Vector3D&, const Atom&>,
										 const Math::Vector3D&, const Math::Vector3D&, Atom&>("DoubleVector3D2AtomFunctor");
    CDPLPythonBase::BoostFunction3Export<boost::function3<double, const Atom&, const Atom&, unsigned int>, Atom&, Atom&>("DoubleAtom2UIntFunctor"); 	

    CDPLPythonBase::BoostFunction4Export<boost::function4<bool, const Entity3D&, const Entity3D&, const Entity3D&, const Entity3D&>,
										 Entity3D&, Entity3D&, Entity3D&, Entity3D&>("BoolEntity3D4Functor");
    CDPLPythonBase::BoostFunction4Export<boost::function4<bool, const Atom&, const Atom&, const Atom&, const Atom&>,
										 Atom&, Atom&, Atom&, Atom&>("BoolAtom4Functor");
}
