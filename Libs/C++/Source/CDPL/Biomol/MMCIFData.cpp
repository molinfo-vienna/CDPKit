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

#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"


using namespace CDPL;


void Biomol::MMCIFData::clear()
{
    categories.clear();
}

std::size_t Biomol::MMCIFData::getNumCategories() const
{
    return categories.size();
}

bool Biomol::MMCIFData::isEmpty() const
{
    return categories.empty();
}
            
bool Biomol::MMCIFData::hasCategory(const std::string_view& name) const
{
    return (findCategory(name) != categories.end());
}
            
Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(std::size_t index)
{
   if (index >= categories.size())
        throw Base::IndexError("Biomol::MMCIFData: category index out of bounds");

    return categories[index];
}
            
const Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(std::size_t index) const
{
    if (index >= categories.size())
        throw Base::IndexError("Biomol::MMCIFData: category index out of bounds");

    return categories[index];
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(const std::string_view& name)
{
    auto it = findCategory(name);

    if (it != categories.end())
        return *it;

    throw Base::ItemNotFound("Biomol::MMCIFData: category not found");
}
            
const Biomol::MMCIFData::Category& Biomol::MMCIFData::getCategory(const std::string_view& name) const
{
    auto it = findCategory(name);

    if (it != categories.end())
        return *it;

    throw Base::ItemNotFound("Biomol::MMCIFData: category not found");
}

Biomol::MMCIFData::ConstCategoryIterator Biomol::MMCIFData::findCategory(const std::string_view& name) const
{
    return std::find_if(categories.begin(), categories.end(), [&](const Category& cat) { return Internal::isEqualCI(name, cat.getName()); });
}

Biomol::MMCIFData::CategoryIterator Biomol::MMCIFData::findCategory(const std::string_view& name)
{
    return std::find_if(categories.begin(), categories.end(), [&](const Category& cat) { return Internal::isEqualCI(name, cat.getName()); });
}

Biomol::MMCIFData::Category& Biomol::MMCIFData::addCategory(const std::string_view& name)
{
    auto it = findCategory(name);

    if (it != categories.end())
        return *it;

    categories.emplace_back(name);

    return categories.back();
}
            
void Biomol::MMCIFData::removeCategory(const CategoryIterator& it)
{
    if (it < categories.begin() || it >= categories.end())
        throw Base::RangeError("Biomol::MMCIFData: category iterator out of valid range");

    categories.erase(it);
}

bool Biomol::MMCIFData::removeCategory(const std::string_view& name)
{
    auto it = findCategory(name);

    if (it == categories.end())
        return false;

    categories.erase(it);
    
    return true;
}

void Biomol::MMCIFData::removeCategory(std::size_t index)
{
   if (index >= categories.size())
        throw Base::IndexError("Biomol::MMCIFData: category index out of bounds");

   categories.erase(categories.begin() + index);
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

