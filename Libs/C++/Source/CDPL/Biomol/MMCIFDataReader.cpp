/* 
 * MMCIFDataReader.cpp 
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


#include "StaticInit.hpp"

#include <locale>
#include <cassert>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "MMCIFDataReader.hpp"
#include "MMCIFFormatData.hpp"


using namespace CDPL;


enum Biomol::MMCIFDataReader::Token : int
{
    EOI = 0,
    PLAIN_STRING,
    QUOTED_STRING,
    TEXT_FIELD
};


bool Biomol::MMCIFDataReader::hasMoreData(std::istream& is)
{
    init(is);

    while (auto token = nextToken(is)) {
        if (token == PLAIN_STRING && Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX)) {
            putbackToken(is);
            return true;
        }            
    }
  
    return false;
}

bool Biomol::MMCIFDataReader::skipMolecule(std::istream& is)
{
    init(is);
    
    while (auto token = nextToken(is)) {
        if (token == PLAIN_STRING && Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX))
            return true;
    }
    
    return false;
}

bool Biomol::MMCIFDataReader::readMolecule(std::istream& is, Chem::Molecule& mol)
{
    auto data = parseInput(is);

    if (!data)
        return false;
    
    setMMCIFData(mol, data);
    
    return true;
}

void Biomol::MMCIFDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);

    is.imbue(std::locale::classic());
}

Biomol::MMCIFData::SharedPointer Biomol::MMCIFDataReader::parseInput(std::istream& is)
{
    if (!hasMoreData(is))
        return MMCIFData::SharedPointer();

    if (!nextToken(is))
        throw Base::IOError("MMCIFDataReader: unexpected end of input while reading data block identifier");

    assert(tokenValue.length() >= MMCIF::DATA_BLOCK_ID_PREFIX.length());
 
    MMCIFData::SharedPointer data(new MMCIFData(tokenValue.substr(MMCIF::DATA_BLOCK_ID_PREFIX.length())));
    std::string cat_name, item_name;
    
    while (auto token = nextToken(is)) {
        if (token != PLAIN_STRING) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: invalid data name or keyword");
        }
        
        assert(!tokenValue.empty());
        
        if (Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX)) {
            putbackToken(is);
            break;
        }
      
        if (Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD)) {
            parseLoopSection(is, *data);
            continue;
        }

        if (!extractCategoryandItemNames(cat_name, item_name, strictErrorChecking))
            continue;

        if (!nextToken(is))
            throw Base::IOError("MMCIFDataReader: unexpected end of input while reading data value");

        auto cat = (data->getNumCategories() == 0 ? nullptr : &data->lastCategory());
 
        if (!cat || !Internal::isEqualCI(cat_name, cat->getName()) || (cat->getNumValueRows() > 1))
            cat = &data->addCategory(cat_name);
            
        cat->addItem(item_name).addValue(tokenValue);
    }

    return data;
}

void Biomol::MMCIFDataReader::parseLoopSection(std::istream& is, MMCIFData& data)
{
    MMCIFData::Category* cat = nullptr;
    std::string cat_name, item_name;
    
    while (true) {
        auto token = nextToken(is);
        
        if (!token)
            return;

        assert(!tokenValue.empty());
        
        if (token != PLAIN_STRING) {
            putbackToken(is);
            break;
        }

        if (Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX) ||
            Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD)) {
            putbackToken(is);
            return;
        }

        if (!extractCategoryandItemNames(cat_name, item_name, false)) {
            putbackToken(is);
            break;
        }

        if (!cat)
            cat = &data.addCategory(cat_name);
        
        else if (!Internal::isEqualCI(cat_name, cat->getName())) {
            putbackToken(is);
            break;
        }
                 
        cat->addItem(item_name);
    }

    if (!cat)
        return;

    for (std::size_t i = 0, num_items = cat->getNumItems(); ; i++) {
        auto item_idx = (i % num_items);
        auto token = nextToken(is);

        if (!token) {
            if (item_idx != 0 && strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: unexpected end of input while reading " + MMCIF::LOOP_KEYWORD + " section data values");

            return;
        }

        assert(!tokenValue.empty());
 
        if (item_idx == 0 && token == PLAIN_STRING &&
            (tokenValue[0] == MMCIF::DATA_NAME_PREFIX ||
             Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX) ||
             Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD))) {

            putbackToken(is);
            return;
        }

        cat->getItem(item_idx).addValue(tokenValue);
    }
}

bool Biomol::MMCIFDataReader::extractCategoryandItemNames(std::string& cat_name, std::string& item_name, bool strict) const
{
    if (tokenValue[0] != MMCIF::DATA_NAME_PREFIX) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: invalid data name");

        return false;
    }

    std::string::size_type cat_pfx_len = tokenValue.find(MMCIF::CATEGORY_NAME_SEPARATOR);

    if (cat_pfx_len == std::string::npos) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: data name without category prefix");

        return false;
    }

    if (cat_pfx_len == (tokenValue.length() - 1)) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: zero-length data item name");

        return false;
    }

    cat_name.assign(tokenValue, 1, cat_pfx_len - 1);
    item_name.assign(tokenValue, cat_pfx_len + 1);
    
    return true;
}

Biomol::MMCIFDataReader::Token Biomol::MMCIFDataReader::nextToken(std::istream& is)
{
    enum State
    {
        START,
        EOL,
        PLAIN_STR,
        QUOTED_STR_1,
        QUOTED_STR_1_END,
        QUOTED_STR_2,
        QUOTED_STR_2_END,
        TXT_FIELD,
        COMMENT
    };

    lastStreamPos = is.tellg();
    tokenValue.clear();

    State state = START;

    while (true) {
        char c = 0;

        if (!is.get(c) && is.bad())
            throw Base::IOError("MMCIFDataReader: stream read error");
  
        switch (state) {

            case START:
                if (is.eof())
                    return EOI;

                switch (c) {

                    case MMCIF::END_OF_LINE:
                        state = EOL;
                        continue;
                        
                    case MMCIF::COMMENT_PREFIX:
                        state = COMMENT;
                        continue;

                    case MMCIF::QUOTED_STRING_DELIMITER_1:
                        state = QUOTED_STR_1;
                        continue;

                    case MMCIF::QUOTED_STRING_DELIMITER_2:
                        state = QUOTED_STR_2;
                        continue;
                        
                    default:
                        if (std::isspace(c, std::locale::classic()))
                            continue;

                        tokenValue.push_back(c);
                        state = PLAIN_STR;
                        continue;
                }

            case EOL:
                if (is.eof())
                    return EOI;
                
                if (c == MMCIF::TEXT_FIELD_DELIMITER)
                    state = TXT_FIELD;

                else {
                    is.unget();
                    state = START;
                }

                continue;
                
            case COMMENT:
                if (is.eof() || c == MMCIF::END_OF_LINE) {
                    is.unget();
                    state = START;
                }

                continue;
                
            case PLAIN_STR:
                if (is.eof() || std::isspace(c, std::locale::classic())) {
                    is.unget();
                    return PLAIN_STRING;
                }

                tokenValue.push_back(c);
                continue;
                
            case QUOTED_STR_1:
                if (is.eof() || c == MMCIF::END_OF_LINE)
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading quoted string");
                
                if (c == MMCIF::QUOTED_STRING_DELIMITER_1)
                    state = QUOTED_STR_1_END;
                else
                    tokenValue.push_back(c);

                continue;

            case QUOTED_STR_1_END:
                if (is.eof() || std::isspace(c, std::locale::classic())) {
                    is.unget();
                    return QUOTED_STRING;
                }

                tokenValue.push_back(MMCIF::QUOTED_STRING_DELIMITER_1);
                tokenValue.push_back(c);
                state = QUOTED_STR_1;
                continue;
                    
            case QUOTED_STR_2:
                if (is.eof() || c == MMCIF::END_OF_LINE)
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading quoted string");
                
                if (c == MMCIF::QUOTED_STRING_DELIMITER_2)
                    state = QUOTED_STR_2_END;
                else
                    tokenValue.push_back(c);

                continue;

            case QUOTED_STR_2_END:
                if (is.eof() || std::isspace(c, std::locale::classic())) {
                    is.unget();
                    return QUOTED_STRING;
                }

                tokenValue.push_back(MMCIF::QUOTED_STRING_DELIMITER_2);
                tokenValue.push_back(c);
                state = QUOTED_STR_2;
                continue;
                
            case TXT_FIELD:
                if (is.eof()) 
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading text field");

                if (c == MMCIF::TEXT_FIELD_DELIMITER && !tokenValue.empty() && tokenValue.back() == MMCIF::END_OF_LINE) {
                    tokenValue.resize(tokenValue.length() - 1);
                    return TEXT_FIELD;
                }

                tokenValue.push_back(c);
                continue;
                
            default:
                throw Base::IOError("MMCIFDataReader: bad tokenizer state");
        }
    }
}

void Biomol::MMCIFDataReader::putbackToken(std::istream& is) const
{
    is.clear();

    if (!is.seekg(lastStreamPos))
        throw Base::IOError("MMCIFDataReader: setting stram input position failed");
}
