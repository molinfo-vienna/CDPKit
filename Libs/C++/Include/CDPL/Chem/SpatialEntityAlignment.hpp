/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpatialEntityAlignment.hpp 
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
 * \brief Definition of the class CDPL::Chem::SpatialEntityAlignment.
 */

#ifndef CDPL_CHEM_SPATIALENTITYALIGNMENT_HPP
#define CDPL_CHEM_SPATIALENTITYALIGNMENT_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional>

#include <boost/functional/hash.hpp>

#include "CDPL/Chem/TopologicalEntityAlignment.hpp"
#include "CDPL/Math/KabschAlgorithm.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \brief SpatialEntityAlignment.
		 */
		template <typename T>
		class SpatialEntityAlignment 
		{

			typedef TopologicalEntityAlignment<T> TopologicalAlignment;

		public:
			/**
			 * \brief The actual entity type.
			 */
			typedef T EntityType;

			/**
			 * \brief A constant iterator over the stored entities.
			 */
			typedef typename TopologicalAlignment::ConstEntityIterator ConstEntityIterator;

			/**
			 * \brief A generic wrapper class used to store a user-defined predicate to restrict allowed topological entity alignments.
			 */
			typedef std::function<bool(const Util::STPairArray&)> TopologicalAlignmentConstraintFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity 3D-coordinates function.
			 */
			typedef std::function<const Math::Vector3D&(const EntityType&)> Entity3DCoordinatesFunction;
	
			/**
			 * \brief A generic wrapper class used to store a user-defined entity alignment weight function.
			 */
			typedef std::function<double(const EntityType&)> EntityWeightFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined topological entity match constraint function.
			 */
			typedef typename TopologicalAlignment::EntityMatchFunction EntityMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity-pair match constraint function.
			 */
			typedef typename TopologicalAlignment::EntityPairMatchFunction EntityPairMatchFunction;

			/**
			 * \brief Constructs the \c %SpatialEntityAlignment instance.
			 */
			SpatialEntityAlignment();

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~SpatialEntityAlignment() {}

			/**
			 * \brief Specifies the minimum number of topologically mapped entities that is required to enable a subsequent
			 *        spatial alignment.
			 * \param min_size The minimum required number of topologically mapped entities.
			 */
			void setMinTopologicalMappingSize(std::size_t min_size);

			/**
			 * \brief Returns the minimum number of topologically mapped entities that is required to enable a subsequent
			 *        spatial alignment.
			 * \return The minimum required number of topologically mapped entities.
			 */
			std::size_t getMinTopologicalMappingSize();

			/**
			 * \brief Specifies a function for the retrieval of entity 3D-coordinates.
			 * \param func The entity 3D-coordinates function.
			 */
			void setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func);

			/**
			 * \brief Returns the function that was registered for the retrieval of entity 3D-coordinates.
			 * \return The registered entity 3D-coordinates function.
			 */
			const Entity3DCoordinatesFunction& getEntity3DCoordinatesFunction() const;
 
			/**
			 * \brief Specifies a function for the retrieval of entity weights for spatial alignment.
			 * \param func The entity weight function.
			 */
			void setEntityWeightFunction(const EntityWeightFunction& func);

			/**
			 * \brief Returns the function that was registered for the retrieval of entity weights for spatial alignment.
			 * \return The registered entity weight function.
			 */
			const EntityWeightFunction& getEntityWeightFunction() const;
 
			/**
			 * \brief Specifies a function for restricting allowed topological entity alignments.
			 * \param func The constraint check function.
			 */
			void setTopAlignmentConstraintFunction(const TopologicalAlignmentConstraintFunction& func);

			/**
			 * \brief Returns the function that was registered for restricting allowed topological entity alignments.
			 * \return The registered constraint check function.
			 */
			const TopologicalAlignmentConstraintFunction& getTopAlignmentConstraintFunction() const;
	
			/**
			 * \brief Specifies a function for restricting allowed topological entity mappings in the search for alignment solutions.
			 * \param func The constraint check function.
			 */
			void setEntityMatchFunction(const EntityMatchFunction& func);

			/**
			 * \brief Returns the function that was registered for restricting allowed topological entity mappings.
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
	 
			void performExhaustiveSearch(bool exhaustive);

			bool exhaustiveSearchPerformed() const;
			
			/**
			 * \brief Adds an entity to the specified alignment entity set.
			 * \param entity The entity object to add.
			 * \param first_set If \c true, the entity is added to the first entity set, if \c false to the second one.
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
			 * \brief Searches for the next alignment solution.
			 * \return \c true if a new alignment solution could be found, and \c false otherwise.
			 */
			bool nextAlignment();

			void reset();
			
			/**
			 * \brief Returns the alignment transformation matrix that was calculated in the last successful call to nextAlignment().
			 *
			 * A transformation of the positions of the entities in the second set aligns them spatially to the topologically mapped
			 * entities in the first set.
			 *
			 * \return The alignment transformation matrix.
			 */
			const Math::Matrix4D& getTransform() const;

			/**
			 * \brief Returns the topological entity mapping resulting from the last successful call to nextAlignment().
			 * \return The topological entity mapping as an array of pairs of entity indices.
			 */
			const Util::STPairArray& getTopologicalMapping() const;

		private:
			void init();

			Util::STPairArray* allocTopMapping();
			
			struct TopMappingCmpFunc
			{

				bool operator()(const Util::STPairArray* m1, const Util::STPairArray* m2) const {
					return (m1->getSize() > m2->getSize());
				}
			};

			struct TopMappingHashFunc
			{

				std::size_t operator()(const Util::STPairArray* m) const {
					return boost::hash_value(m->getData());
				}
			};
	
			struct TopMappingEqCmpFunc
			{

				bool operator()(const Util::STPairArray* m1, const Util::STPairArray* m2) const {
					return (m1->getData() == m2->getData());
				}
			};

			typedef Util::ObjectStack<Util::STPairArray>                                                    TopMappingCache;
			typedef std::vector<Math::Vector3D>                                                             Vector3DArray;
			typedef std::vector<double>                                                                     DoubleArray;
			typedef std::multiset<Util::STPairArray*, TopMappingCmpFunc>                                    TopMappingSet;
			typedef typename TopMappingSet::iterator                                                        TopMappingSetIterator;
			typedef std::unordered_set<const Util::STPairArray*, TopMappingHashFunc, TopMappingEqCmpFunc> TopMappingHashSet;

			TopologicalAlignment                   topAlignment;
			TopMappingSet                          topMappings;
			TopMappingSetIterator                  nextTopMappingIter;
			Util::STPairArray*                     currTopMapping;
			TopologicalAlignmentConstraintFunction topAlignConstrFunc;
			Entity3DCoordinatesFunction            coordsFunc;
			EntityWeightFunction                   weightFunc;
			Math::KabschAlgorithm<double>          kabschAlgorithm;
			Vector3DArray                          firstSetCoords;
			DoubleArray                            firstSetWeights;
			Vector3DArray                          secondSetCoords;
			DoubleArray                            secondSetWeights;
			Math::DMatrix                          refPoints;
			Math::DMatrix                          alignedPoints;
			Math::DVector                          almntWeights;
			Math::Matrix4D                         transform;
			std::size_t                            minTopMappingSize;
			bool                                   changes;
			bool                                   exhaustiveMode;
			TopMappingHashSet                      seenTopMappings;
			TopMappingCache                        topMappingCache;
		};
    }
}


