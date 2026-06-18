/* 
 * MatrixExpression.hpp 
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
 * \brief Definition of various matrix expression types and operations.
 */

#ifndef CDPL_MATH_MATRIXEXPRESSION_HPP
#define CDPL_MATH_MATRIXEXPRESSION_HPP

#include <type_traits>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename C>
        class VectorContainer;
        template <typename C>
        class MatrixContainer;

        /**
         * \brief Expression-template node applying a unary functor \a F element-wise to a matrix expression \a E.
         * \tparam E The wrapped matrix expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        class MatrixUnary : public MatrixExpression<MatrixUnary<E, F> >
        {

            typedef MatrixUnary<E, F>            SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType     ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType            ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType            Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType             ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                   ClosureType;

            /**
             * \brief The size type inherited from the wrapped expression.
             */
            typedef typename E::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped expression.
             */
            typedef typename E::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping \a e.
             * \param e The matrix expression to wrap.
             */
            MatrixUnary(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the wrapped expression's first-dimension size.
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr.getSize1();
            }

            /**
             * \brief Returns the wrapped expression's second-dimension size.
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr.getSize2();
            }

            /**
             * \brief Applies the unary functor to element (\a i, \a j) of the wrapped expression and returns the result.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The element value as transformed by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr(i, j));
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::MatrixUnary instantiation <\a E, \a F>.
         * \tparam E The matrix expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        struct MatrixUnaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef MatrixUnary<E, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType    ResultType;
        };

        /**
         * \brief Expression-template node interpreting a vector expression \a E as a column matrix via the per-element functor \a F.
         * \tparam E The wrapped vector expression type.
         * \tparam F The unary functor type producing matrix elements from vector elements.
         */
        template <typename E, typename F>
        class VectorMatrixUnary : public MatrixExpression<VectorMatrixUnary<E, F> >
        {

            typedef VectorMatrixUnary<E, F>      SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType     ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType            ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType            Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType             ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                   ClosureType;

            /**
             * \brief The size type inherited from the wrapped vector expression.
             */
            typedef typename E::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped vector expression.
             */
            typedef typename E::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping the vector expression \a e.
             * \param e The vector expression to wrap.
             */
            VectorMatrixUnary(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the wrapped vector expression's size (used as the number of rows of the resulting matrix view).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr.getSize();
            }

            /**
             * \brief Returns the wrapped vector expression's size (used as the number of columns of the resulting matrix view).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr.getSize();
            }

            /**
             * \brief Applies the functor to the wrapped vector expression and the index pair (\a i, \a j) to produce the matrix element.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The computed matrix element.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr, i, j);
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::VectorMatrixUnary instantiation <\a E, \a F>.
         * \tparam E The vector expression type.
         * \tparam F The unary functor type producing matrix elements from vector elements.
         */
        template <typename E, typename F>
        struct VectorMatrixUnaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef VectorMatrixUnary<E, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType          ResultType;
        };

        /**
         * \brief Expression-template node combining two matrix expressions \a E1 and \a E2 element-wise via the binary functor \a F.
         * \tparam E1 The first wrapped matrix expression type.
         * \tparam E2 The second wrapped matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class MatrixBinary1 : public MatrixExpression<MatrixBinary1<E1, E2, F> >
        {

            typedef MatrixBinary1<E1, E2, F>      SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType                                                              ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType                                                                     ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType                                                                     Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType                                                                      ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                                                                            ClosureType;

            /**
             * \brief The common size type of the two wrapped expressions.
             */
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;

            /**
             * \brief The common signed difference type of the two wrapped expressions.
             */
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping \a e1 and \a e2.
             * \param e1 The first matrix expression.
             * \param e2 The second matrix expression.
             */
            MatrixBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the number of rows after verifying that both wrapped expressions agree on it.
             * \return The number of rows.
             * \throw Base::SizeError if the two wrapped expressions report different first-dimension sizes.
             */
            SizeType getSize1() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize1()), SizeType(expr2.getSize1()), Base::SizeError);
            }

            /**
             * \brief Returns the number of columns after verifying that both wrapped expressions agree on it.
             * \return The number of columns.
             * \throw Base::SizeError if the two wrapped expressions report different second-dimension sizes.
             */
            SizeType getSize2() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize2()), SizeType(expr2.getSize2()), Base::SizeError);
            }

            /**
             * \brief Applies the binary functor element-wise at (\a i, \a j) of the two wrapped expressions and returns the result.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i, j), expr2(i, j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::MatrixBinary1 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct MatrixBinary1Traits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef MatrixBinary1<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType           ResultType;
        };

        /**
         * \brief Expression-template node combining two matrix expressions \a E1 and \a E2 via a binary functor \a F that
         *        is invoked with both expressions plus the (\e i, \e j) cell indices.
         *
         * Unlike Math::MatrixBinary1 (which is element-wise), the functor here receives both expressions verbatim
         * along with the cell coordinates — used for matrix products and similar non-element-wise combinations.
         *
         * \tparam E1 The first wrapped matrix expression type.
         * \tparam E2 The second wrapped matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class MatrixBinary2 : public MatrixExpression<MatrixBinary2<E1, E2, F> >
        {

            typedef MatrixBinary2<E1, E2, F>      SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType                                                              ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType                                                                     ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType                                                                     Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType                                                                      ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                                                                            ClosureType;

            /**
             * \brief The common size type of the two wrapped expressions.
             */
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;

            /**
             * \brief The common signed difference type of the two wrapped expressions.
             */
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping \a e1 and \a e2.
             * \param e1 The first matrix expression.
             * \param e2 The second matrix expression.
             */
            MatrixBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the first wrapped expression's first-dimension size (number of rows of the result).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr1.getSize1();
            }

            /**
             * \brief Returns the second wrapped expression's second-dimension size (number of columns of the result).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr2.getSize2();
            }

            /**
             * \brief Invokes the functor with both wrapped expressions and the indices (\a i, \a j) and returns the result.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The computed element value.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1, expr2, i, j);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::MatrixBinary2 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct MatrixBinary2Traits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef MatrixBinary2<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType           ResultType;
        };

        /**
         * \brief Expression-template node interpreting a binary combination of two vector expressions as a matrix
         *        (e.g. outer product), via the per-cell functor \a F invoked with both expressions and the cell coordinates.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam F The per-cell functor type.
         */
        template <typename E1, typename E2, typename F>
        class VectorMatrixBinary : public MatrixExpression<VectorMatrixBinary<E1, E2, F> >
        {

            typedef VectorMatrixBinary<E1, E2, F> SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType                                                              ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType                                                                     ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType                                                                     Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType                                                                      ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                                                                            ClosureType;

            /**
             * \brief The common size type of the two wrapped vector expressions.
             */
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;

            /**
             * \brief The common signed difference type of the two wrapped vector expressions.
             */
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping \a e1 and \a e2.
             * \param e1 The first vector expression (row source).
             * \param e2 The second vector expression (column source).
             */
            VectorMatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the first wrapped vector expression's size (number of rows of the resulting matrix view).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr1.getSize();
            }

            /**
             * \brief Returns the second wrapped vector expression's size (number of columns of the resulting matrix view).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr2.getSize();
            }

            /**
             * \brief Applies the binary functor to \a e1(i) and \a e2(j) to produce the matrix element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The computed matrix element.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i), expr2(j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::VectorMatrixBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam F The per-cell functor type.
         */
        template <typename E1, typename E2, typename F>
        struct VectorMatrixBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef VectorMatrixBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                ResultType;
        };

        /**
         * \brief Expression-template node interpreting a binary combination of a matrix expression \a E1 and a vector expression \a E2
         *        as a vector (e.g. matrix-vector product), via the per-element functor \a F invoked with both expressions and the index.
         *
         * The resulting vector has size <tt>e1.getSize1()</tt> (i.e. the matrix expression's number of rows).
         *
         * \tparam E1 The matrix expression type.
         * \tparam E2 The vector expression type.
         * \tparam F The per-element functor type.
         */
        template <typename E1, typename E2, typename F>
        class Matrix1VectorBinary : public VectorExpression<Matrix1VectorBinary<E1, E2, F> >
        {

            typedef Matrix1VectorBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType                                                              ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType                                                                     ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType                                                                     Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType                                                                      ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                                                                            ClosureType;

            /**
             * \brief The common size type of the wrapped matrix and vector expressions.
             */
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;

            /**
             * \brief The common signed difference type of the wrapped matrix and vector expressions.
             */
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping the matrix expression \a e1 and the vector expression \a e2.
             * \param e1 The matrix expression.
             * \param e2 The vector expression.
             */
            Matrix1VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped matrix expression's first-dimension size (number of rows = size of the result vector).
             * \return The result vector size.
             */
            SizeType getSize() const
            {
                return expr1.getSize1();
            }

            /**
             * \brief Invokes the functor with the matrix expression, the vector expression, and the index \a i to compute element \a i of the result.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            /**
             * \brief Alias for operator() — invokes the functor with the matrix expression, the vector expression, and the index \a i.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Matrix1VectorBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The matrix expression type.
         * \tparam E2 The vector expression type.
         * \tparam F The per-element functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Matrix1VectorBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Matrix1VectorBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Expression-template node interpreting a binary combination of a vector expression \a E1 and a matrix expression \a E2
         *        as a vector (e.g. vector-matrix product), via the per-element functor \a F invoked with both expressions and the index.
         *
         * The resulting vector has size <tt>e2.getSize2()</tt> (i.e. the matrix expression's number of columns).
         *
         * \tparam E1 The vector expression type.
         * \tparam E2 The matrix expression type.
         * \tparam F The per-element functor type.
         */
        template <typename E1, typename E2, typename F>
        class Matrix2VectorBinary : public VectorExpression<Matrix2VectorBinary<E1, E2, F> >
        {

            typedef Matrix2VectorBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType                                                              ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType                                                                     ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType                                                                     Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType                                                                      ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                                                                            ClosureType;

            /**
             * \brief The common size type of the wrapped vector and matrix expressions.
             */
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;

            /**
             * \brief The common signed difference type of the wrapped vector and matrix expressions.
             */
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            /**
             * \brief Constructs the expression-template node wrapping the vector expression \a e1 and the matrix expression \a e2.
             * \param e1 The vector expression.
             * \param e2 The matrix expression.
             */
            Matrix2VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped matrix expression's second-dimension size (number of columns = size of the result vector).
             * \return The result vector size.
             */
            SizeType getSize() const
            {
                return expr2.getSize2();
            }

            /**
             * \brief Invokes the functor with the vector expression, the matrix expression, and the index \a i to compute element \a i of the result.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            /**
             * \brief Alias for operator() — invokes the functor with the vector expression, the matrix expression, and the index \a i.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Matrix2VectorBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The vector expression type.
         * \tparam E2 The matrix expression type.
         * \tparam F The per-element functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Matrix2VectorBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Matrix2VectorBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs) and a matrix expression \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar1MatrixBinary : public MatrixExpression<Scalar1MatrixBinary<E1, E2, F> >
        {

            typedef Scalar1MatrixBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef const E1                       Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType      ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType             ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType             Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType              ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                    ClosureType;

            /**
             * \brief The size type inherited from the wrapped matrix expression.
             */
            typedef typename E2::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped matrix expression.
             */
            typedef typename E2::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the scalar \a e1 and the matrix expression \a e2.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The matrix expression on the right-hand side.
             */
            Scalar1MatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped matrix expression's first-dimension size (number of rows).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr2.getSize1();
            }

            /**
             * \brief Returns the wrapped matrix expression's second-dimension size (number of columns).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr2.getSize2();
            }

            /**
             * \brief Applies the binary functor to the scalar and the element at (\a i, \a j) of the wrapped matrix expression and returns the result.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1, expr2(i, j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar1MatrixBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The matrix expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar1MatrixBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Scalar1MatrixBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Expression-template node combining a matrix expression \a E1 (lhs) and a scalar \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The wrapped matrix expression type.
         * \tparam E2 The scalar type appearing on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar2MatrixBinary : public MatrixExpression<Scalar2MatrixBinary<E1, E2, F> >
        {

            typedef Scalar2MatrixBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef const E2                       Expression2ClosureType;

          public:
            /**
             * \brief The element value type of the expression (the functor's result type).
             */
            typedef typename F::ResultType      ValueType;

            /**
             * \brief Constant reference type to an element value.
             */
            typedef const ValueType             ConstReference;

            /**
             * \brief Mutable reference type (degrades to \c const for expression-template results).
             */
            typedef const ValueType             Reference;

            /**
             * \brief Constant closure type used when this expression appears inside another expression.
             */
            typedef const SelfType              ConstClosureType;

            /**
             * \brief Closure type used when this expression appears inside another expression.
             */
            typedef SelfType                    ClosureType;

            /**
             * \brief The size type inherited from the wrapped matrix expression.
             */
            typedef typename E1::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped matrix expression.
             */
            typedef typename E1::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the matrix expression \a e1 and the scalar \a e2.
             * \param e1 The matrix expression on the left-hand side.
             * \param e2 The scalar value on the right-hand side.
             */
            Scalar2MatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped matrix expression's first-dimension size (number of rows).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return expr1.getSize1();
            }

            /**
             * \brief Returns the wrapped matrix expression's second-dimension size (number of columns).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return expr1.getSize2();
            }

            /**
             * \brief Applies the binary functor to the element at (\a i, \a j) of the wrapped matrix expression and the scalar and returns the result.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i, j), expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar2MatrixBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The matrix expression type.
         * \tparam E2 The scalar type on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar2MatrixBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Scalar2MatrixBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Mutable view adapter that exposes the transpose of a matrix \a M as a matrix expression (\f$ (i, j) \to M(j, i) \f$).
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        class MatrixTranspose : public MatrixExpression<MatrixTranspose<M> >
        {

            typedef MatrixTranspose<M> SelfType;

          public:
            /**
             * \brief The wrapped matrix type.
             */
            typedef M                                                        MatrixType;

            /**
             * \brief The size type used by the wrapped matrix.
             */
            typedef typename M::SizeType                                     SizeType;

            /**
             * \brief The signed difference type used by the wrapped matrix.
             */
            typedef typename M::DifferenceType                               DifferenceType;

            /**
             * \brief The element value type of the wrapped matrix.
             */
            typedef typename M::ValueType                                    ValueType;

            /**
             * \brief Constant reference type to an element.
             */
            typedef typename M::ConstReference                               ConstReference;

            /**
             * \brief Mutable reference type (degrades to ConstReference when the wrapped matrix is \c const).
             */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;

            /**
             * \brief Closure type used to store the wrapped matrix internally.
             */
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;

            /**
             * \brief Constant closure type used when this proxy appears inside another expression.
             */
            typedef const SelfType                                           ConstClosureType;

            /**
             * \brief Closure type used when this proxy appears inside another expression.
             */
            typedef SelfType                                                 ClosureType;

            /**
             * \brief Constructs the transpose view proxy referring to \a m.
             * \param m The wrapped matrix.
             */
            explicit MatrixTranspose(MatrixType& m):
                data(m) {}

            /**
             * \brief Returns a mutable reference to the wrapped matrix's element at (\a j, \a i).
             * \param i The zero-based row index in the transposed view.
             * \param j The zero-based column index in the transposed view.
             * \return A mutable reference to \c m(j, i).
             */
            Reference operator()(SizeType i, SizeType j)
            {
                return data(j, i);
            }

            /**
             * \brief Returns a \c const reference to the wrapped matrix's element at (\a j, \a i).
             * \param i The zero-based row index in the transposed view.
             * \param j The zero-based column index in the transposed view.
             * \return A \c const reference to \c m(j, i).
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(j, i);
            }

            /**
             * \brief Returns the number of rows of the transpose view (= number of columns of the wrapped matrix).
             * \return The number of rows.
             */
            SizeType getSize1() const
            {
                return data.getSize2();
            }

            /**
             * \brief Returns the number of columns of the transpose view (= number of rows of the wrapped matrix).
             * \return The number of columns.
             */
            SizeType getSize2() const
            {
                return data.getSize1();
            }

            /**
             * \brief Returns the maximum number of elements the wrapped matrix can hold.
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            /**
             * \brief Tells whether the view is empty (the wrapped matrix has zero rows or zero columns).
             * \return \c true if the wrapped matrix is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (data.getSize1() == 0 || data.getSize2() == 0);
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
             * \brief Copy-assigns the wrapped matrix from the contents of \a mt's wrapped matrix.
             * \param mt The source transpose view.
             * \return A reference to itself.
             */
            MatrixTranspose& operator=(const MatrixTranspose& mt)
            {
                data.operator=(mt.data);
                return *this;
            }

            /**
             * \brief Assigns the wrapped matrix from \a mt's wrapped matrix (possibly differing types).
             * \tparam M1 The source wrapped matrix type.
             * \param mt The source transpose view.
             * \return A reference to itself.
             */
            template <typename M1>
            MatrixTranspose& operator=(const MatrixTranspose<M1>& mt)
            {
                data.operator=(mt.getData());
                return *this;
            }

            /**
             * \brief Assigns the matrix expression \a e to this transpose view (writes the transpose into the wrapped matrix).
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& operator=(const MatrixExpression<E>& e)
            {
                data.operator=(MatrixTranspose<const E>(e()));
                return *this;
            }

            /**
             * \brief Adds the matrix expression \a e to this transpose view.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& operator+=(const MatrixExpression<E>& e)
            {
                data.operator+=(MatrixTranspose<const E>(e()));
                return *this;
            }

            /**
             * \brief Subtracts the matrix expression \a e from this transpose view.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& operator-=(const MatrixExpression<E>& e)
            {
                data.operator-=(MatrixTranspose<const E>(e()));
                return *this;
            }

            /**
             * \brief Multiplies every element of the wrapped matrix by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixTranspose>::type& operator*=(const T& t)
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
            typename std::enable_if<IsScalar<T>::value, MatrixTranspose>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            /**
             * \brief Assigns the matrix expression \a e to this transpose view without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& assign(const MatrixExpression<E>& e)
            {
                data.assign((MatrixTranspose<const E>(e())));
                return *this;
            }

            /**
             * \brief Adds the matrix expression \a e to this transpose view without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& plusAssign(const MatrixExpression<E>& e)
            {
                data.plusAssign((MatrixTranspose<const E>(e())));
                return *this;
            }

            /**
             * \brief Subtracts the matrix expression \a e from this transpose view without intermediate temporary.
             * \tparam E The source matrix expression type.
             * \param e The source matrix expression.
             * \return A reference to itself.
             */
            template <typename E>
            MatrixTranspose& minusAssign(const MatrixExpression<E>& e)
            {
                data.minusAssign((MatrixTranspose<const E>(e())));
                return *this;
            }

            /**
             * \brief Swaps the underlying matrices of the two transpose views.
             * \param mt The transpose view to swap with.
             */
            void swap(MatrixTranspose& mt)
            {
                data.swap(mt.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param mt1 The first transpose view.
             * \param mt2 The second transpose view.
             */
            friend void swap(MatrixTranspose& mt1, MatrixTranspose& mt2)
            {
                mt1.swap(mt2);
            }

          private:
            MatrixClosureType data;
        };

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a Math::MatrixTranspose view.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        struct VectorTemporaryTraits<MatrixTranspose<M> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a \c const Math::MatrixTranspose view.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        struct VectorTemporaryTraits<const MatrixTranspose<M> > : public VectorTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a Math::MatrixTranspose view.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        struct MatrixTemporaryTraits<MatrixTranspose<M> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Math::MatrixTemporaryTraits specialization inheriting the temporary type of the wrapped matrix for a \c const Math::MatrixTranspose view.
         * \tparam M The wrapped matrix type.
         */
        template <typename M>
        struct MatrixTemporaryTraits<const MatrixTranspose<M> > : public MatrixTemporaryTraits<M>
        {};

        /**
         * \brief Returns the element-wise negation of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return An expression-template node representing \f$ -e \f$.
         */
        template <typename E>
        typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType
        operator-(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the matrix expression \a e unchanged (unary \c +).
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return A \c const reference to \a e.
         */
        template <typename E>
        const E&
        operator+(const MatrixExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Returns the element-wise sum of the matrix expressions \a e1 and \a e2.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return An expression-template node representing \f$ e_1 + e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator+(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise difference of the matrix expressions \a e1 and \a e2.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return An expression-template node representing \f$ e_1 - e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator-(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product of the matrix expression \a e and the scalar \a t.
         * \tparam E The matrix expression type.
         * \tparam T The scalar type.
         * \param e The matrix expression.
         * \param t The scalar multiplier.
         * \return An expression-template node representing \f$ e \cdot t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2MatrixBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const MatrixExpression<E>& e, const T& t)
        {
            typedef typename Scalar2MatrixBinaryTraits<E, T,
                                                       ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Returns the element-wise product of the scalar \a t and the matrix expression \a e.
         * \tparam T The scalar type.
         * \tparam E The matrix expression type.
         * \param t The scalar multiplier.
         * \param e The matrix expression.
         * \return An expression-template node representing \f$ t \cdot e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1MatrixBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
        operator*(const T& t, const MatrixExpression<E>& e)
        {
            typedef typename Scalar1MatrixBinaryTraits<T, E,
                                                       ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the element-wise quotient of the matrix expression \a e by the scalar \a t.
         * \tparam E The matrix expression type.
         * \tparam T The scalar type.
         * \param e The matrix expression.
         * \param t The scalar divisor.
         * \return An expression-template node representing \f$ e / t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2MatrixBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const MatrixExpression<E>& e, const T& t)
        {
            typedef typename Scalar2MatrixBinaryTraits<E, T,
                                                       ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Tells whether the matrix expressions \a e1 and \a e2 are element-wise equal.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return \c true if both matrices have equal dimensions and equal elements, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename MatrixEquality<E1, E2>::ResultType
        operator==(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            return MatrixEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the matrix expressions \a e1 and \a e2 differ in at least one element.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return \c true if the matrices differ in dimension or in any element, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename MatrixEquality<E1, E2>::ResultType
        operator!=(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            return !MatrixEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the matrix expressions \a e1 and \a e2 agree element-wise within the absolute tolerance \a eps.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \tparam T The numeric tolerance type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \param eps The non-negative absolute tolerance.
         * \return \c true if all elements agree within \a eps, and \c false otherwise.
         */
        template <typename E1, typename E2, typename T>
        typename std::enable_if<std::is_arithmetic<T>::value, typename MatrixToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, const T& eps)
        {
            return MatrixToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        /**
         * \brief Returns the element-wise complex conjugate of the matrix expression \a e (identity for real-valued matrices).
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        conj(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the Hermitian conjugate (conjugate transpose) of the matrix expression \a e — currently aliased to conj() pending transpose support.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        herm(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise real part of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return An expression-template node representing the real part of \a e.
         */
        template <typename E>
        typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType
        real(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise imaginary part of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return An expression-template node representing the imaginary part of \a e.
         */
        template <typename E>
        typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType
        imag(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the outer product of the vector expressions \a e1 and \a e2 as a matrix expression \f$ e_1 \cdot e_2^T \f$.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return An expression-template node representing the outer product.
         */
        template <typename E1, typename E2>
        typename VectorMatrixBinaryTraits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        outerProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorMatrixBinaryTraits<E1, E2,
                                                      ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise quotient of the matrix expressions \a e1 and \a e2.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The numerator matrix expression.
         * \param e2 The denominator matrix expression.
         * \return An expression-template node representing the element-wise quotient \f$ e_1 / e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemDiv(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product (Hadamard product) of the matrix expressions \a e1 and \a e2.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return An expression-template node representing the element-wise product \f$ e_1 \odot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemProd(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the matrix-vector product \f$ e_1 \cdot e_2 \f$ as a vector expression.
         * \tparam E1 The matrix expression type.
         * \tparam E2 The vector expression type.
         * \param e1 The matrix expression.
         * \param e2 The vector expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType
        operator*(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the matrix-vector product \f$ e_1 \cdot e_2 \f$ as a vector expression (named-function form of operator*).
         * \tparam E1 The matrix expression type.
         * \tparam E2 The vector expression type.
         * \param e1 The matrix expression.
         * \param e2 The vector expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType
        prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Computes the matrix-vector product \f$ e_1 \cdot e_2 \f$ and stores it in \a c.
         * \tparam C The output vector container type.
         * \tparam E1 The matrix expression type.
         * \tparam E2 The input vector expression type.
         * \param e1 The matrix expression.
         * \param e2 The input vector expression.
         * \param c The output vector container receiving the result.
         * \return A reference to \a c.
         */
        template <typename C, typename E1, typename E2>
        C& prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2, VectorContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        /**
         * \brief Returns the vector-matrix product \f$ e_1 \cdot e_2 \f$ as a vector expression.
         * \tparam E1 The vector expression type.
         * \tparam E2 The matrix expression type.
         * \param e1 The vector expression.
         * \param e2 The matrix expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType
        operator*(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the vector-matrix product \f$ e_1 \cdot e_2 \f$ as a vector expression (named-function form of operator*).
         * \tparam E1 The vector expression type.
         * \tparam E2 The matrix expression type.
         * \param e1 The vector expression.
         * \param e2 The matrix expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType
        prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Computes the vector-matrix product \f$ e_1 \cdot e_2 \f$ and stores it in \a c.
         * \tparam C The output vector container type.
         * \tparam E1 The input vector expression type.
         * \tparam E2 The matrix expression type.
         * \param e1 The input vector expression.
         * \param e2 The matrix expression.
         * \param c The output vector container receiving the result.
         * \return A reference to \a c.
         */
        template <typename C, typename E1, typename E2>
        C& prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2, VectorContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        /**
         * \brief Returns the matrix-matrix product \f$ e_1 \cdot e_2 \f$ as a matrix expression.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType
        operator*(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the matrix-matrix product \f$ e_1 \cdot e_2 \f$ as a matrix expression (named-function form of operator*).
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType
        prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Computes the matrix-matrix product \f$ e_1 \cdot e_2 \f$ and stores it in \a c.
         * \tparam C The output matrix container type.
         * \tparam E1 The first matrix expression type.
         * \tparam E2 The second matrix expression type.
         * \param e1 The first matrix expression.
         * \param e2 The second matrix expression.
         * \param c The output matrix container receiving the result.
         * \return A reference to \a c.
         */
        template <typename C, typename E1, typename E2>
        C& prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, MatrixContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        /**
         * \brief Returns the trace (sum of diagonal elements) of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return \f$ \sum_i e(i, i) \f$.
         */
        template <typename E>
        typename MatrixTrace<E>::ResultType
        trace(const MatrixExpression<E>& e)
        {
            return MatrixTrace<E>::apply(e);
        }

        /**
         * \brief Returns the L1 (maximum absolute column sum) norm of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return The L1 norm of \a e.
         */
        template <typename E>
        typename MatrixNorm1<E>::ResultType
        norm1(const MatrixExpression<E>& e)
        {
            return MatrixNorm1<E>::apply(e);
        }

        /**
         * \brief Returns the Frobenius norm of the matrix expression \a e (\f$ \sqrt{\sum_{i, j} |e(i, j)|^2} \f$).
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return The Frobenius norm of \a e.
         */
        template <typename E>
        typename MatrixNormFrobenius<E>::ResultType
        normFrob(const MatrixExpression<E>& e)
        {
            return MatrixNormFrobenius<E>::apply(e);
        }

        /**
         * \brief Returns the L&infin; (maximum absolute row sum) norm of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return The L&infin; norm of \a e.
         */
        template <typename E>
        typename MatrixNormInfinity<E>::ResultType
        normInf(const MatrixExpression<E>& e)
        {
            return MatrixNormInfinity<E>::apply(e);
        }

        /**
         * \brief Returns a diagonal matrix whose diagonal entries are the components of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing the diagonal matrix.
         */
        template <typename E>
        typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ResultType
        diag(const VectorExpression<E>& e)
        {
            typedef typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the cross-product (skew-symmetric) matrix corresponding to the 3-vector expression \a e (such that <tt>cross(e) * v == crossProd(e, v)</tt>).
         * \tparam E The vector expression type.
         * \param e The 3-vector expression.
         * \return An expression-template node representing the skew-symmetric matrix.
         */
        template <typename E>
        typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ResultType
        cross(const VectorExpression<E>& e)
        {
            typedef typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns a mutable Math::MatrixTranspose view of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression to transpose.
         * \return A mutable transpose view of \a e.
         */
        template <typename E>
        MatrixTranspose<E> trans(MatrixExpression<E>& e)
        {
            return MatrixTranspose<E>(e());
        }

        /**
         * \brief Returns a constant Math::MatrixTranspose view of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression to transpose.
         * \return A constant transpose view of \a e.
         */
        template <typename E>
        MatrixTranspose<const E> trans(const MatrixExpression<E>& e)
        {
            return MatrixTranspose<const E>(e());
        }

        /**
         * \brief Returns the sum of all elements of the matrix expression \a e.
         * \tparam E The matrix expression type.
         * \param e The matrix expression.
         * \return \f$ \sum_{i, j} e(i, j) \f$.
         */
        template <typename E>
        typename MatrixElementSum<E>::ResultType
        sum(const MatrixExpression<E>& e)
        {
            return MatrixElementSum<E>::apply(e);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXEXPRESSION_HPP
