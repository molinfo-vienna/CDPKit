/* 
 * QuaternionAssignment.hpp 
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
 * \brief Implementation of quaternion assignment routines.
 */

#ifndef CDPL_MATH_QUATERNIONASSIGNMENT_HPP
#define CDPL_MATH_QUATERNIONASSIGNMENT_HPP

#include <utility>


namespace CDPL
{

    namespace Math
    {

        template <typename E>
        class QuaternionExpression;

        /**
         * \brief Applies the element-wise functor \a F to every (quaternion component, source component) pair (C1, C2, C3, C4).
         * \tparam F The element-wise binary functor template.
         * \tparam Q The destination quaternion container type.
         * \tparam E The source quaternion expression type.
         * \param q The destination quaternion.
         * \param e The source quaternion expression.
         */
        template <template <typename T1, typename T2> class F, typename Q, typename E>
        void quaternionAssignQuaternion(Q& q, const QuaternionExpression<E>& e)
        {
            typedef F<typename Q::Reference, typename E::ValueType> FunctorType;

            FunctorType::apply(q.getC1(), e().getC1());
            FunctorType::apply(q.getC2(), e().getC2());
            FunctorType::apply(q.getC3(), e().getC3());
            FunctorType::apply(q.getC4(), e().getC4());
        }

        /**
         * \brief Applies the element-wise functor \a F to every (quaternion component, scalar) pair.
         * \tparam F The element-wise binary functor template.
         * \tparam Q The destination quaternion container type.
         * \tparam T The scalar type.
         * \param q The destination quaternion.
         * \param t The scalar value applied to every component.
         */
        template <template <typename T1, typename T2> class F, typename Q, typename T>
        void quaternionAssignScalar(Q& q, const T& t)
        {
            typedef F<typename Q::Reference, T> FunctorType;

            FunctorType::apply(q.getC1(), t);
            FunctorType::apply(q.getC2(), t);
            FunctorType::apply(q.getC3(), t);
            FunctorType::apply(q.getC4(), t);
        }

        /**
         * \brief Swaps the components of two quaternion expressions component by component.
         * \tparam Q The first quaternion container type.
         * \tparam E The second quaternion expression type.
         * \param q The first quaternion.
         * \param e The second quaternion expression.
         */
        template <typename Q, typename E>
        void quaternionSwap(Q& q, QuaternionExpression<E>& e)
        {
            std::swap(q.getC1(), e().getC1());
            std::swap(q.getC2(), e().getC2());
            std::swap(q.getC3(), e().getC3());
            std::swap(q.getC4(), e().getC4());
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_QUATERNIONASSIGNMENT_HPP
