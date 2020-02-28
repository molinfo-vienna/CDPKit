/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * QuaternionExpressionAdapter.hpp 
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


#ifndef CDPL_PYTHON_MATH_QUATERNIONEXPRESSIONADAPTER_HPP
#define CDPL_PYTHON_MATH_QUATERNIONEXPRESSIONADAPTER_HPP

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include "QuaternionExpression.hpp"


namespace CDPLPythonMath
{

	template <typename EDT, typename WDT>
	class ConstQuaternionExpressionAdapter : 
		public ConstQuaternionExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef ConstQuaternionExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::SharedPointer ConstExpressionPointer;

		ConstQuaternionExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~ConstQuaternionExpressionAdapter() {} 

		ConstReference getC1() const {
			return boost::unwrap_ref(exprData).getC1();
		}

		ConstReference getC2() const {
			return boost::unwrap_ref(exprData).getC2();
		}
	
		ConstReference getC3() const {
			return boost::unwrap_ref(exprData).getC3();
		}
	
		ConstReference getC4() const {
			return boost::unwrap_ref(exprData).getC4();
		}

	protected:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};

	template <typename EDT, typename WDT>
	class QuaternionExpressionAdapter : public QuaternionExpression<typename boost::unwrap_reference<EDT>::type::ValueType>
	{

	public:
		typedef EDT HeldExpressionDataType;
		typedef WDT KeepAliveWardDataType;
		typedef typename boost::unwrap_reference<EDT>::type HeldExpressionType;
		typedef typename HeldExpressionType::ValueType ValueType;
		typedef QuaternionExpression<ValueType> ExpressionType;
		typedef typename ExpressionType::ConstExpressionType ConstExpressionType;
		typedef typename ExpressionType::ConstReference ConstReference;
		typedef typename ExpressionType::Reference Reference;
		typedef typename ExpressionType::SharedPointer ExpressionPointer;
		typedef typename ExpressionType::ConstExpressionPointer ConstExpressionPointer;

		QuaternionExpressionAdapter(const HeldExpressionDataType& expr_data, const KeepAliveWardDataType& alive_ward_data):
			exprData(expr_data), keepAliveWardData(alive_ward_data) {} 
		
		~QuaternionExpressionAdapter() {} 

		ConstReference getC1() const {
			return boost::unwrap_ref(exprData).getC1();
		}

		ConstReference getC2() const {
			return boost::unwrap_ref(exprData).getC2();
		}
	
		ConstReference getC3() const {
			return boost::unwrap_ref(exprData).getC3();
		}
	
		ConstReference getC4() const {
			return boost::unwrap_ref(exprData).getC4();
		}

		Reference getC1() {
			return boost::unwrap_ref(exprData).getC1();
		}

		Reference getC2() {
			return boost::unwrap_ref(exprData).getC2();
		}
	
		Reference getC3() {
			return boost::unwrap_ref(exprData).getC3();
		}
	
		Reference getC4() {
			return boost::unwrap_ref(exprData).getC4();
		}

		void set(const ValueType& c1, const ValueType& c2, const ValueType& c3, const ValueType& c4) {
			boost::unwrap_ref(exprData).set(c1, c2, c3, c4);
		}

		QuaternionExpressionAdapter& operator=(const ConstExpressionType& e) {
			if (this == &e)
				return *this;

			boost::unwrap_ref(exprData) = e;
			return *this;
		}

		QuaternionExpressionAdapter& operator+=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) += e;
			return *this;
		}
		
		QuaternionExpressionAdapter& operator-=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) -= e;
			return *this;
		}

		QuaternionExpressionAdapter& operator*=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) *= e;
			return *this;
		}
		
		QuaternionExpressionAdapter& operator/=(const ConstExpressionType& e) {
			boost::unwrap_ref(exprData) /= e;
			return *this;
		}
		
		QuaternionExpressionAdapter& operator+=(const ValueType& t) {
			boost::unwrap_ref(exprData) += t;
			return *this;
		}
		
		QuaternionExpressionAdapter& operator-=(const ValueType& t) {
			boost::unwrap_ref(exprData) -= t;
			return *this;
		}

		QuaternionExpressionAdapter& operator*=(const ValueType& t) {
			boost::unwrap_ref(exprData) *= t;
			return *this;
		}
		
		QuaternionExpressionAdapter& operator/=(const ValueType& t) {
			boost::unwrap_ref(exprData) /= t;
			return *this;
		}

	protected:
		HeldExpressionDataType exprData;
		KeepAliveWardDataType  keepAliveWardData;
	};

	template <typename EDT, typename WDT>
	inline
	typename ConstQuaternionExpressionAdapter<EDT, WDT>::ConstExpressionPointer 
	makeConstQuaternionExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename ConstQuaternionExpressionAdapter<EDT, WDT>::ConstExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new ConstQuaternionExpressionAdapter<EDT, WDT>(e, ward));
	}

	template <typename EDT, typename WDT>
	inline
	typename QuaternionExpressionAdapter<EDT, WDT>::ExpressionPointer 
	makeQuaternionExpressionAdapter(const EDT& e, const WDT& ward)
	{
		typedef typename QuaternionExpressionAdapter<EDT, WDT>::ExpressionPointer ExpressionPointerType;

		return ExpressionPointerType(new QuaternionExpressionAdapter<EDT, WDT>(e, ward));
	}
}

#endif // CDPL_PYTHON_MATH_QUATERNIONEXPRESSIONADAPTER_HPP
