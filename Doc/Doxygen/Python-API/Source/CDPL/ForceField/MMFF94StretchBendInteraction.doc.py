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
# \brief Stores paramters for a single MMFF94 stretch-bend coupling interaction.
# 
# \see [\ref MMFF94]
# 
class MMFF94StretchBendInteraction(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %MMFF94StretchBendInteraction instance \a iactn.
    # \param iactn The \c %MMFF94StretchBendInteraction instance to copy.
    # 
    def __init__(iactn: MMFF94StretchBendInteraction) -> None: pass

    ##
    # \brief Constructs the stretch-bend interaction parameter set.
    # 
    # \param term_atom1_idx The zero-based index of the first terminal atom <em>i</em>.
    # \param ctr_atom_idx The zero-based index of the central atom <em>j</em>.
    # \param term_atom2_idx The zero-based index of the second terminal atom <em>k</em>.
    # \param sb_type_idx The MMFF94 stretch-bend type index (0-11).
    # \param ref_angle The reference angle \f$ \Theta_0 \f$ (in degrees).
    # \param ref_length1 The reference length \f$ r_{ij,0} \f$ of bond <em>i-<em>j</em>.</em>
    # \param ref_length2 The reference length \f$ r_{jk,0} \f$ of bond <em>j-<em>k</em>.</em>
    # \param ijk_force_const The force constant \f$ k_{ijk} \f$ coupling <em>i-<em>j</em> stretching</em> to the angle.
    # \param kji_force_const The force constant \f$ k_{kji} \f$ coupling <em>j-<em>k</em> stretching</em> to the angle.
    # 
    def __init__(term_atom1_idx: int, ctr_atom_idx: int, term_atom2_idx: int, sb_type_idx: int, ref_angle: float, ref_length1: float, ref_length2: float, ijk_force_const: float, kji_force_const: float) -> None: pass

    ##
    # \brief Returns the zero-based index of the first terminal atom <em>i</em>.
    # 
    # \return The first terminal-atom index.
    # 
    def getTerminalAtom1Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the second terminal atom <em>k</em>.
    # 
    # \return The second terminal-atom index.
    # 
    def getTerminalAtom2Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the central atom <em>j</em>.
    # 
    # \return The center-atom index.
    # 
    def getCenterAtomIndex() -> int: pass

    ##
    # \brief Returns the zero-based index of the first terminal atom (alias for getTerminalAtom1Index()).
    # 
    # \return The first terminal-atom index.
    # 
    def getAtom1Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the central atom (alias for getCenterAtomIndex()).
    # 
    # \return The center-atom index.
    # 
    def getAtom2Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the second terminal atom (alias for getTerminalAtom2Index()).
    # 
    # \return The second terminal-atom index.
    # 
    def getAtom3Index() -> int: pass

    ##
    # \brief Returns the MMFF94 stretch-bend type index.
    # 
    # \return The stretch-bend type index (0-11).
    # 
    def getStretchBendTypeIndex() -> int: pass

    ##
    # \brief Returns the force constant coupling <em>i-<em>j</em> bond</em> stretching with the central angle.
    # 
    # \return The force constant \f$ k_{ijk} \f$.
    # 
    def getIJKForceConstant() -> float: pass

    ##
    # \brief Returns the force constant coupling <em>j-<em>k</em> bond</em> stretching with the central angle.
    # 
    # \return The force constant \f$ k_{kji} \f$.
    # 
    def getKJIForceConstant() -> float: pass

    ##
    # \brief Returns the reference angle.
    # 
    # \return The reference angle \f$ \Theta_0 \f$ (in degrees).
    # 
    def getReferenceAngle() -> float: pass

    ##
    # \brief Sets the reference angle.
    # 
    # \param angle The new reference angle \f$ \Theta_0 \f$ (in degrees).
    # 
    def setReferenceAngle(angle: float) -> None: pass

    ##
    # \brief Returns the reference length of bond <em>i-<em>j</em>.</em>
    # 
    # \return The reference length \f$ r_{ij,0} \f$.
    # 
    def getReferenceLength1() -> float: pass

    ##
    # \brief Sets the reference length of bond <em>i-<em>j</em>.</em>
    # 
    # \param length The new reference length \f$ r_{ij,0} \f$.
    # 
    def setReferenceLength1(length: float) -> None: pass

    ##
    # \brief Returns the reference length of bond <em>j-<em>k</em>.</em>
    # 
    # \return The reference length \f$ r_{jk,0} \f$.
    # 
    def getReferenceLength2() -> float: pass

    ##
    # \brief Sets the reference length of bond <em>j-<em>k</em>.</em>
    # 
    # \param length The new reference length \f$ r_{jk,0} \f$.
    # 
    def setReferenceLength2(length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94StretchBendInteraction instance \a iactn.
    # \param iactn The \c %MMFF94StretchBendInteraction instance to copy.
    # \return \a self
    # 
    def assign(iactn: MMFF94StretchBendInteraction) -> MMFF94StretchBendInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94StretchBendInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94StretchBendInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    termAtom1Index = property(getTerminalAtom1Index)

    termAtom2Index = property(getTerminalAtom2Index)

    ctrAtomIndex = property(getCenterAtomIndex)

    atom1Index = property(getAtom1Index)

    atom2Index = property(getAtom2Index)

    atom3Index = property(getAtom3Index)

    stretchBendTypeIndex = property(getStretchBendTypeIndex)

    referenceAngle = property(getReferenceAngle, setReferenceAngle)

    referenceLength1 = property(getReferenceLength1, setReferenceLength1)

    referenceLength2 = property(getReferenceLength2, setReferenceLength2)

    ijkForceConstant = property(getIJKForceConstant)

    kjiForceConstant = property(getKJIForceConstant)
