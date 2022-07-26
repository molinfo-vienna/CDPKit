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
class Hydrogen3DCoordinatesGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Hydrogen3DCoordinatesGenerator instance.
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Hydrogen3DCoordinatesGenerator instance.
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance to initialize.
    # \param molgraph 
    # \param coords 
    # \param undef_only 
    #
    def __init__(self: object, molgraph: MolecularGraph, coords: CDPL.Math.Vector3DArray, undef_only: bool = True) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    #
    # Different Python \e %Hydrogen3DCoordinatesGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Hydrogen3DCoordinatesGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Hydrogen3DCoordinatesGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \param func 
    #
    def setAtom3DCoordinatesFunction(self: Hydrogen3DCoordinatesGenerator, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getAtom3DCoordinatesFunction(self: Hydrogen3DCoordinatesGenerator) -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \param func 
    #
    def setAtom3DCoordinatesCheckFunction(self: Hydrogen3DCoordinatesGenerator, func: AtomPredicate) -> None: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \return 
    #
    def getAtom3DCoordinatesCheckFunction(self: Hydrogen3DCoordinatesGenerator) -> AtomPredicate: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \param molgraph 
    #
    def setup(self: Hydrogen3DCoordinatesGenerator, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \param molgraph 
    # \param coords 
    # \param init_coords 
    #
    def generate(self: Hydrogen3DCoordinatesGenerator, molgraph: MolecularGraph, coords: CDPL.Math.Vector3DArray, init_coords: bool = True) -> None: pass

    ##
    # \brief 
    # \param self The \e %Hydrogen3DCoordinatesGenerator instance this method is called upon.
    # \param coords 
    # \param init_coords 
    #
    def generate(self: Hydrogen3DCoordinatesGenerator, coords: CDPL.Math.Vector3DArray, init_coords: bool = True) -> None: pass

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
