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
class LookupKey(Boost.Python.instance):

    ##
    # \brief 
    #
    NONE = LookupKey(id=0, name='NONE')

    ##
    # \brief Initializes the \e %LookupKey instance.
    # \param key 
    #
    def __init__(key: LookupKey) -> None: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def create(name: str) -> LookupKey: pass

    ##
    # \brief 
    # \return 
    #
    def getID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LookupKey instance \a key.
    # \param key The \e %LookupKey instance to copy.
    # \return The assignment target \a self.
    #
    def assign(key: LookupKey) -> LookupKey: pass

    ##
    # \brief 
    # \return 
    #
    def getName() -> str: pass

    ##
    # \brief 
    # \param name 
    #
    def setName(name: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %LookupKey instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LookupKey instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < key</tt>.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(key: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == key</tt>.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(key: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != key</tt>.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(key: LookupKey) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LookupKey instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    numericID = property(getNumericID)

    ##
    # \brief 
    #
    name = property(getName, setName)
