/* 
 * LUDecomposition.hpp 
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
 * \brief Implementation of matrix LU-decomposition and associated operations.
 */

#ifndef CDPL_MATH_LUDECOMPOSITION_HPP
#define CDPL_MATH_LUDECOMPOSITION_HPP

#include <algorithm>

#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/LinearSolve.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Computes an in-place LU decomposition of the matrix \a e without partial pivoting.
         * \tparam E The matrix expression type.
         * \param e The matrix to decompose (modified in place).
         * \return The 1-based row index of the first singular pivot, or \e 0 if the matrix is non-singular.
         */
        template <typename E>
        typename E::SizeType
        luDecompose(MatrixExpression<E>& e)
        {
            typedef typename E::SizeType                              SizeType;
            typedef typename E::ValueType                             ValueType;
            typedef typename MatrixRange<E>::RangeType                MatrixRangeType;
            typedef typename VectorRange<MatrixRow<E> >::RangeType    RowRangeType;
            typedef typename VectorRange<MatrixColumn<E> >::RangeType ColumnRangeType;

            SizeType size1 = e().getSize1();
            SizeType size2 = e().getSize2();
            SizeType size  = std::min(size1, size2);

            if (size == 0)
                return 0;

            SizeType singular = 0;

            for (SizeType i = 0; i < size; i++) {
                MatrixColumn<E> col_i(column(e, i));
                MatrixRow<E>    row_i(row(e, i));

                if (e()(i, i) != ValueType(0)) {
                    ValueType m_inv = ValueType(1) / e()(i, i);
                    range(col_i, ColumnRangeType(i + 1, size1)) *= m_inv;

                } else if (singular == 0)
                    singular = i + 1;

                range(e, MatrixRangeType(i + 1, size1), MatrixRangeType(i + 1, size2))
                    .minusAssign(outerProd(range(col_i, ColumnRangeType(i + 1, size1)),
                                           range(row_i, RowRangeType(i + 1, size2))));
            }

            return singular;
        }

        /**
         * \brief Computes an in-place LU decomposition of the matrix \a e with partial (row) pivoting.
         * \tparam E The matrix expression type.
         * \tparam PV The permutation-vector type (must support indexed write access).
         * \tparam T An arithmetic counter type.
         * \param e The matrix to decompose (modified in place).
         * \param pv The output permutation vector recording the row pivots (\a pv[i] = pivot row index for step \a i).
         * \param num_row_swaps The output count of executed row swaps.
         * \return The 1-based row index of the first singular pivot, or \e 0 if the matrix is non-singular.
         */
        template <typename E, typename PV, typename T>
        typename E::SizeType
        luDecompose(MatrixExpression<E>& e, PV& pv, T& num_row_swaps)
        {
            typedef typename E::SizeType                              SizeType;
            typedef typename E::ValueType                             ValueType;
            typedef typename MatrixRange<E>::RangeType                MatrixRangeType;
            typedef typename VectorRange<MatrixRow<E> >::RangeType    RowRangeType;
            typedef typename VectorRange<MatrixColumn<E> >::RangeType ColumnRangeType;

            SizeType size1 = e().getSize1();
            SizeType size2 = e().getSize2();
            SizeType size  = std::min(size1, size2);

            num_row_swaps = 0;

            if (size == 0)
                return 0;

            SizeType singular = 0;

            for (SizeType i = 0; i < size; i++) {
                MatrixColumn<E> col_i(column(e, i));
                MatrixRow<E>    row_i(row(e, i));
                SizeType        norm_inf_idx = i + normInfIndex(range(col_i, ColumnRangeType(i, size1)));

                if (e()(norm_inf_idx, i) != ValueType(0)) {
                    pv[i] = norm_inf_idx;

                    if (norm_inf_idx != i) {
                        row(e, norm_inf_idx).swap(row_i);
                        num_row_swaps++;
                    }

                    ValueType m_inv = ValueType(1) / e()(i, i);
                    range(col_i, ColumnRangeType(i + 1, size1)) *= m_inv;

                } else if (singular == 0)
                    singular = i + 1;

                range(e, MatrixRangeType(i + 1, size1), MatrixRangeType(i + 1, size2))
                    .minusAssign(outerProd(range(col_i, ColumnRangeType(i + 1, size1)),
                                           range(row_i, RowRangeType(i + 1, size2))));
            }

            return singular;
        }

        /**
         * \brief Applies the permutation vector \a pv to the vector expression \a e by swapping element \a i with element \a pv[i].
         * \tparam E The vector expression type.
         * \tparam PV The permutation-vector type.
         * \param e The vector to permute in place.
         * \param pv The permutation vector.
         */
        template <typename E, typename PV>
        void
        swapRows(VectorExpression<E>& e, const PV& pv)
        {
            typedef typename E::SizeType SizeType;

            for (SizeType i = 0, size = e().getSize(); i < size; i++) {
                if (i != SizeType(pv[i]))
                    std::swap(e()(i), e()(pv[i]));
            }
        }

        /**
         * \brief Applies the permutation vector \a pv to the rows of the matrix expression \a e by swapping row \a i with row \a pv[i].
         * \tparam E The matrix expression type.
         * \tparam PV The permutation-vector type.
         * \param e The matrix to permute in place.
         * \param pv The permutation vector.
         */
        template <typename E, typename PV>
        void
        swapRows(MatrixExpression<E>& e, const PV& pv)
        {
            typedef typename E::SizeType SizeType;

            for (SizeType i = 0, size = e().getSize1(); i < size; i++) {
                if (i != SizeType(pv[i])) {
                    MatrixRow<E> other_row(e(), pv[i]);
                    row(e, i).swap(other_row);
                }
            }
        }

        /**
         * \brief Solves \f$ LU\,x = b \f$ for \a b in place, given the LU decomposition \a lu (without pivoting).
         * \tparam E1 The matrix expression type of \a lu.
         * \tparam E2 The vector expression type of \a b.
         * \param lu The LU decomposition.
         * \param b The right-hand side vector, overwritten with the solution.
         * \return \c true if the back-substitution succeeded, and \c false if a zero pivot was encountered.
         */
        template <typename E1, typename E2>
        bool
        luSubstitute(const MatrixExpression<E1>& lu, VectorExpression<E2>& b)
        {
            if (!solveUnitLower(lu, b))
                return false;

            return solveUpper(lu, b);
        }

        /**
         * \brief Solves \f$ LU\,x = b \f$ for \a b in place, given the LU decomposition \a lu and pivot vector \a pv.
         * \tparam E1 The matrix expression type of \a lu.
         * \tparam E2 The vector expression type of \a b.
         * \tparam PV The permutation-vector type.
         * \param lu The LU decomposition (with pivoting).
         * \param pv The permutation vector recorded during the LU decomposition.
         * \param b The right-hand side vector, overwritten with the solution.
         * \return \c true if the back-substitution succeeded, and \c false if a zero pivot was encountered.
         */
        template <typename E1, typename E2, typename PV>
        bool
        luSubstitute(const MatrixExpression<E1>& lu, const PV& pv, VectorExpression<E2>& b)
        {
            swapRows(b, pv);

            return luSubstitute(lu, b);
        }

        /**
         * \brief Solves \f$ LU\,X = B \f$ for the matrix \a b in place, given the LU decomposition \a lu (without pivoting).
         * \tparam E1 The matrix expression type of \a lu.
         * \tparam E2 The matrix expression type of \a b.
         * \param lu The LU decomposition.
         * \param b The right-hand side matrix, overwritten with the solution.
         * \return \c true if the back-substitution succeeded, and \c false if a zero pivot was encountered.
         */
        template <typename E1, typename E2>
        bool
        luSubstitute(const MatrixExpression<E1>& lu, MatrixExpression<E2>& b)
        {
            if (!solveUnitLower(lu, b))
                return false;

            return solveUpper(lu, b);
        }

        /**
         * \brief Solves \f$ LU\,X = B \f$ for the matrix \a b in place, given the LU decomposition \a lu and pivot vector \a pv.
         * \tparam E1 The matrix expression type of \a lu.
         * \tparam E2 The matrix expression type of \a b.
         * \tparam PV The permutation-vector type.
         * \param lu The LU decomposition (with pivoting).
         * \param pv The permutation vector recorded during the LU decomposition.
         * \param b The right-hand side matrix, overwritten with the solution.
         * \return \c true if the back-substitution succeeded, and \c false if a zero pivot was encountered.
         */
        template <typename E1, typename E2, typename PV>
        bool
        luSubstitute(const MatrixExpression<E1>& lu, const PV& pv, MatrixExpression<E2>& b)
        {
            swapRows(b, pv);

            return luSubstitute(lu, b);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_LUDECOMPOSITION_HPP
