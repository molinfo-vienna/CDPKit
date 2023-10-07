/* 
 * AtomFunctionExport.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
    return CDPL::MolProp::get##FUNC_SUFFIX(atom);                   \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
    return CDPL::MolProp::has##FUNC_SUFFIX(atom);                  \
}

#define EXPORT_ATOM_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &MolProp::clear##FUNC_SUFFIX, python::arg("atom"));                         \
python::def("set"#FUNC_SUFFIX, &MolProp::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 


namespace
{
    
    MAKE_FUNCTION_WRAPPER1(double, getAtomicWeight, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getIUPACGroup, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getPeriod, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(double, getVdWRadius, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(double, getAllredRochowElectronegativity, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(const std::string&, getElementName, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getElementValenceElectronCount, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isChemicalElement, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isMainGroupElement, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isMetal, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isTransitionMetal, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isNonMetal, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isSemiMetal, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isHalogen, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isNobleGas, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(bool, isHeavy, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, calcValenceElectronCount, CDPL::Chem::Atom&);
    MAKE_FUNCTION_WRAPPER1(double, calcTotalPartialCharge, CDPL::Chem::Atom&);
    
    MAKE_FUNCTION_WRAPPER2(double, getHybridPolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(double, getCovalentRadius, CDPL::Chem::Atom&, std::size_t);
    MAKE_FUNCTION_WRAPPER2(bool, isInRing, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingSSSRRings, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, calcExplicitValence, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, calcValence, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, calcFreeValenceElectronCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(bool, isUnsaturated, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(bool, isHBondAcceptor, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(bool, isHBondDonor, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getChainAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getRingAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getAromaticAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getHeavyAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getExplicitBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getExplicitChainAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getExplicitChainBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getChainBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getRingBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getAromaticBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, getHeavyBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(bool, isPlanarNitrogen, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(bool, isInvertibleNitrogen, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(std::size_t, calcStericNumber, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(unsigned int, getVSEPRCoordinationGeometry, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(double, calcLonePairElectronegativity, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    MAKE_FUNCTION_WRAPPER2(double, calcPiElectronegativity, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
    
    MAKE_FUNCTION_WRAPPER3(double, calcEffectivePolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, double);
    MAKE_FUNCTION_WRAPPER3(std::size_t, getExplicitBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
    MAKE_FUNCTION_WRAPPER3(bool, isInRingOfSize, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
    MAKE_FUNCTION_WRAPPER3(std::size_t, getBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
    MAKE_FUNCTION_WRAPPER3(bool, isOrdinaryHydrogen, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int);
    MAKE_FUNCTION_WRAPPER3(std::size_t, getOrdinaryHydrogenCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int);
    MAKE_FUNCTION_WRAPPER3(unsigned int, getVSEPRCoordinationGeometry, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
    MAKE_FUNCTION_WRAPPER3(double, calcInductiveEffect, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
    
    MAKE_FUNCTION_WRAPPER4(bool, isCarbonylLikeAtom, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, bool, bool);
    MAKE_FUNCTION_WRAPPER4(bool, isAmideCenterAtom, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, bool, bool);
    MAKE_FUNCTION_WRAPPER4(bool, isAmideNitrogen, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, bool, bool);
    MAKE_FUNCTION_WRAPPER4(std::size_t, getExplicitAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int, bool);
    MAKE_FUNCTION_WRAPPER4(std::size_t, getAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int, bool);
    
    MAKE_FUNCTION_WRAPPER5(std::size_t, getExplicitBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t, unsigned int, bool);
    MAKE_FUNCTION_WRAPPER5(std::size_t, getBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t, unsigned int, bool);
    MAKE_FUNCTION_WRAPPER5(std::size_t, getRotatableBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, bool, bool, bool);

    MAKE_ATOM_FUNC_WRAPPERS(double, Hydrophobicity)
    MAKE_ATOM_FUNC_WRAPPERS(double, PEOESigmaCharge)
    MAKE_ATOM_FUNC_WRAPPERS(double, PEOESigmaElectronegativity)
    MAKE_ATOM_FUNC_WRAPPERS(double, MHMOPiCharge)
    MAKE_ATOM_FUNC_WRAPPERS(unsigned int, HBondDonorType)
    MAKE_ATOM_FUNC_WRAPPERS(unsigned int, HBondAcceptorType)
}


void CDPLPythonMolProp::exportAtomFunctions()
{
    using namespace boost;
    using namespace CDPL;
    
    python::def("getAtomicWeight", &getAtomicWeightWrapper1, python::arg("atom"));
    python::def("getIUPACGroup", &getIUPACGroupWrapper1, python::arg("atom"));
    python::def("getPeriod", &getPeriodWrapper1, python::arg("atom"));
    python::def("getVdWRadius", &getVdWRadiusWrapper1, python::arg("atom"));
    python::def("getAllredRochowElectronegativity", &getAllredRochowElectronegativityWrapper1, python::arg("atom"));
    python::def("getElementName", &getElementNameWrapper1, python::arg("atom"),
                python::return_value_policy<python::copy_const_reference>());
    python::def("getElementValenceElectronCount", &getElementValenceElectronCountWrapper1, python::arg("atom"));
    python::def("isChemicalElement", &isChemicalElementWrapper1, python::arg("atom"));
    python::def("isMainGroupElement", &isMainGroupElementWrapper1, python::arg("atom"));
    python::def("isMetal", &isMetalWrapper1, python::arg("atom"));
    python::def("isTransitionMetal", &isTransitionMetalWrapper1, python::arg("atom"));
    python::def("isNonMetal", &isNonMetalWrapper1, python::arg("atom"));
    python::def("isSemiMetal", &isSemiMetalWrapper1, python::arg("atom"));
    python::def("isHalogen", &isHalogenWrapper1, python::arg("atom"));
    python::def("isNobleGas", &isNobleGasWrapper1, python::arg("atom"));
    python::def("isHeavy", &isHeavyWrapper1, python::arg("atom"));
    python::def("calcValenceElectronCount", &calcValenceElectronCountWrapper1, python::arg("atom"));
    python::def("calcTotalPartialCharge", &calcTotalPartialChargeWrapper1, python::arg("atom"));
    
    python::def("getHybridPolarizability", &getHybridPolarizabilityWrapper2, 
                (python::arg("atom"), python::arg("molgraph")));
    python::def("getCovalentRadius", &getCovalentRadiusWrapper2, (python::arg("atom"), python::arg("order") = 1));
    python::def("isInRing", &isInRingWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getNumContainingSSSRRings", &getNumContainingSSSRRingsWrapper2, 
                (python::arg("atom"), python::arg("molgraph")));
    python::def("calcExplicitValence", &calcExplicitValenceWrapper2,
                (python::arg("atom"), python::arg("molgraph")));
    python::def("calcValence", &calcValenceWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("calcFreeValenceElectronCount", &calcFreeValenceElectronCountWrapper2,
                (python::arg("atom"), python::arg("molgraph")));
    python::def("isPlanarNitrogen", &isPlanarNitrogenWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("isInvertibleNitrogen", &isInvertibleNitrogenWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("isUnsaturated", &isUnsaturatedWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("isHBondAcceptor", &isHBondAcceptorWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("isHBondDonor", &isHBondDonorWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getChainAtomCount", &getChainAtomCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getRingAtomCount", &getRingAtomCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getAromaticAtomCount", &getAromaticAtomCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getHeavyAtomCount", &getHeavyAtomCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getExplicitBondCount", &getExplicitBondCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getExplicitChainAtomCount", &getExplicitChainAtomCountWrapper2, 
                (python::arg("atom"), python::arg("molgraph")));
    python::def("getBondCount", &getBondCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getExplicitChainBondCount", &getExplicitChainBondCountWrapper2,
                (python::arg("atom"), python::arg("molgraph")));
    python::def("getChainBondCount", &getChainBondCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getRingBondCount", &getRingBondCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getAromaticBondCount", &getAromaticBondCountWrapper2, 
                (python::arg("atom"), python::arg("molgraph")));
    python::def("getHeavyBondCount", &getHeavyBondCountWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("calcStericNumber", &calcStericNumberWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("getVSEPRCoordinationGeometry", &getVSEPRCoordinationGeometryWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("calcLonePairElectronegativity", &calcLonePairElectronegativityWrapper2, (python::arg("atom"), python::arg("molgraph")));
    python::def("calcPiElectronegativity", &calcPiElectronegativityWrapper2, (python::arg("atom"), python::arg("molgraph")));

    python::def("getExplicitBondCount", &getExplicitBondCountWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("order")));
    python::def("isInRingOfSize", &isInRingOfSizeWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("size")));
    python::def("getBondCount", &getBondCountWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("order")));
    python::def("isOrdinaryHydrogen", &isOrdinaryHydrogenWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
    python::def("getOrdinaryHydrogenCount", &getOrdinaryHydrogenCountWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
    python::def("calcEffectivePolarizability", &calcEffectivePolarizabilityWrapper3, 
                (python::arg("atom"), python::arg("molgraph"), python::arg("damping") = 0.75));
    python::def("getVSEPRCoordinationGeometry", &getVSEPRCoordinationGeometryWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("steric_num")));
    python::def("calcInductiveEffect", &calcInductiveEffectWrapper3,
                (python::arg("atom"), python::arg("molgraph"), python::arg("num_bonds") = 10));
    
    python::def("isCarbonylLikeAtom", &isCarbonylLikeAtomWrapper4, 
                (python::arg("atom"), python::arg("molgraph"), python::arg("c_only") = false, python::arg("db_o_only") = false));
    python::def("isAmideCenterAtom", &isAmideCenterAtomWrapper4, 
                (python::arg("atom"), python::arg("molgraph"), python::arg("c_only") = false, python::arg("db_o_only") = false));
    python::def("isAmideNitrogen", &isAmideNitrogenWrapper4, 
                (python::arg("atom"), python::arg("molgraph"), python::arg("c_only") = false, python::arg("db_o_only") = false));
    python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper4,
                (python::arg("atom"), python::arg("molgraph"), python::arg("type"), (python::arg("strict") = true)));
    python::def("getAtomCount", &getAtomCountWrapper4,
                (python::arg("atom"), python::arg("molgraph"), python::arg("type"), (python::arg("strict") = true)));
    
    python::def("getExplicitBondCount", &getExplicitBondCountWrapper5,
                (python::arg("atom"), python::arg("molgraph"), python::arg("order"), python::arg("type"), (python::arg("strict") = true)));
    python::def("getBondCount", &getBondCountWrapper5,
                (python::arg("atom"), python::arg("molgraph"), python::arg("order"), python::arg("type"), (python::arg("strict") = true)));
    python::def("getRotatableBondCount", &getRotatableBondCountWrapper5, 
                (python::arg("atom"), python::arg("molgraph"), python::arg("h_rotors") = false, python::arg("ring_bonds") = false, 
                 python::arg("amide_bonds") = false));
    
    EXPORT_ATOM_FUNCS(PEOESigmaCharge, charge)
    EXPORT_ATOM_FUNCS(PEOESigmaElectronegativity, e_neg)
    EXPORT_ATOM_FUNCS(MHMOPiCharge, charge)
    EXPORT_ATOM_FUNCS(Hydrophobicity, hyd)
    EXPORT_ATOM_FUNCS(HBondDonorType, type)
    EXPORT_ATOM_FUNCS(HBondAcceptorType, type)
}
