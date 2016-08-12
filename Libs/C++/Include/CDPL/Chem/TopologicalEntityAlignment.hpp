/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TopologicalEntityAlignment.hpp 
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
 * \brief Definition of the class CDPL::Chem::TopologicalEntityAlignment.
 */

#ifndef CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP
#define CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP

#include <cstddef>
#include <vector>
#include <set>
#include <utility>

#include <boost/function.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/MultiMap.hpp"
#include "CDPL/Util/BronKerboschAlgorithm.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief TopologicalEntityAlignment.
		 */
		template <typename T>
		class TopologicalEntityAlignment 
		{

		public:
			/**
			 * \brief The actual entity type.
			 */
			typedef T EntityType;

			/**
			 * \brief The container storing the entities to align.
			 */
			typedef std::set<const EntityType*> EntitySet;

			/**
			 * \brief The container storing the entity-mapping of a found alignment solution.
			 */
			typedef Util::MultiMap<const EntityType*, const EntityType*, true> EntityMapping;

			/**
			 * \brief A constant iterator over the stored entities.
			 */
			typedef boost::indirect_iterator<typename EntitySet::const_iterator, const EntityType> ConstEntityIterator;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity match constraint function.
			 */
			typedef boost::function2<bool, const EntityType&, const EntityType&> EntityMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity-pair match constraint function.
			 */
			typedef boost::function4<bool, const EntityType&, const EntityType&, const EntityType&, const EntityType&> EntityPairMatchFunction;

			/**
			 * \brief Constructs the \c %TopologicalEntityAlignment instance.
			 */
			TopologicalEntityAlignment(): changes(true) {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~TopologicalEntityAlignment() {}

			/**
			 * \brief Specifies a function for restricting allowed entity mappings in the search for alignment solutions.
			 * \param func The constraint check function.
			 */
			void setEntityMatchFunction(const EntityMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for restricting allowed entity mappings.
			 * \return The registered constraint check function.
			 */
			const EntityMatchFunction& getEntityMatchFunction() const;
 
			/**
			 * \brief Specifies a function for checking the compatibility of entity-pairs in the search for alignment solutions.
			 * \param func The constraint check function.
			 * \note This function gets only called for pairs with already matching first and second entities.
			 */
			void setEntityPairMatchFunction(const EntityPairMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for checking the compatibility of entity-pairs.
			 * \return The registered constraint check function.
			 */
			const EntityPairMatchFunction& getEntityPairMatchFunction() const;
	 
			/**
			 * \brief Adds an entity to the specified alignment entity set.
			 * \param entity The entity object to add.
			 * \param first_set If \c true, the entity is added to the first entity set, if \c false to the second one.
			 * \note Adding the same entity instance more than once has no effect.
			 */
			void addEntity(const EntityType& entity, bool first_set);

			/**
			 * \brief Removes all entities in the specified alignment entity set.
			 * \param first_set If \c true, the first entity set is cleared, if \c false the second one.
			 */
			void clearEntities(bool first_set);

			/**
			 * \brief Returns the number of entities in the specified alignment entity set.
			 * \param first_set If \c true, the size of first entity set is returned, if \c false the size of the second one.
			 */
			std::size_t getNumEntities(bool first_set) const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the entities stored in the specified set.
			 * \param first_set If \c true, an iterator for first entity set is returned, if \c false for the second one.
			 * \return A constant iterator pointing to the beginning of the entities stored in the specified set.
			 */
			ConstEntityIterator getEntitiesBegin(bool first_set) const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the entities stored in the specified set.
			 * \param first_set If \c true, an iterator for first entity set is returned, if \c false for the second one.
			 * \return A constant iterator pointing to the end of the entities stored in the specified set.
			 */
			ConstEntityIterator getEntitiesEnd(bool first_set) const;

			/*
			 * \brief Resets the internal state and prepares for a new search for entity alignments.
			 * \note If addEntity() or clearEntity() was called before calling nextMapping(), init() gets invoked automatically.
			 */
			void init();

			/**
			 * \brief Searches for the next alignment solution and stores the corresponding mapping of the entities
			 *        in the first set to the entities in the second set in the map provided as an argument.
			 * \param mapping The map where the entitiy mapping of the found alignment solution has to be stored.
			 * \return \c true if a new alignment solution could be found, and \c false otherwise.
			 */
			bool nextAlignment(EntityMapping& mapping);

		private:
			typedef std::pair<const EntityType*, const EntityType*> EntityPair;
			typedef std::vector<EntityPair> EntityPairArray;

			EntityMatchFunction         entityMatchFunc;
			EntityPairMatchFunction     entityPairMatchFunc;
			Util::BronKerboschAlgorithm bkAlgorithm;
			EntityPairArray             compatGraphNodes;
			Util::BitSetArray           adjMatrix;
			Util::BitSet                clique;
			EntitySet                   firstEntities;
			EntitySet                   secondEntities;
			bool                        changes;
		};

		/**
		 * @}
		 */
    }
}


// Implementation

template <typename T>
inline void CDPL::Chem::TopologicalEntityAlignment<T>::setEntityMatchFunction(const EntityMatchFunction& func)
{
	entityMatchFunc = func;
}

template <typename T>
inline const typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityMatchFunction& 
CDPL::Chem::TopologicalEntityAlignment<T>::getEntityMatchFunction() const
{
	return entityMatchFunc; 
}

template <typename T>
inline void CDPL::Chem::TopologicalEntityAlignment<T>::setEntityPairMatchFunction(const EntityPairMatchFunction& func)
{
	entityPairMatchFunc = func;
}

template <typename T>
inline const typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction& 
CDPL::Chem::TopologicalEntityAlignment<T>::getEntityPairMatchFunction() const
{
	return entityPairMatchFunc; 
}

template <typename T>
inline std::size_t CDPL::Chem::TopologicalEntityAlignment<T>::getNumEntities(bool first_set) const  
{
	return (first_set ? firstEntities : secondEntities).size();
}

template <typename T>
inline void CDPL::Chem::TopologicalEntityAlignment<T>::addEntity(const EntityType& entity, bool first_set)
{
	(first_set ? firstEntities : secondEntities).insert(&entity);
	changes = true;
}

template <typename T>
inline void CDPL::Chem::TopologicalEntityAlignment<T>::clearEntities(bool first_set)  
{
	(first_set ? firstEntities : secondEntities).clear();
	changes = true;
}

template <typename T>
inline typename CDPL::Chem::TopologicalEntityAlignment<T>::ConstEntityIterator 
CDPL::Chem::TopologicalEntityAlignment<T>::getEntitiesBegin(bool first_set) const
{
	return (first_set ? firstEntities : secondEntities).begin();
}

template <typename T>
inline typename CDPL::Chem::TopologicalEntityAlignment<T>::ConstEntityIterator 
CDPL::Chem::TopologicalEntityAlignment<T>::getEntitiesEnd(bool first_set) const
{
	return (first_set ? firstEntities : secondEntities).end();
}

template <typename T>
inline void CDPL::Chem::TopologicalEntityAlignment<T>::init()
{
	compatGraphNodes.clear();

	if (entityMatchFunc) {
		for (typename EntitySet::const_iterator it1 = firstEntities.begin(), end1 = firstEntities.end(); it1 != end1; ++it1)
			for (typename EntitySet::const_iterator it2 = secondEntities.begin(), end2 = secondEntities.end(); it2 != end2; ++it2)
				if (entityMatchFunc(**it1, **it2))
					compatGraphNodes.push_back(std::make_pair(*it1, *it2));
	} else {
		for (typename EntitySet::const_iterator it1 = firstEntities.begin(), end1 = firstEntities.end(); it1 != end1; ++it1)
			for (typename EntitySet::const_iterator it2 = secondEntities.begin(), end2 = secondEntities.end(); it2 != end2; ++it2)
				compatGraphNodes.push_back(std::make_pair(*it1, *it2));
	}

	std::size_t num_nodes = compatGraphNodes.size();

	adjMatrix.resize(num_nodes);

	for (std::size_t i = 0; i < num_nodes; i++) {
		adjMatrix[i].resize(num_nodes);
		adjMatrix[i].reset();
	}

	for (std::size_t i = 0; i < num_nodes; i++) {
		const EntityPair& p1 = compatGraphNodes[i];

		for (std::size_t j = i + 1; j < num_nodes; j++) {
			const EntityPair& p2 = compatGraphNodes[j];

			if (p1.first == p2.first)
				continue;

			if (p1.second == p2.second)
				continue;

			if (!entityPairMatchFunc || entityPairMatchFunc(*p1.first, *p1.second, *p2.first, *p2.second)) {
				adjMatrix[i].set(j);
				adjMatrix[j].set(i);
			}
		}
	}

	bkAlgorithm.init(adjMatrix);

	changes = false;
}

template <typename T>
inline bool CDPL::Chem::TopologicalEntityAlignment<T>::nextAlignment(EntityMapping& mapping)
{
	if (changes)
		init();

	if (!bkAlgorithm.nextClique(clique))
		return false;

	mapping.clear();

	for (std::size_t i = clique.find_first(); i != Util::BitSet::npos; i = clique.find_next(i))
		mapping.insertEntry(compatGraphNodes[i]);

	return true;
}

#endif // CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP
