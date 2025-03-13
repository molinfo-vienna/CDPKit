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
class TorsionRuleMatch(Boost.Python.instance):

    ##
    # \brief 
    #
    class AtomArray(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
        # \param atom The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(atom: Chem.Atom) -> bool: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Chem.Atom: pass

    ##
    # \brief Initializes a copy of the \e %TorsionRuleMatch instance \a match.
    # \param match The \e %TorsionRuleMatch instance to copy.
    # 
    def __init__(match: TorsionRuleMatch) -> None: pass

    ##
    # \brief Initializes the \e %TorsionRuleMatch instance.
    # \param rule 
    # \param bond 
    # \param atom1 
    # \param atom2 
    # \param atom3 
    # \param atom4 
    # 
    def __init__(rule: TorsionRule, bond: Chem.Bond, atom1: Chem.Atom, atom2: Chem.Atom, atom3: Chem.Atom, atom4: Chem.Atom) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionRuleMatch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionRuleMatch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getAtoms() -> AtomArray: pass

    ##
    # \brief 
    # \return 
    #
    def getBond() -> Chem.Bond: pass

    ##
    # \brief 
    # \return 
    #
    def getRule() -> TorsionRule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TorsionRuleMatch instance \a match.
    # \param match The \c %TorsionRuleMatch instance to copy.
    # \return \a self
    # 
    def assign(match: TorsionRuleMatch) -> TorsionRuleMatch: pass

    objectID = property(getObjectID)

    rule = property(getRule)

    bond = property(getBond)

    atoms = property(getAtoms)
