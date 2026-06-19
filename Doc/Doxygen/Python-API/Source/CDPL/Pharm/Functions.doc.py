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
# \brief Sets the value of the Pharm.FeatureProperty.DISABLED_FLAG property of the feature <em>feature</em> to <em>flag</em>.
# 
# \param feature The feature for which to set the property value.
# \param flag The new disabled flag value.
# 
def setDisabledFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.DISABLED_FLAG property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the disabled flag is set, and <tt>False</tt> otherwise.
# 
def hasDisabledFlag(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.DISABLED_FLAG property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return <tt>True</tt> if the feature is flagged as disabled, and <tt>False</tt> otherwise.
# 
def getDisabledFlag(feature: Feature) -> bool: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.DISABLED_FLAG property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearDisabledFlag(feature: Feature) -> None: pass

##
# \brief Generates a string describing the per-atom residue environment of the feature <em>feature</em> (residue names and atom names of interacting pocket atoms).
# 
# \param feature The feature.
# 
# \return The generated environment residue atom info string. 
# 
# \since 1.4
# 
def getEnvironmentResidueAtomInfo(feature: Feature) -> str: pass

##
# \brief Generates a string describing the residue environment of the feature <em>feature</em> (residue names of interacting pocket residues).
# 
# \param feature The feature.
# 
# \return The generated environment residue info string. 
# 
# \since 1.3
# 
def getEnvironmentResidueInfo(feature: Feature) -> str: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of the feature <em>feature</em> to <em>substruct</em>.
# 
# \param feature The feature for which to set the property value.
# \param substruct The new environment substructure.
# 
def setEnvironmentSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of the feature <em>feature</em> is set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the environment substructure property is set, and <tt>False</tt> otherwise.
# 
def hasEnvironmentSubstructure(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of the feature <em>feature</em> (interacting pocket residues).
# 
# \param feature The feature for which to get the property value.
# 
# \return A shared reference to the environment substructure. 
# 
# \since 1.4
# 
def getEnvironmentSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearEnvironmentSubstructure(feature: Feature) -> None: pass

##
# \brief Collects the atoms of the molecular substructures underlying the features of the feature container <em>cntr</em> into <em>atoms</em>.
# 
# Features without an associated substructure (see Pharm.hasSubstructure()) are silently skipped.
# 
# \param cntnr The feature container providing the features.
# \param atoms The output fragment receiving the contributing atoms.
# \param append If <tt>False</tt>, <em>atoms</em> is cleared before any atoms are added.
# 
def getFeatureAtoms(cntnr: FeatureContainer, atoms: Chem.Fragment, append: bool = False) -> None: pass

##
# \brief Returns the total number of features stored in the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container.
# 
# \return The number of stored features.
# 
def getFeatureCount(cntnr: FeatureContainer) -> int: pass

##
# \brief Returns the number of features in the feature container <em>cntr</em> whose type matches <em>type</em>.
# 
# \param cntnr The feature container.
# \param type The feature type to count.
# 
# \return The number of features of the specified type.
# 
def getFeatureCount(cntnr: FeatureContainer, type: int) -> int: pass

##
# \brief Returns a concise human-readable string (e.g. <em>"HBD"</em> for H-bond donor) for the given numeric feature type identifier <em>ftr_type</em>.
# 
# \param ftr_type The feature type identifier (see namespace Pharm.FeatureType).
# 
# \return A reference to the feature type string.
# 
def getFeatureTypeString(ftr_type: int) -> str: pass

##
# \brief Extracts features from <em>mapping</em> into the feature set <em>ftr_set</em>.
# 
# \param ftr_set The output feature set.
# \param mapping The feature mapping.
# \param first If <tt>True</tt>, the first feature of each mapping pair is added. Otherwise, the second feature.
# 
def getFeatures(ftr_set: FeatureSet, mapping: FeatureMapping, first: bool) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.GEOMETRY property of the feature <em>feature</em> to <em>geom</em>.
# 
# \param feature The feature for which to set the property value.
# \param geom The new feature geometry identifier (see namespace Pharm.FeatureGeometry).
# 
def setGeometry(feature: Feature, geom: int) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.GEOMETRY property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the geometry property is set, and <tt>False</tt> otherwise.
# 
def hasGeometry(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.GEOMETRY property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The feature geometry identifier (see namespace Pharm.FeatureGeometry).
# 
def getGeometry(feature: Feature) -> int: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.GEOMETRY property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearGeometry(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.HYDROPHOBICITY property of the feature <em>feature</em> to <em>hyd</em>.
# 
# \param feature The feature for which to set the property value.
# \param hyd The new hydrophobicity value.
# 
def setHydrophobicity(feature: Feature, hyd: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.HYDROPHOBICITY property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the hydrophobicity property is set, and <tt>False</tt> otherwise.
# 
def hasHydrophobicity(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.HYDROPHOBICITY property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The hydrophobicity value.
# 
def getHydrophobicity(feature: Feature) -> float: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.HYDROPHOBICITY property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearHydrophobicity(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.LENGTH property of the feature <em>feature</em> to <em>length</em>.
# 
# \param feature The feature for which to set the property value.
# \param length The new length value.
# 
def setLength(feature: Feature, length: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.LENGTH property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the length property is set, and <tt>False</tt> otherwise.
# 
def hasLength(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.LENGTH property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The length value.
# 
def getLength(feature: Feature) -> float: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.LENGTH property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearLength(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureContainerProperty.NAME property of the feature container <em>cntnr</em> to <em>name</em>.
# 
# \param cntnr The feature container for which to set the property value.
# \param name The new name.
# 
def setName(cntnr: FeatureContainer, name: str) -> None: pass

##
# \brief Tells whether the Pharm.FeatureContainerProperty.NAME property of the feature container <em>cntnr</em> is set.
# 
# \param cntnr The feature container for which to query the property value.
# 
# \return <tt>True</tt> if the name property is set, and <tt>False</tt> otherwise.
# 
def hasName(cntnr: FeatureContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureContainerProperty.NAME property of the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container for which to return the property value.
# 
# \return The name (or an empty string if the property is not set).
# 
def getName(cntnr: FeatureContainer) -> str: pass

##
# \brief Clears the value of the Pharm.FeatureContainerProperty.NAME property of the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container for which to clear the property value.
# 
def clearName(cntnr: FeatureContainer) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.OPTIONAL_FLAG property of the feature <em>feature</em> to <em>flag</em>.
# 
# \param feature The feature for which to set the property value.
# \param flag The new optional flag value.
# 
def setOptionalFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.OPTIONAL_FLAG property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the optional flag is set, and <tt>False</tt> otherwise.
# 
def hasOptionalFlag(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.OPTIONAL_FLAG property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return <tt>True</tt> if the feature is flagged as optional, and <tt>False</tt> otherwise.
# 
def getOptionalFlag(feature: Feature) -> bool: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.OPTIONAL_FLAG property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearOptionalFlag(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.ORIENTATION property of the feature <em>feature</em> to <em>orient</em>.
# 
# \param feature The feature for which to set the property value.
# \param orient The new 3D orientation vector.
# 
def setOrientation(feature: Feature, orient: Math.Vector3D) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.ORIENTATION property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the orientation property is set, and <tt>False</tt> otherwise.
# 
def hasOrientation(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.ORIENTATION property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return A reference to the 3D orientation vector.
# 
def getOrientation(feature: Feature) -> Math.Vector3D: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.ORIENTATION property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearOrientation(feature: Feature) -> None: pass

##
# \brief Clears the orientation property of every feature in the feature container <em>cntr</em> and (optionally) resets each feature's geometry property.
# 
# \param cntnr The feature container.
# \param fix_geom If <tt>True</tt>, the geometry property of each feature is set to Pharm.FeatureGeometry.SPHERE after clearing the orientation.
# 
# \since 1.2
# 
def clearOrientations(cntnr: FeatureContainer, fix_geom: bool = True) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.SUBSTRUCTURE property of the feature <em>feature</em> to <em>substruct</em>.
# 
# \param feature The feature for which to set the property value.
# \param substruct The new feature substructure.
# 
def setSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.SUBSTRUCTURE property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the substructure property is set, and <tt>False</tt> otherwise.
# 
def hasSubstructure(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.SUBSTRUCTURE property of the feature <em>feature</em> (the underlying atoms/bonds).
# 
# \param feature The feature for which to get the property value.
# 
# \return A shared reference to the feature substructure.
# 
def getSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.SUBSTRUCTURE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearSubstructure(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.TOLERANCE property of the feature <em>feature</em> to <em>tol</em>.
# 
# \param feature The feature for which to set the property value.
# \param tol The new tolerance value.
# 
def setTolerance(feature: Feature, tol: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.TOLERANCE property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the tolerance property is set, and <tt>False</tt> otherwise.
# 
def hasTolerance(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.TOLERANCE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The tolerance value.
# 
def getTolerance(feature: Feature) -> float: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.TOLERANCE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearTolerance(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.TYPE property of the feature <em>feature</em> to <em>type</em>.
# 
# \param feature The feature for which to set the property value.
# \param type The new feature type identifier (see namespace Pharm.FeatureType).
# 
def setType(feature: Feature, type: int) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.TYPE property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the type property is set, and <tt>False</tt> otherwise.
# 
def hasType(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.TYPE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The feature type identifier (see namespace Pharm.FeatureType).
# 
def getType(feature: Feature) -> int: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.TYPE property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearType(feature: Feature) -> None: pass

##
# \brief Sets the value of the Pharm.FeatureProperty.WEIGHT property of the feature <em>feature</em> to <em>weight</em>.
# 
# \param feature The feature for which to set the property value.
# \param weight The new weight value.
# 
def setWeight(feature: Feature, weight: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.WEIGHT property of the feature <em>feature</em> is set.
# 
# \param feature The feature for which to query the property value.
# 
# \return <tt>True</tt> if the weight property is set, and <tt>False</tt> otherwise.
# 
def hasWeight(feature: Feature) -> bool: pass

##
# \brief Returns the value of the Pharm.FeatureProperty.WEIGHT property of the feature <em>feature</em>.
# 
# \param feature The feature for which to get the property value.
# 
# \return The weight value.
# 
def getWeight(feature: Feature) -> float: pass

##
# \brief Clears the value of the Pharm.FeatureProperty.WEIGHT property of the feature <em>feature</em>.
# 
# \param feature The feature for which to clear the property value.
# 
def clearWeight(feature: Feature) -> None: pass

##
# \brief Tests whether the exclusion volume features in <em>ftr_cntnr</em> remain clash-free with respect to the transformed atom positions of <em>atom_cntnr</em>.
# 
# Each enabled feature of type Pharm.FeatureType.EXCLUSION_VOLUME is checked against every atom of <em>atom_cntnr:</em> a clash is reported as soon as the distance between feature and atom is smaller than the sum of the feature's position tolerance and <em>vdw_factor</em> times the atom's Van der Waals radius.
# 
# \param ftr_cntnr The feature container providing the exclusion volume features.
# \param atom_cntnr The atom container providing the test atoms.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param xform The 4x4 transformation applied to the atom coordinates before the clash test.
# \param vdw_factor Scaling factor for the per-atom Van der Waals radii. If &le; 0 the atoms are treated as point particles.
# 
# \return <tt>True</tt> if no clash is detected, and <tt>False</tt> otherwise.
# 
def checkForExclusionVolumeClashes(ftr_cntnr: FeatureContainer, atom_cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, xform: Math.Matrix4D, vdw_factor: float = 1.0) -> bool: pass

##
# \brief Creates exclusion volume features at the 3D positions of the atoms in <em>cntnr</em> and appends them to the pharmacophore <em>pharm</em>.
# 
# \param pharm The pharmacophore receiving the new exclusion volumes.
# \param cntnr The atom container providing the seed positions.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param tol The position tolerance to assign to new exclusion volumes (if &le; 0 the per-atom VdW radius is used).
# \param min_dist Minimum distance (<em>rel_dist</em> controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
# \param rel_dist If <tt>True</tt>, the per-pair tolerance sum is subtracted from the pair distance before testing against <em>min_dist</em>. Otherwise, the absolute distance is tested.
# \param append If <tt>False</tt>, the pharmacophore <em>pharm</em> is cleared before any exclusion volumes are added.
# 
def createExclusionVolumes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief Creates exclusion volume features at the 3D positions of the features in <em>cntnr</em> and appends them to the pharmacophore <em>pharm</em>.
# 
# \param pharm The pharmacophore receiving the new exclusion volumes.
# \param cntnr The feature container providing the seed positions.
# \param tol The position tolerance to assign to new exclusion volumes (if &le; 0 the per-feature tolerance is used).
# \param min_dist Minimum distance (<em>rel_dist</em> controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
# \param rel_dist If <tt>True</tt>, the per-pair tolerance sum is subtracted from the pair distance before testing against <em>min_dist</em>. Otherwise, the absolute distance is tested.
# \param append If <tt>False</tt>, the pharmacophore <em>pharm</em> is cleared before any exclusion volumes are added.
# 
def createExclusionVolumes(pharm: Pharmacophore, cntnr: FeatureContainer, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief Computes a per-feature type frequency histogram of the features in the feature container <em>cntr</em>.
# 
# \param cntnr The feature container.
# \param hist The output histogram (feature type to count).
# \param append If <tt>False</tt>, <em>hist</em> is cleared before the counts are accumulated.
# 
def generateFeatureTypeHistogram(cntnr: FeatureContainer, hist: FeatureTypeHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def generateFeatureTypeHistogramString(cntnr: FeatureContainer) -> str: pass

##
# \brief Builds an interaction pharmacophore from the supplied feature mapping.
# 
# At least one output feature per interacting ligand feature is emitted. For H-bond donor/acceptor and X-bonding interactions separate vector features are output. The environment substructure properties of the output features are set to the (combined) substructures covered by the interacting target features.
# 
# \param pharm The output pharmacophore where to add the generated features.
# \param iactions The feature mapping describing the interactions.
# \param append If <tt>False</tt>, the pharmacophore <em>pharm</em> is cleared before any features are added.
# 
def generateInteractionPharmacophore(pharm: Pharmacophore, iactions: FeatureMapping, append: bool = False) -> None: pass

##
# \brief Prepares the molecule <em>mol</em> for downstream pharmacophore generation..
# 
# The molecule gets prepared by completing its hydrogens, perceiving the SSSR, ring flags, implicit H counts, hybridization states and aromaticity, generating 3D coordinates for newly added hydrogens and (optionally) calculating per-atom hydrophobicities. Failures of the hydrogen 3D-coordinate or residue sequence info derivation steps are silently caught and ignored. All other exceptions propagate.
# 
# \param mol The molecule to prepare (modified in place).
# \param calc_hyd If <tt>True</tt>, atom hydrophobicities are also calculated and stored as atom properties.
# \param from_logp If <tt>True</tt> and <em>calc_hyd</em> is set, the hydrophobicities are derived from the <em>XLogP</em> [\ref XLOGP] atom contributions instead of the Greene algorithm [\ref CATA].
# 
def prepareForPharmacophoreGeneration(mol: Chem.Molecule, calc_hyd: bool = True, from_logp: bool = False) -> None: pass

##
# \brief Removes every exclusion volume feature from the pharmacophore <em>pharm</em> whose tolerance sphere clashes with any atom of <em>cntnr</em>.
# 
# \param pharm The pharmacophore to filter.
# \param cntnr The atom container providing the clash partners.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param vdw_scaling_fact Scaling factor applied to the per-atom Van der Waals radius during the clash test.
# 
# \return <tt>True</tt> if at least one exclusion volume was removed, and <tt>False</tt> otherwise.
# 
def removeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief Copies the features in the feature container <em>cntr</em> into <em>tgt_set</em>, skipping every feature whose type matches <em>type</em>.
# 
# \param cntnr The feature container providing the input features.
# \param tgt_set The feature set receiving the filtered features.
# \param type The feature type to exclude (see namespace Pharm.FeatureType).
# \param append If <tt>False</tt>, <em>tgt_set</em> is cleared before adding any features.
# 
# \return <tt>True</tt> if at least one feature was excluded, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removeFeaturesWithType(cntnr: FeatureContainer, tgt_set: FeatureSet, type: int, append: bool = False) -> bool: pass

##
# \brief Removes features of the given type from the feature set <em>ftr_set</em>.
# 
# \param ftr_set The feature set to clean (modified in place).
# \param type The feature type to remove (see namespace Pharm.FeatureType).
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removeFeaturesWithType(ftr_set: FeatureSet, type: int) -> bool: pass

##
# \brief Removes every feature in the pharmacophore <em>pharm</em> whose type matches <em>type</em>.
# 
# \param pharm The pharmacophore to filter.
# \param type The feature type to remove (see namespace Pharm.FeatureType).
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removeFeaturesWithType(pharm: Pharmacophore, type: int) -> bool: pass

##
# \brief Copies the features in the feature container <em>cntr</em> into <em>tgt_set</em>, suppressing features that share both type and 3D position with an already collected feature.
# 
# Two features count as duplicates if they have identical type and their position vectors either match exactly (<em>pos_tol</em> &le; 0) or lie within <em>pos_tol</em> from each other. When a duplicate is detected, the feature with the larger position tolerance is retained.
# 
# \param cntnr The feature container providing the input features.
# \param tgt_set The feature set receiving the deduplicated features.
# \param pos_tol The position-equality tolerance in &Aring;ngstrom. Values &le; 0 require an exact position match.
# \param append If <tt>False</tt>, <em>tgt_set</em> is cleared before adding any features.
# 
# \return <tt>True</tt> if at least one duplicate was detected, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removePositionalDuplicates(cntnr: FeatureContainer, tgt_set: FeatureSet, pos_tol: float = 0.0, append: bool = False) -> bool: pass

##
# \brief Removes features from the feature set <em>ftr_set</em> whose 3D position duplicates that of another feature of the same type.
# 
# \param ftr_set The feature set to clean (modified in place).
# \param pos_tol The positional tolerance below which two features are considered duplicates.
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removePositionalDuplicates(ftr_set: FeatureSet, pos_tol: float = 0.0) -> bool: pass

##
# \brief Removes positional duplicate features from the pharmacophore <em>pharm</em> in place.
# 
# Two features count as duplicates if they have identical type and their position vectors either match exactly (<em>pos_tol</em> &le; 0) or lie within <em>pos_tol</em> from each other. When a duplicate is detected, the feature with the larger position tolerance is retained.
# 
# \param pharm The pharmacophore to deduplicate.
# \param pos_tol The position-equality tolerance in &Aring;ngstrom. Values &le; 0 require an exact position match.
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removePositionalDuplicates(pharm: Pharmacophore, pos_tol: float = 0.0) -> bool: pass

##
# \brief Shrinks the tolerance of every exclusion volume feature in the pharmacophore <em>pharm</em> whose tolerance sphere clashes with any atom of <em>cntnr</em>.
# 
# If the resulting tolerance falls below 0.25 then the exclusion volume feature is removed.
# 
# \param pharm The pharmacophore to modify.
# \param cntnr The atom container providing the clash partners.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param vdw_scaling_fact Scaling factor applied to the per-atom Van der Waals radius during the clash test.
# 
# \return <tt>True</tt> if at least one exclusion volume was resized or removed, and <tt>False</tt> otherwise.
# 
def resizeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief Applies the affine transformation <em>mtx</em> to the 3D position property and, if set, the orientation property of every feature in the feature container <em>cntr</em>.
# 
# \param cntnr The feature container to transform.
# \param mtx The 4x4 transformation matrix.
# 
def transform3DCoordinates(cntnr: FeatureContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief Sets the value of the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> to <em>single_prec</em>.
# 
# \param cntnr The control-parameter container.
# \param single_prec <tt>True</tt> to write single-precision floats, and <tt>False</tt> to write double-precision floats.
# 
# \since 1.2
# 
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief Tells whether the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if <em>CDF</em> output uses single-precision floats, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em> to <em>allow</em>.
# 
# \param cntnr The control-parameter container.
# \param allow <tt>True</tt> to allow duplicate database entries, and <tt>False</tt> to reject them.
# 
def setPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer, allow: bool) -> None: pass

##
# \brief Tells whether the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if duplicate database entries are allowed, and <tt>False</tt> otherwise.
# 
def getPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em> to <em>mode</em>.
# 
# \param cntnr The control-parameter container.
# \param mode The new Pharm.ScreeningDBCreator.Mode value.
# 
def setPSDCreationModeParameter(cntnr: Base.ControlParameterContainer, mode: Mode) -> None: pass

##
# \brief Tells whether the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_CREATION_MODE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The Pharm.ScreeningDBCreator.Mode value.
# 
def getPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> Mode: pass

##
# \brief Removes the Pharm.ControlParameter.PSD_CREATION_MODE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
# \param cntnr The control-parameter container.
# \param strict <tt>True</tt> to enable strict error checking, and <tt>False</tt> to disable it.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if strict error checking is enabled, and <tt>False</tt> otherwise.
# 
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
