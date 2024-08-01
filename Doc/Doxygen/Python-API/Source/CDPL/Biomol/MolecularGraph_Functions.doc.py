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
# \param molgraph 
#
def clearChainID(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param id 
#
def setChainID(molgraph: Chem.MolecularGraph, id: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearPDBData(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param data 
#
def setPDBData(molgraph: Chem.MolecularGraph, data: PDBData) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearMMCIFData(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param data 
#
def setMMCIFData(molgraph: Chem.MolecularGraph, data: MMCIFData) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearResidueCode(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param code 
#
def setResidueCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearResidueInsertionCode(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param code 
#
def setResidueInsertionCode(molgraph: Chem.MolecularGraph, code: str) -> None: pass

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
# \param molgraph 
#
def clearResidueSequenceNumber(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param seq_no 
#
def setResidueSequenceNumber(molgraph: Chem.MolecularGraph, seq_no: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearModelNumber(molgraph: Chem.MolecularGraph) -> None: pass

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
# \param model_no 
#
def setModelNumber(molgraph: Chem.MolecularGraph, model_no: int) -> None: pass

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
