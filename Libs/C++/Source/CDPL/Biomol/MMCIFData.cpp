/* 
 * MMCIFData.cpp 
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

#include <algorithm>
#include <ostream>
#include <iomanip>
#include <locale>
#include <utility>

#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "MMCIFFormatData.hpp"


using namespace CDPL;


namespace
{

    enum class StringOutputType
    {
        PLAIN,
        QUOTED_1,
        QUOTED_2,
        TEXT_FIELD
    };

    constexpr std::size_t NEW_LINE_FIELD_WIDTH = 80;
    
    bool containsCharFollowedByWS(char c, const std::string& str)
    {
        for (std::string::size_type i = str.find_first_of(c); i != std::string::npos; i = str.find_first_of(c, i)) {
            if (i < (str.length() - 1) && Biomol::MMCIF::isSpace(str[i + 1]))
                return true;
        }

        return false;
    }

    bool isOrdinaryChar(char c)
    {
        switch (c) {

            case '!':
            case '%':
            case '&':
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
            case '-':
            case '.':
            case '/':
            case ':':
            case '<':
            case '=':
            case '>':
            case '?':
            case '@':
            case '\\':
            case '^':
            case '`':
            case '{':
            case '|':
            case '}':
            case '~':
                return true;

            default:
                return std::isalnum(c, std::locale::classic());
        }
    }

    bool isProblematicChar(char c)
    {
        switch (c) {

            case '(':
            case ')':
            case '[':
            case ']':
                return true;

            default:
                return false;
        }
    }
    
    StringOutputType getOutputType(const std::string& str)
    {
        using namespace Biomol;

        if (str.empty())
            return StringOutputType::QUOTED_1;
        
        if (str.find(MMCIF::END_OF_LINE) != std::string::npos)
            return StringOutputType::TEXT_FIELD;

        if (str.find('\r') != std::string::npos)
            return StringOutputType::TEXT_FIELD;

        for (auto c : str)
            if (isProblematicChar(c) || MMCIF::isSpace(c)) {
                if (str.find(MMCIF::QUOTED_STRING_DELIMITER_1) == std::string::npos)
                    return StringOutputType::QUOTED_1;

                if (str.find(MMCIF::QUOTED_STRING_DELIMITER_2) == std::string::npos)
                    return StringOutputType::QUOTED_2;
                
                if (!containsCharFollowedByWS(MMCIF::QUOTED_STRING_DELIMITER_1, str))
                    return StringOutputType::QUOTED_1;

                if (!containsCharFollowedByWS(MMCIF::QUOTED_STRING_DELIMITER_2, str))
                    return StringOutputType::QUOTED_2;

                return StringOutputType::TEXT_FIELD;
            }

        if (!isOrdinaryChar(str[0]) ||
            Internal::isEqualCI(str, MMCIF::LOOP_KEYWORD) ||
            Internal::isEqualCI(str, MMCIF::STOP_KEYWORD) ||
            Internal::isEqualCI(str, MMCIF::GLOBAL_KEYWORD) ||
            Internal::startsWithCI(str, MMCIF::DATA_BLOCK_ID_PREFIX) ||
            Internal::startsWithCI(str, MMCIF::SAVE_FRAME_PREFIX)) {

            if (str.find(MMCIF::QUOTED_STRING_DELIMITER_1) == std::string::npos)
                return StringOutputType::QUOTED_1;
            
            return StringOutputType::QUOTED_2;
        }

        if (str.find_first_of(MMCIF::QUOTED_STRING_DELIMITER_1, 1) != std::string::npos)
            return StringOutputType::QUOTED_2;

        if (str.find_first_of(MMCIF::QUOTED_STRING_DELIMITER_2, 1) != std::string::npos)
            return StringOutputType::QUOTED_1;
             
        return StringOutputType::PLAIN;
    }

    std::size_t getMaxItemNameLength(const Biomol::MMCIFData::Category& cat)
    {
        std::string::size_type max_len = 0;

        for (auto& item : cat)
            max_len = std::max(max_len, item.getName().length());

        return max_len;
    }

    std::size_t getMaxItemValueLength(const Biomol::MMCIFData::Item& item)
    {
        std::string::size_type max_len = 0;

        for (auto& value : item) {
            switch (getOutputType(value)) {

                case StringOutputType::PLAIN:
                    max_len = std::max(max_len, value.length() > NEW_LINE_FIELD_WIDTH ? max_len : value.length());
                    continue;

                case StringOutputType::QUOTED_1:
                case StringOutputType::QUOTED_2:
                    max_len = std::max(max_len, (value.length() + 2) > NEW_LINE_FIELD_WIDTH ? max_len : value.length() + 2);

                default:
                    continue;
            }
        }

        return max_len;
    }

    bool outputValue(std::ostream& os, const std::string& value, bool after_nl, std::size_t width = 0)
    {
        using namespace Biomol;

        switch (getOutputType(value)) {

            case StringOutputType::PLAIN:
                if (value.length() > NEW_LINE_FIELD_WIDTH) {
                    if (!after_nl)
                        os << MMCIF::END_OF_LINE;
                    
                    os << value << MMCIF::END_OF_LINE;
                    return true;
                }
                
                os << std::setw(width) << std::left << value;
                return false;

            case StringOutputType::QUOTED_1:
                if ((value.length() + 2) > NEW_LINE_FIELD_WIDTH) {
                    if (!after_nl)
                        os << MMCIF::END_OF_LINE;
                    
                    os << MMCIF::QUOTED_STRING_DELIMITER_1 << value << MMCIF::QUOTED_STRING_DELIMITER_1 << MMCIF::END_OF_LINE;
                    return true;
                }
                
                os << std::setw(width) << std::left << (MMCIF::QUOTED_STRING_DELIMITER_1 + value + MMCIF::QUOTED_STRING_DELIMITER_1);
                return false;

            case StringOutputType::QUOTED_2:
                if ((value.length() + 2) > NEW_LINE_FIELD_WIDTH) {
                    if (!after_nl)
                        os << MMCIF::END_OF_LINE;
                    
                    os << MMCIF::QUOTED_STRING_DELIMITER_2 << value << MMCIF::QUOTED_STRING_DELIMITER_2 << MMCIF::END_OF_LINE;
                    return true;
                }
                    
                os << std::setw(width) << std::left << (MMCIF::QUOTED_STRING_DELIMITER_2 + value + MMCIF::QUOTED_STRING_DELIMITER_2);
                return false;

            default:
                if (!after_nl)
                    os << MMCIF::END_OF_LINE;
                
                os << MMCIF::TEXT_FIELD_DELIMITER << value << MMCIF::END_OF_LINE
                   << MMCIF::TEXT_FIELD_DELIMITER << MMCIF::END_OF_LINE;
                return true;
        }
    }
}


Biomol::MMCIFData::MMCIFData(const std::string& id): id(id)
{}

void Biomol::MMCIFData::setID(const std::string& id)
{
    this->id = id;
}

const std::string& Biomol::MMCIFData::getID() const
{
    return id;
}

void Biomol::MMCIFData::clear()
{
    categories.clear();
    id.clear();
}

std::size_t Biomol::MMCIFData::getNumCategories() const
{
    return categories.size();
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(std::size_t index)
{
    if (index >= categories.size())
        throw Base::IndexError("MMCIFData: category index out of bounds");

    return categories[index];
}

const Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(std::size_t index) const
{
    if (index >= categories.size())
        throw Base::IndexError("MMCIFData: category index out of bounds");

    return categories[index];
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(const std::string& name)
{
    auto it = getCategoryIter(name);

    if (it != categories.end())
        return *it;

    throw Base::ItemNotFound("MMCIFData: category not found");
}
            
const Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(const std::string& name) const
{
    auto it = getCategoryIter(name);

    if (it != categories.end())
        return *it;

    throw Base::ItemNotFound("MMCIFData: category not found");
}

const Biomol::MMCIFData::Category* Biomol::MMCIFData::findCategory(const std::string& name) const
{
    auto it = getCategoryIter(name);

    if (it == categories.end())
        return nullptr;

    return &*it;
}

Biomol::MMCIFData::Category* Biomol::MMCIFData::findCategory(const std::string& name)
{
    auto it = getCategoryIter(name);

    if (it == categories.end())
        return nullptr;

    return &*it;
}

const Biomol::MMCIFData::Category& Biomol::MMCIFData::lastCategory() const
{
    if (categories.empty())
        throw Base::OperationFailed("MMCIFData: no categories available");

    return categories.back();
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::lastCategory()
{
    if (categories.empty())
        throw Base::OperationFailed("MMCIFData: no categories available");

    return categories.back();
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::addCategory(const std::string& name, bool front)
{
    if (front) {
        categories.push_front(new Category(name));
        
        return categories.front();
    }
    
    categories.push_back(new Category(name));

    return categories.back();
}
            
Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::removeCategory(const CategoryIterator& it)
{
    if (it < categories.begin() || it >= categories.end())
        throw Base::RangeError("MMCIFData: category iterator out of valid range");

    return categories.erase(it);
}

bool Biomol::MMCIFData::removeCategory(const std::string& name)
{
    auto it = getCategoryIter(name);

    if (it == categories.end())
        return false;

    categories.erase(it);
    
    return true;
}

void Biomol::MMCIFData::removeCategory(std::size_t index)
{
   if (index >= categories.size())
        throw Base::IndexError("MMCIFData: category index out of bounds");

   categories.erase(categories.begin() + index);
}

void Biomol::MMCIFData::swap(MMCIFData& data)
{
    categories.swap(data.categories);
    id.swap(data.id);
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::getCategoriesBegin() const
{
    return categories.begin();
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::getCategoriesBegin()
{
    return categories.begin();
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::getCategoriesEnd() const
{
    return categories.end();
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::getCategoriesEnd()
{
    return categories.end();
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::begin() const
{
    return categories.begin();
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::begin()
{
    return categories.begin();
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::end() const
{
    return categories.end();
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::end()
{
    return categories.end();
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::getCategoryIter(const std::string& name) const
{
    return std::find_if(categories.begin(), categories.end(), [&](const Category& cat) { return Internal::isEqualCI(name, cat.getName()); });
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::getCategoryIter(const std::string& name)
{
    return std::find_if(categories.begin(), categories.end(), [&](const Category& cat) { return Internal::isEqualCI(name, cat.getName()); });
}


// -- Category --

const std::string& Biomol::MMCIFData::Category::getName() const
{
    return name;
}

void Biomol::MMCIFData::Category::clear()
{
    items.clear();
}

std::size_t Biomol::MMCIFData::Category::getNumItems() const
{
    return items.size();
}

Biomol::MMCIFData::Item& Biomol::MMCIFData::Category::getItem(std::size_t index)
{
    if (index >= items.size())
        throw Base::IndexError("MMCIFData::Category: item index out of bounds");

    return items[index];
}

const Biomol::MMCIFData::Item& Biomol::MMCIFData::Category::getItem(std::size_t index) const
{
    if (index >= items.size())
        throw Base::IndexError("MMCIFData::Category: item index out of bounds");

    return items[index];
}

Biomol::MMCIFData::Item& Biomol::MMCIFData::Category::getItem(const std::string& name)
{
    auto it = getItemIter(name);

    if (it != items.end())
        return *it;

    throw Base::ItemNotFound("MMCIFData::Category: item not found");
}
            
const Biomol::MMCIFData::Item& Biomol::MMCIFData::Category::getItem(const std::string& name) const
{
    auto it = getItemIter(name);

    if (it != items.end())
        return *it;

    throw Base::ItemNotFound("MMCIFData::Category: item not found");
}

const Biomol::MMCIFData::Item* Biomol::MMCIFData::Category::findItem(const std::string& name) const
{
    auto it = getItemIter(name);

    if (it == items.end())
        return nullptr;

    return &*it;
}

Biomol::MMCIFData::Item* Biomol::MMCIFData::Category::findItem(const std::string& name)
{
    auto it = getItemIter(name);

    if (it == items.end())
        return nullptr;

    return &*it;
}

Biomol::MMCIFData::Item& Biomol::MMCIFData::Category::addItem(const std::string& name)
{
    items.push_back(new Item(name));

    return items.back();
}
            
Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::removeItem(const ItemIterator& it)
{
    if (it < items.begin() || it >= items.end())
        throw Base::RangeError("MMCIFData::Category: item iterator out of valid range");

    return items.erase(it);
}

bool Biomol::MMCIFData::Category::removeItem(const std::string& name)
{
    auto it = getItemIter(name);

    if (it == items.end())
        return false;

    items.erase(it);
    
    return true;
}

void Biomol::MMCIFData::Category::removeItem(std::size_t index)
{
   if (index >= items.size())
        throw Base::IndexError("MMCIFData::Category: item index out of bounds");

   items.erase(items.begin() + index);
}

void Biomol::MMCIFData::Category::swap(Category& cat)
{
    items.swap(cat.items);
    name.swap(cat.name);
}

Biomol::MMCIFData::Category::ConstItemIterator Biomol::MMCIFData::Category::getItemsBegin() const
{
    return items.begin();
}

Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::getItemsBegin()
{
    return items.begin();
}

Biomol::MMCIFData::Category::ConstItemIterator Biomol::MMCIFData::Category::getItemsEnd() const
{
    return items.end();
}

Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::getItemsEnd()
{
    return items.end();
}

Biomol::MMCIFData::Category::ConstItemIterator Biomol::MMCIFData::Category::begin() const
{
    return items.begin();
}

Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::begin()
{
    return items.begin();
}

Biomol::MMCIFData::Category::ConstItemIterator Biomol::MMCIFData::Category::end() const
{
    return items.end();
}

Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::end()
{
    return items.end();
}

Biomol::MMCIFData::Category::ConstItemIterator Biomol::MMCIFData::Category::getItemIter(const std::string& name) const
{
    return std::find_if(items.begin(), items.end(), [&](const Item& item) { return Internal::isEqualCI(name, item.getName()); });
}

Biomol::MMCIFData::Category::ItemIterator Biomol::MMCIFData::Category::getItemIter(const std::string& name)
{
    return std::find_if(items.begin(), items.end(), [&](const Item& item) { return Internal::isEqualCI(name, item.getName()); });
}

std::size_t Biomol::MMCIFData::Category::getNumValueRows() const
{
    if (items.empty())
        return 0;
    
    std::size_t row_cnt = 0;
    
    for (auto& item : items)
        row_cnt = std::max(row_cnt, item.getNumValues());

    return row_cnt;
}


// -- Item --

const std::string& Biomol::MMCIFData::Item::getName() const
{
    return name;
}

void Biomol::MMCIFData::Item::clear() 
{
    values.clear();
}

std::size_t Biomol::MMCIFData::Item::getNumValues() const
{
    return values.size();
}

const std::string& Biomol::MMCIFData::Item::getValue(std::size_t index) const
{
    if (index >= values.size())
        throw Base::IndexError("MMCIFData::Item: value index out of bounds");

    return values[index];
}

void Biomol::MMCIFData::Item::setValue(std::size_t index, const std::string& value)
{
    if (index >= values.size())
        throw Base::IndexError("MMCIFData::Item: value index out of bounds");

    values[index] = value;
}

void Biomol::MMCIFData::Item::setValue(std::size_t index, std::string&& value)
{
    if (index >= values.size())
        throw Base::IndexError("MMCIFData::Item: value index out of bounds");

    values[index] = std::move(value);
}

void Biomol::MMCIFData::Item::addValue(const std::string& value)
{
    values.emplace_back(value);
}

void Biomol::MMCIFData::Item::addValue(std::string&& value)
{
    values.emplace_back(std::move(value));
}

Biomol::MMCIFData::Item::ValueIterator Biomol::MMCIFData::Item::removeValue(const ValueIterator& it)
{
    if (it < values.begin() || it >= values.end())
        throw Base::RangeError("MMCIFData::Item: value iterator out of valid range");

    return values.erase(it);
}

void Biomol::MMCIFData::Item::removeValue(std::size_t index)
{
   if (index >= values.size())
        throw Base::IndexError("MMCIFData::Item: value index out of bounds");

   values.erase(values.begin() + index);
}

void Biomol::MMCIFData::Item::swap(Item& item)
{
    values.swap(item.values);
    name.swap(item.name);
}

Biomol::MMCIFData::Item::ConstValueIterator Biomol::MMCIFData::Item::getValuesBegin() const
{
    return values.begin();
}

Biomol::MMCIFData::Item::ValueIterator Biomol::MMCIFData::Item::getValuesBegin()
{
    return values.begin();
}

Biomol::MMCIFData::Item::ConstValueIterator Biomol::MMCIFData::Item::getValuesEnd() const
{
    return values.end();
}

Biomol::MMCIFData::Item::ValueIterator Biomol::MMCIFData::Item::getValuesEnd()
{
    return values.end();
}

Biomol::MMCIFData::Item::ConstValueIterator Biomol::MMCIFData::Item::begin() const
{
    return values.begin();
}

Biomol::MMCIFData::Item::ValueIterator Biomol::MMCIFData::Item::begin()
{
    return values.begin();
}

Biomol::MMCIFData::Item::ConstValueIterator Biomol::MMCIFData::Item::end() const
{
    return values.end();
}

Biomol::MMCIFData::Item::ValueIterator Biomol::MMCIFData::Item::end()
{
    return values.end();
}

std::ostream& Biomol::operator<<(std::ostream& os, const Biomol::MMCIFData& data)
{
    os << MMCIF::DATA_BLOCK_ID_PREFIX << data.getID() << MMCIF::END_OF_LINE << MMCIF::COMMENT_PREFIX << MMCIF::END_OF_LINE;

    for (auto& cat : data)
        os << cat << MMCIF::COMMENT_PREFIX << MMCIF::END_OF_LINE;

    return os;
}

std::ostream& Biomol::operator<<(std::ostream& os, const Biomol::MMCIFData::Category& cat)
{
    if (cat.getNumItems() == 0)
        return os;
    
    auto num_rows = cat.getNumValueRows();

    os << std::setfill(' ');
    
    if (num_rows <= 1) {
        auto max_name_len = getMaxItemNameLength(cat) + 3;

        for (auto& item : cat) {
            if (num_rows == 0) {
                os << MMCIF::COMMENT_PREFIX << MMCIF::DATA_NAME_PREFIX << cat.getName()
                   << MMCIF::CATEGORY_NAME_SEPARATOR << item.getName() << MMCIF::END_OF_LINE;
                continue;
            }
                
            os << MMCIF::DATA_NAME_PREFIX << cat.getName() << MMCIF::CATEGORY_NAME_SEPARATOR
               << std::setw(max_name_len) << std::left << item.getName();
            
            if (!outputValue(os, item.getNumValues() != 0 ? item.getValue(0) : MMCIF:: MISSING_DATA_VALUE, false))
                os << MMCIF::END_OF_LINE;
        }

        return os;
    }

    std::vector<std::size_t> field_widths;
    
    os << MMCIF::LOOP_KEYWORD << MMCIF::END_OF_LINE;

    for (auto& item : cat) {
        os << MMCIF::DATA_NAME_PREFIX << cat.getName() << MMCIF::CATEGORY_NAME_SEPARATOR << item.getName()
           << ' ' /* trailing space only for LigandScout bug compatibility */ << MMCIF::END_OF_LINE;

        field_widths.push_back(std::max(std::size_t(1), getMaxItemValueLength(item)));
    }

    for (std::size_t i = 0, num_items = cat.getNumItems(); i < num_rows; i++) {
        bool at_nl = true;
        
        for (std::size_t j = 0; j < num_items; j++) {
            auto& item = cat.getItem(j);
            
            at_nl = outputValue(os, item.getNumValues() > i ? item.getValue(i) : MMCIF:: MISSING_DATA_VALUE, at_nl, field_widths[j] + 1);
        }

        if (!at_nl)
            os << MMCIF::END_OF_LINE;
    }
    
    return os;
}
