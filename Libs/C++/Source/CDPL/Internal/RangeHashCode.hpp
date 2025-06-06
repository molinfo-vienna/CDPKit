/* 
 * RangeHashCode.hpp
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


#ifndef CDPL_INTERNAL_RANGEHASHCODE_HPP
#define CDPL_INTERNAL_RANGEHASHCODE_HPP


namespace CDPL
{

    namespace Internal
    {

        template <typename T, typename Iterator>
        T calcHashCode(Iterator it, Iterator end)
        {
            T hash = T();

            for (; it != end; ++it)
                hash ^= T(*it + 0x9e3779b9 + (hash << 6) + (hash >> 2));

            return hash;
        }
    } // namespace Internal
} // namespace CDPL

#endif // CDPL_INTERNAL_RANGEHASHCODE_HPP
