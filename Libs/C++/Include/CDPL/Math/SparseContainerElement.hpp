/* 
 * SparseContainerElement.hpp 
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
 * \brief Definition of an element proxy for sparse data types.
 */

#ifndef CDPL_MATH_SPARSECONTAINERELEMENT_HPP
#define CDPL_MATH_SPARSECONTAINERELEMENT_HPP

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Proxy that exposes a single (key, value) entry of a sparse container as a writable reference.
         *
         * Reading the proxy returns the value associated with \a key (or a default-constructed value if no entry exists).
         * Writing to the proxy inserts/updates the entry; assigning the default-constructed value removes the entry from
         * the underlying sparse storage.
         *
         * \tparam C The sparse container type (must expose \c KeyType, \c ValueType, \c SizeType, \c ConstReference, \c ArrayType and \c getData()).
         * \tparam K The key type (defaults to <tt>C::KeyType</tt>).
         */
        template <typename C, typename K = typename C::KeyType>
        class SparseContainerElement
        {

          public:
            typedef C                                      ContainerType;
            typedef K                                      KeyType;
            typedef typename ContainerType::ValueType      ValueType;
            typedef typename ContainerType::SizeType       SizeType;
            typedef ValueType&                             Reference;
            typedef typename ContainerType::ConstReference ConstReference;
            typedef typename ContainerType::ArrayType      ArrayType;

            SparseContainerElement(ContainerType& c, KeyType key):
                cntnr(c), key(key) {}

            // Assignment
            SparseContainerElement& operator=(const SparseContainerElement& p)
            {
                p.get();
                set(p.value);

                return *this;
            }

            template <typename D>
            SparseContainerElement& operator=(const D& d)
            {
                set(d);

                return *this;
            }

            template <typename D>
            SparseContainerElement& operator+=(const D& d)
            {
                get();
                value += d;
                set(value);

                return *this;
            }

            template <typename D>
            SparseContainerElement& operator-=(const D& d)
            {
                get();
                value -= d;
                set(value);

                return *this;
            }

            template <typename D>
            SparseContainerElement& operator*=(const D& d)
            {
                get();
                value *= d;
                set(value);

                return *this;
            }

            template <typename D>
            SparseContainerElement& operator/=(const D& d)
            {
                get();
                value /= d;
                set(value);

                return *this;
            }

            // Comparison
            template <typename D>
            bool operator==(const D& d) const
            {
                get();

                return (value == d);
            }

            template <typename D>
            bool operator!=(const D& d) const
            {
                get();

                return (value != d);
            }

            operator ConstReference() const
            {
                get();

                return value;
            }

          private:
            void set(const ValueType& v)
            {
                if (v == ValueType())
                    cntnr.getData().erase(key);

                else {
                    std::pair<typename ArrayType::iterator, bool> pos = cntnr.getData().insert(typename ArrayType::value_type(key, v));

                    if (!pos.second)
                        pos.first->second = v;
                }
            }

            void get() const
            {
                typename ArrayType::const_iterator it = cntnr.getData().find(key);

                if (it == cntnr.getData().end())
                    value = ValueType();
                else
                    value = it->second;
            }

            ContainerType&    cntnr;
            KeyType           key;
            mutable ValueType value;
        };

        /**
         * \brief Math::TypeTraits specialization that delegates to the underlying value type of a Math::SparseContainerElement.
         * \tparam C The sparse container type.
         */
        template <typename C>
        struct TypeTraits<SparseContainerElement<C> > : public TypeTraits<typename SparseContainerElement<C>::ValueType>
        {};
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_SPARSECONTAINERELEMENT_HPP
