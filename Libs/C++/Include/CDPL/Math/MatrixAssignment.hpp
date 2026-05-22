/* 
 * MatrixAssignment.hpp 
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
 * \brief Implementation of matrix assignment routines.
 */

#ifndef CDPL_MATH_MATRIXASSIGNMENT_HPP
#define CDPL_MATH_MATRIXASSIGNMENT_HPP

#include <utility>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename E>
        class MatrixExpression;

        /**
         * \brief Applies the element-wise functor \a F to every (matrix element, source element) pair, i.e. \c F::apply(m(i,j), e()(i,j)).
         * \tparam F The element-wise binary functor template.
         * \tparam M The destination matrix container type.
         * \tparam E The source matrix expression type.
         * \param m The destination matrix.
         * \param e The source matrix expression.
         * \throw Base::SizeError if the dimensions of \a m and \a e differ.
         */
        template <template <typename T1, typename T2> class F, typename M, typename E>
        void matrixAssignMatrix(M& m, const MatrixExpression<E>& e)
        {
            typedef typename CommonType<typename M::SizeType, typename E::SizeType>::Type SizeType;

            SizeType size1 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(m.getSize1()), SizeType(e().getSize1()), Base::SizeError);
            SizeType size2 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(m.getSize2()), SizeType(e().getSize2()), Base::SizeError);

            typedef F<typename M::Reference, typename E::ValueType> FunctorType;

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    FunctorType::apply(m(i, j), e()(i, j));
        }

        /**
         * \brief Applies the element-wise functor \a F to every (matrix element, scalar) pair, i.e. \c F::apply(m(i,j), t).
         * \tparam F The element-wise binary functor template.
         * \tparam M The destination matrix container type.
         * \tparam T The scalar type.
         * \param m The destination matrix.
         * \param t The scalar value applied to every element.
         */
        template <template <typename T1, typename T2> class F, typename M, typename T>
        void matrixAssignScalar(M& m, const T& t)
        {
            typedef F<typename M::Reference, T> FunctorType;
            typedef typename M::SizeType        SizeType;

            SizeType size1 = m.getSize1();
            SizeType size2 = m.getSize2();

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    FunctorType::apply(m(i, j), t);
        }

        /**
         * \brief Swaps the elements of two equally sized matrix expressions element by element.
         * \tparam M The first matrix container type.
         * \tparam E The second matrix expression type.
         * \param m The first matrix.
         * \param e The second matrix expression.
         * \throw Base::SizeError if the dimensions of \a m and \a e differ.
         */
        template <typename M, typename E>
        void matrixSwap(M& m, MatrixExpression<E>& e)
        {
            typedef typename CommonType<typename M::SizeType, typename E::SizeType>::Type SizeType;

            SizeType size1 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(m.getSize1()), SizeType(e().getSize1()), Base::SizeError);
            SizeType size2 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(m.getSize2()), SizeType(e().getSize2()), Base::SizeError);

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    std::swap(m(i, j), e()(i, j));
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXASSIGNMENT_HPP
