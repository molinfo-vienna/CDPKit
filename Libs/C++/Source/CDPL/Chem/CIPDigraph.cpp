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


#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CIPDigraph.hpp"


using namespace CDPL;


namespace
{

    const std::size_t MAX_EDGE_CACHE_SIZE = 1000;
    const std::size_t MAX_NODE_CACHE_SIZE = 1000;
} // namespace


Chem::CIPDigraph::CIPDigraph():
    nodeCache(MAX_NODE_CACHE_SIZE), edgeCache(MAX_EDGE_CACHE_SIZE),
    root(0), tmpRoot(0), numNodes(0), rule6Ref(0)
{}

Chem::CIPDigraph::~CIPDigraph() {}

void Chem::CIPDigraph::setMolecularGraph(const MolecularGraph& molgraph)
{
    if (molGraph) {
        root     = 0;
        tmpRoot  = 0;
        numNodes = 0;
        rule6Ref = 0;

        nodeCache.putAll();
        edgeCache.putAll();
    }

    molGraph = &molgraph;

    mancude.setMolecularGraph(molgraph);
}

Chem::CIPDigraph::Node& Chem::CIPDigraph::init(const Atom& atom)
{
    tmpRoot  = 0;
    numNodes = 0;
    rule6Ref = 0;

    nodeCache.putAll();
    edgeCache.putAll();

    root = allocNode();
    root->init(*this, molGraph->getNumAtoms(), molGraph->getAtomIndex(atom), &atom, getType(atom));

    return *root;
}

void Chem::CIPDigraph::getNodes(const Atom& atom, NodeList& nodes)
{
    nodes.clear();

    Node* root = getCurrRoot();

    if (!root)
        return;
        
    nodeQueue.clear();
    nodeQueue.push_back(root);
    
    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front(); nodeQueue.pop_front();
        
        if (&atom == node->getAtom())
            nodes.push_back(node);

        for (auto e : node->getEdges()) {
            if (!e->isBeg(*node))
                continue;
            
            nodeQueue.push_back(&e->getEnd());
        }
    }
}

void Chem::CIPDigraph::expandAll()
{
    if (!root)
        return;
    
    nodeQueue.clear();
    nodeQueue.push_back(root);
    
    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front(); nodeQueue.pop_front();

        for (auto e : node->getEdges()) {
            if (!e->isBeg(*node))
                continue;
            
            if (!e->getEnd().isTerminal())
                nodeQueue.push_back(&e->getEnd());
        }
    }
}

void Chem::CIPDigraph::changeRoot(Node& new_root)
{
    edgeList.clear();

    nodeQueue.clear();
    nodeQueue.push_back(&new_root);

    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front(); nodeQueue.pop_front();

        for (auto e : node->getEdges()) {
            if (e->isEnd(*node)) {
                edgeList.push_back(e);
                nodeQueue.push_back(&e->getBeg());
            }
        }
    }
    
    for (auto e : edgeList)
        e->flip();
    
    tmpRoot = &new_root;
}

