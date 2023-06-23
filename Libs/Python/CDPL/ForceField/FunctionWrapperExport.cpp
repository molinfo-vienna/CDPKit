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


#include <string>

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/FragmentList.hpp"

#include "Base/FunctionWrapperExport.hpp"

#include "ClassExports.hpp"


void CDPLPythonForceField::exportFunctionWrappers()
{
    using namespace boost;
    using namespace CDPL;
    using namespace Chem;

    CDPLPythonBase::Function1Export<unsigned int(const Atom&), Atom&>("MMFF94NumericAtomTypeFunction");
    CDPLPythonBase::Function1Export<const std::string&(const Atom&), Atom&, python::return_internal_reference<> >("MMFF94SymbolicAtomTypeFunction");
    CDPLPythonBase::Function1Export<double(const Atom&), Atom&>("MMFF94AtomChargeFunction");
    CDPLPythonBase::Function1Export<unsigned int(const Bond&), Bond&>("MMFF94BondTypeIndexFunction");
    CDPLPythonBase::Function1Export<const FragmentList::SharedPointer&(const MolecularGraph&), MolecularGraph&,    python::return_value_policy<python::copy_const_reference> >("MMFF94RingSetFunction");

    CDPLPythonBase::Function2Export<bool(const Atom&, const Atom&), Atom&, Atom&>("InteractionFilterFunction2");
    CDPLPythonBase::Function3Export<bool(const Atom&, const Atom&, const Atom&), Atom&, Atom&, Atom&>("InteractionFilterFunction3");
    CDPLPythonBase::Function4Export<bool(const Atom&, const Atom&, const Atom&, const Atom&), Atom&, Atom&, Atom&, Atom&>("InteractionFilterFunction4");

    CDPLPythonBase::Function3Export<std::size_t(const Atom&, const Atom&, const MolecularGraph&), Atom&, Atom&, MolecularGraph&>("TopologicalAtomDistanceFunction");
}
