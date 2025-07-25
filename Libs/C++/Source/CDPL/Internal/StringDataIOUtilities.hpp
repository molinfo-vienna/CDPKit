/* 
 * StringDataIOUtilities.hpp
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


#ifndef CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP
#define CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP

#include <istream>
#include <ostream>
#include <cstddef>
#include <string>


namespace CDPL
{

    namespace Internal
    {

        
        inline 
        void checkStreamState(const std::istream& is, const char* err_msg);

        inline 
        void skipChars(std::istream& is, std::size_t count, const char* err_msg = "Error", char eol_char = '\n');

        inline 
        void skipLines(std::istream& is, std::size_t count = 1, const char* err_msg = "Error", char eol_char = '\n');

        inline 
        std::string& readLine(std::istream& is, std::string& line, const char* err_msg = "Error", bool trim = false,
                              bool check_ll = false, std::size_t max_llen = 80, char eol_char = '\n');

        inline 
        std::string& readString(std::istream& is, std::size_t field_size, std::string& str, bool clear = true,
                                const char* err_msg = "Error", bool trim = true, char eol_char = '\n');

        inline 
        bool skipToString(std::istream& is, const std::string& str, const char* err_msg = "Error", bool pos_after = false);

        inline 
        bool readToString(std::istream& is, const std::string& str, std::string& data, const char* err_msg = "Error", bool inc_str = false);

        template <typename T>
        T parseNumber(const char* str_beg, const char* str_end, const char* err_msg = "Error", bool throw_ex = true,
                      const T empty_def_val = T(0), const T err_def_val = T(0));

        template <typename T>
        T parseNumber(const std::string& str, const char* err_msg = "Error", bool throw_ex = true,
                      const T empty_def_val = T(0), const T err_def_val = T(0));

        template <typename T, std::size_t FieldSize>
        T readNumber(std::istream& is, const char* err_msg = "Error", bool throw_ex = true,
                     const T empty_def_val = T(0), const T err_def_val = T(0), char eol_char = '\n');

        inline
        void writeWhitespace(std::ostream& os, std::size_t width);

        inline
        void writeEOL(std::ostream& os, char eol_char = '\n');

        inline 
        void writeLine(std::ostream& os, const std::string& line, const char* err_msg,
                       bool check_llen, bool trim, bool trunc, std::size_t max_llen = 80, char eol_char = '\n');

        inline 
        void writeString(std::ostream& os, std::size_t field_size, const std::string& str,
                         const char* err_msg = "Error", bool trim = false, bool trunc = false, bool align_right = false);

        inline 
        void writeSubstring(std::ostream& os, const std::string& str, std::size_t start, std::size_t end);

        template <typename T>
        void writeIntegerNumber(std::ostream& os, std::size_t field_size, const T value, const char* err_msg = "Error",
                                bool align_left = false, char fill = ' ');
  
        template <typename T>
        void writeFloatNumber(std::ostream& os, std::size_t field_size, std::size_t prec,
                              const T value, const char* err_msg = "Error");
      
        inline
        void beginXMLStartTag(std::ostream& os, const std::string& tag, std::size_t indent = 0, const std::string& ns = std::string());

        inline
        void endXMLStartTag(std::ostream& os, bool empty = false, bool write_nl = true);
        
        inline
        void writeXMLEndTag(std::ostream& os, const std::string& tag, std::size_t indent = 0, const std::string& ns = std::string());

        template <typename T>
        void writeXMLAttribute(std::ostream& os, const std::string& name, const T& value);

        inline
        const std::string& escapeXMLData(const std::string& data, std::string& esc_data, bool attr_val, char keep_char = 0);

        struct XMLTagInfo
        {

            enum Type
            {
                UNDEF,
                START,
                END,
                EMPTY
            };

            std::string            name;
            std::string            ns;
            Type                   type;
            std::istream::pos_type streamPos;
        };

        inline bool getNextXMLTag(std::istream& is, XMLTagInfo& tag_info, const char* err_msg = "Error", std::string* read_data = nullptr);
        
    } // namespace Internal
} // namespace CDPL

#include "StringDataIOUtilitiesImpl.hpp"

#endif // CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP
