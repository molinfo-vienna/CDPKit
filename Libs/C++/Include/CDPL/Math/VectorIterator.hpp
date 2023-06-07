/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * VectorIterator.hpp 
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
 * \brief Definition of vector element iterator traits and functions.
 */

#ifndef CDPL_MATH_VECTORITERATOR_HPP
#define CDPL_MATH_VECTORITERATOR_HPP

#include <functional>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E>
		class VectorElementAccessor
		{

			typedef E VectorType;
			typedef typename E::SizeType SizeType;
			typedef typename E::Reference Reference;

		public:
			VectorElementAccessor(VectorType& e): vec(e) {}

			Reference operator()(SizeType i) const {
				return vec.get()(i);
			}

			bool operator==(const VectorElementAccessor& accessor) const {
				return (&vec.get() == &accessor.vec.get());
			}

		private:
			std::reference_wrapper<VectorType> vec;
		};

		template <typename E>
		class VectorElementAccessor<const E>
		{

			typedef E VectorType;
			typedef typename E::SizeType SizeType;
			typedef typename E::ConstReference Reference;

		public:
			VectorElementAccessor(const VectorElementAccessor<E>& accessor): vec(accessor.vec) {}

			VectorElementAccessor(const VectorType& e): vec(e) {}

			Reference operator()(SizeType i) const {
				return vec.get()(i);
			}

			bool operator==(const VectorElementAccessor& accessor) const {
				return (&vec.get() == &accessor.vec.get());
			}

			VectorElementAccessor& operator=(const VectorElementAccessor<E>& accessor) {
				vec = std::reference_wrapper<const VectorType>(accessor.vec);
				return *this;
			}

		private:
			std::reference_wrapper<const VectorType> vec;
		};
	
		template <typename E>
		struct VectorIteratorTraits
		{

			typedef E VectorType;
			typedef typename E::SizeType SizeType;
			typedef typename E::ValueType ValueType;
			typedef VectorElementAccessor<E> AccessorType;
			typedef Util::IndexedElementIterator<ValueType, AccessorType, SizeType> IteratorType;

			static IteratorType makeIterator(VectorType& e, SizeType idx) {
				return IteratorType(AccessorType(e), idx);
			}
		};

		template <typename E>
		struct VectorIteratorTraits<const E>
		{

			typedef E VectorType;
			typedef typename E::SizeType SizeType;
			typedef typename E::ValueType ValueType;
			typedef VectorElementAccessor<const E> AccessorType;
			typedef Util::IndexedElementIterator<const ValueType, AccessorType, SizeType> IteratorType;

			static IteratorType makeIterator(const VectorType& e, SizeType idx) {
				return IteratorType(AccessorType(e), idx);
			}
		};

		template <typename E>
		typename VectorIteratorTraits<E>::IteratorType vectorBegin(VectorExpression<E>& e)
		{
            return VectorIteratorTraits<E>::makeIterator(e(), 0);
		}
		
		template <typename E>
		typename VectorIteratorTraits<E>::IteratorType vectorEnd(VectorExpression<E>& e)
		{
            return VectorIteratorTraits<E>::makeIterator(e(), e().getSize());
		}

		template <typename E>
		typename VectorIteratorTraits<const E>::IteratorType vectorBegin(const VectorExpression<E>& e)
		{
            return VectorIteratorTraits<const E>::makeIterator(e(), 0);
		}
		
		template <typename E>
		typename VectorIteratorTraits<const E>::IteratorType vectorEnd(const VectorExpression<E>& e)
		{
            return VectorIteratorTraits<const E>::makeIterator(e(), e().getSize());
		}
	}
}

#endif // CDPL_MATH_VECTORITERATOR_HPP
