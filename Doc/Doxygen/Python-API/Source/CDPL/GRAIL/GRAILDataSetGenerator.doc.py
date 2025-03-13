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
# \brief GRAILDataSetGenerator.
# 
# \see [\ref GRAIL]
# 
class GRAILDataSetGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_GRID_STEP_SIZE = 0.5

    ##
    # \brief Initializes the \e %GRAILDataSetGenerator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %GRAILDataSetGenerator instance \a gen.
    # \param gen The \e %GRAILDataSetGenerator instance to copy.
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
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \param func 
    #
    def setScoringFunction(ftr_type: int, tgt_ftr_type: int, func: DoubleVector3DFeatureFunctor) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    #
    def removeScoringFunction(ftr_type: int, tgt_ftr_type: int) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \return 
    #
    def getScoringFunction(ftr_type: int, tgt_ftr_type: int) -> DoubleVector3DFeatureFunctor: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \param name 
    #
    def setGridName(ftr_type: int, tgt_ftr_type: int, name: str) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    #
    def removeGridName(ftr_type: int, tgt_ftr_type: int) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \return 
    #
    def getGridName(ftr_type: int, tgt_ftr_type: int) -> str: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \param enable 
    #
    def enableInteraction(ftr_type: int, tgt_ftr_type: int, enable: bool) -> None: pass

    ##
    # \brief 
    # \param ftr_type 
    # \param tgt_ftr_type 
    # \return 
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
    # \brief 
    # \param func 
    #
    def setScoreCombinationFunction(func: Math.DoubleDVectorFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getScoreCombinationFunction() -> Math.DoubleDVectorFunctor: pass

    ##
    # \brief 
    # \param normalize 
    #
    def normalizeScores(normalize: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def scoresNormalized() -> bool: pass

    ##
    # \brief 
    # \param diminish 
    #
    def diminishScoresByAtomDensity(diminish: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def scoresDiminishedByAtomDensity() -> bool: pass

    ##
    # \brief 
    # \param store 
    #
    def storeEnvironmentAtomDensityGrid(store: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def environmentAtomDensityGridStored() -> bool: pass

    ##
    # \brief 
    # \param  
    #
    def setEnvironmentAtomDensityGridName(: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEnvironmentAtomDensityGridName() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def getGridStepSize() -> float: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridStepSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridXSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridXSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridYSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridYSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridZSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridZSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridTransform() -> Math.Matrix4D: pass

    ##
    # \brief 
    # \param xform 
    #
    def setGridTransform(xform: Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param bbox_min 
    # \param bbox_max 
    # \param step_size 
    #
    def setGridParamsForBoundingBox(bbox_min: Math.Vector3D, bbox_max: Math.Vector3D, step_size: float = 0.5) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPharmacophoreGenerator() -> Pharm.DefaultPharmacophoreGenerator: pass

    ##
    # \brief 
    # \param func 
    #
    def setPharmacophoreProcessingFunction(func: VoidPharmacophoreFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPharmacophoreProcessingFunction() -> VoidPharmacophoreFunctor: pass

    ##
    # \brief 
    # \param tgt_env 
    # \param coords_func 
    # \param grid_set 
    # \param append 
    #
    def calcInteractionGrids(tgt_env: Chem.MolecularGraph, coords_func: Chem.Atom3DCoordinatesFunction, grid_set: Grid.DRegularGridSet, append: bool = False) -> None: pass

    ##
    # \brief 
    # \param atoms 
    # \param coords_func 
    # \param grid_name 
    # \return 
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
