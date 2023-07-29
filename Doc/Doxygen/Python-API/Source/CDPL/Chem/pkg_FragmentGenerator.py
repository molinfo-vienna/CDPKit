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
# \brief FragmentGenerator.
# 
class FragmentGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class FragmentationRuler(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentationRuler instance.
        # \param rule 
        # 
        def __init__(rule: FragmentationRuler) -> None: pass

        ##
        # \brief Initializes the \e %FragmentationRuler instance.
        # \param match_ptn 
        # \param id 
        # 
        def __init__(match_ptn: MolecularGraph, id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %FragmentationRuler instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentationRuler instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentationRuler instance \a rule.
        # \param rule The \e %FragmentationRuler instance to copy.
        # \return \a self
        # 
        def assign(rule: FragmentationRuler) -> FragmentationRuler: pass

        ##
        # \brief 
        # \return 
        #
        def getMatchPattern() -> MolecularGraph: pass

        ##
        # \brief 
        # \param ptn 
        #
        def setMatchPattern(ptn: MolecularGraph) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getID() -> int: pass

        ##
        # \brief 
        # \param id 
        #
        def setID(id: int) -> None: pass

        objectID = property(getObjectID)

        matchPattern = property(getMatchPattern, setMatchPattern)

        ##
        # \brief FIXME!
        # \brief 
        #
        id = property(getId, setId)

    ##
    # \brief 
    #
    class ExcludePattern(Boost.Python.instance):

        ##
        # \brief Initializes the \e %ExcludePattern instance.
        # \param excl_ptn 
        # 
        def __init__(excl_ptn: ExcludePattern) -> None: pass

        ##
        # \brief Initializes the \e %ExcludePattern instance.
        # \param match_ptn 
        # \param rule_id 
        # 
        def __init__(match_ptn: MolecularGraph, rule_id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %ExcludePattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ExcludePattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %ExcludePattern instance \a excl_ptn.
        # \param excl_ptn The \e %ExcludePattern instance to copy.
        # \return \a self
        # 
        def assign(excl_ptn: ExcludePattern) -> ExcludePattern: pass

        ##
        # \brief 
        # \return 
        #
        def getMatchPattern() -> MolecularGraph: pass

        ##
        # \brief 
        # \param ptn 
        #
        def setMatchPattern(ptn: MolecularGraph) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getRuleID() -> int: pass

        ##
        # \brief 
        # \param id 
        #
        def setRuleID(id: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def isGeneric() -> bool: pass

        ##
        # \brief 
        # \param generic 
        #
        def setGeneric(generic: bool) -> None: pass

        objectID = property(getObjectID)

        matchPattern = property(getMatchPattern, setMatchPattern)

        ruleID = property(getRuleID, setRuleID)

        ##
        # \brief FIXME!
        # \brief 
        #
        generic = property(getGeneric, setGeneric)

    ##
    # \brief 
    #
    class FragmentLink(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentLink instance.
        # \param link 
        # 
        def __init__(link: FragmentLink) -> None: pass

        ##
        # \brief Initializes the \e %FragmentLink instance.
        # \param frag1_idx 
        # \param frag2_idx 
        # \param bond 
        # \param rule_id 
        # \param atom1_label 
        # \param atom2_label 
        # 
        def __init__(frag1_idx: int, frag2_idx: int, bond: Bond, rule_id: int, atom1_label: int, atom2_label: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %FragmentLink instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentLink instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentLink instance \a link.
        # \param link The \e %FragmentLink instance to copy.
        # \return \a self
        # 
        def assign(link: FragmentLink) -> FragmentLink: pass

        ##
        # \brief 
        # \return 
        #
        def getFragment1Index() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getFragment2Index() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getBond() -> Bond: pass

        ##
        # \brief 
        # \return 
        #
        def getRuleID() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getAtom1Label() -> int: pass

        ##
        # \brief 
        # \return 
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
    # \brief Initializes the \e %FragmentGenerator instance.
    # \param gen 
    # 
    def __init__(gen: FragmentGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FragmentGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentGenerator instance \a gen.
    # \param gen The \e %FragmentGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: FragmentGenerator) -> FragmentGenerator: pass

    ##
    # \brief 
    # \param match_ptn 
    # \param rule_id 
    #
    def addFragmentationRule(match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief 
    # \param rule 
    #
    def addFragmentationRule(rule: FragmentationRuler) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeFragmentationRule(idx: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getFragmentationRule(idx: int) -> FragmentationRuler: pass

    ##
    # \brief 
    #
    def clearFragmentationRules() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFragmentationRules() -> int: pass

    ##
    # \brief 
    # \param match_ptn 
    # \param rule_id 
    #
    def addExcludePattern(match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief 
    # \param excl_ptn 
    #
    def addExcludePattern(excl_ptn: ExcludePattern) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeExcludePattern(idx: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getExcludePattern(idx: int) -> ExcludePattern: pass

    ##
    # \brief 
    #
    def clearExcludePatterns() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumExcludePatterns() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setFragmentFilterFunction(func: BoolConstMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFragmentFilterFunction() -> BoolConstMolecularGraphFunctor: pass

    ##
    # \brief 
    # \param molgraph 
    # \param frag_list 
    # \param append 
    #
    def generate(molgraph: MolecularGraph, frag_list: FragmentList, append: bool = False) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getFragmentLink(idx: int) -> FragmentLink: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFragmentLinks() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def includeSplitBonds() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeSplitBonds(include: bool) -> None: pass

    objectID = property(getObjectID)

    fragmentFilterFunction = property(getFragmentFilterFunction, setFragmentFilterFunction)

    ##
    # \brief FIXME!
    # \brief 
    #
    incSplitBonds = property(getIncSplitBonds, setIncSplitBonds)

    numFragmentationRules = property(getNumFragmentationRules)

    numExcludePatterns = property(getNumExcludePatterns)

    numFragmentLinks = property(getNumFragmentLinks)
