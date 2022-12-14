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
class BuriednessScore(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_NUM_TEST_RAYS = 200

    ##
    # \brief 
    #
    DEF_PROBE_RADIUS = 8.0

    ##
    # \brief Initializes the \e %BuriednessScore instance.
    # \param score 
    #
    def __init__(score: BuriednessScore) -> None: pass

    ##
    # \brief Initializes the \e %BuriednessScore instance.
    # \param probe_radius 
    # \param min_vdw_surf_dist 
    # \param num_test_rays 
    #
    def __init__(probe_radius: float = 8.0, min_vdw_surf_dist: float = 1.0, num_test_rays: float = 200) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %BuriednessScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BuriednessScore instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param dist 
    #
    def setMinVdWSurfaceDistance(dist: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinVdWSurfaceDistance() -> float: pass

    ##
    # \brief 
    # \param radius 
    #
    def setProbeRadius(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getProbeRadius() -> float: pass

    ##
    # \brief 
    # \param num_rays 
    #
    def setNumTestRays(num_rays: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumTestRays() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtom3DCoordinatesFunction(func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom3DCoordinatesFunction() -> Atom3DCoordinatesFunction: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BuriednessScore instance \a score.
    # \param score The \e %BuriednessScore instance to copy.
    # \return \a self
    #
    def assign(score: BuriednessScore) -> BuriednessScore: pass

    ##
    # \brief 
    # \param pos 
    # \param atoms 
    # \return 
    #
    def __call__(pos: CDPL.Math.Vector3D, atoms: AtomContainer) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    probeRadius = property(getProbeRadius, setProbeRadius)

    ##
    # \brief 
    #
    minVdWSurfaceDistance = property(getMinVdWSurfaceDistance, setMinVdWSurfaceDistance)

    ##
    # \brief 
    #
    numTestRays = property(getNumTestRays, setNumTestRays)

    ##
    # \brief FIXME!
    #
    atomCoordinatesFunction = property(getAtomCoordinatesFunction, setAtomCoordinatesFunction)
