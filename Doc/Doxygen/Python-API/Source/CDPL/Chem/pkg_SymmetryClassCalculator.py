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
    # \param self The \e %SymmetryClassCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SymmetryClassCalculator instance.
    # \param self The \e %SymmetryClassCalculator instance to initialize.
    # \param molgraph 
    # \param class_ids 
    #
    def __init__(self: object, molgraph: MolecularGraph, class_ids: CDPL.Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    #
    # Different Python \e %SymmetryClassCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SymmetryClassCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SymmetryClassCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \param flags 
    #
    def setAtomPropertyFlags(self: SymmetryClassCalculator, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \param flags 
    #
    def setBondPropertyFlags(self: SymmetryClassCalculator, flags: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \param include 
    #
    def includeImplicitHydrogens(self: SymmetryClassCalculator, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \return 
    #
    def getAtomPropertyFlags(self: SymmetryClassCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \return 
    #
    def getBondPropertyFlags(self: SymmetryClassCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \return 
    #
    def implicitHydrogensIncluded(self: SymmetryClassCalculator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SymmetryClassCalculator instance this method is called upon.
    # \param molgraph 
    # \param class_ids 
    #
    def calculate(self: SymmetryClassCalculator, molgraph: MolecularGraph, class_ids: CDPL.Util.STArray) -> None: pass

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
