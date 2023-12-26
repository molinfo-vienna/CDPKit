/* 
 * CIPRule6.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * Code based on a Java implementation of the CIP sequence rules by John Mayfield
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
 * \brief Definition of the class CDPL::Chem::CIPRule6.
 */

#ifndef CDPL_CHEM_CIPRULE6_HPP
#define CDPL_CHEM_CIPRULE6_HPP

#include "CIPSequenceRule.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * CIP Sequence Rule 6 (proposed)
         */
        class CIPRule6 : public CIPSequenceRule
        {

          public:
            bool isPseudoAsymmetric() const
            {
                // comes after Rule 5 so must be true
                return true; 
            }
            
            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULE6_HPP
