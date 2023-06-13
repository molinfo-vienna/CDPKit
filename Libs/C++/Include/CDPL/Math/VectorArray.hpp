/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorArray.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Math::VectorArray.
 */

#ifndef CDPL_MATH_VECTORARRAY_HPP
#define CDPL_MATH_VECTORARRAY_HPP

#include <memory>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

	namespace Math
	{

		/**
		 * \brief An array for storing generic vector objects.
		 */
		template <typename V>
		class VectorArray : public Util::Array<V> 
		{

		public:
			typedef V ValueType;

			/**
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %VectorArray instances.
			 */
			typedef std::shared_ptr<VectorArray> SharedPointer;

		private:
			const char* getClassName() const {
				return "VectorArray";
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
	}
}

#endif // CDPL_MATH_VECTORARRAY_HPP
