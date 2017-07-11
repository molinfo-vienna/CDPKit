/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CompleteRingSet.hpp 
 *
 * Hanser algorithm for exhaustive ring perception in a molecular graph 
 * (Th. Hanser, Ph. Jauffret, G. Kaufmann, J. Chem. Inf. Comput. Sci. 1996, 36, 1146-1152)
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::CompleteRingSet.
 */

#ifndef CDPL_CHEM_COMPLETERINGSET_HPP
#define CDPL_CHEM_COMPLETERINGSET_HPP

#include <queue>
#include <functional>
#include <vector>
#include <list>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_MOLECULAR_GRAPH_ALGORITHMS
		 * @{
		 */

		/**
		 * \brief Implements the exhaustive perception of rings in a molecular graph.
		 * \see [\ref HANSER] 
		 */
		class CDPL_CHEM_API CompleteRingSet : public FragmentList
		{

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %CompleteRingSet instances.
			 */
			typedef boost::shared_ptr<CompleteRingSet> SharedPointer;

			/**
			 * \brief Constructs an empty \c %CompleteRingSet instance.
			 */
			CompleteRingSet();

			/**
			 * \brief Constructs a \c %CompleteRingSet instance that contains the rings in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the complete set of rings.
			 */
			CompleteRingSet(const MolecularGraph& molgraph);

			/**
			 * \brief Destructor.
			 */
			~CompleteRingSet();

			/**
			 * \brief Replaces the current set of rings by the rings in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the complete set of rings.
			 */
			void perceive(const MolecularGraph& molgraph);

		private:
			CompleteRingSet(const CompleteRingSet&);

			CompleteRingSet& operator=(const CompleteRingSet&);

			class Edge;
			class Node;

			void init(const MolecularGraph&);
			void reduce();

			Edge* allocEdge(const Edge*, const Edge*, Node*, Node*, bool);
			Edge* allocEdge(const Bond&, Node*, Node*);

			void freeEdge(Edge*);
		 
			class Node
			{

				typedef std::list<Edge*> EdgeList;

			public:
				typedef EdgeList::iterator EdgeIterator;

				struct GreaterCmpFunc : public std::binary_function<const Node*, const Node*, bool>
				{
			
					bool operator()(const Node*, const Node*) const;
				};

				Node(std::size_t idx): index(idx) {}

				EdgeIterator addEdge(Edge*);
				void removeEdge(const EdgeIterator&);

				EdgeIterator getEdgesBegin();
				EdgeIterator getEdgesEnd();

				std::size_t getIndex() const;

			private:
				std::size_t index;
				EdgeList    edges;
			};

			class Edge
			{

			public:
				typedef boost::shared_ptr<Edge> SharedPointer;

				Edge() {}
				Edge(const MolecularGraph*, const Bond&, Node*, Node*);

				void init(const MolecularGraph*, const Bond&, Node*, Node*);
				void init(const Edge*, const Edge*, Node*, Node*, bool);

				bool intersects(const Edge*) const;

				Fragment::SharedPointer createRing(const MolecularGraph*) const;
		
				Node* getNeighbor(const Node*) const;
				const Node::EdgeIterator& getEdgeListIterator(const Node*) const;

			private:
				Node*                nodes[2];
				Node::EdgeIterator   edgeListIters[2];
				Util::BitSet         bondPath;
				Util::BitSet         nodePath;
				mutable Util::BitSet tmpBitMask;
			};
		 
			typedef std::vector<Node> NodeArray;
			typedef std::priority_queue<Node*, std::vector<Node*>, Node::GreaterCmpFunc> NodeQueue;
			typedef std::vector<Edge*> EdgeList;
			typedef std::vector<Edge::SharedPointer> AllocEdgeList;

			const MolecularGraph*    molGraph;
			NodeArray                nodes;
			NodeQueue                nodeQueue;
			AllocEdgeList            allocEdges;
			EdgeList                 freeEdges;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_COMPLETERINGSET_HPP
