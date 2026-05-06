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
# \param atom 
# \param coords 
#
def set2DCoordinates(atom: Atom, coords: Math.Vector2D) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def has2DCoordinates(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def get2DCoordinates(atom: Atom) -> Math.Vector2D: pass

##
# \brief 
# \param atom 
#
def clear2DCoordinates(atom: Atom) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def set2DCoordinates(cntnr: AtomContainer, coords: Math.Vector2DArray) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param append 
#
def get2DCoordinates(cntnr: AtomContainer, coords: Math.Vector2DArray, append: bool = False) -> None: pass

##
# \brief 
# \param bond 
# \param flag 
#
def set2DStereoFlag(bond: Bond, flag: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def has2DStereoFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def get2DStereoFlag(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clear2DStereoFlag(bond: Bond) -> None: pass

##
# \brief 
# \param atom 
# \param coords_array 
#
def set3DCoordinatesArray(atom: Atom, coords_array: Math.Vector3DArray) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def has3DCoordinatesArray(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def get3DCoordinatesArray(atom: Atom) -> Math.Vector3DArray: pass

##
# \brief 
# \param atom 
#
def clear3DCoordinatesArray(atom: Atom) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param coords_func 
# \param append 
#
def get3DCoordinates(cntnr: AtomContainer, coords: Math.Vector3DArray, coords_func: Atom3DCoordinatesFunction, append: bool = False) -> None: pass

##
# \brief 
# \param entity 
# \param coords 
#
def set3DCoordinates(entity: Entity3D, coords: Math.Vector3D) -> None: pass

##
# \brief 
# \param entity 
# \return 
#
def has3DCoordinates(entity: Entity3D) -> bool: pass

##
# \brief 
# \param entity 
# \return 
#
def get3DCoordinates(entity: Entity3D) -> Math.Vector3D: pass

##
# \brief 
# \param entity 
#
def clear3DCoordinates(entity: Entity3D) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def set3DCoordinates(cntnr: Entity3DContainer, coords: Math.Vector3DArray) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param append 
#
def get3DCoordinates(cntnr: Entity3DContainer, coords: Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAromaticRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAromaticSSSRSubset(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param substruct 
#
def setAromaticSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasAromaticSubstructure(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getAromaticSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief 
# \param molgraph 
#
def clearAromaticSubstructure(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param aromatic 
#
def setAromaticityFlag(atom: Atom, aromatic: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasAromaticityFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getAromaticityFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearAromaticityFlag(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param aromatic 
#
def setAromaticityFlag(bond: Bond, aromatic: bool) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasAromaticityFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getAromaticityFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
#
def clearAromaticityFlag(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setAromaticityFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param atom 
# \param id 
#
def setAtomMappingID(atom: Atom, id: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasAtomMappingID(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getAtomMappingID(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearAtomMappingID(atom: Atom) -> None: pass

##
# \brief 
# \param rxn 
# \param mapping 
#
def setAtomMapping(rxn: Reaction, mapping: AtomMapping) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasAtomMapping(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getAtomMapping(rxn: Reaction) -> AtomMapping: pass

##
# \brief 
# \param rxn 
#
def clearAtomMapping(rxn: Reaction) -> None: pass

##
# \brief 
# \param molgraph 
# \param constr 
# \param overwrite 
#
def setAtomMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setAtomMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setAtomSymbolsFromTypes(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setAtomTypesFromSymbols(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param constr 
# \param overwrite 
#
def setBondMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setBondMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param atom 
# \param config 
#
def setCIPConfiguration(atom: Atom, config: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCIPConfiguration(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCIPConfiguration(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearCIPConfiguration(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param config 
#
def setCIPConfiguration(bond: Bond, config: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasCIPConfiguration(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getCIPConfiguration(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clearCIPConfiguration(bond: Bond) -> None: pass

##
# \brief 
# \param atom 
# \param priority 
#
def setCIPPriority(atom: Atom, priority: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCIPPriority(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCIPPriority(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearCIPPriority(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param num 
#
def setCanonicalNumber(atom: Atom, num: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasCanonicalNumber(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getCanonicalNumber(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearCanonicalNumber(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param comment 
#
def setComment(molgraph: MolecularGraph, comment: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasComment(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getComment(molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearComment(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param comment 
#
def setComment(rxn: Reaction, comment: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasComment(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getComment(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearComment(rxn: Reaction) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getCompleteBondCount(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param id 
#
def setComponentGroupID(atom: Atom, id: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasComponentGroupID(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getComponentGroupID(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearComponentGroupID(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param comp_groups 
#
def setComponentGroups(molgraph: MolecularGraph, comp_groups: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasComponentGroups(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getComponentGroups(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearComponentGroups(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param comp_groups 
#
def setComponentGroups(rxn: Reaction, comp_groups: FragmentList) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasComponentGroups(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getComponentGroups(rxn: Reaction) -> FragmentList: pass

##
# \brief 
# \param rxn 
#
def clearComponentGroups(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setComponentMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param comps 
#
def setComponents(molgraph: MolecularGraph, comps: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasComponents(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getComponents(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearComponents(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
# \param coords 
# \param append 
#
def getConformation(cntnr: AtomContainer, conf_idx: int, coords: Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \param conf_idx 
# \return 
#
def getConformationEnergy(molgraph: MolecularGraph, conf_idx: int) -> float: pass

##
# \brief 
# \param molgraph 
# \param index 
#
def setConformationIndex(molgraph: MolecularGraph, index: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasConformationIndex(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getConformationIndex(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearConformationIndex(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param conf_idx 
# \param coords 
# \param energy 
#
def setConformation(molgraph: MolecularGraph, conf_idx: int, coords: Math.Vector3DArray, energy: float) -> None: pass

##
# \brief 
# \param cntnr 
#
def clearConformations(cntnr: AtomContainer) -> None: pass

##
# \brief 
# \param atom 
# \param conf_idx 
# \return 
#
def getConformer3DCoordinates(atom: Atom, conf_idx: int) -> Math.Vector3D: pass

##
# \brief 
# \param molgraph 
# \param energies 
#
def setConformerEnergies(molgraph: MolecularGraph, energies: Util.DArray) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasConformerEnergies(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getConformerEnergies(molgraph: MolecularGraph) -> Util.DArray: pass

##
# \brief 
# \param molgraph 
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
# \brief 
# \param molgraph 
# \param frag_list 
# \param cont_frag_list 
# \param append 
# \param atoms 
# \param bonds 
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
# \brief 
# \param molgraph 
# \param frag_list 
# \param cont_frag_list 
# \param append 
# \param atoms 
# \param bonds 
#
def getContainingFragments(molgraph: MolecularGraph, frag_list: FragmentList, cont_frag_list: FragmentList, append: bool = False, atoms: bool = True, bonds: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param dim 
# \return 
#
def hasCoordinates(cntnr: AtomContainer, dim: int) -> bool: pass

##
# \brief 
# \param molgraph 
# \param substruct 
#
def setCyclicSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasCyclicSubstructure(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getCyclicSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief 
# \param molgraph 
#
def clearCyclicSubstructure(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param bond 
# \param dir 
#
def setDirection(bond: Bond, dir: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasDirection(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getDirection(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clearDirection(bond: Bond) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param max_dist 
# \param env 
# \param append 
# \return 
#
def getEnvironment(atom: Atom, molgraph: MolecularGraph, max_dist: int, env: Fragment, append: bool = False) -> int: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setFormalCharge(atom: Atom, charge: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasFormalCharge(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getFormalCharge(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearFormalCharge(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def getGenericType(atom: Atom) -> int: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def setGeometricalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.DMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasGeometricalDistanceMatrix(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getGeometricalDistanceMatrix(molgraph: MolecularGraph) -> Math.DMatrix: pass

##
# \brief 
# \param molgraph 
#
def clearGeometricalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param hash_code 
#
def setHashCode(molgraph: MolecularGraph, hash_code: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasHashCode(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getHashCode(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearHashCode(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param state 
#
def setHybridizationState(atom: Atom, state: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHybridizationState(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHybridizationState(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearHybridizationState(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param count 
#
def setImplicitHydrogenCount(atom: Atom, count: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasImplicitHydrogenCount(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getImplicitHydrogenCount(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
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
# \brief 
# \param atom 
# \param isotope 
#
def setIsotope(atom: Atom, isotope: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasIsotope(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getIsotope(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearIsotope(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param version 
#
def setMDLCTABVersion(molgraph: MolecularGraph, version: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLCTABVersion(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLCTABVersion(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMDLCTABVersion(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param flag 
#
def setMDLChiralFlag(molgraph: MolecularGraph, flag: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLChiralFlag(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLChiralFlag(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
#
def clearMDLChiralFlag(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param dim 
#
def setMDLDimensionality(molgraph: MolecularGraph, dim: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLDimensionality(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLDimensionality(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMDLDimensionality(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param energy 
#
def setMDLEnergy(molgraph: MolecularGraph, energy: float) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLEnergy(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLEnergy(molgraph: MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
#
def clearMDLEnergy(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param reg_no 
#
def setMDLExternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLExternalRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLExternalRegistryNumber(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearMDLExternalRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param reg_no 
#
def setMDLInternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLInternalRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLInternalRegistryNumber(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearMDLInternalRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param mol_rec 
#
def setMDLMoleculeRecord(rxn: Reaction, mol_rec: Molecule) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLMoleculeRecord(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLMoleculeRecord(rxn: Reaction) -> Molecule: pass

##
# \brief 
# \param rxn 
#
def clearMDLMoleculeRecord(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param parity 
#
def setMDLParity(atom: Atom, parity: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMDLParity(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMDLParity(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearMDLParity(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param name 
#
def setMDLProgramName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLProgramName(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLProgramName(molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearMDLProgramName(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param name 
#
def setMDLProgramName(rxn: Reaction, name: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLProgramName(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLProgramName(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearMDLProgramName(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \param version 
#
def setMDLRXNFileVersion(rxn: Reaction, version: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLRXNFileVersion(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLRXNFileVersion(rxn: Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearMDLRXNFileVersion(rxn: Reaction) -> None: pass

##
# \brief 
# \param molgraph 
# \param reg_no 
#
def setMDLRegistryNumber(molgraph: MolecularGraph, reg_no: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLRegistryNumber(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLRegistryNumber(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMDLRegistryNumber(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param reg_no 
#
def setMDLRegistryNumber(rxn: Reaction, reg_no: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLRegistryNumber(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLRegistryNumber(rxn: Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearMDLRegistryNumber(rxn: Reaction) -> None: pass

##
# \brief 
# \param molgraph 
# \param factor 
#
def setMDLScalingFactor1(molgraph: MolecularGraph, factor: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLScalingFactor1(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLScalingFactor1(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMDLScalingFactor1(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param factor 
#
def setMDLScalingFactor2(molgraph: MolecularGraph, factor: float) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLScalingFactor2(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLScalingFactor2(molgraph: MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
#
def clearMDLScalingFactor2(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param flag 
#
def setMDLStereoCareFlag(atom: Atom, flag: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMDLStereoCareFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMDLStereoCareFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearMDLStereoCareFlag(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param initials 
#
def setMDLUserInitials(molgraph: MolecularGraph, initials: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLUserInitials(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLUserInitials(molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearMDLUserInitials(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param initials 
#
def setMDLUserInitials(rxn: Reaction, initials: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLUserInitials(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLUserInitials(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearMDLUserInitials(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setMOL2Charge(atom: Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2Charge(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2Charge(atom: Atom) -> float: pass

##
# \brief 
# \param atom 
#
def clearMOL2Charge(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param type 
#
def setMOL2ChargeType(molgraph: MolecularGraph, type: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMOL2ChargeType(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMOL2ChargeType(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMOL2ChargeType(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param type 
#
def setMOL2MoleculeType(molgraph: MolecularGraph, type: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMOL2MoleculeType(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMOL2MoleculeType(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearMOL2MoleculeType(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setMOL2Name(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2Name(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2Name(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearMOL2Name(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param chain 
#
def setMOL2SubstructureChain(atom: Atom, chain: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2SubstructureChain(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2SubstructureChain(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureChain(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param id 
#
def setMOL2SubstructureID(atom: Atom, id: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2SubstructureID(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2SubstructureID(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureID(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setMOL2SubstructureName(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2SubstructureName(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2SubstructureName(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureName(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param subtype 
#
def setMOL2SubstructureSubtype(atom: Atom, subtype: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMOL2SubstructureSubtype(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMOL2SubstructureSubtype(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureSubtype(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param constr 
#
def setMatchConstraints(atom: Atom, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMatchConstraints(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMatchConstraints(atom: Atom) -> MatchConstraintList: pass

##
# \brief 
# \param atom 
#
def clearMatchConstraints(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param constr 
#
def setMatchConstraints(bond: Bond, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasMatchConstraints(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getMatchConstraints(bond: Bond) -> MatchConstraintList: pass

##
# \brief 
# \param bond 
#
def clearMatchConstraints(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param constr 
#
def setMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMatchConstraints(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMatchConstraints(molgraph: MolecularGraph) -> MatchConstraintList: pass

##
# \brief 
# \param molgraph 
#
def clearMatchConstraints(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
#
def setMatchConstraints(rxn: Reaction, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMatchConstraints(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMatchConstraints(rxn: Reaction) -> MatchConstraintList: pass

##
# \brief 
# \param rxn 
#
def clearMatchConstraints(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param expr 
#
def setMatchExpression(atom: Atom, expr: AtomMatchExpression) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMatchExpression(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMatchExpression(atom: Atom) -> AtomMatchExpression: pass

##
# \brief 
# \param atom 
#
def clearMatchExpression(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param expr 
#
def setMatchExpression(bond: Bond, expr: BondMatchExpression) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasMatchExpression(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getMatchExpression(bond: Bond) -> BondMatchExpression: pass

##
# \brief 
# \param bond 
#
def clearMatchExpression(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param expr 
#
def setMatchExpression(molgraph: MolecularGraph, expr: MolecularGraphMatchExpression) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMatchExpression(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMatchExpression(molgraph: MolecularGraph) -> MolecularGraphMatchExpression: pass

##
# \brief 
# \param molgraph 
#
def clearMatchExpression(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param expr 
#
def setMatchExpression(rxn: Reaction, expr: ReactionMatchExpression) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMatchExpression(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMatchExpression(rxn: Reaction) -> ReactionMatchExpression: pass

##
# \brief 
# \param rxn 
#
def clearMatchExpression(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param expr_str 
#
def setMatchExpressionString(atom: Atom, expr_str: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMatchExpressionString(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMatchExpressionString(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearMatchExpressionString(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param expr_str 
#
def setMatchExpressionString(bond: Bond, expr_str: str) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasMatchExpressionString(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getMatchExpressionString(bond: Bond) -> str: pass

##
# \brief 
# \param bond 
#
def clearMatchExpressionString(bond: Bond) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMaxAtomMappingID(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMaxAtomMappingID(rxn: Reaction) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMaxComponentGroupID(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMaxComponentGroupID(rxn: Reaction) -> int: pass

##
# \brief 
# \param atom 
# \param num 
#
def setMorganNumber(atom: Atom, num: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMorganNumber(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMorganNumber(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearMorganNumber(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setName(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasName(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getName(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearName(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param name 
#
def setName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasName(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getName(molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearName(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param name 
#
def setName(rxn: Reaction, name: str) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasName(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getName(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
#
def clearName(rxn: Reaction) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getNumConformations(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getNumContainingFragments(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \return 
#
def getNumContainingFragments(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param bond 
# \param order 
#
def setOrder(bond: Bond, order: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasOrder(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getOrder(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clearOrder(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param pi_systems 
#
def setPiElectronSystems(molgraph: MolecularGraph, pi_systems: ElectronSystemList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasPiElectronSystems(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getPiElectronSystems(molgraph: MolecularGraph) -> ElectronSystemList: pass

##
# \brief 
# \param molgraph 
#
def clearPiElectronSystems(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param type 
#
def setRadicalType(atom: Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasRadicalType(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getRadicalType(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearRadicalType(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \param status 
#
def setReactionCenterStatus(atom: Atom, status: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasReactionCenterStatus(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getReactionCenterStatus(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearReactionCenterStatus(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param status 
#
def setReactionCenterStatus(bond: Bond, status: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasReactionCenterStatus(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getReactionCenterStatus(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clearReactionCenterStatus(bond: Bond) -> None: pass

##
# \brief 
# \param rxn 
# \param data 
#
def setReactionData(rxn: Reaction, data: StringDataBlock) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasReactionData(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getReactionData(rxn: Reaction) -> StringDataBlock: pass

##
# \brief 
# \param rxn 
#
def clearReactionData(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom 
# \param in_ring 
#
def setRingFlag(atom: Atom, in_ring: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasRingFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getRingFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearRingFlag(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param in_ring 
#
def setRingFlag(bond: Bond, in_ring: bool) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasRingFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getRingFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
#
def clearRingFlag(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setRingFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param rings 
#
def setRings(molgraph: MolecularGraph, rings: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasRings(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearRings(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param sssr 
#
def setSSSR(molgraph: MolecularGraph, sssr: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasSSSR(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getSSSR(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearSSSR(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getSizeOfLargestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \return 
#
def getSizeOfLargestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getSizeOfSmallestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \return 
#
def getSizeOfSmallestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param atom 
# \param is_center 
#
def setStereoCenterFlag(atom: Atom, is_center: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasStereoCenterFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getStereoCenterFlag(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearStereoCenterFlag(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param is_center 
#
def setStereoCenterFlag(bond: Bond, is_center: bool) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasStereoCenterFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getStereoCenterFlag(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
#
def clearStereoCenterFlag(bond: Bond) -> None: pass

##
# \brief 
# \param atom 
# \param descr 
#
def setStereoDescriptor(atom: Atom, descr: StereoDescriptor) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasStereoDescriptor(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getStereoDescriptor(atom: Atom) -> StereoDescriptor: pass

##
# \brief 
# \param atom 
#
def clearStereoDescriptor(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param descr 
#
def setStereoDescriptor(bond: Bond, descr: StereoDescriptor) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasStereoDescriptor(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getStereoDescriptor(bond: Bond) -> StereoDescriptor: pass

##
# \brief 
# \param bond 
#
def clearStereoDescriptor(bond: Bond) -> None: pass

##
# \brief 
# \param molgraph 
# \param num 
#
def setStoichiometricNumber(molgraph: MolecularGraph, num: float) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasStoichiometricNumber(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getStoichiometricNumber(molgraph: MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
#
def clearStoichiometricNumber(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param data 
#
def setStructureData(molgraph: MolecularGraph, data: StringDataBlock) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasStructureData(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getStructureData(molgraph: MolecularGraph) -> StringDataBlock: pass

##
# \brief 
# \param molgraph 
#
def clearStructureData(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param sybyl_type 
# \return 
#
def getSybylAtomTypeString(sybyl_type: int) -> str: pass

##
# \brief 
# \param sybyl_type 
# \return 
#
def getSybylBondTypeString(sybyl_type: int) -> str: pass

##
# \brief 
# \param atom 
# \param type 
#
def setSybylType(atom: Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSybylType(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSybylType(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearSybylType(atom: Atom) -> None: pass

##
# \brief 
# \param bond 
# \param type 
#
def setSybylType(bond: Bond, type: int) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasSybylType(bond: Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getSybylType(bond: Bond) -> int: pass

##
# \brief 
# \param bond 
#
def clearSybylType(bond: Bond) -> None: pass

##
# \brief 
# \param atom 
# \param symbol 
#
def setSymbol(atom: Atom, symbol: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSymbol(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSymbol(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearSymbol(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def getSymbolForType(atom: Atom) -> str: pass

##
# \brief 
# \param atom 
# \param class_id 
#
def setSymmetryClass(atom: Atom, class_id: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSymmetryClass(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSymmetryClass(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearSymmetryClass(atom: Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param time 
#
def setTimestamp(molgraph: MolecularGraph, time: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasTimestamp(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getTimestamp(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearTimestamp(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param rxn 
# \param time 
#
def setTimestamp(rxn: Reaction, time: int) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasTimestamp(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getTimestamp(rxn: Reaction) -> int: pass

##
# \brief 
# \param rxn 
#
def clearTimestamp(rxn: Reaction) -> None: pass

##
# \brief 
# \param atom1 
# \param atom2 
# \param molgraph 
# \return 
#
def getTopologicalDistance(atom1: Atom, atom2: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def setTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasTopologicalDistanceMatrix(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getTopologicalDistanceMatrix(molgraph: MolecularGraph) -> Math.ULMatrix: pass

##
# \brief 
# \param molgraph 
#
def clearTopologicalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param type 
#
def setType(atom: Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasType(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getType(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearType(atom: Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def getTypeForSymbol(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
# \param count 
#
def setUnpairedElectronCount(atom: Atom, count: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasUnpairedElectronCount(atom: Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getUnpairedElectronCount(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearUnpairedElectronCount(atom: Atom) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def addConformation(cntnr: AtomContainer, coords: Math.Vector3DArray) -> None: pass

##
# \brief 
# \param molgraph 
# \param coords 
# \param energy 
#
def addConformation(molgraph: MolecularGraph, coords: Math.Vector3DArray, energy: float) -> None: pass

##
# \brief 
# \param molgraph 
# \param atoms 
# \param ref_coords 
# \param fix_bond_stereo 
# \return 
#
def align2DCoordinates(molgraph: MolecularGraph, atoms: AtomContainer, ref_coords: Math.Vector2DArray, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief 
# \param molgraph 
# \param ref_atom_mpg 
# \param fix_bond_stereo 
# \return 
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
# \brief 
# \param molgraph 
# \param ref_molgraph 
# \param substr_ptn 
# \param fix_bond_stereo 
# \return 
#
def align2DCoordinates(molgraph: MolecularGraph, ref_molgraph: MolecularGraph, substr_ptn: MolecularGraph, fix_bond_stereo: bool = True) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ref_entities 
# \param ref_coords 
# \return 
#
def align3DCoordinates(cntnr: Entity3DContainer, ref_entities: Entity3DContainer, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ref_atoms 
# \param ref_coords 
# \return 
#
def alignConformations(cntnr: AtomContainer, ref_atoms: Util.BitSet, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ref_atoms 
# \param ref_coords 
# \return 
#
def alignConformations(cntnr: AtomContainer, ref_atoms: AtomContainer, ref_coords: Math.Vector3DArray) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ref_atoms 
# \return 
#
def alignConformations(cntnr: AtomContainer, ref_atoms: Util.BitSet) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ref_atoms 
# \return 
#
def alignConformations(cntnr: AtomContainer, ref_atoms: AtomContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
#
def applyConformation(cntnr: AtomContainer, conf_idx: int) -> None: pass

##
# \brief 
# \param qry_type 
# \param tgt_type 
# \return 
#
def atomTypesMatch(qry_type: int, tgt_type: int) -> bool: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calc2DCoordinates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcAtomCIPConfigurations(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcAtomStereoDescriptorsFromMDLParities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param dim 
# \param check_stc_flag 
#
def calcAtomStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1, check_stc_flag: bool = True) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcBasicProperties(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def calcBasicProperties(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcBond2DStereoFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcBondCIPConfigurations(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param dim 
# \param check_stc_flag 
#
def calcBondStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1, check_stc_flag: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \param reset 
#
def calcBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction, reset: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param reset 
#
def calcBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D, reset: bool = True) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcCIPPriorities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param atom_flags 
# \param bond_flags 
#
def calcCanonicalNumbering(molgraph: MolecularGraph, overwrite: bool, atom_flags: int = 2147483648, bond_flags: int = 2147483648) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param ctr 
# \return 
#
def calcCenterOfMass(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param ctr 
# \return 
#
def calcCentroid(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param ctr 
# \return 
#
def calcCentroid(cntnr: Entity3DContainer, ctr: Math.Vector3D) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param descr 
# \param coords 
# \return 
#
def calcConfiguration(atom: Atom, molgraph: MolecularGraph, descr: StereoDescriptor, coords: Math.Vector3DArray) -> int: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param descr 
# \param coords 
# \return 
#
def calcConfiguration(bond: Bond, molgraph: MolecularGraph, descr: StereoDescriptor, coords: Math.Vector3DArray) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcFormalCharge(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcFormalCharges(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def calcGeometricalDistanceMatrix(cntnr: Entity3DContainer, mtx: Math.DMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def calcGeometricalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> Math.DMatrix: pass

##
# \brief 
# \param molgraph 
# \param atom_flags 
# \param bond_flags 
# \param ord_h_deplete 
# \return 
#
def calcHashCode(molgraph: MolecularGraph, atom_flags: int = 2147483648, bond_flags: int = 2147483648, ord_h_deplete: bool = True) -> int: pass

##
# \brief 
# \param rxn 
# \param role_mask 
# \param atom_flags 
# \param bond_flags 
# \param ord_h_deplete 
# \return 
#
def calcHashCode(rxn: Reaction, role_mask: int = 7, atom_flags: int = 2147483648, bond_flags: int = 2147483648, ord_h_deplete: bool = True) -> int: pass

##
# \brief 
# \param molgraph 
# \param undef_only 
#
def calcHydrogen3DCoordinates(molgraph: MolecularGraph, undef_only: bool = True) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcImplicitHydrogenCount(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcImplicitHydrogenCounts(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcMDLParities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcMDLParity(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcMorganNumbering(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param dim 
# \return 
#
def calcStereoDescriptor(atom: Atom, molgraph: MolecularGraph, dim: int = 1) -> StereoDescriptor: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param dim 
# \return 
#
def calcStereoDescriptor(bond: Bond, molgraph: MolecularGraph, dim: int = 1) -> StereoDescriptor: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcStereoDescriptorFromMDLParity(atom: Atom, molgraph: MolecularGraph) -> StereoDescriptor: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> Math.ULMatrix: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param atoms 
# \param atom_nbrs 
# \param bonds 
# \param bond_atoms 
#
def canonicalize(molgraph: MolecularGraph, atoms: bool = True, atom_nbrs: bool = True, bonds: bool = True, bond_atoms: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \param func 
# \param atoms 
# \param atom_nbrs 
# \param bonds 
# \param bond_atoms 
#
def canonicalize(molgraph: MolecularGraph, func: BoolAtom2Functor, atoms: bool = True, atom_nbrs: bool = True, bonds: bool = True, bond_atoms: bool = False) -> None: pass

##
# \brief 
# \param mol 
# \param coords_func 
# \param dist_tol 
# \param atom_idx_offs 
#
def connectAtoms(mol: Molecule, coords_func: Atom3DCoordinatesFunction, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief 
# \param mol 
# \param dist_tol 
# \param atom_idx_offs 
#
def connectAtoms(mol: Molecule, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief 
# \param frag_list 
# \param bond 
# \return 
#
def containsFragmentWithBond(frag_list: FragmentList, bond: Bond) -> bool: pass

##
# \brief 
# \param frag_list 
# \param min_size 
# \return 
#
def containsFragmentWithMinSize(frag_list: FragmentList, min_size: int) -> bool: pass

##
# \brief 
# \param molgraph 
# \param sub_molgraph 
# \param atoms 
# \param bonds 
# \return 
#
def containsMolecularGraph(molgraph: MolecularGraph, sub_molgraph: MolecularGraph, atoms: bool = True, bonds: bool = True) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mol 
# \param pred 
# \param append 
#
def copyAtomsIf(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param frag 
# \param pred 
# \param append 
#
def copyAtomsIf(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param mol 
# \param pred 
# \param append 
#
def copyAtomsIfNot(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param frag 
# \param pred 
# \param append 
#
def copyAtomsIfNot(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param mask 
# \param type 
# \param reset 
# \param strict 
# \return 
#
def createAtomTypeMask(cntnr: AtomContainer, mask: Util.BitSet, type: int, reset: bool = True, strict: bool = True) -> int: pass

##
# \brief 
# \param molgraph 
# \param result_mol 
# \param search_ptns 
# \param result_ptn 
# \param exclude_ptns 
# \return 
#
def editSubstructures(molgraph: MolecularGraph, result_mol: Molecule, search_ptns: str, result_ptn: str, exclude_ptns: str = '') -> int: pass

##
# \brief 
# \param mol 
# \param search_ptns 
# \param result_ptn 
# \param exclude_ptns 
# \return 
#
def editSubstructures(mol: Molecule, search_ptns: str, result_ptn: str, exclude_ptns: str = '') -> int: pass

##
# \brief 
# \param min 
# \param max 
# \param coords 
# \param reset 
#
def extendBoundingBox(min: Math.Vector3D, max: Math.Vector3D, coords: Math.Vector3D, reset: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \param rxn_center 
#
def extractReactionCenter(molgraph: MolecularGraph, rxn_center: Fragment) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \return 
#
def extractSSSRSubset(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param overwrite 
# \return 
#
def extractSSSRSubset(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param overwrite 
# \return 
#
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, overwrite: bool) -> Math.ULMatrix: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param mtx 
#
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, mtx: Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def generateAdjacencyMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def generateBondAtomTypeMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def generateBondElectronMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
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
# \brief 
# \param molgraph 
# \param mtx 
#
def generateIncidenceMatrix(molgraph: MolecularGraph, mtx: Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def generateMatchExpression(atom: Atom, molgraph: MolecularGraph) -> AtomMatchExpression: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def generateMatchExpression(bond: Bond, molgraph: MolecularGraph) -> BondMatchExpression: pass

##
# \brief 
# \param molgraph 
# \return 
#
def generateMatchExpression(molgraph: MolecularGraph) -> MolecularGraphMatchExpression: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def generateMatchExpression(molgraph: MolecularGraph, overwrite: bool) -> MolecularGraphMatchExpression: pass

##
# \brief 
# \param rxn 
# \return 
#
def generateMatchExpression(rxn: Reaction) -> ReactionMatchExpression: pass

##
# \brief 
# \param rxn 
# \param overwrite 
# \return 
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
# \brief 
# \param molgraph 
# \param overwrite 
#
def generateMatchExpressionStrings(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def generateMatchExpressions(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
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
# \brief 
# \param molgraph 
# \param overwrite 
#
def initSubstructureSearchQuery(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def initSubstructureSearchQuery(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def initSubstructureSearchTarget(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def initSubstructureSearchTarget(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \return 
#
def insideBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \return 
#
def insideBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D) -> bool: pass

##
# \brief 
# \param min 
# \param max 
# \param coords 
# \return 
#
def insideBoundingBox(min: Math.Vector3D, max: Math.Vector3D, coords: Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \return 
#
def intersectsBoundingBox(cntnr: AtomContainer, min: Math.Vector3D, max: Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \return 
#
def intersectsBoundingBox(cntnr: Entity3DContainer, min: Math.Vector3D, max: Math.Vector3D) -> bool: pass

##
# \brief 
# \param ring 
# \param molgraph 
# \param arom_bond_mask 
# \return 
#
def isAromatic(ring: Fragment, molgraph: MolecularGraph, arom_bond_mask: Util.BitSet) -> bool: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \param size 
# \return 
#
def isInFragmentOfSize(atom: Atom, frag_list: FragmentList, size: int) -> bool: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \param size 
# \return 
#
def isInFragmentOfSize(bond: Bond, frag_list: FragmentList, size: int) -> bool: pass

##
# \brief 
# \param ring 
# \param molgraph 
# \return 
#
def isNotAromatic(ring: Fragment, molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param check_asym 
# \param check_inv_n 
# \param check_quart_n 
# \param check_plan_n 
# \param check_amide_n 
# \param check_res_ctrs 
# \return 
#
def isStereoCenter(atom: Atom, molgraph: MolecularGraph, check_asym: bool = True, check_inv_n: bool = True, check_quart_n: bool = True, check_plan_n: bool = True, check_amide_n: bool = True, check_res_ctrs: bool = True) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param check_asym 
# \param check_term_n 
# \param check_order 
# \param min_ring_size 
# \return 
#
def isStereoCenter(bond: Bond, molgraph: MolecularGraph, check_asym: bool = True, check_term_n: bool = True, check_order: bool = True, min_ring_size: int = 8) -> bool: pass

##
# \brief 
# \param molgraph 
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
# \see Chem.isOrdinaryHydrogen
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
# \see Chem.isOrdinaryHydrogen
# 
def makeOrdinaryHydrogenDeplete(mol: Molecule, flags: int, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param atom_mask 
# \param reset 
#
def markReachableAtoms(atom: Atom, molgraph: MolecularGraph, atom_mask: Util.BitSet, reset: bool = True) -> None: pass

##
# \brief 
# \param smarts 
# \param init_qry 
# \return 
#
def parseSMARTS(smarts: str, init_qry: bool = True) -> Molecule: pass

##
# \brief 
# \param smarts 
# \param mol 
# \param init_qry 
# \return 
#
def parseSMARTS(smarts: str, mol: Molecule, init_qry: bool = True) -> bool: pass

##
# \brief 
# \param smiles 
# \return 
#
def parseSMILES(smiles: str) -> Molecule: pass

##
# \brief 
# \param smiles 
# \param mol 
# \return 
#
def parseSMILES(smiles: str, mol: Molecule) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveAromaticSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveAromaticSubstructure(molgraph: MolecularGraph, overwrite: bool) -> Fragment: pass

##
# \brief 
# \param rxn 
# \return 
#
def perceiveAtomMapping(rxn: Reaction) -> AtomMapping: pass

##
# \brief 
# \param rxn 
# \param overwrite 
# \return 
#
def perceiveAtomMapping(rxn: Reaction, overwrite: bool) -> AtomMapping: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param check_asym 
# \param check_inv_n 
# \param check_quart_n 
# \param check_plan_n 
# \param check_amide_n 
# \param check_res_ctrs 
#
def perceiveAtomStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_asym: bool = True, check_inv_n: bool = True, check_quart_n: bool = True, check_plan_n: bool = True, check_amide_n: bool = True, check_res_ctrs: bool = True) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveBondOrders(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param check_asym 
# \param check_term_n 
# \param check_order 
# \param min_ring_size 
#
def perceiveBondStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_asym: bool = True, check_term_n: bool = True, check_order: bool = True, min_ring_size: int = 8) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveComponentGroups(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveComponentGroups(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param rxn 
# \return 
#
def perceiveComponentGroups(rxn: Reaction) -> FragmentList: pass

##
# \brief 
# \param rxn 
# \param overwrite 
# \return 
#
def perceiveComponentGroups(rxn: Reaction, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveComponents(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveComponents(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveCyclicSubstructure(molgraph: MolecularGraph) -> Fragment: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveCyclicSubstructure(molgraph: MolecularGraph, overwrite: bool) -> Fragment: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def perceiveHybridizationState(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveHybridizationStates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceivePiElectronSystems(molgraph: MolecularGraph) -> ElectronSystemList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceivePiElectronSystems(molgraph: MolecularGraph, overwrite: bool) -> ElectronSystemList: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveRings(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveRings(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveSSSR(molgraph: MolecularGraph) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveSSSR(molgraph: MolecularGraph, overwrite: bool) -> FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveSybylAtomTypes(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def perceiveSybylType(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def perceiveSybylType(bond: Bond, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param atom_flags 
# \param bond_flags 
# \param inc_impl_h 
#
def perceiveSymmetryClasses(molgraph: MolecularGraph, overwrite: bool, atom_flags: int = 2147483648, bond_flags: int = 2147483648, inc_impl_h: bool = True) -> None: pass

##
# \brief 
# \param frag 
# \param pred 
#
def removeAtomsIf(frag: Fragment, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param mol 
# \param pred 
#
def removeAtomsIf(mol: Molecule, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param frag 
# \param pred 
#
def removeAtomsIfNot(frag: Fragment, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param mol 
# \param pred 
#
def removeAtomsIfNot(mol: Molecule, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param molgraph 
# \param frag_list 
# \param split_bond_mask 
# \param append 
#
def splitIntoFragments(molgraph: MolecularGraph, frag_list: FragmentList, split_bond_mask: Util.BitSet, append: bool = False) -> None: pass

##
# \brief 
# \param sybyl_type 
# \return 
#
def sybylToAtomType(sybyl_type: int) -> int: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform2DCoordinates(cntnr: AtomContainer, mtx: Math.Matrix3D) -> None: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform3DCoordinates(cntnr: Entity3DContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
# \param mtx 
#
def transformConformation(cntnr: AtomContainer, conf_idx: int, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transformConformations(cntnr: AtomContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param src_frag 
# \param tgt_molgraph 
# \param tgt_frag 
# \param append 
#
def translateFragment(src_molgraph: MolecularGraph, src_frag: Fragment, tgt_molgraph: MolecularGraph, tgt_frag: Fragment, append: bool = False) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param src_frag_list 
# \param tgt_molgraph 
# \param tgt_frag_list 
# \param append 
#
def translateFragments(src_molgraph: MolecularGraph, src_frag_list: FragmentList, tgt_molgraph: MolecularGraph, tgt_frag_list: FragmentList, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param fix 
#
def setBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer, fix: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearBondMemberSwapStereoFixParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param single_prec 
#
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputAtomParityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputCompactAtomDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputCompactBondDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputDoubleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param ns 
#
def setCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer, ns: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputElementNamespaceParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputMoleculeNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputSingleBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputSpinMultiplicityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputStructureDataParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCMLOutputXMLDeclarationParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param check 
#
def setCheckLineLengthParameter(cntnr: Base.ControlParameterContainer, check: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCheckLineLengthParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param pattern 
#
def setConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer, pattern: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearConfIndexNameSuffixPatternParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param dim 
#
def setCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer, dim: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearCoordinatesDimensionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param opts 
#
def setINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer, opts: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearINCHIInputOptionsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param opts 
#
def setINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer, opts: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearINCHIOutputOptionsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param separate 
#
def setJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer, separate: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearJMESeparateComponentsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param version 
#
def setMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer, version: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearMDLCTABVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param tag 
#
def setMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer, tag: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearMDLConfEnergySDTagParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLEnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param ignore 
#
def setMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLIgnoreParityParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLOutputConfEnergyAsSDEntryParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLOutputConfEnergyToEnergyFieldParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param version 
#
def setMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer, version: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearMDLRXNFileVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param trim 
#
def setMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer, trim: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLTrimLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param trim 
#
def setMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer, trim: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLTrimStringsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param trunc 
#
def setMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param trunc 
#
def setMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLTruncateStringsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param update 
#
def setMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer, update: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMDLUpdateTimestampParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param calc 
#
def setMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2CalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param type 
#
def setMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer, type: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2ChargeTypeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2EnableAromaticBondTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param enable 
#
def setMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer, enable: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2EnableExtendedAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param type 
#
def setMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer, type: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2MoleculeTypeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2OutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2OutputSubstructuresParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param read 
#
def setMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer, read: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMOL2ReadPartialAsFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param multi_conf 
#
def setMultiConfExportParameter(cntnr: Base.ControlParameterContainer, multi_conf: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMultiConfExportParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param multi_conf 
#
def setMultiConfImportParameter(cntnr: Base.ControlParameterContainer, multi_conf: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMultiConfImportParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param proc 
#
def setMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer, proc: MultiConfMoleculeInputProcessor) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> MultiConfMoleculeInputProcessor: pass

##
# \brief 
# \param cntnr 
#
def clearMultiConfInputProcessorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param deplete 
#
def setOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer, deplete: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearOrdinaryHydrogenDepleteParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearOutputConfEnergyAsCommentParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param sep 
#
def setRecordSeparatorParameter(cntnr: Base.ControlParameterContainer, sep: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearRecordSeparatorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param min_size 
#
def setSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer, min_size: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESMinStereoBondRingSizeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESMolOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param no_subset 
#
def setSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer, no_subset: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESNoOrganicSubsetParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputAromaticBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputAtomStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputCanonicalFormParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputHydrogenCountParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputIsotopeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputKekuleFormParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputRingBondStereoParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESOutputSingleBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param format 
#
def setSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer, format: str) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> str: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESRecordFormatParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearSMILESRxnOutputAtomMappingIDParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param strict 
#
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param calc 
#
def setXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearXYZCalcFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param is_name 
#
def setXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer, is_name: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearXYZCommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param perceive 
#
def setXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearXYZPerceiveBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param perceive 
#
def setXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearXYZPerceiveConnectivityParameter(cntnr: Base.ControlParameterContainer) -> None: pass
