/* 
 * MMFF94VanDerWaalsInteractionExport.cpp 
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

#include "CDPL/ForceField/MMFF94VanDerWaalsInteraction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    struct MMFF94VanDerWaalsAtomParameters
    {

        typedef CDPL::ForceField::MMFF94VanDerWaalsInteraction::HDonorAcceptorType HDonorAcceptorType;

        MMFF94VanDerWaalsAtomParameters(double atom_pol, double eff_el_num, double fact_a, double fact_g, 
                                        HDonorAcceptorType don_acc_type):
            polarizability(atom_pol), effElNumber(eff_el_num), factA(fact_a), factG(fact_g),
            donAccType(don_acc_type) {}

        double             polarizability;
        double             effElNumber;
        double             factA;
        double             factG;
        HDonorAcceptorType donAccType;
    };

    struct MMFF94VanDerWaalsInteractionWrapper : 
        public CDPL::ForceField::MMFF94VanDerWaalsInteraction, 
        public boost::python::wrapper<CDPL::ForceField::MMFF94VanDerWaalsInteraction>
    {

        MMFF94VanDerWaalsInteractionWrapper(const MMFF94VanDerWaalsInteractionWrapper& iactn): 
            CDPL::ForceField::MMFF94VanDerWaalsInteraction(iactn) {}

        MMFF94VanDerWaalsInteractionWrapper(const CDPL::ForceField::MMFF94VanDerWaalsInteraction& iactn): 
            CDPL::ForceField::MMFF94VanDerWaalsInteraction(iactn) {}

        MMFF94VanDerWaalsInteractionWrapper(std::size_t atom1_idx, std::size_t atom2_idx, 
                                            const MMFF94VanDerWaalsAtomParameters& atom1_params, 
                                            const MMFF94VanDerWaalsAtomParameters& atom2_params, 
                                            double expo, double fact_b, double beta, double fact_darad, 
                                            double fact_daeps):
            CDPL::ForceField::MMFF94VanDerWaalsInteraction(atom1_idx, atom2_idx, atom1_params.polarizability,
                                                           atom1_params.effElNumber, atom1_params.factA,
                                                           atom1_params.factG, atom1_params.donAccType,
                                                           atom2_params.polarizability, atom2_params.effElNumber, 
                                                           atom2_params.factA, atom2_params.factG, atom2_params.donAccType,
                                                           expo, fact_b, beta, fact_darad, fact_daeps) {} 
    };
}


void CDPLPythonForceField::exportMMFF94VanDerWaalsInteraction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<MMFF94VanDerWaalsAtomParameters>("MMFF94VanDerWaalsAtomParameters", python::no_init)
        .def(python::init<const MMFF94VanDerWaalsAtomParameters&>((python::arg("self"), python::arg("params"))))
        .def(python::init<double, double, double, double, ForceField::MMFF94VanDerWaalsInteraction::HDonorAcceptorType>(
                 (python::arg("self"), python::arg("atom_pol"), python::arg("eff_el_num"), python::arg("fact_a"), python::arg("fact_g"),
                  python::arg("don_acc_type"))));

    python::class_<MMFF94VanDerWaalsInteractionWrapper> cl("MMFF94VanDerWaalsInteraction", python::no_init);
    python::scope scope = cl;

    python::enum_<ForceField::MMFF94VanDerWaalsInteraction::HDonorAcceptorType>("HDonorAcceptorType")
        .value("NONE", ForceField::MMFF94VanDerWaalsInteraction::NONE)
        .value("DONOR", ForceField::MMFF94VanDerWaalsInteraction::DONOR)
        .value("ACCEPTOR", ForceField::MMFF94VanDerWaalsInteraction::ACCEPTOR)
        .export_values();

    cl
        .def(python::init<const ForceField::MMFF94VanDerWaalsInteraction&>((python::arg("self"), python::arg("iactn"))))
        .def(python::init<std::size_t, std::size_t, const MMFF94VanDerWaalsAtomParameters&, const MMFF94VanDerWaalsAtomParameters&,
             double, double, double, double, double>(
                 (python::arg("self"), python::arg("atom1_idx"), python::arg("atom2_idx"), python::arg("atom_params1"), 
                  python::arg("atom_params2"), python::arg("expo"), python::arg("fact_b"), python::arg("beta"), 
                  python::arg("fact_darad"), python::arg("fact_daeps"))))
        .def("getAtom1Index", &ForceField::MMFF94VanDerWaalsInteraction::getAtom1Index, python::arg("self"))
        .def("getAtom2Index", &ForceField::MMFF94VanDerWaalsInteraction::getAtom2Index, python::arg("self"))
        .def("getEIJ", &ForceField::MMFF94VanDerWaalsInteraction::getEIJ, python::arg("self"))
        .def("getRIJ", &ForceField::MMFF94VanDerWaalsInteraction::getRIJ, python::arg("self"))
        .def("getRIJPow7", &ForceField::MMFF94VanDerWaalsInteraction::getRIJPow7, python::arg("self"))
        .def("assign", CDPLPythonBase::copyAssOp<ForceField::MMFF94VanDerWaalsInteraction>(),
             (python::arg("self"), python::arg("iactn")), python::return_self<>())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ForceField::MMFF94VanDerWaalsInteraction>())
        .add_property("atom1Index", &ForceField::MMFF94VanDerWaalsInteraction::getAtom1Index) 
        .add_property("atom2Index", &ForceField::MMFF94VanDerWaalsInteraction::getAtom2Index)
        .add_property("eIJ", &ForceField::MMFF94VanDerWaalsInteraction::getEIJ)
        .add_property("rIJ", &ForceField::MMFF94VanDerWaalsInteraction::getRIJ)
        .add_property("rIJPow7", &ForceField::MMFF94VanDerWaalsInteraction::getRIJPow7);
}
