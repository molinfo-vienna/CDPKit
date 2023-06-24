/* 
 * FeatureSet.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureSet.
 */

#ifndef CDPL_PHARM_FEATURESET_HPP
#define CDPL_PHARM_FEATURESET_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"


namespace CDPL
{

    namespace Pharm
    {

        /**
     * \brief FeatureSet.
     */
        class CDPL_PHARM_API FeatureSet : public FeatureContainer
        {

            typedef std::vector<Feature*> FeatureList;

          public:
            /**    
         * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %FeatureSet instances.
         */
            typedef std::shared_ptr<FeatureSet> SharedPointer;

            /**
         * \brief A constant random access iterator used to iterate over the stored \c const Pharm::Feature objects.
         */
            typedef boost::indirect_iterator<FeatureList::const_iterator, const Feature> ConstFeatureIterator;

            /**
         * \brief A mutable random access iterator used to iterate over the stored \c const Pharm::Feature objects.
         */
            typedef boost::indirect_iterator<FeatureList::iterator, Feature> FeatureIterator;

            /**
         * \brief Constructs an empty \c %FeatureSet instance.
         */
            FeatureSet();

            /**
         * \brief Constructs a copy of the \c %FeatureSet instance \a ftr_set.
         * \param ftr_set The other \c %FeatureSet instance to copy.
         */
            FeatureSet(const FeatureSet& ftr_set);

            /**
         * \brief Constructs a \c %FeatureSet instance storing the features and properties of the feature container \a cntnr.
         * \param cntnr The Pharm::FeatureContainer instance providing the features and properties to store.
         */
            explicit FeatureSet(const FeatureContainer& cntnr);

            /**
         * \brief Destructor.
         *
         * Destroys the \c %FeatureSet instance and frees all allocated resources.
         */
            ~FeatureSet();

            /**
         * \brief Returns the number of features.
         * \return The number of features.
         */
            std::size_t getNumFeatures() const;

            /**
         * \brief Tells whether the specified feature is part of this feature set.
         * \param ftr The feature to look for.
         * \return \c true if \a feature is part of this feature set, and \c false otherwise.
         */
            bool containsFeature(const Feature& ftr) const;

            /**
         * \brief Returns the index of the specified feature.
         * \param ftr The feature for which to return the index.
         * \return The zero-based index of the specified feature.
         * \throw Base::ItemNotFound if the specified feature is not part of the feature set.
         */
            std::size_t getFeatureIndex(const Feature& ftr) const;

            /**
         * \brief Returns a constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
         * \return A constant iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
         */
            ConstFeatureIterator getFeaturesBegin() const;

            /**
         * \brief Returns a mutable iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
         * \return A mutable iterator pointing to the beginning of the stored \c const Pharm::Feature objects.
         */
            FeatureIterator getFeaturesBegin();

            /**
         * \brief Returns a constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
         * \return A constant iterator pointing to the end of the stored \c const Pharm::Feature objects.
         */
            ConstFeatureIterator getFeaturesEnd() const;

            /**
         * \brief Returns a mutable iterator pointing to the end of the stored \c const Pharm::Feature objects.
         * \return A mutable iterator pointing to the end of the stored \c const Pharm::Feature objects.
         */
            FeatureIterator getFeaturesEnd();

            /**
         * \brief Returns a \c const reference to the feature at index \a idx.
         * \param idx The zero-based index of the feature to return.
         * \return A \c const reference to the feature at the specified index.
         * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
         */
            const Feature& getFeature(std::size_t idx) const;

            /**
         * \brief Returns a \c non-const reference to the feature at index \a idx.
         * \param idx The zero-based index of the feature to return.
         * \return A \c non-const reference to the feature at the specified index.
         * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
         */
            Feature& getFeature(std::size_t idx);

            /**
         * \brief Extends the feature set by the specified feature.
         * \param ftr The feature to add.
         * \return \c true if the feature was not already a part of the feature set, and \c false otherwise.
         */
            bool addFeature(const Feature& ftr);

            /**
         * \brief Removes the feature at the specified index.
         * \param idx The zero-based index of the feature to remove.
         * \throw Base::IndexError if the number of features is zero or \a idx is not in the range [0, getNumFeatures() - 1].
         */
            void removeFeature(std::size_t idx);

            /**
         * \brief Removes the feature specified by the iterator \a it.
         * \param it An iterator that specifies the feature to remove.
         * \return A mutable iterator pointing to the next feature in the list.
         * \throw Base::RangeError if the number of features is zero or \a it is not in the range
         *        [getFeaturesBegin(), getFeaturesEnd() - 1].
         */
            FeatureIterator removeFeature(const FeatureIterator& it);

            /**
         * \brief Removes the specified feature.
         * \param ftr The feature to remove.
         * \return \c true if the feature was part of the feature set and has been removed, and \c false otherwise.
         */
            bool removeFeature(const Feature& ftr);

            /**
         * \brief Removes all features and properties.
         */
            void clear();

            /**
         * \brief Replaces the current set of features and properties by the features and properties
         *        of the feature set \a ftr_set.
         * \param ftr_set The feature set to copy.
         * \return A reference to itself.
         */
            FeatureSet& operator=(const FeatureSet& ftr_set);

            /**
         * \brief Replaces the current set of features and properties by the features and properties
         *        of the feature container \a cntnr.
         * \param cntnr The Pharm::FeatureContainer instance providing the features and properties to copy.
         * \return A reference to itself.
         */
            FeatureSet& operator=(const FeatureContainer& cntnr);

            /**
         * \brief Extends the current set of features by the features in the feature container \a cntnr.
         * \param cntnr The Pharm::FeatureContainer instance providing the features to append.
         * \return A reference to itself.
         * \note Does not affect any properties.
         */
            FeatureSet& operator+=(const FeatureContainer& cntnr);

            /**
         * \brief Removes the pharmacophore features referenced by the feature container \a cntnr from this \c %FeatureSet instance.
         * \param cntnr The Pharm::FeatureContainer instance providing the features to remove.
         * \return A reference to itself.
         * \note Does not affect any properties if <tt>this != &cntr</tt>.
         */
            FeatureSet& operator-=(const FeatureContainer& cntnr);

          private:
            typedef std::unordered_map<const Feature*, std::size_t> FeatureIndexMap;

            FeatureList     features;
            FeatureIndexMap featureIndices;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_FEATURESET_HPP
