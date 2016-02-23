/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVDecomposition.hpp 
 *
 * Copyright (C) 2010-2012 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of matrix singular value decomposition and associated operations.
 */

#ifndef CDPL_MATH_SVDECOMPOSITION_HPP
#define CDPL_MATH_SVDECOMPOSITION_HPP

#include <cstddef>
#include <cmath>
#include <limits>

#include "CDPL/Math/Config.hpp"
#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		/**
		 * \brief Computes the <em>Singular Value Decomposition</em> [\ref WSVD] \f$ A = UWV^T \f$ of a
		 *        \f$ M \times N \f$-dimensional matrix \a a.
		 *
		 * The matrix \f$ U \f$ replaces \a a on output. The diagonal matrix of singular values
		 * \f$ W \f$ is output as the \f$ N \f$-dimensional vector \a w. The matrix \f$ V \f$
		 * (not the transpose \f$ V^T \f$) is output as the \f$ N \times N \f$-dimensional matrix
		 * \a v. For implementation details see [\ref NRIC].
		 *
		 * \param a The decomposed \f$ M \times N \f$-matrix \f$ A \f$ which will be replaced by \f$ U \f$
		 *          on output.
		 * \param w The \f$ N \f$-dimensional output vector \f$ W \f$ holding the singular 
		 *          values.
		 * \param v The \f$ N \times N \f$-dimensional output matrix \f$ V \f$.
		 * \param max_iter The maximum number of iterations to perform, or \a 0 if no limit. 
		 * \return \c true if convergence has been reached in \a max_iter
		 *         iterations, and \c false otherwise. 
		 * \pre <tt>w().getSize() >= a().getSize2()</tt>, <tt>v().getSize1() >= a().getSize2() and v().getSize2() >= a().getSize2()</tt>. 
		 * \throw Base::SizeError if preconditions are violated.
		 */
		template <typename A, typename W, typename V>
		bool svDecompose(MatrixExpression<A> &a, VectorExpression<W>& w, MatrixExpression<V> &v, std::size_t max_iter = 0)
		{
			typedef typename CommonType<typename CommonType<typename A::ValueType, typename W::ValueType>::Type, 
				typename V::ValueType>::Type ValueType;
			
			typedef typename CommonType<typename CommonType<typename A::SizeType, typename W::SizeType>::Type,
				typename V::SizeType>::Type SizeType;

			SizeType m = a().getSize1();
			SizeType n = a().getSize2();

			CDPL_MATH_CHECK(SizeType(w().getSize()) >= n && SizeType(v().getSize1()) >= n && SizeType(v().getSize2()) >= n, 
						   "svDecompose: Preconditions violated",  Base::SizeError);

			Vector<ValueType> rv1(n);
			SizeType l;
			ValueType g, scale, anorm, s;

			g = scale = anorm = ValueType(0);

			for (SizeType i = 0; i < n; i++) {
				l = i + 2;
				rv1(i) = scale * g;
				g = s = scale = ValueType(0);
				
				if (i < m) {
					for (SizeType k = i; k < m; k++)
						scale += TypeTraits<ValueType>::abs(a()(k, i));
				
					if (scale != ValueType(0)) {
						for (SizeType k = i; k < m; k++) {
							a()(k, i) /= scale;
							s += a()(k, i) * a()(k, i);
						}
						
						ValueType f = a()(i, i);
						
						g = -sign(TypeTraits<ValueType>::sqrt(s), f);
						
						ValueType h = f * g - s;
						
						a()(i, i) = f - g;
						
						for (SizeType j = l - 1; j < n; j++) {
							s = ValueType(0);

							for (SizeType k = i; k < m; k++)
								s += a()(k, i) * a()(k, j);
						
							f = s / h;
							
							for (SizeType k = i; k < m; k++) 
								a()(k, j) += f * a()(k, i);
						}
						
						for (SizeType k = i; k < m; k++) 
							a()(k, i) *= scale;
					}
				}

				w()(i) = scale * g;
				g = s = scale = ValueType(0);

				if (i + 1 <= m && i + 1 != n) {
					for (SizeType k = l - 1; k < n; k++)
						scale += TypeTraits<ValueType>::abs(a()(i, k));
					
					if (scale != ValueType(0)) {
						for (SizeType k = l - 1; k < n; k++) {
							a()(i, k) /= scale;
							s += a()(i, k) * a()(i, k);
						}
					
						ValueType f = a()(i, l - 1);
						
						g = -sign(TypeTraits<ValueType>::sqrt(s), f);
						
						ValueType h = f * g - s;
						
						a()(i, l - 1) = f - g;
						
						for (SizeType k = l - 1; k < n; k++) 
							rv1(k) = a()(i, k) / h;
						
						for (SizeType j = l - 1; j < m; j++) {
							s = ValueType(0);

							for (SizeType k = l - 1; k < n; k++) 
								s += a()(j, k) * a()(i, k);

							for (SizeType k = l - 1; k < n; k++) 
								a()(j, k) += s * rv1(k);
						}

						for (SizeType k = l - 1; k < n; k++) 
							a()(i, k) *= scale;
					}
				}

				anorm = std::max(anorm, (TypeTraits<ValueType>::abs(w()(i)) + TypeTraits<ValueType>::abs(rv1(i))));
			}

			for (SizeType ic = n; ic > 0; ic--) {
				SizeType i = ic - 1;

				if (i < n - 1) {
					if (g != ValueType(0)) {
						for (SizeType j = l; j < n; j++)
							v()(j, i) = (a()(i, j) / a()(i, l)) / g;
					
						for (SizeType j = l; j < n; j++) {
							s = ValueType(0);
 
							for (SizeType k = l; k < n; k++)
								s += a()(i, k) * v()(k, j);
							
							for (SizeType k = l; k < n; k++) 
								v()(k, j) += s * v()(k, i);
						}
					}
					
					for (SizeType j = l; j < n; j++) 
						v()(i, j) = v()(j, i) = ValueType(0);
				}

				v()(i, i) = ValueType(1);
				g = rv1(i);
				l = i;
			}

			for (SizeType ic = std::min(m, n); ic > 0; ic--) {
				SizeType i = ic - 1;

				l = ic;
				g = w()(i);
				
				for (SizeType j = l; j < n; j++) 
					a()(i, j) = ValueType(0);
				
				if (g != ValueType(0)) {
					g = ValueType(1) / g;
					
					for (SizeType j = l; j < n; j++) {
						s = ValueType(0);

						for (SizeType k = l; k < m; k++) 
							s += a()(k, i) * a()(k, j);
						
						ValueType f = (s / a()(i, i)) * g;
						
						for (SizeType k = i; k < m; k++) 
							a()(k, j) += f * a()(k, i);
					}

					for (SizeType j = i; j < m; j++) 
						a()(j, i) *= g;
				
				} else 
					for (SizeType j = i; j < m; j++) 
						a()(j, i) = ValueType(0);
				
				++a()(i, i);
			}

			for (SizeType kc = n; kc > 0; kc--) {
				SizeType k = kc - 1;
				SizeType nm = 0;

				for (std::size_t its = 0; max_iter == 0 || its < max_iter; its++) {
					bool flag = true;
					
					for (SizeType lc = k + 1; lc > 0; lc--) {
						l = lc - 1;
						nm = l - 1;
						
						if (TypeTraits<ValueType>::abs(rv1(l)) + anorm == anorm) {
							flag = false;
							break;
						}
						
						if (TypeTraits<ValueType>::abs(w()(nm)) + anorm == anorm) 
							break;
					}

					if (flag) {
						ValueType c = ValueType(0);
						
						s = ValueType(1);

						for (SizeType i = l; i < k + 1; i++) {
							ValueType f = s * rv1(i);
							
							rv1(i) = c * rv1(i);

							if (TypeTraits<ValueType>::abs(f) + anorm == anorm) 
								break;

							g = w()(i);
							
							ValueType h = pythag(f, g);
							
							w()(i) = h;
							h = ValueType(1) / h;
							c = g * h;
							s = -f * h;

							for (SizeType j = 0; j < m; j++) {
								ValueType y = a()(j, nm);
								ValueType z = a()(j, i);
								
								a()(j, nm) = y * c + z * s;
								a()(j, i) = z * c - y * s;
							}
						}
					}

					ValueType z = w()(k);
					
					if (l == k) {
						if (z < ValueType(0)) {
							w()(k) = -z;

							for (SizeType j = 0; j < n; j++) 
								v()(j, k) = -v()(j, k);
						}
						break;
					}
					
					if (max_iter > 0 && its >= max_iter - 1)
						return false;
					
					ValueType x = w()(l);
					ValueType c = ValueType(1);
					
					nm = k - 1;
					
					ValueType y = w()(nm);
					
					g = rv1(nm);
					
					ValueType h = rv1(k);
					ValueType f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
					
					g = pythag(f, ValueType(1));
					f = ((x - z) * (x + z) + h * ((y / (f + sign(g, f))) - h)) / x;
					s = ValueType(1);
				
					for (SizeType j = l; j <= nm; j++) {
						SizeType i = j + 1;

						g = rv1(i);
						y = w()(i);
						h = s * g;
						g = c * g;
						z = pythag(f, h);
						rv1(j) = z;
						c = f / z;
						s = h / z;
						f = x * c + g * s;
						g = g * c - x * s;
						h = y * s;
						y *= c;
					
						for (SizeType jj = 0; jj < n; jj++) {
							x = v()(jj, j);
							z = v()(jj, i);
							v()(jj, j) = x * c + z * s;
							v()(jj, i) = z * c - x * s;
						}
						
						z = pythag(f, h);
						w()(j) = z;
						
						if (z) {
							z = ValueType(1) / z;
							c = f * z;
							s = h * z;
						}
						
						f = c * g + s * y;
						x = c * y - s * g;
						
						for (SizeType jj = 0; jj < m; jj++) {
							y = a()(jj, j);
							z = a()(jj, i);
							a()(jj, j) = y * c + z * s;
							a()(jj, i) = z * c - y * s;
						}
					}

					rv1(l) = ValueType(0);
					rv1(k) = f;
					w()(k) = x;
				}
			}

			// reordering

			SizeType inc= 1;
			Vector<ValueType> su(m);
			Vector<ValueType>& sv = rv1;

			do {
				inc *= 3; 
				inc++; 
		
			} while (inc <= n);
	
			do {
				inc /= 3;
				
				for (SizeType i = inc; i < n;i++) {
					ValueType sw = w()(i);
				
					for (SizeType k = 0; k < m; k++)
						su(k) = a()(k, i);
			
					for (SizeType k = 0; k < n; k++)
						sv(k) = v()(k, i);
					
					SizeType j = i;
			
					while (w()(j - inc) < sw) {
						w()(j) = w()(j - inc);
				
						for (SizeType k = 0; k < m; k++)
							a()(k, j) = a()(k, j - inc);

						for (SizeType k = 0; k < n; k++) 
							v()(k, j) = v()(k, j - inc);
				
						j -= inc;
				
						if (j < inc)
							break;
					}
			
					w()(j) = sw;
			
					for (SizeType k = 0; k < m; k++)
						a()(k, j) = su(k);

					for (SizeType k = 0; k < n; k++) 
						v()(k, j) = sv(k);

				}

			} while (inc > 1);

			for (SizeType k = 0; k < n; k++) {
				SizeType s = 0;
		
				for (SizeType i = 0; i < m; i++)
					if (a()(i, k) < typename A::ValueType(0)) 
						s++;
		
				for (SizeType j = 0; j < n; j++)
					if (v()(j, k) < typename V::ValueType(0))
						s++;
		
				if (s > (m + n) / 2) {
					for (SizeType i = 0; i < m; i++)
						a()(i, k) = -a()(i, k);
			
					for (SizeType j = 0; j < n; j++)
						v()(j, k) = -v()(j, k);
				}
			}

			return true;
		}

		/**
		 * \brief Solves \f$ A \cdot X = B \f$ for a vector \f$ X \f$ where \f$ A \f$
		 *        is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
		 *
		 * The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular
		 * value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the
		 * \f$ M \times N \f$-dimensional matrix \a u, \f$ W \f$ by the \f$ N \f$-dimensional
		 * vector \a w, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix \a v.
		 * The right-hand side vector \f$ B \f$ is given by the \f$ M \f$-dimensional vector \a b,
		 * and \a x is the \f$ N \f$-dimensional output solution vector \f$ X \f$. No input 
		 * quantities are destroyed, so the routine may be called sequentially with different 
		 * arguments \a b. For implementation details see [\ref NRIC]. 
		 *
		 * \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
		 * \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular 
		 *          values of \f$ A \f$.
		 * \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
		 * \param b The \f$ M \f$-dimensional right-hand side vector \f$ B \f$. 
		 * \param x The \f$ N \f$-dimensional output solution vector \f$ X \f$.
		 * \pre <tt>w.getSize() == u.getSize2()</tt>, <tt>v.getSize1() == u.getSize2() && 
		 *      v.getSize2() == u.getSize2()</tt>, <tt>x.getSize() == u.getSize2())</tt> and
		 *      <tt>b.getSize() == u.getSize1()</tt>.
		 * \see svDecomposition()
		 */
		template <typename U, typename W, typename V, typename B, typename X>
		void svSubstitute(const MatrixExpression<U>& u, const VectorExpression<W>& w, const MatrixExpression<V>& v, 
						  const VectorExpression<B>& b, VectorExpression<X>& x)
		{
			typedef typename CommonType<typename CommonType<typename CommonType<typename CommonType<typename U::ValueType, 
				typename W::ValueType>::Type, typename V::ValueType>::Type, typename B::ValueType>::Type, 
				typename X::ValueType>::Type ValueType;

			typedef typename CommonType<typename U::SizeType, typename W::SizeType>::Type SizeType;

			SizeType m = u().getSize1();
			SizeType n = u().getSize2();

		    CDPL_MATH_CHECK(w().getSize() == n && v().getSize1() == n && v().getSize2() == n &&
						   b().getSize() == m && x().getSize() == n,
						   "svSubstitute: Preconditions violated",  Base::SizeError); 
			
			Vector<ValueType> tmp(n);
			ValueType thresh = 0.5 * std::sqrt(m + n + 1.0) * w()(0) * std::numeric_limits<ValueType>::epsilon();

			for (SizeType i = 0; i < n; i++) {      // Calculate trans(U) * B
				ValueType s = ValueType(0);

				if (w()(i) > thresh)                // Nonzero result only if w(i) > threshold
					s = innerProd(column(u, i), b) / w()(i);

				tmp(i) = s;
			}

			x().assign(prod(v, tmp));
		}

		/**
		 * \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$
		 *        is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
		 *
		 * The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular
		 * value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the
		 * \f$ M \times N \f$-dimensional matrix \a u, \f$ W \f$ by the \f$ N \f$-dimensional
		 * vector \a w, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix \a v.
		 * The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by \a b,
		 * and \a x is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input 
		 * quantities are destroyed, so the routine may be called sequentially with different 
		 * arguments \a b. For implementation details see [\ref NRIC]. 
		 *
		 * \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
		 * \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular 
		 *          values of \f$ A \f$.
		 * \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
		 * \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$. 
		 * \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
		 * \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && 
		 *      v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> 
		 *      and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>.
		 * \throw Base::SizeError if preconditions are violated.
		 * \see svDecomposition()
		 */
		template <typename U, typename W, typename V, typename B, typename X>
		void svSubstitute(const MatrixExpression<U>& u, const VectorExpression<W>& w, const MatrixExpression<V>& v, 
						  const MatrixExpression<B>& b, MatrixExpression<X>& x)
		{

			typedef typename CommonType<typename CommonType<typename CommonType<typename CommonType<typename U::ValueType, 
				typename W::ValueType>::Type, typename V::ValueType>::Type, typename B::ValueType>::Type, 
				typename X::ValueType>::Type ValueType;

			typedef typename CommonType<typename CommonType<typename CommonType<typename U::SizeType, 
				typename W::SizeType>::Type, typename B::SizeType>::Type, typename X::SizeType>::Type SizeType;

			SizeType m = u().getSize1();
			SizeType n = u().getSize2();
			SizeType p = b().getSize2();

		    CDPL_MATH_CHECK(SizeType(w().getSize()) == n && SizeType(v().getSize1()) == n && SizeType(v().getSize2()) == n &&
							SizeType(b().getSize1()) == m && SizeType(x().getSize1()) == n && SizeType(x().getSize2()) == p,
							"svSubstitute: Preconditions violated",  Base::SizeError); 

			Vector<ValueType> tmp(n);
			ValueType thresh = 0.5 * std::sqrt(m + n + 1.0) * w()(0) * std::numeric_limits<ValueType>::epsilon();
			
			for (SizeType i = 0; i < p; i++) {          // For each column of B solve for the respective column of X
				MatrixColumn<const B> b_col(column(b, i));

				for (SizeType j = 0; j < n; j++) {      // Calculate trans(U) * B
					ValueType s = ValueType(0);

					if (w()(j) > thresh)                // Nonzero result only if w(j) > threshold
						s = innerProd(column(u, j), b_col) / w()(j);

					tmp(j) = s;
				}

				column(x, i).assign(prod(v, tmp));
			}
		}
	}
}

#endif // CDPL_MATH_SVDECOMPOSITION_HPP
