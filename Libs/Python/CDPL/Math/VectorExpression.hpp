/* 
 * VectorExpression.hpp 
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


#ifndef CDPL_PYTHON_MATH_VECTOREXPRESSION_HPP
#define CDPL_PYTHON_MATH_VECTOREXPRESSION_HPP

#include <cstddef>
#include <memory>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/VectorAssignment.hpp"


namespace CDPLPythonMath
{

	template <typename T>
	class ConstVectorExpression : public CDPL::Math::VectorExpression<ConstVectorExpression<T> >
	{

	public:
		typedef ConstVectorExpression SelfType;
		typedef T ValueType;
		typedef const T Reference;
		typedef const T ConstReference;
		typedef typename std::size_t SizeType;
		typedef typename std::ptrdiff_t DifferenceType;
		typedef const SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Vector<ValueType> VectorTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;

		virtual ~ConstVectorExpression() {} 

		virtual ConstReference operator[](SizeType i) const = 0;
		virtual ConstReference operator()(SizeType i) const = 0;

		virtual SizeType getSize() const = 0;

		virtual bool isEmpty() const {
			return (getSize() == 0);
		}

	protected:
		ConstVectorExpression() {} 
	};

	template <typename T>
	class VectorExpression : 
		public ConstVectorExpression<T>, public CDPL::Math::VectorContainer<VectorExpression<T> >
	{

	public:
		typedef VectorExpression SelfType;
		typedef ConstVectorExpression<T> ConstExpressionType;
		typedef T ValueType;
		typedef T& Reference;
		typedef const T ConstReference;
		typedef typename ConstExpressionType::SizeType SizeType;
		typedef typename ConstExpressionType::DifferenceType DifferenceType;
		typedef SelfType& ClosureType;
		typedef const SelfType& ConstClosureType;
		typedef CDPL::Math::Vector<ValueType> VectorTemporaryType;
		typedef std::shared_ptr<SelfType> SharedPointer;
		typedef typename ConstExpressionType::SharedPointer ConstExpressionPointer;

		virtual ~VectorExpression() {} 

		virtual Reference operator[](SizeType i) = 0;
		virtual Reference operator()(SizeType i) = 0;

		virtual VectorExpression& operator=(const ConstExpressionType& e) = 0;

		virtual VectorExpression& operator+=(const ConstExpressionType& e) = 0;
		virtual VectorExpression& operator-=(const ConstExpressionType& e) = 0;

		virtual VectorExpression& operator*=(const ValueType& t) = 0;
		virtual VectorExpression& operator/=(const ValueType& t) = 0;

		void swap(VectorExpression& e) {
			CDPL::Math::vectorSwap<VectorExpression, VectorExpression>(*this, e);
		}

		VectorExpression& operator=(const VectorExpression& e) {
			return operator=(static_cast<const ConstExpressionType&>(e));
		}

		template <typename T1>
		VectorExpression& operator=(ConstVectorExpression<T1>& e) {
			using namespace CDPL;
			using namespace Math;

			vectorAssignVector<ScalarAssignment>(*this, e);

			return *this;
		}

		template <typename E>
		VectorExpression& assign(const CDPL::Math::VectorExpression<E>& e) {
			using namespace CDPL;
			using namespace Math;

			vectorAssignVector<ScalarAssignment>(*this, e);
			return *this;
		}

	protected:
		VectorExpression() {} 
	};
}

#endif // CDPL_PYTHON_MATH_VECTOREXPRESSION_HPP
