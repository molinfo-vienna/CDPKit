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
# \brief Functor for the calculation of the <em>buriedness</em> of a 3D query position with respect to the surrounding atoms.
# 
# The buriedness score is computed by casting a configurable number of test rays evenly distributed over the surface of a probe sphere centered at the query position. For each ray it is checked whether the ray hits an atom of the input container (the van der Waals surface, expanded by a minimum distance) within the probe sphere. The returned score is the fraction of rays that hit an atom and thus reflects how surrounded by the atoms the query position is.
# 
class BuriednessScore(Boost.Python.instance):

    ##
    # \brief Default number of test rays cast from the query position.
    # 
    DEF_NUM_TEST_RAYS = 200

    ##
    # \brief Default probe sphere radius.
    # 
    DEF_PROBE_RADIUS = 8.0

    ##
    # \brief Initializes a copy of the \c %BuriednessScore instance \a score.
    # \param score The \c %BuriednessScore instance to copy.
    # 
    def __init__(score: BuriednessScore) -> None: pass

    ##
    # \brief Constructs a <tt>BuriednessScore</tt> instance with the given configuration.
    # 
    # \param probe_radius The probe sphere radius.
    # \param min_vdw_surf_dist The minimum distance to the van der Waals surface of an atom.
    # \param num_test_rays The number of rays used in the calculation.
    # 
    def __init__(probe_radius: float = 8.0, min_vdw_surf_dist: float = 1.0, num_test_rays: float = 200) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %BuriednessScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %BuriednessScore instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the minimum required distance between a ray and the van der Waals surface of an atom.
    # 
    # \param dist The minimum distance to the van der Waals surface.
    # 
    def setMinVdWSurfaceDistance(dist: float) -> None: pass

    ##
    # \brief Returns the currently configured minimum distance to the van der Waals surface of an atom.
    # 
    # \return The configured minimum distance to the van der Waals surface.
    # 
    def getMinVdWSurfaceDistance() -> float: pass

    ##
    # \brief Sets the probe sphere radius.
    # 
    # \param radius The probe sphere radius.
    # 
    def setProbeRadius(radius: float) -> None: pass

    ##
    # \brief Returns the currently configured probe sphere radius.
    # 
    # \return The configured probe sphere radius.
    # 
    def getProbeRadius() -> float: pass

    ##
    # \brief Sets the number of test rays cast from the query position.
    # 
    # \param num_rays The number of test rays.
    # 
    def setNumTestRays(num_rays: int) -> None: pass

    ##
    # \brief Returns the currently configured number of test rays.
    # 
    # \return The configured number of test rays.
    # 
    def getNumTestRays() -> int: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates for buriedness calculation.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: Chem.Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function used for the retrieval of atom 3D-coordinates.
    # 
    # \return The configured atom 3D-coordinates function.
    # 
    def getAtom3DCoordinatesFunction() -> Chem.Atom3DCoordinatesFunction: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %BuriednessScore instance \a score.
    # \param score The \c %BuriednessScore instance to copy.
    # \return \a self
    # 
    def assign(score: BuriednessScore) -> BuriednessScore: pass

    ##
    # \brief Calculates the buriedness score of the query position <em>pos</em> with respect to <em>atoms</em>.
    # 
    # \param pos The 3D position for which to calculate the buriedness score.
    # \param atoms The surrounding atoms used in the calculation.
    # 
    # \return The calculated buriedness score, a value in the range <em>[0, 1]</em>.
    # 
    def __call__(pos: Math.Vector3D, atoms: Chem.AtomContainer) -> float: pass

    objectID = property(getObjectID)

    probeRadius = property(getProbeRadius, setProbeRadius)

    minVdWSurfaceDistance = property(getMinVdWSurfaceDistance, setMinVdWSurfaceDistance)

    numTestRays = property(getNumTestRays, setNumTestRays)

    atomCoordsFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
