/* 
 * CompleteRingSet.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include <algorithm>
#include <iterator>

#include "CDPL/Chem/CompleteRingSet.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Internal/RangeGenerator.hpp"


namespace
{

    const std::size_t MAX_EDGE_CACHE_SIZE = 100000;
}


using namespace CDPL;


Chem::CompleteRingSet::CompleteRingSet():
    edgeCache(MAX_EDGE_CACHE_SIZE)
{}

Chem::CompleteRingSet::CompleteRingSet(const MolecularGraph& molgraph):
    edgeCache(MAX_EDGE_CACHE_SIZE)
{
    perceive(molgraph);
}

Chem::CompleteRingSet::~CompleteRingSet() {}

void Chem::CompleteRingSet::perceive(const MolecularGraph& molgraph)
{
    clear();

    if (molgraph.getNumAtoms() == 0 || molgraph.getNumBonds() == 0)
        return;

    init(molgraph);

    reduce();
}

void Chem::CompleteRingSet::init(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;

    std::size_t num_atoms = molgraph.getNumAtoms();

    nodes.clear();
    nodes.reserve(num_atoms);

    std::generate_n(std::back_inserter(nodes), num_atoms, Internal::RangeGenerator<std::size_t>());

    MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();
 
    for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
        const Bond& bond = *it;
        const Atom& atom1 = bond.getBegin();
        const Atom& atom2 = bond.getEnd();

        Node* node1 = &nodes[molgraph.getAtomIndex(atom1)];
        Node* node2 = &nodes[molgraph.getAtomIndex(atom2)];
        
        allocEdge(bond, node1, node2);
    }    

    nodeQueue = NodeQueue();

    for (std::size_t i = 0; i < num_atoms; i++)
        nodeQueue.push(&nodes[i]);
}

void Chem::CompleteRingSet::reduce()
{
    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.top();
        Node::EdgeIterator edges_end = node->getEdgesEnd();

        for (Node::EdgeIterator it = node->getEdgesBegin(); it != edges_end; ) {
            const EdgePtr& edge1 = *it;
            Node* nbr_node1 = edge1->getNeighbor(node);

            Node::EdgeIterator saved_it = it;

            for (Node::EdgeIterator it2 = ++it; it2 != edges_end; ++it2) {
                const EdgePtr& edge2 = *it2;        

                if (edge1->intersects(edge2))
                    continue;

                Node* nbr_node2 = edge2->getNeighbor(node);

                if (nbr_node1 == nbr_node2) {
                    EdgePtr rng_edge = allocEdge(edge1, edge2, nbr_node1, nbr_node2, false);
        
                    addElement(rng_edge->createRing(molGraph));
                    
                } else
                    allocEdge(edge1, edge2, nbr_node1, nbr_node2, true);            
            }
        
            nbr_node1->removeEdge(edge1->getEdgeListIterator(nbr_node1));
            node->removeEdge(saved_it);
        }

        nodeQueue.pop();
    }
}

Chem::CompleteRingSet::EdgePtr Chem::CompleteRingSet::allocEdge(const EdgePtr& edge1, const EdgePtr& edge2, Node* node1, Node* node2, bool connect)
{
    EdgePtr edge = edgeCache.get();

    edge->init(edge, edge1, edge2, node1, node2, connect);

    return edge;
}

Chem::CompleteRingSet::EdgePtr Chem::CompleteRingSet::allocEdge(const Bond& bond, Node* node1, Node* node2)
{
    EdgePtr edge = edgeCache.get();
    
    edge->init(edge, molGraph, bond, node1, node2);

    return edge;
}


void Chem::CompleteRingSet::Edge::init(const EdgePtr& this_edge, const MolecularGraph* molgraph, const Bond& bond, Node* node1, Node* node2)
{
    bondPath.resize(molgraph->getNumBonds());
    bondPath.reset();

    bondPath.set(molgraph->getBondIndex(bond));

    nodePath.resize(molgraph->getNumAtoms());
    nodePath.reset();

    nodePath.set(node1->getIndex());
    nodePath.set(node2->getIndex());

    nodes[0] = node1;
    nodes[1] = node2;

    edgeListIters[0] = node1->addEdge(this_edge);
    edgeListIters[1] = node2->addEdge(this_edge);
}

void Chem::CompleteRingSet::Edge::init(const EdgePtr& this_edge, const EdgePtr& edge1, const EdgePtr& edge2, Node* node1, Node* node2, bool connect)
{
    bondPath = edge1->bondPath;
    bondPath |= edge2->bondPath;

    nodePath = edge1->nodePath;
    nodePath |= edge2->nodePath;

    nodes[0] = node1;
    nodes[1] = node2; 

    if (connect) {
        edgeListIters[0] = node1->addEdge(this_edge);
        edgeListIters[1] = node2->addEdge(this_edge);
    }
}

bool Chem::CompleteRingSet::Edge::intersects(const EdgePtr& edge) const
{
    tmpBitMask = bondPath;
    tmpBitMask &= edge->bondPath;

    if (tmpBitMask.any())
        return true;

    tmpBitMask = nodePath;
    tmpBitMask &= edge->nodePath;

    tmpBitMask.reset(nodes[0]->getIndex());
    tmpBitMask.reset(nodes[1]->getIndex());
    tmpBitMask.reset(edge->nodes[0]->getIndex());
    tmpBitMask.reset(edge->nodes[1]->getIndex());

    return tmpBitMask.any();
}

Chem::Fragment::SharedPointer Chem::CompleteRingSet::Edge::createRing(const MolecularGraph* molgraph) const
{
    Fragment::SharedPointer ring_ptr(new Fragment());
    Fragment& ring = *ring_ptr;

    const Atom* atom = &molgraph->getAtom(nodes[0]->getIndex());

    ring.addAtom(*atom);

    while (true) {
        Atom::ConstBondIterator bonds_end = atom->getBondsEnd();
        Atom::ConstBondIterator it = atom->getBondsBegin();

        for ( ; it != bonds_end; ++it) {
            const Bond& bond = *it;

            if (!molgraph->containsBond(bond))
                continue;

            if (!ring.containsBond(bond) && bondPath.test(molgraph->getBondIndex(bond))) {
                ring.addBond(bond);
                atom = &bond.getNeighbor(*atom);
                break;
            }
        }

        if (it == bonds_end)
            break;
    }

    return ring_ptr;
}

Chem::CompleteRingSet::Node* Chem::CompleteRingSet::Edge::getNeighbor(const Node* node) const
{
    return (nodes[0] == node ? nodes[1] : nodes[0]);
}

const Chem::CompleteRingSet::Node::EdgeIterator& Chem::CompleteRingSet::Edge::getEdgeListIterator(const Node* node) const
{
    return (nodes[0] == node ? edgeListIters[0] : edgeListIters[1]);
}


Chem::CompleteRingSet::Node::EdgeIterator Chem::CompleteRingSet::Node::addEdge(const EdgePtr& edge)
{
    edges.push_front(edge);

    return edges.begin();
}

void Chem::CompleteRingSet::Node::removeEdge(const EdgeIterator& it)
{
    edges.erase(it);
}

Chem::CompleteRingSet::Node::EdgeIterator Chem::CompleteRingSet::Node::getEdgesBegin()
{
    return edges.begin();
}

Chem::CompleteRingSet::Node::EdgeIterator Chem::CompleteRingSet::Node::getEdgesEnd()
{
    return edges.end();
}

std::size_t Chem::CompleteRingSet::Node::getIndex() const
{
    return index;
}
   
            
bool Chem::CompleteRingSet::Node::GreaterCmpFunc::operator()(const Node* node1, const Node* node2) const 
{
    return (node1->edges.size() > node2->edges.size());
}
