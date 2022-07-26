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
def clearChainID(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasChainID(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getChainID(molgraph: CDPL.Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
# \param id 
#
def setChainID(molgraph: CDPL.Chem.MolecularGraph, id: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearPDBData(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasPDBData(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getPDBData(molgraph: CDPL.Chem.MolecularGraph) -> PDBData: pass

##
# \brief 
# \param molgraph 
# \param data 
#
def setPDBData(molgraph: CDPL.Chem.MolecularGraph, data: PDBData) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearResidueCode(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueCode(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueCode(molgraph: CDPL.Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
# \param code 
#
def setResidueCode(molgraph: CDPL.Chem.MolecularGraph, code: str) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearResidueInsertionCode(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueInsertionCode(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueInsertionCode(molgraph: CDPL.Chem.MolecularGraph) -> str: pass

##
# \brief 
# \param molgraph 
# \param code 
#
def setResidueInsertionCode(molgraph: CDPL.Chem.MolecularGraph, code: str) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param flags 
#
def setHydrogenResidueSequenceInfo(molgraph: CDPL.Chem.MolecularGraph, overwrite: bool, flags: int = 2147483648) -> None: pass

##
# \brief 
# \param molgraph 
# \param override 
#
def convertMOL2ToPDBResidueInfo(molgraph: CDPL.Chem.MolecularGraph, override: bool) -> None: pass

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
def matchesResidueInfo(molgraph: CDPL.Chem.MolecularGraph, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0) -> bool: pass

##
# \brief 
# \param molgraph 
#
def clearResidueSequenceNumber(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasResidueSequenceNumber(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getResidueSequenceNumber(molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param seq_no 
#
def setResidueSequenceNumber(molgraph: CDPL.Chem.MolecularGraph, seq_no: int) -> None: pass

##
# \brief 
# \param molgraph 
#
def clearModelNumber(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasModelNumber(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getModelNumber(molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param model_no 
#
def setModelNumber(molgraph: CDPL.Chem.MolecularGraph, model_no: int) -> None: pass

##
# \brief 
# \param molgraph 
# \param parent_molgraph 
# \param res_substructs 
# \param cnctd_only 
# \param flags 
# \param append 
#
def extractResidueSubstructures(molgraph: CDPL.Chem.MolecularGraph, parent_molgraph: CDPL.Chem.MolecularGraph, res_substructs: CDPL.Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_residues 
# \param max_dist 
# \param append 
#
def extractEnvironmentResidues(core: CDPL.Chem.MolecularGraph, macromol: CDPL.Chem.MolecularGraph, env_residues: CDPL.Chem.Fragment, max_dist: float, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_residues 
# \param coords_func 
# \param max_dist 
# \param append 
#
def extractEnvironmentResidues(core: CDPL.Chem.MolecularGraph, macromol: CDPL.Chem.MolecularGraph, env_residues: CDPL.Chem.Fragment, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, max_dist: float, append: bool = False) -> None: pass

##
# \brief 
# \param core 
# \param macromol 
# \param env_atoms 
# \param max_dist 
# \param inc_core_atoms 
# \param append 
#
def extractProximalAtoms(core: CDPL.Chem.MolecularGraph, macromol: CDPL.Chem.MolecularGraph, env_atoms: CDPL.Chem.Fragment, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass

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
def extractProximalAtoms(core: CDPL.Chem.MolecularGraph, macromol: CDPL.Chem.MolecularGraph, env_atoms: CDPL.Chem.Fragment, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, max_dist: float, inc_core_atoms: bool = False, append: bool = False) -> None: pass
