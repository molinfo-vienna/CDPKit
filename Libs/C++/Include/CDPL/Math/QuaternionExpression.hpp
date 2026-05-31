/* 
 * QuaternionExpression.hpp 
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
 * \brief Definition of various quaternion expression types and operations.
 */

#ifndef CDPL_MATH_QUATERNIONEXPRESSION_HPP
#define CDPL_MATH_QUATERNIONEXPRESSION_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Expression-template node applying a unary functor \a F that returns a quaternion result to a quaternion expression \a E.
         * \tparam E The wrapped quaternion expression type.
         * \tparam F The unary functor type returning a quaternion.
         */
        template <typename E, typename F>
        class QuaternionUnary1 : public QuaternionExpression<QuaternionUnary1<E, F> >
        {

            typedef QuaternionUnary1<E, F>       SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node wrapping \a e.
             * \param e The quaternion expression to wrap.
             */
            QuaternionUnary1(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the result of applying the unary functor to component \e C1 of the wrapped expression.
             * \return The transformed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::apply(expr.getC1());
            }

            /**
             * \brief Returns the result of applying the unary functor to component \e C2 of the wrapped expression.
             * \return The transformed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::apply(expr.getC2());
            }

            /**
             * \brief Returns the result of applying the unary functor to component \e C3 of the wrapped expression.
             * \return The transformed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::apply(expr.getC3());
            }

            /**
             * \brief Returns the result of applying the unary functor to component \e C4 of the wrapped expression.
             * \return The transformed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::apply(expr.getC4());
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::QuaternionUnary1 instantiation <\a E, \a F>.
         * \tparam E The quaternion expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        struct QuaternionUnary1Traits
        {

            /** \brief The expression-template node type. */
            typedef QuaternionUnary1<E, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType         ResultType;
        };

        /**
         * \brief Expression-template node applying a per-component functor \a F to a quaternion expression \a E,
         *        where \a F exposes four separate apply methods (\c applyC1 / \c applyC2 / \c applyC3 / \c applyC4)
         *        operating on the whole source expression.
         * \tparam E The wrapped quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E, typename F>
        class QuaternionUnary2 : public QuaternionExpression<QuaternionUnary2<E, F> >
        {

            typedef QuaternionUnary2<E, F>       SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node wrapping \a e.
             * \param e The quaternion expression to wrap.
             */
            QuaternionUnary2(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the wrapped expression.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the wrapped expression.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the wrapped expression.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the wrapped expression.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr);
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::QuaternionUnary2 instantiation <\a E, \a F>.
         * \tparam E The quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E, typename F>
        struct QuaternionUnary2Traits
        {

            /** \brief The expression-template node type. */
            typedef QuaternionUnary2<E, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType         ResultType;
        };

        /**
         * \brief Expression-template node combining two quaternion expressions \a E1 and \a E2 component-wise via the binary functor \a F.
         * \tparam E1 The first wrapped quaternion expression type.
         * \tparam E2 The second wrapped quaternion expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class QuaternionBinary1 : public QuaternionExpression<QuaternionBinary1<E1, E2, F> >
        {

            typedef QuaternionBinary1<E1, E2, F>  SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node wrapping \a e1 and \a e2.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             */
            QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the binary functor to the \e C1 components of the two wrapped expressions.
             * \return The combined \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::apply(expr1.getC1(), expr2.getC1());
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C2 components of the two wrapped expressions.
             * \return The combined \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::apply(expr1.getC2(), expr2.getC2());
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C3 components of the two wrapped expressions.
             * \return The combined \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::apply(expr1.getC3(), expr2.getC3());
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C4 components of the two wrapped expressions.
             * \return The combined \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::apply(expr1.getC4(), expr2.getC4());
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::QuaternionBinary1 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct QuaternionBinary1Traits
        {

            /** \brief The expression-template node type. */
            typedef QuaternionBinary1<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType               ResultType;
        };

        /**
         * \brief Expression-template node combining two quaternion expressions \a E1 and \a E2 via the per-component functor \a F
         *        (which exposes four separate \c applyC1 / \c applyC2 / \c applyC3 / \c applyC4 methods operating on the whole source expressions).
         * \tparam E1 The first wrapped quaternion expression type.
         * \tparam E2 The second wrapped quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        class QuaternionBinary2 : public QuaternionExpression<QuaternionBinary2<E1, E2, F> >
        {

            typedef QuaternionBinary2<E1, E2, F>  SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node wrapping \a e1 and \a e2.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             */
            QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the two wrapped expressions.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the two wrapped expressions.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the two wrapped expressions.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the two wrapped expressions.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr1, expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::QuaternionBinary2 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        struct QuaternionBinary2Traits
        {

            /** \brief The expression-template node type. */
            typedef QuaternionBinary2<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType               ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs) and a quaternion expression \a E2 (rhs) component-wise via the binary functor \a F.
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped quaternion expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar1QuaternionBinary1 : public QuaternionExpression<Scalar1QuaternionBinary1<E1, E2, F> >
        {

            typedef Scalar1QuaternionBinary1<E1, E2, F> SelfType;
            typedef F                                   FunctorType;
            typedef E1                                  Expression1Type;
            typedef E2                                  Expression2Type;
            typedef const E1                            Expression1ClosureType;
            typedef typename E2::ConstClosureType       Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the scalar \a e1 and the quaternion expression \a e2.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The quaternion expression on the right-hand side.
             */
            Scalar1QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the binary functor to the scalar and the \e C1 component of the wrapped expression.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::apply(expr1, expr2.getC1());
            }

            /**
             * \brief Returns the result of applying the binary functor to the scalar and the \e C2 component of the wrapped expression.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::apply(expr1, expr2.getC2());
            }

            /**
             * \brief Returns the result of applying the binary functor to the scalar and the \e C3 component of the wrapped expression.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::apply(expr1, expr2.getC3());
            }

            /**
             * \brief Returns the result of applying the binary functor to the scalar and the \e C4 component of the wrapped expression.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::apply(expr1, expr2.getC4());
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar1QuaternionBinary1 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The quaternion expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar1QuaternionBinary1Traits
        {

            /** \brief The expression-template node type. */
            typedef Scalar1QuaternionBinary1<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                      ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs) and a quaternion expression \a E2 (rhs) via the per-component functor \a F
         *        (which exposes \c applyC1 / \c applyC2 / \c applyC3 / \c applyC4 methods).
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar1QuaternionBinary2 : public QuaternionExpression<Scalar1QuaternionBinary2<E1, E2, F> >
        {

            typedef Scalar1QuaternionBinary2<E1, E2, F> SelfType;
            typedef F                                   FunctorType;
            typedef E1                                  Expression1Type;
            typedef E2                                  Expression2Type;
            typedef const E1                            Expression1ClosureType;
            typedef typename E2::ConstClosureType       Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the scalar \a e1 and the quaternion expression \a e2.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The quaternion expression on the right-hand side.
             */
            Scalar1QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the scalar and the wrapped expression.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the scalar and the wrapped expression.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the scalar and the wrapped expression.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the scalar and the wrapped expression.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr1, expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar1QuaternionBinary2 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The quaternion expression type.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar1QuaternionBinary2Traits
        {

            /** \brief The expression-template node type. */
            typedef Scalar1QuaternionBinary2<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                      ResultType;
        };

        /**
         * \brief Expression-template node combining a quaternion expression \a E1 (lhs) and a scalar \a E2 (rhs) component-wise via the binary functor \a F.
         * \tparam E1 The wrapped quaternion expression type.
         * \tparam E2 The scalar type appearing on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar2QuaternionBinary1 : public QuaternionExpression<Scalar2QuaternionBinary1<E1, E2, F> >
        {

            typedef Scalar2QuaternionBinary1<E1, E2, F> SelfType;
            typedef F                                   FunctorType;
            typedef E1                                  Expression1Type;
            typedef E2                                  Expression2Type;
            typedef typename E1::ConstClosureType       Expression1ClosureType;
            typedef const E2                            Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the quaternion expression \a e1 and the scalar \a e2.
             * \param e1 The quaternion expression on the left-hand side.
             * \param e2 The scalar value on the right-hand side.
             */
            Scalar2QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the binary functor to the \e C1 component of the wrapped expression and the scalar.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::apply(expr1.getC1(), expr2);
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C2 component of the wrapped expression and the scalar.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::apply(expr1.getC2(), expr2);
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C3 component of the wrapped expression and the scalar.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::apply(expr1.getC3(), expr2);
            }

            /**
             * \brief Returns the result of applying the binary functor to the \e C4 component of the wrapped expression and the scalar.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::apply(expr1.getC4(), expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar2QuaternionBinary1 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The quaternion expression type.
         * \tparam E2 The scalar type on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar2QuaternionBinary1Traits
        {

            /** \brief The expression-template node type. */
            typedef Scalar2QuaternionBinary1<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                      ResultType;
        };

        /**
         * \brief Expression-template node combining a quaternion expression \a E1 (lhs) and a scalar \a E2 (rhs) via the per-component functor \a F
         *        (which exposes \c applyC1 / \c applyC2 / \c applyC3 / \c applyC4 methods).
         * \tparam E1 The wrapped quaternion expression type.
         * \tparam E2 The scalar type appearing on the right-hand side.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar2QuaternionBinary2 : public QuaternionExpression<Scalar2QuaternionBinary2<E1, E2, F> >
        {

            typedef Scalar2QuaternionBinary2<E1, E2, F> SelfType;
            typedef F                                   FunctorType;
            typedef E1                                  Expression1Type;
            typedef E2                                  Expression2Type;
            typedef typename E1::ConstClosureType       Expression1ClosureType;
            typedef const E2                            Expression2ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the quaternion expression \a e1 and the scalar \a e2.
             * \param e1 The quaternion expression on the left-hand side.
             * \param e2 The scalar value on the right-hand side.
             */
            Scalar2QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the wrapped expression and the scalar.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the wrapped expression and the scalar.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the wrapped expression and the scalar.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr1, expr2);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the wrapped expression and the scalar.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr1, expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar2QuaternionBinary2 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The quaternion expression type.
         * \tparam E2 The scalar type on the right-hand side.
         * \tparam F The per-component functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar2QuaternionBinary2Traits
        {

            /** \brief The expression-template node type. */
            typedef Scalar2QuaternionBinary2<E1, E2, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                      ResultType;
        };

        /**
         * \brief Expression-template node combining two quaternion expressions \a E1 (lhs) and \a E2 (middle) with a scalar \a E3 (rhs)
         *        via the per-component ternary functor \a F.
         * \tparam E1 The first wrapped quaternion expression type.
         * \tparam E2 The second wrapped quaternion expression type.
         * \tparam E3 The scalar type appearing on the right-hand side.
         * \tparam F The per-component ternary functor type.
         */
        template <typename E1, typename E2, typename E3, typename F>
        class Scalar3QuaternionTernary : public QuaternionExpression<Scalar3QuaternionTernary<E1, E2, E3, F> >
        {

            typedef Scalar3QuaternionTernary<E1, E2, E3, F> SelfType;
            typedef F                                       FunctorType;
            typedef E1                                      Expression1Type;
            typedef E2                                      Expression2Type;
            typedef E3                                      Expression3Type;
            typedef typename E1::ConstClosureType           Expression1ClosureType;
            typedef typename E2::ConstClosureType           Expression2ClosureType;
            typedef const E3                                Expression3ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the two quaternion expressions and the scalar.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \param e3 The scalar value on the right-hand side.
             */
            Scalar3QuaternionTernary(const Expression1Type& e1, const Expression2Type& e2, const Expression3Type& e3):
                expr1(e1), expr2(e2), expr3(e3) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the two wrapped expressions and the scalar.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the two wrapped expressions and the scalar.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the two wrapped expressions and the scalar.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the two wrapped expressions and the scalar.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr1, expr2, expr3);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
            Expression3ClosureType expr3;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar3QuaternionTernary instantiation <\a E1, \a E2, \a E3, \a F>.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \tparam E3 The scalar type on the right-hand side.
         * \tparam F The per-component ternary functor type.
         */
        template <typename E1, typename E2, typename E3, typename F>
        struct Scalar3QuaternionTernaryTraits
        {

            /** \brief The expression-template node type. */
            typedef Scalar3QuaternionTernary<E1, E2, E3, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                          ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs), a quaternion expression \a E2 (middle), and a scalar \a E3 (rhs)
         *        via the per-component ternary functor \a F.
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped quaternion expression type.
         * \tparam E3 The scalar type appearing on the right-hand side.
         * \tparam F The per-component ternary functor type.
         */
        template <typename E1, typename E2, typename E3, typename F>
        class Scalar13QuaternionTernary : public QuaternionExpression<Scalar13QuaternionTernary<E1, E2, E3, F> >
        {

            typedef Scalar13QuaternionTernary<E1, E2, E3, F> SelfType;
            typedef F                                        FunctorType;
            typedef E1                                       Expression1Type;
            typedef E2                                       Expression2Type;
            typedef E3                                       Expression3Type;
            typedef const E1                                 Expression1ClosureType;
            typedef typename E2::ConstClosureType            Expression2ClosureType;
            typedef const E3                                 Expression3ClosureType;

          public:
            /** \brief The element value type of the expression (the functor's result type). */
            typedef typename F::ResultType ValueType;
            /** \brief Constant reference type to a component value. */
            typedef const ValueType        ConstReference;
            /** \brief Mutable reference type (degrades to \c const for expression-template results). */
            typedef const ValueType        Reference;
            /** \brief Constant closure type used when this expression appears inside another expression. */
            typedef const SelfType         ConstClosureType;
            /** \brief Closure type used when this expression appears inside another expression. */
            typedef SelfType               ClosureType;

            /**
             * \brief Constructs the expression-template node combining the two scalars and the wrapped quaternion expression.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The wrapped quaternion expression.
             * \param e3 The scalar value on the right-hand side.
             */
            Scalar13QuaternionTernary(const Expression1Type& e1, const Expression2Type& e2, const Expression3Type& e3):
                expr1(e1), expr2(e2), expr3(e3) {}

            /**
             * \brief Returns the result of applying the functor's \c applyC1 method to the two scalars and the wrapped expression.
             * \return The computed \e C1 component.
             */
            ConstReference getC1() const
            {
                return FunctorType::applyC1(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC2 method to the two scalars and the wrapped expression.
             * \return The computed \e C2 component.
             */
            ConstReference getC2() const
            {
                return FunctorType::applyC2(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC3 method to the two scalars and the wrapped expression.
             * \return The computed \e C3 component.
             */
            ConstReference getC3() const
            {
                return FunctorType::applyC3(expr1, expr2, expr3);
            }

            /**
             * \brief Returns the result of applying the functor's \c applyC4 method to the two scalars and the wrapped expression.
             * \return The computed \e C4 component.
             */
            ConstReference getC4() const
            {
                return FunctorType::applyC4(expr1, expr2, expr3);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
            Expression3ClosureType expr3;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar13QuaternionTernary instantiation <\a E1, \a E2, \a E3, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The quaternion expression type.
         * \tparam E3 The scalar type on the right-hand side.
         * \tparam F The per-component ternary functor type.
         */
        template <typename E1, typename E2, typename E3, typename F>
        struct Scalar13QuaternionTernaryTraits
        {

            /** \brief The expression-template node type. */
            typedef Scalar13QuaternionTernary<E1, E2, E3, F> ExpressionType;
            /** \brief The expression-template result type returned by free-function operators. */
            typedef ExpressionType                           ResultType;
        };

        /**
         * \brief Returns the component-wise negation of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return An expression-template node representing \f$ -e \f$.
         */
        template <typename E>
        typename QuaternionUnary1Traits<E, ScalarNegation<typename E::ValueType> >::ResultType
        operator-(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary1Traits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the quaternion expression \a e unchanged (unary \c +).
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return A \c const reference to \a e.
         */
        template <typename E>
        const E&
        operator+(const QuaternionExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Returns the component-wise sum of the quaternion expressions \a e1 and \a e2.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return An expression-template node representing \f$ e_1 + e_2 \f$.
         */
        template <typename E1, typename E2>
        typename QuaternionBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator+(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                                                     ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Adds the scalar \a t to the real component (C1) of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \tparam T The scalar type.
         * \param e The quaternion expression.
         * \param t The scalar summand.
         * \return An expression-template node representing \f$ e + t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionAddition<E, T> >::ResultType>::type
        operator+(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionAddition<E, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Adds the scalar \a t to the real component (C1) of the quaternion expression \a e (commutative form).
         * \tparam T The scalar type.
         * \tparam E The quaternion expression type.
         * \param t The scalar summand.
         * \param e The quaternion expression.
         * \return An expression-template node representing \f$ t + e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionAddition<T, E> >::ResultType>::type
        operator+(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionAddition<T, E> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the component-wise difference of the quaternion expressions \a e1 and \a e2.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return An expression-template node representing \f$ e_1 - e_2 \f$.
         */
        template <typename E1, typename E2>
        typename QuaternionBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator-(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                                                     ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Subtracts the scalar \a t from the real component (C1) of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \tparam T The scalar type.
         * \param e The quaternion expression.
         * \param t The scalar subtrahend.
         * \return An expression-template node representing \f$ e - t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionSubtraction<E, T> >::ResultType>::type
        operator-(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionSubtraction<E, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Subtracts the quaternion expression \a e from the scalar \a t (forming \f$ t - e \f$ as a quaternion expression).
         * \tparam T The scalar type.
         * \tparam E The quaternion expression type.
         * \param t The scalar minuend.
         * \param e The quaternion expression to subtract.
         * \return An expression-template node representing \f$ t - e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionSubtraction<T, E> >::ResultType>::type
        operator-(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionSubtraction<T, E> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the (Hamilton) product of the quaternion expressions \a e1 and \a e2.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return An expression-template node representing \f$ e_1 \cdot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename QuaternionBinary2Traits<E1, E2, QuaternionProduct<E1, E2> >::ResultType
        operator*(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary2Traits<E1, E2, QuaternionProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the component-wise product of the quaternion expression \a e and the scalar \a t.
         * \tparam E The quaternion expression type.
         * \tparam T The scalar type.
         * \param e The quaternion expression.
         * \param t The scalar multiplier.
         * \return An expression-template node representing \f$ e \cdot t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary1Traits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary1Traits<E, T,
                                                            ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Returns the component-wise product of the scalar \a t and the quaternion expression \a e.
         * \tparam T The scalar type.
         * \tparam E The quaternion expression type.
         * \param t The scalar multiplier.
         * \param e The quaternion expression.
         * \return An expression-template node representing \f$ t \cdot e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary1Traits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
        operator*(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary1Traits<T, E,
                                                            ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the quaternion division \f$ e_1 \cdot e_2^{-1} \f$ as an expression-template node.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The dividend quaternion expression.
         * \param e2 The divisor quaternion expression.
         * \return An expression-template node representing \f$ e_1 / e_2 \f$.
         */
        template <typename E1, typename E2>
        typename Scalar3QuaternionTernaryTraits<E1, E2, typename QuaternionNorm2<E2>::ResultType,
                                                QuaternionDivision<E1, E2, typename QuaternionNorm2<E2>::ResultType> >::ResultType
        operator/(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename Scalar3QuaternionTernaryTraits<E1, E2, typename QuaternionNorm2<E2>::ResultType,
                                                            QuaternionDivision<E1, E2, typename QuaternionNorm2<E2>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2(), norm2(e2));
        }

        /**
         * \brief Returns the component-wise quotient of the quaternion expression \a e by the scalar \a t.
         * \tparam E The quaternion expression type.
         * \tparam T The scalar type.
         * \param e The quaternion expression.
         * \param t The scalar divisor.
         * \return An expression-template node representing \f$ e / t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary1Traits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary1Traits<E, T,
                                                            ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Returns the quaternion division of the scalar \a t by the quaternion expression \a e (\f$ t \cdot e^{-1} \f$).
         * \tparam T The scalar type.
         * \tparam E The quaternion expression type.
         * \param t The scalar dividend.
         * \param e The quaternion expression divisor.
         * \return An expression-template node representing \f$ t / e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value,
                                typename Scalar13QuaternionTernaryTraits<T, E, typename QuaternionNorm2<E>::ResultType,
                                                                         ScalarQuaternionDivision<T, E, typename QuaternionNorm2<E>::ResultType> >::ResultType>::type
        operator/(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar13QuaternionTernaryTraits<T, E, typename QuaternionNorm2<E>::ResultType,
                                                             ScalarQuaternionDivision<T, E, typename QuaternionNorm2<E>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e(), norm2(e));
        }

        /**
         * \brief Tells whether the quaternion expressions \a e1 and \a e2 are component-wise equal.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return \c true if all four components agree, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename QuaternionEquality<E1, E2>::ResultType
        operator==(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            return QuaternionEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the quaternion expressions \a e1 and \a e2 differ in at least one component.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return \c true if at least one of the four components differs, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename QuaternionEquality<E1, E2>::ResultType
        operator!=(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            return !QuaternionEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the quaternion expressions \a e1 and \a e2 agree component-wise within the absolute tolerance \a eps.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \tparam T The numeric tolerance type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \param eps The non-negative absolute tolerance.
         * \return \c true if all four components agree within \a eps, and \c false otherwise.
         */
        template <typename E1, typename E2, typename T>
        typename std::enable_if<std::is_arithmetic<T>::value, typename QuaternionToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, const T& eps)
        {
            return QuaternionToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        /**
         * \brief Returns the component-wise quotient of the quaternion expressions \a e1 and \a e2.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The numerator quaternion expression.
         * \param e2 The denominator quaternion expression.
         * \return An expression-template node representing the component-wise quotient.
         */
        template <typename E1, typename E2>
        typename QuaternionBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemDiv(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                                                     ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the component-wise product (Hadamard product) of the quaternion expressions \a e1 and \a e2.
         * \tparam E1 The first quaternion expression type.
         * \tparam E2 The second quaternion expression type.
         * \param e1 The first quaternion expression.
         * \param e2 The second quaternion expression.
         * \return An expression-template node representing the component-wise product.
         */
        template <typename E1, typename E2>
        typename QuaternionBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemProd(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                                                     ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the real component (C1) of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return The real component \f$ \mathrm{Re}(e) \f$ as a scalar.
         */
        template <typename E>
        typename E::ValueType
        real(const QuaternionExpression<E>& e)
        {
            return e().getC1();
        }

        /**
         * \brief Returns the unreal (pure-quaternion) part of the quaternion expression \a e (with C1 zeroed out).
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return An expression-template node representing the unreal part of \a e.
         */
        template <typename E>
        typename QuaternionUnary2Traits<E, QuaternionUnreal<E> >::ResultType
        unreal(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary2Traits<E, QuaternionUnreal<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the quaternion conjugate of the quaternion expression \a e (negates C2, C3, C4).
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename QuaternionUnary2Traits<E, QuaternionConjugate<E> >::ResultType
        conj(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary2Traits<E, QuaternionConjugate<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the multiplicative inverse of the quaternion expression \a e (\f$ \overline{e} / |e|^2 \f$).
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return An expression-template node representing \f$ e^{-1} \f$.
         */
        template <typename E>
        typename Scalar2QuaternionBinary2Traits<E, typename QuaternionNorm2<E>::ResultType,
                                                QuaternionInverse<E, typename QuaternionNorm2<E>::ResultType> >::ResultType
        inv(const QuaternionExpression<E>& e)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, typename QuaternionNorm2<E>::ResultType,
                                                            QuaternionInverse<E, typename QuaternionNorm2<E>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(e(), norm2(e));
        }

        /**
         * \brief Returns the norm (Euclidean length) of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return \f$ \|e\| = \sqrt{e \cdot \overline{e}} \f$.
         */
        template <typename E>
        typename QuaternionNorm<E>::ResultType
        norm(const QuaternionExpression<E>& e)
        {
            return QuaternionNorm<E>::apply(e);
        }

        /**
         * \brief Returns the squared norm of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return \f$ \|e\|^2 = e \cdot \overline{e} \f$.
         */
        template <typename E>
        typename QuaternionNorm2<E>::ResultType
        norm2(const QuaternionExpression<E>& e)
        {
            return QuaternionNorm2<E>::apply(e);
        }

        /**
         * \brief Returns the sum of the four components of the quaternion expression \a e.
         * \tparam E The quaternion expression type.
         * \param e The quaternion expression.
         * \return \f$ \sum_{i} C_i(e) \f$.
         */
        template <typename E>
        typename QuaternionElementSum<E>::ResultType
        sum(const QuaternionExpression<E>& e)
        {
            return QuaternionElementSum<E>::apply(e);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_QUATERNIONEXPRESSION_HPP
