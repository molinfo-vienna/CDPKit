/* 
 * DirectAssignmentProxy.hpp 
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
 * \brief Definition of a proxy type for direct assignment of vector and matrix expressions.
 */

#ifndef CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP
#define CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Proxy that converts assignment operator calls on a Math container into calls of corresponding direct-assignment methods
         *        that bypass alias detection.
         * \tparam C The container type whose closure is wrapped.
         */
        template <typename C>
        class DirectAssignmentProxy
        {

            typedef C                       LValueType;
            typedef typename C::ClosureType ClosureType;

          public:
            /**
             * \brief Constructs a \c %DirectAssignmentProxy instance wrapping the container lvalue \a lval.
             * \param lval The container lvalue to wrap.
             */
            explicit DirectAssignmentProxy(LValueType& lval):
                lvalue(lval) {}

            /**
             * \brief Creates a \c %DirectAssignmentProxy instance that is a copy of \a proxy.
             * \param proxy The proxy instance to copy.
             */
            DirectAssignmentProxy(const DirectAssignmentProxy& proxy):
                lvalue(proxy.lvalue) {}

            /**
             * \brief Forwards the assignment of \a e to \c *this to the wrapped lvalue's <tt>assign()</tt> method.
             * \tparam E The source expression type.
             * \param e The source expression.
             * \return A reference to the wrapped lvalue closure.
             */
            template <typename E>
            ClosureType& operator=(const E& e)
            {
                lvalue.assign(e);
                return lvalue;
            }

            /**
             * \brief Forwards the in-place addition of \a e to \c *this to the wrapped lvalue's <tt>plusAssign()</tt>  method.
             * \tparam E The source expression type.
             * \param e The expression to add.
             * \return A reference to the wrapped lvalue closure.
             */
            template <typename E>
            ClosureType& operator+=(const E& e)
            {
                lvalue.plusAssign(e);
                return lvalue;
            }

            /**
             * \brief Forwards the in-place subtraction of \a e from \c *this to the wrapped lvalue's <tt>minusAssign()</tt> method.
             * \tparam E The source expression type.
             * \param e The expression to subtract.
             * \return A reference to the wrapped lvalue closure.
             */
            template <typename E>
            ClosureType& operator-=(const E& e)
            {
                lvalue.minusAssign(e);
                return lvalue;
            }

          private:
            DirectAssignmentProxy(){};

            const DirectAssignmentProxy& operator=(const DirectAssignmentProxy&);

            ClosureType lvalue;
        };

        /**
         * \brief Factory function creating a Math::DirectAssignmentProxy instance for a \c const lvalue.
         * \tparam C The container type.
         * \param lvalue The container lvalue to wrap.
         * \return A Math::DirectAssignmentProxy instance bound to \a lvalue.
         */
        template <typename C>
        DirectAssignmentProxy<const C> direct(const C& lvalue)
        {
            return DirectAssignmentProxy<const C>(lvalue);
        }

        /**
         * \brief Factory function creating a Math::DirectAssignmentProxy instance for a mutable lvalue.
         * \tparam C The container type.
         * \param lvalue The container lvalue to wrap.
         * \return A Math::DirectAssignmentProxy instance bound to \a lvalue.
         */
        template <typename C>
        DirectAssignmentProxy<C> direct(C& lvalue)
        {
            return DirectAssignmentProxy<C>(lvalue);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP
