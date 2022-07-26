#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \param self The \e %PropertyContainer instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \return 
    #
    def getNumProperties(self: PropertyContainer) -> int: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \param def_value 
    # \return 
    #
    def getPropertyOrDefault(self: PropertyContainer, key: LookupKey, def_value: Variant) -> Variant: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \return 
    #
    def getPropertyKeys(self: PropertyContainer) -> list: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \return 
    #
    def getPropertyValues(self: PropertyContainer) -> list: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \return 
    #
    def getProperties(self: PropertyContainer) -> list: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %PropertyContainer instance this method is called upon.
    #
    # Different Python \e %PropertyContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PropertyContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: PropertyContainer) -> int: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: PropertyContainer, key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: PropertyContainer, key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: PropertyContainer, key: LookupKey, throw_: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: PropertyContainer, key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    #
    def clearProperties(self: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: PropertyContainer, cntnr: PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: LookupKey) -> Variant: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: PropertyContainer, key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: PropertyContainer, key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: PropertyContainer, key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PropertyContainer instance this method is called upon.
    # \return 
    #
    def __len__(self: PropertyContainer) -> int: pass

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
