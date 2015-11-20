/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyValueProduct.hpp 
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
 * \brief Definition of the class CDPL::Util::PropertyValueProduct.
 */

#ifndef CDPL_UTIL_PROPERTYVALUEPRODUCT_HPP
#define CDPL_UTIL_PROPERTYVALUEPRODUCT_HPP

#include <functional>

#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL 
{

	namespace Util
	{

		/**
		 * \addtogroup CDPL_UTIL_FUNCTORS
		 * @{
		 */

		/**
		 * \brief A binary functor that calculates the product of two property values retrieved 
		 *        from a pair of Base::PropertyContainer instances passed as argument.
		 * \tparam ResType The result type.
		 * \tparam PropertyValueType The property value type.
		 */
		template <typename ResType, typename PropertyValueType = ResType>
		class PropertyValueProduct : public std::binary_function<Base::PropertyContainer, Base::PropertyContainer, ResType>
		{

		public:
			/**
			 * \brief Constructs a \c %PropertyValueProduct instance for the property specified by \a key.
			 * \param key The key of the property.
			 */
			PropertyValueProduct(const Base::LookupKey& key): propKey(key) {}

			/**
			 * \brief Calculates the product of the property values stored in the Base::PropertyContainer instances
			 *        \a cntnr1 and \a cntnr2.
			 * \param cntnr1 The Base::PropertyContainer instance storing the first property value.
			 * \param cntnr2 The Base::PropertyContainer instance storing the second property value.
			 * \return The product of the property values.
			 */
			ResType operator()(const Base::PropertyContainer& cntnr1, const Base::PropertyContainer& cntnr2) const {
				return (cntnr1.getProperty<PropertyValueType>(propKey) * cntnr2.getProperty<PropertyValueType>(propKey));
			}

		private:
			Base::LookupKey propKey;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_UTIL_PROPERTYVALUEPRODUCT_HPP

 
