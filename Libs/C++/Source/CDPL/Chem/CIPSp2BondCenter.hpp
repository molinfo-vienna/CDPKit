/* 
 * CIPSp2BondCenter.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPSp2BondCenter.
 */

#ifndef CDPL_CHEM_CIPSP2BONDCENTER_HPP
#define CDPL_CHEM_CIPSP2BONDCENTER_HPP

#include <initializer_list>

#include "CIPStereoCenter.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * This configurations is used to describe the cis-trans specification of an
         * Sp2 bond. 
         *
         * It described in terms of two foci (the atoms of the double bond)
         * and two carries (each attached to either atom). The arrangement of the
         * carriers can either be OPPOSITE (trans) or TOGETHER (cis).
         * Importantly carrier[0] should be bonded to foci[0] and carrier[1] to
         * foci[1]. If there are additional atoms bonded they should be ignored, it
         * does not matter which atom is ignored as the labeler will inspect the
         * molecule and flip the labelling if needed. The bond is provided as to where
         * the label should be set.
         *
         *    c[0]           c[1]
         *     \           /
         *      \         /
         *       f[0] == f[1]
         *                \
         *                 \
         *                  x - ignored atom
         * "Together"
         *
         *    c[0]
         *     \
         *      \
         *       f[0] == f[1]
         *                \
         *                 \
         *                  c[1]
         * "Opposite"
         */
        class CIPSp2BondCenter : public CIPStereoCenter
        {

          public:
            static constexpr unsigned int OPPOSITE = 0x1;
            static constexpr unsigned int TOGETHER = 0x2;
            static constexpr unsigned int UNSPEC   = 0x4;
            
            CIPSp2BondCenter(CIPDigraph& digraph, std::initializer_list<const Atom*> foci, std::initializer_list<const Atom*> carriers, int cfg):
                CIPStereoCenter(digraph, foci, carriers, cfg)
            {}

            unsigned int label(CIPSequenceRule& comp);
  
            unsigned int label(CIPDigraph::Node& root1, CIPDigraph& digraph, CIPSequenceRule& comp);

          private:
            CIPDigraph::EdgeList edges1;
            CIPDigraph::EdgeList edges2;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSP2BONDCENTER_HPP
