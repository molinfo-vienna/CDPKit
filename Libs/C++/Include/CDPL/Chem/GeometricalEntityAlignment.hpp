/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalEntityAlignment.hpp 
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
 * \brief Definition of the class CDPL::Chem::GeometricalEntityAlignment.
 */

#ifndef CDPL_CHEM_GEOMETRICALENTITYALIGNMENT_HPP
#define CDPL_CHEM_GEOMETRICALENTITYALIGNMENT_HPP

#include <cstddef>
#include <algorithm>

#include <boost/function.hpp>

#include "CDPL/Chem/TopologicalEntityAlignment.hpp"
#include "CDPL/Math/KabschAlgorithm.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief GeometricalEntityAlignment.
		 */
		template <typename T, typename EM>
		class GeometricalEntityAlignment 
		{

			typedef TopologicalEntityAlignment<T, EM> TopologicalAlignment;

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
			 * \brief The container storing the entity-mapping of a found topological alignment solution.
			 */
			typedef typename TopologicalAlignment::EntityMapping EntityMapping;

			/**
			 * \brief A generic wrapper class used to store a user-defined predicate to restrict allowed topological entity alignments.
			 */
			typedef boost::function1<bool, const EntityMapping&> TopologicalAlignmentConstraintFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity 3D-coordinates function.
			 */
			typedef boost::function1<const Math::Vector3D&, const EntityType&> Entity3DCoordinatesFunction;
	
			/**
			 * \brief A generic wrapper class used to store a user-defined entity alignment weight function.
			 */
			typedef boost::function1<double, const EntityType&> EntityWeightFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined topological entity match constraint function.
			 */
			typedef typename TopologicalAlignment::EntityMatchFunction EntityMatchFunction;

			/**
			 * \brief A generic wrapper class used to store a user-defined entity-pair match constraint function.
			 */
			typedef typename TopologicalAlignment::EntityPairMatchFunction EntityPairMatchFunction;

			/**
			 * \brief Constructs the \c %GeometricalEntityAlignment instance.
			 */
			GeometricalEntityAlignment(): minTopMappingSize(3) {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~GeometricalEntityAlignment() {}

			/**
			 * \brief Specifies the minimum number of topologically mapped entities that is required to enable a subsequent
			 *        geometrical alignment.
			 * \param min_size The minimum required number of topologically mapped entities.
			 */
			void setMinTopologicalMappingSize(std::size_t min_size);

			/**
			 * \brief Returns the minimum number of topologically mapped entities that is required to enable a subsequent
			 *        geometrical alignment.
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
			 * \brief Specifies a function for the retrieval of entity weights for geometrical alignment.
			 * \param func The entity weight function.
			 */
			void setEntityWeightFunction(const EntityWeightFunction& func);

			/**
			 * \brief Returns the function that was registered for the retrieval of entity weights for geometrical alignment.
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
			 * \brief Resets the internal state and prepares for a new search for entity alignments.
			 * \note If addEntity() or clearEntity() was called before calling nextAlignment(), init() gets invoked automatically.
			 */
			void init();

			/**
			 * \brief Searches for the next alignment solution.
			 * \return \c true if a new alignment solution could be found, and \c false otherwise.
			 */
			bool nextAlignment();

			/**
			 * \brief Returns the alignment transformation matrix that was calculated in the last successful call to nextAlignment().
			 *
			 * A transformation of the positions of the entities in the second set aligns them geometrically to the topologically mapped
			 * entities in the first set.
			 *
			 * \return The alignment transformation matrix.
			 */
			const Math::Matrix4D& getTransform() const;

		private:
			TopologicalAlignment                   topAlignment;
			EntityMapping                          topEntityMapping;
			TopologicalAlignmentConstraintFunction topAlignConstrFunc;
			Entity3DCoordinatesFunction            coordsFunc;
			EntityWeightFunction                   weightFunc;
			Math::KabschAlgorithm<double>          kabschAlgorithm;
			Math::DMatrix                          refPoints;
			Math::DMatrix                          alignedPoints;
			Math::DVector                          almntWeights;
			Math::Matrix4D                         transform;
			std::size_t                            minTopMappingSize;
		};

		/**
		 * @}
		 */
    }
}


// Implementation

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setMinTopologicalMappingSize(std::size_t min_size)
{
	minTopMappingSize = min_size;
}

