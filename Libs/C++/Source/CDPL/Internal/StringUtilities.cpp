/* 
 * StringUtilities.cpp
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


#include <algorithm>
#include <locale>

#include <boost/algorithm/string.hpp>

#include "StringUtilities.hpp"


using namespace CDPL;


std::string& Internal::trimString(std::string& str, bool left, bool right)
{
    if (str.empty())
        return str;
        
    if (left && right) {
        boost::trim_if(str, IsWhitespace());
        return str;
    }

    if (right)  {
        boost::trim_right_if(str, IsWhitespace());
        return str;
    }

    if (left)
        boost::trim_left_if(str, IsWhitespace());
    
    return str;
}

std::string Internal::trimStringCopy(const std::string& str, bool left, bool right)
{
    if (str.empty())
        return str;

    if (left && right)
        return boost::trim_copy_if(str, IsWhitespace());

    if (right)
        return boost::trim_right_copy_if(str, IsWhitespace());

    if (left)
        return boost::trim_left_copy_if(str, IsWhitespace());

    return str;
}

bool Internal::isEqualCI(const std::string& str1, const std::string& str2)
{
    if (str1.length() != str2.length())
        return false;

    return std::equal(str1.begin(), str1.end(), str2.begin(),
                      [](unsigned char c1, unsigned char c2) { return (std::tolower(c1, std::locale::classic()) == std::tolower(c2, std::locale::classic())); });
}
