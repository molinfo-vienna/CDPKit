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
# \brief A class providing methods for the storage and lookup of object properties.
# 
# The purpose of <tt>PropertyContainer</tt> is to provide a common facility for the storage and lookup of dynamic object properties to subclasses and their clients.
# 
# <tt>PropertyContainer</tt> stores the properties in a map that associates unique property keys of type Base.LookupKey with corresponding property values of type Base.Any. Iterators pointing to the beginning and end of the property key/value pairs (see PropertyContainer.PropertyEntry) can be retrieved by the methods getPropertiesBegin() and getPropertiesEnd(), respectively. The number of currently stored property value entries is accessible via the method getNumProperties().
# 
# For the explicit assignment of property values the method setProperty() is provided which expects the key of the property as its first and the value to assign as the second argument. Whether the value of a particular property has been set can be tested by the method isPropertySet(). For the erasure of property values the methods removeProperty() and clearProperties() are provided. The first method clears the value of a single property while the latter method removes all assigned property values.
# 
# To access the value of a property, two types of getProperty() methods are available that both expect the key of the property as the first argument. The templated versions return the stored property value (or the specified default if not available) as a reference to an object of the specified template argument type. The non-template method returns the requested property value indirectly as a reference to the Base.Any instance storing the actual value. If the requested property value does not exist, an additional argument decides whether to throw an exception or to return an empty Base.Any instance.
# 
class PropertyContainer(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>PropertyContainer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %PropertyContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PropertyContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the number of property entries.
    # 
    # \return The number of property entries.
    # 
    def getNumProperties() -> int: pass

    ##
    # \brief 
    # \param key 
    # \param def_value 
    # \return 
    #
    def getPropertyOrDefault(key: LookupKey, def_value: Any) -> Any: pass

    ##
    # \brief 
    # \return 
    #
    def getPropertyKeys() -> list: pass

    ##
    # \brief 
    # \return 
    #
    def getPropertyValues() -> list: pass

    ##
    # \brief Returns a reference to itself.
    # 
    # \return \a self
    # 
    def getProperties() -> list: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def setProperty(key: LookupKey, value: Any) -> None: pass

    ##
    # \brief Clears the value of the property specified by <em>key</em>.
    # 
    # \param key The key of the property value to erase.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was erased, and <tt>False</tt> otherwise.
    # 
    def removeProperty(key: LookupKey) -> bool: pass

    ##
    # \brief Returns the value of the property specified by <em>key</em>.
    # 
    # If an entry for the specified property exists, the stored value will be returned. Otherwise an empty Base.Any object gets returned if <em>_throw</em> is <tt>False</tt>, and a Base.ItemNotFound exception will be thrown if <em>_throw</em> is <tt>True</tt>.
    # 
    # \param key The key of the property value to return.
    # \param throw_ Specifies whether to throw a Base.ItemNotFound exception or to return an empty Base.Any object if the requested property value does not exist.
    # 
    # \return The stored property value or and empty Base.Any object. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested property value does not exist and <em>throw_</em> is <tt>True</tt>.
    # 
    def getProperty(key: LookupKey, throw_: bool = False) -> Any: pass

    ##
    # \brief Tells whether or not a value has been assigned to the property specified by <em>key</em>.
    # 
    # \param key The key of the property.
    # 
    # \return <tt>True</tt> if a value has been assigned to the specified property, and <tt>False</tt> otherwise.
    # 
    def isPropertySet(key: LookupKey) -> bool: pass

    ##
    # \brief Clears all property values.
    # 
    def clearProperties() -> None: pass

    ##
    # \brief Adds the property value entries in the <tt>PropertyContainer</tt> instance <em>cntnr</em>.
    # 
    # Any property values which have no corresponding assigned value in <em>cntnr</em> are left unchanged. Otherwise the value of the local property gets overwritten by the value stored in <em>cntnr</em>.
    # 
    # \param cntnr The <tt>PropertyContainer</tt> instance containing the property value entries to add.
    # 
    def addProperties(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief Replaces the current set of properties by a copy of the entries in <em>cntnr</em>.
    # 
    # \param cntnr The <tt>PropertyContainer</tt> instance containing the property value entries to add.
    # 
    def copyProperties(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief Exchanges the properties of this container with the properties of the container <em>cntnr</em>.
    # 
    # \param cntnr The container to exchange the properties with.
    # 
    def swap(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: LookupKey) -> Any: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: LookupKey, value: Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    propertyKeys = property(getPropertyKeys)

    propertyValues = property(getPropertyValues)

    properties = property(getProperties)

    numProperties = property(getNumProperties)
