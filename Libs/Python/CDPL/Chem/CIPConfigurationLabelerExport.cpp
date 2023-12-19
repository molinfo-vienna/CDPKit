/* 
 * CIPConfigurationLabelerExport.cpp 
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

#include "CDPL/Chem/CIPConfigurationLabeler.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    unsigned int getAtomLabel(CDPL::Chem::CIPConfigurationLabeler& labeler, CDPL::Chem::Atom& atom)
    {
        return labeler.getLabel(atom);
    }

    unsigned int getBondLabel(CDPL::Chem::CIPConfigurationLabeler& labeler, CDPL::Chem::Bond& bond)
    {
        return labeler.getLabel(bond);
    }
}


void CDPLPythonChem::exportCIPConfigurationLabeler()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::CIPConfigurationLabeler, Chem::CIPConfigurationLabeler::SharedPointer,
                   boost::noncopyable>("CIPConfigurationLabeler", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&>(python::arg("molgraph"))[python::with_custodian_and_ward<1, 2>()])
        .def(python::init<const Chem::CIPConfigurationLabeler&>(python::arg("labeler"))[python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CIPConfigurationLabeler>())
        .def("assign", &Chem::CIPConfigurationLabeler::operator=, 
             (python::arg("self"), python::arg("labeler")), python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("setup", &Chem::CIPConfigurationLabeler::setup, 
             (python::arg("self"), python::arg("molgraph")), python::with_custodian_and_ward<1, 2>())
        .def("getLabel", &getAtomLabel, (python::arg("self"), python::arg("atom")))
        .def("getLabel", &getBondLabel, (python::arg("self"), python::arg("bond")));
}
