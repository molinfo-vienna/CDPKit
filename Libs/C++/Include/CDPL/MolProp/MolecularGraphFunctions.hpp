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
#include "CDPL/Chem/AtomPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace MolProp
    {

        CDPL_MOLPROP_API double calcMass(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API void calcMassComposition(const Chem::MolecularGraph& molgraph, MassComposition& comp);

        CDPL_MOLPROP_API void generateMassCompositionString(const Chem::MolecularGraph& molgraph, std::string& comp);

        /**
         * \brief Generates the molecular formula of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param formula A reference to the output string.
         * \param sep A string separating the output for each element (since 1.2).
         */
        CDPL_MOLPROP_API void generateMolecularFormula(const Chem::MolecularGraph& molgraph, std::string& formula, const std::string& sep = std::string());

        CDPL_MOLPROP_API void generateElementHistogram(const Chem::MolecularGraph& molgraph, ElementHistogram& hist, bool append = false);


        CDPL_MOLPROP_API std::size_t calcCyclomaticNumber(const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getAtomCount(const Chem::MolecularGraph& molgraph, unsigned int type, bool strict = true);

        CDPL_MOLPROP_API std::size_t getImplicitHydrogenCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        CDPL_MOLPROP_API std::size_t getExplicitOrdinaryHydrogenCount(const Chem::MolecularGraph& molgraph, unsigned int flags = Chem::AtomPropertyFlag::DEFAULT);

        CDPL_MOLPROP_API std::size_t getChainAtomCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getHBondAcceptorAtomCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getHBondDonorAtomCount(const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getBondCount(const Chem::MolecularGraph& molgraph, std::size_t order, bool inc_aro = true);

        CDPL_MOLPROP_API std::size_t getHydrogenBondCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getChainBondCount(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API std::size_t getRotatableBondCount(const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);

        CDPL_MOLPROP_API std::size_t getComponentCount(const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API double calcXLogP(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API double calcLogS(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API double calcTPSA(const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API std::size_t getRuleOfFiveScore(const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API double calcMeanPolarizability(const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API void calcPEOEProperties(Chem::MolecularGraph& molgraph, bool overwrite, std::size_t num_iter = 20,
                                                 double damping = 0.48);

        CDPL_MOLPROP_API void calcMHMOProperties(Chem::MolecularGraph& molgraph, bool overwrite);

        CDPL_MOLPROP_API void calcAtomHydrophobicities(Chem::MolecularGraph& molgraph, bool overwrite, bool from_logp = false);

        CDPL_MOLPROP_API void perceiveHBondDonorAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);

        CDPL_MOLPROP_API void perceiveHBondAcceptorAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_MOLECULARGRAPHFUNCTIONS_HPP