void Chem::CIPDigraph::expand(Node& beg)
{
    const Atom* atom = beg.getAtom();
    const EdgeList& edges = beg.getEdges();
    const Bond* prev = (edges.size() > 0 && !edges[0]->isBeg(beg) ? edges[0]->getBond() : nullptr);

    long charge = getFormalCharge(*atom);
    const CIPMancude::Fraction* atomic_no_fract = 0;
    
    // create 'explicit' nodes
    auto b_it = atom->getBondsBegin();
    
    for (auto a_it = atom->getAtomsBegin(), a_end = atom->getAtomsEnd(); a_it != a_end; ++ a_it, ++b_it) {
        const Atom& nbr = *a_it;

        if (!molGraph->containsAtom(nbr))
            continue;

        const Bond& bond = *b_it;

        if (!molGraph->containsBond(bond))
            continue;
        
        std::size_t nbr_idx = molGraph->getAtomIndex(nbr);
        std::size_t bond_order = getOrder(bond);

        if (!beg.getVisAtomMask().test(nbr_idx)) {
            addEdge(beg, &bond, newNode(beg, nbr_idx, &nbr));

            // duplicate nodes for bond orders (except for root atoms...)
            // for example >S=O
            if (root != &beg) {
                if (charge < 0 && (atomic_no_fract ? atomic_no_fract : atomic_no_fract = &mancude[*atom])->second > 1)
                    addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::BOND_DUPLICATE, beg.getDistance() + 1, atomic_no_fract));
                
                else if (bond_order > 1) {
                    if (!atomic_no_fract)
                        atomic_no_fract = &mancude[*atom];
                    
                    for (std::size_t i = 1; i < bond_order; i++)
                        addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::BOND_DUPLICATE, beg.getDistance() + 1, atomic_no_fract));
                }
            }
            
        } else if (&bond == prev) { // bond order expansion (backwards)
            if (root->getAtom() != &nbr && bond_order > 1) { 
                if (!atomic_no_fract)
                    atomic_no_fract = &mancude[*atom];
                
                for (std::size_t i = 1; i < bond_order; i++)
                    addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::BOND_DUPLICATE, beg.getDistance() - 1, atomic_no_fract));
            }
            
        } else { // ring closures
            std::size_t root_dist = traceBack(beg, &nbr).getDistance();
            
            addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::RING_DUPLICATE, root_dist, atomic_no_fract));

            if (charge < 0 && (atomic_no_fract ? atomic_no_fract : atomic_no_fract = &mancude[*atom])->second > 1) 
                addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::BOND_DUPLICATE, root_dist, atomic_no_fract));
            
            else if (bond_order > 1) {
                if (!atomic_no_fract)
                    atomic_no_fract = &mancude[*atom];
                
                for (std::size_t i = 1; i < bond_order; i++) 
                    addEdge(beg, &bond, newTerminalNode(beg, &nbr, Node::BOND_DUPLICATE, root_dist, atomic_no_fract));
            }
        }
    }

    // create implicit hydrogen nodes
    for (std::size_t i = 0, h_cnt = getImplicitHydrogenCount(*atom); i < h_cnt; i++)
        addEdge(beg, 0, newTerminalNode(beg, 0, Node::IMPL_HYDROGEN, beg.getDistance() + 1, 0));
}

const Chem::CIPDigraph::Node& Chem::CIPDigraph::traceBack(const Node& start, const Atom* atom) const
{
    for (const Node* node = &start; node; node = node->getParent())
        if (node->getAtom() == atom)
            return *node;

    return start; // should never happen!
}
    
Chem::CIPDigraph::Node& Chem::CIPDigraph::newNode(const Node& parent, std::size_t atom_idx, const Atom* atom)
{
    Node* node = allocNode();

    node->init(parent, *this, parent.getVisAtomMask(), atom_idx, atom, getType(*atom), 1, parent.getDistance() + 1, 0);
    
    return *node;
}

Chem::CIPDigraph::Node& Chem::CIPDigraph::newTerminalNode(const Node& parent, const Atom* atom, unsigned int flags, std::size_t root_dist,
                                                          const CIPMancude::Fraction* atomic_no_fract)
{
    Node* node = allocNode();

    if (!atom) {
        node->init(parent, *this, atom, 1, 1, root_dist, flags);
        return *node;
    }
    
    unsigned int atomic_no_num = 1;
    unsigned short atomic_no_den = 1;

    if ((flags & Node::BOND_DUPLICATE) && atomic_no_fract->second > 1) {
        atomic_no_num = atomic_no_fract->first;
        atomic_no_den = atomic_no_fract->second;
        
    } else
        atomic_no_num = getType(*atom);

    node->init(parent, *this, atom, atomic_no_num, atomic_no_den, root_dist, flags);
    return *node;
}

void Chem::CIPDigraph::addEdge(Node& beg, const Bond* bond, Node& end)
{
    Edge& e = *edgeCache.get();

    e.init(beg, bond, end);

    beg.add(e);
    end.add(e);
}

