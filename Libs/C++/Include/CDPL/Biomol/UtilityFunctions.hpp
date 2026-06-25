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
 * \brief Declaration of various utility functions.
 */

#ifndef CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
#define CDPL_BIOMOL_UTILITYFUNCTIONS_HPP

#include <algorithm>
#include <functional>

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ProcessingFlags.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief Searches the iterator range [\a it, \a end) for the first atom whose PDB-style residue
         *        identity attributes match the given filter values.
         *
         * Each filter argument is ignored when set to its sentinel value (\c nullptr / \e 0 / Biomol::IGNORE_SEQUENCE_NO /
         * Biomol::IGNORE_SERIAL_NO). All supplied filters must match for an atom to be considered a hit.
         *
         * \tparam Iter The (forward) iterator type whose value type is \c Chem::Atom.
         * \param it Iterator pointing to the first atom of the range.
         * \param end Iterator pointing one past the last atom of the range.
         * \param res_code The \e PDB three-letter residue code to match (or \c nullptr to ignore).
         * \param chain_id The \e PDB chain ID to match (or \c nullptr to ignore).
         * \param res_seq_no The \e PDB residue sequence number to match (or Biomol::IGNORE_SEQUENCE_NO to ignore).
         * \param ins_code The \e PDB insertion code to match (or \e 0 to ignore).
         * \param model_no The \e PDB model number to match (or \e 0 to ignore).
         * \param atom_name The \e PDB atom name to match (or \c nullptr to ignore).
         * \param serial_no The \e PDB atom serial number to match (or Biomol::IGNORE_SERIAL_NO to ignore).
         * \return An iterator pointing to the first matching atom, or \a end if no match was found.
         */
        template <typename Iter>
        Iter findResidueAtom(Iter it, Iter end, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
                             char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO)
        {
            return std::find_if(it, end,
                                std::bind(static_cast<bool (*)(const Chem::Atom&, const char*, const char*, long, char, std::size_t, const char*, long)>(&matchesResidueInfo), std::placeholders::_1, res_code, chain_id, res_seq_no,
                                          ins_code, model_no, atom_name, serial_no));
        }

        /**
         * \brief Searches the iterator range [\a it, \a end) for the first residue (molecular graph) whose
         *        PDB-style identity attributes match the given filter values, optionally requiring a matching atom.
         *
         * Each filter argument is ignored when set to its sentinel value. If both \a atom_name and \a serial_no
         * are sentinels, the search returns the first residue matching the residue-level filters. Otherwise,
         * a residue is only returned if it additionally contains an atom matching \a atom_name / \a serial_no.
         *
         * \tparam Iter The (forward) iterator type whose value type is convertible to \c Chem::MolecularGraph.
         * \param it Iterator pointing to the first residue of the range.
         * \param end Iterator pointing one past the last residue of the range.
         * \param res_code The \e PDB three-letter residue code to match (or \c nullptr to ignore).
         * \param chain_id The \e PDB chain ID to match (or \c nullptr to ignore).
         * \param res_seq_no The \e PDB residue sequence number to match (or Biomol::IGNORE_SEQUENCE_NO to ignore).
         * \param ins_code The \e PDB insertion code to match (or \e 0 to ignore).
         * \param model_no The \e PDB model number to match (or \e 0 to ignore).
         * \param atom_name The \e PDB atom name an atom of the residue must match (or \c nullptr to ignore).
         * \param serial_no The \e PDB atom serial number an atom of the residue must match (or Biomol::IGNORE_SERIAL_NO to ignore).
         * \return An iterator pointing to the first matching residue, or \a end if no match was found.
         */
        template <typename Iter>
        Iter findResidue(Iter it, Iter end, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
                         char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO)
        {
            for (; it != end; ++it) {
                const Chem::MolecularGraph& res = *it;

                if (!matchesResidueInfo(res, res_code, chain_id, res_seq_no, ins_code, model_no))
                    continue;

                if (atom_name == 0 && serial_no == IGNORE_SERIAL_NO)
                    return it;

                if (std::find_if(res.getAtomsBegin(), res.getAtomsEnd(),
                                 std::bind(static_cast<bool (*)(const Chem::Atom&, const char*, const char*, long, char, std::size_t, const char*, long)>(&matchesResidueInfo), std::placeholders::_1, res_code, chain_id, res_seq_no,
                                           ins_code, model_no, atom_name, serial_no)) != res.getAtomsEnd())
                    return it;
            }

            return end;
        }
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
