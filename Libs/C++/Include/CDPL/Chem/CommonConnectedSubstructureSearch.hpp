/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CommonConnectedSubstructureSearch.hpp 
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
 * \brief Definition of the class CDPL::Chem::CommonConnectedSubstructureSearch.
 */

#ifndef CDPL_CHEM_COMMONCONNECTEDSUBSTRUCTURESEARCH_HPP
#define CDPL_CHEM_COMMONCONNECTEDSUBSTRUCTURESEARCH_HPP

#include <vector>
#include <deque>
#include <set>
#include <cstddef>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Util/BitSet.hpp"


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
		 * \brief CommonConnectedSubstructureSearch.
		 * \see [\ref MCSA]
		 */
		class CDPL_CHEM_API CommonConnectedSubstructureSearch
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
			 * \brief Constructs and initializes a \c %CommonConnectedSubstructureSearch instance.
			 */
			CommonConnectedSubstructureSearch();

			/**
			 * \brief Constructs and initializes a \c %CommonConnectedSubstructureSearch instance for the specified query structure.
			 * \param query A molecular graph that represents the query structure.
			 */
			CommonConnectedSubstructureSearch(const MolecularGraph& query);
			
			/**
			 * \brief Destructor.
			 *
			 * Destroys the \c %CommonConnectedSubstructureSearch instance and frees all allocated resources.
			 */
			~CommonConnectedSubstructureSearch();

			/**
			 * \brief Allows to specify a new query structure.
			 * \param query A molecular graph that represents the query structure.
			 */
			void setQuery(const MolecularGraph& query);

			/**
			 * \brief Searches for a common connected substructure between the query and the specified target molecular graph.
			 *
			 * The method does not store any atom/bond mappings between query and target substructures - it just tells
			 * if a valid common substructure mapping solution involving at least getMinSubstructureSize() atoms could be found. If you need
			 * access to the atom/bond mappings, use findAllMappings() or findMaxMappings() instead.
			 *
			 * \param target The molecular graph that has to be searched for a connected substructure in common with the query.
			 * \return \c true if a common substructure of at least the minimum accepted size could be found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxMappings() will be
			 *       discarded.
			 */		
			bool mappingExists(const MolecularGraph& target);

			/**
			 * \brief Searches for all possible atom/bond mappings of connected query subgraphs to substructures of
			 *        the specified target molecular graph.
			 *
			 * The method will store all found common substructure mapping solutions involving at least getMinSubstructureSize() atoms up to
			 * the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be
			 * stored (see uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
			 *
			 * \param target The molecular graph that has to be searched for all connected substructures in common with the query.
			 * \return \c true if common substructures of at least the minimum accepted size were found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxMappings() will be
			 *       discarded.
			 */
			bool findAllMappings(const MolecularGraph& target);

			/**
			 * \brief Searches for all maximum-sized atom/bond mappings of connected query subgraphs to substructures of
			 *        the specified target molecular graph.
			 *
			 * The method will store all maximum-sized common substructure mapping solutions involving at least getMinSubstructureSize() atoms up to
			 * the maximum number of recorded mappings specified by setMaxNumMappings(). If only unique mappings have to be stored (see
			 * uniqueMappingsOnly(bool unique)), any duplicates of previously found mappings will be discarded.
			 *
			 * \param target The molecular graph that has to be searched for all maximum-sized connected substructures in common with the query.
			 * \return \c true if common substructures of at least the minimum accepted size were found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findAllMappings() or findMaxMappings() will be
			 *       discarded.
			 */
			bool findMaxMappings(const MolecularGraph& target);

			/**
			 * \brief Returns the number of atom/bond mappings that were recorded in the last search for common substructures.
			 * \return The number of atom/bond mappings that were recorded in the last search for common substructures.
			 * \see findAllMappings(), findMaxMappings()
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
			 * In a call to findAllMappings or findMaxMappings() the common substructure search will terminate as soon as the specified
			 * maximum number of stored atom/bond mappings has been reached. A previously set limit on the number of mappings can
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
			 * Any found common substructures which cover less than \a min_size atoms are not accepted as a valid
			 * solution and will be discarded.
			 *
			 * \param min_size The minimum accepted common substructure size in number of atoms.
			 * \note By default, the minimum common substructure size is set to zero.
			 */
			void setMinSubstructureSize(std::size_t min_size);

			/**
			 * \brief Returns the minimum accepted common substructure size.
			 * \return The minimum accepted common substructure size in number of atoms.
			 * \see setMinSubstructureSize()
			 */
			std::size_t getMinSubstructureSize() const;

		private:
			CommonConnectedSubstructureSearch(const CommonConnectedSubstructureSearch&);

			CommonConnectedSubstructureSearch& operator=(const CommonConnectedSubstructureSearch&);

			bool init(const MolecularGraph&);

			void initMatchExpressions();

			bool findEquivAtoms();
			bool findEquivBonds();

			bool mapAtoms();
			bool mapAtoms(std::size_t);
			bool mapAtoms(std::size_t, std::size_t);

			bool nextTargetAtom(std::size_t, std::size_t&, std::size_t&) const;

			bool mappingFound();

			bool hasPostMappingMatchExprs() const;
			bool foundMappingMatches(const AtomBondMapping*) const;

			bool foundMappingUnique();
			bool mappingAlreadySeen(const AtomBondMapping*) const;

			void clearMappings();
			void freeAtomBondMappings();

			AtomBondMapping* createAtomBondMapping();
			void freeAtomBondMapping();

			class ABMappingMask {

			public:
				void initQueryAtomMask(std::size_t);
				void initTargetAtomMask(std::size_t);

				void initQueryBondMask(std::size_t);
				void initTargetBondMask(std::size_t);

				void setQueryAtomBit(std::size_t);
				void setTargetAtomBit(std::size_t);

				void resetQueryAtomBit(std::size_t);
				void resetTargetAtomBit(std::size_t);

				bool testTargetAtomBit(std::size_t) const;

				void setQueryBondBit(std::size_t);
				void setTargetBondBit(std::size_t);

				void resetBondMasks();

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
			typedef std::vector<const Atom*> AtomMappingTable;
			typedef std::vector<std::size_t> AtomIndexList;
			typedef std::vector<std::size_t> BondMappingStack;
			typedef std::deque<std::size_t> AtomQueue;
			typedef std::vector<AtomBondMapping::SharedPointer> AllocABMappingList;
			typedef std::set<ABMappingMask> UniqueMappingList;
			typedef std::vector<const Atom*> AtomList;
			typedef std::vector<const Bond*> BondList;
			typedef std::vector<MatchExpression<Atom, MolecularGraph>::SharedPointer> AtomMatchExprTable;
			typedef std::vector<MatchExpression<Bond, MolecularGraph>::SharedPointer> BondMatchExprTable;

			const MolecularGraph*  query;
			const MolecularGraph*  target;
			BitMatrix              atomEquivMatrix;
			BitMatrix              bondEquivMatrix;
			AtomQueue              termQueryAtoms;
			AtomIndexList          termTargetAtoms;
			BondMappingStack       bondMappingStack;
			AtomMappingTable       queryAtomMapping;
			ABMappingMask          mappingMask;
			Util::BitSet           hiddenQueryAtomMask;
			Util::BitSet           termQueryAtomMask;
			Util::BitSet           termTargetAtomMask;
			ABMappingList          foundMappings;
			AllocABMappingList     allocMappings;
			UniqueMappingList      uniqueMappings;
			AtomMatchExprTable     atomMatchExprTable;
			BondMatchExprTable     bondMatchExprTable;
			MolGraphMatchExprPtr   molGraphMatchExpr;
			AtomList               postMappingMatchAtoms;
			BondList               postMappingMatchBonds;
			bool                   queryChanged;
			bool                   initQueryData;
			bool                   uniqueMatches;
			bool                   saveMappings;
			bool                   maxMappingsOnly;
			std::size_t            numQueryAtoms;
			std::size_t            numQueryBonds;
			std::size_t            numTargetAtoms;
			std::size_t            numTargetBonds;
			std::size_t            numMappedAtoms;
			std::size_t            currMaxSubstructureSize;
			std::size_t            maxBondStackSize;
			std::size_t            maxNumMappings;
			std::size_t            minSubstructureSize;
			std::size_t            freeMappingIdx;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_COMMONCONNECTEDSUBSTRUCTURESEARCH_HPP
