/* 
 * UtilityFunctions.hpp 
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
 * \brief Declaration of miscellaneous utility functions.
 */

#ifndef CDPL_CHEM_UTILITYFUNCTIONS_HPP
#define CDPL_CHEM_UTILITYFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Parses the \e SMARTS string \a smarts into a freshly allocated query Chem::Molecule.
         * \param smarts The \e SMARTS string to parse.
         * \param init_qry If \c true, query-specific perception (e.g. ring-membership, aromaticity) is run on the parsed molecule.
         * \return A smart pointer to the parsed molecule, or an empty smart pointer if parsing failed.
         */
        CDPL_CHEM_API Molecule::SharedPointer parseSMARTS(const std::string& smarts, bool init_qry = true);

        /**
         * \brief Parses the \e SMARTS string \a smarts into the supplied molecule \a mol.
         * \param smarts The \e SMARTS string to parse.
         * \param mol The molecule to populate (cleared before parsing).
         * \param init_qry If \c true, query-specific perception is run on the parsed molecule.
         * \return \c true if parsing succeeded, and \c false otherwise.
         */
        CDPL_CHEM_API bool parseSMARTS(const std::string& smarts, Molecule& mol, bool init_qry = true);


        /**
         * \brief Parses the \e SMILES string \a smiles into a freshly allocated Chem::Molecule.
         * \param smiles The \e SMILES string to parse.
         * \return A smart pointer to the parsed molecule, or an empty smart pointer if parsing failed.
         */
        CDPL_CHEM_API Molecule::SharedPointer parseSMILES(const std::string& smiles);

        /**
         * \brief Parses the \e SMILES string \a smiles into the supplied molecule \a mol.
         * \param smiles The \e SMILES string to parse.
         * \param mol The molecule to populate (cleared before parsing).
         * \return \c true if parsing succeeded, and \c false otherwise.
         */
        CDPL_CHEM_API bool parseSMILES(const std::string& smiles, Molecule& mol);


        /**
         * \brief Extends the axis-aligned bounding box defined by \a min and \a max so that it contains the point \a coords.
         * \param min The lower-left corner of the bounding box (updated in place).
         * \param max The upper-right corner of the bounding box (updated in place).
         * \param coords The 3D point to include.
         * \param reset If \c true, the bounding box is first reset to \a coords (degenerate point box) before extension.
         */
        CDPL_CHEM_API void extendBoundingBox(Math::Vector3D& min, Math::Vector3D& max, const Math::Vector3D& coords, bool reset = false);

        /**
         * \brief Tells whether the point \a coords lies inside the axis-aligned bounding box defined by \a min and \a max.
         * \param min The lower-left corner of the bounding box.
         * \param max The upper-right corner of the bounding box.
         * \param coords The 3D point to test.
         * \return \c true if the point is inside (componentwise <= \a max and >= \a min), and \c false otherwise.
         */
        CDPL_CHEM_API bool insideBoundingBox(const Math::Vector3D& min, const Math::Vector3D& max, const Math::Vector3D& coords);


        /**
         * \brief Tells whether \a ring fulfills the H&uuml;ckel \e (4n+2)\e &pi;-electron criterion within \a molgraph.
         * \param ring The candidate aromatic ring.
         * \param molgraph The parent molecular graph.
         * \param arom_bond_mask A bond bit mask flagging bonds already known to be aromatic.
         * \return \c true if \a ring satisfies the H&uuml;ckel rule, and \c false otherwise.
         */
        CDPL_CHEM_API bool isAromatic(const Fragment& ring, const MolecularGraph& molgraph, const Util::BitSet& arom_bond_mask);

        /**
         * \brief Tells whether \a ring is guaranteed not to be aromatic (based on quick geometric/topological criteria).
         * \param ring The ring to test.
         * \param molgraph The parent molecular graph.
         * \return \c true if \a ring cannot be aromatic, and \c false if a more thorough test is required.
         */
        CDPL_CHEM_API bool isNotAromatic(const Fragment& ring, const MolecularGraph& molgraph);


        /**
         * \brief Tells whether any fragment in \a frag_list contains the bond \a bond.
         * \param frag_list The list of fragments to search.
         * \param bond The queried bond.
         * \return \c true if at least one fragment contains \a bond, and \c false otherwise.
         */
        CDPL_CHEM_API bool containsFragmentWithBond(const FragmentList& frag_list, const Bond& bond);

        /**
         * \brief Tells whether \a frag_list contains at least one fragment with at least \a min_size atoms.
         * \param frag_list The list of fragments to search.
         * \param min_size The minimum required atom count.
         * \return \c true if such a fragment exists, and \c false otherwise.
         */
        CDPL_CHEM_API bool containsFragmentWithMinSize(const FragmentList& frag_list, std::size_t min_size);


        /**
         * \brief Tells whether the target atom type \a tgt_type matches the query atom type \a qry_type
         *        (taking generic atom type classes like Chem::AtomType::HET into account).
         * \param qry_type The query atom type (Chem::AtomType value).
         * \param tgt_type The target atom type (Chem::AtomType value).
         * \return \c true if the target matches the query, and \c false otherwise.
         */
        CDPL_CHEM_API bool atomTypesMatch(unsigned int qry_type, unsigned int tgt_type);


        /**
         * \brief Translates a Sybyl atom type identifier to the corresponding generic Chem::AtomType value.
         * \param sybyl_type The Sybyl atom type identifier (Chem::SybylAtomType value).
         * \return The corresponding Chem::AtomType value.
         */
        CDPL_CHEM_API unsigned int sybylToAtomType(unsigned int sybyl_type);

        /**
         * \brief Returns the canonical textual representation of the Sybyl atom type \a sybyl_type.
         * \param sybyl_type The Sybyl atom type identifier (Chem::SybylAtomType value).
         * \return A \c const reference to the type-name string (empty for unknown types).
         */
        CDPL_CHEM_API const std::string& getSybylAtomTypeString(unsigned int sybyl_type);

        /**
         * \brief Returns the canonical textual representation of the Sybyl bond type \a sybyl_type.
         * \param sybyl_type The Sybyl bond-type identifier (Chem::SybylBondType value).
         * \return A \c const reference to the type-name string (empty for unknown types).
         */
        CDPL_CHEM_API const std::string& getSybylBondTypeString(unsigned int sybyl_type);
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_UTILITYFUNCTIONS_HPP
