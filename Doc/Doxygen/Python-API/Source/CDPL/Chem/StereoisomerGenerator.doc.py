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
# \brief StereoisomerGenerator.
# 
# \since 1.1
# 
class StereoisomerGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class StereoDescriptorArray(Boost.Python.instance):

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %StereoDescriptorArray instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StereoDescriptorArray instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getSize() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def isEmpty() -> bool: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def getElement(idx: int) -> StereoDescriptor: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> StereoDescriptor: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        objectID = property(getObjectID)

        size = property(getSize)

    ##
    # \brief Initializes the \e %StereoisomerGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %StereoisomerGenerator instance \a gen.
    # \param gen The \e %StereoisomerGenerator instance to copy.
    # 
    def __init__(gen: StereoisomerGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %StereoisomerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StereoisomerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %StereoisomerGenerator instance \a gen.
    # \param gen The \c %StereoisomerGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: StereoisomerGenerator) -> StereoisomerGenerator: pass

    ##
    # \brief 
    # \param pred 
    #
    def setAtomPredicate(pred: AtomPredicate) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomPredicate() -> AtomPredicate: pass

    ##
    # \brief 
    # \param pred 
    #
    def setBondPredicate(pred: BondPredicate) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBondPredicate() -> BondPredicate: pass

    ##
    # \brief 
    # \param enumerate 
    #
    def enumerateAtomConfig(enumerate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def atomConfigEnumerated() -> bool: pass

    ##
    # \brief 
    # \param enumerate 
    #
    def enumerateBondConfig(enumerate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def bondConfigEnumerated() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeSpecifiedCenters(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def specifiedCentersIncluded() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeSymmetricCenters(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def symmetricCentersIncluded() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeBridgeheadAtoms(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def bridgeheadAtomsIncluded() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeInvertibleNitrogens(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def invertibleNitrogensIncluded() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeRingBonds(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def ringBondsIncluded() -> bool: pass

    ##
    # \brief 
    # \param min_size 
    #
    def setMinRingSize(min_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinRingSize() -> int: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def setup(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def generate() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomDescriptors() -> StereoDescriptorArray: pass

    ##
    # \brief 
    # \return 
    #
    def getBondDescriptors() -> StereoDescriptorArray: pass

    objectID = property(getObjectID)

    atomPredicate = property(getAtomPredicate, setAtomPredicate)

    bondPredicate = property(getBondPredicate, setBondPredicate)

    enumAtomConfig = property(atomConfigEnumerated, enumerateAtomConfig)

    enumBondConfig = property(enumerateBondConfig, bondConfigEnumerated)

    incSpecifiedCenters = property(specifiedCentersIncluded, includeSpecifiedCenters)

    incSymmetricCenters = property(symmetricCentersIncluded, includeSymmetricCenters)

    incBridgeheadAtoms = property(bridgeheadAtomsIncluded, includeBridgeheadAtoms)

    incInvNitrogens = property(invertibleNitrogensIncluded, includeInvertibleNitrogens)

    incRingBonds = property(ringBondsIncluded, includeRingBonds)

    minRingSize = property(getMinRingSize, setMinRingSize)

    atomDescriptors = property(getAtomDescriptors)

    bondDescriptors = property(getBondDescriptors)
