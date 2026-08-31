/* 
 * MultiConfMoleculeInputProcessor.hpp 
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
 * \brief Definition of class CDPL::Chem::MultiConfMoleculeInputProcessor.
 */

#ifndef CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP
#define CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;

        /**
         * \brief Abstract base for classes that detect and assemble multi-conformer molecules from a
         *        stream of successive single-conformer input molecules.
         */
        class CDPL_CHEM_API MultiConfMoleculeInputProcessor
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated 
             *        \c %MultiConfMoleculeInputProcessor instances.
             */
            typedef std::shared_ptr<MultiConfMoleculeInputProcessor> SharedPointer;

            /**
             * \brief Virtual destructor.
             *
             * Destroys the \c %MultiConfMoleculeInputProcessor instance and frees all allocated resources.
             */
            virtual ~MultiConfMoleculeInputProcessor() {}

            /**
             * \brief Performs initial tests and setup tasks for \a tgt_molgraph as the new conformer collection target.
             * \param tgt_molgraph The molecular graph that will store the read conformers.
             * \return \c true if \a tgt_molgraph fulfills all prerequisites and was successfully initialized, and \c false otherwise.
             */
            virtual bool init(MolecularGraph& tgt_molgraph) const = 0;

            /**
             * \brief Tells whether \a conf_molgraph is a conformer of the conformer collection target \a tgt_molgraph.
             * \param tgt_molgraph The conformer collection target.
             * \param conf_molgraph The molecular graph representing the conformer to check.
             * \return \c true if \a conf_molgraph could be identified as a conformer of tgt_molgraph, and \c false otherwise.
             */
            virtual bool isConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const = 0;

            /**
             * \brief Adds the set of atom 3D coordinates of \a conf_molgraph as a new conformer to \a tgt_molgraph.
             * \param tgt_molgraph The conformer collection target.
             * \param conf_molgraph The molecular graph representing the conformer to add.
             * \return \c true if the conformer was added, and \c false if the addition failed.
             */
            virtual bool addConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const = 0;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP
