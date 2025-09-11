/* 
 * CIPPriorityCalculator.hpp 
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
 * \brief Definition of class CDPL::Chem::CIPPriorityCalculator.
 */

#ifndef CDPL_CHEM_CIPPRIORITYCALCULATOR_HPP
#define CDPL_CHEM_CIPPRIORITYCALCULATOR_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;

        /**
         * \brief CIPPriorityCalculator.
         * \see [\ref TCIP]
         */
        class CDPL_CHEM_API CIPPriorityCalculator
        {

          public:
            /**
             * \brief Constructs the \c %CIPPriorityCalculator instance.
             */
            CIPPriorityCalculator();

            /**
             * \brief Constructs the \c %CIPPriorityCalculator instance and calculates the topological \e CIP priorities
             *        of the atoms in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the \e CIP priorities.
             * \param priorities An array containing the calculated \e CIP priorities. The \e CIP priorities
             *         are stored in the same order as the atoms appear in the atom list of the molecular graph
             *         (i.e. the \e CIP priority of an atom is accessible via its index).
             */
            CIPPriorityCalculator(const MolecularGraph& molgraph, Util::STArray& priorities);

            CIPPriorityCalculator(const CIPPriorityCalculator&) = delete;

            CIPPriorityCalculator& operator=(const CIPPriorityCalculator&) = delete;

            /**
             * \brief Calculates the topological \e CIP priorities of the atoms in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the \e CIP priorities.
             * \param priorities An array containing the calculated \e CIP priorities. The \e CIP priorities
             *         are stored in the same order as the atoms appear in the atom list of the molecular graph
             *         (i.e. the \e CIP priority of an atom is accessible via its index).
             */
            void calculate(const MolecularGraph& molgraph, Util::STArray& priorities);

          private:
            class AtomNode;

            void init(const MolecularGraph&, Util::STArray&);
            void determinePriorities(Util::STArray&);

            AtomNode* allocNode(std::size_t p);

            typedef std::vector<AtomNode*> NodeList;

            class AtomNode
            {

              public:
                void clear();

                void addNbrNode(AtomNode*);

                void setNewPriority(std::size_t);

                void updateNbrList();
                void updatePriority();

                void setPriority(std::size_t p);

                std::size_t getPriority() const;

                struct LessCmpFunc
                {

                    bool operator()(const AtomNode*, const AtomNode*) const;
                };

                struct PriorityLessCmpFunc
                {

                    bool operator()(const AtomNode*, const AtomNode*) const;
                };

                struct PriorityGreaterCmpFunc
                {

                    bool operator()(const AtomNode*, const AtomNode*) const;
                };

              private:
                std::size_t priority;
                std::size_t newPriority;
                NodeList    nbrNodes;
            };

            typedef Util::ObjectStack<AtomNode> NodeCache;

            NodeCache nodeCache;
            NodeList  expAtomNodes;
            NodeList  atomNodes;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPPRIORITYCALCULATOR_HPP
