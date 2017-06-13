/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctionExport.cpp 
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


#include <vector>
#include <iterator>

#include <boost/python.hpp>

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_ATOM_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
	return get##FUNC_SUFFIX(atom);                                 \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Atom& atom)             \
{                                                                  \
	return has##FUNC_SUFFIX(atom);                                 \
}

#define EXPORT_ATOM_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("atom"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("atom"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
			python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("atom"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_ATOM_FUNCS_INT_REF(FUNC_SUFFIX, ARG_NAME)                                                     \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("atom"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME))); 

#define EXPORT_ATOM_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("atom"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("atom"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("atom"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("atom"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());  


namespace
{

	typedef CDPL::Chem::MatchExpression<CDPL::Chem::Atom, CDPL::Chem::MolecularGraph>::SharedPointer MatchExpressionPtr;
	typedef const MatchExpressionPtr& MatchExpressionPtrRef;

	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, Name)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, Symbol)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, UnpairedElectronCount)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, Type)
	MAKE_ATOM_FUNC_WRAPPERS(long, FormalCharge)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, ImplicitHydrogenCount)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, Isotope)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, RadicalType)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, HybridizationState)
	MAKE_ATOM_FUNC_WRAPPERS(bool, AromaticityFlag)
	MAKE_ATOM_FUNC_WRAPPERS(bool, RingFlag)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Math::Vector2D&, 2DCoordinates)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Math::Vector3DArray::SharedPointer&, 3DCoordinatesArray)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, MorganNumber)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, CanonicalNumber)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, CIPPriority)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, SymmetryClass)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, CIPConfiguration)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, MDLParity)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, ReactionAtomMappingID)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, ComponentGroupID)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, ReactionCenterStatus)
	MAKE_ATOM_FUNC_WRAPPERS(double, PEOECharge)
	MAKE_ATOM_FUNC_WRAPPERS(bool, StereoCenterFlag)
	MAKE_ATOM_FUNC_WRAPPERS(bool, MDLStereoCareFlag)
	MAKE_ATOM_FUNC_WRAPPERS(MatchExpressionPtrRef, MatchExpression)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MatchExpressionString)
	MAKE_ATOM_FUNC_WRAPPERS(const CDPL::Chem::StereoDescriptor&, StereoDescriptor)
	MAKE_ATOM_FUNC_WRAPPERS(unsigned int, SybylType)
	MAKE_ATOM_FUNC_WRAPPERS(double, MOL2Charge)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MOL2Name)
	MAKE_ATOM_FUNC_WRAPPERS(std::size_t, MOL2SubstructureID)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MOL2SubstructureName)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MOL2SubstructureSubtype)
	MAKE_ATOM_FUNC_WRAPPERS(const std::string&, MOL2SubstructureChain)

	MAKE_FUNCTION_WRAPPER1(const CDPL::Chem::MatchConstraintList::SharedPointer&, getMatchConstraints, CDPL::Chem::Atom&)
	MAKE_FUNCTION_WRAPPER1(bool, hasMatchConstraints, CDPL::Chem::Atom&)
	MAKE_FUNCTION_WRAPPER1(double, getAtomicWeight, CDPL::Chem::Atom&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getIUPACGroup, CDPL::Chem::Atom&);
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
	MAKE_FUNCTION_WRAPPER1(const std::string&, getSymbolForType, CDPL::Chem::Atom&);
	MAKE_FUNCTION_WRAPPER1(unsigned int, getTypeForSymbol, CDPL::Chem::Atom&);
	MAKE_FUNCTION_WRAPPER1(unsigned int, getGenericType, CDPL::Chem::Atom&);

	MAKE_FUNCTION_WRAPPER2(double, getCovalentRadius, CDPL::Chem::Atom&, std::size_t);
	MAKE_FUNCTION_WRAPPER2(bool, isInRing, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingSSSRRings, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, calcExplicitValence, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, calcValence, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, calcFreeValenceElectronCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isUnsaturated, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isHydrogenAcceptor, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isHydrogenDonor, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(long, calcFormalCharge, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, perceiveHybridizationState, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, calcImplicitHydrogenCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
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
	MAKE_FUNCTION_WRAPPER2(std::size_t, getRotatableBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, calcCIPConfiguration, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(CDPL::Chem::StereoDescriptor, calcStereoDescriptorFromMDLParity, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(bool, isStereoCenter, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, calcMDLParity, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(double, getHybridPolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(MatchExpressionPtr, buildMatchExpression, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getSizeOfSmallestContainingFragment, CDPL::Chem::Atom&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getSizeOfLargestContainingFragment, CDPL::Chem::Atom&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingFragments, CDPL::Chem::Atom&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, perceiveSybylType, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&);

	MAKE_FUNCTION_WRAPPER3(std::size_t, getExplicitBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(bool, isInRingOfSize, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(std::size_t, getBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(CDPL::Chem::StereoDescriptor, calcStereoDescriptor, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(bool, isOrdinaryHydrogen, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int);
	MAKE_FUNCTION_WRAPPER3(std::size_t, getOrdinaryHydrogenCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int);
	MAKE_FUNCTION_WRAPPER3(bool, isInFragmentOfSize, CDPL::Chem::Atom&, CDPL::Chem::FragmentList&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(void, getContainingFragments, CDPL::Chem::Atom&, CDPL::Chem::FragmentList&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER3(double, calcEffectivePolarizability, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, double);

	MAKE_FUNCTION_WRAPPER4(std::size_t, getExplicitAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int, bool);
	MAKE_FUNCTION_WRAPPER4(std::size_t, getAtomCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, unsigned int, bool);

	MAKE_FUNCTION_WRAPPER5(std::size_t, getExplicitBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t, unsigned int, bool);
	MAKE_FUNCTION_WRAPPER5(std::size_t, getBondCount, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, std::size_t, unsigned int, bool);

	std::string buildMatchExpressionStringWrapper(CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMatchExpressionString(atom, molgraph, str);
		return str;
	}

	std::size_t getConnectedAtomsWrapper(CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph, boost::python::list& atoms)
	{
		using namespace CDPL;
		using namespace Chem;

		std::vector<Atom*> tmp_atoms;
		std::size_t count = getConnectedAtoms(atom, molgraph, std::back_inserter(tmp_atoms)); 
		
		for (std::vector<Atom*>::iterator it = tmp_atoms.begin(), end = tmp_atoms.end(); it != end; ++it)
			atoms.append(boost::ref(*it));

		return count;
	}

	std::size_t getIncidentBondsWrapper(CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph, boost::python::list& bonds)
	{
		using namespace CDPL;
		using namespace Chem;

		std::vector<Bond*> tmp_bonds;
		std::size_t count = getIncidentBonds(atom, molgraph, std::back_inserter(tmp_bonds)); 

		for (std::vector<Bond*>::iterator it = tmp_bonds.begin(), end = tmp_bonds.end(); it != end; ++it)
			bonds.append(boost::ref(*it));

		return count;
	}

	std::size_t getConnectedAtomsAndBondsWrapper(CDPL::Chem::Atom& atom, CDPL::Chem::MolecularGraph& molgraph, 
												 boost::python::list& atoms, boost::python::list& bonds)
	{
		using namespace CDPL;
		using namespace Chem;

		std::vector<Atom*> tmp_atoms;
		std::vector<Bond*> tmp_bonds;
		std::size_t count = getConnectedAtomsAndBonds(atom, molgraph, std::back_inserter(tmp_atoms), std::back_inserter(tmp_bonds)); 

		for (std::vector<Atom*>::iterator it = tmp_atoms.begin(), end = tmp_atoms.end(); it != end; ++it)
			atoms.append(boost::ref(*it));

		for (std::vector<Bond*>::iterator it = tmp_bonds.begin(), end = tmp_bonds.end(); it != end; ++it)
			bonds.append(boost::ref(*it));

		return count;
	}
}


void CDPLPythonChem::exportAtomFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("getAtomicWeight", &getAtomicWeightWrapper1, python::arg("atom"));
	python::def("getIUPACGroup", &getIUPACGroupWrapper1, python::arg("atom"));
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
	python::def("getSymbolForType", &getSymbolForTypeWrapper1, python::arg("atom"), 
				python::return_value_policy<python::copy_const_reference>());
	python::def("getTypeForSymbol", &getTypeForSymbolWrapper1, python::arg("atom"));
	python::def("getGenericType", &getGenericTypeWrapper1, python::arg("atom"));

	python::def("getCovalentRadius", &getCovalentRadiusWrapper2, (python::arg("atom"), python::arg("order") = 1));
	python::def("isInRing", &isInRingWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("getNumContainingSSSRRings", &getNumContainingSSSRRingsWrapper2, 
				(python::arg("atom"), python::arg("molgraph")));
	python::def("calcExplicitValence", &calcExplicitValenceWrapper2,
				(python::arg("atom"), python::arg("molgraph")));
	python::def("calcValence", &calcValenceWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("calcFreeValenceElectronCount", &calcFreeValenceElectronCountWrapper2,
				(python::arg("atom"), python::arg("molgraph")));
	python::def("isUnsaturated", &isUnsaturatedWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("isHydrogenAcceptor", &isHydrogenAcceptorWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("isHydrogenDonor", &isHydrogenDonorWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("calcFormalCharge", &calcFormalChargeWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("perceiveHybridizationState", &perceiveHybridizationStateWrapper2,
				(python::arg("atom"), python::arg("molgraph")));
	python::def("calcImplicitHydrogenCount", &calcImplicitHydrogenCountWrapper2,
				(python::arg("atom"), python::arg("molgraph")));
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
	python::def("getRotatableBondCount", &getRotatableBondCountWrapper2, 
				(python::arg("atom"), python::arg("molgraph")));
	python::def("calcCIPConfiguration", &calcCIPConfigurationWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("calcStereoDescriptorFromMDLParity", &calcStereoDescriptorFromMDLParityWrapper2,
				(python::arg("atom"), python::arg("molgraph")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("isStereoCenter", &isStereoCenterWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("calcMDLParity", &calcMDLParityWrapper2, (python::arg("atom"), python::arg("molgraph")));
	python::def("getHybridPolarizability", &getHybridPolarizabilityWrapper2, 
				(python::arg("atom"), python::arg("molgraph")));
	python::def("buildMatchExpression", &buildMatchExpressionWrapper2, (python::arg("atom"), python::arg("molgraph")),
				python::with_custodian_and_ward_postcall<0, 1>());
	python::def("getSizeOfSmallestContainingFragment", &getSizeOfSmallestContainingFragmentWrapper2,
				(python::arg("atom"), python::arg("frag_list")));
	python::def("getSizeOfLargestContainingFragment", &getSizeOfLargestContainingFragmentWrapper2,
				(python::arg("atom"), python::arg("frag_list")));
	python::def("getNumContainingFragments", &getNumContainingFragmentsWrapper2,
				(python::arg("atom"), python::arg("frag_list")));
	python::def("perceiveSybylType", &perceiveSybylTypeWrapper2,
				(python::arg("atom"), python::arg("molgraph")));
	python::def("sybylToAtomType", &Chem::sybylToAtomType, python::arg("sybyl_type"));

	python::def("getExplicitBondCount", &getExplicitBondCountWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("order")));
	python::def("isInRingOfSize", &isInRingOfSizeWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("size")));
	python::def("getBondCount", &getBondCountWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("order")));
	python::def("calcStereoDescriptor", &calcStereoDescriptorWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("dim") = 1),
				python::with_custodian_and_ward_postcall<0, 1>());
	python::def("isOrdinaryHydrogen", &isOrdinaryHydrogenWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("getOrdinaryHydrogenCount", &getOrdinaryHydrogenCountWrapper3,
				(python::arg("atom"), python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("isInFragmentOfSize", &isInFragmentOfSizeWrapper3, 
				(python::arg("atom"), python::arg("frag_list"), python::arg("size")));
	python::def("getContainingFragments", &getContainingFragmentsWrapper3,
				(python::arg("atom"), python::arg("frag_list"), python::arg("cont_frag_list")),
				python::with_custodian_and_ward<3, 2>());
	python::def("calcEffectivePolarizability", &calcEffectivePolarizabilityWrapper3, 
				(python::arg("atom"), python::arg("molgraph"), python::arg("damping") = 0.75));

	python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper4,
				(python::arg("atom"), python::arg("molgraph"), python::arg("type"), (python::arg("strict") = true)));
	python::def("getAtomCount", &getAtomCountWrapper4,
				(python::arg("atom"), python::arg("molgraph"), python::arg("type"), (python::arg("strict") = true)));

	python::def("getExplicitBondCount", &getExplicitBondCountWrapper5,
				(python::arg("atom"), python::arg("molgraph"), python::arg("order"), python::arg("type"), (python::arg("strict") = true)));
	python::def("getBondCount", &getBondCountWrapper5,
				(python::arg("atom"), python::arg("molgraph"), python::arg("order"), python::arg("type"), (python::arg("strict") = true)));

	python::def("buildMatchExpressionString", &buildMatchExpressionStringWrapper,
				(python::arg("atom"), python::arg("molgraph")));

	python::def("getConnectedAtoms", &getConnectedAtomsWrapper,
				(python::arg("atom"), python::arg("molgraph"), python::arg("atoms")));
	python::def("getIncidentBonds", &getIncidentBondsWrapper,
				(python::arg("atom"), python::arg("molgraph"), python::arg("bonds")));
	python::def("getConnectedAtomsAndBonds", &getConnectedAtomsAndBondsWrapper, 
				(python::arg("atom"), python::arg("molgraph"), python::arg("atoms"), python::arg("bonds")));

	python::def("getMatchConstraints", &getMatchConstraintsWrapper1, python::arg("atom"), 
				python::return_value_policy<python::copy_const_reference, python::with_custodian_and_ward_postcall<0, 1> >());
	python::def("hasMatchConstraints", &hasMatchConstraintsWrapper1, python::arg("atom"));
	python::def("setMatchConstraints", &Chem::setMatchConstraints, 
				(python::arg("atom"), python::arg("constr")));
	python::def("clearMatchConstraints", &Chem::clearMatchConstraints, python::arg("atom"));

	python::def("atomTypesMatch", &Chem::atomTypesMatch, (python::arg("qry_type"), python::arg("tgt_type")));

	EXPORT_ATOM_FUNCS_COPY_REF(Name, name)
	EXPORT_ATOM_FUNCS_COPY_REF(Symbol, symbol)
	EXPORT_ATOM_FUNCS(UnpairedElectronCount, count)
	EXPORT_ATOM_FUNCS(Type, type)
	EXPORT_ATOM_FUNCS(FormalCharge, charge)
	EXPORT_ATOM_FUNCS(ImplicitHydrogenCount, count)
	EXPORT_ATOM_FUNCS(Isotope, isotope)
	EXPORT_ATOM_FUNCS(RadicalType, type)
	EXPORT_ATOM_FUNCS(HybridizationState, state)
	EXPORT_ATOM_FUNCS(AromaticityFlag, aromatic)
	EXPORT_ATOM_FUNCS(RingFlag, in_ring)
	EXPORT_ATOM_FUNCS_INT_REF(2DCoordinates, coords)
	EXPORT_ATOM_FUNCS_COPY_REF(3DCoordinatesArray, coords_array)
	EXPORT_ATOM_FUNCS(MorganNumber, num)
	EXPORT_ATOM_FUNCS(CanonicalNumber, num)
	EXPORT_ATOM_FUNCS(CIPPriority, priority)
	EXPORT_ATOM_FUNCS(SymmetryClass, class_id)
	EXPORT_ATOM_FUNCS(CIPConfiguration, config)
	EXPORT_ATOM_FUNCS(MDLParity, parity)
	EXPORT_ATOM_FUNCS(ReactionAtomMappingID, id)
	EXPORT_ATOM_FUNCS(ComponentGroupID, id)
	EXPORT_ATOM_FUNCS(ReactionCenterStatus, status)
	EXPORT_ATOM_FUNCS(PEOECharge, charge)
	EXPORT_ATOM_FUNCS(StereoCenterFlag, is_center)
	EXPORT_ATOM_FUNCS(MDLStereoCareFlag, flag)
    EXPORT_ATOM_FUNCS_COPY_REF_CW(MatchExpression, expr)
	EXPORT_ATOM_FUNCS_COPY_REF(MatchExpressionString, expr_str)
    EXPORT_ATOM_FUNCS_INT_REF_CW(StereoDescriptor, descr)
	EXPORT_ATOM_FUNCS(SybylType, type)
	EXPORT_ATOM_FUNCS(MOL2Charge, charge)
	EXPORT_ATOM_FUNCS_COPY_REF(MOL2Name, name)
	EXPORT_ATOM_FUNCS(MOL2SubstructureID, id)
	EXPORT_ATOM_FUNCS_COPY_REF(MOL2SubstructureName, name)
	EXPORT_ATOM_FUNCS_COPY_REF(MOL2SubstructureSubtype, subtype)
	EXPORT_ATOM_FUNCS_COPY_REF(MOL2SubstructureChain, chain)
}
