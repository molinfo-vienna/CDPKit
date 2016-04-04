/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/INCHIReturnCode.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_MOLGRAPH_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return get##FUNC_SUFFIX(molgraph);                                 \
}                                                                      \
                                                                       \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::MolecularGraph& molgraph)   \
{                                                                      \
	return has##FUNC_SUFFIX(molgraph);                                 \
}

#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("molgraph"),                              \
            python::return_value_policy<python::copy_const_reference,                                            \
			python::with_custodian_and_ward_postcall<0, 1> >());                                                 \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("molgraph"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());                                                            


namespace
{

	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, Name)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, MDLUserInitials)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, MDLProgramName)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::time_t, MDLTimestamp)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, MDLRegistryNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, MDLDimensionality)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, MDLComment)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::MDLDataBlock::SharedPointer&, MDLStructureData)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(unsigned int, MDLCTABVersion)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(long, MDLScalingFactor1)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(double, MDLScalingFactor2)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(double, MDLEnergy)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(bool, MDLChiralFlag)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(double, StoichiometricNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::MatchExpression<CDPL::Chem::MolecularGraph>::SharedPointer&, MatchExpression)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::FragmentList::SharedPointer&, ComponentGroups)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::FragmentList::SharedPointer&, Components)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::FragmentList::SharedPointer&, Rings)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::FragmentList::SharedPointer&, SSSR)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::Fragment::SharedPointer&, CyclicSubstructure)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::Fragment::SharedPointer&, AromaticSubstructure)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Math::ULMatrix::SharedPointer&, TopologicalDistanceMatrix)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Math::DMatrix::SharedPointer&, GeometricalDistanceMatrix)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, ConformationIndex)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const std::string&, ResidueCode)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, ResidueSequenceNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(char, ResidueInsertionCode)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(char, ChainID)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(std::size_t, ModelNumber)
	MAKE_MOLGRAPH_FUNC_WRAPPERS(const CDPL::Chem::PDBData::SharedPointer&, PDBData)

	MAKE_FUNCTION_WRAPPER1(const CDPL::Chem::MatchConstraintList::SharedPointer&, getMatchConstraints, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(bool, hasMatchConstraints, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::MatchExpression<CDPL::Chem::MolecularGraph>::SharedPointer, buildMatchExpression, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveComponentGroups, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveComponents, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveRings, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveSSSR, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, perceiveAromaticRings, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::FragmentList::SharedPointer, extractAromaticSSSRSubset, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::Fragment::SharedPointer, perceiveCyclicSubstructure, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(CDPL::Chem::Fragment::SharedPointer, perceiveAromaticSubstructure, CDPL::Chem::MolecularGraph&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcTopologicalRadius, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcTopologicalDiameter, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcRingComplexity, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcKierShape1, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcKierShape2, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcKierShape3, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcWienerIndex, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcRandicIndex, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcZagrebIndex1, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcZagrebIndex2, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcTotalWalkCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcCyclomaticNumber, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getAtomCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getImplicitHydrogenCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getChainAtomCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getHydrogenAcceptorAtomCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getHydrogenDonorAtomCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getBondCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getHydrogenBondCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getChainBondCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, getRotatableBondCount, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcMass, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcXLogP, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcLogS, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcTPSA, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(std::size_t, calcRuleOfFiveScore, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcMeanPolarizability, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER1(double, calcMolecularComplexity, CDPL::Chem::MolecularGraph&);

	MAKE_FUNCTION_WRAPPER2(void, extractReactionCenter, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&)
	MAKE_FUNCTION_WRAPPER2(void, buildAdjacencyMatrix, CDPL::Chem::MolecularGraph&, CDPL::Math::ULMatrix&)
	MAKE_FUNCTION_WRAPPER2(void, buildIncidenceMatrix, CDPL::Chem::MolecularGraph&, CDPL::Math::ULMatrix&)
	MAKE_FUNCTION_WRAPPER2(void, buildBondMatrix, CDPL::Chem::MolecularGraph&, CDPL::Math::ULMatrix&)
	MAKE_FUNCTION_WRAPPER2(void, buildBondElectronMatrix, CDPL::Chem::MolecularGraph&, CDPL::Math::ULMatrix&)
	MAKE_FUNCTION_WRAPPER2(void, calcTopologicalDistanceMatrix, CDPL::Chem::MolecularGraph&, CDPL::Math::ULMatrix&)
	MAKE_FUNCTION_WRAPPER2(std::size_t, getAtomCount, CDPL::Chem::MolecularGraph&, unsigned int);
	MAKE_FUNCTION_WRAPPER2(void, calcMassComposition, CDPL::Chem::MolecularGraph&, CDPL::Chem::MassComposition&);
    MAKE_FUNCTION_WRAPPER2(void, buildElementHistogram, CDPL::Chem::MolecularGraph&, CDPL::Chem::ElementHistogram&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getOrdinaryHydrogenCount, CDPL::Chem::MolecularGraph&, unsigned int);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getExplicitOrdinaryHydrogenCount, CDPL::Chem::MolecularGraph&, unsigned int);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getBondCount, CDPL::Chem::MolecularGraph&, std::size_t);

	MAKE_FUNCTION_WRAPPER5(CDPL::Base::uint64, calcHashCode, CDPL::Chem::MolecularGraph&,
	 					   unsigned int, unsigned int, bool, bool)

	boost::python::object generateSMILESWrapper(CDPL::Chem::MolecularGraph& molgraph, bool canonical, bool ord_h_deplete,
												unsigned int atom_flags, unsigned int bond_flags)
	{
		std::string smiles;

		if (!generateSMILES(molgraph, smiles, canonical, ord_h_deplete, atom_flags, bond_flags))
			return boost::python::object();

		return boost::python::str(smiles.c_str());
	} 

	boost::python::object generateINCHIWrapper(CDPL::Chem::MolecularGraph& molgraph, const std::string& options, std::size_t dim)
	{
		std::string inchi;

		if (generateINCHI(molgraph, inchi, options, dim) != CDPL::Chem::INCHIReturnCode::OKAY)
			return boost::python::object();

		return boost::python::str(inchi.c_str());
	} 

	boost::python::object generateINCHIKeyWrapper(CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string inchi_key;

		if (generateINCHIKey(molgraph, inchi_key) != CDPL::Chem::INCHIReturnCode::OKAY)
			return boost::python::object();

		return boost::python::str(inchi_key.c_str());
	} 

	std::string buildMassCompositionStringWrapper(CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMassCompositionString(molgraph, str);
		return str;
	}

	std::string buildMolecularFormulaWrapper(CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMolecularFormula(molgraph, str);
		return str;
	}
}


void CDPLPythonChem::exportMolecularGraphFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("setAtomMatchConstraints", &Chem::setAtomMatchConstraints, 
				(python::arg("molgraph"), python::arg("constr"), python::arg("overwrite")));
	python::def("setBondMatchConstraints", &Chem::setBondMatchConstraints, 
				(python::arg("molgraph"), python::arg("constr"), python::arg("overwrite")));
	python::def("buildMatchExpressions", &Chem::buildMatchExpressions, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("initSubstructureSearchQuery", &Chem::initSubstructureSearchQuery, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("initSubstructureSearchTarget", &Chem::initSubstructureSearchTarget, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcGeometricalDistanceMatrix", &Chem::calcGeometricalDistanceMatrix, 
				(python::arg("molgraph"), python::arg("overwrite")));
 	python::def("calcPEOECharges", &Chem::calcPEOECharges, 
				(python::arg("molgraph"), python::arg("overwrite"), 
				 python::arg("num_iter") = 6, python::arg("damping") = 0.5));
	python::def("generate2DCoordinates", &Chem::generate2DCoordinates, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("generateHydrogen3DCoordinates", &Chem::generateHydrogen3DCoordinates, 
				(python::arg("molgraph"), python::arg("undef_only") = true));
	python::def("generateBond2DStereoFlags", &Chem::generateBond2DStereoFlags, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("generateBondDirections", &Chem::generateBondDirections,
				(python::arg("molgraph"), python::arg("overwrite"), 
				 python::arg("ring_bonds") = true, python::arg("min_ring_size") = 8));
	python::def("calcCIPPriorities", &Chem::calcCIPPriorities,
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("perceiveSymmetryClasses", &Chem::perceiveSymmetryClasses, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT, 
				 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT, python::arg("inc_impl_h") = true));
	python::def("generateCanonicalNumbering", &Chem::generateCanonicalNumbering, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT,
				 python::arg("bond_flags") =  Chem::BondPropertyFlag::DEFAULT));
	python::def("generateMorganNumbering", &Chem::generateMorganNumbering, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcImplicitHydrogenCounts", &Chem::calcImplicitHydrogenCounts, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcFormalCharges", &Chem::calcFormalCharges,
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("perceiveHybridizationStates", &Chem::perceiveHybridizationStates, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("kekulizeBonds", &Chem::kekulizeBonds, 
				python::arg("molgraph"));
	python::def("perceiveBondOrders", &Chem::perceiveBondOrders, 
				(python::arg("molgraph"), python::arg("undef_only") = true));
	python::def("perceiveAtomStereoCenters", &Chem::perceiveAtomStereoCenters, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("perceiveBondStereoCenters", &Chem::perceiveBondStereoCenters,
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("min_ring_size") = 8));
	python::def("calcMDLParities", &Chem::calcMDLParities,
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcAtomStereoDescriptors", &Chem::calcAtomStereoDescriptors,
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("dim") = 1));
	python::def("calcAtomStereoDescriptorsFromMDLParities", &Chem::calcAtomStereoDescriptorsFromMDLParities,
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcBondStereoDescriptors", &Chem::calcBondStereoDescriptors,
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("dim") = 1, python::arg("min_ring_size") = 8));
	python::def("calcAtomCIPConfigurations", &Chem::calcAtomCIPConfigurations, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcBondCIPConfigurations", &Chem::calcBondCIPConfigurations,
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("buildMatchExpressionStrings", &Chem::buildMatchExpressionStrings, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("setAromaticityFlags", &Chem::setAromaticityFlags, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("setRingFlags", &Chem::setRingFlags, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("setAtomTypesFromSymbols", &Chem::setAtomTypesFromSymbols, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("setAtomSymbolsFromTypes", &Chem::setAtomSymbolsFromTypes,
				(python::arg("molgraph"), python::arg("overwrite")));

	python::def("buildMatchExpression", &buildMatchExpressionWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveComponentGroups", &perceiveComponentGroupsWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveComponents", &perceiveComponentsWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveRings", &perceiveRingsWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveAromaticRings", &perceiveAromaticRingsWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("extractAromaticSSSRSubset", &extractAromaticSSSRSubsetWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveSSSR", &perceiveSSSRWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveCyclicSubstructure", &perceiveCyclicSubstructureWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveAromaticSubstructure", &perceiveAromaticSubstructureWrapper1,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());

	python::def("buildMatchExpression", 
				static_cast<Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::buildMatchExpression),
                (python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveComponentGroups",
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveComponentGroups),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveComponents", 
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveComponents),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveRings", 
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveRings),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveSSSR",
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveSSSR),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveCyclicSubstructure", 
				static_cast<Chem::Fragment::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveCyclicSubstructure),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveAromaticSubstructure", 
				static_cast<Chem::Fragment::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveAromaticSubstructure),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
     python::def("calcTopologicalDistanceMatrix", 
				static_cast<Math::ULMatrix::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::calcTopologicalDistanceMatrix),
	 			(python::arg("molgraph"), python::arg("overwrite")));
 
	python::def("extractReactionCenter",  &extractReactionCenterWrapper2, 
				(python::arg("molgraph"), python::arg("rxn_center")),
				python::with_custodian_and_ward<2, 1>());
    python::def("buildAdjacencyMatrix",  &buildAdjacencyMatrixWrapper2,
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildIncidenceMatrix",  &buildIncidenceMatrixWrapper2,
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildBondMatrix",  &buildBondMatrixWrapper2, 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildBondElectronMatrix",  &buildBondElectronMatrixWrapper2, 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("calcTopologicalDistanceMatrix",  &calcTopologicalDistanceMatrixWrapper2, 
				(python::arg("molgraph"), python::arg("mtx")));
 	python::def("calcTopologicalRadius", &calcTopologicalRadiusWrapper1, python::arg("molgraph"));
	python::def("calcTopologicalDiameter", &calcTopologicalDiameterWrapper1, python::arg("molgraph"));
	python::def("calcRingComplexity", &calcRingComplexityWrapper1, python::arg("molgraph"));
	python::def("calcKierShape1", &calcKierShape1Wrapper1, python::arg("molgraph"));
	python::def("calcKierShape2", &calcKierShape2Wrapper1, python::arg("molgraph"));
	python::def("calcKierShape3", &calcKierShape3Wrapper1, python::arg("molgraph"));
	python::def("calcWienerIndex", &calcWienerIndexWrapper1, python::arg("molgraph"));
	python::def("calcRandicIndex", &calcRandicIndexWrapper1, python::arg("molgraph"));
	python::def("calcZagrebIndex1", &calcZagrebIndex1Wrapper1, python::arg("molgraph"));
	python::def("calcZagrebIndex2", &calcZagrebIndex2Wrapper1, python::arg("molgraph"));
	python::def("calcTotalWalkCount", &calcTotalWalkCountWrapper1, python::arg("molgraph"));
	python::def("calcCyclomaticNumber", &calcCyclomaticNumberWrapper1, python::arg("molgraph"));
	python::def("getAtomCount", &getAtomCountWrapper1, python::arg("molgraph"));
	python::def("getAtomCount", &getAtomCountWrapper2, (python::arg("molgraph"), python::arg("type")));
	python::def("getImplicitHydrogenCount", &getImplicitHydrogenCountWrapper1, python::arg("molgraph"));
	python::def("getOrdinaryHydrogenCount", &getOrdinaryHydrogenCountWrapper2, 
				(python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("getExplicitOrdinaryHydrogenCount", &getExplicitOrdinaryHydrogenCountWrapper2, 
				(python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("getChainAtomCount", &getChainAtomCountWrapper1, python::arg("molgraph"));
	python::def("getHydrogenAcceptorAtomCount", &getHydrogenAcceptorAtomCountWrapper1, python::arg("molgraph"));
	python::def("getHydrogenDonorAtomCount", &getHydrogenDonorAtomCountWrapper1, python::arg("molgraph"));
	python::def("getBondCount", &getBondCountWrapper1, python::arg("molgraph"));
	python::def("getBondCount", &getBondCountWrapper2, (python::arg("molgraph"), python::arg("order")));
	python::def("getHydrogenBondCount", &getHydrogenBondCountWrapper1, python::arg("molgraph"));
	python::def("getChainBondCount", &getChainBondCountWrapper1, python::arg("molgraph"));
	python::def("getRotatableBondCount", &getRotatableBondCountWrapper1, python::arg("molgraph"));
	python::def("calcMass", &calcMassWrapper1, python::arg("molgraph"));
	python::def("calcMassComposition", &calcMassCompositionWrapper2, 
				(python::arg("molgraph"), python::arg("comp")));
	python::def("buildElementHistogram", &buildElementHistogramWrapper2, 
				(python::arg("molgraph"), python::arg("hist")));
	python::def("calcXLogP", &calcXLogPWrapper1, python::arg("molgraph"));
	python::def("calcLogS", &calcLogSWrapper1, python::arg("molgraph"));
	python::def("calcTPSA", &calcTPSAWrapper1, python::arg("molgraph"));
	python::def("calcRuleOfFiveScore", &calcRuleOfFiveScoreWrapper1, python::arg("molgraph"));
	python::def("calcMeanPolarizability", &calcMeanPolarizabilityWrapper1, python::arg("molgraph"));
	python::def("calcMolecularComplexity", &calcMolecularComplexityWrapper1, python::arg("molgraph"));

	python::def("generateINCHI", &generateINCHIWrapper, 
				(python::arg("molgraph"), python::arg("options") = Chem::ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
				 python::arg("dim") = 0));
	python::def("generateINCHIKey", &generateINCHIKeyWrapper, python::arg("molgraph"));
	python::def("generateSMILES", &generateSMILESWrapper, 
				(python::arg("molgraph"), python::arg("canonical") = false, 
				 python::arg("ord_h_deplete") = true, python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT, 
				 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT));
	python::def("calcHashCode", &calcHashCodeWrapper5,
				(python::arg("molgraph"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT,
				 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT, 
				 python::arg("global_stereo") = true, python::arg("ord_h_deplete") = true));
	python::def("buildMassCompositionString", &buildMassCompositionStringWrapper, python::arg("molgraph"));
	python::def("buildMolecularFormula", &buildMolecularFormulaWrapper, python::arg("molgraph"));

	python::def("hasMatchConstraints", &hasMatchConstraintsWrapper1, python::arg("molgraph"));
	python::def("setMatchConstraints", &Chem::setMatchConstraints, 
				(python::arg("molgraph"), python::arg("constr"), python::arg("overwrite") = true));
	python::def("clearMatchConstraints", &Chem::clearMatchConstraints, python::arg("molgraph"));
	python::def("getMatchConstraints", &getMatchConstraintsWrapper1, 
				python::arg("molgraph"), python::return_value_policy<python::copy_const_reference, 
				python::with_custodian_and_ward_postcall<0, 1> >());

	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(AromaticSubstructure, substruct)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(CyclicSubstructure, substruct)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(SSSR, sssr)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(Rings, rings)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(MatchExpression, expr)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(ComponentGroups, comp_groups)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(Components, comps)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(Name, name)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLUserInitials, initials)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLProgramName, name)
	EXPORT_MOLGRAPH_FUNCS(MDLTimestamp, time)
	EXPORT_MOLGRAPH_FUNCS(MDLRegistryNumber, reg_no)
	EXPORT_MOLGRAPH_FUNCS(MDLDimensionality, dim)
	EXPORT_MOLGRAPH_FUNCS(MDLScalingFactor1, factor)
	EXPORT_MOLGRAPH_FUNCS(MDLScalingFactor2, factor)
	EXPORT_MOLGRAPH_FUNCS(MDLEnergy, energy)
	EXPORT_MOLGRAPH_FUNCS(MDLChiralFlag, flag)
	EXPORT_MOLGRAPH_FUNCS(StoichiometricNumber, num)
	EXPORT_MOLGRAPH_FUNCS(ConformationIndex, index)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(ResidueCode, code)
	EXPORT_MOLGRAPH_FUNCS(ResidueSequenceNumber, seq_no)
	EXPORT_MOLGRAPH_FUNCS(ResidueInsertionCode, code)
	EXPORT_MOLGRAPH_FUNCS(ChainID, id)
	EXPORT_MOLGRAPH_FUNCS(ModelNumber, model_no)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(PDBData, data)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLComment, comment)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLStructureData, data)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(TopologicalDistanceMatrix, mtx)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(GeometricalDistanceMatrix, mtx)
	EXPORT_MOLGRAPH_FUNCS(MDLCTABVersion, version)
}
