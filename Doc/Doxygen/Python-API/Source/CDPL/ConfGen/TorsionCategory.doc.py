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
# \brief A node of a hierarchical torsion library: a named, optionally pattern-matched category that holds child categories and torsion rules.
# 
class TorsionCategory(Boost.Python.instance):

    ##
    # \brief 
    #
    class RuleSequence(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %RuleSequence instance \a rules.
        # \param rules The \c %RuleSequence instance to copy.
        # 
        def __init__(rules: RuleSequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %RuleSequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %RuleSequence instances \e a and \e b reference different C++ objects. 
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
        # \brief Initializes a copy of the \c %CategorySequence instance \a cat.
        # \param cat The \c %CategorySequence instance to copy.
        # 
        def __init__(cat: CategorySequence) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %CategorySequence instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %CategorySequence instances \e a and \e b reference different C++ objects. 
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
    # \brief Constructs an empty <tt>TorsionCategory</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %TorsionCategory instance \a cat.
    # \param cat The \c %TorsionCategory instance to copy.
    # 
    def __init__(cat: TorsionCategory) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionCategory instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionCategory instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TorsionCategory instance \a cat.
    # \param cat The \c %TorsionCategory instance to copy.
    # \return \a self
    # 
    def assign(cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief Returns the SMARTS string used to perceive bonds belonging to this category.
    # 
    # \return A reference to the SMARTS string.
    # 
    def getMatchPatternString() -> str: pass

    ##
    # \brief Sets the SMARTS string used to perceive bonds belonging to this category.
    # 
    # \param ptn_str The new SMARTS pattern string.
    # 
    def setMatchPatternString(ptn_str: str) -> None: pass

    ##
    # \brief Returns the molecular-graph pattern used to perceive bonds belonging to this category.
    # 
    # \return A reference to the pattern smart reference.
    # 
    def getMatchPattern() -> Chem.MolecularGraph: pass

    ##
    # \brief Sets the molecular-graph pattern used to perceive bonds belonging to this category.
    # 
    # \param ptn The new molecular-graph pattern.
    # 
    def setMatchPattern(ptn: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the atom type of the first central-bond atom required by this category.
    # 
    # \return The atom type (Chem.AtomType value).
    # 
    def getBondAtom1Type() -> int: pass

    ##
    # \brief Sets the atom type of the first central-bond atom required by this category.
    # 
    # \param type The new atom type (Chem.AtomType value).
    # 
    def setBondAtom1Type(type: int) -> None: pass

    ##
    # \brief Returns the atom type of the second central-bond atom required by this category.
    # 
    # \return The atom type (Chem.AtomType value).
    # 
    def getBondAtom2Type() -> int: pass

    ##
    # \brief Sets the atom type of the second central-bond atom required by this category.
    # 
    # \param type The new atom type (Chem.AtomType value).
    # 
    def setBondAtom2Type(type: int) -> None: pass

    ##
    # \brief Returns the category name.
    # 
    # \return A reference to the category name.
    # 
    def getName() -> str: pass

    ##
    # \brief Sets the category name.
    # 
    # \param name The new name.
    # 
    def setName(name: str) -> None: pass

    ##
    # \brief Returns the number of contained torsion rules.
    # 
    # \param recursive If <tt>True</tt>, the count includes rules of all descendant categories.
    # 
    # \return The torsion-rule count.
    # 
    def getNumRules(recursive: bool = False) -> int: pass

    ##
    # \brief Returns the torsion rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \return A reference to the rule. 
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumRules() - 1].
    # 
    def getRule(idx: int) -> TorsionRule: pass

    ##
    # \brief Removes the torsion rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumRules() - 1].
    # 
    def removeRule(idx: int) -> None: pass

    ##
    # \brief Appends a copy of <em>rule</em> as a contained torsion rule.
    # 
    # \param rule The torsion rule to copy.
    # 
    # \return A reference to the newly added rule.
    # 
    def addRule(rule: TorsionRule) -> TorsionRule: pass

    ##
    # \brief 
    # \return 
    #
    def getRules() -> RuleSequence: pass

    ##
    # \brief Returns the number of child categories.
    # 
    # \param recursive If <tt>True</tt>, the count includes all descendant categories.
    # 
    # \return The child-category count.
    # 
    def getNumCategories(recursive: bool = False) -> int: pass

    ##
    # \brief Returns the child category at index <em>idx</em>.
    # 
    # \param idx The zero-based child-category index.
    # 
    # \return A reference to the child category. 
    # 
    # \throw Base.IndexError if the number of child categories is zero or <em>idx</em> is not in the range [0, getNumCategories() - 1].
    # 
    def getCategory(idx: int) -> TorsionCategory: pass

    ##
    # \brief Removes the child category at index <em>idx</em>.
    # 
    # \param idx The zero-based child-category index.
    # 
    # \throw Base.IndexError if the number of child categories is zero or <em>idx</em> is not in the range [0, getNumCategories() - 1].
    # 
    def removeCategory(idx: int) -> None: pass

    ##
    # \brief Appends a copy of <em>cat</em> as a child category.
    # 
    # \param cat The child category to copy.
    # 
    # \return A reference to the newly added child category.
    # 
    def addCategory(cat: TorsionCategory) -> TorsionCategory: pass

    ##
    # \brief 
    # \return 
    #
    def getCategories() -> CategorySequence: pass

    ##
    # \brief Removes all child categories and contained rules and resets the pattern/atom-type data.
    # 
    def clear() -> None: pass

    ##
    # \brief Swaps the contents of this category with <em>cat</em>.
    # 
    # \param cat The other category.
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
