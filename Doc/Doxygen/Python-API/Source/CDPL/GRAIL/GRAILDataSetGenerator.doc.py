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
# \brief Generator that pre-computes the per-cell interaction-score grids and the atom-density grid used by GRAIL scoring of ligand poses against a target environment.
# 
# For every enabled (ligand feature type, target feature type) pair the generator runs a GRAIL.FeatureInteractionScoreGridCalculator and stores the resulting grid in a Grid.DRegularGridSet. Optionally the generator also produces an atom-density grid of the target environment (e.g. for use as a buriedness or accessibility weight).
# 
# \see [\ref GRAIL] 
# 
# \since 1.1
# 
class GRAILDataSetGenerator(Boost.Python.instance):

    ##
    # \brief Default grid spacing (isotropic).
    # 
    DEF_GRID_STEP_SIZE = 0.5

    ##
    # \brief Constructs the <tt>GRAILDataSetGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %GRAILDataSetGenerator instance \a gen.
    # \param gen The \c %GRAILDataSetGenerator instance to copy.
    # 
    def __init__(gen: GRAILDataSetGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GRAILDataSetGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GRAILDataSetGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %GRAILDataSetGenerator instance \a gen.
    # \param gen The \c %GRAILDataSetGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: GRAILDataSetGenerator) -> GRAILDataSetGenerator: pass

    ##
    # \brief Sets the scoring function for the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # \param func The scoring function.
    # 
    def setScoringFunction(ftr_type: int, tgt_ftr_type: int, func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief Removes the scoring function configured for the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # 
    def removeScoringFunction(ftr_type: int, tgt_ftr_type: int) -> None: pass

    ##
    # \brief Returns the scoring function configured for the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # 
    # \return The configured scoring function (or an empty function if no entry is registered).
    # 
    def getScoringFunction(ftr_type: int, tgt_ftr_type: int) -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief Sets the grid name associated with the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # \param name The grid name.
    # 
    def setGridName(ftr_type: int, tgt_ftr_type: int, name: str) -> None: pass

    ##
    # \brief Removes the grid name associated with the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # 
    def removeGridName(ftr_type: int, tgt_ftr_type: int) -> None: pass

    ##
    # \brief Returns the grid name associated with the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # 
    # \return The grid name.
    # 
    def getGridName(ftr_type: int, tgt_ftr_type: int) -> str: pass

    ##
    # \brief Enables or disables interaction-grid generation for the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # \param enable If <tt>True</tt>, the interaction is enabled.
    # 
    def enableInteraction(ftr_type: int, tgt_ftr_type: int, enable: bool) -> None: pass

    ##
    # \brief Tells whether interaction-grid generation is enabled for the given (ligand feature type, target feature type) pair.
    # 
    # \param ftr_type The ligand feature type.
    # \param tgt_ftr_type The target feature type.
    # 
    # \return <tt>True</tt> if the interaction is enabled, and <tt>False</tt> otherwise.
    # 
    def isInteractionEnabled(ftr_type: int, tgt_ftr_type: int) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \param arg2 
    # \return 
    #
    def clearEnabledInteractions(arg2: int, self: int) -> bool: pass

    ##
    # \brief Sets the function used to combine per-feature scores into a single grid cell value.
    # 
    # \param func The score-combination function.
    # 
    def setScoreCombinationFunction(func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief Returns the currently configured score-combination function.
    # 
    # \return The configured score-combination function.
    # 
    def getScoreCombinationFunction() -> Math.DoubleDVectorFunctor: pass

    ##
    # \brief Enables or disables normalization of the combined per-cell scores to the range [0, 1].
    # 
    # \param normalize If <tt>True</tt>, the combined scores are normalized.
    # 
    def normalizeScores(normalize: bool) -> None: pass

    ##
    # \brief Tells whether the combined per-cell scores are normalized.
    # 
    # \return <tt>True</tt> if the combined scores are normalized, and <tt>False</tt> otherwise.
    # 
    def scoresNormalized() -> bool: pass

    ##
    # \brief Enables or disables multiplicative diminishing of interaction scores by the (normalized) atom density of the target environment.
    # 
    # \param diminish If <tt>True</tt>, scores are diminished by atom density.
    # 
    def diminishScoresByAtomDensity(diminish: bool) -> None: pass

    ##
    # \brief Tells whether the interaction scores are diminished by the atom density of the target environment.
    # 
    # \return <tt>True</tt> if scores are diminished by atom density, and <tt>False</tt> otherwise.
    # 
    def scoresDiminishedByAtomDensity() -> bool: pass

    ##
    # \brief Specifies whether the target environment atom-density grid shall be added to the produced grid set.
    # 
    # \param store If <tt>True</tt>, the atom-density grid is stored.
    # 
    def storeEnvironmentAtomDensityGrid(store: bool) -> None: pass

    ##
    # \brief Tells whether the target environment atom-density grid is stored in the produced grid set.
    # 
    # \return <tt>True</tt> if the atom-density grid is stored, and <tt>False</tt> otherwise.
    # 
    def environmentAtomDensityGridStored() -> bool: pass

    ##
    # \brief 
    # \param  
    #
    def setEnvironmentAtomDensityGridName(: str) -> None: pass

    ##
    # \brief Returns the name assigned to the target environment atom-density grid.
    # 
    # \return The grid name.
    # 
    def getEnvironmentAtomDensityGridName() -> str: pass

    ##
    # \brief Returns the currently configured grid spacing.
    # 
    # \return The configured grid spacing.
    # 
    def getGridStepSize() -> float: pass

    ##
    # \brief Sets the grid spacing (isotropic).
    # 
    # \param size The grid spacing.
    # 
    def setGridStepSize(size: float) -> None: pass

    ##
    # \brief Returns the grid size in the <em>x</em> direction.
    # 
    # \return The grid size in the <em>x</em> direction.
    # 
    def getGridXSize() -> int: pass

    ##
    # \brief Sets the grid size in the <em>x</em> direction.
    # 
    # \param size The grid size.
    # 
    def setGridXSize(size: int) -> None: pass

    ##
    # \brief Returns the grid size in the <em>y</em> direction.
    # 
    # \return The grid size in the <em>y</em> direction.
    # 
    def getGridYSize() -> int: pass

    ##
    # \brief Sets the grid size in the <em>y</em> direction.
    # 
    # \param size The grid size.
    # 
    def setGridYSize(size: int) -> None: pass

    ##
    # \brief Returns the grid size in the <em>z</em> direction.
    # 
    # \return The grid size in the <em>z</em> direction.
    # 
    def getGridZSize() -> int: pass

    ##
    # \brief Sets the grid size in the <em>z</em> direction.
    # 
    # \param size The grid size.
    # 
    def setGridZSize(size: int) -> None: pass

    ##
    # \brief Returns the affine transformation matrix that places the grids in the target coordinate frame.
    # 
    # \return The grid transformation matrix.
    # 
    def getGridTransform() -> Math.Matrix4D: pass

    ##
    # \brief Sets the affine transformation matrix that places the grids in the target coordinate frame.
    # 
    # \param xform The transformation matrix.
    # 
    def setGridTransform(xform: Math.Matrix4D) -> None: pass

    ##
    # \brief Convenience method that configures grid size, spacing and transformation so that the grid covers the given axis-aligned bounding box.
    # 
    # \param bbox_min The bounding box minimum-corner coordinates.
    # \param bbox_max The bounding box maximum-corner coordinates.
    # \param step_size The grid spacing.
    # 
    def setGridParamsForBoundingBox(bbox_min: Math.Vector3D, bbox_max: Math.Vector3D, step_size: float = 0.5) -> None: pass

    ##
    # \brief Returns the internal pharmacophore generator used for the target environment.
    # 
    # \return A reference to the pharmacophore generator.
    # 
    def getPharmacophoreGenerator() -> Pharm.DefaultPharmacophoreGenerator: pass

    ##
    # \brief Sets the function applied to the generated target pharmacophore before grid calculation (e.g. for filtering or modification).
    # 
    # \param func The pharmacophore processing function.
    # 
    def setPharmacophoreProcessingFunction(func: VoidPharmacophoreFunctor) -> None: pass

    ##
    # \brief Returns the currently configured pharmacophore processing function.
    # 
    # \return The configured pharmacophore processing function.
    # 
    def getPharmacophoreProcessingFunction() -> VoidPharmacophoreFunctor: pass

    ##
    # \brief Calculates the interaction-score grids for all enabled feature-type pairs and stores them in <em>grid_set</em>.
    # 
    # \param tgt_env The target environment.
    # \param coords_func The function used to retrieve atom 3D-coordinates from <em>tgt_env</em>.
    # \param grid_set The output grid set.
    # \param append If <tt>True</tt>, the new grids are appended to <em>grid_set</em>; otherwise <em>grid_set</em> is cleared first.
    # 
    def calcInteractionGrids(tgt_env: Chem.MolecularGraph, coords_func: Chem.Atom3DCoordinatesFunction, grid_set: Grid.DRegularGridSet, append: bool = False) -> None: pass

    ##
    # \brief Calculates an atom-density grid for the given atoms.
    # 
    # \param atoms The atoms contributing to the density.
    # \param coords_func The function used to retrieve atom 3D-coordinates.
    # \param grid_name The name to assign to the resulting grid.
    # 
    # \return A smart reference to the calculated atom-density grid.
    # 
    def calcAtomDensityGrid(atoms: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, grid_name: str) -> Grid.DRegularGrid: pass

    objectID = property(getObjectID)

    normalizedScores = property(scoresNormalized, normalizeScores)

    scoreCombinationFunction = property(getScoreCombinationFunction, setScoreCombinationFunction)

    pharmProcessingFunction = property(getPharmacophoreProcessingFunction, setPharmacophoreProcessingFunction)

    gridStepSize = property(getGridStepSize, setGridStepSize)

    gridXSize = property(getGridXSize, setGridXSize)

    gridYSize = property(getGridYSize, setGridYSize)

    gridZSize = property(getGridZSize, setGridZSize)

    gridTransform = property(getGridTransform, setGridTransform)

    pharmGenerator = property(getPharmacophoreGenerator)

    dimScoresByAtomDensity = property(scoresDiminishedByAtomDensity, diminishScoresByAtomDensity)

    storeEnvAtomDensityGrid = property(environmentAtomDensityGridStored, storeEnvironmentAtomDensityGrid)

    envAtomDensityGridName = property(getEnvironmentAtomDensityGridName, setEnvironmentAtomDensityGridName)
