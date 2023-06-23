/* 
 * ReactionSubstructureSearch.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::ReactionSubstructureSearch.
 */

#ifndef CDPL_CHEM_REACTIONSUBSTRUCTURESEARCH_HPP
#define CDPL_CHEM_REACTIONSUBSTRUCTURESEARCH_HPP

#include <vector>
#include <deque>
#include <set>
#include <utility>
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

		class Reaction;
		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \brief ReactionSubstructureSearch.
		 */
		class CDPL_CHEM_API ReactionSubstructureSearch
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
			 * \brief Constructs and initializes a \c %ReactionSubstructureSearch instance.
			 */
			ReactionSubstructureSearch();

			/**
			 * \brief Constructs and initializes a \c %ReactionSubstructureSearch instance for the specified query reaction pattern.
			 * \param query The query reaction.
			 */
			ReactionSubstructureSearch(const Reaction& query);

			/**
			 * \brief Destructor.
			 *
			 * Destroys the \c %ReactionSubstructureSearch instance and frees all allocated resources.
			 */
			~ReactionSubstructureSearch();

			/**
			 * \brief Allows to specify a new query reaction pattern.
			 * \param query Specifies the reaction pattern to search for.
			 */
			void setQuery(const Reaction& query);
			
			/**
			 * \brief Tells whether the query reaction pattern matches the specified target reaction.
			 *
			 * The method does not store any atom/bond mappings between the query and target reaction - it just tells
			 * if a complete mapping of the query is possible. If you need access to the atom/bond mappings, use findMappings()
			 * instead.
			 *
			 * \param target The reaction that has to be searched for a match of the query reaction pattern.
			 * \return \c true if the query pattern matches the target reaction, and \c false otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
			 *       discarded.
			 */
			bool mappingExists(const Reaction& target);

			/**
			 * \brief Searches for all possible atom/bond between the query reaction pattern and the specified target
			 *        reaction.
			 *
			 * The method will store all found atom/bond mapping solutions up to the maximum number of recorded mappings
			 * specified by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)),
			 * any duplicates of previously found mappings will be discarded.
			 *
			 * \param target The reaction that has to be searched for matches of the query reaction pattern.
			 * \return \c true if the query pattern can be mapped to the specified target reaction, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
			 *       discarded.
			 */
			bool findMappings(const Reaction& target);

			/**
			 * \brief Returns the number of atom/bond mappings that were recorded in the last call to findMappings().
			 * \return The number of atom/bond mappings that were recorded in the last call to findMappings().
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
			 * \brief Returns a mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			MappingIterator begin();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator begin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			MappingIterator end();

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator end() const;

			/**
			 * \brief Allows to specify whether or not to store only unique atom/bond mappings.
			 *
			 * A mapping of the query pattern to the target reaction is considered to be unique if it differs
			 * from all previously found mappings by at least one atom or bond. If the \a unique argument is \c true and a newly discovered
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
			 * In a call to findMappings() the reaction substructure search will terminate as soon as the specified maximum number of stored
			 * atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled
			 * by providing zero for the value of \a max_num_mappings.
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
			 * \brief Allows the reaction role specific exclusion of query and target components from the search for matching reaction substructures.
			 *
			 * The \a roles argument is a bitwise OR combination of the flags defined in namespace Chem::ReactionRole. When the flag for a
			 * particular reaction role is missing in the provided bitmask, then all reaction components with this role assignment (both in the
			 * query and target reaction) will be simply ignored during the reaction substructure search. This has the same effect as 'removing'
			 * the affected components from the query and target reaction prior to starting the search and adding them again afterwards.
			 *
			 * \param roles A bitmask specifying the non-excluded reaction component roles.
			 * \note By default, all types of reaction components are considered.
			 */
			void setEnabledReactionRoles(unsigned int roles);

			/**
			 * \brief Tells which reaction component roles are considered in the search for matching reaction
			 *        substructures.
			 * \return A bitmask specifying the considered reaction component roles.
			 * \see setEnabledReactionRoles(), Chem::ReactionRole
			 */
			unsigned int getEnabledReactionRoles() const;
		
		private:
			typedef std::pair<std::size_t, std::size_t> IndexOffsetPair;

			ReactionSubstructureSearch(const ReactionSubstructureSearch&);

			ReactionSubstructureSearch& operator=(const ReactionSubstructureSearch&);

			bool init(const Reaction&);
			
			void initQueryData();
			void initTargetData();

			bool findEquivAtoms();
			bool findEquivBonds();

			bool mapAtoms();

			std::size_t nextQueryAtom() const;
			bool nextTargetAtom(std::size_t, unsigned int, std::size_t&, std::size_t&) const;

			bool atomMappingAllowed(std::size_t, std::size_t) const;

			bool mapBonds(const Atom*, const Atom*, const IndexOffsetPair&);
			bool mapAtoms(std::size_t);
			bool mapAtoms(std::size_t, std::size_t);

			bool mappingFound();

			bool hasPostMappingMatchExprs() const;
			bool foundMappingMatches(const AtomBondMapping*) const;

			bool foundMappingUnique();

			void freeAtomBondMappings();
			void freeAtomBondMapping();

			AtomBondMapping* createAtomBondMapping();

			class ABMappingMask {

			public:
				void initAtomMask(std::size_t);
				void initBondMask(std::size_t);

				void setAtomBit(std::size_t);
				void resetAtomBit(std::size_t);

				bool testAtomBit(std::size_t) const;

				void setBondBit(std::size_t);
				void resetBondMask();

				bool operator<(const ABMappingMask&) const;
				bool operator>(const ABMappingMask&) const;

			private:
				Util::BitSet atomMask;
				Util::BitSet bondMask;
			};

			typedef MatchExpression<Reaction>::SharedPointer ReactionMatchExprPtr;

			typedef std::vector<Util::BitSet> BitMatrix;
			typedef std::vector<const Atom*> AtomMappingTable;
			typedef std::vector<std::size_t> BondMappingTable;
			typedef std::deque<std::size_t> AtomQueue;
			typedef std::set<ABMappingMask> UniqueMappingList;
			typedef std::vector<const Atom*> AtomList;
			typedef std::vector<const Bond*> BondList;
			typedef std::vector<std::size_t> IndexList;
			typedef std::vector<MatchExpression<Atom, MolecularGraph>::SharedPointer> AtomMatchExprTable;
			typedef std::vector<MatchExpression<Bond, MolecularGraph>::SharedPointer> BondMatchExprTable;
			typedef std::vector<IndexOffsetPair> IndexOffsetTable;
			typedef Util::ObjectStack<AtomBondMapping> MappingCache;

			const Reaction*                query;
			const Reaction*                target;
			AtomList                       queryAtoms;
			BondList                       queryBonds;
			AtomList                       targetAtoms;
			BondList                       targetBonds;
			IndexOffsetTable               queryABIndexOffsets;
			IndexOffsetTable               targetABIndexOffsets;
			BitMatrix                      atomEquivMatrix;
			BitMatrix                      bondEquivMatrix;
			AtomQueue                      termQueryAtoms;
			AtomMappingTable               queryAtomMapping;
			BondMappingTable               queryBondMapping;
			Util::BitSet                   queryMappingMask;
			ABMappingMask                  targetMappingMask;
			ABMappingList                  foundMappings;
			UniqueMappingList              uniqueMappings;
			AtomMatchExprTable             atomMatchExprTable;
			BondMatchExprTable             bondMatchExprTable;
			ReactionMatchExprPtr           rxnMatchExpression; 
			IndexList                      postMappingMatchAtoms;
			IndexList                      postMappingMatchBonds;
			MappingCache                   mappingCache;
			bool                           queryChanged;
			bool                           initQueryMappingData;
			bool                           uniqueMatches;
			bool                           saveMappings;
			unsigned int                   enabledRxnRoles;
			std::size_t                    numQueryAtoms;
			std::size_t                    numQueryBonds;
			std::size_t                    numTargetAtoms;
			std::size_t                    numTargetBonds;
			std::size_t                    maxNumMappings;
		};
	}
}

#endif // CDPL_CHEM_REACTIONSUBSTRUCTURESEARCH_HPP
