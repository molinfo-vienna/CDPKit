/* 
 * TopologicalEntityAlignment.hpp 
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
 * \brief Definition of the class CDPL::Chem::TopologicalEntityAlignment.
 */

#ifndef CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP
#define CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP

#include <cstddef>
#include <vector>
#include <functional>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Util/BronKerboschAlgorithm.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Chem
    {

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
            typedef std::vector<const EntityType*> EntitySet;

            /**
             * \brief A constant iterator over the stored entities.
             */
            typedef boost::indirect_iterator<typename EntitySet::const_iterator, const EntityType> ConstEntityIterator;

            /**
             * \brief A generic wrapper class used to store a user-defined entity match constraint function.
             */
            typedef std::function<bool(const EntityType&, const EntityType&)> EntityMatchFunction;

            /**
             * \brief A generic wrapper class used to store a user-defined entity-pair match constraint function.
             */
            typedef std::function<bool(const EntityType&, const EntityType&, const EntityType&, const EntityType&)> EntityPairMatchFunction;

            /**
             * \brief Constructs the \c %TopologicalEntityAlignment instance.
             */
            TopologicalEntityAlignment():
                changes(true) {}

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

            /**
             * \brief Returns a non-\c const reference to the stored entity at index \a idx in the specified set.
             * \param idx The zero-based index of the entity instance to return.
             * \param first_set \c true, if the entity to return is stored in the first set. \c false, if stored in the second set.
             * \return A non-\c const reference to the entity stored at index \a idx in the specified set.
             * \throw Base::IndexError if the number of entities in the specified set is zero or \a idx is not in the range [0, getNumEntities() - 1].
             */
            const EntityType& getEntity(std::size_t idx, bool first_set) const;

            /**
             * \brief Searches for the next alignment solution and stores the corresponding mapping of the entities
             *        in the first set to the entities in the second set in the map provided as an argument.
             * \param mapping The map where the entitiy mapping of the found alignment solution has to be stored.
             * \return \c true if a new alignment solution could be found, and \c false otherwise.
             */
            bool nextAlignment(Util::STPairArray& mapping);

            void reset();

          private:
            void init();

            typedef std::vector<Util::STPair> CompatGraphNodeArray;

            EntityMatchFunction         entityMatchFunc;
            EntityPairMatchFunction     entityPairMatchFunc;
            Util::BronKerboschAlgorithm bkAlgorithm;
            CompatGraphNodeArray        compatGraphNodes;
            Util::BitSetArray           adjMatrix;
            Util::BitSet                clique;
            EntitySet                   firstEntities;
            EntitySet                   secondEntities;
            bool                        changes;
        };
    } // namespace Chem
} // namespace CDPL


// Implementation

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::setEntityMatchFunction(const EntityMatchFunction& func)
{
    entityMatchFunc = func;
    changes         = true;
}

template <typename T>
const typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityMatchFunction&
CDPL::Chem::TopologicalEntityAlignment<T>::getEntityMatchFunction() const
{
    return entityMatchFunc;
}

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::setEntityPairMatchFunction(const EntityPairMatchFunction& func)
{
    entityPairMatchFunc = func;
    changes             = true;
}

template <typename T>
const typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction&
CDPL::Chem::TopologicalEntityAlignment<T>::getEntityPairMatchFunction() const
{
    return entityPairMatchFunc;
}

template <typename T>
std::size_t CDPL::Chem::TopologicalEntityAlignment<T>::getNumEntities(bool first_set) const
{
    return (first_set ? firstEntities : secondEntities).size();
}

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::addEntity(const EntityType& entity, bool first_set)
{
    (first_set ? firstEntities : secondEntities).push_back(&entity);
    changes = true;
}

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::clearEntities(bool first_set)
{
    (first_set ? firstEntities : secondEntities).clear();
    changes = true;
}

template <typename T>
typename CDPL::Chem::TopologicalEntityAlignment<T>::ConstEntityIterator
CDPL::Chem::TopologicalEntityAlignment<T>::getEntitiesBegin(bool first_set) const
{
    return (first_set ? firstEntities : secondEntities).begin();
}

template <typename T>
typename CDPL::Chem::TopologicalEntityAlignment<T>::ConstEntityIterator
CDPL::Chem::TopologicalEntityAlignment<T>::getEntitiesEnd(bool first_set) const
{
    return (first_set ? firstEntities : secondEntities).end();
}

template <typename T>
const typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityType&
CDPL::Chem::TopologicalEntityAlignment<T>::getEntity(std::size_t idx, bool first_set) const
{
    const EntitySet& entity_set = (first_set ? firstEntities : secondEntities);

    if (idx >= entity_set.size())
        throw Base::IndexError("TopologicalEntityAlignment: entity index out of bounds");

    return *entity_set[idx];
}

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::init()
{
    compatGraphNodes.clear();

    if (entityMatchFunc) {
        std::size_t i = 0;

        for (typename EntitySet::const_iterator it1 = firstEntities.begin(), end1 = firstEntities.end(); it1 != end1; ++it1, i++) {
            const EntityType* ent1 = *it1;
            std::size_t       j    = 0;

            for (typename EntitySet::const_iterator it2 = secondEntities.begin(), end2 = secondEntities.end(); it2 != end2; ++it2, j++)
                if (entityMatchFunc(*ent1, **it2))
                    compatGraphNodes.push_back(Util::STPair(i, j));
        }

    } else {
        for (std::size_t i = 0, num_ents1 = firstEntities.size(); i < num_ents1; i++)
            for (std::size_t j = 0, num_ents2 = secondEntities.size(); j < num_ents2; j++)
                compatGraphNodes.push_back(Util::STPair(i, j));
    }

    std::size_t num_nodes = compatGraphNodes.size();

    adjMatrix.resize(num_nodes);

    for (std::size_t i = 0; i < num_nodes; i++) {
        adjMatrix[i].resize(num_nodes);
        adjMatrix[i].reset();
    }

    for (std::size_t i = 0; i < num_nodes; i++) {
        const Util::STPair& p1 = compatGraphNodes[i];

        for (std::size_t j = i + 1; j < num_nodes; j++) {
            const Util::STPair& p2 = compatGraphNodes[j];

            if (p1.first == p2.first)
                continue;

            if (p1.second == p2.second)
                continue;

            if (!entityPairMatchFunc || entityPairMatchFunc(*firstEntities[p1.first], *firstEntities[p2.first],
                                                            *secondEntities[p1.second], *secondEntities[p2.second])) {
                adjMatrix[i].set(j);
                adjMatrix[j].set(i);
            }
        }
    }

    bkAlgorithm.init(adjMatrix);

    changes = false;
}

template <typename T>
bool CDPL::Chem::TopologicalEntityAlignment<T>::nextAlignment(Util::STPairArray& mapping)
{
    if (changes)
        init();

    if (!bkAlgorithm.nextClique(clique))
        return false;

    mapping.clear();

    for (std::size_t i = clique.find_first(); i != Util::BitSet::npos; i = clique.find_next(i))
        mapping.addElement(compatGraphNodes[i]);

    return true;
}

template <typename T>
void CDPL::Chem::TopologicalEntityAlignment<T>::reset()
{
    changes = true;
}

#endif // CDPL_CHEM_TOPOLOGICALENTITYALIGNMENT_HPP
