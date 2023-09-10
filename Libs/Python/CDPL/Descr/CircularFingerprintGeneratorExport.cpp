/* 
 * CircularFingerprintGeneratorExport.cpp 
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

#include "CDPL/Descr/CircularFingerprintGenerator.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    std::uint64_t defAtomIdentifierFunction(const CDPL::Descr::CircularFingerprintGenerator::DefAtomIdentifierFunctor& func,
                                            CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph)
    {
        return func(atom, molgraph);
    }

    std::uint64_t defBondIdentifierFunction(const CDPL::Descr::CircularFingerprintGenerator::DefBondIdentifierFunctor& func, 
                                            CDPL::Chem::Bond& bond)
    {
        return func(bond);
    }
}


void CDPLPythonDescr::exportCircularFingerprintGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Descr::CircularFingerprintGenerator>("CircularFingerprintGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Descr::CircularFingerprintGenerator&>((python::arg("self"), python::arg("gen"))))
        .def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Descr::CircularFingerprintGenerator>())    
        .def("setAtomIdentifierFunction", &Descr::CircularFingerprintGenerator::setAtomIdentifierFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setBondIdentifierFunction", &Descr::CircularFingerprintGenerator::setBondIdentifierFunction, 
             (python::arg("self"), python::arg("func")))
        .def("setNumIterations", &Descr::CircularFingerprintGenerator::setNumIterations, 
             (python::arg("self"), python::arg("num_iter")))
        .def("getNumIterations", &Descr::CircularFingerprintGenerator::getNumIterations, python::arg("self"))
        .def("includeHydrogens", &Descr::CircularFingerprintGenerator::includeHydrogens, 
             (python::arg("self"), python::arg("include")))
        .def("hydrogensIncluded", &Descr::CircularFingerprintGenerator::hydrogensIncluded, python::arg("self"))
        .def("includeChirality", &Descr::CircularFingerprintGenerator::includeChirality, 
             (python::arg("self"), python::arg("include")))
        .def("chiralityIncluded", &Descr::CircularFingerprintGenerator::chiralityIncluded, python::arg("self"))
        .def("generate", &Descr::CircularFingerprintGenerator::generate, (python::arg("self"), python::arg("molgraph")),
             python::with_custodian_and_ward<1, 2>())
        .def("setFeatureBits", static_cast<void (Descr::CircularFingerprintGenerator::*)(Util::BitSet&, bool) const>
             (&Descr::CircularFingerprintGenerator::setFeatureBits),
             (python::arg("self"), python::arg("bs"), python::arg("reset") = true))
        .def("setFeatureBits", static_cast<void (Descr::CircularFingerprintGenerator::*)(std::size_t, Util::BitSet&, bool) const>
             (&Descr::CircularFingerprintGenerator::setFeatureBits),
             (python::arg("self"), python::arg("atom_idx"), python::arg("bs"), python::arg("reset") = true))
        .def("getNumFeatures", &Descr::CircularFingerprintGenerator::getNumFeatures, python::arg("self"))
        .def("getFeatureIdentifier", &Descr::CircularFingerprintGenerator::getFeatureIdentifier, (python::arg("self"), python::arg("ftr_idx")))
        .def("getFeatureSubstructure", static_cast<const Util::BitSet& (Descr::CircularFingerprintGenerator::*)(std::size_t) const>
             (&Descr::CircularFingerprintGenerator::getFeatureSubstructure),
             (python::arg("self"), python::arg("ftr_idx")), python::return_internal_reference<>())
        .def("getFeatureSubstructure", static_cast<void (Descr::CircularFingerprintGenerator::*)(std::size_t, Chem::Fragment&, bool) const>
             (&Descr::CircularFingerprintGenerator::getFeatureSubstructure),
             (python::arg("self"), python::arg("ftr_idx"), python::arg("frag"), python::arg("clear") = true),
             python::with_custodian_and_ward<3, 1>())
        .def("getFeatureSubstructures", &Descr::CircularFingerprintGenerator::getFeatureSubstructures,
             (python::arg("self"), python::arg("bit_idx"), python::arg("bs_size"), python::arg("frags"), python::arg("clear") = true),
             python::with_custodian_and_ward<4, 1>())
        .def("assign", CDPLPythonBase::copyAssOp<Descr::CircularFingerprintGenerator>(), 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .add_property("numFeatures", &Descr::CircularFingerprintGenerator::getNumFeatures)
        .add_property("numIterations", &Descr::CircularFingerprintGenerator::getNumIterations,
                      &Descr::CircularFingerprintGenerator::setNumIterations)
        .add_property("incHydrogens", &Descr::CircularFingerprintGenerator::hydrogensIncluded,
                      &Descr::CircularFingerprintGenerator::includeHydrogens)
        .add_property("incChirality", &Descr::CircularFingerprintGenerator::chiralityIncluded,
                      &Descr::CircularFingerprintGenerator::includeChirality)
        .def_readonly("DEF_ATOM_PROPERTY_FLAGS", Descr::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)
        .def_readonly("DEF_BOND_PROPERTY_FLAGS", Descr::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS);

    python::class_<Descr::CircularFingerprintGenerator::DefAtomIdentifierFunctor>("DefAtomIdentifierFunctor", python::no_init)
        .def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
                                         Descr::CircularFingerprintGenerator::DEF_ATOM_PROPERTY_FLAGS)))
        .def("__call__", &defAtomIdentifierFunction, (python::arg("self"), python::arg("atom"), python::arg("molgraph")));

    python::class_<Descr::CircularFingerprintGenerator::DefBondIdentifierFunctor>("DefBondIdentifierFunctor", python::no_init)
        .def(python::init<unsigned int>((python::arg("self"), python::arg("flags") = 
                                         Descr::CircularFingerprintGenerator::DEF_BOND_PROPERTY_FLAGS)))
        .def("__call__", &defBondIdentifierFunction, (python::arg("self"), python::arg("bond")));
}
