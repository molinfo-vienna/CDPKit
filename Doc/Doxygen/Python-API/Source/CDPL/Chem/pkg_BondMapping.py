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
class BondMapping(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BondMapping instance.
    # \param self The \e %BondMapping instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BondMapping instance.
    # \param self The \e %BondMapping instance to initialize.
    # \param mapping 
    #
    def __init__(self: object, mapping: BondMapping) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BondMapping instance this method is called upon.
    #
    # Different Python \e %BondMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: BondMapping) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def getSize(self: BondMapping) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def isEmpty(self: BondMapping) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    #
    def clear(self: BondMapping) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BondMapping instance \a map.
    # \param self The \e %BondMapping instance this method is called upon.
    # \param map The \e %BondMapping instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BondMapping, map: BondMapping) -> BondMapping: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def getValue(self: BondMapping, key: Bond) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \param def_value 
    # \return 
    #
    def getValue(self: BondMapping, key: Bond, def_value: Bond) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeEntry(self: BondMapping, key: Bond) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setEntry(self: BondMapping, key: Bond, value: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def getKeys(self: BondMapping) -> object: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def getValues(self: BondMapping) -> object: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def getValues(self: BondMapping, key: Bond) -> object: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def getEntries(self: BondMapping) -> object: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def getNumEntries(self: BondMapping, key: Bond) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeEntries(self: BondMapping, key: Bond) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \param value 
    #
    def insertEntry(self: BondMapping, key: Bond, value: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \return 
    #
    def __len__(self: BondMapping) -> int: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: BondMapping, key: Bond) -> Bond: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: BondMapping, key: Bond, value: Bond) -> None: pass

    ##
    # \brief 
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: BondMapping, key: Bond) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %BondMapping instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: BondMapping, key: Bond) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    keys = property(getKeys)

    ##
    # \brief 
    #
    values = property(getValues)

    ##
    # \brief 
    #
    entries = property(getEntries)

    ##
    # \brief 
    #
    size = property(getSize)
