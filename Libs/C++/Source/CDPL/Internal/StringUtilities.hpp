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
#include <string_view>
#include <locale>
#include <cstddef>

#include <boost/functional/hash.hpp>


namespace CDPL
{

    namespace Internal
    {

        std::string& trimString(std::string& str, bool left = true, bool right = true);

        std::string trimStringCopy(const std::string& str, bool left = true, bool right = true);

        bool isEqualCI(const std::string_view& str1, const std::string_view& str2);

        bool startsWithCI(const std::string_view& str, const std::string_view& query);

        struct IsNonWhitespace
        {

            typedef bool result_type;

            bool operator()(char c) const
            {
                return !std::isspace(c, std::locale::classic());
            }
        };

        struct IsWhitespace
        {

            typedef bool result_type;

            bool operator()(char c) const
            {
                return std::isspace(c, std::locale::classic());
            }
        };

        struct StringPtrHashFunc
        {

            std::size_t operator()(const std::string* str_ptr) const
            {
                if (!str_ptr)
                    return 0;

                return std::hash<std::string>{}(*str_ptr);
            }
        };

        struct StringPtrCmpFunc
        {

            bool operator()(const std::string* str_ptr1, const std::string* str_ptr2) const
            {
                if (!str_ptr1)
                    return !str_ptr2;

                if (!str_ptr2)
                    return false;

                return (*str_ptr1 == *str_ptr2);
            }
        };
        
        struct CIStringPtrHashFunc
        {

            std::size_t operator()(const std::string* str_ptr) const
            {
                if (!str_ptr)
                    return 0;

                std::size_t h = 0;

                for (auto c : *str_ptr)
                    boost::hash_combine(h, std::tolower(c, std::locale::classic()));

                return h;
            }
        };

        struct CIStringPtrCmpFunc
        {

            bool operator()(const std::string* str_ptr1, const std::string* str_ptr2) const
            {
                if (!str_ptr1)
                    return !str_ptr2;

                if (!str_ptr2)
                    return false;

                return isEqualCI(*str_ptr1, *str_ptr2);
            }
        };

        struct CIStringHashFunc
        {

            std::size_t operator()(const std::string& str) const
            {
                std::size_t h = 0;

                for (auto c : str)
                    boost::hash_combine(h, std::tolower(c, std::locale::classic()));

                return h;
            }
        };

        struct CIStringCmpFunc
        {

            bool operator()(const std::string& str1, const std::string& str2) const
            {
                return isEqualCI(str1, str2);
            }
        };
    } // namespace Internal
} // namespace CDPL

#endif // CDPL_INTERNAL_STRINGUTILITIES_HPP
