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
# \brief Generic rule-based molecule fragmentation engine that splits a molecular graph along bonds matching user-defined SMARTS fragmentation rules.
# 
# Fragmentation rules are added via addFragmentationRule() (each rule has a SMARTS pattern matching a bond plus a numeric rule ID). Bonds matching any registered rule are scheduled for splitting, unless a registered exclude pattern overrides the split. The optional fragment filter rejects generated fragments based on a user-supplied predicate. The connectivity between the resulting fragments is exposed via the FragmentLink list, recording for each cleaved bond the two adjacent fragment indices, the cleaved bond, the matching rule and per-side atom labels.
# 
class FragmentGenerator(Boost.Python.instance):

    ##
    # \brief A single fragmentation rule, consisting of a SMARTS match pattern and a numeric rule ID.
    # 
    class FragmentationRule(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %FragmentationRule instance \a rule.
        # \param rule The \c %FragmentationRule instance to copy.
        # 
        def __init__(rule: FragmentationRule) -> None: pass

        ##
        # \brief Constructs the fragmentation rule.
        # 
        # \param match_ptn The SMARTS match pattern (must match a single bond to be cleaved).
        # \param id The rule identifier (forwarded to FragmentLink.getRuleID() for cleaved bonds).
        # 
        def __init__(match_ptn: MolecularGraph, id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %FragmentationRule instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentationRule instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentationRule instance \a rule.
        # \param rule The \c %FragmentationRule instance to copy.
        # \return \a self
        # 
        def assign(rule: FragmentationRule) -> FragmentationRule: pass

        ##
        # \brief Returns the SMARTS match pattern of this rule.
        # 
        # \return A reference to the pattern smart reference.
        # 
        def getMatchPattern() -> MolecularGraph: pass

        ##
        # \brief Sets the SMARTS match pattern of this rule.
        # 
        # \param ptn The new pattern.
        # 
        def setMatchPattern(ptn: MolecularGraph) -> None: pass

        ##
        # \brief Returns the rule identifier.
        # 
        # \return The numeric rule ID.
        # 
        def getID() -> int: pass

        ##
        # \brief Sets the rule identifier.
        # 
        # \param id The new numeric rule ID.
        # 
        def setID(id: int) -> None: pass

        objectID = property(getObjectID)

        matchPattern = property(getMatchPattern, setMatchPattern)

        id = property(getID, setID)

    ##
    # \brief A pattern overriding a fragmentation rule: bonds matching the pattern are not cleaved.
    # 
    # An exclude pattern is either rule-specific (only the matching rule is suppressed) or generic (all rules are suppressed for the matching bonds).
    # 
    class ExcludePattern(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %ExcludePattern instance \a excl_ptn.
        # \param excl_ptn The \c %ExcludePattern instance to copy.
        # 
        def __init__(excl_ptn: ExcludePattern) -> None: pass

        ##
        # \brief Constructs a rule-specific exclude pattern.
        # 
        # \param match_ptn The SMARTS match pattern.
        # \param rule_id The rule ID this exclusion applies to.
        # 
        def __init__(match_ptn: MolecularGraph, rule_id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %ExcludePattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ExcludePattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %ExcludePattern instance \a excl_ptn.
        # \param excl_ptn The \c %ExcludePattern instance to copy.
        # \return \a self
        # 
        def assign(excl_ptn: ExcludePattern) -> ExcludePattern: pass

        ##
        # \brief Returns the SMARTS match pattern.
        # 
        # \return A reference to the pattern smart reference.
        # 
        def getMatchPattern() -> MolecularGraph: pass

        ##
        # \brief Sets the SMARTS match pattern.
        # 
        # \param ptn The new pattern.
        # 
        def setMatchPattern(ptn: MolecularGraph) -> None: pass

        ##
        # \brief Returns the rule ID this exclusion applies to (only meaningful when isGeneric() is <tt>False</tt>).
        # 
        # \return The rule ID.
        # 
        def getRuleID() -> int: pass

        ##
        # \brief Sets the rule ID this exclusion applies to.
        # 
        # \param id The new rule ID.
        # 
        def setRuleID(id: int) -> None: pass

        ##
        # \brief Tells whether this exclude pattern applies to all rules (generic) or only to a specific one.
        # 
        # \return <tt>True</tt> if the pattern is generic, and <tt>False</tt> otherwise.
        # 
        def isGeneric() -> bool: pass

        ##
        # \brief Sets whether this exclude pattern is generic.
        # 
        # \param generic If <tt>True</tt>, the pattern applies to all rules. If <tt>False</tt>, only to the configured rule ID.
        # 
        def setGeneric(generic: bool) -> None: pass

        objectID = property(getObjectID)

        matchPattern = property(getMatchPattern, setMatchPattern)

        ruleID = property(getRuleID, setRuleID)

        generic = property(isGeneric, setGeneric)

    ##
    # \brief Records the connectivity between two fragments produced by a single bond cleavage.
    # 
    class FragmentLink(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %FragmentLink instance \a link.
        # \param link The \c %FragmentLink instance to copy.
        # 
        def __init__(link: FragmentLink) -> None: pass

        ##
        # \brief Constructs the fragment link.
        # 
        # \param frag1_idx The index of the first fragment in the output FragmentList.
        # \param frag2_idx The index of the second fragment in the output FragmentList.
        # \param bond The cleaved bond (from the original molecular graph).
        # \param rule_id The rule ID that triggered the cleavage.
        # \param atom1_label The label assigned to the first atom of the cleaved bond.
        # \param atom2_label The label assigned to the second atom of the cleaved bond.
        # 
        def __init__(frag1_idx: int, frag2_idx: int, bond: Bond, rule_id: int, atom1_label: int, atom2_label: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %FragmentLink instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentLink instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentLink instance \a link.
        # \param link The \c %FragmentLink instance to copy.
        # \return \a self
        # 
        def assign(link: FragmentLink) -> FragmentLink: pass

        ##
        # \brief Returns the index of the first fragment in the output FragmentList.
        # 
        # \return The first fragment index.
        # 
        def getFragment1Index() -> int: pass

        ##
        # \brief Returns the index of the second fragment in the output FragmentList.
        # 
        # \return The second fragment index.
        # 
        def getFragment2Index() -> int: pass

        ##
        # \brief Returns the cleaved bond from the original molecular graph.
        # 
        # \return A reference to the bond.
        # 
        def getBond() -> Bond: pass

        ##
        # \brief Returns the rule ID that triggered the cleavage of this bond.
        # 
        # \return The rule ID.
        # 
        def getRuleID() -> int: pass

        ##
        # \brief Returns the label of the first atom of the cleaved bond.
        # 
        # \return The first atom label.
        # 
        def getAtom1Label() -> int: pass

        ##
        # \brief Returns the label of the second atom of the cleaved bond.
        # 
        # \return The second atom label.
        # 
        def getAtom2Label() -> int: pass

        objectID = property(getObjectID)

        fragment1Index = property(getFragment1Index)

        fragment2Index = property(getFragment2Index)

        bond = property(getBond)

        ruleID = property(getRuleID)

        atom1Label = property(getAtom1Label)

        atom2Label = property(getAtom2Label)

    ##
    # \brief Constructs the <tt>FragmentGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FragmentGenerator</tt> instance <em>gen</em>.
    # 
    # \param gen The <tt>FragmentGenerator</tt> to copy.
    # 
    def __init__(gen: FragmentGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the state of this generator by a copy of the state of <em>gen</em>.
    # 
    # \param gen The source <tt>FragmentGenerator</tt>.
    # 
    # \return \a self
    # 
    def assign(gen: FragmentGenerator) -> FragmentGenerator: pass

    ##
    # \brief Registers a new fragmentation rule by its SMARTS match pattern and rule ID.
    # 
    # \param match_ptn The SMARTS match pattern (must match a single bond to be cleaved).
    # \param rule_id The rule identifier.
    # 
    def addFragmentationRule(match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief Appends a copy of the pre-built fragmentation rule <em>rule</em>.
    # 
    # \param rule The rule to copy and register.
    # 
    def addFragmentationRule(rule: FragmentationRule) -> None: pass

    ##
    # \brief Removes the fragmentation rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumFragmentationRules() - 1].
    # 
    def removeFragmentationRule(idx: int) -> None: pass

    ##
    # \brief Returns the fragmentation rule at index <em>idx</em>.
    # 
    # \param idx The zero-based rule index.
    # 
    # \return A reference to the rule. 
    # 
    # \throw Base.IndexError if the number of rules is zero or <em>idx</em> is not in the range [0, getNumFragmentationRules() - 1].
    # 
    def getFragmentationRule(idx: int) -> FragmentationRule: pass

    ##
    # \brief Removes all registered fragmentation rules.
    # 
    def clearFragmentationRules() -> None: pass

    ##
    # \brief Returns the number of registered fragmentation rules.
    # 
    # \return The rule count.
    # 
    def getNumFragmentationRules() -> int: pass

    ##
    # \brief Registers a rule-specific exclude pattern.
    # 
    # \param match_ptn The SMARTS match pattern.
    # \param rule_id The rule ID this exclusion applies to.
    # 
    def addExcludePattern(match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief Appends a copy of the pre-built exclude pattern <em>excl_ptn</em>.
    # 
    # \param excl_ptn The exclude pattern to copy and register.
    # 
    def addExcludePattern(excl_ptn: ExcludePattern) -> None: pass

    ##
    # \brief Removes the exclude pattern at index <em>idx</em>.
    # 
    # \param idx The zero-based pattern index.
    # 
    # \throw Base.IndexError if the number of exclude patterns is zero or <em>idx</em> is not in the range [0, getNumExcludePatterns() - 1].
    # 
    def removeExcludePattern(idx: int) -> None: pass

    ##
    # \brief Returns the exclude pattern at index <em>idx</em>.
    # 
    # \param idx The zero-based pattern index.
    # 
    # \return A reference to the exclude pattern. 
    # 
    # \throw Base.IndexError if the number of exclude patterns is zero or <em>idx</em> is not in the range [0, getNumExcludePatterns() - 1].
    # 
    def getExcludePattern(idx: int) -> ExcludePattern: pass

    ##
    # \brief Removes all registered exclude patterns.
    # 
    def clearExcludePatterns() -> None: pass

    ##
    # \brief Returns the number of registered exclude patterns.
    # 
    # \return The exclude-pattern count.
    # 
    def getNumExcludePatterns() -> int: pass

    ##
    # \brief Sets the predicate used to filter the generated fragments (fragments for which the predicate returns <tt>False</tt> are discarded).
    # 
    # \param func The new fragment-filter function.
    # 
    def setFragmentFilterFunction(func: BoolConstMolecularGraphFunctor) -> None: pass

    ##
    # \brief Returns the predicate used to filter the generated fragments.
    # 
    # \return A reference to the fragment-filter function.
    # 
    def getFragmentFilterFunction() -> BoolConstMolecularGraphFunctor: pass

    ##
    # \brief Performs the fragmentation of <em>molgraph</em> and writes the resulting fragments to <em>frag_list</em>.
    # 
    # \param molgraph The molecular graph to fragment.
    # \param frag_list The output fragment list.
    # \param append If <tt>True</tt>, new fragments are appended to <em>frag_list</em>. Otherwise, the list is cleared first.
    # 
    def generate(molgraph: MolecularGraph, frag_list: FragmentList, append: bool = False) -> None: pass

    ##
    # \brief Returns the fragment link at index <em>idx</em>.
    # 
    # \param idx The zero-based link index.
    # 
    # \return A reference to the fragment link. 
    # 
    # \throw Base.IndexError if the number of fragment links is zero or <em>idx</em> is not in the range [0, getNumFragmentLinks() - 1].
    # 
    def getFragmentLink(idx: int) -> FragmentLink: pass

    ##
    # \brief Returns the number of fragment links produced by the most recent generate() call.
    # 
    # \return The fragment-link count.
    # 
    def getNumFragmentLinks() -> int: pass

    ##
    # \brief Specifies whether the split (cleaved) bonds shall be retained in the output fragments.
    # 
    # \param include If <tt>True</tt>, the cleaved bonds remain part of the adjacent output fragments.
    # 
    def includeSplitBonds(include: bool) -> None: pass

    objectID = property(getObjectID)

    fragmentFilterFunction = property(getFragmentFilterFunction, setFragmentFilterFunction)

    incSplitBonds = property(splitBondsIncluded, includeSplitBonds)

    numFragmentationRules = property(getNumFragmentationRules)

    numExcludePatterns = property(getNumExcludePatterns)

    numFragmentLinks = property(getNumFragmentLinks)
