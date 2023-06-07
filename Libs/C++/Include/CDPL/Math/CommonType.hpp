/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CommonType.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Common type deduction.
 */

#ifndef CDPL_MATH_COMMONTYPE_HPP
#define CDPL_MATH_COMMONTYPE_HPP

#include <type_traits>


namespace CDPL
{

	namespace Math
	{

		template <typename T1, typename T2>
		struct CommonType
		{

			typedef typename std::common_type<T1, T2>::type Type;
		};
	}
}

#endif // CDPL_MATH_COMMONTYPE_HPP
