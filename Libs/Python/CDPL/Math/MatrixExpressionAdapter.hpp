/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixExpressionAdapter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_MATH_MATRIXEXPRESSIONADAPTER_HPP
#define CDPL_PYTHON_MATH_MATRIXEXPRESSIONADAPTER_HPP

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include "MatrixExpression.hpp"


namespace CDPLPythonMath
{

	template <typename EDT, typename WDT>
	class ConstMatrixExpressionAdapter : 
		public ConstMatrixExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef ConstMatrixExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::SizeType SizeType;
		typedef typename ExpressionType::SharedPointer ConstExpressionPointer;

		ConstMatrixExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~ConstMatrixExpressionAdapter() {} 

		ConstReference operator()(SizeType i, SizeType j) const {
			return boost::unwrap_ref(exprData)(i, j);
		}

		SizeType getSize1() const {
			return boost::unwrap_ref(exprData).getSize1();
		}

		SizeType getSize2() const {
			return boost::unwrap_ref(exprData).getSize2();
		}

	private:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};

	template <typename EDT, typename WDT>
	class MatrixExpressionAdapter : public MatrixExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef MatrixExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstExpressionType ConstExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::Reference Reference;
		typedef typename ExpressionType::SizeType SizeType;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		MatrixExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~MatrixExpressionAdapter() {} 
	
		ConstReference operator()(SizeType i, SizeType j) const {
			return boost::unwrap_ref(exprData)(i, j);
		}

		Reference operator()(SizeType i, SizeType j) {
			return boost::unwrap_ref(exprData)(i, j);
		}

		SizeType getSize1() const {
			return boost::unwrap_ref(exprData).getSize1();
		}

		SizeType getSize2() const {
			return boost::unwrap_ref(exprData).getSize2();
		}

		MatrixExpressionAdapter& operator=(const ConstExpressionType& e) {
			if (this == &e)
				return *this;

			boost::unwrap_ref(exprData) = e;
			return *this;
		}

		MatrixExpressionAdapter& operator+=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) += e;
			return *this;
		}
		
		MatrixExpressionAdapter& operator-=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) -= e;
			return *this;
		}
		
		MatrixExpressionAdapter& operator*=(const ValueType& t) {
			boost::unwrap_ref(exprData) *= t;
			return *this;
		}
		
		MatrixExpressionAdapter& operator/=(const ValueType& t) {
			boost::unwrap_ref(exprData) /= t;
			return *this;
		}

	private:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};


	template <typename EDT, typename WDT>
	inline
	typename ConstMatrixExpressionAdapter<EDT, WDT>::ConstExpressionPointer 
	makeConstMatrixExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename ConstMatrixExpressionAdapter<EDT, WDT>::ConstExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new ConstMatrixExpressionAdapter<EDT, WDT>(e, ward));
	}

	template <typename EDT, typename WDT>
	inline
	typename MatrixExpressionAdapter<EDT, WDT>::ExpressionPointer 
	makeMatrixExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename MatrixExpressionAdapter<EDT, WDT>::ExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new MatrixExpressionAdapter<EDT, WDT>(e, ward));
	}
}

#endif // CDPL_PYTHON_MATH_MATRIXEXPRESSIONADAPTER_HPP
