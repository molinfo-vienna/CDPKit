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
# \param atom 
#
def clearMOL2SubstructureID(atom: Atom) -> None: pass

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
# \param id 
#
def setMOL2SubstructureID(atom: Atom, id: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearAtomMappingID(atom: Atom) -> None: pass

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
# \param id 
#
def setAtomMappingID(atom: Atom, id: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearComponentGroupID(atom: Atom) -> None: pass

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
# \param id 
#
def setComponentGroupID(atom: Atom, id: int) -> None: pass

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
# \param atom 
#
def clearMOL2Charge(atom: Atom) -> None: pass

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
# \param charge 
#
def setMOL2Charge(atom: Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcFormalCharge(atom: Atom, molgraph: MolecularGraph) -> int: pass

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
# \param charge 
#
def setFormalCharge(atom: Atom, charge: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearMOL2Name(atom: Atom) -> None: pass

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
# \param name 
#
def setMOL2Name(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureName(atom: Atom) -> None: pass

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
# \param name 
#
def setMOL2SubstructureName(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearName(atom: Atom) -> None: pass

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
# \param name 
#
def setName(atom: Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearIsotope(atom: Atom) -> None: pass

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
# \param isotope 
#
def setIsotope(atom: Atom, isotope: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def getGenericType(atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearRadicalType(atom: Atom) -> None: pass

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
# \param type 
#
def setRadicalType(atom: Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def perceiveSybylType(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearSybylType(atom: Atom) -> None: pass

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
# \param type 
#
def setSybylType(atom: Atom, type: int) -> None: pass

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
def getSymbolForType(atom: Atom) -> str: pass

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
# \param type 
#
def setType(atom: Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureSubtype(atom: Atom) -> None: pass

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
# \param subtype 
#
def setMOL2SubstructureSubtype(atom: Atom, subtype: str) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def perceiveHybridizationState(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearHybridizationState(atom: Atom) -> None: pass

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
# \param state 
#
def setHybridizationState(atom: Atom, state: int) -> None: pass

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
# \param atom 
#
def clearMDLStereoCareFlag(atom: Atom) -> None: pass

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
# \param flag 
#
def setMDLStereoCareFlag(atom: Atom, flag: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearRingFlag(atom: Atom) -> None: pass

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
# \param in_ring 
#
def setRingFlag(atom: Atom, in_ring: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearStereoCenterFlag(atom: Atom) -> None: pass

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
# \param is_center 
#
def setStereoCenterFlag(atom: Atom, is_center: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearAromaticityFlag(atom: Atom) -> None: pass

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
# \param aromatic 
#
def setAromaticityFlag(atom: Atom, aromatic: bool) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def buildMatchExpressionString(atom: Atom, molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param atom 
#
def clearMatchExpressionString(atom: Atom) -> None: pass

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
# \param expr_str 
#
def setMatchExpressionString(atom: Atom, expr_str: str) -> None: pass

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
def getTypeForSymbol(atom: Atom) -> int: pass

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
# \param symbol 
#
def setSymbol(atom: Atom, symbol: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearMOL2SubstructureChain(atom: Atom) -> None: pass

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
# \param chain 
#
def setMOL2SubstructureChain(atom: Atom, chain: str) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def buildMatchExpression(atom: Atom, molgraph: MolecularGraph) -> AtomMatchExpression: pass

##
# \brief 
# \param atom 
#
def clearMatchExpression(atom: Atom) -> None: pass

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
# \param expr 
#
def setMatchExpression(atom: Atom, expr: AtomMatchExpression) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcCIPConfiguration(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param cip_pri_func 
# \return 
#
def calcCIPConfiguration(atom: Atom, molgraph: MolecularGraph, cip_pri_func: SizeTypeAtomFunctor) -> int: pass

##
# \brief 
# \param atom 
#
def clearCIPConfiguration(atom: Atom) -> None: pass

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
# \param config 
#
def setCIPConfiguration(atom: Atom, config: int) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param descr 
# \param coords 
# \return 
#
def calcAtomConfiguration(atom: Atom, molgraph: MolecularGraph, descr: StereoDescriptor, coords: CDPL.Math.Vector3DArray) -> int: pass

##
# \brief 
# \param atom 
#
def clearCanonicalNumber(atom: Atom) -> None: pass

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
# \param num 
#
def setCanonicalNumber(atom: Atom, num: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearMorganNumber(atom: Atom) -> None: pass

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
# \param num 
#
def setMorganNumber(atom: Atom, num: int) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param check_cip_sym 
# \param check_acyclic_subst_sym_only 
# \return 
#
def isStereoCenter(atom: Atom, molgraph: MolecularGraph, check_cip_sym: bool = True, check_acyclic_subst_sym_only: bool = False) -> bool: pass

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
# \param atom 
#
def clearStereoDescriptor(atom: Atom) -> None: pass

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
# \param descr 
#
def setStereoDescriptor(atom: Atom, descr: StereoDescriptor) -> None: pass

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
# \param bonds 
# \param excl_atom 
# \return 
#
def getIncidentBonds(atom: Atom, molgraph: MolecularGraph, bonds: list, excl_atom: Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clear2DCoordinates(atom: Atom) -> None: pass

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
def get2DCoordinates(atom: Atom) -> CDPL.Math.Vector2D: pass

##
# \brief 
# \param atom 
# \param coords 
#
def set2DCoordinates(atom: Atom, coords: CDPL.Math.Vector2D) -> None: pass

##
# \brief 
# \param atom 
# \param conf_idx 
# \return 
#
def getConformer3DCoordinates(atom: Atom, conf_idx: int) -> CDPL.Math.Vector3D: pass

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
# \param atom 
# \param molgraph 
# \param atom_mask 
# \param reset 
#
def markReachableAtoms(atom: Atom, molgraph: MolecularGraph, atom_mask: CDPL.Util.BitSet, reset: bool = True) -> None: pass

##
# \brief 
# \param atom 
#
def clearSymmetryClass(atom: Atom) -> None: pass

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
# \param class_id 
#
def setSymmetryClass(atom: Atom, class_id: int) -> None: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getNumContainingFragments(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \param cont_frag_list 
#
def getContainingFragments(atom: Atom, frag_list: FragmentList, cont_frag_list: FragmentList) -> None: pass

##
# \brief 
# \param atom 
#
def clearMatchConstraints(atom: Atom) -> None: pass

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
# \param constr 
#
def setMatchConstraints(atom: Atom, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param atom 
#
def clearReactionCenterStatus(atom: Atom) -> None: pass

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
# \param status 
#
def setReactionCenterStatus(atom: Atom, status: int) -> None: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getSizeOfLargestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param atom 
# \param frag_list 
# \return 
#
def getSizeOfSmallestContainingFragment(atom: Atom, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param max_dist 
# \param env 
# \param append 
#
def getEnvironment(atom: Atom, molgraph: MolecularGraph, max_dist: int, env: Fragment, append: bool = False) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcImplicitHydrogenCount(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearImplicitHydrogenCount(atom: Atom) -> None: pass

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
# \param count 
#
def setImplicitHydrogenCount(atom: Atom, count: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearUnpairedElectronCount(atom: Atom) -> None: pass

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
# \param count 
#
def setUnpairedElectronCount(atom: Atom, count: int) -> None: pass

##
# \brief 
# \param atom 
#
def clear3DCoordinatesArray(atom: Atom) -> None: pass

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
def get3DCoordinatesArray(atom: Atom) -> CDPL.Math.Vector3DArray: pass

##
# \brief 
# \param atom 
# \param coords_array 
#
def set3DCoordinatesArray(atom: Atom, coords_array: CDPL.Math.Vector3DArray) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcMDLParity(atom: Atom, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcStereoDescriptorFromMDLParity(atom: Atom, molgraph: MolecularGraph) -> StereoDescriptor: pass

##
# \brief 
# \param atom 
#
def clearMDLParity(atom: Atom) -> None: pass

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
# \param parity 
#
def setMDLParity(atom: Atom, parity: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearCIPPriority(atom: Atom) -> None: pass

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
# \param priority 
#
def setCIPPriority(atom: Atom, priority: int) -> None: pass
