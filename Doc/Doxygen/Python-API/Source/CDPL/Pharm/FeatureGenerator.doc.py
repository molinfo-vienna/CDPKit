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
# \brief FeatureGenerator.
# 
class FeatureGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>FeatureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FeatureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FeatureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: Chem.Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
    # 
    # \return The registered atom 3D-coordinates function.
    # 
    def getAtom3DCoordinatesFunction() -> Chem.Atom3DCoordinatesFunction: pass

    ##
    # \brief Perceives pharmacophore features and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The output pharmacophore where to add the generated features.
    # 
    def generate(molgraph: Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def clone() -> FeatureGenerator: pass

    objectID = property(getObjectID)

    atomCoordsFunction = property(getAtom3DCoordinatesFunction, setAtom3DCoordinatesFunction)
