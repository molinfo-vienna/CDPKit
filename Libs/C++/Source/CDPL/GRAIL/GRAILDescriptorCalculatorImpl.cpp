/* 
 * GRAILDescriptorCalculatorImpl.cpp 
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

 
#include "StaticInit.hpp"

#include <iterator>
#include <algorithm>
#include <cmath>

#include "CDPL/GRAIL/FeatureFunctions.hpp"
#include "CDPL/GRAIL/FeatureType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Pharm/HydrophobicAtomFeatureGenerator.hpp"
#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/UFFAtomTypePropertyTable.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/Octree.hpp"

#include "GRAILDescriptorCalculatorImpl.hpp"


using namespace CDPL;


namespace
{

    constexpr double HYDROPHOBICIY_THRESHOLD         = 0.15;
    constexpr double FEATURE_DISTANCE_CUTOFF         = 10.0;
    constexpr double ESTAT_DISTANCE_CUTOFF           = 20.0;
    constexpr double DIELECTRIC_CONST                = 1.0;
    constexpr double VDW_DISTANCE_CUTOFF             = 10.0;
    constexpr double VDW_POLAR_H_DIST_SCALING_FACTOR = 0.5;
}


GRAIL::GRAILDescriptorCalculatorImpl::GRAILDescriptorCalculatorImpl(const FeatureInteractionFuncList& ftr_ia_funcs,
                                                                    const FeatureTypeInfoList& lig_descr_ftr_types,
                                                                    const FeatureTypeInfoList& tgt_env_hba_hbd_ftr_types,
                                                                    const FeatureTypeFunc& ftr_type_func):
    ftrInteractionFuncList(ftr_ia_funcs), ligDescrFtrTypes(lig_descr_ftr_types), tgtEnvOccupHBAHBDTypes(tgt_env_hba_hbd_ftr_types), ftrTypeFunc(ftr_type_func), 
    tgtPharmGenerator(Pharm::DefaultPharmacophoreGenerator::STATIC_H_DONORS | Pharm::DefaultPharmacophoreGenerator::PI_NI_ON_CHARGED_GROUPS_ONLY),
    tgtAtomOctree(new Octree()), tgtFtrSubsets(FeatureType::MAX_EXT_TYPE + 1),
    ligPharmGenerator(Pharm::DefaultPharmacophoreGenerator::PI_NI_ON_CHARGED_GROUPS_ONLY), ligFtrSubsets(FeatureType::MAX_EXT_TYPE + 1),
    numLigAtoms(0)
{
    initPharmGenerators();
}

GRAIL::GRAILDescriptorCalculatorImpl::GRAILDescriptorCalculatorImpl(const GRAILDescriptorCalculatorImpl& calc):
    ftrInteractionFuncList(calc.ftrInteractionFuncList), ligDescrFtrTypes(calc.ligDescrFtrTypes),
    tgtEnvOccupHBAHBDTypes(calc.tgtEnvOccupHBAHBDTypes), ftrTypeFunc(calc.ftrTypeFunc), 
    tgtPharmGenerator(Pharm::DefaultPharmacophoreGenerator::STATIC_H_DONORS | Pharm::DefaultPharmacophoreGenerator::PI_NI_ON_CHARGED_GROUPS_ONLY),
    tgtPharmacophore(calc.tgtPharmacophore), tgtAtomCharges(calc.tgtAtomCharges), tgtAtomVdWParams(calc.tgtAtomVdWParams),
    tgtAtomCoords(calc.tgtAtomCoords), tgtAtomOctree(new Octree()), tgtFtrSubsets(FeatureType::MAX_EXT_TYPE + 1),
    ligPharmGenerator(Pharm::DefaultPharmacophoreGenerator::PI_NI_ON_CHARGED_GROUPS_ONLY), ligAtomCharges(calc.ligAtomCharges),
    ligAtomVdWParams(calc.ligAtomVdWParams), ligHeavyAtoms(calc.ligHeavyAtoms), ligFtrSubsets(calc.ligFtrSubsets),
    ligFtrAtoms(calc.ligFtrAtoms), ligFtrWeights(calc.ligFtrWeights), ligDescriptor(calc.ligDescriptor), numLigAtoms(calc.numLigAtoms)
{
    initPharmGenerators();

    tgtAtomOctree->initialize(tgtAtomCoords);

    copyTgtFtrSubsets(calc.tgtFtrSubsets);
}

GRAIL::GRAILDescriptorCalculatorImpl& GRAIL::GRAILDescriptorCalculatorImpl::operator=(const GRAILDescriptorCalculatorImpl& calc)
{
    if (this == &calc)
        return *this;

    ftrInteractionFuncList = calc.ftrInteractionFuncList;
    ligDescrFtrTypes = calc.ligDescrFtrTypes;
    tgtEnvOccupHBAHBDTypes = calc.tgtEnvOccupHBAHBDTypes;
    ftrTypeFunc = calc.ftrTypeFunc; 
    ligFtrSubsets = calc.ligFtrSubsets;
    ligFtrAtoms = calc.ligFtrAtoms;
    ligFtrWeights = calc.ligFtrWeights;
    ligHeavyAtoms = calc.ligHeavyAtoms;
    ligAtomCharges = calc.ligAtomCharges;
    ligAtomVdWParams = calc.ligAtomVdWParams;
    numLigAtoms = calc.numLigAtoms;
    tgtAtomCharges = calc.tgtAtomCharges;
    tgtAtomVdWParams = calc.tgtAtomVdWParams;
    tgtAtomCoords = calc.tgtAtomCoords;
    tgtPharmacophore = calc.tgtPharmacophore;
    ligDescriptor = calc.ligDescriptor;
    
    tgtAtomOctree->initialize(tgtAtomCoords);

    copyTgtFtrSubsets(calc.tgtFtrSubsets);
    
    return *this;
}

void GRAIL::GRAILDescriptorCalculatorImpl::initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                                          bool tgt_env_changed)
{
    using namespace Pharm;

    std::size_t num_atoms = tgt_env.getNumAtoms();

    tgtAtomCoords.resize(num_atoms);

    if (tgt_env_changed) {
        if (tgtAtomCharges.size() < num_atoms)
            tgtAtomCharges.resize(num_atoms);

        if (tgtAtomVdWParams.size() < num_atoms)
            tgtAtomVdWParams.resize(num_atoms);
    }
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        const Chem::Atom& atom = tgt_env.getAtom(i);
        
        tgtAtomCoords[i] = coords_func(atom);

        if (tgt_env_changed) {
            tgtAtomCharges[i] = ForceField::getMMFF94Charge(atom);

            getVdWParameters(atom, tgt_env, tgtAtomVdWParams[i]);
        }
    }
    
    tgtAtomOctree->initialize(tgtAtomCoords);

    tgtPharmGenerator.setAtom3DCoordinatesFunction(TargetAtomCoordsFunc(tgt_env, tgtAtomCoords));
    tgtPharmGenerator.generate(tgt_env, tgtPharmacophore);

    for (auto& ftr_ss : tgtFtrSubsets)
        ftr_ss.features.clear();

    for (auto& ftr : tgtPharmacophore) {
        unsigned int ftr_type = ftrTypeFunc(ftr, false);
        
        if (ftr_type > FeatureType::MAX_EXT_TYPE) // sanity check
            continue;

        if (ftr_type == FeatureType::HYDROPHOBIC)
            setWeight(ftr, getHydrophobicity(ftr));
        
        tgtFtrSubsets[ftr_type].features.push_back(&ftr);
    }

    for (auto& ftr_ss : tgtFtrSubsets) {
        std::size_t num_ftrs = ftr_ss.features.size();
        
        ftr_ss.ftrCoords.resize(num_ftrs);

        for (std::size_t i = 0; i < num_ftrs; i++) 
            ftr_ss.ftrCoords[i] = get3DCoordinates(*ftr_ss.features[i]);

        if (!ftr_ss.octree)
            ftr_ss.octree.reset(new Octree());

        ftr_ss.octree->initialize(ftr_ss.ftrCoords);
    }
}

void GRAIL::GRAILDescriptorCalculatorImpl::initLigandData(const Chem::MolecularGraph& ligand)
{
    using namespace Pharm;
    using namespace Chem;

    numLigAtoms = ligand.getNumAtoms();

    ligDescriptor.clear();
    ligHeavyAtoms.clear();
    
    if (ligAtomCharges.size() < numLigAtoms)
        ligAtomCharges.resize(numLigAtoms);

    if (ligAtomVdWParams.size() < numLigAtoms)
        ligAtomVdWParams.resize(numLigAtoms);

    ligHBAAtomMask.resize(numLigAtoms);
    ligHBAAtomMask.reset();

    ligHBDAtomMask.resize(numLigAtoms);
    ligHBDAtomMask.reset();
    
    double total_hyd = 0.0;
    double log_p = 0.0;
        
    for (std::size_t i = 0; i < numLigAtoms; i++) {
        const Atom& atom = ligand.getAtom(i);

        if (getType(atom) != AtomType::H)
            ligHeavyAtoms.push_back(i);

        ligAtomCharges[i] = ForceField::getMMFF94Charge(atom);

        getVdWParameters(atom, ligand, ligAtomVdWParams[i]);

        log_p += MolProp::getHydrophobicity(atom); 
    }
    
    ligPharmGenerator.generate(ligand, ligPharmacophore);
    
    for (auto& il : ligFtrSubsets)
        il.clear();

    std::size_t num_ftrs = ligPharmacophore.getNumFeatures();

    if (ligFtrWeights.size() < num_ftrs)
        ligFtrWeights.resize(num_ftrs);

    if (ligFtrAtoms.size() < num_ftrs)
        ligFtrAtoms.resize(num_ftrs);

    ligFtrCoords.resize(num_ftrs);
    
    for (std::size_t i = 0; i < num_ftrs; i++) {
        const Feature& ftr = ligPharmacophore.getFeature(i);
        const Fragment::SharedPointer& ftr_substruct = getSubstructure(ftr);
        unsigned int ftr_type = getType(ftr);
        Util::BitSet* hba_hbd_mask = (ftr_type == FeatureType::H_BOND_ACCEPTOR ? &ligHBAAtomMask :
                                      ftr_type == FeatureType::H_BOND_DONOR    ? &ligHBDAtomMask : nullptr);

        ligFtrAtoms[i].clear();

        for (const auto& atom : ftr_substruct->getAtoms()) {
            if (getType(atom) == AtomType::H)
                continue;

            std::size_t atom_idx = ligand.getAtomIndex(atom);
            
            ligFtrAtoms[i].push_back(atom_idx);

            if (hba_hbd_mask)
                hba_hbd_mask->set(atom_idx);
        }
        
        ftr_type = ftrTypeFunc(ftr, true);

        if (ftr_type == FeatureType::HYDROPHOBIC) {
            ligFtrWeights[i] = getHydrophobicity(ftr);
            total_hyd += ligFtrWeights[i];
            
        } else
            ligFtrWeights[i] = 1.0;

        if (ftr_type > FeatureType::MAX_EXT_TYPE) // sanity check
            continue;

        ligFtrSubsets[ftr_type].push_back(i);
    }

    for (std::size_t i = 0, num_ftr_types = ligDescrFtrTypes.size(); i < num_ftr_types; i++) {
        const FeatureTypeInfo& ftr_type = ligDescrFtrTypes[i];
        const IndexList& ftrs = ligFtrSubsets[ftr_type.type];
        
        if (!ftr_type.isHBD) {
            ligDescriptor.push_back(ftrs.size());
            continue;
        }

        // for H-donor atoms the number of attached Hs has to be considered 
        std::size_t hbd_cnt = 0;

        for (auto ftr_idx : ftrs) {
            const Feature& ftr = ligPharmacophore.getFeature(ftr_idx);
            const Fragment::SharedPointer& ftr_substruct = getSubstructure(ftr);

            for (const auto& atom : ftr_substruct->getAtoms()) {
                if (getType(atom) == AtomType::H)
                    continue;

                hbd_cnt += MolProp::getAtomCount(atom, ligand, AtomType::H);
                break;
            }
        }

        ligDescriptor.push_back(hbd_cnt);
    }
    
    ligDescriptor.push_back(MolProp::getHeavyAtomCount(ligand));
    ligDescriptor.push_back(MolProp::getRotatableBondCount(ligand));
    ligDescriptor.push_back(total_hyd);
    ligDescriptor.push_back(log_p);
    ligDescriptor.push_back(ligTPSACalculator.calculate(ligand));
}

void GRAIL::GRAILDescriptorCalculatorImpl::calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part)
{
    if (atom_coords.getSize() != numLigAtoms)
        throw Base::SizeError("GRAILDescriptorCalculatorImpl: atom coordinates array size does not match number of atoms");
    
    std::size_t idx = (update_lig_part ? std::size_t(0) : ligDescriptor.size());

    if (update_lig_part)
        for ( ; idx < ligDescriptor.size(); idx++)
            descr[idx] = ligDescriptor[idx];

    calcLigFtrCoordinates(atom_coords.getData());
    calcTgtEnvHBAHBDOccupations(atom_coords.getData(), descr, idx);
    calcFeatureInteractionScores(descr, idx);
    calcElectrostaticInteractionEnergy(atom_coords.getData(), descr, idx);
    calcVdWInteractionEnergy(atom_coords.getData(), descr, idx);
}

void GRAIL::GRAILDescriptorCalculatorImpl::calcLigFtrCoordinates(const Math::Vector3DArray::StorageType& atom_coords)
{
    for (std::size_t i = 0, num_ftrs = ligFtrCoords.size(); i < num_ftrs; i++) {
        Math::Vector3D& ftr_pos = ligFtrCoords[i];
        const IndexList& ftr_atoms  = ligFtrAtoms[i];
        std::size_t num_atoms = ftr_atoms.size();
        
        if (num_atoms == 0) // should never happen!
            continue;
        
        if (num_atoms == 1) {
            ftr_pos = atom_coords[ftr_atoms[0]];
            continue;
        }

        ftr_pos.clear();
        
        for (auto atom_idx : ftr_atoms)
            ftr_pos.plusAssign(atom_coords[atom_idx]);

        ftr_pos /= num_atoms;
    }
}

void GRAIL::GRAILDescriptorCalculatorImpl::calcTgtEnvHBAHBDOccupations(const Math::Vector3DArray::StorageType& atom_coords,
                                                                       Math::DVector& descr, std::size_t& idx)
{
    for (const auto& ftr_type : tgtEnvOccupHBAHBDTypes)
        calcTgtEnvHBAHBDOccupation(atom_coords, descr, ftr_type.type, !ftr_type.isHBD, idx);
}

void GRAIL::GRAILDescriptorCalculatorImpl::calcTgtEnvHBAHBDOccupation(const Math::Vector3DArray::StorageType& atom_coords,
                                                                      Math::DVector& descr, unsigned int tgt_ftr_type,
                                                                      bool is_hba_type, std::size_t& idx)
{
    Pharm::HBondingInteractionScore scoring_func(is_hba_type);
    const FeatureSubset& tgt_ftr_ss = tgtFtrSubsets[tgt_ftr_type];
    double score_sum = 0.0;
    double score_max = 0.0;

    for (auto lig_atom_idx : ligHeavyAtoms) {
        if (is_hba_type) {
            if (ligHBDAtomMask.test(lig_atom_idx))
                continue;

        } else if (ligHBAAtomMask.test(lig_atom_idx))
            continue;
        
        const Math::Vector3D& lig_atom_pos = atom_coords[lig_atom_idx];
        double max_score = 0.0;

        tmpIndexList.clear();
        tgt_ftr_ss.octree->radiusNeighbors<Octree::L2Distance>(lig_atom_pos, FEATURE_DISTANCE_CUTOFF, std::back_inserter(tmpIndexList));

        for (auto tgt_ftr_idx : tmpIndexList) {
            double s = scoring_func(lig_atom_pos, *tgt_ftr_ss.features[tgt_ftr_idx]);

            max_score = std::max(max_score, s);
            score_sum += s;
        }

        score_max += max_score;
    }

    descr[idx++] = score_sum;
    descr[idx++] = score_max;
}

void GRAIL::GRAILDescriptorCalculatorImpl::calcFeatureInteractionScores(Math::DVector& descr, std::size_t& idx)
{
    for (const auto& func_data : ftrInteractionFuncList) {
        const IndexList& lig_ftrs = ligFtrSubsets[func_data.ligFtrType];
        const FeatureSubset& tgt_ftr_ss = tgtFtrSubsets[func_data.tgtFtrType];
        double score_sum = 0.0;
        double score_max = 0.0;
        
        for (auto lig_ftr_idx : lig_ftrs) {
            double lig_ftr_wt = ligFtrWeights[lig_ftr_idx];
            const Math::Vector3D& lig_ftr_pos = ligFtrCoords[lig_ftr_idx];
            double max_score = 0.0;
            
            tmpIndexList.clear();
            tgt_ftr_ss.octree->radiusNeighbors<Octree::L2Distance>(lig_ftr_pos, FEATURE_DISTANCE_CUTOFF, std::back_inserter(tmpIndexList));
            
            for (auto tgt_ftr_idx : tmpIndexList) {
                double s = lig_ftr_wt * (*func_data.scoringFunc)(lig_ftr_pos, *tgt_ftr_ss.features[tgt_ftr_idx]);

                max_score = std::max(max_score, s);
                score_sum += s;
            }

            score_max += max_score;
        }

        descr[idx++] = score_sum;
        descr[idx++] = score_max;
    }
}

void GRAIL::GRAILDescriptorCalculatorImpl::calcElectrostaticInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
                                                                              Math::DVector& descr, std::size_t& idx)
{
    double energy           = 0.0;
    double energy_sqrd_dist = 0.0;
    
    for (std::size_t i = 0; i < numLigAtoms; i++) {
        double la_charge = ligAtomCharges[i];
        const Math::Vector3D& la_pos = atom_coords[i];

        tmpIndexList.clear();
        tgtAtomOctree->radiusNeighbors<Octree::L2Distance>(la_pos, ESTAT_DISTANCE_CUTOFF, std::back_inserter(tmpIndexList));

        for (auto tgt_atom_idx : tmpIndexList) {
            double r_ij = ForceField::calcDistance<double>(la_pos, tgtAtomCoords[tgt_atom_idx]);
            double e = la_charge * tgtAtomCharges[tgt_atom_idx] / (r_ij * DIELECTRIC_CONST);

            energy += e;
            energy_sqrd_dist += e / r_ij;
        }
    }

    descr[idx++] = energy;
    descr[idx++] = energy_sqrd_dist;
}

/*
 * Uses a Morse potential:
 * V = D,i,j * (e^(-2 * alpha * (r,i,j - x,i,j)) - 2 * e^(-alpha * (r,i,j - x,i,j)))
 * D,i,j = sqrt(D,i * D,j)
 * x,i,j = sqrt(x,i * x,j) * 2^(1/6)
 */
