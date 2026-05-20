/* 
 * BronKerboschAlgorithm.hpp 
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
 * \brief Implementation of the Bron-Kerbosch algorithm.
 */

#ifndef CDPL_UTIL_BRONKERBOSCHALGORITHM_HPP
#define CDPL_UTIL_BRONKERBOSCHALGORITHM_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Util/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Implementation of the Bron-Kerbosch clique-detection algorithm [\ref BKA].
         */
        class CDPL_UTIL_API BronKerboschAlgorithm
        {

          public:
            /**
             * \brief Constructs the \c %BronKerboschAlgorithm instance without an associated adjacency matrix.
             */
            BronKerboschAlgorithm() {}

            /**
             * \brief Constructs the \c %BronKerboschAlgorithm instance and immediately initializes it with the adjacency matrix \a adj_mtx.
             * \param adj_mtx The graph adjacency matrix (one Util::BitSet per node).
             */
            BronKerboschAlgorithm(const BitSetArray& adj_mtx);

            /**
             * \brief Constructs a copy of the \c %BronKerboschAlgorithm instance \a bka.
             * \param bka The \c %BronKerboschAlgorithm instance to copy.
             */
            BronKerboschAlgorithm(const BronKerboschAlgorithm& bka);

            /**
             * \brief (Re-)initializes the algorithm with the adjacency matrix \a adj_mtx and resets the clique iterator.
             * \param adj_mtx The graph adjacency matrix (one Util::BitSet per node).
             */
            void init(const BitSetArray& adj_mtx);

            /**
             * \brief Advances the clique iterator and writes the next maximal clique into \a clique.
             * \param clique The output clique (set of node indices).
             * \return \c true if a clique was emitted, and \c false when the iteration is exhausted.
             */
            bool nextClique(BitSet& clique);

            /**
             * \brief Copy assignment operator.
             * \param bka The other \c %BronKerboschAlgorithm instance.
             * \return A reference to itself.
             */
            BronKerboschAlgorithm& operator=(const BronKerboschAlgorithm& bka);

          private:
            struct State
            {

                BitSet      curr;
                BitSet      pool;
                BitSet      excl;
                std::size_t u;
                std::size_t v;
            };

            typedef std::vector<std::size_t> NodeDegreeTable;
            typedef std::vector<State*>      StateStack;
            typedef Util::ObjectStack<State> StateCache;

            const BitSetArray* adjMatrix;
            StateCache         stateCache;
            NodeDegreeTable    nodeDegrees;
            StateStack         states;
            BitSet             pivotCandSet;
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_BRONKERBOSCHALGORITHM_HPP
