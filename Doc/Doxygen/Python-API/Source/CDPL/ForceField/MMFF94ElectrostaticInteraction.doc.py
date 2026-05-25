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
# \brief A single MMFF94 electrostatic interaction between two non-bonded atoms.
# 
# The MMFF94 electrostatic-energy contribution between two atoms with partial charges \f$ q_i \f$ and \f$ q_j \f$ separated by distance <em>r</em> is \f$ E_q = f \frac{q_i q_j}{\varepsilon (r + \delta)^n} \f$ where <em>f</em> is a scaling factor (e.g. 0.75 for 1-4 pairs), \f$ \varepsilon \f$ the dielectric constant, <em>n</em> the distance exponent and \f$ \delta = 0.05 \f$ &Aring; the MMFF94 buffer.
# 
class MMFF94ElectrostaticInteraction(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %MMFF94ElectrostaticInteraction instance \a iactn.
    # \param iactn The \c %MMFF94ElectrostaticInteraction instance to copy.
    # 
    def __init__(iactn: MMFF94ElectrostaticInteraction) -> None: pass

    ##
    # \brief Constructs the electrostatic interaction record.
    # 
    # \param atom1_idx The zero-based index of the first atom.
    # \param atom2_idx The zero-based index of the second atom.
    # \param atom1_chg The partial charge \f$ q_i \f$ of the first atom.
    # \param atom2_chg The partial charge \f$ q_j \f$ of the second atom.
    # \param scale_fact The scaling factor <em>f</em> applied to the energy contribution (e.g. 0.75 for 1-4 pairs).
    # \param de_const The dielectric constant \f$ \varepsilon \f$.
    # \param dist_expo The distance exponent <em>n</em>.
    # 
    def __init__(atom1_idx: int, atom2_idx: int, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> None: pass

    ##
    # \brief Returns the zero-based index of the first atom.
    # 
    # \return The first atom index.
    # 
    def getAtom1Index() -> int: pass

    ##
    # \brief Returns the zero-based index of the second atom.
    # 
    # \return The second atom index.
    # 
    def getAtom2Index() -> int: pass

    ##
    # \brief Returns the partial charge of the first atom.
    # 
    # \return The charge \f$ q_i \f$.
    # 
    def getAtom1Charge() -> float: pass

    ##
    # \brief Returns the partial charge of the second atom.
    # 
    # \return The charge \f$ q_j \f$.
    # 
    def getAtom2Charge() -> float: pass

    ##
    # \brief Returns the scaling factor applied to the energy contribution.
    # 
    # \return The scaling factor <em>f</em>.
    # 
    def getScalingFactor() -> float: pass

    ##
    # \brief Returns the dielectric constant used by this interaction.
    # 
    # \return The dielectric constant \f$ \varepsilon \f$.
    # 
    def getDielectricConstant() -> float: pass

    ##
    # \brief Returns the distance exponent of the electrostatic potential.
    # 
    # \return The distance exponent <em>n</em>.
    # 
    def getDistanceExponent() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94ElectrostaticInteraction instance \a iactn.
    # \param iactn The \c %MMFF94ElectrostaticInteraction instance to copy.
    # \return \a self
    # 
    def assign(iactn: MMFF94ElectrostaticInteraction) -> MMFF94ElectrostaticInteraction: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94ElectrostaticInteraction instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94ElectrostaticInteraction instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    atom1Index = property(getAtom1Index)

    atom2Index = property(getAtom2Index)

    atom1Charge = property(getAtom1Charge)

    atom2Charge = property(getAtom2Charge)

    scalingFactor = property(getScalingFactor)

    dielectricConstant = property(getDielectricConstant)

    distanceExponent = property(getDistanceExponent)
