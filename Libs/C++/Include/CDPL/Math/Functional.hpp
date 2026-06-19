/* 
 * Functional.hpp 
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
 * \brief Definition of various functors.
 */

#ifndef CDPL_MATH_FUNCTIONAL_HPP
#define CDPL_MATH_FUNCTIONAL_HPP

#include <boost/algorithm/clamp.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename E>
        class VectorExpression;
        template <typename E>
        class MatrixExpression;
        template <typename E>
        class QuaternionExpression;
        template <typename E>
        class GridExpression;

        /**
         * \brief %Base class for binary in-place assignment functors of the form <tt>F::apply(T1, const T2&)</tt>.
         *
         * Derived functors (Math::ScalarAssignment, Math::ScalarAdditionAssignment, Math::ScalarSubtractionAssignment,
         * Math::ScalarMultiplicationAssignment, Math::ScalarDivisionAssignment) implement the element-wise update of a
         * destination scalar with a source scalar.
         *
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarBinaryAssignmentFunctor
        {

            /**
             * \brief The (modifiable) first argument type.
             */
            typedef T1        Argument1Type;

            /**
             * \brief The second (source) argument type.
             */
            typedef const T2& Argument2Type;
        };

        /**
         * \brief Scalar plain-assignment functor: <tt>apply(t1, t2)</tt> performs <tt>t1 = t2</tt>.
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
        {

            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

            /**
             * \brief Performs <tt>t1 = t2</tt>.
             * \param t1 The destination scalar.
             * \param t2 The source scalar.
             */
            static void apply(Argument1Type t1, Argument2Type t2)
            {
                t1 = t2;
            }
        };

        /**
         * \brief Scalar in-place addition functor: <tt>apply(t1, t2)</tt> performs <tt>t1 += t2</tt>.
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarAdditionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
        {

            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

            /**
             * \brief Performs <tt>t1 += t2</tt>.
             * \param t1 The destination scalar.
             * \param t2 The summand.
             */
            static void apply(Argument1Type t1, Argument2Type t2)
            {
                t1 += t2;
            }
        };

        /**
         * \brief Scalar in-place subtraction functor: <tt>apply(t1, t2)</tt> performs <tt>t1 -= t2</tt>.
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarSubtractionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
        {

            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

            /**
             * \brief Performs <tt>t1 -= t2</tt>.
             * \param t1 The destination scalar.
             * \param t2 The subtrahend.
             */
            static void apply(Argument1Type t1, Argument2Type t2)
            {
                t1 -= t2;
            }
        };

        /**
         * \brief Scalar in-place multiplication functor: <tt>apply(t1, t2)</tt> performs <tt>t1 *= t2</tt>.
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarMultiplicationAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
        {

            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

            /**
             * \brief Performs <tt>t1 *= t2</tt>.
             * \param t1 The destination scalar.
             * \param t2 The multiplier.
             */
            static void apply(Argument1Type t1, Argument2Type t2)
            {
                t1 *= t2;
            }
        };

        /**
         * \brief Scalar in-place division functor: <tt>apply(t1, t2)</tt> performs <tt>t1 /= t2</tt>.
         * \tparam T1 The (modifiable) destination type.
         * \tparam T2 The source type.
         */
        template <typename T1, typename T2>
        struct ScalarDivisionAssignment : public ScalarBinaryAssignmentFunctor<T1, T2>
        {

            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryAssignmentFunctor<T1, T2>::Argument2Type Argument2Type;

            /**
             * \brief Performs <tt>t1 /= t2</tt>.
             * \param t1 The destination scalar.
             * \param t2 The divisor.
             */
            static void apply(Argument1Type t1, Argument2Type t2)
            {
                t1 /= t2;
            }
        };

        /**
         * \brief %Base class for unary scalar functors of the form <tt>F::apply(const T&)</tt> returning a \a T result.
         *
         * Derived functors (Math::ScalarNegation, Math::ScalarConjugation, Math::ScalarReal, Math::ScalarImaginary)
         * implement specific element-wise operations.
         *
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarUnaryFunctor
        {

            /**
             * \brief The scalar value type.
             */
            typedef T         ValueType;

            /**
             * \brief The argument type (a \c const reference to ValueType).
             */
            typedef const T&  ArgumentType;

            /**
             * \brief The result type of apply().
             */
            typedef ValueType ResultType;
        };

        /**
         * \brief Scalar negation functor: <tt>apply(v)</tt> returns <tt>-v</tt>.
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarNegation : public ScalarUnaryFunctor<T>
        {

            typedef typename ScalarUnaryFunctor<T>::ValueType    ValueType;
            typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
            typedef typename ScalarUnaryFunctor<T>::ResultType   ResultType;

            /**
             * \brief Returns <tt>-v</tt>.
             * \param v The scalar argument.
             * \return The negated value.
             */
            static ResultType apply(ArgumentType v)
            {
                return -v;
            }
        };

        /**
         * \brief Scalar complex-conjugation functor: <tt>apply(v)</tt> returns \f$ \overline{v} \f$ (identity for real types).
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarConjugation : public ScalarUnaryFunctor<T>
        {

            typedef typename ScalarUnaryFunctor<T>::ValueType    ValueType;
            typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
            typedef typename ScalarUnaryFunctor<T>::ResultType   ResultType;

            /**
             * \brief Returns the complex conjugate of \a v.
             * \param v The scalar argument.
             * \return The complex conjugate \f$ \overline{v} \f$.
             */
            static ResultType apply(ArgumentType v)
            {
                return TypeTraits<ValueType>::conj(v);
            }
        };

        /**
         * \brief %Base class for unary scalar functors that return the real part of \a T (Math::ScalarReal, Math::ScalarImaginary).
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarRealUnaryFunctor
        {

            /**
             * \brief The scalar value type.
             */
            typedef T                                ValueType;

            /**
             * \brief The argument type (a \c const reference to ValueType).
             */
            typedef const T&                         ArgumentType;

            /**
             * \brief The real-valued result type derived from ValueType via Math::TypeTraits.
             */
            typedef typename TypeTraits<T>::RealType ResultType;
        };

        /**
         * \brief Scalar real-part functor: <tt>apply(v)</tt> returns \f$ \mathrm{Re}(v) \f$ (identity for real types).
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarReal : public ScalarRealUnaryFunctor<T>
        {

            typedef typename ScalarUnaryFunctor<T>::ValueType    ValueType;
            typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
            typedef typename ScalarUnaryFunctor<T>::ResultType   ResultType;

            /**
             * \brief Returns the real part of \a v.
             * \param v The scalar argument.
             * \return \f$ \mathrm{Re}(v) \f$.
             */
            static ResultType apply(ArgumentType v)
            {
                return TypeTraits<ValueType>::real(v);
            }
        };

        /**
         * \brief Scalar imaginary-part functor: <tt>apply(v)</tt> returns \f$ \mathrm{Im}(v) \f$ (zero for real types).
         * \tparam T The scalar value type.
         */
        template <typename T>
        struct ScalarImaginary : public ScalarRealUnaryFunctor<T>
        {

            typedef typename ScalarUnaryFunctor<T>::ValueType    ValueType;
            typedef typename ScalarUnaryFunctor<T>::ArgumentType ArgumentType;
            typedef typename ScalarUnaryFunctor<T>::ResultType   ResultType;

            /**
             * \brief Returns the imaginary part of \a v.
             * \param v The scalar argument.
             * \return \f$ \mathrm{Im}(v) \f$.
             */
            static ResultType apply(ArgumentType v)
            {
                return TypeTraits<ValueType>::imag(v);
            }
        };

        /**
         * \brief %Base class for binary scalar functors of the form <tt>F::apply(const T1&, const T2&)</tt> returning a Math::CommonType result.
         *
         * Derived functors (Math::ScalarAddition, Math::ScalarSubtraction, Math::ScalarMultiplication, Math::ScalarDivision)
         * implement specific element-wise operations.
         *
         * \tparam T1 The first argument type.
         * \tparam T2 The second argument type.
         */
        template <typename T1, typename T2>
        struct ScalarBinaryFunctor
        {

            /**
             * \brief The first argument type.
             */
            typedef const T1&                         Argument1Type;

            /**
             * \brief The second argument type.
             */
            typedef const T2&                         Argument2Type;

            /**
             * \brief The result type (common type of \a T1 and \a T2).
             */
            typedef typename CommonType<T1, T2>::Type ResultType;
        };

        /**
         * \brief Scalar binary addition functor: <tt>apply(t1, t2)</tt> returns <tt>t1 + t2</tt>.
         * \tparam T1 The first argument type.
         * \tparam T2 The second argument type.
         */
        template <typename T1, typename T2>
        struct ScalarAddition : public ScalarBinaryFunctor<T1, T2>
        {

            typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::ResultType    ResultType;

            /**
             * \brief Returns <tt>t1 + t2</tt>.
             * \param t1 The first argument.
             * \param t2 The second argument.
             * \return The sum of \a t1 and \a t2.
             */
            static ResultType apply(Argument1Type t1, Argument2Type t2)
            {
                return (t1 + t2);
            }
        };

        /**
         * \brief Scalar binary subtraction functor: <tt>apply(t1, t2)</tt> returns <tt>t1 - t2</tt>.
         * \tparam T1 The first argument type.
         * \tparam T2 The second argument type.
         */
        template <typename T1, typename T2>
        struct ScalarSubtraction : public ScalarBinaryFunctor<T1, T2>
        {

            typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::ResultType    ResultType;

            /**
             * \brief Returns <tt>t1 - t2</tt>.
             * \param t1 The minuend.
             * \param t2 The subtrahend.
             * \return The difference of \a t1 and \a t2.
             */
            static ResultType apply(Argument1Type t1, Argument2Type t2)
            {
                return (t1 - t2);
            }
        };

        /**
         * \brief Scalar binary multiplication functor: <tt>apply(t1, t2)</tt> returns <tt>t1 * t2</tt>.
         * \tparam T1 The first argument type.
         * \tparam T2 The second argument type.
         */
        template <typename T1, typename T2>
        struct ScalarMultiplication : public ScalarBinaryFunctor<T1, T2>
        {

            typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::ResultType    ResultType;

            /**
             * \brief Returns <tt>t1 * t2</tt>.
             * \param t1 The first factor.
             * \param t2 The second factor.
             * \return The product of \a t1 and \a t2.
             */
            static ResultType apply(Argument1Type t1, Argument2Type t2)
            {
                return (t1 * t2);
            }
        };

        /**
         * \brief Scalar binary division functor: <tt>apply(t1, t2)</tt> returns <tt>t1 / t2</tt>.
         * \tparam T1 The first argument type.
         * \tparam T2 The second argument type.
         */
        template <typename T1, typename T2>
        struct ScalarDivision : public ScalarBinaryFunctor<T1, T2>
        {

            typedef typename ScalarBinaryFunctor<T1, T2>::Argument1Type Argument1Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::Argument2Type Argument2Type;
            typedef typename ScalarBinaryFunctor<T1, T2>::ResultType    ResultType;

            /**
             * \brief Returns <tt>t1 / t2</tt>.
             * \param t1 The dividend.
             * \param t2 The divisor.
             * \return The quotient of \a t1 and \a t2.
             */
            static ResultType apply(Argument1Type t1, Argument2Type t2)
            {
                return (t1 / t2);
            }
        };

        /**
         * \brief %Base class for binary functors that take two vectors and return a scalar (Math::VectorInnerProduct, Math::VectorAngleCosine).
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorScalarBinaryFunctor
        {

            /**
             * \brief The scalar result type (common type of the two vector element types).
             */
            typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
        };

        /**
         * \brief Vector inner-product functor: <tt>apply(e1, e2)</tt> returns \f$ \sum_i e_1(i) \cdot e_2(i) \f$.
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorInnerProduct : public VectorScalarBinaryFunctor<V1, V2>
        {

            typedef typename VectorScalarBinaryFunctor<V1, V2>::ResultType ResultType;

            /**
             * \brief Returns the inner product of \a e1 and \a e2.
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             * \return \f$ \sum_i e_1(i) \cdot e_2(i) \f$.
             * \throw Base::SizeError if the two vector expressions differ in size.
             */
            static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2)
            {
                typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type SizeType;

                SizeType   size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize()), SizeType(e2().getSize()), Base::SizeError);
                ResultType res  = ResultType();

                for (SizeType i = 0; i < size; i++)
                    res += e1()(i) * e2()(i);

                return res;
            }
        };

        /**
         * \brief Functor returning the cosine of the angle between two vectors (optionally clamped to <tt>[-1, 1]</tt>).
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         * \tparam T The norm-product scalar type.
         */
        template <typename V1, typename V2, typename T>
        struct VectorAngleCosine : public VectorScalarBinaryFunctor<V1, V2>
        {

            typedef typename CommonType<typename VectorInnerProduct<V1, V2>::ResultType, T>::Type ResultType;

            /**
             * \brief Returns the cosine of the angle between \a e1 and \a e2.
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             * \param sd The precomputed product \f$ \|e_1\| \cdot \|e_2\| \f$ of the two vector magnitudes.
             * \param clamp If \c true, the result is clamped to the range <tt>[-1, 1]</tt>.
             * \return The (optionally clamped) cosine of the angle.
             */
            static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2, const T& sd, bool clamp)
            {
                ResultType res = VectorInnerProduct<V1, V2>::apply(e1, e2) / sd;

                if (!clamp)
                    return res;

                return boost::algorithm::clamp(res, ResultType(-1), ResultType(1));
            }
        };

        /**
         * \brief %Base class for binary functors that take two vectors and return a boolean (Math::VectorEquality and similar).
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorBooleanBinaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The unsigned size type (common type of the two vector size types).
             */
            typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type   SizeType;

            /**
             * \brief The element value type (common type of the two vector element types).
             */
            typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ValueType;
        };

        /**
         * \brief Vector equality functor: <tt>apply(e1, e2)</tt> tests element-wise equality of two vector expressions.
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorEquality : public VectorBooleanBinaryFunctor<V1, V2>
        {

            typedef typename VectorBooleanBinaryFunctor<V1, V2>::SizeType   SizeType;
            typedef typename VectorBooleanBinaryFunctor<V1, V2>::ValueType  ValueType;
            typedef typename VectorBooleanBinaryFunctor<V1, V2>::ResultType ResultType;

            /**
             * \brief Tells whether the vector expressions \a e1 and \a e2 are element-wise equal.
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             * \return \c true if both vectors have equal sizes and equal elements, and \c false otherwise.
             */
            static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2)
            {
                if (SizeType(e1().getSize()) != SizeType(e2().getSize()))
                    return false;

                for (SizeType i = 0, size = e1().getSize(); i < size; i++)
                    if (ValueType(e1()(i)) != ValueType(e2()(i)))
                        return false;

                return true;
            }
        };

        /**
         * \brief %Base class for ternary functors that take two vectors and a scalar tolerance and return a boolean (Math::VectorToleranceEquality).
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         * \tparam T The scalar tolerance type.
         */
        template <typename V1, typename V2, typename T>
        struct Scalar3VectorBooleanTernaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T&                                                                  Argument3Type;

            /**
             * \brief The unsigned size type (common type of the two vector size types).
             */
            typedef typename CommonType<typename V1::SizeType, typename V2::SizeType>::Type   SizeType;

            /**
             * \brief The element value type (common type of the two vector element types).
             */
            typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ValueType;
        };

        /**
         * \brief Vector tolerance-equality functor: <tt>apply(e1, e2, eps)</tt> tests element-wise equality within an absolute tolerance.
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         * \tparam T The scalar tolerance type.
         */
        template <typename V1, typename V2, typename T>
        struct VectorToleranceEquality : public Scalar3VectorBooleanTernaryFunctor<V1, V2, T>
        {

            typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::SizeType      SizeType;
            typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::ValueType     ValueType;
            typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::ResultType    ResultType;
            typedef typename Scalar3VectorBooleanTernaryFunctor<V1, V2, T>::Argument3Type Argument3Type;

            /**
             * \brief Tells whether the vector expressions \a e1 and \a e2 are element-wise equal within an absolute tolerance \a epsilon.
             * \param e1 The first vector expression.
             * \param e2 The second vector expression.
             * \param epsilon The non-negative absolute tolerance.
             * \return \c true if both vectors have equal sizes and corresponding elements agree within \a epsilon, and \c false otherwise.
             */
            static ResultType apply(const VectorExpression<V1>& e1, const VectorExpression<V2>& e2, Argument3Type epsilon)
            {
                typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

                if (SizeType(e1().getSize()) != SizeType(e2().getSize()))
                    return false;

                ComparisonType norm_inf_max(epsilon);

                for (SizeType i = 0, size = e1().getSize(); i < size; i++)
                    if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i) - e1()(i))) > norm_inf_max)
                        return false;

                return true;
            }
        };

        /**
         * \brief %Base class for binary functors that take two vectors and return a vector (Math::VectorCrossProduct).
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorBinaryFunctor
        {

            /**
             * \brief The element result type (common type of the two vector element types).
             */
            typedef typename CommonType<typename V1::ValueType, typename V2::ValueType>::Type ResultType;
        };

        /**
         * \brief Vector cross-product functor: <tt>apply(e1, e2, i)</tt> returns the \a i-th component of the 3D vector cross product \f$ e_1 \times e_2 \f$.
         * \tparam V1 The first vector expression type.
         * \tparam V2 The second vector expression type.
         */
        template <typename V1, typename V2>
        struct VectorCrossProduct : public VectorBinaryFunctor<V1, V2>
        {

            typedef typename VectorScalarBinaryFunctor<V1, V2>::ResultType ResultType;

            /**
             * \brief Returns the \a i-th component of the cross product \f$ e_1 \times e_2 \f$.
             * \tparam E1 The first concrete vector expression type.
             * \tparam E2 The second concrete vector expression type.
             * \tparam SizeType The component-index type.
             * \param e1 The first 3D vector expression.
             * \param e2 The second 3D vector expression.
             * \param i The zero-based component index (0, 1, or 2).
             * \return The \a i-th component of the cross product.
             * \throw Base::SizeError if either vector is not of size 3.
             */
            template <typename E1, typename E2, typename SizeType>
            static ResultType apply(const VectorExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i)
            {
                CDPL_MATH_CHECK(e1().getSize() == 3, "Invalid vector size", Base::SizeError);
                CDPL_MATH_CHECK(e2().getSize() == 3, "Invalid vector size", Base::SizeError);

                switch (i) {

                    case 0:
                        return (e1()(1) * e2()(2) - e1()(2) * e2()(1)); // c1 = a2 * b3 - a3 * b2;

                    case 1:
                        return (e1()(2) * e2()(0) - e1()(0) * e2()(2)); // c2 = a3 * b1 - a1 * b3;

                    case 2:
                        return (e1()(0) * e2()(1) - e1()(1) * e2()(0)); // c3 = a1 * b2 - a2 * b1;

                    default:
                        return ResultType();
                }
            }
        };

        /**
         * \brief %Base class for unary functors that take a vector and return a scalar (Math::VectorElementSum).
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorScalarUnaryFunctor
        {

            /**
             * \brief The scalar result type (the vector's element value type).
             */
            typedef typename V::ValueType ResultType;

            /**
             * \brief The unsigned size type used by the vector.
             */
            typedef typename V::SizeType  SizeType;
        };

        /**
         * \brief Functor returning the sum of all elements of a vector expression.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorElementSum : public VectorScalarUnaryFunctor<V>
        {

            typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;

            /**
             * \brief Returns the sum of all elements of \a e.
             * \param e The vector expression.
             * \return \f$ \sum_i e(i) \f$.
             */
            static ResultType apply(const VectorExpression<V>& e)
            {
                typedef typename V::SizeType SizeType;

                ResultType res = ResultType();

                for (SizeType i = 0, size = e().getSize(); i < size; i++)
                    res += e()(i);

                return res;
            }
        };

        template <typename V>
        /**
         * \brief %Base class for unary functors that take a vector and return a real-valued scalar (Math::VectorNorm1, Math::VectorNorm2, Math::VectorNormInfinity).
         * \tparam V The vector expression type.
         */
        struct VectorScalarRealUnaryFunctor
        {

            /**
             * \brief The vector's element value type.
             */
            typedef typename V::ValueType                    ValueType;

            /**
             * \brief The real-valued type derived from ValueType via Math::TypeTraits.
             */
            typedef typename TypeTraits<ValueType>::RealType RealType;

            /**
             * \brief The real-valued result type.
             */
            typedef RealType                                 ResultType;
        };

        /**
         * \brief Functor returning the L1 norm of a vector expression.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorNorm1 : public VectorScalarRealUnaryFunctor<V>
        {

            typedef typename VectorScalarRealUnaryFunctor<V>::ValueType  ValueType;
            typedef typename VectorScalarRealUnaryFunctor<V>::RealType   RealType;
            typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

            /**
             * \brief Returns the L1 norm of \a e.
             * \param e The vector expression.
             * \return \f$ \sum_i \|e(i)\|_1 \f$.
             */
            static ResultType apply(const VectorExpression<V>& e)
            {
                typedef typename V::SizeType SizeType;

                RealType res = RealType();

                for (SizeType i = 0, size = e().getSize(); i < size; i++)
                    res += TypeTraits<ValueType>::norm1(e()(i));

                return res;
            }
        };

        /**
         * \brief Functor returning the L2 (Euclidean) norm of a vector expression.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorNorm2 : public VectorScalarRealUnaryFunctor<V>
        {

            typedef typename VectorScalarRealUnaryFunctor<V>::ValueType  ValueType;
            typedef typename VectorScalarRealUnaryFunctor<V>::RealType   RealType;
            typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

            /**
             * \brief Returns the L2 norm of \a e.
             * \param e The vector expression.
             * \return \f$ \sqrt{\sum_i \|e(i)\|_2^2} \f$.
             */
            static ResultType apply(const VectorExpression<V>& e)
            {
                typedef typename V::SizeType SizeType;

                RealType res2 = RealType();

                for (SizeType i = 0, size = e().getSize(); i < size; i++) {
                    RealType t = TypeTraits<ValueType>::norm2(e()(i));

                    res2 += t * t;
                }

                return TypeTraits<RealType>::sqrt(res2);
            }
        };

        /**
         * \brief Functor returning the L&infin; (maximum-magnitude) norm of a vector expression.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorNormInfinity : public VectorScalarRealUnaryFunctor<V>
        {

            typedef typename VectorScalarRealUnaryFunctor<V>::ValueType  ValueType;
            typedef typename VectorScalarRealUnaryFunctor<V>::RealType   RealType;
            typedef typename VectorScalarRealUnaryFunctor<V>::ResultType ResultType;

            /**
             * \brief Returns the L&infin; norm of \a e.
             * \param e The vector expression.
             * \return \f$ \max_i \|e(i)\|_\infty \f$.
             */
            static ResultType apply(const VectorExpression<V>& e)
            {
                typedef typename V::SizeType SizeType;

                RealType res = RealType();

                for (SizeType i = 0, size = e().getSize(); i < size; i++) {
                    RealType t = TypeTraits<ValueType>::normInf(e()(i));

                    if (t > res)
                        res = t;
                }

                return res;
            }
        };

        /**
         * \brief %Base class for unary functors that take a vector and return a vector-element index (Math::VectorNormInfinityIndex).
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorScalarIndexUnaryFunctor
        {

            /**
             * \brief The vector's element value type.
             */
            typedef typename V::ValueType                    ValueType;

            /**
             * \brief The real-valued type derived from ValueType via Math::TypeTraits.
             */
            typedef typename TypeTraits<ValueType>::RealType RealType;

            /**
             * \brief The result type (the vector's size type, used for element indices).
             */
            typedef typename V::SizeType                     ResultType;
        };

        /**
         * \brief Functor returning the index of the vector element with the largest L&infin; norm.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorNormInfinityIndex : public VectorScalarIndexUnaryFunctor<V>
        {

            typedef typename VectorScalarIndexUnaryFunctor<V>::ValueType  ValueType;
            typedef typename VectorScalarIndexUnaryFunctor<V>::RealType   RealType;
            typedef typename VectorScalarIndexUnaryFunctor<V>::ResultType ResultType;

            /**
             * \brief Returns the index of the element of \a e with the largest L&infin; norm.
             * \param e The vector expression.
             * \return The zero-based index of the element \f$ \arg\max_i \|e(i)\|_\infty \f$ (0 if \a e is empty).
             */
            static ResultType apply(const VectorExpression<V>& e)
            {
                typedef typename V::SizeType SizeType;

                RealType   norm = RealType();
                ResultType res  = ResultType(0);

                for (SizeType i = 0, size = e().getSize(); i < size; i++) {
                    RealType t = TypeTraits<ValueType>::normInf(e()(i));

                    if (t > norm) {
                        norm = t;
                        res  = ResultType(i);
                    }
                }

                return res;
            }
        };

        /**
         * \brief %Base class for binary functors that take two matrix expressions and return a \c bool result (Math::MatrixEquality).
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         */
        template <typename M1, typename M2>
        struct MatrixBooleanBinaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The unsigned size type (common type of the two matrix size types).
             */
            typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type   SizeType;

            /**
             * \brief The element value type (common type of the two matrix element types).
             */
            typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking element-wise equality of two matrix expressions.
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         */
        template <typename M1, typename M2>
        struct MatrixEquality : public MatrixBooleanBinaryFunctor<M1, M2>
        {

            typedef typename MatrixBooleanBinaryFunctor<M1, M2>::SizeType   SizeType;
            typedef typename MatrixBooleanBinaryFunctor<M1, M2>::ValueType  ValueType;
            typedef typename MatrixBooleanBinaryFunctor<M1, M2>::ResultType ResultType;

            /**
             * \brief Tells whether \a e1 and \a e2 have the same dimensions and equal element values.
             * \param e1 The first matrix expression.
             * \param e2 The second matrix expression.
             * \return \c true if the matrices agree in dimensions and element-wise values, and \c false otherwise.
             */
            static ResultType apply(const MatrixExpression<M1>& e1, const MatrixExpression<M2>& e2)
            {
                if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
                    return false;

                if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
                    return false;

                for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
                    for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
                        if (ValueType(e1()(i, j)) != ValueType(e2()(i, j)))
                            return false;

                return true;
            }
        };

        /**
         * \brief %Base class for ternary functors that take two matrix expressions plus a tolerance scalar and return a \c bool result (Math::MatrixToleranceEquality).
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename M1, typename M2, typename T>
        struct Scalar3MatrixBooleanTernaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T&                                                                  Argument3Type;

            /**
             * \brief The unsigned size type (common type of the two matrix size types).
             */
            typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type   SizeType;

            /**
             * \brief The element value type (common type of the two matrix element types).
             */
            typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking element-wise approximate equality of two matrix expressions within an absolute tolerance.
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename M1, typename M2, typename T>
        struct MatrixToleranceEquality : public Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>
        {

            typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::SizeType      SizeType;
            typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::ValueType     ValueType;
            typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::ResultType    ResultType;
            typedef typename Scalar3MatrixBooleanTernaryFunctor<M1, M2, T>::Argument3Type Argument3Type;

            /**
             * \brief Tells whether \a e1 and \a e2 agree element-wise within the absolute tolerance \a epsilon.
             * \param e1 The first matrix expression.
             * \param e2 The second matrix expression.
             * \param epsilon The non-negative absolute tolerance.
             * \return \c true if the matrices have equal dimensions and all elements agree within \a epsilon, and \c false otherwise.
             */
            static ResultType apply(const MatrixExpression<M1>& e1, const MatrixExpression<M2>& e2, Argument3Type epsilon)
            {
                typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

                if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
                    return false;

                if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
                    return false;

                ComparisonType norm_inf_max(epsilon);

                for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
                    for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
                        if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i, j) - e1()(i, j))) > norm_inf_max)
                            return false;

                return true;
            }
        };

        /**
         * \brief %Base class for unary functors that take a matrix expression and return a scalar result (Math::MatrixElementSum, Math::MatrixTrace).
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixScalarUnaryFunctor
        {

            /**
             * \brief The scalar result type (the matrix's element value type).
             */
            typedef typename M::ValueType ResultType;
        };

        /**
         * \brief Functor returning the sum of all elements of a matrix expression.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixElementSum : public MatrixScalarUnaryFunctor<M>
        {

            typedef typename MatrixScalarUnaryFunctor<M>::ResultType ResultType;

            /**
             * \brief Returns the element sum of \a e.
             * \param e The matrix expression.
             * \return \f$ \sum_{i, j} e(i, j) \f$.
             */
            static ResultType apply(const MatrixExpression<M>& e)
            {
                typedef typename M::SizeType SizeType;

                ResultType res   = ResultType();
                SizeType   size1 = e().getSize1();
                SizeType   size2 = e().getSize2();

                for (SizeType i = 0; i < size1; i++)
                    for (SizeType j = 0; j < size2; j++)
                        res += e()(i, j);

                return res;
            }
        };

        /**
         * \brief Functor returning the trace (sum of diagonal entries) of a matrix expression.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixTrace : public MatrixScalarUnaryFunctor<M>
        {

            typedef typename MatrixScalarUnaryFunctor<M>::ResultType ResultType;

            /**
             * \brief Returns the trace of \a e.
             * \param e The matrix expression.
             * \return \f$ \sum_i e(i, i) \f$.
             * \throw Base::SizeError if \a e is not square.
             */
            static ResultType apply(const MatrixExpression<M>& e)
            {
                typedef typename M::SizeType SizeType;

                SizeType   size = CDPL_MATH_CHECK_SIZE_EQUALITY(e().getSize1(), e().getSize2(), Base::SizeError);
                ResultType res  = ResultType();

                for (SizeType i = 0; i < size; i++)
                    res += e()(i, i);

                return res;
            }
        };

        /**
         * \brief %Base class for unary functors that take a matrix expression and return a real-valued scalar (Math::MatrixNorm1, Math::MatrixNormFrobenius, Math::MatrixNormInfinity).
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixScalarRealUnaryFunctor
        {

            /**
             * \brief The matrix's element value type.
             */
            typedef typename M::ValueType                    ValueType;

            /**
             * \brief The real-valued type derived from ValueType via Math::TypeTraits.
             */
            typedef typename TypeTraits<ValueType>::RealType RealType;

            /**
             * \brief The real-valued result type.
             */
            typedef RealType                                 ResultType;
        };

        /**
         * \brief Functor returning the L1 (maximum absolute column sum) norm of a matrix expression.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixNorm1 : public MatrixScalarRealUnaryFunctor<M>
        {

            typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType  ValueType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::RealType   RealType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

            /**
             * \brief Returns the L1 norm of \a e.
             * \param e The matrix expression.
             * \return \f$ \max_j \sum_i \|e(i, j)\|_1 \f$.
             */
            static ResultType apply(const MatrixExpression<M>& e)
            {
                typedef typename M::SizeType SizeType;

                RealType res   = RealType();
                SizeType size1 = e().getSize1();
                SizeType size2 = e().getSize2();

                for (SizeType j = 0; j < size2; j++) {
                    RealType t = RealType();

                    for (SizeType i = 0; i < size1; i++)
                        t += TypeTraits<ValueType>::norm1(e()(i, j));

                    if (t > res)
                        res = t;
                }

                return res;
            }
        };

        /**
         * \brief Functor returning the Frobenius norm of a matrix expression.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixNormFrobenius : public MatrixScalarRealUnaryFunctor<M>
        {

            typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType  ValueType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::RealType   RealType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

            /**
             * \brief Returns the Frobenius norm of \a e.
             * \param e The matrix expression.
             * \return \f$ \sqrt{\sum_{i, j} \|e(i, j)\|_2^2} \f$.
             */
            static ResultType apply(const MatrixExpression<M>& e)
            {
                typedef typename M::SizeType SizeType;

                RealType res2  = RealType();
                SizeType size1 = e().getSize1();
                SizeType size2 = e().getSize2();

                for (SizeType i = 0; i < size1; i++) {
                    for (SizeType j = 0; j < size2; j++) {
                        RealType t = TypeTraits<ValueType>::norm2(e()(i, j));

                        res2 += t * t;
                    }
                }

                return TypeTraits<RealType>::sqrt(res2);
            }
        };

        /**
         * \brief Functor returning the L&infin; (maximum absolute row sum) norm of a matrix expression.
         * \tparam M The matrix expression type.
         */
        template <typename M>
        struct MatrixNormInfinity : public MatrixScalarRealUnaryFunctor<M>
        {

            typedef typename MatrixScalarRealUnaryFunctor<M>::ValueType  ValueType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::RealType   RealType;
            typedef typename MatrixScalarRealUnaryFunctor<M>::ResultType ResultType;

            /**
             * \brief Returns the L&infin; norm of \a e.
             * \param e The matrix expression.
             * \return \f$ \max_i \sum_j \|e(i, j)\|_\infty \f$.
             */
            static ResultType apply(const MatrixExpression<M>& e)
            {
                typedef typename M::SizeType SizeType;

                RealType res   = RealType();
                SizeType size1 = e().getSize1();
                SizeType size2 = e().getSize2();

                for (SizeType i = 0; i < size1; i++) {
                    RealType t = RealType();

                    for (SizeType j = 0; j < size2; j++)
                        t += TypeTraits<ValueType>::normInf(e()(i, j));

                    if (t > res)
                        res = t;
                }

                return res;
            }
        };

        /**
         * \brief %Base class for unary functors that produce a matrix element from a vector expression and (\e i, \e j) cell indices (Math::DiagonalMatrixFromVector, Math::CrossProductMatrixFromVector).
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct VectorMatrixUnaryFunctor
        {

            /**
             * \brief The matrix element result type (the vector's element value type).
             */
            typedef typename V::ValueType ResultType;

            /**
             * \brief The unsigned size type used by the vector.
             */
            typedef typename V::SizeType  SizeType;
        };

        /**
         * \brief Functor producing the diagonal matrix element at (\e i, \e j) from a vector expression (\f$ e(i) \f$ on the diagonal, \c 0 elsewhere).
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct DiagonalMatrixFromVector : public VectorMatrixUnaryFunctor<V>
        {

            typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;
            typedef typename VectorScalarUnaryFunctor<V>::SizeType   SizeType;

            /**
             * \brief Returns \f$ e(i) \f$ if \a i equals \a j, otherwise \c 0.
             * \tparam E The vector expression type.
             * \param e The vector expression.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The diagonal matrix element.
             */
            template <typename E>
            static ResultType apply(const VectorExpression<E>& e, SizeType i, SizeType j)
            {
                if (i == j)
                    return e()(i);

                return ResultType();
            }
        };

        /**
         * \brief Functor producing the cross-product (skew-symmetric) matrix element at (\e i, \e j) for a 3D vector expression.
         * \tparam V The vector expression type.
         */
        template <typename V>
        struct CrossProductMatrixFromVector : public VectorMatrixUnaryFunctor<V>
        {

            typedef typename VectorScalarUnaryFunctor<V>::ResultType ResultType;
            typedef typename VectorScalarUnaryFunctor<V>::SizeType   SizeType;

            /**
             * \brief Returns the (\a i, \a j) element of the skew-symmetric matrix \f$ [e]_\times \f$ corresponding to the 3D vector \a e.
             * \tparam E The vector expression type.
             * \param e The 3D vector expression.
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The corresponding element of \f$ [e]_\times \f$.
             * \throw Base::SizeError if \a e does not have size 3.
             */
            template <typename E>
            static ResultType apply(const VectorExpression<E>& e, SizeType i, SizeType j)
            {
                CDPL_MATH_CHECK(e().getSize() == 3, "Invalid vector size", Base::SizeError);

                //                       |  0  -a3  a2 |
                // cross([a1, a2, a3]) = |  a3  0  -a1 |
                //                       | -a2  a1  0  |
                switch (i) {

                    case 0:
                        switch (j) {

                            case 1:
                                return -e()(2);

                            case 2:
                                return e()(1);

                            default:
                                return ResultType();
                        }

                    case 1:
                        switch (j) {

                            case 0:
                                return e()(2);

                            case 2:
                                return -e()(0);

                            default:
                                return ResultType();
                        }

                    case 2:
                        switch (j) {

                            case 0:
                                return -e()(1);

                            case 1:
                                return e()(0);

                            default:
                                return ResultType();
                        }

                    default:
                        return ResultType();
                }
            }
        };

        /**
         * \brief %Base class for binary functors that take a matrix expression and a vector expression and return a vector element scalar result (Math::MatrixVectorProduct, Math::VectorMatrixProduct).
         * \tparam M The matrix expression type.
         * \tparam V The vector expression type.
         */
        template <typename M, typename V>
        struct MatrixVectorBinaryFunctor
        {

            /**
             * \brief The element value type (common type of the matrix and vector element types).
             */
            typedef typename CommonType<typename M::ValueType, typename V::ValueType>::Type ValueType;

            /**
             * \brief The unsigned size type (common type of the matrix and vector size types).
             */
            typedef typename CommonType<typename M::SizeType, typename V::SizeType>::Type   SizeType;

            /**
             * \brief The scalar result type (alias for ValueType).
             */
            typedef ValueType                                                               ResultType;
        };

        /**
         * \brief Functor returning element \e i of the matrix-vector product \f$ e_1 \cdot e_2 \f$.
         * \tparam M The matrix expression type.
         * \tparam V The vector expression type.
         */
        template <typename M, typename V>
        struct MatrixVectorProduct : public MatrixVectorBinaryFunctor<M, V>
        {

            typedef typename MatrixVectorBinaryFunctor<M, V>::ValueType  ValueType;
            typedef typename MatrixVectorBinaryFunctor<M, V>::SizeType   SizeType;
            typedef typename MatrixVectorBinaryFunctor<M, V>::ResultType ResultType;

            /**
             * \brief Returns element \e i of the matrix-vector product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The matrix expression type.
             * \tparam E2 The vector expression type.
             * \param e1 The matrix expression.
             * \param e2 The vector expression.
             * \param i The zero-based row index of the result element.
             * \return \f$ \sum_j e_1(i, j) \cdot e_2(j) \f$.
             * \throw Base::SizeError if \c e1.getSize2() does not equal \c e2.getSize().
             */
            template <typename E1, typename E2>
            static ResultType apply(const MatrixExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i)
            {
                SizeType   size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize2()), SizeType(e2().getSize()), Base::SizeError);
                ResultType res  = ResultType();

                for (SizeType j = 0; j < size; j++)
                    res += e1()(i, j) * e2()(j);

                return res;
            }
        };

        /**
         * \brief Functor returning element \e i of the vector-matrix product \f$ e_1 \cdot e_2 \f$.
         * \tparam V The vector expression type.
         * \tparam M The matrix expression type.
         */
        template <typename V, typename M>
        struct VectorMatrixProduct : public MatrixVectorBinaryFunctor<M, V>
        {

            typedef typename MatrixVectorBinaryFunctor<M, V>::ValueType  ValueType;
            typedef typename MatrixVectorBinaryFunctor<M, V>::SizeType   SizeType;
            typedef typename MatrixVectorBinaryFunctor<M, V>::ResultType ResultType;

            /**
             * \brief Returns element \e i of the vector-matrix product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The vector expression type.
             * \tparam E2 The matrix expression type.
             * \param e1 The vector expression.
             * \param e2 The matrix expression.
             * \param i The zero-based column index of the result element.
             * \return \f$ \sum_j e_1(j) \cdot e_2(j, i) \f$.
             * \throw Base::SizeError if \c e1.getSize() does not equal \c e2.getSize1().
             */
            template <typename E1, typename E2>
            static ResultType apply(const VectorExpression<E1>& e1, const MatrixExpression<E2>& e2, SizeType i)
            {
                SizeType   size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize()), SizeType(e2().getSize1()), Base::SizeError);
                ResultType res  = ResultType();

                for (SizeType j = 0; j < size; j++)
                    res += e1()(j) * e2()(j, i);

                return res;
            }
        };

        /**
         * \brief %Base class for binary functors that take two matrix expressions and return a matrix element scalar result (Math::MatrixProduct).
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         */
        template <typename M1, typename M2>
        struct MatrixBinaryFunctor
        {

            /**
             * \brief The element value type (common type of the two matrix element types).
             */
            typedef typename CommonType<typename M1::ValueType, typename M2::ValueType>::Type ValueType;

            /**
             * \brief The unsigned size type (common type of the two matrix size types).
             */
            typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type   SizeType;

            /**
             * \brief The scalar result type (alias for ValueType).
             */
            typedef ValueType                                                                 ResultType;
        };

        /**
         * \brief Functor returning element (\e i, \e j) of the matrix product \f$ e_1 \cdot e_2 \f$.
         * \tparam M1 The first matrix expression type.
         * \tparam M2 The second matrix expression type.
         */
        template <typename M1, typename M2>
        struct MatrixProduct : public MatrixBinaryFunctor<M1, M2>
        {

            typedef typename MatrixVectorBinaryFunctor<M1, M2>::ValueType  ValueType;
            typedef typename MatrixVectorBinaryFunctor<M1, M2>::SizeType   SizeType;
            typedef typename MatrixVectorBinaryFunctor<M1, M2>::ResultType ResultType;

            /**
             * \brief Returns element (\e i, \e j) of the matrix product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The first matrix expression type.
             * \tparam E2 The second matrix expression type.
             * \param e1 The first matrix expression.
             * \param e2 The second matrix expression.
             * \param i The zero-based row index of the result element.
             * \param j The zero-based column index of the result element.
             * \return \f$ \sum_k e_1(i, k) \cdot e_2(k, j) \f$.
             * \throw Base::SizeError if \c e1.getSize2() does not equal \c e2.getSize1().
             */
            template <typename E1, typename E2>
            static ResultType apply(const MatrixExpression<E1>& e1, const MatrixExpression<E2>& e2, SizeType i, SizeType j)
            {
                SizeType   size = CDPL_MATH_CHECK_SIZE_EQUALITY(SizeType(e1().getSize2()), SizeType(e2().getSize1()), Base::SizeError);
                ResultType res  = ResultType();

                for (SizeType k = 0; k < size; k++)
                    res += e1()(i, k) * e2()(k, j);

                return res;
            }
        };

        /**
         * \brief %Base class for binary functors that take two quaternion expressions and return a \c bool result (Math::QuaternionEquality).
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         */
        template <typename Q1, typename Q2>
        struct QuaternionBooleanBinaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The component value type (common type of the two quaternion element types).
             */
            typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking component-wise equality of two quaternion expressions.
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         */
        template <typename Q1, typename Q2>
        struct QuaternionEquality : public QuaternionBooleanBinaryFunctor<Q1, Q2>
        {

            typedef typename QuaternionBooleanBinaryFunctor<Q1, Q2>::ValueType  ValueType;
            typedef typename QuaternionBooleanBinaryFunctor<Q1, Q2>::ResultType ResultType;

            /**
             * \brief Tells whether \a e1 and \a e2 have equal components.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \return \c true if all four components agree, and \c false otherwise.
             */
            static ResultType apply(const QuaternionExpression<Q1>& e1, const QuaternionExpression<Q2>& e2)
            {
                return (ValueType(e1().getC1()) == ValueType(e2().getC1()) && ValueType(e1().getC2()) == ValueType(e2().getC2()) && ValueType(e1().getC3()) == ValueType(e2().getC3()) && ValueType(e1().getC4()) == ValueType(e2().getC4()));
            }
        };

        /**
         * \brief %Base class for ternary functors that take two quaternion expressions plus a tolerance scalar and return a \c bool result (Math::QuaternionToleranceEquality).
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename Q1, typename Q2, typename T>
        struct Scalar3QuaternionBooleanTernaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T&                                                                  Argument3Type;

            /**
             * \brief The component value type (common type of the two quaternion element types).
             */
            typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking component-wise approximate equality of two quaternion expressions within an absolute tolerance.
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename Q1, typename Q2, typename T>
        struct QuaternionToleranceEquality : public Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>
        {

            typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::ValueType     ValueType;
            typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::ResultType    ResultType;
            typedef typename Scalar3QuaternionBooleanTernaryFunctor<Q1, Q2, T>::Argument3Type Argument3Type;

            /**
             * \brief Tells whether \a e1 and \a e2 agree component-wise within the absolute tolerance \a epsilon.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \param epsilon The non-negative absolute tolerance.
             * \return \c true if all four components agree within \a epsilon, and \c false otherwise.
             */
            static ResultType apply(const QuaternionExpression<Q1>& e1, const QuaternionExpression<Q2>& e2, Argument3Type epsilon)
            {
                typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

                ComparisonType norm_inf_max(epsilon);

                return (ComparisonType(TypeTraits<ValueType>::normInf(e2().getC1() - e1().getC1())) <= norm_inf_max && ComparisonType(TypeTraits<ValueType>::normInf(e2().getC2() - e1().getC2())) <= norm_inf_max && ComparisonType(TypeTraits<ValueType>::normInf(e2().getC3() - e1().getC3())) <= norm_inf_max && ComparisonType(TypeTraits<ValueType>::normInf(e2().getC4() - e1().getC4())) <= norm_inf_max);
            }
        };

        /**
         * \brief %Base class for unary functors that take a quaternion expression and return a scalar result (Math::QuaternionElementSum).
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionScalarUnaryFunctor
        {

            /**
             * \brief The scalar result type (the quaternion's element value type).
             */
            typedef typename Q::ValueType ResultType;
        };

        /**
         * \brief Functor returning the sum of the four components of a quaternion expression.
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionElementSum : public QuaternionScalarUnaryFunctor<Q>
        {

            typedef typename QuaternionScalarUnaryFunctor<Q>::ResultType ResultType;

            /**
             * \brief Returns the component sum of \a e.
             * \param e The quaternion expression.
             * \return \f$ C_1(e) + C_2(e) + C_3(e) + C_4(e) \f$.
             */
            static ResultType apply(const QuaternionExpression<Q>& e)
            {
                return (e().getC1() + e().getC2() + e().getC3() + e().getC4());
            }
        };

        /**
         * \brief %Base class for unary functors that take a quaternion expression and return a real-valued scalar (Math::QuaternionNorm, Math::QuaternionNorm2).
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionScalarRealUnaryFunctor
        {

            /**
             * \brief The quaternion's component value type.
             */
            typedef typename Q::ValueType ValueType;

            /**
             * \brief The real-valued type (alias for ValueType).
             */
            typedef ValueType             RealType;

            /**
             * \brief The real-valued result type.
             */
            typedef RealType              ResultType;
        };

        /**
         * \brief Functor returning the (Euclidean) norm \f$ \|e\| \f$ of a quaternion expression.
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionNorm : public QuaternionScalarRealUnaryFunctor<Q>
        {

            typedef typename QuaternionScalarRealUnaryFunctor<Q>::ValueType  ValueType;
            typedef typename QuaternionScalarRealUnaryFunctor<Q>::RealType   RealType;
            typedef typename QuaternionScalarRealUnaryFunctor<Q>::ResultType ResultType;

            /**
             * \brief Returns \f$ \|e\| = \sqrt{C_1^2 + C_2^2 + C_3^2 + C_4^2} \f$.
             * \param e The quaternion expression.
             * \return The Euclidean norm of \a e.
             */
            static ResultType apply(const QuaternionExpression<Q>& e)
            {
                RealType t = e().getC1() * e().getC1() +
                             e().getC2() * e().getC2() +
                             e().getC3() * e().getC3() +
                             e().getC4() * e().getC4();

                return TypeTraits<RealType>::sqrt(t);
            }
        };

        /**
         * \brief Functor returning the squared norm \f$ \|e\|^2 \f$ of a quaternion expression.
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionNorm2 : public QuaternionScalarRealUnaryFunctor<Q>
        {

            typedef typename QuaternionScalarRealUnaryFunctor<Q>::ValueType  ValueType;
            typedef typename QuaternionScalarRealUnaryFunctor<Q>::RealType   RealType;
            typedef typename QuaternionScalarRealUnaryFunctor<Q>::ResultType ResultType;

            /**
             * \brief Returns \f$ \|e\|^2 = C_1^2 + C_2^2 + C_3^2 + C_4^2 \f$.
             * \param e The quaternion expression.
             * \return The squared Euclidean norm of \a e.
             */
            static ResultType apply(const QuaternionExpression<Q>& e)
            {
                RealType t = e().getC1() * e().getC1() +
                             e().getC2() * e().getC2() +
                             e().getC3() * e().getC3() +
                             e().getC4() * e().getC4();

                return t;
            }
        };

        /**
         * \brief %Base class for per-component unary functors that take a quaternion expression and produce a quaternion result via \c applyC1 / \c applyC2 / \c applyC3 / \c applyC4 (Math::QuaternionUnreal, Math::QuaternionConjugate).
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionUnaryFunctor
        {

            /**
             * \brief The component result type (the quaternion's element value type).
             */
            typedef typename Q::ValueType ResultType;
        };

        /**
         * \brief Per-component functor returning the unreal (pure-quaternion) part of a quaternion expression (zeros \c C1, keeps \c C2/\c C3/\c C4).
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionUnreal : public QuaternionUnaryFunctor<Q>
        {

            typedef typename QuaternionUnaryFunctor<Q>::ResultType ResultType;

            /**
             * \brief Returns the \c C1 component of the unreal part (always zero).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return Zero.
             */
            template <typename E>
            static ResultType applyC1(const QuaternionExpression<E>& e)
            {
                return ResultType();
            }

            /**
             * \brief Returns the \c C2 component of the unreal part (equals \c e.getC2()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c e.getC2().
             */
            template <typename E>
            static ResultType applyC2(const QuaternionExpression<E>& e)
            {
                return e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of the unreal part (equals \c e.getC3()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c e.getC3().
             */
            template <typename E>
            static ResultType applyC3(const QuaternionExpression<E>& e)
            {
                return e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of the unreal part (equals \c e.getC4()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c e.getC4().
             */
            template <typename E>
            static ResultType applyC4(const QuaternionExpression<E>& e)
            {
                return e().getC4();
            }
        };

        /**
         * \brief Per-component functor returning the quaternion conjugate (keeps \c C1, negates \c C2/\c C3/\c C4).
         * \tparam Q The quaternion expression type.
         */
        template <typename Q>
        struct QuaternionConjugate : public QuaternionUnaryFunctor<Q>
        {

            typedef typename QuaternionUnaryFunctor<Q>::ResultType ResultType;

            /**
             * \brief Returns the \c C1 component of the conjugate (equals \c e.getC1()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c e.getC1().
             */
            template <typename E>
            static ResultType applyC1(const QuaternionExpression<E>& e)
            {
                return e().getC1();
            }

            /**
             * \brief Returns the \c C2 component of the conjugate (equals \c -e.getC2()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c -e.getC2().
             */
            template <typename E>
            static ResultType applyC2(const QuaternionExpression<E>& e)
            {
                return -e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of the conjugate (equals \c -e.getC3()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c -e.getC3().
             */
            template <typename E>
            static ResultType applyC3(const QuaternionExpression<E>& e)
            {
                return -e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of the conjugate (equals \c -e.getC4()).
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \return \c -e.getC4().
             */
            template <typename E>
            static ResultType applyC4(const QuaternionExpression<E>& e)
            {
                return -e().getC4();
            }
        };

        /**
         * \brief %Base class for per-component binary functors that take a scalar \a T (lhs) and a quaternion expression (Math::Scalar1QuaternionAddition, Math::Scalar1QuaternionSubtraction).
         * \tparam T The scalar type.
         * \tparam Q The quaternion expression type.
         */
        template <typename T, typename Q>
        struct Scalar1QuaternionBinaryFunctor
        {

            /**
             * \brief The component result type (common type of the scalar and the quaternion's element value type).
             */
            typedef typename CommonType<T, typename Q::ValueType>::Type ResultType;

            /**
             * \brief The first (scalar) argument type.
             */
            typedef const T&                                            Argument1Type;
        };

        /**
         * \brief Per-component functor returning \f$ t + e \f$ (scalar \a t added to the real component of \a e).
         * \tparam T The scalar type.
         * \tparam Q The quaternion expression type.
         */
        template <typename T, typename Q>
        struct Scalar1QuaternionAddition : public Scalar1QuaternionBinaryFunctor<T, Q>
        {

            typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::Argument1Type Argument1Type;
            typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of \f$ t + e \f$.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \return \c t + e.getC1().
             */
            template <typename E>
            static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e)
            {
                return (t + e().getC1());
            }

            /**
             * \brief Returns the \c C2 component of \f$ t + e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c e.getC2() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC2(Argument1Type, const QuaternionExpression<E>& e)
            {
                return e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of \f$ t + e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c e.getC3() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC3(Argument1Type, const QuaternionExpression<E>& e)
            {
                return e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of \f$ t + e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c e.getC4() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC4(Argument1Type, const QuaternionExpression<E>& e)
            {
                return e().getC4();
            }
        };

        /**
         * \brief Per-component functor returning \f$ t - e \f$ (scalar \a t with the quaternion \a e subtracted).
         * \tparam T The scalar type.
         * \tparam Q The quaternion expression type.
         */
        template <typename T, typename Q>
        struct Scalar1QuaternionSubtraction : public Scalar1QuaternionBinaryFunctor<T, Q>
        {

            typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::Argument1Type Argument1Type;
            typedef typename Scalar1QuaternionBinaryFunctor<T, Q>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of \f$ t - e \f$.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \return \c t - e.getC1().
             */
            template <typename E>
            static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e)
            {
                return (t - e().getC1());
            }

            /**
             * \brief Returns the \c C2 component of \f$ t - e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c -e.getC2() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC2(Argument1Type, const QuaternionExpression<E>& e)
            {
                return -e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of \f$ t - e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c -e.getC3() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC3(Argument1Type, const QuaternionExpression<E>& e)
            {
                return -e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of \f$ t - e \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the right-hand side.
             * \return \c -e.getC4() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC4(Argument1Type, const QuaternionExpression<E>& e)
            {
                return -e().getC4();
            }
        };

        /**
         * \brief %Base class for per-component binary functors that take a quaternion expression (lhs) and a scalar \a T (Math::Scalar2QuaternionAddition, Math::Scalar2QuaternionSubtraction, Math::QuaternionInverse).
         * \tparam Q The quaternion expression type.
         * \tparam T The scalar type.
         */
        template <typename Q, typename T>
        struct Scalar2QuaternionBinaryFunctor
        {

            /**
             * \brief The component result type (common type of the quaternion's element value type and the scalar).
             */
            typedef typename CommonType<typename Q::ValueType, T>::Type ResultType;

            /**
             * \brief The second (scalar) argument type.
             */
            typedef const T&                                            Argument2Type;
        };

        /**
         * \brief Per-component functor returning \f$ e + t \f$ (scalar \a t added to the real component of \a e).
         * \tparam Q The quaternion expression type.
         * \tparam T The scalar type.
         */
        template <typename Q, typename T>
        struct Scalar2QuaternionAddition : public Scalar2QuaternionBinaryFunctor<Q, T>
        {

            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of \f$ e + t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \param t The scalar value on the right-hand side.
             * \return \c e.getC1() + t.
             */
            template <typename E>
            static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type t)
            {
                return (e().getC1() + t);
            }

            /**
             * \brief Returns the \c C2 component of \f$ e + t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC2() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of \f$ e + t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC3() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of \f$ e + t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC4() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC4();
            }
        };

        /**
         * \brief Per-component functor returning \f$ e - t \f$ (scalar \a t subtracted from the real component of \a e).
         * \tparam Q The quaternion expression type.
         * \tparam T The scalar type.
         */
        template <typename Q, typename T>
        struct Scalar2QuaternionSubtraction : public Scalar2QuaternionBinaryFunctor<Q, T>
        {

            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of \f$ e - t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \param t The scalar value on the right-hand side.
             * \return \c e.getC1() - t.
             */
            template <typename E>
            static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type t)
            {
                return (e().getC1() - t);
            }

            /**
             * \brief Returns the \c C2 component of \f$ e - t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC2() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC2();
            }

            /**
             * \brief Returns the \c C3 component of \f$ e - t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC3() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC3();
            }

            /**
             * \brief Returns the \c C4 component of \f$ e - t \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression on the left-hand side.
             * \return \c e.getC4() (the scalar argument does not contribute to this component).
             */
            template <typename E>
            static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type)
            {
                return e().getC4();
            }
        };

        /**
         * \brief Per-component functor returning the multiplicative inverse \f$ \overline{e} / \|e\|^2 \f$ of a quaternion expression (\a n2 is the precomputed squared norm).
         * \tparam Q The quaternion expression type.
         * \tparam T The precomputed-norm scalar type.
         */
        template <typename Q, typename T>
        struct QuaternionInverse : public Scalar2QuaternionBinaryFunctor<Q, T>
        {

            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::Argument2Type Argument2Type;
            typedef typename Scalar2QuaternionBinaryFunctor<Q, T>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 (real) component of the multiplicative inverse \f$ e^{-1} = \overline{e} / \|e\|^2 \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e\|^2 \f$.
             * \return \c e.getC1() / n2.
             */
            template <typename E>
            static ResultType applyC1(const QuaternionExpression<E>& e, Argument2Type n2)
            {
                return (e().getC1() / n2);
            }

            /**
             * \brief Returns the \c C2 component of the multiplicative inverse \f$ e^{-1} \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e\|^2 \f$.
             * \return \c -e.getC2() / n2.
             */
            template <typename E>
            static ResultType applyC2(const QuaternionExpression<E>& e, Argument2Type n2)
            {
                return (-e().getC2() / n2);
            }

            /**
             * \brief Returns the \c C3 component of the multiplicative inverse \f$ e^{-1} \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e\|^2 \f$.
             * \return \c -e.getC3() / n2.
             */
            template <typename E>
            static ResultType applyC3(const QuaternionExpression<E>& e, Argument2Type n2)
            {
                return (-e().getC3() / n2);
            }

            /**
             * \brief Returns the \c C4 component of the multiplicative inverse \f$ e^{-1} \f$.
             * \tparam E The quaternion expression type.
             * \param e The quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e\|^2 \f$.
             * \return \c -e.getC4() / n2.
             */
            template <typename E>
            static ResultType applyC4(const QuaternionExpression<E>& e, Argument2Type n2)
            {
                return (-e().getC4() / n2);
            }
        };

        /**
         * \brief %Base class for per-component binary functors that take two quaternion expressions and produce a quaternion result (Math::QuaternionProduct).
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         */
        template <typename Q1, typename Q2>
        struct QuaternionBinaryFunctor
        {

            /**
             * \brief The component result type (common type of the two quaternion element types).
             */
            typedef typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type ResultType;
        };

        /**
         * \brief Per-component functor returning the Hamilton product \f$ e_1 \cdot e_2 \f$ of two quaternion expressions.
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         */
        template <typename Q1, typename Q2>
        struct QuaternionProduct : public QuaternionBinaryFunctor<Q1, Q2>
        {

            typedef typename QuaternionBinaryFunctor<Q1, Q2>::ResultType ResultType;

            /**
             * \brief Returns the \c C1 component of the Hamilton product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \return The \c C1 component of the Hamilton product.
             */
            template <typename E1, typename E2>
            static ResultType applyC1(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
            {
                // a = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2
                return (e1().getC1() * e2().getC1() - e1().getC2() * e2().getC2() - e1().getC3() * e2().getC3() - e1().getC4() * e2().getC4());
            }

            /**
             * \brief Returns the \c C2 component of the Hamilton product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \return The \c C2 component of the Hamilton product.
             */
            template <typename E1, typename E2>
            static ResultType applyC2(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
            {
                // b = a1 * b2 + b1 * a2 + c1 * d2 - d1 * c2
                return (e1().getC1() * e2().getC2() + e1().getC2() * e2().getC1() + e1().getC3() * e2().getC4() - e1().getC4() * e2().getC3());
            }

            /**
             * \brief Returns the \c C3 component of the Hamilton product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \return The \c C3 component of the Hamilton product.
             */
            template <typename E1, typename E2>
            static ResultType applyC3(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
            {
                // c = a1 * c2 - b1 * d2 + c1 * a2 + d1 * b2
                return (e1().getC1() * e2().getC3() - e1().getC2() * e2().getC4() + e1().getC3() * e2().getC1() + e1().getC4() * e2().getC2());
            }

            /**
             * \brief Returns the \c C4 component of the Hamilton product \f$ e_1 \cdot e_2 \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The first quaternion expression.
             * \param e2 The second quaternion expression.
             * \return The \c C4 component of the Hamilton product.
             */
            template <typename E1, typename E2>
            static ResultType applyC4(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2)
            {
                // d = a1 * d2 + b1 * c2 - c1 * b2 + d1 * a2
                return (e1().getC1() * e2().getC4() + e1().getC2() * e2().getC3() - e1().getC3() * e2().getC2() + e1().getC4() * e2().getC1());
            }
        };

        /**
         * \brief %Base class for per-component ternary functors that take two quaternion expressions plus a scalar (Math::QuaternionDivision).
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         * \tparam T The scalar type.
         */
        template <typename Q1, typename Q2, typename T>
        struct Scalar3QuaternionTernaryFunctor
        {

            /**
             * \brief The component result type (common type of the two quaternion element types and the scalar).
             */
            typedef typename CommonType<typename CommonType<typename Q1::ValueType, typename Q2::ValueType>::Type, T>::Type ResultType;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T&                                                                                                Argument3Type;
        };

        /**
         * \brief Per-component functor returning the quaternion division \f$ e_1 \cdot e_2^{-1} \f$ (\a n2 is the precomputed squared norm of \a e_2).
         * \tparam Q1 The first quaternion expression type.
         * \tparam Q2 The second quaternion expression type.
         * \tparam T The precomputed-norm scalar type.
         */
        template <typename Q1, typename Q2, typename T>
        struct QuaternionDivision : public Scalar3QuaternionTernaryFunctor<Q1, Q2, T>
        {

            typedef typename Scalar3QuaternionTernaryFunctor<Q1, Q2, T>::Argument3Type Argument3Type;
            typedef typename Scalar3QuaternionTernaryFunctor<Q1, Q2, T>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of the quaternion division \f$ e_1 \cdot e_2^{-1} \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The dividend quaternion expression.
             * \param e2 The divisor quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e_2\|^2 \f$.
             * \return The \c C1 component of \f$ e_1 \cdot e_2^{-1} \f$.
             */
            template <typename E1, typename E2>
            static ResultType applyC1(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
            {
                // a = (a1 * a2 + b1 * b2 + c1 * c2 + d1 * d2) / n2
                return ((e1().getC1() * e2().getC1() + e1().getC2() * e2().getC2() + e1().getC3() * e2().getC3() + e1().getC4() * e2().getC4()) / n2);
            }

            /**
             * \brief Returns the \c C2 component of the quaternion division \f$ e_1 \cdot e_2^{-1} \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The dividend quaternion expression.
             * \param e2 The divisor quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e_2\|^2 \f$.
             * \return The \c C2 component of \f$ e_1 \cdot e_2^{-1} \f$.
             */
            template <typename E1, typename E2>
            static ResultType applyC2(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
            {
                // b = (-a1 * b2 + b1 * a2 - c1 * d2 + d1 * c2) / n2
                return ((-e1().getC1() * e2().getC2() + e1().getC2() * e2().getC1() - e1().getC3() * e2().getC4() + e1().getC4() * e2().getC3()) / n2);
            }

            /**
             * \brief Returns the \c C3 component of the quaternion division \f$ e_1 \cdot e_2^{-1} \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The dividend quaternion expression.
             * \param e2 The divisor quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e_2\|^2 \f$.
             * \return The \c C3 component of \f$ e_1 \cdot e_2^{-1} \f$.
             */
            template <typename E1, typename E2>
            static ResultType applyC3(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
            {
                // c = (-a1 * c2 + b1 * d2 + c1 * a2 - d1 * b2) / n2
                return ((-e1().getC1() * e2().getC3() + e1().getC2() * e2().getC4() + e1().getC3() * e2().getC1() - e1().getC4() * e2().getC2()) / n2);
            }

            /**
             * \brief Returns the \c C4 component of the quaternion division \f$ e_1 \cdot e_2^{-1} \f$.
             * \tparam E1 The first quaternion expression type.
             * \tparam E2 The second quaternion expression type.
             * \param e1 The dividend quaternion expression.
             * \param e2 The divisor quaternion expression.
             * \param n2 The precomputed squared norm \f$ \|e_2\|^2 \f$.
             * \return The \c C4 component of \f$ e_1 \cdot e_2^{-1} \f$.
             */
            template <typename E1, typename E2>
            static ResultType applyC4(const QuaternionExpression<E1>& e1, const QuaternionExpression<E2>& e2, Argument3Type n2)
            {
                // d = (-a1 * d2 - b1 * c2 + c1 * b2 + d1 * a2) / n2
                return ((-e1().getC1() * e2().getC4() - e1().getC2() * e2().getC3() + e1().getC3() * e2().getC2() + e1().getC4() * e2().getC1()) / n2);
            }
        };

        /**
         * \brief %Base class for per-component ternary functors that take a scalar \a T1 (lhs), a quaternion expression, and a scalar \a T2 (Math::ScalarQuaternionDivision).
         * \tparam T1 The scalar type on the left-hand side.
         * \tparam Q The quaternion expression type.
         * \tparam T2 The scalar type on the right-hand side.
         */
        template <typename T1, typename Q, typename T2>
        struct Scalar13QuaternionTernaryFunctor
        {

            /**
             * \brief The component result type (common type of \a T1, the quaternion's element value type, and \a T2).
             */
            typedef typename CommonType<typename CommonType<T1, typename Q::ValueType>::Type, T2>::Type ResultType;

            /**
             * \brief The first (scalar) argument type.
             */
            typedef const T1&                                                                           Argument1Type;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T2&                                                                           Argument3Type;
        };

        /**
         * \brief Per-component functor returning the scalar/quaternion division \f$ t \cdot e^{-1} \f$ (\a n2 is the precomputed squared norm of \a e).
         * \tparam T1 The scalar type on the left-hand side.
         * \tparam Q The quaternion expression type.
         * \tparam T2 The precomputed-norm scalar type.
         */
        template <typename T1, typename Q, typename T2>
        struct ScalarQuaternionDivision : public Scalar13QuaternionTernaryFunctor<T1, Q, T2>
        {

            typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::Argument1Type Argument1Type;
            typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::Argument3Type Argument3Type;
            typedef typename Scalar13QuaternionTernaryFunctor<T1, Q, T2>::ResultType    ResultType;

            /**
             * \brief Returns the \c C1 component of \f$ t / e \f$ using the precomputed squared norm \a n2 of \a e.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \param n2 The squared norm of \a e.
             * \return \c t * e.getC1() / n2.
             */
            template <typename E>
            static ResultType applyC1(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
            {
                return (t * e().getC1() / n2);
            }

            /**
             * \brief Returns the \c C2 component of \f$ t / e \f$ using the precomputed squared norm \a n2 of \a e.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \param n2 The squared norm of \a e.
             * \return \c t * -e.getC2() / n2.
             */
            template <typename E>
            static ResultType applyC2(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
            {
                return (t * -e().getC2() / n2);
            }

            /**
             * \brief Returns the \c C3 component of \f$ t / e \f$ using the precomputed squared norm \a n2 of \a e.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \param n2 The squared norm of \a e.
             * \return \c t * -e.getC3() / n2.
             */
            template <typename E>
            static ResultType applyC3(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
            {
                return (t * -e().getC3() / n2);
            }

            /**
             * \brief Returns the \c C4 component of \f$ t / e \f$ using the precomputed squared norm \a n2 of \a e.
             * \tparam E The quaternion expression type.
             * \param t The scalar value on the left-hand side.
             * \param e The quaternion expression on the right-hand side.
             * \param n2 The squared norm of \a e.
             * \return \c t * -e.getC4() / n2.
             */
            template <typename E>
            static ResultType applyC4(Argument1Type t, const QuaternionExpression<E>& e, Argument3Type n2)
            {
                return (t * -e().getC4() / n2);
            }
        };

        /**
         * \brief %Base class for binary functors that take a quaternion expression and a vector expression and return a vector element scalar (Math::QuaternionVectorRotation).
         * \tparam Q The quaternion expression type.
         * \tparam V The vector expression type.
         */
        template <typename Q, typename V>
        struct QuaternionVectorBinaryFunctor
        {

            /**
             * \brief The element value type (common type of the quaternion and vector element types).
             */
            typedef typename CommonType<typename Q::ValueType, typename V::ValueType>::Type ValueType;

            /**
             * \brief The unsigned size type used by the vector.
             */
            typedef typename V::SizeType                                                    SizeType;

            /**
             * \brief The scalar result type (alias for ValueType).
             */
            typedef ValueType                                                               ResultType;
        };

        /**
         * \brief Functor returning element \e i of the rotated 3-dimensional vector \f$ e_1 \cdot e_2 \cdot e_1^{-1} \f$
         *        (quaternion rotation of \f$ e_2 \f$ by \f$ e_1 \f$).
         * \tparam Q The quaternion expression type.
         * \tparam V The vector expression type.
         */
        template <typename Q, typename V>
        struct QuaternionVectorRotation : public QuaternionVectorBinaryFunctor<Q, V>
        {

            typedef typename QuaternionVectorBinaryFunctor<Q, V>::ValueType  ValueType;
            typedef typename QuaternionVectorBinaryFunctor<Q, V>::SizeType   SizeType;
            typedef typename QuaternionVectorBinaryFunctor<Q, V>::ResultType ResultType;

            /**
             * \brief Returns element \a i (\f$ 0 \le i < 3 \f$) of the rotated 3D vector \f$ e_1 \cdot e_2 \cdot e_1^{-1} \f$.
             * \tparam E1 The quaternion expression type.
             * \tparam E2 The vector expression type.
             * \param e1 The quaternion expression (rotation).
             * \param e2 The 3D vector expression to rotate.
             * \param i The zero-based element index (\c 0, \c 1, or \c 2).
             * \return The rotated vector's \a i-th element (zero for \a i &gt; 2).
             * \throw Base::SizeError if \a e2 has fewer than 3 elements.
             */
            template <typename E1, typename E2>
            static ResultType apply(const QuaternionExpression<E1>& e1, const VectorExpression<E2>& e2, SizeType i)
            {
                CDPL_MATH_CHECK(e2().getSize() >= 3, "Invalid vector size", Base::SizeError);

                switch (i) {

                    case 0: {
                        // vr1 = (a2 + b2 - c2 - d2) * v1 + (2bc - 2ad) * v2 + (2bd + 2ac) * v3
                        ValueType t1 = e1().getC1() * e1().getC1() + e1().getC2() * e1().getC2() - e1().getC3() * e1().getC3() - e1().getC4() * e1().getC4();
                        ValueType t2 = ValueType(2) * (e1().getC2() * e1().getC3() - e1().getC1() * e1().getC4());
                        ValueType t3 = ValueType(2) * (e1().getC2() * e1().getC4() + e1().getC1() * e1().getC3());

                        return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
                    }

                    case 1: {
                        // vr2 = (2bc + 2ad) * v1 + (a2 - b2 + c2 - d2) * v2 + (2cd - 2ab) * v3
                        ValueType t1 = ValueType(2) * (e1().getC2() * e1().getC3() + e1().getC1() * e1().getC4());
                        ValueType t2 = e1().getC1() * e1().getC1() - e1().getC2() * e1().getC2() + e1().getC3() * e1().getC3() - e1().getC4() * e1().getC4();
                        ValueType t3 = ValueType(2) * (e1().getC3() * e1().getC4() - e1().getC1() * e1().getC2());

                        return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
                    }

                    case 2: {
                        // vr3 = (2bd - 2ac) * v1 + (2cd + 2ab) * v2 + (a2 - b2 - c2 + d2) * v3
                        ValueType t1 = ValueType(2) * (e1().getC2() * e1().getC4() - e1().getC1() * e1().getC3());
                        ValueType t2 = ValueType(2) * (e1().getC3() * e1().getC4() + e1().getC1() * e1().getC2());
                        ValueType t3 = e1().getC1() * e1().getC1() - e1().getC2() * e1().getC2() - e1().getC3() * e1().getC3() + e1().getC4() * e1().getC4();

                        return (t1 * e2()(0) + t2 * e2()(1) + t3 * e2()(2));
                    }

                    default:
                        return ResultType();
                }
            }
        };

        /**
         * \brief %Base class for binary functors that take two grid expressions and return a \c bool result (Math::GridEquality).
         * \tparam G1 The first grid expression type.
         * \tparam G2 The second grid expression type.
         */
        template <typename G1, typename G2>
        struct GridBooleanBinaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The unsigned size type (common type of the two grid size types).
             */
            typedef typename CommonType<typename G1::SizeType, typename G2::SizeType>::Type   SizeType;

            /**
             * \brief The cell value type (common type of the two grid cell types).
             */
            typedef typename CommonType<typename G1::ValueType, typename G2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking cell-wise equality of two grid expressions.
         * \tparam G1 The first grid expression type.
         * \tparam G2 The second grid expression type.
         */
        template <typename G1, typename G2>
        struct GridEquality : public GridBooleanBinaryFunctor<G1, G2>
        {

            typedef typename GridBooleanBinaryFunctor<G1, G2>::SizeType   SizeType;
            typedef typename GridBooleanBinaryFunctor<G1, G2>::ValueType  ValueType;
            typedef typename GridBooleanBinaryFunctor<G1, G2>::ResultType ResultType;

            /**
             * \brief Tells whether \a e1 and \a e2 have the same dimensions and equal cell values.
             * \param e1 The first grid expression.
             * \param e2 The second grid expression.
             * \return \c true if the grids agree in dimensions and cell-wise values, and \c false otherwise.
             */
            static ResultType apply(const GridExpression<G1>& e1, const GridExpression<G2>& e2)
            {
                if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
                    return false;

                if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
                    return false;

                if (SizeType(e1().getSize3()) != SizeType(e2().getSize3()))
                    return false;

                for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
                    for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
                        for (SizeType k = 0, size3 = e1().getSize3(); k < size3; k++)
                            if (ValueType(e1()(i, j, k)) != ValueType(e2()(i, j, k)))
                                return false;

                return true;
            }
        };

        /**
         * \brief %Base class for ternary functors that take two grid expressions plus a tolerance scalar and return a \c bool result (Math::GridToleranceEquality).
         * \tparam G1 The first grid expression type.
         * \tparam G2 The second grid expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename G1, typename G2, typename T>
        struct Scalar3GridBooleanTernaryFunctor
        {

            /**
             * \brief The boolean result type.
             */
            typedef bool                                                                      ResultType;

            /**
             * \brief The third (scalar) argument type.
             */
            typedef const T&                                                                  Argument3Type;

            /**
             * \brief The unsigned size type (common type of the two grid size types).
             */
            typedef typename CommonType<typename G1::SizeType, typename G2::SizeType>::Type   SizeType;

            /**
             * \brief The cell value type (common type of the two grid cell types).
             */
            typedef typename CommonType<typename G1::ValueType, typename G2::ValueType>::Type ValueType;
        };

        /**
         * \brief Functor checking cell-wise approximate equality of two grid expressions within an absolute tolerance.
         * \tparam G1 The first grid expression type.
         * \tparam G2 The second grid expression type.
         * \tparam T The tolerance scalar type.
         */
        template <typename G1, typename G2, typename T>
        struct GridToleranceEquality : public Scalar3GridBooleanTernaryFunctor<G1, G2, T>
        {

            typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::SizeType      SizeType;
            typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::ValueType     ValueType;
            typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::ResultType    ResultType;
            typedef typename Scalar3GridBooleanTernaryFunctor<G1, G2, T>::Argument3Type Argument3Type;

            /**
             * \brief Tells whether \a e1 and \a e2 agree cell-wise within the absolute tolerance \a epsilon.
             * \param e1 The first grid expression.
             * \param e2 The second grid expression.
             * \param epsilon The non-negative absolute tolerance.
             * \return \c true if the grids have equal dimensions and all cells agree within \a epsilon, and \c false otherwise.
             */
            static ResultType apply(const GridExpression<G1>& e1, const GridExpression<G2>& e2, Argument3Type epsilon)
            {
                typedef typename CommonType<typename TypeTraits<ValueType>::RealType, T>::Type ComparisonType;

                if (SizeType(e1().getSize1()) != SizeType(e2().getSize1()))
                    return false;

                if (SizeType(e1().getSize2()) != SizeType(e2().getSize2()))
                    return false;

                if (SizeType(e1().getSize3()) != SizeType(e2().getSize3()))
                    return false;

                ComparisonType norm_inf_max(epsilon);

                for (SizeType i = 0, size1 = e1().getSize1(); i < size1; i++)
                    for (SizeType j = 0, size2 = e1().getSize2(); j < size2; j++)
                        for (SizeType k = 0, size3 = e1().getSize3(); k < size3; k++)
                            if (ComparisonType(TypeTraits<ValueType>::normInf(e2()(i, j, k) - e1()(i, j, k))) > norm_inf_max)
                                return false;

                return true;
            }
        };

        /**
         * \brief %Base class for unary functors that take a grid expression and return a scalar result (Math::GridElementSum).
         * \tparam M The grid expression type.
         */
        template <typename M>
        struct GridScalarUnaryFunctor
        {

            /**
             * \brief The scalar result type (the grid's cell value type).
             */
            typedef typename M::ValueType ResultType;
        };

        /**
         * \brief Functor returning the sum of all cells of a grid expression.
         * \tparam G The grid expression type.
         */
        template <typename G>
        struct GridElementSum : public GridScalarUnaryFunctor<G>
        {

            typedef typename GridScalarUnaryFunctor<G>::ResultType ResultType;

            /**
             * \brief Returns the cell sum of \a e.
             * \param e The grid expression.
             * \return \f$ \sum_{i, j, k} e(i, j, k) \f$.
             */
            static ResultType apply(const GridExpression<G>& e)
            {
                typedef typename G::SizeType SizeType;

                ResultType res   = ResultType();
                SizeType   size1 = e().getSize1();
                SizeType   size2 = e().getSize2();
                SizeType   size3 = e().getSize3();

                for (SizeType i = 0; i < size1; i++)
                    for (SizeType j = 0; j < size2; j++)
                        for (SizeType k = 0; k < size3; k++)
                            res += e()(i, j, k);

                return res;
            }
        };
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_FUNCTIONAL_HPP
