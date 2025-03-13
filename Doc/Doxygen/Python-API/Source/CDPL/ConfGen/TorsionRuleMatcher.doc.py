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
class TorsionRuleMatcher(Boost.Python.instance):

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TorsionRuleMatcher instance.
    # \param lib 
    # 
    def __init__(lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param unique 
    #
    def findUniqueMappingsOnly(unique: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def findUniqueMappingsOnly() -> bool: pass

    ##
    # \brief 
    # \param all 
    #
    def findAllRuleMappings(all: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def findAllRuleMappings() -> bool: pass

    ##
    # \brief 
    # \param stop 
    #
    def stopAtFirstMatchingRule(stop: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def stopAtFirstMatchingRule() -> bool: pass

    ##
    # \brief 
    # \param lib 
    #
    def setTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTorsionLibrary() -> TorsionLibrary: pass

    ##
    # \brief Returns the number of stored torsion rule matches found by calls to findMatches().
    # 
    # \return The number of stored torsion rule matches.
    # 
    def getNumMatches() -> int: pass

    ##
    # \brief Returns a reference to the stored torsion rule match object at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the torsion rule match object to return.
    # 
    # \return A reference to the torsion rule match object at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if no torsion rule matches are available or <em>idx</em> is not in the range [0, getNumMatches() - 1].
    # 
    def getMatch(idx: int) -> TorsionRuleMatch: pass

    ##
    # \brief 
    # \param bond 
    # \param molgraph 
    # \param append 
    # \return 
    #
    def findMatches(bond: Chem.Bond, molgraph: Chem.MolecularGraph, append: bool = False) -> bool: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionRuleMatcher instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionRuleMatcher instances \e a and \e b reference different C++ objects. 
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
    def __getitem__(idx: int) -> TorsionRuleMatch: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    numMatches = property(getNumMatches)

    uniqueMappingsOnly = property(findUniqueMappingsOnly, findUniqueMappingsOnly)

    allRuleMappings = property(findAllRuleMappings, findAllRuleMappings)

    onlyFirstMatchingRule = property(stopAtFirstMatchingRule, stopAtFirstMatchingRule)

    torsionLibrary = property(getTorsionLibrary, setTorsionLibrary)
