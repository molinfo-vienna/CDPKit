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
# \brief A data structure for the storage of imported MMCIF data (see [\ref MMCIF]).
# 
# \since 1.2
# 
class MMCIFData(Boost.Python.instance):

    ##
    # \brief 
    #
    class Item(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Item instance.
        # \param name 
        # 
        def __init__(name: str) -> None: pass

        ##
        # \brief Initializes a copy of the \e %Item instance \a item.
        # \param item The \e %Item instance to copy.
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
        # \brief 
        #
        def clear() -> None: pass

        ##
        # \brief 
        # \param arg1 
        # \return 
        #
        def getName() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getNumValues() -> int: pass

        ##
        # \brief 
        # \param index 
        # \return 
        #
        def getValue(index: int) -> str: pass

        ##
        # \brief 
        # \param index 
        # \param value 
        #
        def setValue(index: int, value: str) -> None: pass

        ##
        # \brief 
        # \param value 
        #
        def addValue(value: str) -> None: pass

        ##
        # \brief 
        # \param index 
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
    # \brief 
    #
    class Category(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Category instance.
        # \param name 
        # 
        def __init__(name: str) -> None: pass

        ##
        # \brief Initializes a copy of the \e %Category instance \a cat.
        # \param cat The \e %Category instance to copy.
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
        # \brief 
        # \return 
        #
        def getNumItems() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getNumValueRows() -> int: pass

        ##
        # \brief 
        #
        def clear() -> None: pass

        ##
        # \brief 
        # \param cat 
        #
        def swap(cat: Category) -> None: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def findItem(name: str) -> Item: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def addItem(name: str) -> Item: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def getItem(name: str) -> Item: pass

        ##
        # \brief 
        # \param index 
        # \return 
        #
        def getItem(index: int) -> Item: pass

        ##
        # \brief 
        # \param name 
        # \return 
        #
        def removeItem(name: str) -> bool: pass

        ##
        # \brief 
        # \param index 
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
        # \brief Returns a string representation of the \e %Category instance.
        # \return The generated string representation.
        # 
        def __str__() -> object: pass

        objectID = property(getObjectID)

        numValueRows = property(getNumValueRows)

        numItems = property(getNumItems)

        name = property(getName)

    ##
    # \brief Initializes the \e %MMCIFData instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %MMCIFData instance \a data.
    # \param data The \e %MMCIFData instance to copy.
    # 
    def __init__(data: MMCIFData) -> None: pass

    ##
    # \brief Initializes the \e %MMCIFData instance.
    # \param id 
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
    # \brief 
    # \return 
    #
    def getID() -> str: pass

    ##
    # \brief 
    # \param id 
    #
    def setID(id: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumCategories() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMCIFData instance \a data.
    # \param data The \c %MMCIFData instance to copy.
    # \return \a self
    # 
    def assign(data: MMCIFData) -> MMCIFData: pass

    ##
    # \brief 
    # \param data 
    #
    def swap(data: MMCIFData) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def findCategory(name: str) -> Category: pass

    ##
    # \brief 
    # \param name 
    # \param front 
    # \return 
    #
    def addCategory(name: str, front: bool = False) -> Category: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def getCategory(name: str) -> Category: pass

    ##
    # \brief 
    # \param index 
    # \return 
    #
    def getCategory(index: int) -> Category: pass

    ##
    # \brief 
    # \return 
    #
    def lastCategory() -> Category: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def removeCategory(name: str) -> bool: pass

    ##
    # \brief 
    # \param index 
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
    # \brief Returns a string representation of the \e %MMCIFData instance.
    # \return The generated string representation.
    # 
    def __str__() -> object: pass

    objectID = property(getObjectID)

    numCategories = property(getNumCategories)

    id = property(getID, setID)
