/* 
 * MatrixExpression.hpp 
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


#ifndef CDPL_PYTHON_MATH_MATRIXEXPRESSION_HPP
#define CDPL_PYTHON_MATH_MATRIXEXPRESSION_HPP

#include <cstddef>
#include <memory>

#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"


namespace CDPLPythonMath
{

	template <typename T>
	class ConstMatrixExpression : public CDPL::Math::MatrixExpression<ConstMatrixExpression<T> >
	{

	public:
		typedef ConstMatrixExpression SelfType;
		typedef T ValueType;
		typedef const T Reference;
		typedef const T ConstReference;
		typedef typename std::size_t SizeType;
		typedef typename std::ptrdiff_t DifferenceType;
		typedef const SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Matrix<ValueType> MatrixTemporaryType;
		typedef CDPL::Math::Vector<ValueType> VectorTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;

		virtual ~ConstMatrixExpression() {} 

		virtual ConstReference operator()(SizeType i, SizeType j) const = 0;

		virtual SizeType getSize1() const = 0;
		virtual SizeType getSize2() const = 0;

		virtual bool isEmpty() const {
			return (getSize1() == 0 || getSize2() == 0);
		}

	protected:
		ConstMatrixExpression() {} 
	};

	template <typename T>
	class MatrixExpression : 
		public ConstMatrixExpression<T>, public CDPL::Math::MatrixContainer<MatrixExpression<T> >
	{

	public:
		typedef MatrixExpression SelfType;
		typedef ConstMatrixExpression<T> ConstExpressionType;
		typedef T ValueType;
		typedef T& Reference;
		typedef const T ConstReference;
		typedef typename ConstExpressionType::SizeType SizeType;
		typedef typename ConstExpressionType::DifferenceType DifferenceType;
		typedef SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Matrix<ValueType> MatrixTemporaryType;
		typedef CDPL::Math::Vector<ValueType> VectorTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;
		typedef typename ConstExpressionType::SharedPointer ConstExpressionPointer;

		virtual ~MatrixExpression() {} 

		virtual Reference operator()(SizeType i, SizeType j) = 0;

		virtual MatrixExpression& operator=(const ConstExpressionType& e) = 0;

		virtual MatrixExpression& operator+=(const ConstExpressionType& e) = 0;
		virtual MatrixExpression& operator-=(const ConstExpressionType& e) = 0;

		virtual MatrixExpression& operator*=(const ValueType& t) = 0;
		virtual MatrixExpression& operator/=(const ValueType& t) = 0;

		void swap(MatrixExpression& e) {
			CDPL::Math::matrixSwap<MatrixExpression, MatrixExpression>(*this, e);
		}

		MatrixExpression& operator=(const MatrixExpression& e) {
			return operator=(static_cast<const ConstExpressionType&>(e));
		}

		template <typename T1>
		MatrixExpression& operator=(ConstMatrixExpression<T1>& e) {
			using namespace CDPL;
			using namespace Math;

			matrixAssignMatrix<ScalarAssignment>(*this, e);
			return *this;
		}

		template <typename E>
		MatrixExpression& operator=(const CDPL::Math::MatrixExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			MatrixTemporaryType tmp(e);
			matrixAssignMatrix<ScalarAssignment>(*this, tmp);

			return *this;
		}

		template <typename E>
		MatrixExpression& assign(const CDPL::Math::MatrixExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			matrixAssignMatrix<ScalarAssignment>(*this, e);
			return *this;
		}

		template <typename E>
		MatrixExpression& operator+=(const CDPL::Math::MatrixExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			MatrixTemporaryType tmp(static_cast<const Math::MatrixExpression<ConstExpressionType>&>(*this) + e);
			matrixAssignMatrix<ScalarAssignment>(*this, tmp);

			return *this;
		}

		template <typename E>
		MatrixExpression& operator-=(const CDPL::Math::MatrixExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			MatrixTemporaryType tmp(static_cast<const Math::MatrixExpression<ConstExpressionType>&>(*this) - e);
			matrixAssignMatrix<ScalarAssignment>(*this, tmp);

			return *this;
		}

	protected:
		MatrixExpression() {} 
	};
}

#endif // CDPL_PYTHON_MATH_MATRIXEXPRESSION_HPP
