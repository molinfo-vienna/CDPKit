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
class MoleculeAutoCorr2DDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class Mode(Boost.Python.enum):

        ##
        # \brief SEMI_SPLIT.
        #
        SEMI_SPLIT = 0

        ##
        # \brief FULL_SPLIT.
        #
        FULL_SPLIT = 1

    ##
    # \brief Initializes the \e %MoleculeAutoCorr2DDescriptorCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MoleculeAutoCorr2DDescriptorCalculator instance.
    # \param calculator 
    #
    def __init__(calculator: MoleculeAutoCorr2DDescriptorCalculator) -> None: pass

    ##
    # \brief Initializes the \e %MoleculeAutoCorr2DDescriptorCalculator instance.
    # \param molgraph 
    # \param corr_vec 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, corr_vec: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %MoleculeAutoCorr2DDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MoleculeAutoCorr2DDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MoleculeAutoCorr2DDescriptorCalculator instance \a calculator.
    # \param calculator The \e %MoleculeAutoCorr2DDescriptorCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(calculator: MoleculeAutoCorr2DDescriptorCalculator) -> MoleculeAutoCorr2DDescriptorCalculator: pass

    ##
    # \brief 
    # \param max_dist 
    #
    def setMaxDistance(max_dist: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxDistance() -> int: pass

    ##
    # \brief 
    # \param max_dist 
    #
    def setMode(max_dist: Mode) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMode() -> Mode: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtomPairWeightFunction(func: CDPL.Chem.DoubleAtom2UInt2Functor) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    # \param corr_vec 
    #
    def calculate(molgraph: CDPL.Chem.MolecularGraph, corr_vec: CDPL.Math.DVector) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    maxDistance = property(getMaxDistance, setMaxDistance)

    ##
    # \brief 
    #
    mode = property(getMode, setMode)
