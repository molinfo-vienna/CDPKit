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
class BuriednessGridCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BuriednessGridCalculator instance.
    # \param self The \e %BuriednessGridCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BuriednessGridCalculator instance.
    # \param self The \e %BuriednessGridCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: BuriednessGridCalculator) -> None: pass

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
    def getObjectID(self: BuriednessGridCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BuriednessGridCalculator instance \a calculator.
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param calculator The \e %BuriednessGridCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BuriednessGridCalculator, calculator: BuriednessGridCalculator) -> BuriednessGridCalculator: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param dist 
    #
    def setMinVdWSurfaceDistance(self: BuriednessGridCalculator, dist: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \return 
    #
    def getMinVdWSurfaceDistance(self: BuriednessGridCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param radius 
    #
    def setProbeRadius(self: BuriednessGridCalculator, radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \return 
    #
    def getProbeRadius(self: BuriednessGridCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param num_rays 
    #
    def setNumTestRays(self: BuriednessGridCalculator, num_rays: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \return 
    #
    def getNumTestRays(self: BuriednessGridCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param func 
    #
    def setAtom3DCoordinatesFunction(self: BuriednessGridCalculator, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \return 
    #
    def getAtom3DCoordinatesFunction(self: BuriednessGridCalculator) -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %BuriednessGridCalculator instance this method is called upon.
    # \param atoms 
    # \param grid 
    #
    def calculate(self: BuriednessGridCalculator, atoms: AtomContainer, grid: CDPL.Grid.DSpatialGrid) -> None: pass

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
    # \brief 
    #
    atom3DCoordinatesFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
