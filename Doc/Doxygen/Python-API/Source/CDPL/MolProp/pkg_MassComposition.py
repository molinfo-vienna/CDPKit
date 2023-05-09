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
class MassComposition(Boost.Python.instance):

    ##
    # \brief Initializes the \e %MassComposition instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MassComposition instance.
    # \param mass_comp 
    #
    def __init__(mass_comp: MassComposition) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MassComposition instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MassComposition instances \e a and \e b reference different C++ objects. 
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
    def getSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MassComposition instance \a map.
    # \param map The \e %MassComposition instance to copy.
    # \return \a self
    #
    def assign(map: MassComposition) -> MassComposition: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def getValue(key: int) -> float: pass

    ##
    # \brief 
    # \param key 
    # \param def_value 
    # \return 
    #
    def getValue(key: int, def_value: float) -> float: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def removeEntry(key: int) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def setEntry(key: int, value: float) -> None: pass

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
    # \return 
    #
    def getEntries() -> object: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def containsEntry(key: int) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    # \return 
    #
    def insertEntry(key: int, value: float) -> bool: pass

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
    def __getitem__(key: int) -> float: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: int, value: float) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(mass_comp: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(mass_comp: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(mass_comp: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(mass_comp: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(mass_comp: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > mass_comp</tt>.
    # \param mass_comp The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(mass_comp: object) -> bool: pass

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
