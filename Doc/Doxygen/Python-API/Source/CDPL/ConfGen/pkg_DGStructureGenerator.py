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
class DGStructureGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DGStructureGenerator instance.
    # \param self The \e %DGStructureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DGStructureGenerator instance.
    # \param self The \e %DGStructureGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: DGStructureGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    #
    # Different Python \e %DGStructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DGStructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DGStructureGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGStructureGenerator instance \a gen.
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param gen The \e %DGStructureGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGStructureGenerator, gen: DGStructureGenerator) -> DGStructureGenerator: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \return 
    #
    def getExcludedHydrogenMask(self: DGStructureGenerator) -> CDPL.Util.BitSet: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param molgraph 
    #
    def setup(self: DGStructureGenerator, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param molgraph 
    # \param ia_data 
    #
    def setup(self: DGStructureGenerator, molgraph: CDPL.Chem.MolecularGraph, ia_data: CDPL.ForceField.MMFF94InteractionData) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def generate(self: DGStructureGenerator, coords: CDPL.Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \return 
    #
    def getNumAtomStereoCenters(self: DGStructureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \return 
    #
    def getNumBondStereoCenters(self: DGStructureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def checkAtomConfigurations(self: DGStructureGenerator, coords: CDPL.Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \param coords 
    # \return 
    #
    def checkBondConfigurations(self: DGStructureGenerator, coords: CDPL.Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \return 
    #
    def getSettings(self: DGStructureGenerator) -> DGStructureGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %DGStructureGenerator instance this method is called upon.
    # \return 
    #
    def getConstraintGenerator(self: DGStructureGenerator) -> DGConstraintGenerator: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numAtomStereoCenters = property(getNumAtomStereoCenters)

    ##
    # \brief 
    #
    numBondStereoCenters = property(getNumBondStereoCenters)

    ##
    # \brief 
    #
    settings = property(getSettings)

    ##
    # \brief 
    #
    constraintGenerator = property(getConstraintGenerator)

    ##
    # \brief FIXME!
    #
    exclHydrogenMask = property(getExclHydrogenMask)
