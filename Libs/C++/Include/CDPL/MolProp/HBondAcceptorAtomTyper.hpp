/* 
 * HBondAcceptorAtomTyper.hpp 
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
 * \brief Definition of class CDPL::MolProp::HBondAcceptorAtomTyper.
 */

#ifndef CDPL_MOLPROP_HBONDACCEPTORATOMTYPER_HPP
#define CDPL_MOLPROP_HBONDACCEPTORATOMTYPER_HPP

#include <memory>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Implements the perception of H-bond acceptor atom types (see namespace MolProp::HBondAcceptorAtomType).
         */
        class CDPL_MOLPROP_API HBondAcceptorAtomTyper
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %HBondAcceptorAtomTyper instances. */
            typedef std::shared_ptr<HBondAcceptorAtomTyper> SharedPointer;

            /** \brief Constructs the \c %HBondAcceptorAtomTyper instance. */
            HBondAcceptorAtomTyper();

            /**
             * \brief Constructs the \c %HBondAcceptorAtomTyper instance and perceives the H-bond acceptor types of the atoms in \a molgraph.
             * \param molgraph The molecular graph.
             * \param types The output array storing the perceived H-bond acceptor types (indexed by atom index).
             */
            HBondAcceptorAtomTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types);

            /**
             * \brief Perceives the H-bond acceptor types of the atoms in \a molgraph.
             * \param molgraph The molecular graph.
             * \param types The output array storing the perceived H-bond acceptor types (indexed by atom index).
             */
            void perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types);

          private:
            Chem::PatternAtomTyper atomTyper;
        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_HBONDACCEPTORATOMTYPER_HPP
