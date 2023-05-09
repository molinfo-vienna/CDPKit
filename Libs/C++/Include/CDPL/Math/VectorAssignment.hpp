/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorAssignment.hpp 
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
 * \brief Implementation of vector assignment routines.
 */

#ifndef CDPL_MATH_VECTORASSIGNMENT_HPP
#define CDPL_MATH_VECTORASSIGNMENT_HPP

#include <boost/swap.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E> class VectorExpression;

		template <template <typename T1, typename T2> class F, typename V, typename E>
		void vectorAssignVector(V& v, const VectorExpression<E>& e)
		{
			typedef typename CommonType<typename V::SizeType, typename E::SizeType>::Type SizeType;

			SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(v.getSize()), SizeType(e().getSize()), Base::SizeError);

			typedef F<typename V::Reference, typename E::ValueType> FunctorType;

			for (SizeType i = 0; i < size; i++)
				FunctorType::apply(v(i), e()(i));
		}

		template <template <typename T1, typename T2> class F, typename V, typename T>
		void vectorAssignScalar(V& v, const T& t)
		{
			typedef F<typename V::Reference, T> FunctorType;
			typedef typename V::SizeType SizeType;

			SizeType size = v.getSize();

			for (SizeType i = 0; i < size; i++)
				FunctorType::apply(v(i), t);
		}
	
		template <typename V, typename E>
		void vectorSwap(V& v, VectorExpression<E>& e)
		{
			typedef typename CommonType<typename V::SizeType, typename E::SizeType>::Type SizeType;

			SizeType size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(v.getSize()), SizeType(e().getSize()), Base::SizeError);

			for (SizeType i = 0; i < size; i++)
				boost::swap(v(i), e()(i));
		}
	}
}

#endif // CDPL_MATH_VECTORASSIGNMENT_HPP
