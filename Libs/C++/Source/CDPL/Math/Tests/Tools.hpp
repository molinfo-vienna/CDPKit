/* 
 * Tools.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef CDPL_MATH_TEST_TOOLS_HPP
#define CDPL_MATH_TEST_TOOLS_HPP


namespace
{

    template <typename M, typename Array>
    void initMatrix(M& mtx, const Array& data)
    {
        for (typename M::SizeType i = 0, k = 0; i < mtx.getSize1(); i++)
            for (typename M::SizeType j = 0; j < mtx.getSize2(); j++)
                mtx(i, j) = data[k++];
    } 

    template <typename V, typename Array>
    void initVector(V& vec, const Array& data)
    {
        for (typename V::SizeType i = 0; i < vec.getSize(); i++)
            vec(i) = data[i];
    } 
}

#endif // CDPL_MATH_TEST_TOOLS_HPP
