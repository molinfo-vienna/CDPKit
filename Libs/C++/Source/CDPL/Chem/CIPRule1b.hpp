/* 
 * CIPRule1b.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPRule1b.
 */

#ifndef CDPL_CHEM_CIPRULE1B_HPP
#define CDPL_CHEM_CIPRULE1B_HPP

#include "CIPSequenceRule.hpp"
#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * CIPSequence Rule 1b
         *
         * <i>"A duplicate atom node whose corresponding nonduplicated atom
         * node is the root or is closer to the root ranks higher than
         * a duplicate atom node whose corresponding nonduplicated atom
         * node is farther from the root."</i>
         */
        class CIPRule1b : public CIPSequenceRule
        {

          public:
            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULE1B_HPP
