/* 
 * MatrixAdapter.hpp 
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
 * \brief Provides matrix adapter classes.
 */

#ifndef CDPL_MATH_MATRIXADAPTER_HPP
#define CDPL_MATH_MATRIXADAPTER_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename T>
        class Range;

        /** \brief Tag selecting the lower-triangular view (entries strictly above the diagonal read as zero) for Math::TriangularAdapter. */
        struct Lower
        {

            template <typename M>
            static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j)
            {
                if (i >= j)
                    return m.getData()(i, j);

                return m.zero;
            }
        };

        /** \brief Tag selecting the unit-lower-triangular view (zero above the diagonal, one on the diagonal) for Math::TriangularAdapter. */
        struct UnitLower
        {

            template <typename M>
            static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j)
            {
                if (i == j)
                    return m.one;

                if (i >= j)
                    return m.getData()(i, j);

                return m.zero;
            }
        };

        /** \brief Tag selecting the upper-triangular view (entries strictly below the diagonal read as zero) for Math::TriangularAdapter. */
        struct Upper
        {

            template <typename M>
            static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j)
            {
                if (i <= j)
                    return m.getData()(i, j);

                return m.zero;
            }
        };

        /** \brief Tag selecting the unit-upper-triangular view (zero below the diagonal, one on the diagonal) for Math::TriangularAdapter. */
        struct UnitUpper
        {

            template <typename M>
            static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j)
            {
                if (i == j)
                    return m.one;

                if (i <= j)
                    return m.getData()(i, j);

                return m.zero;
            }
        };

        /**
         * \brief Matrix expression that exposes only the triangular part of an underlying matrix \a M selected by the policy \a Tri (Math::Lower, Math::UnitLower, Math::Upper or Math::UnitUpper).
         * \tparam M The wrapped matrix type.
         * \tparam Tri The triangular-view selection policy.
         */
        template <typename M, typename Tri>
        class TriangularAdapter : public MatrixExpression<TriangularAdapter<M, Tri> >
        {

            typedef TriangularAdapter<M, Tri> SelfType;

            friend struct Lower;
            friend struct UnitLower;
            friend struct Upper;
            friend struct UnitUpper;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                        MatrixType;
            /** \brief The triangular-view selection policy. */
            typedef Tri                                                      TriangularType;
            /** \brief The size type used by the underlying matrix. */
            typedef typename M::SizeType                                     SizeType;
            /** \brief The signed difference type used by the underlying matrix. */
            typedef typename M::DifferenceType                               DifferenceType;
            /** \brief The element value type of the underlying matrix. */
            typedef typename M::ValueType                                    ValueType;
            /** \brief Constant reference type to an element of the underlying matrix. */
            typedef typename M::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped matrix internally (mutable or const flavor). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            /** \brief Constant closure type used when this adapter appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this adapter appears inside another expression. */
            typedef SelfType                                                 ClosureType;
            /** \brief The Math::Range type used to address sub-ranges. */
            typedef Range<SizeType>                                          RangeType;

            /**
             * \brief Constructs the adapter wrapping \a m.
             * \param m The matrix to be viewed through the triangular policy.
             */
            explicit TriangularAdapter(MatrixType& m):
                data(m) {}

            /**
             * \brief Returns the value of element (\a i, \a j) as seen through the triangular policy
             *        (off-policy entries return the appropriate fill value: zero or one).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The element value as defined by the triangular-view policy.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return TriangularType::template get<SelfType>(*this, i, j);
            }

            /**
             * \brief Returns the number of rows of the wrapped matrix.
             * \return The row count.
             */
            SizeType getSize1() const
            {
                return data.getSize1();
            }

            /**
             * \brief Returns the number of columns of the wrapped matrix.
             * \return The column count.
             */
            SizeType getSize2() const
            {
                return data.getSize2();
            }

            /**
             * \brief Returns a reference to the wrapped matrix (via its stored closure).
             * \return A reference to the wrapped matrix closure.
             */
            MatrixClosureType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the wrapped matrix (via its stored closure).
             * \return A \c const reference to the wrapped matrix closure.
             */
            const MatrixClosureType& getData() const
            {
                return data;
            }

            /**
             * \brief Tells whether the wrapped matrix is empty (zero rows or zero columns).
             * \return \c true if the wrapped matrix is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (data.getSize1() == 0 || data.getSize2() == 0);
            }

          private:
            MatrixClosureType      data;
            static const ValueType zero;
            static const ValueType one;
        };

        template <typename M, typename Tri>
        const typename TriangularAdapter<M, Tri>::ValueType TriangularAdapter<M, Tri>::zero = TriangularAdapter<M, Tri>::ValueType();

        template <typename M, typename Tri>
        const typename TriangularAdapter<M, Tri>::ValueType TriangularAdapter<M, Tri>::one = TriangularAdapter<M, Tri>::ValueType(1);

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a Math::TriangularAdapter view.
         * \tparam M The wrapped matrix type.
         * \tparam Tri The triangular-view selection policy.
         */
        template <typename M, typename Tri>
        struct VectorTemporaryTraits<TriangularAdapter<M, Tri> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a \c const Math::TriangularAdapter view.
         * \tparam M The wrapped matrix type.
         * \tparam Tri The triangular-view selection policy.
         */
        template <typename M, typename Tri>
        struct VectorTemporaryTraits<const TriangularAdapter<M, Tri> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a Math::TriangularAdapter view.
         * \tparam M The wrapped matrix type.
         * \tparam Tri The triangular-view selection policy.
         */
        template <typename M, typename Tri>
        struct MatrixTemporaryTraits<TriangularAdapter<M, Tri> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a \c const Math::TriangularAdapter view.
         * \tparam M The wrapped matrix type.
         * \tparam Tri The triangular-view selection policy.
         */
        template <typename M, typename Tri>
        struct MatrixTemporaryTraits<const TriangularAdapter<M, Tri> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Creates a Math::TriangularAdapter view of the matrix expression \a e using the triangular policy \a Tri.
         * \tparam Tri The triangular-view selection policy (Math::Lower, Math::UnitLower, Math::Upper or Math::UnitUpper).
         * \tparam E The matrix expression type.
         * \param e The matrix expression to wrap.
         * \return A mutable triangular view of \a e.
         */
        template <typename Tri, typename E>
        TriangularAdapter<E, Tri>
        triang(MatrixExpression<E>& e)
        {
            return TriangularAdapter<E, Tri>(e());
        }

        /**
         * \brief Creates a constant Math::TriangularAdapter view of the matrix expression \a e using the triangular policy \a Tri.
         * \tparam Tri The triangular-view selection policy (Math::Lower, Math::UnitLower, Math::Upper or Math::UnitUpper).
         * \tparam E The matrix expression type.
         * \param e The matrix expression to wrap.
         * \return A constant triangular view of \a e.
         */
        template <typename Tri, typename E>
        TriangularAdapter<const E, Tri>
        triang(const MatrixExpression<E>& e)
        {
            return TriangularAdapter<const E, Tri>(e());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXADAPTER_HPP
