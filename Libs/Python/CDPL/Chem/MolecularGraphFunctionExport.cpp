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


#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"));                                \
python::def("has"#FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));                                \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"),                                 \
            python::return_value_policy<python::copy_const_reference>());                                        \
python::def("has"#FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));                                \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME))); 

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"),                                 \
            python::return_value_policy<python::copy_const_reference,                                            \
			python::with_custodian_and_ward_postcall<0, 1> >());                                                 \
python::def("has"#FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));                                \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());                                                            


namespace
{

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

	boost::python::object buildMassCompositionStringWrapper(CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMassCompositionString(molgraph, str);

		return boost::python::str(str.c_str());
	}

	boost::python::object buildMolecularFormulaWrapper(CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMolecularFormula(molgraph, str);

		return boost::python::str(str.c_str());
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
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("perceiveAtomStereoCenters", &Chem::perceiveAtomStereoCenters, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("check_cip_sym") = true, 
				 python::arg("check_acyclic_subst_sym_only") = false));
	python::def("perceiveBondStereoCenters", &Chem::perceiveBondStereoCenters,
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("check_cip_sym") = true, python::arg("min_ring_size") = 8));
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
	python::def("perceiveSybylAtomTypes", &Chem::perceiveSybylAtomTypes, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("calcAtomHydrophobicities", &Chem::calcAtomHydrophobicities, 
				(python::arg("molgraph"), python::arg("overwrite")));
	python::def("containsMolecularGraph", &Chem::containsMolecularGraph, 
				(python::arg("molgraph"), python::arg("sub_molgraph"), python::arg("atoms") = true, python::arg("bonds") = true));
	python::def("getContainingFragments", &Chem::getContainingFragments, 
				(python::arg("molgraph"), python::arg("frag_list"), python::arg("cont_frag_list"), 
				 python::arg("append") = false, python::arg("atoms") = true, python::arg("bonds") = true));
	python::def("getContainedFragments", &Chem::getContainedFragments, 
				(python::arg("molgraph"), python::arg("frag_list"), python::arg("cont_frag_list"), 
				 python::arg("append") = false, python::arg("atoms") = true, python::arg("bonds") = true));
	python::def("splitIntoFragments", &Chem::splitIntoFragments, 
				(python::arg("molgraph"), python::arg("frag_list"), python::arg("split_bond_mask"), 
				 python::arg("append") = false));

	python::def("buildMatchExpression", static_cast<Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::buildMatchExpression),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("buildMatchExpression", 
				static_cast<Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::buildMatchExpression),
                (python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveComponentGroups", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveComponentGroups),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveComponentGroups",
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveComponentGroups),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveComponents", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveComponents),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveComponents", 
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveComponents),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveRings", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveRings),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveRings", 
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveRings),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveSSSR", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveSSSR),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveSSSR",
				static_cast<Chem::FragmentList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveSSSR),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
  	python::def("extractSSSR", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&)>(&Chem::extractSSSR),
	 			(python::arg("src_molgraph"), python::arg("tgt_molgraph")),
				python::with_custodian_and_ward_postcall<0, 1>());
	python::def("extractSSSR", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&, Chem::MolecularGraph&, bool)>(&Chem::extractSSSR),
	 			(python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("overwrite")),
				python::with_custodian_and_ward_postcall<0, 1>());
	python::def("copySSSR", &Chem::copySSSR,
	 			(python::arg("src_molgraph"), python::arg("tgt_molgraph")),
				python::with_custodian_and_ward_postcall<0, 2>());
	python::def("perceiveCyclicSubstructure", static_cast<Chem::Fragment::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveCyclicSubstructure),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveCyclicSubstructure", 
				static_cast<Chem::Fragment::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveCyclicSubstructure),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveAromaticSubstructure", static_cast<Chem::Fragment::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceiveAromaticSubstructure),
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceiveAromaticSubstructure", 
				static_cast<Chem::Fragment::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceiveAromaticSubstructure),
	 			(python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("perceiveAromaticRings", &Chem::perceiveAromaticRings,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("extractAromaticSSSRSubset", &Chem::extractAromaticSSSRSubset,
	 			python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
	python::def("calcTopologicalDistanceMatrix", 
				static_cast<Math::ULMatrix::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::calcTopologicalDistanceMatrix),
				(python::arg("molgraph"), python::arg("overwrite")));
    python::def("extractTopologicalDistanceMatrix", 
				static_cast<Math::ULMatrix::SharedPointer (*)(const Chem::MolecularGraph&, Chem::MolecularGraph&, bool)>(&Chem::extractTopologicalDistanceMatrix),
				(python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("overwrite")));
 
	python::def("extractReactionCenter", &Chem::extractReactionCenter, 
				(python::arg("molgraph"), python::arg("rxn_center")),
				python::with_custodian_and_ward<2, 1>());
    python::def("buildAdjacencyMatrix", &Chem::buildAdjacencyMatrix,
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildIncidenceMatrix", &Chem::buildIncidenceMatrix,
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildBondMatrix", &Chem::buildBondMatrix, 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildBondAtomTypeMatrix", &Chem::buildBondAtomTypeMatrix, 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("buildBondElectronMatrix", &Chem::buildBondElectronMatrix, 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("calcTopologicalDistanceMatrix", static_cast<void (*)(const Chem::MolecularGraph&, Math::ULMatrix&)>(&Chem::calcTopologicalDistanceMatrix), 
				(python::arg("molgraph"), python::arg("mtx")));
	python::def("calcTopologicalDistanceMatrix",  static_cast<void (*)(const Chem::MolecularGraph&, Math::SparseULMatrix&)>(&Chem::calcTopologicalDistanceMatrix), 
				(python::arg("molgraph"), python::arg("mtx")));
    python::def("extractTopologicalDistanceMatrix", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Math::ULMatrix&)>(&Chem::extractTopologicalDistanceMatrix), 
				(python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("mtx")));
	python::def("extractTopologicalDistanceMatrix",  static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Math::SparseULMatrix&)>(&Chem::extractTopologicalDistanceMatrix), 
				(python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("mtx")));

 	python::def("calcTopologicalRadius", &Chem::calcTopologicalRadius, python::arg("molgraph"));
	python::def("calcTopologicalDiameter", &Chem::calcTopologicalDiameter, python::arg("molgraph"));
	python::def("calcRingComplexity", &Chem::calcRingComplexity, python::arg("molgraph"));
	python::def("calcKierShape1", &Chem::calcKierShape1, python::arg("molgraph"));
	python::def("calcKierShape2", &Chem::calcKierShape2, python::arg("molgraph"));
	python::def("calcKierShape3", &Chem::calcKierShape3, python::arg("molgraph"));
	python::def("calcWienerIndex", &Chem::calcWienerIndex, python::arg("molgraph"));
	python::def("calcRandicIndex", &Chem::calcRandicIndex, python::arg("molgraph"));
	python::def("calcZagrebIndex1", &Chem::calcZagrebIndex1, python::arg("molgraph"));
	python::def("calcZagrebIndex2", &Chem::calcZagrebIndex2, python::arg("molgraph"));
	python::def("calcTotalWalkCount", &Chem::calcTotalWalkCount, python::arg("molgraph"));
	python::def("calcCyclomaticNumber", &Chem::calcCyclomaticNumber, python::arg("molgraph"));
	python::def("getAtomCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&)>(&Chem::getAtomCount),
				python::arg("molgraph"));
	python::def("getAtomCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&, unsigned int)>(&Chem::getAtomCount),
				(python::arg("molgraph"), python::arg("type")));
	python::def("getImplicitHydrogenCount", &Chem::getImplicitHydrogenCount, python::arg("molgraph"));
	python::def("getOrdinaryHydrogenCount", &Chem::getOrdinaryHydrogenCount, 
				(python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("getExplicitOrdinaryHydrogenCount", &Chem::getExplicitOrdinaryHydrogenCount, 
				(python::arg("molgraph"), python::arg("flags") = Chem::AtomPropertyFlag::DEFAULT));
	python::def("getChainAtomCount", &Chem::getChainAtomCount, python::arg("molgraph"));
	python::def("getHydrogenAcceptorAtomCount", &Chem::getHydrogenAcceptorAtomCount, python::arg("molgraph"));
	python::def("getHydrogenDonorAtomCount", &Chem::getHydrogenDonorAtomCount, python::arg("molgraph"));
	python::def("getCompleteBondCount", &Chem::getCompleteBondCount, python::arg("molgraph"));
	python::def("getBondCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&)>(&Chem::getBondCount),
				python::arg("molgraph"));
	python::def("getBondCount", static_cast<std::size_t (*)(const Chem::MolecularGraph&, std::size_t)>(&Chem::getBondCount),
				(python::arg("molgraph"), python::arg("order")));
	python::def("getHydrogenBondCount", &Chem::getHydrogenBondCount, python::arg("molgraph"));
	python::def("getChainBondCount", &Chem::getChainBondCount, python::arg("molgraph"));
	python::def("getComponentCount", &Chem::getComponentCount, python::arg("molgraph"));
	python::def("calcMass", &Chem::calcMass, python::arg("molgraph"));
	python::def("calcMassComposition", &Chem::calcMassComposition, 
				(python::arg("molgraph"), python::arg("comp")));
	python::def("buildElementHistogram", &Chem::buildElementHistogram, 
				(python::arg("molgraph"), python::arg("hist")));
	python::def("calcXLogP", &Chem::calcXLogP, python::arg("molgraph"));
	python::def("calcLogS", &Chem::calcLogS, python::arg("molgraph"));
	python::def("calcTPSA", &Chem::calcTPSA, python::arg("molgraph"));
	python::def("calcRuleOfFiveScore", &Chem::calcRuleOfFiveScore, python::arg("molgraph"));
	python::def("calcMeanPolarizability", &Chem::calcMeanPolarizability, python::arg("molgraph"));
	python::def("calcMolecularComplexity", &Chem::calcMolecularComplexity, python::arg("molgraph"));
	python::def("getRotatableBondCount", &Chem::getRotatableBondCount, 
				(python::arg("molgraph"), python::arg("inc_h_rotors"), python::arg("inc_amide_bonds")));

	python::def("generateINCHI", &generateINCHIWrapper, 
				(python::arg("molgraph"), python::arg("options") = Chem::ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
				 python::arg("dim") = 0));
	python::def("generateINCHIKey", &generateINCHIKeyWrapper, python::arg("molgraph"));
	python::def("generateSMILES", &generateSMILESWrapper, 
				(python::arg("molgraph"), python::arg("canonical") = false, 
				 python::arg("ord_h_deplete") = true, python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT, 
				 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT));
	python::def("calcHashCode", &Chem::calcHashCode,
				(python::arg("molgraph"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT,
				 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT, 
				 python::arg("global_stereo") = true, python::arg("ord_h_deplete") = true));
	python::def("buildMassCompositionString", &buildMassCompositionStringWrapper, python::arg("molgraph"));
	python::def("buildMolecularFormula", &buildMolecularFormulaWrapper, python::arg("molgraph"));

	python::def("hasMatchConstraints", &Chem::hasMatchConstraints, python::arg("molgraph"));
	python::def("setMatchConstraints", &Chem::setMatchConstraints, 
				(python::arg("molgraph"), python::arg("constr")));
	python::def("clearMatchConstraints", &Chem::clearMatchConstraints, python::arg("molgraph"));
	python::def("getMatchConstraints", &Chem::getMatchConstraints, 
				python::arg("molgraph"), python::return_value_policy<python::copy_const_reference, 
				python::with_custodian_and_ward_postcall<0, 1> >());

	python::def("canonicalize", static_cast<void (*)(Chem::MolecularGraph& molgraph, bool, bool, bool, bool)>(&Chem::canonicalize), 
				(python::arg("molgraph"), python::arg("atoms") = true, python::arg("atom_nbrs") = true, 
				 python::arg("bonds") = true, python::arg("bond_atoms") = false));
	python::def("canonicalize", static_cast<void (*)(Chem::MolecularGraph& molgraph, const Chem::AtomCompareFunction&, bool, 
													 bool, bool, bool)>(&Chem::canonicalize), 
				(python::arg("molgraph"),  python::arg("func"), python::arg("atoms") = true, 
				 python::arg("atom_nbrs") = true, python::arg("bonds") = true, python::arg("bond_atoms") = false));

	python::def("copyAtomStereoDescriptors", &Chem::copyAtomStereoDescriptors,
				(python::arg("mol_copy"), python::arg("molgraph"), python::arg("atom_idx_offs") = 0));
	python::def("copyBondStereoDescriptors", &Chem::copyBondStereoDescriptors,
				(python::arg("mol_copy"), python::arg("molgraph"), python::arg("atom_idx_offs") = 0, 
				 python::arg("bond_start_idx") = 0));

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
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(ConformerEnergies, energies)
	EXPORT_MOLGRAPH_FUNCS(HashCode, hash_code)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLComment, comment)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(StructureData, data)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(TopologicalDistanceMatrix, mtx)
	EXPORT_MOLGRAPH_FUNCS_COPY_REF(GeometricalDistanceMatrix, mtx)
	EXPORT_MOLGRAPH_FUNCS(MDLCTABVersion, version)
	EXPORT_MOLGRAPH_FUNCS(MOL2ChargeType, type)
	EXPORT_MOLGRAPH_FUNCS(MOL2MoleculeType, type)
}
