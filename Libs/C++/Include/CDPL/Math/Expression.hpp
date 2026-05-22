/* 
 * Expression.hpp 
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
 * \brief Definition of basic expression types.
 */

#ifndef CDPL_MATH_EXPRESSION_HPP
#define CDPL_MATH_EXPRESSION_HPP


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief CRTP base for all numeric expression types in the Math namespace (Barton-Nackman idiom).
         * \tparam E The derived expression type.
         */
        template <typename E>
        class Expression
        {

          public:
            typedef E ExpressionType;

          protected:
            Expression(){};
            ~Expression(){};

          private:
            const Expression& operator=(const Expression&);
        };

        /**
         * \brief CRTP base for all vector expression types. Provides downcast access to the concrete derived expression.
         * \tparam E The derived vector expression type.
         */
        template <typename E>
        class VectorExpression : public Expression<E>
        {

          public:
            typedef E ExpressionType;

            const ExpressionType& operator()() const
            {
                return *static_cast<const ExpressionType*>(this);
            }

            ExpressionType& operator()()
            {
                return *static_cast<ExpressionType*>(this);
            }

          protected:
            VectorExpression(){};
            ~VectorExpression(){};
        };

        /**
         * \brief CRTP base for all matrix expression types. Provides downcast access to the concrete derived expression.
         * \tparam E The derived matrix expression type.
         */
        template <typename E>
        class MatrixExpression : public Expression<E>
        {

          public:
            typedef E ExpressionType;

            const ExpressionType& operator()() const
            {
                return *static_cast<const ExpressionType*>(this);
            }

            ExpressionType& operator()()
            {
                return *static_cast<ExpressionType*>(this);
            }

          protected:
            MatrixExpression(){};
            ~MatrixExpression(){};
        };

        /**
         * \brief CRTP base for all quaternion expression types. Provides downcast access to the concrete derived expression.
         * \tparam E The derived quaternion expression type.
         */
        template <typename E>
        class QuaternionExpression : public Expression<E>
        {

          public:
            typedef E ExpressionType;

            const ExpressionType& operator()() const
            {
                return *static_cast<const ExpressionType*>(this);
            }

            ExpressionType& operator()()
            {
                return *static_cast<ExpressionType*>(this);
            }

          protected:
            QuaternionExpression(){};
            ~QuaternionExpression(){};
        };

        /**
         * \brief CRTP base for all grid expression types. Provides downcast access to the concrete derived expression.
         * \tparam E The derived grid expression type.
         */
        template <typename E>
        class GridExpression : public Expression<E>
        {

          public:
            typedef E ExpressionType;

            const ExpressionType& operator()() const
            {
                return *static_cast<const ExpressionType*>(this);
            }

            ExpressionType& operator()()
            {
                return *static_cast<ExpressionType*>(this);
            }

          protected:
            GridExpression(){};
            ~GridExpression(){};
        };

        /**
         * \brief Refinement of Math::VectorExpression marking the derived type as a concrete (writable) vector container.
         * \tparam C The derived vector container type.
         */
        template <typename C>
        class VectorContainer : public VectorExpression<C>
        {

          public:
            typedef C ContainerType;

            const ContainerType& operator()() const
            {
                return *static_cast<const ContainerType*>(this);
            }

            ContainerType& operator()()
            {
                return *static_cast<ContainerType*>(this);
            }

          protected:
            VectorContainer(){};
            ~VectorContainer(){};
        };

        /**
         * \brief Refinement of Math::MatrixExpression marking the derived type as a concrete (writable) matrix container.
         * \tparam C The derived matrix container type.
         */
        template <typename C>
        class MatrixContainer : public MatrixExpression<C>
        {

          public:
            typedef C ContainerType;

            const ContainerType& operator()() const
            {
                return *static_cast<const ContainerType*>(this);
            }

            ContainerType& operator()()
            {
                return *static_cast<ContainerType*>(this);
            }

          protected:
            MatrixContainer(){};
            ~MatrixContainer(){};
        };

        /**
         * \brief Refinement of Math::QuaternionExpression marking the derived type as a concrete (writable) quaternion container.
         * \tparam C The derived quaternion container type.
         */
        template <typename C>
        class QuaternionContainer : public QuaternionExpression<C>
        {

          public:
            typedef C ContainerType;

            const ContainerType& operator()() const
            {
                return *static_cast<const ContainerType*>(this);
            }

            ContainerType& operator()()
            {
                return *static_cast<ContainerType*>(this);
            }

          protected:
            QuaternionContainer(){};
            ~QuaternionContainer(){};
        };

        /**
         * \brief Refinement of Math::GridExpression marking the derived type as a concrete (writable) grid container.
         * \tparam C The derived grid container type.
         */
        template <typename C>
        class GridContainer : public GridExpression<C>
        {

          public:
            typedef C ContainerType;

            const ContainerType& operator()() const
            {
                return *static_cast<const ContainerType*>(this);
            }

            ContainerType& operator()()
            {
                return *static_cast<ContainerType*>(this);
            }

          protected:
            GridContainer(){};
            ~GridContainer(){};
        };
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_EXPRESSION_HPP
