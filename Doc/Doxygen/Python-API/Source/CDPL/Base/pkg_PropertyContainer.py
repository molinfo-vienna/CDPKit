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
# \brief 
#
class PropertyContainer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %PropertyContainer instance.
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
    # \brief 
    # \return 
    #
    def getNumProperties() -> int: pass

    ##
    # \brief 
    # \param key 
    # \param def_value 
    # \return 
    #
    def getPropertyOrDefault(key: LookupKey, def_value: Variant) -> Variant: pass

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
    # \brief 
    # \return 
    #
    def getProperties() -> list: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def setProperty(key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def removeProperty(key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(key: LookupKey, throw_: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def isPropertySet(key: LookupKey) -> bool: pass

    ##
    # \brief 
    #
    def clearProperties() -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def addProperties(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def copyProperties(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def swap(cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: LookupKey) -> Variant: pass

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
    def __setitem__(key: LookupKey, value: Variant) -> None: pass

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

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    propertyKeys = property(getPropertyKeys)

    ##
    # \brief 
    #
    propertyValues = property(getPropertyValues)

    ##
    # \brief 
    #
    properties = property(getProperties)

    ##
    # \brief 
    #
    numProperties = property(getNumProperties)
