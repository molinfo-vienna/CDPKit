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
# \param bond 
# \param molgraph 
# \return 
#
def perceiveSybylType(bond: Bond, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param bond 
#
def clearSybylType(bond: Bond) -> None: pass

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
# \param type 
#
def setSybylType(bond: Bond, type: int) -> None: pass

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
# \param bond 
#
def clearRingFlag(bond: Bond) -> None: pass

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
# \param in_ring 
#
def setRingFlag(bond: Bond, in_ring: bool) -> None: pass

##
# \brief 
# \param bond 
#
def clear2DStereoFlag(bond: Bond) -> None: pass

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
# \param flag 
#
def set2DStereoFlag(bond: Bond, flag: int) -> None: pass

##
# \brief 
# \param bond 
#
def clearStereoCenterFlag(bond: Bond) -> None: pass

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
# \param is_center 
#
def setStereoCenterFlag(bond: Bond, is_center: bool) -> None: pass

##
# \brief 
# \param bond 
#
def clearAromaticityFlag(bond: Bond) -> None: pass

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
# \param aromatic 
#
def setAromaticityFlag(bond: Bond, aromatic: bool) -> None: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def buildMatchExpressionString(bond: Bond, molgraph: MolecularGraph) -> str: pass

##
# \brief 
# \param bond 
#
def clearMatchExpressionString(bond: Bond) -> None: pass

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
# \param expr_str 
#
def setMatchExpressionString(bond: Bond, expr_str: str) -> None: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def buildMatchExpression(bond: Bond, molgraph: MolecularGraph) -> BondMatchExpression: pass

##
# \brief 
# \param bond 
#
def clearMatchExpression(bond: Bond) -> None: pass

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
# \param expr 
#
def setMatchExpression(bond: Bond, expr: BondMatchExpression) -> None: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def calcCIPConfiguration(bond: Bond, molgraph: MolecularGraph) -> int: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param cip_pri_func 
# \return 
#
def calcCIPConfiguration(bond: Bond, molgraph: MolecularGraph, cip_pri_func: SizeTypeAtomFunctor) -> int: pass

##
# \brief 
# \param bond 
#
def clearCIPConfiguration(bond: Bond) -> None: pass

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
# \param config 
#
def setCIPConfiguration(bond: Bond, config: int) -> None: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param descr 
# \param coords 
# \return 
#
def calcBondConfiguration(bond: Bond, molgraph: MolecularGraph, descr: StereoDescriptor, coords: CDPL.Math.Vector3DArray) -> int: pass

##
# \brief 
# \param bond 
#
def clearDirection(bond: Bond) -> None: pass

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
# \param dir 
#
def setDirection(bond: Bond, dir: int) -> None: pass

##
# \brief 
# \param bond 
#
def clearOrder(bond: Bond) -> None: pass

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
# \param order 
#
def setOrder(bond: Bond, order: int) -> None: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param check_cip_sym 
# \param min_ring_size 
# \return 
#
def isStereoCenter(bond: Bond, molgraph: MolecularGraph, check_cip_sym: bool = True, min_ring_size: int = 8) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param dim 
# \param min_ring_size 
# \param check_order 
# \return 
#
def calcStereoDescriptor(bond: Bond, molgraph: MolecularGraph, dim: int = 1, min_ring_size: int = 8, check_order: bool = True) -> StereoDescriptor: pass

##
# \brief 
# \param bond 
#
def clearStereoDescriptor(bond: Bond) -> None: pass

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
# \param descr 
#
def setStereoDescriptor(bond: Bond, descr: StereoDescriptor) -> None: pass

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
# \param frag_list 
# \param cont_frag_list 
#
def getContainingFragments(bond: Bond, frag_list: FragmentList, cont_frag_list: FragmentList) -> None: pass

##
# \brief 
# \param bond 
#
def clearMatchConstraints(bond: Bond) -> None: pass

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
# \param constr 
#
def setMatchConstraints(bond: Bond, constr: MatchConstraintList) -> None: pass

##
# \brief 
# \param bond 
#
def clearReactionCenterStatus(bond: Bond) -> None: pass

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
# \param status 
#
def setReactionCenterStatus(bond: Bond, status: int) -> None: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \return 
#
def getSizeOfLargestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass

##
# \brief 
# \param bond 
# \param frag_list 
# \return 
#
def getSizeOfSmallestContainingFragment(bond: Bond, frag_list: FragmentList) -> int: pass
