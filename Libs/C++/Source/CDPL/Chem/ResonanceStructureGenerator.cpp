/* 
 * ResonanceStructureGenerator.cpp 
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

#include <algorithm>
#include <iterator>
#include <limits>
#include <cstdlib>
#include <functional>

#include <boost/functional/hash.hpp>

#include "CDPL/Chem/ResonanceStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    constexpr std::size_t MAX_RES_STRUCT_DATA_CACHE_SIZE = 2000;
    constexpr std::size_t MIN_SP1_RING_SIZE              = 7;
}


using namespace CDPL;


Chem::ResonanceStructureGenerator::ResonanceStructureGenerator():
    resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE), minOctRuleViolations(true),
    minSP1GeomViolations(true), minCBond12Charges(false), chargeCountWin(0),
    octRuleCheckAtomTypes(AtomType::MAX_ATOMIC_NO), maxNumGenStructs(0)
{
    octRuleCheckAtomTypes.set(AtomType::N);
    octRuleCheckAtomTypes.set(AtomType::O);
}

Chem::ResonanceStructureGenerator::ResonanceStructureGenerator(const ResonanceStructureGenerator& gen):
    resStructDataCache(MAX_RES_STRUCT_DATA_CACHE_SIZE),    minOctRuleViolations(gen.minOctRuleViolations),
    minSP1GeomViolations(gen.minSP1GeomViolations), minCBond12Charges(gen.minCBond12Charges),
    chargeCountWin(gen.chargeCountWin), octRuleCheckAtomTypes(gen.octRuleCheckAtomTypes),
    maxNumGenStructs(gen.maxNumGenStructs)
{
    std::transform(gen.outputResStructs.begin(), gen.outputResStructs.end(), std::back_inserter(outputResStructs),
                   std::bind(&ResonanceStructureGenerator::copyResStructPtr, this, std::placeholders::_1));
}

Chem::ResonanceStructureGenerator& Chem::ResonanceStructureGenerator::operator=(const ResonanceStructureGenerator& gen) 
{
    if (this == &gen)
        return *this;

    minOctRuleViolations = gen.minOctRuleViolations;
    minSP1GeomViolations = gen.minSP1GeomViolations;
    minCBond12Charges = gen.minCBond12Charges;
    octRuleCheckAtomTypes = gen.octRuleCheckAtomTypes;
    chargeCountWin = gen.chargeCountWin;
    maxNumGenStructs = gen.maxNumGenStructs;
    
    outputResStructs.clear();
    
    std::transform(gen.outputResStructs.begin(), gen.outputResStructs.end(), std::back_inserter(outputResStructs),
                   std::bind(&ResonanceStructureGenerator::copyResStructPtr, this, std::placeholders::_1));
        
    return *this;
}

Util::BitSet& Chem::ResonanceStructureGenerator::getOctetRuleCheckAtomTypes()
{
    return octRuleCheckAtomTypes;
}

const Util::BitSet& Chem::ResonanceStructureGenerator::getOctetRuleCheckAtomTypes() const
{
    return octRuleCheckAtomTypes;
}
            
void Chem::ResonanceStructureGenerator::minimizeOctetRuleViolations(bool minimize)
{
    minOctRuleViolations = minimize;
}

bool Chem::ResonanceStructureGenerator::octetRuleViolationsMinimized() const
{
    return minOctRuleViolations;
}

void Chem::ResonanceStructureGenerator::minimizeSP1GeometryViolations(bool minimize)
{
    minSP1GeomViolations = minimize;
}

bool Chem::ResonanceStructureGenerator::sp1GeometryViolationsMinimized() const
{
    return minSP1GeomViolations;
}

void Chem::ResonanceStructureGenerator::minimizeCarbonBond12Charges(bool minimize)
{
    minCBond12Charges = minimize;
}

bool Chem::ResonanceStructureGenerator::carbonBond12ChargesMinimized() const
{
    return minCBond12Charges;
}

void Chem::ResonanceStructureGenerator::setChargeCountWindow(std::size_t win_size)
{
    chargeCountWin = win_size;
}

std::size_t Chem::ResonanceStructureGenerator::getChargeCountWindow() const
{
    return chargeCountWin;
}

void Chem::ResonanceStructureGenerator::setMaxNumGeneratedStructures(std::size_t max_num)
{
    maxNumGenStructs = max_num;
}

std::size_t Chem::ResonanceStructureGenerator::getMaxNumGeneratedStructures() const
{
    return maxNumGenStructs;
}

void Chem::ResonanceStructureGenerator::generate(const MolecularGraph& molgraph)
{
    init(molgraph);

    genStartResStructs();
    genOutputResStructs();
}

std::size_t Chem::ResonanceStructureGenerator::getNumStructures() const
{
    return outputResStructs.size();
}

const Chem::ResonanceStructureGenerator::StructureData& Chem::ResonanceStructureGenerator::getStructureData(std::size_t idx) const
{
    if (idx >= outputResStructs.size())
        throw Base::IndexError("ResonanceStructureGenerator: structure data index out of bounds");

    return *outputResStructs[idx];
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::getStructureDataBegin() const
{
    return outputResStructs.begin();
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::getStructureDataEnd() const
{
    return outputResStructs.end();
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::begin() const
{
    return outputResStructs.begin();
}

Chem::ResonanceStructureGenerator::ConstStructureDataIterator Chem::ResonanceStructureGenerator::end() const
{
    return outputResStructs.end();
}

void Chem::ResonanceStructureGenerator::init(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;
    
    createInputResStructData();
    extractResBonds();
}

void Chem::ResonanceStructureGenerator::createInputResStructData()
{
    std::size_t num_atoms = molGraph->getNumAtoms();
        
    inputResStruct.atomCharges.resize(num_atoms);
    inputResStruct.numCharges = 0;
    
    atomData.resize(num_atoms);

    FragmentList::SharedPointer sssr_ptr = (minSP1GeomViolations ? getSSSR(*molGraph) : FragmentList::SharedPointer());
        
    for (std::size_t i = 0; i < num_atoms; i++)  {
        const Atom& atom = molGraph->getAtom(i);
        long charge = atomData[i].init(atom, *molGraph, i);
        
        inputResStruct.atomCharges[i] = charge;

        if (minSP1GeomViolations && getRingFlag(atom) && getSizeOfSmallestContainingFragment(atom, *sssr_ptr) < MIN_SP1_RING_SIZE)
            atomData[i].setInSmallRingFlag();
    }
    
    inputResStruct.bondOrders.clear();

    std::transform(molGraph->getBondsBegin(), molGraph->getBondsEnd(), std::back_inserter(inputResStruct.bondOrders.getData()),
                   std::bind(&getOrder, std::placeholders::_1));
}

void Chem::ResonanceStructureGenerator::extractResBonds()
{
    resBonds.clear();
    visBondMask.resize(molGraph->getNumBonds());
    visBondMask.reset();

    for (AtomDataArray::iterator it = atomData.begin(), end = atomData.end(); it != end; ++it) {
        AtomData& atom_data = *it;

        if (!atom_data.getVisitedFlag() && atom_data.canShiftElectrons())
            extractResBonds(atom_data);
    }
}

void Chem::ResonanceStructureGenerator::extractResBonds(AtomData& atom_data)
{
    atom_data.setVisitedFlag();
    
    for (std::size_t i = 0, num_bonds = atom_data.getNumBonds(); i < num_bonds; i++) {
        std::size_t nbr_atom_idx = atom_data.getAtomIndex(i);

        if (!atomData[nbr_atom_idx].canShiftElectrons())
            continue;
        
        std::size_t nbr_bond_idx = atom_data.getBondIndex(i);

        if (visBondMask.test(nbr_bond_idx))
            continue;

        visBondMask.set(nbr_bond_idx);
        resBonds.push_back({ atom_data.getIndex(), nbr_atom_idx, nbr_bond_idx});
            
        if (!atomData[nbr_atom_idx].getVisitedFlag())
            extractResBonds(atomData[nbr_atom_idx]);
    }
}

void Chem::ResonanceStructureGenerator::genStartResStructs()
{
    startResStructs.clear();

    minNumRepChargePairs = std::numeric_limits<std::size_t>::max();
    chargeDiffPtn.assign(atomData.size(), 0);
    
    genStartResStructs(0, 0);
}

void Chem::ResonanceStructureGenerator::genStartResStructs(std::size_t depth, std::size_t num_rep_chg_pairs)
{
    if (num_rep_chg_pairs > minNumRepChargePairs)
        return;

    if (depth >= resBonds.size()) {
        StructureDataPtr rs_copy = copyResStruct(inputResStruct);
        
        if (num_rep_chg_pairs < minNumRepChargePairs) {
            startResStructs.clear();
            minNumRepChargePairs = num_rep_chg_pairs;
        }
        
        startResStructs.push_back(rs_copy);
        return;
    }

    const BondData& res_bond = resBonds[depth];
    std::size_t bond_order = inputResStruct.bondOrders[res_bond.bondIndex];
    
    if (bond_order <= 1 || bond_order > 3) {
        genStartResStructs(depth + 1, num_rep_chg_pairs);
        return;
    }
    
    const AtomData& atom1_data = atomData[res_bond.atom1Index];
    const AtomData& atom2_data = atomData[res_bond.atom2Index];

    double atom1_eneg = atom1_data.getElectronegativity();
    double atom2_eneg = atom2_data.getElectronegativity();

    if (bond_order == 3 && atom1_eneg >= atom2_eneg && atom1_data.checkValenceState(inputResStruct, -2, -2) && atom2_data.checkValenceState(inputResStruct, -2, 2)) {
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, -2, -2, 2);

        chargeDiffPtn[res_bond.atom1Index] -= 1;
        chargeDiffPtn[res_bond.atom2Index] += 1;
        
        genStartResStructs(depth + 1, num_rep_chg_pairs + atom1_data.countRepChargePairs(chargeDiffPtn) + atom2_data.countRepChargePairs(chargeDiffPtn));

        chargeDiffPtn[res_bond.atom1Index] += 1;
        chargeDiffPtn[res_bond.atom2Index] -= 1;
        
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, 2, 2, -2);

    } else if (atom1_eneg >= atom2_eneg && atom1_data.checkValenceState(inputResStruct, -1, -1) && atom2_data.checkValenceState(inputResStruct, -1, 1)) {
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, -1, -1, 1);

        chargeDiffPtn[res_bond.atom1Index] -= 1;
        chargeDiffPtn[res_bond.atom2Index] += 1;
        
        genStartResStructs(depth + 1, num_rep_chg_pairs + atom1_data.countRepChargePairs(chargeDiffPtn) + atom2_data.countRepChargePairs(chargeDiffPtn));

        chargeDiffPtn[res_bond.atom1Index] += 1;
        chargeDiffPtn[res_bond.atom2Index] -= 1;
        
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, 1, 1, -1);
    }
    
    if (bond_order == 3 && atom1_eneg <= atom2_eneg && atom1_data.checkValenceState(inputResStruct, -2, 2) && atom2_data.checkValenceState(inputResStruct, -2, -2)) {
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, -2, 2, -2);

        chargeDiffPtn[res_bond.atom1Index] += 1;
        chargeDiffPtn[res_bond.atom2Index] -= 1;

        genStartResStructs(depth + 1, num_rep_chg_pairs + atom1_data.countRepChargePairs(chargeDiffPtn) + atom2_data.countRepChargePairs(chargeDiffPtn));

        chargeDiffPtn[res_bond.atom1Index] -= 1;
        chargeDiffPtn[res_bond.atom2Index] += 1;
    
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, 2, -2, 2);

    } else if (atom1_eneg <= atom2_eneg && atom1_data.checkValenceState(inputResStruct, -1, 1) && atom2_data.checkValenceState(inputResStruct, -1, -1)) {
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, -1, 1, -1);

        chargeDiffPtn[res_bond.atom1Index] += 1;
        chargeDiffPtn[res_bond.atom2Index] -= 1;

        genStartResStructs(depth + 1, num_rep_chg_pairs + atom1_data.countRepChargePairs(chargeDiffPtn) + atom2_data.countRepChargePairs(chargeDiffPtn));

        chargeDiffPtn[res_bond.atom1Index] -= 1;
        chargeDiffPtn[res_bond.atom2Index] += 1;
    
        modifyResStruct(inputResStruct, res_bond.bondIndex, res_bond.atom1Index, res_bond.atom2Index, 1, -1, 1);
    }
}

void Chem::ResonanceStructureGenerator::genOutputResStructs()
{
    typedef boost::indirect_iterator<StructureDataList::iterator, StructureData> IndirIter;

    workingResStructs.clear();
    resAtoms.clear();
    visBondMask.reset();

    for (AtomDataArray::const_iterator it = atomData.begin(), end = atomData.end(); it != end; ++it)
        if (it->canShiftElectrons())
            resAtoms.push_back(&(*it));
    
    minNumCharges = atomData.size() * 8;

    std::for_each(IndirIter(startResStructs.begin()), IndirIter(startResStructs.end()),
                  std::bind(static_cast<void (ResonanceStructureGenerator::*)(StructureData&, std::size_t, std::size_t, std::size_t)>
                            (&ResonanceStructureGenerator::genOutputResStructs), this, std::placeholders::_1, 0, 0, 0));

    postprocOutputResStructs();
}

void Chem::ResonanceStructureGenerator::genOutputResStructs(StructureData& res_struct, std::size_t depth, std::size_t con_idx,
                                                            std::size_t num_charges)
{
    if (maxNumGenStructs > 0 && workingResStructs.size() >= maxNumGenStructs)
        return;
    
    if (con_idx == 0) {
        if (num_charges > (minNumCharges + chargeCountWin))
            return;
    
        if (depth >= resAtoms.size()) {
            StructureDataPtr rs_copy = copyResStruct(res_struct);

            rs_copy->numCharges = num_charges;
                
            if (num_charges < minNumCharges) {
                if (chargeCountWin == 0)
                    workingResStructs.clear();

                else {
                    std::size_t max_num_charges = num_charges + chargeCountWin;
                    
                    for (StructureDataSet::iterator it = workingResStructs.begin(), end = workingResStructs.end(); it != end; ) {
                        if ((*it)->numCharges > max_num_charges)
                            it = workingResStructs.erase(it);
                        else
                            ++it;
                    }
                }
                
                minNumCharges = num_charges;
            }
        
            workingResStructs.insert(rs_copy);
            return;
        }
    }
    
    const AtomData* atom_data = resAtoms[depth];
    std::size_t num_bonds = atom_data->getNumBonds();
    std::size_t atom_idx = atom_data->getIndex();
    
    if (con_idx >= num_bonds) {
        genOutputResStructs(res_struct, depth + 1, 0, num_charges + std::abs(res_struct.atomCharges[atom_idx]));
        return;
    }

    std::size_t con_bond_idx = atom_data->getBondIndex(con_idx);
    std::size_t con_atom_idx = atom_data->getAtomIndex(con_idx);
    const AtomData& con_atom_data = atomData[con_atom_idx];

    if (visBondMask.test(con_bond_idx) || !con_atom_data.canShiftElectrons()) {
        genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);
        return;
    }

    visBondMask.set(con_bond_idx);

    if (atom_data->checkValenceState(res_struct, 2, -2) && con_atom_data.checkValenceState(res_struct, 2, 2)) {
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, 2, -2, 2);
        
        genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);
        
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, -2, 2, -2);
    }

    if (atom_data->checkValenceState(res_struct, 1, -1) && con_atom_data.checkValenceState(res_struct, 1, 1)) {
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, 1, -1, 1);
        
        genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);
        
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, -1, 1, -1);
    }

    if (atom_data->checkValenceState(res_struct, 2, 2) && con_atom_data.checkValenceState(res_struct, 2, -2)) {
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, 2, 2, -2);
        
        genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);
        
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, -2, -2, 2);
    }

    if (atom_data->checkValenceState(res_struct, 1, 1) && con_atom_data.checkValenceState(res_struct, 1, -1)) {
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, 1, 1, -1);
        
        genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);
        
        modifyResStruct(res_struct, con_bond_idx, atom_idx, con_atom_idx, -1, -1, 1);
    }

    genOutputResStructs(res_struct, depth, con_idx + 1, num_charges);

    visBondMask.reset(con_bond_idx);
}

void Chem::ResonanceStructureGenerator::postprocOutputResStructs()
{
    outputResStructs.clear();
    tmpOutputResStructs.clear();
    
    std::copy(workingResStructs.begin(), workingResStructs.end(), std::back_inserter(outputResStructs));

    if (minSP1GeomViolations)
        minimzeResStructProperty(&ResonanceStructureGenerator::countSP1GeometryViolations);

    if (minOctRuleViolations)
        minimzeResStructProperty(&ResonanceStructureGenerator::countOctetRuleViolations);

    if (minCBond12Charges)
        minimzeResStructProperty(&ResonanceStructureGenerator::count12ChargedCBonds);

    if (outputResStructs.empty()) 
        outputResStructs.push_back(copyResStruct(inputResStruct));
}

void Chem::ResonanceStructureGenerator::minimzeResStructProperty(std::size_t (ResonanceStructureGenerator::* prop_func)(const StructureData&) const)
{
    std::size_t min_prop_val = std::numeric_limits<std::size_t>::max();

    for (StructureDataList::const_iterator it = outputResStructs.begin(), end = outputResStructs.end(); it != end; ++it) {
        const StructureDataPtr& res_struct = *it;
        std::size_t prop_val = (this->*prop_func)(*res_struct);

        if (prop_val > min_prop_val)
            continue;
            
        if (prop_val < min_prop_val) {
            tmpOutputResStructs.clear();
            min_prop_val = prop_val;
        }

        tmpOutputResStructs.push_back(res_struct);
    }

    outputResStructs.swap(tmpOutputResStructs);
    tmpOutputResStructs.clear();
}

std::size_t Chem::ResonanceStructureGenerator::countOctetRuleViolations(const StructureData& res_struct) const
{
    std::size_t count = 0;
    
    for (AtomDataPtrArray::const_iterator it = resAtoms.begin(), end = resAtoms.end(); it != end; ++it) {
        const AtomData* atom_data = *it;
            
        if (octRuleCheckAtomTypes.test(atom_data->getType())&& !atom_data->octetRuleFulfilled(res_struct))
            count++;
    }
    
    return count;
}

std::size_t Chem::ResonanceStructureGenerator::countSP1GeometryViolations(const StructureData& res_struct) const
{
    std::size_t count = 0;
    
    for (AtomDataPtrArray::const_iterator it = resAtoms.begin(), end = resAtoms.end(); it != end; ++it) {
        const AtomData* atom_data = *it;
            
        if (atom_data->getInSmallRingFlag() && atom_data->isSP1Hybridized(res_struct))
            count++;
    }
    
    return count;
}

std::size_t Chem::ResonanceStructureGenerator::count12ChargedCBonds(const StructureData& res_struct) const
{
    std::size_t count = 0;
    
    for (BondDataList::const_iterator it = resBonds.begin(), end = resBonds.end(); it != end; ++it) {
        const BondData& bond_data = *it;
            
        if ((atomData[bond_data.atom1Index].getType() == AtomType::C || atomData[bond_data.atom2Index].getType() == AtomType::C) &&
            res_struct.atomCharges[bond_data.atom1Index] != 0 && res_struct.atomCharges[bond_data.atom2Index] != 0)
            count++;
    }
    
    return count;
}

void Chem::ResonanceStructureGenerator::modifyResStruct(StructureData& res_struct, std::size_t bond_idx, std::size_t atom1_idx, std::size_t atom2_idx,  
                                                        long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff) const
{
    res_struct.bondOrders[bond_idx] += bond_order_diff;
    res_struct.atomCharges[atom1_idx] += atom1_chg_diff;
    res_struct.atomCharges[atom2_idx] += atom2_chg_diff;
}

Chem::ResonanceStructureGenerator::StructureDataPtr Chem::ResonanceStructureGenerator::copyResStruct(const StructureData& res_struct)
{
    StructureDataPtr rs_copy = resStructDataCache.get();

    *rs_copy = res_struct;

    return rs_copy;
}

Chem::ResonanceStructureGenerator::StructureDataPtr Chem::ResonanceStructureGenerator::copyResStructPtr(const StructureDataPtr& res_struct_ptr)
{
    return copyResStruct(*res_struct_ptr);
}

//---------

const Util::LArray& Chem::ResonanceStructureGenerator::StructureData::getAtomCharges() const
{
    return atomCharges;
}

const Util::STArray& Chem::ResonanceStructureGenerator::StructureData::getBondOrders() const
{
    return bondOrders;
}

//---------

long Chem::ResonanceStructureGenerator::AtomData::init(const Atom& atom, const MolecularGraph& molgraph, std::size_t idx)
{
    canShiftElecs = false;
    visited = false;
    inSmallRing = false;
    index = idx;
    type = Chem::getType(atom);
    valElecCount = AtomDictionary::getNumValenceElectrons(type);
    enegativity = AtomDictionary::getAllredRochowElectronegativity(type);
    unprdElecCount = getUnpairedElectronCount(atom);
    implHCount = getImplicitHydrogenCount(atom);
    
    long form_charge = getFormalCharge(atom);
    std::size_t iupac_grp = AtomDictionary::getIUPACGroup(type);

    if (iupac_grp < 14 || iupac_grp > 16)
        return form_charge;

    bondIndices.clear();

    std::size_t exp_val = 0;
    bool unsat = getAromaticityFlag(atom);
    Atom::ConstBondIterator b_it = atom.getBondsBegin();
    
    for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        const Atom& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;
        
        const Bond& nbr_bond = *b_it;

        if (!molgraph.containsBond(nbr_bond))
            continue;

        bondIndices.push_back(molgraph.getBondIndex(nbr_bond));
        atomIndices.push_back(molgraph.getAtomIndex(nbr_atom));

        std::size_t order = getOrder(nbr_bond);

        exp_val += order;
        unsat |= (order > 1);
    }

    if (bondIndices.empty())
        return form_charge;

    if (form_charge == 0 && !unsat && (valElecCount - unprdElecCount - implHCount - exp_val) < 2)
        return form_charge;

    canShiftElecs = true;
    
    return form_charge;
}

bool Chem::ResonanceStructureGenerator::AtomData::canShiftElectrons() const
{
    return canShiftElecs;
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getIndex() const
{
    return index;
}

unsigned int Chem::ResonanceStructureGenerator::AtomData::getType() const
{
    return type;
}
            
std::size_t Chem::ResonanceStructureGenerator::AtomData::getNumBonds() const
{
    return bondIndices.size();
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getBondIndex(std::size_t list_idx) const
{
    return bondIndices[list_idx];
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::getAtomIndex(std::size_t list_idx) const
{
    return atomIndices[list_idx];
}

double Chem::ResonanceStructureGenerator::AtomData::getElectronegativity() const
{
    return enegativity;
}

bool Chem::ResonanceStructureGenerator::AtomData::getVisitedFlag() const
{
    return visited;
}

void Chem::ResonanceStructureGenerator::AtomData::setVisitedFlag()
{
    visited = true;
}
                
bool Chem::ResonanceStructureGenerator::AtomData::getInSmallRingFlag() const
{
    return inSmallRing;
}

void Chem::ResonanceStructureGenerator::AtomData::setInSmallRingFlag()
{
    inSmallRing = true;
}

bool Chem::ResonanceStructureGenerator::AtomData::isSP1Hybridized(const StructureData& res_struct) const
{
    if (type > AtomType::N)
        return false;

    if (implHCount + unprdElecCount + bondIndices.size() != 2)
        return false;
    
    long val = implHCount + unprdElecCount;

    for (IndexArray::const_iterator it = bondIndices.begin(), end = bondIndices.end(); it != end; ++it)
        val += res_struct.bondOrders[*it];
    
    return (val == 4);
}

bool Chem::ResonanceStructureGenerator::AtomData::checkValenceState(const StructureData& res_struct, long val_diff, long charge_diff) const
{
    long elec_cnt = valElecCount - charge_diff - res_struct.atomCharges[index];

    if (elec_cnt > 8)
        return false;

    long val = implHCount + unprdElecCount + val_diff;

    for (IndexArray::const_iterator it = bondIndices.begin(), end = bondIndices.end(); it != end; ++it)
        val += res_struct.bondOrders[*it];

    if (type <= AtomType::O) {
        if (val > 4 || val > elec_cnt)
            return false;

        return ((val + elec_cnt) <= 8);
    }
    
    return (val <= elec_cnt);
}

bool Chem::ResonanceStructureGenerator::AtomData::octetRuleFulfilled(const StructureData& res_struct) const
{
    long elec_cnt = valElecCount - res_struct.atomCharges[index] + implHCount;

    for (IndexArray::const_iterator it = bondIndices.begin(), end = bondIndices.end(); it != end; ++it)
        elec_cnt += res_struct.bondOrders[*it];

    return (elec_cnt == 8);
}

std::size_t Chem::ResonanceStructureGenerator::AtomData::countRepChargePairs(const Util::LArray& charges) const
{
    std::size_t count = 0;
    long charge = charges[index];

    if (charge < 0) {
        for (IndexArray::const_iterator it = atomIndices.begin(), end = atomIndices.end(); it != end; ++it)
            if (charges[*it] < 0)
                count++;
                    
    } else if (charge > 0) {
        for (IndexArray::const_iterator it = atomIndices.begin(), end = atomIndices.end(); it != end; ++it)
            if (charges[*it] > 0)
                count++;
    }
    
    return count;
}


std::size_t Chem::ResonanceStructureGenerator::StructureDataPtrHashFunc::operator()(const StructureDataPtr& rs_ptr) const
{
    std::size_t seed = 0;
                    
    boost::hash_combine(seed, boost::hash_value(rs_ptr->getBondOrders().getData()));
    boost::hash_combine(seed, boost::hash_value(rs_ptr->getAtomCharges().getData()));

    return seed;
}
