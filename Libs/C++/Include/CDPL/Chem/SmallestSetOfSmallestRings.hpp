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

			void init(const MolecularGraph&);
	
			void findSSSR();
			void createRingFragments();

			bool sssrComplete() const;

			PathMessage* allocMessage();
			PathMessage* allocMessage(std::size_t, std::size_t, std::size_t, std::size_t);

			void freeMessage(PathMessage*);

			bool processCollision(const PathMessage*, const PathMessage*, bool);
			void processRing(PathMessage*);
			void processEvenRings();

			class TNode
			{

			public:
				TNode(std::size_t idx): index(idx) {}

				bool send(Controller*);
				bool receive(Controller*);

				void freeMessages(Controller*);

				std::size_t getIndex() const;

				static void connect(Controller*, TNode*, TNode*, std::size_t, std::size_t, std::size_t);

			private:
				typedef std::vector<TNode*> NodeList;
				typedef std::vector<std::size_t> BondIndexList;
				typedef std::vector<PathMessage*> MessageBuffer;

				NodeList      nbrNodes;
				BondIndexList bondIndices;
				MessageBuffer receiveBuffer;
				MessageBuffer sendBuffer;
				std::size_t   index;
			};

			class PathMessage
			{

			public:
				typedef boost::shared_ptr<PathMessage> SharedPointer;

				PathMessage() {} 
				PathMessage(std::size_t, std::size_t, std::size_t, std::size_t); 

				void init(std::size_t, std::size_t, std::size_t, std::size_t);

				void copy(const PathMessage*);
				bool join(const PathMessage*, const PathMessage*);

				void push(std::size_t, std::size_t);

				bool containsAtom(std::size_t const);
				bool containsBond(std::size_t const);

				std::size_t getFirstAtomIndex() const;
				std::size_t getFirstBondIndex() const;
				
				std::size_t getMaxBondIndex() const;
				std::size_t getNumBonds() const;

				Fragment::SharedPointer createRing(const MolecularGraph&) const;

				PathMessage& operator^=(const PathMessage&);

				struct LessCmpFunc : public std::binary_function<const PathMessage*, const PathMessage*, bool>
				{

					bool operator()(const PathMessage*, const PathMessage*) const;
				};

			private:
				Util::BitSet atomPath;
				Util::BitSet bondPath;
				std::size_t  firstAtomIdx;
				std::size_t  firstBondIdx;
				std::size_t  maxBondIdx;
			};

			struct TestMatrixRowCmpFunc : public std::binary_function<const PathMessage*, const PathMessage*, bool>
			{

				bool operator()(const PathMessage*, const PathMessage*) const;
			};

			typedef std::vector<TNode> NodeArray;
			typedef std::vector<PathMessage *> MessageList;
			typedef std::vector<PathMessage::SharedPointer> AllocMessageList;
			typedef std::set<const PathMessage*, PathMessage::LessCmpFunc> ProcRingSet;

			CyclicSubstructure       cycleSubstruct;
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
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SMALLESTSETOFSMALLESTRINGS_HPP
