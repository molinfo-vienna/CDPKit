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
class Hydrogen3DCoordinatesCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Hydrogen3DCoordinatesCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Hydrogen3DCoordinatesCalculator instance.
    # \param molgraph 
    # \param coords 
    # \param undef_only 
    #
    def __init__(molgraph: MolecularGraph, coords: CDPL.Math.Vector3DArray, undef_only: bool = True) -> None: pass

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
    # \brief 
    # \param func 
    #
    def setAtom3DCoordinatesCheckFunction(func: AtomPredicate) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtom3DCoordinatesCheckFunction() -> AtomPredicate: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def setup(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    # \param coords 
    # \param init_coords 
    #
    def calculate(molgraph: MolecularGraph, coords: CDPL.Math.Vector3DArray, init_coords: bool = True) -> None: pass

    ##
    # \brief 
    # \param coords 
    # \param init_coords 
    #
    def calculate(coords: CDPL.Math.Vector3DArray, init_coords: bool = True) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    undefinedOnly = property(getUndefinedOnly, setUndefinedOnly)

    ##
    # \brief FIXME!
    #
    coordsFunction = property(getCoordsFunction, setCoordsFunction)

    ##
    # \brief FIXME!
    #
    coordsCheckFunction = property(getCoordsCheckFunction, setCoordsCheckFunction)
