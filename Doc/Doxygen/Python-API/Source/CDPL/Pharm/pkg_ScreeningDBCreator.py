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
# \brief A class for the creation of optimized pharmacophore screening databases.
# 
class ScreeningDBCreator(Boost.Python.instance):

    ##
    # \brief 
    #
    class Mode(Boost.Python.enum):

        ##
        # \brief CREATE.
        #
        CREATE = 0

        ##
        # \brief UPDATE.
        #
        UPDATE = 1

        ##
        # \brief APPEND.
        #
        APPEND = 2

    ##
    # \brief Initializes the \e %ScreeningDBCreator instance.
    # \param self The \e %ScreeningDBCreator instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # 
    # Different Python \e %ScreeningDBCreator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ScreeningDBCreator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param name 
    # \param mode 
    # \param allow_dup_entries 
    #
    def open(name: str, mode: Mode = CDPL.Pharm.Mode.CREATE, allow_dup_entries: bool = True) -> None: pass

    ##
    # \brief 
    #
    def close() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMode() -> Mode: pass

    ##
    # \brief 
    # \return 
    #
    def allowDuplicateEntries() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    # \return 
    #
    def process(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param db_acc 
    # \param func 
    # \return 
    #
    def merge(db_acc: ScreeningDBAccessor, func: BoolDoubleFunctor) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getNumProcessed() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumRejected() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumDeleted() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumInserted() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getDatabaseName() -> str: pass

    objectID = property(getObjectID)

    mode = property(getMode)

    ##
    # \brief FIXME!
    # \brief 
    #
    allowDuplicates = property(getAllowDuplicates)

    numProcessed = property(getNumProcessed)

    numRejected = property(getNumRejected)

    numDeleted = property(getNumDeleted)

    numInserted = property(getNumInserted)

    databaseName = property(getDatabaseName)
