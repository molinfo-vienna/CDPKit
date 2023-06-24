/* 
 * ResidueList.hpp 
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
 * \brief Definition of the class CDPL::Biomol::ResidueList.
 */

#ifndef CDPL_BIOMOL_RESIDUELIST_HPP
#define CDPL_BIOMOL_RESIDUELIST_HPP

#include <cstddef>
#include <string>
#include <unordered_map>
#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"
#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief Implements the extraction of residues in biological macromolecules.
         */
        class CDPL_BIOMOL_API ResidueList : public Chem::FragmentList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ResidueList instances.
             */
            typedef std::shared_ptr<ResidueList> SharedPointer;

            /**
             * \brief Constructs an empty \c %ResidueList instance.
             */
            ResidueList() {}

            /**
             * \brief Constructs a \c %ResidueList instance that contains the residues of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to extract the residues.
             * \param flags The set of atom properties uniquely identifying a residue.
             */
            ResidueList(const Chem::MolecularGraph& molgraph, unsigned int flags = AtomPropertyFlag::DEFAULT);

            /**
             * \brief Replaces the current list of residues by the residues in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to extract the residues.
             * \param flags The set of atom properties uniquely identifying a residue.
             */
            void extract(const Chem::MolecularGraph& molgraph, unsigned int flags = AtomPropertyFlag::DEFAULT);

          private:
            struct ResidueID
            {

                std::size_t modelNumber;
                std::string chainID;
                char        insCode;
                std::string resCode;
                long        seqNumber;

                bool operator==(const ResidueID& res_id) const;
            };

            struct ResidueIDHashFunc
            {

                std::size_t operator()(const ResidueID& res_id) const;
            };

            void initResidueID(const Chem::Atom& atom, ResidueID& res_id, unsigned int flags) const;

            typedef std::unordered_map<ResidueID, Chem::Fragment::SharedPointer, ResidueIDHashFunc> ResidueIDToFragmentMap;

            ResidueIDToFragmentMap resIDsToFragments;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_RESIDUELIST_HPP
