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

Biomol::MMCIFData::Category& Biomol::MMCIFData::addCategory(const std::string& name)
{
    auto it = getCategoryIter(name);

    if (it != categories.end())
        return *it;

    categories.emplace_back(name);

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
    auto it = getItemIter(name);

    if (it != items.end())
        return *it;

    items.emplace_back(name);

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
    
    std::size_t min_val_cnt = std::numeric_limits<std::size_t>::max();
    
    for (auto& item : items)
        min_val_cnt = std::min(min_val_cnt, item.getNumValues());

    return min_val_cnt;
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

void Biomol::MMCIFData::Item::addValue(const std::string& value)
{
    values.push_back(value);
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
