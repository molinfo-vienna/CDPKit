/* 
 * CIPRule4a.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPRule4a.
 */

#ifndef CDPL_CHEM_CIPRULE4a_HPP
#define CDPL_CHEM_CIPRULE4a_HPP

#include "CIPSequenceRule.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * CIP Sequence Rule 4a
         *
         * <i>Chiral stereogenic units precede pseudoasymmetric stereogenic
         *    units and these precede nonstereogenic units.</i>
         */
        class CIPRule4a : public CIPSequenceRule
        {

          public:
            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);

          private:
            static unsigned int ordinal(unsigned int descr);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULE4a_HPP
