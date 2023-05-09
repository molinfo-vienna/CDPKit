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
class MMFF94FormalAtomChargeDefinitionTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        #
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param entry 
        #
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param atom_type 
        # \param ass_mode 
        # \param charge 
        # \param type_list 
        #
        def __init__(atom_type: str, ass_mode: int, charge: float, type_list: str) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        #
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # \return \a self
        #
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomType() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getAssignmentMode() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getFormalCharge() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomTypeList() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def __nonzero__() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __bool__() -> bool: pass

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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94FormalAtomChargeDefinitionTable instance.
    # \param table 
    #
    def __init__(table: MMFF94FormalAtomChargeDefinitionTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MMFF94FormalAtomChargeDefinitionTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94FormalAtomChargeDefinitionTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atom_type 
    # \param ass_mode 
    # \param charge 
    # \param type_list 
    #
    def addEntry(atom_type: str, ass_mode: int, charge: float, type_list: str) -> None: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def removeEntry(atom_type: str) -> bool: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def getEntry(atom_type: str) -> Entry: pass

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
    def load(is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94FormalAtomChargeDefinitionTable instance \a table.
    # \param table The \e %MMFF94FormalAtomChargeDefinitionTable instance to copy.
    # \return \a self
    #
    def assign(table: MMFF94FormalAtomChargeDefinitionTable) -> MMFF94FormalAtomChargeDefinitionTable: pass

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
