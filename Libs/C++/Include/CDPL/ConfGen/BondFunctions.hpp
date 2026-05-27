/* 
 * BondFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Bond instances.
 */

#ifndef CDPL_CONFGEN_BONDFUNCTIONS_HPP
#define CDPL_CONFGEN_BONDFUNCTIONS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Bond;
        class MolecularGraph;
    } // namespace Chem

    namespace ConfGen
    {

        /**
         * \brief Tells whether \a bond is a link bond between two fragments under the fragment-based conformer generation heuristics.
         * \param bond The bond to test.
         * \param molgraph The parent molecular graph.
         * \return \c true if \a bond connects two fragments, and \c false otherwise.
         */
        CDPL_CONFGEN_API bool isFragmentLinkBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a bond is rotatable under the conformer generation rotatable bond heuristics.
         * \param bond The bond to test.
         * \param molgraph The parent molecular graph.
         * \param het_h_rotors If \c true, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
         * \return \c true if \a bond is rotatable, and \c false otherwise.
         */
        CDPL_CONFGEN_API bool isRotatableBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool het_h_rotors);
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_BONDFUNCTIONS_HPP
