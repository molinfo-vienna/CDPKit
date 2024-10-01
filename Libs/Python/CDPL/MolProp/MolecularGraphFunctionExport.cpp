/* 
 * MolecularGraphFunctionExport.cpp 
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

#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "FunctionExports.hpp"


namespace
{

    boost::python::object generateMassCompositionStringWrapper(CDPL::Chem::MolecularGraph& molgraph)
    {
        std::string str;

        CDPL::MolProp::generateMassCompositionString(molgraph, str);

        return boost::python::str(str.c_str());
    }

    boost::python::object generateMolecularFormulaWrapper(CDPL::Chem::MolecularGraph& molgraph, const std::string& sep)
    {
        std::string str;

        CDPL::MolProp::generateMolecularFormula(molgraph, str, sep);

        return boost::python::str(str.c_str());
    }
}


void CDPLPythonMolProp::exportMolecularGraphFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("calcAtomHydrophobicities", &MolProp::calcAtomHydrophobicities, 
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("from_logp") = false));
    python::def("calcMass", &MolProp::calcMass, python::arg("molgraph"));
    python::def("calcMassComposition", &MolProp::calcMassComposition, 
                (python::arg("molgraph"), python::arg("comp")));
    python::def("generateElementHistogram", &MolProp::generateElementHistogram, 
                (python::arg("molgraph"), python::arg("hist"), python::arg("append") = false));

    python::def("calcCyclomaticNumber", &MolProp::calcCyclomaticNumber, python::arg("molgraph"));
    python::def("getComponentCount", &MolProp::getComponentCount, python::arg("molgraph"));
    
    python::def("getAtomCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&)>(&MolProp::getAtomCount),
                python::arg("molgraph"));
    python::def("getAtomCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&, unsigned int, bool)>(&MolProp::getAtomCount),
                (python::arg("molgraph"), python::arg("type"), python::arg("strict") = true));
    python::def("getImplicitHydrogenCount", &MolProp::getImplicitHydrogenCount, python::arg("molgraph"));
    python::def("getOrdinaryHydrogenCount", &MolProp::getOrdinaryHydrogenCount, 
                (python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
    python::def("getExplicitOrdinaryHydrogenCount", &MolProp::getExplicitOrdinaryHydrogenCount, 
                (python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
    python::def("getChainAtomCount", &MolProp::getChainAtomCount, python::arg("molgraph"));
    python::def("getHBondAcceptorAtomCount", &MolProp::getHBondAcceptorAtomCount, python::arg("molgraph"));
    python::def("getHBondDonorAtomCount", &MolProp::getHBondDonorAtomCount, python::arg("molgraph"));

    python::def("getBondCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&)>(&MolProp::getBondCount),
                python::arg("molgraph"));
    python::def("getBondCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&, std::size_t, bool)>(&MolProp::getBondCount),
                (python::arg("molgraph"), python::arg("order"), python::arg("inc_aro") = true));
    python::def("getHydrogenBondCount", &MolProp::getHydrogenBondCount, python::arg("molgraph"));
    python::def("getChainBondCount", &MolProp::getChainBondCount, python::arg("molgraph"));
    python::def("getRotatableBondCount", &MolProp::getRotatableBondCount, 
                (python::arg("molgraph"), python::arg("h_rotors") = false, python::arg("ring_bonds") = false, python::arg("amide_bonds") = false));

    python::def("getRuleOfFiveScore", &MolProp::getRuleOfFiveScore, python::arg("molgraph"));

    python::def("calcXLogP", &MolProp::calcXLogP, python::arg("molgraph"));
    python::def("calcLogS", &MolProp::calcLogS, python::arg("molgraph"));
    python::def("calcTPSA", &MolProp::calcTPSA, python::arg("molgraph"));

    python::def("calcMeanPolarizability", &MolProp::calcMeanPolarizability, python::arg("molgraph"));
    python::def("calcPEOEProperties", &MolProp::calcPEOEProperties,
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("num_iter") = 20, python::arg("damping") = 0.48));
    python::def("calcMHMOProperties", &MolProp::calcMHMOProperties,    (python::arg("molgraph"), python::arg("overwrite")));
    python::def("generateMassCompositionString", &generateMassCompositionStringWrapper, python::arg("molgraph"));
    python::def("generateMolecularFormula", &generateMolecularFormulaWrapper, (python::arg("molgraph"), python::arg("sep") = std::string()));

    python::def("perceiveHBondDonorAtomTypes", &MolProp::perceiveHBondDonorAtomTypes,
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("perceiveHBondAcceptorAtomTypes", &MolProp::perceiveHBondAcceptorAtomTypes,
                (python::arg("molgraph"), python::arg("overwrite")));
}
