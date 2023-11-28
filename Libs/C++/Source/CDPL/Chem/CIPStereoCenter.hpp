/* 
 * CIPStereoCenter.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPStereoCenter.
 */

#ifndef CDPL_CHEM_CIPSTEREOCENTER_HPP
#define CDPL_CHEM_CIPSTEREOCENTER_HPP

#include <initializer_list>
#include <cstddef>
#include <memory>

#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class CIPSequenceRule;

        class CIPStereoCenter
        {

          public:
            typedef std::unique_ptr<CIPStereoCenter> UniquePointer;
            
            CIPStereoCenter(std::initializer_list<const Atom*> foci, std::initializer_list<const Atom*> carriers, unsigned int cfg):
                focusAtoms(foci), numFocusAtoms(foci.size()), carrierAtoms(carriers), numCarrierAtoms(carriers.size()), config(cfg), digraph(0)
            {}

            CIPStereoCenter(const Atom* focus, std::initializer_list<const Atom*> carriers, unsigned int cfg):
                focusAtoms({focus}), numFocusAtoms(1), carrierAtoms(carriers), numCarrierAtoms(carriers.size()), config(cfg), digraph(0)
            {}

            virtual ~CIPStereoCenter() {}

            const Atom* getFocus() const
            {
                return focusAtoms[0];
            }

            const Atom* const* getFocusAtoms() const
            {
                return focusAtoms;
            }

            std::size_t getNumFocusAtoms() const
            {
                return numFocusAtoms;
            }

            unsigned int getConfig() const
            {
                return config;
            }

            const Atom* const* getCarrierAtoms() const
            {
                return carrierAtoms;
            }

            std::size_t getNumCarrierAtoms() const
            {
                return numCarrierAtoms;
            }

            void setDigraph(CIPDigraph& digraph)
            {
                this->digraph = &digraph;
            }

            CIPDigraph& getDigraph() const;

            virtual unsigned int label(CIPSequenceRule& comp) = 0;

            virtual unsigned int label(CIPDigraph::Node& node, CIPDigraph& digraph, CIPSequenceRule& comp);

            template <typename T>
            static unsigned int parity4(const T* const* trg, const T* const* ref)
            {
                if (ref[0] == trg[0]) {
                    if (ref[1] == trg[1]) {
                        // a,b,c,d -> a,b,c,d
                        if (ref[2] == trg[2] && ref[3] == trg[3])
                            return 2;
                        // a,b,c,d -> a,b,d,c
                        if (ref[2] == trg[3] && ref[3] == trg[2])
                            return 1;
                    } else if (ref[1] == trg[2]) {
                        // a,b,c,d -> a,c,b,d
                        if (ref[2] == trg[1] && ref[3] == trg[3])
                            return 1;
                        // a,b,c,d -> a,c,d,b
                        if (ref[2] == trg[3] && ref[3] == trg[1])
                            return 2;
                    } else if (ref[1] == trg[3]) {
                        // a,b,c,d -> a,d,c,b
                        if (ref[2] == trg[2] && ref[3] == trg[1])
                            return 1;
                        // a,b,c,d -> a,d,b,c
                        if (ref[2] == trg[1] && ref[3] == trg[2])
                            return 2;
                    }
                } else if (ref[0] == trg[1]) {
                    if (ref[1] == trg[0]) {
                        // a,b,c,d -> b,a,c,d
                        if (ref[2] == trg[2] && ref[3] == trg[3])
                            return 1;
                        // a,b,c,d -> b,a,d,c
                        if (ref[2] == trg[3] && ref[3] == trg[2])
                            return 2;
                    } else if (ref[1] == trg[2]) {
                        // a,b,c,d -> b,c,a,d
                        if (ref[2] == trg[0] && ref[3] == trg[3])
                            return 2;
                        // a,b,c,d -> b,c,d,a
                        if (ref[2] == trg[3] && ref[3] == trg[0])
                            return 1;
                    } else if (ref[1] == trg[3]) {
                        // a,b,c,d -> b,d,c,a
                        if (ref[2] == trg[2] && ref[3] == trg[0])
                            return 2;
                        // a,b,c,d -> b,d,a,c
                        if (ref[2] == trg[0] && ref[3] == trg[2])
                            return 1;
                    }
                } else if (ref[0] == trg[2]) {
                    if (ref[1] == trg[1]) {
                        // a,b,c,d -> c,b,a,d
                        if (ref[2] == trg[0] && ref[3] == trg[3])
                            return 1;
                        // a,b,c,d -> c,b,d,a
                        if (ref[2] == trg[3] && ref[3] == trg[0])
                            return 2;
                    } else if (ref[1] == trg[0]) {
                        // a,b,c,d -> c,a,b,d
                        if (ref[2] == trg[1] && ref[3] == trg[3])
                            return 2;
                        // a,b,c,d -> c,a,d,b
                        if (ref[2] == trg[3] && ref[3] == trg[1])
                            return 1;
                    } else if (ref[1] == trg[3]) {
                        // a,b,c,d -> c,d,a,b
                        if (ref[2] == trg[0] && ref[3] == trg[1])
                            return 2;
                        // a,b,c,d -> c,d,b,a
                        if (ref[2] == trg[1] && ref[3] == trg[0])
                            return 1;
                    }
                } else if (ref[0] == trg[3]) {
                    if (ref[1] == trg[1]) {
                        // a,b,c,d -> d,b,c,a
                        if (ref[2] == trg[2] && ref[3] == trg[0])
                            return 1;
                        // a,b,c,d -> d,b,a,c
                        if (ref[2] == trg[0] && ref[3] == trg[2])
                            return 2;
                    } else if (ref[1] == trg[2]) {
                        // a,b,c,d -> d,c,b,a
                        if (ref[2] == trg[1] && ref[3] == trg[0])
                            return 2;
                        // a,b,c,d -> d,c,a,b
                        if (ref[2] == trg[0] && ref[3] == trg[1])
                            return 1;
                    } else if (ref[1] == trg[0]) {
                        // a,b,c,d -> d,a,c,b
                        if (ref[2] == trg[2] && ref[3] == trg[1])
                            return 2;
                        // a,b,c,d -> d,a,b,c
                        if (ref[2] == trg[1] && ref[3] == trg[2])
                            return 1;
                    }
                }

                return 0;
            }

          protected:
            static CIPDigraph::Edge* findInternalEdge(const CIPDigraph::Node::EdgeList& edges, const Atom* f1, const Atom* f2);

            static bool isInternalEdge(const CIPDigraph::Edge& edge, const Atom* f1, const Atom* f2);

            static void removeInternalEdges(CIPDigraph::Node::EdgeList& edges, const Atom* f1, const Atom* f2);
        
            static void removeDuplicatedEdges(CIPDigraph::Node::EdgeList& edges);

          private:
            const Atom*  focusAtoms[2];
            std::size_t  numFocusAtoms;
            const Atom*  carrierAtoms[6];
            std::size_t  numCarrierAtoms;
            unsigned int config;
            CIPDigraph*  digraph;
        }
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPSTEREOCENTER_HPP
