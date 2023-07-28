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
# \brief BuriednessGridCalculator.
# 
class BuriednessGridCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BuriednessGridCalculator instance.
    # \param self The \e %BuriednessGridCalculator instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BuriednessGridCalculator instance.
    # \param self The \e %BuriednessGridCalculator instance to initialize.
    # \param calc 
    # 
    def __init__(calc: BuriednessGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # 
    # Different Python \e %BuriednessGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BuriednessGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BuriednessGridCalculator instance \a calc.
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param calc The \e %BuriednessGridCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: BuriednessGridCalculator) -> BuriednessGridCalculator: pass

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
    # \brief Specifies a function for the retrieval of atom 3D-coordinates for grid calculation.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: CDPL.Chem.Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom3DCoordinatesFunction() -> CDPL.Chem.Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param atoms 
    # \param grid 
    #
    def calculate(atoms: CDPL.Chem.AtomContainer, grid: CDPL.Grid.DSpatialGrid) -> None: pass

    objectID = property(getObjectID)

    probeRadius = property(getProbeRadius, setProbeRadius)

    minVdWSurfaceDistance = property(getMinVdWSurfaceDistance, setMinVdWSurfaceDistance)

    numTestRays = property(getNumTestRays, setNumTestRays)

    atom3DCoordinatesFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
