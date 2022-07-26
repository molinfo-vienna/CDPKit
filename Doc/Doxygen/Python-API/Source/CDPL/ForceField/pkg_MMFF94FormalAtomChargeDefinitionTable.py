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
class MMFF94FormalAtomChargeDefinitionTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param atom_type 
        # \param ass_mode 
        # \param charge 
        # \param type_list 
        #
        def __init__(self: object, atom_type: str, ass_mode: int, charge: float, type_list: str) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Entry instance this method is called upon.
        #
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Entry) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param self The \e %Entry instance this method is called upon.
        # \param entry The \e %Entry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Entry, entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAtomType(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAssignmentMode(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getFormalCharge(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAtomTypeList(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def __nonzero__(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def __bool__(self: Entry) -> bool: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        atomType = property(getAtomType)

        ##
        # \brief 
        #
        assignmentMode = property(getAssignmentMode)

        ##
        # \brief 
        #
        formalCharge = property(getFormalCharge)

        ##
        # \brief 
        #
        atomTypeList = property(getAtomTypeList)

    ##
    # \brief Initializes the \e %MMFF94FormalAtomChargeDefinitionTable instance.
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94FormalAtomChargeDefinitionTable instance.
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    #
    # Different Python \e %MMFF94FormalAtomChargeDefinitionTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94FormalAtomChargeDefinitionTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94FormalAtomChargeDefinitionTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \param atom_type 
    # \param ass_mode 
    # \param charge 
    # \param type_list 
    #
    def addEntry(self: MMFF94FormalAtomChargeDefinitionTable, atom_type: str, ass_mode: int, charge: float, type_list: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def removeEntry(self: MMFF94FormalAtomChargeDefinitionTable, atom_type: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def getEntry(self: MMFF94FormalAtomChargeDefinitionTable, atom_type: str) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    #
    def clear(self: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: MMFF94FormalAtomChargeDefinitionTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: MMFF94FormalAtomChargeDefinitionTable) -> list: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \param is 
    #
    def load(self: MMFF94FormalAtomChargeDefinitionTable, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    #
    def loadDefaults(self: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94FormalAtomChargeDefinitionTable instance \a table.
    # \param self The \e %MMFF94FormalAtomChargeDefinitionTable instance this method is called upon.
    # \param table The \e %MMFF94FormalAtomChargeDefinitionTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94FormalAtomChargeDefinitionTable, table: MMFF94FormalAtomChargeDefinitionTable) -> MMFF94FormalAtomChargeDefinitionTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94FormalAtomChargeDefinitionTable: pass

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
