/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrimeNumberTable.cpp 
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


#include <cmath>

#include "CDPL/Math/PrimeNumberTable.hpp"


using namespace CDPL;


Math::PrimeNumberTable::PrimeNumberTable()
{
	primeNumbers.reserve(256);
	primeNumbers.push_back(2);
}

Math::PrimeNumberTable& Math::PrimeNumberTable::getInstance()
{
	static PrimeNumberTable instance;

	return instance;
}

std::size_t Math::PrimeNumberTable::getPrimeNumber(std::size_t i)
{
	std::vector<std::size_t>& prime_numbers = getInstance().primeNumbers;

	if (i >= prime_numbers.size()) {
		std::size_t curr_size = prime_numbers.size();
		std::size_t next_test_val = prime_numbers.back() + 1;

		while (i >= curr_size) {
			std::size_t limit = std::size_t(std::floor(std::sqrt(double(next_test_val))));
			std::size_t j = 0;

			for ( ; prime_numbers[j] <= limit; j++) 
				if ((next_test_val % prime_numbers[j]) == 0)
					break;
			
			if (prime_numbers[j] > limit) {
				prime_numbers.push_back(next_test_val);
				curr_size++;
			}

			next_test_val++;
		}		
	}

	return prime_numbers[i];
}
