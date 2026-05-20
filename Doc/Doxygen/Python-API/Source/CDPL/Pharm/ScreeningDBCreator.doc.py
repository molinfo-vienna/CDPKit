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
# \brief Abstract base class for creators that build optimized pharmacophore screening databases.
# 
class ScreeningDBCreator(Boost.Python.instance):

    ##
    # \brief Specifies how an existing database file is treated by open().
    # 
    class Mode(Boost.Python.enum):

        ##
        # \brief Create a new database (replacing any existing file).
        # 
        CREATE = 0

        ##
        # \brief Update an existing database in place.
        # 
        UPDATE = 1

        ##
        # \brief Append to an existing database.
        # 
        APPEND = 2

    ##
    # \brief Initializes the \c %ScreeningDBCreator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ScreeningDBCreator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ScreeningDBCreator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Opens the database identified by <em>name</em> in the specified <em>mode</em>.
    # 
    # \param name The database name (path, URI, etc., interpreted by the concrete subclass).
    # \param mode The open mode (see Mode).
    # \param allow_dup_entries If <tt>True</tt>, duplicate molecule entries are allowed; if <tt>False</tt>, duplicates are rejected.
    # 
    def open(name: str, mode: Mode = CDPL.Pharm.Mode.CREATE, allow_dup_entries: bool = True) -> None: pass

    ##
    # \brief Closes the currently open database.
    # 
    def close() -> None: pass

    ##
    # \brief Returns the mode in which the currently open database was opened.
    # 
    # \return The open mode.
    # 
    def getMode() -> Mode: pass

    ##
    # \brief Tells whether duplicate molecule entries are allowed.
    # 
    # \return <tt>True</tt> if duplicates are allowed, and <tt>False</tt> otherwise.
    # 
    def allowDuplicateEntries() -> bool: pass

    ##
    # \brief Processes <em>molgraph</em> and adds it (or its derived pharmacophores) to the database.
    # 
    # \param molgraph The molecular graph to process.
    # 
    # \return <tt>True</tt> if at least one entry was inserted, and <tt>False</tt> otherwise (e.g. when duplicates are rejected).
    # 
    def process(molgraph: Chem.MolecularGraph) -> bool: pass

    ##
    # \brief Merges the contents of <em>db_acc</em> into the currently open database.
    # 
    # \param db_acc The source database accessor.
    # \param func An optional progress-reporting callback (called repeatedly with a fraction in [0, 1]).
    # 
    # \return <tt>True</tt> if the merge completed successfully, and <tt>False</tt> if it was aborted by the callback.
    # 
    def merge(db_acc: ScreeningDBAccessor, func: BoolDoubleFunctor) -> bool: pass

    ##
    # \brief Returns the number of molecules processed since the database was opened.
    # 
    # \return The processed-molecule count.
    # 
    def getNumProcessed() -> int: pass

    ##
    # \brief Returns the number of molecules that were rejected (e.g. as duplicates) since the database was opened.
    # 
    # \return The rejected-molecule count.
    # 
    def getNumRejected() -> int: pass

    ##
    # \brief Returns the number of entries that were deleted since the database was opened.
    # 
    # \return The deleted-entry count.
    # 
    def getNumDeleted() -> int: pass

    ##
    # \brief Returns the number of entries that were inserted since the database was opened.
    # 
    # \return The inserted-entry count.
    # 
    def getNumInserted() -> int: pass

    ##
    # \brief Returns the name of the currently open database.
    # 
    # \return A reference to the database name.
    # 
    def getDatabaseName() -> str: pass

    objectID = property(getObjectID)

    mode = property(getMode)

    allowDuplicates = property(allowDuplicateEntries)

    numProcessed = property(getNumProcessed)

    numRejected = property(getNumRejected)

    numDeleted = property(getNumDeleted)

    numInserted = property(getNumInserted)

    databaseName = property(getDatabaseName)
