/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpecialFunctions.hpp 
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
 * \brief Provides miscellaneous special mathematical functions.
 */

#ifndef CDPL_MATH_SPECIALFUNCTIONS_HPP
#define CDPL_MATH_SPECIALFUNCTIONS_HPP

#include <cstddef>
#include <cmath>
#include <limits>

#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

	namespace Math
	{	

		/**
		 * \brief Computes the factorial \f$ n! \f$ of the non-negative integer \a n.
		 * \param n The non-negative integer for which to compute the factorial.
		 * \return The computed factorial of \a n.
		 */
		template <typename T>
		T factorial(unsigned int n);

		/**
		 * \brief Computes \f$ \sqrt{a^2 + b^2} \f$ without destructive underflow or overflow.
		 * \param a The variable \a a.
		 * \param b The variable \a b.
		 * \return The result of computing \f$ \sqrt{a^2 + b^2} \f$.
		 */
		template <typename T>
		T pythag(const T& a, const T& b);

		/**
		 * \brief Returns the magnitude of parameter \a a times the sign of parameter \a b.
		 * \param a The parameter \a a.
		 * \param b The parameter \a b.
		 * \return \a a times the sign of parameter \a b.
		 */
		template <typename T1, typename T2>
		T1 sign(const T1& a, const T2& b);

		/**
		 * \brief Computes \f$ \ln[\Gamma(z)] \f$ for \f$ z > 0 \f$.
		 * \param z The argument to the gamma function.
		 * \return The computed logarithm of the gamma function value for \a z.
		 */
		template <typename T>
		T lnGamma(const T& z);

		/**
		 * \brief Computes the incomplete gamma function \f$ Q(a, x) = 1 - P(a, x) \f$ (see [\ref NRIC] for details).
		 * \param a The function argument \a a.
		 * \param x The function argument \a x.
		 * \return The computed value of the incomplete gamma function. 
		 */
		template <typename T>
		T gammaQ(const T& a, const T& x);
	
		/**
		 * \brief Computes the generalized bell function \f$ Bell(x) = \frac{1}{1 + |\frac{x-c}{a}|^{2b}} \f$ at \a x.
		 * \param x The generalized bell function argument
		 * \param a Controls the width of the curve at \f$f(x) = 0.5 \f$.
		 * \param b Controls the slope of the curve at \f$ x = c - a \f$ and \f$ x = c + a \f$.
		 * \param c Locates the center of the curve.
		 * \return The generalized bell function value at \a x.
		 */
		template <typename T>
		T generalizedBell(const T& x, const T& a, const T& b, const T& c);
	}
}


// Implementation 
// \cond UNHIDE_DETAILS

namespace CDPL
{

	namespace Math
	{

		namespace Detail
		{

			// Computes the incomplete gamma function P(a, x) evaluated by its series representation.
			template <typename T>
			T gammaPSer(const T& a, const T& x)
			{
				using namespace CDPL;
				using namespace Math;

				if (x <= 0) {
					if (x < 0)
						return std::numeric_limits<T>::quiet_NaN();

					return 0;
				}

				T ap = a;
				T del = 1 / a;
				T sum = del;

				for (unsigned int i = 0; i < 100; i++) {
					++ap;

					del *= x / ap;
					sum += del;

					if (TypeTraits<T>::abs(del) < TypeTraits<T>::abs(sum) * std::numeric_limits<T>::epsilon())
						return (sum * std::exp(-x + a * log(x) - CDPL::Math::lnGamma(a)));
				}

				return std::numeric_limits<T>::quiet_NaN();
			}

			// Computes the incomplete gamma function Q(a, x) evaluated by its continued fraction representation.
			template <typename T>
			T gammaQContFrac(const T& a, const T& x)
			{
				using namespace CDPL;
				using namespace Math;

				static const T EPS = std::numeric_limits<T>::epsilon();
				static const T FP_MIN = std::numeric_limits<T>::min() / EPS;

				T b = x + 1 - a;
				T c = 1 / FP_MIN;
				T d = 1 / b;
				T h = d;

				for (unsigned int i = 0; i < 100; i++) {
					T an = -i * (i - a);
					b += 2;
					d = an * d + b;

					if (TypeTraits<T>::abs(d) < FP_MIN)
						d = FP_MIN;
		
					c = b + an / c;

					if (TypeTraits<T>::abs(c) < FP_MIN)
						c = FP_MIN;
		
					d = 1 / d;
					T del = d * c;
					h *= del;

					if (TypeTraits<T>::abs(del - 1) <= EPS)
						return (std::exp(-x + a * log(x) - CDPL::Math::lnGamma(a)) * h);
				}

				return std::numeric_limits<T>::quiet_NaN();
			}
		}
	}
}


template <typename T>
T CDPL::Math::factorial(unsigned int n) 
{
	T f(1);

	if (n == 0)
		return f;

	for (unsigned int i = 2; i <= n; i++)
		f *= T(i);

	return f;
}

template <typename T>
T CDPL::Math::pythag(const T& a, const T& b) 
{
	T abs_a = TypeTraits<T>::abs(a);
	T abs_b = TypeTraits<T>::abs(b);

	if (abs_a > abs_b) {
		T tmp = abs_b / abs_a;

		return (abs_a * TypeTraits<T>::sqrt(T(1) + tmp * tmp));
	}

	if (abs_b == 0)
		return 0;

	T tmp = abs_a / abs_b;

	return (abs_b * TypeTraits<T>::sqrt(T(1) + tmp * tmp)); 
}

template <typename T1, typename T2>
T1 CDPL::Math::sign(const T1& a, const T2& b)
{
	return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a)); 
}

template <typename T>
T CDPL::Math::lnGamma(const T& xx)
{
	static const long double cof[6] = {
	    76.18009172947146,
		-86.50532032941677,
		24.01409824083091,
		-1.231739572450155,
		0.1208650973866179e-2,
		-0.5395239384953e-5
	};

	long double ser = 1.000000000190015;
	long double x = xx;
	long double y = xx;
	long double tmp = x + 5.5;
	
	tmp -= (x + 0.5) * std::log(tmp);
	
	for (unsigned int i = 0; i < 6; i++)
		ser += cof[i] / ++y;

	return T(-tmp + std::log(2.5066282746310005 * ser / x));
}

template <typename T>
T CDPL::Math::gammaQ(const T& a, const T& x)
{
	if (x < T(0) || a <= T(0))
		return std::numeric_limits<T>::quiet_NaN();

	if (x < (a + T(1))) 
		return (T(1) - Detail::gammaPSer(a, x));
	
	return Detail::gammaQContFrac(a, x);
}

template <typename T>
T CDPL::Math::generalizedBell(const T& x, const T& a, const T& b, const T& c)
{
	return (T(1) / (T(1) + std::pow(std::abs((x - c) / a), T(2) * b)));
}

// \endcond

#endif // CDPL_MATH_SPECIALFUNCTIONS_HPP

