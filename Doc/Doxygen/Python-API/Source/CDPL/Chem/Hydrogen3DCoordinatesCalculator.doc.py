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
# \brief Hydrogen3DCoordinatesCalculator.
# 
class Hydrogen3DCoordinatesCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>Hydrogen3DCoordinatesCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>Hydrogen3DCoordinatesCalculator</tt> instance and calculates 3D-coordinates for the hydrogen atoms of the molecular graph <em>molgraph</em>.
    # 
    # The calculated coordinates can be retrieved by a call to getResult().
    # 
    # \param molgraph The molecular graph for which to calculate 3D-coordinates.
    # \param coords An array containing the heavy atom and calculated hydrogen 3D-coordinates. The coordinates are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the coordinates of an atom are accessible via its index).
    # \param undef_only Specifies whether or not to recalculate already defined hydrogen atom coordinates.
    # 
    def __init__(molgraph: MolecularGraph, coords: Math.Vector3DArray, undef_only: bool = True) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Hydrogen3DCoordinatesCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Hydrogen3DCoordinatesCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify whether already defined hydrogen atom coordinates have to be recalculated or are left unchanged.
    # 
    # \param undef_only <tt>True</tt> if already defined hydrogen atom coordinates have to be left unchanged, and <tt>False</tt> otherwise.
    # 
    # \note The default setting is to calculate coordinates only for hydrogens with not yet defined positions.
    # 
    def undefinedOnly(undef_only: bool) -> None: pass

    ##
    # \brief Tells whether already defined hydrogen atom coordinates are recalculated or left unchanged.
    # 
    # \return <tt>True</tt> if already defined hydrogen atom coordinates are left unchanged, and <tt>False</tt> otherwise.
    # 
    def undefinedOnly() -> bool: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
    # 
    # \return The registered atom 3D-coordinates function.
    # 
    def getAtom3DCoordinatesFunction() -> Atom3DCoordinatesFunction: pass

    ##
    # \brief Specifies a function that tells whether 3D coordinates are available for it's argument atom.
    # 
    # \param func The atom 3D coordinates check function.
    # 
    def setAtom3DCoordinatesCheckFunction(func: AtomPredicate) -> None: pass

    ##
    # \brief Returns the function that was registered to determine whether for a given atom 3D coordinates are available.
    # 
    # \return The registered atom 3D coordinates check function.
    # 
    def getAtom3DCoordinatesCheckFunction() -> AtomPredicate: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def setup(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Calculates 3D-coordinates for the hydrogen atoms of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate 3D-coordinates.
    # \param coords An array containing the heavy atom and calculated hydrogen 3D-coordinates. The coordinates are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the coordinates of an atom are accessible via its index).
    # \param init_coords If <tt>False</tt>, defined atom coordinates are already present in <em>coords</em> and thus won't get assigned again.
    # 
    def calculate(molgraph: MolecularGraph, coords: Math.Vector3DArray, init_coords: bool = True) -> None: pass

    ##
    # \brief 
    # \param coords 
    # \param init_coords 
    #
    def calculate(coords: Math.Vector3DArray, init_coords: bool = True) -> None: pass

    objectID = property(getObjectID)

    undefOnly = property(undefinedOnly, undefinedOnly)

    atomCoordsFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesCheckFunction)

    atomCoordsCheckFunction = property(getAtom3DCoordinatesCheckFunction, setAtom3DCoordinatesCheckFunction)
