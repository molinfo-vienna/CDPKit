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
    # \param self The \e %ControlParameterContainer instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setParameter(self: ControlParameterContainer, key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeParameter(self: ControlParameterContainer, key: LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \param local 
    # \return 
    #
    def getParameter(self: ControlParameterContainer, key: LookupKey, throw_: bool = False, local: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \param def_value 
    # \param local 
    # \return 
    #
    def getParameterOrDefault(self: ControlParameterContainer, key: LookupKey, def_value: Variant, local: bool = False) -> Variant: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \param local 
    # \return 
    #
    def isParameterSet(self: ControlParameterContainer, key: LookupKey, local: bool = False) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    #
    def clearParameters(self: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param cntnr 
    #
    def addParameters(self: ControlParameterContainer, cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param cntnr 
    #
    def copyParameters(self: ControlParameterContainer, cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def getNumParameters(self: ControlParameterContainer) -> int: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param func 
    # \return 
    #
    def registerParameterChangedCallback(self: ControlParameterContainer, func: VoidLookupKeyVariantFunctor) -> int: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param id 
    #
    def unregisterParameterChangedCallback(self: ControlParameterContainer, id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param func 
    # \return 
    #
    def registerParameterRemovedCallback(self: ControlParameterContainer, func: VoidLookupKeyFunctor) -> int: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param id 
    #
    def unregisterParameterRemovedCallback(self: ControlParameterContainer, id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param func 
    # \return 
    #
    def registerParentChangedCallback(self: ControlParameterContainer, func: VoidFunctor) -> int: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param id 
    #
    def unregisterParentChangedCallback(self: ControlParameterContainer, id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def getParent(self: ControlParameterContainer) -> ControlParameterContainer: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param cntnr 
    #
    def setParent(self: ControlParameterContainer, cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def getParameterKeys(self: ControlParameterContainer) -> list: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def getParameterValues(self: ControlParameterContainer) -> list: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def getParameters(self: ControlParameterContainer) -> list: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    #
    # Different Python \e %ControlParameterContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ControlParameterContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ControlParameterContainer) -> int: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: ControlParameterContainer, key: LookupKey) -> Variant: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: ControlParameterContainer, key: LookupKey, value: Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \param arg1 
    # \return 
    #
    def __delitem__(arg1: ControlParameterContainer, self: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>self in arg1</tt>.
    # \param arg1 The \e %ControlParameterContainer instance this method is called upon.
    # \param self The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(arg1: ControlParameterContainer, self: LookupKey, key: bool) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ControlParameterContainer instance this method is called upon.
    # \return 
    #
    def __len__(self: ControlParameterContainer) -> int: pass

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
