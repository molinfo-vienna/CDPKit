/* 
 * Dereferencer.hpp 
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
 * \brief Definition of classes CDPL::Util::Dereferencer and CDPL::Util::NullCheckDereferencer.
 */

#ifndef CDPL_UTIL_DEREFERENCER_HPP
#define CDPL_UTIL_DEREFERENCER_HPP

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief An unary functor for the dereferenciation of pointers
         *        \e without \e null pointer checking.
         * \tparam ArgType The pointer type.
         * \tparam ResType The type of the pointer dereferenciation result.
         * \note The type resulting from dereferencing \a ArgType must be convertible
         *       to \a ResType. If \a ResType is a not a reference, a copy of the
         *       pointed-to object will be returned. 
         */
        template <typename ArgType, typename ResType>
        struct Dereferencer
        {

          public:
            typedef ResType result_type;

            /**
             * \brief Returns a reference to or copy of the pointed-to argument object.
             * \param ptr A pointer of type \a ArgType to an object.
             * \return A copy of or reference to the object. 
             */
            ResType operator()(const ArgType& ptr) const;
        };

        /**
         * \brief An unary functor for the dereferenciation of pointers
         *        \e with \e null pointer checking.
         * \tparam ArgType The pointer type.
         * \tparam ResType The type of the pointer dereferenciation result.
         * \note The type resulting from dereferencing \a ArgType must be convertible
         *       to \a ResType. If \a ResType is a not a reference, a copy of the
         *       pointed-to object will be returned. 
         */
        template <typename ArgType, typename ResType>
        struct NullCheckDereferencer
        {

          public:
            typedef ResType result_type;

            /**
             * \brief Returns a reference to or copy of the pointed-to argument object.
             * \param ptr A pointer of type \a ArgType to an object.
             * \return A copy of or reference to the object. 
             * \throw Base::NullPointerException if \a ptr is \e null.
             */
            ResType operator()(const ArgType& ptr) const;
        };
    } // namespace Util
} // namespace CDPL


// Implementation

template <typename ArgType, typename ResType>
ResType CDPL::Util::Dereferencer<ArgType, ResType>::operator()(const ArgType& ptr) const
{
    return *ptr;
}

template <typename ArgType, typename ResType>
ResType CDPL::Util::NullCheckDereferencer<ArgType, ResType>::operator()(const ArgType& ptr) const
{
    if (!ptr)
        throw Base::NullPointerException("NullCheckDereferencer: attempt to dereference null pointer");

    return *ptr;
}

#endif // CDPL_UTIL_DEREFERENCER_HPP
