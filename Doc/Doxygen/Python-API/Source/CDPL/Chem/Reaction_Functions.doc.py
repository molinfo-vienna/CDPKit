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
# \param rxn 
# \return 
#
def getMaxAtomMappingID(rxn: Reaction) -> int: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMaxComponentGroupID(rxn: Reaction) -> int: pass

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
# \param rxn 
#
def clearReactionData(rxn: Reaction) -> None: pass

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
# \param data 
#
def setReactionData(rxn: Reaction, data: StringDataBlock) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLMoleculeRecord(rxn: Reaction) -> None: pass

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
# \param mol_rec 
#
def setMDLMoleculeRecord(rxn: Reaction, mol_rec: Molecule) -> None: pass

##
# \brief 
# \param rxn 
# \param role_mask 
# \param atom_flags 
# \param bond_flags 
# \param global_stereo 
# \param ord_h_deplete 
# \return 
#
def calcHashCode(rxn: Reaction, role_mask: int = 7, atom_flags: int = 2147483648, bond_flags: int = 2147483648, global_stereo: bool = True, ord_h_deplete: bool = True) -> int: pass

##
# \brief 
# \param rxn 
#
def clearMDLProgramName(rxn: Reaction) -> None: pass

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
# \param name 
#
def setMDLProgramName(rxn: Reaction, name: str) -> None: pass

##
# \brief 
# \param rxn 
#
def clearName(rxn: Reaction) -> None: pass

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
# \param name 
#
def setName(rxn: Reaction, name: str) -> None: pass

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
# \param rxn 
#
def clearAtomMapping(rxn: Reaction) -> None: pass

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
# \param mapping 
#
def setAtomMapping(rxn: Reaction, mapping: AtomMapping) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLRXNFileVersion(rxn: Reaction) -> None: pass

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
# \param version 
#
def setMDLRXNFileVersion(rxn: Reaction, version: int) -> None: pass

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
# \param rxn 
#
def clearMatchExpression(rxn: Reaction) -> None: pass

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
# \param expr 
#
def setMatchExpression(rxn: Reaction, expr: ReactionMatchExpression) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLTimestamp(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLTimestamp(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLTimestamp(rxn: Reaction) -> int: pass

##
# \brief 
# \param rxn 
# \param time 
#
def setMDLTimestamp(rxn: Reaction, time: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLRegistryNumber(rxn: Reaction) -> None: pass

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
# \param reg_no 
#
def setMDLRegistryNumber(rxn: Reaction, reg_no: int) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLInternalRegistryNumber(rxn: Reaction) -> None: pass

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
# \param reg_no 
#
def setMDLInternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLExternalRegistryNumber(rxn: Reaction) -> None: pass

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
# \param reg_no 
#
def setMDLExternalRegistryNumber(rxn: Reaction, reg_no: str) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def calcBasicProperties(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLUserInitials(rxn: Reaction) -> None: pass

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
# \param initials 
#
def setMDLUserInitials(rxn: Reaction, initials: str) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def generateMatchExpressions(rxn: Reaction, overwrite: bool) -> None: pass

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
# \param rxn 
#
def clearComponentGroups(rxn: Reaction) -> None: pass

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
# \param comp_groups 
#
def setComponentGroups(rxn: Reaction, comp_groups: FragmentList) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setBondMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setAtomMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMatchConstraints(rxn: Reaction) -> None: pass

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
# \param constr 
#
def setMatchConstraints(rxn: Reaction, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param rxn 
# \param constr 
# \param overwrite 
#
def setComponentMatchConstraints(rxn: Reaction, constr: MatchConstraintList, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def initSubstructureSearchTarget(rxn: Reaction, overwrite: bool) -> None: pass

##
# \brief 
# \param rxn 
#
def clearMDLComment(rxn: Reaction) -> None: pass

##
# \brief 
# \param rxn 
# \return 
#
def hasMDLComment(rxn: Reaction) -> bool: pass

##
# \brief 
# \param rxn 
# \return 
#
def getMDLComment(rxn: Reaction) -> str: pass

##
# \brief 
# \param rxn 
# \param comment 
#
def setMDLComment(rxn: Reaction, comment: str) -> None: pass

##
# \brief 
# \param rxn 
# \param overwrite 
#
def initSubstructureSearchQuery(rxn: Reaction, overwrite: bool) -> None: pass
