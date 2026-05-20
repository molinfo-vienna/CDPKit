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

        /**
         * \brief Returns the value of the MolProp::AtomProperty::HYDROPHOBICITY property of \a atom.
         * \param atom The atom.
         * \return The hydrophobicity value.
         */
        CDPL_MOLPROP_API double getHydrophobicity(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::HYDROPHOBICITY property of \a atom to \a hyd.
         * \param atom The atom.
         * \param hyd The new hydrophobicity value.
         */
        CDPL_MOLPROP_API void setHydrophobicity(Chem::Atom& atom, double hyd);

        /**
         * \brief Removes the MolProp::AtomProperty::HYDROPHOBICITY property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearHydrophobicity(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::HYDROPHOBICITY property.
         * \param atom The atom.
         * \return \c true if the hydrophobicity property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasHydrophobicity(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property of \a atom.
         * \param atom The atom.
         * \return The PEOE sigma charge value.
         */
        CDPL_MOLPROP_API double getPEOESigmaCharge(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property of \a atom to \a charge.
         * \param atom The atom.
         * \param charge The new PEOE sigma charge value.
         */
        CDPL_MOLPROP_API void setPEOESigmaCharge(Chem::Atom& atom, double charge);

        /**
         * \brief Removes the MolProp::AtomProperty::PEOE_SIGMA_CHARGE property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearPEOESigmaCharge(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::PEOE_SIGMA_CHARGE property.
         * \param atom The atom.
         * \return \c true if the PEOE sigma charge property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasPEOESigmaCharge(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property of \a atom.
         * \param atom The atom.
         * \return The PEOE sigma electronegativity value.
         */
        CDPL_MOLPROP_API double getPEOESigmaElectronegativity(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property of \a atom to \a e_neg.
         * \param atom The atom.
         * \param e_neg The new PEOE sigma electronegativity value.
         */
        CDPL_MOLPROP_API void setPEOESigmaElectronegativity(Chem::Atom& atom, double e_neg);

        /**
         * \brief Removes the MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearPEOESigmaElectronegativity(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::PEOE_SIGMA_ELECTRONEGATIVITY property.
         * \param atom The atom.
         * \return \c true if the PEOE sigma electronegativity property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasPEOESigmaElectronegativity(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the MolProp::AtomProperty::MHMO_PI_CHARGE property of \a atom.
         * \param atom The atom.
         * \return The MHMO pi charge value.
         */
        CDPL_MOLPROP_API double getMHMOPiCharge(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::MHMO_PI_CHARGE property of \a atom to \a charge.
         * \param atom The atom.
         * \param charge The new MHMO pi charge value.
         */
        CDPL_MOLPROP_API void setMHMOPiCharge(Chem::Atom& atom, double charge);

        /**
         * \brief Removes the MolProp::AtomProperty::MHMO_PI_CHARGE property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearMHMOPiCharge(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::MHMO_PI_CHARGE property.
         * \param atom The atom.
         * \return \c true if the MHMO pi charge property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasMHMOPiCharge(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the MolProp::AtomProperty::H_BOND_DONOR_TYPE property of \a atom (see namespace MolProp::HBondDonorAtomType).
         * \param atom The atom.
         * \return The H-bond donor type identifier.
         */
        CDPL_MOLPROP_API unsigned int getHBondDonorType(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::H_BOND_DONOR_TYPE property of \a atom to \a type.
         * \param atom The atom.
         * \param type The new MolProp::HBondDonorAtomType identifier.
         */
        CDPL_MOLPROP_API void setHBondDonorType(Chem::Atom& atom, unsigned int type);

        /**
         * \brief Removes the MolProp::AtomProperty::H_BOND_DONOR_TYPE property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearHBondDonorType(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::H_BOND_DONOR_TYPE property.
         * \param atom The atom.
         * \return \c true if the H-bond donor type property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasHBondDonorType(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property of \a atom (see namespace MolProp::HBondAcceptorAtomType).
         * \param atom The atom.
         * \return The H-bond acceptor type identifier.
         */
        CDPL_MOLPROP_API unsigned int getHBondAcceptorType(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property of \a atom to \a type.
         * \param atom The atom.
         * \param type The new MolProp::HBondAcceptorAtomType identifier.
         */
        CDPL_MOLPROP_API void setHBondAcceptorType(Chem::Atom& atom, unsigned int type);

        /**
         * \brief Removes the MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property from \a atom.
         * \param atom The atom.
         */
        CDPL_MOLPROP_API void clearHBondAcceptorType(Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom carries an explicit MolProp::AtomProperty::H_BOND_ACCEPTOR_TYPE property.
         * \param atom The atom.
         * \return \c true if the H-bond acceptor type property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasHBondAcceptorType(const Chem::Atom& atom);


        /**
         * \brief Tells whether \a atom is a member of any ring in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is in a ring, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isInRing(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a member of a ring of size \a size in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param size The ring size to test for.
         * \return \c true if \a atom is in a ring of size \a size, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isInRingOfSize(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t size);

        /**
         * \brief Returns the number of SSSR rings of \a molgraph that contain \a atom.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The number of containing SSSR rings.
         */
        CDPL_MOLPROP_API std::size_t getNumContainingSSSRRings(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the standard atomic weight of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The standard atomic weight.
         */
        CDPL_MOLPROP_API double getAtomicWeight(const Chem::Atom& atom);

        /**
         * \brief Returns the IUPAC group number of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The IUPAC group number.
         */
        CDPL_MOLPROP_API std::size_t getIUPACGroup(const Chem::Atom& atom);

        /**
         * \brief Returns the period of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The element period.
         */
        CDPL_MOLPROP_API std::size_t getPeriod(const Chem::Atom& atom);

        /**
         * \brief Returns the van der Waals radius of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The van der Waals radius.
         */
        CDPL_MOLPROP_API double getVdWRadius(const Chem::Atom& atom);

        /**
         * \brief Returns the covalent radius of the chemical element associated with \a atom for the given bond order.
         * \param atom The atom.
         * \param order The bond order.
         * \return The covalent radius.
         */
        CDPL_MOLPROP_API double getCovalentRadius(const Chem::Atom& atom, std::size_t order);

        /**
         * \brief Returns the Allred-Rochow electronegativity of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The Allred-Rochow electronegativity.
         */
        CDPL_MOLPROP_API double getAllredRochowElectronegativity(const Chem::Atom& atom);

        /**
         * \brief Returns the element name of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return A \c const reference to the element name.
         */
        CDPL_MOLPROP_API const std::string& getElementName(const Chem::Atom& atom);

        /**
         * \brief Returns the number of valence electrons of the chemical element associated with \a atom.
         * \param atom The atom.
         * \return The number of valence electrons.
         */
        CDPL_MOLPROP_API std::size_t getElementValenceElectronCount(const Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom represents a chemical element.
         * \param atom The atom.
         * \return \c true if \a atom represents a chemical element, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isChemicalElement(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a main-group element.
         * \param atom The atom.
         * \return \c true if the element is a main-group element, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isMainGroupElement(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a metal.
         * \param atom The atom.
         * \return \c true if the element is a metal, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isMetal(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a transition metal.
         * \param atom The atom.
         * \return \c true if the element is a transition metal, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isTransitionMetal(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a non-metal.
         * \param atom The atom.
         * \return \c true if the element is a non-metal, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isNonMetal(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a semi-metal.
         * \param atom The atom.
         * \return \c true if the element is a semi-metal, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isSemiMetal(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a halogen.
         * \param atom The atom.
         * \return \c true if the element is a halogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHalogen(const Chem::Atom& atom);

        /**
         * \brief Tells whether the chemical element associated with \a atom is a noble gas.
         * \param atom The atom.
         * \return \c true if the element is a noble gas, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isNobleGas(const Chem::Atom& atom);


        /**
         * \brief Tells whether \a atom is an \e ordinary hydrogen.
         *
         * An "ordinary" hydrogen is a hydrogen atom that has the default values for every atom property
         * named by the \a flags bitmask (e.g. with the Chem::AtomPropertyFlag::ISOTOPE flag set, only
         * unspecified-isotope hydrogens count as ordinary; with Chem::AtomPropertyFlag::FORMAL_CHARGE set,
         * only neutral hydrogens count as ordinary; etc.). All other hydrogens are deemed special.
         *
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that qualify "ordinary"; an empty bitmask makes any hydrogen ordinary.
         * \return \c true if \a atom is an ordinary hydrogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isOrdinaryHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                 unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /**
         * \brief Tells whether \a atom is a heavy (non-hydrogen) atom.
         * \param atom The atom.
         * \return \c true if \a atom is a heavy atom, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHeavy(const Chem::Atom& atom);

        /**
         * \brief Tells whether \a atom is unsaturated (involved in at least one multiple bond) in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is unsaturated, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isUnsaturated(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom acts as an H-bond acceptor in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is an H-bond acceptor, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHBondAcceptor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom acts as an H-bond donor in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is an H-bond donor, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHBondDonor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a carbonyl-like center in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon centers are recognized.
         * \param db_o_only If \c true, a double bond to oxygen must be present. Otherwise, a double bond to sulfur is also allowed.
         * \return \c true if \a atom is a carbonyl-like center, and \c false otherwise.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isCarbonylLike(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /**
         * \brief Tells whether \a atom is the center of an amide group in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon amides are recognized.
         * \param db_o_only If \c true, a double bond to oxygen must be present. Otherwise, a double bond to sulfur is also allowed.
         * \return \c true if \a atom is an amide center, and \c false otherwise.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isAmideCenter(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /**
         * \brief Tells whether \a atom is the nitrogen of an amide group in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param c_only If \c true, only carbon amides are recognized.
         * \param db_o_only If \c true, the center atom must be double bonded to oxygen. Otherwise, a double bond to sulfur is also allowed. 
         * \return \c true if \a atom is an amide nitrogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isAmideNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);

        /**
         * \brief Tells whether \a atom is an invertible (pyramidal, non-aromatic, non-amide) nitrogen in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is an invertible nitrogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a planar nitrogen in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is a planar nitrogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isPlanarNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a atom is a bridgehead atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param bridged_only If \c true, only bridgeheads of bridged (non-fused) ring systems are recognized.
         * \return \c true if \a atom is a bridgehead, and \c false otherwise.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isBridgehead(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool bridged_only);

        /**
         * \brief Tells whether \a atom is a spiro center in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return \c true if \a atom is a spiro center, and \c false otherwise.
         * \since 1.2
         */
        CDPL_MOLPROP_API bool isSpiroCenter(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
        
        
        /**
         * \brief Returns the number of ordinary-hydrogen neighbors of \a atom in \a molgraph (see isOrdinaryHydrogen() for the definition of "ordinary").
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that qualify "ordinary".
         * \return The ordinary-hydrogen neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getOrdinaryHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                              unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /**
         * \brief Returns the number of explicit neighbors of \a atom in \a molgraph whose Chem::AtomType matches \a type.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param type The Chem::AtomType to count.
         * \param strict If \c true, the atom type must match \a type exactly; otherwise generic types match via Chem::atomTypesMatch().
         * \return The matching explicit-atom neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        /**
         * \brief Returns the number of neighbors of \a atom in \a molgraph (including implicit hydrogens) whose Chem::AtomType matches \a type.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param type The Chem::AtomType to count.
         * \param strict If \c true, the atom type must match \a type exactly; otherwise generic types match via Chem::atomTypesMatch().
         * \return The matching neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        /**
         * \brief Returns the number of explicit chain (non-ring) neighbors of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The explicit chain-atom neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getExplicitChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of chain (non-ring) neighbors of \a atom in \a molgraph (including implicit hydrogens).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The chain-atom neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getChainAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of ring-atom neighbors of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The ring-atom neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getRingAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of aromatic neighbors of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The aromatic neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getAromaticAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of heavy-atom neighbors of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The heavy-atom neighbor count.
         */
        CDPL_MOLPROP_API std::size_t getHeavyAtomCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the number of explicit bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The explicit-bond count.
         */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of explicit bonds of the given order incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param order The bond order to count.
         * \return The number of matching explicit bonds.
         */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

        /**
         * \brief Returns the number of explicit bonds of the given order incident to \a atom that bond to atoms whose Chem::AtomType matches \a type.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param order The bond order to count.
         * \param type The Chem::AtomType of the bonded partner.
         * \param strict If \c true, the atom type must match \a type exactly; otherwise generic types match via Chem::atomTypesMatch().
         * \return The number of matching explicit bonds.
         */
        CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

        /**
         * \brief Returns the total number of bonds incident to \a atom in \a molgraph (including implicit-hydrogen bonds).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The total bond count.
         */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the total number of bonds of the given order incident to \a atom (including implicit-hydrogen bonds).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param order The bond order to count.
         * \return The number of matching bonds.
         */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order);

        /**
         * \brief Returns the total number of bonds of the given order incident to \a atom that bond to atoms whose Chem::AtomType matches \a type.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param order The bond order to count.
         * \param type The Chem::AtomType of the bonded partner.
         * \param strict If \c true, the atom type must match \a type exactly; otherwise generic types match via Chem::atomTypesMatch().
         * \return The number of matching bonds.
         */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t order, unsigned int type, bool strict = true);

        /**
         * \brief Returns the number of explicit chain (non-ring) bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The explicit chain-bond count.
         */
        CDPL_MOLPROP_API std::size_t getExplicitChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of chain (non-ring) bonds incident to \a atom in \a molgraph (including implicit-hydrogen bonds).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The chain-bond count.
         */
        CDPL_MOLPROP_API std::size_t getChainBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of ring bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The ring-bond count.
         */
        CDPL_MOLPROP_API std::size_t getRingBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of aromatic bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The aromatic-bond count.
         */
        CDPL_MOLPROP_API std::size_t getAromaticBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of heavy-atom bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The heavy-atom bond count.
         */
        CDPL_MOLPROP_API std::size_t getHeavyBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of rotatable bonds incident to \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param h_rotors If \c true, hydrogen-only rotors are counted as rotatable.
         * \param ring_bonds If \c true, ring bonds are also considered.
         * \param amide_bonds If \c true, amide bonds are also considered.
         * \return The rotatable-bond count.
         */
        CDPL_MOLPROP_API std::size_t getRotatableBondCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);


        /**
         * \brief Calculates the explicit valence of \a atom in \a molgraph (sum of explicit bond orders).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The explicit valence.
         */
        CDPL_MOLPROP_API std::size_t calcExplicitValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the total valence of \a atom in \a molgraph (explicit valence plus implicit hydrogens).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The total valence.
         */
        CDPL_MOLPROP_API std::size_t calcValence(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /**
         * \brief Calculates the number of free (lone-pair) valence electrons of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The number of free valence electrons.
         */
        CDPL_MOLPROP_API std::size_t calcFreeValenceElectronCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the number of valence electrons of the chemical element associated with \a atom (corrected for the atom's formal charge).
         * \param atom The atom.
         * \return The valence-electron count.
         */
        CDPL_MOLPROP_API std::size_t calcValenceElectronCount(const Chem::Atom& atom);


        /**
         * \brief Calculates the steric number of \a atom in \a molgraph (used by VSEPR theory).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The steric number.
         */
        CDPL_MOLPROP_API std::size_t calcStericNumber(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the VSEPR coordination geometry of \a atom in \a molgraph (see namespace MolProp::CoordinationGeometry).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param steric_num The pre-computed steric number of \a atom (avoids re-computation).
         * \return The MolProp::CoordinationGeometry identifier.
         */
        CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t steric_num);

        /**
         * \brief Returns the VSEPR coordination geometry of \a atom in \a molgraph (see namespace MolProp::CoordinationGeometry).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The MolProp::CoordinationGeometry identifier.
         */
        CDPL_MOLPROP_API unsigned int getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the hybridization-state-dependent atomic polarizability of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The hybrid polarizability.
         */
        CDPL_MOLPROP_API double getHybridPolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the effective atomic polarizability of \a atom in \a molgraph (after Kang and Jhon).
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param damping The damping factor applied to remote-atom contributions.
         * \return The effective polarizability.
         */
        CDPL_MOLPROP_API double calcEffectivePolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double damping = 0.75);

        /**
         * \brief Calculates the total partial charge of \a atom (sum of stored PEOE sigma and MHMO pi charge contributions).
         * \param atom The atom.
         * \return The total partial charge.
         */
        CDPL_MOLPROP_API double calcTotalPartialCharge(const Chem::Atom& atom);

        /**
         * \brief Calculates the lone-pair electronegativity of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The lone-pair electronegativity.
         */
        CDPL_MOLPROP_API double calcLonePairElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the pi electronegativity of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \return The pi electronegativity.
         */
        CDPL_MOLPROP_API double calcPiElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the inductive effect parameter of \a atom in \a molgraph.
         * \param atom The atom.
         * \param molgraph The molecular graph.
         * \param num_bonds The maximum number of bonds over which to accumulate the inductive contributions.
         * \return The inductive effect value.
         */
        CDPL_MOLPROP_API double calcInductiveEffect(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t num_bonds = 10);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_ATOMFUNCTIONS_HPP
