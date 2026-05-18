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
# \brief Calculator that fills a spatial grid with per-cell buriedness scores derived from GRAIL.BuriednessScore.
# 
# For each grid cell, the buriedness score with respect to the surrounding atoms is computed and stored. The configurable parameters (probe radius, minimum van der Waals surface distance, number of test rays) are forwarded to the underlying BuriednessScore instance.
# 
class BuriednessGridCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BuriednessGridCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>BuriednessGridCalculator</tt> instance <em>calc</em>.
    # 
    # \param calc The <tt>BuriednessGridCalculator</tt> to copy.
    # 
    def __init__(calc: BuriednessGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %BuriednessGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %BuriednessGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param calc The other <tt>BuriednessGridCalculator</tt> instance.
    # 
    # \return \a self
    # 
    def assign(calc: BuriednessGridCalculator) -> BuriednessGridCalculator: pass

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
    # \brief Sets the probe sphere radius used by the underlying GRAIL.BuriednessScore.
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
    # \brief Sets the number of test rays cast from each grid cell.
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
    # \brief Specifies a function for the retrieval of atom 3D-coordinates for grid calculation.
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
    # \brief Calculates the buriedness value at each cell of <em>grid</em> for the given atoms.
    # 
    # \param atoms The atoms used as the environment for the buriedness calculation.
    # \param grid The output grid populated with per-cell buriedness scores.
    # 
    def calculate(atoms: Chem.AtomContainer, grid: Grid.DSpatialGrid) -> None: pass

    objectID = property(getObjectID)

    probeRadius = property(getProbeRadius, setProbeRadius)

    minVdWSurfaceDistance = property(getMinVdWSurfaceDistance, setMinVdWSurfaceDistance)

    numTestRays = property(getNumTestRays, setNumTestRays)

    atom3DCoordinatesFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
