#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \param molgraph 
#
def clearMDLScalingFactor1(molgraph: MolecularGraph) -> None: pass

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
# \param factor 
#
def setMDLScalingFactor1(molgraph: MolecularGraph, factor: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLScalingFactor2(molgraph: MolecularGraph) -> None: pass

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
# \param factor 
#
def setMDLScalingFactor2(molgraph: MolecularGraph, factor: float) -> None: pass

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
#
def clearSSSR(molgraph: MolecularGraph) -> None: pass

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
# \param sssr 
#
def setSSSR(molgraph: MolecularGraph, sssr: FragmentList) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \return 
#
def copySSSR(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph) -> FragmentList: pass

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
# \param molgraph 
#
def clearStructureData(molgraph: MolecularGraph) -> None: pass

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
# \param data 
#
def setStructureData(molgraph: MolecularGraph, data: StringDataBlock) -> None: pass

##
# \brief 
# \param molgraph 
# \param atom_flags 
# \param bond_flags 
# \param global_stereo 
# \param ord_h_deplete 
# \return 
#
def calcHashCode(molgraph: MolecularGraph, atom_flags: int = 2147483648, bond_flags: int = 2147483648, global_stereo: bool = True, ord_h_deplete: bool = True) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearHashCode(molgraph: MolecularGraph) -> None: pass

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
# \param hash_code 
#
def setHashCode(molgraph: MolecularGraph, hash_code: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLProgramName(molgraph: MolecularGraph) -> None: pass

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
# \param name 
#
def setMDLProgramName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearName(molgraph: MolecularGraph) -> None: pass

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
# \param name 
#
def setName(molgraph: MolecularGraph, name: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMOL2ChargeType(molgraph: MolecularGraph) -> None: pass

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
# \param type 
#
def setMOL2ChargeType(molgraph: MolecularGraph, type: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMOL2MoleculeType(molgraph: MolecularGraph) -> None: pass

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
# \param type 
#
def setMOL2MoleculeType(molgraph: MolecularGraph, type: int) -> None: pass

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
# \param molgraph 
#
def clearCyclicSubstructure(molgraph: MolecularGraph) -> None: pass

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
# \param substruct 
#
def setCyclicSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

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
# \param molgraph 
#
def clearAromaticSubstructure(molgraph: MolecularGraph) -> None: pass

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
# \param substruct 
#
def setAromaticSubstructure(molgraph: MolecularGraph, substruct: Fragment) -> None: pass

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
def canonicalize(molgraph: MolecularGraph, func: CDPL.ForceField.InteractionFilterFunction2, atoms: bool = True, atom_nbrs: bool = True, bonds: bool = True, bond_atoms: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLChiralFlag(molgraph: MolecularGraph) -> None: pass

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
# \param flag 
#
def setMDLChiralFlag(molgraph: MolecularGraph, flag: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param atom_flags 
# \param bond_flags 
#
def calculateCanonicalNumbering(molgraph: MolecularGraph, overwrite: bool, atom_flags: int = 2147483648, bond_flags: int = 2147483648) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calculateMorganNumbering(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
# \param molgraph 
#
def clearMDLCTABVersion(molgraph: MolecularGraph) -> None: pass

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
# \param version 
#
def setMDLCTABVersion(molgraph: MolecularGraph, version: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def buildMatchExpression(molgraph: MolecularGraph) -> MolecularGraphMatchExpression: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def buildMatchExpression(molgraph: MolecularGraph, overwrite: bool) -> MolecularGraphMatchExpression: pass

##
# \brief 
# \param molgraph 
#
def clearMatchExpression(molgraph: MolecularGraph) -> None: pass

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
# \param expr 
#
def setMatchExpression(molgraph: MolecularGraph, expr: MolecularGraphMatchExpression) -> None: pass

##
# \brief 
# \param molgraph 
# \param coords 
# \param energy 
#
def addConformation(molgraph: MolecularGraph, coords: CDPL.Math.Vector3DArray, energy: float) -> None: pass

##
# \brief 
# \param molgraph 
# \param conf_idx 
# \param coords 
# \param energy 
#
def setConformation(molgraph: MolecularGraph, conf_idx: int, coords: CDPL.Math.Vector3DArray, energy: float) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLTimestamp(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLTimestamp(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLTimestamp(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param time 
#
def setMDLTimestamp(molgraph: MolecularGraph, time: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearStoichiometricNumber(molgraph: MolecularGraph) -> None: pass

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
# \param num 
#
def setStoichiometricNumber(molgraph: MolecularGraph, num: float) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLRegistryNumber(molgraph: MolecularGraph) -> None: pass

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
# \param reg_no 
#
def setMDLRegistryNumber(molgraph: MolecularGraph, reg_no: int) -> None: pass

##
# \brief 
# \param molgraph 
# \param rxn_center 
#
def extractReactionCenter(molgraph: MolecularGraph, rxn_center: Fragment) -> None: pass

##
# \brief 
# \param molgraph 
#
def kekulizeBonds(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcFormalCharges(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearConformerEnergies(molgraph: MolecularGraph) -> None: pass

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
def getConformerEnergies(molgraph: MolecularGraph) -> CDPL.Util.DArray: pass

##
# \brief 
# \param molgraph 
# \param energies 
#
def setConformerEnergies(molgraph: MolecularGraph, energies: CDPL.Util.DArray) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcMDLParities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
#
def calcCIPPriorities(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
def perceiveSybylAtomTypes(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
# \param molgraph 
# \param overwrite 
#
def calculate2DCoordinates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param undef_only 
#
def calculateHydrogen3DCoordinates(molgraph: MolecularGraph, undef_only: bool = True) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveHybridizationStates(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setRingFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calculateBond2DStereoFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setAromaticityFlags(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveAromaticRings(molgraph: MolecularGraph) -> FragmentList: pass

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
#
def clearRings(molgraph: MolecularGraph) -> None: pass

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
# \param rings 
#
def setRings(molgraph: MolecularGraph, rings: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def buildMatchExpressionStrings(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLUserInitials(molgraph: MolecularGraph) -> None: pass

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
# \param initials 
#
def setMDLUserInitials(molgraph: MolecularGraph, initials: str) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def setAtomTypesFromSymbols(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
#
def clearPiElectronSystems(molgraph: MolecularGraph) -> None: pass

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
# \param pi_systems 
#
def setPiElectronSystems(molgraph: MolecularGraph, pi_systems: ElectronSystemList) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def buildMatchExpressions(molgraph: MolecularGraph, overwrite: bool) -> None: pass

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
#
def calcAtomCIPConfigurations(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param ring_bonds 
# \param min_ring_size 
#
def calculateBondDirections(molgraph: MolecularGraph, overwrite: bool, ring_bonds: bool = True, min_ring_size: int = 8) -> None: pass

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
# \param molgraph 
#
def clearComponentGroups(molgraph: MolecularGraph) -> None: pass

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
# \param comp_groups 
#
def setComponentGroups(molgraph: MolecularGraph, comp_groups: FragmentList) -> None: pass

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
# \param check_cip_sym 
# \param min_ring_size 
#
def perceiveBondStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_cip_sym: bool = True, min_ring_size: int = 8) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param check_cip_sym 
# \param check_acyclic_subst_sym_only 
#
def perceiveAtomStereoCenters(molgraph: MolecularGraph, overwrite: bool, check_cip_sym: bool = True, check_acyclic_subst_sym_only: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param dim 
# \param min_ring_size 
#
def calcBondStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1, min_ring_size: int = 8) -> None: pass

##
# \brief 
# \param mol_copy 
# \param molgraph 
# \param atom_idx_offs 
# \param bond_start_idx 
#
def copyBondStereoDescriptors(mol_copy: MolecularGraph, molgraph: MolecularGraph, atom_idx_offs: int = 0, bond_start_idx: int = 0) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param dim 
#
def calcAtomStereoDescriptors(molgraph: MolecularGraph, overwrite: bool, dim: int = 1) -> None: pass

##
# \brief 
# \param mol_copy 
# \param molgraph 
# \param atom_idx_offs 
#
def copyAtomStereoDescriptors(mol_copy: MolecularGraph, molgraph: MolecularGraph, atom_idx_offs: int = 0) -> None: pass

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
# \param molgraph 
# \param frag_list 
# \param split_bond_mask 
# \param append 
#
def splitIntoFragments(molgraph: MolecularGraph, frag_list: FragmentList, split_bond_mask: CDPL.Util.BitSet, append: bool = False) -> None: pass

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
#
def clearComponents(molgraph: MolecularGraph) -> None: pass

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
# \param comps 
#
def setComponents(molgraph: MolecularGraph, comps: FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \param constr 
# \param overwrite 
#
def setBondMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param constr 
# \param overwrite 
#
def setAtomMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMatchConstraints(molgraph: MolecularGraph) -> None: pass

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
# \param constr 
#
def setMatchConstraints(molgraph: MolecularGraph, constr: MatchConstraintList) -> None: pass

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
def initSubstructureSearchTarget(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def extractAromaticSSSRSubset(molgraph: MolecularGraph) -> FragmentList: pass

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
# \param molgraph 
#
def clearMDLComment(molgraph: MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMDLComment(molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMDLComment(molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
# \param comment 
#
def setMDLComment(molgraph: MolecularGraph, comment: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getCompleteBondCount(molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearConformationIndex(molgraph: MolecularGraph) -> None: pass

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
# \param index 
#
def setConformationIndex(molgraph: MolecularGraph, index: int) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param overwrite 
# \return 
#
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, overwrite: bool) -> CDPL.Math.ULMatrix: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param mtx 
#
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param src_molgraph 
# \param tgt_molgraph 
# \param mtx 
#
def extractTopologicalDistanceSubMatrix(src_molgraph: MolecularGraph, tgt_molgraph: MolecularGraph, mtx: CDPL.Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def buildBondMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> CDPL.Math.ULMatrix: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def calcTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.SparseULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearTopologicalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

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
def getTopologicalDistanceMatrix(molgraph: MolecularGraph) -> CDPL.Math.ULMatrix: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def setTopologicalDistanceMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def calcGeometricalDistanceMatrix(molgraph: MolecularGraph, overwrite: bool) -> CDPL.Math.DMatrix: pass

##
# \brief 
# \param molgraph 
#
def clearGeometricalDistanceMatrix(molgraph: MolecularGraph) -> None: pass

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
def getGeometricalDistanceMatrix(molgraph: MolecularGraph) -> CDPL.Math.DMatrix: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def setGeometricalDistanceMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.DMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def buildIncidenceMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def buildBondAtomTypeMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def buildBondElectronMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \param mtx 
#
def buildAdjacencyMatrix(molgraph: MolecularGraph, mtx: CDPL.Math.ULMatrix) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def generateINCHIKey(molgraph: MolecularGraph) -> object: pass

##
# \brief 
# \param molgraph 
#
def clearMDLEnergy(molgraph: MolecularGraph) -> None: pass

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
# \param energy 
#
def setMDLEnergy(molgraph: MolecularGraph, energy: float) -> None: pass

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
# \param overwrite 
#
def initSubstructureSearchQuery(molgraph: MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMDLDimensionality(molgraph: MolecularGraph) -> None: pass

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
# \param dim 
#
def setMDLDimensionality(molgraph: MolecularGraph, dim: int) -> None: pass
