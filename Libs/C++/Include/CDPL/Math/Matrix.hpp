/* 
 * Matrix.hpp 
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
 * \brief Definition of matrix data types.
 */

#ifndef CDPL_MATH_MATRIX_HPP
#define CDPL_MATH_MATRIX_HPP

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <limits>
#include <unordered_map>
#include <type_traits>
#include <utility>
#include <initializer_list>
#include <memory>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/DirectAssignmentProxy.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/SparseContainerElement.hpp"
#include "CDPL/Math/LUDecomposition.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Lightweight matrix expression that proxies a reference to an underlying matrix container.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixReference : public MatrixExpression<MatrixReference<M> >
        {

            typedef MatrixReference<M> SelfType;

          public:
            /** \brief The wrapped matrix type. */
            typedef M                                                      MatrixType;
            /** \brief The element value type of the wrapped matrix. */
            typedef typename M::ValueType                                  ValueType;
            /** \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const). */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type Reference;
            /** \brief Constant reference type to an element. */
            typedef typename M::ConstReference                             ConstReference;
            /** \brief The unsigned size type of the wrapped matrix. */
            typedef typename M::SizeType                                   SizeType;
            /** \brief The signed difference type of the wrapped matrix. */
            typedef typename M::DifferenceType                             DifferenceType;
            /** \brief Closure type used when this proxy appears inside another expression. */
            typedef SelfType                                               ClosureType;
            /** \brief Constant closure type used when this proxy appears inside another expression. */
            typedef const SelfType                                         ConstClosureType;

            /**
             * \brief Constructs the reference proxy referring to \a m.
             * \param m The wrapped matrix to proxy.
             */
            explicit MatrixReference(MatrixType& m):
                data(m) {}

            /**
             * \brief Returns a mutable reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                return data(i, j);
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the element.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(i, j);
            }

            /**
             * \brief Returns the wrapped matrix's number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return data.getSize1();
            }

            /**
             * \brief Returns the wrapped matrix's number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return data.getSize2();
            }

            /**
             * \brief Returns the wrapped matrix's maximum total element count.
             * \return The maximum total element count.
             */
            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            /**
             * \brief Returns the wrapped matrix's maximum number of rows.
             * \return The maximum number of rows.
             */
            SizeType getMaxSize1() const
            {
                return data.getMaxSize1();
            }

            /**
             * \brief Returns the wrapped matrix's maximum number of columns.
             * \return The maximum number of columns.
             */
            SizeType getMaxSize2() const
            {
                return data.getMaxSize2();
            }

            /**
             * \brief Tells whether the wrapped matrix is empty.
             * \return \c true if the wrapped matrix has zero rows or zero columns, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.isEmpty();
            }

            /**
             * \brief Returns a \c const reference to the wrapped matrix.
             * \return A \c const reference to the wrapped matrix.
             */
            const MatrixType& getData() const
            {
                return data;
            }

            /**
             * \brief Returns a reference to the wrapped matrix.
             * \return A reference to the wrapped matrix.
             */
            MatrixType& getData()
            {
                return data;
            }

            /**
             * \brief Copy-assigns the wrapped matrix from the matrix referenced by \a r.
             * \param r The source reference proxy.
             * \return A reference to itself.
             */
            MatrixReference& operator=(const MatrixReference& r)
            {
                data.operator=(r.data);
                return *this;
            }

            /**
             * \brief Assigns the matrix expression \a e to the wrapped matrix.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& operator=(const MatrixExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            /**
             * \brief Adds the matrix expression \a e element-wise to the wrapped matrix.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& operator+=(const MatrixExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            /**
             * \brief Subtracts the matrix expression \a e element-wise from the wrapped matrix.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& operator-=(const MatrixExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            /**
             * \brief Multiplies every element of the wrapped matrix by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixReference>::type& operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            /**
             * \brief Divides every element of the wrapped matrix by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixReference>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            /**
             * \brief Assigns the matrix expression \a e to the wrapped matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& assign(const MatrixExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            /**
             * \brief Adds the matrix expression \a e to the wrapped matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& plusAssign(const MatrixExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            /**
             * \brief Subtracts the matrix expression \a e from the wrapped matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixReference& minusAssign(const MatrixExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            /**
             * \brief Swaps the contents of the two wrapped matrices.
             * \param r The reference proxy to swap with.
             */
            void swap(MatrixReference& r)
            {
                data.swap(r.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first reference proxy.
             * \param r2 The second reference proxy.
             */
            friend void swap(MatrixReference& r1, MatrixReference& r2)
            {
                r1.swap(r2);
            }

          private:
            MatrixType& data;
        };

        template <typename T, typename A>
        class Matrix;
        template <typename T, typename A>
        class Vector;

        /**
         * \brief Lightweight matrix container that wraps a nested \c std::initializer_list of \c T values.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class InitListMatrix : public MatrixContainer<InitListMatrix<T> >
        {

          public:
            /** \brief Convenience alias for this instantiation. */
            typedef InitListMatrix                                            SelfType;
            /** \brief The nested \c std::initializer_list type wrapped by this matrix. */
            typedef std::initializer_list<std::initializer_list<T> >          InitializerListType;
            /** \brief The scalar value type. */
            typedef typename InitializerListType::value_type::value_type      ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename InitializerListType::value_type::const_reference ConstReference;
            /** \brief Mutable reference type to an element. */
            typedef typename InitializerListType::value_type::reference       Reference;
            /** \brief The unsigned size type. */
            typedef typename InitializerListType::size_type                   SizeType;
            /** \brief The signed difference type. */
            typedef typename std::ptrdiff_t                                   DifferenceType;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef SelfType                                                  ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const SelfType                                            ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef Matrix<T, std::vector<T> >                                MatrixTemporaryType;
            /** \brief Concrete temporary vector type used by expression-template machinery. */
            typedef Vector<T, std::vector<T> >                                VectorTemporaryType;

            /**
             * \brief Constructs an \c %InitListMatrix wrapping the nested initializer list \a l.
             *
             * The second-dimension size is the longest inner list's length; shorter rows are zero-padded on access.
             *
             * \param l The nested initializer list.
             */
            InitListMatrix(InitializerListType l):
                list(l), size2(0)
            {
                for (const auto& r : l)
                    size2 = std::max(size2, r.size());
            }

            /**
             * \brief Returns a mutable reference to the element at row \a i and column \a j.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable reference to the element (or to a zero element if \a j is past the row's length).
             * \throw Base::IndexError if \a i or \a j is out of range.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                if (j >= (list.begin() + i)->size())
                    return zero;

                return *((list.begin() + i)->begin() + j);
            }

            /**
             * \brief Returns a \c const reference to the element at row \a i and column \a j.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the element (or to a zero element if \a j is past the row's length).
             * \throw Base::IndexError if \a i or \a j is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                if (j >= (list.begin() + i)->size())
                    return zero;

                return *((list.begin() + i)->begin() + j);
            }

            /**
             * \brief Returns the number of rows.
             * \return The first-dimension size.
             */
            SizeType getSize1() const
            {
                return list.size();
            }

            /**
             * \brief Returns the number of columns (the longest row length).
             * \return The second-dimension size.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Tells whether the matrix is empty (zero rows or zero columns).
             * \return \c true if the matrix is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size2 == 0 || list.size() == 0);
            }

          private:
            InitializerListType    list;
            SizeType               size2;
            static const ValueType zero;
        };

        template <typename T>
        const typename InitListMatrix<T>::ValueType InitListMatrix<T>::zero = InitListMatrix<T>::ValueType();

        /**
         * \brief Dynamically-sized dense row-major matrix with configurable underlying storage.
         * \tparam T The scalar value type.
         * \tparam A The underlying storage container type (default: \c std::vector).
         */
        template <typename T, typename A = std::vector<T> >
        class Matrix : public MatrixContainer<Matrix<T, A> >
        {

            typedef Matrix<T, A> SelfType;

          public:
            /** \brief The scalar value type stored in the matrix. */
            typedef T                                                ValueType;
            /** \brief Mutable reference type to an element. */
            typedef T&                                               Reference;
            /** \brief Constant reference type to an element. */
            typedef const T&                                         ConstReference;
            /** \brief The unsigned size type used by the underlying storage container. */
            typedef typename A::size_type                            SizeType;
            /** \brief The signed difference type used by the underlying storage container. */
            typedef typename A::difference_type                      DifferenceType;
            /** \brief The underlying storage container type (row-major linear storage). */
            typedef A                                                ArrayType;
            /** \brief Pointer type for raw element access. */
            typedef T*                                               Pointer;
            /** \brief Constant pointer type for raw element access. */
            typedef const T*                                         ConstPointer;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>                        ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType>            ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef SelfType                                         MatrixTemporaryType;
            /** \brief Concrete temporary vector type compatible with this matrix's value type and storage. */
            typedef Vector<T, A>                                     VectorTemporaryType;
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Matrix instances. */
            typedef std::shared_ptr<SelfType>                        SharedPointer;
            /** \brief Type of the brace-initializer list of lists accepted by the corresponding constructor (one inner list per row). */
            typedef std::initializer_list<std::initializer_list<T> > InitializerListType;

            /**
             * \brief Constructs an empty matrix (zero rows and zero columns).
             */
            Matrix():
                size1(0), size2(0), data() {}

            /**
             * \brief Constructs an \e m &times; \e n matrix with default-initialized elements.
             * \param m The number of rows.
             * \param n The number of columns.
             */
            Matrix(SizeType m, SizeType n):
                size1(m), size2(n), data(storageSize(m, n)) {}

            /**
             * \brief Constructs an \e m &times; \e n matrix with every element initialized to \a v.
             * \param m The number of rows.
             * \param n The number of columns.
             * \param v The element value used to initialize every cell.
             */
            Matrix(SizeType m, SizeType n, const ValueType& v):
                size1(m), size2(n), data(storageSize(m, n), v) {}

            /**
             * \brief Constructs a copy of the matrix \a m.
             * \param m The matrix to copy.
             */
            Matrix(const Matrix& m):
                size1(m.size1), size2(m.size2), data(m.data) {}

            /**
             * \brief Move-constructs a matrix from \a m (\a m is left in a valid empty state).
             * \param m The matrix to move from.
             */
            Matrix(Matrix&& m):
                size1(0), size2(0), data()
            {
                swap(m);
            }

            /**
             * \brief Constructs the matrix from a brace-initializer list of rows.
             *
             * The outer list yields the rows; each inner list yields the row elements. The size is derived
             * from the dimensions of the supplied initializer (all inner lists must have the same length).
             *
             * \param l The initializer list of rows.
             */
            Matrix(InitializerListType l):
                size1(0), size2(0), data()
            {
                assign(l);
            }

            /**
             * \brief Constructs the matrix from the matrix expression \a e (materializing the expression result).
             * \tparam E The matrix expression type.
             * \param e The matrix expression to materialize.
             */
            template <typename E>
            Matrix(const MatrixExpression<E>& e):
                size1(e().getSize1()), size2(e().getSize2()), data(storageSize(e().getSize1(), e().getSize2()))
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i * getSize2() + j];
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i * getSize2() + j];
            }

            /**
             * \brief Tells whether the matrix is empty.
             * \return \c true if the underlying storage holds no elements, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.empty();
            }

            /**
             * \brief Returns the number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the maximum total element count the underlying storage container can hold.
             * \return The maximum total element count.
             */
            SizeType getMaxSize() const
            {
                return data.max_size();
            }

            /**
             * \brief Returns a mutable reference to the underlying storage container (row-major linear layout).
             * \return A mutable reference to the storage container.
             */
            ArrayType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the underlying storage container (row-major linear layout).
             * \return A \c const reference to the storage container.
             */
            const ArrayType& getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the contents of \a m to this matrix.
             * \param m The source matrix.
             * \return A reference to itself.
             */
            Matrix& operator=(const Matrix& m)
            {
                data  = m.data;
                size1 = m.size1;
                size2 = m.size2;
                return *this;
            }

            /**
             * \brief Move-assigns the contents of \a m to this matrix.
             * \param m The source matrix (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            Matrix& operator=(Matrix&& m)
            {
                swap(m);
                return *this;
            }

            /**
             * \brief Assigns the contents of the matrix container \a c to this matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            Matrix& operator=(const MatrixContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the rows in \a l to this matrix (resizes to match).
             * \param l The initializer list of rows.
             * \return A reference to itself.
             */
            Matrix& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the matrix expression \a e to this matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& operator=(const MatrixExpression<E>& e)
            {
                Matrix tmp(e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Adds the contents of the matrix container \a c element-wise to this matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            Matrix& operator+=(const MatrixContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the rows in \a l element-wise to this matrix.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            Matrix& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the matrix expression \a e element-wise to this matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& operator+=(const MatrixExpression<E>& e)
            {
                Matrix tmp(*this + e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the matrix container \a c element-wise from this matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            Matrix& operator-=(const MatrixContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this matrix.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            Matrix& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the matrix expression \a e element-wise from this matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& operator-=(const MatrixExpression<E>& e)
            {
                Matrix tmp(*this - e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Multiplies every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Matrix>::type& operator*=(const T1& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Matrix>::type& operator/=(const T1& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match the dimensions of \a e and assigns its elements (without intermediate temporary).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& assign(const MatrixExpression<E>& e)
            {
                resize(e().getSize1(), e().getSize2(), false);
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match \a l and assigns its elements.
             * \param l The initializer list of rows providing the new elements.
             * \return A reference to itself.
             */
            Matrix& assign(InitializerListType l)
            {
                InitListMatrix<ValueType> ilm(l);
                resize(ilm.getSize1(), ilm.getSize2(), false);
                matrixAssignMatrix<ScalarAssignment>(*this, ilm);
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the rows in \a l element-wise to this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            Matrix& plusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            Matrix& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            Matrix& minusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this matrix with those of \a m.
             * \param m The matrix to swap with.
             */
            void swap(Matrix& m)
            {
                if (this != &m) {
                    std::swap(data, m.data);
                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first matrix.
             * \param m2 The second matrix.
             */
            friend void swap(Matrix& m1, Matrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Sets every element of the matrix to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                std::fill(data.begin(), data.end(), v);
            }

            /**
             * \brief Resizes the matrix to \f$ m \times n \f$ elements.
             * \param m The new row count.
             * \param n The new column count.
             * \param preserve If \c true, existing element values at indices that remain valid are kept; if \c false, all elements are set to \a v.
             * \param v The fill value for newly added elements (or for all elements when \a preserve is \c false).
             */
            void resize(SizeType m, SizeType n, bool preserve = true, const ValueType& v = ValueType())
            {
                if (size1 == m && size2 == n)
                    return;

                if (preserve) {
                    Matrix tmp(m, n, v);

                    for (SizeType i = 0, min_size1 = std::min(size1, m); i < min_size1; i++)
                        for (SizeType j = 0, min_size2 = std::min(size2, n); j < min_size2; j++)
                            tmp(i, j) = (*this)(i, j);

                    swap(tmp);

                } else {
                    data.resize(storageSize(m, n), v);
                    size1 = m;
                    size2 = n;
                }
            }

          private:
            SizeType storageSize(SizeType m, SizeType n)
            {
                CDPL_MATH_CHECK(n == 0 || m <= data.max_size() / n, "Maximum size exceeded", Base::SizeError);
                return (m * n);
            }

            SizeType  size1;
            SizeType  size2;
            ArrayType data;
        };

        /**
         * \brief Sparse matrix that stores only non-default entries keyed by a packed (row, column) identifier.
         * \tparam T The scalar value type.
         * \tparam A The underlying associative container type (default: \c std::unordered_map keyed by \c std::uint64_t).
         */
        template <typename T, typename A = std::unordered_map<std::uint64_t, T> >
        class SparseMatrix : public MatrixContainer<SparseMatrix<T, A> >
        {

            typedef SparseMatrix<T> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T                                                ValueType;
            /** \brief The packed (row, column) key type used by the underlying associative container. */
            typedef typename A::key_type                             KeyType;
            /** \brief Mutable reference type (a proxy object that inserts on assignment to a previously-absent cell). */
            typedef SparseContainerElement<SelfType>                 Reference;
            /** \brief Constant reference type to a stored element value. */
            typedef const T&                                         ConstReference;
            /** \brief The unsigned size type. */
            typedef std::uint32_t                                    SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t                                   DifferenceType;
            /** \brief The underlying associative container type. */
            typedef A                                                ArrayType;
            /** \brief Pointer type for raw access to stored entries. */
            typedef T*                                               Pointer;
            /** \brief Constant pointer type for raw access to stored entries. */
            typedef const T*                                         ConstPointer;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>                        ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType>            ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef SelfType                                         MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix. */
            typedef Vector<T, std::vector<T> >                       VectorTemporaryType;
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %SparseMatrix instances. */
            typedef std::shared_ptr<SelfType>                        SharedPointer;
            /** \brief The initializer-list-of-rows type accepted by constructors and assignment. */
            typedef std::initializer_list<std::initializer_list<T> > InitializerListType;

            /**
             * \brief Constructs an empty sparse matrix (zero rows, zero columns, no stored entries).
             */
            SparseMatrix():
                size1(0), size2(0), data() {}

            /**
             * \brief Constructs a sparse matrix of size \f$ m \times n \f$ with no stored entries.
             * \param m The number of rows.
             * \param n The number of columns.
             * \throw Base::SizeError if \f$ m \cdot n \f$ exceeds the underlying container's capacity.
             */
            SparseMatrix(SizeType m, SizeType n):
                size1(m), size2(n), data()
            {
                CDPL_MATH_CHECK((n == 0 || m <= data.max_size() / n), "Maximum size exceeded", Base::SizeError);
            }

            /**
             * \brief Constructs a copy of the sparse matrix \a m.
             * \param m The sparse matrix to copy.
             */
            SparseMatrix(const SparseMatrix& m):
                size1(m.size1), size2(m.size2), data(m.data) {}

            /**
             * \brief Move-constructs a sparse matrix from \a m (\a m is left in a valid empty state).
             * \param m The sparse matrix to move from.
             */
            SparseMatrix(SparseMatrix&& m):
                size1(0), size2(0), data()
            {
                swap(m);
            }

            /**
             * \brief Constructs a sparse matrix from the initializer list of rows \a l.
             * \param l The initializer list of rows.
             */
            SparseMatrix(InitializerListType l):
                size1(0), size2(0), data()
            {
                assign(l);
            }

            /**
             * \brief Constructs a sparse matrix from the matrix expression \a e.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \throw Base::SizeError if the dimensions of \a e exceed the underlying container's capacity.
             */
            template <typename E>
            SparseMatrix(const MatrixExpression<E>& e):
                size1(e().getSize1()), size2(e().getSize2()), data()
            {
                CDPL_MATH_CHECK((size1 == 0 || size2 <= data.max_size() / size1), "Maximum size exceeded", Base::SizeError);
                matrixAssignMatrix<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable proxy reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable proxy reference (creates a stored entry on first assignment).
             * \throw Base::IndexError if either index is out of range.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                return Reference(*this, makeKey(i, j));
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the stored value, or to the zero element if no entry exists at (\a i, \a j).
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                typename ArrayType::const_iterator it = data.find(makeKey(i, j));

                if (it == data.end())
                    return zero;

                return it->second;
            }

            /**
             * \brief Returns the number of explicitly stored (non-default) entries.
             * \return The number of stored entries.
             */
            SizeType getNumElements() const
            {
                return data.size();
            }

            /**
             * \brief Tells whether the matrix is empty (zero rows or zero columns).
             * \return \c true if either dimension is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0);
            }

            /**
             * \brief Returns the logical number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the logical number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the maximum number of stored entries the underlying associative container can hold.
             * \return The maximum entry count.
             */
            typename ArrayType::size_type getMaxSize() const
            {
                return data.max_size();
            }

            /**
             * \brief Returns a mutable reference to the underlying associative container of stored entries.
             * \return A mutable reference to the storage container.
             */
            ArrayType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the underlying associative container of stored entries.
             * \return A \c const reference to the storage container.
             */
            const ArrayType& getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the contents of \a m to this sparse matrix.
             * \param m The source sparse matrix.
             * \return A reference to itself.
             */
            SparseMatrix& operator=(const SparseMatrix& m)
            {
                data  = m.data;
                size1 = m.size1;
                size2 = m.size2;
                return *this;
            }

            /**
             * \brief Move-assigns the contents of \a m to this sparse matrix.
             * \param m The source sparse matrix (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            SparseMatrix& operator=(SparseMatrix&& m)
            {
                swap(m);
                return *this;
            }

            /**
             * \brief Assigns the contents of the matrix container \a c to this sparse matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseMatrix& operator=(const MatrixContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the rows in \a l to this sparse matrix (resizes to match).
             * \param l The initializer list of rows.
             * \return A reference to itself.
             */
            SparseMatrix& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the matrix expression \a e to this sparse matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& operator=(const MatrixExpression<E>& e)
            {
                SparseMatrix tmp(e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Adds the contents of the matrix container \a c element-wise to this sparse matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseMatrix& operator+=(const MatrixContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the rows in \a l element-wise to this sparse matrix.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            SparseMatrix& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the matrix expression \a e element-wise to this sparse matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& operator+=(const MatrixExpression<E>& e)
            {
                SparseMatrix tmp(*this + e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the matrix container \a c element-wise from this sparse matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseMatrix& operator-=(const MatrixContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this sparse matrix.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            SparseMatrix& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the matrix expression \a e element-wise from this sparse matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& operator-=(const MatrixExpression<E>& e)
            {
                SparseMatrix tmp(*this - e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Multiplies every stored entry by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseMatrix>::type& operator*=(const T1& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every stored entry by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseMatrix>::type& operator/=(const T1& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match \a e and assigns its elements without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& assign(const MatrixExpression<E>& e)
            {
                resize(e().getSize1(), e().getSize2());
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match \a l and assigns its elements.
             * \param l The initializer list of rows providing the new elements.
             * \return A reference to itself.
             */
            SparseMatrix& assign(InitializerListType l)
            {
                InitListMatrix<ValueType> ilm(l);
                resize(ilm.getSize1(), ilm.getSize2());
                matrixAssignMatrix<ScalarAssignment>(*this, ilm);
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the rows in \a l element-wise to this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            SparseMatrix& plusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseMatrix& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            SparseMatrix& minusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this sparse matrix with those of \a m.
             * \param m The sparse matrix to swap with.
             */
            void swap(SparseMatrix& m)
            {
                if (this != &m) {
                    std::swap(data, m.data);
                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first sparse matrix.
             * \param m2 The second sparse matrix.
             */
            friend void swap(SparseMatrix& m1, SparseMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Removes all explicitly stored entries (the logical dimensions remain unchanged).
             */
            void clear()
            {
                data.clear();
            }

            /**
             * \brief Resizes the logical dimensions to \f$ m \times n \f$, dropping any stored entries that fall outside the new bounds.
             * \param m The new row count.
             * \param n The new column count.
             * \throw Base::SizeError if \f$ m \cdot n \f$ exceeds the underlying container's capacity.
             */
            void resize(SizeType m, SizeType n)
            {
                CDPL_MATH_CHECK((n == 0 || m <= data.max_size() / n), "Maximum size exceeded", Base::SizeError);

                for (typename ArrayType::iterator it = data.begin(); it != data.end();) {
                    const KeyType& key = it->first;

                    if (getRowIdx(key) >= m || getColIdx(key) >= n)
                        it = data.erase(it);
                    else
                        ++it;
                }

                size1 = m;
                size2 = n;
            }

          private:
            static KeyType makeKey(SizeType i, SizeType j)
            {
                return ((KeyType(i) << (sizeof(SizeType) * 8)) + j);
            }

            static SizeType getRowIdx(const KeyType& key)
            {
                return (key >> (sizeof(SizeType) * 8));
            }

            static SizeType getColIdx(const KeyType& key)
            {
                return (key & KeyType(~SizeType()));
            }

            SizeType               size1;
            SizeType               size2;
            ArrayType              data;
            static const ValueType zero;
        };

        template <typename T, typename A>
        const typename SparseMatrix<T, A>::ValueType SparseMatrix<T, A>::zero = SparseMatrix<T, A>::ValueType();

        template <typename T, std::size_t N>
        class BoundedVector;

        /**
         * \brief Variable-size matrix with fixed upper capacities \a M \f$ \times \f$ \a N stored in a stack-allocated array.
         * \tparam T The scalar value type.
         * \tparam M The maximum number of rows.
         * \tparam N The maximum number of columns.
         */
        template <typename T, std::size_t M, std::size_t N>
        class BoundedMatrix : public MatrixContainer<BoundedMatrix<T, M, N> >
        {

            typedef BoundedMatrix<T, M, N> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T              ValueType;
            /** \brief Mutable reference type to an element. */
            typedef T&             Reference;
            /** \brief Constant reference type to an element. */
            typedef const T&       ConstReference;
            /** \brief The unsigned size type. */
            typedef std::size_t    SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t DifferenceType;
            /** \brief The fixed-capacity 2D C-array type used for in-memory storage. */
            typedef ValueType      ArrayType[M][N];
            /** \brief Pointer-to-row type for raw access to the element array. */
            typedef T (*ArrayPointer)[N];
            /** \brief Constant pointer-to-row type for raw access to the element array. */
            typedef const T (*ConstArrayPointer)[N];
            /** \brief Pointer type to a single element. */
            typedef T*                                               Pointer;
            /** \brief Constant pointer type to a single element. */
            typedef const T*                                         ConstPointer;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>                        ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType>            ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef SelfType                                         MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix (a bounded vector of capacity \a M * \a N). */
            typedef BoundedVector<T, M * N>                          VectorTemporaryType;
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BoundedMatrix instances. */
            typedef std::shared_ptr<SelfType>                        SharedPointer;
            /** \brief The initializer-list-of-rows type accepted by constructors and assignment. */
            typedef std::initializer_list<std::initializer_list<T> > InitializerListType;

            /** \brief The compile-time maximum number of rows \a M. */
            static const SizeType MaxSize1 = M;
            /** \brief The compile-time maximum number of columns \a N. */
            static const SizeType MaxSize2 = N;

            /**
             * \brief Constructs an empty bounded matrix (zero rows, zero columns).
             */
            BoundedMatrix():
                size1(0), size2(0) {}

            /**
             * \brief Constructs a bounded matrix of size \f$ m \times n \f$ with value-initialized elements.
             * \param m The initial row count.
             * \param n The initial column count.
             * \throw Base::SizeError if \a m exceeds the bound \a M or \a n exceeds \a N.
             */
            BoundedMatrix(SizeType m, SizeType n):
                size1(0), size2(0)
            {
                resize(m, n);
            }

            /**
             * \brief Constructs a bounded matrix of size \f$ m \times n \f$ with every element initialized to \a v.
             * \param m The initial row count.
             * \param n The initial column count.
             * \param v The initial element value.
             * \throw Base::SizeError if \a m exceeds the bound \a M or \a n exceeds \a N.
             */
            BoundedMatrix(SizeType m, SizeType n, const ValueType& v):
                size1(0), size2(0)
            {
                resize(m, n, v);
            }

            /**
             * \brief Constructs a copy of the bounded matrix \a m.
             * \param m The bounded matrix to copy.
             */
            BoundedMatrix(const BoundedMatrix& m):
                size1(m.size1), size2(m.size2)
            {
                for (SizeType i = 0; i < size1; i++)
                    std::copy(m.data[i], m.data[i] + size2, data[i]);
            }

            /**
             * \brief Constructs a bounded matrix from the initializer list of rows \a l.
             * \param l The initializer list of rows.
             * \throw Base::SizeError if the dimensions of \a l exceed the bounds \a M, \a N.
             */
            BoundedMatrix(InitializerListType l):
                size1(0), size2(0)
            {
                assign(l);
            }

            /**
             * \brief Constructs a bounded matrix from the matrix expression \a e.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \throw Base::SizeError if the dimensions of \a e exceed the bounds \a M, \a N.
             */
            template <typename E>
            BoundedMatrix(const MatrixExpression<E>& e):
                size1(0), size2(0)
            {
                resize(e().getSize1(), e().getSize2());
                matrixAssignMatrix<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i][j];
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i][j];
            }

            /**
             * \brief Tells whether the matrix is empty.
             * \return \c true if either dimension is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0);
            }

            /**
             * \brief Returns the current row count.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the current column count.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the compile-time maximum row count \a M.
             * \return The maximum number of rows.
             */
            SizeType getMaxSize1() const
            {
                return M;
            }

            /**
             * \brief Returns the compile-time maximum column count \a N.
             * \return The maximum number of columns.
             */
            SizeType getMaxSize2() const
            {
                return N;
            }

            /**
             * \brief Returns a mutable pointer-to-row to the contiguous 2D element array.
             * \return A mutable array pointer.
             */
            ArrayPointer getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const pointer-to-row to the contiguous 2D element array.
             * \return A \c const array pointer.
             */
            ConstArrayPointer getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the elements of \a m to this bounded matrix.
             * \param m The source bounded matrix.
             * \return A reference to itself.
             */
            BoundedMatrix& operator=(const BoundedMatrix& m)
            {
                if (this != &m) {
                    for (SizeType i = 0; i < m.size1; i++)
                        std::copy(m.data[i], m.data[i] + m.size2, data[i]);

                    size1 = m.size1;
                    size2 = m.size2;
                }

                return *this;
            }

            /**
             * \brief Assigns the contents of the matrix container \a c to this bounded matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedMatrix& operator=(const MatrixContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the rows in \a l to this bounded matrix (resizes to match, respecting the bounds).
             * \param l The initializer list of rows.
             * \return A reference to itself.
             * \throw Base::SizeError if the dimensions of \a l exceed the bounds \a M, \a N.
             */
            BoundedMatrix& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the matrix expression \a e to this bounded matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             * \throw Base::SizeError if the dimensions of \a e exceed the bounds \a M, \a N.
             */
            template <typename E>
            BoundedMatrix& operator=(const MatrixExpression<E>& e)
            {
                BoundedMatrix tmp(e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Adds the contents of the matrix container \a c element-wise to this bounded matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedMatrix& operator+=(const MatrixContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the rows in \a l element-wise to this bounded matrix.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            BoundedMatrix& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the matrix expression \a e element-wise to this bounded matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedMatrix& operator+=(const MatrixExpression<E>& e)
            {
                BoundedMatrix tmp(*this + e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Subtracts the contents of the matrix container \a c element-wise from this bounded matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedMatrix& operator-=(const MatrixContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this bounded matrix.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            BoundedMatrix& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the matrix expression \a e element-wise from this bounded matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedMatrix& operator-=(const MatrixExpression<E>& e)
            {
                BoundedMatrix tmp(*this - e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Multiplies every element by the scalar \a v.
             * \tparam T1 The scalar type.
             * \param v The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedMatrix>::type& operator*=(const T1& v)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, v);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a v.
             * \tparam T1 The scalar type.
             * \param v The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedMatrix>::type& operator/=(const T1& v)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, v);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match \a e and assigns its elements without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             * \throw Base::SizeError if the dimensions of \a e exceed the bounds \a M, \a N.
             */
            template <typename E>
            BoundedMatrix& assign(const MatrixExpression<E>& e)
            {
                resize(e().getSize1(), e().getSize2());
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Resizes this matrix to match \a l and assigns its elements.
             * \param l The initializer list of rows providing the new elements.
             * \return A reference to itself.
             * \throw Base::SizeError if the dimensions of \a l exceed the bounds \a M, \a N.
             */
            BoundedMatrix& assign(InitializerListType l)
            {
                InitListMatrix<ValueType> ilm(l);
                resize(ilm.getSize1(), ilm.getSize2());
                matrixAssignMatrix<ScalarAssignment>(*this, ilm);
                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedMatrix& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the rows in \a l element-wise to this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            BoundedMatrix& plusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedMatrix& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            BoundedMatrix& minusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this bounded matrix with those of \a m.
             * \param m The bounded matrix to swap with.
             */
            void swap(BoundedMatrix& m)
            {
                if (this != &m) {
                    SizeType max_size1 = std::max(size1, m.size1);
                    SizeType max_size2 = std::max(size2, m.size2);

                    for (SizeType i = 0; i < max_size1; i++)
                        std::swap_ranges(data[i], data[i] + max_size2, m.data[i]);

                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first bounded matrix.
             * \param m2 The second bounded matrix.
             */
            friend void swap(BoundedMatrix& m1, BoundedMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Sets every element of the matrix to the value \a v (dimensions unchanged).
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                for (SizeType i = 0; i < size1; i++)
                    std::fill(data[i], data[i] + size2, v);
            }

            /**
             * \brief Resizes the matrix to \f$ m \times n \f$ elements (new elements are left value-uninitialized).
             * \param m The new row count.
             * \param n The new column count.
             * \throw Base::SizeError if \a m exceeds \a M or \a n exceeds \a N.
             */
            void resize(SizeType m, SizeType n)
            {
                m = CDPL_MATH_CHECK_MAX_SIZE(m, M, Base::SizeError);
                n = CDPL_MATH_CHECK_MAX_SIZE(n, N, Base::SizeError);

                size1 = m;
                size2 = n;
            }

            /**
             * \brief Resizes the matrix to \f$ m \times n \f$ elements; newly added cells are set to \a v.
             * \param m The new row count.
             * \param n The new column count.
             * \param v The fill value for newly added cells.
             * \throw Base::SizeError if \a m exceeds \a M or \a n exceeds \a N.
             */
            void resize(SizeType m, SizeType n, const ValueType& v)
            {
                m = CDPL_MATH_CHECK_MAX_SIZE(m, M, Base::SizeError);
                n = CDPL_MATH_CHECK_MAX_SIZE(n, N, Base::SizeError);

                if (n > size2) {
                    SizeType min_size1 = std::min(size1, m);

                    for (SizeType i = 0; i < min_size1; i++)
                        std::fill(data[i] + size2, data[i] + n, v);
                }

                if (m > size1)
                    for (SizeType i = size1; i < m; i++)
                        std::fill(data[i], data[i] + n, v);

                size1 = m;
                size2 = n;
            }

          private:
            SizeType  size1;
            SizeType  size2;
            ArrayType data;
        };

        template <typename T, std::size_t M, std::size_t N>
        const typename BoundedMatrix<T, M, N>::SizeType BoundedMatrix<T, M, N>::MaxSize1;
        template <typename T, std::size_t M, std::size_t N>
        const typename BoundedMatrix<T, M, N>::SizeType BoundedMatrix<T, M, N>::MaxSize2;

        /**
         * \brief Fixed-size dense matrix of dimensions \a M \f$ \times \f$ \a N backed by a 2D C-array (no dynamic allocation).
         * \tparam T The scalar value type.
         * \tparam M The fixed number of rows.
         * \tparam N The fixed number of columns.
         */
        template <typename T, std::size_t M, std::size_t N>
        class CMatrix : public MatrixContainer<CMatrix<T, M, N> >
        {

            typedef CMatrix<T, M, N> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T              ValueType;
            /** \brief Mutable reference type to an element. */
            typedef T&             Reference;
            /** \brief Constant reference type to an element. */
            typedef const T&       ConstReference;
            /** \brief The unsigned size type. */
            typedef std::size_t    SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t DifferenceType;
            /** \brief The fixed-size 2D C-array type used for in-memory storage of \a M \f$ \times \f$ \a N elements. */
            typedef ValueType      ArrayType[M][N];
            /** \brief Pointer-to-row type for raw access to the element array. */
            typedef T (*ArrayPointer)[N];
            /** \brief Constant pointer-to-row type for raw access to the element array. */
            typedef const T (*ConstArrayPointer)[N];
            /** \brief Pointer type to a single element. */
            typedef T*                                               Pointer;
            /** \brief Constant pointer type to a single element. */
            typedef const T*                                         ConstPointer;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>                        ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType>            ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery (a Math::BoundedMatrix of equal capacity). */
            typedef BoundedMatrix<T, M, N>                           MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix. */
            typedef BoundedVector<T, M * N>                          VectorTemporaryType;
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CMatrix instances. */
            typedef std::shared_ptr<SelfType>                        SharedPointer;
            /** \brief The initializer-list-of-rows type accepted by constructors and assignment. */
            typedef std::initializer_list<std::initializer_list<T> > InitializerListType;

            /** \brief The compile-time fixed row count \a M. */
            static const SizeType Size1 = M;
            /** \brief The compile-time fixed column count \a N. */
            static const SizeType Size2 = N;

            /**
             * \brief Constructs a zero-initialized \f$ M \times N \f$ matrix.
             */
            CMatrix()
            {
                for (SizeType i = 0; i < M; i++)
                    std::fill(data[i], data[i] + N, ValueType());
            }

            /**
             * \brief Constructs an \f$ M \times N \f$ matrix with every element initialized to \a v.
             * \param v The initial element value.
             */
            explicit CMatrix(const ValueType& v)
            {
                for (SizeType i = 0; i < M; i++)
                    std::fill(data[i], data[i] + N, v);
            }

            /**
             * \brief Constructs a copy of the fixed-size matrix \a m.
             * \param m The fixed-size matrix to copy.
             */
            CMatrix(const CMatrix& m)
            {
                for (SizeType i = 0; i < M; i++)
                    std::copy(m.data[i], m.data[i] + N, data[i]);
            }

            /**
             * \brief Constructs a fixed-size matrix with the contents of the initializer list of rows \a l.
             * \param l The initializer list of rows (clipped or zero-padded to \a M \f$ \times \f$ \a N).
             */
            CMatrix(InitializerListType l)
            {
                assign(l);
            }

            /**
             * \brief Constructs a fixed-size matrix from the matrix expression \a e.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             */
            template <typename E>
            CMatrix(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            Reference operator()(SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i][j];
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return data[i][j];
            }

            /**
             * \brief Tells whether the matrix is empty (\a M or \a N is zero).
             * \return \c true if either \a M or \a N is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (M == 0 || N == 0);
            }

            /**
             * \brief Returns the fixed row count \a M.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return M;
            }

            /**
             * \brief Returns the fixed column count \a N.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return N;
            }

            /**
             * \brief Returns the fixed row count \a M (capacity equals size for Math::CMatrix).
             * \return The number of rows.
             */
            SizeType getMaxSize1() const
            {
                return M;
            }

            /**
             * \brief Returns the fixed column count \a N (capacity equals size for Math::CMatrix).
             * \return The number of columns.
             */
            SizeType getMaxSize2() const
            {
                return N;
            }

            /**
             * \brief Returns a mutable pointer-to-row to the contiguous 2D element array.
             * \return A mutable array pointer.
             */
            ArrayPointer getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const pointer-to-row to the contiguous 2D element array.
             * \return A \c const array pointer.
             */
            ConstArrayPointer getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the elements of \a m to this fixed-size matrix.
             * \param m The source fixed-size matrix.
             * \return A reference to itself.
             */
            CMatrix& operator=(const CMatrix& m)
            {
                if (this != &m) {
                    for (SizeType i = 0; i < M; i++)
                        std::copy(m.data[i], m.data[i] + N, data[i]);
                }

                return *this;
            }

            /**
             * \brief Assigns the contents of the matrix container \a c to this fixed-size matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            CMatrix& operator=(const MatrixContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the rows in \a l to this fixed-size matrix (clipped or zero-padded to \a M \f$ \times \f$ \a N).
             * \param l The initializer list of rows.
             * \return A reference to itself.
             */
            template <typename T1>
            CMatrix& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the matrix expression \a e to this fixed-size matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& operator=(const MatrixExpression<E>& e)
            {
                CMatrix      tmp(e);
                return this->operator=(tmp);
            }

            /**
             * \brief Adds the contents of the matrix container \a c element-wise to this fixed-size matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            CMatrix& operator+=(const MatrixContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the rows in \a l element-wise to this fixed-size matrix.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            CMatrix& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the matrix expression \a e element-wise to this fixed-size matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& operator+=(const MatrixExpression<E>& e)
            {
                CMatrix      tmp(*this + e);
                return this->operator=(tmp);
            }

            /**
             * \brief Subtracts the contents of the matrix container \a c element-wise from this fixed-size matrix (no alias check needed).
             * \tparam C The source matrix container type.
             * \param c The source matrix container.
             * \return A reference to itself.
             */
            template <typename C>
            CMatrix& operator-=(const MatrixContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this fixed-size matrix.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            CMatrix& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the matrix expression \a e element-wise from this fixed-size matrix (via a temporary to handle aliasing).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& operator-=(const MatrixExpression<E>& e)
            {
                CMatrix      tmp(*this - e);
                return this->operator=(tmp);
            }

            /**
             * \brief Multiplies every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CMatrix>::type& operator*=(const T1& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CMatrix>::type& operator/=(const T1& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the matrix expression \a e to this fixed-size matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& assign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Assigns the rows in \a l to this fixed-size matrix (clipped or zero-padded to \a M \f$ \times \f$ \a N).
             * \param l The initializer list of rows.
             * \return A reference to itself.
             * \throw Base::SizeError if \c l.size() exceeds \a M or any row's size exceeds \a N.
             */
            CMatrix& assign(InitializerListType l)
            {
                SizeType n_rows = CDPL_MATH_CHECK_MAX_SIZE(SizeType(l.size()), M, Base::SizeError);

                for (SizeType i = 0; i < n_rows; i++) {
                    const auto& row = *(l.begin() + i);

                    if (row.size() < N) {
                        std::copy(row.begin(), row.end(), data[i]);
                        std::fill(data[i] + row.size(), data[i] + N, ValueType());

                    } else {
                        CDPL_MATH_CHECK_MAX_SIZE(SizeType(row.size()), N, Base::SizeError);
                        std::copy(row.begin(), row.begin() + N, data[i]);
                    }
                }

                for (SizeType i = n_rows; i < M; i++)
                    std::fill(data[i], data[i] + N, ValueType());

                return *this;
            }

            /**
             * \brief Adds the elements of the matrix expression \a e to this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the rows in \a l element-wise to this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the addends.
             * \return A reference to itself.
             */
            CMatrix& plusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the matrix expression \a e from this matrix without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            CMatrix& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the rows in \a l element-wise from this matrix without intermediate temporary.
             * \param l The initializer list of rows providing the subtrahends.
             * \return A reference to itself.
             */
            CMatrix& minusAssign(InitializerListType l)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, InitListMatrix<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this fixed-size matrix with those of \a m.
             * \param m The fixed-size matrix to swap with.
             */
            void swap(CMatrix& m)
            {
                if (this != &m) {
                    for (SizeType i = 0; i < M; i++)
                        std::swap_ranges(data[i], data[i] + N, m.data[i]);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first fixed-size matrix.
             * \param m2 The second fixed-size matrix.
             */
            friend void swap(CMatrix& m1, CMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Sets every element of the matrix to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                for (SizeType i = 0; i < M; i++)
                    std::fill(data[i], data[i] + N, v);
            }

          private:
            ArrayType data;
        };

        template <typename T, std::size_t M, std::size_t N>
        const typename CMatrix<T, M, N>::SizeType CMatrix<T, M, N>::Size1;
        template <typename T, std::size_t M, std::size_t N>
        const typename CMatrix<T, M, N>::SizeType CMatrix<T, M, N>::Size2;

        /**
         * \brief Constant matrix expression whose entries are all zero.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ZeroMatrix : public MatrixContainer<ZeroMatrix<T> >
        {

            typedef ZeroMatrix<T> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T                                     ValueType;
            /** \brief Reference type (always a \c const reference — all elements are zero). */
            typedef const T&                              Reference;
            /** \brief Constant reference type to the zero element. */
            typedef const T&                              ConstReference;
            /** \brief The unsigned size type. */
            typedef std::size_t                           SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t                        DifferenceType;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef Matrix<T>                             MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix. */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an empty zero matrix.
             */
            ZeroMatrix():
                size1(0), size2(0) {}

            /**
             * \brief Constructs a zero matrix of size \f$ m \times n \f$.
             * \param m The number of rows.
             * \param n The number of columns.
             */
            ZeroMatrix(SizeType m, SizeType n):
                size1(m), size2(n) {}

            /**
             * \brief Constructs a copy of the zero matrix \a m.
             * \param m The zero matrix to copy.
             */
            ZeroMatrix(const ZeroMatrix& m):
                size1(m.size1), size2(m.size2) {}

            /**
             * \brief Returns a \c const reference to the zero element.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the zero element.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return zero;
            }

            /**
             * \brief Tells whether the matrix is empty (either dimension is zero).
             * \return \c true if either dimension is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0);
            }

            /**
             * \brief Returns the logical number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the logical number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum number of rows.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum number of columns.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimensions from \a m.
             * \param m The source zero matrix.
             * \return A reference to itself.
             */
            ZeroMatrix& operator=(const ZeroMatrix& m)
            {
                if (this != &m) {
                    size1 = m.size1;
                    size2 = m.size2;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimensions with \a m.
             * \param m The zero matrix to swap with.
             */
            void swap(ZeroMatrix& m)
            {
                if (this != &m) {
                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first zero matrix.
             * \param m2 The second zero matrix.
             */
            friend void swap(ZeroMatrix& m1, ZeroMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the dimensions to \f$ m \times n \f$.
             * \param m The new row count.
             * \param n The new column count.
             */
            void resize(SizeType m, SizeType n)
            {
                size1 = m;
                size2 = n;
            }

          private:
            SizeType               size1;
            SizeType               size2;
            static const ValueType zero;
        };

        template <typename T>
        const typename ZeroMatrix<T>::ValueType ZeroMatrix<T>::zero = ZeroMatrix<T>::ValueType();

        /**
         * \brief Constant matrix expression in which every entry equals the same scalar value.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ScalarMatrix : public MatrixContainer<ScalarMatrix<T> >
        {

            typedef ScalarMatrix<T> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T                                     ValueType;
            /** \brief Reference type (always a \c const reference — elements are immutable). */
            typedef const T&                              Reference;
            /** \brief Constant reference type to the common value. */
            typedef const T&                              ConstReference;
            /** \brief The unsigned size type. */
            typedef std::size_t                           SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t                        DifferenceType;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef Matrix<T>                             MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix. */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an empty scalar matrix.
             */
            ScalarMatrix():
                size1(0), size2(0), value() {}

            /**
             * \brief Constructs a scalar matrix of size \f$ m \times n \f$ in which every entry equals \a v.
             * \param m The number of rows.
             * \param n The number of columns.
             * \param v The common entry value.
             */
            ScalarMatrix(SizeType m, SizeType n, const ValueType& v = ValueType()):
                size1(m), size2(n), value(v) {}

            /**
             * \brief Constructs a copy of the scalar matrix \a m.
             * \param m The scalar matrix to copy.
             */
            ScalarMatrix(const ScalarMatrix& m):
                size1(m.size1), size2(m.size2), value(m.value) {}

            /**
             * \brief Returns a \c const reference to the common entry value.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to the common entry value.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return value;
            }

            /**
             * \brief Tells whether the matrix is empty.
             * \return \c true if either dimension is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0);
            }

            /**
             * \brief Returns the logical number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the logical number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum number of rows.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum number of columns.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimensions and common value from \a m.
             * \param m The source scalar matrix.
             * \return A reference to itself.
             */
            ScalarMatrix& operator=(const ScalarMatrix& m)
            {
                if (this != &m) {
                    size1 = m.size1;
                    size2 = m.size2;
                    value = m.value;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimensions and common value with \a m.
             * \param m The scalar matrix to swap with.
             */
            void swap(ScalarMatrix& m)
            {
                if (this != &m) {
                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                    std::swap(value, m.value);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first scalar matrix.
             * \param m2 The second scalar matrix.
             */
            friend void swap(ScalarMatrix& m1, ScalarMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the dimensions to \f$ m \times n \f$.
             * \param m The new row count.
             * \param n The new column count.
             */
            void resize(SizeType m, SizeType n)
            {
                size1 = m;
                size2 = n;
            }

          private:
            SizeType  size1;
            SizeType  size2;
            ValueType value;
        };

        /**
         * \brief Constant identity-matrix expression (\f$ 1 \f$ on the diagonal, \f$ 0 \f$ elsewhere).
         * \tparam T The scalar value type.
         */
        template <typename T>
        class IdentityMatrix : public MatrixContainer<IdentityMatrix<T> >
        {

            typedef IdentityMatrix<T> SelfType;

          public:
            /** \brief The scalar value type. */
            typedef T                                     ValueType;
            /** \brief Reference type (always a \c const reference — elements are immutable). */
            typedef const T&                              Reference;
            /** \brief Constant reference type to an element. */
            typedef const T&                              ConstReference;
            /** \brief The unsigned size type. */
            typedef std::size_t                           SizeType;
            /** \brief The signed difference type. */
            typedef std::ptrdiff_t                        DifferenceType;
            /** \brief Closure type used when this matrix appears inside another expression. */
            typedef MatrixReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this matrix appears inside another expression. */
            typedef const MatrixReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary matrix type used by expression-template machinery. */
            typedef Matrix<T>                             MatrixTemporaryType;
            /** \brief Concrete temporary vector type used when assembling vectors from this matrix. */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an empty identity matrix.
             */
            IdentityMatrix():
                size1(0), size2(0) {}

            /**
             * \brief Constructs an identity matrix of size \f$ m \times n \f$ (\c 1 on the diagonal, \c 0 elsewhere).
             * \param m The number of rows.
             * \param n The number of columns.
             */
            IdentityMatrix(SizeType m, SizeType n):
                size1(m), size2(n) {}

            /**
             * \brief Constructs a copy of the identity matrix \a m.
             * \param m The identity matrix to copy.
             */
            IdentityMatrix(const IdentityMatrix& m):
                size1(m.size1), size2(m.size2) {}

            /**
             * \brief Returns a \c const reference to either \c 1 (if \a i equals \a j) or \c 0.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return A \c const reference to either \c 1 (on the diagonal) or \c 0 (off the diagonal).
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);
                return (i == j ? one : zero);
            }

            /**
             * \brief Tells whether the matrix is empty.
             * \return \c true if either dimension is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0);
            }

            /**
             * \brief Returns the logical number of rows.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the logical number of columns.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum number of rows.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum number of columns.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimensions from \a m.
             * \param m The source identity matrix.
             * \return A reference to itself.
             */
            IdentityMatrix& operator=(const IdentityMatrix& m)
            {
                if (this != &m) {
                    size1 = m.size1;
                    size2 = m.size2;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimensions with \a m.
             * \param m The identity matrix to swap with.
             */
            void swap(IdentityMatrix& m)
            {
                if (this != &m) {
                    std::swap(size1, m.size1);
                    std::swap(size2, m.size2);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first identity matrix.
             * \param m2 The second identity matrix.
             */
            friend void swap(IdentityMatrix& m1, IdentityMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the dimensions to \f$ m \times n \f$.
             * \param m The new row count.
             * \param n The new column count.
             */
            void resize(SizeType m, SizeType n)
            {
                size1 = m;
                size2 = n;
            }

          private:
            SizeType               size1;
            SizeType               size2;
            static const ValueType zero;
            static const ValueType one;
        };

        template <typename T>
        const typename IdentityMatrix<T>::ValueType IdentityMatrix<T>::zero = IdentityMatrix<T>::ValueType();
        template <typename T>
        const typename IdentityMatrix<T>::ValueType IdentityMatrix<T>::one = IdentityMatrix<T>::ValueType(1);

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying matrix for a Math::MatrixReference view.
         * \tparam M The underlying matrix type.
         */
        template <typename M>
        struct VectorTemporaryTraits<MatrixReference<M> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying matrix for a \c const Math::MatrixReference view.
         * \tparam M The underlying matrix type.
         */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixReference<M> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the underlying matrix for a Math::MatrixReference view.
         * \tparam M The underlying matrix type.
         */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixReference<M> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the underlying matrix for a \c const Math::MatrixReference view.
         * \tparam M The underlying matrix type.
         */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixReference<M> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Returns the determinant of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return The determinant of \a e.
         */
        template <typename E>
        typename E::ValueType
        det(const MatrixExpression<E>& e)
        {
            typedef typename E::ValueType                ValueType;
            typedef typename Matrix<ValueType>::SizeType SizeType;

            Matrix<ValueType>     lu(e);
            std::vector<SizeType> pv(lu.getSize1());
            std::size_t           num_row_swaps;

            luDecompose(lu, pv, num_row_swaps);

            ValueType res(1);
            SizeType  size = std::min(lu.getSize1(), lu.getSize2());

            for (SizeType i = 0; i < size; i++)
                res *= lu(i, i);

            return (num_row_swaps % 2 == 0 ? res : -res);
        }

        /**
         * \brief Returns the determinant of the matrix container \a c (specialization avoiding an extra temporary copy when possible).
         * \tparam C The matrix container type.
         * \param c The matrix container.
         * \return The determinant of \a c.
         */
        template <typename C>
        typename C::ValueType
        det(const MatrixContainer<C>& c)
        {
            typedef typename C::ValueType                   ValueType;
            typedef typename MatrixTemporaryTraits<C>::Type CTemporaryType;
            typedef typename CTemporaryType::SizeType       SizeType;

            CTemporaryType        lu(c);
            std::vector<SizeType> pv(lu.getSize1());
            std::size_t           num_row_swaps;

            luDecompose(lu, pv, num_row_swaps);

            ValueType res(1);
            SizeType  size = std::min(lu.getSize1(), lu.getSize2());

            for (SizeType i = 0; i < size; i++)
                res *= lu(i, i);

            return (num_row_swaps % 2 == 0 ? res : -res);
        }

        /**
         * \brief Computes the inverse of the matrix expression \a e and stores it in \a c.
         * \tparam E The source matrix expression type.
         * \tparam C The output matrix container type.
         * \param e The matrix expression to invert.
         * \param c The output container receiving the inverse of \a e.
         * \return \c true if \a e is invertible and the inverse was computed, and \c false if \a e is singular.
         */
        template <typename E, typename C>
        bool
        invert(const MatrixExpression<E>& e, MatrixContainer<C>& c)
        {
            typedef typename C::ValueType                   ValueType;
            typedef typename MatrixTemporaryTraits<C>::Type CTemporaryType;
            typedef typename CTemporaryType::SizeType       SizeType;

            CTemporaryType        lu(e);
            std::vector<SizeType> pv(lu.getSize1());
            std::size_t           num_row_swaps;

            if (luDecompose(lu, pv, num_row_swaps) > 0)
                return false;

            c().assign(IdentityMatrix<ValueType>(lu.getSize1(), lu.getSize2()));

            return luSubstitute(lu, pv, c);
        }

        /**
         * \brief Computes the inverse of the matrix container \a c in place.
         * \tparam C The matrix container type.
         * \param c The matrix container to invert in place.
         * \return \c true if \a c is invertible and the inverse was computed, and \c false if \a c is singular.
         */
        template <typename C>
        bool
        invert(MatrixContainer<C>& c)
        {
            return invert(c, c);
        }

        /**
         * \brief Memory-efficient immutable matrix where all elements have the value zero of type <tt>float</tt>.
         */
        typedef ZeroMatrix<float> FZeroMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the value zero of type <tt>double</tt>.
         */
        typedef ZeroMatrix<double> DZeroMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the value zero of type <tt>long</tt>.
         */
        typedef ZeroMatrix<long> LZeroMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the value zero of type <tt>unsigned long</tt>.
         */
        typedef ZeroMatrix<unsigned long> ULZeroMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the same value of type <tt>float</tt>.
         */
        typedef ScalarMatrix<float> FScalarMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the same value of type <tt>double</tt>.
         */
        typedef ScalarMatrix<double> DScalarMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the same value of type <tt>long</tt>.
         */
        typedef ScalarMatrix<long> LScalarMatrix;

        /**
         * \brief Memory-efficient immutable matrix where all elements have the same value of type <tt>unsigned long</tt>.
         */
        typedef ScalarMatrix<unsigned long> ULScalarMatrix;

        /**
         * \brief Memory-efficient immutable identity matrix with element values of type <tt>float</tt>.
         */
        typedef IdentityMatrix<float> FIdentityMatrix;

        /**
         * \brief Memory-efficient immutable identity matrix with element values of type <tt>double</tt>.
         */
        typedef IdentityMatrix<double> DIdentityMatrix;

        /**
         * \brief Memory-efficient immutable identity matrix with element values of type <tt>long</tt>.
         */
        typedef IdentityMatrix<long> LIdentityMatrix;

        /**
         * \brief Memory-efficient immutable identity matrix with element values of type <tt>unsigned long</tt>.
         */
        typedef IdentityMatrix<unsigned long> ULIdentityMatrix;

        /**
         * \brief Unbounded dense matrix holding floating point values of type <tt>float</tt>..
         */
        typedef Matrix<float> FMatrix;

        /**
         * \brief Unbounded dense matrix holding floating point values of type <tt>double</tt>..
         */
        typedef Matrix<double> DMatrix;

        /**
         * \brief Unbounded dense matrix holding signed integers of type <tt>long</tt>.
         */
        typedef Matrix<long> LMatrix;

        /**
         * \brief Unbounded dense matrix holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef Matrix<unsigned long> ULMatrix;

        /**
         * \brief Bounded 2x2 matrix holding floating point values of type <tt>float</tt>.
         */
        typedef CMatrix<float, 2, 2> Matrix2F;

        /**
         * \brief Bounded 3x3 matrix holding floating point values of type <tt>float</tt>.
         */
        typedef CMatrix<float, 3, 3> Matrix3F;

        /**
         * \brief Bounded 4x4 matrix holding floating point values of type <tt>float</tt>.
         */
        typedef CMatrix<float, 4, 4> Matrix4F;

        /**
         * \brief Bounded 2x2 matrix holding floating point values of type <tt>double</tt>.
         */
        typedef CMatrix<double, 2, 2> Matrix2D;

        /**
         * \brief Bounded 3x3 matrix holding floating point values of type <tt>double</tt>.
         */
        typedef CMatrix<double, 3, 3> Matrix3D;

        /**
         * \brief Bounded 4x4 matrix holding floating point values of type <tt>double</tt>.
         */
        typedef CMatrix<double, 4, 4> Matrix4D;

        /**
         * \brief Bounded 2x2 matrix holding signed integers of type <tt>long</tt>.
         */
        typedef CMatrix<long, 2, 2> Matrix2L;

        /**
         * \brief Bounded 3x3 matrix holding signed integers of type <tt>long</tt>.
         */
        typedef CMatrix<long, 3, 3> Matrix3L;

        /**
         * \brief Bounded 4x4 matrix holding signed integers of type <tt>long</tt>.
         */
        typedef CMatrix<long, 4, 4> Matrix4L;

        /**
         * \brief Bounded 2x2 matrix holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CMatrix<unsigned long, 2, 2> Matrix2UL;

        /**
         * \brief Bounded 3x3 matrix holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CMatrix<unsigned long, 3, 3> Matrix3UL;

        /**
         * \brief Bounded 4x4 matrix holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CMatrix<unsigned long, 4, 4> Matrix4UL;

        /**
         * \brief Unbounded sparse matrix holding floating point values of type <tt>float</tt>..
         */
        typedef SparseMatrix<float> SparseFMatrix;

        /**
         * \brief Unbounded sparse matrix holding floating point values of type <tt>double</tt>..
         */
        typedef SparseMatrix<double> SparseDMatrix;

        /**
         * \brief Unbounded sparse matrix holding signed integers of type <tt>long</tt>.
         */
        typedef SparseMatrix<long> SparseLMatrix;

        /**
         * \brief Unbounded sparse matrix holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef SparseMatrix<unsigned long> SparseULMatrix;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIX_HPP
