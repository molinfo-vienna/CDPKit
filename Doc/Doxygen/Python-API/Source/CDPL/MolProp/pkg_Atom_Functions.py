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
def isUnsaturated(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPeriod(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcValence(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcExplicitValence(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearPEOESigmaCharge(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasPEOESigmaCharge(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPEOESigmaCharge(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setPEOESigmaCharge(atom: CDPL.Chem.Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
#
def clearMHMOPiCharge(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMHMOPiCharge(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMHMOPiCharge(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setMHMOPiCharge(atom: CDPL.Chem.Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def calcTotalPartialCharge(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getElementName(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
#
def clearHBondDonorType(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHBondDonorType(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHBondDonorType(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondDonorType(atom: CDPL.Chem.Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearHBondAcceptorType(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHBondAcceptorType(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHBondAcceptorType(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondAcceptorType(atom: CDPL.Chem.Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param size 
# \return 
#
def isInRingOfSize(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, size: int) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isInRing(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isSemiMetal(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNonMetal(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isTransitionMetal(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isMetal(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isCarbonylLikeAtom(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideCenterAtom(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isHalogen(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param flags 
# \return 
#
def isOrdinaryHydrogen(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, flags: int = 2147483648) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideNitrogen(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isInvertibleNitrogen(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isPlanarNitrogen(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getIUPACGroup(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcStericNumber(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isHBondDonor(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isHBondAcceptor(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNobleGas(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getNumContainingSSSRRings(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def getVdWRadius(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param order 
# \return 
#
def getCovalentRadius(atom: CDPL.Chem.Atom, order: int = 1) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param num_bonds 
# \return 
#
def calcInductiveEffect(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, num_bonds: int = 10) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getAtomicWeight(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def isChemicalElement(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isMainGroupElement(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param h_rotors 
# \param ring_bonds 
# \param amide_bonds 
# \return 
#
def getRotatableBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, h_rotors: bool = False, ring_bonds: bool = False, amide_bonds: bool = False) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getRingBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \return 
#
def getBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, order: int) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \param type 
# \param strict 
# \return 
#
def getBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \return 
#
def getExplicitBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, order: int) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param order 
# \param type 
# \param strict 
# \return 
#
def getExplicitBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyBondCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getRingAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param type 
# \param strict 
# \return 
#
def getAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param type 
# \param strict 
# \return 
#
def getExplicitAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyAtomCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param flags 
# \return 
#
def getOrdinaryHydrogenCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def calcValenceElectronCount(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcFreeValenceElectronCount(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def getElementValenceElectronCount(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getVSEPRCoordinationGeometry(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param steric_num 
# \return 
#
def getVSEPRCoordinationGeometry(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, steric_num: int) -> int: pass

##
# \brief 
# \param atom 
#
def clearHydrophobicity(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasHydrophobicity(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getHydrophobicity(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param hyd 
#
def setHydrophobicity(atom: CDPL.Chem.Atom, hyd: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHybridPolarizability(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param damping 
# \return 
#
def calcEffectivePolarizability(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph, damping: float = 0.75) -> float: pass

##
# \brief 
# \param atom 
#
def clearPEOESigmaElectronegativity(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasPEOESigmaElectronegativity(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getPEOESigmaElectronegativity(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param e_neg 
#
def setPEOESigmaElectronegativity(atom: CDPL.Chem.Atom, e_neg: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcPiElectronegativity(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcLonePairElectronegativity(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def getAllredRochowElectronegativity(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def isHeavy(atom: CDPL.Chem.Atom) -> bool: pass
