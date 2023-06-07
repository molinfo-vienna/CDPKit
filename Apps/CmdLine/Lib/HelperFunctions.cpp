/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HelperFunctions.cpp
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


#include "HelperFunctions.hpp"


std::string CmdLineLib::formatTimeDuration(std::size_t secs)
{
    std::string time_str;
    std::size_t days = secs / (3600 * 24);
    std::size_t hours = (secs % (3600 * 24)) / 3600;
    std::size_t mins = (secs % 3600) / 60;
    
	secs = secs % 60;

	if (days > 0)
		time_str.append(std::to_string(days)).push_back('d');

    if (days > 0 || hours > 0)
		time_str.append(std::to_string(hours)).push_back('h');

    if (days > 0 || hours > 0 || mins > 0)
		time_str.append(std::to_string(mins)).push_back('m');

    time_str.append(std::to_string(secs)).push_back('s');

    return time_str;
}
