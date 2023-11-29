/* 
 * CIPTetrahedralCenter.hpp 
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

/*
 * Copyright (c) 2020 John Mayfield
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Chem::CIPTetrahedralCenter.
 */

#ifndef CDPL_CHEM_CIPTETRAHEDRALCENTER_HPP
#define CDPL_CHEM_CIPTETRAHEDRALCENTER_HPP

#include <initializer_list>

#include "CIPStereoCenter.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * Describes a Sp3 tetrahedral centre using a "focus" (the central atom) and
         * four "carrier" (the neighbours of the central atom). 
         *
         * The arrangement of these atoms is described as left or right handed. This is the
         * ordering of the carries (c[1],c[2],c[3]) looking from the first carrier
         * (c[0]). For example in the diagram below if the bond from f to c[0] was a
         * bold wedge (pointing towards the viewer) the neighbours would be ordered
         * clockwise:
         *
         *           c[3]
         *           |
         *           |
         *   c[2] -- f -=# c[0]
         *           |
         *           |
         *           c[1]
         *
         *  Up/Bold wedge, c[1..3] are clockwise/right-handed.
         *
         * If the bond was a hashed wedged (pointing towards the viewer) the ordering
         * is now left-handed.
         *
         *           c[3]
         *           |
         *           |
         *   c[2] -- f ... c[0]
         *           |
         *           |
         *           c[1]
         *
         *  Down/Hashed wedge, c[1..3] are anti-clockwise/left-handed.
         *
         * Note - If one of the carriers is a hydrogen or lone pair you can re-use
         * the focus as a placeholder in the carriers:
         *
         *           f
         *           |
         *           |
         *   c[2] -- f ... c[0]
         *           |
         *           |
         *           c[1]
         *
         *  Down/Hashed wedge, {c[1..2],f} are anti-clockwise/left-handed.
         */
        class CIPTetrahedralCenter : public CIPStereoCenter
        {

          public:
            static constexpr unsigned int LEFT  = 0x1;
            static constexpr unsigned int RIGHT = 0x2;

            CIPTetrahedralCenter(const Atom* focus, std::initializer_list<const Atom*> carriers, unsigned int cfg):
                CIPStereoCenter(focus, carriers, cfg)
                {}

            unsigned int label(SequenceRule& comp);

            unsigned int label(CIPDigraph::Node& node, CIPDigraph& digraph, CIPSequenceRule& comp);

          private:
            unsigned int label(CIPDigraph::Node& node, CIPSequenceRule& comp);
 
            CIPDigraph::EdgeList edges;
        }
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPTETRAHEDRALCENTER_HPP
