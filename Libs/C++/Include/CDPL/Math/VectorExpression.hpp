/* 
 * VectorExpression.hpp 
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
 * \brief Definition of various vector expression types and operations.
 */

#ifndef CDPL_MATH_VECTOREXPRESSION_HPP
#define CDPL_MATH_VECTOREXPRESSION_HPP

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

        /**
         * \brief Expression-template node applying a unary functor \a F element-wise to a vector expression \a E.
         * \tparam E The wrapped vector expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        class VectorUnary : public VectorExpression<VectorUnary<E, F> >
        {

            typedef VectorUnary<E, F>            SelfType;
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
             * \param e The vector expression to wrap.
             */
            VectorUnary(const ExpressionType& e):
                expr(e) {}

            /**
             * \brief Returns the wrapped expression's size.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return expr.getSize();
            }

            /**
             * \brief Applies the unary functor to element \a i of the wrapped expression and returns the result.
             * \param i The zero-based element index.
             * \return The element value as transformed by the functor.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr(i));
            }

            /**
             * \brief Alias for operator() — applies the unary functor to element \a i of the wrapped expression.
             * \param i The zero-based element index.
             * \return The element value as transformed by the functor.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr[i]);
            }

          private:
            ExpressionClosureType expr;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::VectorUnary instantiation <\a E, \a F>.
         * \tparam E The vector expression type.
         * \tparam F The unary functor type.
         */
        template <typename E, typename F>
        struct VectorUnaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef VectorUnary<E, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType    ResultType;
        };

        /**
         * \brief Expression-template node combining two vector expressions \a E1 and \a E2 element-wise via the binary functor \a F.
         * \tparam E1 The first wrapped vector expression type.
         * \tparam E2 The second wrapped vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class VectorBinary1 : public VectorExpression<VectorBinary1<E1, E2, F> >
        {

            typedef VectorBinary1<E1, E2, F>      SelfType;
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
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             */
            VectorBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the element count after verifying that both wrapped expressions agree on it.
             * \return The element count.
             * \throw Base::SizeError if the two wrapped expressions report different sizes.
             */
            SizeType getSize() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize()), SizeType(expr2.getSize()), Base::SizeError);
            }

            /**
             * \brief Applies the binary functor element-wise at index \a i of the two wrapped expressions and returns the result.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1(i), expr2(i));
            }

            /**
             * \brief Alias for operator() — applies the binary functor element-wise at index \a i.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1[i], expr2[i]);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::VectorBinary1 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct VectorBinary1Traits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef VectorBinary1<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType           ResultType;
        };

        /**
         * \brief Expression-template node combining two vector expressions \a E1 and \a E2 via a binary functor \a F
         *        invoked with both expressions plus the element index \e i.
         *
         * Unlike Math::VectorBinary1 (which is element-wise), the functor here receives both expressions verbatim
         * along with the element index — used for inner products and similar non-element-wise combinations.
         *
         * \tparam E1 The first wrapped vector expression type.
         * \tparam E2 The second wrapped vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class VectorBinary2 : public VectorExpression<VectorBinary2<E1, E2, F> >
        {

            typedef VectorBinary2<E1, E2, F>      SelfType;
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
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             */
            VectorBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the element count after verifying that both wrapped expressions agree on it.
             * \return The element count.
             * \throw Base::SizeError if the two wrapped expressions report different sizes.
             */
            SizeType getSize() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize()), SizeType(expr2.getSize()), Base::SizeError);
            }

            /**
             * \brief Invokes the functor with both wrapped expressions and the index \a i and returns the result.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            /**
             * \brief Alias for operator() — invokes the functor with both wrapped expressions and the index \a i.
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
         * \brief Traits selecting the expression-template node and its result type for the Math::VectorBinary2 instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct VectorBinary2Traits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef VectorBinary2<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType           ResultType;
        };

        /**
         * \brief Expression-template node combining a scalar \a E1 (lhs) and a vector expression \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The scalar type appearing on the left-hand side.
         * \tparam E2 The wrapped vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar1VectorBinary : public VectorExpression<Scalar1VectorBinary<E1, E2, F> >
        {

            typedef Scalar1VectorBinary<E1, E2, F> SelfType;
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
             * \brief The size type inherited from the wrapped vector expression.
             */
            typedef typename E2::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped vector expression.
             */
            typedef typename E2::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the scalar \a e1 and the vector expression \a e2.
             * \param e1 The scalar value on the left-hand side.
             * \param e2 The vector expression on the right-hand side.
             */
            Scalar1VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped vector expression's size.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return expr2.getSize();
            }

            /**
             * \brief Applies the binary functor to the scalar and element \a i of the wrapped vector expression and returns the result.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2(i));
            }

            /**
             * \brief Alias for operator() — applies the binary functor to the scalar and element \a i of the wrapped expression.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1, expr2[i]);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar1VectorBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The scalar type on the left-hand side.
         * \tparam E2 The vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar1VectorBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Scalar1VectorBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Expression-template node combining a vector expression \a E1 (lhs) and a scalar \a E2 (rhs) element-wise via the binary functor \a F.
         * \tparam E1 The wrapped vector expression type.
         * \tparam E2 The scalar type appearing on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        class Scalar2VectorBinary : public VectorExpression<Scalar2VectorBinary<E1, E2, F> >
        {

            typedef Scalar2VectorBinary<E1, E2, F> SelfType;
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
             * \brief The size type inherited from the wrapped vector expression.
             */
            typedef typename E1::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped vector expression.
             */
            typedef typename E1::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the vector expression \a e1 and the scalar \a e2.
             * \param e1 The vector expression on the left-hand side.
             * \param e2 The scalar value on the right-hand side.
             */
            Scalar2VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped vector expression's size.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return expr1.getSize();
            }

            /**
             * \brief Applies the binary functor to element \a i of the wrapped vector expression and the scalar and returns the result.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1(i), expr2);
            }

            /**
             * \brief Alias for operator() — applies the binary functor to element \a i of the wrapped expression and the scalar.
             * \param i The zero-based element index.
             * \return The element value as combined by the functor.
             */
            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1[i], expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        /**
         * \brief Traits selecting the expression-template node and its result type for the Math::Scalar2VectorBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The vector expression type.
         * \tparam E2 The scalar type on the right-hand side.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct Scalar2VectorBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef Scalar2VectorBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                 ResultType;
        };

        /**
         * \brief Expression-template node combining a quaternion expression \a E1 and a vector expression \a E2
         *        into a vector expression via the per-element functor \a F (used e.g. for quaternion-vector rotation).
         * \tparam E1 The wrapped quaternion expression type.
         * \tparam E2 The wrapped vector expression type.
         * \tparam F The per-element functor type.
         */
        template <typename E1, typename E2, typename F>
        class QuaternionVectorBinary : public VectorExpression<QuaternionVectorBinary<E1, E2, F> >
        {

            typedef QuaternionVectorBinary<E1, E2, F> SelfType;
            typedef F                                 FunctorType;
            typedef E1                                Expression1Type;
            typedef E2                                Expression2Type;
            typedef typename E1::ConstClosureType     Expression1ClosureType;
            typedef typename E2::ConstClosureType     Expression2ClosureType;

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
             * \brief The size type inherited from the wrapped vector expression.
             */
            typedef typename E2::SizeType       SizeType;

            /**
             * \brief The signed difference type inherited from the wrapped vector expression.
             */
            typedef typename E2::DifferenceType DifferenceType;

            /**
             * \brief Constructs the expression-template node combining the quaternion expression \a e1 and the vector expression \a e2.
             * \param e1 The quaternion expression.
             * \param e2 The vector expression.
             */
            QuaternionVectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            /**
             * \brief Returns the wrapped vector expression's size.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return expr2.getSize();
            }

            /**
             * \brief Invokes the functor with the quaternion expression, the vector expression, and the index \a i.
             * \param i The zero-based element index.
             * \return The computed element value.
             */
            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            /**
             * \brief Alias for operator() — invokes the functor with both wrapped expressions and the index \a i.
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
         * \brief Traits selecting the expression-template node and its result type for the Math::QuaternionVectorBinary instantiation <\a E1, \a E2, \a F>.
         * \tparam E1 The quaternion expression type.
         * \tparam E2 The vector expression type.
         * \tparam F The binary functor type.
         */
        template <typename E1, typename E2, typename F>
        struct QuaternionVectorBinaryTraits
        {

            /**
             * \brief The expression-template node type.
             */
            typedef QuaternionVectorBinary<E1, E2, F> ExpressionType;

            /**
             * \brief The expression-template result type returned by free-function operators.
             */
            typedef ExpressionType                    ResultType;
        };

        /**
         * \brief Returns the element-wise negation of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing \f$ -e \f$.
         */
        template <typename E>
        typename VectorUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType
        operator-(const VectorExpression<E>& e)
        {
            typedef typename VectorUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the vector expression \a e unchanged (unary \c +).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A \c const reference to \a e.
         */
        template <typename E>
        const E&
        operator+(const VectorExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Returns the element-wise sum of the vector expressions \a e1 and \a e2.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return An expression-template node representing \f$ e_1 + e_2 \f$.
         */
        template <typename E1, typename E2>
        typename VectorBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator+(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorBinary1Traits<E1, E2,
                                                 ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise difference of the vector expressions \a e1 and \a e2.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return An expression-template node representing \f$ e_1 - e_2 \f$.
         */
        template <typename E1, typename E2>
        typename VectorBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator-(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorBinary1Traits<E1, E2,
                                                 ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product of the vector expression \a e and the scalar \a t.
         * \tparam E The vector expression type.
         * \tparam T The scalar type.
         * \param e The vector expression.
         * \param t The scalar multiplier.
         * \return An expression-template node representing \f$ e \cdot t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2VectorBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const VectorExpression<E>& e, const T& t)
        {
            typedef typename Scalar2VectorBinaryTraits<E, T,
                                                       ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Returns the element-wise product of the scalar \a t and the vector expression \a e.
         * \tparam T The scalar type.
         * \tparam E The vector expression type.
         * \param t The scalar multiplier.
         * \param e The vector expression.
         * \return An expression-template node representing \f$ t \cdot e \f$.
         */
        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1VectorBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
        operator*(const T& t, const VectorExpression<E>& e)
        {
            typedef typename Scalar1VectorBinaryTraits<T, E,
                                                       ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        /**
         * \brief Returns the element-wise quotient of the vector expression \a e by the scalar \a t.
         * \tparam E The vector expression type.
         * \tparam T The scalar type.
         * \param e The vector expression.
         * \param t The scalar divisor.
         * \return An expression-template node representing \f$ e / t \f$.
         */
        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2VectorBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const VectorExpression<E>& e, const T& t)
        {
            typedef typename Scalar2VectorBinaryTraits<E, T,
                                                       ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        /**
         * \brief Tells whether the vector expressions \a e1 and \a e2 are element-wise equal.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return \c true if both vectors have equal sizes and equal elements, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename VectorEquality<E1, E2>::ResultType
        operator==(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            return VectorEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the vector expressions \a e1 and \a e2 differ in at least one element.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return \c true if the vectors differ in size or in any element, and \c false otherwise.
         */
        template <typename E1, typename E2>
        typename VectorEquality<E1, E2>::ResultType
        operator!=(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            return !VectorEquality<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Tells whether the vector expressions \a e1 and \a e2 agree element-wise within the absolute tolerance \a eps.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam T The numeric tolerance type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \param eps The non-negative absolute tolerance.
         * \return \c true if all elements agree within \a eps, and \c false otherwise.
         */
        template <typename E1, typename E2, typename T>
        typename std::enable_if<std::is_arithmetic<T>::value, typename VectorToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, const T& eps)
        {
            return VectorToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        /**
         * \brief Returns the element-wise complex conjugate of the vector expression \a e (identity for real-valued vectors).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        conj(const VectorExpression<E>& e)
        {
            typedef typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the Hermitian conjugate of the vector expression \a e (alias of conj() for vectors).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing \f$ \overline{e} \f$.
         */
        template <typename E>
        typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        herm(const VectorExpression<E>& e)
        {
            typedef typename VectorUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise real part of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing the real part of \a e.
         */
        template <typename E>
        typename VectorUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType
        real(const VectorExpression<E>& e)
        {
            typedef typename VectorUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise imaginary part of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return An expression-template node representing the imaginary part of \a e.
         */
        template <typename E>
        typename VectorUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType
        imag(const VectorExpression<E>& e)
        {
            typedef typename VectorUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        /**
         * \brief Returns the element-wise quotient of the vector expressions \a e1 and \a e2.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The numerator vector expression.
         * \param e2 The denominator vector expression.
         * \return An expression-template node representing the element-wise quotient \f$ e_1 / e_2 \f$.
         */
        template <typename E1, typename E2>
        typename VectorBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemDiv(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorBinary1Traits<E1, E2,
                                                 ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the element-wise product (Hadamard product) of the vector expressions \a e1 and \a e2.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return An expression-template node representing the element-wise product \f$ e_1 \odot e_2 \f$.
         */
        template <typename E1, typename E2>
        typename VectorBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorBinary1Traits<E1, E2,
                                                 ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the 3-vector cross product \f$ e_1 \times e_2 \f$ as an expression-template node.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first 3-vector expression.
         * \param e2 The second 3-vector expression.
         * \return An expression-template node representing the cross product.
         */
        template <typename E1, typename E2>
        typename VectorBinary2Traits<E1, E2, VectorCrossProduct<E1, E2> >::ResultType
        crossProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorBinary2Traits<E1, E2,
                                                 VectorCrossProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        /**
         * \brief Returns the inner (dot) product of the vector expressions \a e1 and \a e2.
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \return \f$ \sum_i e_1(i) \cdot e_2(i) \f$.
         */
        template <typename E1, typename E2>
        typename VectorInnerProduct<E1, E2>::ResultType
        innerProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            return VectorInnerProduct<E1, E2>::apply(e1, e2);
        }

        /**
         * \brief Returns the cosine of the angle between the vector expressions \a e1 and \a e2 (optionally clamped to <tt>[-1, 1]</tt>).
         * \tparam E1 The first vector expression type.
         * \tparam E2 The second vector expression type.
         * \tparam T The norm-product scalar type.
         * \param e1 The first vector expression.
         * \param e2 The second vector expression.
         * \param sd The precomputed product \f$ \|e_1\| \cdot \|e_2\| \f$ of the two vector magnitudes.
         * \param clamp If \c true (default), the result is clamped to the range <tt>[-1, 1]</tt>.
         * \return The (optionally clamped) cosine of the angle.
         */
        template <typename E1, typename E2, typename T>
        typename VectorAngleCosine<E1, E2, T>::ResultType
        angleCos(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, const T& sd, bool clamp = true)
        {
            return VectorAngleCosine<E1, E2, T>::apply(e1, e2, sd, clamp);
        }

        /**
         * \brief Returns the sum of all elements of the vector expression \a e.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return \f$ \sum_i e(i) \f$.
         */
        template <typename E>
        typename VectorElementSum<E>::ResultType
        sum(const VectorExpression<E>& e)
        {
            return VectorElementSum<E>::apply(e);
        }

        /**
         * \brief Returns the L1 norm of the vector expression \a e (\f$ \sum_i |e(i)| \f$).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return The L1 norm.
         */
        template <typename E>
        typename VectorNorm1<E>::ResultType
        norm1(const VectorExpression<E>& e)
        {
            return VectorNorm1<E>::apply(e);
        }

        /**
         * \brief Returns the L2 (Euclidean) norm of the vector expression \a e (\f$ \sqrt{\sum_i |e(i)|^2} \f$).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return The L2 norm.
         */
        template <typename E>
        typename VectorNorm2<E>::ResultType
        norm2(const VectorExpression<E>& e)
        {
            return VectorNorm2<E>::apply(e);
        }

        /**
         * \brief Returns the L&infin; norm of the vector expression \a e (\f$ \max_i |e(i)| \f$).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return The L&infin; norm.
         */
        template <typename E>
        typename VectorNormInfinity<E>::ResultType
        normInf(const VectorExpression<E>& e)
        {
            return VectorNormInfinity<E>::apply(e);
        }

        /**
         * \brief Returns the (first) index at which the vector expression \a e attains its L&infin; norm.
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return The zero-based index of the element with the maximum absolute value.
         */
        template <typename E>
        typename VectorNormInfinityIndex<E>::ResultType
        normInfIndex(const VectorExpression<E>& e)
        {
            return VectorNormInfinityIndex<E>::apply(e);
        }

        /**
         * \brief Returns the length (L2 norm) of the vector expression \a e (alias of norm2()).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return The vector length.
         */
        template <typename E>
        typename VectorNorm2<E>::ResultType
        length(const VectorExpression<E>& e)
        {
            return norm2(e);
        }

        /**
         * \brief Returns the transpose of the vector expression \a e (the identity for vectors — provided for matrix-API symmetry).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A \c const reference to \a e.
         */
        template <typename E>
        const E&
        trans(const VectorExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Returns the transpose of the mutable vector expression \a e (the identity for vectors — provided for matrix-API symmetry).
         * \tparam E The vector expression type.
         * \param e The vector expression.
         * \return A reference to \a e.
         */
        template <typename E>
        E&
        trans(VectorExpression<E>& e)
        {
            return e();
        }

        /**
         * \brief Rotates the vector expression \a e2 by the quaternion expression \a e1.
         * \tparam E1 The quaternion expression type.
         * \tparam E2 The vector expression type.
         * \param e1 The unit quaternion expression encoding the rotation.
         * \param e2 The vector expression to rotate.
         * \return An expression-template node representing the rotated 3-vector \f$ e_1 \cdot e_2 \cdot e_1^{-1} \f$.
         */
        template <typename E1, typename E2>
        typename QuaternionVectorBinaryTraits<E1, E2, QuaternionVectorRotation<E1, E2> >::ResultType
        rotate(const QuaternionExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename QuaternionVectorBinaryTraits<E1, E2, QuaternionVectorRotation<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTOREXPRESSION_HPP
