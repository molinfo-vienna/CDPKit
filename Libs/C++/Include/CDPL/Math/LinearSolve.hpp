/* 
 * LinearSolve.hpp 
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
 * \brief Functions for solving linear equations.
 */

#ifndef CDPL_MATH_LINEARSOLVE_HPP
#define CDPL_MATH_LINEARSOLVE_HPP

#include "CDPL/Math/CommonType.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename E>
        class VectorExpression;
        template <typename E>
        class MatrixExpression;

        /**
         * \brief Solves \f$ L\,x = b \f$ in place by forward-substitution, where \a l is a lower-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The vector expression type of the right-hand side.
         * \param l The lower-triangular coefficient matrix.
         * \param bv The right-hand side vector, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
         */
        template <typename E1, typename E2>
        bool
        solveLower(const MatrixExpression<E1>& l, VectorExpression<E2>& bv)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type   SizeType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

            if (l().getSize1() != l().getSize2())
                return false;

            if (SizeType(l().getSize2()) != SizeType(bv().getSize()))
                return false;

            SizeType size = bv().getSize();

            for (SizeType n = 0; n < size; n++) {
                if (l()(n, n) == typename E1::ValueType(0))
                    return false;

                ValueType t = bv()(n) /= l()(n, n);

                if (t != ValueType(0))
                    for (SizeType m = n + 1; m < size; m++)
                        bv()(m) -= l()(m, n) * t;
            }

            return true;
        }

        /**
         * \brief Solves \f$ L\,x = b \f$ in place by forward-substitution, where \a l is a unit lower-triangular matrix (1 on the diagonal).
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The vector expression type of the right-hand side.
         * \param l The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
         * \param bv The right-hand side vector, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square or dimensions do not match.
         */
        template <typename E1, typename E2>
        bool
        solveUnitLower(const MatrixExpression<E1>& l, VectorExpression<E2>& bv)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type   SizeType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

            if (l().getSize1() != l().getSize2())
                return false;

            if (SizeType(l().getSize2()) != SizeType(bv().getSize()))
                return false;

            SizeType size = bv().getSize();

            for (SizeType n = 0; n < size; n++) {
                ValueType t = bv()(n);

                if (t != ValueType(0))
                    for (SizeType m = n + 1; m < size; m++)
                        bv()(m) -= l()(m, n) * t;
            }

            return true;
        }

        /**
         * \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where \a l is a lower-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The matrix expression type of the right-hand side.
         * \param l The lower-triangular coefficient matrix.
         * \param bm The right-hand side matrix, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
         */
        template <typename E1, typename E2>
        bool
        solveLower(const MatrixExpression<E1>& l, MatrixExpression<E2>& bm)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type   SizeType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

            if (l().getSize1() != l().getSize2())
                return false;

            if (SizeType(l().getSize2()) != SizeType(bm().getSize1()))
                return false;

            SizeType size1 = bm().getSize1();
            SizeType size2 = bm().getSize2();

            for (SizeType n = 0; n < size1; n++) {
                if (l()(n, n) == typename E1::ValueType(0))
                    return false;

                for (SizeType o = 0; o < size2; o++) {
                    ValueType t = bm()(n, o) /= l()(n, n);

                    if (t != ValueType(0))
                        for (SizeType m = n + 1; m < size1; m++)
                            bm()(m, o) -= l()(m, n) * t;
                }
            }

            return true;
        }

        /**
         * \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where \a l is a unit lower-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The matrix expression type of the right-hand side.
         * \param l The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
         * \param bm The right-hand side matrix, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square or dimensions do not match.
         */
        template <typename E1, typename E2>
        bool
        solveUnitLower(const MatrixExpression<E1>& l, MatrixExpression<E2>& bm)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type   SizeType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

            if (l().getSize1() != l().getSize2())
                return false;

            if (SizeType(l().getSize2()) != SizeType(bm().getSize1()))
                return false;

            SizeType size1 = bm().getSize1();
            SizeType size2 = bm().getSize2();

            for (SizeType n = 0; n < size1; n++) {
                for (SizeType o = 0; o < size2; o++) {
                    ValueType t = bm()(n, o);

                    if (t != ValueType(0))
                        for (SizeType m = n + 1; m < size1; m++)
                            bm()(m, o) -= l()(m, n) * t;
                }
            }

            return true;
        }

        /**
         * \brief Solves \f$ U\,x = b \f$ in place by back-substitution, where \a u is an upper-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The vector expression type of the right-hand side.
         * \param u The upper-triangular coefficient matrix.
         * \param bv The right-hand side vector, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
         */
        template <typename E1, typename E2>
        bool
        solveUpper(const MatrixExpression<E1>& u, VectorExpression<E2>& bv)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type           ValueType;

            if (u().getSize1() != u().getSize2())
                return false;

            if (SizeType(u().getSize2()) != SizeType(bv().getSize()))
                return false;

            SizeType size = bv().getSize();

            for (DifferenceType n = size - 1; n >= 0; n--) {
                if (u()(n, n) == typename E1::ValueType(0))
                    return false;

                ValueType t = bv()(n) /= u()(n, n);

                if (t != ValueType(0))
                    for (DifferenceType m = n - 1; m >= 0; m--)
                        bv()(m) -= u()(m, n) * t;
            }

            return true;
        }

        /**
         * \brief Solves \f$ U\,x = b \f$ in place by back-substitution, where \a u is a unit upper-triangular matrix (1 on the diagonal).
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The vector expression type of the right-hand side.
         * \param u The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
         * \param bv The right-hand side vector, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square or dimensions do not match.
         */
        template <typename E1, typename E2>
        bool
        solveUnitUpper(const MatrixExpression<E1>& u, VectorExpression<E2>& bv)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type           ValueType;

            if (u().getSize1() != u().getSize2())
                return false;

            if (SizeType(u().getSize2()) != SizeType(bv().getSize()))
                return false;

            SizeType size = bv().getSize();

            for (DifferenceType n = size - 1; n >= 0; n--) {
                ValueType t = bv()(n);

                if (t != ValueType(0))
                    for (DifferenceType m = n - 1; m >= 0; m--)
                        bv()(m) -= u()(m, n) * t;
            }

            return true;
        }

        /**
         * \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where \a u is an upper-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The matrix expression type of the right-hand side.
         * \param u The upper-triangular coefficient matrix.
         * \param bm The right-hand side matrix, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
         */
        template <typename E1, typename E2>
        bool
        solveUpper(const MatrixExpression<E1>& u, MatrixExpression<E2>& bm)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type           ValueType;

            if (u().getSize1() != u().getSize2())
                return false;

            if (SizeType(u().getSize2()) != SizeType(bm().getSize1()))
                return false;

            SizeType size1 = bm().getSize1();
            SizeType size2 = bm().getSize2();

            for (DifferenceType n = size1 - 1; n >= 0; n--) {
                if (u()(n, n) == typename E1::ValueType(0))
                    return false;

                for (DifferenceType o = size2 - 1; o >= 0; o--) {
                    ValueType t = bm()(n, o) /= u()(n, n);

                    if (t != ValueType(0))
                        for (DifferenceType m = n - 1; m >= 0; m--)
                            bm()(m, o) -= u()(m, n) * t;
                }
            }

            return true;
        }

        /**
         * \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where \a u is a unit upper-triangular matrix.
         * \tparam E1 The matrix expression type of the coefficient matrix.
         * \tparam E2 The matrix expression type of the right-hand side.
         * \param u The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
         * \param bm The right-hand side matrix, overwritten with the solution.
         * \return \c true if the substitution succeeded, and \c false if the system is not square or dimensions do not match.
         */
        template <typename E1, typename E2>
        bool
        solveUnitUpper(const MatrixExpression<E1>& u, MatrixExpression<E2>& bm)
        {
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
            typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type           ValueType;

            if (u().getSize1() != u().getSize2())
                return false;

            if (SizeType(u().getSize2()) != SizeType(bm().getSize1()))
                return false;

            SizeType size1 = bm().getSize1();
            SizeType size2 = bm().getSize2();

            for (DifferenceType n = size1 - 1; n >= 0; n--) {
                for (DifferenceType o = size2 - 1; o >= 0; o--) {
                    ValueType t = bm()(n, o);

                    if (t != ValueType(0))
                        for (DifferenceType m = n - 1; m >= 0; m--)
                            bm()(m, o) -= u()(m, n) * t;
                }
            }

            return true;
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_LINEARSOLVE_HPP
