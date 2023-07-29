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
class TorsionCategory(Boost.Python.instance):

    ##
    # \brief 
    #
    class RuleSequence(Boost.Python.instance):

        ##
        # \brief Initializes the \e %RuleSequence instance.
        # \param rules 
        # 
        def __init__(rules: RuleSequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %RuleSequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %RuleSequence instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> TorsionRule: pass

        ##
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        objectID = property(getObjectID)

    ##
    # \brief 
    #
    class CategorySequence(Boost.Python.instance):

        ##
        # \brief Initializes the \e %CategorySequence instance.
        # \param cat 
        # 
        def __init__(cat: CategorySequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %CategorySequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CategorySequence instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> TorsionCategory: pass

        ##
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        objectID = property(getObjectID)

    ##
    # \brief Initializes the \e %TorsionCategory instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TorsionCategory instance.
    # \param cat 
    # 
    def __init__(cat: TorsionCategory) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %TorsionCategory instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionCategory instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionCategory instance \a cat.
    # \param cat The \e %TorsionCategory instance to copy.
    # \return \a self
    # 
    def assign(cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief 
    # \return 
    #
    def getMatchPatternString() -> str: pass

    ##
    # \brief 
    # \param ptn_str 
    #
    def setMatchPatternString(ptn_str: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMatchPattern() -> Chem.MolecularGraph: pass

    ##
    # \brief 
    # \param ptn 
    #
    def setMatchPattern(ptn: Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBondAtom1Type() -> int: pass

    ##
    # \brief 
    # \param type 
    #
    def setBondAtom1Type(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBondAtom2Type() -> int: pass

    ##
    # \brief 
    # \param type 
    #
    def setBondAtom2Type(type: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getName() -> str: pass

    ##
    # \brief 
    # \param name 
    #
    def setName(name: str) -> None: pass

    ##
    # \brief 
    # \param recursive 
    # \return 
    #
    def getNumRules(recursive: bool = False) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getRule(idx: int) -> TorsionRule: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeRule(idx: int) -> None: pass

    ##
    # \brief 
    # \param rule 
    # \return 
    #
    def addRule(rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief 
    # \return 
    #
    def getRules() -> RuleSequence: pass

    ##
    # \brief 
    # \param recursive 
    # \return 
    #
    def getNumCategories(recursive: bool = False) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getCategory(idx: int) -> TorsionCategory: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeCategory(idx: int) -> None: pass

    ##
    # \brief 
    # \param cat 
    # \return 
    #
    def addCategory(cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief 
    # \return 
    #
    def getCategories() -> CategorySequence: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param cat 
    #
    def swap(cat: TorsionCategory) -> None: pass

    objectID = property(getObjectID)

    rules = property(getRules)

    categories = property(getCategories)

    numRules = property(getNumRules)

    numCategories = property(getNumCategories)

    bondAtom1Type = property(getBondAtom1Type, setBondAtom1Type)

    bondAtom2Type = property(getBondAtom2Type, setBondAtom2Type)

    matchPatternString = property(getMatchPatternString, setMatchPatternString)

    matchPattern = property(getMatchPattern, setMatchPattern)

    name = property(getName, setName)
