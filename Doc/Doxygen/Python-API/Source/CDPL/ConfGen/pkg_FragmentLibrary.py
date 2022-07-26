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
class FragmentLibrary(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FragmentLibrary instance.
    # \param self The \e %FragmentLibrary instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FragmentLibrary instance.
    # \param self The \e %FragmentLibrary instance to initialize.
    # \param lib 
    #
    def __init__(self: object, lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FragmentLibrary instance this method is called upon.
    #
    # Different Python \e %FragmentLibrary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentLibrary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FragmentLibrary) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param lib 
    #
    def addEntries(self: FragmentLibrary, lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param entry 
    # \return 
    #
    def addEntry(self: FragmentLibrary, entry: FragmentLibraryEntry) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param hash_code 
    # \return 
    #
    def removeEntry(self: FragmentLibrary, hash_code: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param hash_code 
    # \return 
    #
    def getEntry(self: FragmentLibrary, hash_code: int) -> FragmentLibraryEntry: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param hash_code 
    # \return 
    #
    def containsEntry(self: FragmentLibrary, hash_code: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    #
    def clear(self: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: FragmentLibrary) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \return 
    #
    def getEntries(self: FragmentLibrary) -> list: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param is 
    #
    def load(self: FragmentLibrary, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    #
    def loadDefaults(self: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param os 
    #
    def save(self: FragmentLibrary, os: CDPL.Base.OStream) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentLibrary instance \a lib.
    # \param self The \e %FragmentLibrary instance this method is called upon.
    # \param lib The \e %FragmentLibrary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FragmentLibrary, lib: FragmentLibrary) -> FragmentLibrary: pass

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

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numEntries = property(getNumEntries)

    ##
    # \brief 
    #
    entries = property(getEntries)
