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
# \brief Constructs geometric constraints (distance, planarity, volume) for distance-geometry-based 3D structure generation.
# 
# Given a molecular graph (and optionally an MMFF94 force-field interaction parameter set) the generator derives ideal bond lengths, bond angles and 1,4-distances, identifies atom and bond stereo centers and emits the corresponding constraints into a Util.DG3DCoordinatesGenerator. The constraint set is used by ConfGen.DGStructureGenerator to produce a 3D embedding of the molecular graph.
# 
class DGConstraintGenerator(Boost.Python.instance):

    ##
    # \brief Pair holding an atom or bond index plus the associated stereo descriptor.
    # 
    class StereoCenterData(Boost.Python.instance):

        ##
        # \brief Initializes the \c %StereoCenterData instance.
        # \param ctr_idx 
        # \param descr 
        # 
        def __init__(ctr_idx: int, descr: Chem.StereoDescriptor) -> None: pass

        ##
        # \brief Initializes a copy of the \c %StereoCenterData instance \a data.
        # \param data The \c %StereoCenterData instance to copy.
        # 
        def __init__(data: StereoCenterData) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %StereoCenterData instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StereoCenterData instances \e a and \e b reference different C++ objects. 
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
        def getCenterIndex() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getDescriptor() -> Chem.StereoDescriptor: pass

        objectID = property(getObjectID)

        centerIndex = property(getCenterIndex)

        descriptor = property(getDescriptor)

    ##
    # \brief Constructs the <tt>DGConstraintGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DGConstraintGenerator instance \a gen.
    # \param gen The \c %DGConstraintGenerator instance to copy.
    # 
    def __init__(gen: DGConstraintGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DGConstraintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DGConstraintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DGConstraintGenerator instance \a gen.
    # \param gen The \c %DGConstraintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: DGConstraintGenerator) -> DGConstraintGenerator: pass

    ##
    # \brief Returns the bit mask of hydrogen atoms that have been excluded from constraint generation.
    # 
    # \return A reference to the excluded-hydrogen bit mask.
    # 
    def getExcludedHydrogenMask() -> Util.BitSet: pass

    ##
    # \brief Initializes the generator for the molecular graph <em>molgraph</em> using default geometry data.
    # 
    # \param molgraph The molecular graph to process.
    # 
    def setup(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Initializes the generator for the molecular graph <em>molgraph</em> using bond lengths and angles obtained from <em>ia_data</em>.
    # 
    # \param molgraph The molecular graph to process.
    # \param ia_data MMFF94 interaction data providing the reference bond lengths and angles.
    # 
    def setup(molgraph: Chem.MolecularGraph, ia_data: ForceField.MMFF94InteractionData) -> None: pass

    ##
    # \brief Returns the number of registered atom stereo centers.
    # 
    # \return The number of atom stereo centers.
    # 
    def getNumAtomStereoCenters() -> int: pass

    ##
    # \brief Returns the stereo-center data for the atom stereo center at index <em>idx</em>.
    # 
    # \param idx The zero-based stereo-center index.
    # 
    # \return A reference to the stereo-center data. 
    # 
    # \throw Base.IndexError if the number of atom stereo centers is zero or <em>idx</em> is not in the range [0, getNumAtomStereoCenters() - 1].
    # 
    def getAtomStereoCenterData(idx: int) -> StereoCenterData: pass

    ##
    # \brief Returns the stereo-center data for the bond stereo center at index <em>idx</em>.
    # 
    # \param idx The zero-based stereo-center index.
    # 
    # \return A reference to the stereo-center data. 
    # 
    # \throw Base.IndexError if the number of bond stereo centers is zero or <em>idx</em> is not in the range [0, getNumBondStereoCenters() - 1].
    # 
    def getBondStereoCenterData(idx: int) -> StereoCenterData: pass

    ##
    # \brief Returns the number of registered bond stereo centers.
    # 
    # \return The number of bond stereo centers.
    # 
    def getNumBondStereoCenters() -> int: pass

    ##
    # \brief Adds bond-length distance constraints to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addBondLengthConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds bond-angle (1,3) distance constraints to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addBondAngleConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds 1,4-distance constraints (cis/trans bounds) to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def add14DistanceConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds default (Van der Waals-derived) lower/upper distance constraints between all non-bonded atom pairs to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addDefaultDistanceConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds planarity (zero-volume) constraints for sp2-hybridized / aromatic atoms to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addAtomPlanarityConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds planarity (zero-volume) constraints for double and aromatic bonds to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addBondPlanarityConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds volume constraints enforcing the registered atom stereo-center configurations to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addAtomConfigurationConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Adds distance and volume constraints enforcing the registered bond stereo-center configurations to <em>coords_gen</em>.
    # 
    # \param coords_gen The coordinates generator to add the constraints to.
    # 
    def addBondConfigurationConstraints(coords_gen: Util.DG3DCoordinatesGenerator) -> None: pass

    ##
    # \brief Returns a reference to the constraint-generation settings.
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> DGConstraintGeneratorSettings: pass

    objectID = property(getObjectID)

    settings = property(getSettings)

    numAtomStereoCenters = property(getNumAtomStereoCenters)

    numBondStereoCenters = property(getNumBondStereoCenters)

    exclHydrogenMask = property(getExcludedHydrogenMask)
