/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringDataIOUtilities.hpp
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


#ifndef CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP
#define CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP

#include <istream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <cstddef>
#include <string>
#include <locale>
#include <limits>
#include <cstdlib>

#include <boost/lexical_cast.hpp>

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Internal
	{

		inline void checkStreamState(const std::istream& is, const char* err_msg)
		{
			if (!is.good())
				throw Base::IOError(std::string(err_msg) + ": unexpected end of data or unspecified read error");
		}

		void skipChars(std::istream& is, std::size_t count, const char* err_msg = "Error", char eol_char = '\n');
		
		void skipLines(std::istream& is, std::size_t count = 1, const char* err_msg = "Error", char eol_char = '\n');
			
		std::string& readLine(std::istream& is, std::string& line, const char* err_msg = "Error", bool trim = false, 
							  bool check_ll = false, std::size_t max_llen = 80, char eol_char = '\n');


		std::string& readString(std::istream& is, std::size_t field_size, std::string& str, bool clear = true,
								const char* err_msg = "Error", bool trim = true, char eol_char = '\n');
	
		bool skipToString(std::istream& is, const std::string& str, const char* err_msg = "Error", bool pos_after = false); 

		bool readToString(std::istream& is, const std::string& str, std::string& data, const char* err_msg = "Error", bool inc_str = false); 

		template <typename T>
		T parseNumber(const char* str_beg, const char* str_end, const char* err_msg = "Error", bool throw_ex = true, 
					 const T empty_def_val = T(0), const T err_def_val = T(0))
		{
			if (str_beg == str_end)
				return empty_def_val;
		
			T val;
			const char* old_loc = std::setlocale(LC_ALL, "C");
			char* parse_end;

			if (std::numeric_limits<T>::is_integer) {
				if (std::numeric_limits<T>::is_signed)
					val = T(std::strtol(str_beg, &parse_end, 10));
				else
					val = T(std::strtoul(str_beg, &parse_end, 10));

			} else 
				val = T(std::strtod(str_beg, &parse_end)); 

			std::setlocale(LC_ALL, old_loc);

			if (str_end != parse_end) {
				if (throw_ex)
					throw Base::IOError(std::string(err_msg) + ": '" + std::string(str_beg) + "' invalid number format");

				return err_def_val;
			}

			return val;
		}

		template <typename T>
		T parseNumber(const std::string& str, const char* err_msg = "Error", bool throw_ex = true, 
							 const T empty_def_val = T(0), const T err_def_val = T(0))
		{
			const char* c_str = str.c_str();

			return parseNumber<T>(c_str, c_str + str.size(), err_msg, throw_ex, empty_def_val, err_def_val);
		}

		template <typename T, std::size_t FieldSize>
		T readNumber(std::istream& is, const char* err_msg = "Error", bool throw_ex = true, 
					 const T empty_def_val = T(0), const T err_def_val = T(0), char eol_char = '\n')
		{
			char buf[FieldSize + 1];
			char *buf_end_ptr = buf;
			char c = 0;

			for (std::size_t i = 0; i < FieldSize && is.get(c) && c != eol_char; i++) {
				if (std::isspace(c, std::locale::classic()))
					continue;

				*buf_end_ptr++ = c;
			}

			checkStreamState(is, err_msg);

			if (c == eol_char)
				is.putback(eol_char);

			*buf_end_ptr = 0;

			return parseNumber<T>(buf, buf_end_ptr, err_msg, throw_ex, empty_def_val, err_def_val);
		}

		inline void writeWhitespace(std::ostream& os, std::size_t width)
		{
			os << std::setw(width) << "";
		}

		inline void writeEOL(std::ostream& os, char eol_char = '\n')
		{
			os << eol_char;
		}

		void writeLine(std::ostream& os, const std::string& line, const char* err_msg, 
					   bool check_llen, bool trim, bool trunc, std::size_t max_llen = 80, char eol_char = '\n');
	
		void writeString(std::ostream& os, std::size_t field_size, const std::string& str, 
						 const char* err_msg = "Error", bool trim = false, bool trunc = false, bool align_right = false);

		void writeSubstring(std::ostream& os, const std::string& str, std::size_t start, std::size_t end);

		template <typename T>
		void writeIntegerNumber(std::ostream& os, std::size_t field_size, const T value, const char* err_msg = "Error", 
								bool align_left = false)
		{
			std::ostringstream oss;

			oss.imbue(std::locale::classic());

			oss << std::setw(field_size);
	
			if (align_left)
				oss << std::left;
			else
				oss << std::right;

			oss << value;

			if (!oss.good())
				throw Base::IOError(std::string(err_msg) + ": conversion of numeric value to string failed");

			std::string val_str = oss.str();

			if (val_str.size() > field_size)
				throw Base::IOError(std::string(err_msg )+ ": number exceeds limit of " 
									+ boost::lexical_cast<std::string>(field_size) + " allowed digits"); 

			os << val_str; 
		}

		template <typename T>
		void writeFloatNumber(std::ostream& os, std::size_t field_size, std::size_t prec, 
							  const T value, const char* err_msg = "Error")
		{
			std::ostringstream oss;

			oss.imbue(std::locale::classic());

			oss << std::fixed << std::setw(field_size) << std::showpoint << std::setprecision(prec) << std::right << value;

			if (!oss.good())
				throw Base::IOError(std::string(err_msg) + ": conversion of numeric value to string failed");

			std::string val_str = oss.str();

			if (val_str.size() > field_size)
				throw Base::IOError(std::string(err_msg) + ": number exceeds limit of " 
									+ boost::lexical_cast<std::string>(field_size) + " allowed characters"); 
			os << val_str; 
		}
	}
}

#endif // CDPL_INTERNAL_STRINGDATAIOUTILITIES_HPP
