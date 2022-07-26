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
class TorsionCategory(Boost.Python.instance):

    ##
    # \brief 
    #
    class RuleSequence(Boost.Python.instance):

        ##
        # \brief Initializes the \e %RuleSequence instance.
        # \param self The \e %RuleSequence instance to initialize.
        # \param rules 
        #
        def __init__(self: object, rules: RuleSequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %RuleSequence instance this method is called upon.
        #
        # Different Python \e %RuleSequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %RuleSequence instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: RuleSequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %RuleSequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: RuleSequence, idx: int) -> TorsionRule: pass

        ##
        # \brief 
        # \param self The \e %RuleSequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: RuleSequence, idx: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %RuleSequence instance this method is called upon.
        # \return 
        #
        def __len__(self: RuleSequence) -> int: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

    ##
    # \brief 
    #
    class CategorySequence(Boost.Python.instance):

        ##
        # \brief Initializes the \e %CategorySequence instance.
        # \param self The \e %CategorySequence instance to initialize.
        # \param cat 
        #
        def __init__(self: object, cat: CategorySequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %CategorySequence instance this method is called upon.
        #
        # Different Python \e %CategorySequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CategorySequence instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: CategorySequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %CategorySequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: CategorySequence, idx: int) -> TorsionCategory: pass

        ##
        # \brief 
        # \param self The \e %CategorySequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: CategorySequence, idx: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %CategorySequence instance this method is called upon.
        # \return 
        #
        def __len__(self: CategorySequence) -> int: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

    ##
    # \brief Initializes the \e %TorsionCategory instance.
    # \param self The \e %TorsionCategory instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TorsionCategory instance.
    # \param self The \e %TorsionCategory instance to initialize.
    # \param cat 
    #
    def __init__(self: object, cat: TorsionCategory) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %TorsionCategory instance this method is called upon.
    #
    # Different Python \e %TorsionCategory instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionCategory instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: TorsionCategory) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionCategory instance \a cat.
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param cat The \e %TorsionCategory instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TorsionCategory, cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getMatchPatternString(self: TorsionCategory) -> str: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param ptn_str 
    #
    def setMatchPatternString(self: TorsionCategory, ptn_str: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getMatchPattern(self: TorsionCategory) -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param ptn 
    #
    def setMatchPattern(self: TorsionCategory, ptn: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getBondAtom1Type(self: TorsionCategory) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param type 
    #
    def setBondAtom1Type(self: TorsionCategory, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getBondAtom2Type(self: TorsionCategory) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param type 
    #
    def setBondAtom2Type(self: TorsionCategory, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getName(self: TorsionCategory) -> str: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param name 
    #
    def setName(self: TorsionCategory, name: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param recursive 
    # \return 
    #
    def getNumRules(self: TorsionCategory, recursive: bool = False) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getRule(self: TorsionCategory, idx: int) -> TorsionRule: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param idx 
    #
    def removeRule(self: TorsionCategory, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param rule 
    # \return 
    #
    def addRule(self: TorsionCategory, rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getRules(self: TorsionCategory) -> RuleSequence: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param recursive 
    # \return 
    #
    def getNumCategories(self: TorsionCategory, recursive: bool = False) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getCategory(self: TorsionCategory, idx: int) -> TorsionCategory: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param idx 
    #
    def removeCategory(self: TorsionCategory, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param cat 
    # \return 
    #
    def addCategory(self: TorsionCategory, cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \return 
    #
    def getCategories(self: TorsionCategory) -> CategorySequence: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    #
    def clear(self: TorsionCategory) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionCategory instance this method is called upon.
    # \param cat 
    #
    def swap(self: TorsionCategory, cat: TorsionCategory) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    rules = property(getRules)

    ##
    # \brief 
    #
    categories = property(getCategories)

    ##
    # \brief 
    #
    numRules = property(getNumRules)

    ##
    # \brief 
    #
    numCategories = property(getNumCategories)

    ##
    # \brief 
    #
    bondAtom1Type = property(getBondAtom1Type, setBondAtom1Type)

    ##
    # \brief 
    #
    bondAtom2Type = property(getBondAtom2Type, setBondAtom2Type)

    ##
    # \brief 
    #
    matchPatternString = property(getMatchPatternString, setMatchPatternString)

    ##
    # \brief 
    #
    matchPattern = property(getMatchPattern, setMatchPattern)

    ##
    # \brief 
    #
    name = property(getName, setName)
