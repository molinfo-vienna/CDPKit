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
# \brief Sets the Pharm.FeatureProperty.DISABLED_FLAG property of <em>feature</em>.
# 
# \param feature The feature.
# \param flag The new disabled-flag value.
# 
def setDisabledFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.DISABLED_FLAG property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the disabled flag is set, and <tt>False</tt> otherwise.
# 
def hasDisabledFlag(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.DISABLED_FLAG property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the feature is flagged as disabled, and <tt>False</tt> otherwise.
# 
def getDisabledFlag(feature: Feature) -> bool: pass

##
# \brief Removes the Pharm.FeatureProperty.DISABLED_FLAG property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearDisabledFlag(feature: Feature) -> None: pass

##
# \brief Generates a string describing the per-atom residue environment of <em>feature</em> (residue names and atom names of interacting pocket atoms).
# 
# \param feature The feature.
# 
# \return The generated environment-residue-atom info string. 
# 
# \since 1.4
# 
def getEnvironmentResidueAtomInfo(feature: Feature) -> str: pass

##
# \brief Generates a string describing the residue environment of <em>feature</em> (residue names of interacting pocket residues).
# 
# \param feature The feature.
# 
# \return The generated environment-residue info string. 
# 
# \since 1.3
# 
def getEnvironmentResidueInfo(feature: Feature) -> str: pass

##
# \brief Sets the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of <em>feature</em>.
# 
# \param feature The feature.
# \param substruct The new environment substructure.
# 
def setEnvironmentSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the environment substructure property is set, and <tt>False</tt> otherwise.
# 
def hasEnvironmentSubstructure(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property of <em>feature</em> (interacting pocket residues).
# 
# \param feature The feature.
# 
# \return A reference to the environment substructure. 
# 
# \since 1.4
# 
def getEnvironmentSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief Removes the Pharm.FeatureProperty.ENVIRONMENT_SUBSTRUCTURE property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearEnvironmentSubstructure(feature: Feature) -> None: pass

##
# \brief Collects the atoms of the molecular substructures underlying the features of <em>cntnr</em> into <em>atoms</em>.
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
# \brief Returns the number of features in <em>cntnr</em> whose type matches <em>type</em>.
# 
# \param cntnr The feature container.
# \param type The Pharm.FeatureType to count.
# 
# \return The number of features of the specified type.
# 
def getFeatureCount(cntnr: FeatureContainer, type: int) -> int: pass

##
# \brief Returns a concise human-readable string (e.g. <em>"HBD"</em> for H-bond donor) for the given numeric feature type identifier <em>ftr_type</em>.
# 
# \param ftr_type The numeric feature type identifier (see namespace Pharm.FeatureType).
# 
# \return A reference to the feature type string.
# 
def getFeatureTypeString(ftr_type: int) -> str: pass

##
# \brief Extracts features from <em>mapping</em> into <em>ftr_set</em>.
# 
# \param ftr_set The output feature set.
# \param mapping The feature mapping.
# \param first If <tt>True</tt>, the first feature of each mapping pair is added; otherwise the second feature.
# 
def getFeatures(ftr_set: FeatureSet, mapping: FeatureMapping, first: bool) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.GEOMETRY property of <em>feature</em>.
# 
# \param feature The feature.
# \param geom The new Pharm.FeatureGeometry identifier.
# 
def setGeometry(feature: Feature, geom: int) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.GEOMETRY property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the geometry property is set, and <tt>False</tt> otherwise.
# 
def hasGeometry(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.GEOMETRY property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The Pharm.FeatureGeometry identifier.
# 
def getGeometry(feature: Feature) -> int: pass

##
# \brief Removes the Pharm.FeatureProperty.GEOMETRY property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearGeometry(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.HYDROPHOBICITY property of <em>feature</em>.
# 
# \param feature The feature.
# \param hyd The new hydrophobicity value.
# 
def setHydrophobicity(feature: Feature, hyd: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.HYDROPHOBICITY property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the hydrophobicity property is set, and <tt>False</tt> otherwise.
# 
def hasHydrophobicity(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.HYDROPHOBICITY property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The hydrophobicity value.
# 
def getHydrophobicity(feature: Feature) -> float: pass

##
# \brief Removes the Pharm.FeatureProperty.HYDROPHOBICITY property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearHydrophobicity(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.LENGTH property of <em>feature</em>.
# 
# \param feature The feature.
# \param length The new length value.
# 
def setLength(feature: Feature, length: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.LENGTH property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the length property is set, and <tt>False</tt> otherwise.
# 
def hasLength(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.LENGTH property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The length value.
# 
def getLength(feature: Feature) -> float: pass

##
# \brief Removes the Pharm.FeatureProperty.LENGTH property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearLength(feature: Feature) -> None: pass

##
# \brief Sets the name of the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container.
# \param name The new name.
# 
def setName(cntnr: FeatureContainer, name: str) -> None: pass

##
# \brief Tells whether a name has been set for the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container.
# 
# \return <tt>True</tt> if the name property is set, and <tt>False</tt> otherwise.
# 
def hasName(cntnr: FeatureContainer) -> bool: pass

##
# \brief Returns the name of the feature container <em>cntnr</em> (stored as Pharm.FeatureContainerProperty.NAME).
# 
# \param cntnr The feature container.
# 
# \return The name (or an empty string if the property is not set).
# 
def getName(cntnr: FeatureContainer) -> str: pass

##
# \brief Removes the name property from the feature container <em>cntnr</em>.
# 
# \param cntnr The feature container.
# 
def clearName(cntnr: FeatureContainer) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.OPTIONAL_FLAG property of <em>feature</em>.
# 
# \param feature The feature.
# \param flag The new optional-flag value.
# 
def setOptionalFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.OPTIONAL_FLAG property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the optional flag is set, and <tt>False</tt> otherwise.
# 
def hasOptionalFlag(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.OPTIONAL_FLAG property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the feature is flagged as optional, and <tt>False</tt> otherwise.
# 
def getOptionalFlag(feature: Feature) -> bool: pass

##
# \brief Removes the Pharm.FeatureProperty.OPTIONAL_FLAG property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearOptionalFlag(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.ORIENTATION property of <em>feature</em>.
# 
# \param feature The feature.
# \param orient The new 3D orientation vector.
# 
def setOrientation(feature: Feature, orient: Math.Vector3D) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.ORIENTATION property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the orientation property is set, and <tt>False</tt> otherwise.
# 
def hasOrientation(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.ORIENTATION property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return A reference to the 3D orientation vector.
# 
def getOrientation(feature: Feature) -> Math.Vector3D: pass

##
# \brief Removes the Pharm.FeatureProperty.ORIENTATION property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearOrientation(feature: Feature) -> None: pass

##
# \brief Clears the orientation property of every feature in <em>cntnr</em> and (optionally) resets each feature's geometry to Pharm.FeatureGeometry.SPHERE.
# 
# \param cntnr The feature container.
# \param fix_geom If <tt>True</tt>, the geometry of each feature is set to Pharm.FeatureGeometry.SPHERE after clearing the orientation.
# 
# \since 1.2
# 
def clearOrientations(cntnr: FeatureContainer, fix_geom: bool = True) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.SUBSTRUCTURE property of <em>feature</em>.
# 
# \param feature The feature.
# \param substruct The new feature substructure.
# 
def setSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.SUBSTRUCTURE property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the substructure property is set, and <tt>False</tt> otherwise.
# 
def hasSubstructure(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.SUBSTRUCTURE property of <em>feature</em> (the underlying atoms/bonds).
# 
# \param feature The feature.
# 
# \return A reference to the feature substructure.
# 
def getSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief Removes the Pharm.FeatureProperty.SUBSTRUCTURE property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearSubstructure(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.TOLERANCE property of <em>feature</em>.
# 
# \param feature The feature.
# \param tol The new tolerance value.
# 
def setTolerance(feature: Feature, tol: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.TOLERANCE property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the tolerance property is set, and <tt>False</tt> otherwise.
# 
def hasTolerance(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.TOLERANCE property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The tolerance value.
# 
def getTolerance(feature: Feature) -> float: pass

##
# \brief Removes the Pharm.FeatureProperty.TOLERANCE property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearTolerance(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.TYPE property of <em>feature</em>.
# 
# \param feature The feature.
# \param type The new Pharm.FeatureType identifier.
# 
def setType(feature: Feature, type: int) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.TYPE property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the type property is set, and <tt>False</tt> otherwise.
# 
def hasType(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.TYPE property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The Pharm.FeatureType identifier.
# 
def getType(feature: Feature) -> int: pass

##
# \brief Removes the Pharm.FeatureProperty.TYPE property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearType(feature: Feature) -> None: pass

##
# \brief Sets the Pharm.FeatureProperty.WEIGHT property of <em>feature</em>.
# 
# \param feature The feature.
# \param weight The new weight value.
# 
def setWeight(feature: Feature, weight: float) -> None: pass

##
# \brief Tells whether the Pharm.FeatureProperty.WEIGHT property of <em>feature</em> has been set.
# 
# \param feature The feature.
# 
# \return <tt>True</tt> if the weight property is set, and <tt>False</tt> otherwise.
# 
def hasWeight(feature: Feature) -> bool: pass

##
# \brief Returns the Pharm.FeatureProperty.WEIGHT property of <em>feature</em>.
# 
# \param feature The feature.
# 
# \return The weight value.
# 
def getWeight(feature: Feature) -> float: pass

##
# \brief Removes the Pharm.FeatureProperty.WEIGHT property from <em>feature</em>.
# 
# \param feature The feature.
# 
def clearWeight(feature: Feature) -> None: pass

##
# \brief Tests whether the exclusion-volume features in <em>ftr_cntnr</em> remain clash-free with respect to the transformed atom positions of <em>atom_cntnr</em>.
# 
# Each enabled feature of type Pharm.FeatureType.EXCLUSION_VOLUME is checked against every atom of <em>atom_cntnr:</em> a clash is reported as soon as the distance between feature and atom is smaller than the sum of the feature's position tolerance and <em>vdw_factor</em> times the atom's Van der Waals radius.
# 
# \param ftr_cntnr The feature container providing the exclusion-volume features.
# \param atom_cntnr The atom container providing the test atoms.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param xform The 4x4 transformation applied to the atom coordinates before the clash test.
# \param vdw_factor Scaling factor for the per-atom Van der Waals radii; if &le; 0 the atoms are treated as point particles.
# 
# \return <tt>True</tt> if no clash is detected, and <tt>False</tt> otherwise.
# 
def checkForExclusionVolumeClashes(ftr_cntnr: FeatureContainer, atom_cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, xform: Math.Matrix4D, vdw_factor: float = 1.0) -> bool: pass

##
# \brief Creates exclusion-volume features at the 3D positions of the atoms in <em>cntnr</em> and appends them to <em>pharm</em>.
# 
# \param pharm The pharmacophore receiving the new exclusion volumes.
# \param cntnr The atom container providing the seed positions.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param tol The position tolerance to assign to new exclusion volumes (if &le; 0, the per-atom vdW radius is used).
# \param min_dist Minimum distance (<em>rel_dist</em> controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
# \param rel_dist If <tt>True</tt>, the per-pair tolerance sum is subtracted from the pair distance before testing against <em>min_dist</em>; otherwise the absolute distance is tested.
# \param append If <tt>False</tt>, <em>pharm</em> is cleared before any exclusion volumes are added.
# 
def createExclusionVolumes(pharm: Pharmacophore, cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief Creates exclusion-volume features at the 3D positions of the features in <em>cntnr</em> and appends them to <em>pharm</em>.
# 
# \param pharm The pharmacophore receiving the new exclusion volumes.
# \param cntnr The feature container providing the seed positions.
# \param tol The position tolerance to assign to new exclusion volumes (if &le; 0, the per-feature tolerance is used).
# \param min_dist Minimum distance (<em>rel_dist</em> controls absolute vs. tolerance-corrected) that a new exclusion volume must keep from existing ones.
# \param rel_dist If <tt>True</tt>, the per-pair tolerance sum is subtracted from the pair distance before testing against <em>min_dist</em>; otherwise the absolute distance is tested.
# \param append If <tt>False</tt>, <em>pharm</em> is cleared before any exclusion volumes are added.
# 
def createExclusionVolumes(pharm: Pharmacophore, cntnr: FeatureContainer, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief Computes a per Pharm.FeatureType frequency histogram of the features in <em>cntnr</em>.
# 
# \param cntnr The feature container.
# \param hist The output histogram (feature type &rarr; count).
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
# \brief Builds an interaction pharmacophore from the supplied feature-to-feature mapping by emitting one feature per source feature, optionally enriched with orientation vectors and environment substructures derived from the mapped partner features.
# 
# \param pharm The output pharmacophore where to add the generated features.
# \param iactions The feature-to-feature mapping describing the interactions.
# \param append If <tt>False</tt>, <em>pharm</em> is cleared before any features are added.
# 
def generateInteractionPharmacophore(pharm: Pharmacophore, iactions: FeatureMapping, append: bool = False) -> None: pass

##
# \brief Prepares <em>mol</em> for downstream pharmacophore generation by completing its hydrogens, perceiving SSSR, ring flags, implicit H counts, hybridization states and aromaticity, generating 3D coordinates for newly added hydrogens and (optionally) calculating per-atom hydrophobicities.
# 
# Failures of the hydrogen 3D-coordinate or residue-sequence-info derivation steps are silently caught and ignored; all other exceptions propagate.
# 
# \param mol The molecule to prepare (modified in place).
# \param calc_hyd If <tt>True</tt>, atom hydrophobicities are also calculated and stored as atom properties.
# \param from_logp If <tt>True</tt> and <em>calc_hyd</em> is set, the hydrophobicities are derived from the XLogP atom contributions instead of the Greene algorithm.
# 
def prepareForPharmacophoreGeneration(mol: Chem.Molecule, calc_hyd: bool = True, from_logp: bool = False) -> None: pass

##
# \brief Removes every Pharm.FeatureType.EXCLUSION_VOLUME feature of <em>pharm</em> whose tolerance sphere clashes with any atom of <em>cntnr</em>.
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
# \brief Copies the features in <em>cntnr</em> into <em>tgt_set</em>, skipping every feature whose Pharm.FeatureType matches <em>type</em>.
# 
# \param cntnr The feature container providing the input features.
# \param tgt_set The feature set receiving the filtered features.
# \param type The Pharm.FeatureType to exclude.
# \param append If <tt>False</tt>, <em>tgt_set</em> is cleared before adding any features.
# 
# \return <tt>True</tt> if at least one feature was excluded, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removeFeaturesWithType(cntnr: FeatureContainer, tgt_set: FeatureSet, type: int, append: bool = False) -> bool: pass

##
# \brief Removes features of the given type from <em>ftr_set</em>.
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
# \brief Removes every feature in <em>pharm</em> whose Pharm.FeatureType matches <em>type</em>.
# 
# \param pharm The pharmacophore to filter.
# \param type The Pharm.FeatureType to remove.
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removeFeaturesWithType(pharm: Pharmacophore, type: int) -> bool: pass

##
# \brief Copies the features in <em>cntnr</em> into <em>tgt_set</em>, suppressing features that share both type and 3D position with an already-collected feature.
# 
# Two features count as duplicates if they have identical Pharm.FeatureType and their position vectors either match exactly (<em>pos_tol</em> &le; 0) or lie within <em>pos_tol</em> from each other. When a duplicate is detected, the feature with the larger position tolerance is retained.
# 
# \param cntnr The feature container providing the input features.
# \param tgt_set The feature set receiving the deduplicated features.
# \param pos_tol The position-equality tolerance in &Aring;ngstrom; values &le; 0 require an exact position match.
# \param append If <tt>False</tt>, <em>tgt_set</em> is cleared before adding any features.
# 
# \return <tt>True</tt> if at least one duplicate was detected, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removePositionalDuplicates(cntnr: FeatureContainer, tgt_set: FeatureSet, pos_tol: float = 0.0, append: bool = False) -> bool: pass

##
# \brief Removes features from <em>ftr_set</em> whose 3D position duplicates that of another feature of the same type.
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
# \brief Removes positional duplicate features from <em>pharm</em> in place.
# 
# Two features count as duplicates if they have identical Pharm.FeatureType and their position vectors either match exactly (<em>pos_tol</em> &le; 0) or lie within <em>pos_tol</em> from each other. When a duplicate is detected, the feature with the larger position tolerance is retained.
# 
# \param pharm The pharmacophore to deduplicate.
# \param pos_tol The position-equality tolerance in &Aring;ngstrom; values &le; 0 require an exact position match.
# 
# \return <tt>True</tt> if at least one feature was removed, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def removePositionalDuplicates(pharm: Pharmacophore, pos_tol: float = 0.0) -> bool: pass

##
# \brief Shrinks the tolerance of every Pharm.FeatureType.EXCLUSION_VOLUME feature of <em>pharm</em> whose tolerance sphere clashes with any atom of <em>cntnr</em>; removes the exclusion volume when the resulting tolerance falls below 0.25.
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
# \brief Applies the affine transformation <em>mtx</em> to the 3D position (and, if set, the orientation vector) of every feature in <em>cntnr</em>.
# 
# \param cntnr The feature container to transform.
# \param mtx The 4x4 transformation matrix.
# 
def transform3DCoordinates(cntnr: FeatureContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief Sets the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> to <em>single_prec</em>.
# 
# \param cntnr The control-parameter container.
# \param single_prec <tt>True</tt> to write single-precision floats, and <tt>False</tt> to write double-precision floats.
# 
# \since 1.2
# 
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em>.
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
# \brief Sets the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em> to <em>allow</em>.
# 
# \param cntnr The control-parameter container.
# \param allow <tt>True</tt> to allow duplicate database entries, and <tt>False</tt> to reject them.
# 
def setPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer, allow: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_ALLOW_DUPLICATES parameter of <em>cntnr</em>.
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
# \brief Sets the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em> to <em>mode</em>.
# 
# \param cntnr The control-parameter container.
# \param mode The new Pharm.ScreeningDBCreator.Mode value.
# 
def setPSDCreationModeParameter(cntnr: Base.ControlParameterContainer, mode: Mode) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.PSD_CREATION_MODE parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.PSD_CREATION_MODE parameter of <em>cntnr</em>.
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
# \brief Sets the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
# \param cntnr The control-parameter container.
# \param strict <tt>True</tt> to enable strict error checking, and <tt>False</tt> to disable it.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether <em>cntnr</em> carries an explicit Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Pharm.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em>.
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
