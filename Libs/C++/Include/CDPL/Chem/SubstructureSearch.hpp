/* 
 * SubstructureSearch.hpp 
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
 * \brief Definition of the class CDPL::Chem::SubstructureSearch.
 */

#ifndef CDPL_CHEM_SUBSTRUCTURESEARCH_HPP
#define CDPL_CHEM_SUBSTRUCTURESEARCH_HPP

#include <vector>
#include <deque>
#include <set>
#include <cstddef>
#include <unordered_map>
#include <memory>
#include <functional>

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
         * \brief SubstructureSearch.
         * \see [\ref VFLIB2]
         */
        class CDPL_CHEM_API SubstructureSearch
        {

            typedef std::vector<AtomBondMapping*> ABMappingList;

            typedef MatchExpression<MolecularGraph>::SharedPointer MolGraphMatchExprPtr;
            typedef MatchExpression<Atom, MolecularGraph>::SharedPointer AtomMatchExprPtr;
            typedef MatchExpression<Bond, MolecularGraph>::SharedPointer BondMatchExprPtr;

          public:
            typedef std::shared_ptr<SubstructureSearch> SharedPointer;

            /**
             * \brief A mutable random access iterator used to iterate over the stored atom/bond mapping objects.
             */
            typedef boost::indirect_iterator<ABMappingList::iterator, AtomBondMapping> MappingIterator;

            /**
             * \brief A constant random access iterator used to iterate over the stored atom/bond mapping objects.
             */
            typedef boost::indirect_iterator<ABMappingList::const_iterator, const AtomBondMapping> ConstMappingIterator;

            typedef std::function<const AtomMatchExprPtr&(const Atom&)> AtomMatchExpressionFunction;
            typedef std::function<const BondMatchExprPtr&(const Bond&)> BondMatchExpressionFunction;
            typedef std::function<const MolGraphMatchExprPtr&(const MolecularGraph&)> MolecularGraphMatchExpressionFunction;

            /**
             * \brief Constructs and initializes a \c %SubstructureSearch instance.
             */
            SubstructureSearch();

            /**
             * \brief Constructs and initializes a \c %SubstructureSearch instance for the specified query structure.
             * \param query A molecular graph that represents the query structure.
             */
            SubstructureSearch(const MolecularGraph& query);
            
            /**
             * \brief Destructor.
             *
             * Destroys the \c %SubstructureSearch instance and frees all allocated resources.
             */
            ~SubstructureSearch();

            void setAtomMatchExpressionFunction(const AtomMatchExpressionFunction& func);

            void setBondMatchExpressionFunction(const BondMatchExpressionFunction& func);

            void setMolecularGraphMatchExpressionFunction(const MolecularGraphMatchExpressionFunction& func);

            /**
             * \brief Allows to specify a new query structure.
             * \param query A molecular graph that represents the query structure.
             */
            void setQuery(const MolecularGraph& query);

            /**
             * \brief Tells whether the query structure matches a substructure of the specified target molecular graph.
             *
             * The method does not store any atom/bond mappings between the query and target structure - it just tells
             * if a complete mapping of the query is possible. If you need access to the atom/bond mappings, use findMappings()
             * instead.
             *
             * \param target The molecular graph that has to be searched for a match of the query structure.
             * \return \c true if the query matches a substructure of the target molecular graph, and \c false otherwise.
             * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
             *       discarded.
             */
            bool mappingExists(const MolecularGraph& target);

            /**
             * \brief Searches for all possible atom/bond mappings of the query structure to substructures of the specified target
             *        molecular graph.
             *
             * The method will store all found subgraph mapping solutions up to the maximum number of recorded mappings specified
             * by setMaxNumMappings(). If only unique mappings have to be stored (see uniqueMappingsOnly(bool unique)), any duplicates of
             * previously found mappings will be discarded.
             *
             * \param target The molecular graph that has to be searched for matches of the query structure.
             * \return \c true if the query matches at least one substructure of the specified target molecular graph, and \c false
             *         otherwise.
             * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
             *       discarded.
             */
            bool findMappings(const MolecularGraph& target);

            void stopSearch();
            
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
             * A mapping of the query pattern to a substructure of the target molecular graph is considered to be unique if it differs
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
             * In a call to findMappings() the substructure search will terminate as soon as the specified maximum number of stored
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
             * \brief Adds a constraint on the allowed mappings between query and target structure atoms.
             *
             * By default, an atom of the query structure is free to match any suitable target structure atom. When this method gets
             * called for a particular query/target atom pair (specified by \a query_atom_idx and \a target_atom_idx), future substructure
             * searches will find only those subgraph mapping solutions (if any) where the given query atom maps to the specified
             * target structure atom. Multiple calls to addMappingConstraint() for the same query atom have an additive effect and allow
             * to restrict the valid query atom mappings not only to a single but also a larger set of target structure
             * atoms.
             *
             * \param query_atom_idx The index of the query structure atom.
             * \param target_atom_idx The index of the target structure atom that has to be matched by the query atom.
             */
            void addAtomMappingConstraint(std::size_t query_atom_idx, std::size_t target_atom_idx);

            /**
             * \brief Clears all previously defined query to target atom mapping constraints.
             * \see addAtomMappingConstraint()
             */
            void clearAtomMappingConstraints();

            /**
             * \brief Adds a constraint on the allowed mappings between query and target structure bonds.
             *
             * By default, a bond of the query structure is free to match any suitable target structure bond. When this method gets
             * called for a particular query/target bond pair (specified by \a query_bond_idx and \a target_bond_idx), future substructure
             * searches will find only those subgraph mapping solutions (if any) where the given query bond maps to the specified
             * target structure bond. Multiple calls to addMappingConstraint() for the same query bond have an additive effect and allow
             * to restrict the valid query bond mappings not only to a single but also a larger set of target structure
             * bonds.
             *
             * \param query_bond_idx The index of the query structure bond.
             * \param target_bond_idx The index of the target structure bond that has to be matched by the query bond.
             */
            void addBondMappingConstraint(std::size_t query_bond_idx, std::size_t target_bond_idx);

            /**
             * \brief Clears all previously defined query to target bond mapping constraints.
             * \see addBondMappingConstraint()
             */
            void clearBondMappingConstraints();

        private:
            SubstructureSearch(const SubstructureSearch&);

            SubstructureSearch& operator=(const SubstructureSearch&);

            bool init(const MolecularGraph&);

            void initMatchExpressions();

            bool findEquivAtoms();
            bool findEquivBonds();

            bool mapAtoms();

            std::size_t nextQueryAtom() const;
            bool nextTargetAtom(std::size_t, std::size_t&, std::size_t&) const;

            bool atomMappingAllowed(std::size_t, std::size_t) const;
            bool checkAtomMappingConstraints(std::size_t, std::size_t) const;
            bool checkBondMappingConstraints(std::size_t, std::size_t) const;

            bool mapBonds(std::size_t, std::size_t);
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

            typedef std::vector<Util::BitSet> BitMatrix;
            typedef std::vector<const Atom*> AtomMappingTable;
            typedef std::vector<const Bond*> BondMappingTable;
            typedef std::deque<std::size_t> AtomQueue;
            typedef std::set<ABMappingMask> UniqueMappingList;
            typedef std::vector<const Atom*> AtomList;
            typedef std::vector<const Bond*> BondList;
            typedef std::vector<AtomMatchExprPtr> AtomMatchExprTable;
            typedef std::vector<BondMatchExprPtr> BondMatchExprTable;
            typedef std::unordered_multimap<std::size_t, std::size_t> MappingConstraintMap;
            typedef Util::ObjectStack<AtomBondMapping> MappingCache;

            const MolecularGraph*                 query;
            const MolecularGraph*                 target;
            AtomMatchExpressionFunction           atomMatchExprFunc;
            BondMatchExpressionFunction           bondMatchExprFunc;
            MolecularGraphMatchExpressionFunction molGraphMatchExprFunc;
            BitMatrix                             atomEquivMatrix;
            BitMatrix                             bondEquivMatrix;
            MappingConstraintMap                  atomMappingConstrs;
            MappingConstraintMap                  bondMappingConstrs;
            AtomQueue                             termQueryAtoms;
            AtomMappingTable                      queryAtomMapping;
            BondMappingTable                      queryBondMapping;
            Util::BitSet                          queryMappingMask;
            ABMappingMask                         targetMappingMask;
            ABMappingList                         foundMappings;
            UniqueMappingList                     uniqueMappings;
            AtomMatchExprTable                    atomMatchExprTable;
            BondMatchExprTable                    bondMatchExprTable;
            MolGraphMatchExprPtr                  molGraphMatchExpr;
            AtomList                              postMappingMatchAtoms;
            BondList                              postMappingMatchBonds;
            MappingCache                          mappingCache;
            bool                                  queryChanged;
            bool                                  initQueryData;
            bool                                  uniqueMatches;
            bool                                  saveMappings;
            bool                                  exitSearch;
            std::size_t                           numQueryAtoms;
            std::size_t                           numQueryBonds;
            std::size_t                           numTargetAtoms;
            std::size_t                           numTargetBonds;
            std::size_t                           numMappedAtoms;
            std::size_t                           maxNumMappings;
        };
    }
}

#endif // CDPL_CHEM_SUBSTRUCTURESEARCH_HPP