Chem::CIPDigraph::Node* Chem::CIPDigraph::allocNode()
{
    numNodes++;
    
    return nodeCache.get();
}


// Edge implementation

Chem::CIPDigraph::Edge::Edge():
    beg(0), bond(0), end(0), auxDescr(CIPDescriptor::UNDEF)
{}

void Chem::CIPDigraph::Edge::init(Node& beg, const Bond* bond, Node& end)
{
    this->beg  = &beg;
    this->bond = bond;
    this->end  = &end;

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

Chem::CIPDigraph::Node::Node():
    digraph(0), atom(0), rootDist(0), atomicNoNum(0), atomicNoDen(1),
    auxDescr(CIPDescriptor::UNDEF), flags(0), visAtoms(), edges(), parent(0)
{}

void Chem::CIPDigraph::Node::init(CIPDigraph& dg, std::size_t num_atoms, std::size_t atom_idx, const Atom* atom,
                                  unsigned int atomic_no)
{
    digraph     = &dg;
    this->atom  = atom;
    rootDist    = 1;
    atomicNoNum = atomic_no;
    atomicNoDen = 1;
    auxDescr    = CIPDescriptor::UNDEF;
    flags       = 0;
    parent      = 0;

    visAtoms.resize(num_atoms);
    visAtoms.reset();
    visAtoms.set(atom_idx);
    edges.clear();
}

void Chem::CIPDigraph::Node::init(const Node& parent, CIPDigraph& dg, const Util::BitSet& vis_mask, std::size_t atom_idx, const Atom* atom,
                                  unsigned int atomic_no_num, unsigned short atomic_no_den, std::size_t root_dist, unsigned int flags)
{
    digraph      = &dg;
    this->atom   = atom;
    rootDist     = root_dist;
    atomicNoNum  = atomic_no_num;
    atomicNoDen  = atomic_no_den;
    auxDescr     = CIPDescriptor::UNDEF;
    this->flags  = flags;
    visAtoms     = vis_mask;
    this->parent = &parent;

    visAtoms.set(atom_idx);
    edges.clear();
}

void Chem::CIPDigraph::Node::init(const Node& parent, CIPDigraph& dg, const Atom* atom, unsigned int atomic_no_num,
                                  unsigned short atomic_no_den, std::size_t root_dist, unsigned int flags)
{
    digraph      = &dg;
    this->atom   = atom;
    rootDist     = root_dist;
    atomicNoNum  = atomic_no_num;
    atomicNoDen  = atomic_no_den;
    auxDescr     = CIPDescriptor::UNDEF;
    this->flags  = flags | EXPANDED;
    this->parent = &parent;

    visAtoms.clear();
    edges.clear();
}

Chem::CIPDigraph::EdgeList& Chem::CIPDigraph::Node::getEdges()
{
    if (flags & EXPANDED)
        return edges;
    
    flags |= EXPANDED;
    digraph->expand(*this);

    return edges;
}

void Chem::CIPDigraph::Node::getEdges(EdgeList& edges, const Atom* end)
{
    edges.clear();
    
    for (auto e : getEdges()) {
        if (e->getEnd().isDuplicate())
            continue;
        
        if (end == e->getBeg().getAtom() || end == e->getEnd().getAtom())
            edges.push_back(e);
    }
}

void Chem::CIPDigraph::Node::getEdges(EdgeList& edges, const Edge* excl)
{
    edges.clear();

    for (auto e : getEdges())
        if (e != excl)
            edges.push_back(e);
}

void Chem::CIPDigraph::Node::getOutEdges(EdgeList& edges)
{
    edges.clear();

    for (auto e : getEdges())
        if (e->isBeg(*this))
            edges.push_back(e);
}

void Chem::CIPDigraph::Node::getNonTerminalOutEdges(EdgeList& edges)
{
    edges.clear();

    for (auto e : getEdges())
         if (e->isBeg(*this) && !e->getEnd().isTerminal())
             edges.push_back(e);
}
