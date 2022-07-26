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
class MMFF94PartialBondChargeIncrementTable(Boost.Python.instance):

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
        # \param part_bond_chg_inc 
        # \param form_chg_adj_factor 
        #
        def __init__(self: object, atom_type: int, part_bond_chg_inc: float, form_chg_adj_factor: float) -> None: pass

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
        def getAtomType(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getPartialChargeIncrement(self: Entry) -> float: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getFormalChargeAdjustmentFactor(self: Entry) -> float: pass

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
        partialChargeIncrement = property(getPartialChargeIncrement)

        ##
        # \brief 
        #
        formalChargeAdjustmentFactor = property(getFormalChargeAdjustmentFactor)

    ##
    # \brief Initializes the \e %MMFF94PartialBondChargeIncrementTable instance.
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94PartialBondChargeIncrementTable instance.
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    #
    # Different Python \e %MMFF94PartialBondChargeIncrementTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94PartialBondChargeIncrementTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94PartialBondChargeIncrementTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \param atom_type 
    # \param part_bond_chg_inc 
    # \param form_chg_adj_factor 
    #
    def addEntry(self: MMFF94PartialBondChargeIncrementTable, atom_type: int, part_bond_chg_inc: float, form_chg_adj_factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def removeEntry(self: MMFF94PartialBondChargeIncrementTable, atom_type: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def getEntry(self: MMFF94PartialBondChargeIncrementTable, atom_type: int) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    #
    def clear(self: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: MMFF94PartialBondChargeIncrementTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: MMFF94PartialBondChargeIncrementTable) -> list: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \param is 
    #
    def load(self: MMFF94PartialBondChargeIncrementTable, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    #
    def loadDefaults(self: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94PartialBondChargeIncrementTable instance \a table.
    # \param self The \e %MMFF94PartialBondChargeIncrementTable instance this method is called upon.
    # \param table The \e %MMFF94PartialBondChargeIncrementTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94PartialBondChargeIncrementTable, table: MMFF94PartialBondChargeIncrementTable) -> MMFF94PartialBondChargeIncrementTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94PartialBondChargeIncrementTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94PartialBondChargeIncrementTable: pass

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
