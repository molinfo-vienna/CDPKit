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
    def __init__(self: object) -> None: pass

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
    def getObjectID(self: ScreeningDBCreator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \param name 
    # \param mode 
    # \param allow_dup_entries 
    #
    def open(self: ScreeningDBCreator, name: str, mode: Mode = CDPL.Pharm.Mode.CREATE, allow_dup_entries: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    #
    def close(self: ScreeningDBCreator) -> None: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getMode(self: ScreeningDBCreator) -> Mode: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def allowDuplicateEntries(self: ScreeningDBCreator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def process(self: ScreeningDBCreator, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \param db_acc 
    # \param func 
    # \return 
    #
    def merge(self: ScreeningDBCreator, db_acc: ScreeningDBAccessor, func: BoolDoubleFunctor) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getNumProcessed(self: ScreeningDBCreator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getNumRejected(self: ScreeningDBCreator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getNumDeleted(self: ScreeningDBCreator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getNumInserted(self: ScreeningDBCreator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ScreeningDBCreator instance this method is called upon.
    # \return 
    #
    def getDatabaseName(self: ScreeningDBCreator) -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    mode = property(getMode)

    ##
    # \brief FIXME!
    #
    allowDuplicates = property(getAllowDuplicates)

    ##
    # \brief 
    #
    numProcessed = property(getNumProcessed)

    ##
    # \brief 
    #
    numRejected = property(getNumRejected)

    ##
    # \brief 
    #
    numDeleted = property(getNumDeleted)

    ##
    # \brief 
    #
    numInserted = property(getNumInserted)

    ##
    # \brief 
    #
    databaseName = property(getDatabaseName)
