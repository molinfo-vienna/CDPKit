/* 
 * MoleculeFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Molecule instances.
 */

#ifndef CDPL_PHARM_MOLECULEFUNCTIONS_HPP
#define CDPL_PHARM_MOLECULEFUNCTIONS_HPP

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Pharm
    {

        /**
         * \brief Prepares the molecule \a mol for downstream pharmacophore generation..
         *
         * The molecule gets prepared by completing its hydrogens, perceiving the
         * SSSR, ring flags, implicit H counts, hybridization states and aromaticity, generating 3D coordinates
         * for newly added hydrogens and (optionally) calculating per-atom hydrophobicities.
         * Failures of the hydrogen 3D-coordinate or residue sequence info derivation steps are silently caught and
         * ignored. All other exceptions propagate.
         *
         * \param mol The molecule to prepare (modified in place).
         * \param calc_hyd If \c true, atom hydrophobicities are also calculated and stored as atom properties.
         * \param from_logp If \c true and \a calc_hyd is set, the hydrophobicities are derived from the \e XLogP [\ref XLOGP] atom
         *                  contributions instead of the Greene algorithm [\ref CATA].
         */
        CDPL_PHARM_API void prepareForPharmacophoreGeneration(Chem::Molecule& mol, bool calc_hyd = true, bool from_logp = false);
    }
} // namespace CDPL

#endif // CDPL_PHARM_MOLECULEFUNCTIONS_HPP
