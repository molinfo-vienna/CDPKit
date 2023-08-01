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
# \param molgraph 
# \return 
#
def isUnsaturated(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPeriod(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcValence(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcExplicitValence(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearPEOESigmaCharge(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasPEOESigmaCharge(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPEOESigmaCharge(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setPEOESigmaCharge(atom: Chem.Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
#
def clearMHMOPiCharge(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMHMOPiCharge(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMHMOPiCharge(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setMHMOPiCharge(atom: Chem.Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def calcTotalPartialCharge(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getElementName(atom: Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearHBondDonorType(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHBondDonorType(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHBondDonorType(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondDonorType(atom: Chem.Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearHBondAcceptorType(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHBondAcceptorType(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHBondAcceptorType(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondAcceptorType(atom: Chem.Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param size 
# \return 
#
def isInRingOfSize(atom: Chem.Atom, molgraph: Chem.MolecularGraph, size: int) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isInRing(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isSemiMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNonMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isTransitionMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isCarbonylLikeAtom(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideCenterAtom(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isHalogen(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param flags 
# \return 
#
def isOrdinaryHydrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isInvertibleNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isPlanarNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getIUPACGroup(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcStericNumber(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isHBondDonor(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isHBondAcceptor(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNobleGas(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getNumContainingSSSRRings(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def getVdWRadius(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param order 
# \return 
#
def getCovalentRadius(atom: Chem.Atom, order: int = 1) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param num_bonds 
# \return 
#
def calcInductiveEffect(atom: Chem.Atom, molgraph: Chem.MolecularGraph, num_bonds: int = 10) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getAtomicWeight(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def isChemicalElement(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isMainGroupElement(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param h_rotors 
# \param ring_bonds 
# \param amide_bonds 
# \return 
#
def getRotatableBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, h_rotors: bool = False, ring_bonds: bool = False, amide_bonds: bool = False) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getRingBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \return 
#
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \param type 
# \param strict 
# \return 
#
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \return 
#
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \param type 
# \param strict 
# \return 
#
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getRingAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param type 
# \param strict 
# \return 
#
def getAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param type 
# \param strict 
# \return 
#
def getExplicitAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param flags 
# \return 
#
def getOrdinaryHydrogenCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def calcValenceElectronCount(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcFreeValenceElectronCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def getElementValenceElectronCount(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getVSEPRCoordinationGeometry(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param steric_num 
# \return 
#
def getVSEPRCoordinationGeometry(atom: Chem.Atom, molgraph: Chem.MolecularGraph, steric_num: int) -> int: pass

##
# \brief 
# \param atom 
#
def clearHydrophobicity(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHydrophobicity(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHydrophobicity(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param hyd 
#
def setHydrophobicity(atom: Chem.Atom, hyd: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHybridPolarizability(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param damping 
# \return 
#
def calcEffectivePolarizability(atom: Chem.Atom, molgraph: Chem.MolecularGraph, damping: float = 0.75) -> float: pass

##
# \brief 
# \param atom 
#
def clearPEOESigmaElectronegativity(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasPEOESigmaElectronegativity(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPEOESigmaElectronegativity(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param e_neg 
#
def setPEOESigmaElectronegativity(atom: Chem.Atom, e_neg: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcPiElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcLonePairElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getAllredRochowElectronegativity(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def isHeavy(atom: Chem.Atom) -> bool: pass
