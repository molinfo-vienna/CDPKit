/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SparseContainerElement.hpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of an element proxy for sparse data types.
 */

#ifndef CDPL_MATH_SPARSECONTAINERELEMENT_HPP
#define CDPL_MATH_SPARSECONTAINERELEMENT_HPP

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename C, typename K = typename C::KeyType>
		class SparseContainerElement
		{
				
		public:
			typedef C ContainerType;
			typedef K KeyType;
			typedef typename ContainerType::ValueType ValueType;
			typedef typename ContainerType::SizeType SizeType;
			typedef ValueType& Reference;
			typedef typename ContainerType::ConstReference ConstReference;

			SparseContainerElement(ContainerType& c, KeyType key): cntnr(c), key(key) {}

			// Assignment
			SparseContainerElement& operator=(const SparseContainerElement &p) {
				ref() = p.constRef();
				return *this;
			}

			template <typename D>
			SparseContainerElement& operator=(const D &d) {
				ref() = d;
				return *this;
			}

			template <typename D>
			SparseContainerElement& operator+=(const D &d) {
				ref() += d;
				return *this;
			}

			template <typename D>
			SparseContainerElement& operator-=(const D &d) {
				ref() -= d;
				return *this;
			}

			template <typename D>
			SparseContainerElement& operator*=(const D &d) {
				ref() *= d;
				return *this;
			}

			template <typename D>
			SparseContainerElement& operator/=(const D &d) {
				ref() /= d;
				return *this;
			}

			// Comparison
			template <typename D>
			bool operator==(const D &d) const {
				return (constRef() == d);
			}

			template <typename D>
			bool operator!=(const D &d) const {
				return (constRef() != d);
			}

			operator ConstReference() const {
				return constRef();
			}

			Reference ref() const {
				return cntnr.getData().insert(typename ContainerType::ArrayType::value_type(key, cntnr.getDefaultValue())).first->second;
			}
	
			ConstReference& constRef() const {
				typename ContainerType::ArrayType::const_iterator it = cntnr.getData().find(key);

				if (it == cntnr.getData().end())
					return cntnr.getDefaultValue();

				return it->second;
			}

		private:
			ContainerType& cntnr;
			KeyType        key;
		};

		template <typename C>
		struct TypeTraits<SparseContainerElement<C> > : public TypeTraits<typename SparseContainerElement<C>::ValueType>  {};
	}
}

#endif // CDPL_MATH_SPARSECONTAINERELEMENT_HPP
