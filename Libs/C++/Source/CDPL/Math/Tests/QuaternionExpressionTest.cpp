/* 
 * QuaternionExpressionTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Math/QuaternionExpression.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/IO.hpp"


namespace
{

    template <typename Q>
    void checkQuaternionNormFunction(const Q& q)
    {
        using namespace CDPL;
        using namespace Math;

        typedef typename Q::ValueType ValueType;

        BOOST_CHECK_EQUAL(norm(q), TypeTraits<ValueType>::sqrt(q.getC1() * q.getC1() + q.getC2() * q.getC2() +
                                                               q.getC3() * q.getC3() + q.getC4() * q.getC4()));
    }

    template <typename Q>
    void checkQuaternionNorm2Function(const Q& q)
    {
        BOOST_CHECK_EQUAL(norm2(q), (q.getC1() * q.getC1() + q.getC2() * q.getC2() +
                                     q.getC3() * q.getC3() + q.getC4() * q.getC4()));
    }

    template <typename Q>
    void checkQuaternionUnrealFunction(const Q& q)
    {
        BOOST_CHECK_EQUAL(unreal(q).getC1(), typename Q::ValueType());
        BOOST_CHECK_EQUAL(unreal(q).getC2(), q.getC2());
        BOOST_CHECK_EQUAL(unreal(q).getC3(), q.getC3());
        BOOST_CHECK_EQUAL(unreal(q).getC4(), q.getC4());
    }

    template <typename Q>
    void checkQuaternionConjFunction(const Q& q)
    {
        BOOST_CHECK_EQUAL(conj(q).getC1(),  q.getC1());
        BOOST_CHECK_EQUAL(conj(q).getC2(), -q.getC2());
        BOOST_CHECK_EQUAL(conj(q).getC3(), -q.getC3());
        BOOST_CHECK_EQUAL(conj(q).getC4(), -q.getC4());
    }

    template <typename Q1, typename Q2>
    void checkQuaternionElemDivFunction(const Q1& q1, const Q2& q2)
    {
        BOOST_CHECK_EQUAL(elemDiv(q1, q2).getC1(), q1.getC1() / q2.getC1());
        BOOST_CHECK_EQUAL(elemDiv(q1, q2).getC2(), q1.getC2() / q2.getC2());
        BOOST_CHECK_EQUAL(elemDiv(q1, q2).getC3(), q1.getC3() / q2.getC3());
        BOOST_CHECK_EQUAL(elemDiv(q1, q2).getC4(), q1.getC4() / q2.getC4());
    }

    template <typename Q1, typename Q2>
    void checkQuaternionElemProdFunction(const Q1& q1, const Q2& q2)
    {
        BOOST_CHECK_EQUAL(elemProd(q1, q2).getC1(), q1.getC1() * q2.getC1());
        BOOST_CHECK_EQUAL(elemProd(q1, q2).getC2(), q1.getC2() * q2.getC2());
        BOOST_CHECK_EQUAL(elemProd(q1, q2).getC3(), q1.getC3() * q2.getC3());
        BOOST_CHECK_EQUAL(elemProd(q1, q2).getC4(), q1.getC4() * q2.getC4());
    }

    template <typename Q>
    void checkQuaternionPlusOperator(const Q& q)
    {
        BOOST_CHECK_EQUAL(operator+(q).getC1(), q.getC1());
        BOOST_CHECK_EQUAL(operator+(q).getC2(), q.getC2());
        BOOST_CHECK_EQUAL(operator+(q).getC3(), q.getC3());
        BOOST_CHECK_EQUAL(operator+(q).getC4(), q.getC4());
    }

    template <typename Q>
    void checkQuaternionMinusOperator(const Q& q)
    {
        BOOST_CHECK_EQUAL(operator-(q).getC1(), -q.getC1());
        BOOST_CHECK_EQUAL(operator-(q).getC2(), -q.getC2());
        BOOST_CHECK_EQUAL(operator-(q).getC3(), -q.getC3());
        BOOST_CHECK_EQUAL(operator-(q).getC4(), -q.getC4());
    }

    template <typename Q1, typename Q2>
    void checkQuaternionAddition(const Q1& q1, const Q2& q2)
    {
        BOOST_CHECK_EQUAL((q1 + q2).getC1(), q1.getC1() + q2.getC1());
        BOOST_CHECK_EQUAL((q1 + q2).getC2(), q1.getC2() + q2.getC2());
        BOOST_CHECK_EQUAL((q1 + q2).getC3(), q1.getC3() + q2.getC3());
        BOOST_CHECK_EQUAL((q1 + q2).getC4(), q1.getC4() + q2.getC4());

        BOOST_CHECK_EQUAL(operator+(q1, q2).getC1(), q1.getC1() + q2.getC1());
        BOOST_CHECK_EQUAL(operator+(q1, q2).getC2(), q1.getC2() + q2.getC2());
        BOOST_CHECK_EQUAL(operator+(q1, q2).getC3(), q1.getC3() + q2.getC3());
        BOOST_CHECK_EQUAL(operator+(q1, q2).getC4(), q1.getC4() + q2.getC4());

        BOOST_CHECK_EQUAL((q2 + q1).getC1(), q1.getC1() + q2.getC1());
        BOOST_CHECK_EQUAL((q2 + q1).getC2(), q1.getC2() + q2.getC2());
        BOOST_CHECK_EQUAL((q2 + q1).getC3(), q1.getC3() + q2.getC3());
        BOOST_CHECK_EQUAL((q2 + q1).getC4(), q1.getC4() + q2.getC4());

        BOOST_CHECK_EQUAL(operator+(q2, q1).getC1(), q1.getC1() + q2.getC1());
        BOOST_CHECK_EQUAL(operator+(q2, q1).getC2(), q1.getC2() + q2.getC2());
        BOOST_CHECK_EQUAL(operator+(q2, q1).getC3(), q1.getC3() + q2.getC3());
        BOOST_CHECK_EQUAL(operator+(q2, q1).getC4(), q1.getC4() + q2.getC4());
    }

    template <typename Q1, typename Q2>
    void checkQuaternionSubtraction(const Q1& q1, const Q2& q2)
    {
        BOOST_CHECK_EQUAL((q1 - q2).getC1(), q1.getC1() - q2.getC1());
        BOOST_CHECK_EQUAL((q1 - q2).getC2(), q1.getC2() - q2.getC2());
        BOOST_CHECK_EQUAL((q1 - q2).getC3(), q1.getC3() - q2.getC3());
        BOOST_CHECK_EQUAL((q1 - q2).getC4(), q1.getC4() - q2.getC4());

        BOOST_CHECK_EQUAL(operator-(q1, q2).getC1(), q1.getC1() - q2.getC1());
        BOOST_CHECK_EQUAL(operator-(q1, q2).getC2(), q1.getC2() - q2.getC2());
        BOOST_CHECK_EQUAL(operator-(q1, q2).getC3(), q1.getC3() - q2.getC3());
        BOOST_CHECK_EQUAL(operator-(q1, q2).getC4(), q1.getC4() - q2.getC4());

        BOOST_CHECK_EQUAL((q2 - q1).getC1(), -(q1.getC1() - q2.getC1()));
        BOOST_CHECK_EQUAL((q2 - q1).getC2(), -(q1.getC2() - q2.getC2()));
        BOOST_CHECK_EQUAL((q2 - q1).getC3(), -(q1.getC3() - q2.getC3()));
        BOOST_CHECK_EQUAL((q2 - q1).getC4(), -(q1.getC4() - q2.getC4()));

        BOOST_CHECK_EQUAL(operator-(q2, q1).getC1(), -(q1.getC1() - q2.getC1()));
        BOOST_CHECK_EQUAL(operator-(q2, q1).getC2(), -(q1.getC2() - q2.getC2()));
        BOOST_CHECK_EQUAL(operator-(q2, q1).getC3(), -(q1.getC3() - q2.getC3()));
        BOOST_CHECK_EQUAL(operator-(q2, q1).getC4(), -(q1.getC4() - q2.getC4()));
    }

    template <typename T, typename Q>
    void checkScalarQuaternionAddition(const T& t, const Q& q)
    {
        BOOST_CHECK_EQUAL((t + q).getC1(), q.getC1() + t);
        BOOST_CHECK_EQUAL((t + q).getC2(), q.getC2());
        BOOST_CHECK_EQUAL((t + q).getC3(), q.getC3());
        BOOST_CHECK_EQUAL((t + q).getC4(), q.getC4());

        BOOST_CHECK_EQUAL(operator+(t, q).getC1(), q.getC1() + t);
        BOOST_CHECK_EQUAL(operator+(t, q).getC2(), q.getC2());
        BOOST_CHECK_EQUAL(operator+(t, q).getC3(), q.getC3());
        BOOST_CHECK_EQUAL(operator+(t, q).getC4(), q.getC4());
    }

    template <typename T, typename Q>
    void checkScalarQuaternionSubtraction(const T& t, const Q& q)
    {
        BOOST_CHECK_EQUAL((t - q).getC1(), t - q.getC1());
        BOOST_CHECK_EQUAL((t - q).getC2(), -q.getC2());
        BOOST_CHECK_EQUAL((t - q).getC3(), -q.getC3());
        BOOST_CHECK_EQUAL((t - q).getC4(), -q.getC4());

        BOOST_CHECK_EQUAL(operator-(t, q).getC1(), t - q.getC1());
        BOOST_CHECK_EQUAL(operator-(t, q).getC2(), -q.getC2());
        BOOST_CHECK_EQUAL(operator-(t, q).getC3(), -q.getC3());
        BOOST_CHECK_EQUAL(operator-(t, q).getC4(), -q.getC4());
    }

    template <typename Q, typename T>
    void checkQuaternionScalarAddition(const Q& q, const T& t)
    {
        BOOST_CHECK_EQUAL((q + t).getC1(), q.getC1() + t);
        BOOST_CHECK_EQUAL((q + t).getC2(), q.getC2());
        BOOST_CHECK_EQUAL((q + t).getC3(), q.getC3());
        BOOST_CHECK_EQUAL((q + t).getC4(), q.getC4());

        BOOST_CHECK_EQUAL(operator+(q, t).getC1(), q.getC1() + t);
        BOOST_CHECK_EQUAL(operator+(q, t).getC2(), q.getC2());
        BOOST_CHECK_EQUAL(operator+(q, t).getC3(), q.getC3());
        BOOST_CHECK_EQUAL(operator+(q, t).getC4(), q.getC4());
    }

    template <typename Q, typename T>
    void checkQuaternionScalarSubtraction(const Q& q, const T& t)
    {
        BOOST_CHECK_EQUAL((q - t).getC1(), q.getC1() - t);
        BOOST_CHECK_EQUAL((q - t).getC2(), q.getC2());
        BOOST_CHECK_EQUAL((q - t).getC3(), q.getC3());
        BOOST_CHECK_EQUAL((q - t).getC4(), q.getC4());

        BOOST_CHECK_EQUAL(operator-(q, t).getC1(), q.getC1() - t);
        BOOST_CHECK_EQUAL(operator-(q, t).getC2(), q.getC2());
        BOOST_CHECK_EQUAL(operator-(q, t).getC3(), q.getC3());
        BOOST_CHECK_EQUAL(operator-(q, t).getC4(), q.getC4());
    }

    template <typename Q1, typename Q2>
    void checkQuaternionMultiplication(const Q1& q1, const Q2& q2)
    {
        using namespace CDPL;
        using namespace Math;

        typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;

        // a = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2
        ValueType c1 = q1.getC1() * q2.getC1() - q1.getC2() * q2.getC2() 
            - q1.getC3() * q2.getC3() - q1.getC4() * q2.getC4();

        // b = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2 
        ValueType c2 =    q1.getC1() * q2.getC2() + q1.getC2() * q2.getC1() 
            + q1.getC3() * q2.getC4() - q1.getC4() * q2.getC3();

        // c = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2
        ValueType c3 =    q1.getC1() * q2.getC3() - q1.getC2() * q2.getC4() 
            + q1.getC3() * q2.getC1() + q1.getC4() * q2.getC2();
    
        // d = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2
        ValueType c4 =    q1.getC1() * q2.getC4() + q1.getC2() * q2.getC3() 
            - q1.getC3() * q2.getC2() + q1.getC4() * q2.getC1();
    
        BOOST_CHECK_EQUAL((q1 * q2).getC1(), c1);
        BOOST_CHECK_EQUAL((q1 * q2).getC2(), c2);
        BOOST_CHECK_EQUAL((q1 * q2).getC3(), c3);
        BOOST_CHECK_EQUAL((q1 * q2).getC4(), c4);

        BOOST_CHECK_EQUAL(operator*(q1, q2).getC1(), c1);
        BOOST_CHECK_EQUAL(operator*(q1, q2).getC2(), c2);
        BOOST_CHECK_EQUAL(operator*(q1, q2).getC3(), c3);
        BOOST_CHECK_EQUAL(operator*(q1, q2).getC4(), c4);
    }

    template <typename T, typename Q>
    void checkScalarQuaternionMultiplication(const T& t, const Q& q)
    {
        BOOST_CHECK_EQUAL((t * q).getC1(), t * q.getC1());
        BOOST_CHECK_EQUAL((t * q).getC2(), t * q.getC2());
        BOOST_CHECK_EQUAL((t * q).getC3(), t * q.getC3());
        BOOST_CHECK_EQUAL((t * q).getC4(), t * q.getC4());

        BOOST_CHECK_EQUAL(operator*(t, q).getC1(), t * q.getC1());
        BOOST_CHECK_EQUAL(operator*(t, q).getC2(), t * q.getC2());
        BOOST_CHECK_EQUAL(operator*(t, q).getC3(), t * q.getC3());
        BOOST_CHECK_EQUAL(operator*(t, q).getC4(), t * q.getC4());
    }

    template <typename Q, typename T>
    void checkQuaternionScalarMultiplication(const Q& q, const T& t)
    {
        BOOST_CHECK_EQUAL((q * t).getC1(), t * q.getC1());
        BOOST_CHECK_EQUAL((q * t).getC2(), t * q.getC2());
        BOOST_CHECK_EQUAL((q * t).getC3(), t * q.getC3());
        BOOST_CHECK_EQUAL((q * t).getC4(), t * q.getC4());

        BOOST_CHECK_EQUAL(operator*(q, t).getC1(), t * q.getC1());
        BOOST_CHECK_EQUAL(operator*(q, t).getC2(), t * q.getC2());
        BOOST_CHECK_EQUAL(operator*(q, t).getC3(), t * q.getC3());
        BOOST_CHECK_EQUAL(operator*(q, t).getC4(), t * q.getC4());
    }

    template <typename Q, typename T>
    void checkQuaternionScalarDivision(const Q& q, const T& t)
    {
        BOOST_CHECK_EQUAL((q / t).getC1(), q.getC1() / t);
        BOOST_CHECK_EQUAL((q / t).getC2(), q.getC2() / t);
        BOOST_CHECK_EQUAL((q / t).getC3(), q.getC3() / t);
        BOOST_CHECK_EQUAL((q / t).getC4(), q.getC4() / t);

        BOOST_CHECK_EQUAL(operator/(q, t).getC1(), q.getC1() / t);
        BOOST_CHECK_EQUAL(operator/(q, t).getC2(), q.getC2() / t);
        BOOST_CHECK_EQUAL(operator/(q, t).getC3(), q.getC3() / t);
        BOOST_CHECK_EQUAL(operator/(q, t).getC4(), q.getC4() / t);
    }

    template <typename T, typename Q>
    void checkScalarQuaternionDivision(const T& t, const Q& q)
    {
        typename Q::ValueType n = q.getC1() * q.getC1() + q.getC2() * q.getC2() +
            q.getC3() * q.getC3() + q.getC4() * q.getC4();

        BOOST_CHECK_EQUAL((t / q).getC1(), t * q.getC1() / n);
        BOOST_CHECK_EQUAL((t / q).getC2(), t * -q.getC2() / n);
        BOOST_CHECK_EQUAL((t / q).getC3(), t * -q.getC3() / n);
        BOOST_CHECK_EQUAL((t / q).getC4(), t * -q.getC4() / n);

        BOOST_CHECK_EQUAL(operator/(t, q).getC1(), t * q.getC1() / n);
        BOOST_CHECK_EQUAL(operator/(t, q).getC2(), t * -q.getC2() / n);
        BOOST_CHECK_EQUAL(operator/(t, q).getC3(), t * -q.getC3() / n);
        BOOST_CHECK_EQUAL(operator/(t, q).getC4(), t * -q.getC4() / n);
    }

    template <typename Q1, typename Q2>
    void checkQuaternionDivision(const Q1& q1, const Q2& q2)
    {
        using namespace CDPL;
        using namespace Math;

        typename Q2::ValueType n = q2.getC1() * q2.getC1() + q2.getC2() * q2.getC2() +
            q2.getC3() * q2.getC3() + q2.getC4() * q2.getC4();

        typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;

        // a = (a1 * a2 - b1 * -b2 - c1 * -c2 - d1 * -d2) / n
        ValueType c1 = (q1.getC1() * q2.getC1() - q1.getC2() * -q2.getC2() 
                        - q1.getC3() * -q2.getC3() - q1.getC4() * -q2.getC4()) / n;

        // b = (a1 * -b2 + b1 * a2 + c1 * -d2 - d1 * -c2) / n 
        ValueType c2 =    (q1.getC1() * -q2.getC2() + q1.getC2() * q2.getC1() 
                         + q1.getC3() * -q2.getC4() - q1.getC4() * -q2.getC3()) / n;

        // c = (a1 * -c2 - b1 * -d2 + c1 * a2 + d1 * -b2) / n
        ValueType c3 =    (q1.getC1() * -q2.getC3() - q1.getC2() * -q2.getC4() 
                         + q1.getC3() * q2.getC1() + q1.getC4() * -q2.getC2()) / n;
    
        // d = (a1 * -d2 + b1 * -c2 - c1 * -b2 + d1 * a2) / n
        ValueType c4 =    (q1.getC1() * -q2.getC4() + q1.getC2() * -q2.getC3() 
                         - q1.getC3() * -q2.getC2() + q1.getC4() * q2.getC1()) / n;
    
        BOOST_CHECK_EQUAL((q1 / q2).getC1(), c1);
        BOOST_CHECK_EQUAL((q1 / q2).getC2(), c2);
        BOOST_CHECK_EQUAL((q1 / q2).getC3(), c3);
        BOOST_CHECK_EQUAL((q1 / q2).getC4(), c4);

        BOOST_CHECK_EQUAL(operator/(q1, q2).getC1(), c1);
        BOOST_CHECK_EQUAL(operator/(q1, q2).getC2(), c2);
        BOOST_CHECK_EQUAL(operator/(q1, q2).getC3(), c3);
        BOOST_CHECK_EQUAL(operator/(q1, q2).getC4(), c4);
    }

    template <typename Q>
    void checkQuaternionInvFunction(const Q& q)
    {
        typename Q::ValueType n = q.getC1() * q.getC1() + q.getC2() * q.getC2() +
            q.getC3() * q.getC3() + q.getC4() * q.getC4();

        BOOST_CHECK_EQUAL(inv(q).getC1(),  q.getC1() / n);
        BOOST_CHECK_EQUAL(inv(q).getC2(), -q.getC2() / n);
        BOOST_CHECK_EQUAL(inv(q).getC3(), -q.getC3() / n);
        BOOST_CHECK_EQUAL(inv(q).getC4(), -q.getC4() / n);
    }

    template <typename ResType, typename ArgType>
    struct QuaternionUnary1TestFunctor
    {
        
        typedef ResType ResultType;
        typedef ArgType ArgumentType;

        static ResultType apply(ArgumentType arg) {
            return (arg * arg);
        }
    };

    template <typename ResType>
    struct QuaternionUnary2TestFunctor
    {
        
        typedef ResType ResultType;
    
        template <typename E>
        static ResultType applyC1(const CDPL::Math::QuaternionExpression<E>& q) {
            return q().getC4();
        }

        template <typename E>
        static ResultType applyC2(const CDPL::Math::QuaternionExpression<E>& q) {
            return q().getC3();
        }
    
        template <typename E>
        static ResultType applyC3(const CDPL::Math::QuaternionExpression<E>& q) {
            return q().getC2();
        }

        template <typename E>
        static ResultType applyC4(const CDPL::Math::QuaternionExpression<E>& q) {
            return q().getC1();
        }
    };

    template <typename ResType, typename ArgType1, typename ArgType2>
    struct QuaternionBinary1TestFunctor
    {
        
        typedef ResType ResultType;
        typedef ArgType1 ArgumentType1;
        typedef ArgType2 ArgumentType2;

        static ResultType apply(ArgumentType1 arg1, ArgumentType2 arg2) {
            return (arg1 * arg2 - arg1) ;
        }
    };

    template <typename ResType>
    struct QuaternionBinary2TestFunctor
    {
        
        typedef ResType ResultType;
    
        template <typename E1, typename E2>
        static ResultType applyC1(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2) {
            return (q1().getC4() * q2().getC1());
        }

        template <typename E1, typename E2>
        static ResultType applyC2(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2) {
            return (q1().getC3() * q2().getC2());
        }
    
        template <typename E1, typename E2>
        static ResultType applyC3(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2) {
            return (q1().getC2() * q2().getC3());
        }

        template <typename E1, typename E2>
        static ResultType applyC4(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2) {
            return (q1().getC1() * q2().getC4());
        }
    };

    template <typename ResType, typename Arg1Type, typename Arg2Type>
    struct Scalar1QuaternionBinary1TestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg1Type Argument1Type;
        typedef Arg2Type Argument2Type;
    
        static ResultType apply(Argument1Type arg1, Argument2Type arg2) {
            return (arg1 * arg2 + arg1);
        }
    };

    template <typename ResType, typename Arg1Type>
    struct Scalar1QuaternionBinary2TestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg1Type Argument1Type;
    
        template <typename E>
        static ResultType applyC1(Argument1Type arg1, const CDPL::Math::QuaternionExpression<E>& q) {
            return (arg1 * q().getC4() * 2 + arg1);
        }

        template <typename E>
        static ResultType applyC2(Argument1Type arg1, const CDPL::Math::QuaternionExpression<E>& q) {
            return (arg1 * q().getC3() * 3 + arg1);
        }
    
        template <typename E>
        static ResultType applyC3(Argument1Type arg1, const CDPL::Math::QuaternionExpression<E>& q) {
            return (arg1 * q().getC2() * 4 + arg1);
        }

        template <typename E>
        static ResultType applyC4(Argument1Type arg1, const CDPL::Math::QuaternionExpression<E>& q) {
            return (arg1 * q().getC1() * 5 + arg1);
        }
    };

    template <typename ResType, typename Arg1Type, typename Arg2Type>
    struct Scalar2QuaternionBinary1TestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg1Type Argument1Type;
        typedef Arg2Type Argument2Type;
    
        static ResultType apply(Argument1Type arg1, Argument2Type arg2) {
            return ((arg1 - arg2) / arg1);
        }
    };

    template <typename ResType, typename Arg2Type>
    struct Scalar2QuaternionBinary2TestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg2Type Argument2Type;
    
        template <typename E>
        static ResultType applyC1(const CDPL::Math::QuaternionExpression<E>& q, Argument2Type arg2) {
            return (arg2 * q().getC4() * 2 + 17);
        }

        template <typename E>
        static ResultType applyC2(const CDPL::Math::QuaternionExpression<E>& q, Argument2Type arg2) {
            return (arg2 * q().getC3() * 3 + 27);
        }
    
        template <typename E>
        static ResultType applyC3(const CDPL::Math::QuaternionExpression<E>& q, Argument2Type arg2) {
            return (arg2 * q().getC2() * 4 + 37);
        }

        template <typename E>
        static ResultType applyC4(const CDPL::Math::QuaternionExpression<E>& q, Argument2Type arg2) {
            return (arg2 * q().getC1() * 5 + 47);
        }
    };

    template <typename ResType, typename Arg3Type>
    struct Scalar3QuaternionTernaryTestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg3Type Argument3Type;
    
        template <typename E1, typename E2>
        static ResultType applyC1(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2, 
                                  Argument3Type arg3) {

            return (q1().getC4() * q2().getC1() + arg3);
        }

        template <typename E1, typename E2>
        static ResultType applyC2(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2, 
                                  Argument3Type arg3) {

            return (q1().getC3() * q2().getC2() - arg3);
        }
    
        template <typename E1, typename E2>
        static ResultType applyC3(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2, 
                                  Argument3Type arg3) {

            return (q1().getC2() * q2().getC3() * arg3);
        }

        template <typename E1, typename E2>
        static ResultType applyC4(const CDPL::Math::QuaternionExpression<E1>& q1, 
                                  const CDPL::Math::QuaternionExpression<E2>& q2, 
                                  Argument3Type arg3) {

            return (q1().getC1() * q2().getC4() / arg3);
        }
    };

    template <typename ResType, typename Arg1Type, typename Arg3Type>
    struct Scalar13QuaternionTernaryTestFunctor
    {
        
        typedef ResType ResultType;
        typedef Arg1Type Argument1Type;
        typedef Arg3Type Argument3Type;
    
        template <typename E>
        static ResultType applyC1(Argument1Type arg1, 
                                  const CDPL::Math::QuaternionExpression<E>& q, 
                                  Argument3Type arg3) {

            return (q().getC4() * arg1 + arg3);
        }

        template <typename E>
        static ResultType applyC2(Argument1Type arg1, 
                                  const CDPL::Math::QuaternionExpression<E>& q, 
                                  Argument3Type arg3) {

            return (q().getC3() * arg1 - arg3);
        }
    
        template <typename E>
        static ResultType applyC3(Argument1Type arg1, 
                                  const CDPL::Math::QuaternionExpression<E>& q, 
                                  Argument3Type arg3) {

            return (q().getC2() * arg1 * arg3);
        }

        template <typename E>
        static ResultType applyC4(Argument1Type arg1, 
                                  const CDPL::Math::QuaternionExpression<E>& q, 
                                  Argument3Type arg3) {

            return (q().getC1() * arg1 / arg3);
        }
    };
}


BOOST_AUTO_TEST_CASE(QuaternionUnary1Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<double>, QuaternionUnary1TestFunctor<long, float> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<double>, QuaternionUnary1TestFunctor<long, char> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<double>, QuaternionUnary1TestFunctor<long, int> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<float>, QuaternionUnary1TestFunctor<long double, double> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<float>, QuaternionUnary1TestFunctor<long double, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionUnary1<Quaternion<float>, QuaternionUnary1TestFunctor<long double, long> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef QuaternionUnary1TestFunctor<long, const int&> Functor;

    Quaternion<int> q(-1, 0, 4, 22);
    QuaternionUnary1<Quaternion<int>, Functor> q_un(q);

    BOOST_CHECK_EQUAL(q_un.getC1(), Functor::apply(q.getC1()));
    BOOST_CHECK_EQUAL(q_un.getC2(), Functor::apply(q.getC2()));
    BOOST_CHECK_EQUAL(q_un.getC3(), Functor::apply(q.getC3()));
    BOOST_CHECK_EQUAL(q_un.getC4(), Functor::apply(q.getC4()));
}

BOOST_AUTO_TEST_CASE(QuaternionUnary2Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<double>, QuaternionUnary2TestFunctor<long> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<double>, QuaternionUnary2TestFunctor<long> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<double>, QuaternionUnary2TestFunctor<long> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<float>, QuaternionUnary2TestFunctor<long double> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<float>, QuaternionUnary2TestFunctor<long double> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionUnary2<Quaternion<float>, QuaternionUnary2TestFunctor<long double> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef QuaternionUnary2TestFunctor<long> Functor;

    Quaternion<int> q(-1, 0, 4, 22);
    QuaternionUnary2<Quaternion<int>, Functor> q_un(q);

    BOOST_CHECK_EQUAL(q_un.getC1(), Functor::applyC1(q));
    BOOST_CHECK_EQUAL(q_un.getC2(), Functor::applyC2(q));
    BOOST_CHECK_EQUAL(q_un.getC3(), Functor::applyC3(q));
    BOOST_CHECK_EQUAL(q_un.getC4(), Functor::applyC4(q));
}

BOOST_AUTO_TEST_CASE(QuaternionBinary1Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<double>, Quaternion<char>, QuaternionBinary1TestFunctor<long, long double, float> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<double>, Quaternion<short>, QuaternionBinary1TestFunctor<long, long double, int> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<double>, Quaternion<int>, QuaternionBinary1TestFunctor<long, long double, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<float>, Quaternion<float>, QuaternionBinary1TestFunctor<long double, char, short> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<float>, Quaternion<double>, QuaternionBinary1TestFunctor<long double, char, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionBinary1<Quaternion<float>, Quaternion<long>, QuaternionBinary1TestFunctor<long double, char, unsigned int> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef QuaternionBinary1TestFunctor<long double, const int&, const double&> Functor;

    Quaternion<int> q1(-1, 0, 4, 22);
    Quaternion<double> q2(50.2, 0.23, 24.23, -22.0);
    QuaternionBinary1<Quaternion<int>, Quaternion<double>, Functor> q_bin(q1, q2);

    BOOST_CHECK_EQUAL(q_bin.getC1(), Functor::apply(q1.getC1(), q2.getC1()));
    BOOST_CHECK_EQUAL(q_bin.getC2(), Functor::apply(q1.getC2(), q2.getC2()));
    BOOST_CHECK_EQUAL(q_bin.getC3(), Functor::apply(q1.getC3(), q2.getC3()));
    BOOST_CHECK_EQUAL(q_bin.getC4(), Functor::apply(q1.getC4(), q2.getC4()));
}

BOOST_AUTO_TEST_CASE(QuaternionBinary2Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<double>, Quaternion<char>, QuaternionBinary2TestFunctor<long> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<double>, Quaternion<short>, QuaternionBinary2TestFunctor<long> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<double>, Quaternion<int>, QuaternionBinary2TestFunctor<long> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<float>, Quaternion<float>, QuaternionBinary2TestFunctor<long double> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<float>, Quaternion<double>, QuaternionBinary2TestFunctor<long double> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(QuaternionBinary2<Quaternion<float>, Quaternion<long>, QuaternionBinary2TestFunctor<long double> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef QuaternionBinary2TestFunctor<long double> Functor;

    Quaternion<int> q1(-1, 0, 4, 22);
    Quaternion<double> q2(50.2, 0.23, 24.23, -22.0);
    QuaternionBinary2<Quaternion<int>, Quaternion<double>, Functor> q_bin(q1, q2);

    BOOST_CHECK_EQUAL(q_bin.getC1(), Functor::applyC1(q1, q2));
    BOOST_CHECK_EQUAL(q_bin.getC2(), Functor::applyC2(q1, q2));
    BOOST_CHECK_EQUAL(q_bin.getC3(), Functor::applyC3(q1, q2));
    BOOST_CHECK_EQUAL(q_bin.getC4(), Functor::applyC4(q1, q2));
}

BOOST_AUTO_TEST_CASE(Scalar1QuaternionBinary1Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<double, Quaternion<char>, Scalar1QuaternionBinary1TestFunctor<long, long double, float> >::ValueType) ==
                       typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<double, Quaternion<short>, Scalar1QuaternionBinary1TestFunctor<long, long double, int> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<double, Quaternion<int>, Scalar1QuaternionBinary1TestFunctor<long, long double, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<float, Quaternion<float>, Scalar1QuaternionBinary1TestFunctor<long double, char, short> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<float, Quaternion<double>, Scalar1QuaternionBinary1TestFunctor<long double, char, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary1<float, Quaternion<long>, Scalar1QuaternionBinary1TestFunctor<long double, char, unsigned int> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar1QuaternionBinary1TestFunctor<long double, const long&, const double&> Functor;

    Quaternion<double> q(50.2, 0.23, 24.23, -22.0);
    Scalar1QuaternionBinary1<long, Quaternion<double>, Functor> sq_bin(-34, q);

    BOOST_CHECK_EQUAL(sq_bin.getC1(), Functor::apply(-34, q.getC1()));
    BOOST_CHECK_EQUAL(sq_bin.getC2(), Functor::apply(-34, q.getC2()));
    BOOST_CHECK_EQUAL(sq_bin.getC3(), Functor::apply(-34, q.getC3()));
    BOOST_CHECK_EQUAL(sq_bin.getC4(), Functor::apply(-34, q.getC4()));
}

BOOST_AUTO_TEST_CASE(Scalar1QuaternionBinary2Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<double, Quaternion<char>, Scalar1QuaternionBinary2TestFunctor<long, float> >::ValueType) ==
                       typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<double, Quaternion<short>, Scalar1QuaternionBinary2TestFunctor<long, int> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<double, Quaternion<int>, Scalar1QuaternionBinary2TestFunctor<long, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<float, Quaternion<float>, Scalar1QuaternionBinary2TestFunctor<long double, short> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<float, Quaternion<double>, Scalar1QuaternionBinary2TestFunctor<long double, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar1QuaternionBinary2<float, Quaternion<long>, Scalar1QuaternionBinary2TestFunctor<long double, unsigned int> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar1QuaternionBinary2TestFunctor<long double, const int&> Functor;

    Quaternion<double> q(50.2, 0.23, 24.23, -22.0);
    Scalar1QuaternionBinary2<int, Quaternion<double>, Functor> sq_bin(-34, q);

    BOOST_CHECK_EQUAL(sq_bin.getC1(), Functor::applyC1(-34, q));
    BOOST_CHECK_EQUAL(sq_bin.getC2(), Functor::applyC2(-34, q));
    BOOST_CHECK_EQUAL(sq_bin.getC3(), Functor::applyC3(-34, q));
    BOOST_CHECK_EQUAL(sq_bin.getC4(), Functor::applyC4(-34, q));
}

BOOST_AUTO_TEST_CASE(Scalar2QuaternionBinary1Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<char>, double, Scalar2QuaternionBinary1TestFunctor<long, long double, float> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<short>, double, Scalar2QuaternionBinary1TestFunctor<long, long double, int> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<int>, double, Scalar2QuaternionBinary1TestFunctor<long, long double, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<float>, float, Scalar2QuaternionBinary1TestFunctor<long double, char, short> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<double>, float, Scalar2QuaternionBinary1TestFunctor<long double, char, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary1<Quaternion<long>, float, Scalar2QuaternionBinary1TestFunctor<long double, char, unsigned int> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar2QuaternionBinary1TestFunctor<long double, const double&, const float&> Functor;

    Quaternion<double> q(50.2, 0.23, 24.23, -22.0);
    Scalar2QuaternionBinary1<Quaternion<double>, float, Functor> qs_bin(q, 5.17f);

    BOOST_CHECK_EQUAL(qs_bin.getC1(), Functor::apply(q.getC1(), 5.17f));
    BOOST_CHECK_EQUAL(qs_bin.getC2(), Functor::apply(q.getC2(), 5.17f));
    BOOST_CHECK_EQUAL(qs_bin.getC3(), Functor::apply(q.getC3(), 5.17f));
    BOOST_CHECK_EQUAL(qs_bin.getC4(), Functor::apply(q.getC4(), 5.17f));
}

BOOST_AUTO_TEST_CASE(Scalar2QuaternionBinary2Test)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<char>, double, Scalar2QuaternionBinary2TestFunctor<long, float> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<short>, double, Scalar2QuaternionBinary2TestFunctor<long, int> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<int>, double, Scalar2QuaternionBinary2TestFunctor<long, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<float>, float, Scalar2QuaternionBinary2TestFunctor<long double, short> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<double>, float, Scalar2QuaternionBinary2TestFunctor<long double, int> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar2QuaternionBinary2<Quaternion<long>, float, Scalar2QuaternionBinary2TestFunctor<long double, unsigned int> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar2QuaternionBinary2TestFunctor<long double, const int&> Functor;

    Quaternion<double> q(50.2, 0.23, 24.23, -22.0);
    Scalar2QuaternionBinary2<Quaternion<double>, int, Functor> qs_bin(q, -32);

    BOOST_CHECK_EQUAL(qs_bin.getC1(), Functor::applyC1(q, -32));
    BOOST_CHECK_EQUAL(qs_bin.getC2(), Functor::applyC2(q, -32));
    BOOST_CHECK_EQUAL(qs_bin.getC3(), Functor::applyC3(q, -32));
    BOOST_CHECK_EQUAL(qs_bin.getC4(), Functor::applyC4(q, -32));
}

BOOST_AUTO_TEST_CASE(Scalar3QuaternionTernaryTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<double>, Quaternion<char>, float, 
                      Scalar3QuaternionTernaryTestFunctor<long, int> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<double>, Quaternion<short>, int, 
                      Scalar3QuaternionTernaryTestFunctor<long, char> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<double>, Quaternion<int>, char, 
                      Scalar3QuaternionTernaryTestFunctor<long, short> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<float>, Quaternion<float>, short, 
                      Scalar3QuaternionTernaryTestFunctor<long double, int> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<float>, Quaternion<double>, unsigned int, 
                      Scalar3QuaternionTernaryTestFunctor<long double, char> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar3QuaternionTernary<Quaternion<float>, Quaternion<long>, unsigned char, 
                      Scalar3QuaternionTernaryTestFunctor<long double, short> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar3QuaternionTernaryTestFunctor<long double, const float&> Functor;

    Quaternion<int> q1(-1, 0, 4, 22);
    Quaternion<double> q2(50.2, 0.23, 24.23, -22.0);
    Scalar3QuaternionTernary<Quaternion<int>, Quaternion<double>, float, Functor> qqs_tern(q1, q2, -1.17f);

    BOOST_CHECK_EQUAL(qqs_tern.getC1(), Functor::applyC1(q1, q2, -1.17f));
    BOOST_CHECK_EQUAL(qqs_tern.getC2(), Functor::applyC2(q1, q2, -1.17f));
    BOOST_CHECK_EQUAL(qqs_tern.getC3(), Functor::applyC3(q1, q2, -1.17f));
    BOOST_CHECK_EQUAL(qqs_tern.getC4(), Functor::applyC4(q1, q2, -1.17f));
}

BOOST_AUTO_TEST_CASE(Scalar13QuaternionTernaryTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Scalar13QuaternionTernary<double, Quaternion<char>, float, 
                      Scalar13QuaternionTernaryTestFunctor<long, int, short> >::ValueType) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar13QuaternionTernary<double, Quaternion<short>, int, 
                      Scalar13QuaternionTernaryTestFunctor<long, char, float> >::ConstReference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar13QuaternionTernary<double, Quaternion<int>, char, 
                      Scalar13QuaternionTernaryTestFunctor<long, short, float> >::Reference) ==
                      typeid(const long));
    BOOST_CHECK(typeid(Scalar13QuaternionTernary<float, Quaternion<float>, short, 
                      Scalar13QuaternionTernaryTestFunctor<long double, int, char> >::ValueType) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar13QuaternionTernary<float, Quaternion<double>, unsigned int, 
                      Scalar13QuaternionTernaryTestFunctor<long double, char, short> >::ConstReference) ==
                      typeid(const long double));
    BOOST_CHECK(typeid(Scalar13QuaternionTernary<float, Quaternion<long>, unsigned char, 
                      Scalar13QuaternionTernaryTestFunctor<long double, short, double> >::Reference) ==
                      typeid(const long double));

    // ----------

    typedef Scalar13QuaternionTernaryTestFunctor<long double, const int&, const float&> Functor;

    Quaternion<double> q(50.2, 0.23, 24.23, -22.0);
    Scalar13QuaternionTernary<int, Quaternion<double>, float, Functor> sqs_tern(103, q, -1.17f);

    BOOST_CHECK_EQUAL(sqs_tern.getC1(), Functor::applyC1(103, q, -1.17f));
    BOOST_CHECK_EQUAL(sqs_tern.getC2(), Functor::applyC2(103, q, -1.17f));
    BOOST_CHECK_EQUAL(sqs_tern.getC3(), Functor::applyC3(103, q, -1.17f));
    BOOST_CHECK_EQUAL(sqs_tern.getC4(), Functor::applyC4(103, q, -1.17f));
}

BOOST_AUTO_TEST_CASE(QuaternionMinusTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionMinusOperator(Quaternion<int>(0));
    checkQuaternionMinusOperator(Quaternion<int>(5));
    checkQuaternionMinusOperator(Quaternion<int>(5, -3));
    checkQuaternionMinusOperator(Quaternion<int>(-25, -23, 27));
    checkQuaternionMinusOperator(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionMinusOperator(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionMinusOperator(RealQuaternion<float>(0));
    checkQuaternionMinusOperator(RealQuaternion<float>(-2.34245f));
    checkQuaternionMinusOperator(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionMinusOperator(Quaternion<double>(0));
    checkQuaternionMinusOperator(Quaternion<double>(-2.34245));
    checkQuaternionMinusOperator(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionMinusOperator(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionMinusOperator(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionPlusTest)
{
    using namespace CDPL;
    using namespace Math;
    
    checkQuaternionPlusOperator(Quaternion<int>(0));
    checkQuaternionPlusOperator(Quaternion<int>(5));
    checkQuaternionPlusOperator(Quaternion<int>(5, -3));
    checkQuaternionPlusOperator(Quaternion<int>(-25, -23, 27));
    checkQuaternionPlusOperator(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionPlusOperator(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionPlusOperator(RealQuaternion<float>(0));
    checkQuaternionPlusOperator(RealQuaternion<float>(-2.34245f));
    checkQuaternionPlusOperator(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionPlusOperator(Quaternion<double>(0));
    checkQuaternionPlusOperator(Quaternion<double>(-2.34245));
    checkQuaternionPlusOperator(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionPlusOperator(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionPlusOperator(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionAdditionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionAddition(RealQuaternion<float>(-3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionAddition(RealQuaternion<int>(-25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionAddition(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), RealQuaternion<int>(-25));
    checkQuaternionAddition(Quaternion<int>(1, 2, 3, 4), RealQuaternion<float>(-3.1f));

    // ----------

    checkQuaternionAddition(Quaternion<float>(0, 0, -3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionAddition(Quaternion<int>(0, -25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionAddition(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(0, 0, 0, -25));
    checkQuaternionAddition(Quaternion<int>(1, 2, 3, 4), Quaternion<float>(-3.1f));

    checkQuaternionAddition(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(25, 23, 31, -2));
    checkQuaternionAddition(Quaternion<int>(1, 2, 33, 4), Quaternion<float>(-3.1f, -12.3f, 2.2f, 0.03f));

    checkQuaternionAddition(Quaternion<double>(42.4245, 0.0, -2.01, 0.0), Quaternion<int>(0.0, -30.0, 0.0, 6.0));

    // ----------

    checkQuaternionAddition(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                              std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
                            Quaternion<double>(42.4245, -20.0, -0.0001, 1.234));
    checkQuaternionAddition(Quaternion<double>(242.4245, 320.0, 0.70001, 14.234),
                            Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                              std::complex<double>(11.17, -22.15), std::complex<double>(-3.1, -1.25)));
    checkQuaternionAddition(Quaternion<std::complex<double> >(std::complex<double>(7.2, 34.5), std::complex<double>(-6.16, -74.5), 
                                                              std::complex<double>(0.0, -22.15), std::complex<double>(63.1, -1.15)),
                            Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(35.16, -14.5), 
                                                              std::complex<double>(13.17, 2.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionScalarAdditionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionScalarAddition(Quaternion<double>(0), int(-4));
    checkQuaternionScalarAddition(Quaternion<int>(5), 4.27);
    checkQuaternionScalarAddition(Quaternion<double>(5, -3), -25.778985f);
    checkQuaternionScalarAddition(Quaternion<float>(3, 23, -22, 1), 0.3);
    checkQuaternionScalarAddition(Quaternion<int>(3, 0, 0, -2), int(15));
    checkQuaternionScalarAddition(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

    // ----------

    checkQuaternionScalarAddition(RealQuaternion<int>(0), 1.12);
    checkQuaternionScalarAddition(RealQuaternion<float>(-2.34245f), 16.66f);
    checkQuaternionScalarAddition(RealQuaternion<double>(42.4245f), int(-51));
    checkQuaternionScalarAddition(RealQuaternion<double>(42.4245f), short(0));

    // ----------

    checkQuaternionScalarAddition(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
    checkQuaternionScalarAddition(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
    checkQuaternionScalarAddition(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                    std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15),
                                                                    std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
}

BOOST_AUTO_TEST_CASE(ScalarQuaternionAdditionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkScalarQuaternionAddition(int(-4), Quaternion<double>(0));
    checkScalarQuaternionAddition(4.27, Quaternion<int>(5));
    checkScalarQuaternionAddition(-25.778985f, Quaternion<double>(5, -3));
    checkScalarQuaternionAddition(0.3, Quaternion<float>(3, 23, -22, 1));
    checkScalarQuaternionAddition(int(15), Quaternion<int>(3, 0, 0, -2));
    checkScalarQuaternionAddition(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

    // ----------

    checkScalarQuaternionAddition(1.12, RealQuaternion<int>(0));
    checkScalarQuaternionAddition(16.66f, RealQuaternion<float>(-2.34245f));
    checkScalarQuaternionAddition(int(-51), RealQuaternion<double>(42.4245f));
    checkScalarQuaternionAddition(short(0), RealQuaternion<double>(42.4245f));

    // ----------

    checkScalarQuaternionAddition(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
    checkScalarQuaternionAddition(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                          std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
    checkScalarQuaternionAddition(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                                                         std::complex<double>(15.16, -14.5), 
                                                                                                         std::complex<double>(11.17, 22.15),
                                                                                                         std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionSubtractionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionSubtraction(RealQuaternion<float>(-3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionSubtraction(RealQuaternion<int>(-25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionSubtraction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), RealQuaternion<int>(-25));
    checkQuaternionSubtraction(Quaternion<int>(1, 2, 3, 4), RealQuaternion<float>(-3.1f));

    // ----------

    checkQuaternionSubtraction(Quaternion<float>(0, 0, -3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionSubtraction(Quaternion<int>(0, -25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionSubtraction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(0, 0, 0, -25));
    checkQuaternionSubtraction(Quaternion<int>(1, 2, 3, 4), Quaternion<float>(-3.1f));

    checkQuaternionSubtraction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(25, 23, 31, -2));
    checkQuaternionSubtraction(Quaternion<int>(1, 2, 33, 4), Quaternion<float>(-3.1f, -12.3f, 2.2f, 0.03f));

    checkQuaternionSubtraction(Quaternion<double>(42.4245, 0.0, -2.01, 0.0), Quaternion<int>(0.0, -30.0, 0.0, 6.0));

    // ----------

    checkQuaternionSubtraction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
                               Quaternion<double>(42.4245, -20.0, -0.0001, 1.234));
    checkQuaternionSubtraction(Quaternion<double>(242.4245, 320.0, 0.70001, 14.234),
                               Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                 std::complex<double>(11.17, -22.15), std::complex<double>(-3.1, -1.25)));
    checkQuaternionSubtraction(Quaternion<std::complex<double> >(std::complex<double>(7.2, 34.5), std::complex<double>(-6.16, -74.5), 
                                                                 std::complex<double>(0.0, -22.15), std::complex<double>(63.1, -1.15)),
                               Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(35.16, -14.5), 
                                                                 std::complex<double>(13.17, 2.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionScalarSubtractionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionScalarSubtraction(Quaternion<double>(0), int(-4));
    checkQuaternionScalarSubtraction(Quaternion<int>(5), 4.27);
    checkQuaternionScalarSubtraction(Quaternion<double>(5, -3), -25.778985f);
    checkQuaternionScalarSubtraction(Quaternion<float>(3, 23, -22, 1), 0.3);
    checkQuaternionScalarSubtraction(Quaternion<int>(3, 0, 0, -2), int(15));
    checkQuaternionScalarSubtraction(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

    // ----------

    checkQuaternionScalarSubtraction(RealQuaternion<int>(0), 1.12);
    checkQuaternionScalarSubtraction(RealQuaternion<float>(-2.34245f), 16.66f);
    checkQuaternionScalarSubtraction(RealQuaternion<double>(42.4245f), int(-51));
    checkQuaternionScalarSubtraction(RealQuaternion<double>(42.4245f), short(0));

    // ----------

    checkQuaternionScalarSubtraction(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
    checkQuaternionScalarSubtraction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                       std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
    checkQuaternionScalarSubtraction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                       std::complex<double>(15.16, -14.5), 
                                                                       std::complex<double>(11.17, 22.15),
                                                                       std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
}

BOOST_AUTO_TEST_CASE(ScalarQuaternionSubtractionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkScalarQuaternionSubtraction(int(-4), Quaternion<double>(0));
    checkScalarQuaternionSubtraction(4.27, Quaternion<int>(5));
    checkScalarQuaternionSubtraction(-25.778985f, Quaternion<double>(5, -3));
    checkScalarQuaternionSubtraction(0.3, Quaternion<float>(3, 23, -22, 1));
    checkScalarQuaternionSubtraction(int(15), Quaternion<int>(3, 0, 0, -2));
    checkScalarQuaternionSubtraction(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

    // ----------

    checkScalarQuaternionSubtraction(1.12, RealQuaternion<int>(0));
    checkScalarQuaternionSubtraction(16.66f, RealQuaternion<float>(-2.34245f));
    checkScalarQuaternionSubtraction(int(-51), RealQuaternion<double>(42.4245f));
    checkScalarQuaternionSubtraction(short(0), RealQuaternion<double>(42.4245f));

    // ----------

    checkScalarQuaternionSubtraction(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
    checkScalarQuaternionSubtraction(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                             std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
    checkScalarQuaternionSubtraction(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                                                            std::complex<double>(15.16, -14.5), 
                                                                                                            std::complex<double>(11.17, 22.15),
                                                                                                            std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionMultiplicationTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionMultiplication(Quaternion<double>(0), Quaternion<int>(5));
    checkQuaternionMultiplication(Quaternion<int>(5), Quaternion<double>(5, -3));
    checkQuaternionMultiplication(Quaternion<double>(5, -3), Quaternion<float>(3, 23, -22, 1));
    checkQuaternionMultiplication(Quaternion<float>(3, 23, -22, 1), Quaternion<int>(3, 0, 0, -2));
    checkQuaternionMultiplication(Quaternion<int>(3, 0, 0, -2), Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionMultiplication(Quaternion<double>(-233, 100.23, -5.5555, -2), RealQuaternion<double>(42.4245));

    // ----------

    checkQuaternionMultiplication(RealQuaternion<int>(0), Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionMultiplication(RealQuaternion<float>(-2.34245f), RealQuaternion<double>(42.4245));
    checkQuaternionMultiplication(RealQuaternion<double>(42.4245), RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)));
    checkQuaternionMultiplication(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), RealQuaternion<double>(42.4245));

    // ----------

    checkQuaternionMultiplication(Quaternion<int>(-25, -23, 27), Quaternion<std::complex<int> >(std::complex<int>(-17, 5)));
    checkQuaternionMultiplication(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
                                  Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionMultiplication(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                    std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15),
                                                                    std::complex<double>(-3.1, -1.25)),
                                  Quaternion<std::complex<double> >(std::complex<double>(17.2, 54.5),
                                                                    std::complex<double>(0.0, -14.5), 
                                                                    std::complex<double>(11.17, 0.15),
                                                                    std::complex<double>(-33.1, 1.25)));
    // ----------

    Quaternion<double> q1(1, 0, 1, 0);
    Quaternion<double> q2(1, 0.5, 0.5, 0.75);

    BOOST_CHECK_CLOSE((q1 * q2).getC1(), 0.5, 0.0000001);
    BOOST_CHECK_CLOSE((q1 * q2).getC2(), 1.25, 0.0000001);
    BOOST_CHECK_CLOSE((q1 * q2).getC3(), 1.5, 0.0000001);
    BOOST_CHECK_CLOSE((q1 * q2).getC4(), 0.25, 0.0000001);

    BOOST_CHECK_CLOSE(operator*(q1, q2).getC1(), 0.5, 0.0000001);
    BOOST_CHECK_CLOSE(operator*(q1, q2).getC2(), 1.25, 0.0000001);
    BOOST_CHECK_CLOSE(operator*(q1, q2).getC3(), 1.5, 0.0000001);
    BOOST_CHECK_CLOSE(operator*(q1, q2).getC4(), 0.25, 0.0000001);
}

BOOST_AUTO_TEST_CASE(QuaternionScalarMultiplicationTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionScalarMultiplication(Quaternion<double>(0), int(-4));
    checkQuaternionScalarMultiplication(Quaternion<int>(5), 4.27);
    checkQuaternionScalarMultiplication(Quaternion<double>(5, -3), -25.778985f);
    checkQuaternionScalarMultiplication(Quaternion<float>(3, 23, -22, 1), 0.3);
    checkQuaternionScalarMultiplication(Quaternion<int>(3, 0, 0, -2), int(15));
    checkQuaternionScalarMultiplication(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);

    // ----------

    checkQuaternionScalarMultiplication(RealQuaternion<int>(0), 1.12);
    checkQuaternionScalarMultiplication(RealQuaternion<float>(-2.34245f), 16.66f);
    checkQuaternionScalarMultiplication(RealQuaternion<double>(42.4245f), int(-51));
    checkQuaternionScalarMultiplication(RealQuaternion<double>(42.4245f), short(0));

    // ----------

    checkQuaternionScalarMultiplication(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
    checkQuaternionScalarMultiplication(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                          std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
    checkQuaternionScalarMultiplication(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                          std::complex<double>(15.16, -14.5), 
                                                                          std::complex<double>(11.17, 22.15),
                                                                          std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
    // ----------

    BOOST_CHECK_EQUAL(Quaternion<double>(-233, 100.23, -5.5555, -2) * RealQuaternion<double>(5.2354), Quaternion<double>(-233, 100.23, -5.5555, -2) * 5.2354);
}

BOOST_AUTO_TEST_CASE(ScalarQuaternionMultiplicationTest)
{
    using namespace CDPL;
    using namespace Math;

    checkScalarQuaternionMultiplication(int(-4), Quaternion<double>(0));
    checkScalarQuaternionMultiplication(4.27, Quaternion<int>(5));
    checkScalarQuaternionMultiplication(-25.778985f, Quaternion<double>(5, -3));
    checkScalarQuaternionMultiplication(0.3, Quaternion<float>(3, 23, -22, 1));
    checkScalarQuaternionMultiplication(int(15), Quaternion<int>(3, 0, 0, -2));
    checkScalarQuaternionMultiplication(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

    // ----------

    checkScalarQuaternionMultiplication(1.12, RealQuaternion<int>(0));
    checkScalarQuaternionMultiplication(16.66f, RealQuaternion<float>(-2.34245f));
    checkScalarQuaternionMultiplication(int(-51), RealQuaternion<double>(42.4245f));
    checkScalarQuaternionMultiplication(short(0), RealQuaternion<double>(42.4245f));

    // ----------

    checkScalarQuaternionMultiplication(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
    checkScalarQuaternionMultiplication(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                                std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
    checkScalarQuaternionMultiplication(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                                                               std::complex<double>(15.16, -14.5), 
                                                                                                               std::complex<double>(11.17, 22.15),
                                                                                                               std::complex<double>(-3.1, -1.25)));
    // ----------

    BOOST_CHECK_EQUAL(RealQuaternion<double>(5.2354) * Quaternion<double>(-233, 100.23, -5.5555, -2), 5.2354 * Quaternion<double>(-233, 100.23, -5.5555, -2));
}

BOOST_AUTO_TEST_CASE(QuaternionDivisionOperatorTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionDivision(Quaternion<double>(0), Quaternion<int>(5));
    checkQuaternionDivision(Quaternion<int>(5), Quaternion<double>(5, -3));
    checkQuaternionDivision(Quaternion<double>(5, -3), Quaternion<float>(3, 23, -22, 1));
    checkQuaternionDivision(Quaternion<float>(3, 23, -22, 1), Quaternion<int>(3, 0, 0, -2));
    checkQuaternionDivision(Quaternion<int>(3, 0, 0, -2), Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionDivision(Quaternion<double>(-233, 100.23, -5.5555, -2), RealQuaternion<double>(42.4245));

    // ----------

    checkQuaternionDivision(RealQuaternion<int>(0), Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionDivision(RealQuaternion<float>(-2.34245f), RealQuaternion<double>(42.4245));
    checkQuaternionDivision(RealQuaternion<double>(42.4245), RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)));
    checkQuaternionDivision(RealQuaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5)), RealQuaternion<double>(42.4245));

    // ----------

    checkQuaternionDivision(Quaternion<int>(-25, -23, 27), Quaternion<std::complex<int> >(std::complex<int>(-17, 5)));
    checkQuaternionDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                              std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 
                            Quaternion<double>(-233, 100.23, -5.5555, -2));
    checkQuaternionDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                              std::complex<double>(15.16, -14.5), 
                                                              std::complex<double>(11.17, 22.15),
                                                              std::complex<double>(-3.1, -1.25)),
                            Quaternion<std::complex<double> >(std::complex<double>(17.2, 54.5),
                                                              std::complex<double>(0.0, -14.5), 
                                                              std::complex<double>(11.17, 0.15),
                                                              std::complex<double>(-33.1, 1.25)));
    // ----------

    Quaternion<double> q(-1, 0.5, -0.5, 0.75);

    BOOST_CHECK_CLOSE((q / q).getC1(), 1.0, 0.0000001);
    BOOST_CHECK_SMALL((q / q).getC2(), 0.0000001);
    BOOST_CHECK_SMALL((q / q).getC3(), 0.0000001);
    BOOST_CHECK_SMALL((q / q).getC4(), 0.0000001);

    BOOST_CHECK_CLOSE(operator/(q, q).getC1(), 1.0, 0.0000001);
    BOOST_CHECK_SMALL(operator/(q, q).getC2(), 0.0000001);
    BOOST_CHECK_SMALL(operator/(q, q).getC3(), 0.0000001);
    BOOST_CHECK_SMALL(operator/(q, q).getC4(), 0.0000001);
}

BOOST_AUTO_TEST_CASE(QuaternionScalarDivisionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionScalarDivision(Quaternion<double>(0), int(-4));
    checkQuaternionScalarDivision(Quaternion<int>(5), 4.27);
    checkQuaternionScalarDivision(Quaternion<double>(5, -3), -25.778985f);
    checkQuaternionScalarDivision(Quaternion<float>(3, 23, -22, 1), 0.3);
    checkQuaternionScalarDivision(Quaternion<int>(3, 0, 0, -2), int(15));
    checkQuaternionScalarDivision(Quaternion<double>(-233, 100.23, -5.5555, -2), -37.77);
    checkQuaternionScalarDivision(Quaternion<double>(-233, 100.23, -5.5555, -2), 0);

    // ----------

    checkQuaternionScalarDivision(RealQuaternion<int>(0), 1.12);
    checkQuaternionScalarDivision(RealQuaternion<float>(-2.34245f), 16.66f);
    checkQuaternionScalarDivision(RealQuaternion<double>(42.4245f), int(-51));
    checkQuaternionScalarDivision(RealQuaternion<double>(42.4245f), short(230));

    // ----------

    checkQuaternionScalarDivision(Quaternion<int>(-25, -23, 27), std::complex<int>(-3, 1));
    checkQuaternionScalarDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)), 12.2);
    checkQuaternionScalarDivision(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                    std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15),
                                                                    std::complex<double>(-3.1, -1.25)), std::complex<double>(17.2, -4.5001));
    // ----------

    Quaternion<double> q(-233, 100.23, -5.5555, -2);
    double t = -5.2354;
    RealQuaternion<double> rq(t); 

    BOOST_CHECK_CLOSE((q / rq).getC1(), (q / t).getC1(), 0.0000001);
    BOOST_CHECK_CLOSE((q / rq).getC2(), (q / t).getC2(), 0.0000001);
    BOOST_CHECK_CLOSE((q / rq).getC3(), (q / t).getC3(), 0.0000001);
    BOOST_CHECK_CLOSE((q / rq).getC4(), (q / t).getC4(), 0.0000001);

    BOOST_CHECK_CLOSE(operator/(q, rq).getC1(), operator/(q, t).getC1(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(q, rq).getC2(), operator/(q, t).getC2(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(q, rq).getC3(), operator/(q, t).getC3(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(q, rq).getC4(), operator/(q, t).getC4(), 0.0000001);
}

BOOST_AUTO_TEST_CASE(ScalarQuaternionDivisionOperatorTest)
{
    using namespace CDPL;
    using namespace Math;

    checkScalarQuaternionDivision(int(0), Quaternion<double>(-5.3));
    checkScalarQuaternionDivision(4.27, Quaternion<int>(5));
    checkScalarQuaternionDivision(-25.778985f, Quaternion<double>(5, -3));
    checkScalarQuaternionDivision(0.3, Quaternion<float>(3, 23, -22, 1));
    checkScalarQuaternionDivision(int(15), Quaternion<int>(3, 0, 0, -2));
    checkScalarQuaternionDivision(-37.77, Quaternion<double>(-233, 100.23, -5.5555, -2));

    // ----------

    checkScalarQuaternionDivision(1.12, RealQuaternion<int>(23));
    checkScalarQuaternionDivision(16.66f, RealQuaternion<float>(-2.34245f));
    checkScalarQuaternionDivision(int(-51), RealQuaternion<double>(42.4245f));
    checkScalarQuaternionDivision(short(0), RealQuaternion<double>(42.4245f));

    // ----------

    checkScalarQuaternionDivision(std::complex<int>(-3, 1), Quaternion<int>(-25, -23, 27));
    checkScalarQuaternionDivision(12.2, Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                          std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
    checkScalarQuaternionDivision(std::complex<double>(17.2, -4.5001), Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5),
                                                                                                         std::complex<double>(15.16, -14.5), 
                                                                                                         std::complex<double>(11.17, 22.15),
                                                                                                         std::complex<double>(-3.1, -1.25)));
    // ----------

    Quaternion<double> q(-233, 100.23, -5.5555, -2);
    double t = -5.2354;
    RealQuaternion<double> rq(t); 

    BOOST_CHECK_CLOSE((rq / q).getC1(), (t / q).getC1(), 0.0000001);
    BOOST_CHECK_CLOSE((rq / q).getC2(), (t / q).getC2(), 0.0000001);
    BOOST_CHECK_CLOSE((rq / q).getC3(), (t / q).getC3(), 0.0000001);
    BOOST_CHECK_CLOSE((rq / q).getC4(), (t / q).getC4(), 0.0000001);

    BOOST_CHECK_CLOSE(operator/(rq, q).getC1(), operator/(t, q).getC1(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(rq, q).getC2(), operator/(t, q).getC2(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(rq, q).getC3(), operator/(t, q).getC3(), 0.0000001);
    BOOST_CHECK_CLOSE(operator/(rq, q).getC4(), operator/(t, q).getC4(), 0.0000001);
}

BOOST_AUTO_TEST_CASE(QuaternionEqualTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(Quaternion<int>(0) == RealQuaternion<float>());
    BOOST_CHECK_EQUAL(Quaternion<int>(0) == RealQuaternion<float>(), operator==(Quaternion<int>(0), RealQuaternion<float>()));

    BOOST_CHECK(RealQuaternion<double>(0) == Quaternion<float>(0));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(0) == Quaternion<float>(0), operator==(RealQuaternion<double>(0), Quaternion<float>(0)));
    
    BOOST_CHECK(Quaternion<int>(3) == RealQuaternion<float>(3));
    BOOST_CHECK_EQUAL(Quaternion<int>(3) == RealQuaternion<float>(3), operator==(Quaternion<int>(3), RealQuaternion<float>(3)));

    BOOST_CHECK(RealQuaternion<double>(-2) == Quaternion<float>(-2));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(-2) == Quaternion<float>(-2), operator==(RealQuaternion<double>(-2), Quaternion<float>(-2)));

    BOOST_CHECK(!(Quaternion<float>(2) == RealQuaternion<float>(3)));
    BOOST_CHECK_EQUAL(Quaternion<float>(2) == RealQuaternion<float>(3), operator==(Quaternion<float>(2), RealQuaternion<float>(3)));

    BOOST_CHECK(!(RealQuaternion<double>(5) == Quaternion<float>(5, 2)));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(5) == Quaternion<float>(5, 2), operator==(RealQuaternion<double>(5), Quaternion<float>(5, 2)));
    
    // ----------

    Quaternion<int> q1(0);
    Quaternion<double> q2(0);

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q1.getC1() = -2;

    BOOST_CHECK(!(q1 == q2));
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(!(q2 == q1));
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q2.getC1() = -2;

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    // ----------

    q1.getC4() = 5;

    BOOST_CHECK(!(q1 == q2));
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(!(q2 == q1));
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q2.getC4() = 5;

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    // ----------

    q1.getC3() = -6;

    BOOST_CHECK(!(q1 == q2));
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(!(q2 == q1));
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q2.getC3() = -6;

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    // ----------

    q1.getC2() = 15;

    BOOST_CHECK(!(q1 == q2));
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(!(q2 == q1));
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q2.getC2() = 15;

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    // ----------

    q1.getC4() = -15;

    BOOST_CHECK(!(q1 == q2));
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(!(q2 == q1));
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    q2.getC4() = -15;

    BOOST_CHECK(q1 == q2);
    BOOST_CHECK_EQUAL(q1 == q2, operator==(q1, q2));

    BOOST_CHECK(q2 == q1);
    BOOST_CHECK_EQUAL(q2 == q1, operator==(q2, q1));

    // ----------

    BOOST_CHECK(Quaternion<double>(0.1, -0.2, 2, 3) == Quaternion<double>(0.1, -0.2, 2, 3));
    BOOST_CHECK_EQUAL(Quaternion<double>(0.1, -0.2, 2, 3) == Quaternion<double>(0.1, -0.2, 2, 3), 
                      operator==(Quaternion<double>(0.1, -0.2, 2, 3), Quaternion<double>(0.1, -0.2, 2, 3)));

    BOOST_CHECK(!(Quaternion<double>(0.1, -0.2, 2, 3) == Quaternion<double>(0.1, -0.2, 2, 3.00001)));
    BOOST_CHECK_EQUAL(Quaternion<double>(0.1, -0.2, 2, 3) == Quaternion<double>(0.1, -0.2, 2, 3.00001),
                      operator==(Quaternion<double>(0.1, -0.2, 2, 3), Quaternion<double>(0.1, -0.2, 2, 3.00001)));
}

BOOST_AUTO_TEST_CASE(QuaternionNotEqualTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(!(Quaternion<int>(0) != RealQuaternion<float>()));
    BOOST_CHECK_EQUAL(Quaternion<int>(0) != RealQuaternion<float>(), operator!=(Quaternion<int>(0), RealQuaternion<float>()));

    BOOST_CHECK(!(RealQuaternion<double>(0) != Quaternion<float>(0)));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(0) != Quaternion<float>(0), operator!=(RealQuaternion<double>(0), Quaternion<float>(0)));
    
    BOOST_CHECK(!(Quaternion<int>(3) != RealQuaternion<float>(3)));
    BOOST_CHECK_EQUAL(Quaternion<int>(3) != RealQuaternion<float>(3), operator!=(Quaternion<int>(3), RealQuaternion<float>(3)));

    BOOST_CHECK(!(RealQuaternion<double>(-2) != Quaternion<float>(-2)));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(-2) != Quaternion<float>(-2), operator!=(RealQuaternion<double>(-2), Quaternion<float>(-2)));

    BOOST_CHECK(Quaternion<float>(2) != RealQuaternion<float>(3));
    BOOST_CHECK_EQUAL(Quaternion<float>(2) != RealQuaternion<float>(3), operator!=(Quaternion<float>(2), RealQuaternion<float>(3)));

    BOOST_CHECK(RealQuaternion<double>(5) != Quaternion<float>(5, 2));
    BOOST_CHECK_EQUAL(RealQuaternion<double>(5) != Quaternion<float>(5, 2), operator!=(RealQuaternion<double>(5), Quaternion<float>(5, 2)));
    
    // ----------

    Quaternion<int> q1(0);
    Quaternion<double> q2(0);

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q1.getC1() = -2;

    BOOST_CHECK(q1 != q2);
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(q2 != q1);
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q2.getC1() = -2;

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    // ----------

    q1.getC4() = 5;

    BOOST_CHECK(q1 != q2);
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(q2 != q1);
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q2.getC4() = 5;

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    // ----------

    q1.getC3() = -6;

    BOOST_CHECK(q1 != q2);
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(q2 != q1);
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q2.getC3() = -6;

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    // ----------

    q1.getC2() = 15;

    BOOST_CHECK(q1 != q2);
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(q2 != q1);
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q2.getC2() = 15;

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    // ----------

    q1.getC4() = -15;

    BOOST_CHECK(q1 != q2);
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(q2 != q1);
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    q2.getC4() = -15;

    BOOST_CHECK(!(q1 != q2));
    BOOST_CHECK_EQUAL(q1 != q2, operator!=(q1, q2));

    BOOST_CHECK(!(q2 != q1));
    BOOST_CHECK_EQUAL(q2 != q1, operator!=(q2, q1));

    // ----------

    BOOST_CHECK(!(Quaternion<double>(0.1, -0.2, 2, 3) != Quaternion<double>(0.1, -0.2, 2, 3)));
    BOOST_CHECK_EQUAL(Quaternion<double>(0.1, -0.2, 2, 3) != Quaternion<double>(0.1, -0.2, 2, 3), 
                      operator!=(Quaternion<double>(0.1, -0.2, 2, 3), Quaternion<double>(0.1, -0.2, 2, 3)));

    BOOST_CHECK(Quaternion<double>(0.1, -0.2, 2, 3) != Quaternion<double>(0.1, -0.2, 2, 3.00001));
    BOOST_CHECK_EQUAL(Quaternion<double>(0.1, -0.2, 2, 3) != Quaternion<double>(0.1, -0.2, 2, 3.00001),
                      operator!=(Quaternion<double>(0.1, -0.2, 2, 3), Quaternion<double>(0.1, -0.2, 2, 3.00001)));
}

BOOST_AUTO_TEST_CASE(QuaternionEqualsFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(equals(RealQuaternion<int>(0), Quaternion<float>(0), 0));
    BOOST_CHECK(equals(Quaternion<int>(3), RealQuaternion<float>(3), 0.0));
    BOOST_CHECK(equals(Quaternion<int>(3), RealQuaternion<float>(3), 2.23));

    BOOST_CHECK(!equals(Quaternion<double>(3.01), RealQuaternion<float>(3), 0));
    BOOST_CHECK(equals(Quaternion<double>(3.01, 0.002), RealQuaternion<float>(3), 0.01));
    BOOST_CHECK(!equals(Quaternion<double>(3.01, 0.002), RealQuaternion<float>(3), 0.009));

    // ----------

    Quaternion<int> q1(1, -2, 3, 4);
    Quaternion<double> q2(0);

    BOOST_CHECK(!equals(q1, q2, 0.0f));
    BOOST_CHECK(!equals(q2, q1, 0.0f));

    BOOST_CHECK(!equals(q1, q2, 3.9999f));
    BOOST_CHECK(!equals(q2, q1, 3.9999));

    BOOST_CHECK(equals(q1, q2, 4.0f));
    BOOST_CHECK(equals(q2, q1, 4));
    BOOST_CHECK(!equals(q2, q1, -4));

    q2.getC4() = 4;

    BOOST_CHECK(!equals(q1, q2, 0.0f));
    BOOST_CHECK(!equals(q2, q1, 0.0f));

    BOOST_CHECK(!equals(q1, q2, 2.9999));
    BOOST_CHECK(!equals(q2, q1, 2.9999L));

    BOOST_CHECK(equals(q1, q2, 3.0));
    BOOST_CHECK(equals(q2, q1, 3));
    BOOST_CHECK(!equals(q2, q1, -3));

    q2.getC3() = 3;

    BOOST_CHECK(!equals(q1, q2, 0.0f));
    BOOST_CHECK(!equals(q2, q1, 0.0f));

    BOOST_CHECK(!equals(q1, q2, 1.9999f));
    BOOST_CHECK(!equals(q2, q1, 1.9999));

    BOOST_CHECK(equals(q1, q2, 2));
    BOOST_CHECK(equals(q2, q1, 2.0f));
    BOOST_CHECK(!equals(q2, q1, -2.0f));

    q2.getC2() = -2;

    BOOST_CHECK(!equals(q1, q2, 0.0f));
    BOOST_CHECK(!equals(q2, q1, 0.0f));

    BOOST_CHECK(!equals(q1, q2, 0.9999));
    BOOST_CHECK(!equals(q2, q1, 0.9999L));

    BOOST_CHECK(equals(q1, q2, 1));
    BOOST_CHECK(equals(q2, q1, 1.0));
    BOOST_CHECK(!equals(q2, q1, -1.0));

    q2.getC1() = 1;

    BOOST_CHECK(equals(q1, q2, 0.0f));
    BOOST_CHECK(equals(q2, q1, 0));
    BOOST_CHECK(equals(q1, q2, 0.000001));
    BOOST_CHECK(!equals(q1, q2, -0.000001));

    // ----------

    q2.getC1() = -1;

    BOOST_CHECK(!equals(q1, q2, 0.0f));
    BOOST_CHECK(!equals(q2, q1, 0));
    BOOST_CHECK(!equals(q1, q2, 1.0f));
    BOOST_CHECK(!equals(q2, q1, 1));
    BOOST_CHECK(!equals(q1, q2, 1.99f));
    BOOST_CHECK(!equals(q2, q1, 1));
    BOOST_CHECK(equals(q1, q2, 2.0f));
    BOOST_CHECK(equals(q2, q1, 2));
}

BOOST_AUTO_TEST_CASE(QuaternionElemDivFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionElemDivFunction(RealQuaternion<float>(-3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionElemDivFunction(RealQuaternion<int>(-25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionElemDivFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), RealQuaternion<int>(-25));
    checkQuaternionElemDivFunction(Quaternion<int>(1, 2, 3, 4), RealQuaternion<float>(-3.1f));

    // ----------

    checkQuaternionElemDivFunction(Quaternion<float>(0, 0, -3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionElemDivFunction(Quaternion<int>(0, -25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionElemDivFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(0, 0, 0, -25));
    checkQuaternionElemDivFunction(Quaternion<int>(1, 2, 3, 4), Quaternion<float>(-3.1f));

    checkQuaternionElemDivFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(25, 23, 31, -2));
    checkQuaternionElemDivFunction(Quaternion<int>(1, 2, 33, 4), Quaternion<float>(-3.1f, -12.3f, 2.2f, 0.03f));

    checkQuaternionElemDivFunction(Quaternion<double>(42.4245, 0.0, -2.01, 0.0), Quaternion<int>(0.0, -30.0, 0.0, 6.0));

    // ----------

    checkQuaternionElemDivFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                     std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
                                   Quaternion<double>(42.4245, -20.0, -0.0001, 1.234));
    checkQuaternionElemDivFunction(Quaternion<double>(242.4245, 320.0, 0.70001, 14.234),
                                   Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                     std::complex<double>(11.17, -22.15), std::complex<double>(-3.1, -1.25)));
    checkQuaternionElemDivFunction(Quaternion<std::complex<double> >(std::complex<double>(7.2, 34.5), std::complex<double>(-6.16, -74.5), 
                                                                     std::complex<double>(0.0, -22.15), std::complex<double>(63.1, -1.15)),
                                   Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(35.16, -14.5), 
                                                                     std::complex<double>(13.17, 2.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionElemProdFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionElemProdFunction(RealQuaternion<float>(-3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionElemProdFunction(RealQuaternion<int>(-25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionElemProdFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), RealQuaternion<int>(-25));
    checkQuaternionElemProdFunction(Quaternion<int>(1, 2, 3, 4), RealQuaternion<float>(-3.1f));

    // ----------

    checkQuaternionElemProdFunction(Quaternion<float>(0, 0, -3.1f), Quaternion<int>(1, 2, 3, 4));
    checkQuaternionElemProdFunction(Quaternion<int>(0, -25), Quaternion<double>(42.4245, -20.0, 0.0001, 1.234));

    checkQuaternionElemProdFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(0, 0, 0, -25));
    checkQuaternionElemProdFunction(Quaternion<int>(1, 2, 3, 4), Quaternion<float>(-3.1f));

    checkQuaternionElemProdFunction(Quaternion<double>(42.4245, -20.0, 0.0001, 1.234), Quaternion<int>(25, 23, 31, -2));
    checkQuaternionElemProdFunction(Quaternion<int>(1, 2, 33, 4), Quaternion<float>(-3.1f, -12.3f, 2.2f, 0.03f));

    checkQuaternionElemProdFunction(Quaternion<double>(42.4245, 0.0, -2.01, 0.0), Quaternion<int>(0.0, -30.0, 0.0, 6.0));

    // ----------

    checkQuaternionElemProdFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                     std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)),
                                    Quaternion<double>(42.4245, -20.0, -0.0001, 1.234));
    checkQuaternionElemProdFunction(Quaternion<double>(242.4245, 320.0, 0.70001, 14.234),
                                    Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                     std::complex<double>(11.17, -22.15), std::complex<double>(-3.1, -1.25)));
    checkQuaternionElemProdFunction(Quaternion<std::complex<double> >(std::complex<double>(7.2, 34.5), std::complex<double>(-6.16, -74.5), 
                                                                     std::complex<double>(0.0, -22.15), std::complex<double>(63.1, -1.15)),
                                    Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(35.16, -14.5), 
                                                                     std::complex<double>(13.17, 2.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionRealFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK_EQUAL(real(Quaternion<int>(0)), int(0));
    BOOST_CHECK_EQUAL(real(Quaternion<int>(5)), int(5));
    BOOST_CHECK_EQUAL(real(Quaternion<int>(5, -3)), int(5));
    BOOST_CHECK_EQUAL(real(Quaternion<int>(-25, -23, 27)), int(-25));
    BOOST_CHECK_EQUAL(real(Quaternion<int>(3, 23, -22, 1)), int(3));
    BOOST_CHECK_EQUAL(real(Quaternion<int>(3, 0, 0, -2)), int(3));

    // ----------

    BOOST_CHECK_EQUAL(real(RealQuaternion<float>(0)), 0.0f);
    BOOST_CHECK_EQUAL(real(RealQuaternion<float>(-2.34245f)), -2.34245f);
    BOOST_CHECK_EQUAL(real(RealQuaternion<float>(42.4245f)), 42.4245f);

    // ----------

    BOOST_CHECK_EQUAL(real(Quaternion<double>(0)), 0.0);
    BOOST_CHECK_EQUAL(real(Quaternion<double>(-2.34245)), -2.34245);
    BOOST_CHECK_EQUAL(real(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234)), 42.4245);
    BOOST_CHECK_EQUAL(real(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223)), 2.4245);

    // ----------

    BOOST_CHECK_EQUAL(real(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                             std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25))),
                      std::complex<double>(-17.2, 4.5));
}

BOOST_AUTO_TEST_CASE(QuaternionUnrealFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionUnrealFunction(Quaternion<int>(0));
    checkQuaternionUnrealFunction(Quaternion<int>(5));
    checkQuaternionUnrealFunction(Quaternion<int>(5, -3));
    checkQuaternionUnrealFunction(Quaternion<int>(-25, -23, 27));
    checkQuaternionUnrealFunction(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionUnrealFunction(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionUnrealFunction(RealQuaternion<float>(0));
    checkQuaternionUnrealFunction(RealQuaternion<float>(-2.34245f));
    checkQuaternionUnrealFunction(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionUnrealFunction(Quaternion<double>(0));
    checkQuaternionUnrealFunction(Quaternion<double>(-2.34245));
    checkQuaternionUnrealFunction(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionUnrealFunction(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionUnrealFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                    std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionConjFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionConjFunction(Quaternion<int>(0));
    checkQuaternionConjFunction(Quaternion<int>(5));
    checkQuaternionConjFunction(Quaternion<int>(5, -3));
    checkQuaternionConjFunction(Quaternion<int>(-25, -23, 27));
    checkQuaternionConjFunction(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionConjFunction(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionConjFunction(RealQuaternion<float>(0));
    checkQuaternionConjFunction(RealQuaternion<float>(-2.34245f));
    checkQuaternionConjFunction(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionConjFunction(Quaternion<double>(0));
    checkQuaternionConjFunction(Quaternion<double>(-2.34245));
    checkQuaternionConjFunction(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionConjFunction(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionConjFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionInvFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionInvFunction(Quaternion<int>(4));
    checkQuaternionInvFunction(Quaternion<int>(5, 0, 5));
    checkQuaternionInvFunction(Quaternion<int>(5, -3));
    checkQuaternionInvFunction(Quaternion<int>(-25, -23, 27));
    checkQuaternionInvFunction(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionInvFunction(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionInvFunction(RealQuaternion<float>(22.2f));
    checkQuaternionInvFunction(RealQuaternion<float>(-2.34245f));
    checkQuaternionInvFunction(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionInvFunction(Quaternion<double>(5.23));
    checkQuaternionInvFunction(Quaternion<double>(-2.34245));
    checkQuaternionInvFunction(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionInvFunction(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionInvFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                 std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionNormFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionNormFunction(Quaternion<int>(0));
    checkQuaternionNormFunction(Quaternion<int>(5));
    checkQuaternionNormFunction(Quaternion<int>(5, -3));
    checkQuaternionNormFunction(Quaternion<int>(-25, -23, 27));
    checkQuaternionNormFunction(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionNormFunction(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionNormFunction(RealQuaternion<float>(0));
    checkQuaternionNormFunction(RealQuaternion<float>(-2.34245f));
    checkQuaternionNormFunction(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionNormFunction(Quaternion<double>(0));
    checkQuaternionNormFunction(Quaternion<double>(-2.34245));
    checkQuaternionNormFunction(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionNormFunction(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionNormFunction(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                  std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionNorm2FunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    checkQuaternionNorm2Function(Quaternion<int>(0));
    checkQuaternionNorm2Function(Quaternion<int>(5));
    checkQuaternionNorm2Function(Quaternion<int>(5, -3));
    checkQuaternionNorm2Function(Quaternion<int>(-25, -23, 27));
    checkQuaternionNorm2Function(Quaternion<int>(3, 23, -22, 1));
    checkQuaternionNorm2Function(Quaternion<int>(3, 0, 0, -2));

    // ----------

    checkQuaternionNorm2Function(RealQuaternion<float>(0));
    checkQuaternionNorm2Function(RealQuaternion<float>(-2.34245f));
    checkQuaternionNorm2Function(RealQuaternion<float>(42.4245f));

    // ----------

    checkQuaternionNorm2Function(Quaternion<double>(0));
    checkQuaternionNorm2Function(Quaternion<double>(-2.34245));
    checkQuaternionNorm2Function(Quaternion<double>(42.4245, 0.0, 0.0001, 1.234));
    checkQuaternionNorm2Function(Quaternion<double>(2.4245, 1.23, 5.27, -2.2223));

    // ----------

    checkQuaternionNorm2Function(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                                   std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25)));
}

BOOST_AUTO_TEST_CASE(QuaternionSumFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK_EQUAL(sum(Quaternion<double>(0)), 0.0 + 0.0 + 0.0 + 0.0);

    BOOST_CHECK_EQUAL(sum(Quaternion<float>(1.123f)), 1.123f + 0.0f + 0.0f + 0.0f);

    BOOST_CHECK_EQUAL(sum(RealQuaternion<double>(0)), 0.0 + 0.0 + 0.0 + 0.0);

    BOOST_CHECK_EQUAL(sum(RealQuaternion<double>(-2.1234)), -2.1234 + 0.0 + 0.0 + 0.0);

    BOOST_CHECK_EQUAL(sum(Quaternion<int>(-1, 2, -3)), -1 + 2 + -3 + 0);

    BOOST_CHECK_EQUAL(sum(Quaternion<double>(1.2, 2.345, -15.67, 20.111)), 1.2 + 2.345 + -15.67 + 20.111);

    BOOST_CHECK_EQUAL(sum(Quaternion<float>(-100.2f, 40.0f, 50.2f, 10.0f)), -100.2f + 40.0f + 50.2f + 10.0f);

    // ----------

    BOOST_CHECK_EQUAL(sum(Quaternion<std::complex<double> >(std::complex<double>(-17.2, 4.5), std::complex<double>(15.16, -14.5), 
                                                            std::complex<double>(11.17, 22.15), std::complex<double>(-3.1, -1.25))),
                      std::complex<double>(-17.2, 4.5) + std::complex<double>(15.16, -14.5) +
                      std::complex<double>(11.17, 22.15) + std::complex<double>(-3.1, -1.25));    
}
