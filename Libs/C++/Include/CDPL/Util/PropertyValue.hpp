/* 
 * PropertyValue.hpp 
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
 * \brief Definition of class CDPL::Util::PropertyValue.
 */

#ifndef CDPL_UTIL_PROPERTYVALUE_HPP
#define CDPL_UTIL_PROPERTYVALUE_HPP

#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief An unary functor that retrieves the value of a given property from the
         *        Base::PropertyContainer instance provided as argument.
         * \tparam T The type of the property value.
         */
        template <typename T>
        class PropertyValue
        {

          public:
            /**
             * \brief Constructs a \c %PropertyValue instance for the property specified by \a key.
             * \param key The key of the property.
             */
            PropertyValue(const Base::LookupKey& key):
                propKey(key) {}

            /**
             * \brief Retrievs the value of the property specified in the constructor from the
             *        Base::PropertyContainer instance \a cntnr.
             * \param cntnr The Base::PropertyContainer instance storing the property value.
             * \return The value of the property.
             */
            const T& operator()(const Base::PropertyContainer& cntnr) const
            {
                return cntnr.getProperty<T>(propKey);
            }

          private:
            Base::LookupKey propKey;
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_PROPERTYVALUE_HPP
