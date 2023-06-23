/* 
 * DirectAssignmentProxy.hpp 
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
 * \brief Definition of a proxy type for direct assignment of vector and matrix expressions.
 */

#ifndef CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP
#define CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP


namespace CDPL
{

    namespace Math
    {

        template <typename C>
        class DirectAssignmentProxy
        {

            typedef C LValueType;
            typedef typename C::ClosureType ClosureType;

        public:
            explicit DirectAssignmentProxy(LValueType& lval): lvalue(lval) {}

            DirectAssignmentProxy(const DirectAssignmentProxy& proxy): lvalue(proxy.lvalue) {}

            template <typename E>
            ClosureType& operator=(const E& e) {
                lvalue.assign(e);
                return lvalue;
            }

            template <typename E>
            ClosureType& operator+=(const E& e) {
                lvalue.plusAssign(e);
                return lvalue;
            }

            template <typename E>
            ClosureType& operator-=(const E& e) {
                lvalue.minusAssign(e);
                return lvalue;
            }

        private:
            DirectAssignmentProxy() {};

            const DirectAssignmentProxy& operator=(const DirectAssignmentProxy&);

            ClosureType lvalue;
        };

        template <typename C>
        DirectAssignmentProxy<const C> direct(const C& lvalue)
        {
            return DirectAssignmentProxy<const C>(lvalue);
        }

        template <typename C>
        DirectAssignmentProxy<C> direct(C& lvalue)
        {
            return DirectAssignmentProxy<C>(lvalue);
        }
    }
}

#endif // CDPL_MATH_DIRECTASSIGNMENTPROXY_HPP
