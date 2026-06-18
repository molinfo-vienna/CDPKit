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
 * \brief Definition of class CDPL::Biomol::MMCIFData.
 */

#ifndef CDPL_BIOMOL_MMCIFDATA_HPP
#define CDPL_BIOMOL_MMCIFDATA_HPP

#include <cstddef>
#include <string>
#include <memory>
#include <iosfwd>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Biomol
    {

        /**
         * \brief Data structure for the storage of imported MMCIF data (see [\ref MMCIF]).
         * \since 1.2
         */
        class CDPL_BIOMOL_API MMCIFData
        {

          public:

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMCIFData instances.
             */
            typedef std::shared_ptr<MMCIFData> SharedPointer;

            /**
             * \brief A single data item (column) of an \e mmCIF category, holding an ordered list of string values.
             */
            class CDPL_BIOMOL_API Item
            {

                typedef std::vector<std::string> ValueList;

              public:
                /**
                 * \brief A constant iterator over the value list of the item.
                 */
                typedef ValueList::const_iterator ConstValueIterator;
    
                /**
                 * \brief A mutable iterator over the value list of the item.
                 */
                typedef ValueList::iterator       ValueIterator;

                /**
                 * \brief Constructs an empty \c %Item with the data-item name \a name.
                 * \param name The fully-qualified \e mmCIF data-item name (including the \c _ prefix).
                 */
                Item(const std::string& name):
                    name(name) {}

                /**
                 * \brief Returns the fully-qualified \e mmCIF data-item name.
                 * \return A \c const reference to the data-item name.
                 */
                const std::string& getName() const;

                /**
                 * \brief Returns the number of values stored in the item.
                 * \return The value count.
                 */
                std::size_t getNumValues() const;

                /**
                 * \brief Removes all values from the item.
                 */
                void clear();

                /**
                 * \brief Returns the value at the zero-based index \a index.
                 * \param index The zero-based value index.
                 * \return A \c const reference to the value.
                 * \throw Base::IndexError if the number of values is zero or \a index is not in the range [0, getNumValues() - 1].
                 */
                const std::string& getValue(std::size_t index) const;

                /**
                 * \brief Replaces the value at the zero-based index \a index by \a value.
                 * \param index The zero-based value index.
                 * \param value The new value.
                 * \throw Base::IndexError if the number of values is zero or \a index is not in the range [0, getNumValues() - 1].
                 */
                void setValue(std::size_t index, const std::string& value);

                /**
                 * \brief Replaces the value at the zero-based index \a index by moving \a value.
                 * \param index The zero-based value index.
                 * \param value The new value to move-assign.
                 * \throw Base::IndexError if the number of values is zero or \a index is not in the range [0, getNumValues() - 1].
                 */
                void setValue(std::size_t index, std::string&& value);

                /**
                 * \brief Appends the value \a value to the item's value list.
                 * \param value The value to append.
                 */
                void addValue(const std::string& value);

                /**
                 * \brief Appends the value \a value to the item's value list by moving.
                 * \param value The value to move-append.
                 */
                void addValue(std::string&& value);

                /**
                 * \brief Removes the value pointed to by the iterator \a it.
                 * \param it An iterator pointing to the value to remove.
                 * \return An iterator pointing to the value immediately following the removed one.
                 */
                ValueIterator removeValue(const ValueIterator& it);

                /**
                 * \brief Removes the value at the zero-based index \a index.
                 * \param index The zero-based value index.
                 * \throw Base::IndexError if the number of values is zero or \a index is not in the range [0, getNumValues() - 1].
                 */
                void removeValue(std::size_t index);

                /**
                 * \brief Swaps the contents of this item with those of \a item.
                 * \param item The other item to swap with.
                 */
                void swap(Item& item);

                /**
                 * \brief Returns a constant iterator pointing to the beginning of the value list.
                 * \return A constant iterator to the first value.
                 */
                ConstValueIterator getValuesBegin() const;

                /**
                 * \brief Returns a mutable iterator pointing to the beginning of the value list.
                 * \return A mutable iterator to the first value.
                 */
                ValueIterator getValuesBegin();

                /**
                 * \brief Returns a constant iterator pointing one past the last value.
                 * \return A constant iterator to the end of the value list.
                 */
                ConstValueIterator getValuesEnd() const;

                /**
                 * \brief Returns a mutable iterator pointing one past the last value.
                 * \return A mutable iterator to the end of the value list.
                 */
                ValueIterator getValuesEnd();

                /**
                 * \brief Returns a constant iterator pointing to the beginning of the value list (alias of getValuesBegin()).
                 * \return A constant iterator to the first value.
                 */
                ConstValueIterator begin() const;

                /**
                 * \brief Returns a mutable iterator pointing to the beginning of the value list (alias of getValuesBegin()).
                 * \return A mutable iterator to the first value.
                 */
                ValueIterator begin();

                /**
                 * \brief Returns a constant iterator pointing one past the last value (alias of getValuesEnd()).
                 * \return A constant iterator to the end of the value list.
                 */
                ConstValueIterator end() const;

                /**
                 * \brief Returns a mutable iterator pointing one past the last value (alias of getValuesEnd()).
                 * \return A mutable iterator to the end of the value list.
                 */
                ValueIterator end();

              private:
                std::string name;
                ValueList   values;
            };

            /**
             * \brief A single \e mmCIF data category, holding an ordered list of data items (columns).
             */
            class CDPL_BIOMOL_API Category
            {

                typedef boost::ptr_vector<Item> ItemList;

              public:
                /**
                 * \brief A constant iterator over the items of the category.
                 */
                typedef ItemList::const_iterator ConstItemIterator;

                /**
                 * \brief A mutable iterator over the items of the category.
                 */
                typedef ItemList::iterator ItemIterator;

                /**
                 * \brief Constructs an empty \c %Category with the name \a name.
                 * \param name The \e mmCIF category name (without the leading underscore).
                 */
                Category(const std::string& name):
                  name(name) {}

                /**
                 * \brief Returns the \e mmCIF category name.
                 * \return A \c const reference to the category name.
                 */
                const std::string& getName() const;

                /**
                 * \brief Removes all items from the category.
                 */
                void clear();

                /**
                 * \brief Returns the number of items in the category.
                 * \return The item count.
                 */
                std::size_t getNumItems() const;

                /**
                 * \brief Returns a mutable reference to the item at the zero-based index \a index.
                 * \param index The zero-based item index.
                 * \return A mutable reference to the item.
                 * \throw Base::IndexError if the number of items is zero or \a index is not in the range [0, getNumItems() - 1].
                 */
                Item& getItem(std::size_t index);

                /**
                 * \brief Returns a \c const reference to the item at the zero-based index \a index.
                 * \param index The zero-based item index.
                 * \return A \c const reference to the item.
                 * \throw Base::IndexError if the number of items is zero or \a index is not in the range [0, getNumItems() - 1].
                 */
                const Item& getItem(std::size_t index) const;

                /**
                 * \brief Returns a mutable reference to the item with name \a name.
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return A mutable reference to the matching item.
                 * \throw Base::ItemNotFound if no matching item exists.
                 */
                Item& getItem(const std::string& name);

                /**
                 * \brief Returns a \c const reference to the item with name \a name.
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return A \c const reference to the matching item.
                 * \throw Base::ItemNotFound if no matching item exists.
                 */
                const Item& getItem(const std::string& name) const;

                /**
                 * \brief Returns a pointer to the item with name \a name, or \c nullptr if no matching item exists.
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return A \c const pointer to the matching item, or \c nullptr.
                 */
                const Item* findItem(const std::string& name) const;

                /**
                 * \brief Returns a mutable pointer to the item with name \a name, or \c nullptr if no matching item exists.
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return A mutable pointer to the matching item, or \c nullptr.
                 */
                Item* findItem(const std::string& name);

                /**
                 * \brief Appends a new (empty) item with name \a name to the category.
                 *
                 * If an item with the given name already exists, no new item is added and a reference to the existing
                 * item is returned.
                 *
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return A mutable reference to the added (or pre-existing) item.
                 */
                Item& addItem(const std::string& name);

                /**
                 * \brief Removes the item pointed to by the iterator \a it.
                 * \param it An iterator pointing to the item to remove.
                 * \return An iterator pointing to the item immediately following the removed one.
                 */
                ItemIterator removeItem(const ItemIterator& it);

                /**
                 * \brief Removes the item with name \a name.
                 * \param name The fully-qualified data-item name (including the \c _ prefix).
                 * \return \c true if a matching item was removed, and \c false if no such item existed.
                 */
                bool removeItem(const std::string& name);

                /**
                 * \brief Removes the item at the zero-based index \a index.
                 * \param index The zero-based item index.
                 * \throw Base::IndexError if the number of items is zero or \a index is not in the range [0, getNumItems() - 1].
                 */
                void removeItem(std::size_t index);

                /**
                 * \brief Swaps the contents of this category with those of \a cat.
                 * \param cat The other category to swap with.
                 */
                void swap(Category& cat);

                /**
                 * \brief Returns a constant iterator pointing to the beginning of the item list.
                 * \return A constant iterator to the first item.
                 */
                ConstItemIterator getItemsBegin() const;

                /**
                 * \brief Returns a mutable iterator pointing to the beginning of the item list.
                 * \return A mutable iterator to the first item.
                 */
                ItemIterator getItemsBegin();

                /**
                 * \brief Returns a constant iterator pointing one past the last item.
                 * \return A constant iterator to the end of the item list.
                 */
                ConstItemIterator getItemsEnd() const;

                /**
                 * \brief Returns a mutable iterator pointing one past the last item.
                 * \return A mutable iterator to the end of the item list.
                 */
                ItemIterator getItemsEnd();

                /**
                 * \brief Returns a constant iterator pointing to the beginning of the item list (alias of getItemsBegin()).
                 * \return A constant iterator to the first item.
                 */
                ConstItemIterator begin() const;

                /**
                 * \brief Returns a mutable iterator pointing to the beginning of the item list (alias of getItemsBegin()).
                 * \return A mutable iterator to the first item.
                 */
                ItemIterator begin();

                /**
                 * \brief Returns a constant iterator pointing one past the last item (alias of getItemsEnd()).
                 * \return A constant iterator to the end of the item list.
                 */
                ConstItemIterator end() const;

                /**
                 * \brief Returns a mutable iterator pointing one past the last item (alias of getItemsEnd()).
                 * \return A mutable iterator to the end of the item list.
                 */
                ItemIterator end();

                /**
                 * \brief Returns the number of value rows of the category, i.e. the maximum value count over all items.
                 * \return The category's value-row count.
                 */
                std::size_t getNumValueRows() const;

              private:
                ItemIterator getItemIter(const std::string& name);

                ConstItemIterator getItemIter(const std::string& name) const;

                std::string name;
                ItemList    items;
            };

          private:
            typedef boost::ptr_deque<Category> CategoryList;
            
          public:
            /**
             * \brief A constant iterator over the categories of the data record.
             */
            typedef CategoryList::const_iterator ConstCategoryIterator;

            /**
             * \brief A mutable iterator over the categories of the data record.
             */
            typedef CategoryList::iterator       CategoryIterator;

            /**
             * \brief Constructs an empty \c %MMCIFData instance with an empty data-block ID.
             */
            MMCIFData() = default;

            /**
             * \brief Constructs an empty \c %MMCIFData instance with the data-block ID \a id.
             * \param id The \e mmCIF data-block ID.
             */
            MMCIFData(const std::string& id);

            /**
             * \brief Sets the \e mmCIF data-block ID to \a id.
             * \param id The new data-block ID.
             */
            void setID(const std::string& id);

            /**
             * \brief Returns the \e mmCIF data-block ID.
             * \return A \c const reference to the data-block ID.
             */
            const std::string& getID() const;

            /**
             * \brief Removes all categories from the data record (without changing the data-block ID).
             */
            void clear();

            /**
             * \brief Returns the number of categories in the data record.
             * \return The category count.
             */
            std::size_t getNumCategories() const;

            /**
             * \brief Returns a mutable reference to the category at the zero-based index \a index.
             * \param index The zero-based category index.
             * \return A mutable reference to the category.
             * \throw Base::IndexError if the number of categories is zero or \a index is not in the range [0, getNumCategories() - 1].
             */
            Category& getCategory(std::size_t index);

            /**
             * \brief Returns a \c const reference to the category at the zero-based index \a index.
             * \param index The zero-based category index.
             * \return A \c const reference to the category.
             * \throw Base::IndexError if the number of categories is zero or \a index is not in the range [0, getNumCategories() - 1].
             */
            const Category& getCategory(std::size_t index) const;

            /**
             * \brief Returns a mutable reference to the category with name \a name.
             * \param name The \e mmCIF category name (without the leading underscore).
             * \return A mutable reference to the matching category.
             * \throw Base::ItemNotFound if no matching category exists.
             */
            Category& getCategory(const std::string& name);

            /**
             * \brief Returns a \c const reference to the category with name \a name.
             * \param name The \e mmCIF category name (without the leading underscore).
             * \return A \c const reference to the matching category.
             * \throw Base::ItemNotFound if no matching category exists.
             */
            const Category& getCategory(const std::string& name) const;

            /**
             * \brief Returns a pointer to the category with name \a name, or \c nullptr if no matching category exists.
             * \param name The \e mmCIF category name (without the leading underscore).
             * \return A \c const pointer to the matching category, or \c nullptr.
             */
            const Category* findCategory(const std::string& name) const;

            /**
             * \brief Returns a mutable pointer to the category with name \a name, or \c nullptr if no matching category exists.
             * \param name The \e mmCIF category name (without the leading underscore).
             * \return A mutable pointer to the matching category, or \c nullptr.
             */
            Category* findCategory(const std::string& name);

            /**
             * \brief Returns a \c const reference to the last category of the data record.
             * \return A \c const reference to the last category.
             * \throw Base::OperationFailed if the data record is empty.
             */
            const Category& lastCategory() const;

            /**
             * \brief Returns a mutable reference to the last category of the data record.
             * \return A mutable reference to the last category.
             * \throw Base::OperationFailed if the data record is empty.
             */
            Category& lastCategory();

            /**
             * \brief Adds a new (empty) category with name \a name to the data record.
             *
             * If a category with the given name already exists, no new category is added and a reference to the existing
             * category is returned.
             *
             * \param name The \e mmCIF category name (without the leading underscore).
             * \param front If \c true, the new category is inserted at the front of the category list. If \c false, it is appended.
             * \return A mutable reference to the added (or pre-existing) category.
             */
            Category& addCategory(const std::string& name, bool front = false);

            /**
             * \brief Removes the category pointed to by the iterator \a it.
             * \param it An iterator pointing to the category to remove.
             * \return An iterator pointing to the category immediately following the removed one.
             */
            CategoryIterator removeCategory(const CategoryIterator& it);

            /**
             * \brief Removes the category with name \a name.
             * \param name The \e mmCIF category name (without the leading underscore).
             * \return \c true if a matching category was removed, and \c false if no such category existed.
             */
            bool removeCategory(const std::string& name);

            /**
             * \brief Removes the category at the zero-based index \a index.
             * \param index The zero-based category index.
             * \throw Base::IndexError if the number of categories is zero or \a index is not in the range [0, getNumCategories() - 1].
             */
            void removeCategory(std::size_t index);

            /**
             * \brief Swaps the contents of this data record with those of \a data.
             * \param data The other data record to swap with.
             */
            void swap(MMCIFData& data);

            /**
             * \brief Returns a constant iterator pointing to the beginning of the category list.
             * \return A constant iterator to the first category.
             */
            ConstCategoryIterator getCategoriesBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the category list.
             * \return A mutable iterator to the first category.
             */
            CategoryIterator getCategoriesBegin();

            /**
             * \brief Returns a constant iterator pointing one past the last category.
             * \return A constant iterator to the end of the category list.
             */
            ConstCategoryIterator getCategoriesEnd() const;

            /**
             * \brief Returns a mutable iterator pointing one past the last category.
             * \return A mutable iterator to the end of the category list.
             */
            CategoryIterator getCategoriesEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the category list (alias of getCategoriesBegin()).
             * \return A constant iterator to the first category.
             */
            ConstCategoryIterator begin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the category list (alias of getCategoriesBegin()).
             * \return A mutable iterator to the first category.
             */
            CategoryIterator begin();

            /**
             * \brief Returns a constant iterator pointing one past the last category (alias of getCategoriesEnd()).
             * \return A constant iterator to the end of the category list.
             */
            ConstCategoryIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing one past the last category (alias of getCategoriesEnd()).
             * \return A mutable iterator to the end of the category list.
             */
            CategoryIterator end();

          private:
            CategoryIterator getCategoryIter(const std::string& name);

            ConstCategoryIterator getCategoryIter(const std::string& name) const;
            
            std::string  id;
            CategoryList categories;
        };

        /**
         * \brief Writes the \e mmCIF data record \a data in textual \e mmCIF format to the output stream \a os.
         * \param os The output stream to write to.
         * \param data The \e mmCIF data record to write.
         * \return A reference to \a os.
         * \since 1.2
         */
        CDPL_BIOMOL_API std::ostream& operator<<(std::ostream& os, const MMCIFData& data);

        /**
         * \brief Writes the \e mmCIF category \a cat in textual \e mmCIF format to the output stream \a os.
         * \param os The output stream to write to.
         * \param cat The \e mmCIF category to write.
         * \return A reference to \a os.
         * \since 1.2
         */
        CDPL_BIOMOL_API std::ostream& operator<<(std::ostream& os, const MMCIFData::Category& cat);
        
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATA_HPP
