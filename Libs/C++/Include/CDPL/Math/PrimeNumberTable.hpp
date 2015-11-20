/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrimeNumberTable.hpp 
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
 * \brief Definition of the class CDPL::Math::PrimeNumberTable.
 */

#ifndef CDPL_MATH_PRIMENUMBERTABLE_HPP
#define CDPL_MATH_PRIMENUMBERTABLE_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Math/APIPrefix.hpp"


namespace CDPL
{

	namespace Math
	{	

		/**
		 * \addtogroup CDPL_MATH_MISCELLANEOUS
		 * @{
		 */

		/**
		 * \brief A singleton class for the generation and lookup of prime numbers.
		 */
		class CDPL_MATH_API PrimeNumberTable
		{

		public:
			/**
			 * \brief Returns the \a i-th element in the sequence of primes starting with \e 2.
			 * \param i The zero-based index of the requested prime number.
			 * \return The requested prime number.
			 */
			static std::size_t getPrimeNumber(std::size_t i);

		private:
			PrimeNumberTable();

			static PrimeNumberTable& getInstance();

			std::vector<std::size_t> primeNumbers;
		};

		/**
		 * @}
		 */
	}
}


#endif // CDPL_MATH_PRIMENUMBERTABLE_HPP

