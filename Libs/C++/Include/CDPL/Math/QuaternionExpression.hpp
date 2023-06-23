/* 
 * QuaternionExpression.hpp 
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
 * \brief Definition of various quaternion expression types and operations.
 */

#ifndef CDPL_MATH_QUATERNIONEXPRESSION_HPP
#define CDPL_MATH_QUATERNIONEXPRESSION_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename E, typename F>
        class QuaternionUnary1 : public QuaternionExpression<QuaternionUnary1<E, F> >
        {

            typedef QuaternionUnary1<E, F> SelfType;
            typedef F FunctorType;
            typedef E ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            QuaternionUnary1(const ExpressionType& e): expr(e) {}

            ConstReference getC1() const {
                return FunctorType::apply(expr.getC1());
            }

            ConstReference getC2() const {
                return FunctorType::apply(expr.getC2());
            }
    
            ConstReference getC3() const {
                return FunctorType::apply(expr.getC3());
            }

            ConstReference getC4() const {
                return FunctorType::apply(expr.getC4());
            }

        private:
            ExpressionClosureType expr;
        };

        template <typename E, typename F>
        struct QuaternionUnary1Traits
        {

            typedef QuaternionUnary1<E, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E, typename F>
        class QuaternionUnary2 : public QuaternionExpression<QuaternionUnary2<E, F> >
        {

            typedef QuaternionUnary2<E, F> SelfType;
            typedef F FunctorType;
            typedef E ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            QuaternionUnary2(const ExpressionType& e): expr(e) {}

            ConstReference getC1() const {
                return FunctorType::applyC1(expr);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr);
            }

        private:
            ExpressionClosureType expr;
        };

        template <typename E, typename F>
        struct QuaternionUnary2Traits
        {

            typedef QuaternionUnary2<E, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename F>
        class QuaternionBinary1 : public QuaternionExpression<QuaternionBinary1<E1, E2, F> >
        {

            typedef QuaternionBinary1<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;

            QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}
        
            ConstReference getC1() const {
                return FunctorType::apply(expr1.getC1(), expr2.getC1());
            }

            ConstReference getC2() const {
                return FunctorType::apply(expr1.getC2(), expr2.getC2());
            }
    
            ConstReference getC3() const {
                return FunctorType::apply(expr1.getC3(), expr2.getC3());
            }

            ConstReference getC4() const {
                return FunctorType::apply(expr1.getC4(), expr2.getC4());
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct QuaternionBinary1Traits
        {

            typedef QuaternionBinary1<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename F>
        class QuaternionBinary2 : public QuaternionExpression<QuaternionBinary2<E1, E2, F> >
        {

            typedef QuaternionBinary2<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;

            QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}
        
            ConstReference getC1() const {
                return FunctorType::applyC1(expr1, expr2);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr1, expr2);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr1, expr2);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr1, expr2);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct QuaternionBinary2Traits
        {

            typedef QuaternionBinary2<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Scalar1QuaternionBinary1 : public QuaternionExpression<Scalar1QuaternionBinary1<E1, E2, F> >
        {

            typedef Scalar1QuaternionBinary1<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef const E1 Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar1QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

            ConstReference getC1() const {
                return FunctorType::apply(expr1, expr2.getC1());
            }

            ConstReference getC2() const {
                return FunctorType::apply(expr1, expr2.getC2());
            }
    
            ConstReference getC3() const {
                return FunctorType::apply(expr1, expr2.getC3());
            }

            ConstReference getC4() const {
                return FunctorType::apply(expr1, expr2.getC4());
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar1QuaternionBinary1Traits
        {

            typedef Scalar1QuaternionBinary1<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };
    
        template <typename E1, typename E2, typename F>
        class Scalar1QuaternionBinary2 : public QuaternionExpression<Scalar1QuaternionBinary2<E1, E2, F> >
        {

            typedef Scalar1QuaternionBinary2<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef const E1 Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar1QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

            ConstReference getC1() const {
                return FunctorType::applyC1(expr1, expr2);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr1, expr2);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr1, expr2);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr1, expr2);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar1QuaternionBinary2Traits
        {

            typedef Scalar1QuaternionBinary2<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Scalar2QuaternionBinary1 : public QuaternionExpression<Scalar2QuaternionBinary1<E1, E2, F> >
        {

            typedef Scalar2QuaternionBinary1<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef const E2 Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar2QuaternionBinary1(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

            ConstReference getC1() const {
                return FunctorType::apply(expr1.getC1(), expr2);
            }

            ConstReference getC2() const {
                return FunctorType::apply(expr1.getC2(), expr2);
            }
    
            ConstReference getC3() const {
                return FunctorType::apply(expr1.getC3(), expr2);
            }

            ConstReference getC4() const {
                return FunctorType::apply(expr1.getC4(), expr2);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar2QuaternionBinary1Traits
        {

            typedef Scalar2QuaternionBinary1<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Scalar2QuaternionBinary2 : public QuaternionExpression<Scalar2QuaternionBinary2<E1, E2, F> >
        {

            typedef Scalar2QuaternionBinary2<E1, E2, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef const E2 Expression2ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar2QuaternionBinary2(const Expression1Type& e1, const Expression2Type& e2): expr1(e1), expr2(e2) {}

            ConstReference getC1() const {
                return FunctorType::applyC1(expr1, expr2);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr1, expr2);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr1, expr2);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr1, expr2);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar2QuaternionBinary2Traits
        {

            typedef Scalar2QuaternionBinary2<E1, E2, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E1, typename E2, typename E3, typename F>
        class Scalar3QuaternionTernary : public QuaternionExpression<Scalar3QuaternionTernary<E1, E2, E3, F> >
        {

            typedef Scalar3QuaternionTernary<E1, E2, E3, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef E3 Expression3Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;
            typedef const E3 Expression3ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar3QuaternionTernary(const Expression1Type& e1, const Expression2Type& e2, const Expression3Type& e3):
                expr1(e1), expr2(e2), expr3(e3) {}

            ConstReference getC1() const {
                return FunctorType::applyC1(expr1, expr2, expr3);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr1, expr2, expr3);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr1, expr2, expr3);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr1, expr2, expr3);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
            Expression3ClosureType expr3;
        };

        template <typename E1, typename E2, typename E3, typename F>
        struct Scalar3QuaternionTernaryTraits
        {

            typedef Scalar3QuaternionTernary<E1, E2, E3, F> ExpressionType;
            typedef ExpressionType ResultType;
        };
    
        template <typename E1, typename E2, typename E3, typename F>
        class Scalar13QuaternionTernary : public QuaternionExpression<Scalar13QuaternionTernary<E1, E2, E3, F> >
        {

            typedef Scalar13QuaternionTernary<E1, E2, E3, F> SelfType;
            typedef F FunctorType;
            typedef E1 Expression1Type;
            typedef E2 Expression2Type;
            typedef E3 Expression3Type;
            typedef const E1 Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;
            typedef const E3 Expression3ClosureType;

        public:
            typedef typename F::ResultType ValueType;
            typedef const ValueType ConstReference;
            typedef const ValueType Reference;
            typedef const SelfType ConstClosureType;
            typedef SelfType ClosureType;
        
            Scalar13QuaternionTernary(const Expression1Type& e1, const Expression2Type& e2, const Expression3Type& e3):
                expr1(e1), expr2(e2), expr3(e3) {}

            ConstReference getC1() const {
                return FunctorType::applyC1(expr1, expr2, expr3);
            }

            ConstReference getC2() const {
                return FunctorType::applyC2(expr1, expr2, expr3);
            }
    
            ConstReference getC3() const {
                return FunctorType::applyC3(expr1, expr2, expr3);
            }

            ConstReference getC4() const {
                return FunctorType::applyC4(expr1, expr2, expr3);
            }

        private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
            Expression3ClosureType expr3;
        };

        template <typename E1, typename E2, typename E3, typename F>
        struct Scalar13QuaternionTernaryTraits
        {

            typedef Scalar13QuaternionTernary<E1, E2, E3, F> ExpressionType;
            typedef ExpressionType ResultType;
        };

        template <typename E>        
        typename QuaternionUnary1Traits<E, ScalarNegation<typename E::ValueType> >::ResultType 
        operator-(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary1Traits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }
    
        template <typename E>
        const E& 
        operator+(const QuaternionExpression<E>& e)
        {
            return e();
        }

        template <typename E1, typename E2>        
        typename QuaternionBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType 
        operator+(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }
    
        template <typename E, typename T>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionAddition<E, T> >::ResultType>::type
        operator+(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionAddition<E, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        template <typename T, typename E>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionAddition<T, E> >::ResultType>::type
        operator+(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionAddition<T, E> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        template <typename E1, typename E2>        
        typename QuaternionBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType 
        operator-(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E, typename T>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionSubtraction<E, T> >::ResultType>::type
        operator-(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, T, Scalar2QuaternionSubtraction<E, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        template <typename T, typename E>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionSubtraction<T, E> >::ResultType>::type
        operator-(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary2Traits<T, E, Scalar1QuaternionSubtraction<T, E> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        template <typename E1, typename E2>        
        typename QuaternionBinary2Traits<E1, E2, QuaternionProduct<E1, E2> >::ResultType 
        operator*(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary2Traits<E1, E2, QuaternionProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E, typename T>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary1Traits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary1Traits<E, T,
                ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        template <typename T, typename E>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar1QuaternionBinary1Traits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type 
        operator*(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar1QuaternionBinary1Traits<T, E,
                ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        template <typename E1, typename E2>        
        typename Scalar3QuaternionTernaryTraits<E1, E2, typename QuaternionNorm2<E2>::ResultType, 
                                                QuaternionDivision<E1, E2, typename QuaternionNorm2<E2>::ResultType> >::ResultType 
        operator/(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename Scalar3QuaternionTernaryTraits<E1, E2, typename QuaternionNorm2<E2>::ResultType, 
                QuaternionDivision<E1, E2, typename QuaternionNorm2<E2>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2(), norm2(e2));
        }
        
        template <typename E, typename T>        
        typename std::enable_if<IsScalar<T>::value, typename Scalar2QuaternionBinary1Traits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const QuaternionExpression<E>& e, const T& t)
        {
            typedef typename Scalar2QuaternionBinary1Traits<E, T,
                ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }
        
        template <typename T, typename E>        
        typename std::enable_if<IsScalar<T>::value, 
                                  typename Scalar13QuaternionTernaryTraits<T, E, typename QuaternionNorm2<E>::ResultType, 
                                                                           ScalarQuaternionDivision<T, E, typename QuaternionNorm2<E>::ResultType> >::ResultType>::type
        operator/(const T& t, const QuaternionExpression<E>& e)
        {
            typedef typename Scalar13QuaternionTernaryTraits<T, E, typename QuaternionNorm2<E>::ResultType, 
                                                             ScalarQuaternionDivision<T, E, typename QuaternionNorm2<E>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e(), norm2(e));
        }

        template <typename E1, typename E2>        
        typename QuaternionEquality<E1, E2>::ResultType
        operator==(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            return QuaternionEquality<E1, E2>::apply(e1, e2);
        }

        template <typename E1, typename E2>        
        typename QuaternionEquality<E1, E2>::ResultType
        operator!=(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            return !QuaternionEquality<E1, E2>::apply(e1, e2);
        }

        template <typename E1, typename E2, typename T>        
        typename std::enable_if<std::is_arithmetic<T>::value, typename QuaternionToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, const T& eps)
        {
            return QuaternionToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        template <typename E1, typename E2>        
        typename QuaternionBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType 
        elemDiv(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>        
        typename QuaternionBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType 
        elemProd(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
        {
            typedef typename QuaternionBinary1Traits<E1, E2,
                ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E>        
        typename E::ValueType 
        real(const QuaternionExpression<E>& e)
        {
            return e().getC1();
        }

        template <typename E>        
        typename QuaternionUnary2Traits<E, QuaternionUnreal<E> >::ResultType 
        unreal(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary2Traits<E, QuaternionUnreal<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>        
        typename QuaternionUnary2Traits<E, QuaternionConjugate<E> >::ResultType 
        conj(const QuaternionExpression<E>& e)
        {
            typedef typename QuaternionUnary2Traits<E, QuaternionConjugate<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }
    
        template <typename E>        
        typename Scalar2QuaternionBinary2Traits<E, typename QuaternionNorm2<E>::ResultType, 
                                                QuaternionInverse<E, typename QuaternionNorm2<E>::ResultType> >::ResultType 
        inv(const QuaternionExpression<E>& e)
        {
            typedef typename Scalar2QuaternionBinary2Traits<E, typename QuaternionNorm2<E>::ResultType, 
                QuaternionInverse<E, typename QuaternionNorm2<E>::ResultType> >::ExpressionType ExpressionType;

            return ExpressionType(e(), norm2(e));
        }
        
        template <typename E>        
        typename QuaternionNorm<E>::ResultType 
        norm(const QuaternionExpression<E>& e)
        {
            return QuaternionNorm<E>::apply(e);
        }

        template <typename E>        
        typename QuaternionNorm2<E>::ResultType 
        norm2(const QuaternionExpression<E>& e)
        {
            return QuaternionNorm2<E>::apply(e);
        }

        template <typename E>        
        typename QuaternionElementSum<E>::ResultType
        sum(const QuaternionExpression<E>& e)
        {
            return QuaternionElementSum<E>::apply(e);
        }
    }
}

#endif // CDPL_MATH_QUATERNIONEXPRESSION_HPP
