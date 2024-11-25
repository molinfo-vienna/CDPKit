/* 
 * StringDataIOUtilitiesImpl.hpp
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
#include <iterator>
#include <sstream>
#include <iomanip>
#include <locale>
#include <clocale>
#include <limits>
#include <cstdlib>

#include "CDPL/Base/Exceptions.hpp"

#include "StringUtilities.hpp"


void CDPL::Internal::checkStreamState(const std::istream& is, const char* err_msg)
{
    if (!is.good())
        throw Base::IOError(std::string(err_msg) + ": unexpected end of data or unspecified read error");
}

void CDPL::Internal::skipChars(std::istream& is, std::size_t count, const char* err_msg, char eol_char)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();

    char c = 0;
    auto rdbuf = is.rdbuf();
    
    for (std::size_t i = 0; i < count; i++) {
        int tmp = rdbuf->sbumpc();

        if (std::istream::traits_type::eq_int_type(tmp, EOF_)) {
            is.clear(std::ios_base::eofbit | std::ios_base::failbit);
            break;
        }

        c = std::istream::traits_type::to_char_type(tmp);

        if (c == eol_char)
            break;
    }

    checkStreamState(is, err_msg);

    if (c == eol_char)
        is.putback(eol_char);
}

bool CDPL::Internal::skipToString(std::istream& is, const std::string& str, const char* err_msg, bool pos_after)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();

    checkStreamState(is, err_msg);
 
    std::size_t str_len = str.length();
    auto rdbuf = is.rdbuf();
    
    while (true) {
        std::istream::pos_type last_spos = is.tellg();
        std::size_t i = 0;

        for ( ; i < str_len; i++) {
            int tmp = rdbuf->sbumpc();

            if (std::istream::traits_type::eq_int_type(tmp, EOF_))
                return false;

            if (std::istream::traits_type::to_char_type(tmp) != str[i]) {
                is.seekg(last_spos + std::istream::pos_type(1));
                checkStreamState(is, err_msg);
                break;
            }
        }
    
        if (i == str_len) {
            if (!pos_after) {
                is.seekg(last_spos);
                checkStreamState(is, err_msg);
            }
            
            return true;
        }
    }

    return false;
}

bool CDPL::Internal::readToString(std::istream& is, const std::string& str, std::string& data, const char* err_msg, bool inc_str)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();

    checkStreamState(is, err_msg);

    std::size_t str_len = str.length();
    auto rdbuf = is.rdbuf();
    
    while (true) {
        int tmp = rdbuf->sbumpc();

        if (std::istream::traits_type::eq_int_type(tmp, EOF_))
            return false;

        char c = std::istream::traits_type::to_char_type(tmp);

        data.push_back(c);

        std::size_t data_len = data.length();

        if (data_len < str_len)
            continue;

        std::size_t cmp_pos = data_len - str_len;

        if (std::equal(data.begin() + cmp_pos, data.end(), str.begin())) {
            if (!inc_str)
                data.resize(cmp_pos);

            return true;
        }
    }

    return false;
}

template <typename T>
T CDPL::Internal::parseNumber(const char* str_beg, const char* str_end, const char* err_msg, bool throw_ex,
                              const T empty_def_val, const T err_def_val)
{
    if (str_beg == str_end)
        return empty_def_val;

    T val;
    char* parse_end;

    if (std::numeric_limits<T>::is_integer) {
        if (std::numeric_limits<T>::is_signed)
            val = T(std::strtol(str_beg, &parse_end, 10));
        else
            val = T(std::strtoul(str_beg, &parse_end, 10));

    } else {
        const char* old_loc = std::setlocale(LC_NUMERIC, "C");

        val = T(std::strtod(str_beg, &parse_end));

        std::setlocale(LC_NUMERIC, old_loc);
    }

    if (str_end != parse_end) {
        if (throw_ex)
            throw Base::IOError(std::string(err_msg) + ": '" + std::string(str_beg) + "' invalid number format");

        return err_def_val;
    }

    return val;
}

template <typename T>
T CDPL::Internal::parseNumber(const std::string& str, const char* err_msg, bool throw_ex,
                              const T empty_def_val, const T err_def_val)
{
    const char* c_str = str.c_str();

    return parseNumber<T>(c_str, c_str + str.size(), err_msg, throw_ex, empty_def_val, err_def_val);
}

template <typename T, std::size_t FieldSize>
T CDPL::Internal::readNumber(std::istream& is, const char* err_msg, bool throw_ex,
                             const T empty_def_val, const T err_def_val, char eol_char)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();
            
    char  buf[FieldSize + 1];
    char* buf_end_ptr = buf;
    char  c           = 0;
    auto  rdbuf       = is.rdbuf();

    for (std::size_t i = 0; i < FieldSize; i++) {
        int tmp = rdbuf->sbumpc();

        if (std::istream::traits_type::eq_int_type(tmp, EOF_)) {
            is.clear(std::ios_base::eofbit | std::ios_base::failbit);
            break;
        }
                
        c = std::istream::traits_type::to_char_type(tmp);

        if (c == eol_char)
            break;
                
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

void CDPL::Internal::writeWhitespace(std::ostream& os, std::size_t width)
{
    os << std::setfill(' ') << std::setw(width) << "";
}

void CDPL::Internal::writeEOL(std::ostream& os, char eol_char)
{
    os << eol_char;
}

void CDPL::Internal::skipLines(std::istream& is, std::size_t count, const char* err_msg, char eol_char, bool allow_eof)
{
    for (std::size_t i = 0; i < count && is.good(); i++)
        is.ignore(std::numeric_limits<std::streamsize>::max(), std::istream::traits_type::to_int_type(eol_char));

    if (allow_eof && is.rdstate() == std::istream::eofbit)
        return;
    
    checkStreamState(is, err_msg);
}
        
std::string& CDPL::Internal::readLine(std::istream& is, std::string& line, const char* err_msg, bool trim, 
                                      bool check_ll, std::size_t max_llen, char eol_char)
{
    std::getline(is, line, eol_char);

    checkStreamState(is, err_msg);

    if (!line.empty() && *line.rbegin() == '\r') 
        line.erase(--line.end());

    if (check_ll && line.size() > max_llen)
        throw Base::IOError(std::string(err_msg) + ": max. line length exceeded");

    if (trim)
        trimString(line);

    return line;
}

std::string& CDPL::Internal::readString(std::istream& is, std::size_t field_size, std::string& str, bool clear,
                                        const char* err_msg, bool trim, char eol_char)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();

    if (clear)
        str.clear();

    char c = 0;
    std::size_t ws_erase_beg = 0;
    bool skip_ws = trim;
    auto rdbuf = is.rdbuf();
    
    for (std::size_t i = 0; i < field_size; i++) {
        int tmp = rdbuf->sbumpc();

        if (std::istream::traits_type::eq_int_type(tmp, EOF_)) {
            is.clear(std::ios_base::eofbit | std::ios_base::failbit);
            break;
        }

        c = std::istream::traits_type::to_char_type(tmp);

        if (c == eol_char)
            break;

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

void CDPL::Internal::writeLine(std::ostream& os, const std::string& line, const char* err_msg, 
                               bool check_llen, bool trim, bool trunc, std::size_t max_llen, char eol_char)
{
    if (check_llen && line.size() > max_llen) {
        if (trim) {
            std::string trimmed_line = line;
                
            trimString(trimmed_line);

            if (trimmed_line.size() > max_llen) {
                if (!trunc)
                    throw Base::IOError(std::string(err_msg) + ": length of '" + trimmed_line + "' exceeds limit of " 
                                        + std::to_string(max_llen) + " allowed characters");
                else
                    os << trimmed_line.substr(0, max_llen) << eol_char;

            } else
                os << trimmed_line << eol_char;

        } else {
            if (!trunc)
                throw Base::IOError(std::string(err_msg) + ": length of '" + line + "' exceeds limit of " 
                                    + std::to_string(max_llen) + " allowed characters");
            else
                os << line.substr(0, max_llen) << eol_char;
        }

    } else
        os << (trim ? trimStringCopy(line) : line) << eol_char;
}

void CDPL::Internal::writeString(std::ostream& os, std::size_t field_size, const std::string& str, 
                                 const char* err_msg, bool trim, bool trunc, bool align_right)
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
                    throw Base::IOError(std::string(err_msg) + ": length of '" + trimmed_str + "' exceeds limit of " 
                                        + std::to_string(field_size) + " allowed characters");
                else
                    os << trimmed_str.substr(0, field_size);

            } else
                os << trimmed_str;

        } else {
            if (!trunc)
                throw Base::IOError(std::string(err_msg) + ": length of '" + str + "' exceeds limit of " 
                                    + std::to_string(field_size) + " allowed characters");
            else
                os << str.substr(0, field_size);
        }

    } else
        os << (trim ? trimStringCopy(str) : str);
}

void CDPL::Internal::writeSubstring(std::ostream& os, const std::string& str, std::size_t start, std::size_t end)
{
    std::string::const_iterator str_beg = str.begin();

    std::copy(str_beg + start, str_beg + end, std::ostream_iterator<char>(os));
}

template <typename T>
void CDPL::Internal::writeIntegerNumber(std::ostream& os, std::size_t field_size, const T value, const char* err_msg,
                                        bool align_left, char fill)
{
    std::ostringstream oss;

    oss.imbue(std::locale::classic());

    oss << std::setw(field_size) << std::setfill(fill);

    if (align_left)
        oss << std::left;
    else
        oss << std::right;

    oss << value;

    if (!oss.good())
        throw Base::IOError(std::string(err_msg) + ": conversion of numeric value to string failed");

    std::string val_str = oss.str();

    if (val_str.size() > field_size)
        throw Base::IOError(std::string(err_msg) + ": number exceeds limit of " + std::to_string(field_size) + " allowed digits");

    os << val_str;
}

template <typename T>
void CDPL::Internal::writeFloatNumber(std::ostream& os, std::size_t field_size, std::size_t prec,
                                      const T value, const char* err_msg)
{
    std::ostringstream oss;

    oss.imbue(std::locale::classic());

    oss << std::fixed << std::setw(field_size) << std::showpoint << std::setprecision(prec) << std::right << value;

    if (!oss.good())
        throw Base::IOError(std::string(err_msg) + ": conversion of numeric value to string failed");

    std::string val_str = oss.str();

    if (val_str.size() > field_size)
        throw Base::IOError(std::string(err_msg) + ": number exceeds limit of " + std::to_string(field_size) + " allowed characters");

    os << val_str;
}

void CDPL::Internal::beginXMLStartTag(std::ostream& os, const std::string& tag, std::size_t indent, const std::string& ns)
{
    if (indent > 0)
        writeWhitespace(os, indent);

    os << '<';

    if (!ns.empty())
        os << ns << ':';
    
    os << tag;
}

void CDPL::Internal::endXMLStartTag(std::ostream& os, bool empty, bool write_nl)
{
    if (empty)
        os << " />";
    else
        os << '>';
    
    if (write_nl)
        os << '\n';
}

void CDPL::Internal::writeXMLEndTag(std::ostream& os, const std::string& tag, std::size_t indent, const std::string& ns)
{
    if (indent > 0)
        writeWhitespace(os, indent);

    os << "</";

    if (!ns.empty())
        os << ns << ':';
  
    os << tag << ">\n";
}

template <typename T>
void CDPL::Internal::writeXMLAttribute(std::ostream& os, const std::string& name, const T& value)
{
    os << ' ' << name << "=\"" << value << '"';
}

const std::string& CDPL::Internal::escapeXMLData(const std::string& data, std::string& esc_data, bool attr_val, char keep_char)
{
    esc_data.clear();

    for (char c : data) {
        if (c != keep_char) {
            switch (c) {

                case '<':
                    esc_data.push_back('&'); esc_data.push_back('l'); esc_data.push_back('t'); esc_data.push_back(';');
                    continue;
                    
                case '>': 
                    esc_data.push_back('&'); esc_data.push_back('g'); esc_data.push_back('t'); esc_data.push_back(';');
                    continue;

                case '\'': 
                    esc_data.push_back('&'); esc_data.push_back('a'); esc_data.push_back('p'); esc_data.push_back('o'); esc_data.push_back('s'); esc_data.push_back(';');
                    continue;

                case '"': 
                    esc_data.push_back('&'); esc_data.push_back('q'); esc_data.push_back('u'); esc_data.push_back('o'); esc_data.push_back('t'); esc_data.push_back(';');
                    continue;

                case '&': 
                    esc_data.push_back('&'); esc_data.push_back('a'); esc_data.push_back('m'); esc_data.push_back('p'); esc_data.push_back(';'); 
                    continue;

                default:
                    if (std::isspace(c, std::locale::classic())) {
                        if (attr_val && ((c == ' ') || (c == '\t')))
                            break;
                        
                        esc_data.push_back('&'); esc_data.push_back('#'); esc_data.append(std::to_string(int(c))); esc_data.push_back(';');
                        continue;
                    }
            }
        }

        esc_data.push_back(c);
    }
    
    return esc_data;
}

bool CDPL::Internal::getNextXMLTag(std::istream& is, XMLTagInfo& tag_info, const char* err_msg, std::string* read_data)
{
    static constexpr int EOF_ = std::istream::traits_type::eof();

    enum State
    {
        START,
        TAG_NAME,
        TAG_NAME_END,
        EMPTY_TAG_END,
        ATTR_NAME,
        ATTR_VAL_DQ,
        ATTR_VAL_SQ
    };

    checkStreamState(is, err_msg);
    
    auto state = START;
    auto rdbuf = is.rdbuf();
    auto& locale = std::locale::classic();
    auto exit = false;
    
    while (!exit) {
        auto tmp = rdbuf->sbumpc();

        if (std::istream::traits_type::eq_int_type(tmp, EOF_))
            return false;
        
        auto c = std::istream::traits_type::to_char_type(tmp);

        if (read_data)
            read_data->push_back(c);
        
        switch (state) {

            case START:
                if (c != '<')
                    continue;
                
                state = TAG_NAME;
                    
                tag_info.name.clear();
                tag_info.ns.clear();
                
                tag_info.type = XMLTagInfo::UNDEF;
                tag_info.streamPos = is.tellg() - std::istream::pos_type(1);
                continue;

            case TAG_NAME:
                if (tag_info.name.empty()) {
                    if (c == '/') {
                        tag_info.type = XMLTagInfo::END;
                        continue;
                    }

                    if ((c != '_') && !std::isalpha(c, locale)) {
                        state = START;
                        continue;
                    }

                    if (tag_info.type == XMLTagInfo::UNDEF)
                        tag_info.type = XMLTagInfo::START;

                    tag_info.name.push_back(c);
                    continue;
                }

                switch (c) {

                    case '/':
                    case '>':
                        rdbuf->sungetc();

                        if (read_data)
                            read_data->pop_back();

                        state = TAG_NAME_END;
                        continue;

                    case ':':
                        if (tag_info.ns.empty()) {
                            tag_info.name.swap(tag_info.ns);
                            continue;
                        }
                        
                    case '_':
                    case '-':
                    case '.':
                        tag_info.name.push_back(c);
                        continue;
                }
                
                if (std::isspace(c, locale)) {
                    state = TAG_NAME_END;
                    continue;
                }
                    
                if (!std::isalnum(c, locale)) {
                    rdbuf->sungetc();

                    if (read_data)
                        read_data->pop_back();
                    
                    state = START;

                } else
                    tag_info.name.push_back(c);

                continue;

            case TAG_NAME_END:
                if (std::isspace(c, locale))
                    continue;

                if (c == '>') {
                    exit = true;
                    continue;
                }

                if (c == '/') {
                    state = EMPTY_TAG_END;
                    continue;
                }

                rdbuf->sungetc();

                if (read_data)
                    read_data->pop_back();

                state = ATTR_NAME;
                continue;

            case EMPTY_TAG_END:
                if (c == '>') {
                    tag_info.type = XMLTagInfo::EMPTY;
                    exit = true;
                    continue;
                }

                rdbuf->sungetc();

                if (read_data)
                    read_data->pop_back();              

                state = START;
                continue;

            case ATTR_NAME:
                if (std::isspace(c, locale)) {
                    state = TAG_NAME_END;
                    continue;
                }

                if (c == '"') {
                    state = ATTR_VAL_DQ;
                    continue;
                }

                if (c == '\'') {
                    state = ATTR_VAL_SQ;
                    continue;
                }

                if (c == '>') {
                    exit = true;
                    continue;
                }

                if (c == '/')
                    state = EMPTY_TAG_END;

                continue;

            case ATTR_VAL_DQ:
                if (c == '"')
                    state = TAG_NAME_END;
                
                continue;

            case ATTR_VAL_SQ:
                if (c == '\'')
                    state = TAG_NAME_END;
                
                continue;
        }
    }

    return true;
}
