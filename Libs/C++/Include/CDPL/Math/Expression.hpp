/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Expression.hpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/Config.hpp"


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
			CDPL_MATH_INLINE Expression() {};
			CDPL_MATH_INLINE ~Expression() {};
		
		private:
			const Expression& operator=(const Expression&);
		};

		template <typename E>
		class VectorExpression : public Expression<E>
		{

		public:
			typedef E ExpressionType;

			CDPL_MATH_INLINE const ExpressionType& operator()() const {
				return *static_cast<const ExpressionType*>(this);
			}

			CDPL_MATH_INLINE ExpressionType& operator()() {
				return *static_cast<ExpressionType*>(this);
			}

		protected:
			CDPL_MATH_INLINE VectorExpression() {};
			CDPL_MATH_INLINE ~VectorExpression() {};
		};

		template <typename E>
		class MatrixExpression : public Expression<E>
		{

		public:
			typedef E ExpressionType;

			CDPL_MATH_INLINE const ExpressionType& operator()() const {
				return *static_cast<const ExpressionType*>(this);
			}

			CDPL_MATH_INLINE ExpressionType& operator()() {
				return *static_cast<ExpressionType*>(this);
			}

		protected:
			CDPL_MATH_INLINE MatrixExpression() {};
			CDPL_MATH_INLINE ~MatrixExpression() {};
		};

		template <typename E>
		class QuaternionExpression : public Expression<E>
		{

		public:
			typedef E ExpressionType;

			CDPL_MATH_INLINE const ExpressionType& operator()() const {
				return *static_cast<const ExpressionType*>(this);
			}

			CDPL_MATH_INLINE ExpressionType& operator()() {
				return *static_cast<ExpressionType*>(this);
			}

		protected:
			CDPL_MATH_INLINE QuaternionExpression() {};
			CDPL_MATH_INLINE ~QuaternionExpression() {};
		};

		template <typename C> 
		class VectorContainer : public VectorExpression<C>
		{

		public:
			typedef C ContainerType;

			CDPL_MATH_INLINE const ContainerType& operator()() const {
				return *static_cast<const ContainerType*>(this);
			}

			CDPL_MATH_INLINE ContainerType& operator()() {
				return *static_cast<ContainerType*>(this);
			}

		protected:
			CDPL_MATH_INLINE VectorContainer() {};
			CDPL_MATH_INLINE ~VectorContainer() {};
		};
	
		template <typename C> 
		class MatrixContainer : public MatrixExpression<C>
		{

		public:
			typedef C ContainerType;

			CDPL_MATH_INLINE const ContainerType& operator()() const {
				return *static_cast<const ContainerType*>(this);
			}

			CDPL_MATH_INLINE ContainerType& operator()() {
				return *static_cast<ContainerType*>(this);
			}

		protected:
			CDPL_MATH_INLINE MatrixContainer() {};
			CDPL_MATH_INLINE ~MatrixContainer() {};
		};
	
		template <typename C> 
		class QuaternionContainer : public QuaternionExpression<C>
		{

		public:
			typedef C ContainerType;

			CDPL_MATH_INLINE const ContainerType& operator()() const {
				return *static_cast<const ContainerType*>(this);
			}

			CDPL_MATH_INLINE ContainerType& operator()() {
				return *static_cast<ContainerType*>(this);
			}

		protected:
			CDPL_MATH_INLINE QuaternionContainer() {};
			CDPL_MATH_INLINE ~QuaternionContainer() {};
		};
	}
}

#endif // CDPL_MATH_EXPRESSION_HPP