// Implementation

template <typename T>
CDPL::Chem::SpatialEntityAlignment<T>::SpatialEntityAlignment():
	minTopMappingSize(3), changes(true), exhaustiveMode(true), topMappingCache(5000)
{
	currTopMapping = allocTopMapping();
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setMinTopologicalMappingSize(std::size_t min_size)
{
	minTopMappingSize = min_size;
	changes = true;
}

template <typename T>
std::size_t CDPL::Chem::SpatialEntityAlignment<T>::getMinTopologicalMappingSize()
{
	return minTopMappingSize;
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func)
{
	coordsFunc = func;
	changes = true;
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::Entity3DCoordinatesFunction& 
CDPL::Chem::SpatialEntityAlignment<T>::getEntity3DCoordinatesFunction() const
{
	return coordsFunc; 
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setEntityWeightFunction(const EntityWeightFunction& func)
{
	weightFunc = func;
	changes = true;
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::EntityWeightFunction& 
CDPL::Chem::SpatialEntityAlignment<T>::getEntityWeightFunction() const
{
	return weightFunc; 
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setTopAlignmentConstraintFunction(const TopologicalAlignmentConstraintFunction& func)
{
	topAlignConstrFunc = func;
	changes = true;
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::TopologicalAlignmentConstraintFunction& 
CDPL::Chem::SpatialEntityAlignment<T>::getTopAlignmentConstraintFunction() const
{
	return topAlignConstrFunc; 
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setEntityMatchFunction(const EntityMatchFunction& func)
{
	topAlignment.setEntityMatchFunction(func);
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::EntityMatchFunction& 
CDPL::Chem::SpatialEntityAlignment<T>::getEntityMatchFunction() const
{
	return topAlignment.getEntityMatchFunction();
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::setEntityPairMatchFunction(const EntityPairMatchFunction& func)
{
	topAlignment.setEntityPairMatchFunction(func);
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::EntityPairMatchFunction& 
CDPL::Chem::SpatialEntityAlignment<T>::getEntityPairMatchFunction() const
{
	return topAlignment.getEntityPairMatchFunction();
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::performExhaustiveSearch(bool exhaustive)
{
	exhaustiveMode = exhaustive;
	changes = true;
}

template <typename T>
bool CDPL::Chem::SpatialEntityAlignment<T>::exhaustiveSearchPerformed() const
{
	return exhaustiveMode;
}

template <typename T>
std::size_t CDPL::Chem::SpatialEntityAlignment<T>::getNumEntities(bool first_set) const  
{
	return topAlignment.getNumEntities(first_set);
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::addEntity(const EntityType& entity, bool first_set)
{
	topAlignment.addEntity(entity, first_set);
	changes = true;
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::clearEntities(bool first_set)  
{
	topAlignment.clearEntities(first_set);
	changes = true;
}

template <typename T>
typename CDPL::Chem::SpatialEntityAlignment<T>::ConstEntityIterator 
CDPL::Chem::SpatialEntityAlignment<T>::getEntitiesBegin(bool first_set) const
{
	return topAlignment.getEntitiesBegin(first_set);
}

template <typename T>
typename CDPL::Chem::SpatialEntityAlignment<T>::ConstEntityIterator 
CDPL::Chem::SpatialEntityAlignment<T>::getEntitiesEnd(bool first_set) const
{
	return topAlignment.getEntitiesEnd(first_set);
}

template <typename T>
const typename CDPL::Chem::SpatialEntityAlignment<T>::EntityType&
CDPL::Chem::SpatialEntityAlignment<T>::getEntity(std::size_t idx, bool first_set) const
{
	return topAlignment.getEntity(idx, first_set);
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::reset()  
{
	changes = true;
}

template <typename T>
bool CDPL::Chem::SpatialEntityAlignment<T>::nextAlignment()
{
	if (changes)
		init();

	if (firstSetCoords.empty() || secondSetCoords.empty())
		return false;

	bool have_weights = !firstSetWeights.empty();
	std::size_t min_sub_mpg_size = (minTopMappingSize < 3 ? minTopMappingSize : std::size_t(3));
	
	while (nextTopMappingIter != topMappings.end()) {
		currTopMapping = *nextTopMappingIter;

		std::size_t num_points = currTopMapping->getSize();

		refPoints.resize(3, num_points, false);
		alignedPoints.resize(3, num_points, false);
	
		if (have_weights)
			almntWeights.resize(num_points, 1.0);

		std::size_t i = 0;
	
		for (Util::STPairArray::ConstElementIterator it = currTopMapping->getElementsBegin(), end = currTopMapping->getElementsEnd();
			 it != end; ++it, i++) {
		
			std::size_t first_idx = it->first;
			std::size_t sec_idx = it->second;			
			
			column(refPoints, i) = firstSetCoords[first_idx];
			column(alignedPoints, i) = secondSetCoords[sec_idx];

			if (have_weights)
				almntWeights(i) = std::max(firstSetWeights[first_idx], secondSetWeights[sec_idx]);
		}

		if (exhaustiveMode && (num_points > min_sub_mpg_size)) {
			Util::STPairArray* sub_mpg = 0;
			
			for (std::size_t j = 0; j < num_points; j++) {
				if (!sub_mpg)
					sub_mpg = allocTopMapping();

				sub_mpg->clear();

				for (std::size_t k = 0; k < num_points; k++)
					if (k != j)
						sub_mpg->addElement(currTopMapping->getElement(k));

				if (!seenTopMappings.insert(sub_mpg).second) {
					continue;
				}
				
				topMappings.insert(sub_mpg);
				sub_mpg = 0;
			}

			if (sub_mpg)
				topMappingCache.put();
		}

		if (!have_weights) {
			if (!kabschAlgorithm.align(alignedPoints, refPoints)) {
				++nextTopMappingIter;
				continue;
			}
			
		} else if (!kabschAlgorithm.align(alignedPoints, refPoints, almntWeights)) {
			++nextTopMappingIter;
			continue;
		}
		
		transform.assign(kabschAlgorithm.getTransform());
		++nextTopMappingIter;
		
		return true;
	}

	return false;
}

template <typename T>
const CDPL::Math::Matrix4D& CDPL::Chem::SpatialEntityAlignment<T>::getTransform() const 
{
	return transform;
}

template <typename T>
const CDPL::Util::STPairArray&  
CDPL::Chem::SpatialEntityAlignment<T>::getTopologicalMapping() const
{
	return *currTopMapping;
}

template <typename T>
void CDPL::Chem::SpatialEntityAlignment<T>::init()
{
	firstSetCoords.clear();
	secondSetCoords.clear();	

	firstSetWeights.clear();
	secondSetWeights.clear();	

	if (coordsFunc) {
		for (ConstEntityIterator it = getEntitiesBegin(true), end = getEntitiesEnd(true); it != end; ++it) {
			const EntityType& entity = *it;

			firstSetCoords.push_back(coordsFunc(entity));
		
			if (weightFunc)
				firstSetWeights.push_back(weightFunc(entity));
		}
	
		for (ConstEntityIterator it = getEntitiesBegin(false), end = getEntitiesEnd(false); it != end; ++it) {
			const EntityType& entity = *it;

			secondSetCoords.push_back(coordsFunc(entity));
		
			if (weightFunc)
				secondSetWeights.push_back(weightFunc(entity));
		}
	}

	topAlignment.reset();
	topMappingCache.putAll();
	seenTopMappings.clear();
	topMappings.clear();
	
	currTopMapping = allocTopMapping();

	while (topAlignment.nextAlignment(*currTopMapping)) {
		if (currTopMapping->getSize() < minTopMappingSize)
			continue;
		
		if (topAlignConstrFunc && !topAlignConstrFunc(*currTopMapping))
			continue;

		topMappings.insert(currTopMapping);
		currTopMapping = allocTopMapping();
	}

	currTopMapping->clear();
	
	nextTopMappingIter = topMappings.begin();
	changes = false;
}

template <typename T>
CDPL::Util::STPairArray*
CDPL::Chem::SpatialEntityAlignment<T>::allocTopMapping()
{
	return topMappingCache.getRaw();
}

#endif // CDPL_CHEM_SPATIALENTITYALIGNMENT_HPP
