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
#include <cmath>

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
			typedef CVector<T, Dim> VecType;
			typedef CMatrix<T1, Dim, Dim> MtxType;

			typedef typename VectorArray<VecType>::ElementIterator Iterator;
			typedef typename VecType::Pointer VecDataPointer;
			typedef typename MtxType::ConstArrayPointer MtxDataPointer;

			T tmp[Dim];
			MtxDataPointer xform_data = xform.getData();

			for (Iterator it = va.getElementsBegin(), end = va.getElementsEnd(); it != end; ++it) {
				VecDataPointer vec = it->getData();

				for (std::size_t i = 0; i < Dim; i++) {
					tmp[i] = T();
	
					for (std::size_t j = 0; j < Dim; j++) 
						tmp[i] += vec[j] * xform_data[i][j];
				}

				for (std::size_t i = 0; i < Dim; i++) 
					vec[i] = tmp[i];
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
			typedef CVector<T, Dim> VecType;
			typedef CMatrix<T1, Dim + 1, Dim + 1> MtxType;

			typedef typename VectorArray<VecType>::ElementIterator Iterator;
			typedef typename VecType::Pointer VecDataPointer;
			typedef typename MtxType::ConstArrayPointer MtxDataPointer;

			T tmp[Dim];
			MtxDataPointer xform_data = xform.getData();

			for (Iterator it = va.getElementsBegin(), end = va.getElementsEnd(); it != end; ++it) {
				VecDataPointer vec = it->getData();
		
				for (std::size_t i = 0; i < Dim; i++) {
					tmp[i] = T();
	
					for (std::size_t j = 0; j < Dim; j++) 
						tmp[i] += vec[j] * xform_data[i][j];

					tmp[i] += xform_data[i][Dim];
				}

				for (std::size_t i = 0; i < Dim; i++) 
					vec[i] = tmp[i];
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

		template <typename T, std::size_t Dim>
		T calcRMSD(const VectorArray<CVector<T, Dim> >& va1, const VectorArray<CVector<T, Dim> >& va2)
		{
			typedef CVector<T, Dim> VecType;
			typedef typename VectorArray<VecType>::SizeType ArraySizeType;

			ArraySizeType num_elem = std::min(va1.getSize(), va2.getSize());

			if (num_elem == 0)
				return T();

			typedef typename VectorArray<VecType>::ConstElementIterator Iterator;
			typedef typename VecType::ConstPointer VecDataPointer;

			T sd = T();

			for (Iterator it1 = va1.getElementsBegin(), it2 = va2.getElementsBegin(), end = it1 + num_elem; it1 != end; ++it1, ++it2) {
				VecDataPointer vec1 = it1->getData();
				VecDataPointer vec2 = it2->getData();

				for (std::size_t i = 0; i < Dim; i++) {
					T diff = vec1[i] - vec2[i];

					sd += diff * diff;
				}
			}

			return std::sqrt(sd / num_elem); 
		}

		template <typename T, std::size_t Dim, typename T1>
		T calcRMSD(const VectorArray<CVector<T, Dim> >& va1, const VectorArray<CVector<T, Dim> >& va2, const CMatrix<T1, Dim + 1, Dim + 1>& va1_xform)
		{
			typedef CVector<T, Dim> VecType;
			typedef CMatrix<T1, Dim + 1, Dim + 1> MtxType;

			typedef typename VectorArray<VecType>::SizeType ArraySizeType;

			ArraySizeType num_elem = std::min(va1.getSize(), va2.getSize());

			if (num_elem == 0)
				return T();

			typedef typename VectorArray<VecType>::ConstElementIterator Iterator;
			typedef typename VecType::ConstPointer VecDataPointer;
			typedef typename MtxType::ConstArrayPointer MtxDataPointer;

			T sd = T();
			MtxDataPointer xform_data = va1_xform.getData();

			for (Iterator it1 = va1.getElementsBegin(), it2 = va2.getElementsBegin(), end = it1 + num_elem; it1 != end; ++it1, ++it2) {
				VecDataPointer vec1 = it1->getData();
				VecDataPointer vec2 = it2->getData();

				for (std::size_t i = 0; i < Dim; i++) {
					T tmp = T();

					for (std::size_t j = 0; j < Dim; j++) 
						tmp += vec1[j] * xform_data[i][j];

					tmp += xform_data[i][Dim] - vec2[i];
					sd += tmp * tmp;
				}
			}

			return std::sqrt(sd / num_elem); 
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_MATH_VECTORARRAYFUNCTIONS_HPP
