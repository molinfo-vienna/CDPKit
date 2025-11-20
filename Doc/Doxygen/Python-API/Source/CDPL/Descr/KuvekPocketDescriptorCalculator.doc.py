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
# \brief Implements the algorithm devised by Kuvek et al. [\ref KBPD] for the calculation of receptor binding pocket shape and surface electrostatics descriptors.
# 
# \since 1.3
# 
class KuvekPocketDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_PROBE_RADIUS = 20.0

    ##
    # \brief 
    #
    DEF_MAX_ATOM_TO_SPHERE_SURF_DIST = 2.0

    ##
    # \brief 
    #
    DEF_NUM_TEST_VECTORS = 492

    ##
    # \brief Initializes the \e %KuvekPocketDescriptorCalculator instance.
    # \param sphere_radius 
    # \param num_test_vecs 
    # \param max_atom_to_sphr_surf_dist 
    # 
    def __init__(sphere_radius: float = 20.0, num_test_vecs: int = 492, max_atom_to_sphr_surf_dist: float = 492) -> None: pass

    ##
    # \brief Initializes a copy of the \e %KuvekPocketDescriptorCalculator instance \a calc.
    # \param calc The \e %KuvekPocketDescriptorCalculator instance to copy.
    # 
    def __init__(calc: KuvekPocketDescriptorCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %KuvekPocketDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %KuvekPocketDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %KuvekPocketDescriptorCalculator instance \a calc.
    # \param calc The \c %KuvekPocketDescriptorCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: KuvekPocketDescriptorCalculator) -> KuvekPocketDescriptorCalculator: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: Chem.Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom3DCoordinatesFunction() -> Chem.Atom3DCoordinatesFunction: pass

    ##
    # \brief Specifies a function for the retrieval of atom charges.
    # 
    # \param func The atom charge retrieval function.
    # 
    # \note By default, formal charges will be used.
    # 
    def setAtomChargeFunction(func: ForceField.MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomChargeFunction() -> ForceField.MMFF94AtomChargeFunction: pass

    ##
    # \brief 
    # \param radius 
    #
    def setSphereRadius(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSphereRadius() -> float: pass

    ##
    # \brief 
    # \param radius 
    #
    def setMaxAtomToSphereSurfaceDistance(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAtomToSphereSurfaceDistance() -> float: pass

    ##
    # \brief 
    # \param num_vectors 
    #
    def setNumTestVectors(num_vectors: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumTestVectors() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getTestVector(idx: int) -> Math.Vector3D: pass

    ##
    # \brief 
    # \param sphere_ctr 
    # \param atoms 
    # \param descr 
    #
    def calculate(sphere_ctr: Math.Vector3D, atoms: Chem.AtomContainer, descr: Math.DVector) -> None: pass

    objectID = property(getObjectID)

    sphereRadius = property(getSphereRadius, setSphereRadius)

    maxAtomToSphereSurfaceDistance = property(getMaxAtomToSphereSurfaceDistance, setMaxAtomToSphereSurfaceDistance)

    numTestVectors = property(getNumTestVectors, setNumTestVectors)

    atomCoordsFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)

    atomChargeFunction = property(getAtomChargeFunction, setAtomChargeFunction)
