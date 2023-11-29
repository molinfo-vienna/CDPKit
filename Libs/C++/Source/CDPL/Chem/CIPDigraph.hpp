/* 
 * CIPDigraph.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPDigraph.
 */

#ifndef CDPL_CHEM_CIPDIGRAPH_HPP
#define CDPL_CHEM_CIPDIGRAPH_HPP

#include <cstddef>
#include <queue>
#include <vector>
#include <memory>
#include <utility>

#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolGraph;
        class Atom;
        class Bond;
        
        class CIPDigraph
        {

        public:
            class Node;
            class Edge;

            typedef std::vector<Node*> NodeList;
            typedef std::vector<Edge*> EdgeList;

            class Edge
            {

            public:
                typedef std::shared_ptr<Edge> SharedPointer;

                Edge();

                void set(Node& beg, const Bond* bond, Node& end);

                Node& getOther(const Node& node) const ;
 
                Node& getBeg() const
                {
                    return *beg;
                }

                Node& getEnd() const
                {
                    return *end;
                }

                unsigned int getAuxDescriptor() const
                {
                    return auxDescr;
                }

                void setAuxDescriptor(unsigned int descr)
                {
                    auxDescr = descr;
                }

                void flip()
                {
                    std::swap(beg, end);
                }

                const Bond* getBond() const
                {
                    return bond;
                }

                bool isBeg(const Node& node) const
                {
                    return (&node == beg);
                }

                bool isEnd(const Node& node) const
                {
                    return node.equals(end);
                }

            private:
                const Bond*  bond;
                Node*        beg;
                Node*        end;
                unsigned int auxDescr;
            };

            class Node
            {

            public:
                typedef std::shared_ptr<Node> SharedPointer;
       
                /**
                 * Flag indicates whether the node has been expanded.
                 */
                static constexpr unsigned int EXPANDED = 0x1;

                /**
                 * Flag indicates whether the node was duplicated
                 * at a ring closure.
                 */
                static constexpr unsigned int RING_DUPLICATE = 0x2;
                
                /**
                 * Flag indicates whether the node was duplicated
                 * at a bond with order &gt; 1.
                 */
                static constexpr unsigned int BOND_DUPLICATE = 0x4;
                
                /**
                 * Mask to check if a node is duplicated.
                 */
                static constexpr unsigned int DUPLICATE = 0x6;

                /**
                 * Node was created for an implicit hydrogen,
                 * the 'atom' value will be null.
                 */
                static constexpr unsigned int IMPL_HYDROGEN = 0x8;

                Node();
   
                void set(CIPDigraph& g, const Util::BitSet& vis_mask, std::size_t atom_idx, const Atom* atom, 
                         unsigned int atomic_no, unsigned short atomic_no_den, std::size_t root_dist, unsigned int flags);
 
                CIPDigraph& getDigraph() const
                {
                    return *digraph;
                }

                void add(Edge& e)
                {
                    edges.push_back(&e);
                }

                std::size_t getDistance() const
                {
                    return rootDist;
                }

                const Atom* getAtom() const
                {
                    return atom;
                }

                unsigned int getAtomicNo() const
                {
                    return atomicnumNum;
                }

                unsigned short getAtomicNoDenominator() const
                {
                    return atomicNoDen;
                }

                unsigned int getAuxDescriptor() const
                {
                    return auxDescr;
                }

                void setAuxDescriptor(unsigned int descr)
                {
                    auxDescr = descr;
                }

                EdgeList& getEdges();
 
                void getEdges(EdgeList& res, const Atom* end);

                void getEdges(EdgeList& res, const Edge* excl);

                void getOutEdges(EdgeList& res);

                void getNonTerminalOutEdges(EdgeList& res);

                bool isSet(unsigned int mask) const
                {
                    return (mask & flags);
                }

                bool isDuplicate() const
                {
                    return (flags & DUPLICATE);
                }

                bool isTerminal() const
                {
                    return (visAtoms.empty() || ((flags & EXPANDED) && edges.size() == 1));
                }

                bool isExpanded() const
                {
                    return (flags & EXPANDED);
                }

            private:
                CIPDigraph*    digraph;
                const Atom*    atom;
                std::size_t    rootDist;
                unsigned int   atomicNo;
                unsigned short atomicNoDen;
                unsigned int   auxDescr;
                unsigned int   flags;
                Util::BitSet   visAtoms;
                EdgeList       edges;
            };

            CIPDigraph();

            ~CIPDigraph();
            
            void setMolecularGraph(const MolecularGraph& molgraph);

            const MolecularGraph& getMolecularGraph() const
            {
                return *molGraph;
            }

            Node* init(const Atom& atom);

            std::size_t getNumNodes() const
            {
                return numNodes;
            }

            Node* getRoot() const
            {
                return root;
            }

            Node* getCurrRoot() const
            {
                return (!tmpRoot ? root : tmpRoot);
            }
 
            /**
             * Sets the root node of this digraph by flipping all the
             * 'up' edges to be 'down'.
             *
             * @param new_root the new root
             */
            void changeRoot(Node* new_root);

            void getNodes(const Atom& atom, NodeList& res);
  
            void expandAll();

            void expand(Node* beg);
 
            /**
             * Used exclusively for Rule 6, we set one atom as the reference.
             * @param ref reference atom
             */
            void setRule6Ref(const Atom* ref) 
            {
                rule6Ref = ref;
            }

            /**
             * Access the reference atom for Rule 6 (if one is set).
             */
            const Atom* getRule6Ref() const
            {
                return rule6Ref;
            }

        private:
            Node* newChild(const Node& parent, std::size_t atom_idx, const Atom* atom);
            Node* newTerminalChild(const Node& parent, std::size_t idx, const Atom* atom, unsigned int flags);

            void addEdge(Node& beg, const Bond* bond, Node& end);

            typedef Util::ObjectStack<Node> NodeCache;
            typedef Util::ObjectStack<Edge> EdgeCache;

            NodeCache             nodeCache;
            EdgeCache             edgeCache;
            const MolecularGraph* molGraph;
            Node*                 root;
            Node*                 tmpRoot;
            std::size_t           numNodes;
            const Atom*           rule6Ref;
        }
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPDIGRAPH_HPP
