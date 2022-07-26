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
class AtomDensityGridCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param self The \e %AtomDensityGridCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param self The \e %AtomDensityGridCalculator instance to initialize.
    # \param func 
    #
    def __init__(self: object, func: DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param self The \e %AtomDensityGridCalculator instance to initialize.
    # \param density_func 
    # \param comb_func 
    #
    def __init__(self: object, density_func: DoubleVector3D2AtomFunctor, comb_func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param self The \e %AtomDensityGridCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: AtomDensityGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    #
    # Different Python \e %AtomDensityGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomDensityGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: AtomDensityGridCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomDensityGridCalculator instance \a calculator.
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param calculator The \e %AtomDensityGridCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AtomDensityGridCalculator, calculator: AtomDensityGridCalculator) -> AtomDensityGridCalculator: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param dist 
    #
    def setDistanceCutoff(self: AtomDensityGridCalculator, dist: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \return 
    #
    def getDistanceCutoff(self: AtomDensityGridCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \return 
    #
    def getDensityFunction(self: AtomDensityGridCalculator) -> DoubleVector3D2AtomFunctor: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param func 
    #
    def setDensityFunction(self: AtomDensityGridCalculator, func: DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param func 
    #
    def setDensityCombinationFunction(self: AtomDensityGridCalculator, func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \return 
    #
    def getDensityCombinationFunction(self: AtomDensityGridCalculator) -> CDPL.Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param func 
    #
    def setAtom3DCoordinatesFunction(self: AtomDensityGridCalculator, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \return 
    #
    def getAtom3DCoordinatesFunction(self: AtomDensityGridCalculator) -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %AtomDensityGridCalculator instance this method is called upon.
    # \param atoms 
    # \param grid 
    #
    def calculate(self: AtomDensityGridCalculator, atoms: AtomContainer, grid: CDPL.Grid.DSpatialGrid) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    distanceCutoff = property(getDistanceCutoff, setDistanceCutoff)

    ##
    # \brief 
    #
    densityFunction = property(getDensityFunction, setDensityFunction)

    ##
    # \brief 
    #
    densityCombinationFunction = property(getDensityCombinationFunction, setDensityCombinationFunction)

    ##
    # \brief FIXME!
    #
    atomCoordinatesFunction = property(getAtomCoordinatesFunction, setAtomCoordinatesFunction)
