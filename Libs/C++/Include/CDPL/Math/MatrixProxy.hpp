/* 
 * MatrixProxy.hpp 
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
 * \brief Definition of matrix proxy types.
 */

#ifndef CDPL_MATH_MATRIXPROXY_HPP
#define CDPL_MATH_MATRIXPROXY_HPP

#include <type_traits>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/MatrixAssignment.hpp"
#include "CDPL/Math/Range.hpp"
#include "CDPL/Math/Slice.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename M>
        class MatrixRow : public VectorExpression<MatrixRow<M> >
        {

            typedef MatrixRow<M> SelfType;

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

            MatrixRow(MatrixType& m, SizeType i):
                data(m), index(i) {}

            Reference operator()(SizeType i)
            {
                return data(index, i);
            }

            ConstReference operator()(SizeType i) const
            {
                return data(index, i);
            }

            Reference operator[](SizeType i)
            {
                return data(index, i);
            }

            ConstReference operator[](SizeType i) const
            {
                return data(index, i);
            }

            SizeType getIndex() const
            {
                return index;
            }

            SizeType getSize() const
            {
                return data.getSize2();
            }

            bool isEmpty() const
            {
                return (data.getSize2() == 0);
            }

            MatrixClosureType& getData()
            {
                return data;
            }

            const MatrixClosureType& getData() const
            {
                return data;
            }

            MatrixRow& operator=(const MatrixRow& r)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(r));
                return *this;
            }

            template <typename E>
            MatrixRow& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(e));
                return *this;
            }

            template <typename E>
            MatrixRow& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            template <typename E>
            MatrixRow& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRow>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRow>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            MatrixRow& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixRow& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixRow& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(MatrixRow& r)
            {
                if (this != &r)
                    vectorSwap(*this, r);
            }

            friend void swap(MatrixRow& r1, MatrixRow& r2)
            {
                r1.swap(r2);
            }

          private:
            MatrixClosureType data;
            SizeType          index;
        };

        template <typename M>
        class MatrixColumn : public VectorExpression<MatrixColumn<M> >
        {

            typedef MatrixColumn<M> SelfType;

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

            MatrixColumn(MatrixType& m, SizeType i):
                data(m), index(i) {}

            Reference operator()(SizeType i)
            {
                return data(i, index);
            }

            ConstReference operator()(SizeType i) const
            {
                return data(i, index);
            }

            Reference operator[](SizeType i)
            {
                return data(i, index);
            }

            ConstReference operator[](SizeType i) const
            {
                return data(i, index);
            }

            SizeType getIndex() const
            {
                return index;
            }

            SizeType getSize() const
            {
                return data.getSize1();
            }

            bool isEmpty() const
            {
                return (data.getSize1() == 0);
            }

            MatrixClosureType& getData()
            {
                return data;
            }

            const MatrixClosureType& getData() const
            {
                return data;
            }

            MatrixColumn& operator=(const MatrixColumn& c)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(c));
                return *this;
            }

            template <typename E>
            MatrixColumn& operator=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(e));
                return *this;
            }

            template <typename E>
            MatrixColumn& operator+=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            template <typename E>
            MatrixColumn& operator-=(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, typename VectorTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixColumn>::type& operator*=(const T& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixColumn>::type& operator/=(const T& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            MatrixColumn& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixColumn& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixColumn& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(MatrixColumn& c)
            {
                if (this != &c)
                    vectorSwap(*this, c);
            }

            friend void swap(MatrixColumn& c1, MatrixColumn& c2)
            {
                c1.swap(c2);
            }

          private:
            MatrixClosureType data;
            SizeType          index;
        };

        template <typename M>
        class MatrixRange : public MatrixExpression<MatrixRange<M> >
        {

            typedef MatrixRange<M> SelfType;

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
            typedef Range<SizeType>                                          RangeType;

            MatrixRange(MatrixType& m, const RangeType& r1, const RangeType& r2):
                data(m), range1(r1), range2(r2) {}

            Reference operator()(SizeType i, SizeType j)
            {
                return data(range1(i), range2(j));
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(range1(i), range2(j));
            }

            SizeType getStart1() const
            {
                return range1.getStart();
            }

            SizeType getStart2() const
            {
                return range2.getStart();
            }

            SizeType getSize1() const
            {
                return range1.getSize();
            }

            SizeType getSize2() const
            {
                return range2.getSize();
            }

            bool isEmpty() const
            {
                return (range1.getSize() == SizeType(0) || range2.getSize() == SizeType(0));
            }

            MatrixClosureType& getData()
            {
                return data;
            }

            const MatrixClosureType& getData() const
            {
                return data;
            }

            MatrixRange& operator=(const MatrixRange& r)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(r));
                return *this;
            }

            template <typename E>
            MatrixRange& operator=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(e));
                return *this;
            }

            template <typename E>
            MatrixRange& operator+=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            template <typename E>
            MatrixRange& operator-=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRange>::type& operator*=(const T& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixRange>::type& operator/=(const T& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            MatrixRange& assign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixRange& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixRange& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(MatrixRange& r)
            {
                if (this != &r)
                    matrixSwap(*this, r);
            }

            friend void swap(MatrixRange& r1, MatrixRange& r2)
            {
                r1.swap(r2);
            }

          private:
            MatrixClosureType data;
            RangeType         range1;
            RangeType         range2;
        };

        template <typename M>
        class MatrixSlice : public MatrixExpression<MatrixSlice<M> >
        {

            typedef MatrixSlice<M> SelfType;

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
            typedef Slice<SizeType, DifferenceType>                          SliceType;

            MatrixSlice(MatrixType& m, const SliceType& s1, const SliceType& s2):
                data(m), slice1(s1), slice2(s2) {}

            Reference operator()(SizeType i, SizeType j)
            {
                return data(slice1(i), slice2(j));
            }

            ConstReference operator()(SizeType i, SizeType j) const
            {
                return data(slice1(i), slice2(j));
            }

            SizeType getStart1() const
            {
                return slice1.getStart();
            }

            SizeType getStart2() const
            {
                return slice2.getStart();
            }

            DifferenceType getStride1() const
            {
                return slice1.getStride();
            }

            DifferenceType getStride2() const
            {
                return slice2.getStride();
            }

            SizeType getSize1() const
            {
                return slice1.getSize();
            }

            SizeType getSize2() const
            {
                return slice2.getSize();
            }

            bool isEmpty() const
            {
                return (slice1.getSize() == SizeType(0) || slice2.getSize() == SizeType(0));
            }

            MatrixClosureType& getData()
            {
                return data;
            }

            const MatrixClosureType& getData() const
            {
                return data;
            }

            MatrixSlice& operator=(const MatrixSlice& s)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(s));
                return *this;
            }

            template <typename E>
            MatrixSlice& operator=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(e));
                return *this;
            }

            template <typename E>
            MatrixSlice& operator+=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this + e));
                return *this;
            }

            template <typename E>
            MatrixSlice& operator-=(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, typename MatrixTemporaryTraits<M>::Type(*this - e));
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixSlice>::type& operator*=(const T& t)
            {
                matrixAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, MatrixSlice>::type& operator/=(const T& t)
            {
                matrixAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            MatrixSlice& assign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixSlice& plusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            template <typename E>
            MatrixSlice& minusAssign(const MatrixExpression<E>& e)
            {
                matrixAssignMatrix<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            void swap(MatrixSlice& s)
            {
                if (this != &s)
                    matrixSwap(*this, s);
            }

            friend void swap(MatrixSlice& s1, MatrixSlice& s2)
            {
                s1.swap(s2);
            }

          private:
            MatrixClosureType data;
            SliceType         slice1;
            SliceType         slice2;
        };

        template <typename M>
        struct VectorTemporaryTraits<MatrixRow<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<const MatrixRow<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<MatrixRow<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<const MatrixRow<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<MatrixColumn<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<const MatrixColumn<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<MatrixColumn<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<const MatrixColumn<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<MatrixRange<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<const MatrixRange<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<MatrixRange<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<const MatrixRange<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<MatrixSlice<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct VectorTemporaryTraits<const MatrixSlice<M> > : public VectorTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<MatrixSlice<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>
        struct MatrixTemporaryTraits<const MatrixSlice<M> > : public MatrixTemporaryTraits<M>
        {};

        template <typename M>

        MatrixRow<M>
        row(MatrixExpression<M>& e, typename MatrixRow<M>::SizeType i)
        {
            return MatrixRow<M>(e(), i);
        }

        template <typename M>
        MatrixRow<const M>
        row(const MatrixExpression<M>& e, typename MatrixRow<const M>::SizeType i)
        {
            return MatrixRow<const M>(e(), i);
        }

        template <typename M>
        MatrixColumn<M>
        column(MatrixExpression<M>& e, typename MatrixColumn<M>::SizeType j)
        {
            return MatrixColumn<M>(e(), j);
        }

        template <typename M>
        MatrixColumn<const M>
        column(const MatrixExpression<M>& e, typename MatrixColumn<const M>::SizeType j)
        {
            return MatrixColumn<const M>(e(), j);
        }

        template <typename E>
        MatrixRange<E>
        range(MatrixExpression<E>&                      e,
              const typename MatrixRange<E>::RangeType& r1,
              const typename MatrixRange<E>::RangeType& r2)
        {
            return MatrixRange<E>(e(), r1, r2);
        }

        template <typename E>
        MatrixRange<const E>
        range(const MatrixExpression<E>&                      e,
              const typename MatrixRange<const E>::RangeType& r1,
              const typename MatrixRange<const E>::RangeType& r2)
        {
            return MatrixRange<const E>(e(), r1, r2);
        }

        template <typename E>
        MatrixRange<E>
        range(MatrixExpression<E>&                         e,
              typename MatrixRange<E>::RangeType::SizeType start1,
              typename MatrixRange<E>::RangeType::SizeType stop1,
              typename MatrixRange<E>::RangeType::SizeType start2,
              typename MatrixRange<E>::RangeType::SizeType stop2)
        {
            typedef typename MatrixRange<E>::RangeType RangeType;

            return MatrixRange<E>(e(), RangeType(start1, stop1), RangeType(start2, stop2));
        }

        template <typename E>
        MatrixRange<const E>
        range(const MatrixExpression<E>&                         e,
              typename MatrixRange<const E>::RangeType::SizeType start1,
              typename MatrixRange<const E>::RangeType::SizeType stop1,
              typename MatrixRange<const E>::RangeType::SizeType start2,
              typename MatrixRange<const E>::RangeType::SizeType stop2)
        {
            typedef typename MatrixRange<const E>::RangeType RangeType;

            return MatrixRange<const E>(e(), RangeType(start1, stop1), RangeType(start2, stop2));
        }

        template <typename E>
        MatrixSlice<E>
        slice(MatrixExpression<E>&                      e,
              const typename MatrixSlice<E>::SliceType& s1,
              const typename MatrixSlice<E>::SliceType& s2)
        {
            return MatrixSlice<E>(e(), s1, s2);
        }

        template <typename E>
        MatrixSlice<const E>
        slice(const MatrixExpression<E>&                      e,
              const typename MatrixSlice<const E>::SliceType& s1,
              const typename MatrixSlice<const E>::SliceType& s2)
        {
            return MatrixSlice<const E>(e(), s1, s2);
        }

        template <typename E>
        MatrixSlice<E>
        slice(MatrixExpression<E>&                               e,
              typename MatrixSlice<E>::SliceType::SizeType       start1,
              typename MatrixSlice<E>::SliceType::DifferenceType stride1,
              typename MatrixSlice<E>::SliceType::SizeType       size1,
              typename MatrixSlice<E>::SliceType::SizeType       start2,
              typename MatrixSlice<E>::SliceType::DifferenceType stride2,
              typename MatrixSlice<E>::SliceType::SizeType       size2)
        {
            typedef typename MatrixSlice<E>::SliceType SliceType;

            return MatrixSlice<E>(e(), SliceType(start1, stride1, size1), SliceType(start2, stride2, size2));
        }

        template <typename E>
        MatrixSlice<const E>
        slice(const MatrixExpression<E>&                               e,
              typename MatrixSlice<const E>::SliceType::SizeType       start1,
              typename MatrixSlice<const E>::SliceType::DifferenceType stride1,
              typename MatrixSlice<const E>::SliceType::SizeType       size1,
              typename MatrixSlice<const E>::SliceType::SizeType       start2,
              typename MatrixSlice<const E>::SliceType::DifferenceType stride2,
              typename MatrixSlice<const E>::SliceType::SizeType       size2)
        {
            typedef typename MatrixSlice<const E>::SliceType SliceType;

            return MatrixSlice<const E>(e(), SliceType(start1, stride1, size1), SliceType(start2, stride2, size2));
        }
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_MATRIXPROXY_HPP
