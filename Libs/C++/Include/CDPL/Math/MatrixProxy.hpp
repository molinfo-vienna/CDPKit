/* 
 * MatrixProxy.hpp 
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
 * \brief Definition of matrix proxy types.
 */

#ifndef CDPL_MATH_MATRIXPROXY_HPP
#define CDPL_MATH_MATRIXPROXY_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/Range.hpp"
#include "CDPL/Math/Slice.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Vector-expression proxy that views a single row of an underlying matrix.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixRow : public VectorExpression<MatrixRow<M> >
        {

            typedef MatrixRow<M> SelfType;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                        MatrixType;
            /** \brief The size type used by the wrapped matrix. */
            typedef typename M::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped matrix. */
            typedef typename M::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped matrix. */
            typedef typename M::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename M::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped matrix internally (mutable or const flavor). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the row proxy viewing row \a i of \a m.
             * \param m The wrapped matrix.
             * \param i The zero-based row index to view.
             */
            MatrixRow(MatrixType& m, SizeType i):
                data(m), index(i) {}

            /**
             * \brief Returns a mutable reference to the element at column \a i of the row.
             * \param i The zero-based column index.
             * \return A mutable reference to the underlying element <tt>m(index, i)</tt>.
             */
            Reference operator()(SizeType i)
            {
                return data(index, i);
            }

            /**
             * \brief Returns a \c const reference to the element at column \a i of the row.
             * \param i The zero-based column index.
             * \return A \c const reference to the underlying element <tt>m(index, i)</tt>.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(index, i);
            }

            /**
             * \brief Returns a mutable reference to the element at column \a i of the row (alias for operator()).
             * \param i The zero-based column index.
             * \return A mutable reference to the underlying element.
             */
            Reference operator[](SizeType i)
            {
                return data(index, i);
            }

            /**
             * \brief Returns a \c const reference to the element at column \a i of the row (alias for operator()).
             * \param i The zero-based column index.
             * \return A \c const reference to the underlying element.
             */
            ConstReference operator[](SizeType i) const
            {
                return data(index, i);
            }

            /**
             * \brief Returns the row index this proxy refers to within the wrapped matrix.
             * \return The zero-based row index.
             */
            SizeType getIndex() const
            {
                return index;
            }

            /**
             * \brief Returns the size of the row (number of columns of the wrapped matrix).
             * \return The number of columns.
             */
            SizeType getSize() const
            {
                return data.getSize2();
            }

            /**
             * \brief Tells whether the row is empty (the wrapped matrix has zero columns).
             * \return \c true if the wrapped matrix has zero columns, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (data.getSize2() == 0);
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
             * \brief Copy-assigns the contents of \a r to this row (via a temporary to handle aliasing).
             * \param r The source row.
             * \return A reference to itself.
             */
            MatrixRow& operator=(const MatrixRow& r)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(r));
                return *this;
            }

            /**
             * \brief Assigns the elements of the vector expression \a e to this row (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this row (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this row (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this row by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRow>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this row by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRow>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the vector expression \a e to this row without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this row without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this row without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRow& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this row with those of \a r (via element-wise swap of the underlying matrix elements).
             * \param r The row to swap with.
             */
            void swap(MatrixRow& r)
            {
                if (this != &r)
                    vectorSwap(*this, r);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first row.
             * \param r2 The second row.
             */
            friend void swap(MatrixRow& r1, MatrixRow& r2)
            {
                r1.swap(r2);
            }

          private:
            MatrixClosureType data;
            SizeType          index;
        };

        /**
         * \brief Vector-expression proxy that views a single column of an underlying matrix.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixColumn : public VectorExpression<MatrixColumn<M> >
        {

            typedef MatrixColumn<M> SelfType;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                        MatrixType;
            /** \brief The size type used by the wrapped matrix. */
            typedef typename M::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped matrix. */
            typedef typename M::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped matrix. */
            typedef typename M::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename M::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped matrix internally. */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the column proxy viewing column \a i of \a m.
             * \param m The wrapped matrix.
             * \param i The zero-based column index to view.
             */
            MatrixColumn(MatrixType& m, SizeType i):
                data(m), index(i) {}

            /**
             * \brief Returns a mutable reference to the element at row \a i of the column.
             * \param i The zero-based row index.
             * \return A mutable reference to the underlying element <tt>m(i, index)</tt>.
             */
            Reference operator()(SizeType i)
            {
                return data(i, index);
            }

            /**
             * \brief Returns a \c const reference to the element at row \a i of the column.
             * \param i The zero-based row index.
             * \return A \c const reference to the underlying element <tt>m(i, index)</tt>.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(i, index);
            }

            /**
             * \brief Returns a mutable reference to the element at row \a i of the column (alias for operator()).
             * \param i The zero-based row index.
             * \return A mutable reference to the underlying element.
             */
            Reference operator[](SizeType i)
            {
                return data(i, index);
            }

            /**
             * \brief Returns a \c const reference to the element at row \a i of the column (alias for operator()).
             * \param i The zero-based row index.
             * \return A \c const reference to the underlying element.
             */
            ConstReference operator[](SizeType i) const
            {
                return data(i, index);
            }

            /**
             * \brief Returns the column index this proxy refers to within the wrapped matrix.
             * \return The zero-based column index.
             */
            SizeType getIndex() const
            {
                return index;
            }

            /**
             * \brief Returns the size of the column (number of rows of the wrapped matrix).
             * \return The number of rows.
             */
            SizeType getSize() const
            {
                return data.getSize1();
            }

            /**
             * \brief Tells whether the column is empty (the wrapped matrix has zero rows).
             * \return \c true if the wrapped matrix has zero rows, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (data.getSize1() == 0);
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
             * \brief Copy-assigns the contents of \a c to this column (via a temporary to handle aliasing).
             * \param c The source column.
             * \return A reference to itself.
             */
            MatrixColumn& operator=(const MatrixColumn& c)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(c));
                return *this;
            }

            /**
             * \brief Assigns the elements of the vector expression \a e to this column (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this column (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this column (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this column by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixColumn>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this column by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixColumn>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the vector expression \a e to this column without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this column without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this column without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixColumn& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this column with those of \a c (via element-wise swap of the underlying matrix elements).
             * \param c The column to swap with.
             */
            void swap(MatrixColumn& c)
            {
                if (this != &c)
                    vectorSwap(*this, c);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param c1 The first column.
             * \param c2 The second column.
             */
            friend void swap(MatrixColumn& c1, MatrixColumn& c2)
            {
                c1.swap(c2);
            }

          private:
            MatrixClosureType data;
            SizeType          index;
        };

        /**
         * \brief Matrix-expression proxy that views a contiguous rectangular subrange of an underlying matrix.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixRange : public MatrixExpression<MatrixRange<M> >
        {

            typedef MatrixRange<M> SelfType;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                        MatrixType;
            /** \brief The size type used by the wrapped matrix. */
            typedef typename M::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped matrix. */
            typedef typename M::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped matrix. */
            typedef typename M::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename M::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped matrix internally. */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;
            /** \brief Range type used to specify the row and column index ranges. */
            typedef Range<SizeType>                                          RangeType;

            /**
             * \brief Constructs the matrix range proxy viewing rows in \a r1 and columns in \a r2 of \a m.
             * \param m The wrapped matrix.
             * \param r1 The row index range.
             * \param r2 The column index range.
             */
            MatrixRange(MatrixType& m, const RangeType& r1, const RangeType& r2):
                data(m), range1(r1), range2(r2) {}

            /**
             * \brief Returns a mutable reference to the element at proxy index (\a i, \a j).
             * \param i The zero-based proxy row index.
             * \param j The zero-based proxy column index.
             * \return A mutable reference to the underlying element <tt>m(r1(i), r2(j))</tt>.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                return data(range1(i), range2(j));
            }

            /**
             * \brief Returns a \c const reference to the element at proxy index (\a i, \a j).
             * \param i The zero-based proxy row index.
             * \param j The zero-based proxy column index.
             * \return A \c const reference to the underlying element <tt>m(r1(i), r2(j))</tt>.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(range1(i), range2(j));
            }

            /**
             * \brief Returns the row index range's start index in the wrapped matrix.
             * \return The start row index.
             */
            SizeType getStart1() const
            {
                return range1.getStart();
            }

            /**
             * \brief Returns the column index range's start index in the wrapped matrix.
             * \return The start column index.
             */
            SizeType getStart2() const
            {
                return range2.getStart();
            }

            /**
             * \brief Returns the number of rows in the proxy (size of the row range).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return range1.getSize();
            }

            /**
             * \brief Returns the number of columns in the proxy (size of the column range).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return range2.getSize();
            }

            /**
             * \brief Tells whether the proxy is empty (either range has size zero).
             * \return \c true if either range has zero size, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (range1.getSize() == SizeType(0) || range2.getSize() == SizeType(0));
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
             * \brief Copy-assigns the contents of \a r to this matrix range (via a temporary to handle aliasing).
             * \param r The source matrix range.
             * \return A reference to itself.
             */
            MatrixRange& operator=(const MatrixRange& r)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(r));
                return *this;
            }

            /**
             * \brief Assigns the elements of the matrix expression \a e to this matrix range (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& operator=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix range (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& operator+=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix range (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& operator-=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this matrix range by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRange>::type& operator*=(const T& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this matrix range by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRange>::type& operator/=(const T& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the matrix expression \a e to this matrix range without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& assign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix range without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix range without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixRange& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this matrix range with those of \a r (via element-wise swap of the underlying matrix elements).
             * \param r The matrix range to swap with.
             */
            void swap(MatrixRange& r)
            {
                if (this != &r)
                    matrixSwap(*this, r);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first matrix range.
             * \param r2 The second matrix range.
             */
            friend void swap(MatrixRange& r1, MatrixRange& r2)
            {
                r1.swap(r2);
            }

          private:
            MatrixClosureType data;
            RangeType         range1;
            RangeType         range2;
        };

        /**
         * \brief Matrix-expression proxy that views a strided rectangular slice of an underlying matrix.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixSlice : public MatrixExpression<MatrixSlice<M> >
        {

            typedef MatrixSlice<M> SelfType;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                        MatrixType;
            /** \brief The size type used by the wrapped matrix. */
            typedef typename M::SizeType                                     SizeType;
            /** \brief The signed difference type used by the wrapped matrix. */
            typedef typename M::DifferenceType                               DifferenceType;
            /** \brief The element value type of the wrapped matrix. */
            typedef typename M::ValueType                                    ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename M::ConstReference                               ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            /** \brief Closure type used to store the wrapped matrix internally. */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                           ConstClosureType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                                 ClosureType;
            /** \brief Slice type used to specify the row and column slices (start, stride, size). */
            typedef Slice<SizeType, DifferenceType>                          SliceType;

            /**
             * \brief Constructs the matrix slice proxy viewing rows in \a s1 and columns in \a s2 of \a m.
             * \param m The wrapped matrix.
             * \param s1 The row slice (start, stride, size).
             * \param s2 The column slice (start, stride, size).
             */
            MatrixSlice(MatrixType& m, const SliceType& s1, const SliceType& s2):
                data(m), slice1(s1), slice2(s2) {}

            /**
             * \brief Returns a mutable reference to the element at proxy index (\a i, \a j).
             * \param i The zero-based proxy row index.
             * \param j The zero-based proxy column index.
             * \return A mutable reference to the underlying element <tt>m(s1(i), s2(j))</tt>.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                return data(slice1(i), slice2(j));
            }

            /**
             * \brief Returns a \c const reference to the element at proxy index (\a i, \a j).
             * \param i The zero-based proxy row index.
             * \param j The zero-based proxy column index.
             * \return A \c const reference to the underlying element <tt>m(s1(i), s2(j))</tt>.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(slice1(i), slice2(j));
            }

            /**
             * \brief Returns the row slice's start index in the wrapped matrix.
             * \return The start row index.
             */
            SizeType getStart1() const
            {
                return slice1.getStart();
            }

            /**
             * \brief Returns the column slice's start index in the wrapped matrix.
             * \return The start column index.
             */
            SizeType getStart2() const
            {
                return slice2.getStart();
            }

            /**
             * \brief Returns the row slice's stride in the wrapped matrix.
             * \return The row stride.
             */
            DifferenceType getStride1() const
            {
                return slice1.getStride();
            }

            /**
             * \brief Returns the column slice's stride in the wrapped matrix.
             * \return The column stride.
             */
            DifferenceType getStride2() const
            {
                return slice2.getStride();
            }

            /**
             * \brief Returns the number of rows in the proxy (size of the row slice).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return slice1.getSize();
            }

            /**
             * \brief Returns the number of columns in the proxy (size of the column slice).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return slice2.getSize();
            }

            /**
             * \brief Tells whether the proxy is empty (either slice has size zero).
             * \return \c true if either slice has zero size, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (slice1.getSize() == SizeType(0) || slice2.getSize() == SizeType(0));
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
             * \brief Copy-assigns the contents of \a s to this matrix slice (via a temporary to handle aliasing).
             * \param s The source matrix slice.
             * \return A reference to itself.
             */
            MatrixSlice& operator=(const MatrixSlice& s)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(s));
                return *this;
            }

            /**
             * \brief Assigns the elements of the matrix expression \a e to this matrix slice (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& operator=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(e));
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix slice (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& operator+=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix slice (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& operator-=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            /**
             * \brief Multiplies every element of this matrix slice by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixSlice>::type& operator*=(const T& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element of this matrix slice by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixSlice>::type& operator/=(const T& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the matrix expression \a e to this matrix slice without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& assign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix slice without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix slice without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixSlice& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this matrix slice with those of \a s (via element-wise swap of the underlying matrix elements).
             * \param s The matrix slice to swap with.
             */
            void swap(MatrixSlice& s)
            {
                if (this != &s)
                    matrixSwap(*this, s);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param s1 The first matrix slice.
             * \param s2 The second matrix slice.
             */
            friend void swap(MatrixSlice& s1, MatrixSlice& s2)
            {
                s1.swap(s2);
            }

          private:
            MatrixClosureType data;
            SliceType         slice1;
            SliceType         slice2;
        };

        /** \brief Vector-temporary trait specialization for Math::MatrixRow — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<MatrixRow<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for \c const Math::MatrixRow — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixRow<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for Math::MatrixRow — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixRow<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for \c const Math::MatrixRow — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixRow<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for Math::MatrixColumn — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<MatrixColumn<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for \c const Math::MatrixColumn — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixColumn<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for Math::MatrixColumn — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixColumn<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for \c const Math::MatrixColumn — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixColumn<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for Math::MatrixRange — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<MatrixRange<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for \c const Math::MatrixRange — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixRange<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for Math::MatrixRange — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixRange<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for \c const Math::MatrixRange — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixRange<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for Math::MatrixSlice — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<MatrixSlice<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Vector-temporary trait specialization for \c const Math::MatrixSlice — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixSlice<M> > : public VectorTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for Math::MatrixSlice — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixSlice<M> > : public MatrixTemporaryTraits<M>
        {};

        /** \brief Matrix-temporary trait specialization for \c const Math::MatrixSlice — inherits the temporary type from the wrapped matrix. */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixSlice<M> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Returns a mutable row proxy for row \a i of the matrix expression \a e.
         * \tparam M The matrix expression type.
         * \param e The matrix expression.
         * \param i The zero-based row index.
         * \return A Math::MatrixRow proxy referring to row \a i of \a e.
         */
        template <typename M>

        MatrixRow<M>
        row(MatrixExpression<M>& e, typename MatrixRow<M>::SizeType i)
        {
            return MatrixRow<M>(e(), i);
        }

        /**
         * \brief Returns a \c const row proxy for row \a i of the matrix expression \a e.
         * \tparam M The matrix expression type.
         * \param e The matrix expression.
         * \param i The zero-based row index.
         * \return A Math::MatrixRow proxy referring to row \a i of \a e.
         */
        template <typename M>
        MatrixRow<const M>
        row(const MatrixExpression<M>& e, typename MatrixRow<const M>::SizeType i)
        {
            return MatrixRow<const M>(e(), i);
        }

        /**
         * \brief Returns a mutable column proxy for column \a j of the matrix expression \a e.
         * \tparam M The matrix expression type.
         * \param e The matrix expression.
         * \param j The zero-based column index.
         * \return A Math::MatrixColumn proxy referring to column \a j of \a e.
         */
        template <typename M>
        MatrixColumn<M>
        column(MatrixExpression<M>& e, typename MatrixColumn<M>::SizeType j)
        {
            return MatrixColumn<M>(e(), j);
        }

        /**
         * \brief Returns a \c const column proxy for column \a j of the matrix expression \a e.
         * \tparam M The matrix expression type.
         * \param e The matrix expression.
         * \param j The zero-based column index.
         * \return A Math::MatrixColumn proxy referring to column \a j of \a e.
         */
        template <typename M>
        MatrixColumn<const M>
        column(const MatrixExpression<M>& e, typename MatrixColumn<const M>::SizeType j)
        {
            return MatrixColumn<const M>(e(), j);
        }

        /**
         * \brief Returns a mutable matrix range proxy viewing rows in \a r1 and columns in \a r2 of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param r1 The row index range.
         * \param r2 The column index range.
         * \return A Math::MatrixRange proxy referring to the specified rectangular subrange of \a e.
         */
        template <typename E>
        MatrixRange<E>
        range(MatrixExpression<E>&                      e,
              const typename MatrixRange<E>::RangeType& r1,
              const typename MatrixRange<E>::RangeType& r2)
        {
            return MatrixRange<E>(e(), r1, r2);
        }

        /**
         * \brief Returns a \c const matrix range proxy viewing rows in \a r1 and columns in \a r2 of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param r1 The row index range.
         * \param r2 The column index range.
         * \return A Math::MatrixRange proxy referring to the specified rectangular subrange of \a e.
         */
        template <typename E>
        MatrixRange<const E>
        range(const MatrixExpression<E>&                      e,
              const typename MatrixRange<const E>::RangeType& r1,
              const typename MatrixRange<const E>::RangeType& r2)
        {
            return MatrixRange<const E>(e(), r1, r2);
        }

        /**
         * \brief Returns a mutable matrix range proxy viewing rows <tt>[start1, stop1)</tt> and columns <tt>[start2, stop2)</tt> of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param start1 The first row index (inclusive).
         * \param stop1 The last row index (exclusive).
         * \param start2 The first column index (inclusive).
         * \param stop2 The last column index (exclusive).
         * \return A Math::MatrixRange proxy referring to the specified rectangular subrange of \a e.
         */
        template <typename E>
        MatrixRange<E>
        range(MatrixExpression<E>&                         e,
              typename MatrixRange<E>::RangeType::SizeType start1,
              typename MatrixRange<E>::RangeType::SizeType stop1,
              typename MatrixRange<E>::RangeType::SizeType start2,
              typename MatrixRange<E>::RangeType::SizeType stop2)
        {
            typedef typename MatrixRange<E>::RangeType RangeType;

            return MatrixRange<E>(e(), RangeType(start1, stop1), RangeType(start2, stop2));
        }

        /**
         * \brief Returns a \c const matrix range proxy viewing rows <tt>[start1, stop1)</tt> and columns <tt>[start2, stop2)</tt> of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param start1 The first row index (inclusive).
         * \param stop1 The last row index (exclusive).
         * \param start2 The first column index (inclusive).
         * \param stop2 The last column index (exclusive).
         * \return A Math::MatrixRange proxy referring to the specified rectangular subrange of \a e.
         */
        template <typename E>
        MatrixRange<const E>
        range(const MatrixExpression<E>&                         e,
              typename MatrixRange<const E>::RangeType::SizeType start1,
              typename MatrixRange<const E>::RangeType::SizeType stop1,
              typename MatrixRange<const E>::RangeType::SizeType start2,
              typename MatrixRange<const E>::RangeType::SizeType stop2)
        {
            typedef typename MatrixRange<const E>::RangeType RangeType;

            return MatrixRange<const E>(e(), RangeType(start1, stop1), RangeType(start2, stop2));
        }

        /**
         * \brief Returns a mutable matrix slice proxy viewing the strided rectangular slice (\a s1, \a s2) of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param s1 The row slice (start, stride, size).
         * \param s2 The column slice (start, stride, size).
         * \return A Math::MatrixSlice proxy referring to the specified strided rectangular slice of \a e.
         */
        template <typename E>
        MatrixSlice<E>
        slice(MatrixExpression<E>&                      e,
              const typename MatrixSlice<E>::SliceType& s1,
              const typename MatrixSlice<E>::SliceType& s2)
        {
            return MatrixSlice<E>(e(), s1, s2);
        }

        /**
         * \brief Returns a \c const matrix slice proxy viewing the strided rectangular slice (\a s1, \a s2) of \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param s1 The row slice (start, stride, size).
         * \param s2 The column slice (start, stride, size).
         * \return A Math::MatrixSlice proxy referring to the specified strided rectangular slice of \a e.
         */
        template <typename E>
        MatrixSlice<const E>
        slice(const MatrixExpression<E>&                      e,
              const typename MatrixSlice<const E>::SliceType& s1,
              const typename MatrixSlice<const E>::SliceType& s2)
        {
            return MatrixSlice<const E>(e(), s1, s2);
        }

        /**
         * \brief Returns a mutable matrix slice proxy specified by row (\a start1, \a stride1, \a size1) and column (\a start2, \a stride2, \a size2).
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param start1 The start row index.
         * \param stride1 The row stride.
         * \param size1 The number of rows.
         * \param start2 The start column index.
         * \param stride2 The column stride.
         * \param size2 The number of columns.
         * \return A Math::MatrixSlice proxy referring to the specified strided rectangular slice of \a e.
         */
        template <typename E>
        MatrixSlice<E>
        slice(MatrixExpression<E>&                               e,
              typename MatrixSlice<E>::SliceType::SizeType       start1,
              typename MatrixSlice<E>::SliceType::DifferenceType stride1,
              typename MatrixSlice<E>::SliceType::SizeType       size1,
              typename MatrixSlice<E>::SliceType::SizeType       start2,
              typename MatrixSlice<E>::SliceType::DifferenceType stride2,
              typename MatrixSlice<E>::SliceType::SizeType       size2)
        {
            typedef typename MatrixSlice<E>::SliceType SliceType;

            return MatrixSlice<E>(e(), SliceType(start1, stride1, size1), SliceType(start2, stride2, size2));
        }

        /**
         * \brief Returns a \c const matrix slice proxy specified by row (\a start1, \a stride1, \a size1) and column (\a start2, \a stride2, \a size2).
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \param start1 The start row index.
         * \param stride1 The row stride.
         * \param size1 The number of rows.
         * \param start2 The start column index.
         * \param stride2 The column stride.
         * \param size2 The number of columns.
         * \return A Math::MatrixSlice proxy referring to the specified strided rectangular slice of \a e.
         */
        template <typename E>
        MatrixSlice<const E>
        slice(const MatrixExpression<E>&                               e,
              typename MatrixSlice<const E>::SliceType::SizeType       start1,
              typename MatrixSlice<const E>::SliceType::DifferenceType stride1,
              typename MatrixSlice<const E>::SliceType::SizeType       size1,
              typename MatrixSlice<const E>::SliceType::SizeType       start2,
              typename MatrixSlice<const E>::SliceType::DifferenceType stride2,
              typename MatrixSlice<const E>::SliceType::SizeType       size2)
        {
            typedef typename MatrixSlice<const E>::SliceType SliceType;

            return MatrixSlice<const E>(e(), SliceType(start1, stride1, size1), SliceType(start2, stride2, size2));
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXPROXY_HPP
