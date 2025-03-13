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
class DGStructureGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DGStructureGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %DGStructureGenerator instance \a gen.
    # \param gen The \e %DGStructureGenerator instance to copy.
    # 
    def __init__(gen: DGStructureGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DGStructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DGStructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DGStructureGenerator instance \a gen.
    # \param gen The \c %DGStructureGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: DGStructureGenerator) -> DGStructureGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def getExcludedHydrogenMask() -> Util.BitSet: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def setup(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    # \param ia_data 
    #
    def setup(molgraph: Chem.MolecularGraph, ia_data: ForceField.MMFF94InteractionData) -> None: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def generate(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getNumAtomStereoCenters() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumBondStereoCenters() -> int: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def checkAtomConfigurations(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \param coords 
    # \return 
    #
    def checkBondConfigurations(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getSettings() -> DGStructureGeneratorSettings: pass

    ##
    # \brief 
    # \return 
    #
    def getConstraintGenerator() -> DGConstraintGenerator: pass

    objectID = property(getObjectID)

    numAtomStereoCenters = property(getNumAtomStereoCenters)

    numBondStereoCenters = property(getNumBondStereoCenters)

    settings = property(getSettings)

    constraintGenerator = property(getConstraintGenerator)

    exclHydrogenMask = property(getExcludedHydrogenMask)
