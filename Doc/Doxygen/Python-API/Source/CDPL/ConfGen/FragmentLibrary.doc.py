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
# \brief A library of pre-generated conformations for rigid molecular fragments, indexed by canonical-fragment hash code.
# 
# Entries are FragmentLibraryEntry instances keyed by the hash code of the associated ConfGen.CanonicalFragment. The library is iterable, supports lookup/insertion/removal, can be serialized to and from a stream, and provides a process-wide default instance via the static set() / get() accessors. A built-in mutex is exposed via getMutex() to allow callers to coordinate concurrent access.
# 
class FragmentLibrary(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>FragmentLibrary</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FragmentLibrary</tt> instance <em>lib</em>.
    # 
    # \param lib The <tt>FragmentLibrary</tt> to copy.
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
    # \brief Adds all entries from <em>lib</em> to this library.
    # 
    # \param lib The source <tt>FragmentLibrary</tt>.
    # 
    def addEntries(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Adds the given entry to the library.
    # 
    # \param entry The entry to add.
    # 
    # \return <tt>True</tt> if the entry was added, and <tt>False</tt> if an entry with the same hash code was already present.
    # 
    def addEntry(entry: FragmentLibraryEntry) -> bool: pass

    ##
    # \brief Removes the entry with the specified hash code.
    # 
    # \param hash_code The hash code of the entry to remove.
    # 
    # \return <tt>True</tt> if the entry was removed, and <tt>False</tt> if no matching entry existed.
    # 
    def removeEntry(hash_code: int) -> bool: pass

    ##
    # \brief Returns the entry with the specified hash code.
    # 
    # \param hash_code The hash code of the queried entry.
    # 
    # \return A reference to the matching entry's smart reference, or to an empty smart reference if no entry with <em>hash_code</em> exists.
    # 
    def getEntry(hash_code: int) -> FragmentLibraryEntry: pass

    ##
    # \brief Tells whether the library contains an entry with the specified hash code.
    # 
    # \param hash_code The hash code of the queried entry.
    # 
    # \return <tt>True</tt> if the entry exists, and <tt>False</tt> otherwise.
    # 
    def containsEntry(hash_code: int) -> bool: pass

    ##
    # \brief Removes all entries from the library.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of entries stored in the library.
    # 
    # \return The number of entries.
    # 
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief Loads the contents of the library from the input stream <em>is</em>.
    # 
    # \param is The input stream to read from.
    # 
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief Loads the default fragment library bundled with CDPKit.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Writes the contents of the library to the output stream <em>os</em>.
    # 
    # \param os The output stream to write to.
    # 
    def save(os: Base.OStream) -> None: pass

    ##
    # \brief Replaces the contents of this library with a copy of the contents of <em>lib</em>.
    # 
    # \param lib The source <tt>FragmentLibrary</tt>.
    # 
    # \return \a self
    # 
    def assign(lib: FragmentLibrary) -> FragmentLibrary: pass

    ##
    # \brief Sets the process-wide default fragment library used by ConfGen routines.
    # 
    # \param lib The new default fragment library.
    # 
    @staticmethod
    def set(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the process-wide default fragment library.
    # 
    # \return The current default fragment library.
    # 
    @staticmethod
    def get(: ) -> FragmentLibrary: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
