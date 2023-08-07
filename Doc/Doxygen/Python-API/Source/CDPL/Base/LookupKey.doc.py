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
# \brief An unique lookup key for control-parameter and property values.
# 
# <tt>LookupKey</tt> has a private default constructor and a public copy constructor. The creation of not copy constructed new instances is only possible by the method create(const std::string& name). <tt>LookupKey</tt> instances created by this method are guaranteed to be unique (given that the internal instance counter of type <tt>std::size_t</tt> does not overflow), i.e. the created instance is <em>not a copy</em> of an existing key and does not compare equal to any instance created before or afterwards. <br>
# 
class LookupKey(Boost.Python.instance):

    ##
    # \brief Used to denote an invalid, unused or unspecified key.
    # 
    NONE = LookupKey(id=0, name='NONE')

    ##
    # \brief Initializes a copy of the \e %LookupKey instance \a key.
    # \param key The \e %LookupKey instance to copy.
    # 
    def __init__(key: LookupKey) -> None: pass

    ##
    # \brief Creates a new unique <tt>LookupKey</tt> instance and registers it under the specified name.
    # 
    # <tt>LookupKey</tt> instances created by this method are guaranteed to be unique (given that the internal instance counter of type <tt>std::size_t</tt> does not overflow), i.e. the instance is <em>not a copy</em> of an existing key and does not compare equal to any instance created before or afterwards.
    # 
    # \param name The name of the <tt>LookupKey</tt> instance.
    # 
    # \return A new unique <tt>LookupKey</tt> instance.
    # 
    @staticmethod
    def create(name: str) -> LookupKey: pass

    ##
    # \brief Returns the unique numeric identifier associated with the <tt>LookupKey</tt> instance.
    # 
    # \return The unique numeric identifier of the <tt>LookupKey</tt> instance.
    # 
    def getID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LookupKey instance \a key.
    # \param key The \e %LookupKey instance to copy.
    # \return \a self
    # 
    def assign(key: LookupKey) -> LookupKey: pass

    ##
    # \brief Returns the name of the <tt>LookupKey</tt> instance.
    # 
    # \return The name of the <tt>LookupKey</tt> instance. 
    # 
    # \throw Base.ItemNotFound if the requested name could not be found.
    # 
    def getName() -> str: pass

    ##
    # \brief Sets the name of the <tt>LookupKey</tt> instance.
    # 
    # \param name The new name of the <tt>LookupKey</tt> instance.
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
    # \brief Less than comparison operator.
    # 
    # \param key The other <tt>LookupKey</tt> instance to be compared with.
    # 
    # \return <tt>True</tt> if the numeric identifier of this instance is smaller than the identifier of <em>key</em>, and <tt>False</tt> otherwise.
    # 
    def __lt__(key: LookupKey) -> bool: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param key The other <tt>LookupKey</tt> instance to be compared with.
    # 
    # \return <tt>True</tt> if the numeric identifiers of the keys are equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(key: LookupKey) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # \param key The other <tt>LookupKey</tt> instance to be compared with.
    # 
    # \return <tt>True</tt> if the numeric identifiers of the keys are not equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(key: LookupKey) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LookupKey instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    numericID = property(getID)

    name = property(getName, setName)
