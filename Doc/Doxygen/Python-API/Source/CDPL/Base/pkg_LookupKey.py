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
    # \param self The \e %LookupKey instance to initialize.
    # \param key 
    #
    def __init__(self: object, key: LookupKey) -> None: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    @staticmethod
    def create(name: str) -> LookupKey: pass

    ##
    # \brief 
    # \param self The \e %LookupKey instance this method is called upon.
    # \return 
    #
    def getID(self: LookupKey) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LookupKey instance \a key.
    # \param self The \e %LookupKey instance this method is called upon.
    # \param key The \e %LookupKey instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LookupKey, key: LookupKey) -> LookupKey: pass

    ##
    # \brief 
    # \param self The \e %LookupKey instance this method is called upon.
    # \return 
    #
    def getName(self: LookupKey) -> str: pass

    ##
    # \brief 
    # \param self The \e %LookupKey instance this method is called upon.
    # \param name 
    #
    def setName(self: LookupKey, name: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LookupKey instance this method is called upon.
    #
    # Different Python \e %LookupKey instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LookupKey instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: LookupKey) -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < key</tt>.
    # \param self The \e %LookupKey instance this method is called upon.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(self: LookupKey, key: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == key</tt>.
    # \param self The \e %LookupKey instance this method is called upon.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: LookupKey, key: LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != key</tt>.
    # \param self The \e %LookupKey instance this method is called upon.
    # \param key The \e %LookupKey instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: LookupKey, key: LookupKey) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LookupKey instance.
    # \param self The \e %LookupKey instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: LookupKey) -> str: pass

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
