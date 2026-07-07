/* 
 * AffineTransform.hpp 
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
 * \brief Matrix types for various affine transformations.
 */

#ifndef CDPL_MATH_AFFINETRANSFORM_HPP
#define CDPL_MATH_AFFINETRANSFORM_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <cstddef>
#include <vector>
#include <utility>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/Expression.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename V>
        class MatrixReference;
        template <typename T, typename A>
        class Vector;
        template <typename T, typename A>
        class Matrix;

        /**
         * \brief <em>N&times;N</em> rotation matrix backed by a unit quaternion (or an axis-angle representation).
         *
         * The first <em>3&times;3</em> block holds the rotation, the remaining diagonal entries are \e 1 (identity)
         * and all other entries are \e 0. The size \e N is configurable and typically chosen to fit the surrounding
         * coordinate system (e.g. \e 4 for homogeneous transformations).
         *
         * \tparam T The scalar value type.
         */
        template <typename T>
        class RotationMatrix : public MatrixContainer<RotationMatrix<T> >
        {

            typedef RotationMatrix<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Element reference type (always a \c const reference — elements are computed).
             */
            typedef const T                               Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T                               ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this matrix appears inside another expression.
             */
            typedef MatrixReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this matrix appears inside another expression.
             */
            typedef const MatrixReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary matrix type used by expression template machinery.
             */
            typedef Matrix<T, std::vector<T> >            MatrixTemporaryType;

            /**
             * \brief Concrete temporary vector type used when assembling vectors from this matrix.
             */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an <em>N&times;N</em> rotation matrix from the unit quaternion \a q.
             * \tparam E The quaternion expression type.
             * \param n The matrix dimension \a N.
             * \param q The unit quaternion expressing the rotation.
             */
            template <typename E>
            RotationMatrix(SizeType n, const QuaternionExpression<E>& q):
                size(n)
            {
                set(q);
            }

            /**
             * \brief Constructs an <em>N&times;N</em> rotation matrix from an axis-angle representation.
             * \tparam T1 The rotation angle scalar type.
             * \tparam T2 The x-axis component scalar type.
             * \tparam T3 The y-axis component scalar type.
             * \tparam T4 The z-axis component scalar type.
             * \param n The matrix dimension \a N.
             * \param w The rotation angle (in radians).
             * \param ux The x-component of the rotation axis (unit vector).
             * \param uy The y-component of the rotation axis (unit vector).
             * \param uz The z-component of the rotation axis (unit vector).
             */
            template <typename T1, typename T2, typename T3, typename T4>
            RotationMatrix(SizeType n, const T1& w, const T2& ux, const T3& uy, const T4& uz):
                size(n)
            {
                set(w, ux, uy, uz);
            }

            /**
             * \brief Constructs a copy of the rotation matrix \a m.
             * \param m The rotation matrix to copy.
             */
            RotationMatrix(const RotationMatrix& m):
                size(m.size)
            {
                std::copy(m.data, m.data + 4, data);
            }

            /**
             * \brief Sets the rotation from the unit quaternion \a q.
             * \tparam E The quaternion expression type.
             * \param q The unit quaternion expressing the rotation.
             */
            template <typename E>
            void set(const QuaternionExpression<E>& q)
            {
                data[0] = q().getC1();
                data[1] = q().getC2();
                data[2] = q().getC3();
                data[3] = q().getC4();
            }

            /**
             * \brief Sets the rotation from an axis-angle representation.
             * \tparam T1 The rotation angle scalar type.
             * \tparam T2 The x-axis component scalar type.
             * \tparam T3 The y-axis component scalar type.
             * \tparam T4 The z-axis component scalar type.
             * \param w The rotation angle (in radians).
             * \param ux The x-component of the rotation axis (unit vector).
             * \param uy The y-component of the rotation axis (unit vector).
             * \param uz The z-component of the rotation axis (unit vector).
             */
            template <typename T1, typename T2, typename T3, typename T4>
            void set(const T1& w, const T2& ux, const T3& uy, const T4& uz)
            {
                data[0] = std::cos(w / 2.0);
                data[1] = std::sin(w / 2.0) * ux;
                data[2] = std::sin(w / 2.0) * uy;
                data[3] = std::sin(w / 2.0) * uz;
            }

            /**
             * \brief Returns the rotation matrix element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The matrix element (computed from the stored unit quaternion).
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                if (i >= 3 || i >= size || j >= 3 || j >= size)
                    return (i == j ? ValueType(1) : ValueType());

                switch (i) {

                    case 0:
                        switch (j) {

                            case 0:
                                // a2 + b2 - c2 - d2
                                return (data[0] * data[0] + data[1] * data[1] - data[2] * data[2] - data[3] * data[3]);

                            case 1:
                                // 2(bc - ad)
                                return 2 * (data[1] * data[2] - data[0] * data[3]);

                            case 2:
                                // 2(bd + ac)
                                return 2 * (data[1] * data[3] + data[0] * data[2]);

                            default:
                                return ValueType();
                        }

                    case 1:
                        switch (j) {

                            case 0:
                                // 2(bc + ad)
                                return 2 * (data[1] * data[2] + data[0] * data[3]);

                            case 1:
                                // a2 - b2 + c2 - d2
                                return (data[0] * data[0] - data[1] * data[1] + data[2] * data[2] - data[3] * data[3]);

                            case 2:
                                // 2(cd - ab)
                                return 2 * (data[2] * data[3] - data[0] * data[1]);

                            default:
                                return ValueType();
                        }

                    case 2:
                        switch (j) {

                            case 0:
                                // 2(bd - ac)
                                return 2 * (data[1] * data[3] - data[0] * data[2]);

                            case 1:
                                // 2(cd + ab)
                                return 2 * (data[2] * data[3] + data[0] * data[1]);

                            case 2:
                                // a2 - b2 - c2 + d2
                                return (data[0] * data[0] - data[1] * data[1] - data[2] * data[2] + data[3] * data[3]);

                            default:
                                return ValueType();
                        }

                    default:
                        return (i == j ? ValueType(1) : ValueType());
                }
            }

            /**
             * \brief Tells whether the matrix is empty (size zero).
             * \return \c true if \a N is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the dimension \a N (the row count).
             * \return \a N.
             */
            SizeType getSize1() const
            {
                return size;
            }

            /**
             * \brief Returns the dimension \a N (the column count).
             * \return \a N.
             */
            SizeType getSize2() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum row count.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum column count.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimension and the underlying quaternion components from \a m.
             * \param m The source rotation matrix.
             * \return A reference to itself.
             */
            RotationMatrix& operator=(const RotationMatrix& m)
            {
                if (this != &m) {
                    std::copy(m.data, m.data + 4, data);
                    size = m.size;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimension and the underlying quaternion components with \a m.
             * \param m The rotation matrix to swap with.
             */
            void swap(RotationMatrix& m)
            {
                if (this != &m) {
                    std::swap_ranges(data, data + 4, m.data);
                    std::swap(size, m.size);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first rotation matrix.
             * \param m2 The second rotation matrix.
             */
            friend void swap(RotationMatrix& m1, RotationMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the matrix dimension to \a n (the underlying quaternion is left unchanged).
             * \param n The new dimension.
             */
            void resize(SizeType n)
            {
                size = n;
            }

          private:
            typedef ValueType ArrayType[4];

            SizeType  size;
            ArrayType data;
        };

        /**
         * \brief <em>N&times;N</em> diagonal scaling matrix.
         *
         * The diagonal entries hold the per-axis scale factors; all off-diagonal entries are \e 0. The size \f$ N \f$
         * is configurable so the matrix can be combined with homogeneous coordinates.
         *
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ScalingMatrix : public MatrixContainer<ScalingMatrix<T> >
        {

            typedef ScalingMatrix<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Element reference type (always a \c const reference — elements are computed).
             */
            typedef const T                               Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T                               ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this matrix appears inside another expression.
             */
            typedef MatrixReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this matrix appears inside another expression.
             */
            typedef const MatrixReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary matrix type used by expression template machinery.
             */
            typedef Matrix<T, std::vector<T> >            MatrixTemporaryType;

            /**
             * \brief Concrete temporary vector type used when assembling vectors from this matrix.
             */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an <em>N&times;N</em> scaling matrix with the supplied per-axis scale factors.
             * \param n The matrix dimension \a N.
             * \param sx The x-axis scale factor (default: 1).
             * \param sy The y-axis scale factor (default: 1).
             * \param sz The z-axis scale factor (default: 1).
             */
            explicit ScalingMatrix(SizeType n, const ValueType& sx = ValueType(1),
                                   const ValueType& sy = ValueType(1), const ValueType& sz = ValueType(1)):
                size(n)
            {
                set(sx, sy, sz);
            }

            /**
             * \brief Constructs a copy of the scaling matrix \a m.
             * \param m The scaling matrix to copy.
             */
            ScalingMatrix(const ScalingMatrix& m):
                size(m.size)
            {
                std::copy(m.data, m.data + 3, data);
            }

            /**
             * \brief Sets the per-axis scale factors.
             * \param sx The x-axis scale factor (default: 1).
             * \param sy The y-axis scale factor (default: 1).
             * \param sz The z-axis scale factor (default: 1).
             */
            void set(const ValueType& sx = ValueType(1), const ValueType& sy = ValueType(1),
                     const ValueType& sz = ValueType(1))
            {
                data[0] = sx;
                data[1] = sy;
                data[2] = sz;
            }

            /**
             * \brief Returns the scaling matrix element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return The corresponding axis scaling factor on a diagonal position and \e 0 off the diagonal.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                if (i != j)
                    return ValueType();

                if (i < size && i < 3)
                    return data[i];

                return ValueType(1);
            }

            /**
             * \brief Tells whether the matrix is empty (size zero).
             * \return \c true if \a N is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the dimension \a N (the row count).
             * \return \a N.
             */
            SizeType getSize1() const
            {
                return size;
            }

            /**
             * \brief Returns the dimension \a N (the column count).
             * \return \a N.
             */
            SizeType getSize2() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum row count.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum column count.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimension and the per-axis scale factors from \a m.
             * \param m The source scaling matrix.
             * \return A reference to itself.
             */
            ScalingMatrix& operator=(const ScalingMatrix& m)
            {
                if (this != &m) {
                    std::copy(m.data, m.data + 3, data);
                    size = m.size;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimension and the per-axis scale factors with \a m.
             * \param m The scaling matrix to swap with.
             */
            void swap(ScalingMatrix& m)
            {
                if (this != &m) {
                    std::swap_ranges(data, data + 3, m.data);
                    std::swap(size, m.size);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first scaling matrix.
             * \param m2 The second scaling matrix.
             */
            friend void swap(ScalingMatrix& m1, ScalingMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the matrix dimension to \a n (the scale factors are left unchanged).
             * \param n The new dimension.
             */
            void resize(SizeType n)
            {
                size = n;
            }

          private:
            typedef ValueType ArrayType[3];

            SizeType  size;
            ArrayType data;
        };

        /**
         * \brief <em>N&times;N</em> translation matrix in homogeneous coordinates.
         *
         * The diagonal entries are all 1; the last column (above the diagonal) holds the per-axis translation
         * components; all other entries are \e 0. The size \f$ N \f$ is configurable to fit the embedding coordinate
         * dimension plus one (e.g. \e 4 for translations of 3D points in homogeneous form).
         *
         * \tparam T The scalar value type.
         */
        template <typename T>
        class TranslationMatrix : public MatrixContainer<TranslationMatrix<T> >
        {

            typedef TranslationMatrix<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Element reference type (always a \c const reference — elements are computed).
             */
            typedef const T                               Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T                               ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this matrix appears inside another expression.
             */
            typedef MatrixReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this matrix appears inside another expression.
             */
            typedef const MatrixReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary matrix type used by expression template machinery.
             */
            typedef Matrix<T, std::vector<T> >            MatrixTemporaryType;

            /**
             * \brief Concrete temporary vector type used when assembling vectors from this matrix.
             */
            typedef Vector<T, std::vector<T> >            VectorTemporaryType;

            /**
             * \brief Constructs an <em>N&times;N</em> translation matrix with the supplied per-axis translation components.
             * \param n The matrix dimension \a N.
             * \param tx The x-axis translation (default: 0).
             * \param ty The y-axis translation (default: 0).
             * \param tz The z-axis translation (default: 0).
             */
            explicit TranslationMatrix(SizeType n, const ValueType& tx = ValueType(),
                                       const ValueType& ty = ValueType(), const ValueType& tz = ValueType()):
                size(n)
            {
                set(tx, ty, tz);
            }

            /**
             * \brief Constructs a copy of the translation matrix \a m.
             * \param m The translation matrix to copy.
             */
            TranslationMatrix(const TranslationMatrix& m):
                size(m.size)
            {
                std::copy(m.data, m.data + 3, data);
            }

            /**
             * \brief Sets the per-axis translation components.
             * \param tx The x-axis translation (default: 0).
             * \param ty The y-axis translation (default: 0).
             * \param tz The z-axis translation (default: 0).
             */
            void set(const ValueType& tx = ValueType(), const ValueType& ty = ValueType(),
                     const ValueType& tz = ValueType())
            {
                data[0] = tx;
                data[1] = ty;
                data[2] = tz;
            }

            /**
             * \brief Returns the translation matrix element at (\a i, \a j).
             * \param i The zero-based row index.
             * \param j The zero-based column index.
             * \return \e 1 on the diagonal, the corresponding translation component in the last column (rows 0-2) and \e 0 elsewhere.
             * \throw Base::IndexError if either index is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2(), "Index out of range", Base::IndexError);

                if (i == j)
                    return ValueType(1);

                if (j == (size - 1) && i < size && i < 3)
                    return data[i];

                return ValueType();
            }

            /**
             * \brief Tells whether the matrix is empty (size zero).
             * \return \c true if \a N is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the dimension \a N (the row count).
             * \return \a N.
             */
            SizeType getSize1() const
            {
                return size;
            }

            /**
             * \brief Returns the dimension \a N (the column count).
             * \return \a N.
             */
            SizeType getSize2() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum representable row count.
             * \return The maximum row count.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable column count.
             * \return The maximum column count.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the dimension and the translation components from \a m.
             * \param m The source translation matrix.
             * \return A reference to itself.
             */
            TranslationMatrix& operator=(const TranslationMatrix& m)
            {
                if (this != &m) {
                    std::copy(m.data, m.data + 3, data);
                    size = m.size;
                }

                return *this;
            }

            /**
             * \brief Swaps the dimension and the translation components with \a m.
             * \param m The translation matrix to swap with.
             */
            void swap(TranslationMatrix& m)
            {
                if (this != &m) {
                    std::swap_ranges(data, data + 3, m.data);
                    std::swap(size, m.size);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param m1 The first translation matrix.
             * \param m2 The second translation matrix.
             */
            friend void swap(TranslationMatrix& m1, TranslationMatrix& m2)
            {
                m1.swap(m2);
            }

            /**
             * \brief Resizes the matrix dimension to \a n (the translation components are left unchanged).
             * \param n The new dimension.
             */
            void resize(SizeType n)
            {
                size = n;
            }

          private:
            typedef ValueType ArrayType[3];

            SizeType  size;
            ArrayType data;
        };

        /**
         * \brief Scaling matrix holding floating-point values of type <tt>float</tt>.
         */
        typedef ScalingMatrix<float>         FScalingMatrix;
        
        /**
         * \brief Scaling matrix holding floating-point values of type <tt>double</tt>.
         */
        typedef ScalingMatrix<double>        DScalingMatrix;
        
        /**
         * \brief Scaling matrix holding integer values of type <tt>long</tt>.
         */
        typedef ScalingMatrix<long>          LScalingMatrix;
        
        /**
         * \brief Scaling matrix holding unsigned integer values of type <tt>unsigned long</tt>.
         */
        typedef ScalingMatrix<unsigned long> ULScalingMatrix;

        /**
         * \brief Rotation matrix holding floating-point values of type <tt>float</tt>.
         */
        typedef RotationMatrix<float>         FRotationMatrix;
        
        /**
         * \brief Rotation matrix holding floating-point values of type <tt>double</tt>.
         */
        typedef RotationMatrix<double>        DRotationMatrix;
        
        /**
         * \brief Rotation matrix holding integer values of type <tt>long</tt>.
         */
        typedef RotationMatrix<long>          LRotationMatrix;
        
        /**
         * \brief Rotation matrix holding unsigned integer values of type <tt>unsigned long</tt>.
         */
        typedef RotationMatrix<unsigned long> ULRotationMatrix;

        /**
         * \brief Translation matrix holding floating-point values of type <tt>float</tt>.
         */
        typedef TranslationMatrix<float>         FTranslationMatrix;
        
        /**
         * \brief Translation matrix holding floating-point values of type <tt>double</tt>.
         */
        typedef TranslationMatrix<double>        DTranslationMatrix;
        
        /**
         * \brief Translation matrix holding integer values of type <tt>long</tt>.
         */
        typedef TranslationMatrix<long>          LTranslationMatrix;
        
        /**
         * \brief Translation matrix holding unsigned integer values of type <tt>unsigned long</tt>.
         */
        typedef TranslationMatrix<unsigned long> ULTranslationMatrix;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_AFFINETRANSFORM_HPP
