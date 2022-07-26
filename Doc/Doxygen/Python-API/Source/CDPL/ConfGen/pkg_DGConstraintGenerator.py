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
class DGConstraintGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class StereoCenterData(Boost.Python.instance):

        ##
        # \brief Initializes the \e %StereoCenterData instance.
        # \param self The \e %StereoCenterData instance to initialize.
        # \param ctr_idx 
        # \param descr 
        #
        def __init__(self: object, ctr_idx: int, descr: CDPL.Chem.StereoDescriptor) -> None: pass

        ##
        # \brief Initializes the \e %StereoCenterData instance.
        # \param self The \e %StereoCenterData instance to initialize.
        # \param data 
        #
        def __init__(self: object, data: StereoCenterData) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %StereoCenterData instance this method is called upon.
        #
        # Different Python \e %StereoCenterData instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StereoCenterData instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: StereoCenterData) -> int: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief FIXME!
        #
        centerIndex = property(getCenterIndex)

        ##
        # \brief FIXME!
        #
        descriptor = property(getDescriptor)

    ##
    # \brief Initializes the \e %DGConstraintGenerator instance.
    # \param self The \e %DGConstraintGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DGConstraintGenerator instance.
    # \param self The \e %DGConstraintGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: DGConstraintGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    #
    # Different Python \e %DGConstraintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DGConstraintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DGConstraintGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGConstraintGenerator instance \a gen.
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param gen The \e %DGConstraintGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGConstraintGenerator, gen: DGConstraintGenerator) -> DGConstraintGenerator: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \return 
    #
    def getExcludedHydrogenMask(self: DGConstraintGenerator) -> CDPL.Util.BitSet: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param arg1 
    # \param atom 
    # \param descr 
    #
    def addAtomStereoCenter(arg1: DGConstraintGenerator, atom: CDPL.Chem.Atom, descr: CDPL.Chem.StereoDescriptor) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param arg1 
    # \param bond 
    # \param descr 
    #
    def addBondStereoCenter(arg1: DGConstraintGenerator, bond: CDPL.Chem.Bond, descr: CDPL.Chem.StereoDescriptor) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param molgraph 
    #
    def setup(self: DGConstraintGenerator, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param molgraph 
    # \param ia_data 
    #
    def setup(self: DGConstraintGenerator, molgraph: CDPL.Chem.MolecularGraph, ia_data: CDPL.ForceField.MMFF94InteractionData) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \return 
    #
    def getNumAtomStereoCenters(self: DGConstraintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getAtomStereoCenterData(self: DGConstraintGenerator, idx: int) -> StereoCenterData: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getBondStereoCenterData(self: DGConstraintGenerator, idx: int) -> StereoCenterData: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \return 
    #
    def getNumBondStereoCenters(self: DGConstraintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addBondLengthConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addBondAngleConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def add14DistanceConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addDefaultDistanceConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addAtomPlanarityConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addBondPlanarityConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addAtomConfigurationConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \param coords_gen 
    #
    def addBondConfigurationConstraints(self: DGConstraintGenerator, coords_gen: CDPL.Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGConstraintGenerator instance this method is called upon.
    # \return 
    #
    def getSettings(self: DGConstraintGenerator) -> DGConstraintGeneratorSettings: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    settings = property(getSettings)

    ##
    # \brief 
    #
    numAtomStereoCenters = property(getNumAtomStereoCenters)

    ##
    # \brief 
    #
    numBondStereoCenters = property(getNumBondStereoCenters)

    ##
    # \brief FIXME!
    #
    exclHydrogenMask = property(getExclHydrogenMask)
