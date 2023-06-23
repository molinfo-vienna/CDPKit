/* 
 * BondDirectionCalculator.cpp 
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
#include <limits>
#include <cassert>

#include "CDPL/Chem/BondDirectionCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL;


Chem::BondDirectionCalculator::BondDirectionCalculator():
    incRingBonds(true), minRingSize(8) {}

Chem::BondDirectionCalculator::BondDirectionCalculator(const MolecularGraph& molgraph, Util::UIArray& dirs):
    incRingBonds(true), minRingSize(8)
{
    calculate(molgraph, dirs);
}

void Chem::BondDirectionCalculator::includeRingBonds(bool include) 
{
    incRingBonds = include;
}

bool Chem::BondDirectionCalculator::ringBondsIncluded() const
{
    return incRingBonds;
}

void Chem::BondDirectionCalculator::setRingSizeLimit(std::size_t rsize)
{
    minRingSize = rsize;
}

std::size_t Chem::BondDirectionCalculator::getRingSizeLimit() const
{
    return minRingSize;
}

void Chem::BondDirectionCalculator::calculate(const MolecularGraph& molgraph, Util::UIArray& dirs)
{
    init(molgraph, dirs);

    if (!stereoBonds.empty())
        assignDirections(0, dirs);
}

void Chem::BondDirectionCalculator::init(const MolecularGraph& molgraph, Util::UIArray& dirs)
{
    molGraph = &molgraph;

    std::size_t num_bonds = molgraph.getNumBonds();

    dirs.assign(num_bonds, BondDirection::NONE);
    workingDirs.assign(num_bonds, BondDirection::NONE);

    if (configMatchMask.size() < num_bonds)
        configMatchMask.resize(num_bonds);

    configMatchMask.reset();

    atomStereoBondTable.assign(molgraph.getNumAtoms(), 0);

    stereoBonds.reserve(num_bonds);
    stereoBonds.clear();
    orderedStereoBonds.clear();

    FragmentList::SharedPointer sssr;

    if (incRingBonds && minRingSize > 0)
        sssr = getSSSR(molgraph);

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
        const Atom* bond_atoms[2] = { &bond.getBegin(), &bond.getEnd() };

        if (!molgraph.containsAtom(*bond_atoms[0]) || !molgraph.containsAtom(*bond_atoms[1]))
            continue;
    
        const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);
        unsigned int config = stereo_desc.getConfiguration();

        if (config != BondConfiguration::EITHER && config != BondConfiguration::CIS && config != BondConfiguration::TRANS)
            continue;

        if (!incRingBonds) {
            if (getRingFlag(bond))
                config = BondConfiguration::EITHER;

        } else if (minRingSize > 0) {
            std::size_t min_rsize = getSizeOfSmallestContainingFragment(bond, *sssr);

            if (min_rsize > 0 && min_rsize < minRingSize)
                config = BondConfiguration::EITHER;
        }

        if (molgraph.getAtomIndex(*bond_atoms[0]) > molgraph.getAtomIndex(*bond_atoms[1]))
            std::swap(bond_atoms[0], bond_atoms[1]);

        const Atom* config_ref_atoms[2] = { 0, 0 };

        if (config != BondConfiguration::EITHER) {
            if (!stereo_desc.isValid(bond))
                continue;

            const Atom* const* sto_ref_atoms = stereo_desc.getReferenceAtoms();
    
            if (sto_ref_atoms[1] == bond_atoms[1] && sto_ref_atoms[2] == bond_atoms[0]) {
                config_ref_atoms[0] = sto_ref_atoms[3];
                config_ref_atoms[1] = sto_ref_atoms[0];

            } else  {
                config_ref_atoms[0] = sto_ref_atoms[0];
                config_ref_atoms[1] = sto_ref_atoms[3];
            }
        }

        StereoBond stereo_bond(bond);
        bool add_to_list = true;

        for (std::size_t i = 0; i < 2; i++) {
            const Atom* nbr_atoms[2] = { 0, 0 };
            const Bond* nbr_bonds[2] = { 0, 0 };
            
            Atom::ConstBondIterator nbr_bonds_end = bond_atoms[i]->getBondsEnd();
            Atom::ConstAtomIterator a_it = bond_atoms[i]->getAtomsBegin();

            for (Atom::ConstBondIterator nbr_b_it = bond_atoms[i]->getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++a_it) {
                const Bond& nbr_bond = *nbr_b_it;

                if (&nbr_bond == &bond)
                    continue;

                const Atom& nbr_atom = *a_it;                

                if (!molgraph.containsBond(nbr_bond) || !molgraph.containsAtom(nbr_atom))
                    continue;

                std::size_t nbr_idx = (nbr_atoms[0] ? 1 : 0);
                
                nbr_atoms[nbr_idx] = &nbr_atom;
                nbr_bonds[nbr_idx] = &nbr_bond;
            }

            if (!nbr_atoms[0]) {
                add_to_list = false;
                break;
            }

            if (!nbr_atoms[1]) 
                stereo_bond.addNeighborIndices(i, molgraph.getBondIndex(*nbr_bonds[0]), molgraph.getAtomIndex(*nbr_atoms[0]));

            else {
                std::size_t nbr_atom1_idx = molgraph.getAtomIndex(*nbr_atoms[0]);
                std::size_t nbr_atom2_idx = molgraph.getAtomIndex(*nbr_atoms[1]);

                if (nbr_atom1_idx < nbr_atom2_idx) {
                    stereo_bond.addNeighborIndices(i, molgraph.getBondIndex(*nbr_bonds[0]), nbr_atom1_idx);
                    stereo_bond.addNeighborIndices(i, molgraph.getBondIndex(*nbr_bonds[1]), nbr_atom2_idx);

                } else {
                    stereo_bond.addNeighborIndices(i, molgraph.getBondIndex(*nbr_bonds[1]), nbr_atom2_idx);
                    stereo_bond.addNeighborIndices(i, molgraph.getBondIndex(*nbr_bonds[0]), nbr_atom1_idx);
                }
            }
        }

        if (!add_to_list)
            continue;

        if     (config != BondConfiguration::EITHER &&
             ((&molgraph.getAtom(stereo_bond.getNeighborAtomIndex(0, 0)) == config_ref_atoms[0]) ^ 
              (&molgraph.getAtom(stereo_bond.getNeighborAtomIndex(1, 0)) == config_ref_atoms[1])))
            config = (config == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);
        
        stereo_bond.setConfiguration(config);
        stereoBonds.push_back(stereo_bond);

        StereoBond* stereo_bond_ptr = &stereoBonds.back();

        orderedStereoBonds.push_back(stereo_bond_ptr);

        atomStereoBondTable[molgraph.getAtomIndex(*bond_atoms[0])] = stereo_bond_ptr;
        atomStereoBondTable[molgraph.getAtomIndex(*bond_atoms[1])] = stereo_bond_ptr;
    }

    if (!stereoBonds.empty()) {
        std::sort(orderedStereoBonds.begin(), orderedStereoBonds.end(), StereoBondOrderingFunction(*this));

        numMismatches = 0;
        minNumMismatches = std::numeric_limits<std::size_t>::max();
        numDirBonds = 0;
        minNumDirBonds = std::numeric_limits<std::size_t>::max();
    }
}

bool Chem::BondDirectionCalculator::assignDirections(std::size_t list_idx, Util::UIArray& dirs)
{    
    if (numMismatches > minNumMismatches)
        return false;

    if (numMismatches == minNumMismatches && numDirBonds >= minNumDirBonds)
        return false;

    if (list_idx == stereoBonds.size()) {
        dirs = workingDirs;

        if (numMismatches == 0 && numDirBonds <= stereoBonds.size() * 2)
            return true;
            
        minNumMismatches = numMismatches;
        minNumDirBonds = numDirBonds;

        return false;
    }

    const StereoBond& stereo_bond = *orderedStereoBonds[list_idx];
    std::size_t bond_idx = molGraph->getBondIndex(stereo_bond.getBond());

    if (stereo_bond.configMatches(workingDirs)) {
        configMatchMask.set(bond_idx);

        if (assignDirections(list_idx + 1, dirs))
            return true;

        configMatchMask.reset(bond_idx);

        return false;
    }

    if (stereo_bond.getConfiguration() != BondConfiguration::EITHER) {
        bool has_dir_bonds1 = stereo_bond.hasDirBonds(workingDirs, 0);
        bool has_dir_bonds2 = stereo_bond.hasDirBonds(workingDirs, 1);

        if (!has_dir_bonds1 && !has_dir_bonds2) {
            std::size_t num_nbrs1 = stereo_bond.getNumNeighbors(0);
            std::size_t num_nbrs2 = stereo_bond.getNumNeighbors(1);

            for (std::size_t i = 0; i < num_nbrs1; i++) {
                unsigned int& nbr_dir1 = workingDirs[stereo_bond.getNeighborBondIndex(0, i)];

                assert(nbr_dir1 == BondDirection::NONE);

                const StereoBond* nbr_stereo_bond1 = atomStereoBondTable[stereo_bond.getNeighborAtomIndex(0, i)];
                bool check_nbr_stereo_bond1 = false;

                if (nbr_stereo_bond1)
                    check_nbr_stereo_bond1 = configMatchMask.test(molGraph->getBondIndex(nbr_stereo_bond1->getBond()));

                for (std::size_t j = 0; j < 2; j++) {
                    switchDirection(nbr_dir1);

                    for (std::size_t k = 0; k < num_nbrs2; k++) {
                        unsigned int& nbr_dir2 = workingDirs[stereo_bond.getNeighborBondIndex(1, k)];

                        assert(nbr_dir2 == BondDirection::NONE);

                        const StereoBond* nbr_stereo_bond2 = atomStereoBondTable[stereo_bond.getNeighborAtomIndex(1, k)];
                        bool check_nbr_stereo_bond2 = false;

                        if (nbr_stereo_bond2) 
                            check_nbr_stereo_bond2 = configMatchMask.test(molGraph->getBondIndex(nbr_stereo_bond2->getBond()));

                        for (std::size_t l = 0; l < 2; l++) {
                            switchDirection(nbr_dir2);

                            if (stereo_bond.configMatches(workingDirs)
                                && (!check_nbr_stereo_bond1 || nbr_stereo_bond1->configMatches(workingDirs))
                                && (!check_nbr_stereo_bond2 || nbr_stereo_bond2->configMatches(workingDirs))) {

                                configMatchMask.set(bond_idx);

                                if (assignDirections(list_idx + 1, dirs))
                                    return true;

                                configMatchMask.reset(bond_idx);
                            }
                        }

                        switchDirection(nbr_dir2);

                        assert(nbr_dir2 == BondDirection::NONE);
                    }
                }

                switchDirection(nbr_dir1);

                assert(nbr_dir1 == BondDirection::NONE);
            }

        } else if ((has_dir_bonds1 && !has_dir_bonds2) || (!has_dir_bonds1 && has_dir_bonds2)) {
            std::size_t atom_idx = (has_dir_bonds1 ? 1 : 0);
            std::size_t num_nbrs = stereo_bond.getNumNeighbors(atom_idx);

            for (std::size_t i = 0; i < num_nbrs; i++) {
                unsigned int& nbr_dir = workingDirs[stereo_bond.getNeighborBondIndex(atom_idx, i)];

                assert(nbr_dir == BondDirection::NONE);

                const StereoBond* nbr_stereo_bond = atomStereoBondTable[stereo_bond.getNeighborAtomIndex(atom_idx, i)];
                bool check_nbr_stereo_bond = false;

                if (nbr_stereo_bond)
                    check_nbr_stereo_bond = configMatchMask.test(molGraph->getBondIndex(nbr_stereo_bond->getBond()));

                for (std::size_t j = 0; j < 2; j++) {
                    switchDirection(nbr_dir);

                    if (stereo_bond.configMatches(workingDirs)
                        && (!check_nbr_stereo_bond || nbr_stereo_bond->configMatches(workingDirs))) {

                        configMatchMask.set(bond_idx);

                        if (assignDirections(list_idx + 1, dirs))
                            return true;

                        configMatchMask.reset(bond_idx);
                    }
                }

                switchDirection(nbr_dir);

                assert(nbr_dir == BondDirection::NONE);
            }
        }
    }

    numMismatches++;

    assignDirections(list_idx + 1, dirs);

    numMismatches--;

    return false;
}

void Chem::BondDirectionCalculator::switchDirection(unsigned int& bond_dir)
{
    switch (bond_dir) {

        case BondDirection::NONE:
            bond_dir = BondDirection::UP;

            numDirBonds++;
            return;

        case BondDirection::UP:
            bond_dir = BondDirection::DOWN;
            return;

        case BondDirection::DOWN:
            numDirBonds--;

        default:
            bond_dir = BondDirection::NONE;
            return;
    }
}


bool Chem::BondDirectionCalculator::StereoBondOrderingFunction::operator()(const StereoBond* lhs, const StereoBond* rhs) const
{
    const Bond& lhs_bond = lhs->getBond();
    const Bond& rhs_bond = rhs->getBond();

    std::size_t lhs_bond_atom_idx1 = calculator.molGraph->getAtomIndex(lhs_bond.getBegin());
    std::size_t lhs_bond_atom_idx2 = calculator.molGraph->getAtomIndex(lhs_bond.getEnd());

    if (lhs_bond_atom_idx1 > lhs_bond_atom_idx2)
        std::swap(lhs_bond_atom_idx1, lhs_bond_atom_idx2);

    std::size_t rhs_bond_atom_idx1 = calculator.molGraph->getAtomIndex(rhs_bond.getBegin());
    std::size_t rhs_bond_atom_idx2 = calculator.molGraph->getAtomIndex(rhs_bond.getEnd());

    if (rhs_bond_atom_idx1 > rhs_bond_atom_idx2)
        std::swap(rhs_bond_atom_idx1, rhs_bond_atom_idx2);

    if (lhs_bond_atom_idx1 == rhs_bond_atom_idx1)
        return (lhs_bond_atom_idx2 < rhs_bond_atom_idx2);

    return (lhs_bond_atom_idx1 < rhs_bond_atom_idx1);
}


Chem::BondDirectionCalculator::StereoBond::StereoBond(const Bond& bnd): bond(&bnd)
{
    nbrBondCounts[0] = 0;
    nbrBondCounts[1] = 0;
}

const Chem::Bond& Chem::BondDirectionCalculator::StereoBond::getBond() const
{
    return *bond;
}

unsigned int Chem::BondDirectionCalculator::StereoBond::getConfiguration() const
{
    return configuration;
}

void Chem::BondDirectionCalculator::StereoBond::setConfiguration(unsigned int config)
{
    configuration = config;
}

std::size_t Chem::BondDirectionCalculator::StereoBond::getNumNeighbors(std::size_t atom_idx) const
{
    assert(atom_idx <= 1);

    return nbrBondCounts[atom_idx];
}

std::size_t Chem::BondDirectionCalculator::StereoBond::getNeighborBondIndex(std::size_t atom_idx, std::size_t nbr_idx) const
{
    assert(atom_idx <= 1);
    assert(nbr_idx < nbrBondCounts[atom_idx]);

    return nbrBondIndices[atom_idx][nbr_idx];
}

std::size_t Chem::BondDirectionCalculator::StereoBond::getNeighborAtomIndex(std::size_t atom_idx, std::size_t nbr_idx) const
{
    assert(atom_idx <= 1);
    assert(nbr_idx < nbrBondCounts[atom_idx]);

    return nbrAtomIndices[atom_idx][nbr_idx];
}

void Chem::BondDirectionCalculator::StereoBond::addNeighborIndices(std::size_t atom_idx, std::size_t nbr_bond_idx, std::size_t nbr_atom_idx)
{
    assert(atom_idx <= 1);
    assert(nbrBondCounts[atom_idx] < 2);

    nbrBondIndices[atom_idx][nbrBondCounts[atom_idx]] = nbr_bond_idx;
    nbrAtomIndices[atom_idx][nbrBondCounts[atom_idx]++] = nbr_atom_idx;
}

bool Chem::BondDirectionCalculator::StereoBond::hasDirBonds(const Util::UIArray& dirs, std::size_t atom_idx) const
{
    assert(atom_idx <= 1);

    for (std::size_t i = 0; i < nbrBondCounts[atom_idx]; i++) {
        unsigned int dir = dirs[nbrBondIndices[atom_idx][i]];

        if (dir == BondDirection::UP || dir == BondDirection::DOWN)
            return true;
    }

    return false;
}

bool Chem::BondDirectionCalculator::StereoBond::configMatches(const Util::UIArray& dirs) const
{
    for (std::size_t i = 0; i < 2; i++)
        if (nbrBondCounts[i] > 1) {
            unsigned int dir1 = dirs[nbrBondIndices[i][0]] & (BondDirection::UP | BondDirection::DOWN);
            unsigned int dir2 = dirs[nbrBondIndices[i][1]] & (BondDirection::UP | BondDirection::DOWN);

            if (dir1 != BondDirection::NONE && dir2 != BondDirection::NONE && dir1 == dir2)
                return false;
        }

    if (configuration == BondConfiguration::EITHER) 
        return (!hasDirBonds(dirs, 0) || !hasDirBonds(dirs, 1));

    bool match = false;

    for (std::size_t i = 0; i < nbrBondCounts[0]; i++) {
        std::size_t bond_idx1 = nbrBondIndices[0][i];
        unsigned int bond_dir1 = dirs[bond_idx1] & (BondDirection::UP | BondDirection::DOWN);

        if (bond_dir1 == 0)
            continue;

        for (std::size_t j = 0; j < nbrBondCounts[1]; j++) {
            std::size_t bond_idx2 = nbrBondIndices[1][j];
            unsigned int bond_dir2 = dirs[bond_idx2] & (BondDirection::UP | BondDirection::DOWN);

            if (bond_dir2 == 0)
                continue;

            if ((bond_idx1 == nbrBondIndices[0][0] && bond_idx2 == nbrBondIndices[1][0])
                || (bond_idx1 != nbrBondIndices[0][0] && bond_idx2 != nbrBondIndices[1][0])) {

                switch (configuration) {
                         
                    case BondConfiguration::CIS:
                        if (bond_dir1 == bond_dir2)
                            return false;

                        break;

                    case BondConfiguration::TRANS:
                        if (bond_dir1 != bond_dir2)
                            return false;

                    default:
                        break;
                }

            } else {
                switch (configuration) {
                         
                    case BondConfiguration::CIS:
                        if (bond_dir1 != bond_dir2)
                            return false;

                        break;

                    case BondConfiguration::TRANS:
                        if (bond_dir1 == bond_dir2)
                            return false;

                    default:
                        break;
                }
            }

            match = true;
        }
    }

    return match;
}
