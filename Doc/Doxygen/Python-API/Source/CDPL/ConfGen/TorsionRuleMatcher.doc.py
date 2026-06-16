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
# \brief Finds torsion rules from a ConfGen.TorsionLibrary instance that match a given rotatable bond.
# 
# For a queried bond in a molecular graph the matcher iterates the configured torsion library (top-down through torsion categories) and reports every rule whose central bond pattern matches the queried bond. Each match is stored as a ConfGen.TorsionRuleMatch object providing the four matching atoms, the matched rule and the underlying atom/bond mapping.
# 
class TorsionRuleMatcher(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>TorsionRuleMatcher</tt> instance without an associated torsion library.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>TorsionRuleMatcher</tt> instance and associates it with <em>lib</em>.
    # 
    # \param lib The torsion library to query.
    # 
    def __init__(lib: TorsionLibrary) -> None: pass

    ##
    # \brief Specifies whether only unique substructure mappings shall be reported during matching.
    # 
    # \param unique If <tt>True</tt>, only one of multiple equivalent mappings is reported per rule.
    # 
    def findUniqueMappingsOnly(unique: bool) -> None: pass

    ##
    # \brief Tells whether only unique substructure mappings are reported during matching.
    # 
    # \return <tt>True</tt> if only unique mappings are reported, and <tt>False</tt> otherwise.
    # 
    def findUniqueMappingsOnly() -> bool: pass

    ##
    # \brief Specifies whether all matching rules shall be reported (instead of just the most-specific one).
    # 
    # \param all If <tt>True</tt>, every matching rule across all categories is reported.
    # 
    def findAllRuleMappings(all: bool) -> None: pass

    ##
    # \brief Tells whether all matching rules are reported during matching.
    # 
    # \return <tt>True</tt> if all matching rules are reported, and <tt>False</tt> otherwise.
    # 
    def findAllRuleMappings() -> bool: pass

    ##
    # \brief Specifies whether the matching process shall stop at the first rule that produces matches.
    # 
    # \param stop If <tt>True</tt>, matching stops as soon as a rule yields at least one match.
    # 
    def stopAtFirstMatchingRule(stop: bool) -> None: pass

    ##
    # \brief Tells whether matching stops at the first rule that produces matches.
    # 
    # \return <tt>True</tt> if matching stops at the first matching rule, and <tt>False</tt> otherwise.
    # 
    def stopAtFirstMatchingRule() -> bool: pass

    ##
    # \brief Sets the torsion library to query.
    # 
    # \param lib The new torsion library.
    # 
    def setTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief Returns the currently associated torsion library.
    # 
    # \return A reference to the torsion library smart reference.
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
    # \brief Searches the associated torsion library for rules that match the bond <em>bond</em> of the molecular graph <em>molgraph</em>.
    # 
    # \param bond The rotatable bond for which matching torsion rules are sought.
    # \param molgraph The molecular graph the bond belongs to.
    # \param append If <tt>True</tt>, new matches are appended to the previously stored ones. Otherwise, stored matches are cleared first.
    # 
    # \return <tt>True</tt> if at least one matching rule was found, and <tt>False</tt> otherwise.
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
