#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Data structure for the storage of preprocessed <em>Macromolecular Crystallographic Information File (mmCIF)</em> data.
# 
# \see [\ref MMCIF] 
# 
# \since 1.2
# 
class MMCIFData(Boost.Python.instance):

    ##
    # \brief A single data item (column) of an <em>mmCIF</em> category, holding an ordered list of string values.
    # 
    class Item(Boost.Python.instance):

        ##
        # \brief Constructs an empty <tt>Item</tt> instance with the data item name <em>name</em>.
        # 
        # \param name The <em>mmCIF</em> data item name (without a category name prefix!).
        # 
        def __init__(name: str) -> None: pass

        ##
        # \brief Initializes a copy of the \c %Item instance \a item.
        # \param item The \c %Item instance to copy.
        # 
        def __init__(item: Item) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Item instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Item instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Item instance \a item.
        # \param item The \c %Item instance to copy.
        # \return \a self
        # 
        def assign(item: Item) -> Item: pass

        ##
        # \brief 
        # \param cat 
        #
        def swap(cat: Item) -> None: pass

        ##
        # \brief Removes all values from the item.
        # 
        def clear() -> None: pass

        ##
        # \brief 
        # \param arg1 
        # \return 
        #
        def getName() -> str: pass

        ##
        # \brief Returns the number of values stored in the item.
        # 
        # \return The value count.
        # 
        def getNumValues() -> int: pass

        ##
        # \brief Returns the value at index <em>index</em>.
        # 
        # \param index The zero-based value index.
        # 
        # \return A reference to the value. 
        # 
        # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumValues()).
        # 
        def getValue(index: int) -> str: pass

        ##
        # \brief Replaces the value at index <em>index</em> by moving <em>value</em>.
        # 
        # \param index The zero-based value index.
        # \param value The new value to move-assign.
        # 
        # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumValues()).
        # 
        def setValue(index: int, value: str) -> None: pass

        ##
        # \brief Appends the value <em>value</em> to the item's value list by moving.
        # 
        # \param value The value to move-append.
        # 
        def addValue(value: str) -> None: pass

        ##
        # \brief Removes the value at index <em>index</em>.
        # 
        # \param index The zero-based value index.
        # 
        # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumValues()).
        # 
        def removeValue(index: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param index 
        # \return 
        #
        def __getitem__(index: int) -> str: pass

        ##
        # \brief 
        # \param index 
        #
        def __delitem__(index: int) -> None: pass

        ##
        # \brief 
        # \param index 
        # \param value 
        #
        def __setitem__(index: int, value: str) -> None: pass

        objectID = property(getObjectID)

        numValues = property(getNumValues)

        name = property(getName)

    ##
    # \brief A single <em>mmCIF</em> data category, holding an ordered list of data items (columns).
    # 
    class Category(Boost.Python.instance):

        ##
        # \brief Constructs an empty <tt>Category</tt> instance with the name <em>name</em>.
        # 
        # \param name The <em>mmCIF</em> category name (without the leading underscore!).
        # 
        def __init__(name: str) -> None: pass

        ##
        # \brief Initializes a copy of the \c %Category instance \a cat.
        # \param cat The \c %Category instance to copy.
        # 
        def __init__(cat: Category) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Category instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Category instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Category instance \a cat.
        # \param cat The \c %Category instance to copy.
        # \return \a self
        # 
        def assign(cat: Category) -> Category: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %MMCIFData instance \a cat.
        # \param cat The \c %MMCIFData instance to copy.
        # \return \a self
        # 
        def assign(cat: MMCIFData) -> MMCIFData: pass

        ##
        # \brief 
        # \param arg1 
        # \return 
        #
        def getName() -> str: pass

        ##
        # \brief Returns the number of items in the category.
        # 
        # \return The item count.
        # 
        def getNumItems() -> int: pass

        ##
        # \brief Returns the number of value rows of the category, i.e. the maximum value count over all items.
        # 
        # \return The category's value-row count.
        # 
        def getNumValueRows() -> int: pass

        ##
        # \brief Removes all items from the category.
        # 
        def clear() -> None: pass

        ##
        # \brief Swaps the contents of this category with those of <em>cat</em>.
        # 
        # \param cat The other category to swap with.
        # 
        def swap(cat: Category) -> None: pass

        ##
        # \brief Returns a mutable reference to the item with name <em>name</em>, or <tt>None</tt> if no matching item exists.
        # 
        # \param name The data item name.
        # 
        # \return A mutable reference to the matching item, or <tt>None</tt>.
        # 
        def findItem(name: str) -> Item: pass

        ##
        # \brief Appends a new (empty) item with name <em>name</em> to the category.
        # 
        # If an item with the given name already exists, no new item is added and a reference to the existing item is returned.
        # 
        # \param name The data item name.
        # 
        # \return A mutable reference to the added (or pre-existing) item.
        # 
        def addItem(name: str) -> Item: pass

        ##
        # \brief Returns a reference to the item with name <em>name</em>.
        # 
        # \param name The data item name.
        # 
        # \return A reference to the matching item. 
        # 
        # \throw Base.ItemNotFound if no matching item exists.
        # 
        def getItem(name: str) -> Item: pass

        ##
        # \brief Returns a reference to the item at index <em>index</em>.
        # 
        # \param index The zero-based item index.
        # 
        # \return A reference to the item. 
        # 
        # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumItems()).
        # 
        def getItem(index: int) -> Item: pass

        ##
        # \brief Removes the item with name <em>name</em>.
        # 
        # \param name The data item name.
        # 
        # \return <tt>True</tt> if a matching item was removed, and <tt>False</tt> if no such item existed.
        # 
        def removeItem(name: str) -> bool: pass

        ##
        # \brief Removes the item at index <em>index</em>.
        # 
        # \param index The zero-based item index.
        # 
        # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumItems()).
        # 
        def removeItem(index: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def __getitem__(name: str) -> Item: pass

        ##
        # \brief 
        # \param index 
        # \return 
        #
        def __getitem__(index: int) -> Item: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def __delitem__(name: str) -> bool: pass

        ##
        # \brief 
        # \param index 
        #
        def __delitem__(index: int) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>name in self</tt>.
        # \param name The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(name: str) -> bool: pass

        ##
        # \brief Returns a string representation of the \c %Category instance.
        # \return The generated string representation.
        # 
        def __str__() -> object: pass

        objectID = property(getObjectID)

        numValueRows = property(getNumValueRows)

        numItems = property(getNumItems)

        name = property(getName)

    ##
    # \brief Constructs an empty <tt>MMCIFData</tt> instance with an empty data-block ID.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMCIFData instance \a data.
    # \param data The \c %MMCIFData instance to copy.
    # 
    def __init__(data: MMCIFData) -> None: pass

    ##
    # \brief Constructs an empty <tt>MMCIFData</tt> instance with the data-block ID <em>id</em>.
    # 
    # \param id The <em>mmCIF</em> data-block ID.
    # 
    def __init__(id: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMCIFData instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMCIFData instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the <em>mmCIF</em> data-block ID.
    # 
    # \return A reference to the data-block ID.
    # 
    def getID() -> str: pass

    ##
    # \brief Sets the <em>mmCIF</em> data-block ID to <em>id</em>.
    # 
    # \param id The new data-block ID.
    # 
    def setID(id: str) -> None: pass

    ##
    # \brief Returns the number of categories in the data record.
    # 
    # \return The category count.
    # 
    def getNumCategories() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMCIFData instance \a data.
    # \param data The \c %MMCIFData instance to copy.
    # \return \a self
    # 
    def assign(data: MMCIFData) -> MMCIFData: pass

    ##
    # \brief Swaps the contents of this data record with those of <em>data</em>.
    # 
    # \param data The other data record to swap with.
    # 
    def swap(data: MMCIFData) -> None: pass

    ##
    # \brief Removes all categories from the data record (without changing the data-block ID).
    # 
    def clear() -> None: pass

    ##
    # \brief Returns a mutable reference to the category with name <em>name</em>, or <tt>None</tt> if no matching category exists.
    # 
    # \param name The <em>mmCIF</em> category name (without the leading underscore!).
    # 
    # \return A mutable reference to the matching category, or <tt>None</tt>.
    # 
    def findCategory(name: str) -> Category: pass

    ##
    # \brief Adds a new (empty) category with name <em>name</em> to the data record.
    # 
    # If a category with the given name already exists, no new category is added and a reference to the existing category is returned.
    # 
    # \param name The <em>mmCIF</em> category name (without the leading underscore!).
    # \param front If <tt>True</tt>, the new category is inserted at the front of the category list. If <tt>False</tt>, it is appended.
    # 
    # \return A mutable reference to the added (or pre-existing) category.
    # 
    def addCategory(name: str, front: bool = False) -> Category: pass

    ##
    # \brief Returns a reference to the category with name <em>name</em>.
    # 
    # \param name The <em>mmCIF</em> category name (without the leading underscore!).
    # 
    # \return A reference to the matching category. 
    # 
    # \throw Base.ItemNotFound if no matching category exists.
    # 
    def getCategory(name: str) -> Category: pass

    ##
    # \brief Returns a reference to the category at index <em>index</em>.
    # 
    # \param index The zero-based category index.
    # 
    # \return A reference to the category. 
    # 
    # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumCategories()).
    # 
    def getCategory(index: int) -> Category: pass

    ##
    # \brief Returns a mutable reference to the last category of the data record.
    # 
    # \return A mutable reference to the last category. 
    # 
    # \throw Base.OperationFailed if the data record is empty.
    # 
    def lastCategory() -> Category: pass

    ##
    # \brief Removes the category with name <em>name</em>.
    # 
    # \param name The <em>mmCIF</em> category name (without the leading underscore).
    # 
    # \return <tt>True</tt> if a matching category was removed, and <tt>False</tt> if no such category existed.
    # 
    def removeCategory(name: str) -> bool: pass

    ##
    # \brief Removes the category at index <em>index</em>.
    # 
    # \param index The zero-based category index.
    # 
    # \throw Base.IndexError if <em>index</em> is not in the range [0, getNumCategories()).
    # 
    def removeCategory(index: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def __getitem__(name: str) -> Category: pass

    ##
    # \brief 
    # \param index 
    # \return 
    #
    def __getitem__(index: int) -> Category: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def __delitem__(name: str) -> bool: pass

    ##
    # \brief 
    # \param index 
    #
    def __delitem__(index: int) -> None: pass

    ##
    # \brief Returns the result of the membership test operation <tt>name in self</tt>.
    # \param name The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(name: str) -> bool: pass

    ##
    # \brief Returns a string representation of the \c %MMCIFData instance.
    # \return The generated string representation.
    # 
    def __str__() -> object: pass

    objectID = property(getObjectID)

    numCategories = property(getNumCategories)

    id = property(getID, setID)
