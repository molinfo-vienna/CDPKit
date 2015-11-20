/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StringDataIOUtilities.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "StringDataIOUtilities.hpp"
#include "StringUtilities.hpp"


using namespace CDPL;


void Chem::skipChars(std::istream& is, std::size_t count, const std::string& err_msg, char eol_char)
{
	char c = 0;
	
	for (std::size_t i = 0; i < count && is.get(c) && c != eol_char; i++);

	checkStreamState(is, err_msg);

	if (c == eol_char)
		is.putback(eol_char);
}

void Chem::skipLines(std::istream& is, std::size_t count, const std::string& err_msg, char eol_char)
{
	for (std::size_t i = 0; i < count && is.good(); i++)
		is.ignore(std::numeric_limits<std::streamsize>::max(), std::istream::traits_type::to_int_type(eol_char));

	checkStreamState(is, err_msg);
}
		
std::string& Chem::readLine(std::istream& is, std::string& line, const std::string& err_msg, bool trim, 
							bool check_ll, std::size_t max_llen, char eol_char)
{
	std::getline(is, line, eol_char);

	checkStreamState(is, err_msg);

	if (!line.empty() && *line.rbegin() == '\r') 
		line.erase(--line.end());

	if (check_ll && line.size() > max_llen)
		throw Base::IOError(err_msg + ": max. line length exceeded");

	if (trim)
		trimString(line);

	return line;
}

std::string& Chem::readString(std::istream& is, std::size_t field_size, std::string& str, bool clear,
							  const std::string& err_msg, bool trim, char eol_char)
{
	if (clear)
		str.clear();

	char c = 0;
	std::size_t ws_erase_beg = 0;
	bool skip_ws = trim;

	for (std::size_t i = 0; i < field_size && is.get(c) && c != eol_char; i++) {
		if (skip_ws && std::isspace(c, std::locale::classic()))
			continue;

		str.push_back(c);	

		if (trim && !std::isspace(c, std::locale::classic()))
			ws_erase_beg = str.size(); 

		skip_ws = false;
	}

	checkStreamState(is, err_msg);

	if (c == eol_char)
		is.putback(eol_char);

	if (trim)
		str.resize(ws_erase_beg);

	return str;
}

void Chem::writeLine(std::ostream& os, const std::string& line, const std::string& err_msg, 
					 bool check_llen, bool trim, bool trunc, std::size_t max_llen, char eol_char)
{
	if (check_llen && line.size() > max_llen) {
		if (trim) {
			std::string trimmed_line = line;
				
			trimString(trimmed_line);

			if (trimmed_line.size() > max_llen) {
				if (!trunc)
					throw Base::IOError(err_msg + ": length of '" + trimmed_line + "' exceeds limit of " 
										+ boost::lexical_cast<std::string>(max_llen) + " allowed characters");
				else
					os << trimmed_line.substr(0, max_llen) << eol_char;

			} else
				os << trimmed_line << eol_char;

		} else {
			if (!trunc)
				throw Base::IOError(err_msg + ": length of '" + line + "' exceeds limit of " 
									+ boost::lexical_cast<std::string>(max_llen) + " allowed characters");
			else
				os << line.substr(0, max_llen) << eol_char;
		}

	} else
		os << (trim ? trimStringCopy(line) : line) << eol_char;
}

void Chem::writeString(std::ostream& os, std::size_t field_size, const std::string& str, 
					   const std::string& err_msg, bool trim, bool trunc, bool align_right)
{
	os << std::setw(field_size);

	if (align_right)
		os << std::right;
	else
		os << std::left;

	if (str.size() > field_size) {
		if (trim) {
			std::string trimmed_str = str;

			trimString(trimmed_str);

			if (trimmed_str.size() > field_size) {
				if (!trunc)
					throw Base::IOError(err_msg + ": length of '" + trimmed_str + "' exceeds limit of " 
										+ boost::lexical_cast<std::string>(field_size) + " allowed characters");
				else
					os << trimmed_str.substr(0, field_size);

			} else
				os << trimmed_str;

		} else {
			if (!trunc)
				throw Base::IOError(err_msg + ": length of '" + str + "' exceeds limit of " 
									+ boost::lexical_cast<std::string>(field_size) + " allowed characters");
			else
				os << str.substr(0, field_size);
		}

	} else
		os << (trim ? trimStringCopy(str) : str);
}

void Chem::writeSubstring(std::ostream& os, const std::string& str, std::size_t start, std::size_t end)
{
	std::string::const_iterator str_beg = str.begin();

	std::copy(str_beg + start, str_beg + end, std::ostream_iterator<char>(os));
}
