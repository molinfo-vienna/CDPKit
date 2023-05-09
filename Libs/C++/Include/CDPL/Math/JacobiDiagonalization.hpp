/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * JacobiDiagonalization.hpp 
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

/**
 * \file
 * \brief Implementation of the Jacobi method for the calculation of eigenvalues and
 *        eigenvectors.
 */

#ifndef CDPL_MATH_JACOBIDIAGONALIZATION_HPP
#define CDPL_MATH_JACOBIDIAGONALIZATION_HPP

#include <cstddef>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{	

		/**
		 * \brief Computes all eigenvalues and eigenvectors of a real symmetric matrix \a an using Jacobi's
		 *        algorithm [\ref WJACO ].
		 *
		 * On output, elements of \a a above the diagonal are destroyed. The vector \a d returns
		 * the eigenvalues of \a a. The columns of matrix \a v contain, on output, the normalized
		 * eigenvectors of \a a. For implementation details see [\ref NRIC].
		 * 
		 * \param a The real symmetric matrix for which to compute eigenvalues and eigenvectors.
		 * \param d The output vector which will contain the eigenvalues of \a a.
		 * \param v The matrix whose columns will contain the normalized eigenvectors of \a a.
		 * \param max_iter The maximum number of iterations to perform.
		 * \return \c true if \a a is a non-empty symmetric matrix and convergence has been reached in
		 *         \a max_iter iterations, and \c false otherwise.
		 * \pre \a a is symmetric and non-empty, i.e. <tt>a().getSize1() == a().getSize2() && a().getSize1() != 0</tt>,
		 *      and furthermore <tt>d().getSize() >= a().getSize1()</tt>. 
		 * \throw Base::SizeError if preconditions are violated.
		 */
		template <typename M1, typename V, typename M2>
		bool jacobiDiagonalize(MatrixExpression<M1>& a, VectorExpression<V>& d, MatrixExpression<M2>& v, std::size_t max_iter = 50);
	}
}


// Implementation 

namespace
{

	template <typename M>
	void jacobiRotate(M& a, typename M::SizeType i, typename M::SizeType j, 
					  typename M::SizeType k, typename M::SizeType l, 
					  typename M::ValueType tau, typename M::ValueType s)
	{
		typedef typename M::ValueType ValueType;

		ValueType g = a(i, j);
		ValueType h = a(k, l);

		a(i, j) = g - s * (h + g * tau);
		a(k, l) = h + s * (g - h * tau);
	}
}


template <typename M1, typename V, typename M2>
bool CDPL::Math::jacobiDiagonalize(MatrixExpression<M1>& a, VectorExpression<V>& d, MatrixExpression<M2>& v, std::size_t max_iter)
{
	typedef typename CommonType<typename CommonType<typename M1::ValueType, typename V::ValueType>::Type, 
		typename M2::ValueType>::Type ValueType;
			
	typedef typename CommonType<typename CommonType<typename M1::SizeType, typename V::SizeType>::Type,
		typename M2::SizeType>::Type SizeType;

	SizeType n = a().getSize1();

	CDPL_MATH_CHECK(n == a().getSize2() && n > 0 && SizeType(d().getSize()) >= n, "Preconditions violated",  Base::SizeError);

	typename VectorTemporaryTraits<V>::Type b(n);
	typename VectorTemporaryTraits<V>::Type z(n);

	v().assign(IdentityMatrix<ValueType>(n, n));

	for (SizeType ip = 0; ip < n; ip++) {     
		b(ip) = d()(ip) = a()(ip, ip);  // Initialize b and d to the diagonal of a
		z(ip) = ValueType();                  // This vector will accumulate terms of the form tapq as in equation (11.1.14).
	}

	for (std::size_t i = 0; i < max_iter; i++) {
		ValueType sm = ValueType(); 

		for (SizeType ip = 0; ip < n - 1; ip++)  // Sum off-diagonal elements.
			for (SizeType iq = ip + 1; iq < n; iq++)
				sm += TypeTraits<ValueType>::abs(a()(ip, iq));

		if (sm == ValueType())            // The normal return, which relies on quadratic convergence to machine underflow.
			return true;

		ValueType tresh;

		if (i < 3)
			tresh = ValueType(0.2) * sm / (n * n); // ...on the first three sweeps.
		else
			tresh = ValueType();                  // ...thereafter.

		for (SizeType ip = 0; ip < n - 1; ip++) {
			for (SizeType iq = ip + 1; iq < n; iq++) {
				ValueType g = 100 * TypeTraits<ValueType>::abs(a()(ip, iq));

				if (i > 3 && (TypeTraits<ValueType>::abs(d()(ip)) + g) == TypeTraits<ValueType>::abs(d()(ip)) // After four sweeps, skip the rotation if the off-diagonal element is small.
					&& (TypeTraits<ValueType>::abs(d()(iq)) + g) == TypeTraits<ValueType>::abs(d()(iq)))
					a()(ip, iq) = ValueType();

				else if (TypeTraits<ValueType>::abs(a()(ip, iq)) > tresh) {
					ValueType h = d()(iq) - d()(ip);
					ValueType t;

					if (TypeTraits<ValueType>::abs(h) + g == TypeTraits<ValueType>::abs(h))
						t = (a()(ip, iq)) / h;

					else {
						ValueType theta = 0.5 * h / a()(ip, iq);
						t = 1 / (TypeTraits<ValueType>::abs(theta) + TypeTraits<ValueType>::sqrt(1 + theta * theta));

						if (theta < ValueType()) 
							t = -t;
					}
					
					ValueType c = 1 / TypeTraits<ValueType>::sqrt(1 + t * t);
					ValueType s = t * c;
					ValueType tau = s / (1 + c);
					h = t * a()(ip, iq);
					z(ip) -= h;
					z(iq) += h;
					d()(ip) -= h;
					d()(iq) += h;
					a()(ip, iq) = ValueType();

					for (SizeType j = 0; j < ip; j++)        // Case of rotations 1 < j < p.
						jacobiRotate(a(), j, ip, j, iq, tau, s);

					for (SizeType j = ip + 1; j < iq; j++)   // Case of rotations p < j < q.
						jacobiRotate(a(), ip, j, j, iq, tau, s);

					for (SizeType j = iq + 1; j < n; j++)    // Case of rotations q < j < n.
						jacobiRotate(a(), ip, j, iq, j, tau, s);
					
					for (SizeType j = 0; j < n; j++) 
						jacobiRotate(v(), j, ip, j, iq, tau, s);
				}
			}
		}

		for (SizeType ip = 0; ip < n; ip++) {
			b(ip) += z(ip);
			d()(ip) = b(ip);         // Update d with the sum of tapq,
			z(ip) = ValueType();     // and reinitialize z.
		}
	}

	return false;
}

#endif // CDPL_MATH_JACOBIDIAGONALIZATION_HPP

