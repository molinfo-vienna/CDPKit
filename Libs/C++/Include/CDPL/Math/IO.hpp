/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IO.hpp 
 *
 * Copyright (C) 2010-2011 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Stream output operators.
 */

#ifndef CDPL_MATH_IO_HPP
#define CDPL_MATH_IO_HPP

#include <ostream>
#include <sstream>


namespace CDPL
{

	namespace Math
	{

		template <typename E> class VectorExpression;
		template <typename E> class MatrixExpression;
		template <typename E> class QuaternionExpression;

		template <typename C, typename T, typename E>
		std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, const VectorExpression<E>& e)
		{
			typename std::basic_ostream<C, T>::sentry se(os);
			std::ios_base::iostate state(std::ios_base::goodbit);

			if (se) {
				try {
					std::basic_ostringstream<C, T, std::allocator<C> > oss;

					oss.flags(os.flags());
					oss.imbue(os.getloc());
					oss.precision(os.precision());
			
					typedef typename E::SizeType SizeType;

					SizeType size = e().getSize();

					oss << '[' << size << "](";

					if (size > 0)
						oss << e()(0);

					for (SizeType i = 1; i < size; i++)
						oss << ',' << e()(i);

					oss << ')';
				
					if (!oss.good())
						state |= std::ios_base::failbit;
					else 
						os << oss.str().c_str();
				
				} catch (...) {
					os.setstate(std::ios_base::failbit); 
					throw;
				}
			}

			if (state != std::ios_base::goodbit)
				os.setstate(state);

			return os;
		}

		template <typename C, typename T, typename E>
		std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, const MatrixExpression<E>& e)
		{
			typename std::basic_ostream<C, T>::sentry se(os);
			std::ios_base::iostate state(std::ios_base::goodbit);

			if (se) {
				try {
					std::basic_ostringstream<C, T, std::allocator<C> > oss;

					oss.flags(os.flags());
					oss.imbue(os.getloc());
					oss.precision(os.precision());
			
					typedef typename E::SizeType SizeType;

					SizeType size1 = e().getSize1();
					SizeType size2 = e().getSize2();

					oss << '[' << size1 << ',' << size2 << "](";

					if (size1 > 0 && size2 > 0) {
						for (SizeType i = 0; i < size1; i++) {
							if (i > 0)
								oss << ',';

							oss << '(';

							for (SizeType j = 0; j < size2; j++) {
								if (j > 0)
									oss << ',';

								oss << e()(i, j);
							}

							oss << ')';
						}
					}

					oss << ')';

					if (!oss.good())
						state |= std::ios_base::failbit;
					else 
						os << oss.str().c_str();
				
				} catch (...) {
					os.setstate(std::ios_base::failbit); 
					throw;
				}
			}

			if (state != std::ios_base::goodbit)
				os.setstate(state);

			return os;
		}

		template <typename C, typename T, typename E>
		std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, const QuaternionExpression<E>& e)
		{
			typename std::basic_ostream<C, T>::sentry se(os);
			std::ios_base::iostate state(std::ios_base::goodbit);

			if (se) {
				try {
					std::basic_ostringstream<C, T, std::allocator<C> > oss;

					oss.flags(os.flags());
					oss.imbue(os.getloc());
					oss.precision(os.precision());
			
					oss << '(' << e().getC1() << ',' << e().getC2() << ',' << e().getC3() << ',' << e().getC4() << ')';
				
					if (!oss.good())
						state |= std::ios_base::failbit;
					else 
						os << oss.str().c_str();
				
				} catch (...) {
					os.setstate(std::ios_base::failbit); 
					throw;
				}
			}

			if (state != std::ios_base::goodbit)
				os.setstate(state);

			return os;
		}
	}
}

#endif // CDPL_MATH_IO_HPP
