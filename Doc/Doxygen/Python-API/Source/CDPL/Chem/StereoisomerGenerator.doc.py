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
# \brief Enumerates the stereoisomers of a molecular graph by flipping the configurations of selected atom and bond stereocenters.
# 
# After calling setup() for an input molecular graph, each call to generate() yields the next stereoisomer (encoded as per-atom and per-bond StereoDescriptor arrays accessible via getAtomDescriptors() / getBondDescriptors()); generate() returns <tt>False</tt> when the enumeration is exhausted. Atom and bond predicates plus a number of inclusion flags control which stereocenters are enumerated.
# 
# \since 1.1
# 
class StereoisomerGenerator(Boost.Python.instance):

    ##
    # \brief Array of StereoDescriptor values (one per atom or one per bond of the input molecular graph).
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
    # \brief Initializes the \c %StereoisomerGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %StereoisomerGenerator instance \a gen.
    # \param gen The \c %StereoisomerGenerator instance to copy.
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
    # \brief Sets the predicate used to filter atom stereocenters considered during enumeration.
    # 
    # \param pred The new atom predicate.
    # 
    def setAtomPredicate(pred: AtomPredicate) -> None: pass

    ##
    # \brief Returns the currently configured atom predicate.
    # 
    # \return A reference to the atom predicate.
    # 
    def getAtomPredicate() -> AtomPredicate: pass

    ##
    # \brief Sets the predicate used to filter bond stereocenters considered during enumeration.
    # 
    # \param pred The new bond predicate.
    # 
    def setBondPredicate(pred: BondPredicate) -> None: pass

    ##
    # \brief Returns the currently configured bond predicate.
    # 
    # \return A reference to the bond predicate.
    # 
    def getBondPredicate() -> BondPredicate: pass

    ##
    # \brief Specifies whether atom-stereocenter configurations shall be enumerated.
    # 
    # \param enumerate If <tt>True</tt>, atom configurations are flipped during enumeration.
    # 
    def enumerateAtomConfig(enumerate: bool) -> None: pass

    ##
    # \brief Tells whether atom-stereocenter configurations are enumerated.
    # 
    # \return <tt>True</tt> if atom configurations are enumerated, and <tt>False</tt> otherwise.
    # 
    def atomConfigEnumerated() -> bool: pass

    ##
    # \brief Specifies whether bond-stereocenter configurations shall be enumerated.
    # 
    # \param enumerate If <tt>True</tt>, bond configurations are flipped during enumeration.
    # 
    def enumerateBondConfig(enumerate: bool) -> None: pass

    ##
    # \brief Tells whether bond-stereocenter configurations are enumerated.
    # 
    # \return <tt>True</tt> if bond configurations are enumerated, and <tt>False</tt> otherwise.
    # 
    def bondConfigEnumerated() -> bool: pass

    ##
    # \brief Specifies whether stereocenters with explicitly specified configurations shall be enumerated.
    # 
    # \param include If <tt>True</tt>, specified stereocenters are also flipped.
    # 
    def includeSpecifiedCenters(include: bool) -> None: pass

    ##
    # \brief Tells whether specified stereocenters are enumerated.
    # 
    # \return <tt>True</tt> if specified stereocenters are included, and <tt>False</tt> otherwise.
    # 
    def specifiedCentersIncluded() -> bool: pass

    ##
    # \brief Specifies whether topologically-symmetric stereocenters shall be enumerated.
    # 
    # \param include If <tt>True</tt>, symmetric stereocenters are also flipped.
    # 
    def includeSymmetricCenters(include: bool) -> None: pass

    ##
    # \brief Tells whether topologically-symmetric stereocenters are enumerated.
    # 
    # \return <tt>True</tt> if symmetric stereocenters are included, and <tt>False</tt> otherwise.
    # 
    def symmetricCentersIncluded() -> bool: pass

    ##
    # \brief Specifies whether bridgehead atoms in fused ring systems shall be enumerated as stereocenters.
    # 
    # \param include If <tt>True</tt>, bridgehead atoms are included.
    # 
    def includeBridgeheadAtoms(include: bool) -> None: pass

    ##
    # \brief Tells whether bridgehead atoms are enumerated.
    # 
    # \return <tt>True</tt> if bridgehead atoms are included, and <tt>False</tt> otherwise.
    # 
    def bridgeheadAtomsIncluded() -> bool: pass

    ##
    # \brief Specifies whether invertible (pyramidal) nitrogen stereocenters shall be enumerated.
    # 
    # \param include If <tt>True</tt>, invertible nitrogens are included.
    # 
    def includeInvertibleNitrogens(include: bool) -> None: pass

    ##
    # \brief Tells whether invertible nitrogen stereocenters are enumerated.
    # 
    # \return <tt>True</tt> if invertible nitrogens are included, and <tt>False</tt> otherwise.
    # 
    def invertibleNitrogensIncluded() -> bool: pass

    ##
    # \brief Specifies whether ring bonds (large enough to allow cis/trans isomerism) shall be enumerated.
    # 
    # \param include If <tt>True</tt>, ring bonds whose ring is at least getMinRingSize() atoms in size are included.
    # 
    def includeRingBonds(include: bool) -> None: pass

    ##
    # \brief Tells whether ring bonds are enumerated.
    # 
    # \return <tt>True</tt> if ring bonds are included, and <tt>False</tt> otherwise.
    # 
    def ringBondsIncluded() -> bool: pass

    ##
    # \brief Sets the minimum ring size for a ring bond to be eligible as a stereocenter.
    # 
    # \param min_size The new minimum ring size (in atoms).
    # 
    def setMinRingSize(min_size: int) -> None: pass

    ##
    # \brief Returns the minimum ring size for a ring bond to be eligible as a stereocenter.
    # 
    # \return The minimum ring size.
    # 
    def getMinRingSize() -> int: pass

    ##
    # \brief Prepares the generator for enumerating the stereoisomers of <em>molgraph</em>.
    # 
    # \param molgraph The input molecular graph.
    # 
    def setup(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Advances the enumeration by one step and updates the per-atom/per-bond stereo-descriptor arrays.
    # 
    # \return <tt>True</tt> if a new stereoisomer was generated, and <tt>False</tt> if the enumeration is exhausted.
    # 
    def generate() -> bool: pass

    ##
    # \brief Returns the per-atom stereo descriptors for the current stereoisomer.
    # 
    # \return A reference to the atom-stereo-descriptor array.
    # 
    def getAtomDescriptors() -> StereoDescriptorArray: pass

    ##
    # \brief Returns the per-bond stereo descriptors for the current stereoisomer.
    # 
    # \return A reference to the bond-stereo-descriptor array.
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
