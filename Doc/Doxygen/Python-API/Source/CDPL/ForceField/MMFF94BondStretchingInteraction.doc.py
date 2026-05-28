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
# \brief Stores parameters for a single MMFF94 bond-stretching interaction between two bonded atoms.
# 
class MMFF94BondStretchingInteraction(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %MMFF94BondStretchingInteraction instance \a iactn.
    # \param iactn The \c %MMFF94BondStretchingInteraction instance to copy.
    # 
    def __init__(iactn: MMFF94BondStretchingInteraction) -> None: pass

    ##
    # \brief Constructs the bond-stretching interaction parameter set.
    # 
    # \param atom1_idx The zero-based index of the first bonded atom.
    # \param atom2_idx The zero-based index of the second bonded atom.
    # \param bond_type_idx The MMFF94 bond type index (0 or 1).
    # \param force_const The bond-stretching force constant.
    # \param ref_length The reference bond length \f$ r_0 \f$.
    # 
    def __init__(atom1_idx: int, atom2_idx: int, bond_type_idx: int, force_const: float, ref_length: float) -> None: pass

    ##
    # \brief Returns the zero-based index of the first bonded atom.
    # 
    # \return The first atom index.
    # 
    def getAtom1Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the second bonded atom.
    # 
    # \return The second atom index.
    # 
    def getAtom2Index() -> int: pass

    ##
    # \brief Returns the MMFF94 bond type index of this bond.
    # 
    # \return The bond type index (0 or 1).
    # 
    def getBondTypeIndex() -> int: pass

    ##
    # \brief Returns the bond-stretching force constant.
    # 
    # \return The force constant.
    # 
    def getForceConstant() -> float: pass

    ##
    # \brief Returns the reference bond length.
    # 
    # \return The reference bond length \f$ r_0 \f$.
    # 
    def getReferenceLength() -> float: pass

    ##
    # \brief Sets the reference bond length.
    # 
    # \param length The new reference bond length \f$ r_0 \f$.
    # 
    def setReferenceLength(length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94BondStretchingInteraction instance \a iactn.
    # \param iactn The \c %MMFF94BondStretchingInteraction instance to copy.
    # \return \a self
    # 
    def assign(iactn: MMFF94BondStretchingInteraction) -> MMFF94BondStretchingInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94BondStretchingInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94BondStretchingInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    atom1Index = property(getAtom1Index)

    atom2Index = property(getAtom2Index)

    bondTypeIndex = property(getBondTypeIndex)

    forceConstant = property(getForceConstant)

    referenceLength = property(getReferenceLength, setReferenceLength)
