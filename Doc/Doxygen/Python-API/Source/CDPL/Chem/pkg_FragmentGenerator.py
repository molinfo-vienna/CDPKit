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
class FragmentGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class FragmentationRuler(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentationRuler instance.
        # \param self The \e %FragmentationRuler instance to initialize.
        # \param rule 
        #
        def __init__(self: object, rule: FragmentationRuler) -> None: pass

        ##
        # \brief Initializes the \e %FragmentationRuler instance.
        # \param self The \e %FragmentationRuler instance to initialize.
        # \param match_ptn 
        # \param id 
        #
        def __init__(self: object, match_ptn: MolecularGraph, id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %FragmentationRuler instance this method is called upon.
        #
        # Different Python \e %FragmentationRuler instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentationRuler instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: FragmentationRuler) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentationRuler instance \a rule.
        # \param self The \e %FragmentationRuler instance this method is called upon.
        # \param rule The \e %FragmentationRuler instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: FragmentationRuler, rule: FragmentationRuler) -> FragmentationRuler: pass

        ##
        # \brief 
        # \param self The \e %FragmentationRuler instance this method is called upon.
        # \return 
        #
        def getMatchPattern(self: FragmentationRuler) -> MolecularGraph: pass

        ##
        # \brief 
        # \param self The \e %FragmentationRuler instance this method is called upon.
        # \param ptn 
        #
        def setMatchPattern(self: FragmentationRuler, ptn: MolecularGraph) -> None: pass

        ##
        # \brief 
        # \param self The \e %FragmentationRuler instance this method is called upon.
        # \return 
        #
        def getID(self: FragmentationRuler) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentationRuler instance this method is called upon.
        # \param id 
        #
        def setID(self: FragmentationRuler, id: int) -> None: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        matchPattern = property(getMatchPattern, setMatchPattern)

        ##
        # \brief FIXME!
        #
        id = property(getId, setId)

    ##
    # \brief 
    #
    class ExcludePattern(Boost.Python.instance):

        ##
        # \brief Initializes the \e %ExcludePattern instance.
        # \param self The \e %ExcludePattern instance to initialize.
        # \param excl_ptn 
        #
        def __init__(self: object, excl_ptn: ExcludePattern) -> None: pass

        ##
        # \brief Initializes the \e %ExcludePattern instance.
        # \param self The \e %ExcludePattern instance to initialize.
        # \param match_ptn 
        # \param rule_id 
        #
        def __init__(self: object, match_ptn: MolecularGraph, rule_id: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %ExcludePattern instance this method is called upon.
        #
        # Different Python \e %ExcludePattern instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ExcludePattern instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: ExcludePattern) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %ExcludePattern instance \a excl_ptn.
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \param excl_ptn The \e %ExcludePattern instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: ExcludePattern, excl_ptn: ExcludePattern) -> ExcludePattern: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \return 
        #
        def getMatchPattern(self: ExcludePattern) -> MolecularGraph: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \param ptn 
        #
        def setMatchPattern(self: ExcludePattern, ptn: MolecularGraph) -> None: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \return 
        #
        def getRuleID(self: ExcludePattern) -> int: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \param id 
        #
        def setRuleID(self: ExcludePattern, id: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \return 
        #
        def isGeneric(self: ExcludePattern) -> bool: pass

        ##
        # \brief 
        # \param self The \e %ExcludePattern instance this method is called upon.
        # \param generic 
        #
        def setGeneric(self: ExcludePattern, generic: bool) -> None: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        matchPattern = property(getMatchPattern, setMatchPattern)

        ##
        # \brief 
        #
        ruleID = property(getRuleID, setRuleID)

        ##
        # \brief FIXME!
        #
        generic = property(getGeneric, setGeneric)

    ##
    # \brief 
    #
    class FragmentLink(Boost.Python.instance):

        ##
        # \brief Initializes the \e %FragmentLink instance.
        # \param self The \e %FragmentLink instance to initialize.
        # \param link 
        #
        def __init__(self: object, link: FragmentLink) -> None: pass

        ##
        # \brief Initializes the \e %FragmentLink instance.
        # \param self The \e %FragmentLink instance to initialize.
        # \param frag1_idx 
        # \param frag2_idx 
        # \param bond 
        # \param rule_id 
        # \param atom1_label 
        # \param atom2_label 
        #
        def __init__(self: object, frag1_idx: int, frag2_idx: int, bond: Bond, rule_id: int, atom1_label: int, atom2_label: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %FragmentLink instance this method is called upon.
        #
        # Different Python \e %FragmentLink instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentLink instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: FragmentLink) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentLink instance \a link.
        # \param self The \e %FragmentLink instance this method is called upon.
        # \param link The \e %FragmentLink instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: FragmentLink, link: FragmentLink) -> FragmentLink: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getFragment1Index(self: FragmentLink) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getFragment2Index(self: FragmentLink) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getBond(self: FragmentLink) -> Bond: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getRuleID(self: FragmentLink) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getAtom1Label(self: FragmentLink) -> int: pass

        ##
        # \brief 
        # \param self The \e %FragmentLink instance this method is called upon.
        # \return 
        #
        def getAtom2Label(self: FragmentLink) -> int: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        fragment1Index = property(getFragment1Index)

        ##
        # \brief 
        #
        fragment2Index = property(getFragment2Index)

        ##
        # \brief 
        #
        bond = property(getBond)

        ##
        # \brief 
        #
        ruleID = property(getRuleID)

        ##
        # \brief 
        #
        atom1Label = property(getAtom1Label)

        ##
        # \brief 
        #
        atom2Label = property(getAtom2Label)

    ##
    # \brief Initializes the \e %FragmentGenerator instance.
    # \param self The \e %FragmentGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FragmentGenerator instance.
    # \param self The \e %FragmentGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: FragmentGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FragmentGenerator instance this method is called upon.
    #
    # Different Python \e %FragmentGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FragmentGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentGenerator instance \a gen.
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param gen The \e %FragmentGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FragmentGenerator, gen: FragmentGenerator) -> FragmentGenerator: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param match_ptn 
    # \param rule_id 
    #
    def addFragmentationRule(self: FragmentGenerator, match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param rule 
    #
    def addFragmentationRule(self: FragmentGenerator, rule: FragmentationRuler) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param idx 
    #
    def removeFragmentationRule(self: FragmentGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFragmentationRule(self: FragmentGenerator, idx: int) -> FragmentationRuler: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    #
    def clearFragmentationRules(self: FragmentGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \return 
    #
    def getNumFragmentationRules(self: FragmentGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param match_ptn 
    # \param rule_id 
    #
    def addExcludePattern(self: FragmentGenerator, match_ptn: MolecularGraph, rule_id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param excl_ptn 
    #
    def addExcludePattern(self: FragmentGenerator, excl_ptn: ExcludePattern) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param idx 
    #
    def removeExcludePattern(self: FragmentGenerator, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getExcludePattern(self: FragmentGenerator, idx: int) -> ExcludePattern: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    #
    def clearExcludePatterns(self: FragmentGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \return 
    #
    def getNumExcludePatterns(self: FragmentGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param func 
    #
    def setFragmentFilterFunction(self: FragmentGenerator, func: BoolConstMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \return 
    #
    def getFragmentFilterFunction(self: FragmentGenerator) -> BoolConstMolecularGraphFunctor: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param molgraph 
    # \param frag_list 
    # \param append 
    #
    def generate(self: FragmentGenerator, molgraph: MolecularGraph, frag_list: FragmentList, append: bool = False) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFragmentLink(self: FragmentGenerator, idx: int) -> FragmentLink: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \return 
    #
    def getNumFragmentLinks(self: FragmentGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \return 
    #
    def includeSplitBonds(self: FragmentGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FragmentGenerator instance this method is called upon.
    # \param include 
    #
    def includeSplitBonds(self: FragmentGenerator, include: bool) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    fragmentFilterFunction = property(getFragmentFilterFunction, setFragmentFilterFunction)

    ##
    # \brief FIXME!
    #
    incSplitBonds = property(getIncSplitBonds, setIncSplitBonds)

    ##
    # \brief 
    #
    numFragmentationRules = property(getNumFragmentationRules)

    ##
    # \brief 
    #
    numExcludePatterns = property(getNumExcludePatterns)

    ##
    # \brief 
    #
    numFragmentLinks = property(getNumFragmentLinks)
