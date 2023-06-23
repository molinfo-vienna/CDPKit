/* 
 * RangeGenerator.hpp 
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
 * \brief Definition of the class CDPL::Internal::RangeGenerator.
 */

#ifndef CDPL_INTERNAL_RANGEGENERATOR_HPP
#define CDPL_INTERNAL_RANGEGENERATOR_HPP


namespace CDPL
{

	namespace Internal
	{

		/**
		 * \brief A function object for the generation of arithmetic progressions.
		 * 
		 * The generator object is initialized with the desired start value and value
		 * difference of successive sequence members. To generate the actual sequence,
		 * the function call operator has to be invoked repeatedly.
		 *
		 * Example:
		 * \code
		 *
		 * std::vector<int> values; // storage for the generated sequence
		 *
		 * // generates the sequence 2, 5, 8, 11, 14, 17, 20, 23, 26, 29 and stores it in 'values'
		 * std::generate_n(std::back_inserter(values), 10, RangeGenerator<int>(2, 3));
		 * \endcode
		 * \tparam T The type of the generated range values.
		 */
		template <typename T>
		class RangeGenerator
		{

		public:
		   /**
			* \brief Constructor initializing the generator object.
			* \param start The start value of the sequence.
			* \param inc The arithmetic difference of successive values.
			*/
			RangeGenerator(T start = T(), T inc = T(1)): 
				startValue(start), increment(inc), currentValue(start) {}

		   /**
			* \brief Returns the next value in the sequence.
			* 
			* The returned value is either the start value (on the first call) or the
			* previously returned value incremented by the specified step-size.
			*
			* \return The next value in the sequence.
			*/
			T operator()();

		private:
			T startValue;
			T increment;
			T currentValue;
		};
	}
}


// Implementation

template <typename T>
T CDPL::Internal::RangeGenerator<T>::operator()()
{
	T tmp = currentValue;
	currentValue += increment;

	return tmp;
}

#endif // CDPL_INTERNAL_RANGEGENERATOR_HPP
