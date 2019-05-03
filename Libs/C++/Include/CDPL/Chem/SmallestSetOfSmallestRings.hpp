/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SmallestSetOfSmallestRings.hpp 
 * 
 * Implementation of Balducci's SSSR-finder algorithm 
 * (R. Balducci, R. S. Pearlman, J. Chem. Inf. Comput. Sci. 1994, 34, 822-831)
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
 * \brief Definition of the class CDPL::Chem::SmallestSetOfSmallestRings.
 */

#ifndef CDPL_CHEM_SMALLESTSETOFSMALLESTRINGS_HPP
#define CDPL_CHEM_SMALLESTSETOFSMALLESTRINGS_HPP

#include <vector>
#include <functional>
#include <cstddef>
#include <set>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/CyclicSubstructure.hpp"
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
		 * \brief Implements the perception of the <em>Smallest Set of Smallest Rings (SSSR)</em> of a molecular graphs.
		 * \see [\ref BALD] 
		 */
		class CDPL_CHEM_API SmallestSetOfSmallestRings : public FragmentList 
		{

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %SmallestSetOfSmallestRings instances.
			 */
			typedef boost::shared_ptr<SmallestSetOfSmallestRings> SharedPointer;

			/**
			 * \brief Constructs an empty \c %SmallestSetOfSmallestRings instance.
			 */
			SmallestSetOfSmallestRings() {}

			/**
			 * \brief Constructs a \c %SmallestSetOfSmallestRings instance containing the \e SSSR of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the \e SSSR.
			 */
			SmallestSetOfSmallestRings(const MolecularGraph& molgraph);

			/**
			 * \brief Replaces the current set of rings by the \e SSSR of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the \e SSSR.
			 */
			void perceive(const MolecularGraph& molgraph);

		private:
			typedef SmallestSetOfSmallestRings Controller;

			class TNode;
			class PathMessage;

			SmallestSetOfSmallestRings(const SmallestSetOfSmallestRings&);

			SmallestSetOfSmallestRings& operator=(const SmallestSetOfSmallestRings&);

			void visitComponentAtom(const Atom& atom);

			void init();
			void findSSSR();
			void createRingFragments();

			Fragment::SharedPointer createRing(const MolecularGraph& molgraph, PathMessage* msg);

			bool sssrComplete() const;

			PathMessage* allocMessage();
			PathMessage* allocMessage(std::size_t, std::size_t, std::size_t, std::size_t);

			void freeMessage(PathMessage*);

			bool processCollision(const PathMessage*, const PathMessage*, std::size_t, bool);
			void processRing(PathMessage*);
			void processEvenRings();

			class TNode
			{

			public:
				TNode(std::size_t idx): index(idx), active(true) {}

				bool send(Controller*);
				bool receive(Controller*);

				std::size_t getIndex() const;
				std::size_t getNumNeighbors() const;

				void initMessages(Controller* ctrl, std::size_t max_num_atoms, std::size_t max_num_bonds);

				void compressLinearRingFrags() const;

				bool isActive() const;

				Util::BitSet& getLinearRingFragBondMask();

				static void connect(TNode*, TNode*, std::size_t);

			private:
				std::size_t disconnect(TNode* nbr_node);

				void collectLinearFragNodes(TNode* coll_node, const TNode* last_node);
				void setCollectedBondBit(std::size_t idx);

				typedef std::vector<TNode*> NodeList;
				typedef std::vector<std::size_t> BondIndexList;
				typedef std::vector<PathMessage*> MessageBuffer;

				NodeList      nbrNodes;
				BondIndexList bondIndices;
				MessageBuffer receiveBuffer;
				MessageBuffer sendBuffer;
				std::size_t   index;
				Util::BitSet  collBondMask;
				bool          active;
			};

			class PathMessage
			{

			public:
				typedef boost::shared_ptr<PathMessage> SharedPointer;

				struct LessCmpFunc : public std::binary_function<const PathMessage*, const PathMessage*, bool>
				{

					bool operator()(const PathMessage*, const PathMessage*) const;
				};

				PathMessage() {} 
				PathMessage(std::size_t, std::size_t, std::size_t, std::size_t); 

				void init(std::size_t, std::size_t, std::size_t, std::size_t);

				void copy(const PathMessage*);
				bool join(const PathMessage*, const PathMessage*);

				void addAtom(std::size_t);
				void addBond(std::size_t);

				bool containsAtom(std::size_t const);
				bool containsBond(std::size_t const);

				std::size_t getFirstAtomIndex() const;
				std::size_t getFirstBondIndex() const;
				
				std::size_t getMaxBondIndex() const;

				const Util::BitSet& getAtomMask() const;
				const Util::BitSet& getBondMask() const;

				void clearFlags();

				void setRemoveFlag();
				void setEdgeCollisionFlag();

				bool getRemoveFlag() const;
				bool getEdgeCollisionFlag() const;

				PathMessage& operator^=(const PathMessage&);

			private:
				Util::BitSet atomPath;
				Util::BitSet bondPath;
				std::size_t  firstAtomIdx;
				std::size_t  firstBondIdx;
				std::size_t  maxBondIdx;
				bool         removeFlag;
				bool         edgeCollFlag;
			};

			struct TestMatrixRowCmpFunc : public std::binary_function<const PathMessage*, const PathMessage*, bool>
			{

				bool operator()(const PathMessage*, const PathMessage*) const;
			};

			typedef std::vector<TNode> NodeArray;
			typedef std::vector<PathMessage *> MessageList;
			typedef std::vector<PathMessage::SharedPointer> AllocMessageList;
			typedef std::set<const PathMessage*, PathMessage::LessCmpFunc> ProcRingSet;

			CyclicSubstructure       cyclicSubstruct;
			Fragment                 component;
			Util::BitSet             visAtomMask;
			NodeArray                nodes;
			AllocMessageList         allocMessages;
			MessageList              freeMessages;
			ProcRingSet              procRings;
			MessageList              evenRings;
			PathMessage*             testRing;
			PathMessage*             linDepTestRing;
			MessageList              linDepTestMtx;
			MessageList              sssr;
			std::size_t              sssrSize;
			Util::BitSet             ringBondMask;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SMALLESTSETOFSMALLESTRINGS_HPP
