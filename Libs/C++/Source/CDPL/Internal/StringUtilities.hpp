/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringUtilities.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_INTERNAL_STRINGUTILITIES_HPP
#define CDPL_INTERNAL_STRINGUTILITIES_HPP

#include <functional>
#include <string>
#include <locale>


namespace CDPL
{

	namespace Internal
	{

		struct IsNonWhitespace : public std::unary_function<char, bool>
		{

			bool operator()(char c) const {
				return !std::isspace(c, std::locale::classic());
			}
		};

		struct IsWhitespace : public std::unary_function<char, bool>
		{

			bool operator()(char c) const {
				return std::isspace(c, std::locale::classic());
			}
		};

		std::string& trimString(std::string& str, bool left = true, bool right = true);

		std::string trimStringCopy(const std::string& str, bool left = true, bool right = true);
	}
}

#endif // CDPL_INTERNAL_STRINGUTILITIES_HPP