void GRAIL::GRAILDescriptorCalculatorImpl::calcVdWInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
                                                                    Math::DVector& descr, std::size_t idx)
{
    const double RMIN_FACT = std::pow(2, 1.0 / 6);
    const double ALPHA     = 1.1;

    double energy_att = 0.0;
    double energy_rep = 0.0;
    
    for (std::size_t i = 0; i < numLigAtoms; i++) {
        const DoublePair& la_params = ligAtomVdWParams[i];
        const Math::Vector3D& la_pos = atom_coords[i];

        tmpIndexList.clear();
        tgtAtomOctree->radiusNeighbors<Octree::L2Distance>(la_pos, VDW_DISTANCE_CUTOFF, std::back_inserter(tmpIndexList));

        for (auto tgt_atom_idx : tmpIndexList) {
            const DoublePair& ta_params = tgtAtomVdWParams[tgt_atom_idx];

            double r_ij = ForceField::calcDistance<double>(la_pos, tgtAtomCoords[tgt_atom_idx]);
            double D_ij = std::sqrt(la_params.second * ta_params.second);
            double x_ij = RMIN_FACT * std::sqrt(la_params.first * ta_params.first);
            double r_delta = r_ij - x_ij;

            energy_att += -D_ij * 2 * std::exp(-ALPHA * r_delta);
            energy_rep += D_ij * std::exp(-2 * ALPHA * r_delta);
        }
    }

    descr[idx++] = energy_att;
    descr[idx++] = energy_rep;
}

