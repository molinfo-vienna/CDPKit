/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataIOUtilities.cpp
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


#include "StaticInit.hpp"

#include <istream>

#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "DataIOUtilities.hpp"
#include "MMFF94DataFormat.hpp"


using namespace CDPL;


bool ForceField::readMMFF94DataLine(std::istream& is, std::string& line, const char* err_msg)
{
	while (!std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof())) {
		Internal::readLine(is, line, err_msg, true, false, 0, MMFF94DataFormat::END_OF_LINE);

		if (line.empty())
			continue;

		if (line[0] == MMFF94DataFormat::COMMENT_PREFIX)
			continue;

		if (line.size() == 1 && line[0] == MMFF94DataFormat::END_OF_FILE)
			return false;

		return true;
	}

	return false;
}
