/* 
 * QuaternionAssignment.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of quaternion assignment routines.
 */

#ifndef CDPL_MATH_QUATERNIONASSIGNMENT_HPP
#define CDPL_MATH_QUATERNIONASSIGNMENT_HPP

#include <utility>


namespace CDPL
{

	namespace Math
	{

		template <typename E> class QuaternionExpression;

		template <template <typename T1, typename T2> class F, typename Q, typename E>
		void quaternionAssignQuaternion(Q& q, const QuaternionExpression<E>& e)
		{
			typedef F<typename Q::Reference, typename E::ValueType> FunctorType;

			FunctorType::apply(q.getC1(), e().getC1());
			FunctorType::apply(q.getC2(), e().getC2());
			FunctorType::apply(q.getC3(), e().getC3());
			FunctorType::apply(q.getC4(), e().getC4());
		}

		template <template <typename T1, typename T2> class F, typename Q, typename T>
		void quaternionAssignScalar(Q& q, const T& t)
		{
			typedef F<typename Q::Reference, T> FunctorType;
		
			FunctorType::apply(q.getC1(), t);
			FunctorType::apply(q.getC2(), t);
			FunctorType::apply(q.getC3(), t);
			FunctorType::apply(q.getC4(), t);
		}

		template <typename Q, typename E>
		void quaternionSwap(Q& q, QuaternionExpression<E>& e)
		{
			std::swap(q.getC1(), e().getC1());
			std::swap(q.getC2(), e().getC2());
			std::swap(q.getC3(), e().getC3());
			std::swap(q.getC4(), e().getC4());
		}
	}
}

#endif // CDPL_MATH_QUATERNIONASSIGNMENT_HPP
