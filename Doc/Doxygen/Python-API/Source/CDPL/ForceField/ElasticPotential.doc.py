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
# \brief Stores parameters for a harmonic distance-restraint potential between a pair of atoms.
# 
# \see ForceField.calcElasticPotentialEnergy() 
# 
# \since 1.1
# 
class ElasticPotential(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %ElasticPotential instance \a pot.
    # \param pot The \c %ElasticPotential instance to copy.
    # 
    def __init__(pot: ElasticPotential) -> None: pass

    ##
    # \brief Constructs the elastic potential between atoms <em>atom1_idx</em> and <em>atom2_idx</em> with the specified force constant and reference length.
    # 
    # \param atom1_idx The zero-based index of the first restrained atom.
    # \param atom2_idx The zero-based index of the second restrained atom.
    # \param force_const The force constant <em>k</em> of the harmonic potential.
    # \param ref_length The reference length \f$ r_0 \f$ of the harmonic potential.
    # 
    def __init__(atom1_idx: int, atom2_idx: int, force_const: float, ref_length: float) -> None: pass

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
    # \brief Returns the force constant of the potential.
    # 
    # \return The force constant <em>k</em>.
    # 
    def getForceConstant() -> float: pass

    ##
    # \brief Returns the reference length of the potential.
    # 
    # \return The reference length \f$ r_0 \f$.
    # 
    def getReferenceLength() -> float: pass

    ##
    # \brief Sets the reference length of the potential.
    # 
    # \param length The new reference length \f$ r_0 \f$.
    # 
    def setReferenceLength(length: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ElasticPotential instance \a pot.
    # \param pot The \c %ElasticPotential instance to copy.
    # \return \a self
    # 
    def assign(pot: ElasticPotential) -> ElasticPotential: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ElasticPotential instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ElasticPotential instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    objectID = property(getObjectID)

    atom1Index = property(getAtom1Index)

    atom2Index = property(getAtom2Index)

    forceConstant = property(getForceConstant)

    referenceLength = property(getReferenceLength, setReferenceLength)
