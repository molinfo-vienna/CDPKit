/* 
 * ComponentSet.hpp 
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
 * \brief Definition of the class CDPL::Chem::ComponentSet.
 */

#ifndef CDPL_CHEM_COMPONENTSET_HPP
#define CDPL_CHEM_COMPONENTSET_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Implements the perception of molecular graph components.
         */
        class CDPL_CHEM_API ComponentSet : public FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ComponentSet instances.
             */
            typedef std::shared_ptr<ComponentSet> SharedPointer;

            /**
             * \brief Constructs an empty \c %ComponentSet instance.
             */
            ComponentSet() {}

            /**
             * \brief Constructs a \c %ComponentSet instance that contains the componenents of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the components.
             */
            ComponentSet(const MolecularGraph& molgraph);

            /**
             * \brief Replaces the current set of components by the components of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the components.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            void visitAtom(const Atom&, Fragment&);

            const char* getClassName() const
            {
                return "ComponentSet";
            }

            const MolecularGraph* molGraph;
            Util::BitSet          visAtomMask;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_COMPONENTSET_HPP
