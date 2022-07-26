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
class MMFF94AtomTypePropertyTable(Boost.Python.instance):

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
        # \param atomic_no 
        # \param num_nbrs 
        # \param valence 
        # \param has_pi_lp 
        # \param mltb_desig 
        # \param is_arom 
        # \param lin_bnd_ang 
        # \param has_mb_or_sb 
        #
        def __init__(self: object, atom_type: int, atomic_no: int, num_nbrs: int, valence: int, has_pi_lp: bool, mltb_desig: int, is_arom: bool, lin_bnd_ang: bool, has_mb_or_sb: bool) -> None: pass

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
        def getAtomicNumber(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getNumNeighbors(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getValence(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def hasPiLonePair(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getMultiBondDesignator(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isAromaticAtomType(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def formsLinearBondAngle(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def formsMultiOrSingleBonds(self: Entry) -> bool: pass

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
        atomicNumber = property(getAtomicNumber)

        ##
        # \brief 
        #
        numNeighbors = property(getNumNeighbors)

        ##
        # \brief 
        #
        valence = property(getValence)

        ##
        # \brief FIXME!
        #
        piLonePair = property(getPiLonePair)

        ##
        # \brief 
        #
        multiBondDesignator = property(getMultiBondDesignator)

        ##
        # \brief FIXME!
        #
        aromAtomType = property(getAromAtomType)

        ##
        # \brief FIXME!
        #
        linearBondAngle = property(getLinearBondAngle)

        ##
        # \brief FIXME!
        #
        multiOrSingleBonds = property(getMultiOrSingleBonds)

    ##
    # \brief Initializes the \e %MMFF94AtomTypePropertyTable instance.
    # \param self The \e %MMFF94AtomTypePropertyTable instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %MMFF94AtomTypePropertyTable instance.
    # \param self The \e %MMFF94AtomTypePropertyTable instance to initialize.
    # \param table 
    #
    def __init__(self: object, table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    #
    # Different Python \e %MMFF94AtomTypePropertyTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94AtomTypePropertyTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: MMFF94AtomTypePropertyTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \param atom_type 
    # \param atomic_no 
    # \param num_nbrs 
    # \param valence 
    # \param has_pi_lp 
    # \param mltb_desig 
    # \param is_arom 
    # \param lin_bnd_ang 
    # \param has_mb_or_sb 
    #
    def addEntry(self: MMFF94AtomTypePropertyTable, atom_type: int, atomic_no: int, num_nbrs: int, valence: int, has_pi_lp: bool, mltb_desig: int, is_arom: bool, lin_bnd_ang: bool, has_mb_or_sb: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def removeEntry(self: MMFF94AtomTypePropertyTable, atom_type: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \param atom_type 
    # \return 
    #
    def getEntry(self: MMFF94AtomTypePropertyTable, atom_type: int) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    #
    def clear(self: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: MMFF94AtomTypePropertyTable) -> int: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \return 
    #
    def getEntries(self: MMFF94AtomTypePropertyTable) -> list: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \param is 
    #
    def load(self: MMFF94AtomTypePropertyTable, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    #
    def loadDefaults(self: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94AtomTypePropertyTable instance \a table.
    # \param self The \e %MMFF94AtomTypePropertyTable instance this method is called upon.
    # \param table The \e %MMFF94AtomTypePropertyTable instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MMFF94AtomTypePropertyTable, table: MMFF94AtomTypePropertyTable) -> MMFF94AtomTypePropertyTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94AtomTypePropertyTable: pass

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
