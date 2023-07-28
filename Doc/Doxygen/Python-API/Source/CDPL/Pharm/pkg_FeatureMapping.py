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
# \brief A data type for the storage and lookup of arbitrary feature to feature mappings.
# 
# Features mappings are stored as pairs of references to the mapped Pharm.Feature objects. Mappings do not have to be unique and multiple mappings of a given feature to other features are possible. If a mapping entry for a particular feature does not exist, the methods FeatureMapping.getValue() and FeatureMapping.operator[]() return a <em>None</em> reference to indicate that the lookup of the mapped feature has failed.
# 
class FeatureMapping(Boost.Python.instance):

    ##
    # \brief Creates an empty map.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FeatureMapping instance.
    # \param self The \e %FeatureMapping instance to initialize.
    # \param mapping 
    # 
    def __init__(mapping: FeatureMapping) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FeatureMapping instance this method is called upon.
    # 
    # Different Python \e %FeatureMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the size (number of entries) of the map.
    # 
    # \return The size of the map.
    # 
    def getSize() -> int: pass

    ##
    # \brief Tells whether the map is empty (getSize() == 0).
    # 
    # \return <tt>True</tt> if the map is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Erases all entries.
    # 
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureMapping instance \a map.
    # \param self The \e %FeatureMapping instance this method is called upon.
    # \param map The \e %FeatureMapping instance to copy.
    # \return \a self
    # 
    def assign(map: FeatureMapping) -> FeatureMapping: pass

    ##
    # \brief Returns a reference to the first value associated with the specified key.
    # 
    # If the map contains the specified entry, a reference to the associated value is returned. If the map does not contain the entry and default values are enabled (that is, the template parameter <em>AllowDefValues</em> is <tt>True</tt>), a reference to a default constructed value object is returned. Otherwise, Base.ItemNotFound is thrown to indicate the error.
    # 
    # \param key The key associated with the requested value.
    # 
    # \return A reference to the requested value. 
    # 
    # \throw Base.ItemNotFound if <em>AllowDefValues</em> is <tt>False</tt> and the map does not contain an entry with the specified key.
    # 
    # \see getValue(const Key&) const
    # 
    def getValue(key: Feature) -> Feature: pass

    ##
    # \brief Returns a reference to the first value associated with the specified key, or the value given by the second argument if an entry with the given key does not exist.
    # 
    # If the map contains an entry with the specified key, a reference to the associated value is returned. If the map does not contain the entry, the second argument <em>def_value</em> is returned.
    # 
    # \param key The key associated with the requested value.
    # \param def_value The value which is returned if the specified entry does not exist.
    # 
    # \return A reference to the requested or default value.
    # 
    def getValue(key: Feature, def_value: Feature) -> Feature: pass

    ##
    # \brief Removes the first entry with the specified key from the map.
    # 
    # \param key The key specifying the entry to remove.
    # 
    def removeEntry(key: Feature) -> bool: pass

    ##
    # \brief Replaces all entries with a key equivalent to <em>key</em> with a single copy of the key/value pair (<em>key</em>, <em>value</em>).
    # 
    # If no entries with a key equivalent to the specified key exist, <tt>setEntry(k, v)</tt> is equivalent to <tt>insertEntry(k, v)</tt>.
    # 
    # \param key The key of the entries to replace.
    # \param value The value associated with <em>key</em>.
    # 
    # \return An iterator that points to the entry with a key that is equivalent to the specified key.
    # 
    def setEntry(key: Feature, value: Feature) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getKeys() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getValues() -> object: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def getValues(key: Feature) -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> object: pass

    ##
    # \brief Returns the number of entries with the specified key.
    # 
    # \param key The key of the entries to count.
    # 
    # \return The number of entries with the specified key.
    # 
    def getNumEntries(key: Feature) -> int: pass

    ##
    # \brief Removes all entries with the specified key from the map.
    # 
    # \param key The key specifying the entries to remove.
    # 
    # \return The number of removed entries.
    # 
    def removeEntries(key: Feature) -> int: pass

    ##
    # \brief Inserts a new entry with specified key and value into the map.
    # 
    # \param key The key of the entry to insert.
    # \param value The value associated with <em>key</em>
    # 
    # \return An iterator pointing to the inserted entry.
    # 
    def insertEntry(key: Feature, value: Feature) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Feature) -> Feature: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Feature, value: Feature) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Feature) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FeatureMapping instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Feature) -> int: pass

    objectID = property(getObjectID)

    keys = property(getKeys)

    values = property(getValues)

    entries = property(getEntries)

    size = property(getSize)
