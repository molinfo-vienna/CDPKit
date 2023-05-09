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
# \brief 
#
class AtomDensityGridCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param func 
    #
    def __init__(func: CDPL.Chem.DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param density_func 
    # \param comb_func 
    #
    def __init__(density_func: CDPL.Chem.DoubleVector3D2AtomFunctor, comb_func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Initializes the \e %AtomDensityGridCalculator instance.
    # \param calculator 
    #
    def __init__(calculator: AtomDensityGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %AtomDensityGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomDensityGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomDensityGridCalculator instance \a calculator.
    # \param calculator The \e %AtomDensityGridCalculator instance to copy.
    # \return \a self
    #
    def assign(calculator: AtomDensityGridCalculator) -> AtomDensityGridCalculator: pass

    ##
    # \brief 
    # \param dist 
    #
    def setDistanceCutoff(dist: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDistanceCutoff() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getDensityFunction() -> CDPL.Chem.DoubleVector3D2AtomFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setDensityFunction(func: CDPL.Chem.DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setDensityCombinationFunction(func: CDPL.Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDensityCombinationFunction() -> CDPL.Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param func 
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
