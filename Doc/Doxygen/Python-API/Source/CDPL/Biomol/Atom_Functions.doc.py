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
#
def clearChainID(atom: Chem.Atom) -> None: pass

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
# \param id 
#
def setChainID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearAltLocationID(atom: Chem.Atom) -> None: pass

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
# \param id 
#
def setAltLocationID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearEntityID(atom: Chem.Atom) -> None: pass

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
# \param id 
#
def setEntityID(atom: Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueCode(atom: Chem.Atom) -> None: pass

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
# \param code 
#
def setResidueCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueInsertionCode(atom: Chem.Atom) -> None: pass

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
# \param code 
#
def setResidueInsertionCode(atom: Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueAtomName(atom: Chem.Atom) -> None: pass

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
# \param name 
#
def setResidueAtomName(atom: Chem.Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueAltAtomName(atom: Chem.Atom) -> None: pass

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
# \param name 
#
def setResidueAltAtomName(atom: Chem.Atom, name: str) -> None: pass

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
# \param atom1 
# \param atom2 
# \param flags 
# \return 
#
def areInSameResidue(atom1: Chem.Atom, atom2: Chem.Atom, flags: int = 2147483648) -> bool: pass

##
# \brief 
# \param atom 
#
def clearResidueLinkingAtomFlag(atom: Chem.Atom) -> None: pass

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
# \param linking 
#
def setResidueLinkingAtomFlag(atom: Chem.Atom, linking: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueLeavingAtomFlag(atom: Chem.Atom) -> None: pass

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
# \param leaving 
#
def setResidueLeavingAtomFlag(atom: Chem.Atom, leaving: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearHeteroAtomFlag(atom: Chem.Atom) -> None: pass

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
# \param is_het 
#
def setHeteroAtomFlag(atom: Chem.Atom, is_het: bool) -> None: pass

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
# \param atom 
#
def clearResidueSequenceNumber(atom: Chem.Atom) -> None: pass

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
# \param seq_no 
#
def setResidueSequenceNumber(atom: Chem.Atom, seq_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearSerialNumber(atom: Chem.Atom) -> None: pass

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
# \param serial_no 
#
def setSerialNumber(atom: Chem.Atom, serial_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearModelNumber(atom: Chem.Atom) -> None: pass

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
# \param model_no 
#
def setModelNumber(atom: Chem.Atom, model_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearBFactor(atom: Chem.Atom) -> None: pass

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
# \param factor 
#
def setBFactor(atom: Chem.Atom, factor: float) -> None: pass

##
# \brief 
# \param atom 
#
def clearOccupancy(atom: Chem.Atom) -> None: pass

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
# \param occupancy 
#
def setOccupancy(atom: Chem.Atom, occupancy: float) -> None: pass
