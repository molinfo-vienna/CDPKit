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

#ifndef CDPL_BIOMOL_MOLECULEFUNCTIONS_HPP
#define CDPL_BIOMOL_MOLECULEFUNCTIONS_HPP

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Biomol
    {

        /**
         * \brief Merges alternative residue conformers in \a mol whose residue centers lie within \a max_ctr_dist of one another.
         *
         * Many \e PDB and \e mmCIF structures encode alternative conformations of a residue as multiple residues
         * with distinct alternate-location identifiers but mostly overlapping atom positions. This function
         * detects such interfering residue copies (residues whose geometric centers are closer than
         * \a max_ctr_dist) and combines them into a single residue with all observed atom positions, leaving
         * the molecule's topology and residue ordering otherwise unchanged.
         *
         * \param mol The molecule whose interfering residues are to be combined.
         * \param max_ctr_dist The maximum distance between residue centers that still qualifies them as
         *                     interfering copies of one another.
         * \return \c true if at least one residue group was combined, and \c false if no interfering
         *         residues were found.
         */
        CDPL_BIOMOL_API bool combineInterferingResidueCoordinates(Chem::Molecule& mol, double max_ctr_dist = 1.0);
    }
} // namespace CDPL

#endif // CDPL_BIOMOL_MOLECULEFUNCTIONS_HPP