void GRAIL::GRAILDescriptorCalculatorImpl::getVdWParameters(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, DoublePair& params) const
{
    using namespace ForceField;
    
    const UFFAtomTypePropertyTable::Entry& uff_props = UFFAtomTypePropertyTable::get()->getEntry(perceiveUFFType(atom, molgraph));

    if (!uff_props) {
        params.first = 0.0;
        params.second = 0.0;
        return;
    }
    
    params.first = uff_props.getVdWDistance();
    params.second = uff_props.getVdWEnergy();

    if (isPolarHydrogen(atom, molgraph))
        params.first *= VDW_POLAR_H_DIST_SCALING_FACTOR;
}
            
bool GRAIL::GRAILDescriptorCalculatorImpl::isPolarHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const
{
    using namespace Chem;

    if (getType(atom) != AtomType::H)
        return false;
    
    if (atom.getNumAtoms() != 1 || !molgraph.containsAtom(atom.getAtom(0)))
        return false;
        
    switch (getType(atom.getAtom(0))) {

        case AtomType::N:
        case AtomType::O:
        case AtomType::S:
            return true;
    }

    return false;
}

void GRAIL::GRAILDescriptorCalculatorImpl::initPharmGenerators()
{
    Pharm::HydrophobicAtomFeatureGenerator::SharedPointer tgt_h_gen(new Pharm::HydrophobicAtomFeatureGenerator());
    
    tgt_h_gen->setHydrophobicityThreshold(HYDROPHOBICIY_THRESHOLD);

    tgtPharmGenerator.setFeatureGenerator(FeatureType::HYDROPHOBIC, tgt_h_gen);
    tgtPharmGenerator.enableFeature(FeatureType::HALOGEN_BOND_ACCEPTOR, true);
    tgtPharmGenerator.enableFeature(FeatureType::NEGATIVE_IONIZABLE, false);

    Pharm::HydrophobicAtomFeatureGenerator::SharedPointer lig_h_gen(new Pharm::HydrophobicAtomFeatureGenerator());
    
    lig_h_gen->setHydrophobicityThreshold(HYDROPHOBICIY_THRESHOLD);

    ligPharmGenerator.setFeatureGenerator(FeatureType::HYDROPHOBIC, lig_h_gen);
}

void GRAIL::GRAILDescriptorCalculatorImpl::copyTgtFtrSubsets(const FeatureSubsetList& ftr_ss_list)
{
    for (std::size_t i = 0; i < (FeatureType::MAX_EXT_TYPE + 1); i++) {
        tgtFtrSubsets[i].features.clear();

        for (std::size_t j = 0, num_ftrs = ftr_ss_list[i].features.size(); j < num_ftrs; j++)
            tgtFtrSubsets[i].features.push_back(&tgtPharmacophore.getFeature(ftr_ss_list[i].features[j]->getIndex()));

        tgtFtrSubsets[i].ftrCoords = ftr_ss_list[i].ftrCoords;
    
        if (!tgtFtrSubsets[i].octree)
            tgtFtrSubsets[i].octree.reset(new Octree());
        
        tgtFtrSubsets[i].octree->initialize(tgtFtrSubsets[i].ftrCoords);
    }
}

inline const Math::Vector3D& GRAIL::GRAILDescriptorCalculatorImpl::TargetAtomCoordsFunc::operator()(const Chem::Atom& atom) const
{
    return (*coords)[tgtEnv->getAtomIndex(atom)];
}
