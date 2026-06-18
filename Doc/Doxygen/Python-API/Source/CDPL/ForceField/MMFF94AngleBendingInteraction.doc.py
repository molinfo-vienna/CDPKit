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
# \brief Stores parameters for a single MMFF94 angle-bending interaction defined over an atom triplet.
# 
# \see [\ref MMFF94]
# 
class MMFF94AngleBendingInteraction(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %MMFF94AngleBendingInteraction instance \a iactn.
    # \param iactn The \c %MMFF94AngleBendingInteraction instance to copy.
    # 
    def __init__(iactn: MMFF94AngleBendingInteraction) -> None: pass

    ##
    # \brief Constructs the angle-bending interaction parameter set.
    # 
    # \param term_atom1_idx The zero-based index of the first terminal atom.
    # \param ctr_atom_idx The zero-based index of the central (vertex) atom.
    # \param term_atom2_idx The zero-based index of the second terminal atom.
    # \param angle_type_idx The MMFF94 angle type index (0-8).
    # \param linear <tt>True</tt> if the equilibrium angle is near linear (180&deg;).
    # \param force_const The angle-bending force constant.
    # \param ref_angle The reference angle \f$ \Theta_0 \f$ (in degrees).
    # 
    def __init__(term_atom1_idx: int, ctr_atom_idx: int, term_atom2_idx: int, angle_type_idx: int, linear: bool, force_const: float, ref_angle: float) -> None: pass

    ##
    # \brief Returns the zero-based index of the first terminal atom.
    # 
    # \return The first terminal-atom index.
    # 
    def getTerminalAtom1Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the second terminal atom.
    # 
    # \return The second terminal-atom index.
    # 
    def getTerminalAtom2Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the central (vertex) atom.
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
    # \brief Returns the MMFF94 angle type index.
    # 
    # \return The angle type index (0-8).
    # 
    def getAngleTypeIndex() -> int: pass

    ##
    # \brief Tells whether the equilibrium angle is near linear (180&deg;).
    # 
    # \return <tt>True</tt> if the angle is near linear, and <tt>False</tt> otherwise.
    # 
    def isLinearAngle() -> bool: pass

    ##
    # \brief Returns the angle-bending force constant.
    # 
    # \return The force constant.
    # 
    def getForceConstant() -> float: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94AngleBendingInteraction instance \a iactn.
    # \param iactn The \c %MMFF94AngleBendingInteraction instance to copy.
    # \return \a self
    # 
    def assign(iactn: MMFF94AngleBendingInteraction) -> MMFF94AngleBendingInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94AngleBendingInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94AngleBendingInteraction instances \e a and \e b reference different C++ objects. 
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

    angleTypeIndex = property(getAngleTypeIndex)

    linear = property(isLinearAngle)

    forceConstant = property(getForceConstant)

    referenceAngle = property(getReferenceAngle, setReferenceAngle)
