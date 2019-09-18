/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MaxCommonBondSubstructureSearch.hpp 
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
 * \brief Definition of the class CDPL::Chem::MaxCommonBondSubstructureSearch.
 */

#ifndef CDPL_CHEM_MAXCOMMONBONDSUBSTRUCTURESEARCH_HPP
#define CDPL_CHEM_MAXCOMMONBONDSUBSTRUCTURESEARCH_HPP

#include <vector>
#include <set>
#include <cstddef>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \addtogroup CDPL_CHEM_MAX_COMMON_SUBSTRUCTURE_SEARCH
		 * @{
		 */

		/**
		 * \brief MaxCommonBondSubstructureSearch.
		 * \see [\ref MCESA]
		 */
		class CDPL_CHEM_API MaxCommonBondSubstructureSearch
		{

			typedef std::vector<AtomBondMapping*> ABMappingList;

		public:
			/**
			 * \brief A mutable random access iterator used to iterate over the stored atom/bond mapping objects.
			 */
			typedef boost::indirect_iterator<ABMappingList::iterator, AtomBondMapping> MappingIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the stored atom/bond mapping objects.
			 */
			typedef boost::indirect_iterator<ABMappingList::const_iterator, const AtomBondMapping> ConstMappingIterator;

			/**
			 * \brief Constructs and initializes a \c %MaxCommonBondSubstructureSearch instance.
			 */
			MaxCommonBondSubstructureSearch();

			/**
			 * \brief Constructs and initializes a \c %MaxCommonBondSubstructureSearch instance for the specified query structure.
			 * \param query A molecular graph that represents the query structure.
			 */
			MaxCommonBondSubstructureSearch(const MolecularGraph& query);
						
			/**
			 * \brief Destructor.
			 *
			 * Destroys the \c %MaxCommonBondSubstructureSearch instance and frees all allocated resources.
			 */
			~MaxCommonBondSubstructureSearch();

			/**
			 * \brief Allows to specify a new query structure.
			 * \param query A molecular graph that represents the query structure.
			 */
			void setQuery(const MolecularGraph& query);

			/**
			 * \brief Searches for a common substructure between the query and the specified target molecular graph.
			 *
			 * The method does not store any atom/bond mappings between query and target substructures - it just tells
			 * if a valid common substructure mapping solution involving at least getMinSubstructureSize() bonds could be found. If you need
			 * access to the atom/bond mappings, use findMappings() instead.
			 *
			 * \param target The molecular graph that has to be searched for a substructure in common with the query.
			 * \return \c true if a common substructure of at least the minimum accepted size could be found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
			 *       discarded.
			 */		
			bool mappingExists(const MolecularGraph& target);

			/**
			 * \brief Searches for all atom/bond mappings of query subgraphs to substructures of the specified target molecular graph
			 *        with a maximum bond count.
			 *
			 * The method will store all maximum-sized (in number of bonds) common substructure mapping solutions involving at
			 * least getMinSubstructureSize() atoms up to the maximum number of recorded mappings specified by setMaxNumMappings().
			 * If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found
			 * mappings will be discarded.
			 *
			 * \param target The molecular graph that has to be searched for all maximum-sized substructures in common with the query.
			 * \return \c true if common substructures of at least the minimum accepted size were found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
			 *       discarded.
			 */
			bool findMappings(const MolecularGraph& target);

			/**
			 * \brief Returns the number of atom/bond mappings that were recorded in the last search for common substructures.
			 * \return The number of atom/bond mappings that were recorded in the last search for common substructures.
			 * \see findMappings()
			 */
			std::size_t getNumMappings() const;

			/**
			 * \brief Returns a non-\c const reference to the stored atom/bond mapping object at index \a idx.
			 * \param idx The zero-based index of the atom/bond mapping object to return.
			 * \return A non-\c const reference to the atom/bond mapping object at index \a idx.
			 * \throw Base::IndexError if no mappings are available or \a idx is not in the range [0, getNumMappings() - 1].
			 */
			AtomBondMapping& getMapping(std::size_t idx);

			/**
			 * \brief Returns a \c const reference to the stored atom/bond mapping object at index \a idx.
			 * \param idx The zero-based index of the atom/bond mapping object to return.
			 * \return A \c const reference to the atom/bond mapping object at index \a idx.
			 * \throw Base::IndexError if no mappings are available or \a idx is not in the range [0, getNumMappings() - 1].
			 */
			const AtomBondMapping& getMapping(std::size_t idx) const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			MappingIterator getMappingsBegin();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator getMappingsBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			MappingIterator getMappingsEnd();

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator getMappingsEnd() const;

			/**
			 * \brief Allows to specify whether or not to store only unique atom/bond mappings.
			 *
			 * The mapping of a query pattern subgraph to a substructure of the target molecular graph is considered to be unique if it differs
			 * from all previously found mappings by at least one atom or bond. If the \a unique argument is \c true, and a newly discovered
			 * mapping covers the same atoms and bonds of the target (including all permutations) as a mapping that was found earlier
			 * in the search process, it is considered as a duplicate and will be discarded.
			 *
			 * \param unique If \c true, only unique mappings will be stored, and all found mappings otherwise.
			 * \note By default, duplicate mappings are not discarded.
			 */
			void uniqueMappingsOnly(bool unique);

			/**
			 * \brief Tells whether duplicate atom/bond mappings are discarded.
			 * \return \c true if duplicate mappings are discarded, and \c false otherwise.
			 * \see uniqueMappingsOnly(bool unique)
			 */
			bool uniqueMappingsOnly() const;

			/**
			 * \brief Allows to specify a limit on the number of stored atom/bond mappings.
			 *
			 * In a call to findMappings() the common substructure search will terminate as soon as the specified maximum
			 * number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can
			 * be disabled by providing zero for the value of \a max_num_mappings.
			 *
			 * \param max_num_mappings The maximum number of atom/bond mappings to store.
			 * \note By default, no limit is imposed on the number of stored mappings.
			 */
			void setMaxNumMappings(std::size_t max_num_mappings);

			/**
			 * \brief Returns the specified limit on the number of stored atom/bond mappings.
			 * \return The specified maximum number of stored atom/bond mappings.
			 * \see setMaxNumMappings(), findMappings() 
			 */
			std::size_t getMaxNumMappings() const;

			/**
			 * \brief Allows to specify the minimum accepted common substructure size.
			 *
			 * Any found common substructures which cover less than \a min_size bonds are not accepted as a valid
			 * solution and will be discarded.
			 *
			 * \param min_size The minimum accepted common substructure size in number of bonds.
			 * \note By default, the minimum common substructure size is set to zero.
			 */
			void setMinSubstructureSize(std::size_t min_size);

			/**
			 * \brief Returns the minimum accepted common substructure size.
			 * \return The minimum accepted common substructure size in number of bonds.
			 * \see setMinSubstructureSize()
			 */
			std::size_t getMinSubstructureSize() const;

		private:
			class AGNode;

			MaxCommonBondSubstructureSearch(const MaxCommonBondSubstructureSearch&);

			MaxCommonBondSubstructureSearch& operator=(const MaxCommonBondSubstructureSearch&);

			bool init(const MolecularGraph&);

			void initMatchExpressions();

			bool findEquivAtoms();
			
			bool atomsCompatible(const Bond&, const Bond&) const;
			
			const Atom* getCommonAtom(const Bond&, const Bond&) const;
			
			bool buildAssocGraph();

			bool findAssocGraphCliques(std::size_t);
			bool isLegal(const AGNode*);

			void undoAtomMapping(std::size_t);

			bool mappingFound();

			bool hasPostMappingMatchExprs() const;
			bool foundMappingMatches(const AtomBondMapping*) const;

			bool foundMappingUnique(bool);

			void clearMappings();

			AtomBondMapping* createAtomBondMapping(bool);
			void freeAtomBondMapping();

			void freeAssocGraph();
			void freeAtomBondMappings();

			class AGEdge;

			AGNode* allocAGNode(const Bond*, const Bond*);
			AGEdge* allocAGEdge(const Atom*, const Atom*);

			typedef std::vector<const AGEdge*> AGraphEdgeList;

			class AGNode
			{

			public:
				void setQueryBond(const Bond*);
				const Bond* getQueryBond() const;
				
				void setAssocBond(const Bond*);
				const Bond* getAssocBond() const;
				
				void addEdge(const AGEdge*);

				bool isConnected(const AGNode*) const;
				const AGEdge* findEdge(const AGNode*) const;
				
				void clear();

				void setIndex(std::size_t idx);

			private:
				std::size_t    index;
				const Bond*    queryBond;
				const Bond*    assocBond;
				Util::BitSet   connNodes;
				AGraphEdgeList atomEdges;
			};

			class AGEdge
			{

			public:
				void setQueryAtom(const Atom*);
				const Atom* getQueryAtom() const;
				
				void setAssocAtom(const Atom*);
				const Atom* getAssocAtom() const;
				
				void setNode1(const AGNode*);
				void setNode2(const AGNode*);
				
				const AGNode* getNode1() const;
				const AGNode* getNode2() const;

				const AGNode* getOther(const AGNode*) const;

			private:
				const Atom*   queryAtom;
				const Atom*   assocAtom;
				const AGNode* node1;
				const AGNode* node2;
			};

			class ABMappingMask 
			{

			public:
				void initQueryAtomMask(std::size_t);
				void initTargetAtomMask(std::size_t);

				void initQueryBondMask(std::size_t);
				void initTargetBondMask(std::size_t);

				void setQueryAtomBit(std::size_t);
				void setTargetAtomBit(std::size_t);

				void resetQueryAtomBit(std::size_t);
				void resetTargetAtomBit(std::size_t);

				bool testQueryAtomBit(std::size_t) const;
				bool testTargetAtomBit(std::size_t) const;

				void setQueryBondBit(std::size_t);
				void setTargetBondBit(std::size_t);

				void resetQueryAtomBits();
				void resetTargetAtomBits();

				void resetBondBits();

				bool operator<(const ABMappingMask&) const;
				bool operator>(const ABMappingMask&) const;

			private:
				Util::BitSet queryAtomMask;
				Util::BitSet targetAtomMask;
				Util::BitSet queryBondMask;
				Util::BitSet targetBondMask;
			};

			typedef MatchExpression<MolecularGraph>::SharedPointer MolGraphMatchExprPtr;

			typedef std::vector<Util::BitSet> BitMatrix;
			typedef std::vector<AGNode*> AGraphNodeList;
			typedef std::vector<AGraphNodeList> AGraphNodeMatrix;
			typedef std::set<ABMappingMask> UniqueMappingList;
			typedef std::vector<const Atom*> AtomList;
			typedef std::vector<const Bond*> BondList;
			typedef std::vector<MatchExpression<Atom, MolecularGraph>::SharedPointer> AtomMatchExprTable;
			typedef std::vector<MatchExpression<Bond, MolecularGraph>::SharedPointer> BondMatchExprTable;
			typedef Util::ObjectStack<AGNode> NodeCache;
			typedef Util::ObjectStack<AGEdge> EdgeCache;
			typedef Util::ObjectStack<AtomBondMapping> MappingCache;

			const MolecularGraph*         query;
			const MolecularGraph*         target;
			BitMatrix                     atomEquivMatrix;
			AGraphNodeMatrix              nodeMatrix;
			ABMappingList                 foundMappings;
			UniqueMappingList             uniqueMappings;
			AGraphEdgeList                cliqueEdges;
			AGraphNodeList                cliqueNodes;
			ABMappingMask                 mappingMask;
			AtomMatchExprTable            atomMatchExprTable;
			BondMatchExprTable            bondMatchExprTable;
			MolGraphMatchExprPtr          molGraphMatchExpr;
			AtomList                      postMappingMatchAtoms;
			BondList                      postMappingMatchBonds;
			NodeCache                     nodeCache;
			EdgeCache                     edgeCache;
			MappingCache                  mappingCache;
			bool                          queryChanged;
			bool                          initQueryData;
			bool                          uniqueMatches;
			bool                          saveMappings;
			std::size_t                   numQueryAtoms;
			std::size_t                   numQueryBonds;
			std::size_t                   numTargetAtoms;
			std::size_t                   numTargetBonds;
			std::size_t                   maxBondSubstructureSize;
			std::size_t                   currNumNullNodes;
			std::size_t                   minNumNullNodes;
			std::size_t                   maxNumMappings;
			std::size_t                   minSubstructureSize;
			std::size_t                   currNodeIdx;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MAXCOMMONBONDSUBSTRUCTURESEARCH_HPP
