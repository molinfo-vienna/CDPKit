/* 
 * CIPSortingResult.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * The code in this file is a C++11 port of Java code written by John Mayfield
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
 * \brief Definition of the class CDPL::Chem::CIPSortingResult.
 */

#ifndef CDPL_CHEM_CIPSORTINGRESULT_HPP
#define CDPL_CHEM_CIPSORTINGRESULT_HPP


namespace CDPL
{

    namespace Chem
    {

        /**
         * Holds some properties that are determined when sorting/prioritising ligands.
         */
        class CIPSortingResult
        {
 
          public:
            CIPSortingResult(bool unique, bool found_wc, bool pseudo_asym):
                unique(unique), foundWildcard(found_wc), pseudoAsym(pseudo_asym)
            {}

            /**
             * Indicates whether the ligands were unique (i.e. could be ordered)
             *
             * @return whether the ligands were unique.
             */
            bool isUnique() const
            {
                return unique;
            }

            bool isPseudoAsymmetric() const
            {
                return pseudoAsym;
            }

            bool wasWildcardFound() const
            {
                return foundWildcard;
            }

          private:
            bool unique;
            bool foundWildcard;
            bool pseudoAsym;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSORTINGRESULT_HPP
