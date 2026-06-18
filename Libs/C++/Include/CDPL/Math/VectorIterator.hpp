/* 
 * VectorIterator.hpp 
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
 * \brief Definition of vector element iterator traits and functions.
 */

#ifndef CDPL_MATH_VECTORITERATOR_HPP
#define CDPL_MATH_VECTORITERATOR_HPP

#include <functional>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Access functor used by Math::VectorIteratorTraits to read mutable vector elements via Util::IndexedElementIterator.
         * \tparam E The vector expression type.
         */
        template <typename E>
        class VectorElementAccessor
        {

            typedef E                     VectorType;
            typedef typename E::SizeType  SizeType;
            typedef typename E::Reference Reference;

          public:
            /**
             * \brief Constructs the accessor referencing the (mutable) vector \a e.
             * \param e The referenced vector.
             */
            VectorElementAccessor(VectorType& e):
                vec(e) {}

            /**
             * \brief Returns a mutable reference to the element at index \a i of the referenced vector.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i) const
            {
                return vec.get()(i);
            }

            /**
             * \brief Tells whether this accessor references the same vector as \a accessor.
             * \param accessor The other accessor.
             * \return \c true if both accessors reference the same vector, and \c false otherwise.
             */
            bool operator==(const VectorElementAccessor& accessor) const
            {
                return (&vec.get() == &accessor.vec.get());
            }

          private:
            std::reference_wrapper<VectorType> vec;
        };

        /**
         * \brief Specialization of Math::VectorElementAccessor for const vector references (read-only iteration).
         * \tparam E The vector expression type.
         */
        template <typename E>
        class VectorElementAccessor<const E>
        {

            typedef E                          VectorType;
            typedef typename E::SizeType       SizeType;
            typedef typename E::ConstReference Reference;

          public:
            /**
             * \brief Constructs the accessor from a mutable-vector accessor (relaxing it to read-only access).
             * \param accessor The source mutable accessor.
             */
            VectorElementAccessor(const VectorElementAccessor<E>& accessor):
                vec(accessor.vec) {}

            /**
             * \brief Constructs the accessor referencing the constant vector \a e.
             * \param e The referenced vector.
             */
            VectorElementAccessor(const VectorType& e):
                vec(e) {}

            /**
             * \brief Returns a \c const reference to the element at index \a i of the referenced vector.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             */
            Reference operator()(SizeType i) const
            {
                return vec.get()(i);
            }

            /**
             * \brief Tells whether this accessor references the same vector as \a accessor.
             * \param accessor The other accessor.
             * \return \c true if both accessors reference the same vector, and \c false otherwise.
             */
            bool operator==(const VectorElementAccessor& accessor) const
            {
                return (&vec.get() == &accessor.vec.get());
            }

            /**
             * \brief Rebinds this accessor to the vector referenced by \a accessor.
             * \param accessor The source accessor.
             * \return A reference to itself.
             */
            VectorElementAccessor& operator=(const VectorElementAccessor<E>& accessor)
            {
                vec = std::reference_wrapper<const VectorType>(accessor.vec);
                return *this;
            }

          private:
            std::reference_wrapper<const VectorType> vec;
        };

        /**
         * \brief Traits selecting the element accessor and Util::IndexedElementIterator specialization for mutable iteration over \a E.
         * \tparam E The vector expression type.
         */
        template <typename E>
        struct VectorIteratorTraits
        {

            /**
             * \brief The (mutable) vector expression type being iterated.
             */
            typedef E                                                               VectorType;

            /**
             * \brief The size type used by the iterated vector.
             */
            typedef typename E::SizeType                                            SizeType;

            /**
             * \brief The element value type of the iterated vector.
             */
            typedef typename E::ValueType                                           ValueType;

            /**
             * \brief The element-access functor type used to materialize iterator references.
             */
            typedef VectorElementAccessor<E>                                        AccessorType;

            /**
             * \brief The constructed iterator type (a Util::IndexedElementIterator specialization).
             */
            typedef Util::IndexedElementIterator<ValueType, AccessorType, SizeType> IteratorType;

            /**
             * \brief Creates an iterator pointing to the element at index \a idx of \a e.
             * \param e The vector expression.
             * \param idx The zero-based index of the element to point to.
             * \return The constructed iterator.
             */
            static IteratorType makeIterator(VectorType& e, SizeType idx)
            {
                return IteratorType(AccessorType(e), idx);
            }
        };

        /**
         * \brief Specialization of Math::VectorIteratorTraits for read-only iteration over \a E.
         * \tparam E The vector expression type.
         */
        template <typename E>
        struct VectorIteratorTraits<const E>
        {

            /**
             * \brief The constant vector expression type being iterated.
             */
            typedef E                                                                     VectorType;

            /**
             * \brief The size type used by the iterated vector.
             */
            typedef typename E::SizeType                                                  SizeType;

            /**
             * \brief The element value type of the iterated vector.
             */
            typedef typename E::ValueType                                                 ValueType;

            /**
             * \brief The element-access functor type used to materialize iterator references (const-qualified).
             */
            typedef VectorElementAccessor<const E>                                        AccessorType;

            /**
             * \brief The constructed constant iterator type (a Util::IndexedElementIterator specialization).
             */
            typedef Util::IndexedElementIterator<const ValueType, AccessorType, SizeType> IteratorType;

            /**
             * \brief Creates a constant iterator pointing to the element at index \a idx of \a e.
             * \param e The vector expression.
             * \param idx The zero-based index of the element to point to.
             * \return The constructed iterator.
             */
            static IteratorType makeIterator(const VectorType& e, SizeType idx)
            {
                return IteratorType(AccessorType(e), idx);
            }
        };

        /**
         * \brief Returns a mutable iterator pointing to the first element of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A mutable iterator pointing to the first element.
         */
        template <typename E>
        typename VectorIteratorTraits<E>::IteratorType vectorBegin(VectorExpression<E>& e)
        {
            return VectorIteratorTraits<E>::makeIterator(e(), 0);
        }

        /**
         * \brief Returns a mutable iterator pointing one past the last element of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A mutable iterator pointing one past the last element.
         */
        template <typename E>
        typename VectorIteratorTraits<E>::IteratorType vectorEnd(VectorExpression<E>& e)
        {
            return VectorIteratorTraits<E>::makeIterator(e(), e().getSize());
        }

        /**
         * \brief Returns a constant iterator pointing to the first element of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A constant iterator pointing to the first element.
         */
        template <typename E>
        typename VectorIteratorTraits<const E>::IteratorType vectorBegin(const VectorExpression<E>& e)
        {
            return VectorIteratorTraits<const E>::makeIterator(e(), 0);
        }

        /**
         * \brief Returns a constant iterator pointing one past the last element of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A constant iterator pointing one past the last element.
         */
        template <typename E>
        typename VectorIteratorTraits<const E>::IteratorType vectorEnd(const VectorExpression<E>& e)
        {
            return VectorIteratorTraits<const E>::makeIterator(e(), e().getSize());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTORITERATOR_HPP
