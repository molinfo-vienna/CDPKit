/* 
 * StringUtilities.hpp
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


#ifndef CDPL_INTERNAL_STRINGUTILITIES_HPP
#define CDPL_INTERNAL_STRINGUTILITIES_HPP

#include <string>
#include <cctype>


namespace CDPL
{

    namespace Internal
    {

        struct IsNonWhitespace
        {

            typedef bool result_type;

            bool operator()(unsigned char c) const
            {
                return !std::isspace(c);
            }
        };

        struct IsWhitespace
        {

            typedef bool result_type;

            bool operator()(unsigned char c) const
            {
                return std::isspace(c);
            }
        };

        std::string& trimString(std::string& str, bool left = true, bool right = true);

        std::string trimStringCopy(const std::string& str, bool left = true, bool right = true);

        bool isEqualCI(const std::string& str1, const std::string& str2);
        
    } // namespace Internal
} // namespace CDPL

#endif // CDPL_INTERNAL_STRINGUTILITIES_HPP
