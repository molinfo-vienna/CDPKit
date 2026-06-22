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

#ifndef CDPL_MOLPROP_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_MOLPROP_MOLECULARGRAPHFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/MolProp/MassComposition.hpp"
#include "CDPL/MolProp/ElementHistogram.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace MolProp
    {

        /**
         * \brief Calculates the total molecular mass of the molecular graph \a molgraph (sum of atom standard atomic weights including implicit hydrogens).
         * \param molgraph The molecular graph.
         * \return The molecular mass.
         */
        CDPL_MOLPROP_API double calcMass(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the per-element mass composition of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param comp The output mass composition.
         */
        CDPL_MOLPROP_API void calcMassComposition(const Chem::MolecularGraph& molgraph, MassComposition& comp);

        /**
         * \brief Generates a string representation of the per-element mass composition of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param comp The output mass composition string.
         */
        CDPL_MOLPROP_API void generateMassCompositionString(const Chem::MolecularGraph& molgraph, std::string& comp);

        /**
         * \brief Generates the molecular formula of the molecular graph the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param formula A reference to the output string.
         * \param sep A string separating the output for each element (since 1.2).
         */
        CDPL_MOLPROP_API void generateMolecularFormula(const Chem::MolecularGraph& molgraph, std::string& formula, const std::string& sep = std::string());

        /**
         * \brief Generates the element histogram of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param hist The output element histogram.
         * \param append If \c true, \a hist is appended to instead of cleared first.
         */
        CDPL_MOLPROP_API void generateElementHistogram(const Chem::MolecularGraph& molgraph, ElementHistogram& hist, bool append = false);


        /**
         * \brief Calculates the cyclomatic number of the molecular graph \a molgraph (number of independent cycles).
         * \param molgraph The molecular graph.
         * \return The cyclomatic number.
         */
        CDPL_MOLPROP_API std::size_t calcCyclomaticNumber(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the total number of atoms in the molecular graph \a molgraph (including implicit hydrogens).
         * \param molgraph The molecular graph.
         * \return The total atom count.
         */
        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of atoms in the molecular graph \a molgraph whose type property matches \a type.
         * \param molgraph The molecular graph.
         * \param type The atom type to count (see namespace Chem::AtomType).
         * \param strict If \c true, the atom type must match \a type exactly. Otherwise, generic types match via Chem::atomTypesMatch().
         * \return The number of matching atoms (including implicit hydrogens when \a type matches Chem::AtomType::H).
         * \since 1.1
         */
        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        /**
         * \brief Returns the total number of implicit hydrogens in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The implicit hydrogen count.
         */
        CDPL_MOLPROP_API std::size_t getImplicitHydrogenCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of ordinary hydrogens in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that qualify "ordinary". An empty bitmask makes any hydrogen ordinary.
         * \return The ordinary hydrogen count.
         * \see MolProp::isOrdinaryHydrogen() for the definition of "ordinary".
         */
        CDPL_MOLPROP_API std::size_t getOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /**
         * \brief Returns the number of explicit ordinary hydrogens in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param flags Bitmask of Chem::AtomPropertyFlag values that qualify "ordinary". An empty bitmask makes any hydrogen ordinary.
         * \return The explicit ordinary hydrogen count.
         * \see MolProp::isOrdinaryHydrogen() for the definition of "ordinary".
         */
        CDPL_MOLPROP_API std::size_t getExplicitOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        /**
         * \brief Returns the number of chain (non-ring) atoms in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The chain-atom count.
         */
        CDPL_MOLPROP_API std::size_t getChainAtomCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of H-bond acceptor atoms in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The H-bond acceptor count.
         */
        CDPL_MOLPROP_API std::size_t getHBondAcceptorAtomCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of H-bond donor atoms in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The H-bond donor count.
         */
        CDPL_MOLPROP_API std::size_t getHBondDonorAtomCount(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the total number of bonds in the molecular graph \a molgraph (including bonds to implicit hydrogens).
         * \param molgraph The molecular graph.
         * \return The total bond count.
         */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of bonds in the molecular graph \a molgraph with the given order, optionally including aromatic bonds.
         * \param molgraph The molecular graph.
         * \param order The bond order to count.
         * \param inc_aro If \c true, aromatic bonds are counted in addition to bonds of the given order.
         * \return The number of matching bonds.
         */
        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::MolecularGraph& molgraph, std::size_t order, bool inc_aro = true);

        /**
         * \brief Returns the number of bonds in the molecular graph \a molgraph that involve at least one hydrogen atom.
         * \param molgraph The molecular graph.
         * \return The hydrogen-bond count.
         */
        CDPL_MOLPROP_API std::size_t getHydrogenBondCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of chain (non-ring) bonds in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The chain-bond count.
         */
        CDPL_MOLPROP_API std::size_t getChainBondCount(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Returns the number of rotatable bonds in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param h_rotors If \c true, hydrogen-only rotors are counted.
         * \param ring_bonds If \c true, ring bonds are also considered.
         * \param amide_bonds If \c true, amide bonds are also considered.
         * \return The rotatable-bond count.
         */
        CDPL_MOLPROP_API std::size_t getRotatableBondCount(const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);

        /**
         * \brief Returns the number of connected components in the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The component count.
         */
        CDPL_MOLPROP_API std::size_t getComponentCount(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Calculates the \f$ \log P \f$ value of the molecular graph \a molgraph using MolProp::XLogPCalculator.
         * \param molgraph The molecular graph.
         * \return The \f$ \log P \f$ value.
         * \see [\ref XLOGP]
         */
        CDPL_MOLPROP_API double calcXLogP(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the \f$ \log S \f$ (aqueous solubility) of the molecular graph \a molgraph using MolProp::LogSCalculator.
         * \param molgraph The molecular graph.
         * \return The \f$ \log S \f$ value.
         * \see [\ref LOGS]
         */
        CDPL_MOLPROP_API double calcLogS(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the topological polar surface area (TPSA) of the molecular graph \a molgraph using MolProp::TPSACalculator.
         * \param molgraph The molecular graph.
         * \return The TPSA value.
         * \see [\ref TPSA]
         */
        CDPL_MOLPROP_API double calcTPSA(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Returns the Lipinski rule-of-five score of the molecular graph \a molgraph, defined as the number of satisfied criteria (0-4).
         *
         * The four criteria evaluated are:
         *   - the number of H-bond donor atoms is &le; 5,
         *   - the number of H-bond acceptor atoms is &le; 10,
         *   - the \e XLogP value is &le; 5.0,
         *   - the molecular mass is &le; 500.0.
         *
         * A score of 4 indicates full compliance with the Lipinski rule of five.
         *
         * \param molgraph The molecular graph.
         * \return The rule-of-five score (0-4).
         */
        CDPL_MOLPROP_API std::size_t getRuleOfFiveScore(const Chem::MolecularGraph& molgraph);


        /**
         * \brief Calculates the mean atomic polarizability of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The mean atomic polarizability.
         */
        CDPL_MOLPROP_API double calcMeanPolarizability(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates PEOE &sigma;-charges and electronegativities for the atoms of the molecular graph \a molgraph and stores them as atom properties.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, existing atom properties are overwritten.
         * \param num_iter The number of charge-shifting iterations.
         * \param damping The per-iteration damping factor.
         */
        CDPL_MOLPROP_API void calcPEOEProperties(Chem::MolecularGraph& molgraph, bool overwrite, std::size_t num_iter = 20,
                                                 double damping = 0.48);

        /**
         * \brief Calculates MHMO &pi;-charges and &pi;-bond orders for the molecular graph \a molgraph and stores them as atom/bond properties.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, existing atom/bond properties are overwritten.
         */
        CDPL_MOLPROP_API void calcMHMOProperties(Chem::MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Calculates per-atom hydrophobicities for the molecular graph \a molgraph and stores them as atom properties.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, existing atom hydrophobicity properties are overwritten.
         * \param from_logp If \c true, the hydrophobicities are derived from the \e XLogP atom
         *                  contributions [\ref XLOGP] instead of the Greene algorithm [\ref CATA].
         */
        CDPL_MOLPROP_API void calcAtomHydrophobicities(Chem::MolecularGraph& molgraph, bool overwrite, bool from_logp = false);

        /**
         * \brief Perceives the H-bond donor types of the atoms in the molecular graph \a molgraph and stores them as atom properties.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, existing atom H-bond donor type properties are overwritten.
         */
        CDPL_MOLPROP_API void perceiveHBondDonorAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives the H-bond acceptor types of the atoms in the molecular graph \a molgraph and stores them as atom properties.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, existing atom H-bond acceptor type properties are overwritten.
         */
        CDPL_MOLPROP_API void perceiveHBondAcceptorAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Returns the value of the MolProp::MolecularGraphProperty::FUNCTIONAL_GROUPS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return A \c const shared pointer to the functional group list.
         * \since 1.3
         */
        CDPL_MOLPROP_API const Chem::FragmentList::SharedPointer& getFunctionalGroups(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the MolProp::MolecularGraphProperty::FUNCTIONAL_GROUPS property of the molecular graph \a molgraph to \a fg_list.
         * \param molgraph The molecular graph for which to set the property value.
         * \param fg_list The new functional group list.
         * \since 1.3
         */
        CDPL_MOLPROP_API void setFunctionalGroups(Chem::MolecularGraph& molgraph, const Chem::FragmentList::SharedPointer& fg_list);

        /**
         * \brief Clears the value of the MolProp::MolecularGraphProperty::FUNCTIONAL_GROUPS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         * \since 1.3
         */
        CDPL_MOLPROP_API void clearFunctionalGroups(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether the MolProp::MolecularGraphProperty::FUNCTIONAL_GROUPS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         * \since 1.3
         */
        CDPL_MOLPROP_API bool hasFunctionalGroups(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Perceives the functional groups of the molecular graph \a molgraph using MolProp::FunctionalGroupList.
         * \param molgraph The molecular graph.
         * \return A shared pointer to the perceived functional group list.
         * \since 1.3
         */
        CDPL_MOLPROP_API Chem::FragmentList::SharedPointer perceiveFunctionalGroups(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Perceives the functional groups of the molecular graph \a molgraph and stores them as a property.
         * \param molgraph The molecular graph (modified in place).
         * \param overwrite If \c true, an existing MolProp::MolecularGraphProperty::FUNCTIONAL_GROUPS property is overwritten.
         * \return A shared pointer to the perceived functional group list.
         * \since 1.3
         */
        CDPL_MOLPROP_API Chem::FragmentList::SharedPointer perceiveFunctionalGroups(Chem::MolecularGraph& molgraph, bool overwrite);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_MOLECULARGRAPHFUNCTIONS_HPP
