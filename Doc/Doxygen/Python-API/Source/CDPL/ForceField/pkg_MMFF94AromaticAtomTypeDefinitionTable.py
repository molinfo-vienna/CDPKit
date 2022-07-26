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
class MMFF94AromaticAtomTypeDefinitionTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param old_type 
        # \param aro_type 
        # \param atomic_no 
        # \param ring_size 
        # \param het_atom_dist 
        # \param im_cation 
        # \param n5_anion 
        #
        def __init__(self: object, old_type: str, aro_type: str, atomic_no: int, ring_size: int, het_atom_dist: int, im_cation: bool, n5_anion: bool) -> None: pass

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
        def getOldAtomType(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAromAtomType(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getAtomicNumber(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getRingSize(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getHeteroAtomDistance(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isImidazoliumCation(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isN5RingAnion(self: Entry) -> bool: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        oldAtomType = property(getOldAtomType)

        ##
        # \brief 
        #
        aromAtomType = property(getAromAtomType)

        ##
        # \brief 
        #
        atomicNumber = property(getAtomicNumber)

        ##
        # \brief 
        #
        ringSize = property(getRingSize)

        ##
        # \brief 
        #
        heteroAtomDistance = property(getHeteroAtomDistance)

        ##
        # \brief FIXME!
        #
        imidazoliumCation = property(getImidazoliumCation)

        ##
        # \brief FIXME!
        #
        n5RingAnion = property(getN5RingAnion)

    ##
    # \brief Initializes the \e %MMFF94AromaticAtomTypeDefinitionTable instance.
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AromaticAtomTypeDefinitionTable instance.
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    #
    # Different Python \e %MMFF94AromaticAtomTypeDefinitionTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94AromaticAtomTypeDefinitionTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94AromaticAtomTypeDefinitionTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \param old_type 
    # \param aro_type 
    # \param atomic_no 
    # \param ring_size 
    # \param het_atom_dist 
    # \param im_cation 
    # \param n5_anion 
    #
    def addEntry(self: MMFF94AromaticAtomTypeDefinitionTable, old_type: str, aro_type: str, atomic_no: int, ring_size: int, het_atom_dist: int, im_cation: bool, n5_anion: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \param idx 
    #
    def removeEntry(self: MMFF94AromaticAtomTypeDefinitionTable, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getEntry(self: MMFF94AromaticAtomTypeDefinitionTable, idx: int) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    #
    def clear(self: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: MMFF94AromaticAtomTypeDefinitionTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: MMFF94AromaticAtomTypeDefinitionTable) -> list: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \param is 
    #
    def load(self: MMFF94AromaticAtomTypeDefinitionTable, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    #
    def loadDefaults(self: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94AromaticAtomTypeDefinitionTable instance \a table.
    # \param self The \e %MMFF94AromaticAtomTypeDefinitionTable instance this method is called upon.
    # \param table The \e %MMFF94AromaticAtomTypeDefinitionTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94AromaticAtomTypeDefinitionTable, table: MMFF94AromaticAtomTypeDefinitionTable) -> MMFF94AromaticAtomTypeDefinitionTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94AromaticAtomTypeDefinitionTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94AromaticAtomTypeDefinitionTable: pass

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
