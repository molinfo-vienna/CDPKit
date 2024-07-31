/* 
 * MMCIFData.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Biomol::MMCIFData.
 */

#ifndef CDPL_BIOMOL_MMCIFDATA_HPP
#define CDPL_BIOMOL_MMCIFDATA_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief A data structure for the storage of imported MMCIF data (see [\ref MMCIF]).
         * \since 1.2
         */
        class CDPL_BIOMOL_API MMCIFData
        {

          public:
            typedef std::shared_ptr<MMCIFData> SharedPointer;

            class CDPL_BIOMOL_API Item
            {

                typedef std::vector<std::string> ValueList;

              public:
                typedef ValueList::const_iterator ConstValueIterator;
                typedef ValueList::iterator       ValueIterator;

                Item(const std::string& name):
                    name(name) {}

                const std::string& getName() const;

                std::size_t getNumValues() const;

                void clear();

                const std::string& getValue(std::size_t index) const;

                void setValue(std::size_t index, const std::string& value);

                void addValue(const std::string& value);

                ValueIterator removeValue(const ValueIterator& it);

                void removeValue(std::size_t index);

                void swap(Item& item);

                ConstValueIterator getValuesBegin() const;

                ValueIterator getValuesBegin();

                ConstValueIterator getValuesEnd() const;

                ValueIterator getValuesEnd();

                ConstValueIterator begin() const;

                ValueIterator begin();

                ConstValueIterator end() const;

                ValueIterator end();
                  
              private:
                std::string name;
                ValueList   values;
            };

            class CDPL_BIOMOL_API Category
            {

                typedef std::vector<Item> ItemList;

              public:
                typedef ItemList::const_iterator ConstItemIterator;
                typedef ItemList::iterator       ItemIterator;

                Category(const std::string& name):
                  name(name), numRows(0) {}

                const std::string& getName() const;

                void clear();

                std::size_t getNumItems() const;

                Item& getItem(std::size_t index);

                const Item& getItem(std::size_t index) const;

                Item& getItem(const std::string& name);

                const Item& getItem(const std::string& name) const;

                const Item* findItem(const std::string& name) const;

                Item* findItem(const std::string& name);

                Item& addItem(const std::string& name);

                ItemIterator removeItem(const ItemIterator& it);

                bool removeItem(const std::string& name);

                void removeItem(std::size_t index);

                void swap(Category& cat);

                ConstItemIterator getItemsBegin() const;

                ItemIterator getItemsBegin();

                ConstItemIterator getItemsEnd() const;

                ItemIterator getItemsEnd();

                ConstItemIterator begin() const;

                ItemIterator begin();

                ConstItemIterator end() const;

                ItemIterator end();

                std::size_t getNumValueRows() const;

              private:
                ItemIterator getItemIter(const std::string& name);

                ConstItemIterator getItemIter(const std::string& name) const;

                std::string name;
                ItemList    items;
                  std::size_t numRows;
            };

          private:
            typedef std::vector<Category> CategoryList;
            
          public:
            typedef CategoryList::const_iterator ConstCategoryIterator;
            typedef CategoryList::iterator       CategoryIterator;

            MMCIFData() = default;
            
            MMCIFData(const std::string& id);

            void setID(const std::string& id);
            
            const std::string& getID() const;
            
            void clear();

            std::size_t getNumCategories() const;
     
            Category& getCategory(std::size_t index);
            
            const Category& getCategory(std::size_t index) const;

            Category& getCategory(const std::string& name);
            
            const Category& getCategory(const std::string& name) const;

            const Category* findCategory(const std::string& name) const;

            Category* findCategory(const std::string& name);
            
            Category& addCategory(const std::string& name);

            CategoryIterator removeCategory(const CategoryIterator& it);

            bool removeCategory(const std::string& name);

            void removeCategory(std::size_t index);

            void swap(MMCIFData& data);

            ConstCategoryIterator getCategoriesBegin() const;

            CategoryIterator getCategoriesBegin();

            ConstCategoryIterator getCategoriesEnd() const;

            CategoryIterator getCategoriesEnd();

            ConstCategoryIterator begin() const;

            CategoryIterator begin();

            ConstCategoryIterator end() const;

            CategoryIterator end();

          private:
            CategoryIterator getCategoryIter(const std::string& name);

            ConstCategoryIterator getCategoryIter(const std::string& name) const;
            
            std::string  id;
            CategoryList categories;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATA_HPP
