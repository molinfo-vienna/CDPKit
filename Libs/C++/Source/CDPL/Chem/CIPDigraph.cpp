/* 
 * CIPDigraph.cpp 
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


#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CIPDigraph.hpp"


using namespace CDPL;


namespace
{

    const std::size_t MAX_EDGE_CACHE_SIZE = 10000;
    const std::size_t MAX_NODE_CACHE_SIZE = 10000;
}


Chem::CIPDigraph::CIPDigraph(): 
    nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE),
    root(0), tmpRoot(0), numNodes(0), rule6Ref(0) 
{}

Chem::CIPDigraph::~CIPDigraph() {} 

void Chem::CIPDigraph::setMolecularGraph(const MolecularGraph& molgraph)
{
    if (molGraph) {
        root = 0;
        tmpRoot = 0;
        numNodes = 0;
        rule6Ref = 0;

        nodeCache.putAll();
        edgeCache.putAll();
    }

    molGraph = &molgraph;
}

Chem::CIPDigraph::Node* Chem::CIPDigraph::init(const Atom& atom)
{
      
    this.root = new Node<>(this,
                           new char[mol.getNumAtoms()],
                           atom,
                           mol.getAtomicNum(atom),
                           1,
                           (char) 1,
                           0);
    int atomIdx = mol.getAtomIdx(atom);
    this.root.visit[atomIdx] = 1;
    numNodes++;
    return this.root;
}

void Chem::CIPDigraph::getNodes(const Atom* atom, NodeList& res)
{
    List<Node>  result = new ArrayList<>();
    Deque<Node> queue  = new ArrayDeque<>();
    queue.add(getCurrRoot());
    while (!queue.isEmpty()) {
        Node node = queue.poll();
        if (atom.equals(node.getAtom())) {
            result.add(node);
        }
        for (Edge e : node.getEdges()) {
            if (!e.isBeg(node))
                continue;
            queue.add(e.getEnd());
        }
    }
    return result;
}

void Chem::CIPDigraph::expandAll()
{
    Deque<Node> queue = new ArrayDeque<>();
    queue.add(root);
    while (!queue.isEmpty()) {
        Node node = queue.poll();
        for (Edge e : node.getEdges()) {
            if (!e.isBeg(node)) continue;
            if (!e.getEnd().isTerminal())
                queue.add(e.getEnd());
        }
    }
}

void Chem::CIPDigraph::changeRoot(Node* new_root)
{
    Deque<Node> queue = new ArrayDeque<>();
    queue.add(newroot);
    List<Edge> toflip = new ArrayList<>();
    while (!queue.isEmpty()) {
        Node node = queue.poll();
        for (Edge e : node.getEdges()) {
            if (e.isEnd(node)) {
                toflip.add(e);
                queue.add(e.getBeg());
            }
        }
    }
    for (Edge e : toflip)
        e.flip();
    tmproot = newroot;
}

void Chem::CIPDigraph::expand(Node* beg)
{
    final A                atom  = beg.getAtom();
    final List<Edge> edges = beg.getEdges();
    final B                prev  = edges.size() > 0 && !edges.get(0).isBeg(beg) ? edges.get(0).getBond() : null;

    // create 'explicit' nodes
    for (final B bond : mol.getBonds(atom)) {
        final A   nbr    = mol.getOther(bond, atom);
        final int nbrIdx = mol.getAtomIdx(nbr);
        final int bord   = mol.getBondOrder(bond);

        if (beg.visit[nbrIdx] == 0) {

            Node end = beg.newChild(nbrIdx, nbr);
            numNodes++;
            addEdge(beg, bond, end);

            // duplicate nodes for bond orders (except for root atoms...)
            // for example >S=O
            if (!root.equals(beg)) {
                if (mol.getCharge(atom) < 0 && mol.getFractionalAtomicNum(atom).getDen() > 1) {
                    end = beg.newTerminalChild(nbrIdx, nbr, Node.BOND_DUPLICATE);
                    numNodes++;
                    addEdge(beg, bond, end);
                } else {
                    for (int i = 1; i < bord; i++) {
                        end = beg.newTerminalChild(nbrIdx, nbr, Node.BOND_DUPLICATE);
                        numNodes++;
                        addEdge(beg, bond, end);
                    }
                }
            }
        }
        // bond order expansion (backwards)
        else if (bond.equals(prev)) {
            if (!root.getAtom().equals(nbr)) {
                for (int i = 1; i < bord; i++) {
                    Node end = beg.newTerminalChild(nbrIdx, nbr, Node.BOND_DUPLICATE);
                    numNodes++;
                    addEdge(beg, bond, end);
                }
            }
        }
        // ring closures
        else {
            Node end = beg.newTerminalChild(nbrIdx, nbr, Node.RING_DUPLICATE);
            numNodes++;
            addEdge(beg, bond, end);

            if (mol.getCharge(atom) < 0 && mol.getFractionalAtomicNum(atom).getDen() > 1) {
                end = beg.newTerminalChild(nbrIdx, nbr, Node.BOND_DUPLICATE);
                numNodes++;
                addEdge(beg, bond, end);
            } else {
                for (int i = 1; i < bord; i++) {
                    end = beg.newTerminalChild(nbrIdx, nbr, Node.BOND_DUPLICATE);
                    numNodes++;
                    addEdge(beg, bond, end);
                }
            }
        }
    }

    // Create implicit hydrogen nodes
    final int hcnt = mol.getNumHydrogens(atom);
    for (int i = 0; i < hcnt; i++) {
        Node end = beg.newTerminalChild(-1, null, Node.IMPL_HYDROGEN);
        numNodes++;
        addEdge(beg, null, end);
    }
}

void Chem::CIPDigraph::addEdge(Node& beg, const Bond* bond, Node& end)
{
    Edge& e = *edgeCache.getRaw();

    e.set(beg, end, bond);

    beg.add(e);
    end.add(e);
}


// Edge implementation

Chem::CIPDigraph::Edge::Edge():
    beg(0), end(0), bond(0), auxDescr(CIPDescriptor::UNDEF)
{}

void Chem::CIPDigraph::Edge::set(Node& beg, const Bond* bond, Node& end)
{
    this->beg = &beg;
    this->end = &end;
    this->bond = bond;

    auxDescr = CIPDescriptor::UNDEF;
}

Chem::CIPDigraph::Node& Chem::CIPDigraph::Edge::getOther(const Node& node) const 
{
    if (&node == beg)
        return *end;

    if (&node == end)
        return *beg;

    throw Base::ItemNotFound("CIPDigraph::Edge: node not an end-point of this edge");
}


// Node implementation
