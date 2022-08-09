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
class SymmetryClassCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_ATOM_PROPERTY_FLAGS = 158

    ##
    # \brief 
    #
    DEF_BOND_PROPERTY_FLAGS = 10

    ##
    # \brief Initializes the \e %SymmetryClassCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SymmetryClassCalculator instance.
    # \param molgraph 
    # \param class_ids 
    #
    def __init__(molgraph: MolecularGraph, class_ids: CDPL.Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %SymmetryClassCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SymmetryClassCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param flags 
    #
    def setAtomPropertyFlags(flags: int) -> None: pass

    ##
    # \brief 
    # \param flags 
    #
    def setBondPropertyFlags(flags: int) -> None: pass

    ##
    # \brief 
    # \param include 
    #
    def includeImplicitHydrogens(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomPropertyFlags() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getBondPropertyFlags() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def implicitHydrogensIncluded() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    # \param class_ids 
    #
    def calculate(molgraph: MolecularGraph, class_ids: CDPL.Util.STArray) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    ##
    # \brief 
    #
    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    ##
    # \brief FIXME!
    #
    hydrogenComplete = property(getHydrogenComplete, setHydrogenComplete)