/* 
 * GridAssignment.hpp 
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
 * \brief Implementation of grid assignment routines.
 */

#ifndef CDPL_MATH_GRIDASSIGNMENT_HPP
#define CDPL_MATH_GRIDASSIGNMENT_HPP

#include <utility>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename E> class GridExpression;
        template <template <typename T1, typename T2> class F, typename G, typename E>
        void gridAssignGrid(G& g, const GridExpression<E>& e)
        {
            typedef typename CommonType<typename G::SizeType, typename E::SizeType>::Type SizeType;

            SizeType size1 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize1()), SizeType(e().getSize1()), Base::SizeError);
            SizeType size2 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize2()), SizeType(e().getSize2()), Base::SizeError);
            SizeType size3 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize3()), SizeType(e().getSize3()), Base::SizeError);

            typedef F<typename G::Reference, typename E::ValueType> FunctorType;

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    for (SizeType k = 0; k < size3; k++)
                        FunctorType::apply(g(i, j, k), e()(i, j, k));
        }

        template <template <typename T1, typename T2> class F, typename G, typename T>
        void gridAssignScalar(G& g, const T& t)
        {
            typedef F<typename G::Reference, T> FunctorType;
            typedef typename G::SizeType SizeType;

            SizeType size1 = g.getSize1();
            SizeType size2 = g.getSize2();
            SizeType size3 = g.getSize3();

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    for (SizeType k = 0; k < size3; k++)
                        FunctorType::apply(g(i, j, k), t);
        }

        template <typename G, typename E>
        void gridSwap(G& g, GridExpression<E>& e)
        {
            typedef typename CommonType<typename G::SizeType, typename E::SizeType>::Type SizeType;

            SizeType size1 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize1()), SizeType(e().getSize1()), Base::SizeError);
            SizeType size2 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize2()), SizeType(e().getSize2()), Base::SizeError);
            SizeType size3 = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(g.getSize3()), SizeType(e().getSize3()), Base::SizeError);

            for (SizeType i = 0; i < size1; i++)
                for (SizeType j = 0; j < size2; j++)
                    for (SizeType k = 0; k < size3; k++)
                        std::swap(g(i, j, k), e()(i, j, k));
        }
    }
}

#endif // CDPL_MATH_GRIDASSIGNMENT_HPP
