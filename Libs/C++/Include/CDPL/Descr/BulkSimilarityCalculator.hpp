/* 
 * BulkSimilarityCalculator.hpp 
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
 * \brief Definition of class template CDPL::Descr::BulkSimilarityCalculator.
 */

#ifndef CDPL_DESCR_BULKSIMILARITYCALCULATOR_HPP
#define CDPL_DESCR_BULKSIMILARITYCALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>
#include <algorithm>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Descr/SimilarityFunctors.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Descr
    {

        /**
         * \brief Calculator that performs a bulk pairwise comparison of a single query descriptor
         *        against a stored set of target descriptors using a configurable similarity function.
         *
         * Stored descriptors are held by shared pointer; the calculator can therefore share descriptor
         * ownership with external code. After a call to calculate() the per-target similarity values
         * are available in stored order and can optionally be sorted.
         *
         * \tparam DT The descriptor type (defaults to Util::BitSet, suitable for fingerprint similarity).
         * \tparam SVT The similarity-value type (defaults to \c double).
         *
         * \since 1.2.3
         */
        template <typename DT = Util::BitSet, typename SVT = double>
        class BulkSimilarityCalculator
        {

          public:
            /**
             * \brief The descriptor type.
             */
            typedef DT                                        Descriptor;

            /**
             * \brief A smart pointer to a stored descriptor.
             */
            typedef std::shared_ptr<DT>                       DescriptorPointer;

            /**
             * \brief The similarity-value type.
             */
            typedef SVT                                       SimilarityValue;

            /**
             * \brief Type of the generic functor used to compute the similarity of two descriptors.
             */
            typedef std::function<SVT(const DT&, const DT&)>  SimilarityFunction;

            /**
             * \brief A single calculation result: (target descriptor index, similarity value).
             */
            typedef std::pair<std::size_t, SVT>               Result;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BulkSimilarityCalculator instances.
             */
            typedef std::shared_ptr<BulkSimilarityCalculator> SharedPointer;

          private:
            typedef std::vector<DescriptorPointer> DescriptorList;
            typedef std::vector<Result>            ResultList;

          public:
            /**
             * \brief A constant iterator over the stored target descriptors.
             */
            typedef boost::indirect_iterator<typename DescriptorList::const_iterator, DT>
                ConstDescriptorIterator;

            /**
             * \brief A mutable iterator over the stored target descriptors.
             */
            typedef boost::indirect_iterator<typename DescriptorList::iterator, DT>
                DescriptorIterator;

            /**
             * \brief A constant iterator over the calculation results.
             */
            typedef typename ResultList::const_iterator ConstResultIterator;

            /**
             * \brief Constructs the \c %BulkSimilarityCalculator instance with the default similarity function
             *        (TanimotoSimilarity).
             */
            BulkSimilarityCalculator() = default;

            /**
             * \brief Copy constructor.
             * \param calc The other \c %BulkSimilarityCalculator instance.
             */
            BulkSimilarityCalculator(const BulkSimilarityCalculator& calc) = default;

            /**
             * \brief Move constructor.
             * \param calc The other \c %BulkSimilarityCalculator instance.
             */
            BulkSimilarityCalculator(BulkSimilarityCalculator&& calc) = default;

            /**
             * \brief Constructs the \c %BulkSimilarityCalculator instance with the given similarity function.
             * \tparam SF The similarity-function type.
             * \param sim_func The similarity function.
             */
            template <typename SF>
            BulkSimilarityCalculator(SF&& sim_func):
                simFunc(std::forward<SF>(sim_func)) {}

            /**
             * \brief Copy assignment operator.
             * \param calc The other \c %BulkSimilarityCalculator instance.
             * \return A reference to itself.
             */
            BulkSimilarityCalculator& operator=(const BulkSimilarityCalculator& calc) = default;

            /**
             * \brief Move assignment operator.
             * \param calc The other \c %BulkSimilarityCalculator instance.
             * \return A reference to itself.
             */
            BulkSimilarityCalculator& operator=(BulkSimilarityCalculator&& calc) = default;

            /**
             * \brief Returns the currently configured similarity function.
             * \return A \c const reference to the similarity function.
             */
            const SimilarityFunction& getSimilarityFunction() const;

            /**
             * \brief Sets the similarity function.
             * \tparam SF The similarity-function type.
             * \param func The new similarity function.
             */
            template <typename SF>
            void setSimilarityFunction(SF&& func);

            /**
             * \brief Removes all stored descriptors and calculation results.
             */
            void clear();

            /**
             * \brief Returns a mutable iterator pointing to the first stored descriptor.
             * \return A mutable iterator pointing to the first stored descriptor.
             */
            DescriptorIterator getDescriptorsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last stored descriptor.
             * \return A mutable iterator pointing one past the last stored descriptor.
             */
            DescriptorIterator getDescriptorsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first stored descriptor.
             * \return A constant iterator pointing to the first stored descriptor.
             */
            ConstDescriptorIterator getDescriptorsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last stored descriptor.
             * \return A constant iterator pointing one past the last stored descriptor.
             */
            ConstDescriptorIterator getDescriptorsEnd() const;

            /**
             * \brief Returns the number of stored descriptors.
             * \return The number of descriptors.
             */
            std::size_t getNumDescriptors() const;

            /**
             * \brief Adds a copy of \a descr to the stored descriptor list.
             * \param descr The descriptor to copy.
             */
            void addDescriptor(const Descriptor& descr);

            /**
             * \brief Adds the descriptor referenced by \a descr_ptr to the stored descriptor list, sharing ownership.
             * \param descr_ptr A smart pointer to the descriptor.
             */
            void addDescriptor(const DescriptorPointer& descr_ptr);

            /**
             * \brief Tells whether a descriptor that compares equal to \a descr is stored.
             * \param descr The descriptor to look for.
             * \return \c true if such a descriptor is stored, and \c false otherwise.
             */
            bool containsDescriptor(const Descriptor& descr) const;

            /**
             * \brief Returns the stored descriptor at index \a idx.
             * \param idx The zero-based descriptor index.
             * \return A \c const reference to the descriptor.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDescriptors()).
             */
            const Descriptor& getDescriptor(std::size_t idx) const;

            /**
             * \brief Removes the descriptor at index \a idx.
             * \param idx The zero-based descriptor index.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDescriptors()).
             */
            void removeDescriptor(std::size_t idx);

            /**
             * \brief Removes the descriptor referenced by \a it.
             * \param it Iterator referencing the descriptor to remove.
             * \return A mutable iterator pointing to the descriptor following the removed one.
             * \throw Base::RangeError if \a it is not in the range [getDescriptorsBegin(), getDescriptorsEnd()).
             */
            DescriptorIterator removeDescriptor(const DescriptorIterator& it);

            /**
             * \brief Computes the similarity between the query \a descr and every stored descriptor.
             * \param descr The query descriptor.
             * \param sort If \c true, the resulting (index, similarity) pairs are sorted by similarity value.
             * \param sort_desc If \c true (default), sorting is in descending order of similarity. If \c false, in ascending order.
             */
            void calculate(const Descriptor& descr, bool sort = false, bool sort_desc = true);

            /**
             * \brief Returns a constant iterator pointing to the first result of the last calculate() call.
             * \return A constant iterator pointing to the first result.
             */
            ConstResultIterator getResultsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last result of the last calculate() call.
             * \return A constant iterator pointing one past the last result.
             */
            ConstResultIterator getResultsEnd() const;

            /**
             * \brief Returns a constant iterator pointing to the first result (range-based for support).
             * \return A constant iterator pointing to the first result.
             */
            ConstResultIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last result (range-based for support).
             * \return A constant iterator pointing one past the last result.
             */
            ConstResultIterator end() const;

            /**
             * \brief Returns the result at the given index.
             * \param idx The zero-based result index.
             * \return A \c const reference to the (descriptor index, similarity) pair.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDescriptors()).
             */
            const Result& getResult(std::size_t idx) const;

            /**
             * \brief Returns the similarity value of the result at the given index.
             * \param idx The zero-based result index.
             * \return A \c const reference to the similarity value.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDescriptors()).
             */
            const SimilarityValue& getSimilarity(std::size_t idx) const;

            /**
             * \brief Returns the index of the target descriptor referenced by the result at the given result index.
             * \param idx The zero-based result index.
             * \return The descriptor index referenced by the result.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumDescriptors()).
             */
            std::size_t getDescriptorIndex(std::size_t idx) const;

          private:
            SimilarityFunction simFunc{TanimotoSimilarity()};
            DescriptorList     descriptors;
            ResultList         results;
        };

    } // namespace Descr
} // namespace CDPL


