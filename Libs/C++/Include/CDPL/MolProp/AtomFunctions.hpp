/* 
 * AtomFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_MOLPROP_ATOMFUNCTIONS_HPP
#define CDPL_MOLPROP_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class MolecularGraph;
    } // namespace Chem

    namespace MolProp
    {

        /** \brief Returns the value of the MolProp::AtomProperty::HYDROPHOBICITY property of \a atom. */
        CDPL_MOLPROP_API double getHydrophobicity(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::HYDROPHOBICITY property of \a atom to \a hyd. */
        CDPL_MOLPROP_API void setHydrophobicity(Chem::Atom& atom, double hyd);

        /** \brief Removes the MolProp::AtomProperty::HYDROPHOBICITY property from \a atom. */
        CDPL_MOLPROP_API void clearHydrophobicity(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::HYDROPHOBICITY property. */
        CDPL_MOLPROP_API bool hasHydrophobicity(const Chem::Atom& atom);


        /** \brief Returns the value of the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property of \a atom. */
        CDPL_MOLPROP_API double getPEOESigmaCharge(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property of \a atom to \a charge. */
        CDPL_MOLPROP_API void setPEOESigmaCharge(Chem::Atom& atom, double charge);

        /** \brief Removes the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property from \a atom. */
        CDPL_MOLPROP_API void clearPEOESigmaCharge(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::PEOE_SIGMA_CHARGE property. */
        CDPL_MOLPROP_API bool hasPEOESigmaCharge(const Chem::Atom& atom);


        /** \brief Returns the value of the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property of \a atom. */
        CDPL_MOLPROP_API double getPEOESigmaElectronegativity(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property of \a atom to \a e_neg. */
        CDPL_MOLPROP_API void setPEOESigmaElectronegativity(Chem::Atom& atom, double e_neg);

        /** \brief Removes the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property from \a atom. */
        CDPL_MOLPROP_API void clearPEOESigmaElectronegativity(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property. */
        CDPL_MOLPROP_API bool hasPEOESigmaElectronegativity(const Chem::Atom& atom);


        /** \brief Returns the value of the MolProp::AtomProperty::MHMO_PI_CHARGE property of \a atom. */
        CDPL_MOLPROP_API double getMHMOPiCharge(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::MHMO_PI_CHARGE property of \a atom to \a charge. */
        CDPL_MOLPROP_API void setMHMOPiCharge(Chem::Atom& atom, double charge);

        /** \brief Removes the MolProp::AtomProperty::MHMO_PI_CHARGE property from \a atom. */
        CDPL_MOLPROP_API void clearMHMOPiCharge(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::MHMO_PI_CHARGE property. */
        CDPL_MOLPROP_API bool hasMHMOPiCharge(const Chem::Atom& atom);


        /** \brief Returns the value of the MolProp::AtomProperty::H_BOND_DONOR_TYPE property of \a atom (see namespace MolProp::HBondDonorAtomType). */
        CDPL_MOLPROP_API unsigned int getHBondDonorType(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::H_BOND_DONOR_TYPE property of \a atom to \a type. */
        CDPL_MOLPROP_API void setHBondDonorType(Chem::Atom& atom, unsigned int type);

        /** \brief Removes the MolProp::AtomProperty::H_BOND_DONOR_TYPE property from \a atom. */
        CDPL_MOLPROP_API void clearHBondDonorType(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::H_BOND_DONOR_TYPE property. */
        CDPL_MOLPROP_API bool hasHBondDonorType(const Chem::Atom& atom);


        /** \brief Returns the value of the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property of \a atom (see namespace MolProp::HBondAcceptorAtomType). */
        CDPL_MOLPROP_API unsigned int getHBondAcceptorType(const Chem::Atom& atom);

        /** \brief Sets the value of the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property of \a atom to \a type. */
        CDPL_MOLPROP_API void setHBondAcceptorType(Chem::Atom& atom, unsigned int type);

        /** \brief Removes the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property from \a atom. */
        CDPL_MOLPROP_API void clearHBondAcceptorType(Chem::Atom& atom);

        /** \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property. */
        CDPL_MOLPROP_API bool hasHBondAcceptorType(const Chem::Atom& atom);


        /** \brief Tells whether \a atom is a member of any ring in \a molgraph. */
        CDPL_MOLPROP_API bool isInRing(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Tells whether \a atom is a member of a ring of size \a size in \a molgraph. */
        CDPL_MOLPROP_API bool isInRingOfSize(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t size);

        /** \brief Returns the number of SSSR rings of \a molgraph that contain \a atom. */
        CDPL_MOLPROP_API std::size_t getNumContainingSSSRRings(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /** \brief Returns the standard atomic weight of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API double getAtomicWeight(const Chem::Atom& atom);

        /** \brief Returns the IUPAC group number of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API std::size_t getIUPACGroup(const Chem::Atom& atom);

        /** \brief Returns the period of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API std::size_t getPeriod(const Chem::Atom& atom);

        /** \brief Returns the van der Waals radius of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API double getVdWRadius(const Chem::Atom& atom);

        /** \brief Returns the covalent radius of the chemical element associated with \a atom for the given bond order. */
        CDPL_MOLPROP_API double getCovalentRadius(const Chem::Atom& atom, std::size_t order);

        /** \brief Returns the Allred-Rochow electronegativity of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API double getAllredRochowElectronegativity(const Chem::Atom& atom);

        /** \brief Returns the element name of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API const std::string& getElementName(const Chem::Atom& atom);

        /** \brief Returns the number of valence electrons of the chemical element associated with \a atom. */
        CDPL_MOLPROP_API std::size_t getElementValenceElectronCount(const Chem::Atom& atom);

        /** \brief Tells whether \a atom represents a chemical element. */
        CDPL_MOLPROP_API bool isChemicalElement(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a main-group element. */
        CDPL_MOLPROP_API bool isMainGroupElement(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a metal. */
        CDPL_MOLPROP_API bool isMetal(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a transition metal. */
        CDPL_MOLPROP_API bool isTransitionMetal(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a non-metal. */
        CDPL_MOLPROP_API bool isNonMetal(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a semi-metal. */
        CDPL_MOLPROP_API bool isSemiMetal(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a halogen. */
        CDPL_MOLPROP_API bool isHalogen(const Chem::Atom& atom);

        /** \brief Tells whether the chemical element associated with \a atom is a noble gas. */
        CDPL_MOLPROP_API bool isNobleGas(const Chem::Atom& atom);


        /**
         * \brief Tells whether \a atom is an ordinary hydrogen (no isotope, no charge, etc.).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that further qualify "ordinary".
         */
        CDPL_MOLPROP_API bool isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                 unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /** \brief Tells whether \a atom is a heavy (non-hydrogen) atom. */
        CDPL_MOLPROP_API bool isHeavy(const Chem::Atom& atom);

        /** \brief Tells whether \a atom is unsaturated (involved in at least one multiple bond) in \a molgraph. */
        CDPL_MOLPROP_API bool isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Tells whether \a atom acts as an H-bond acceptor in \a molgraph. */
        CDPL_MOLPROP_API bool isHBondAcceptor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Tells whether \a atom acts as an H-bond donor in \a molgraph. */
        CDPL_MOLPROP_API bool isHBondDonor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a carbonyl-like center in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon centers are recognized.
         * \param db_o_only If \c true, the multiple bond partner must be a double-bonded oxygen.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isCarbonylLike(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /**
         * \brief Tells whether \a atom is the carbon center of an amide group in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon centers are recognized.
         * \param db_o_only If \c true, the C=O must be a double bond to oxygen specifically.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isAmideCenter(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /**
         * \brief Tells whether \a atom is the nitrogen of an amide group in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon-bonded amides are recognized.
         * \param db_o_only If \c true, the C=O must be a double bond to oxygen specifically.
         */
        CDPL_MOLPROP_API bool isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /** \brief Tells whether \a atom is an invertible (pyramidal, non-aromatic, non-amide) nitrogen in \a molgraph. */
        CDPL_MOLPROP_API bool isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Tells whether \a atom is a planar nitrogen in \a molgraph. */
        CDPL_MOLPROP_API bool isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a bridgehead atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param bridged_only If \c true, only bridgeheads of bridged (non-fused) ring systems are recognized.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isBridgehead(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool bridged_only);

        /**
         * \brief Tells whether \a atom is a spiro center in \a molgraph.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isSpiroCenter(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
        
        
        /**
         * \brief Returns the number of ordinary-hydrogen neighbors of \a atom in \a molgraph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that qualify "ordinary".
         */
        CDPL_MOLPROP_API std::size_t getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                              unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /** \brief Returns the number of explicit neighbors of \a atom in \a molgraph that match the given atom type. */
        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        /** \brief Returns the number of neighbors (including implicit hydrogens) of \a atom in \a molgraph that match the given atom type. */
        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        /** \brief Returns the number of explicit chain (non-ring) neighbors of \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getExplicitChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of chain (non-ring) neighbors of \a atom in \a molgraph (including implicit hydrogens). */
        CDPL_MOLPROP_API std::size_t getChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of ring-atom neighbors of \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getRingAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of aromatic neighbors of \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getAromaticAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of heavy-atom neighbors of \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /** \brief Returns the number of explicit bonds incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of explicit bonds of the given order incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

        /** \brief Returns the number of explicit bonds of the given order incident to \a atom that bond to atoms matching the given type. */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

        /** \brief Returns the total number of bonds incident to \a atom in \a molgraph (including implicit-hydrogen bonds). */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the total number of bonds of the given order incident to \a atom (including implicit-hydrogen bonds). */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

        /** \brief Returns the total number of bonds of the given order incident to \a atom that bond to atoms matching the given type. */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

        /** \brief Returns the number of explicit chain (non-ring) bonds incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getExplicitChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of chain (non-ring) bonds incident to \a atom in \a molgraph (including implicit-hydrogen bonds). */
        CDPL_MOLPROP_API std::size_t getChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of ring bonds incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of aromatic bonds incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getAromaticBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Returns the number of heavy-atom bonds incident to \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of rotatable bonds incident to \a atom in \a molgraph.
         * \param h_rotors If \c true, hydrogen-only rotors are counted as rotatable.
         * \param ring_bonds If \c true, ring bonds are also considered.
         * \param amide_bonds If \c true, amide bonds are also considered.
         */
        CDPL_MOLPROP_API std::size_t getRotatableBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);


        /** \brief Calculates the explicit valence of \a atom in \a molgraph (sum of explicit bond orders). */
        CDPL_MOLPROP_API std::size_t calcExplicitValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Calculates the total valence of \a atom in \a molgraph (explicit valence plus implicit hydrogens). */
        CDPL_MOLPROP_API std::size_t calcValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /** \brief Calculates the number of free (lone-pair) valence electrons of \a atom in \a molgraph. */
        CDPL_MOLPROP_API std::size_t calcFreeValenceElectronCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Calculates the number of valence electrons of the chemical element associated with \a atom (corrected for the atom's formal charge). */
        CDPL_MOLPROP_API std::size_t calcValenceElectronCount(const Chem::Atom& atom);


        /** \brief Calculates the steric number of \a atom in \a molgraph (used by VSEPR theory). */
        CDPL_MOLPROP_API std::size_t calcStericNumber(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the VSEPR coordination geometry of \a atom in \a molgraph (see namespace MolProp::CoordinationGeometry).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param steric_num The pre-computed steric number of \a atom (avoids re-computation).
         */
        CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t steric_num);

        /** \brief Returns the VSEPR coordination geometry of \a atom in \a molgraph (see namespace MolProp::CoordinationGeometry). */
        CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /** \brief Returns the hybridization-state-dependent atomic polarizability of \a atom in \a molgraph. */
        CDPL_MOLPROP_API double getHybridPolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the effective atomic polarizability of \a atom in \a molgraph (after Kang and Jhon).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param damping The damping factor applied to remote-atom contributions.
         */
        CDPL_MOLPROP_API double calcEffectivePolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double damping = 0.75);

        /** \brief Calculates the total partial charge of \a atom (sum of stored PEOE sigma and MHMO pi charge contributions). */
        CDPL_MOLPROP_API double calcTotalPartialCharge(const Chem::Atom& atom);

        /** \brief Calculates the lone-pair electronegativity of \a atom in \a molgraph. */
        CDPL_MOLPROP_API double calcLonePairElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /** \brief Calculates the pi electronegativity of \a atom in \a molgraph. */
        CDPL_MOLPROP_API double calcPiElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the inductive effect parameter of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param num_bonds The maximum number of bonds over which to accumulate the inductive contributions.
         */
        CDPL_MOLPROP_API double calcInductiveEffect(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t num_bonds = 10);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_ATOMFUNCTIONS_HPP
