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
class MMFF94BondStretchingRuleParameterTable(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param atomic_no1 
        # \param atomic_no2 
        # \param force_const 
        # \param ref_length 
        # 
        def __init__(atomic_no1: int, atomic_no2: int, force_const: float, ref_length: float) -> None: pass

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
        def getObjectID() -> int: pass

        ##
        # \brief 
        # \param entry 
        # \return 
        #
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomicNumber1() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomicNumber2() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getForceConstant() -> float: pass

        ##
        # \brief 
        # \return 
        #
        def getReferenceLength() -> float: pass

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

        objectID = property(getObjectID)

        ##
        # \brief FIXME!
        # \brief 
        #
        atomicNo1 = property(getAtomicNo1)

        ##
        # \brief FIXME!
        # \brief 
        #
        atomicNo2 = property(getAtomicNo2)

        forceConstant = property(getForceConstant)

        referenceLength = property(getReferenceLength)

    ##
    # \brief Initializes the \e %MMFF94BondStretchingRuleParameterTable instance.
    # \param self The \e %MMFF94BondStretchingRuleParameterTable instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94BondStretchingRuleParameterTable instance.
    # \param self The \e %MMFF94BondStretchingRuleParameterTable instance to initialize.
    # \param table 
    # 
    def __init__(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94BondStretchingRuleParameterTable instance this method is called upon.
    # 
    # Different Python \e %MMFF94BondStretchingRuleParameterTable instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94BondStretchingRuleParameterTable instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atomic_no1 
    # \param atomic_no2 
    # \param force_const 
    # \param ref_length 
    #
    def addEntry(atomic_no1: int, atomic_no2: int, force_const: float, ref_length: float) -> None: pass

    ##
    # \brief 
    # \param atomic_no1 
    # \param atomic_no2 
    # \return 
    #
    def removeEntry(atomic_no1: int, atomic_no2: int) -> bool: pass

    ##
    # \brief 
    # \param atomic_no1 
    # \param atomic_no2 
    # \return 
    #
    def getEntry(atomic_no1: int, atomic_no2: int) -> Entry: pass

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
    # \brief 
    # \param table 
    # \return 
    #
    def assign(table: MMFF94BondStretchingRuleParameterTable) -> MMFF94BondStretchingRuleParameterTable: pass

    ##
    # \brief 
    # \param table 
    #
    @staticmethod
    def set(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94BondStretchingRuleParameterTable: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
