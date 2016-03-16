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
 * \brief Definition of the class CDPL::Chem::Pharmacophore.
 */

#ifndef CDPL_CHEM_PHARMACOPHORE_HPP
#define CDPL_CHEM_PHARMACOPHORE_HPP

#include <boost/shared_ptr.hpp>
#include <boost/ref.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Feature;

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_INTERFACES
		 * @{
		 */

		/**
		 * \brief Pharmacophore.
		 */
		class CDPL_CHEM_API Pharmacophore : public Entity3DContainer, public Base::PropertyContainer
		{

			class ConstFeatureAccessor;
			class FeatureAccessor;

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %Pharmacophore instances.
			 */
			typedef boost::shared_ptr<Pharmacophore> SharedPointer;

			/**
			 * \brief A constant random access iterator used to iterate over the stored \c const Chem::Feature objects.
			 */
			typedef Util::IndexedElementIterator<const Feature, ConstFeatureAccessor> ConstFeatureIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored Chem::Feature objects.
			 */
			typedef Util::IndexedElementIterator<Feature, FeatureAccessor> FeatureIterator;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Pharmacophore() {}
		
			/**
			 * \brief Removes all feature and clears all properties of the pharmacophore.
			 */
			virtual void clear() = 0;
		
			/**
			 * \brief Returns the number of pharmacophore features.
			 * \return The number of feature.
			 */
			virtual std::size_t getNumFeatures() const = 0;

			/**
			 * \brief Returns a \c const reference to the pharmacophore feature at index \a idx.
			 * \param idx The zero-based index of the feature to return.
			 * \return A \c const reference to the feature at the specified index.
			 * \throw Base::IndexError if the number of pharmacophore feature is zero or \a idx is not in the range [0, getNumFeatures() - 1].
			 */
			virtual const Feature& getFeature(std::size_t idx) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the pharmacophore feature at index \a idx.
			 * \param idx The zero-based index of the feature to return.
			 * \return A non-\c const reference to the feature at the specified index.
			 * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
			 */
			virtual Feature& getFeature(std::size_t idx) = 0;

			/**
			 * \brief Creates a new pharmacophore feature and adds it to the pharmacophore.
			 * \return A reference to the newly created feature.
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
			 * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Feature objects.
			 * \return A constant iterator pointing to the beginning of the stored \c const Chem::Feature objects.
			 */
			ConstFeatureIterator getFeaturesBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Feature objects.
			 * \return A constant iterator pointing to the end of the stored \c const Chem::Feature objects.
			 */
			ConstFeatureIterator getFeaturesEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored Chem::Feature objects.
			 * \return A mutable iterator pointing to the beginning of the stored Chem::Feature objects.
			 */
			FeatureIterator getFeaturesBegin();

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored Chem::Feature objects.
			 * \return A mutable iterator pointing to the end of the stored Chem::Feature objects.
			 */
			FeatureIterator getFeaturesEnd();

			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the pharmacophore \a pharm.
			 * \param pharm The pharmacophore to copy.
			 */
			virtual void copy(const Pharmacophore& pharm) = 0;
		
			/**
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        pharmacophore \a pharm.
			 * \param pharm The pharmacophore providing the features to append.
			 * \note Does not affect any properties.
			 */
			virtual void append(const Pharmacophore& pharm) = 0;

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
			 * \brief Extends the current set of pharmacophore features by a copy of the features in the
			 *        pharmacophore \a pharm.
			 *
			 * Internally calls append() to perform the actual work.
			 *
			 * \param pharm The pharmacophore providing the features to append.
			 * \return A reference to itself.
			 */
			Pharmacophore& operator+=(const Pharmacophore& pharm);

			virtual std::size_t getNumEntities() const;

			virtual const Entity3D& getEntity(std::size_t idx) const;

			virtual Entity3D& getEntity(std::size_t idx);

		  private:
			class CDPL_CHEM_API ConstFeatureAccessor
			{
			
			  public:
				ConstFeatureAccessor(const FeatureAccessor& accessor): container(accessor.container) {}

				ConstFeatureAccessor(const Pharmacophore& cntnr): container(cntnr) {}

				const Feature& operator()(std::size_t idx) const;

				bool operator==(const ConstFeatureAccessor& accessor) const;

				ConstFeatureAccessor& operator=(const FeatureAccessor& accessor);

			  private:
				boost::reference_wrapper<const Pharmacophore> container;
			};

			class CDPL_CHEM_API FeatureAccessor
			{
			
				friend class ConstFeatureAccessor;

			  public:
				FeatureAccessor(Pharmacophore& cntnr): container(cntnr) {}

				Feature& operator()(std::size_t idx) const;

				bool operator==(const FeatureAccessor& accessor) const;

			  private:
				boost::reference_wrapper<Pharmacophore> container;
			};
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_PHARMACOPHORE_HPP
