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
# \param id 
#
def setAltLocationID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasAltLocationID(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getAltLocationID(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearAltLocationID(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param factor 
#
def setBFactor(atom: Chem.Atom, factor: float) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasBFactor(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getBFactor(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
#
def clearBFactor(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param id 
#
def setChainID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasChainID(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getChainID(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearChainID(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param id 
#
def setChainID(molgraph: Chem.MolecularGraph, id: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasChainID(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getChainID(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearChainID(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param id 
#
def setEntityID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasEntityID(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getEntityID(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearEntityID(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param is_het 
#
def setHeteroAtomFlag(atom: Chem.Atom, is_het: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHeteroAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHeteroAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearHeteroAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param flags 
#
def setHydrogenResidueSequenceInfo(molgraph: Chem.MolecularGraph, overwrite: bool, flags: int = 2147483648) -> None: pass

##
# \brief 
# \param molgraph 
# \param data 
#
def setMMCIFData(molgraph: Chem.MolecularGraph, data: MMCIFData) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMMCIFData(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMMCIFData(molgraph: Chem.MolecularGraph) -> MMCIFData: pass

##
# \brief 
# \param molgraph 
#
def clearMMCIFData(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param model_no 
#
def setModelNumber(atom: Chem.Atom, model_no: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasModelNumber(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getModelNumber(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearModelNumber(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param model_no 
#
def setModelNumber(molgraph: Chem.MolecularGraph, model_no: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasModelNumber(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getModelNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearModelNumber(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param occupancy 
#
def setOccupancy(atom: Chem.Atom, occupancy: float) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasOccupancy(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getOccupancy(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
#
def clearOccupancy(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param data 
#
def setPDBData(molgraph: Chem.MolecularGraph, data: PDBData) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasPDBData(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getPDBData(molgraph: Chem.MolecularGraph) -> PDBData: pass

##
# \brief 
# \param molgraph 
#
def clearPDBData(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setResidueAltAtomName(atom: Chem.Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueAltAtomName(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueAltAtomName(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearResidueAltAtomName(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param name 
#
def setResidueAtomName(atom: Chem.Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueAtomName(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueAtomName(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearResidueAtomName(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param code 
#
def setResidueCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueCode(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueCode(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearResidueCode(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param code 
#
def setResidueCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueCode(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueCode(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearResidueCode(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param code 
#
def setResidueInsertionCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueInsertionCode(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueInsertionCode(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearResidueInsertionCode(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param code 
#
def setResidueInsertionCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueInsertionCode(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueInsertionCode(molgraph: Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
#
def clearResidueInsertionCode(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param leaving 
#
def setResidueLeavingAtomFlag(atom: Chem.Atom, leaving: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueLeavingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueLeavingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearResidueLeavingAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param linking 
#
def setResidueLinkingAtomFlag(atom: Chem.Atom, linking: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueLinkingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueLinkingAtomFlag(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
#
def clearResidueLinkingAtomFlag(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param seq_no 
#
def setResidueSequenceNumber(atom: Chem.Atom, seq_no: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueSequenceNumber(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueSequenceNumber(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearResidueSequenceNumber(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \param seq_no 
#
def setResidueSequenceNumber(molgraph: Chem.MolecularGraph, seq_no: int) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
#
def clearResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param atom 
# \param serial_no 
#
def setSerialNumber(atom: Chem.Atom, serial_no: int) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSerialNumber(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSerialNumber(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
#
def clearSerialNumber(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom1 
# \param atom2 
# \param flags 
# \return 
#
def areInSameResidue(atom1: Chem.Atom, atom2: Chem.Atom, flags: int = 2147483648) -> bool: pass

##
# \brief Merges alternative residue conformers in <em>mol</em> whose residue centers lie within <em>max_ctr_dist</em> of one another.
# 
# Many PDB and mmCIF structures encode alternative conformations of a residue as multiple residues with distinct alternate-location identifiers but mostly overlapping atom positions. This function detects such interfering residue copies (residues whose geometric centers are closer than <em>max_ctr_dist</em>) and combines them into a single residue with all observed atom positions, leaving the molecule's topology and residue ordering otherwise unchanged.
# 
# \param mol The molecule whose interfering residues are to be combined.
# \param max_ctr_dist The maximum distance between residue centers that still qualifies them as interfering copies of one another.
# 
# \return <tt>True</tt> if at least one residue group was combined, and <tt>False</tt> if no interfering residues were found.
# 
def combineInterferingResidueCoordinates(mol: Chem.Molecule, max_ctr_dist: float = 1.0) -> bool: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_residues 
# \param max_dist 
# \param append 
#
def extractEnvironmentResidues(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_residues: Chem.Fragment, max_dist: float, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_residues 
# \param coords_func 
# \param max_dist 
# \param append 
#
def extractEnvironmentResidues(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_residues: Chem.Fragment, coords_func: Chem.Atom3DCoordinatesFunction, max_dist: float, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_atoms 
# \param max_dist 
# \param inc_core_atoms 
# \param append 
#
def extractProximalAtoms(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_atoms: Chem.Fragment, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_atoms 
# \param coords_func 
# \param max_dist 
# \param inc_core_atoms 
# \param append 
#
def extractProximalAtoms(core: Chem.MolecularGraph, macromol: Chem.MolecularGraph, env_atoms: Chem.Fragment, coords_func: Chem.Atom3DCoordinatesFunction, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param res_substruct 
# \param cnctd_only 
# \param flags 
# \param append 
#
def extractResidueSubstructure(atom: Chem.Atom, molgraph: Chem.MolecularGraph, res_substruct: Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \param parent_molgraph 
# \param res_substructs 
# \param cnctd_only 
# \param flags 
# \param append 
#
def extractResidueSubstructures(molgraph: Chem.MolecularGraph, parent_molgraph: Chem.MolecularGraph, res_substructs: Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param idx 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \param atom_name 
# \param serial_no 
# \return 
#
def findResidueAtom(cntnr: object, idx: int, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> int: pass

##
# \brief 
# \param cntnr 
# \param idx 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \param atom_name 
# \param serial_no 
# \return 
#
def findResidue(cntnr: object, idx: int, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def isPDBBackboneAtom(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \param atom_name 
# \param serial_no 
# \return 
#
def matchesResidueInfo(atom: Chem.Atom, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> bool: pass

##
# \brief 
# \param molgraph 
# \param res_code 
# \param chain_id 
# \param res_seq_no 
# \param ins_code 
# \param model_no 
# \return 
#
def matchesResidueInfo(molgraph: Chem.MolecularGraph, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0) -> bool: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearApplyDictAtomTypesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearApplyDictFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param calc 
#
def setCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer, calc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCalcMissingFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

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
# \param comb 
#
def setCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer, comb: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCombineInterferingResidueCoordinatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMMCIFApplyDictAtomBondingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMMCIFApplyDictBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearMMCIFOutputBiopolymersAsChemCompParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param func 
#
def setMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer, func: MMCIFDataProcessingFunction) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> MMCIFDataProcessingFunction: pass

##
# \brief 
# \param cntnr 
#
def clearMMCIFOutputDataPostprocFunctionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBApplyDictAtomBondingToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBApplyDictAtomBondingToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBApplyDictBondOrdersToNonStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param apply 
#
def setPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer, apply: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBApplyDictBondOrdersToStdResiduesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param deduce 
#
def setPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, deduce: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBDeduceBondOrdersFromCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param evaluate 
#
def setPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer, evaluate: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBEvaluateMASTERRecordParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param ver 
#
def setPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer, ver: int) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearPDBFormatVersionParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param ignore 
#
def setPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBIgnoreCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param ignore 
#
def setPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer, ignore: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBIgnoreFormalChargeFieldParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBOutputCONECTRecordsForAllBondsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBOutputCONECTRecordsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBOutputCONECTRecordsReflectingBondOrderParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param output 
#
def setPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer, output: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBOutputFormalChargesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param trunc 
#
def setPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer, trunc: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPDBTruncateLinesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param perceive 
#
def setPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer, perceive: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearPerceiveMissingBondOrdersParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param dict 
#
def setResidueDictionaryParameter(cntnr: Base.ControlParameterContainer, dict: ResidueDictionary) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> ResidueDictionary: pass

##
# \brief 
# \param cntnr 
#
def clearResidueDictionaryParameter(cntnr: Base.ControlParameterContainer) -> None: pass

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
