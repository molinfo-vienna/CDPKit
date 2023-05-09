/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomArray3DCoordinatesFunctorExport.cpp 
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

#include "CDPL/Chem/AtomArray3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    const CDPL::Math::Vector3D& callOperator(CDPL::Chem::AtomArray3DCoordinatesFunctor& func, CDPL::Chem::Atom& atom)
    {
		return func(atom);
    }
}


void CDPLPythonChem::exportAtomArray3DCoordinatesFunctor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::AtomArray3DCoordinatesFunctor, boost::noncopyable>("AtomArray3DCoordinatesFunctor", python::no_init)
		.def(python::init<const Chem::AtomArray3DCoordinatesFunctor&>((python::arg("self"), python::arg("func"))))
		.def(python::init<const Math::Vector3DArray&, const Chem::MolecularGraph&>((python::arg("self"), python::arg("coords"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomArray3DCoordinatesFunctor>())
		.def("assign", CDPLPythonBase::copyAssOp(&Chem::AtomArray3DCoordinatesFunctor::operator=), 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("atom")),
			 boost::python::return_internal_reference<2>());
}
