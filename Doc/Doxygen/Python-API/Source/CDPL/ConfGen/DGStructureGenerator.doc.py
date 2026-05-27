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
# \brief Distance-geometry-based generation of raw 3D structures for molecular graphs.
# 
# Constraints are produced by an embedded ConfGen.DGConstraintGenerator and used to embed the coordinates via a two-phase Util.DG3DCoordinatesGenerator pipeline. After generation, atom and bond stereo configurations can be validated against the perceived stereo descriptors.
# 
class DGStructureGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>DGStructureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DGStructureGenerator instance \a gen.
    # \param gen The \c %DGStructureGenerator instance to copy.
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
    # \brief Returns the bit mask of hydrogens excluded from the coordinate-generation step.
    # 
    # \return A reference to the bit mask.
    # 
    def getExcludedHydrogenMask() -> Util.BitSet: pass

    ##
    # \brief Sets up the generator for <em>molgraph</em> using geometry defaults derived from each atom's element number and hybridization state.
    # 
    # No MMFF94 parameterization is carried out; reference bond lengths and angles are taken from element-/hybridization-based lookup tables.
    # 
    # \param molgraph The input molecular graph.
    # 
    def setup(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Sets up the generator for <em>molgraph</em> using the supplied MMFF94 interaction data.
    # 
    # \param molgraph The input molecular graph.
    # \param ia_data The pre-computed MMFF94 interaction data.
    # 
    def setup(molgraph: Chem.MolecularGraph, ia_data: ForceField.MMFF94InteractionData) -> None: pass

    ##
    # \brief Generates a 3D coordinate set that respects the configured distance constraints.
    # 
    # \param coords The output 3D coordinate array.
    # 
    # \return <tt>True</tt> if the embedding succeeded, and <tt>False</tt> otherwise.
    # 
    def generate(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief Returns the number of atom stereo centers in the set-up molecular graph.
    # 
    # \return The atom stereo-center count.
    # 
    def getNumAtomStereoCenters() -> int: pass

    ##
    # \brief Returns the number of bond stereo centers in the set-up molecular graph.
    # 
    # \return The bond stereo-center count.
    # 
    def getNumBondStereoCenters() -> int: pass

    ##
    # \brief Validates the per-atom stereo-configurations of <em>coords</em> against the perceived stereo descriptors.
    # 
    # \param coords The 3D coordinates to test.
    # 
    # \return <tt>True</tt> if all per-atom stereo-configurations are valid, and <tt>False</tt> otherwise.
    # 
    def checkAtomConfigurations(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief Validates the per-bond stereo-configurations of <em>coords</em> against the perceived stereo descriptors.
    # 
    # \param coords The 3D coordinates to test.
    # 
    # \return <tt>True</tt> if all per-bond stereo-configurations are valid, and <tt>False</tt> otherwise.
    # 
    def checkBondConfigurations(coords: Math.Vector3DArray) -> bool: pass

    ##
    # \brief Returns the current generator settings.
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> DGStructureGeneratorSettings: pass

    ##
    # \brief Returns the embedded constraint generator used to produce the distance/volume constraints.
    # 
    # \return A reference to the constraint generator.
    # 
    def getConstraintGenerator() -> DGConstraintGenerator: pass

    objectID = property(getObjectID)

    numAtomStereoCenters = property(getNumAtomStereoCenters)

    numBondStereoCenters = property(getNumBondStereoCenters)

    settings = property(getSettings)

    constraintGenerator = property(getConstraintGenerator)

    exclHydrogenMask = property(getExcludedHydrogenMask)
