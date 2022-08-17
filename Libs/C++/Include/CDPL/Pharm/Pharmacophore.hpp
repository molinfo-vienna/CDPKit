/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Pharmacophore.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2016 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::Pharmacophore.
 */

#ifndef CDPL_PHARM_PHARMACOPHORE_HPP
#define CDPL_PHARM_PHARMACOPHORE_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \brief Pharmacophore.
		 */
		class CDPL_PHARM_API Pharmacophore : public FeatureContainer
		{

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %Pharmacophore instances.
			 */
			typedef boost::shared_ptr<Pharmacophore> SharedPointer;

			/**
			 * \brief A constant random access iterator used to iterate over the stored \c const Pharm::Feature objects.
			 */
			typedef FeatureContainer::ConstFeatureIterator ConstFeatureIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored Pharm::Feature objects.
			 */
			typedef FeatureContainer::FeatureIterator FeatureIterator;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Pharmacophore() {}

			using FeatureContainer::getFeaturesBegin;
			using FeatureContainer::getFeaturesEnd;

			/**
			 * \brief Removes all features and clears all properties of the pharmacophore.
			 */
			virtual void clear() = 0;
		
			/**
			 * \brief Returns the number of pharmacophore features.
			 * \return The number of features.
			 */
			virtual std::size_t getNumFeatures() const = 0;

			/**
			 * \brief Returns a \c const reference to the pharmacophore feature at index \a idx.
			 * \param idx The zero-based index of the feature to return.
			 * \return A \c const reference to the feature at the specified index.
			 * \throw Base::IndexError if the number of pharmacophore features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
			 */
			virtual const Feature& getFeature(std::size_t idx) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the pharmacophore feature at index \a idx.
			 * \param idx The zero-based index of the feature to return.
			 * \return A non-\c const reference to the feature at the specified index.
			 * \throw Base::IndexError if the number of featuress is zero or \a idx is not in the range [0, getNumFeatures() - 1].
			 */
			virtual Feature& getFeature(std::size_t idx) = 0;

			/**
			 * \brief Creates a new pharmacophore feature and adds it to the pharmacophore.
			 * \return A reference to the newly created features.
			 */
			virtual Feature& addFeature() = 0;
	
			/**
			 * \brief Removes the pharmacophore feature at the specified index.
			 * \param idx The index of the feature to remove.
			 * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
			 */
			virtual void removeFeature(std::size_t idx) = 0;

			/**
			 * \brief Removes the pharmacophore feature specified by the iterator \a it.
			 * \param it An iterator that specifies the feature to remove.
			 * \return A mutable iterator pointing to the next feature in the list.
			 * \throw Base::RangeError if the number of features is zero or \a it is not in the range
			 *        [getFeaturesBegin(), getFeaturesEnd() - 1].
			 */
			FeatureIterator removeFeature(const FeatureIterator& it);

			/**
			 * \brief Returns the index of the specified feature in this pharmacophore.
			 * \param feature The feature instance for which to return the index.
			 * \return The zero-based index of the specified feature instance.
			 * \throw Base::ItemNotFound if the specified feature instance could not be found.
			 */
			virtual std::size_t getFeatureIndex(const Feature& feature) const = 0;

			/**
			 * \brief Tells whether the specified feature instance is stored in this pharmacophore.
			 * \param feature The feature to look for.
			 * \return \c true if \a feature is stored in the pharmacophore, and \c false otherwise.
			 */
			virtual bool containsFeature(const Feature& feature) const = 0;

			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the pharmacophore \a pharm.
			 * \param pharm The pharmacophore to copy.
			 */
			virtual void copy(const Pharmacophore& pharm) = 0;

			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the feature container \a cntnr.
			 * \param cntnr The Pharm::FeatureContainer instance providing the features and properties to copy.
			 */
			virtual void copy(const FeatureContainer& cntnr) = 0;
		
			/**
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        pharmacophore \a pharm.
			 * \param pharm The pharmacophore providing the features to append.
			 * \note Does not affect any properties.
			 */
			virtual void append(const Pharmacophore& pharm) = 0;

			/**
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        feature container \a cntnr.
			 * \param cntnr The pharmacophore providing the features to append.
			 * \note Does not affect any properties.
			 */
			virtual void append(const FeatureContainer& cntnr) = 0;

			/**
			 * \brief Creates a copy of the current pharmacophore state.
			 * \return A smart pointer to the copy of the pharmacophore.
			 */
			virtual SharedPointer clone() const = 0;

			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the pharmacophore \a pharm.
			 *
			 * Internally calls copy() to perform the actual work.
			 *
			 * \param pharm The pharmacophore to copy.
			 * \return A reference to itself.
			 */
			Pharmacophore& operator=(const Pharmacophore& pharm);

			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the feature container \a cntnr.
			 *
			 * Internally calls copy() to perform the actual work.
			 *
			 * \param cntnr The Pharm::FeatureContainer instance providing the features and properties to copy.
			 * \return A reference to itself.
			 */
			Pharmacophore& operator=(const FeatureContainer& cntnr);

			/**
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        pharmacophore \a pharm.
			 *
			 * Internally calls append() to perform the actual work.
			 *
			 * \param pharm The pharmacophore providing the features to append.
			 * \return A reference to itself.
			 */
			Pharmacophore& operator+=(const Pharmacophore& pharm);

			/**
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        feature container \a cntnr.
			 *
			 * Internally calls append() to perform the actual work.
			 *
			 * \param cntnr The Pharm::FeatureContainer instance providing the features to append.
			 * \return A reference to itself.
			 */
			Pharmacophore& operator+=(const FeatureContainer& cntnr);
		};
    }
}

#endif // CDPL_PHARM_PHARMACOPHORE_HPP
