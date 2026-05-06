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
# \return 
#
def getAllredRochowElectronegativity(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAromaticAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getAromaticBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAromaticBondCount(cntnr: Chem.BondContainer) -> int: pass

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
# \param molgraph 
# \return 
#
def getAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param type 
# \param strict 
# \return 
#
def getAtomCount(molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \return 
#
def getAtomicWeight(atom: Chem.Atom) -> float: pass

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
# \param molgraph 
# \return 
#
def getBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \param order 
# \param inc_aro 
# \return 
#
def getBondCount(molgraph: Chem.MolecularGraph, order: int, inc_aro: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getChainAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getChainBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getComponentCount(molgraph: Chem.MolecularGraph) -> int: pass

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
# \return 
#
def getElementName(atom: Chem.Atom) -> str: pass

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
# \param type 
# \param strict 
# \return 
#
def getExplicitAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param type 
# \param strict 
# \return 
#
def getExplicitAtomCount(cntnr: Chem.AtomContainer, type: int, strict: bool = True) -> int: pass

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
# \param cntnr 
# \return 
#
def getExplicitBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param order 
# \param inc_aro 
# \return 
#
def getExplicitBondCount(cntnr: Chem.BondContainer, order: int, inc_aro: bool = True) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitChainAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getExplicitChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitChainBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitHydrogenBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief 
# \param molgraph 
# \param flags 
# \return 
#
def getExplicitOrdinaryHydrogenCount(molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief 
# \param molgraph 
# \param fg_list 
#
def setFunctionalGroups(molgraph: Chem.MolecularGraph, fg_list: Chem.FragmentList) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasFunctionalGroups(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getFunctionalGroups(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearFunctionalGroups(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getHBondAcceptorAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondAcceptorType(atom: Chem.Atom, type: int) -> None: pass

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
#
def clearHBondAcceptorType(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getHBondDonorAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setHBondDonorType(atom: Chem.Atom, type: int) -> None: pass

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
#
def clearHBondDonorType(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getHeavyAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHeavyBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getHeavyBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getHybridPolarizability(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getHydrogenBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
# \param hyd 
#
def setHydrophobicity(atom: Chem.Atom, hyd: float) -> None: pass

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
#
def clearHydrophobicity(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def getIUPACGroup(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getImplicitHydrogenCount(molgraph: Chem.MolecularGraph) -> int: pass

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
#
def clearMHMOPiCharge(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param bond 
# \param order 
#
def setMHMOPiOrder(bond: Chem.Bond, order: float) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasMHMOPiOrder(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def getMHMOPiOrder(bond: Chem.Bond) -> float: pass

##
# \brief 
# \param bond 
#
def clearMHMOPiOrder(bond: Chem.Bond) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getNetFormalCharge(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getNumContainingSSSRRings(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def getNumContainingSSSRRings(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> int: pass

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
# \param molgraph 
# \param flags 
# \return 
#
def getOrdinaryHydrogenCount(molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setPEOESigmaCharge(atom: Chem.Atom, charge: float) -> None: pass

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
#
def clearPEOESigmaCharge(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \param e_neg 
#
def setPEOESigmaElectronegativity(atom: Chem.Atom, e_neg: float) -> None: pass

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
#
def clearPEOESigmaElectronegativity(atom: Chem.Atom) -> None: pass

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
def getRingAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getRingAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def getRingBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getRingBondCount(cntnr: Chem.BondContainer) -> int: pass

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
# \param molgraph 
# \param h_rotors 
# \param ring_bonds 
# \param amide_bonds 
# \return 
#
def getRotatableBondCount(molgraph: Chem.MolecularGraph, h_rotors: bool = False, ring_bonds: bool = False, amide_bonds: bool = False) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getRuleOfFiveScore(molgraph: Chem.MolecularGraph) -> int: pass

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
# \return 
#
def getVdWRadius(atom: Chem.Atom) -> float: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param from_logp 
#
def calcAtomHydrophobicities(molgraph: Chem.MolecularGraph, overwrite: bool, from_logp: bool = False) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcCyclomaticNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param cntnr 
# \param moment 
# \return 
#
def calcDipoleMoment(cntnr: Chem.AtomContainer, moment: Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param moment 
# \return 
#
def calcDipoleMoment(cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, moment: Math.Vector3D) -> bool: pass

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
# \param cntnr 
# \return 
#
def calcExplicitMass(cntnr: Chem.AtomContainer) -> float: pass

##
# \brief 
# \param cntnr 
# \param mass_comp 
#
def calcExplicitMassComposition(cntnr: Chem.AtomContainer, mass_comp: MassComposition) -> None: pass

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
# \param molgraph 
# \return 
#
def calcFreeValenceElectronCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

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
# \param molgraph 
# \return 
#
def calcLogS(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcLonePairElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def calcMHMOProperties(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param comp 
#
def calcMassComposition(molgraph: Chem.MolecularGraph, comp: MassComposition) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcMass(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcMeanPolarizability(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \param num_iter 
# \param damping 
#
def calcPEOEProperties(molgraph: Chem.MolecularGraph, overwrite: bool, num_iter: int = 20, damping: float = 0.48) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcPiElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param damping 
# \return 
#
def calcPolarizability(bond: Chem.Bond, molgraph: Chem.MolecularGraph, damping: float = 0.75) -> float: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def calcStericNumber(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcTPSA(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param atom 
# \return 
#
def calcTotalPartialCharge(atom: Chem.Atom) -> float: pass

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
# \return 
#
def calcValenceElectronCount(atom: Chem.Atom) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcXLogP(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \param hist 
# \param append 
#
def generateElementHistogram(molgraph: Chem.MolecularGraph, hist: ElementHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param hist 
# \param append 
#
def generateExplicitElementHistogram(cntnr: Chem.AtomContainer, hist: ElementHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def generateExplicitMassCompositionString(cntnr: Chem.AtomContainer) -> str: pass

##
# \brief 
# \param cntnr 
# \return 
#
def generateExplicitMolecularFormula(cntnr: Chem.AtomContainer) -> str: pass

##
# \brief 
# \param molgraph 
# \return 
#
def generateMassCompositionString(molgraph: Chem.MolecularGraph) -> object: pass

##
# \brief 
# \param molgraph 
# \param sep 
# \return 
#
def generateMolecularFormula(molgraph: Chem.MolecularGraph, sep: str = '') -> object: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideBond(bond: Chem.Bond, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideCenter(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

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
# \param bridged_only 
# \return 
#
def isBridgehead(atom: Chem.Atom, molgraph: Chem.MolecularGraph, bridged_only: bool) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isCarbonylLike(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isChemicalElement(atom: Chem.Atom) -> bool: pass

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
# \param molgraph 
# \return 
#
def isHBondDonor(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isHalogen(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isHeavy(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def isHeteroAtomHydrogenRotor(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param bond 
# \return 
#
def isHydrogenBond(bond: Chem.Bond) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def isHydrogenRotor(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isInRing(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def isInRing(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

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
# \param bond 
# \param molgraph 
# \param size 
# \return 
#
def isInRingOfSize(bond: Chem.Bond, molgraph: Chem.MolecularGraph, size: int) -> bool: pass

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
# \return 
#
def isMainGroupElement(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNobleGas(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isNonMetal(atom: Chem.Atom) -> bool: pass

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
# \return 
#
def isPlanarNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param h_rotors 
# \param ring_bonds 
# \param amide_bonds 
# \return 
#
def isRotatable(bond: Chem.Bond, molgraph: Chem.MolecularGraph, h_rotors: bool, ring_bonds: bool, amide_bonds: bool) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isSemiMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isSpiroCenter(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def isTransitionMetal(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def isUnsaturated(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveFunctionalGroups(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveFunctionalGroups(molgraph: Chem.MolecularGraph, overwrite: bool) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveHBondAcceptorAtomTypes(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def perceiveHBondDonorAtomTypes(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass
