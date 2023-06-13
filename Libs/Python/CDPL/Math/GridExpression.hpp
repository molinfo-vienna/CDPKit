/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GridExpression.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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


#ifndef CDPL_PYTHON_MATH_GRIDEXPRESSION_HPP
#define CDPL_PYTHON_MATH_GRIDEXPRESSION_HPP

#include <cstddef>
#include <memory>

#include "CDPL/Math/Grid.hpp"
#include "CDPL/Math/GridExpression.hpp"
#include "CDPL/Math/GridAssignment.hpp"


namespace CDPLPythonMath
{

	template <typename T>
	class ConstGridExpression : public CDPL::Math::GridExpression<ConstGridExpression<T> >
	{

	public:
		typedef ConstGridExpression SelfType;
		typedef T ValueType;
		typedef const T Reference;
		typedef const T ConstReference;
		typedef typename std::size_t SizeType;
		typedef typename std::ptrdiff_t DifferenceType;
		typedef const SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Grid<ValueType> GridTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;

		virtual ~ConstGridExpression() {} 

		virtual ConstReference operator()(SizeType i, SizeType j, SizeType k) const = 0;

		virtual SizeType getSize1() const = 0;
		virtual SizeType getSize2() const = 0;
		virtual SizeType getSize3() const = 0;

		virtual bool isEmpty() const {
			return (getSize1() == 0 || getSize2() == 0 || getSize3() == 0);
		}

	protected:
		ConstGridExpression() {} 
	};

	template <typename T>
	class GridExpression : 
		public ConstGridExpression<T>, public CDPL::Math::GridContainer<GridExpression<T> >
	{

	public:
		typedef GridExpression SelfType;
		typedef ConstGridExpression<T> ConstExpressionType;
		typedef T ValueType;
		typedef T& Reference;
		typedef const T ConstReference;
		typedef typename ConstExpressionType::SizeType SizeType;
		typedef typename ConstExpressionType::DifferenceType DifferenceType;
		typedef SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Grid<ValueType> GridTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;
		typedef typename ConstExpressionType::SharedPointer ConstExpressionPointer;

		virtual ~GridExpression() {} 

		virtual Reference operator()(SizeType i, SizeType j, SizeType k) = 0;

		virtual GridExpression& operator=(const ConstExpressionType& e) = 0;

		virtual GridExpression& operator+=(const ConstExpressionType& e) = 0;
		virtual GridExpression& operator-=(const ConstExpressionType& e) = 0;

		virtual GridExpression& operator*=(const ValueType& t) = 0;
		virtual GridExpression& operator/=(const ValueType& t) = 0;

		void swap(GridExpression& e) {
			CDPL::Math::gridSwap<GridExpression, GridExpression>(*this, e);
		}

		GridExpression& operator=(const GridExpression& e) {
			return operator=(static_cast<const ConstExpressionType&>(e));
		}

		template <typename T1>
		GridExpression& operator=(ConstGridExpression<T1>& e) {
			using namespace CDPL;
			using namespace Math;

			gridAssignGrid<ScalarAssignment>(*this, e);
			return *this;
		}

		template <typename E>
		GridExpression& operator=(const CDPL::Math::GridExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			GridTemporaryType tmp(e);
			gridAssignGrid<ScalarAssignment>(*this, tmp);

			return *this;
		}

		template <typename E>
		GridExpression& assign(const CDPL::Math::GridExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			gridAssignGrid<ScalarAssignment>(*this, e);
			return *this;
		}

		template <typename E>
		GridExpression& operator+=(const CDPL::Math::GridExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			GridTemporaryType tmp(static_cast<const Math::GridExpression<ConstExpressionType>&>(*this) + e);
			gridAssignGrid<ScalarAssignment>(*this, tmp);

			return *this;
		}

		template <typename E>
		GridExpression& operator-=(const CDPL::Math::GridExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			GridTemporaryType tmp(static_cast<const Math::GridExpression<ConstExpressionType>&>(*this) - e);
			gridAssignGrid<ScalarAssignment>(*this, tmp);

			return *this;
		}

	protected:
		GridExpression() {} 
	};
}

#endif // CDPL_PYTHON_MATH_GRIDEXPRESSION_HPP
