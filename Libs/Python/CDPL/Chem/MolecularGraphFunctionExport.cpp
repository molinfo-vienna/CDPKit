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

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/INCHIReturnCode.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define EXPORT_MOLGRAPH_FUNCS(FUNC_SUFFIX, ARG_NAME)                                       \
    python::def("get" #FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"));     \
    python::def("has" #FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));     \
    python::def("clear" #FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph")); \
    python::def("set" #FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)));

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                              \
    python::def("get" #FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"),      \
                python::return_value_policy<python::copy_const_reference>());              \
    python::def("has" #FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));     \
    python::def("clear" #FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph")); \
    python::def("set" #FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)));

#define EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                 \
    python::def("get" #FUNC_SUFFIX, &Chem::get##FUNC_SUFFIX, python::arg("molgraph"),            \
                python::return_value_policy<python::copy_const_reference,                        \
                                            python::with_custodian_and_ward_postcall<0, 1> >()); \
    python::def("has" #FUNC_SUFFIX, &Chem::has##FUNC_SUFFIX, python::arg("molgraph"));           \
    python::def("clear" #FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("molgraph"));       \
    python::def("set" #FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("molgraph"), python::arg(#ARG_NAME)));


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

    MAKE_FUNCTION_WRAPPER4(bool, align2DCoordinates, CDPL::Chem::MolecularGraph&, CDPL::Chem::AtomContainer&, const CDPL::Math::Vector2DArray&, bool);
}


void CDPLPythonChem::exportMolecularGraphFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("setAtomMatchConstraints", &Chem::setAtomMatchConstraints, 
                (python::arg("molgraph"), python::arg("constr"), python::arg("overwrite")));
    python::def("setBondMatchConstraints", &Chem::setBondMatchConstraints, 
                (python::arg("molgraph"), python::arg("constr"), python::arg("overwrite")));
    python::def("generateMatchExpressions", &Chem::generateMatchExpressions, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("initSubstructureSearchQuery", &Chem::initSubstructureSearchQuery, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("initSubstructureSearchTarget", &Chem::initSubstructureSearchTarget, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcGeometricalDistanceMatrix", &Chem::calcGeometricalDistanceMatrix, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calc2DCoordinates", &Chem::calc2DCoordinates, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("align2DCoordinates", &align2DCoordinatesWrapper4, (python::arg("cntnr"), python::arg("ref_atoms"),
                                                                    python::arg("ref_coords"), python::arg("fix_bond_stereo") = true));
    python::def("calcHydrogen3DCoordinates", &Chem::calcHydrogen3DCoordinates, 
                (python::arg("molgraph"), python::arg("undef_only") = true));
    python::def("calcBond2DStereoFlags", &Chem::calcBond2DStereoFlags, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcCIPPriorities", &Chem::calcCIPPriorities,
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("perceiveSymmetryClasses", &Chem::perceiveSymmetryClasses, 
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT, 
                 python::arg("bond_flags") = Chem::BondPropertyFlag::DEFAULT, python::arg("inc_impl_h") = true));
    python::def("calcCanonicalNumbering", &Chem::calcCanonicalNumbering, 
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("atom_flags") = Chem::AtomPropertyFlag::DEFAULT,
                 python::arg("bond_flags") =  Chem::BondPropertyFlag::DEFAULT));
    python::def("calcMorganNumbering", &Chem::calcMorganNumbering, 
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
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("check_asym") = true,
                 python::arg("check_inv_n") = true, python::arg("check_quart_n") = true, python::arg("check_plan_n") = true,
                 python::arg("check_amide_n") = true, python::arg("check_res_ctrs") = true));
    python::def("perceiveBondStereoCenters", &Chem::perceiveBondStereoCenters,
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("check_asym") = true,
                 python::arg("check_term_n") = true, python::arg("check_order") = true, python::arg("min_ring_size") = 8));
    python::def("calcMDLParities", &Chem::calcMDLParities,
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcAtomStereoDescriptors", &Chem::calcAtomStereoDescriptors,
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("dim") = 1,
                 python::arg("check_stc_flag") = true));
    python::def("calcAtomStereoDescriptorsFromMDLParities", &Chem::calcAtomStereoDescriptorsFromMDLParities,
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcBondStereoDescriptors", &Chem::calcBondStereoDescriptors,
                (python::arg("molgraph"), python::arg("overwrite"), python::arg("dim") = 1,
                 python::arg("check_stc_flag") = true));
    python::def("calcAtomCIPConfigurations", &Chem::calcAtomCIPConfigurations, 
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcBondCIPConfigurations", &Chem::calcBondCIPConfigurations,
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("generateMatchExpressionStrings", &Chem::generateMatchExpressionStrings, 
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
    python::def("containsMolecularGraph", &Chem::containsMolecularGraph, 
                (python::arg("molgraph"), python::arg("sub_molgraph"), python::arg("atoms") = true,
                 python::arg("bonds") = true));
    python::def("getContainingFragments", &Chem::getContainingFragments, 
                (python::arg("molgraph"), python::arg("frag_list"), python::arg("cont_frag_list"), 
                 python::arg("append") = false, python::arg("atoms") = true, python::arg("bonds") = true));
    python::def("getContainedFragments", &Chem::getContainedFragments, 
                (python::arg("molgraph"), python::arg("frag_list"), python::arg("cont_frag_list"), 
                 python::arg("append") = false, python::arg("atoms") = true, python::arg("bonds") = true));
    python::def("splitIntoFragments", &Chem::splitIntoFragments, 
                (python::arg("molgraph"), python::arg("frag_list"), python::arg("split_bond_mask"), 
                 python::arg("append") = false));

    python::def("generateMatchExpression", static_cast<Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::generateMatchExpression),
                 python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("generateMatchExpression", 
                static_cast<Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::generateMatchExpression),
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
    python::def("extractSSSRSubset", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&)>(&Chem::extractSSSRSubset),
                (python::arg("src_molgraph"), python::arg("tgt_molgraph")),
                python::with_custodian_and_ward_postcall<0, 1>());
    python::def("extractSSSRSubset", static_cast<Chem::FragmentList::SharedPointer (*)(const Chem::MolecularGraph&, Chem::MolecularGraph&, bool)>(&Chem::extractSSSRSubset),
                (python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("overwrite")),
                python::with_custodian_and_ward_postcall<0, 1>());
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
    python::def("getAromaticRings", &Chem::getAromaticRings,
                python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("getAromaticSSSRSubset", &Chem::getAromaticSSSRSubset,
                python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("calcTopologicalDistanceMatrix",
                static_cast<Math::ULMatrix::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::calcTopologicalDistanceMatrix),
                (python::arg("molgraph"), python::arg("overwrite")));
    python::def("calcTopologicalDistanceMatrix", static_cast<void (*)(const Chem::MolecularGraph&, Math::ULMatrix&)>(&Chem::calcTopologicalDistanceMatrix), 
                (python::arg("molgraph"), python::arg("mtx")));
    python::def("extractTopologicalDistanceSubMatrix", 
                static_cast<Math::ULMatrix::SharedPointer (*)(const Chem::MolecularGraph&, Chem::MolecularGraph&, bool)>(&Chem::extractTopologicalDistanceSubMatrix),
                (python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("overwrite")));
    python::def("extractTopologicalDistanceSubMatrix", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Math::ULMatrix&)>(&Chem::extractTopologicalDistanceSubMatrix), 
                (python::arg("src_molgraph"), python::arg("tgt_molgraph"), python::arg("mtx")));
     python::def("extractReactionCenter", &Chem::extractReactionCenter, 
                (python::arg("molgraph"), python::arg("rxn_center")),
                python::with_custodian_and_ward<2, 1>());
    python::def("generateAdjacencyMatrix", &Chem::generateAdjacencyMatrix,
                (python::arg("molgraph"), python::arg("mtx")));
    python::def("generateIncidenceMatrix", &Chem::generateIncidenceMatrix,
                (python::arg("molgraph"), python::arg("mtx")));
    python::def("generateBondMatrix", &Chem::generateBondMatrix, 
                (python::arg("molgraph"), python::arg("mtx")));
    python::def("generateBondAtomTypeMatrix", &Chem::generateBondAtomTypeMatrix, 
                (python::arg("molgraph"), python::arg("mtx")));
    python::def("generateBondElectronMatrix", &Chem::generateBondElectronMatrix, 
                (python::arg("molgraph"), python::arg("mtx")));

    python::def("perceivePiElectronSystems", static_cast<Chem::ElectronSystemList::SharedPointer (*)(const Chem::MolecularGraph&)>(&Chem::perceivePiElectronSystems),
                 python::arg("molgraph"), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("perceivePiElectronSystems",
                static_cast<Chem::ElectronSystemList::SharedPointer (*)(Chem::MolecularGraph&, bool)>(&Chem::perceivePiElectronSystems),
                 (python::arg("molgraph"), python::arg("overwrite")), python::with_custodian_and_ward_postcall<0, 1>());
    python::def("getCompleteBondCount", &Chem::getCompleteBondCount, python::arg("molgraph"));
        
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
                 python::arg("ord_h_deplete") = true));

    python::def("canonicalize", static_cast<void (*)(Chem::MolecularGraph& molgraph, bool, bool, bool, bool)>(&Chem::canonicalize), 
                (python::arg("molgraph"), python::arg("atoms") = true, python::arg("atom_nbrs") = true, 
                 python::arg("bonds") = true, python::arg("bond_atoms") = false));
    python::def("canonicalize", static_cast<void (*)(Chem::MolecularGraph& molgraph, const Chem::AtomCompareFunction&, bool, 
                                                     bool, bool, bool)>(&Chem::canonicalize), 
                (python::arg("molgraph"),  python::arg("func"), python::arg("atoms") = true, 
                 python::arg("atom_nbrs") = true, python::arg("bonds") = true, python::arg("bond_atoms") = false));

    python::def("translateFragment", &Chem::translateFragment,
                (python::arg("src_molgraph"), python::arg("src_frag"), python::arg("tgt_molgraph"), python::arg("tgt_frag"),
                 python::arg("append") = false));
    python::def("translateFragments", &Chem::translateFragments,
                (python::arg("src_molgraph"), python::arg("src_frag_list"), python::arg("tgt_molgraph"), python::arg("tgt_frag_list"),
                 python::arg("append") = false));
   
    python::def("setConformation", &Chem::setConformation,
                (python::arg("molgraph"), python::arg("conf_idx"), python::arg("coords"), python::arg("energy")));
    python::def("addConformation", &Chem::addConformation,
                (python::arg("molgraph"), python::arg("coords"), python::arg("energy")));
    python::def("getConformationEnergy", &Chem::getConformationEnergy,
                (python::arg("molgraph"), python::arg("conf_idx")));

    python::def("calcBasicProperties", &Chem::calcBasicProperties,
                (python::arg("molgraph"), python::arg("overwrite")));

    python::def("editSubstructures", &Chem::editSubstructures,
                (python::arg("molgraph"), python::arg("result_mol"), python::arg("search_ptns"),
                 python::arg("result_ptn"), python::arg("exclude_ptns") = std::string()));
 
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(AromaticSubstructure, substruct)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(CyclicSubstructure, substruct)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(SSSR, sssr)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(Rings, rings)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(MatchExpression, expr)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(MatchConstraints, constr)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(ComponentGroups, comp_groups)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(Components, comps)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF_CW(PiElectronSystems, pi_systems)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(Name, name)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(Comment, comment)
    EXPORT_MOLGRAPH_FUNCS(Timestamp, time)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLUserInitials, initials)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(MDLProgramName, name)
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
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(StructureData, data)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(TopologicalDistanceMatrix, mtx)
    EXPORT_MOLGRAPH_FUNCS_COPY_REF(GeometricalDistanceMatrix, mtx)
    EXPORT_MOLGRAPH_FUNCS(MDLCTABVersion, version)
    EXPORT_MOLGRAPH_FUNCS(MOL2ChargeType, type)
    EXPORT_MOLGRAPH_FUNCS(MOL2MoleculeType, type)
}
