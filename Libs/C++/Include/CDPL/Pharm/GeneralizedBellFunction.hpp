/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeneralizedBellFunction.hpp 
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
 * \brief Definition of the class CDPL::Pharm::GeneralizedBellFunction.
 */

#ifndef CDPL_PHARM_GENERALIZEDBELLFUNCTION_HPP
#define CDPL_PHARM_GENERALIZEDBELLFUNCTION_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief GeneralizedBellFunction.
		 * \f$ Bell(x) = \frac{1}{1 + |\frac{x-c}{a}|^{2b}} \f$ 
		 */
		class CDPL_PHARM_API GeneralizedBellFunction : public std::unary_function<double, double>
		{

		  public:
			/**
			 * \brief Constructs a \c %GeneralizedBellFunction functor with the specified parameters.
			 * \param a Controls the width of the curve at \f$f(x) = 0.5 \f$.
			 * \param b Controls the slope of the curve at \f$ x = c-a \f$ and \f$ x = c+a \f$.
			 * \param c Locates the center of the curve.
			 */
			GeneralizedBellFunction(double a, double b, double c): a(a), b(b), c(c) {}

			/**
			 * \brief Calculates the generalized bell function value at \a x.
			 * \param x The generalized bell function argument
			 * \return The generalized bell function value at \a x
			 */
			double operator()(double x) const;

		  private:
			double  a;
			double  b;
			double  c;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_GENERALIZEDBELLFUNCTION_HPP
