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
class ControlParameterContainer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ControlParameterContainer instance.
    #
    def __init__() -> None: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def setParameter(key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def removeParameter(key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param throw_ 
    # \param local 
    # \return 
    #
    def getParameter(key: LookupKey, throw_: bool = False, local: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param key 
    # \param def_value 
    # \param local 
    # \return 
    #
    def getParameterOrDefault(key: LookupKey, def_value: Variant, local: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param key 
    # \param local 
    # \return 
    #
    def isParameterSet(key: LookupKey, local: bool = False) -> bool: pass

    ##
    # \brief 
    #
    def clearParameters() -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def addParameters(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def copyParameters(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumParameters() -> int: pass

    ##
    # \brief 
    # \param func 
    # \return 
    #
    def registerParameterChangedCallback(func: VoidLookupKeyVariantFunctor) -> int: pass

    ##
    # \brief 
    # \param id 
    #
    def unregisterParameterChangedCallback(id: int) -> None: pass

    ##
    # \brief 
    # \param func 
    # \return 
    #
    def registerParameterRemovedCallback(func: VoidLookupKeyFunctor) -> int: pass

    ##
    # \brief 
    # \param id 
    #
    def unregisterParameterRemovedCallback(id: int) -> None: pass

    ##
    # \brief 
    # \param func 
    # \return 
    #
    def registerParentChangedCallback(func: VoidFunctor) -> int: pass

    ##
    # \brief 
    # \param id 
    #
    def unregisterParentChangedCallback(id: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getParent() -> ControlParameterContainer: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def setParent(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getParameterKeys() -> list: pass

    ##
    # \brief 
    # \return 
    #
    def getParameterValues() -> list: pass

    ##
    # \brief 
    # \return 
    #
    def getParameters() -> list: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ControlParameterContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ControlParameterContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: LookupKey) -> Variant: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __delitem__(self: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>self in arg1</tt>.
    # \param self The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: LookupKey, key: bool) -> bool: pass

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
    parent = property(getParent, setParent)

    ##
    # \brief 
    #
    parameterKeys = property(getParameterKeys)

    ##
    # \brief 
    #
    parameterValues = property(getParameterValues)

    ##
    # \brief 
    #
    parameters = property(getParameters)

    ##
    # \brief 
    #
    numParameters = property(getNumParameters)
