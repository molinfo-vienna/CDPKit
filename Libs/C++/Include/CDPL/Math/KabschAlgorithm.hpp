/* 
 * KabschAlgorithm.hpp 
 *
 * Copyright (C) 2010-2012 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of the Kabsch algorithm.
 */

#ifndef CDPL_MATH_KABSCHALGORITHM_HPP
#define CDPL_MATH_KABSCHALGORITHM_HPP

#include <cstddef>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Implementation of the Kabsch algorithm [\ref KABA].
         *
         * Finds the least Root Mean Square Distance between two sets of \f$ N \f$ points in \f$ D \f$ dimensions
         * and the rigid transformation (i.e. translation and rotation) to employ in order to bring one set that close
         * to the other.
         *
         * Note that the points are paired, i.e. it is known which point in one set should be compared to a given point in the other set.
         * It is possible to give weights to the points. Those weights are determined a priori and do not depend on the distances.
         *
         * The convention is used that points are column vectors of the input matrices. 
         */
        template <typename T>
        class KabschAlgorithm
        {

          public:
            typedef T         ValueType;
            typedef Matrix<T> MatrixType;
            typedef Vector<T> VectorType;

            /**
             * \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points
             *        \a points with a corresponding set of reference points \a ref_points at a minimum RMSD.
             *
             * \param points A \f$ D \times N \f$-matrix storing the points to align as column vectors.
             * \param ref_points A \f$ D \times N \f$-matrix storing the reference points as column vectors.
             * \param weights A \f$ N \f$-dimensional vector storing the non-negative weights that are assigned to the points.
             * \param do_center \c true if centering of the data points needs to be performed, and \c false if not.
             * \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or \a 0 if no limit. 
             * \return \c true if convergence in the internal SV-decomposition has been reached in \a max_svd_iter iterations, and \c false otherwise. 
             * \pre <tt>points().getSize1() == ref_points().getSize1()</tt>
             * \pre <tt>points().getSize2() == ref_points().getSize2()</tt>
             * \pre <tt>weights().getSize() == points().getSize2()</tt>
             * \pre <tt>weights()(i) >= 0 && sum(weights) > 0</tt> 
             * \throw Base::SizeError or Base::ValueError if preconditions got violated.
             */
            template <typename M1, typename M2, typename V>
            bool align(const MatrixExpression<M1>& points, const MatrixExpression<M2>& ref_points, const VectorExpression<V>& weights,
                       bool do_center = true, std::size_t max_svd_iter = 0)
            {

                typedef typename CommonType<typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type,
                                            typename V::SizeType>::Type SizeType;

                SizeType dim     = points().getSize1();
                SizeType num_pts = points().getSize2();

                CDPL_MATH_CHECK(dim == SizeType(ref_points().getSize1()) && num_pts == SizeType(ref_points().getSize2()),
                                "KabschAlgorithm: Point-sets of different size", Base::SizeError);

                CDPL_MATH_CHECK(num_pts == SizeType(weights().getSize()),
                                "KabschAlgorithm: Number of points != number of weights", Base::SizeError);

                ValueType w_sum = ValueType();

                for (SizeType i = 0; i < num_pts; i++) {
                    CDPL_MATH_CHECK(ValueType(weights()(i)) >= ValueType(), "KabschAlgorithm: weights must be non-negative entries", Base::ValueError);
                    w_sum += weights()(i);
                }

                CDPL_MATH_CHECK(w_sum > ValueType(), "KabschAlgorithm: weights must contain some positive entry", Base::ValueError);

                if (do_center) {
                    prod(points, weights, centroid1);
                    prod(ref_points, weights, centroid2);

                    centroid1 /= w_sum;
                    centroid2 /= w_sum;

                    tmpPoints.resize(dim, num_pts, false);
                    tmpPoints.assign(points);

                    tmpRefPoints.resize(dim, num_pts, false);
                    tmpRefPoints.assign(ref_points);

                    for (SizeType i = 0; i < num_pts; i++) {
                        column(tmpPoints, i).minusAssign(centroid1) *= weights()(i) / w_sum;
                        column(tmpRefPoints, i).minusAssign(centroid2);
                    }

                } else {
                    tmpPoints.resize(dim, num_pts, false);
                    tmpPoints.assign(points);

                    for (SizeType i = 0; i < num_pts; i++)
                        column(tmpPoints, i) *= weights()(i) / w_sum;
                }

                covarMatrix.resize(dim, dim, false);

                if (do_center)
                    prod(tmpPoints, trans(tmpRefPoints), covarMatrix);
                else
                    prod(tmpPoints, trans(ref_points), covarMatrix);

                return align(dim, do_center, max_svd_iter);
            }

            /**
             * \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points
             *        \a points with a corresponding set of reference points \a ref_points at a minimum RMSD.
             *
             * \param points A \f$ D \times N \f$-matrix storing the points to align as column vectors.
             * \param ref_points A \f$ D \times N \f$-matrix storing the reference points as column vectors.
             * \param do_center \c true if centering of the data points needs to be performed, and \c false if not.
             * \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or \a 0 if no limit. 
             * \return \c true if convergence in the internal SV-decomposition has been reached in \a max_svd_iter iterations, and \c false otherwise. 
             * \pre <tt>points().getSize1() == ref_points().getSize1()</tt>
             * \pre <tt>points().getSize2() == ref_points().getSize2()</tt>
             * \throw Base::SizeError if preconditions got violated.
             */
            template <typename M1, typename M2>
            bool align(const MatrixExpression<M1>& points, const MatrixExpression<M2>& ref_points,
                       bool do_center = true, std::size_t max_svd_iter = 0)
            {

                typedef typename CommonType<typename M1::SizeType, typename M2::SizeType>::Type SizeType;

                SizeType dim     = points().getSize1();
                SizeType num_pts = points().getSize2();

                CDPL_MATH_CHECK(dim == SizeType(ref_points().getSize1()) && num_pts == SizeType(ref_points().getSize2()),
                                "KabschAlgorithm: Point-sets of different size", Base::SizeError);

                if (do_center) {
                    prod(points, ScalarVector<ValueType>(num_pts, ValueType(1) / num_pts), centroid1);
                    prod(ref_points, ScalarVector<ValueType>(num_pts, ValueType(1) / num_pts), centroid2);

                    tmpPoints.resize(dim, num_pts, false);
                    tmpPoints.assign(points);

                    tmpRefPoints.resize(dim, num_pts, false);
                    tmpRefPoints.assign(ref_points);

                    for (SizeType i = 0; i < num_pts; i++) {
                        column(tmpPoints, i).minusAssign(centroid1);
                        column(tmpRefPoints, i).minusAssign(centroid2);
                    }
                }

                covarMatrix.resize(dim, dim, false);

                if (do_center)
                    prod(tmpPoints, trans(tmpRefPoints), covarMatrix);
                else
                    prod(points, trans(ref_points), covarMatrix);

                return align(dim, do_center, max_svd_iter);
            }

            const MatrixType& getTransform() const
            {
                return transform;
            }

          private:
            template <typename SizeType>
            bool align(SizeType dim, bool do_center, std::size_t max_svd_iter)
            {
                svdW.resize(dim);
                svdV.resize(dim, dim, false);

                if (!svDecompose(covarMatrix, svdW, svdV, max_svd_iter))
                    return false;

                if (det(prod(covarMatrix, trans(svdV))) < ValueType())
                    column(svdV, dim - 1) *= -ValueType(1);

                SizeType xform_dim = dim + 1;

                transform.resize(xform_dim, xform_dim, false);

                range(transform, 0, dim, 0, dim).assign(prod(svdV, trans(covarMatrix)));

                MatrixRow<MatrixType>    last_row(transform, dim);
                MatrixColumn<MatrixType> last_col(transform, dim);

                range(last_row, 0, dim).assign(ZeroVector<ValueType>(dim));

                if (do_center)
                    range(last_col, 0, dim).assign(centroid2 - prod(range(transform, 0, dim, 0, dim), centroid1));
                else
                    range(last_col, 0, dim).assign(ZeroVector<ValueType>(dim));

                transform(dim, dim) = ValueType(1);

                return true;
            }

            MatrixType transform;
            MatrixType tmpPoints;
            MatrixType tmpRefPoints;
            MatrixType covarMatrix;
            VectorType svdW;
            MatrixType svdV;
            VectorType centroid1;
            VectorType centroid2;
        };
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_KABSCHALGORITHM_HPP
