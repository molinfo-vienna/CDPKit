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

#ifndef CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Descr/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Descr
    {

        /**
         * \brief Calculates the topological radius (minimum atom eccentricity) of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The topological radius.
         */
        CDPL_DESCR_API std::size_t calcTopologicalRadius(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the topological diameter (maximum atom-pair topological distance) of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The topological diameter.
         */
        CDPL_DESCR_API std::size_t calcTopologicalDiameter(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the ring complexity of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The calculated ring complexity.
         */
        CDPL_DESCR_API double calcRingComplexity(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the molecular complexity of \a molgraph (Hendrickson, Huang and Toczko).
         * \param molgraph The molecular graph.
         * \return The calculated molecular complexity.
         * \see [\ref MCPLX]
         */
        CDPL_DESCR_API double calcMolecularComplexity(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the first Kier shape index (\f$ \kappa_1 \f$) of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The calculated Kier shape index \f$ \kappa_1 \f$.
         */
        CDPL_DESCR_API double calcKierShape1(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the second Kier shape index (\f$ \kappa_2 \f$) of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The calculated Kier shape index \f$ \kappa_2 \f$.
         */
        CDPL_DESCR_API double calcKierShape2(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the third Kier shape index (\f$ \kappa_3 \f$) of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The calculated Kier shape index \f$ \kappa_3 \f$.
         */
        CDPL_DESCR_API double calcKierShape3(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the Wiener index of \a molgraph.
         *
         * The Wiener index is the sum of the topological distances over all pairs of heavy atoms.
         *
         * \param molgraph The molecular graph.
         * \return The Wiener index.
         */
        CDPL_DESCR_API std::size_t calcWienerIndex(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the Randic connectivity index of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The Randic index.
         */
        CDPL_DESCR_API double calcRandicIndex(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the first Zagreb index (\f$ M_1 \f$) of \a molgraph.
         *
         * \f$ M_1 \f$ is the sum of squared heavy atom degrees over all heavy atoms.
         *
         * \param molgraph The molecular graph.
         * \return The first Zagreb index.
         */
        CDPL_DESCR_API std::size_t calcZagrebIndex1(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the second Zagreb index (\f$ M_2 \f$) of \a molgraph.
         *
         * \f$ M_2 \f$ is the sum of the products of the heavy atom degrees over all heavy bonds.
         *
         * \param molgraph The molecular graph.
         * \return The second Zagreb index.
         */
        CDPL_DESCR_API std::size_t calcZagrebIndex2(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Calculates the total walk count of \a molgraph.
         * \param molgraph The molecular graph.
         * \return The total walk count.
         */
        CDPL_DESCR_API std::size_t calcTotalWalkCount(const Chem::MolecularGraph& molgraph);
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_MOLECULARGRAPHFUNCTIONS_HPP
