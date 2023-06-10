/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Timer.hpp 
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

#ifndef CDPL_INTERNAL_TIMER_HPP
#define CDPL_INTERNAL_TIMER_HPP

#include <chrono>
#include <ratio>
#include <sstream>
#include <iomanip>
#include <cstdint>


namespace CDPL
{

    namespace Internal
    {

		class Timer
		{

		 public:
			typedef std::chrono::high_resolution_clock::duration Duration;
	    
			Timer(): start(std::chrono::high_resolution_clock::now()) {}

			void reset() {
				start = std::chrono::high_resolution_clock::now();
			}

			Duration elapsed() const {
				return (std::chrono::high_resolution_clock::now() - start);
			}

			template <int PREC = 0, typename PERIOD = std::ratio<1> >
			std::string format() {
				std::ostringstream oss;

				if (PREC > 0) {
					oss << std::fixed << std::setprecision(PREC);
					oss << std::chrono::duration_cast<std::chrono::duration<double, PERIOD> >(elapsed()).count();

				} else 
					oss << std::chrono::duration_cast<std::chrono::duration<std::uintmax_t, PERIOD> >(elapsed()).count();
				
				return oss.str();
			}
	    
		 private:
			typedef std::chrono::high_resolution_clock::time_point TimePoint;

			TimePoint start;
		};
    }
}

#endif // CDPL_INTERNAL_TIMER_HPP
