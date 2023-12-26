/* 
 * CIPDigraph.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPDigraph.
 */

#ifndef CDPL_CHEM_CIPDIGRAPH_HPP
#define CDPL_CHEM_CIPDIGRAPH_HPP

#include <cstddef>
#include <deque>
#include <vector>
#include <memory>
#include <utility>

#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"

#include "CIPMancude.hpp"


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

                void init(Node& beg, const Bond* bond, Node& end);

                Node& getOther(const Node& node) const;

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
                    return (&node == end);
                }

              private:
                Node*        beg;
                const Bond*  bond;
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

                void init(CIPDigraph& dg, std::size_t num_atoms, std::size_t atom_idx, const Atom* atom,
                          unsigned int atomic_no);

                void init(const Node& parent, CIPDigraph& dg, const Util::BitSet& vis_mask, std::size_t atom_idx, const Atom* atom,
                          unsigned int atomic_no_num, unsigned short atomic_no_den, std::size_t root_dist,
                          unsigned int flags);

                void init(const Node& parent, CIPDigraph& dg, const Atom* atom, unsigned int atomic_no_num, unsigned short atomic_no_den,
                          std::size_t root_dist, unsigned int flags);

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

                unsigned int getAtomicNoNumerator() const
                {
                    return atomicNoNum;
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

                const Util::BitSet& getVisAtomMask() const
                {
                    return visAtoms;
                }

                EdgeList& getEdges();

                void getEdges(EdgeList& edges, const Atom* end);

                void getEdges(EdgeList& edges, const Edge* excl = 0);

                void getOutEdges(EdgeList& edges);

                void getNonTerminalOutEdges(EdgeList& edges);

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
                    return (visAtoms.empty() || ((flags & EXPANDED) && edges.size() <= 1));
                }

                bool isExpanded() const
                {
                    return (flags & EXPANDED);
                }

                const Node* getParent() const
                {
                    return parent;
                }

              private:
                CIPDigraph*    digraph;
                const Atom*    atom;
                std::size_t    rootDist;
                unsigned int   atomicNoNum;
                unsigned short atomicNoDen;
                unsigned int   auxDescr;
                unsigned int   flags;
                Util::BitSet   visAtoms;
                EdgeList       edges;
                const Node*    parent;
            };

            CIPDigraph();

            ~CIPDigraph();

            void setMolecularGraph(const MolecularGraph& molgraph);

            const MolecularGraph& getMolecularGraph() const
            {
                return *molGraph;
            }

            Node& init(const Atom& atom);

            void reset();
            
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
            void changeRoot(Node& new_root);

            void getNodes(const Atom& atom, NodeList& nodes);

            void expandAll();

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
            void expand(Node& beg);

            const Node& traceBack(const Node& start, const Atom* atom) const;
    
            Node& newNode(const Node& parent, std::size_t atom_idx, const Atom* atom);
            Node& newTerminalNode(const Node& parent, const Atom* atom, unsigned int flags, std::size_t root_dist,
                                  const CIPMancude::Fraction* atomic_no_fract);
            
            void addEdge(Node& beg, const Bond* bond, Node& end);
            
            typedef std::deque<Node*>       NodeQueue;
            typedef Util::ObjectStack<Node> NodeCache;
            typedef Util::ObjectStack<Edge> EdgeCache;

            NodeCache             nodeCache;
            EdgeCache             edgeCache;
            const MolecularGraph* molGraph;
            Node*                 root;
            Node*                 tmpRoot;
            const Atom*           rule6Ref;
            NodeQueue             nodeQueue;
            EdgeList              edgeList;
            CIPMancude            mancude;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPDIGRAPH_HPP
