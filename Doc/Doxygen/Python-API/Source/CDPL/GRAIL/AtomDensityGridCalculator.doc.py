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
# \brief Calculator that fills a spatial grid with combined per-atom density contributions.
# 
# For each grid cell, the density contributions of all atoms within the configured cutoff distance are evaluated using a user-supplied density function and combined into a single cell value via a user-supplied combination function (defaulting to a sum).
# 
class AtomDensityGridCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>AtomDensityGridCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>AtomDensityGridCalculator</tt> instance with the given density function.
    # 
    # \param func The density function.
    # 
    def __init__(func: Chem.DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief Constructs the <tt>AtomDensityGridCalculator</tt> instance with the given density and density-combination functions.
    # 
    # \param density_func The density function.
    # \param comb_func The function used to combine per-atom density contributions.
    # 
    def __init__(density_func: Chem.DoubleVector3D2AtomFunctor, comb_func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>AtomDensityGridCalculator</tt> instance <em>calc</em>.
    # 
    # \param calc The <tt>AtomDensityGridCalculator</tt> to copy.
    # 
    def __init__(calc: AtomDensityGridCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %AtomDensityGridCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %AtomDensityGridCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param calc The other <tt>AtomDensityGridCalculator</tt> instance.
    # 
    # \return \a self
    # 
    def assign(calc: AtomDensityGridCalculator) -> AtomDensityGridCalculator: pass

    ##
    # \brief Sets the distance cutoff beyond which atoms are not considered.
    # 
    # \param dist The cutoff distance.
    # 
    def setDistanceCutoff(dist: float) -> None: pass

    ##
    # \brief Returns the currently configured distance cutoff.
    # 
    # \return The configured cutoff distance.
    # 
    def getDistanceCutoff() -> float: pass

    ##
    # \brief Returns the currently configured density function.
    # 
    # \return The configured density function.
    # 
    def getDensityFunction() -> Chem.DoubleVector3D2AtomFunctor: pass

    ##
    # \brief Sets the density function used to evaluate per-atom contributions.
    # 
    # \param func The density function.
    # 
    def setDensityFunction(func: Chem.DoubleVector3D2AtomFunctor) -> None: pass

    ##
    # \brief Sets the function used to combine per-atom density contributions.
    # 
    # \param func The density-combination function.
    # 
    def setDensityCombinationFunction(func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Returns the currently configured density-combination function.
    # 
    # \return The configured density-combination function.
    # 
    def getDensityCombinationFunction() -> Math.DoubleDVectorFunctor: pass

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
    # \brief Calculates the combined per-atom density at each cell of <em>grid</em> for the given atoms.
    # 
    # \param atoms The atoms contributing to the density.
    # \param grid The output grid populated with per-cell density values.
    # 
    def calculate(atoms: Chem.AtomContainer, grid: Grid.DSpatialGrid) -> None: pass

    objectID = property(getObjectID)

    distanceCutoff = property(getDistanceCutoff, setDistanceCutoff)

    densityFunction = property(getDensityFunction, setDensityFunction)

    densityCombFunction = property(getDensityCombinationFunction, setDensityCombinationFunction)

    atomCoordsFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
