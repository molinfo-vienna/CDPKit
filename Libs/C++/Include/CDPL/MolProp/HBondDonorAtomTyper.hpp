/* 
 * HBondDonorAtomTyper.hpp 
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
 * \brief Definition of class CDPL::MolProp::HBondDonorAtomTyper.
 */

#ifndef CDPL_MOLPROP_HBONDDONORATOMTYPER_HPP
#define CDPL_MOLPROP_HBONDDONORATOMTYPER_HPP

#include <memory>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Perception of H-bond donor atom types (see namespace MolProp::HBondDonorAtomType) by SMARTS pattern matching.
         */
        class CDPL_MOLPROP_API HBondDonorAtomTyper
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %HBondDonorAtomTyper instances. */
            typedef std::shared_ptr<HBondDonorAtomTyper> SharedPointer;

            /** \brief Constructs the \c %HBondDonorAtomTyper instance. */
            HBondDonorAtomTyper();

            /**
             * \brief Constructs the \c %HBondDonorAtomTyper instance and perceives the H-bond donor types of the atoms in \a molgraph.
             * \param molgraph The molecular graph.
             * \param types The output array storing the perceived H-bond donor types (indexed by atom index).
             */
            HBondDonorAtomTyper(const Chem::MolecularGraph& molgraph, Util::UIArray& types);

            /**
             * \brief Perceives the H-bond donor types of the atoms in \a molgraph.
             * \param molgraph The molecular graph.
             * \param types The output array storing the perceived H-bond donor types (indexed by atom index).
             */
            void perceiveTypes(const Chem::MolecularGraph& molgraph, Util::UIArray& types);

          private:
            Chem::PatternAtomTyper atomTyper;
        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_HBONDDONORATOMTYPER_HPP
