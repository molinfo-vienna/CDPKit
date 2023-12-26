/* 
 * CIPRule4b.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPRule5.
 */

#ifndef CDPL_CHEM_CIPRULE5_HPP
#define CDPL_CHEM_CIPRULE5_HPP

#include <deque>

#include "CIPSequenceRule.hpp"
#include "CIPDigraph.hpp"
#include "CIPPairList.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * CIP Sequence Rule 5
         */
        class CIPRule5 : public CIPSequenceRule
        {

          public:
            CIPRule5();

            bool isPseudoAsymmetric() const
            {
                return true;
            }

            int compare(const CIPDigraph::Edge& a, const CIPDigraph::Edge& b);

          private:
            void fillPairs(CIPDigraph::Node& beg, CIPPairList& plist);

            typedef std::deque<CIPDigraph::Node*> NodeQueue;
            
            unsigned int refDescriptor;
            CIPPairList  listRA;
            CIPPairList  listSA;
            CIPPairList  listRB;
            CIPPairList  listSB;
            NodeQueue    nodeQueue;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPRULE5_HPP
