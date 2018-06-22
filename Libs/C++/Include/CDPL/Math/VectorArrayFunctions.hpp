/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorArrayFunctions.hpp 
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

/**
 * \file
 * \brief Definition of utility functions operating on CDPL::Math::VectorArray instances.
 */

#ifndef CDPL_MATH_VECTORARRAYFUNCTIONS_HPP
#define CDPL_MATH_VECTORARRAYFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

	namespace Math
	{

		/**
		 * \addtogroup CDPL_MATH_FUNCTIONS
		 * @{
		 */
		
		/**
		 * \brief Transforms each \f$ N \f$-dimensional vector in the array with the \f$ N \f$-dimensional square matrix \a xform.
		 * \param va The vectors to transform.
		 * \param xform The transformation matrix.
		 */
		template <typename T, std::size_t Dim, typename T1>
		void transform(VectorArray<CVector<T, Dim> >& va, const CMatrix<T1, Dim, Dim>& xform) 
		{
			typedef typename VectorArray<CVector<T, Dim> >::ElementIterator Iterator;
			typedef typename VectorArray<CVector<T, Dim> >::ValueType ValueType;

			for (Iterator it = va.getElementsBegin(), end = va.getElementsEnd(); it != end; ++it) {
				ValueType& vec = *it;

				vec = prod(xform, vec);  
			}
		}

		/**
		 * \brief Transforms each \f$ N \f$-dimensional vector in the array with the \f$ N+1 \f$-dimensional square matrix \a xform.
		 * \param va The vectors to transform.
		 * \param xform The transformation matrix.
		 * \note The missing vector element is taken to be \c 1.0.
		 */
		template <typename T, std::size_t Dim, typename T1>
		void transform(VectorArray<CVector<T, Dim> >& va, const CMatrix<T1, Dim + 1, Dim + 1>& xform)
		{
			typedef typename VectorArray<CVector<T, Dim> >::ElementIterator Iterator;
			typedef typename VectorArray<CVector<T, Dim> >::ValueType ValueType;

			CVector<T, Dim + 1> tmp1(1.0);
			CVector<T, Dim + 1> tmp2;

			for (Iterator it = va.getElementsBegin(), end = va.getElementsEnd(); it != end; ++it) {
				ValueType& vec = *it;
		
				for (std::size_t i = 0; i < Dim; i++)
					tmp1(i) = vec(i);

				prod(xform, tmp1, tmp2);
	
				for (std::size_t i = 0; i < Dim; i++)
					vec(i) = tmp2(i);
			}
		}

		/**
		 * \brief Calculates the centroid of the array elements.
		 * \param va The vectors for which to calculate the centroid.
		 * \param ctr Stores the calculated centroid.
		 * \return \c true if the array is not empty, and \c false otherwise.
		 */
		template <typename T, std::size_t Dim, typename T1>
		bool calcCentroid(const VectorArray<CVector<T, Dim> >& va, CVector<T1, Dim>& ctr)
		{
			if (va.isEmpty())
				return false;

			ctr.clear();

			typedef typename VectorArray<CVector<T, Dim> >::ConstElementIterator Iterator;

			for (Iterator it = va.getElementsBegin(), end = va.getElementsEnd(); it != end; ++it) 
				ctr.plusAssign(*it);

			ctr /= va.getSize();

			return true;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_MATH_VECTORARRAYFUNCTIONS_HPP
