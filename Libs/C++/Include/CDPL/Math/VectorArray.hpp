/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorArray.hpp 
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
 * \brief Definition of the class CDPL::Math::VectorArray.
 */

#ifndef CDPL_MATH_VECTORARRAY_HPP
#define CDPL_MATH_VECTORARRAY_HPP

#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

	namespace Math
	{

		/**
		 * \addtogroup CDPL_MATH_MISCELLANEOUS
		 * @{
		 */
		
		/**
		 * \brief An array for storing generic vector objects.
		 */
		template <typename V>
		class VectorArray : public Util::Array<V> 
		{

		public:
			typedef VectorContainer<V> ValueType;

			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %VectorArray instances.
			 */
			typedef boost::shared_ptr<VectorArray> SharedPointer;

		private:
			CDPL_MATH_INLINE const char* getClassName() const {
				return "VectorArray<T>";
			}
		};

		/**
		 * \brief A partial Math::VectorArray template specialization for storing Math::CVector objects.
		 */
		template <typename T, std::size_t Dim>
		class VectorArray<CVector<T, Dim> > : public Util::Array<CVector<T, Dim> >
		{

		public:
			typedef CVector<T, Dim> ValueType;

			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %VectorArray instances.
			 */
			typedef boost::shared_ptr<VectorArray> SharedPointer;

			/**
			 * \brief Transforms each \f$ N \f$-dimenional vector in the array with the \f$ N \f$-dimensional square matrix \a xform.
			 * \param xform The transformation matrix.
			 */
			template <typename T1>
			void transform(const CMatrix<T1, Dim, Dim>& xform);

			/**
			 * \brief Transforms each \f$ N \f$-dimenional vector in the array with the \f$ N+1 \f$-dimensional square matrix \a xform.
			 * \param xform The transformation matrix.
			 * \note The missing vector element is taken to be \c 1.0.
			 */
			template <typename T1>
			void transform(const CMatrix<T1, Dim + 1, Dim + 1>& xform);

		private:
			CDPL_MATH_INLINE const char* getClassName() const {
				return "CVectorArray";
			}
		};

		/**
		 * \brief An array of Math::Vector2F objects.
		 */
		typedef VectorArray<Vector2F> Vector2FArray;

		/**
		 * \brief An array of Math::Vector3F objects.
		 */
		typedef VectorArray<Vector3F> Vector3FArray;

		/**
		 * \brief An array of Math::Vector2D objects.
		 */
		typedef VectorArray<Vector2D> Vector2DArray;

		/**
		 * \brief An array of Math::Vector3D objects.
		 */
		typedef VectorArray<Vector3D> Vector3DArray;

		/**
		 * \brief An array of Math::Vector2L objects.
		 */
		typedef VectorArray<Vector2L> Vector2LArray;

		/**
		 * \brief An array of Math::Vector3L objects.
		 */
		typedef VectorArray<Vector3L> Vector3LArray;

		/**
		 * \brief An array of Math::Vector2UL objects.
		 */
		typedef VectorArray<Vector2UL> Vector2ULArray;

		/**
		 * \brief An array of Math::Vector3UL objects.
		 */
		typedef VectorArray<Vector3UL> Vector3ULArray;


		// Implementation

		template <typename T, std::size_t Dim>
		template <typename T1>
		CDPL_MATH_INLINE
		void VectorArray<CVector<T, Dim> >::transform(const CMatrix<T1, Dim, Dim>& xform)
		{
			for (typename VectorArray::ElementIterator it = this->getElementsBegin(), end = this->getElementsEnd(); it != end; ++it) {
				ValueType& vec = *it;

				vec = prod(xform, vec);  
			}
		}

		template <typename T, std::size_t Dim>
		template <typename T1>
		CDPL_MATH_INLINE
		void VectorArray<CVector<T, Dim> >::transform(const CMatrix<T1, Dim + 1, Dim + 1>& xform)
		{
			CVector<T, Dim + 1> tmp1(1.0);
			CVector<T, Dim + 1> tmp2;

			for (typename VectorArray::ElementIterator it = this->getElementsBegin(), end = this->getElementsEnd(); it != end; ++it) {
				ValueType& vec = *it;
		
				for (std::size_t i = 0; i < Dim; i++)
					tmp1(i) = vec(i);

				prod(xform, tmp1, tmp2);
	
				for (std::size_t i = 0; i < Dim; i++)
					vec(i) = tmp2(i);
			}
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_MATH_VECTORARRAY_HPP
