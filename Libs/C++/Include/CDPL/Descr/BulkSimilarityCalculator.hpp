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
 * \brief Definition of the class template CDPL::Descr::BulkSimilarityCalculator.
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
         * \since 1.2.3
         */
        template <typename DT = Util::BitSet, typename SVT = double>
        class BulkSimilarityCalculator
        {

          public:
            typedef DT                                        Descriptor;
            typedef std::shared_ptr<DT>                       DescriptorPointer;
            typedef SVT                                       SimilarityValue;
            typedef std::function<SVT(const DT&, const DT&)>  SimilarityFunction;
            typedef std::pair<std::size_t, SVT>               Result;
            typedef std::shared_ptr<BulkSimilarityCalculator> SharedPointer;

          private:
            typedef std::vector<DescriptorPointer> DescriptorList;
            typedef std::vector<Result>            ResultList;

          public:
            typedef boost::indirect_iterator<typename DescriptorList::const_iterator, DT>
                ConstDescriptorIterator;
            typedef boost::indirect_iterator<typename DescriptorList::iterator, DT>
                DescriptorIterator;

            typedef typename ResultList::const_iterator ConstResultIterator;
            
            BulkSimilarityCalculator() = default;

            BulkSimilarityCalculator(const BulkSimilarityCalculator& calc) = default;
            BulkSimilarityCalculator(BulkSimilarityCalculator&& calc) = default;
            
            template <typename SF>
            BulkSimilarityCalculator(SF&& sim_func):
                simFunc(std::forward<SF>(sim_func)) {}

            BulkSimilarityCalculator& operator=(const BulkSimilarityCalculator& calc) = default;
            BulkSimilarityCalculator& operator=(BulkSimilarityCalculator&& calc) = default;
            
            const SimilarityFunction& getSimilarityFunction() const;

            template <typename SF>
            void setSimilarityFunction(SF&& func);
            
            void clear();

            DescriptorIterator getDescriptorsBegin();
            DescriptorIterator getDescriptorsEnd();

            ConstDescriptorIterator getDescriptorsBegin() const;
            ConstDescriptorIterator getDescriptorsEnd() const;

            std::size_t getNumDescriptors() const;

            void addDescriptor(const Descriptor& descr);
            void addDescriptor(const DescriptorPointer& descr_ptr);

            bool containsDescriptor(const Descriptor& descr) const;

            const Descriptor& getDescriptor(std::size_t idx) const;

            void removeDescriptor(std::size_t idx);
            DescriptorIterator removeDescriptor(const DescriptorIterator& it);

            void calculate(const Descriptor& descr, bool sort = false, bool sort_desc = true);

            ConstResultIterator getResultsBegin() const;
            ConstResultIterator getResultsEnd() const;

            ConstResultIterator begin() const;
            ConstResultIterator end() const;

            const Result& getResult(std::size_t idx) const;

            const SimilarityValue& getSimilarity(std::size_t idx) const;
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
