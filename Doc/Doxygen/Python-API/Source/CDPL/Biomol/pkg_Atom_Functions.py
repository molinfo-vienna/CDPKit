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
def clearChainID(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasChainID(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getChainID(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param id 
#
def setChainID(atom: CDPL.Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearAltLocationID(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasAltLocationID(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getAltLocationID(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param id 
#
def setAltLocationID(atom: CDPL.Chem.Atom, id: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueCode(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueCode(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueCode(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param code 
#
def setResidueCode(atom: CDPL.Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueInsertionCode(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueInsertionCode(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueInsertionCode(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param code 
#
def setResidueInsertionCode(atom: CDPL.Chem.Atom, code: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueAtomName(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueAtomName(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueAtomName(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param name 
#
def setResidueAtomName(atom: CDPL.Chem.Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueAltAtomName(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueAltAtomName(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueAltAtomName(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param name 
#
def setResidueAltAtomName(atom: CDPL.Chem.Atom, name: str) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param res_substruct 
# \param cnctd_only 
# \param flags 
# \param append 
#
def extractResidueSubstructure(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, res_substruct: CDPL.Chem.Fragment, cnctd_only: bool = False, flags: int = 2147483648, append: bool = False) -> None: pass

##
# \brief 
# \param atom1 
# \param atom2 
# \param flags 
# \return 
#
def areInSameResidue(atom1: CDPL.Chem.Atom, atom2: CDPL.Chem.Atom, flags: int = 2147483648) -> bool: pass

##
# \brief 
# \param atom 
#
def clearResidueLinkingAtomFlag(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueLinkingAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueLinkingAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param linking 
#
def setResidueLinkingAtomFlag(atom: CDPL.Chem.Atom, linking: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearResidueLeavingAtomFlag(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueLeavingAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueLeavingAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param leaving 
#
def setResidueLeavingAtomFlag(atom: CDPL.Chem.Atom, leaving: bool) -> None: pass

##
# \brief 
# \param atom 
#
def clearHeteroAtomFlag(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHeteroAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHeteroAtomFlag(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param is_het 
#
def setHeteroAtomFlag(atom: CDPL.Chem.Atom, is_het: bool) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def isPDBBackboneAtom(atom: CDPL.Chem.Atom) -> bool: pass

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
def matchesResidueInfo(atom: CDPL.Chem.Atom, res_code: str = '', chain_id: str = '', res_seq_no: int = -9223372036854775808, ins_code: str = '\x00', model_no: int = 0, atom_name: str = '', serial_no: int = -9223372036854775808) -> bool: pass

##
# \brief 
# \param atom 
#
def clearResidueSequenceNumber(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasResidueSequenceNumber(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getResidueSequenceNumber(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param seq_no 
#
def setResidueSequenceNumber(atom: CDPL.Chem.Atom, seq_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearSerialNumber(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSerialNumber(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSerialNumber(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param serial_no 
#
def setSerialNumber(atom: CDPL.Chem.Atom, serial_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearModelNumber(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasModelNumber(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getModelNumber(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param model_no 
#
def setModelNumber(atom: CDPL.Chem.Atom, model_no: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearBFactor(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasBFactor(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getBFactor(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param factor 
#
def setBFactor(atom: CDPL.Chem.Atom, factor: float) -> None: pass

##
# \brief 
# \param atom 
#
def clearOccupancy(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasOccupancy(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getOccupancy(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param occupancy 
#
def setOccupancy(atom: CDPL.Chem.Atom, occupancy: float) -> None: pass
