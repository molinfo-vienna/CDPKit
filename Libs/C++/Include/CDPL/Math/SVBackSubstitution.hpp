/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVBackSubstitution.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of singular value backsubstitution.
 */

#ifndef CDPL_MATH_SVBACKSUBSTITUTION_HPP
#define CDPL_MATH_SVBACKSUBSTITUTION_HPP

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

	namespace Math
	{	

		/**
		 * \addtogroup CDPL_MATH_SV_DECOMPOSITION
		 * @{
		 */

		/**
		 * \brief Solves \f$ A \cdot X = B \f$ for a vector \f$ X \f$ where \f$ A \f$
		 *        is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
		 *
		 * The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular
		 * value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the
		 * \f$ M \times N \f$-dimensional matrix \a u, \f$ W \f$ by the \f$ N \f$-dimensional
		 * vector \a w, and \f$ V \f$ is given by the \f$ N \times N \f$-dimensional matrix \a v.
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
		 * \pre <tt>w.size() == u.size2()</tt>, <tt>v.size1() == u.size2() && 
		 *      v.size2() == c.size2()</tt>, and <tt>b.size() == u.size1()</tt>.
		 * \see svDecomposition()
		 */
		template <typename M1, typename V1, typename M2, typename V2, typename V3>
		void svBackSubstitution(const M1& u, const V1& w, const M2& v, const V2& b, V3& x);

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename M1, typename V1, typename M2, typename V2, typename V3>
void CDPL::Math::svBackSubstitution(const M1& u, const V1& w, const M2& v, const V2& b, V3& x)
{
	typedef typename V3::value_type T;

	typename M1::size_type n = u.size2();

	Vector<T> tmp(n);

	for (typename M1::size_type j = 0; j < n; j++) {      // Calculate trans(U) * B
		T s = 0;

		if (w(j) != 0)                                    // Nonzero result only if w(j) is nonzero
			s = inner_prod(column(u, j), b) / w(j);

		tmp(j) = s;
	}

	x = prod(v, tmp);
}

#endif // CDPL_MATH_SVBACKSUBSTITUTION_HPP