// Implementation

template <typename DT, typename SVT>
const typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::SimilarityFunction&
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getSimilarityFunction() const
{
    return simFunc;
}

template <typename DT, typename SVT>
template <typename SF>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::setSimilarityFunction(SF&& func)
{
    simFunc = std::forward<SF>(func);
}

template <typename DT, typename SVT>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::clear()
{
    descriptors.clear();
    results.clear();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::DescriptorIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptorsBegin()
{
    return descriptors.begin();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::DescriptorIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptorsEnd()
{
    return descriptors.end();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstDescriptorIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptorsBegin() const
{
    return descriptors.begin();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstDescriptorIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptorsEnd() const
{
    return descriptors.end();
}

template <typename DT, typename SVT>
std::size_t CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getNumDescriptors() const
{
    return descriptors.size();
}

template <typename DT, typename SVT>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::addDescriptor(const Descriptor& descr)
{
    descriptors.emplace_back(DescriptorPointer(new Descriptor(descr)));
}

template <typename DT, typename SVT>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::addDescriptor(const DescriptorPointer& descr_ptr)
{
    descriptors.emplace_back(descr_ptr);
}

template <typename DT, typename SVT>
bool CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::containsDescriptor(const Descriptor& descr) const
{
    for (auto& dp : descriptors)
        if (*dp == descr)
            return true;

    return false;
}

template <typename DT, typename SVT>
const typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::Descriptor&
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptor(std::size_t idx) const
{
    if (idx >= descriptors.size())
        throw Base::IndexError("BulkSimilarityCalculator: descriptor index out of bounds");

    return *descriptors[idx];
}

template <typename DT, typename SVT>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::removeDescriptor(std::size_t idx)
{
    if (idx >= descriptors.size())
        throw Base::IndexError("BulkSimilarityCalculator: descriptor index out of bounds");

    descriptors.erase(descriptors.begin() + idx);
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::DescriptorIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::removeDescriptor(const DescriptorIterator& it)
{
    auto& b_it = it.base();

    if ((b_it < descriptors.begin()) || (b_it >= descriptors.end()))
        throw Base::RangeError("BulkSimilarityCalculator: descriptor iterator out of valid range");

    return descriptors.erase(b_it);
}

template <typename DT, typename SVT>
void CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::calculate(const Descriptor& descr, bool sort, bool sort_desc)
{
    results.clear();
    results.reserve(descriptors.size());

    for (std::size_t i = 0, num_descrs = descriptors.size(); i < num_descrs; i++)
        results.emplace_back(i, simFunc(descr, *descriptors[i]));

    if (!sort)
        return;

    if (sort_desc)
        std::sort(results.begin(), results.end(),
                  [](const Result& r1, const Result& r2) {
                      return (r1.second > r2.second);
                  });
    else
        std::sort(results.begin(), results.end(),
                  [](const Result& r1, const Result& r2) {
                      return (r1.second < r2.second);
                  });
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstResultIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getResultsBegin() const
{
    return results.begin();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstResultIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getResultsEnd() const
{
    return results.end();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstResultIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::begin() const
{
    return results.begin();
}

template <typename DT, typename SVT>
typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::ConstResultIterator
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::end() const
{
    return results.end();
}

template <typename DT, typename SVT>
const typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::Result&
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getResult(std::size_t idx) const
{
    if (idx >= results.size())
        throw Base::IndexError("BulkSimilarityCalculator: result index out of bounds");

    return results[idx];
}

template <typename DT, typename SVT>
const typename CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::SimilarityValue&
CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getSimilarity(std::size_t idx) const
{
    if (idx >= results.size())
        throw Base::IndexError("BulkSimilarityCalculator: result index out of bounds");

    return results[idx].second;
}

template <typename DT, typename SVT>
std::size_t CDPL::Descr::BulkSimilarityCalculator<DT, SVT>::getDescriptorIndex(std::size_t idx) const
{
    if (idx >= results.size())
        throw Base::IndexError("BulkSimilarityCalculator: result index out of bounds");

    return results[idx].first;
}

#endif // CDPL_DESCR_BULKSIMILARITYCALCULATOR_HPP
