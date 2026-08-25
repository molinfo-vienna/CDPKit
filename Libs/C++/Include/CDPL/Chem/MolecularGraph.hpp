/* 
 * MolecularGraph.hpp 
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
 * \brief Definition of class CDPL::Chem::MolecularGraph.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPH_HPP
#define CDPL_CHEM_MOLECULARGRAPH_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Abstract base class for data structures that represent chemical structures as molecular graphs.
         *
         * Vertices (= atoms) of the molecular graph are represented by Chem::Atom instances and edges (= bonds)
         * by Chem::Bond instances. Read-only access to the Chem::Atom and Chem::Bond objects is enabled by
         * corresponding methods inherited from Chem::AtomContainer and Chem::BondContainer, respectively.
         * Molecular graph properties can be stored/retrieved via methods provided by the Base::PropertyContainer
         * base class.
         * Deep copies of the molecular graph are created by the pure virtual clone() method which needs to
         * be implemented by concrete subclasses (e.g. Chem::BasicMolecule, Chem::Fragment) of \c %MolecularGraph.
         */
        class CDPL_CHEM_API MolecularGraph : public AtomContainer,
                                             public BondContainer,
                                             public Base::PropertyContainer
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MolecularGraph instances.
             */
            typedef std::shared_ptr<MolecularGraph> SharedPointer;

            /**
             * \brief Virtual destructor.
             */
            virtual ~MolecularGraph() {}

            /**
             * \brief Creates a deep copy of the molecular graph.
             * \return A smart pointer to the copy of the molecular graph.
             */
            virtual SharedPointer clone() const = 0;

          protected:
            /**
             * \brief Assignment operator.
             * \param molgraph The other \c %MolecularGraph instance to copy.
             * \return A reference to itself.
             */
            MolecularGraph& operator=(const MolecularGraph& molgraph);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPH_HPP
