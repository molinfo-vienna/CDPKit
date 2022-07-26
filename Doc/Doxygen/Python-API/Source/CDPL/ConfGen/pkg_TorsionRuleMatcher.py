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
class TorsionRuleMatcher(Boost.Python.instance):

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    # \param self The \e %TorsionRuleMatcher instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    # \param self The \e %TorsionRuleMatcher instance to initialize.
    # \param lib 
    #
    def __init__(self: object, lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param unique 
    #
    def findUniqueMappingsOnly(self: TorsionRuleMatcher, unique: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def findUniqueMappingsOnly(self: TorsionRuleMatcher) -> bool: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param all 
    #
    def findAllRuleMappings(self: TorsionRuleMatcher, all: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def findAllRuleMappings(self: TorsionRuleMatcher) -> bool: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param stop 
    #
    def stopAtFirstMatchingRule(self: TorsionRuleMatcher, stop: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def stopAtFirstMatchingRule(self: TorsionRuleMatcher) -> bool: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param lib 
    #
    def setTorsionLibrary(self: TorsionRuleMatcher, lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def getTorsionLibrary(self: TorsionRuleMatcher) -> TorsionLibrary: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def getNumMatches(self: TorsionRuleMatcher) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getMatch(self: TorsionRuleMatcher, idx: int) -> TorsionRuleMatch: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param bond 
    # \param molgraph 
    # \param append 
    # \return 
    #
    def findMatches(self: TorsionRuleMatcher, bond: CDPL.Chem.Bond, molgraph: CDPL.Chem.MolecularGraph, append: bool = False) -> bool: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    #
    # Different Python \e %TorsionRuleMatcher instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TorsionRuleMatcher instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: TorsionRuleMatcher) -> int: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: TorsionRuleMatcher, idx: int) -> TorsionRuleMatch: pass

    ##
    # \brief 
    # \param self The \e %TorsionRuleMatcher instance this method is called upon.
    # \return 
    #
    def __len__(self: TorsionRuleMatcher) -> int: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numMatches = property(getNumMatches)

    ##
    # \brief FIXME!
    #
    uniqueMappingsOnly = property(getUniqueMappingsOnly, setUniqueMappingsOnly)

    ##
    # \brief FIXME!
    #
    allRuleMappings = property(getAllRuleMappings, setAllRuleMappings)

    ##
    # \brief FIXME!
    #
    onlyFirstMatchingRule = property(getOnlyFirstMatchingRule, setOnlyFirstMatchingRule)

    ##
    # \brief 
    #
    torsionLibrary = property(getTorsionLibrary, setTorsionLibrary)
