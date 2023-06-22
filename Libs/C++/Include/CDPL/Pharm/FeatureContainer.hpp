/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureContainer.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2016 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::FeatureContainer.
 */

#ifndef CDPL_PHARM_FEATURECONTAINER_HPP
#define CDPL_PHARM_FEATURECONTAINER_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief FeatureContainer.
		 */
		class CDPL_PHARM_API FeatureContainer : public Chem::Entity3DContainer, public Base::PropertyContainer
		{

			class ConstFeatureAccessor;
			class FeatureAccessor;

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureContainer instances.
			 */
			typedef std::shared_ptr<FeatureContainer> SharedPointer;

			/**
			 * \brief A constant random access iterator used to iterate over the stored \c const Pharm::Feature objects.
			 */
			typedef Util::IndexedElementIterator<const Feature, ConstFeatureAccessor> ConstFeatureIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored Pharm::Feature objects.
			 */
			typedef Util::IndexedElementIterator<Feature, FeatureAccessor> FeatureIterator;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~FeatureContainer() {}

			/**
			 * \brief Returns the number of contained features.
			 * \return The number of features.
			 */
			virtual std::size_t getNumFeatures() const = 0;

			/**
			 * \brief Returns a \c const reference to the feature at index \a idx.
			 * \param idx The zero-based index of the feature to return.
			 * \return A \c const reference to the feature at the specified index.
			 * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
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
			 * \brief Returns the index of the specified feature.
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
			 * \brief Returns a constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
			 * \return A constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
			 */
			ConstFeatureIterator getFeaturesBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
			 * \return A constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
			 */
			ConstFeatureIterator getFeaturesEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored Pharm::Feature objects.
			 * \return A mutable iterator pointing to the beginning of the stored Pharm::Feature objects.
			 */
			FeatureIterator getFeaturesBegin();

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored Pharm::Feature objects.
			 * \return A mutable iterator pointing to the end of the stored Pharm::Feature objects.
			 */
			FeatureIterator getFeaturesEnd();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
			 * \return A constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
			 */
			ConstFeatureIterator begin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
			 * \return A constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
			 */
			ConstFeatureIterator end() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored Pharm::Feature objects.
			 * \return A mutable iterator pointing to the beginning of the stored Pharm::Feature objects.
			 */
			FeatureIterator begin();

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored Pharm::Feature objects.
			 * \return A mutable iterator pointing to the end of the stored Pharm::Feature objects.
			 */
			FeatureIterator end();

			virtual std::size_t getNumEntities() const;

			virtual const Chem::Entity3D& getEntity(std::size_t idx) const;

			virtual Chem::Entity3D& getEntity(std::size_t idx);

		  protected:
			/**
			 * \brief Replaces the current set of pharmacophore features and properties by a copy of the
			 *        features and properties of the container \a cntnr.
			 * \param cntnr The container to copy.
			 * \return A reference to itself.
			 */
			FeatureContainer& operator=(const FeatureContainer& cntnr);

		  private:
			class CDPL_PHARM_API ConstFeatureAccessor
			{
			
			  public:
				ConstFeatureAccessor(const FeatureAccessor& accessor): container(accessor.container) {}

				ConstFeatureAccessor(const FeatureContainer* cntnr): container(cntnr) {}

				const Feature& operator()(std::size_t idx) const;

				bool operator==(const ConstFeatureAccessor& accessor) const;

				ConstFeatureAccessor& operator=(const FeatureAccessor& accessor);

			  private:
				const FeatureContainer* container;
			};

			class CDPL_PHARM_API FeatureAccessor
			{
			
				friend class ConstFeatureAccessor;

			  public:
				FeatureAccessor(FeatureContainer* cntnr): container(cntnr) {}

				Feature& operator()(std::size_t idx) const;

				bool operator==(const FeatureAccessor& accessor) const;

			  private:
				FeatureContainer* container;
			};
		};
    }
}

#endif // CDPL_PHARM_FEATURECONTAINER_HPP
