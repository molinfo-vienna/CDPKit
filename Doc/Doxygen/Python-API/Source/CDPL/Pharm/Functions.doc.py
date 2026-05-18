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
# \param feature 
# \param flag 
#
def setDisabledFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasDisabledFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getDisabledFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
#
def clearDisabledFlag(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def getEnvironmentResidueAtomInfo(feature: Feature) -> str: pass

##
# \brief 
# \param feature 
# \return 
#
def getEnvironmentResidueInfo(feature: Feature) -> str: pass

##
# \brief 
# \param feature 
# \param substruct 
#
def setEnvironmentSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasEnvironmentSubstructure(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getEnvironmentSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief 
# \param feature 
#
def clearEnvironmentSubstructure(feature: Feature) -> None: pass

##
# \brief 
# \param cntnr 
# \param atoms 
# \param append 
#
def getFeatureAtoms(cntnr: FeatureContainer, atoms: Chem.Fragment, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getFeatureCount(cntnr: FeatureContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param type 
# \return 
#
def getFeatureCount(cntnr: FeatureContainer, type: int) -> int: pass

##
# \brief 
# \param ftr_type 
# \return 
#
def getFeatureTypeString(ftr_type: int) -> str: pass

##
# \brief 
# \param ftr_set 
# \param mapping 
# \param first 
#
def getFeatures(ftr_set: FeatureSet, mapping: FeatureMapping, first: bool) -> None: pass

##
# \brief 
# \param feature 
# \param geom 
#
def setGeometry(feature: Feature, geom: int) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasGeometry(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getGeometry(feature: Feature) -> int: pass

##
# \brief 
# \param feature 
#
def clearGeometry(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param hyd 
#
def setHydrophobicity(feature: Feature, hyd: float) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasHydrophobicity(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getHydrophobicity(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
#
def clearHydrophobicity(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param length 
#
def setLength(feature: Feature, length: float) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasLength(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getLength(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
#
def clearLength(feature: Feature) -> None: pass

##
# \brief 
# \param cntnr 
# \param name 
#
def setName(cntnr: FeatureContainer, name: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasName(cntnr: FeatureContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getName(cntnr: FeatureContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearName(cntnr: FeatureContainer) -> None: pass

##
# \brief 
# \param feature 
# \param flag 
#
def setOptionalFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasOptionalFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getOptionalFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
#
def clearOptionalFlag(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param orient 
#
def setOrientation(feature: Feature, orient: Math.Vector3D) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasOrientation(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getOrientation(feature: Feature) -> Math.Vector3D: pass

##
# \brief 
# \param feature 
#
def clearOrientation(feature: Feature) -> None: pass

##
# \brief 
# \param cntnr 
# \param fix_geom 
#
def clearOrientations(cntnr: FeatureContainer, fix_geom: bool = True) -> None: pass

##
# \brief 
# \param feature 
# \param substruct 
#
def setSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasSubstructure(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief 
# \param feature 
#
def clearSubstructure(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param tol 
#
def setTolerance(feature: Feature, tol: float) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasTolerance(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getTolerance(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
#
def clearTolerance(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param type 
#
def setType(feature: Feature, type: int) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasType(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getType(feature: Feature) -> int: pass

##
# \brief 
# \param feature 
#
def clearType(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \param weight 
#
def setWeight(feature: Feature, weight: float) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasWeight(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getWeight(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
#
def clearWeight(feature: Feature) -> None: pass

##
# \brief 
# \param ftr_cntnr 
# \param atom_cntnr 
# \param coords_func 
# \param xform 
# \param vdw_factor 
# \return 
#
def checkForExclusionVolumeClashes(ftr_cntnr: FeatureContainer, atom_cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, xform: Math.Matrix4D, vdw_factor: float = 1.0) -> bool: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param tol 
# \param min_dist 
# \param rel_dist 
# \param append 
#
def createExclusionVolumes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param tol 
# \param min_dist 
# \param rel_dist 
# \param append 
#
def createExclusionVolumes(pharm: Pharmacophore, cntnr: FeatureContainer, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param hist 
# \param append 
#
def generateFeatureTypeHistogram(cntnr: FeatureContainer, hist: FeatureTypeHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def generateFeatureTypeHistogramString(cntnr: FeatureContainer) -> str: pass

##
# \brief 
# \param pharm 
# \param iactions 
# \param append 
#
def generateInteractionPharmacophore(pharm: Pharmacophore, iactions: FeatureMapping, append: bool = False) -> None: pass

##
# \brief 
# \param mol 
# \param calc_hyd 
# \param from_logp 
#
def prepareForPharmacophoreGeneration(mol: Chem.Molecule, calc_hyd: bool = True, from_logp: bool = False) -> None: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param vdw_scaling_fact 
# \return 
#
def removeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief 
# \param cntnr 
# \param tgt_set 
# \param type 
# \param append 
# \return 
#
def removeFeaturesWithType(cntnr: FeatureContainer, tgt_set: FeatureSet, type: int, append: bool = False) -> bool: pass

##
# \brief 
# \param ftr_set 
# \param type 
# \return 
#
def removeFeaturesWithType(ftr_set: FeatureSet, type: int) -> bool: pass

##
# \brief 
# \param pharm 
# \param type 
# \return 
#
def removeFeaturesWithType(pharm: Pharmacophore, type: int) -> bool: pass

##
# \brief 
# \param cntnr 
# \param tgt_set 
# \param pos_tol 
# \param append 
# \return 
#
def removePositionalDuplicates(cntnr: FeatureContainer, tgt_set: FeatureSet, pos_tol: float = 0.0, append: bool = False) -> bool: pass

##
# \brief 
# \param ftr_set 
# \param pos_tol 
# \return 
#
def removePositionalDuplicates(ftr_set: FeatureSet, pos_tol: float = 0.0) -> bool: pass

##
# \brief 
# \param pharm 
# \param pos_tol 
# \return 
#
def removePositionalDuplicates(pharm: Pharmacophore, pos_tol: float = 0.0) -> bool: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param vdw_scaling_fact 
# \return 
#
def resizeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform3DCoordinates(cntnr: FeatureContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief Sets the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> to <em>single_prec</em>.
# 
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter.
# 
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em>.
# 
# \since 1.2
# 
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from <em>cntnr</em>.
# 
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em> to <em>allow</em>.
# 
def setPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer, allow: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter.
# 
def hasPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em>.
# 
def getPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter from <em>cntnr</em>.
# 
def clearPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em> to <em>mode</em>.
# 
def setPSDCreationModeParameter(cntnr: Base.ControlParameterContainer, mode: Mode) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.PSD_CREATION_MODE parameter.
# 
def hasPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em>.
# 
def getPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> Mode: pass

##
# \brief Removes the Pharm.ControlParameter.PSD_CREATION_MODE parameter from <em>cntnr</em>.
# 
def clearPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em>.
# 
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter from <em>cntnr</em>.
# 
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