template <typename T, typename EM>
std::size_t CDPL::Chem::GeometricalEntityAlignment<T, EM>::getMinTopologicalMappingSize()
{
	return minTopMappingSize;
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setEntity3DCoordinatesFunction(const Entity3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

template <typename T, typename EM>
const typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::Entity3DCoordinatesFunction& 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntity3DCoordinatesFunction() const
{
	return coordsFunc; 
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setEntityWeightFunction(const EntityWeightFunction& func)
{
	weightFunc = func;
}

template <typename T, typename EM>
const typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::EntityWeightFunction& 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntityWeightFunction() const
{
	return weightFunc; 
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setTopAlignmentConstraintFunction(const TopologicalAlignmentConstraintFunction& func)
{
	topAlignConstrFunc = func;
}

template <typename T, typename EM>
const typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::TopologicalAlignmentConstraintFunction& 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getTopAlignmentConstraintFunction() const
{
	return topAlignConstrFunc; 
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setEntityMatchFunction(const EntityMatchFunction& func)
{
	topAlignment.setEntityMatchFunction(func);
}

template <typename T, typename EM>
const typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::EntityMatchFunction& 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntityMatchFunction() const
{
	return topAlignment.getEntityMatchFunction();
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::setEntityPairMatchFunction(const EntityPairMatchFunction& func)
{
	topAlignment.setEntityPairMatchFunction(func);
}

template <typename T, typename EM>
const typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::EntityPairMatchFunction& 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntityPairMatchFunction() const
{
	return topAlignment.getEntityPairMatchFunction();
}

template <typename T, typename EM>
std::size_t CDPL::Chem::GeometricalEntityAlignment<T, EM>::getNumEntities(bool first_set) const  
{
	return topAlignment.getNumEntities(first_set);
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::addEntity(const EntityType& entity, bool first_set)
{
	topAlignment.addEntity(entity, first_set);
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::clearEntities(bool first_set)  
{
	topAlignment.clearEntities(first_set);
}

template <typename T, typename EM>
typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::ConstEntityIterator 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntitiesBegin(bool first_set) const
{
	return topAlignment.getEntitiesBegin(first_set);
}

template <typename T, typename EM>
typename CDPL::Chem::GeometricalEntityAlignment<T, EM>::ConstEntityIterator 
CDPL::Chem::GeometricalEntityAlignment<T, EM>::getEntitiesEnd(bool first_set) const
{
	return topAlignment.getEntitiesEnd(first_set);
}

template <typename T, typename EM>
void CDPL::Chem::GeometricalEntityAlignment<T, EM>::init()
{
	topAlignment.init();
}

template <typename T, typename EM>
bool CDPL::Chem::GeometricalEntityAlignment<T, EM>::nextAlignment()
{
	if (!coordsFunc)
		return false;

	while (topAlignment.nextAlignment(topEntityMapping)) {
		std::size_t num_points = topEntityMapping.getSize();

		if (num_points < minTopMappingSize)
			continue;

		if (topAlignConstrFunc && !topAlignConstrFunc(topEntityMapping))
			continue;

		refPoints.resize(3, num_points, false);
		alignedPoints.resize(3, num_points, false);

		if (weightFunc)
			almntWeights.resize(num_points, 1.0);

		std::size_t i = 0;

		for (typename EntityMapping::ConstEntryIterator it = topEntityMapping.getEntriesBegin(), end = topEntityMapping.getEntriesEnd();
			 it != end; ++it, i++) {

			column(refPoints, i) = coordsFunc(*it->first);
			column(alignedPoints, i) = coordsFunc(*it->second);

			if (weightFunc)
				almntWeights(i) = std::max(weightFunc(*it->first), weightFunc(*it->second));
		}

		if (!weightFunc) {
			if (!kabschAlgorithm.align(alignedPoints, refPoints))
				continue;

		} else if (!kabschAlgorithm.align(alignedPoints, refPoints, almntWeights))
			continue;

		transform.assign(kabschAlgorithm.getTransform());

		return true;
	}

	return false;
}

template <typename T, typename EM>
const CDPL::Math::Matrix4D& CDPL::Chem::GeometricalEntityAlignment<T, EM>::getTransform() const 
{
	return transform;
}

#endif // CDPL_CHEM_GEOMETRICALENTITYALIGNMENT_HPP
