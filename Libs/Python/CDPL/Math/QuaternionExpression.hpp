/* 
 * QuaternionExpression.hpp 
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


#ifndef CDPL_PYTHON_MATH_QUATERNIONEXPRESSION_HPP
#define CDPL_PYTHON_MATH_QUATERNIONEXPRESSION_HPP

#include <memory>

#include "CDPL/Math/QuaternionAssignment.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"


namespace CDPLPythonMath
{

    template <typename T>
    class ConstQuaternionExpression : public CDPL::Math::QuaternionExpression<ConstQuaternionExpression<T> >
    {

      public:
        typedef ConstQuaternionExpression SelfType;
        typedef T                         ValueType;
        typedef const T                   Reference;
        typedef const T                   ConstReference;
        typedef const SelfType&           ClosureType;
        typedef const SelfType&           ConstClosureType;
        typedef std::shared_ptr<SelfType> SharedPointer;

        virtual ~ConstQuaternionExpression() {}

        virtual ConstReference getC1() const = 0;
        virtual ConstReference getC2() const = 0;
        virtual ConstReference getC3() const = 0;
        virtual ConstReference getC4() const = 0;

      protected:
        ConstQuaternionExpression() {}
    };

    template <typename T>
    class QuaternionExpression : public ConstQuaternionExpression<T>,
                                 public CDPL::Math::QuaternionExpression<QuaternionExpression<T> >
    {

      public:
        typedef QuaternionExpression                        SelfType;
        typedef ConstQuaternionExpression<T>                ConstExpressionType;
        typedef T                                           ValueType;
        typedef T&                                          Reference;
        typedef const T                                     ConstReference;
        typedef SelfType&                                   ClosureType;
        typedef const SelfType&                             ConstClosureType;
        typedef std::shared_ptr<SelfType>                   SharedPointer;
        typedef typename ConstExpressionType::SharedPointer ConstExpressionPointer;

        virtual ~QuaternionExpression() {}

        using ConstQuaternionExpression<T>::getC1;
        using ConstQuaternionExpression<T>::getC2;
        using ConstQuaternionExpression<T>::getC3;
        using ConstQuaternionExpression<T>::getC4;

        virtual Reference getC1() = 0;
        virtual Reference getC2() = 0;
        virtual Reference getC3() = 0;
        virtual Reference getC4() = 0;

        virtual void set(const ValueType& c1, const ValueType& c2, const ValueType& c3, const ValueType& c4) = 0;

        virtual QuaternionExpression& operator=(const ConstExpressionType& e) = 0;

        virtual QuaternionExpression& operator+=(const ConstExpressionType& e) = 0;
        virtual QuaternionExpression& operator-=(const ConstExpressionType& e) = 0;

        virtual QuaternionExpression& operator+=(const ValueType& t) = 0;
        virtual QuaternionExpression& operator-=(const ValueType& t) = 0;

        virtual QuaternionExpression& operator*=(const ConstExpressionType& e) = 0;
        virtual QuaternionExpression& operator/=(const ConstExpressionType& e) = 0;

        virtual QuaternionExpression& operator*=(const ValueType& t) = 0;
        virtual QuaternionExpression& operator/=(const ValueType& t) = 0;

        void swap(QuaternionExpression& e)
        {
            CDPL::Math::quaternionSwap<QuaternionExpression, QuaternionExpression>(*this, e);
        }

        QuaternionExpression& operator=(const QuaternionExpression& e)
        {
            return operator=(static_cast<const ConstExpressionType&>(e));
        }

        template <typename T1>
        QuaternionExpression& operator=(ConstQuaternionExpression<T1>& e)
        {
            using namespace CDPL;
            using namespace Math;

            quaternionAssignQuaternion<ScalarAssignment>(*this, e);
            return *this;
        }

      protected:
        QuaternionExpression() {}
    };
} // namespace CDPLPythonMath

#endif // CDPL_PYTHON_MATH_QUATERNIONEXPRESSION_HPP
