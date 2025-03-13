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
class FragmentLibrary(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FragmentLibrary instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %FragmentLibrary instance \a lib.
    # \param lib The \e %FragmentLibrary instance to copy.
    # 
    def __init__(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentLibrary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentLibrary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param lib 
    #
    def addEntries(lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param entry 
    # \return 
    #
    def addEntry(entry: FragmentLibraryEntry) -> bool: pass

    ##
    # \brief 
    # \param hash_code 
    # \return 
    #
    def removeEntry(hash_code: int) -> bool: pass

    ##
    # \brief 
    # \param hash_code 
    # \return 
    #
    def getEntry(hash_code: int) -> FragmentLibraryEntry: pass

    ##
    # \brief 
    # \param hash_code 
    # \return 
    #
    def containsEntry(hash_code: int) -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief 
    # \param is 
    #
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief 
    # \param os 
    #
    def save(os: Base.OStream) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentLibrary instance \a lib.
    # \param lib The \c %FragmentLibrary instance to copy.
    # \return \a self
    # 
    def assign(lib: FragmentLibrary) -> FragmentLibrary: pass

    ##
    # \brief 
    # \param lib 
    #
    @staticmethod
    def set(lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> FragmentLibrary: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
