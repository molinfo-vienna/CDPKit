/* 
 * HashCodeCalculator.cpp 
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
#include <functional>

#include <boost/math/special_functions/prime.hpp>

#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Internal/SHA1.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


namespace 
{

    const std::size_t ATOM_CONFIG_R_IDX           = 0;
    const std::size_t ATOM_CONFIG_S_IDX           = 1;
    const std::size_t ATOM_CONFIG_M_IDX           = 2;
    const std::size_t ATOM_CONFIG_P_IDX           = 3;
    const std::size_t ATOM_CONFIG_r_IDX           = 4;
    const std::size_t ATOM_CONFIG_s_IDX           = 5;
    const std::size_t ATOM_CONFIG_m_IDX           = 6;
    const std::size_t ATOM_CONFIG_p_IDX           = 7;
    const std::size_t ATOM_H_COUNT_IDX            = ATOM_CONFIG_p_IDX + 1;
    const std::size_t ATOM_H_COUNT_RANGE          = 5;
    const std::size_t ATOM_NEG_CHARGE_IDX         = ATOM_H_COUNT_IDX + ATOM_H_COUNT_RANGE;
    const std::size_t ATOM_NEG_CHARGE_RANGE       = 4;
    const std::size_t ATOM_POS_CHARGE_IDX         = ATOM_NEG_CHARGE_IDX + ATOM_NEG_CHARGE_RANGE;
    const std::size_t ATOM_POS_CHARGE_RANGE       = 4;
    const std::size_t ATOM_GLOBAL_STEREO_REF_IDX  = ATOM_POS_CHARGE_IDX + ATOM_POS_CHARGE_RANGE;
    const std::size_t ATOM_TYPE_IDX               = ATOM_GLOBAL_STEREO_REF_IDX + 1;
    const std::size_t ATOM_TYPE_RANGE             = Chem::AtomType::MAX_ATOMIC_NO + 1;
    const std::size_t ATOM_ISOTOPE_IDX            = ATOM_TYPE_IDX + ATOM_TYPE_RANGE;
    const std::size_t ATOM_ISOTOPE_RANGE          = 200;
    const std::size_t ATOM_AROMATICITY_IDX        = ATOM_ISOTOPE_IDX + ATOM_ISOTOPE_RANGE;

    const std::size_t BOND_AROM_FLAG_IDX          = 0;
    const std::size_t BOND_RING_FLAG_IDX          = BOND_AROM_FLAG_IDX + 1;
    const std::size_t BOND_CONFIG_E_IDX           = BOND_RING_FLAG_IDX + 1;
    const std::size_t BOND_CONFIG_Z_IDX           = BOND_CONFIG_E_IDX + 1;
    const std::size_t BOND_CONFIG_SEQCIS_IDX      = BOND_CONFIG_Z_IDX + 1;
    const std::size_t BOND_CONFIG_SEQTRANS_IDX    = BOND_CONFIG_SEQCIS_IDX + 1;
    const std::size_t BOND_ORDER_IDX              = BOND_CONFIG_SEQTRANS_IDX + 1;
    const std::size_t BOND_ORDER_RANGE            = 4;

    const std::size_t NUM_ATOM_HASH_ITERATIONS    = 32;
    const std::size_t NUM_BOND_HASH_ITERATIONS    = 32;

    typedef std::pair<const Chem::Atom*, const Chem::Bond*> Ligand;

    class AtomCIPPGreaterCmpFunc
    {

    public:
        AtomCIPPGreaterCmpFunc() {}

        bool operator()(const Ligand& lig1, const Ligand& lig2) const {
            return (getCIPPriority(*lig1.first) > getCIPPriority(*lig2.first));
        }
    };
}


constexpr unsigned int Chem::HashCodeCalculator::DEF_ATOM_PROPERTY_FLAGS;
constexpr unsigned int Chem::HashCodeCalculator::DEF_BOND_PROPERTY_FLAGS;

//-----

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::operator()(const Atom& atom) const
{
    std::uint64_t seed = 1;

    if (flags & AtomPropertyFlag::TYPE)
        seed = getAtomTypeHashSeed(atom);
    
    if (flags & AtomPropertyFlag::ISOTOPE)
        seed *= getAtomIsotopeHashSeed(atom);

    if (flags & AtomPropertyFlag::H_COUNT)
        seed *= getAtomHCountHashSeed(atom);

    if (flags & AtomPropertyFlag::FORMAL_CHARGE)
        seed *= getAtomChargeHashSeed(atom);

    if (flags & AtomPropertyFlag::CIP_CONFIGURATION)
        seed *= getAtomConfigHashSeed(atom);

    if (flags & AtomPropertyFlag::AROMATICITY)
        seed *= getAtomAromaticityHashSeed(atom);

    return seed;
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomTypeHashSeed(const Atom& atom) const
{
    return boost::math::prime(ATOM_TYPE_IDX + (getType(atom) % ATOM_TYPE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomIsotopeHashSeed(const Atom& atom) const
{
    return boost::math::prime(ATOM_ISOTOPE_IDX + (getIsotope(atom) % ATOM_ISOTOPE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomAromaticityHashSeed(const Atom& atom) const
{
    if (getAromaticityFlag(atom))
        return boost::math::prime(ATOM_AROMATICITY_IDX);

    return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomChargeHashSeed(const Atom& atom) const
{
    const long charge = getFormalCharge(atom);

    if (charge < 0)
        return boost::math::prime(ATOM_NEG_CHARGE_IDX + ((-charge - 1) % ATOM_NEG_CHARGE_RANGE));
    
    return boost::math::prime(ATOM_POS_CHARGE_IDX + (charge % ATOM_POS_CHARGE_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomHCountHashSeed(const Atom& atom) const
{
    return boost::math::prime(ATOM_H_COUNT_IDX + (Internal::getBondCount(atom, *calculator.molGraph, 1, AtomType::H) % ATOM_H_COUNT_RANGE));
}

std::uint64_t Chem::HashCodeCalculator::DefAtomHashSeedFunctor::getAtomConfigHashSeed(const Atom& atom) const
{
    unsigned int config = getCIPConfiguration(atom);

    switch (config) {

        case CIPDescriptor::R: 
            return boost::math::prime(ATOM_CONFIG_R_IDX);

        case CIPDescriptor::S: 
            return boost::math::prime(ATOM_CONFIG_S_IDX);

        case CIPDescriptor::M: 
            return boost::math::prime(ATOM_CONFIG_M_IDX);

        case CIPDescriptor::P: 
            return boost::math::prime(ATOM_CONFIG_P_IDX);

        case CIPDescriptor::r: 
            return boost::math::prime(ATOM_CONFIG_r_IDX);

        case CIPDescriptor::s: 
            return boost::math::prime(ATOM_CONFIG_s_IDX);

        case CIPDescriptor::m: 
            return boost::math::prime(ATOM_CONFIG_m_IDX);

        case CIPDescriptor::p: 
            return boost::math::prime(ATOM_CONFIG_p_IDX);

        default: 
            return 1;
    }
}

//-----

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::operator()(const Bond& bond) const
{
    std::uint64_t seed = 1;
    
    if (flags & (BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY))
        seed = getBondTypeHashSeed(bond);

    if (flags & BondPropertyFlag::CIP_CONFIGURATION)
        seed *= getBondConfigHashSeed(bond);

    if (flags & BondPropertyFlag::TOPOLOGY)
        seed *= getBondTopologyHashSeed(bond);

    return seed;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondTopologyHashSeed(const Bond& bond) const
{
    if (getRingFlag(bond))
        return boost::math::prime(BOND_RING_FLAG_IDX);

    return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondTypeHashSeed(const Bond& bond) const
{
    if ((flags & BondPropertyFlag::AROMATICITY) && getAromaticityFlag(bond))
        return boost::math::prime(BOND_AROM_FLAG_IDX);

    if (flags & BondPropertyFlag::ORDER) 
        return boost::math::prime(BOND_ORDER_IDX + (getOrder(bond) % BOND_ORDER_RANGE));
    return 1;
}

std::uint64_t Chem::HashCodeCalculator::DefBondHashSeedFunctor::getBondConfigHashSeed(const Bond& bond) const
{
    unsigned int config = getCIPConfiguration(bond);

    switch (config) {

        case CIPDescriptor::E:
            return boost::math::prime(BOND_CONFIG_E_IDX);

        case CIPDescriptor::Z:
            return boost::math::prime(BOND_CONFIG_Z_IDX);

        case CIPDescriptor::seqCis:
            return boost::math::prime(BOND_CONFIG_SEQCIS_IDX);

        case CIPDescriptor::seqTrans:
            return boost::math::prime(BOND_CONFIG_SEQTRANS_IDX);

        default:
            return 1;
    }
}

//-----

Chem::HashCodeCalculator::HashCodeCalculator():
    atomHashSeedFunc(DefAtomHashSeedFunctor(*this)), bondHashSeedFunc(DefBondHashSeedFunctor())
{
    std::fill(shaHashCode, shaHashCode + sizeof(shaHashCode), 0);
}

Chem::HashCodeCalculator::HashCodeCalculator(const MolecularGraph& molgraph):
    atomHashSeedFunc(DefAtomHashSeedFunctor(*this)), bondHashSeedFunc(DefBondHashSeedFunctor())
{
    std::fill(shaHashCode, shaHashCode + sizeof(shaHashCode), 0);

    calculate(molgraph);
}

std::uint64_t Chem::HashCodeCalculator::calculate(const MolecularGraph& molgraph)
{
    init(molgraph);

    calcAtomHashCodes();
    calcBondHashCodes();
    calcSHAHashCode();

    return getResult();
}

std::uint64_t Chem::HashCodeCalculator::getResult() const
{
    std::uint64_t hash_code = 0;

    for (std::size_t i = 0; i < Internal::SHA1::HASH_SIZE; i++) 
        hash_code = hash_code ^ (std::uint64_t(shaHashCode[i]) << ((i % 8) * 8));

    return hash_code;
}

void Chem::HashCodeCalculator::setAtomHashSeedFunction(const AtomHashSeedFunction& func)
{
    atomHashSeedFunc = func;
}

void Chem::HashCodeCalculator::setBondHashSeedFunction(const BondHashSeedFunction& func)
{
    bondHashSeedFunc = func;
}

void Chem::HashCodeCalculator::init(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;

    std::size_t num_atoms = molgraph.getNumAtoms();
    std::size_t num_bonds = molgraph.getNumBonds();

    if (atomHashCodes.size() < num_atoms)
        atomHashCodes.resize(num_atoms); 

    MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
        const Atom& atom = *it;
        std::size_t atom_idx = molgraph.getAtomIndex(atom);

        atomHashCodes[atom_idx] = atomHashSeedFunc(atom);
    }

    if (bondHashCodes.size() < num_bonds)
        bondHashCodes.resize(num_bonds); 

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;

        if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
            continue;

        std::size_t bond_idx = molgraph.getBondIndex(bond);
        
        bondHashCodes[bond_idx] = bondHashSeedFunc(bond);
    }
}

void Chem::HashCodeCalculator::calcAtomHashCodes()
{
    MolecularGraph::ConstAtomIterator atoms_beg = molGraph->getAtomsBegin();
    MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();
    
    std::size_t num_atoms = molGraph->getNumAtoms();

    if (tmpHashCodes1.size() < num_atoms)
        tmpHashCodes1.resize(num_atoms);

    for (std::size_t i = 0, num_iter = std::min(num_atoms, NUM_ATOM_HASH_ITERATIONS); i < num_iter; i++) {
        for (MolecularGraph::ConstAtomIterator it1 = atoms_beg; it1 != atoms_end; ++it1) {
            const Atom& atom = *it1;
            std::size_t atom_idx = molGraph->getAtomIndex(atom);

            tmpHashCodes2.clear();

            Atom::ConstAtomIterator nbr_atoms_end = atom.getAtomsEnd();
            Atom::ConstBondIterator it3 = atom.getBondsBegin();

            for (Atom::ConstAtomIterator it2 = atom.getAtomsBegin(); it2 != nbr_atoms_end; ++it2, ++it3) {
                if (!molGraph->containsAtom(*it2) || !molGraph->containsBond(*it3))
                    continue;

                std::size_t nbr_atom_idx = molGraph->getAtomIndex(*it2);

                tmpHashCodes2.push_back(atomHashCodes[nbr_atom_idx]);
            }
            
            UInt64Array::iterator nbr_hash_beg = tmpHashCodes2.begin();
            UInt64Array::iterator nbr_hash_end = tmpHashCodes2.end();

            std::sort(nbr_hash_beg, nbr_hash_end);

            std::uint64_t new_hash_code = atomHashCodes[atom_idx];

            for (UInt64Array::const_iterator it2 = nbr_hash_beg; it2 != nbr_hash_end; ++it2) 
                new_hash_code = (new_hash_code << 1) ^ *it2;

            tmpHashCodes1[atom_idx] = new_hash_code;
        }
        
        atomHashCodes.swap(tmpHashCodes1);
    }
}

void Chem::HashCodeCalculator::calcBondHashCodes()
{
    MolecularGraph::ConstBondIterator bonds_beg = molGraph->getBondsBegin();
    MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = bonds_beg; it != bonds_end; ++it) {
        const Bond& bond = *it;

        if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
            continue;

        std::size_t bond_idx = molGraph->getBondIndex(bond);

        bondHashCodes[bond_idx] ^= atomHashCodes[molGraph->getAtomIndex(bond.getBegin())] + 
            atomHashCodes[molGraph->getAtomIndex(bond.getEnd())];
    }

    std::size_t num_bonds = molGraph->getNumBonds();

    if (tmpHashCodes1.size() < num_bonds)
        tmpHashCodes1.resize(num_bonds);

    for (std::size_t i = 0, num_iter = std::min(num_bonds, NUM_BOND_HASH_ITERATIONS); i < num_iter; i++) {
        for (MolecularGraph::ConstBondIterator it1 = bonds_beg; it1 != bonds_end; ++it1) {
            const Bond& bond = *it1;

            if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
                continue;

            std::size_t bond_idx = molGraph->getBondIndex(bond);

            tmpHashCodes2.clear();

            Atom::ConstBondIterator nbr_bonds_end = bond.getBegin().getBondsEnd();
            Atom::ConstAtomIterator a_it = bond.getBegin().getAtomsBegin();

            for (Atom::ConstBondIterator it2 = bond.getBegin().getBondsBegin(); it2 != nbr_bonds_end; ++it2, ++a_it) {
                if (!molGraph->containsBond(*it2) || !molGraph->containsAtom(*a_it))
                    continue;

                std::size_t nbr_bond_idx = molGraph->getBondIndex(*it2);

                tmpHashCodes2.push_back(bondHashCodes[nbr_bond_idx]);
            }
            
            nbr_bonds_end = bond.getEnd().getBondsEnd();
            a_it = bond.getEnd().getAtomsBegin();

            for (Atom::ConstBondIterator it2 = bond.getEnd().getBondsBegin(); it2 != nbr_bonds_end; ++it2, ++a_it) {
                if (!molGraph->containsBond(*it2) || !molGraph->containsAtom(*a_it))
                    continue;

                std::size_t nbr_bond_idx = molGraph->getBondIndex(*it2);

                tmpHashCodes2.push_back(bondHashCodes[nbr_bond_idx]);
            }
            
            UInt64Array::iterator bnd_hash_beg = tmpHashCodes2.begin();
            UInt64Array::iterator bnd_hash_end = tmpHashCodes2.end();

            std::sort(bnd_hash_beg, bnd_hash_end);

            std::uint64_t new_hash_code = bondHashCodes[bond_idx];

            for (UInt64Array::const_iterator it2 = bnd_hash_beg; it2 != bnd_hash_end; ++it2) 
                new_hash_code = (new_hash_code << 1) ^ *it2;

            tmpHashCodes1[bond_idx] = new_hash_code;
        }

        bondHashCodes.swap(tmpHashCodes1);
    }
}

void Chem::HashCodeCalculator::calcSHAHashCode()
{
    shaInput.clear();

    MolecularGraph::ConstAtomIterator atoms_end = molGraph->getAtomsEnd();

    for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(); it != atoms_end; ++it) {
        std::size_t atom_idx = molGraph->getAtomIndex(*it);

        shaInput.push_back(atomHashCodes[atom_idx]);
    }

    MolecularGraph::ConstBondIterator bonds_end = molGraph->getBondsEnd();

    for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
    
        if (!molGraph->containsAtom(bond.getBegin()) || !molGraph->containsAtom(bond.getEnd()))
            continue;

        std::size_t bond_idx = molGraph->getBondIndex(*it);

        shaInput.push_back(bondHashCodes[bond_idx]);
    }

    std::sort(shaInput.begin(), shaInput.end());

    Internal::SHA1 sha;

    sha.input(shaInput.begin(), shaInput.end());
    sha.getResult(&shaHashCode[0]);
}
