/* 
 * IndexedElementIterator.hpp 
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
 * \brief Definition of the class CDPL::Util::IndexedElementIterator.
 */

#ifndef CDPL_UTIL_INDEXEDELEMENTITERATOR_HPP
#define CDPL_UTIL_INDEXEDELEMENTITERATOR_HPP

#include <cstddef>

#include <boost/iterator/iterator_facade.hpp>


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief A STL compatible random access iterator for container elements accessible by index.
         *
         * The rationale for \c %IndexedElementIterator is to allow STL-style iteration over
         * the elements of container classes which do not provide suitable iterators on their
         * own, but allow element access by some sort of consecutive index. \c %IndexedElementIterator
         * is a random access iterator and therefore provides both increment and decrement operations
         * and constant-time methods for moving forward and backward in arbitrary-sized steps.
         * Random access iterators essentially provide all of the operations of ordinary C/C++ pointer
         * arithmetic (see [\ref STLRAI] for details).
         *    
         * As an example consider the class \c StringContainer which provides access to stored
         * C++ strings via a method \c getString(std::size_t idx):
         * \code 
         * class StringContainer
         * {
         *
         * public:
         *
         *    .....
         *
         *    std::string getString(std::size_t idx); // retrieves a reference to a stored string by its index
         *    std::size_t getNumStrings() const;      // returns the total number of stored strings
         *
         *    .....
         *
         * };
         * \endcode
         *
         * To implement an iterator for string traversal using \c %IndexedElementIterator, one
         * first has to define a \c StringContainer access functor that returns a reference
         * to the string stored at a particular index. 
         *
         * A possible implementation of this functor may look like this:
         * \code
         * class StringAccessFunc
         * {
         *    
         * public:
         *    StringAccessFunc(StringContainer* cntnr): container(ctnr) {}
         *
         *    std::string& operator()(std::size_t idx) const {
         *       return container->getString(idx);
         *    }
         *
         *    bool operator==(const StringAccessFunc& func) const {
         *       return (func.container == container);
         *    }
         *
         * private:
         *    StringContainer* cntnr;
         * };
         * \endcode
         *
         * With \c StringAccessFunc in hands, the type of the string traversal iterator
         * for \c StringContainer is defined as:
         * \code
         * typedef IndexedElementIterator<std::string, StringAccessFunc> StringIterator;
         * \endcode
         *
         * \c StringIterator can then easily be used with STL-algorithms, e.g. to find a particular
         * string in a \c StringContainer instance:
         * \code
         * StringContainer str_molGraph;
         *
         *    ..... // do something with 'str_container'
         *
         * // does 'str_container' contain the string "foobar"?
         *
         * bool contains_foobar = (std::find(StringIterator(&str_container, 0),        
         *                                   StringIterator(&str_container, str_container.getNumStrings()),
         *                                   std::string("foobar")) 
         *                         != StringIterator(&str_container, str_container.getNumStrings())); 
         * \endcode
         *
         * \tparam ValueType The type of the elements accessed by the iterator.
         * \tparam AccessFunc The type of the functor object used to access the elements by index.
         * \tparam IndexType The type of the indices used to access the elements. 
         */
        template <typename ValueType, typename AccessFunc, typename IndexType = std::size_t>
        class IndexedElementIterator : public boost::iterator_facade<IndexedElementIterator<ValueType, AccessFunc, IndexType>,
                                                                     ValueType, boost::random_access_traversal_tag>
        {

            typedef typename boost::iterator_facade<IndexedElementIterator<ValueType, AccessFunc, IndexType>,
                                                    ValueType,
                                                    boost::random_access_traversal_tag>::difference_type DifferenceType;

          public:
            /**
             * \brief Constructs and initializes the iterator with another iterator object.
             * \param it The other iterator.
             */
            template <typename ValueType2, typename AccessFunc2, typename IndexType2>
            IndexedElementIterator(const IndexedElementIterator<ValueType2, AccessFunc2, IndexType2>& it):
                accessFunc(it.getAccessFunc()), index(it.getIndex())
            {}

            /**
             * \brief Constructs and initializes the iterator with the access function \a access_func
             *        and the start element index \a start_idx.
             * \param access_func The element access function to use.
             * \param start_idx The index of the first element the iterator will point to.
             */
            IndexedElementIterator(const AccessFunc& access_func, IndexType start_idx):
                accessFunc(access_func), index(start_idx) {}

            const AccessFunc& getAccessFunc() const;

            IndexType getIndex() const;

          private:
            friend class boost::iterator_core_access;

            void increment();
            void decrement();
            void advance(DifferenceType);

            template <typename ValueType2, typename AccessFunc2, typename IndexType2>
            DifferenceType distance_to(const IndexedElementIterator<ValueType2, AccessFunc2, IndexType2>&) const;

            template <typename ValueType2, typename AccessFunc2, typename IndexType2>
            bool equal(const IndexedElementIterator<ValueType2, AccessFunc2, IndexType2>&) const;

            ValueType& dereference() const;

            AccessFunc accessFunc;
            IndexType  index;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename ValueType, typename AccessFunc, typename IndexType>
IndexType CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::getIndex() const
{
    return index;
}

template <typename ValueType, typename AccessFunc, typename IndexType>
const AccessFunc& CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::getAccessFunc() const
{
    return accessFunc;
}

template <typename ValueType, typename AccessFunc, typename IndexType>
void CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::increment()
{
    index++;
}

template <typename ValueType, typename AccessFunc, typename IndexType>
void CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::decrement()
{
    index--;
}

template <typename ValueType, typename AccessFunc, typename IndexType>
void CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::advance(DifferenceType diff)
{
    index += diff;
}

template <typename ValueType, typename AccessFunc, typename IndexType>
template <typename ValueType2, typename AccessFunc2, typename IndexType2>
typename CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::DifferenceType
CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::distance_to(const IndexedElementIterator<ValueType2, AccessFunc2, IndexType2>& it) const
{
    return (DifferenceType(it.index) - DifferenceType(index));
}

template <typename ValueType, typename AccessFunc, typename IndexType>
template <typename ValueType2, typename AccessFunc2, typename IndexType2>
bool CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::equal(const IndexedElementIterator<ValueType2, AccessFunc2, IndexType2>& it) const
{
    return (index == it.index && accessFunc == it.accessFunc);
}

template <typename ValueType, typename AccessFunc, typename IndexType>
ValueType& CDPL::Util::IndexedElementIterator<ValueType, AccessFunc, IndexType>::dereference() const
{
    return accessFunc(index);
}

#endif // CDPL_UTIL_INDEXEDELEMENTITERATOR_HPP
