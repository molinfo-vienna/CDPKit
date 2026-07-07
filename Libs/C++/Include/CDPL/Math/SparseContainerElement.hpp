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
            /**
             * \brief The sparse container type the proxy references.
             */
            typedef C                                      ContainerType;

            /**
             * \brief The key type used to address an entry of the container.
             */
            typedef K                                      KeyType;

            /**
             * \brief The value type stored in the container.
             */
            typedef typename ContainerType::ValueType      ValueType;

            /**
             * \brief The size type used by the container.
             */
            typedef typename ContainerType::SizeType       SizeType;

            /**
             * \brief Mutable element value reference type.
             */
            typedef ValueType&                             Reference;

            /**
             * \brief Constant element value reference type (as defined by the container).
             */
            typedef typename ContainerType::ConstReference ConstReference;

            /**
             * \brief Underlying associative-array type of the container (typically a \c std::map / \c std::unordered_map specialization).
             */
            typedef typename ContainerType::ArrayType      ArrayType;

            /**
             * \brief Constructs the proxy for the (\a key, value) entry of the sparse container \a c.
             * \param c The sparse container.
             * \param key The key of the addressed entry.
             */
            SparseContainerElement(ContainerType& c, KeyType key):
                cntnr(c), key(key) {}

            /**
             * \brief Copies the value pointed to by \a p into the entry pointed to by this proxy.
             * \param p The source proxy.
             * \return A reference to itself.
             */
            SparseContainerElement& operator=(const SparseContainerElement& p)
            {
                p.get();
                set(p.value);

                return *this;
            }

            /**
             * \brief Assigns the value \a d to the entry pointed to by this proxy.
             *
             * If \a d equals the default-constructed value, the entry is removed from the underlying sparse storage.
             *
             * \tparam D The type of the assigned value (convertible to ValueType).
             * \param d The value to assign.
             * \return A reference to itself.
             */
            template <typename D>
            SparseContainerElement& operator=(const D& d)
            {
                set(d);

                return *this;
            }

            /**
             * \brief Adds \a d to the value of the entry pointed to by this proxy.
             * \tparam D The type of the addend (must support \c value \c += \c d).
             * \param d The value to add.
             * \return A reference to itself.
             */
            template <typename D>
            SparseContainerElement& operator+=(const D& d)
            {
                get();
                value += d;
                set(value);

                return *this;
            }

            /**
             * \brief Subtracts \a d from the value of the entry pointed to by this proxy.
             * \tparam D The type of the subtrahend (must support \c value \c -= \c d).
             * \param d The value to subtract.
             * \return A reference to itself.
             */
            template <typename D>
            SparseContainerElement& operator-=(const D& d)
            {
                get();
                value -= d;
                set(value);

                return *this;
            }

            /**
             * \brief Multiplies the value of the entry pointed to by this proxy by \a d.
             * \tparam D The type of the multiplier (must support \c value \c *= \c d).
             * \param d The multiplier.
             * \return A reference to itself.
             */
            template <typename D>
            SparseContainerElement& operator*=(const D& d)
            {
                get();
                value *= d;
                set(value);

                return *this;
            }

            /**
             * \brief Divides the value of the entry pointed to by this proxy by \a d.
             * \tparam D The type of the divisor (must support \c value \c /= \c d).
             * \param d The divisor.
             * \return A reference to itself.
             */
            template <typename D>
            SparseContainerElement& operator/=(const D& d)
            {
                get();
                value /= d;
                set(value);

                return *this;
            }

            /**
             * \brief Tests the value of the entry pointed to by this proxy for equality with \a d.
             * \tparam D The type of the right-hand side (must support \c value \c == \c d).
             * \param d The value to compare against.
             * \return \c true if the entry's value equals \a d, and \c false otherwise.
             */
            template <typename D>
            bool operator==(const D& d) const
            {
                get();

                return (value == d);
            }

            /**
             * \brief Tests the value of the entry pointed to by this proxy for inequality with \a d.
             * \tparam D The type of the right-hand side (must support \c value \c != \c d).
             * \param d The value to compare against.
             * \return \c true if the entry's value differs from \a d, and \c false otherwise.
             */
            template <typename D>
            bool operator!=(const D& d) const
            {
                get();

                return (value != d);
            }

            /**
             * \brief Implicit conversion to a \c const reference to the value of the entry pointed to by this proxy
             *        (returns a default-constructed value when the entry does not exist in the underlying storage).
             * \return A \c const reference to the value.
             */
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
