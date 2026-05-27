/* 
 * CIPConfigurationLabeler.hpp 
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
 * \brief Definition of class CDPL::Chem::CIPConfigurationLabeler.
 */

#ifndef CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP
#define CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
        class CIPConfigurationLabelerImpl;
        
        /**
         * \brief Assigns <em>Cahn-Ingold-Prelog (CIP)</em> configuration labels to stereogenic atoms and bonds of a molecular graph.
         *
         * After calling setup() for a molecular graph the per-atom or per-bond CIP descriptor
         * can be queried via the getLabel() overloads. The implementation
         * is largely based on John Mayfield's Java implementation of the CIP
         * sequence rules [\ref CIPJM].
         *
         * \see Chem::CIPDescriptor
         * \since 1.1
         */
        class CDPL_CHEM_API CIPConfigurationLabeler
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CIPConfigurationLabeler instances. */
            typedef std::shared_ptr<CIPConfigurationLabeler> SharedPointer;

            /**
             * \brief Constructs the \c %CIPConfigurationLabeler instance without an associated molecular graph.
             */
            CIPConfigurationLabeler();

            /**
             * \brief Constructs the \c %CIPConfigurationLabeler instance and prepares it for \a molgraph.
             * \param molgraph The molecular graph to label.
             */
            CIPConfigurationLabeler(const MolecularGraph& molgraph);

            /**
             * \brief Constructs a copy of the \c %CIPConfigurationLabeler instance \a labeler.
             * \param labeler The \c %CIPConfigurationLabeler to copy.
             */
            CIPConfigurationLabeler(const CIPConfigurationLabeler& labeler);

            /**
             * \brief Destructor.
             */
            ~CIPConfigurationLabeler();

            /**
             * \brief Prepares the labeler to assign CIP descriptors for the molecular graph \a molgraph.
             * \param molgraph The molecular graph to label.
             */
            void setup(const MolecularGraph& molgraph);

            /**
             * \brief Returns the CIP descriptor of the stereogenic atom \a atom.
             * \param atom The atom whose CIP descriptor is queried.
             * \return One of the Chem::CIPDescriptor values.
             */
            unsigned int getLabel(const Atom& atom);

            /**
             * \brief Returns the CIP descriptor of the stereogenic bond \a bond.
             * \param bond The bond whose CIP descriptor is queried.
             * \return One of the Chem::CIPDescriptor values.
             */
            unsigned int getLabel(const Bond& bond);

            /**
             * \brief Replaces the state of this labeler by a copy of the state of \a labeler.
             * \param labeler The source \c %CIPConfigurationLabeler.
             * \return A reference to itself.
             */
            CIPConfigurationLabeler& operator=(const CIPConfigurationLabeler& labeler);
            
          private:
            typedef std::unique_ptr<CIPConfigurationLabelerImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP
