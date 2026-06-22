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
# \brief Sets the value of the Chem.AtomProperty.COORDINATES_2D property of the atom <em>atom</em> to <em>coords</em>.
# 
# \param atom The atom for which to set the property value.
# \param coords The new 2D coordinates.
# 
def set2DCoordinates(atom: Atom, coords: Math.Vector2D) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.COORDINATES_2D property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def has2DCoordinates(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.COORDINATES_2D property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored 2D coordinates.
# 
def get2DCoordinates(atom: Atom) -> Math.Vector2D: pass

##
# \brief Clears the value of the Chem.AtomProperty.COORDINATES_2D property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clear2DCoordinates(atom: Atom) -> None: pass

##
# \brief Writes the 2D coordinates in <em>coords</em> back to the corresponding atoms of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param coords The 2D coordinates to assign (must contain at least one entry per atom).
# 
def set2DCoordinates(cntnr: AtomContainer, coords: Math.Vector2DArray) -> None: pass

##
# \brief Extracts the 2D coordinates of all atoms in <em>cntnr</em> into <em>coords</em>.
# 
# \param cntnr The atom container.
# \param coords The output 2D-coordinate array.
# \param append If <tt>True</tt>, the coordinates are appended to <em>coords</em>. Otherwise, <em>coords</em> is cleared first.
# 
def get2DCoordinates(cntnr: AtomContainer, coords: Math.Vector2DArray, append: bool = False) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.STEREO_2D_FLAG property of the bond <em>bond</em> to <em>flag</em>.
# 
# \param bond The bond for which to set the property value.
# \param flag The new 2D stereo flag value (see namespace Chem.BondStereoFlag).
# 
def set2DStereoFlag(bond: Bond, flag: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.STEREO_2D_FLAG property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def has2DStereoFlag(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.STEREO_2D_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored 2D stereo flag (see namespace Chem.BondStereoFlag).
# 
def get2DStereoFlag(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.STEREO_2D_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clear2DStereoFlag(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.COORDINATES_3D_ARRAY property of the atom <em>atom</em> to <em>coords_array</em>.
# 
# \param atom The atom for which to set the property value.
# \param coords_array The new 3D conformer-coordinates array.
# 
def set3DCoordinatesArray(atom: Atom, coords_array: Math.Vector3DArray) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.COORDINATES_3D_ARRAY property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def has3DCoordinatesArray(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.COORDINATES_3D_ARRAY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored 3D conformer-coordinates array.
# 
def get3DCoordinatesArray(atom: Atom) -> Math.Vector3DArray: pass

##
# \brief Clears the value of the Chem.AtomProperty.COORDINATES_3D_ARRAY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clear3DCoordinatesArray(atom: Atom) -> None: pass

##
# \brief Extracts the 3D coordinates of all atoms in <em>cntnr</em> into <em>coords</em> using the per-atom coordinate lookup function <em>coords_func</em>.
# 
# \param cntnr The atom container.
# \param coords The output 3D-coordinate array.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param append If <tt>True</tt>, the coordinates are appended to <em>coords</em>. Otherwise, <em>coords</em> is cleared first.
# 
def get3DCoordinates(cntnr: AtomContainer, coords: Math.Vector3DArray, coords_func: Atom3DCoordinatesFunction, append: bool = False) -> None: pass

##
# \brief Sets the value of the Chem.Entity3DProperty.COORDINATES_3D property of the 3D entity <em>entity</em> to <em>coords</em>.
# 
# \param entity The 3D entity for which to set the property value.
# \param coords The new 3D coordinates.
# 
def set3DCoordinates(entity: Entity3D, coords: Math.Vector3D) -> None: pass

##
# \brief Tells whether the Chem.Entity3DProperty.COORDINATES_3D property of the 3D entity <em>entity</em> is set.
# 
# \param entity The 3D entity for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def has3DCoordinates(entity: Entity3D) -> bool: pass

##
# \brief Returns the value of the Chem.Entity3DProperty.COORDINATES_3D property of the 3D entity <em>entity</em>.
# 
# \param entity The 3D entity for which to return the property value.
# 
# \return The stored 3D coordinates. 
# 
# \throw Base.ItemNotFound if the property has not been set.
# 
def get3DCoordinates(entity: Entity3D) -> Math.Vector3D: pass

##
# \brief Clears the value of the Chem.Entity3DProperty.COORDINATES_3D property of the 3D entity <em>entity</em>.
# 
# \param entity The 3D entity for which to clear the property value.
# 
def clear3DCoordinates(entity: Entity3D) -> None: pass

##
# \brief Sets the 3D coordinates of the entities of <em>cntnr</em> from <em>coords</em>.
# 
# \param cntnr The entity 3D container whose coordinates are to be updated.
# \param coords The input coordinates array (must contain at least one position per entity in <em>cntnr</em>).
# 
def set3DCoordinates(cntnr: Entity3DContainer, coords: Math.Vector3DArray) -> None: pass

##
# \brief Stores the 3D coordinates of the entities of <em>cntnr</em> in <em>coords</em>.
# 
# \param cntnr The entity 3D container providing the source coordinates.
# \param coords The output coordinates array.
# \param append If <tt>True</tt>, the entity coordinates are appended to <em>coords</em>. If <tt>False</tt>, <em>coords</em> is cleared first.
# 
def get3DCoordinates(cntnr: Entity3DContainer, coords: Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief Returns the subset of the aromatic rings of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The aromatic rings.
# 
def getAromaticRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Returns the subset of the SSSR of the molecular graph <em>molgraph</em> that contains only aromatic rings,.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The aromatic-SSSR subset.
# 
def getAromaticSSSRSubset(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.AROMATIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em> to <em>substruct</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param substruct The new aromatic substructure.
# 
def setAromaticSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.AROMATIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAromaticSubstructure(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.AROMATIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored aromatic substructure.
# 
def getAromaticSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.AROMATIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearAromaticSubstructure(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.AROMATICITY_FLAG property of the atom <em>atom</em> to <em>aromatic</em>.
# 
# \param atom The atom for which to set the property value.
# \param aromatic <tt>True</tt> to flag the atom as aromatic, and <tt>False</tt> to flag it as non-aromatic.
# 
def setAromaticityFlag(atom: Atom, aromatic: bool) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.AROMATICITY_FLAG property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAromaticityFlag(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.AROMATICITY_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return <tt>True</tt> if the atom is flagged as aromatic, and <tt>False</tt> otherwise.
# 
def getAromaticityFlag(atom: Atom) -> bool: pass

##
# \brief Clears the value of the Chem.AtomProperty.AROMATICITY_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearAromaticityFlag(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.AROMATICITY_FLAG property of the bond <em>bond</em> to <em>aromatic</em>.
# 
# \param bond The bond for which to set the property value.
# \param aromatic <tt>True</tt> to flag the bond as aromatic, and <tt>False</tt> to flag it as non-aromatic.
# 
def setAromaticityFlag(bond: Bond, aromatic: bool) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.AROMATICITY_FLAG property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAromaticityFlag(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.AROMATICITY_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return <tt>True</tt> if the bond is flagged as aromatic, and <tt>False</tt> otherwise.
# 
def getAromaticityFlag(bond: Bond) -> bool: pass

##
# \brief Clears the value of the Chem.BondProperty.AROMATICITY_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearAromaticityFlag(bond: Bond) -> None: pass

##
# \brief Perceives aromaticity and sets the corresponding atom/bond aromaticity flags on the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing aromaticity flags.
# 
def setAromaticityFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.ATOM_MAPPING_ID property of the atom <em>atom</em> to <em>id</em>.
# 
# \param atom The atom for which to set the property value.
# \param id The new reactant-to-product atom-mapping ID.
# 
def setAtomMappingID(atom: Atom, id: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.ATOM_MAPPING_ID property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomMappingID(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.ATOM_MAPPING_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored reactant-to-product atom-mapping ID.
# 
def getAtomMappingID(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.ATOM_MAPPING_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearAtomMappingID(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.ATOM_MAPPING property of the reaction <em>rxn</em> to <em>mapping</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param mapping The new reactant-to-product atom mapping.
# 
def setAtomMapping(rxn: Reaction, mapping: AtomMapping) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.ATOM_MAPPING property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasAtomMapping(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.ATOM_MAPPING property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored reactant-to-product atom mapping.
# 
def getAtomMapping(rxn: Reaction) -> AtomMapping: pass

##
# \brief Clears the value of the Chem.ReactionProperty.ATOM_MAPPING property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearAtomMapping(rxn: Reaction) -> None: pass

##
# \brief Sets the atom-level match constraint list <em>constr</em> on every atom of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param constr The match constraint list to assign.
# \param overwrite If <tt>True</tt>, replaces any existing per-atom constraints. If <tt>False</tt>, leaves atoms that already carry a list unchanged.
# 
def setAtomMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief Sets the atom-level match constraint list <em>constr</em> on every atom of every component of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to modify.
# \param constr The match constraint list to assign.
# \param overwrite If <tt>True</tt>, replaces any existing per-atom constraints. If <tt>False</tt>, leaves atoms that already carry a list unchanged.
# 
def setAtomMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief Sets the atom symbols of the molecular graph <em>molgraph</em> from their atom types.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing atom symbols.
# 
def setAtomSymbolsFromTypes(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Sets the atom types of the molecular graph <em>molgraph</em> from their element symbols.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing atom types.
# 
def setAtomTypesFromSymbols(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Sets the bond-level match constraint list <em>constr</em> on every bond of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param constr The match constraint list to assign.
# \param overwrite If <tt>True</tt>, replaces any existing per-bond constraints. If <tt>False</tt>, leaves bonds that already carry a list unchanged.
# 
def setBondMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief Sets the bond-level match constraint list <em>constr</em> on every bond of every component of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to modify.
# \param constr The match constraint list to assign.
# \param overwrite If <tt>True</tt>, replaces any existing per-bond constraints. If <tt>False</tt>, leaves bonds that already carry a list unchanged.
# 
def setBondMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.CIP_CONFIGURATION property of the atom <em>atom</em> to <em>config</em>.
# 
# \param atom The atom for which to set the property value.
# \param config The new CIP configuration label (see namespace Chem.CIPDescriptor).
# 
def setCIPConfiguration(atom: Atom, config: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.CIP_CONFIGURATION property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasCIPConfiguration(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.CIP_CONFIGURATION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored CIP configuration label (see namespace Chem.CIPDescriptor).
# 
def getCIPConfiguration(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.CIP_CONFIGURATION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearCIPConfiguration(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.CIP_CONFIGURATION property of the bond <em>bond</em> to <em>config</em>.
# 
# \param bond The bond for which to set the property value.
# \param config The new CIP configuration label (see namespace Chem.CIPDescriptor).
# 
def setCIPConfiguration(bond: Bond, config: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.CIP_CONFIGURATION property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasCIPConfiguration(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.CIP_CONFIGURATION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored CIP configuration label (see namespace Chem.CIPDescriptor).
# 
def getCIPConfiguration(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.CIP_CONFIGURATION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearCIPConfiguration(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.CIP_PRIORITY property of the atom <em>atom</em> to <em>priority</em>.
# 
# \param atom The atom for which to set the property value.
# \param priority The new CIP priority.
# 
def setCIPPriority(atom: Atom, priority: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.CIP_PRIORITY property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasCIPPriority(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.CIP_PRIORITY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored CIP priority.
# 
def getCIPPriority(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.CIP_PRIORITY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearCIPPriority(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.CANONICAL_NUMBER property of the atom <em>atom</em> to <em>num</em>.
# 
# \param atom The atom for which to set the property value.
# \param num The new canonical number.
# 
def setCanonicalNumber(atom: Atom, num: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.CANONICAL_NUMBER property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasCanonicalNumber(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.CANONICAL_NUMBER property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored canonical number.
# 
def getCanonicalNumber(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.CANONICAL_NUMBER property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearCanonicalNumber(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.COMMENT property of the molecular graph <em>molgraph</em> to <em>comment</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param comment The new comment string.
# 
def setComment(molgraph: MolecularGraph, comment: str) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.COMMENT property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComment(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.COMMENT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored comment.
# 
def getComment(molgraph: MolecularGraph) -> str: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.COMMENT property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearComment(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.COMMENT property of the reaction <em>rxn</em> to <em>comment</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param comment The new comment string.
# 
def setComment(rxn: Reaction, comment: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.COMMENT property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComment(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.COMMENT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored comment.
# 
def getComment(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.COMMENT property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearComment(rxn: Reaction) -> None: pass

##
# \brief Returns the number of bonds of the molecular graph <em>molgraph</em> whose connected atoms are likewise contained in <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The count of non-dangling bonds.
# 
def getCompleteBondCount(molgraph: MolecularGraph) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.COMPONENT_GROUP_ID property of the atom <em>atom</em> to <em>id</em>.
# 
# \param atom The atom for which to set the property value.
# \param id The new component-group ID.
# 
def setComponentGroupID(atom: Atom, id: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.COMPONENT_GROUP_ID property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentGroupID(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.COMPONENT_GROUP_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored component-group ID.
# 
def getComponentGroupID(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.COMPONENT_GROUP_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearComponentGroupID(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.COMPONENT_GROUPS property of the molecular graph <em>molgraph</em> to <em>comp_groups</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param comp_groups The new component-group fragment list.
# 
def setComponentGroups(molgraph: MolecularGraph, comp_groups: FragmentList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.COMPONENT_GROUPS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentGroups(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.COMPONENT_GROUPS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored component-group fragment list.
# 
def getComponentGroups(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.COMPONENT_GROUPS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearComponentGroups(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.COMPONENT_GROUPS property of the reaction <em>rxn</em> to <em>comp_groups</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param comp_groups The new component-group fragment list.
# 
def setComponentGroups(rxn: Reaction, comp_groups: FragmentList) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.COMPONENT_GROUPS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponentGroups(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.COMPONENT_GROUPS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored component-group fragment list.
# 
def getComponentGroups(rxn: Reaction) -> FragmentList: pass

##
# \brief Clears the value of the Chem.ReactionProperty.COMPONENT_GROUPS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearComponentGroups(rxn: Reaction) -> None: pass

##
# \brief Sets the molecular graph-level match constraint list <em>constr</em> on every component of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to modify.
# \param constr The match constraint list to assign.
# \param overwrite If <tt>True</tt>, replaces any existing per-component constraints. If <tt>False</tt>, leaves components that already carry a list unchanged.
# 
def setComponentMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.COMPONENTS property of the molecular graph <em>molgraph</em> to <em>comps</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param comps The new connected-component list.
# 
def setComponents(molgraph: MolecularGraph, comps: FragmentList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.COMPONENTS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasComponents(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.COMPONENTS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored connected-component list.
# 
def getComponents(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.COMPONENTS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearComponents(molgraph: MolecularGraph) -> None: pass

##
# \brief Extracts the conformation at index <em>conf_idx</em> into <em>coords</em>.
# 
# \param cntnr The atom container.
# \param conf_idx The zero-based conformation index.
# \param coords The output 3D-coordinate array.
# \param append If <tt>True</tt>, the coordinates are appended to <em>coords</em>. Otherwise, <em>coords</em> is cleared first.
# 
def getConformation(cntnr: AtomContainer, conf_idx: int, coords: Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief Returns the energy of the conformation at index <em>conf_idx</em>.
# 
# \param molgraph The molecular graph to query.
# \param conf_idx The zero-based conformation index.
# 
# \return The energy of the requested conformation.
# 
def getConformationEnergy(molgraph: MolecularGraph, conf_idx: int) -> float: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.CONFORMATION_INDEX property of the molecular graph <em>molgraph</em> to <em>index</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param index The new zero-based conformation index.
# 
def setConformationIndex(molgraph: MolecularGraph, index: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.CONFORMATION_INDEX property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasConformationIndex(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.CONFORMATION_INDEX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored zero-based conformation index.
# 
def getConformationIndex(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.CONFORMATION_INDEX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearConformationIndex(molgraph: MolecularGraph) -> None: pass

##
# \brief Overwrites the conformation at index <em>conf_idx</em> with the supplied coordinates and energy.
# 
# \param molgraph The molecular graph to modify.
# \param conf_idx The zero-based conformation index.
# \param coords The 3D coordinates of the conformation.
# \param energy The energy associated with the conformation.
# 
def setConformation(molgraph: MolecularGraph, conf_idx: int, coords: Math.Vector3DArray, energy: float) -> None: pass

##
# \brief Removes all stored conformations from the atoms of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
def clearConformations(cntnr: AtomContainer) -> None: pass

##
# \brief Returns the 3D coordinates of the atom <em>atom</em> for conformer <em>conf_idx</em> (from the Chem.AtomProperty.COORDINATES_3D_ARRAY property).
# 
# \param atom The atom for which to return the conformer 3D coordinates.
# \param conf_idx The zero-based conformer index.
# 
# \return The 3D coordinates of the specified conformer.
# 
def getConformer3DCoordinates(atom: Atom, conf_idx: int) -> Math.Vector3D: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.CONFORMER_ENERGIES property of the molecular graph <em>molgraph</em> to <em>energies</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param energies The new per-conformer energy array.
# 
def setConformerEnergies(molgraph: MolecularGraph, energies: Util.DArray) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.CONFORMER_ENERGIES property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasConformerEnergies(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.CONFORMER_ENERGIES property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored per-conformer energy array.
# 
def getConformerEnergies(molgraph: MolecularGraph) -> Util.DArray: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.CONFORMER_ENERGIES property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearConformerEnergies(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param atoms 
# \param bonds 
# \param excl_atom 
# \return 
#
def getConnectedAtomsAndBonds(atom: Atom, molgraph: MolecularGraph, atoms: list, bonds: list, excl_atom: Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param atoms 
# \param excl_atom 
# \return 
#
def getConnectedAtoms(atom: Atom, molgraph: MolecularGraph, atoms: list, excl_atom: Atom) -> int: pass

##
# \brief Collects the fragments in <em>frag_list</em> that are fully contained in the molecular graph <em>molgraph</em> into <em>cont_frag_list</em>.
# 
# \param molgraph The host molecular graph.
# \param frag_list The candidate fragment list.
# \param cont_frag_list The output fragment list receiving the matches.
# \param append If <tt>True</tt>, matches are appended to <em>cont_frag_list</em>. Otherwise, it is cleared first.
# \param atoms If <tt>True</tt>, atom membership is required for a match.
# \param bonds If <tt>True</tt>, bond membership is required for a match.
# 
def getContainedFragments(molgraph: MolecularGraph, frag_list: FragmentList, cont_frag_list: FragmentList, append: bool = False, atoms: bool = True, bonds: bool = True) -> None: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \param cont_frag_list 
#
def getContainingFragments(atom: Atom, frag_list: FragmentList, cont_frag_list: FragmentList) -> None: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \param cont_frag_list 
#
def getContainingFragments(bond: Bond, frag_list: FragmentList, cont_frag_list: FragmentList) -> None: pass

##
# \brief Collects the fragments in <em>frag_list</em> that contain the molecular graph <em>molgraph</em> into <em>cont_frag_list</em>.
# 
# \param molgraph The query molecular graph.
# \param frag_list The candidate fragment list.
# \param cont_frag_list The output fragment list receiving the matches.
# \param append If <tt>True</tt>, matches are appended to <em>cont_frag_list</em>. Otherwise, it is cleared first.
# \param atoms If <tt>True</tt>, atom membership is required for a match.
# \param bonds If <tt>True</tt>, bond membership is required for a match.
# 
def getContainingFragments(molgraph: MolecularGraph, frag_list: FragmentList, cont_frag_list: FragmentList, append: bool = False, atoms: bool = True, bonds: bool = True) -> None: pass

##
# \brief Tells whether all atoms of <em>cntnr</em> carry coordinates of the given dimensionality.
# 
# \param cntnr The atom container.
# \param dim The coordinate dimensionality (<em>2</em> or <em>3</em>).
# 
# \return <tt>True</tt> if all atoms have the requested coordinates, and <tt>False</tt> otherwise.
# 
def hasCoordinates(cntnr: AtomContainer, dim: int) -> bool: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.CYCLIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em> to <em>substruct</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param substruct The new cyclic substructure.
# 
def setCyclicSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.CYCLIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasCyclicSubstructure(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.CYCLIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored cyclic substructure.
# 
def getCyclicSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.CYCLIC_SUBSTRUCTURE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearCyclicSubstructure(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.DIRECTION property of the bond <em>bond</em> to <em>dir</em>.
# 
# \param bond The bond for which to set the property value.
# \param dir The new bond direction descriptor (see namespace Chem.BondDirection).
# 
def setDirection(bond: Bond, dir: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.DIRECTION property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasDirection(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.DIRECTION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored <em>SMILES/SMARTS</em> bond direction descriptor (see namespace Chem.BondDirection).
# 
def getDirection(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.DIRECTION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearDirection(bond: Bond) -> None: pass

##
# \brief Collects every atom of the molecular graph <em>molgraph</em> that is within <em>max_dist</em> bonds of the atom <em>atom</em> into the fragment <em>env</em>.
# 
# \param atom The seed atom.
# \param molgraph The molecular graph providing the bonding context.
# \param max_dist The maximum topological distance.
# \param env The output fragment receiving the environment atoms and the bonds between them.
# \param append If <tt>True</tt>, atoms/bonds are appended to <em>env</em>. Otherwise, it is cleared first.
# 
# \return The number of atoms appended to <em>env</em>.
# 
def getEnvironment(atom: Atom, molgraph: MolecularGraph, max_dist: int, env: Fragment, append: bool = False) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.FORMAL_CHARGE property of the atom <em>atom</em> to <em>charge</em>.
# 
# \param atom The atom for which to set the property value.
# \param charge The new formal charge.
# 
def setFormalCharge(atom: Atom, charge: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.FORMAL_CHARGE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasFormalCharge(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.FORMAL_CHARGE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored formal charge.
# 
def getFormalCharge(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.FORMAL_CHARGE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearFormalCharge(atom: Atom) -> None: pass

##
# \brief Returns the generic atom type that the atom's Chem.AtomProperty.TYPE property value belongs to.
# 
# \param atom The atom to query.
# 
# \return The generic atom type.
# 
def getGenericType(atom: Atom) -> int: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em> to <em>mtx</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param mtx The new geometrical-distance matrix.
# 
def setGeometricalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.DMatrix) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasGeometricalDistanceMatrix(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored geometrical-distance matrix.
# 
def getGeometricalDistanceMatrix(molgraph: MolecularGraph) -> Math.DMatrix: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearGeometricalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.HASH_CODE property of the molecular graph <em>molgraph</em> to <em>hash_code</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param hash_code The new 64-bit hash code.
# 
def setHashCode(molgraph: MolecularGraph, hash_code: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.HASH_CODE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasHashCode(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.HASH_CODE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored 64-bit hash code.
# 
def getHashCode(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.HASH_CODE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearHashCode(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.HYBRIDIZATION property of the atom <em>atom</em> to <em>state</em>.
# 
# \param atom The atom for which to set the property value.
# \param state The new hybridization state (see namespace Chem.HybridizationState).
# 
def setHybridizationState(atom: Atom, state: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.HYBRIDIZATION property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasHybridizationState(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.HYBRIDIZATION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored hybridization state (see namespace Chem.HybridizationState).
# 
def getHybridizationState(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.HYBRIDIZATION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearHybridizationState(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.IMPLICIT_HYDROGEN_COUNT property of the atom <em>atom</em> to <em>count</em>.
# 
# \param atom The atom for which to set the property value.
# \param count The new implicit-hydrogen count.
# 
def setImplicitHydrogenCount(atom: Atom, count: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.IMPLICIT_HYDROGEN_COUNT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasImplicitHydrogenCount(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.IMPLICIT_HYDROGEN_COUNT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored implicit-hydrogen count.
# 
def getImplicitHydrogenCount(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.IMPLICIT_HYDROGEN_COUNT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearImplicitHydrogenCount(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param bonds 
# \param excl_atom 
# \return 
#
def getIncidentBonds(atom: Atom, molgraph: MolecularGraph, bonds: list, excl_atom: Atom) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.ISOTOPE property of the atom <em>atom</em> to <em>isotope</em>.
# 
# \param atom The atom for which to set the property value.
# \param isotope The new mass number (zero for the natural isotope mixture).
# 
def setIsotope(atom: Atom, isotope: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.ISOTOPE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasIsotope(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.ISOTOPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored mass number, or zero for the natural isotope mixture.
# 
def getIsotope(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.ISOTOPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearIsotope(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_CTAB_VERSION property of the molecular graph <em>molgraph</em> to <em>version</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param version The new CTAB version (see namespace Chem.MDLDataFormatVersion).
# 
def setMDLCTABVersion(molgraph: MolecularGraph, version: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_CTAB_VERSION property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLCTABVersion(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_CTAB_VERSION property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored CTAB version (see namespace Chem.MDLDataFormatVersion).
# 
def getMDLCTABVersion(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_CTAB_VERSION property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLCTABVersion(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_CHIRAL_FLAG property of the molecular graph <em>molgraph</em> to <em>flag</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param flag The new <em>MDL</em> chiral flag.
# 
def setMDLChiralFlag(molgraph: MolecularGraph, flag: bool) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_CHIRAL_FLAG property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLChiralFlag(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_CHIRAL_FLAG property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> chiral flag.
# 
def getMDLChiralFlag(molgraph: MolecularGraph) -> bool: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_CHIRAL_FLAG property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLChiralFlag(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_DIMENSIONALITY property of the molecular graph <em>molgraph</em> to <em>dim</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param dim The new <em>MDL</em> coordinate dimensionality.
# 
def setMDLDimensionality(molgraph: MolecularGraph, dim: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_DIMENSIONALITY property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLDimensionality(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_DIMENSIONALITY property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> coordinate dimensionality.
# 
def getMDLDimensionality(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_DIMENSIONALITY property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLDimensionality(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_ENERGY property of the molecular graph <em>molgraph</em> to <em>energy</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param energy The new <em>MDL</em> energy.
# 
def setMDLEnergy(molgraph: MolecularGraph, energy: float) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_ENERGY property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLEnergy(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_ENERGY property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> energy.
# 
def getMDLEnergy(molgraph: MolecularGraph) -> float: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_ENERGY property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLEnergy(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em> to <em>reg_no</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param reg_no The new <em>MDL</em> external registry number.
# 
def setMDLExternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLExternalRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> external registry number.
# 
def getMDLExternalRegistryNumber(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLExternalRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_INTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em> to <em>reg_no</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param reg_no The new <em>MDL</em> internal registry number.
# 
def setMDLInternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_INTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLInternalRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_INTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> internal registry number.
# 
def getMDLInternalRegistryNumber(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_INTERNAL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLInternalRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_MOLECULE_RECORD property of the reaction <em>rxn</em> to <em>mol_rec</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param mol_rec The new <em>MDL</em> molecule record.
# 
def setMDLMoleculeRecord(rxn: Reaction, mol_rec: Molecule) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_MOLECULE_RECORD property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLMoleculeRecord(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_MOLECULE_RECORD property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL RD-File</em> molecule record.
# 
def getMDLMoleculeRecord(rxn: Reaction) -> Molecule: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_MOLECULE_RECORD property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLMoleculeRecord(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MDL_PARITY property of the atom <em>atom</em> to <em>parity</em>.
# 
# \param atom The atom for which to set the property value.
# \param parity The new <em>MDL</em> stereo parity (see namespace Chem.MDLParity).
# 
def setMDLParity(atom: Atom, parity: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MDL_PARITY property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLParity(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MDL_PARITY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>MDL</em> stereo parity (see namespace Chem.MDLParity).
# 
def getMDLParity(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.MDL_PARITY property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMDLParity(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_PROGRAM_NAME property of the molecular graph <em>molgraph</em> to <em>name</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param name The new <em>MDL</em> program name.
# 
def setMDLProgramName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_PROGRAM_NAME property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLProgramName(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_PROGRAM_NAME property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> program name.
# 
def getMDLProgramName(molgraph: MolecularGraph) -> str: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_PROGRAM_NAME property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLProgramName(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_PROGRAM_NAME property of the reaction <em>rxn</em> to <em>name</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param name The new <em>MDL</em> program name.
# 
def setMDLProgramName(rxn: Reaction, name: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_PROGRAM_NAME property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLProgramName(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_PROGRAM_NAME property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> program name.
# 
def getMDLProgramName(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_PROGRAM_NAME property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLProgramName(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_RXN_FILE_VERSION property of the reaction <em>rxn</em> to <em>version</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param version The new <em>MDL Rxn-File</em> version (see Chem.MDLDataFormatVersion).
# 
def setMDLRXNFileVersion(rxn: Reaction, version: int) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_RXN_FILE_VERSION property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLRXNFileVersion(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_RXN_FILE_VERSION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL Rxn-File</em> version (see Chem.MDLDataFormatVersion).
# 
def getMDLRXNFileVersion(rxn: Reaction) -> int: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_RXN_FILE_VERSION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLRXNFileVersion(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_REGISTRY_NUMBER property of the molecular graph <em>molgraph</em> to <em>reg_no</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param reg_no The new <em>MDL</em> registry number.
# 
def setMDLRegistryNumber(molgraph: MolecularGraph, reg_no: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_REGISTRY_NUMBER property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLRegistryNumber(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_REGISTRY_NUMBER property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> registry number.
# 
def getMDLRegistryNumber(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_REGISTRY_NUMBER property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLRegistryNumber(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_REGISTRY_NUMBER property of the reaction <em>rxn</em> to <em>reg_no</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param reg_no The new <em>MDL</em> registry number.
# 
def setMDLRegistryNumber(rxn: Reaction, reg_no: int) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_REGISTRY_NUMBER property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> registry number.
# 
def getMDLRegistryNumber(rxn: Reaction) -> int: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_REGISTRY_NUMBER property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR1 property of the molecular graph <em>molgraph</em> to <em>factor</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param factor The new <em>MDL</em> scaling factor 1.
# 
def setMDLScalingFactor1(molgraph: MolecularGraph, factor: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR1 property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLScalingFactor1(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR1 property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> scaling factor 1.
# 
def getMDLScalingFactor1(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR1 property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLScalingFactor1(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR2 property of the molecular graph <em>molgraph</em> to <em>factor</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param factor The new <em>MDL</em> scaling factor 2.
# 
def setMDLScalingFactor2(molgraph: MolecularGraph, factor: float) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR2 property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLScalingFactor2(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR2 property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> scaling factor 2.
# 
def getMDLScalingFactor2(molgraph: MolecularGraph) -> float: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_SCALING_FACTOR2 property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLScalingFactor2(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MDL_DB_STEREO_CARE_FLAG property of the atom <em>atom</em> to <em>flag</em>.
# 
# \param atom The atom for which to set the property value.
# \param flag The new <em>MDL</em> stereo-care flag.
# 
def setMDLStereoCareFlag(atom: Atom, flag: bool) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MDL_DB_STEREO_CARE_FLAG property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLStereoCareFlag(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MDL_DB_STEREO_CARE_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>MDL</em> stereo-care flag.
# 
def getMDLStereoCareFlag(atom: Atom) -> bool: pass

##
# \brief Clears the value of the Chem.AtomProperty.MDL_DB_STEREO_CARE_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMDLStereoCareFlag(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MDL_USER_INITIALS property of the molecular graph <em>molgraph</em> to <em>initials</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param initials The new <em>MDL</em> user initials.
# 
def setMDLUserInitials(molgraph: MolecularGraph, initials: str) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MDL_USER_INITIALS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLUserInitials(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MDL_USER_INITIALS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>MDL</em> user initials.
# 
def getMDLUserInitials(molgraph: MolecularGraph) -> str: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MDL_USER_INITIALS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMDLUserInitials(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MDL_USER_INITIALS property of the reaction <em>rxn</em> to <em>initials</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param initials The new <em>MDL</em> user initials.
# 
def setMDLUserInitials(rxn: Reaction, initials: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MDL_USER_INITIALS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMDLUserInitials(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MDL_USER_INITIALS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> user initials.
# 
def getMDLUserInitials(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MDL_USER_INITIALS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMDLUserInitials(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MOL2_CHARGE property of the atom <em>atom</em> to <em>charge</em>.
# 
# \param atom The atom for which to set the property value.
# \param charge The new <em>Sybyl MOL2</em> partial charge.
# 
def setMOL2Charge(atom: Atom, charge: float) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_CHARGE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2Charge(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_CHARGE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> partial charge.
# 
def getMOL2Charge(atom: Atom) -> float: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_CHARGE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2Charge(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MOL2_CHARGE_TYPE property of the molecular graph <em>molgraph</em> to <em>type</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param type The new <em>Sybyl MOL2</em> charge type (see namespace Chem.MOL2ChargeType).
# 
def setMOL2ChargeType(molgraph: MolecularGraph, type: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MOL2_CHARGE_TYPE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2ChargeType(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MOL2_CHARGE_TYPE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> charge type (see namespace Chem.MOL2ChargeType).
# 
def getMOL2ChargeType(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MOL2_CHARGE_TYPE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMOL2ChargeType(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MOL2_MOLECULE_TYPE property of the molecular graph <em>molgraph</em> to <em>type</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param type The new <em>Sybyl MOL2</em> molecule type (see namespace Chem.MOL2MoleculeType).
# 
def setMOL2MoleculeType(molgraph: MolecularGraph, type: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MOL2_MOLECULE_TYPE property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2MoleculeType(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MOL2_MOLECULE_TYPE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> molecule type (see namespace Chem.MOL2MoleculeType).
# 
def getMOL2MoleculeType(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MOL2_MOLECULE_TYPE property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMOL2MoleculeType(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MOL2_NAME property of the atom <em>atom</em> to <em>name</em>.
# 
# \param atom The atom for which to set the property value.
# \param name The new <em>Sybyl MOL2</em> atom name.
# 
def setMOL2Name(atom: Atom, name: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_NAME property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2Name(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> atom name.
# 
def getMOL2Name(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2Name(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_CHAIN property of the atom <em>atom</em> to <em>chain</em>.
# 
# \param atom The atom for which to set the property value.
# \param chain The new <em>Sybyl MOL2</em> substructure chain identifier.
# 
def setMOL2SubstructureChain(atom: Atom, chain: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_SUBSTRUCTURE_CHAIN property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2SubstructureChain(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_CHAIN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> substructure chain identifier.
# 
def getMOL2SubstructureChain(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_CHAIN property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2SubstructureChain(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_ID property of the atom <em>atom</em> to <em>id</em>.
# 
# \param atom The atom for which to set the property value.
# \param id The new <em>Sybyl MOL2</em> substructure ID.
# 
def setMOL2SubstructureID(atom: Atom, id: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_SUBSTRUCTURE_ID property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2SubstructureID(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> substructure ID.
# 
def getMOL2SubstructureID(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_ID property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2SubstructureID(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setMOL2SubstructureName(atom: Atom, name: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_SUBSTRUCTURE_NAME property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2SubstructureName(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> substructure name.
# 
def getMOL2SubstructureName(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2SubstructureName(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_SUBTYPE property of the atom <em>atom</em> to <em>subtype</em>.
# 
# \param atom The atom for which to set the property value.
# \param subtype The new <em>Sybyl MOL2</em> substructure subtype string.
# 
def setMOL2SubstructureSubtype(atom: Atom, subtype: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MOL2_SUBSTRUCTURE_SUBTYPE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMOL2SubstructureSubtype(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_SUBTYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> substructure subtype string.
# 
def getMOL2SubstructureSubtype(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.MOL2_SUBSTRUCTURE_SUBTYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMOL2SubstructureSubtype(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MATCH_CONSTRAINTS property of the atom <em>atom</em> to <em>constr</em>.
# 
# \param atom The atom for which to set the property value.
# \param constr The new match constraint list.
# 
def setMatchConstraints(atom: Atom, constr: MatchConstraintList) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MATCH_CONSTRAINTS property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchConstraints(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MATCH_CONSTRAINTS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored match constraint list.
# 
def getMatchConstraints(atom: Atom) -> MatchConstraintList: pass

##
# \brief Clears the value of the Chem.AtomProperty.MATCH_CONSTRAINTS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMatchConstraints(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.MATCH_CONSTRAINTS property of the bond <em>bond</em> to <em>constr</em>.
# 
# \param bond The bond for which to set the property value.
# \param constr The new match constraint list.
# 
def setMatchConstraints(bond: Bond, constr: MatchConstraintList) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.MATCH_CONSTRAINTS property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchConstraints(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.MATCH_CONSTRAINTS property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored match constraint list.
# 
def getMatchConstraints(bond: Bond) -> MatchConstraintList: pass

##
# \brief Clears the value of the Chem.BondProperty.MATCH_CONSTRAINTS property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearMatchConstraints(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MATCH_CONSTRAINTS property of the molecular graph <em>molgraph</em> to <em>constr</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param constr The new top-level match constraint list.
# 
def setMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MATCH_CONSTRAINTS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchConstraints(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MATCH_CONSTRAINTS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored top-level match constraint list.
# 
def getMatchConstraints(molgraph: MolecularGraph) -> MatchConstraintList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MATCH_CONSTRAINTS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMatchConstraints(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MATCH_CONSTRAINTS property of the reaction <em>rxn</em> to <em>constr</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param constr The new match constraint list to store.
# 
def setMatchConstraints(rxn: Reaction, constr: MatchConstraintList) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MATCH_CONSTRAINTS property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchConstraints(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MATCH_CONSTRAINTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored top-level match constraint list.
# 
def getMatchConstraints(rxn: Reaction) -> MatchConstraintList: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MATCH_CONSTRAINTS property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMatchConstraints(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MATCH_EXPRESSION property of the atom <em>atom</em> to <em>expr</em>.
# 
# \param atom The atom for which to set the property value.
# \param expr The new atom-level match expression.
# 
def setMatchExpression(atom: Atom, expr: AtomMatchExpression) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MATCH_EXPRESSION property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpression(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MATCH_EXPRESSION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored atom-level match expression.
# 
def getMatchExpression(atom: Atom) -> AtomMatchExpression: pass

##
# \brief Clears the value of the Chem.AtomProperty.MATCH_EXPRESSION property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMatchExpression(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.MATCH_EXPRESSION property of the bond <em>bond</em> to <em>expr</em>.
# 
# \param bond The bond for which to set the property value.
# \param expr The new bond-level match expression.
# 
def setMatchExpression(bond: Bond, expr: BondMatchExpression) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.MATCH_EXPRESSION property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpression(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.MATCH_EXPRESSION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored bond-level match expression.
# 
def getMatchExpression(bond: Bond) -> BondMatchExpression: pass

##
# \brief Clears the value of the Chem.BondProperty.MATCH_EXPRESSION property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearMatchExpression(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.MATCH_EXPRESSION property of the molecular graph <em>molgraph</em> to <em>expr</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param expr The new top-level match expression.
# 
def setMatchExpression(molgraph: MolecularGraph, expr: MolecularGraphMatchExpression) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.MATCH_EXPRESSION property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpression(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.MATCH_EXPRESSION property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored top-level match expression.
# 
def getMatchExpression(molgraph: MolecularGraph) -> MolecularGraphMatchExpression: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.MATCH_EXPRESSION property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearMatchExpression(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.MATCH_EXPRESSION property of the reaction <em>rxn</em> to <em>expr</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param expr The new match expression to store.
# 
def setMatchExpression(rxn: Reaction, expr: ReactionMatchExpression) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.MATCH_EXPRESSION property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpression(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.MATCH_EXPRESSION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored top-level reaction match expression.
# 
def getMatchExpression(rxn: Reaction) -> ReactionMatchExpression: pass

##
# \brief Clears the value of the Chem.ReactionProperty.MATCH_EXPRESSION property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearMatchExpression(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.MATCH_EXPRESSION_STRING property of the atom <em>atom</em> to <em>expr_str</em>.
# 
# \param atom The atom for which to set the property value.
# \param expr_str The new match expression string.
# 
def setMatchExpressionString(atom: Atom, expr_str: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MATCH_EXPRESSION_STRING property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpressionString(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MATCH_EXPRESSION_STRING property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored match expression string.
# 
def getMatchExpressionString(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.MATCH_EXPRESSION_STRING property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMatchExpressionString(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.MATCH_EXPRESSION_STRING property of the bond <em>bond</em> to <em>expr_str</em>.
# 
# \param bond The bond for which to set the property value.
# \param expr_str The new match expression string.
# 
def setMatchExpressionString(bond: Bond, expr_str: str) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.MATCH_EXPRESSION_STRING property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMatchExpressionString(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.MATCH_EXPRESSION_STRING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored match expression string.
# 
def getMatchExpressionString(bond: Bond) -> str: pass

##
# \brief Clears the value of the Chem.BondProperty.MATCH_EXPRESSION_STRING property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearMatchExpressionString(bond: Bond) -> None: pass

##
# \brief Returns the largest atom-mapping ID assigned to any atom of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The largest atom-mapping ID (zero if no atom carries an atom-mapping ID).
# 
def getMaxAtomMappingID(cntnr: AtomContainer) -> int: pass

##
# \brief Returns the largest atom-mapping ID found on any of the atoms in <em>rxn</em>.
# 
# \param rxn The reaction to scan.
# 
# \return The largest atom-mapping ID, or zero if no IDs are assigned.
# 
def getMaxAtomMappingID(rxn: Reaction) -> int: pass

##
# \brief Returns the largest component-group ID assigned to any atom of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The largest component-group ID (zero if no atom carries a component-group ID).
# 
def getMaxComponentGroupID(cntnr: AtomContainer) -> int: pass

##
# \brief Returns the largest component-group ID found on any of the components of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to scan.
# 
# \return The largest component-group ID, or zero if no IDs are assigned.
# 
def getMaxComponentGroupID(rxn: Reaction) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.MORGAN_NUMBER property of the atom <em>atom</em> to <em>num</em>.
# 
# \param atom The atom for which to set the property value.
# \param num The new Morgan number.
# 
def setMorganNumber(atom: Atom, num: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.MORGAN_NUMBER property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasMorganNumber(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.MORGAN_NUMBER property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored Morgan number.
# 
def getMorganNumber(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.MORGAN_NUMBER property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearMorganNumber(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.NAME property of the atom <em>atom</em> to <em>name</em>.
# 
# \param atom The atom for which to set the property value.
# \param name The new atom name.
# 
def setName(atom: Atom, name: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.NAME property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasName(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored atom name.
# 
def getName(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.NAME property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearName(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.NAME property of the molecular graph <em>molgraph</em> to <em>name</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param name The new name.
# 
def setName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.NAME property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasName(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.NAME property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored name.
# 
def getName(molgraph: MolecularGraph) -> str: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.NAME property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearName(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.NAME property of the reaction <em>rxn</em> to <em>name</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param name The new reaction name.
# 
def setName(rxn: Reaction, name: str) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.NAME property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasName(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.NAME property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored reaction name.
# 
def getName(rxn: Reaction) -> str: pass

##
# \brief Clears the value of the Chem.ReactionProperty.NAME property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearName(rxn: Reaction) -> None: pass

##
# \brief Returns the number of conformations stored on the atoms of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The conformation count.
# 
def getNumConformations(cntnr: AtomContainer) -> int: pass

##
# \brief Returns the number of fragments in <em>frag_list</em> that contain the atom <em>atom</em>.
# 
# \param atom The atom to query.
# \param frag_list The list of fragments to search.
# 
# \return The number of containing fragments.
# 
def getNumContainingFragments(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief Returns the number of fragments in <em>frag_list</em> that contain the bond <em>bond</em>.
# 
# \param bond The bond to query.
# \param frag_list The list of fragments to search.
# 
# \return The number of containing fragments.
# 
def getNumContainingFragments(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief Sets the value of the Chem.BondProperty.ORDER property of the bond <em>bond</em> to <em>order</em>.
# 
# \param bond The bond for which to set the property value.
# \param order The new bond order.
# 
def setOrder(bond: Bond, order: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.ORDER property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasOrder(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.ORDER property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored bond order.
# 
def getOrder(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.ORDER property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearOrder(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.PI_ELECTRON_SYSTEMS property of the molecular graph <em>molgraph</em> to <em>pi_systems</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param pi_systems The new pi-electron-system list.
# 
def setPiElectronSystems(molgraph: MolecularGraph, pi_systems: ElectronSystemList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.PI_ELECTRON_SYSTEMS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasPiElectronSystems(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.PI_ELECTRON_SYSTEMS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored pi-electron-system list.
# 
def getPiElectronSystems(molgraph: MolecularGraph) -> ElectronSystemList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.PI_ELECTRON_SYSTEMS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearPiElectronSystems(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.RADICAL_TYPE property of the atom <em>atom</em> to <em>type</em>.
# 
# \param atom The atom for which to set the property value.
# \param type The new radical type (see namespace Chem.RadicalType).
# 
def setRadicalType(atom: Atom, type: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.RADICAL_TYPE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRadicalType(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.RADICAL_TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored radical type (see namespace Chem.RadicalType).
# 
def getRadicalType(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.RADICAL_TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearRadicalType(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.REACTION_CENTER_STATUS property of the atom <em>atom</em> to <em>status</em>.
# 
# \param atom The atom for which to set the property value.
# \param status The new reaction-center status (see namespace Chem.ReactionCenterStatus).
# 
def setReactionCenterStatus(atom: Atom, status: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.REACTION_CENTER_STATUS property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterStatus(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.REACTION_CENTER_STATUS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored reaction-center status (see namespace Chem.ReactionCenterStatus).
# 
def getReactionCenterStatus(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.REACTION_CENTER_STATUS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearReactionCenterStatus(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.REACTION_CENTER_STATUS property of the bond <em>bond</em> to <em>status</em>.
# 
# \param bond The bond for which to set the property value.
# \param status The new reaction-center status (see namespace Chem.ReactionCenterStatus).
# 
def setReactionCenterStatus(bond: Bond, status: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.REACTION_CENTER_STATUS property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionCenterStatus(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.REACTION_CENTER_STATUS property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored reaction-center status (see namespace Chem.ReactionCenterStatus).
# 
def getReactionCenterStatus(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.REACTION_CENTER_STATUS property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearReactionCenterStatus(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.REACTION_DATA property of the reaction <em>rxn</em> to <em>data</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param data The new <em>MDL</em> reaction data block.
# 
def setReactionData(rxn: Reaction, data: StringDataBlock) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.REACTION_DATA property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasReactionData(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.REACTION_DATA property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored <em>MDL</em> reaction data block.
# 
def getReactionData(rxn: Reaction) -> StringDataBlock: pass

##
# \brief Clears the value of the Chem.ReactionProperty.REACTION_DATA property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearReactionData(rxn: Reaction) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.RING_FLAG property of the atom <em>atom</em> to <em>in_ring</em>.
# 
# \param atom The atom for which to set the property value.
# \param in_ring <tt>True</tt> to flag the atom as part of a ring, and <tt>False</tt> to flag it as acyclic.
# 
def setRingFlag(atom: Atom, in_ring: bool) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.RING_FLAG property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRingFlag(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.RING_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return <tt>True</tt> if the atom is flagged as part of any ring, and <tt>False</tt> otherwise.
# 
def getRingFlag(atom: Atom) -> bool: pass

##
# \brief Clears the value of the Chem.AtomProperty.RING_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearRingFlag(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.RING_FLAG property of the bond <em>bond</em> to <em>in_ring</em>.
# 
# \param bond The bond for which to set the property value.
# \param in_ring <tt>True</tt> to flag the bond as part of a ring, and <tt>False</tt> to flag it as acyclic.
# 
def setRingFlag(bond: Bond, in_ring: bool) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.RING_FLAG property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRingFlag(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.RING_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return <tt>True</tt> if the bond is flagged as part of any ring, and <tt>False</tt> otherwise.
# 
def getRingFlag(bond: Bond) -> bool: pass

##
# \brief Clears the value of the Chem.BondProperty.RING_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearRingFlag(bond: Bond) -> None: pass

##
# \brief Perceives ring membership and sets the corresponding atom/bond ring flags on the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing ring flags.
# 
def setRingFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.RINGS property of the molecular graph <em>molgraph</em> to <em>rings</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param rings The new full ring set.
# 
def setRings(molgraph: MolecularGraph, rings: FragmentList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.RINGS property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasRings(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.RINGS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored full ring set.
# 
def getRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.RINGS property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearRings(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.SSSR property of the molecular graph <em>molgraph</em> to <em>sssr</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param sssr The new Smallest Set of Smallest Rings.
# 
def setSSSR(molgraph: MolecularGraph, sssr: FragmentList) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.SSSR property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSSSR(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.SSSR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored Smallest Set of Smallest Rings.
# 
def getSSSR(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.SSSR property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearSSSR(molgraph: MolecularGraph) -> None: pass

##
# \brief Returns the size (in atoms) of the largest fragment in <em>frag_list</em> that contains the atom <em>atom</em>.
# 
# \param atom The atom to query.
# \param frag_list The list of fragments to search.
# 
# \return The largest containing fragment's size, or zero if no fragment contains <em>atom</em>.
# 
def getSizeOfLargestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief Returns the size (in atoms) of the largest fragment in <em>frag_list</em> that contains the bond <em>bond</em>.
# 
# \param bond The bond to query.
# \param frag_list The list of fragments to search.
# 
# \return The largest containing fragment's size, or zero if no fragment contains the bond <em>bond</em>.
# 
def getSizeOfLargestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief Returns the size (in atoms) of the smallest fragment in <em>frag_list</em> that contains the atom <em>atom</em>.
# 
# \param atom The atom to query.
# \param frag_list The list of fragments to search.
# 
# \return The smallest containing fragment's size, or zero if no fragment contains <em>atom</em>.
# 
def getSizeOfSmallestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief Returns the size (in atoms) of the smallest fragment in <em>frag_list</em> that contains the bond <em>bond</em>.
# 
# \param bond The bond to query.
# \param frag_list The list of fragments to search.
# 
# \return The smallest containing fragment's size, or zero if no fragment contains the bond <em>bond</em>.
# 
def getSizeOfSmallestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.STEREO_CENTER_FLAG property of the atom <em>atom</em> to <em>is_center</em>.
# 
# \param atom The atom for which to set the property value.
# \param is_center <tt>True</tt> to flag the atom as a stereo center, and <tt>False</tt> otherwise.
# 
def setStereoCenterFlag(atom: Atom, is_center: bool) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.STEREO_CENTER_FLAG property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoCenterFlag(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.STEREO_CENTER_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return <tt>True</tt> if the atom is flagged as a stereo center, and <tt>False</tt> otherwise.
# 
def getStereoCenterFlag(atom: Atom) -> bool: pass

##
# \brief Clears the value of the Chem.AtomProperty.STEREO_CENTER_FLAG property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearStereoCenterFlag(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.STEREO_CENTER_FLAG property of the bond <em>bond</em> to <em>is_center</em>.
# 
# \param bond The bond for which to set the property value.
# \param is_center <tt>True</tt> to flag the bond as a stereo center, and <tt>False</tt> otherwise.
# 
def setStereoCenterFlag(bond: Bond, is_center: bool) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.STEREO_CENTER_FLAG property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoCenterFlag(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.STEREO_CENTER_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return <tt>True</tt> if the bond is flagged as a stereo center, and <tt>False</tt> otherwise.
# 
def getStereoCenterFlag(bond: Bond) -> bool: pass

##
# \brief Clears the value of the Chem.BondProperty.STEREO_CENTER_FLAG property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearStereoCenterFlag(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.STEREO_DESCRIPTOR property of the atom <em>atom</em> to <em>descr</em>.
# 
# \param atom The atom for which to set the property value.
# \param descr The new stereo descriptor.
# 
def setStereoDescriptor(atom: Atom, descr: StereoDescriptor) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.STEREO_DESCRIPTOR property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoDescriptor(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.STEREO_DESCRIPTOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored stereo descriptor.
# 
def getStereoDescriptor(atom: Atom) -> StereoDescriptor: pass

##
# \brief Clears the value of the Chem.AtomProperty.STEREO_DESCRIPTOR property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearStereoDescriptor(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.STEREO_DESCRIPTOR property of the bond <em>bond</em> to <em>descr</em>.
# 
# \param bond The bond for which to set the property value.
# \param descr The new stereo descriptor.
# 
def setStereoDescriptor(bond: Bond, descr: StereoDescriptor) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.STEREO_DESCRIPTOR property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStereoDescriptor(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.STEREO_DESCRIPTOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored stereo descriptor.
# 
def getStereoDescriptor(bond: Bond) -> StereoDescriptor: pass

##
# \brief Clears the value of the Chem.BondProperty.STEREO_DESCRIPTOR property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearStereoDescriptor(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.STOICHIOMETRIC_NUMBER property of the molecular graph <em>molgraph</em> to <em>num</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param num The new stoichiometric number.
# 
def setStoichiometricNumber(molgraph: MolecularGraph, num: float) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.STOICHIOMETRIC_NUMBER property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStoichiometricNumber(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.STOICHIOMETRIC_NUMBER property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored stoichiometric number.
# 
def getStoichiometricNumber(molgraph: MolecularGraph) -> float: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.STOICHIOMETRIC_NUMBER property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearStoichiometricNumber(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.STRUCTURE_DATA property of the molecular graph <em>molgraph</em> to <em>data</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param data The new structure-data block.
# 
def setStructureData(molgraph: MolecularGraph, data: StringDataBlock) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.STRUCTURE_DATA property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasStructureData(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.STRUCTURE_DATA property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored structure-data block.
# 
def getStructureData(molgraph: MolecularGraph) -> StringDataBlock: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.STRUCTURE_DATA property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearStructureData(molgraph: MolecularGraph) -> None: pass

##
# \brief Returns the canonical textual representation of the Sybyl atom type <em>sybyl_type</em>.
# 
# \param sybyl_type The Sybyl atom type identifier (Chem.SybylAtomType value).
# 
# \return A reference to the type-name string (empty for unknown types).
# 
def getSybylAtomTypeString(sybyl_type: int) -> str: pass

##
# \brief Returns the canonical textual representation of the Sybyl bond type <em>sybyl_type</em>.
# 
# \param sybyl_type The Sybyl bond-type identifier (Chem.SybylBondType value).
# 
# \return A reference to the type-name string (empty for unknown types).
# 
def getSybylBondTypeString(sybyl_type: int) -> str: pass

##
# \brief Sets the value of the Chem.AtomProperty.SYBYL_TYPE property of the atom <em>atom</em> to <em>type</em>.
# 
# \param atom The atom for which to set the property value.
# \param type The new <em>Sybyl MOL2</em> atom type (see namespace Chem.SybylAtomType).
# 
def setSybylType(atom: Atom, type: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.SYBYL_TYPE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSybylType(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.SYBYL_TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> atom type (see namespace Chem.SybylAtomType).
# 
def getSybylType(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.SYBYL_TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearSybylType(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.BondProperty.SYBYL_TYPE property of the bond <em>bond</em> to <em>type</em>.
# 
# \param bond The bond for which to set the property value.
# \param type The new <em>Sybyl MOL2</em> bond type (see namespace Chem.SybylBondType).
# 
def setSybylType(bond: Bond, type: int) -> None: pass

##
# \brief Tells whether the Chem.BondProperty.SYBYL_TYPE property of the bond <em>bond</em> is set.
# 
# \param bond The bond for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSybylType(bond: Bond) -> bool: pass

##
# \brief Returns the value of the Chem.BondProperty.SYBYL_TYPE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to return the property value.
# 
# \return The stored <em>Sybyl MOL2</em> bond type (see namespace Chem.SybylBondType).
# 
def getSybylType(bond: Bond) -> int: pass

##
# \brief Clears the value of the Chem.BondProperty.SYBYL_TYPE property of the bond <em>bond</em>.
# 
# \param bond The bond for which to clear the property value.
# 
def clearSybylType(bond: Bond) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.SYMBOL property of the atom <em>atom</em> to <em>symbol</em>.
# 
# \param atom The atom for which to set the property value.
# \param symbol The new element symbol.
# 
def setSymbol(atom: Atom, symbol: str) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.SYMBOL property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSymbol(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.SYMBOL property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored element symbol.
# 
def getSymbol(atom: Atom) -> str: pass

##
# \brief Clears the value of the Chem.AtomProperty.SYMBOL property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearSymbol(atom: Atom) -> None: pass

##
# \brief Returns the element symbol that corresponds to the Chem.AtomProperty.TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom to query.
# 
# \return The element symbol mapped from the atom's type (see namespace Chem.AtomType).
# 
def getSymbolForType(atom: Atom) -> str: pass

##
# \brief Sets the value of the Chem.AtomProperty.SYMMETRY_CLASS property of the atom <em>atom</em> to <em>class_id</em>.
# 
# \param atom The atom for which to set the property value.
# \param class_id The new topological-symmetry class ID.
# 
def setSymmetryClass(atom: Atom, class_id: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.SYMMETRY_CLASS property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasSymmetryClass(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.SYMMETRY_CLASS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored topological-symmetry class ID.
# 
def getSymmetryClass(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.SYMMETRY_CLASS property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearSymmetryClass(atom: Atom) -> None: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.TIMESTAMP property of the molecular graph <em>molgraph</em> to <em>time</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param time The new timestamp value.
# 
def setTimestamp(molgraph: MolecularGraph, time: int) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.TIMESTAMP property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTimestamp(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.TIMESTAMP property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored timestamp.
# 
def getTimestamp(molgraph: MolecularGraph) -> int: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.TIMESTAMP property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearTimestamp(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.ReactionProperty.TIMESTAMP property of the reaction <em>rxn</em> to <em>time</em>.
# 
# \param rxn The reaction for which to set the property value.
# \param time The new timestamp value.
# 
def setTimestamp(rxn: Reaction, time: int) -> None: pass

##
# \brief Tells whether the Chem.ReactionProperty.TIMESTAMP property of the reaction <em>rxn</em> is set.
# 
# \param rxn The reaction for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTimestamp(rxn: Reaction) -> bool: pass

##
# \brief Returns the value of the Chem.ReactionProperty.TIMESTAMP property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to return the property value.
# 
# \return The stored timestamp.
# 
def getTimestamp(rxn: Reaction) -> int: pass

##
# \brief Clears the value of the Chem.ReactionProperty.TIMESTAMP property of the reaction <em>rxn</em>.
# 
# \param rxn The reaction for which to clear the property value.
# 
def clearTimestamp(rxn: Reaction) -> None: pass

##
# \brief Returns the topological distance between two atoms of the molecular graph <em>molgraph</em>.
# 
# \param atom1 The first atom.
# \param atom2 The second atom.
# \param molgraph The molecular graph providing the bonding context.
# 
# \return The topological distance between <em>atom1</em> and <em>atom2</em>.
# 
def getTopologicalDistance(atom1: Atom, atom2: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Sets the value of the Chem.MolecularGraphProperty.TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em> to <em>mtx</em>.
# 
# \param molgraph The molecular graph for which to set the property value.
# \param mtx The new topological-distance matrix.
# 
def setTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief Tells whether the Chem.MolecularGraphProperty.TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em> is set.
# 
# \param molgraph The molecular graph for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTopologicalDistanceMatrix(molgraph: MolecularGraph) -> bool: pass

##
# \brief Returns the value of the Chem.MolecularGraphProperty.TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to return the property value.
# 
# \return The stored topological-distance matrix.
# 
def getTopologicalDistanceMatrix(molgraph: MolecularGraph) -> Math.ULMatrix: pass

##
# \brief Clears the value of the Chem.MolecularGraphProperty.TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph for which to clear the property value.
# 
def clearTopologicalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

##
# \brief Sets the value of the Chem.AtomProperty.TYPE property of the atom <em>atom</em> to <em>type</em>.
# 
# \param atom The atom for which to set the property value.
# \param type The new atom type (see namespace Chem.AtomType).
# 
def setType(atom: Atom, type: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.TYPE property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasType(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored atom type (see namespace Chem.AtomType).
# 
def getType(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.TYPE property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearType(atom: Atom) -> None: pass

##
# \brief Returns the atom type that corresponds to the Chem.AtomProperty.SYMBOL property of the atom <em>atom</em>.
# 
# \param atom The atom to query.
# 
# \return The atom type mapped from the element symbol.
# 
def getTypeForSymbol(atom: Atom) -> int: pass

##
# \brief Sets the value of the Chem.AtomProperty.UNPAIRED_ELECTRON_COUNT property of the atom <em>atom</em> to <em>count</em>.
# 
# \param atom The atom for which to set the property value.
# \param count The new unpaired electron count.
# 
def setUnpairedElectronCount(atom: Atom, count: int) -> None: pass

##
# \brief Tells whether the Chem.AtomProperty.UNPAIRED_ELECTRON_COUNT property of the atom <em>atom</em> is set.
# 
# \param atom The atom for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasUnpairedElectronCount(atom: Atom) -> bool: pass

##
# \brief Returns the value of the Chem.AtomProperty.UNPAIRED_ELECTRON_COUNT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to return the property value.
# 
# \return The stored unpaired electron count.
# 
def getUnpairedElectronCount(atom: Atom) -> int: pass

##
# \brief Clears the value of the Chem.AtomProperty.UNPAIRED_ELECTRON_COUNT property of the atom <em>atom</em>.
# 
# \param atom The atom for which to clear the property value.
# 
def clearUnpairedElectronCount(atom: Atom) -> None: pass

##
# \brief Appends a new conformation built from the supplied 3D coordinates to the atoms of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param coords The 3D coordinates of the new conformation.
# 
def addConformation(cntnr: AtomContainer, coords: Math.Vector3DArray) -> None: pass

##
# \brief Appends a new conformation built from the supplied coordinates and energy.
# 
# \param molgraph The molecular graph to modify.
# \param coords The 3D coordinates of the new conformation.
# \param energy The energy associated with the new conformation.
# 
def addConformation(molgraph: MolecularGraph, coords: Math.Vector3DArray, energy: float) -> None: pass

##
# \brief Aligns <em>molgraph's</em> 2D coordinates so that the atoms of <em>atoms</em> come to lie at the reference coordinates <em>ref_coords</em>.
# 
# \param molgraph The molecular graph to align.
# \param atoms The atoms used as alignment anchors.
# \param ref_coords Reference 2D coordinates of the alignment-anchor atoms.
# \param fix_bond_stereo If <tt>True</tt>, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
# 
# \return <tt>True</tt> if the alignment succeeded, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def align2DCoordinates(molgraph: MolecularGraph, atoms: AtomContainer, ref_coords: Math.Vector2DArray, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief Aligns <em>molgraph's</em> 2D coordinates onto a reference atom mapping.
# 
# \param molgraph The molecular graph to align.
# \param ref_atom_mpg The atom mapping providing the target atom→atom correspondence.
# \param fix_bond_stereo If <tt>True</tt>, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
# 
# \return <tt>True</tt> if the alignment succeeded, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def align2DCoordinates(molgraph: MolecularGraph, ref_atom_mpg: AtomMapping, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief 
# \param molgraph 
# \param ref_molgraph 
# \param use_mcs 
# \param fix_bond_stereo 
# \return 
#
def align2DCoordinates(molgraph: MolecularGraph, ref_molgraph: MolecularGraph, use_mcs: bool, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief Aligns <em>molgraph's</em> 2D coordinates onto those of <em>ref_molgraph</em>, using <em>substr_ptn</em> as the explicit substructure pattern.
# 
# \param molgraph The molecular graph to align.
# \param ref_molgraph The reference molecular graph providing the target coordinates.
# \param substr_ptn The substructure pattern that defines the atom correspondence.
# \param fix_bond_stereo If <tt>True</tt>, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
# 
# \return <tt>True</tt> if the alignment succeeded, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def align2DCoordinates(molgraph: MolecularGraph, ref_molgraph: MolecularGraph, substr_ptn: MolecularGraph, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief Rigid-body aligns the 3D coordinates of <em>cntnr</em> to the reference geometry defined by the entity-coordinate pair (<em>ref_entities</em>, <em>ref_coords</em>).
# 
# \param cntnr The entity 3D container whose coordinates are to be aligned.
# \param ref_entities The reference entity 3D container.
# \param ref_coords The reference coordinates corresponding to the entities of <em>ref_entities</em>.
# 
# \return <tt>True</tt> if the alignment succeeded, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def align3DCoordinates(cntnr: Entity3DContainer, ref_entities: Entity3DContainer, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief Aligns each stored conformation of <em>cntnr</em> onto the supplied reference coordinates using the atoms of <em>ref_atoms</em> as alignment anchors.
# 
# \param cntnr The atom container holding the conformations to be aligned.
# \param ref_atoms The atoms used as alignment anchors (must all be members of <em>cntnr</em>).
# \param ref_coords Reference 3D coordinates of the alignment-anchor atoms.
# 
# \return <tt>True</tt> if the alignment succeeded for every conformation, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def alignConformations(cntnr: AtomContainer, ref_atoms: Util.BitSet, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief Aligns each stored conformation of <em>cntnr</em> onto the supplied reference coordinates using the atoms of <em>ref_atoms</em> as alignment anchors.
# 
# \param cntnr The atom container holding the conformations to be aligned.
# \param ref_atoms The atoms used as alignment anchors (must all be members of <em>cntnr</em>).
# \param ref_coords Reference 3D coordinates of the alignment-anchor atoms.
# 
# \return <tt>True</tt> if the alignment succeeded for every conformation, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def alignConformations(cntnr: AtomContainer, ref_atoms: AtomContainer, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief Aligns each stored conformation of <em>cntnr</em> to the first conformation using the atoms of <em>ref_atoms</em> as alignment anchors.
# 
# \param cntnr The atom container holding the conformations to be aligned.
# \param ref_atoms The atoms used as alignment anchors (must all be members of <em>cntnr</em>).
# 
# \return <tt>True</tt> if the alignment succeeded for every conformation, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def alignConformations(cntnr: AtomContainer, ref_atoms: Util.BitSet) -> bool: pass

##
# \brief Aligns each stored conformation of <em>cntnr</em> to the first conformation using the atoms of <em>ref_atoms</em> as alignment anchors.
# 
# \param cntnr The atom container holding the conformations to be aligned.
# \param ref_atoms The atoms used as alignment anchors (must all be members of <em>cntnr</em>).
# 
# \return <tt>True</tt> if the alignment succeeded for every conformation, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def alignConformations(cntnr: AtomContainer, ref_atoms: AtomContainer) -> bool: pass

##
# \brief Promotes the stored conformation at index <em>conf_idx</em> to the active per-atom 3D coordinates.
# 
# \param cntnr The atom container.
# \param conf_idx The zero-based conformation index.
# 
def applyConformation(cntnr: AtomContainer, conf_idx: int) -> None: pass

##
# \brief Tells whether the target atom type <em>tgt_type</em> matches the query atom type <em>qry_type</em> (taking generic atom type classes like Chem.AtomType.HET into account).
# 
# \param qry_type The query atom type (Chem.AtomType value).
# \param tgt_type The target atom type (Chem.AtomType value).
# 
# \return <tt>True</tt> if the target matches the query, and <tt>False</tt> otherwise.
# 
def atomTypesMatch(qry_type: int, tgt_type: int) -> bool: pass

##
# \brief Computes 2D atom coordinates for <em>molgraph</em> and stores them as Chem.AtomProperty.COORDINATES_2D.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing 2D coordinates. Otherwise, leaves atoms that already carry coordinates unchanged.
# 
def calc2DCoordinates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores CIP configuration labels for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing CIP configuration labels.
# 
def calcAtomCIPConfigurations(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Derives atom stereo descriptors of the molecular graph <em>molgraph</em> from previously-assigned <em>MDL</em> parities.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing stereo descriptors.
# 
def calcAtomStereoDescriptorsFromMDLParities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores stereo descriptors for the atoms of the molecular graph <em>molgraph</em> from their geometric layout.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing stereo descriptors.
# \param dim The dimensionality of the atomic coordinates to use (<em>2</em> or <em>3</em>).
# \param check_stc_flag If <tt>True</tt>, descriptors are only computed for atoms whose Chem.AtomProperty.STEREO_CENTER_FLAG is set.
# 
def calcAtomStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1, check_stc_flag: bool = True) -> None: pass

##
# \brief Computes the basic per-atom/per-bond properties (aromaticity, ring info, etc.) of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
# \since 1.1
# 
def calcBasicProperties(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes the basic per-component properties (aromaticity, ring info, etc.) of every component of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
# \since 1.1
# 
def calcBasicProperties(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief Derives 2D wedge/hash bond stereo flags for the bonds of the molecular graph <em>molgraph</em> from the atoms' stereo descriptors and 2D layout.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing 2D stereo flags.
# 
def calcBond2DStereoFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores CIP configuration labels for the bonds of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing CIP configuration labels.
# 
def calcBondCIPConfigurations(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores stereo descriptors for the bonds of the molecular graph <em>molgraph</em> from their geometric layout.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing stereo descriptors.
# \param dim The dimensionality of the atomic coordinates to use (<em>2</em> or <em>3</em>).
# \param check_stc_flag If <tt>True</tt>, descriptors are only computed for bonds whose Chem.BondProperty.STEREO_CENTER_FLAG is set.
# 
def calcBondStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1, check_stc_flag: bool = True) -> None: pass

##
# \brief Computes the axis-aligned bounding box enclosing the atoms of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param min The output lower-left corner of the bounding box.
# \param max The output upper-right corner of the bounding box.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param reset If <tt>True</tt>, the bounding box is reset to the first atom. Otherwise, <em>min</em> and <em>max</em> are extended in place.
# 
def calcBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction, reset: bool = True) -> None: pass

##
# \brief Calculates the axis-aligned bounding box of the 3D coordinates of <em>cntnr</em>.
# 
# \param cntnr The entity 3D container.
# \param min The output vector receiving the per-axis minimum coordinates.
# \param max The output vector receiving the per-axis maximum coordinates.
# \param reset If <tt>True</tt>, <em>min</em> and <em>max</em> are reset before the calculation. If <tt>False</tt>, the box is extended to include the existing range.
# 
def calcBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D, reset: bool = True) -> None: pass

##
# \brief Computes and stores CIP priorities for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing CIP-priority values.
# 
def calcCIPPriorities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores canonical atom numbers for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing canonical numbers.
# \param atom_flags A bitmask of Chem.AtomPropertyFlag flags controlling which atomic properties enter the numbering.
# \param bond_flags A bitmask of Chem.BondPropertyFlag flags controlling which bond properties enter the numbering.
# 
def calcCanonicalNumbering(molgraph: MolecularGraph, overwrite: bool, atom_flags: int = 2147483648, bond_flags: int = 2147483648) -> None: pass

##
# \brief Computes the mass-weighted center of mass of the atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param ctr The output center-of-mass coordinates.
# 
# \return <tt>True</tt> if the center of mass could be computed (at least one atom with non-zero mass), and <tt>False</tt> otherwise.
# 
def calcCenterOfMass(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: Math.Vector3D) -> bool: pass

##
# \brief Computes the unweighted centroid (arithmetic mean of atom coordinates) of <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param coords_func The function returning the 3D coordinates of an atom.
# \param ctr The output centroid coordinates.
# 
# \return <tt>True</tt> if the centroid could be computed (<em>cntnr</em> is non-empty), and <tt>False</tt> otherwise.
# 
def calcCentroid(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: Math.Vector3D) -> bool: pass

##
# \brief Calculates the geometric centroid of the entities of <em>cntnr</em>.
# 
# \param cntnr The entity 3D container.
# \param ctr The output centroid vector.
# 
# \return <tt>True</tt> if the centroid could be calculated (i.e. <em>cntnr</em> is non-empty), and <tt>False</tt> otherwise.
# 
def calcCentroid(cntnr: Entity3DContainer, ctr: Math.Vector3D) -> bool: pass

##
# \brief Derives the atom configuration label from the supplied descriptor and 3D coordinates.
# 
# \param atom The atom for which to calculate the configuration.
# \param molgraph The molecular graph providing the structural context.
# \param descr The stereo descriptor whose configuration is to be evaluated.
# \param coords The 3D atomic coordinates used by the evaluation.
# 
# \return The derived configuration label (see namespace Chem.AtomConfiguration).
# 
def calcConfiguration(atom: Atom, molgraph: MolecularGraph, descr: StereoDescriptor, coords: Math.Vector3DArray) -> int: pass

##
# \brief Derives the bond configuration label from the supplied descriptor and 3D coordinates.
# 
# \param bond The bond to inspect.
# \param molgraph The molecular graph providing the structural context.
# \param descr The stereo descriptor whose configuration is to be evaluated.
# \param coords The 3D atomic coordinates used by the evaluation.
# 
# \return The derived configuration label (see namespace Chem.BondConfiguration).
# 
def calcConfiguration(bond: Bond, molgraph: MolecularGraph, descr: StereoDescriptor, coords: Math.Vector3DArray) -> int: pass

##
# \brief Computes the formal charge of the atom <em>atom</em> from its valence environment in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to calculate the charge.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The computed formal charge.
# 
def calcFormalCharge(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Computes and stores formal charges for the atoms of the molecular graph <em>molgraph</em> from their valence environment.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing formal charges.
# 
def calcFormalCharges(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Calculates the inter-entity geometric distance matrix for the entities of <em>cntnr</em>.
# 
# \param cntnr The entity 3D container providing the source coordinates.
# \param mtx The output matrix receiving the calculated pairwise distances.
# 
def calcGeometricalDistanceMatrix(cntnr: Entity3DContainer, mtx: Math.DMatrix) -> None: pass

##
# \brief Computes and (optionally) stores the geometrical-distance matrix of the molecular graph <em>molgraph</em> from its 3D coordinates.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing geometrical-distance matrix.
# 
# \return The computed (or pre-existing) matrix.
# 
def calcGeometricalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> Math.DMatrix: pass

##
# \brief Computes a 64-bit hash code for <em>molgraph</em> taking into account the specified atom and bond properties.
# 
# \param molgraph The molecular graph to hash.
# \param atom_flags A bitmask of Chem.AtomPropertyFlag flags controlling which atomic properties enter the hash.
# \param bond_flags A bitmask of Chem.BondPropertyFlag flags controlling which bond properties enter the hash.
# \param ord_h_deplete <tt>True</tt> to suppress ordinary hydrogens before hashing.
# 
# \return The computed hash code.
# 
def calcHashCode(molgraph: MolecularGraph, atom_flags: int = 2147483648, bond_flags: int = 2147483648, ord_h_deplete: bool = True) -> int: pass

##
# \brief Computes a 64-bit hash code for the reaction <em>rxn</em> taking into account the specified reaction roles and atom/bond properties.
# 
# \param rxn The reaction to hash.
# \param role_mask A bitmask of Chem.ReactionRole flags selecting the considered component sets.
# \param atom_flags A bitmask of Chem.AtomPropertyFlag flags controlling which atomic properties enter the hash.
# \param bond_flags A bitmask of Chem.BondPropertyFlag flags controlling which bond properties enter the hash.
# \param ord_h_deplete <tt>True</tt> to suppress ordinary hydrogens before hashing.
# 
# \return The computed hash code.
# 
def calcHashCode(rxn: Reaction, role_mask: int = 7, atom_flags: int = 2147483648, bond_flags: int = 2147483648, ord_h_deplete: bool = True) -> int: pass

##
# \brief Computes 3D coordinates for the hydrogen atoms of the molecular graph <em>molgraph</em> from the geometry of their non-hydrogen neighbors.
# 
# \param molgraph The molecular graph to modify.
# \param undef_only If <tt>True</tt>, only hydrogens without prior 3D coordinates are placed. If <tt>False</tt>, all hydrogen coordinates are recomputed.
# 
def calcHydrogen3DCoordinates(molgraph: MolecularGraph, undef_only: bool = True) -> None: pass

##
# \brief Computes the implicit hydrogen count of the atom <em>atom</em> from its valence environment in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to calculate the hydrogen count.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The computed implicit-hydrogen count.
# 
def calcImplicitHydrogenCount(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Computes and stores implicit-hydrogen counts for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing implicit-hydrogen counts.
# 
def calcImplicitHydrogenCounts(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes and stores <em>MDL</em> parities for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing <em>MDL</em> parities.
# 
def calcMDLParities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes the <em>MDL</em> parity of the atom <em>atom</em> from its 2D layout and stereo flags in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to calculate the parity.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The computed <em>MDL</em> parity (see namespace Chem.MDLParity).
# 
def calcMDLParity(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Computes and stores Morgan numbers for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing Morgan numbers.
# 
def calcMorganNumbering(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Computes the stereo descriptor for the atom <em>atom</em> based on the geometry of the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to calculate the stereo descriptor.
# \param molgraph The molecular graph providing the structural context.
# \param dim The dimensionality of the atomic coordinates to use (<em>2</em> or <em>3</em>).
# 
# \return The computed stereo descriptor.
# 
def calcStereoDescriptor(atom: Atom, molgraph: MolecularGraph, dim: int = 1) -> StereoDescriptor: pass

##
# \brief Computes the stereo descriptor for the bond <em>bond</em> based on the geometry of the molecular graph <em>molgraph</em>.
# 
# \param bond The bond to inspect.
# \param molgraph The molecular graph providing the structural context.
# \param dim The dimensionality of the atomic coordinates to use (<em>2</em> or <em>3</em>).
# 
# \return The computed stereo descriptor.
# 
def calcStereoDescriptor(bond: Bond, molgraph: MolecularGraph, dim: int = 1) -> StereoDescriptor: pass

##
# \brief Derives the stereo descriptor of the atom <em>atom</em> from its <em>MDL</em> parity in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to calculate the stereo descriptor.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The derived stereo descriptor.
# 
def calcStereoDescriptorFromMDLParity(atom: Atom, molgraph: MolecularGraph) -> StereoDescriptor: pass

##
# \brief Computes and (optionally) stores the topological-distance matrix of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing topological-distance matrix.
# 
# \return The computed (or pre-existing) matrix.
# 
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> Math.ULMatrix: pass

##
# \brief Computes the topological-distance matrix of the molecular graph <em>molgraph</em> into the supplied <em>mtx</em>.
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output dense matrix receiving the topological distances.
# 
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph <em>molgraph</em> according to the canonical-numbering attached to its atoms.
# 
# \param molgraph The molecular graph to canonicalize.
# \param atoms <tt>True</tt> to sort atoms.
# \param atom_nbrs <tt>True</tt> to sort each atom's neighbor list.
# \param bonds <tt>True</tt> to sort bonds.
# \param bond_atoms <tt>True</tt> to reorder the start/end atoms of each bond.
# 
def canonicalize(molgraph: MolecularGraph, atoms: bool = True, atom_nbrs: bool = True, bonds: bool = True, bond_atoms: bool = False) -> None: pass

##
# \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph <em>molgraph</em> according to a user-supplied comparator.
# 
# \param molgraph The molecular graph to canonicalize.
# \param func The atom comparator that defines the canonical ordering.
# \param atoms <tt>True</tt> to sort atoms.
# \param atom_nbrs <tt>True</tt> to sort each atom's neighbor list.
# \param bonds <tt>True</tt> to sort bonds.
# \param bond_atoms <tt>True</tt> to reorder the start/end atoms of each bond according to the comparator.
# 
def canonicalize(molgraph: MolecularGraph, func: BoolAtom2Functor, atoms: bool = True, atom_nbrs: bool = True, bonds: bool = True, bond_atoms: bool = False) -> None: pass

##
# \brief Adds bonds between atoms of the molecule <em>mol</em> whose 3D distance (obtained via <em>coords_func</em>) falls within the covalent-radii sum plus <em>dist_tol</em>.
# 
# \param mol The molecule whose atoms are to be connected.
# \param coords_func The function used to retrieve the 3D coordinates of an atom.
# \param dist_tol The tolerance added to the sum of the two atoms' covalent radii.
# \param atom_idx_offs Bonds are only added when at least one of the two atom indices is greater than or equal to <em>atom_idx_offs</em>.
# 
def connectAtoms(mol: Molecule, coords_func: Atom3DCoordinatesFunction, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief Adds bonds between atoms of the molecule <em>mol</em> whose 3D distance falls within the covalent-radii sum plus <em>dist_tol</em>.
# 
# \param mol The molecule whose atoms are to be connected.
# \param dist_tol The tolerance added to the sum of the two atoms' covalent radii.
# \param atom_idx_offs Bonds are only added when at least one of the two atom indices is greater than or equal to <em>atom_idx_offs</em> (useful to extend an existing bonding network without re-evaluating already-connected atoms).
# 
def connectAtoms(mol: Molecule, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief Tells whether any fragment in <em>frag_list</em> contains the bond <em>bond</em>.
# 
# \param frag_list The list of fragments to search.
# \param bond The queried bond.
# 
# \return <tt>True</tt> if at least one fragment contains <em>bond</em>, and <tt>False</tt> otherwise.
# 
def containsFragmentWithBond(frag_list: FragmentList, bond: Bond) -> bool: pass

##
# \brief Tells whether <em>frag_list</em> contains at least one fragment with at least <em>min_size</em> atoms.
# 
# \param frag_list The list of fragments to search.
# \param min_size The minimum required atom count.
# 
# \return <tt>True</tt> if such a fragment exists, and <tt>False</tt> otherwise.
# 
def containsFragmentWithMinSize(frag_list: FragmentList, min_size: int) -> bool: pass

##
# \brief Tells whether the molecular graph <em>molgraph</em> contains the atoms and/or bonds of <em>sub_molgraph</em>.
# 
# \param molgraph The host molecular graph.
# \param sub_molgraph The candidate sub-graph.
# \param atoms If <tt>True</tt>, every atom of <em>sub_molgraph</em> must be a member of the molecular graph <em>molgraph</em>.
# \param bonds If <tt>True</tt>, every bond of <em>sub_molgraph</em> must be a member of the molecular graph <em>molgraph</em>.
# 
# \return <tt>True</tt> if the requested containment relations all hold, and <tt>False</tt> otherwise.
# 
def containsMolecularGraph(molgraph: MolecularGraph, sub_molgraph: MolecularGraph, atoms: bool = True, bonds: bool = True) -> bool: pass

##
# \brief Copies every atom of <em>cntnr</em> that satisfies <em>pred</em> into the molecule <em>mol</em>.
# 
# \param cntnr The source atom container.
# \param mol The target molecule.
# \param pred The predicate evaluated for each atom. Only atoms for which it returns <tt>True</tt> are copied.
# \param append If <tt>True</tt>, atoms are appended to <em>mol</em>. Otherwise, <em>mol</em> is cleared first.
# 
def copyAtomsIf(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief Copies every atom of <em>cntnr</em> that satisfies <em>pred</em> into the fragment <em>frag</em>.
# 
# \param cntnr The source atom container.
# \param frag The target fragment.
# \param pred The predicate evaluated for each atom. Only atoms for which it returns <tt>True</tt> are copied.
# \param append If <tt>True</tt>, atoms are appended to <em>frag</em>. Otherwise, <em>frag</em> is cleared first.
# 
def copyAtomsIf(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief Copies every atom of <em>cntnr</em> that does <em>not</em> satisfy <em>pred</em> into the molecule <em>mol</em>.
# 
# \param cntnr The source atom container.
# \param mol The target molecule.
# \param pred The predicate evaluated for each atom. Only atoms for which it returns <tt>False</tt> are copied.
# \param append If <tt>True</tt>, atoms are appended to <em>mol</em>. Otherwise, <em>mol</em> is cleared first.
# 
def copyAtomsIfNot(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief Copies every atom of <em>cntnr</em> that does <em>not</em> satisfy <em>pred</em> into the fragment <em>frag</em>.
# 
# \param cntnr The source atom container.
# \param frag The target fragment.
# \param pred The predicate evaluated for each atom. Only atoms for which it returns <tt>False</tt> are copied.
# \param append If <tt>True</tt>, atoms are appended to <em>frag</em>. Otherwise, <em>frag</em> is cleared first.
# 
def copyAtomsIfNot(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief Sets bits in <em>mask</em> corresponding to atoms of <em>cntnr</em> whose atom type matches <em>type</em>.
# 
# \param cntnr The atom container.
# \param mask The output bit mask (bit <em>i</em> is set if atom <em>i</em> of <em>cntnr</em> has the requested type).
# \param type The query atom type (Chem.AtomType value, possibly a generic class such as Chem.AtomType.HET).
# \param reset If <tt>True</tt>, <em>mask</em> is reset before processing. Otherwise, existing bits are preserved.
# \param strict If <tt>True</tt>, only exact type matches are accepted. If <tt>False</tt>, generic-class matches also set the bit.
# 
# \return The number of atoms whose bit was set.
# 
def createAtomTypeMask(cntnr: AtomContainer, mask: Util.BitSet, type: int, reset: bool = True, strict: bool = True) -> int: pass

##
# \brief Builds the molecule <em>result_mol</em> from the molecular graph <em>molgraph</em> by replacing all substructures matching the <em>SMARTS</em> patterns in <em>search_ptns</em> with <em>result_ptn</em>.
# 
# \param molgraph The source molecular graph.
# \param result_mol The molecule receiving the edited result.
# \param search_ptns A whitespace-separated list of <em>SMARTS</em> patterns matching the substructures to replace.
# \param result_ptn The <em>SMARTS</em> replacement pattern.
# \param exclude_ptns A whitespace-separated list of <em>SMARTS</em> patterns matching substructures that shall be retained even if they also match <em>search_ptns</em>.
# 
# \return The number of applied substructure replacements. 
# 
# \since 1.3
# 
def editSubstructures(molgraph: MolecularGraph, result_mol: Molecule, search_ptns: str, result_ptn: str, exclude_ptns: str = '') -> int: pass

##
# \brief Edits the molecule <em>mol</em> by replacing all substructures matching the <em>SMARTS</em> search patterns in <em>search_ptns</em> with the <em>SMARTS</em> replacement pattern <em>result_ptn</em>, optionally skipping matches that also match <em>exclude_ptns</em>.
# 
# \param mol The molecule to edit in place.
# \param search_ptns A whitespace-separated list of <em>SMARTS</em> patterns matching the substructures to replace.
# \param result_ptn The <em>SMARTS</em> replacement pattern.
# \param exclude_ptns A whitespace-separated list of <em>SMARTS</em> patterns matching substructures that shall be retained even if they match <em>search_ptns</em>.
# 
# \return The number of replaced substructures. 
# 
# \since 1.3
# 
def editSubstructures(mol: Molecule, search_ptns: str, result_ptn: str, exclude_ptns: str = '') -> int: pass

##
# \brief Extends the axis-aligned bounding box defined by <em>min</em> and <em>max</em> so that it contains the point <em>coords</em>.
# 
# \param min The lower-left corner of the bounding box (updated in place).
# \param max The upper-right corner of the bounding box (updated in place).
# \param coords The 3D point to include.
# \param reset If <tt>True</tt>, the bounding box is first reset to <em>coords</em> (degenerate point box) before extension.
# 
def extendBoundingBox(min: Math.Vector3D, max: Math.Vector3D, coords: Math.Vector3D, reset: bool = False) -> None: pass

##
# \brief Collects every atom and bond of the molecular graph <em>molgraph</em> that carries a reaction-center flag into the fragment <em>rxn_center</em>.
# 
# \param molgraph The molecular graph to inspect.
# \param rxn_center The output fragment receiving the reaction-center atoms and bonds.
# 
def extractReactionCenter(molgraph: MolecularGraph, rxn_center: Fragment) -> None: pass

##
# \brief Extracts the subset of the SSSR of the molecular graph <em>src_molgraph</em> whose rings consist of atoms and bonds of <em>tgt_molgraph</em>.
# 
# \param src_molgraph The source molecular graph whose SSSR is to be projected.
# \param tgt_molgraph The target molecular graph providing the membership filter.
# 
# \return The extracted SSSR subset.
# 
def extractSSSRSubset(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Extracts the SSSR subset of the molecular graph <em>src_molgraph</em> that fits within <em>tgt_molgraph</em> and (optionally) stores it on the latter.
# 
# \param src_molgraph The source molecular graph whose SSSR is to be projected.
# \param tgt_molgraph The target molecular graph that receives the projected SSSR.
# \param overwrite If <tt>True</tt>, replaces any existing SSSR on <em>tgt_molgraph</em>.
# 
# \return The extracted (or pre-existing) SSSR subset.
# 
def extractSSSRSubset(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief Extracts the topological-distance sub-matrix of the molecular graph <em>src_molgraph</em> that covers the atoms of <em>tgt_molgraph</em> and (optionally) stores it on the latter.
# 
# \param src_molgraph The source molecular graph providing the full matrix.
# \param tgt_molgraph The target molecular graph providing the atom subset and (optionally) receiving the sub-matrix.
# \param overwrite If <tt>True</tt>, replaces any existing matrix on <em>tgt_molgraph</em>.
# 
# \return The extracted (or pre-existing) sub-matrix.
# 
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, overwrite: bool) -> Math.ULMatrix: pass

##
# \brief Extracts the topological-distance sub-matrix of the molecular graph <em>src_molgraph</em> that covers the atoms of <em>tgt_molgraph</em> into the supplied <em>mtx</em>.
# 
# \param src_molgraph The source molecular graph providing the full matrix.
# \param tgt_molgraph The target molecular graph providing the atom subset.
# \param mtx The output dense matrix receiving the sub-matrix entries.
# 
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief Builds the adjacency matrix of the molecular graph <em>molgraph</em> (entry <tt></tt>(i,j) is the bond count between atoms <tt>i</tt> and <tt>j</tt>).
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output sparse matrix receiving the adjacency entries.
# 
def generateAdjacencyMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief Builds a matrix combining bond order and atom type information of the endpoints of every bond in <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output sparse matrix receiving the combined entries.
# 
def generateBondAtomTypeMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief Builds the bond-electron-count matrix of the molecular graph <em>molgraph</em> (entry <tt></tt>(i,j) is the number of bonding electrons between atoms <tt>i</tt> and <tt>j</tt>).
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output sparse matrix receiving the bond-electron counts.
# 
def generateBondElectronMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief Builds the bond order matrix of the molecular graph <em>molgraph</em> (entry <tt></tt>(i,j) is the order of the bond between atoms <tt>i</tt> and <tt>j</tt>).
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output sparse matrix receiving the bond order entries.
# 
def generateBondMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def generateINCHIKey(molgraph: MolecularGraph) -> object: pass

##
# \brief 
# \param molgraph 
# \param options 
# \param dim 
# \return 
#
def generateINCHI(molgraph: MolecularGraph, options: str = '/WarnOnEmptyStructure /AuxNone /NEWPSOFF', dim: int = 0) -> object: pass

##
# \brief Builds the atom/bond incidence matrix of the molecular graph <em>molgraph</em> (entry <tt></tt>(i,j) is <tt>1</tt> if atom <tt>i</tt> is an endpoint of bond <tt>j</tt>).
# 
# \param molgraph The molecular graph to inspect.
# \param mtx The output sparse matrix receiving the incidence entries.
# 
def generateIncidenceMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief Builds an atom-level match expression from the match constraint list attached to the atom <em>atom</em>.
# 
# \param atom The atom for which to generate the expression.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The generated match expression.
# 
def generateMatchExpression(atom: Atom, molgraph: MolecularGraph) -> AtomMatchExpression: pass

##
# \brief Builds a bond-level match expression from the match constraint list attached to the bond <em>bond</em>.
# 
# \param bond The bond to inspect.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The generated match expression.
# 
def generateMatchExpression(bond: Bond, molgraph: MolecularGraph) -> BondMatchExpression: pass

##
# \brief Builds a top-level match expression from the match constraint list attached to <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The generated match expression.
# 
def generateMatchExpression(molgraph: MolecularGraph) -> MolecularGraphMatchExpression: pass

##
# \brief Builds and (optionally) stores the top-level match expression of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing match expression. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The generated (or pre-existing) match expression.
# 
def generateMatchExpression(molgraph: MolecularGraph, overwrite: bool) -> MolecularGraphMatchExpression: pass

##
# \brief Builds a reaction-level match expression from the constraints currently attached to the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect.
# 
# \return The generated match expression.
# 
def generateMatchExpression(rxn: Reaction) -> ReactionMatchExpression: pass

##
# \brief Builds and (optionally) stores the reaction-level match expression of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect/modify.
# \param overwrite If <tt>True</tt>, the generated expression replaces any existing Chem.ReactionProperty.MATCH_EXPRESSION. If <tt>False</tt>, the existing one (if any) is returned unchanged.
# 
# \return The generated (or pre-existing) match expression.
# 
def generateMatchExpression(rxn: Reaction, overwrite: bool) -> ReactionMatchExpression: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def generateMatchExpressionString(atom: Atom, molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def generateMatchExpressionString(bond: Bond, molgraph: MolecularGraph) -> str: pass

##
# \brief Generates and stores textual representations of the match expressions of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing match expression strings.
# 
def generateMatchExpressionStrings(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Generates and stores match expressions for every atom, bond and the molecular graph itself.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing match expressions. If <tt>False</tt>, leaves items that already carry a match expression unchanged.
# 
def generateMatchExpressions(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Generates and stores match expressions for the atoms, bonds, components, and the reaction <em>rxn</em> itself.
# 
# \param rxn The reaction to modify.
# \param overwrite If <tt>True</tt>, replaces any existing match expressions. If <tt>False</tt>, leaves items that already carry a match expression unchanged.
# 
def generateMatchExpressions(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param canonical 
# \param ord_h_deplete 
# \param atom_flags 
# \param bond_flags 
# \return 
#
def generateSMILES(molgraph: MolecularGraph, canonical: bool = False, ord_h_deplete: bool = True, atom_flags: int = 2147483648, bond_flags: int = 2147483648) -> object: pass

##
# \brief 
# \param rxn 
# \param canonical 
# \param ord_h_deplete 
# \param atom_flags 
# \param bond_flags 
# \return 
#
def generateSMILES(rxn: Reaction, canonical: bool = False, ord_h_deplete: bool = True, atom_flags: int = 2147483648, bond_flags: int = 2147483648) -> object: pass

##
# \brief Prepares the molecular graph <em>molgraph</em> for use as a substructure search query (precomputes match expressions and required cached properties).
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
def initSubstructureSearchQuery(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Prepares the reaction <em>rxn</em> for use as a substructure search query (e.g. by pre-computing match expressions and required cached properties).
# 
# \param rxn The reaction to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
def initSubstructureSearchQuery(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief Prepares the molecular graph <em>molgraph</em> for use as a substructure search target (precomputes required cached properties).
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
def initSubstructureSearchTarget(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Prepares the reaction <em>rxn</em> for use as a substructure search target (e.g. by pre-computing required cached properties).
# 
# \param rxn The reaction to modify.
# \param overwrite If <tt>True</tt>, recomputes derived data. If <tt>False</tt>, leaves up-to-date data unchanged.
# 
def initSubstructureSearchTarget(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief Tells whether every atom of <em>cntnr</em> lies inside the axis-aligned bounding box defined by <em>min</em> and <em>max</em>.
# 
# \param cntnr The atom container.
# \param min The lower-left corner of the bounding box.
# \param max The upper-right corner of the bounding box.
# \param coords_func The function returning the 3D coordinates of an atom.
# 
# \return <tt>True</tt> if all atoms are inside the box, and <tt>False</tt> otherwise.
# 
def insideBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass

##
# \brief Tells whether all entities of <em>cntnr</em> lie within the axis-aligned box defined by <em>min</em> and <em>max</em>.
# 
# \param cntnr The entity 3D container.
# \param min The per-axis minimum coordinates of the box.
# \param max The per-axis maximum coordinates of the box.
# 
# \return <tt>True</tt> if every entity coordinate is inside the box, and <tt>False</tt> otherwise.
# 
def insideBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D) -> bool: pass

##
# \brief Tells whether the point <em>coords</em> lies inside the axis-aligned bounding box defined by <em>min</em> and <em>max</em>.
# 
# \param min The lower-left corner of the bounding box.
# \param max The upper-right corner of the bounding box.
# \param coords The 3D point to test.
# 
# \return <tt>True</tt> if the point is inside (componentwise <= <em>max</em> and >= <em>min</em>), and <tt>False</tt> otherwise.
# 
def insideBoundingBox(min: Math.Vector3D, max: Math.Vector3D, coords: Math.Vector3D) -> bool: pass

##
# \brief Tells whether at least one atom of <em>cntnr</em> lies inside the axis-aligned bounding box defined by <em>min</em> and <em>max</em>.
# 
# \param cntnr The atom container.
# \param min The lower-left corner of the bounding box.
# \param max The upper-right corner of the bounding box.
# \param coords_func The function returning the 3D coordinates of an atom.
# 
# \return <tt>True</tt> if at least one atom is inside the box, and <tt>False</tt> otherwise.
# 
def intersectsBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass

##
# \brief Tells whether at least one entity of <em>cntnr</em> lies within the axis-aligned box defined by <em>min</em> and <em>max</em>.
# 
# \param cntnr The entity 3D container.
# \param min The per-axis minimum coordinates of the box.
# \param max The per-axis maximum coordinates of the box.
# 
# \return <tt>True</tt> if any entity coordinate is inside the box, and <tt>False</tt> otherwise.
# 
def intersectsBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D) -> bool: pass

##
# \brief Tells whether <em>ring</em> fulfills the H&uuml;ckel <em></em>(4n+2)<em>&pi;-electron</em> criterion within <em>molgraph</em>.
# 
# \param ring The candidate aromatic ring.
# \param molgraph The parent molecular graph.
# \param arom_bond_mask A bond bit mask flagging bonds already known to be aromatic.
# 
# \return <tt>True</tt> if <em>ring</em> satisfies the H&uuml;ckel rule, and <tt>False</tt> otherwise.
# 
def isAromatic(ring: Fragment, molgraph: MolecularGraph, arom_bond_mask: Util.BitSet) -> bool: pass

##
# \brief Tells whether the atom <em>atom</em> is a member of any fragment in <em>frag_list</em> whose size matches <em>size</em>.
# 
# \param atom The atom to query.
# \param frag_list The list of fragments to search.
# \param size The required fragment size (in number of atoms).
# 
# \return <tt>True</tt> if at least one matching fragment contains <em>atom</em>, and <tt>False</tt> otherwise.
# 
def isInFragmentOfSize(atom: Atom, frag_list: FragmentList, size: int) -> bool: pass

##
# \brief Tells whether the bond <em>bond</em> is a member of any fragment in <em>frag_list</em> whose size matches <em>size</em>.
# 
# \param bond The bond to query.
# \param frag_list The list of fragments to search.
# \param size The required fragment size (in number of atoms).
# 
# \return <tt>True</tt> if at least one matching fragment contains the bond <em>bond</em>, and <tt>False</tt> otherwise.
# 
def isInFragmentOfSize(bond: Bond, frag_list: FragmentList, size: int) -> bool: pass

##
# \brief Tells whether <em>ring</em> is guaranteed not to be aromatic (based on quick geometric/topological criteria).
# 
# \param ring The ring to test.
# \param molgraph The parent molecular graph.
# 
# \return <tt>True</tt> if <em>ring</em> cannot be aromatic, and <tt>False</tt> if a more thorough test is required.
# 
def isNotAromatic(ring: Fragment, molgraph: MolecularGraph) -> bool: pass

##
# \brief Tells whether the atom <em>atom</em> qualifies as a stereo center in the context of the molecular graph <em>molgraph</em>.
# 
# \param atom The atom to evaluate.
# \param molgraph The molecular graph providing the structural context.
# \param check_asym <tt>True</tt> to enforce non-equivalent ligand environments.
# \param check_inv_n <tt>True</tt> to reject inversion-prone nitrogen centers (umbrella inversion).
# \param check_quart_n <tt>True</tt> to accept positively charged quaternary nitrogen centers.
# \param check_plan_n <tt>True</tt> to reject planar nitrogen centers.
# \param check_amide_n <tt>True</tt> to reject amide-nitrogen centers.
# \param check_res_ctrs <tt>True</tt> to reject centers participating in resonance.
# 
# \return <tt>True</tt> if the atom qualifies as a stereo center under the given conditions, and <tt>False</tt> otherwise.
# 
def isStereoCenter(atom: Atom, molgraph: MolecularGraph, check_asym: bool = True, check_inv_n: bool = True, check_quart_n: bool = True, check_plan_n: bool = True, check_amide_n: bool = True, check_res_ctrs: bool = True) -> bool: pass

##
# \brief Tells whether the bond <em>bond</em> qualifies as a stereo center in the context of the molecular graph <em>molgraph</em>.
# 
# \param bond The bond to inspect.
# \param molgraph The molecular graph providing the structural context.
# \param check_asym <tt>True</tt> to enforce non-equivalent ligand environments.
# \param check_term_n <tt>True</tt> to reject bonds to terminal nitrogen atoms.
# \param check_order <tt>True</tt> to require that the bond order matches a stereogenic pattern.
# \param min_ring_size If the bond <em>bond</em> is a ring bond, the containing ring must have at least this size to qualify.
# 
# \return <tt>True</tt> if the bond qualifies as a stereo center under the given conditions, and <tt>False</tt> otherwise.
# 
def isStereoCenter(bond: Bond, molgraph: MolecularGraph, check_asym: bool = True, check_term_n: bool = True, check_order: bool = True, min_ring_size: int = 8) -> bool: pass

##
# \brief Assigns Kekulé bond orders to the aromatic bonds of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# 
def kekulizeBonds(molgraph: MolecularGraph) -> None: pass

##
# \brief Converts all implicit hydrogens of the molecule <em>mol</em> to explicit hydrogen atoms.
# 
# \param mol The molecule that has to be made hydrogen complete.
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be set to zero, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise.
# 
def makeHydrogenComplete(mol: Molecule, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief Removes all explicit hydrogen atoms from the fragment <em>frag</em>.
# 
# \param frag The fragment for which to remove all explicit hydrogen atoms.
# 
# \return <tt>False</tt> if <em>frag</em> was not altered, <tt>True</tt> otherwise.
# 
def makeHydrogenDeplete(frag: Fragment) -> bool: pass

##
# \brief Removes all explicit hydrogen atoms from the molecule <em>mol</em>.
# 
# \param mol The molecule for which to remove all explicit hydrogen atoms.
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be corrected, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise.
# 
def makeHydrogenDeplete(mol: Molecule, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief Removes all explicit ordinary hydrogen atoms from the fragment <em>frag</em>.
# 
# \param frag The fragment for which to remove all explicit ordinary hydrogen atoms.
# \param flags Specifies the set of atom properties to check (see namespace Chem.AtomPropertyFlag).
# 
# \return <tt>False</tt> if <em>frag</em> was not altered, <tt>True</tt> otherwise. 
# 
# \see MolProp.isOrdinaryHydrogen
# 
def makeOrdinaryHydrogenDeplete(frag: Fragment, flags: int) -> bool: pass

##
# \brief Removes all explicit ordinary hydrogen atoms from the molecule <em>mol</em>.
# 
# \param mol The molecule for which to remove all explicit ordinary hydrogen atoms.
# \param flags Specifies the set of atom properties to check (see namespace Chem.AtomPropertyFlag).
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be corrected, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise. 
# 
# \see MolProp.isOrdinaryHydrogen
# 
def makeOrdinaryHydrogenDeplete(mol: Molecule, flags: int, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief Sets bits in <em>atom_mask</em> for every atom of the molecular graph <em>molgraph</em> that is reachable from the atom <em>atom</em> through the bonds of <em>molgraph</em>.
# 
# \param atom The seed atom.
# \param molgraph The molecular graph providing the bonding context.
# \param atom_mask The output bit mask.
# \param reset If <tt>True</tt>, <em>atom_mask</em> is cleared first. Otherwise, existing bits are preserved.
# 
def markReachableAtoms(atom: Atom, molgraph: MolecularGraph, atom_mask: Util.BitSet, reset: bool = True) -> None: pass

##
# \brief Parses the <em>SMARTS</em> string <em>smarts</em> into a freshly allocated query Chem.Molecule.
# 
# \param smarts The <em>SMARTS</em> string to parse.
# \param init_qry If <tt>True</tt>, query-specific perception (e.g. ring-membership, aromaticity) is run on the parsed molecule.
# 
# \return A smart reference to the parsed molecule, or an empty smart reference if parsing failed.
# 
def parseSMARTS(smarts: str, init_qry: bool = True) -> Molecule: pass

##
# \brief Parses the <em>SMARTS</em> string <em>smarts</em> into the supplied molecule <em>mol</em>.
# 
# \param smarts The <em>SMARTS</em> string to parse.
# \param mol The molecule to populate (cleared before parsing).
# \param init_qry If <tt>True</tt>, query-specific perception is run on the parsed molecule.
# 
# \return <tt>True</tt> if parsing succeeded, and <tt>False</tt> otherwise.
# 
def parseSMARTS(smarts: str, mol: Molecule, init_qry: bool = True) -> bool: pass

##
# \brief Parses the <em>SMILES</em> string <em>smiles</em> into a freshly allocated Chem.Molecule.
# 
# \param smiles The <em>SMILES</em> string to parse.
# 
# \return A smart reference to the parsed molecule, or an empty smart reference if parsing failed.
# 
def parseSMILES(smiles: str) -> Molecule: pass

##
# \brief Parses the <em>SMILES</em> string <em>smiles</em> into the supplied molecule <em>mol</em>.
# 
# \param smiles The <em>SMILES</em> string to parse.
# \param mol The molecule to populate (cleared before parsing).
# 
# \return <tt>True</tt> if parsing succeeded, and <tt>False</tt> otherwise.
# 
def parseSMILES(smiles: str, mol: Molecule) -> bool: pass

##
# \brief Perceives the aromatic substructure of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived aromatic substructure.
# 
def perceiveAromaticSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief Perceives and (optionally) stores the aromatic substructure of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing aromatic substructure.
# 
# \return The perceived (or pre-existing) aromatic substructure.
# 
def perceiveAromaticSubstructure(molgraph: MolecularGraph, overwrite: bool) -> Fragment: pass

##
# \brief Derives the reactant-to-product atom mapping from the atom mapping IDs of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect.
# 
# \return The perceived atom mapping.
# 
def perceiveAtomMapping(rxn: Reaction) -> AtomMapping: pass

##
# \brief Derives and (optionally) stores the reactant-to-product atom mapping of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect/modify.
# \param overwrite If <tt>True</tt>, the perceived mapping replaces any existing Chem.ReactionProperty.ATOM_MAPPING property. If <tt>False</tt>, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) atom mapping.
# 
def perceiveAtomMapping(rxn: Reaction, overwrite: bool) -> AtomMapping: pass

##
# \brief Flags the atoms of the molecular graph <em>molgraph</em> that qualify as stereo centers under the supplied criteria.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing stereo-center flags.
# \param check_asym <tt>True</tt> to enforce non-equivalent ligand environments.
# \param check_inv_n <tt>True</tt> to reject inversion-prone nitrogen centers.
# \param check_quart_n <tt>True</tt> to accept positively charged quaternary nitrogen centers.
# \param check_plan_n <tt>True</tt> to reject planar nitrogen centers.
# \param check_amide_n <tt>True</tt> to reject amide-nitrogen centers.
# \param check_res_ctrs <tt>True</tt> to reject centers participating in resonance.
# 
def perceiveAtomStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_asym: bool = True, check_inv_n: bool = True, check_quart_n: bool = True, check_plan_n: bool = True, check_amide_n: bool = True, check_res_ctrs: bool = True) -> None: pass

##
# \brief Perceives bond orders for the bonds of the molecular graph <em>molgraph</em> from atom geometry and ligand environment.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing bond orders.
# 
def perceiveBondOrders(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Flags the bonds of the molecular graph <em>molgraph</em> that qualify as stereo centers under the supplied criteria.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing stereo-center flags.
# \param check_asym <tt>True</tt> to enforce non-equivalent ligand environments.
# \param check_term_n <tt>True</tt> to reject bonds to terminal nitrogen atoms.
# \param check_order <tt>True</tt> to require that the bond order matches a stereogenic pattern.
# \param min_ring_size The minimum ring size required for ring bonds to qualify.
# 
def perceiveBondStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_asym: bool = True, check_term_n: bool = True, check_order: bool = True, min_ring_size: int = 8) -> None: pass

##
# \brief Perceives the component groups of the molecular graph <em>molgraph</em> (from atom-level Chem.AtomProperty.COMPONENT_GROUP_ID values).
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived component-group fragment list.
# 
def perceiveComponentGroups(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Perceives and (optionally) stores the component groups of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing component-group list. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) component-group list.
# 
def perceiveComponentGroups(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief Perceives the component groups of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect.
# 
# \return The perceived component-group fragment list.
# 
def perceiveComponentGroups(rxn: Reaction) -> FragmentList: pass

##
# \brief Perceives and (optionally) stores the component groups of the reaction <em>rxn</em>.
# 
# \param rxn The reaction to inspect/modify.
# \param overwrite If <tt>True</tt>, the perceived list replaces any existing Chem.ReactionProperty.COMPONENT_GROUPS. If <tt>False</tt>, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) component-group fragment list.
# 
def perceiveComponentGroups(rxn: Reaction, overwrite: bool) -> FragmentList: pass

##
# \brief Perceives the connected components of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived connected-component list.
# 
def perceiveComponents(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Perceives and (optionally) stores the connected components of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing component list. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) component list.
# 
def perceiveComponents(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief Perceives the cyclic substructure (union of all rings) of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived cyclic substructure.
# 
def perceiveCyclicSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief Perceives and (optionally) stores the cyclic substructure of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing cyclic substructure. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) cyclic substructure.
# 
def perceiveCyclicSubstructure(molgraph: MolecularGraph, overwrite: bool) -> Fragment: pass

##
# \brief Derives the hybridization state of the atom <em>atom</em> from its valence environment in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to perceive the hybridzation state.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The perceived hybridization state (see namespace Chem.HybridizationState).
# 
def perceiveHybridizationState(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Computes and stores hybridization states for the atoms of the molecular graph <em>molgraph</em> from their valence environment.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing hybridization states.
# 
def perceiveHybridizationStates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Perceives the pi-electron systems of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived pi-electron-system list.
# 
def perceivePiElectronSystems(molgraph: MolecularGraph) -> ElectronSystemList: pass

##
# \brief Perceives and (optionally) stores the pi-electron systems of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing pi-electron-system list.
# 
# \return The perceived (or pre-existing) pi-electron-system list.
# 
def perceivePiElectronSystems(molgraph: MolecularGraph, overwrite: bool) -> ElectronSystemList: pass

##
# \brief Perceives the full set of rings of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return The perceived ring set.
# 
def perceiveRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Perceives and (optionally) stores the full set of rings of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing ring set. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) ring set.
# 
def perceiveRings(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief Perceives the Smallest Set of Smallest Rings of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect.
# 
# \return A shared reference to the perceived SSSR.
# 
def perceiveSSSR(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief Perceives and (optionally) stores the Smallest Set of Smallest Rings of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to inspect/modify.
# \param overwrite If <tt>True</tt>, replaces any existing SSSR. Otherwise, the existing one (if any) is returned unchanged.
# 
# \return The perceived (or pre-existing) SSSR.
# 
def perceiveSSSR(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief Perceives Sybyl atom types for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing Sybyl atom types.
# 
def perceiveSybylAtomTypes(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Derives the <em>Sybyl MOL2</em> atom type of the atom <em>atom</em> from its valence environment in the molecular graph <em>molgraph</em>.
# 
# \param atom The atom for which to perceive the type.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The perceived <em>Sybyl MOL2</em> atom type (see namespace Chem.SybylAtomType).
# 
def perceiveSybylType(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief Derives the <em>Sybyl MOL2</em> bond type of the bond <em>bond</em> from its bond order, aromaticity and ligand environment in the molecular graph <em>molgraph</em>.
# 
# \param bond The bond to inspect.
# \param molgraph The molecular graph providing the structural context.
# 
# \return The perceived <em>Sybyl MOL2</em> bond type (see namespace Chem.SybylBondType).
# 
def perceiveSybylType(bond: Bond, molgraph: MolecularGraph) -> int: pass

##
# \brief Computes and stores topological-symmetry classes for the atoms of the molecular graph <em>molgraph</em>.
# 
# \param molgraph The molecular graph to modify.
# \param overwrite If <tt>True</tt>, replaces any existing symmetry-class IDs.
# \param atom_flags A bitmask of Chem.AtomPropertyFlag flags controlling which atomic properties enter the perception.
# \param bond_flags A bitmask of Chem.BondPropertyFlag flags controlling which bond properties enter the perception.
# \param inc_impl_h If <tt>True</tt>, implicit hydrogens are treated as if they were explicit. Otherwise, they are ignored.
# 
def perceiveSymmetryClasses(molgraph: MolecularGraph, overwrite: bool, atom_flags: int = 2147483648, bond_flags: int = 2147483648, inc_impl_h: bool = True) -> None: pass

##
# \brief Removes all atoms of the fragment <em>frag</em> for which the predicate <em>pred</em> returns <tt>True</tt>.
# 
# \param frag The fragment to filter in place.
# \param pred The atom predicate to evaluate.
# 
def removeAtomsIf(frag: Fragment, pred: AtomPredicate) -> None: pass

##
# \brief Removes all atoms of the molecule <em>mol</em> for which the predicate <em>pred</em> returns <tt>True</tt>.
# 
# \param mol The molecule to filter in place.
# \param pred The atom predicate to evaluate.
# 
def removeAtomsIf(mol: Molecule, pred: AtomPredicate) -> None: pass

##
# \brief Removes all atoms of the fragment <em>frag</em> for which the predicate <em>pred</em> returns <tt>False</tt>.
# 
# \param frag The fragment to filter in place.
# \param pred The atom predicate to evaluate.
# 
def removeAtomsIfNot(frag: Fragment, pred: AtomPredicate) -> None: pass

##
# \brief Removes all atoms of the molecule <em>mol</em> for which the predicate <em>pred</em> returns <tt>False</tt>.
# 
# \param mol The molecule to filter in place.
# \param pred The atom predicate to evaluate.
# 
def removeAtomsIfNot(mol: Molecule, pred: AtomPredicate) -> None: pass

##
# \brief Splits the molecular graph <em>molgraph</em> into connected fragments by removing the bonds flagged in <em>split_bond_mask</em>.
# 
# \param molgraph The molecular graph to split.
# \param frag_list The output fragment list receiving the resulting fragments.
# \param split_bond_mask Bit mask selecting the bonds to be virtually removed before fragmentation (bit <tt>i</tt> corresponds to the bond at index <tt>i</tt> in <em>molgraph</em>).
# \param append If <tt>True</tt>, fragments are appended to <em>frag_list</em>. Otherwise, it is cleared first.
# 
def splitIntoFragments(molgraph: MolecularGraph, frag_list: FragmentList, split_bond_mask: Util.BitSet, append: bool = False) -> None: pass

##
# \brief Translates a Sybyl atom type identifier to the corresponding generic Chem.AtomType value.
# 
# \param sybyl_type The Sybyl atom type identifier (Chem.SybylAtomType value).
# 
# \return The corresponding Chem.AtomType value.
# 
def sybylToAtomType(sybyl_type: int) -> int: pass

##
# \brief Transforms the 2D coordinates of all atoms in <em>cntnr</em> by the affine 3&times;3 matrix <em>mtx</em>.
# 
# \param cntnr The atom container.
# \param mtx The 2D affine transformation matrix.
# 
def transform2DCoordinates(cntnr: AtomContainer, mtx: Math.Matrix3D) -> None: pass

##
# \brief Transforms the 3D coordinates of the entities of <em>cntnr</em> by the affine matrix <em>mtx</em>.
# 
# \param cntnr The entity 3D container whose coordinates are to be transformed.
# \param mtx The \f$ 4 \times 4 \f$ affine transformation matrix.
# 
def transform3DCoordinates(cntnr: Entity3DContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief Transforms the conformation at index <em>conf_idx</em> by the homogeneous 4&times;4 matrix <em>mtx</em>.
# 
# \param cntnr The atom container.
# \param conf_idx The zero-based conformation index.
# \param mtx The homogeneous 4&times;4 transformation matrix.
# 
def transformConformation(cntnr: AtomContainer, conf_idx: int, mtx: Math.Matrix4D) -> None: pass

##
# \brief Transforms every stored conformation of the atoms in <em>cntnr</em> by the homogeneous 4&times;4 matrix <em>mtx</em>.
# 
# \param cntnr The atom container.
# \param mtx The homogeneous 4&times;4 transformation matrix.
# 
def transformConformations(cntnr: AtomContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief Translates the atoms/bonds of <em>src_frag</em> to the corresponding atoms/bonds of <em>tgt_molgraph</em> and stores them in <em>tgt_frag</em>.
# 
# \param src_molgraph The source molecular graph providing the original atoms/bonds.
# \param src_frag The fragment defining the atom/bond subset to translate (a fragment of the molecular graph <em>src_molgraph</em>).
# \param tgt_molgraph The target molecular graph providing the translated atoms/bonds.
# \param tgt_frag The output fragment receiving the translated atoms/bonds.
# \param append If <tt>True</tt>, atoms/bonds are appended to <em>tgt_frag</em>. Otherwise, it is cleared first.
# 
def translateFragment(src_molgraph: MolecularGraph, src_frag: Fragment, tgt_molgraph: MolecularGraph, tgt_frag: Fragment, append: bool = False) -> None: pass

##
# \brief Translates every fragment in <em>src_frag_list</em> to the corresponding fragments on <em>tgt_molgraph</em>.
# 
# \param src_molgraph The source molecular graph providing the original atoms/bonds.
# \param src_frag_list The fragments to translate (fragments of the molecular graph <em>src_molgraph</em>).
# \param tgt_molgraph The target molecular graph providing the translated atoms/bonds.
# \param tgt_frag_list The output fragment list receiving the translated fragments.
# \param append If <tt>True</tt>, fragments are appended to <em>tgt_frag_list</em>. Otherwise, it is cleared first.
# 
def translateFragments(src_molgraph: MolecularGraph, src_frag_list: FragmentList, tgt_molgraph: MolecularGraph, tgt_frag_list: FragmentList, append: bool = False) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX parameter of <em>cntnr</em> to <em>fix</em>.
# 
# \param cntnr The control-parameter container.
# \param fix The new parameter value.
# 
def setBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer, fix: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> to <em>single_prec</em>.
# 
# \param cntnr The control-parameter container.
# \param single_prec The new parameter value.
# 
# \since 1.2
# 
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> to <em>enable</em>.
# 
# \param cntnr The control-parameter container.
# \param enable The new parameter value.
# 
# \since 1.3
# 
def setCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_ENABLE_AROMATIC_BOND_TYPES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.3
# 
def getCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_ENABLE_AROMATIC_BOND_TYPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_ATOM_PARITY parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_ATOM_PARITY parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_ATOM_PARITY parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_ATOM_PARITY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_COMPACT_ATOM_DATA parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_COMPACT_ATOM_DATA parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_COMPACT_ATOM_DATA parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_COMPACT_ATOM_DATA parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_COMPACT_BOND_DATA parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_COMPACT_BOND_DATA parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_COMPACT_BOND_DATA parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_COMPACT_BOND_DATA parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_DOUBLE_BOND_STEREO parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_DOUBLE_BOND_STEREO parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_DOUBLE_BOND_STEREO parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_DOUBLE_BOND_STEREO parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_ELEMENT_NAMESPACE parameter of <em>cntnr</em> to <em>ns</em>.
# 
# \param cntnr The control-parameter container.
# \param ns The new XML-namespace string.
# 
# \since 1.2
# 
def setCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer, ns: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_ELEMENT_NAMESPACE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_ELEMENT_NAMESPACE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored XML-namespace string. 
# 
# \since 1.2
# 
def getCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_ELEMENT_NAMESPACE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_ISOTOPE parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_ISOTOPE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_ISOTOPE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_ISOTOPE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_MOLECULE_NAME parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_MOLECULE_NAME parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_MOLECULE_NAME parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_MOLECULE_NAME parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_SINGLE_BOND_STEREO parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_SINGLE_BOND_STEREO parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_SINGLE_BOND_STEREO parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_SINGLE_BOND_STEREO parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_SPIN_MULTIPLICITY parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_SPIN_MULTIPLICITY parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_SPIN_MULTIPLICITY parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_SPIN_MULTIPLICITY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_STRUCTURE_DATA parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_STRUCTURE_DATA parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_STRUCTURE_DATA parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_STRUCTURE_DATA parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CML_OUTPUT_XML_DECLARATION parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CML_OUTPUT_XML_DECLARATION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CML_OUTPUT_XML_DECLARATION parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CML_OUTPUT_XML_DECLARATION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CHECK_LINE_LENGTH parameter of <em>cntnr</em> to <em>check</em>.
# 
# \param cntnr The control-parameter container.
# \param check The new parameter value.
# 
def setCheckLineLengthParameter(cntnr: Base.ControlParameterContainer, check: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CHECK_LINE_LENGTH parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CHECK_LINE_LENGTH parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.CHECK_LINE_LENGTH parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.CONF_INDEX_NAME_SUFFIX_PATTERN parameter of <em>cntnr</em> to <em>pattern</em>.
# 
# \param cntnr The control-parameter container.
# \param pattern The new suffix pattern string.
# 
def setConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer, pattern: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.CONF_INDEX_NAME_SUFFIX_PATTERN parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.CONF_INDEX_NAME_SUFFIX_PATTERN parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored suffix pattern string.
# 
def getConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.CONF_INDEX_NAME_SUFFIX_PATTERN parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.COORDINATES_DIMENSION parameter of <em>cntnr</em> to <em>dim</em>.
# 
# \param cntnr The control-parameter container.
# \param dim The new coordinates dimensionality.
# 
def setCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer, dim: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.COORDINATES_DIMENSION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.COORDINATES_DIMENSION parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored coordinates dimensionality.
# 
def getCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.COORDINATES_DIMENSION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.INCHI_INPUT_OPTIONS parameter of <em>cntnr</em> to <em>opts</em>.
# 
# \param cntnr The control-parameter container.
# \param opts The new InChI input-options string.
# 
def setINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer, opts: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.INCHI_INPUT_OPTIONS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.INCHI_INPUT_OPTIONS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored InChI input-options string.
# 
def getINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.INCHI_INPUT_OPTIONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.INCHI_OUTPUT_OPTIONS parameter of <em>cntnr</em> to <em>opts</em>.
# 
# \param cntnr The control-parameter container.
# \param opts The new <em>InChI</em> output-options string.
# 
def setINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer, opts: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.INCHI_OUTPUT_OPTIONS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.INCHI_OUTPUT_OPTIONS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored <em>InChI</em> output-options string.
# 
def getINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.INCHI_OUTPUT_OPTIONS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.JME_SEPARATE_COMPONENTS parameter of <em>cntnr</em> to <em>separate</em>.
# 
# \param cntnr The control-parameter container.
# \param separate The new parameter value.
# 
def setJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer, separate: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.JME_SEPARATE_COMPONENTS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.JME_SEPARATE_COMPONENTS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.JME_SEPARATE_COMPONENTS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_CTAB_VERSION parameter of <em>cntnr</em> to <em>version</em>.
# 
# \param cntnr The control-parameter container.
# \param version The new CTAB version (see namespace Chem.MDLDataFormatVersion).
# 
def setMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer, version: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_CTAB_VERSION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_CTAB_VERSION parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored CTAB version (see namespace Chem.MDLDataFormatVersion).
# 
def getMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.MDL_CTAB_VERSION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_CONF_ENERGY_SD_TAG parameter of <em>cntnr</em> to <em>tag</em>.
# 
# \param cntnr The control-parameter container.
# \param tag The new <em>MDL SD-File</em> structure data record header string.
# 
def setMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer, tag: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_CONF_ENERGY_SD_TAG parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_CONF_ENERGY_SD_TAG parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored <em>MDL SD-File</em> structure data record header string.
# 
def getMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.MDL_CONF_ENERGY_SD_TAG parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> to <em>enable</em>.
# 
# \param cntnr The control-parameter container.
# \param enable The new parameter value.
# 
# \since 1.3
# 
def setMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_ENABLE_AROMATIC_BOND_TYPES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.3
# 
def getMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_ENABLE_AROMATIC_BOND_TYPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_IGNORE_PARITY parameter of <em>cntnr</em> to <em>ignore</em>.
# 
# \param cntnr The control-parameter container.
# \param ignore The new parameter value.
# 
def setMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_IGNORE_PARITY parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_IGNORE_PARITY parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_IGNORE_PARITY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
def setMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
def setMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_RXN_FILE_VERSION parameter of <em>cntnr</em> to <em>version</em>.
# 
# \param cntnr The control-parameter container.
# \param version The new <em>MDL Rxn-File</em> version (see namespace Chem.MDLDataFormatVersion).
# 
def setMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer, version: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_RXN_FILE_VERSION parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_RXN_FILE_VERSION parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored <em>MDL Rxn-File</em> version (see namespace Chem.MDLDataFormatVersion).
# 
def getMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.MDL_RXN_FILE_VERSION parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_TRIM_LINES parameter of <em>cntnr</em> to <em>trim</em>.
# 
# \param cntnr The control-parameter container.
# \param trim The new parameter value.
# 
def setMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer, trim: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_TRIM_LINES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_TRIM_LINES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_TRIM_LINES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_TRIM_STRINGS parameter of <em>cntnr</em> to <em>trim</em>.
# 
# \param cntnr The control-parameter container.
# \param trim The new parameter value.
# 
def setMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer, trim: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_TRIM_STRINGS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_TRIM_STRINGS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_TRIM_STRINGS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_TRUNCATE_LINES parameter of <em>cntnr</em> to <em>trunc</em>.
# 
# \param cntnr The control-parameter container.
# \param trunc The new parameter value.
# 
def setMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_TRUNCATE_LINES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_TRUNCATE_LINES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_TRUNCATE_LINES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_TRUNCATE_STRINGS parameter of <em>cntnr</em> to <em>trunc</em>.
# 
# \param cntnr The control-parameter container.
# \param trunc The new parameter value.
# 
def setMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_TRUNCATE_STRINGS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_TRUNCATE_STRINGS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_TRUNCATE_STRINGS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MDL_UPDATE_TIMESTAMP parameter of <em>cntnr</em> to <em>update</em>.
# 
# \param cntnr The control-parameter container.
# \param update The new parameter value.
# 
def setMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer, update: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MDL_UPDATE_TIMESTAMP parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MDL_UPDATE_TIMESTAMP parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MDL_UPDATE_TIMESTAMP parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_CALC_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>calc</em>.
# 
# \param cntnr The control-parameter container.
# \param calc The new parameter value.
# 
def setMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_CALC_FORMAL_CHARGES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_CALC_FORMAL_CHARGES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_CALC_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_CHARGE_TYPE parameter of <em>cntnr</em> to <em>type</em>.
# 
# \param cntnr The control-parameter container.
# \param type The new <em>Sybyl MOL2</em> charge type (see namespace Chem.MOL2ChargeType).
# 
def setMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer, type: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_CHARGE_TYPE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_CHARGE_TYPE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored <em>Sybyl MOL2</em> charge type (see namespace Chem.MOL2ChargeType).
# 
def getMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_CHARGE_TYPE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> to <em>enable</em>.
# 
# \param cntnr The control-parameter container.
# \param enable The new parameter value.
# 
def setMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_ENABLE_AROMATIC_BOND_TYPES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_ENABLE_AROMATIC_BOND_TYPES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_ENABLE_AROMATIC_BOND_TYPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter of <em>cntnr</em> to <em>enable</em>.
# 
# \param cntnr The control-parameter container.
# \param enable The new parameter value.
# 
def setMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_ENABLE_EXTENDED_ATOM_TYPES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_MOLECULE_TYPE parameter of <em>cntnr</em> to <em>type</em>.
# 
# \param cntnr The control-parameter container.
# \param type The new <em>Sybyl MOL2</em> molecule type (see namespace Chem.MOL2MoleculeType).
# 
def setMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer, type: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_MOLECULE_TYPE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_MOLECULE_TYPE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored <em>Sybyl MOL2</em> molecule type (see namespace Chem.MOL2MoleculeType).
# 
def getMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_MOLECULE_TYPE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_OUTPUT_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2.3
# 
def setMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_OUTPUT_FORMAL_CHARGES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2.3
# 
def hasMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_OUTPUT_FORMAL_CHARGES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2.3
# 
def getMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_OUTPUT_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2.3
# 
def clearMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_OUTPUT_SUBSTRUCTURES parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
def setMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_OUTPUT_SUBSTRUCTURES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_OUTPUT_SUBSTRUCTURES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_OUTPUT_SUBSTRUCTURES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>read</em>.
# 
# \param cntnr The control-parameter container.
# \param read The new parameter value.
# 
# \since 1.2.3
# 
def setMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer, read: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2.3
# 
def hasMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2.3
# 
def getMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MOL2_READ_PARTIAL_AS_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2.3
# 
def clearMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MULTI_CONF_EXPORT parameter of <em>cntnr</em> to <em>multi_conf</em>.
# 
# \param cntnr The control-parameter container.
# \param multi_conf The new parameter value.
# 
def setMultiConfExportParameter(cntnr: Base.ControlParameterContainer, multi_conf: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MULTI_CONF_EXPORT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MULTI_CONF_EXPORT parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MULTI_CONF_EXPORT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MULTI_CONF_IMPORT parameter of <em>cntnr</em> to <em>multi_conf</em>.
# 
# \param cntnr The control-parameter container.
# \param multi_conf The new parameter value.
# 
def setMultiConfImportParameter(cntnr: Base.ControlParameterContainer, multi_conf: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MULTI_CONF_IMPORT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MULTI_CONF_IMPORT parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.MULTI_CONF_IMPORT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.MULTI_CONF_INPUT_PROCESSOR parameter of <em>cntnr</em> to <em>proc</em>.
# 
# \param cntnr The control-parameter container.
# \param proc The new Chem.MultiConfMoleculeInputProcessor implementation reference.
# 
def setMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer, proc: MultiConfMoleculeInputProcessor) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.MULTI_CONF_INPUT_PROCESSOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.MULTI_CONF_INPUT_PROCESSOR parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored Chem.MultiConfMoleculeInputProcessor implementation reference.
# 
def getMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> MultiConfMoleculeInputProcessor: pass

##
# \brief Removes the Chem.ControlParameter.MULTI_CONF_INPUT_PROCESSOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE parameter of <em>cntnr</em> to <em>deplete</em>.
# 
# \param cntnr The control-parameter container.
# \param deplete The new parameter value.
# 
def setOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer, deplete: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.OUTPUT_CONF_ENERGY_AS_COMMENT parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
def setOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.OUTPUT_CONF_ENERGY_AS_COMMENT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.OUTPUT_CONF_ENERGY_AS_COMMENT parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.OUTPUT_CONF_ENERGY_AS_COMMENT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.RECORD_SEPARATOR parameter of <em>cntnr</em> to <em>sep</em>.
# 
# \param cntnr The control-parameter container.
# \param sep The new record separator string.
# 
def setRecordSeparatorParameter(cntnr: Base.ControlParameterContainer, sep: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.RECORD_SEPARATOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.RECORD_SEPARATOR parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored record separator string.
# 
def getRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.RECORD_SEPARATOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE parameter of <em>cntnr</em> to <em>min_size</em>.
# 
# \param cntnr The control-parameter container.
# \param min_size The new minimum ring size.
# 
def setSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer, min_size: int) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored minimum ring size.
# 
def getSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_MOL_OUTPUT_ATOM_MAPPING_ID parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET parameter of <em>cntnr</em> to <em>no_subset</em>.
# 
# \param cntnr The control-parameter container.
# \param no_subset The new parameter value.
# 
def setSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer, no_subset: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_AROMATIC_BONDS parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_AROMATIC_BONDS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_AROMATIC_BONDS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_AROMATIC_BONDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_ATOM_STEREO parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_ATOM_STEREO parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_ATOM_STEREO parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_ATOM_STEREO parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_CANONICAL_FORM parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_CANONICAL_FORM parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_CANONICAL_FORM parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_CANONICAL_FORM parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_HYDROGEN_COUNT parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.3
# 
def setSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_HYDROGEN_COUNT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_HYDROGEN_COUNT parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.3
# 
def getSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_HYDROGEN_COUNT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.3
# 
def clearSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_ISOTOPE parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_ISOTOPE parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_ISOTOPE parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_ISOTOPE parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_OUTPUT_SINGLE_BONDS parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_OUTPUT_SINGLE_BONDS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_OUTPUT_SINGLE_BONDS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_OUTPUT_SINGLE_BONDS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_RECORD_FORMAT parameter of <em>cntnr</em> to <em>format</em>.
# 
# \param cntnr The control-parameter container.
# \param format The new record-format string.
# 
def setSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer, format: str) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_RECORD_FORMAT parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_RECORD_FORMAT parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The stored record-format string.
# 
def getSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_RECORD_FORMAT parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter of <em>cntnr</em> to <em>output</em>.
# 
# \param cntnr The control-parameter container.
# \param output The new parameter value.
# 
# \since 1.2
# 
def setSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.2
# 
def getSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.SMILES_RXN_OUTPUT_ATOM_MAPPING_ID parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
# \param cntnr The control-parameter container.
# \param strict The new parameter value.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.STRICT_ERROR_CHECKING parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter.
# 
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.STRICT_ERROR_CHECKING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.XYZ_CALC_FORMAL_CHARGES parameter of <em>cntnr</em> to <em>calc</em>.
# 
# \param cntnr The control-parameter container.
# \param calc The new parameter value.
# 
# \since 1.1
# 
def setXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.XYZ_CALC_FORMAL_CHARGES parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.XYZ_CALC_FORMAL_CHARGES parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.1
# 
def getXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.XYZ_CALC_FORMAL_CHARGES parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.XYZ_COMMENT_IS_NAME parameter of <em>cntnr</em> to <em>is_name</em>.
# 
# \param cntnr The control-parameter container.
# \param is_name The new parameter value.
# 
# \since 1.1
# 
def setXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer, is_name: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.XYZ_COMMENT_IS_NAME parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.XYZ_COMMENT_IS_NAME parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.1
# 
def getXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.XYZ_COMMENT_IS_NAME parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.XYZ_PERCEIVE_BOND_ORDERS parameter of <em>cntnr</em> to <em>perceive</em>.
# 
# \param cntnr The control-parameter container.
# \param perceive The new parameter value.
# 
# \since 1.1
# 
def setXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.XYZ_PERCEIVE_BOND_ORDERS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.XYZ_PERCEIVE_BOND_ORDERS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.1
# 
def getXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.XYZ_PERCEIVE_BOND_ORDERS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Chem.ControlParameter.XYZ_PERCEIVE_CONNECTIVITY parameter of <em>cntnr</em> to <em>perceive</em>.
# 
# \param cntnr The control-parameter container.
# \param perceive The new parameter value.
# 
# \since 1.1
# 
def setXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief Tells whether the Chem.ControlParameter.XYZ_PERCEIVE_CONNECTIVITY parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.1
# 
def hasXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Chem.ControlParameter.XYZ_PERCEIVE_CONNECTIVITY parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The value of the parameter. 
# 
# \since 1.1
# 
def getXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Chem.ControlParameter.XYZ_PERCEIVE_CONNECTIVITY parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.1
# 
def clearXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> None: pass
