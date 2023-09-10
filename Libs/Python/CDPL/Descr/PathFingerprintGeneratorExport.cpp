/* 
 * PathFingerprintGeneratorExport.cpp 
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

#include "CDPL/Descr/PathFingerprintGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    std::uint64_t defAtomDescriptorFunction(const CDPL::Descr::PathFingerprintGenerator::DefAtomDescriptorFunctor& func,
                                            CDPL::Chem::Atom& atom)
    {
        return func(atom);
    }

    std::uint64_t defBondDescriptorFunction(const CDPL::Descr::PathFingerprintGenerator::DefBondDescriptorFunctor& func, 
                                            CDPL::Chem::Bond& bond)
    {
        return func(bond);
    }
}


void CDPLPythonDescr::exportPathFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Descr::PathFingerprintGenerator>("PathFingerprintGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&, Util::BitSet&>(
                 (python::arg("self"), python::arg("molgraph"), python::arg("fp"))))
        .def(python::init<const Descr::PathFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::PathFingerprintGenerator>())    
        .def("assign", CDPLPythonBase::copyAssOp<Descr::PathFingerprintGenerator>(), 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setAtomDescriptorFunction", &Descr::PathFingerprintGenerator::setAtomDescriptorFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setBondDescriptorFunction", &Descr::PathFingerprintGenerator::setBondDescriptorFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setMinPathLength", &Descr::PathFingerprintGenerator::setMinPathLength, 
             (python::arg("self"), python::arg("min_length")))
        .def("setMaxPathLength", &Descr::PathFingerprintGenerator::setMaxPathLength, 
             (python::arg("self"), python::arg("max_length")))
        .def("setNumBits", &Descr::PathFingerprintGenerator::setNumBits, 
             (python::arg("self"), python::arg("num_bits")))
        .def("getMinPathLength", &Descr::PathFingerprintGenerator::getMinPathLength, python::arg("self"))
        .def("getMaxPathLength", &Descr::PathFingerprintGenerator::getMaxPathLength, python::arg("self"))
        .def("getNumBits", &Descr::PathFingerprintGenerator::getNumBits, python::arg("self"))
        .def("generate", &Descr::PathFingerprintGenerator::generate,
             (python::arg("self"), python::arg("molgraph"), python::arg("fp")))
        .add_property("minPathLength", &Descr::PathFingerprintGenerator::getMinPathLength,
                      &Descr::PathFingerprintGenerator::setMinPathLength)
        .add_property("maxPathLength", &Descr::PathFingerprintGenerator::getMaxPathLength,
                      &Descr::PathFingerprintGenerator::setMaxPathLength)
        .add_property("numBits", &Descr::PathFingerprintGenerator::getNumBits,
                      &Descr::PathFingerprintGenerator::setNumBits)
        .def_readonly("DEF_ATOM_PROPERTY_FLAGS", Descr::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)
        .def_readonly("DEF_BOND_PROPERTY_FLAGS", Descr::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS);

    python::class_<Descr::PathFingerprintGenerator::DefAtomDescriptorFunctor>("DefAtomDescriptorFunctor", python::no_init)
        .def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
                                         Descr::PathFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)))
        .def("__call__", &defAtomDescriptorFunction, (python::arg("self"), python::arg("atom")));

    python::class_<Descr::PathFingerprintGenerator::DefBondDescriptorFunctor>("DefBondDescriptorFunctor", python::no_init)
        .def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
                                         Descr::PathFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS)))
        .def("__call__", &defBondDescriptorFunction, (python::arg("self"), python::arg("bond")));
}
