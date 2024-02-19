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
