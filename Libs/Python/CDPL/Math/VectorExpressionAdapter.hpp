/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorExpressionAdapter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_MATH_VECTOREXPRESSIONADAPTER_HPP
#define CDPL_PYTHON_MATH_VECTOREXPRESSIONADAPTER_HPP

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include "VectorExpression.hpp"


namespace CDPLPythonMath
{

	template <typename EDT, typename WDT>
	class ConstVectorExpressionAdapter : 
		public ConstVectorExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef ConstVectorExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::SizeType SizeType;
		typedef typename ExpressionType::SharedPointer ConstExpressionPointer;

		ConstVectorExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~ConstVectorExpressionAdapter() {} 

		ConstReference operator[](SizeType i) const {
			return boost::unwrap_ref(exprData)[i];
		}

		ConstReference operator()(SizeType i) const {
			return boost::unwrap_ref(exprData)(i);
		}

		SizeType getSize() const {
			return boost::unwrap_ref(exprData).getSize();
		}

	protected:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};

	template <typename EDT, typename WDT>
	class VectorExpressionAdapter : public VectorExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef VectorExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstExpressionType ConstExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::Reference Reference;
		typedef typename ExpressionType::SizeType SizeType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		VectorExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~VectorExpressionAdapter() {} 

		ConstReference operator[](SizeType i) const {
			return boost::unwrap_ref(exprData)[i];
		}

		ConstReference operator()(SizeType i) const {
			return boost::unwrap_ref(exprData)(i);
		}

		Reference operator[](SizeType i) {
			return boost::unwrap_ref(exprData)[i];
		}

		Reference operator()(SizeType i) {
			return boost::unwrap_ref(exprData)(i);
		}

		SizeType getSize() const {
			return boost::unwrap_ref(exprData).getSize();
		}

		VectorExpressionAdapter& operator=(const ConstExpressionType& e) {
			if (this == &e)
				return *this;

			boost::unwrap_ref(exprData) = e;
			return *this;
		}

		VectorExpressionAdapter& operator+=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) += e;
			return *this;
		}
		
		VectorExpressionAdapter& operator-=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) -= e;
			return *this;
		}
		
		VectorExpressionAdapter& operator*=(const ValueType& t) {
			boost::unwrap_ref(exprData) *= t;
			return *this;
		}
		
		VectorExpressionAdapter& operator/=(const ValueType& t) {
			boost::unwrap_ref(exprData) /= t;
			return *this;
		}

		void swap(ExpressionType& e) {
			CDPL::Math::vectorSwap<typename boost::unwrap_reference<EDT>::type, 
				ExpressionType>(boost::unwrap_ref(exprData), e);
		}

	protected:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};

	template <typename EDT, typename WDT>
	inline
	typename ConstVectorExpressionAdapter<EDT, WDT>::ConstExpressionPointer 
	makeConstVectorExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename ConstVectorExpressionAdapter<EDT, WDT>::ConstExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new ConstVectorExpressionAdapter<EDT, WDT>(e, ward));
	}

	template <typename EDT, typename WDT>
	inline
	typename VectorExpressionAdapter<EDT, WDT>::ExpressionPointer 
	makeVectorExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename VectorExpressionAdapter<EDT, WDT>::ExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new VectorExpressionAdapter<EDT, WDT>(e, ward));
	}
}

#endif // CDPL_PYTHON_MATH_VECTOREXPRESSIONADAPTER_HPP
