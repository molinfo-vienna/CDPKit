/* 
 * GridExpression.hpp 
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
 * \brief Definition of various grid expression types and operations.
 */

#ifndef CDPL_MATH_GRIDEXPRESSION_HPP
#define CDPL_MATH_GRIDEXPRESSION_HPP

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
        class GridContainer;

        /**
         * \brief Expression-template node applying a unary functor \a F element-wise to a grid expression \a E.
         * \tparam E The wrapped grid expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        class GridUnary : public GridExpression<GridUnary<E, F> >
        {

            typedef GridUnary<E, F>              SelfType;
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
             * \param e The grid expression to wrap.
             */
            GridUnary(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the size of the wrapped grid expression along the first dimension.
             * \return The wrapped expression's first-dimension size.
             */
            SizeType getSize1() const
            {
                return expr.getSize1();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the second dimension.
             * \return The wrapped expression's second-dimension size.
             */
            SizeType getSize2() const
            {
                return expr.getSize2();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the third dimension.
             * \return The wrapped expression's third-dimension size.
             */
            SizeType getSize3() const
            {
                return expr.getSize3();
            }

            /**
             * \brief Applies the unary functor to the element at (\a i, \a j, \a k) of the wrapped expression and returns the result.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return The element value as transformed by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return FunctorType::apply(expr(i, j, k));
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::GridUnary instantiation <\a E, \a F>.
         * \tparam E The grid expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        struct GridUnaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef GridUnary<E, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType  ResultType;
        };

        /**
         * \brief Expression-template node combining two grid expressions \a E1 and \a E2 element-wise via the binary functor \a F.
         * \tparam E1 The first wrapped grid expression type.
         * \tparam E2 The second wrapped grid expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class GridBinary1 : public GridExpression<GridBinary1<E1, E2, F> >
        {

            typedef GridBinary1<E1, E2, F>        SelfType;
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
             * \param e1 The first grid expression.
             * \param e2 The second grid expression.
             */
            GridBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the size along the first dimension after verifying that both wrapped expressions agree on it.
             * \return The first-dimension size.
             * \throw Base::SizeError if the two wrapped expressions report different first-dimension sizes.
             */
            SizeType getSize1() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize1()), SizeType(expr2.getSize1()), Base::SizeError);
            }

            /**
             * \brief Returns the size along the second dimension after verifying that both wrapped expressions agree on it.
             * \return The second-dimension size.
             * \throw Base::SizeError if the two wrapped expressions report different second-dimension sizes.
             */
            SizeType getSize2() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize2()), SizeType(expr2.getSize2()), Base::SizeError);
            }

            /**
             * \brief Returns the size along the third dimension after verifying that both wrapped expressions agree on it.
             * \return The third-dimension size.
             * \throw Base::SizeError if the two wrapped expressions report different third-dimension sizes.
             */
            SizeType getSize3() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize3()), SizeType(expr2.getSize3()), Base::SizeError);
            }

            /**
             * \brief Applies the binary functor to the elements at (\a i, \a j, \a k) of the two wrapped expressions and returns the result.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return FunctorType::apply(expr1(i, j, k), expr2(i, j, k));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::GridBinary1 instantiation Binary <\a E1, \a E2, \a F>.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct GridBinary1Traits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef GridBinary1<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType         ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs) and a grid expression \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped grid expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar1GridBinary : public GridExpression<Scalar1GridBinary<E1, E2, F> >
        {

            typedef Scalar1GridBinary<E1, E2, F>  SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef const E1                      Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

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
             * \brief The size type inherited from the wrapped grid expression.
             */
            typedef typename E2::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped grid expression.
             */
            typedef typename E2::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the scalar \a e1 and the grid expression \a e2.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The grid expression on the right-hand side.
             */
            Scalar1GridBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the size of the wrapped grid expression along the first dimension.
             * \return The wrapped expression's first-dimension size.
             */
            SizeType getSize1() const
            {
                return expr2.getSize1();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the second dimension.
             * \return The wrapped expression's second-dimension size.
             */
            SizeType getSize2() const
            {
                return expr2.getSize2();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the third dimension.
             * \return The wrapped expression's third-dimension size.
             */
            SizeType getSize3() const
            {
                return expr2.getSize3();
            }

            /**
             * \brief Applies the binary functor to the scalar and the element at (\a i, \a j, \a k) of the wrapped grid expression and returns the result.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return FunctorType::apply(expr1, expr2(i, j, k));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar1GridBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The grid expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar1GridBinaryTraits
        {
            /**
             * \brief The expression-template node type.
             */
            typedef Scalar1GridBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType               ResultType;
        };

        /**
         * \brief Expression-template node combining a grid expression \a E1 (lhs) and a scalar \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The wrapped grid expression type.
         * \tparam E2 The scalar type appearing on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar2GridBinary : public GridExpression<Scalar2GridBinary<E1, E2, F> >
        {

            typedef Scalar2GridBinary<E1, E2, F>  SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef const E2                      Expression2ClosureType;

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
             * \brief The size type inherited from the wrapped grid expression.
             */
            typedef typename E1::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped grid expression.
             */
            typedef typename E1::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the grid expression \a e1 and the scalar \a e2.
             * \param e1 The grid expression on the left-hand side.
             * \param e2 The scalar value on the right-hand side.
             */
            Scalar2GridBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the size of the wrapped grid expression along the first dimension.
             * \return The wrapped expression's first-dimension size.
             */
            SizeType getSize1() const
            {
                return expr1.getSize1();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the second dimension.
             * \return The wrapped expression's second-dimension size.
             */
            SizeType getSize2() const
            {
                return expr1.getSize2();
            }

            /**
             * \brief Returns the size of the wrapped grid expression along the third dimension.
             * \return The wrapped expression's third-dimension size.
             */
            SizeType getSize3() const
            {
                return expr1.getSize3();
            }

            /**
             * \brief Applies the binary functor to the element at (\a i, \a j, \a k) of the wrapped grid expression and the scalar and returns the result.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return FunctorType::apply(expr1(i, j, k), expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar2GridBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The grid expression type.
         * \tparam E2 The scalar type on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar2GridBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Scalar2GridBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType               ResultType;
        };

        /**
         * \brief Returns the element-wise negation of the grid expression \a e.
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return An expression-template node representing \f$ -e \f$.
         */
        template <typename E>
        typename GridUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType
        operator-(const GridExpression<E>& e)
        {
            typedef typename GridUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the grid expression \a e unchanged (unary \c +).
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return A \c const reference to \a e.
         */
        template <typename E>

        const E&
        operator+(const GridExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Returns the element-wise sum of the grid expressions \a e1 and \a e2.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \return An expression-template node representing \f$ e_1 + e_2 \f$.
         */
        template <typename E1, typename E2>
        typename GridBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator+(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            typedef typename GridBinary1Traits<E1, E2,
                                               ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise difference of the grid expressions \a e1 and \a e2.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \return An expression-template node representing \f$ e_1 - e_2 \f$.
         */
        template <typename E1, typename E2>
        typename GridBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator-(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            typedef typename GridBinary1Traits<E1, E2,
                                               ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product of the grid expression \a e and the scalar \a t.
         * \tparam E The grid expression type.
         * \tparam T The scalar type.
         * \param e The grid expression.
         * \param t The scalar multiplier.
         * \return An expression-template node representing \f$ e \cdot t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2GridBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const GridExpression<E>& e, const T& t)
        {
            typedef typename Scalar2GridBinaryTraits<E, T,
                                                     ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Returns the element-wise product of the scalar \a t and the grid expression \a e.
         * \tparam T The scalar type.
         * \tparam E The grid expression type.
         * \param t The scalar multiplier.
         * \param e The grid expression.
         * \return An expression-template node representing \f$ t \cdot e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1GridBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
        operator*(const T& t, const GridExpression<E>& e)
        {
            typedef typename Scalar1GridBinaryTraits<T, E,
                                                     ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the element-wise quotient of the grid expression \a e by the scalar \a t.
         * \tparam E The grid expression type.
         * \tparam T The scalar type.
         * \param e The grid expression.
         * \param t The scalar divisor.
         * \return An expression-template node representing \f$ e / t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2GridBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const GridExpression<E>& e, const T& t)
        {
            typedef typename Scalar2GridBinaryTraits<E, T,
                                                     ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Tells whether the grid expressions \a e1 and \a e2 are element-wise equal.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \return \c true if both grids have equal sizes and equal elements, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename GridEquality<E1, E2>::ResultType
        operator==(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            return GridEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the grid expressions \a e1 and \a e2 differ in at least one element.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \return \c true if the grids differ in size or in any element, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename GridEquality<E1, E2>::ResultType
        operator!=(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            return !GridEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the grid expressions \a e1 and \a e2 agree element-wise within the absolute tolerance \a eps.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \tparam T The numeric tolerance type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \param eps The non-negative absolute tolerance.
         * \return \c true if all elements agree within \a eps, and \c false otherwise.
         */
        template <typename E1, typename E2, typename T>
        typename std::enable_if<std::is_arithmetic<T>::value, typename GridToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const GridExpression<E1>& e1, const GridExpression<E2>& e2, const T& eps)
        {
            return GridToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        /**
         * \brief Returns the element-wise complex conjugate of the grid expression \a e (identity for real-valued grids).
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        conj(const GridExpression<E>& e)
        {
            typedef typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the Hermitian conjugate of the grid expression \a e (alias of conj() for grids).
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        herm(const GridExpression<E>& e)
        {
            typedef typename GridUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise real part of the grid expression \a e.
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return An expression-template node representing the real part of \a e.
         */
        template <typename E>
        typename GridUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType
        real(const GridExpression<E>& e)
        {
            typedef typename GridUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise imaginary part of the grid expression \a e.
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return An expression-template node representing the imaginary part of \a e.
         */
        template <typename E>
        typename GridUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType
        imag(const GridExpression<E>& e)
        {
            typedef typename GridUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise quotient of the grid expressions \a e1 and \a e2.
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The numerator grid expression.
         * \param e2 The denominator grid expression.
         * \return An expression-template node representing the element-wise quotient \f$ e_1 / e_2 \f$.
         */
        template <typename E1, typename E2>
        typename GridBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemDiv(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            typedef typename GridBinary1Traits<E1, E2,
                                               ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product of the grid expressions \a e1 and \a e2 (Hadamard product).
         * \tparam E1 The first grid expression type.
         * \tparam E2 The second grid expression type.
         * \param e1 The first grid expression.
         * \param e2 The second grid expression.
         * \return An expression-template node representing the element-wise product \f$ e_1 \odot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename GridBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemProd(const GridExpression<E1>& e1, const GridExpression<E2>& e2)
        {
            typedef typename GridBinary1Traits<E1, E2,
                                               ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the sum of all elements of the grid expression \a e.
         * \tparam E The grid expression type.
         * \param e The grid expression.
         * \return \f$ \sum_{i, j, k} e(i, j, k) \f$.
         */
        template <typename E>
        typename GridElementSum<E>::ResultType
        sum(const GridExpression<E>& e)
        {
            return GridElementSum<E>::apply(e);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_GRIDEXPRESSION_HPP
