/* 
 * MatrixExpression.hpp 
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
 * \brief Definition of various matrix expression types and operations.
 */

#ifndef CDPL_MATH_MATRIXEXPRESSION_HPP
#define CDPL_MATH_MATRIXEXPRESSION_HPP

#include <type_traits>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename C>
        class VectorContainer;
        template <typename C>
        class MatrixContainer;

        template <typename E, typename F>
        class MatrixUnary : public MatrixExpression<MatrixUnary<E, F> >
        {

            typedef MatrixUnary<E, F>            SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            typedef typename F::ResultType     ValueType;
            typedef const ValueType            ConstReference;
            typedef const ValueType            Reference;
            typedef const SelfType             ConstClosureType;
            typedef SelfType                   ClosureType;
            typedef typename E::SizeType       SizeType;
            typedef typename E::DifferenceType DifferenceType;

            MatrixUnary(const ExpressionType& e):
                expr(e) {}

            SizeType getSize1() const
            {
                return expr.getSize1();
            }

            SizeType getSize2() const
            {
                return expr.getSize2();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr(i, j));
            }

          private:
            ExpressionClosureType expr;
        };

        template <typename E, typename F>
        struct MatrixUnaryTraits
        {

            typedef MatrixUnary<E, F> ExpressionType;
            typedef ExpressionType    ResultType;
        };

        template <typename E, typename F>
        class VectorMatrixUnary : public MatrixExpression<VectorMatrixUnary<E, F> >
        {

            typedef VectorMatrixUnary<E, F>      SelfType;
            typedef F                            FunctorType;
            typedef E                            ExpressionType;
            typedef typename E::ConstClosureType ExpressionClosureType;

          public:
            typedef typename F::ResultType     ValueType;
            typedef const ValueType            ConstReference;
            typedef const ValueType            Reference;
            typedef const SelfType             ConstClosureType;
            typedef SelfType                   ClosureType;
            typedef typename E::SizeType       SizeType;
            typedef typename E::DifferenceType DifferenceType;

            VectorMatrixUnary(const ExpressionType& e):
                expr(e) {}

            SizeType getSize1() const
            {
                return expr.getSize();
            }

            SizeType getSize2() const
            {
                return expr.getSize();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr, i, j);
            }

          private:
            ExpressionClosureType expr;
        };

        template <typename E, typename F>
        struct VectorMatrixUnaryTraits
        {

            typedef VectorMatrixUnary<E, F> ExpressionType;
            typedef ExpressionType          ResultType;
        };

        template <typename E1, typename E2, typename F>
        class MatrixBinary1 : public MatrixExpression<MatrixBinary1<E1, E2, F> >
        {

            typedef MatrixBinary1<E1, E2, F>      SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            typedef typename F::ResultType                                                              ValueType;
            typedef const ValueType                                                                     ConstReference;
            typedef const ValueType                                                                     Reference;
            typedef const SelfType                                                                      ConstClosureType;
            typedef SelfType                                                                            ClosureType;
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            MatrixBinary1(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize1() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize1()), SizeType(expr2.getSize1()), Base::SizeError);
            }

            SizeType getSize2() const
            {
                return CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(expr1.getSize2()), SizeType(expr2.getSize2()), Base::SizeError);
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i, j), expr2(i, j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct MatrixBinary1Traits
        {

            typedef MatrixBinary1<E1, E2, F> ExpressionType;
            typedef ExpressionType           ResultType;
        };

        template <typename E1, typename E2, typename F>
        class MatrixBinary2 : public MatrixExpression<MatrixBinary2<E1, E2, F> >
        {

            typedef MatrixBinary2<E1, E2, F>      SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            typedef typename F::ResultType                                                              ValueType;
            typedef const ValueType                                                                     ConstReference;
            typedef const ValueType                                                                     Reference;
            typedef const SelfType                                                                      ConstClosureType;
            typedef SelfType                                                                            ClosureType;
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            MatrixBinary2(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize1() const
            {
                return expr1.getSize1();
            }

            SizeType getSize2() const
            {
                return expr2.getSize2();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1, expr2, i, j);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct MatrixBinary2Traits
        {

            typedef MatrixBinary2<E1, E2, F> ExpressionType;
            typedef ExpressionType           ResultType;
        };

        template <typename E1, typename E2, typename F>
        class VectorMatrixBinary : public MatrixExpression<VectorMatrixBinary<E1, E2, F> >
        {

            typedef VectorMatrixBinary<E1, E2, F> SelfType;
            typedef F                             FunctorType;
            typedef E1                            Expression1Type;
            typedef E2                            Expression2Type;
            typedef typename E1::ConstClosureType Expression1ClosureType;
            typedef typename E2::ConstClosureType Expression2ClosureType;

          public:
            typedef typename F::ResultType                                                              ValueType;
            typedef const ValueType                                                                     ConstReference;
            typedef const ValueType                                                                     Reference;
            typedef const SelfType                                                                      ConstClosureType;
            typedef SelfType                                                                            ClosureType;
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            VectorMatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize1() const
            {
                return expr1.getSize();
            }

            SizeType getSize2() const
            {
                return expr2.getSize();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i), expr2(j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct VectorMatrixBinaryTraits
        {

            typedef VectorMatrixBinary<E1, E2, F> ExpressionType;
            typedef ExpressionType                ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Matrix1VectorBinary : public VectorExpression<Matrix1VectorBinary<E1, E2, F> >
        {

            typedef Matrix1VectorBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            typedef typename F::ResultType                                                              ValueType;
            typedef const ValueType                                                                     ConstReference;
            typedef const ValueType                                                                     Reference;
            typedef const SelfType                                                                      ConstClosureType;
            typedef SelfType                                                                            ClosureType;
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            Matrix1VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize() const
            {
                return expr1.getSize1();
            }

            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Matrix1VectorBinaryTraits
        {

            typedef Matrix1VectorBinary<E1, E2, F> ExpressionType;
            typedef ExpressionType                 ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Matrix2VectorBinary : public VectorExpression<Matrix2VectorBinary<E1, E2, F> >
        {

            typedef Matrix2VectorBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            typedef typename F::ResultType                                                              ValueType;
            typedef const ValueType                                                                     ConstReference;
            typedef const ValueType                                                                     Reference;
            typedef const SelfType                                                                      ConstClosureType;
            typedef SelfType                                                                            ClosureType;
            typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type             SizeType;
            typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;

            Matrix2VectorBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize() const
            {
                return expr2.getSize2();
            }

            ConstReference operator()(SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

            ConstReference operator[](SizeType i) const
            {
                return FunctorType::apply(expr1, expr2, i);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Matrix2VectorBinaryTraits
        {

            typedef Matrix2VectorBinary<E1, E2, F> ExpressionType;
            typedef ExpressionType                 ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Scalar1MatrixBinary : public MatrixExpression<Scalar1MatrixBinary<E1, E2, F> >
        {

            typedef Scalar1MatrixBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef const E1                       Expression1ClosureType;
            typedef typename E2::ConstClosureType  Expression2ClosureType;

          public:
            typedef typename F::ResultType      ValueType;
            typedef const ValueType             ConstReference;
            typedef const ValueType             Reference;
            typedef const SelfType              ConstClosureType;
            typedef SelfType                    ClosureType;
            typedef typename E2::SizeType       SizeType;
            typedef typename E2::DifferenceType DifferenceType;

            Scalar1MatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize1() const
            {
                return expr2.getSize1();
            }

            SizeType getSize2() const
            {
                return expr2.getSize2();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1, expr2(i, j));
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar1MatrixBinaryTraits
        {

            typedef Scalar1MatrixBinary<E1, E2, F> ExpressionType;
            typedef ExpressionType                 ResultType;
        };

        template <typename E1, typename E2, typename F>
        class Scalar2MatrixBinary : public MatrixExpression<Scalar2MatrixBinary<E1, E2, F> >
        {

            typedef Scalar2MatrixBinary<E1, E2, F> SelfType;
            typedef F                              FunctorType;
            typedef E1                             Expression1Type;
            typedef E2                             Expression2Type;
            typedef typename E1::ConstClosureType  Expression1ClosureType;
            typedef const E2                       Expression2ClosureType;

          public:
            typedef typename F::ResultType      ValueType;
            typedef const ValueType             ConstReference;
            typedef const ValueType             Reference;
            typedef const SelfType              ConstClosureType;
            typedef SelfType                    ClosureType;
            typedef typename E1::SizeType       SizeType;
            typedef typename E1::DifferenceType DifferenceType;

            Scalar2MatrixBinary(const Expression1Type& e1, const Expression2Type& e2):
                expr1(e1), expr2(e2) {}

            SizeType getSize1() const
            {
                return expr1.getSize1();
            }

            SizeType getSize2() const
            {
                return expr1.getSize2();
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return FunctorType::apply(expr1(i, j), expr2);
            }

          private:
            Expression1ClosureType expr1;
            Expression2ClosureType expr2;
        };

        template <typename E1, typename E2, typename F>
        struct Scalar2MatrixBinaryTraits
        {

            typedef Scalar2MatrixBinary<E1, E2, F> ExpressionType;
            typedef ExpressionType                 ResultType;
        };

        template <typename M>
        class MatrixTranspose : public MatrixExpression<MatrixTranspose<M> >
        {

            typedef MatrixTranspose<M> SelfType;

          public:
            typedef M                                                        MatrixType;
            typedef typename M::SizeType                                     SizeType;
            typedef typename M::DifferenceType                               DifferenceType;
            typedef typename M::ValueType                                    ValueType;
            typedef typename M::ConstReference                               ConstReference;
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstReference,
                                              typename M::Reference>::type   Reference;
            typedef typename std::conditional<std::is_const<M>::value,
                                              typename M::ConstClosureType,
                                              typename M::ClosureType>::type MatrixClosureType;
            typedef const SelfType                                           ConstClosureType;
            typedef SelfType                                                 ClosureType;

            explicit MatrixTranspose(MatrixType& m):
                data(m) {}

            Reference operator()(SizeType i, SizeType j)
            {
                return data(j, i);
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(j, i);
            }

            SizeType getSize1() const
            {
                return data.getSize2();
            }

            SizeType getSize2() const
            {
                return data.getSize1();
            }

            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            bool isEmpty() const
            {
                return (data.getSize1() == 0 || data.getSize2() == 0);
            }

            MatrixClosureType& getData()
            {
                return data;
            }

            const MatrixClosureType& getData() const
            {
                return data;
            }

            MatrixTranspose& operator=(const MatrixTranspose& mt)
            {
                data.operator=(mt.data);
                return *this;
            }

            template <typename M1>
            MatrixTranspose& operator=(const MatrixTranspose<M1>& mt)
            {
                data.operator=(mt.getData());
                return *this;
            }

            template <typename E>
            MatrixTranspose& operator=(const MatrixExpression<E>& e)
            {
                data.operator=(MatrixTranspose<const E>(e()));
                return *this;
            }

            template <typename E>
            MatrixTranspose& operator+=(const MatrixExpression<E>& e)
            {
                data.operator+=(MatrixTranspose<const E>(e()));
                return *this;
            }

            template <typename E>
            MatrixTranspose& operator-=(const MatrixExpression<E>& e)
            {
                data.operator-=(MatrixTranspose<const E>(e()));
                return *this;
            }

            template <typename T>

            typename std::enable_if<IsScalar<T>::value, MatrixTranspose>::type& operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            template <typename T>

            typename std::enable_if<IsScalar<T>::value, MatrixTranspose>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            template <typename E>
            MatrixTranspose& assign(const MatrixExpression<E>& e)
            {
                data.assign((MatrixTranspose<const E>(e())));
                return *this;
            }

            template <typename E>
            MatrixTranspose& plusAssign(const MatrixExpression<E>& e)
            {
                data.plusAssign((MatrixTranspose<const E>(e())));
                return *this;
            }

            template <typename E>
            MatrixTranspose& minusAssign(const MatrixExpression<E>& e)
            {
                data.minusAssign((MatrixTranspose<const E>(e())));
                return *this;
            }

            void swap(MatrixTranspose& mt)
            {
                data.swap(mt.data);
            }

            friend void swap(MatrixTranspose& mt1, MatrixTranspose& mt2)
            {
                mt1.swap(mt2);
            }

          private:
            MatrixClosureType data;
        };

        template <typename M>
        struct VectorTemporaryTraits<MatrixTranspose<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<const MatrixTranspose<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<MatrixTranspose<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<const MatrixTranspose<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename E>
        typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ResultType
        operator-(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarNegation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        const E&
        operator+(const MatrixExpression<E>& e)
        {
            return e();
        }

        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator+(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarAddition<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ResultType
        operator-(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarSubtraction<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2MatrixBinaryTraits<E, T, ScalarMultiplication<typename E::ValueType, T> >::ResultType>::type
        operator*(const MatrixExpression<E>& e, const T& t)
        {
            typedef typename Scalar2MatrixBinaryTraits<E, T,
                                                       ScalarMultiplication<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        template <typename T, typename E>
        typename std::enable_if<IsScalar<T>::value, typename Scalar1MatrixBinaryTraits<T, E, ScalarMultiplication<T, typename E::ValueType> >::ResultType>::type
        operator*(const T& t, const MatrixExpression<E>& e)
        {
            typedef typename Scalar1MatrixBinaryTraits<T, E,
                                                       ScalarMultiplication<T, typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(t, e());
        }

        template <typename E, typename T>
        typename std::enable_if<IsScalar<T>::value, typename Scalar2MatrixBinaryTraits<E, T, ScalarDivision<typename E::ValueType, T> >::ResultType>::type
        operator/(const MatrixExpression<E>& e, const T& t)
        {
            typedef typename Scalar2MatrixBinaryTraits<E, T,
                                                       ScalarDivision<typename E::ValueType, T> >::ExpressionType ExpressionType;

            return ExpressionType(e(), t);
        }

        template <typename E1, typename E2>
        typename MatrixEquality<E1, E2>::ResultType
        operator==(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            return MatrixEquality<E1, E2>::apply(e1, e2);
        }

        template <typename E1, typename E2>
        typename MatrixEquality<E1, E2>::ResultType
        operator!=(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            return !MatrixEquality<E1, E2>::apply(e1, e2);
        }

        template <typename E1, typename E2, typename T>
        typename std::enable_if<std::is_arithmetic<T>::value, typename MatrixToleranceEquality<E1, E2, T>::ResultType>::type
        equals(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, const T& eps)
        {
            return MatrixToleranceEquality<E1, E2, T>::apply(e1, e2, eps);
        }

        template <typename E>
        typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        conj(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ResultType
        herm(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarConjugation<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ResultType
        real(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarReal<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ResultType
        imag(const MatrixExpression<E>& e)
        {
            typedef typename MatrixUnaryTraits<E, ScalarImaginary<typename E::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E1, typename E2>
        typename VectorMatrixBinaryTraits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        outerProd(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename VectorMatrixBinaryTraits<E1, E2,
                                                      ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemDiv(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarDivision<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename MatrixBinary1Traits<E1, E2, ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ResultType
        elemProd(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary1Traits<E1, E2,
                                                 ScalarMultiplication<typename E1::ValueType, typename E2::ValueType> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType
        operator*(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ResultType
        prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2)
        {
            typedef typename Matrix1VectorBinaryTraits<E1, E2, MatrixVectorProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename C, typename E1, typename E2>
        C& prod(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2, VectorContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        template <typename E1, typename E2>
        typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType
        operator*(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ResultType
        prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename Matrix2VectorBinaryTraits<E1, E2, VectorMatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename C, typename E1, typename E2>
        C& prod(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2, VectorContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        template <typename E1, typename E2>
        typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType
        operator*(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename E1, typename E2>
        typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ResultType
        prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2)
        {
            typedef typename MatrixBinary2Traits<E1, E2, MatrixProduct<E1, E2> >::ExpressionType ExpressionType;

            return ExpressionType(e1(), e2());
        }

        template <typename C, typename E1, typename E2>
        C& prod(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, MatrixContainer<C>& c)
        {
            return c().assign(prod(e1, e2));
        }

        template <typename E>
        typename MatrixTrace<E>::ResultType
        trace(const MatrixExpression<E>& e)
        {
            return MatrixTrace<E>::apply(e);
        }

        template <typename E>
        typename MatrixNorm1<E>::ResultType
        norm1(const MatrixExpression<E>& e)
        {
            return MatrixNorm1<E>::apply(e);
        }

        template <typename E>
        typename MatrixNormFrobenius<E>::ResultType
        normFrob(const MatrixExpression<E>& e)
        {
            return MatrixNormFrobenius<E>::apply(e);
        }

        template <typename E>
        typename MatrixNormInfinity<E>::ResultType
        normInf(const MatrixExpression<E>& e)
        {
            return MatrixNormInfinity<E>::apply(e);
        }

        template <typename E>
        typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ResultType
        diag(const VectorExpression<E>& e)
        {
            typedef typename VectorMatrixUnaryTraits<E, DiagonalMatrixFromVector<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ResultType
        cross(const VectorExpression<E>& e)
        {
            typedef typename VectorMatrixUnaryTraits<E, CrossProductMatrixFromVector<E> >::ExpressionType ExpressionType;

            return ExpressionType(e());
        }

        template <typename E>
        MatrixTranspose<E> trans(MatrixExpression<E>& e)
        {
            return MatrixTranspose<E>(e());
        }

        template <typename E>
        MatrixTranspose<const E> trans(const MatrixExpression<E>& e)
        {
            return MatrixTranspose<const E>(e());
        }

        template <typename E>
        typename MatrixElementSum<E>::ResultType
        sum(const MatrixExpression<E>& e)
        {
            return MatrixElementSum<E>::apply(e);
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXEXPRESSION_HPP
