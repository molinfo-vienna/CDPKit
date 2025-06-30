/* 
 * MolecularGraphFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP

#include <string>
#include <cstddef>
#include <cstdint>
#include <ctime>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/ElectronSystemList.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
        class AtomMapping;

        CDPL_CHEM_API const std::string& getName(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setName(MolecularGraph& molgraph, const std::string& name);

        CDPL_CHEM_API void clearName(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasName(const MolecularGraph& molgraph);


        CDPL_CHEM_API std::time_t getTimestamp(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setTimestamp(MolecularGraph& molgraph, std::time_t time);

        CDPL_CHEM_API void clearTimestamp(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasTimestamp(const MolecularGraph& molgraph);


        CDPL_CHEM_API const std::string& getComment(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setComment(MolecularGraph& molgraph, const std::string& comment);

        CDPL_CHEM_API void clearComment(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasComment(const MolecularGraph& molgraph);


        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr);

        CDPL_CHEM_API void clearMatchConstraints(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMatchConstraints(const MolecularGraph& molgraph);


        CDPL_CHEM_API const MatchExpression<MolecularGraph>::SharedPointer& getMatchExpression(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMatchExpression(MolecularGraph& molgraph, const MatchExpression<MolecularGraph>::SharedPointer& expr);

        CDPL_CHEM_API void clearMatchExpression(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMatchExpression(const MolecularGraph& molgraph);

        CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer generateMatchExpression(const MolecularGraph& molgraph);

        CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer generateMatchExpression(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const FragmentList::SharedPointer& getRings(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setRings(MolecularGraph& molgraph, const FragmentList::SharedPointer& rings);

        CDPL_CHEM_API void clearRings(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasRings(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const FragmentList::SharedPointer& getSSSR(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setSSSR(MolecularGraph& molgraph, const FragmentList::SharedPointer& sssr);

        CDPL_CHEM_API void clearSSSR(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasSSSR(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API FragmentList::SharedPointer extractSSSRSubset(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer extractSSSRSubset(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite);


        CDPL_CHEM_API const Fragment::SharedPointer& getCyclicSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setCyclicSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

        CDPL_CHEM_API void clearCyclicSubstructure(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasCyclicSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const FragmentList::SharedPointer& getComponents(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setComponents(MolecularGraph& molgraph, const FragmentList::SharedPointer& comps);

        CDPL_CHEM_API void clearComponents(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasComponents(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const FragmentList::SharedPointer& getComponentGroups(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setComponentGroups(MolecularGraph& molgraph, const FragmentList::SharedPointer& comp_groups);

        CDPL_CHEM_API void clearComponentGroups(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasComponentGroups(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API std::size_t getConformationIndex(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setConformationIndex(MolecularGraph& molgraph, std::size_t index);

        CDPL_CHEM_API void clearConformationIndex(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasConformationIndex(const MolecularGraph& molgraph);


        CDPL_CHEM_API const Util::DArray::SharedPointer& getConformerEnergies(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setConformerEnergies(MolecularGraph& molgraph, const Util::DArray::SharedPointer& energies);

        CDPL_CHEM_API void clearConformerEnergies(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasConformerEnergies(const MolecularGraph& molgraph);


        CDPL_CHEM_API void setConformation(MolecularGraph& molgraph, std::size_t conf_idx, const Math::Vector3DArray& coords, double energy);

        CDPL_CHEM_API void addConformation(MolecularGraph& molgraph, const Math::Vector3DArray& coords, double energy);

        CDPL_CHEM_API double getConformationEnergy(const MolecularGraph& molgraph, std::size_t conf_idx);


        CDPL_CHEM_API std::uint64_t getHashCode(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setHashCode(MolecularGraph& molgraph, std::uint64_t hash_code);

        CDPL_CHEM_API void clearHashCode(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasHashCode(const MolecularGraph& molgraph);

        CDPL_CHEM_API std::uint64_t calcHashCode(const MolecularGraph& molgraph, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                 unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool ord_h_deplete = true);


        CDPL_CHEM_API void extractReactionCenter(const MolecularGraph& molgraph, Fragment& rxn_center);


        CDPL_CHEM_API double getStoichiometricNumber(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setStoichiometricNumber(MolecularGraph& molgraph, double num);

        CDPL_CHEM_API void clearStoichiometricNumber(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasStoichiometricNumber(const MolecularGraph& molgraph);


        CDPL_CHEM_API const std::string& getMDLUserInitials(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLUserInitials(MolecularGraph& molgraph, const std::string& initials);

        CDPL_CHEM_API void clearMDLUserInitials(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLUserInitials(const MolecularGraph& molgraph);


        CDPL_CHEM_API const std::string& getMDLProgramName(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLProgramName(MolecularGraph& molgraph, const std::string& name);

        CDPL_CHEM_API void clearMDLProgramName(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLProgramName(const MolecularGraph& molgraph);


        CDPL_CHEM_API std::size_t getMDLRegistryNumber(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLRegistryNumber(MolecularGraph& molgraph, std::size_t reg_no);

        CDPL_CHEM_API void clearMDLRegistryNumber(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLRegistryNumber(const MolecularGraph& molgraph);


        CDPL_CHEM_API unsigned int getMDLCTABVersion(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLCTABVersion(MolecularGraph& molgraph, unsigned int version);

        CDPL_CHEM_API void clearMDLCTABVersion(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLCTABVersion(const MolecularGraph& molgraph);


        CDPL_CHEM_API const StringDataBlock::SharedPointer& getStructureData(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setStructureData(MolecularGraph& molgraph, const StringDataBlock::SharedPointer& data);

        CDPL_CHEM_API void clearStructureData(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasStructureData(const MolecularGraph& molgraph);


        CDPL_CHEM_API std::size_t getMDLDimensionality(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLDimensionality(MolecularGraph& molgraph, std::size_t dim);

        CDPL_CHEM_API void clearMDLDimensionality(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLDimensionality(const MolecularGraph& molgraph);


        CDPL_CHEM_API long getMDLScalingFactor1(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLScalingFactor1(MolecularGraph& molgraph, long factor);

        CDPL_CHEM_API void clearMDLScalingFactor1(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLScalingFactor1(const MolecularGraph& molgraph);


        CDPL_CHEM_API double getMDLScalingFactor2(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLScalingFactor2(MolecularGraph& molgraph, double factor);

        CDPL_CHEM_API void clearMDLScalingFactor2(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLScalingFactor2(const MolecularGraph& molgraph);


        CDPL_CHEM_API double getMDLEnergy(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLEnergy(MolecularGraph& molgraph, double energy);

        CDPL_CHEM_API void clearMDLEnergy(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLEnergy(const MolecularGraph& molgraph);


        CDPL_CHEM_API bool getMDLChiralFlag(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMDLChiralFlag(MolecularGraph& molgraph, bool flag);

        CDPL_CHEM_API void clearMDLChiralFlag(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMDLChiralFlag(const MolecularGraph& molgraph);


        CDPL_CHEM_API unsigned int getMOL2MoleculeType(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMOL2MoleculeType(MolecularGraph& molgraph, unsigned int type);

        CDPL_CHEM_API void clearMOL2MoleculeType(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMOL2MoleculeType(const MolecularGraph& molgraph);


        CDPL_CHEM_API unsigned int getMOL2ChargeType(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setMOL2ChargeType(MolecularGraph& molgraph, unsigned int type);

        CDPL_CHEM_API void clearMOL2ChargeType(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasMOL2ChargeType(const MolecularGraph& molgraph);


        CDPL_CHEM_API void generateAdjacencyMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        CDPL_CHEM_API void generateIncidenceMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        CDPL_CHEM_API void generateBondMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        CDPL_CHEM_API void generateBondElectronMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        CDPL_CHEM_API void generateBondAtomTypeMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);


        CDPL_CHEM_API const Math::ULMatrix::SharedPointer& getTopologicalDistanceMatrix(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setTopologicalDistanceMatrix(MolecularGraph& molgraph, const Math::ULMatrix::SharedPointer& mtx);

        CDPL_CHEM_API void clearTopologicalDistanceMatrix(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasTopologicalDistanceMatrix(const MolecularGraph& molgraph);

        CDPL_CHEM_API Math::ULMatrix::SharedPointer calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

        CDPL_CHEM_API Math::ULMatrix::SharedPointer extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite);

        CDPL_CHEM_API void extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph, Math::ULMatrix& mtx);


        CDPL_CHEM_API const Math::DMatrix::SharedPointer& getGeometricalDistanceMatrix(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setGeometricalDistanceMatrix(MolecularGraph& molgraph, const Math::DMatrix::SharedPointer& mtx);

        CDPL_CHEM_API void clearGeometricalDistanceMatrix(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasGeometricalDistanceMatrix(const MolecularGraph& molgraph);

        CDPL_CHEM_API Math::DMatrix::SharedPointer calcGeometricalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const Fragment::SharedPointer& getAromaticSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setAromaticSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

        CDPL_CHEM_API void clearAromaticSubstructure(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasAromaticSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(const MolecularGraph& molgraph);

        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API const ElectronSystemList::SharedPointer& getPiElectronSystems(const MolecularGraph& molgraph);

        CDPL_CHEM_API void setPiElectronSystems(MolecularGraph& molgraph, const ElectronSystemList::SharedPointer& pi_systems);

        CDPL_CHEM_API void clearPiElectronSystems(MolecularGraph& molgraph);

        CDPL_CHEM_API bool hasPiElectronSystems(const MolecularGraph& molgraph);

        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(const MolecularGraph& molgraph);

        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(MolecularGraph& molgraph, bool overwrite);


        CDPL_CHEM_API bool generateSMILES(const MolecularGraph& molgraph, std::string& smiles, bool canonical = false,
                                          bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                          unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        CDPL_CHEM_API int generateINCHI(const MolecularGraph& molgraph, std::string& inchi,
                                        const std::string& options = ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
                                        std::size_t        dim     = 0);

        CDPL_CHEM_API int generateINCHIKey(const MolecularGraph& molgraph, std::string& inchi_key);

        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, const AtomCompareFunction& func, bool atoms = true,
                                        bool atom_nbrs = true, bool bonds = true, bool bond_atoms = false);

        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, bool atoms = true, bool atom_nbrs = true,
                                        bool bonds = true, bool bond_atoms = false);

        CDPL_CHEM_API void calc2DCoordinates(MolecularGraph& molgraph, bool overwrite);

        /**
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomContainer& atoms, const Math::Vector2DArray& ref_coords, bool fix_bond_stereo = true);

        /**
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomMapping& ref_atom_mpg, bool fix_bond_stereo = true);

        /**
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, bool use_mcss, bool fix_bond_stereo = true);

        /**
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, const MolecularGraph& substr_ptn, bool fix_bond_stereo = true);

        
        CDPL_CHEM_API void calcHydrogen3DCoordinates(MolecularGraph& molgraph, bool undef_only = true);

        CDPL_CHEM_API void calcBond2DStereoFlags(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcCIPPriorities(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void perceiveSymmetryClasses(MolecularGraph& molgraph, bool overwrite,
                                                   unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                   unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool inc_impl_h = true);

        CDPL_CHEM_API void calcCanonicalNumbering(MolecularGraph& molgraph, bool overwrite,
                                                  unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                  unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        CDPL_CHEM_API void calcMorganNumbering(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcImplicitHydrogenCounts(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcFormalCharges(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void perceiveHybridizationStates(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void perceiveBondOrders(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void kekulizeBonds(MolecularGraph& molgraph);

        CDPL_CHEM_API void perceiveAtomStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_inv_n = true, bool check_quart_n = true, bool check_plan_n = true,
                                                     bool check_amide_n = true, bool check_res_ctrs = true);

        CDPL_CHEM_API void perceiveBondStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_term_n = true, bool check_order = true, std::size_t min_ring_size = 8);

        CDPL_CHEM_API void calcMDLParities(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcAtomStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1, bool check_stc_flag = true);

        CDPL_CHEM_API void calcAtomStereoDescriptorsFromMDLParities(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcBondStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1,
                                                     bool check_stc_flag = true);

        CDPL_CHEM_API void calcAtomCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void calcBondCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void setAtomMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        CDPL_CHEM_API void setBondMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        CDPL_CHEM_API void generateMatchExpressions(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void generateMatchExpressionStrings(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void initSubstructureSearchQuery(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void initSubstructureSearchTarget(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void setAromaticityFlags(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void setRingFlags(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void setAtomTypesFromSymbols(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void setAtomSymbolsFromTypes(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API void perceiveSybylAtomTypes(MolecularGraph& molgraph, bool overwrite);

        CDPL_CHEM_API FragmentList::SharedPointer getAromaticRings(const MolecularGraph& molgraph);

        CDPL_CHEM_API FragmentList::SharedPointer getAromaticSSSRSubset(const MolecularGraph& molgraph);

        CDPL_CHEM_API bool containsMolecularGraph(const MolecularGraph& molgraph, const MolecularGraph& sub_molgraph,
                                                  bool atoms = true, bool bonds = true);

        CDPL_CHEM_API void getContainedFragments(const MolecularGraph& molgraph, const FragmentList& frag_list,
                                                 FragmentList& cont_frag_list, bool append = false, bool atoms = true,
                                                 bool bonds = true);

        CDPL_CHEM_API void getContainingFragments(const MolecularGraph& molgraph, const FragmentList& frag_list,
                                                  FragmentList& cont_frag_list, bool append = false, bool atoms = true,
                                                  bool bonds = true);

        CDPL_CHEM_API void translateFragment(const MolecularGraph& src_molgraph, const Fragment& src_frag,
                                             const MolecularGraph& tgt_molgraph, Fragment& tgt_frag, bool append = false);
        
        CDPL_CHEM_API void translateFragments(const MolecularGraph& src_molgraph, const FragmentList& src_frag_list,
                                              const MolecularGraph& tgt_molgraph, FragmentList& tgt_frag_list, bool append = false);

        CDPL_CHEM_API void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list,
                                              const Util::BitSet& split_bond_mask, bool append = false);

        CDPL_CHEM_API std::size_t getCompleteBondCount(const MolecularGraph& molgraph);

        /**
         * \since 1.1
         */
        CDPL_CHEM_API void calcBasicProperties(MolecularGraph& molgraph, bool overwrite);

        /**
         * \since 1.3
         */
        CDPL_CHEM_API std::size_t editSubstructures(const MolecularGraph& molgraph, Molecule& result_mol, const std::string& search_ptns,
                                                    const std::string& result_ptn, const std::string& exclude_ptns = std::string());
        
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
