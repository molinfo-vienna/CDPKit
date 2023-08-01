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
# \brief BondStereoFlagCalculator.
# 
class BondStereoFlagCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BondStereoFlagCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>BondStereoFlagCalculator</tt> instance and calculates the 2D stereo flags of the bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the stereo flags.
    # \param flags An array containing the calculated stereo flags (possible values are defined as constants in namespace Chem.BondStereoFlag). The stereo flags are stored in the same order as the bonds appear in the bond list of the molecular graph (i.e. the 2D stereo flag of a bond is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, flags: Util.UIArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %BondStereoFlagCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondStereoFlagCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for the retrieval of atom 2D-coordinates.
    # 
    # \param func The atom 2D-coordinates function.
    # 
    def setAtom2DCoordinatesFunction(func: Vector2DAtomFunctor) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 2D-coordinates.
    # 
    # \return The registered atom 2D-coordinates function.
    # 
    def getAtom2DCoordinatesFunction() -> Vector2DAtomFunctor: pass

    ##
    # \brief Calculates the 2D stereo flags of the bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the stereo flags.
    # \param flags An array containing the calculated stereo flags (possible values are defined as constants in namespace Chem.BondStereoFlag). The stereo flags are stored in the same order as the bonds appear in the bond list of the molecular graph (i.e. the 2D stereo flag of a bond is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, flags: Util.UIArray) -> None: pass

    objectID = property(getObjectID)
