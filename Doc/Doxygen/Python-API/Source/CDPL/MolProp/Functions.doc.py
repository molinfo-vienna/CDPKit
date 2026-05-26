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
# \brief Returns the Allred-Rochow electronegativity of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The Allred-Rochow electronegativity.
# 
def getAllredRochowElectronegativity(atom: Chem.Atom) -> float: pass

##
# \brief Returns the number of aromatic neighbors of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The aromatic neighbor count.
# 
def getAromaticAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of aromatic atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The number of aromatic atoms.
# 
def getAromaticAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of aromatic bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The aromatic-bond count.
# 
def getAromaticBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of aromatic bonds in <em>cntnr</em>.
# 
# \param cntnr The bond container.
# 
# \return The number of aromatic bonds.
# 
def getAromaticBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the number of neighbors of <em>atom</em> in <em>molgraph</em> (including implicit hydrogens) whose Chem.AtomType matches <em>type</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param type The Chem.AtomType to count.
# \param strict If <tt>True</tt>, the atom type must match <em>type</em> exactly; otherwise generic types match via Chem.atomTypesMatch().
# 
# \return The matching neighbor count.
# 
def getAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the total number of atoms in <em>molgraph</em> (including implicit hydrogens).
# 
# \param molgraph The molecular graph.
# 
# \return The total atom count.
# 
def getAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of atoms in <em>molgraph</em> whose Chem.AtomType matches <em>type</em>.
# 
# \param molgraph The molecular graph.
# \param type The Chem.AtomType to count.
# \param strict If <tt>True</tt>, the atom type must match <em>type</em> exactly; otherwise generic types match via Chem.atomTypesMatch().
# 
# \return The number of matching atoms (including implicit hydrogens when <em>type</em> matches Chem.AtomType.H). 
# 
# \since 1.1
# 
def getAtomCount(molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the standard atomic weight of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The standard atomic weight.
# 
def getAtomicWeight(atom: Chem.Atom) -> float: pass

##
# \brief Returns the total number of bonds incident to <em>atom</em> in <em>molgraph</em> (including implicit-hydrogen bonds).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The total bond count.
# 
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the total number of bonds of the given order incident to <em>atom</em> (including implicit-hydrogen bonds).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param order The bond order to count.
# 
# \return The number of matching bonds.
# 
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int) -> int: pass

##
# \brief Returns the total number of bonds of the given order incident to <em>atom</em> that bond to atoms whose Chem.AtomType matches <em>type</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param order The bond order to count.
# \param type The Chem.AtomType of the bonded partner.
# \param strict If <tt>True</tt>, the atom type must match <em>type</em> exactly; otherwise generic types match via Chem.atomTypesMatch().
# 
# \return The number of matching bonds.
# 
def getBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the total number of bonds in <em>molgraph</em> (including bonds to implicit hydrogens).
# 
# \param molgraph The molecular graph.
# 
# \return The total bond count.
# 
def getBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of bonds in <em>molgraph</em> with the given order, optionally including aromatic bonds.
# 
# \param molgraph The molecular graph.
# \param order The bond order to count.
# \param inc_aro If <tt>True</tt>, aromatic bonds are counted in addition to bonds of the given order.
# 
# \return The number of matching bonds.
# 
def getBondCount(molgraph: Chem.MolecularGraph, order: int, inc_aro: bool = True) -> int: pass

##
# \brief Returns the number of chain (non-ring) neighbors of <em>atom</em> in <em>molgraph</em> (including implicit hydrogens).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The chain-atom neighbor count.
# 
def getChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of chain (non-ring) atoms in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The chain-atom count.
# 
def getChainAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of chain (non-ring) bonds incident to <em>atom</em> in <em>molgraph</em> (including implicit-hydrogen bonds).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The chain-bond count.
# 
def getChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of chain (non-ring) bonds in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The chain-bond count.
# 
def getChainBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of connected components in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The component count.
# 
def getComponentCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the covalent radius of the chemical element associated with <em>atom</em> for the given bond order.
# 
# \param atom The atom.
# \param order The bond order.
# 
# \return The covalent radius.
# 
def getCovalentRadius(atom: Chem.Atom, order: int = 1) -> float: pass

##
# \brief Returns the element name of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return A reference to the element name.
# 
def getElementName(atom: Chem.Atom) -> str: pass

##
# \brief Returns the number of valence electrons of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The number of valence electrons.
# 
def getElementValenceElectronCount(atom: Chem.Atom) -> int: pass

##
# \brief Returns the number of explicit neighbors of <em>atom</em> in <em>molgraph</em> whose Chem.AtomType matches <em>type</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param type The Chem.AtomType to count.
# \param strict If <tt>True</tt>, the atom type must match <em>type</em> exactly; otherwise generic types match via Chem.atomTypesMatch().
# 
# \return The matching explicit-atom neighbor count.
# 
def getExplicitAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the total number of explicit atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The number of explicit atoms.
# 
def getExplicitAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of explicit atoms in <em>cntnr</em> that match the given atom type.
# 
# \param cntnr The atom container.
# \param type The atom type to match (see namespace Chem.AtomType).
# \param strict If <tt>True</tt>, atoms must match the type strictly; otherwise generic-type matching applies.
# 
# \return The number of matching explicit atoms.
# 
def getExplicitAtomCount(cntnr: Chem.AtomContainer, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the number of explicit bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The explicit-bond count.
# 
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of explicit bonds of the given order incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param order The bond order to count.
# 
# \return The number of matching explicit bonds.
# 
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int) -> int: pass

##
# \brief Returns the number of explicit bonds of the given order incident to <em>atom</em> that bond to atoms whose Chem.AtomType matches <em>type</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param order The bond order to count.
# \param type The Chem.AtomType of the bonded partner.
# \param strict If <tt>True</tt>, the atom type must match <em>type</em> exactly; otherwise generic types match via Chem.atomTypesMatch().
# 
# \return The number of matching explicit bonds.
# 
def getExplicitBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, order: int, type: int, strict: bool = True) -> int: pass

##
# \brief Returns the total number of explicit bonds in <em>cntnr</em>.
# 
# \param cntnr The bond container.
# 
# \return The number of explicit bonds.
# 
def getExplicitBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the number of explicit bonds in <em>cntnr</em> that match the given bond order.
# 
# \param cntnr The bond container.
# \param order The bond order to match.
# \param inc_aro If <tt>True</tt>, aromatic bonds are included in the count for any order.
# 
# \return The number of matching explicit bonds.
# 
def getExplicitBondCount(cntnr: Chem.BondContainer, order: int, inc_aro: bool = True) -> int: pass

##
# \brief Returns the number of explicit chain (non-ring) neighbors of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The explicit chain-atom neighbor count.
# 
def getExplicitChainAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of explicit chain (non-ring) atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The number of chain atoms.
# 
def getExplicitChainAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of explicit chain (non-ring) bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The explicit chain-bond count.
# 
def getExplicitChainBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of explicit chain (non-ring) bonds in <em>cntnr</em>.
# 
# \param cntnr The bond container.
# 
# \return The number of explicit chain bonds.
# 
def getExplicitChainBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the number of explicit bonds in <em>cntnr</em> that involve a hydrogen atom.
# 
# \param cntnr The bond container.
# 
# \return The number of explicit hydrogen-involving bonds.
# 
def getExplicitHydrogenBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the number of explicit ordinary hydrogens in <em>molgraph</em> (see MolProp.isOrdinaryHydrogen() for the definition of "ordinary").
# 
# \param molgraph The molecular graph.
# \param flags Bitmask of Chem.AtomPropertyFlag values that qualify "ordinary"; an empty bitmask makes any hydrogen ordinary.
# 
# \return The explicit ordinary-hydrogen count.
# 
def getExplicitOrdinaryHydrogenCount(molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief Sets the value of the MolProp.MolecularGraphProperty.FUNCTIONAL_GROUPS property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# \param fg_list The new functional-groups fragment list.
# 
# \since 1.3
# 
def setFunctionalGroups(molgraph: Chem.MolecularGraph, fg_list: Chem.FragmentList) -> None: pass

##
# \brief Tells whether <em>molgraph</em> carries an explicit MolProp.MolecularGraphProperty.FUNCTIONAL_GROUPS property.
# 
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if the FUNCTIONAL_GROUPS property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.3
# 
def hasFunctionalGroups(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Returns the value of the MolProp.MolecularGraphProperty.FUNCTIONAL_GROUPS property of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return A reference to the functional-groups fragment list. 
# 
# \since 1.3
# 
def getFunctionalGroups(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief Removes the MolProp.MolecularGraphProperty.FUNCTIONAL_GROUPS property from <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \since 1.3
# 
def clearFunctionalGroups(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief Returns the number of H-bond acceptor atoms in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The H-bond acceptor count.
# 
def getHBondAcceptorAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Sets the value of the MolProp.AtomProperty.H_BOND_ACCEPTOR_TYPE property of <em>atom</em> to <em>type</em>.
# 
# \param atom The atom.
# \param type The new MolProp.HBondAcceptorAtomType identifier.
# 
def setHBondAcceptorType(atom: Chem.Atom, type: int) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.H_BOND_ACCEPTOR_TYPE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the H-bond acceptor type property is set, and <tt>False</tt> otherwise.
# 
def hasHBondAcceptorType(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.H_BOND_ACCEPTOR_TYPE property of <em>atom</em> (see namespace MolProp.HBondAcceptorAtomType).
# 
# \param atom The atom.
# 
# \return The H-bond acceptor type identifier.
# 
def getHBondAcceptorType(atom: Chem.Atom) -> int: pass

##
# \brief Removes the MolProp.AtomProperty.H_BOND_ACCEPTOR_TYPE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearHBondAcceptorType(atom: Chem.Atom) -> None: pass

##
# \brief Returns the number of H-bond donor atoms in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The H-bond donor count.
# 
def getHBondDonorAtomCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Sets the value of the MolProp.AtomProperty.H_BOND_DONOR_TYPE property of <em>atom</em> to <em>type</em>.
# 
# \param atom The atom.
# \param type The new MolProp.HBondDonorAtomType identifier.
# 
def setHBondDonorType(atom: Chem.Atom, type: int) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.H_BOND_DONOR_TYPE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the H-bond donor type property is set, and <tt>False</tt> otherwise.
# 
def hasHBondDonorType(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.H_BOND_DONOR_TYPE property of <em>atom</em> (see namespace MolProp.HBondDonorAtomType).
# 
# \param atom The atom.
# 
# \return The H-bond donor type identifier.
# 
def getHBondDonorType(atom: Chem.Atom) -> int: pass

##
# \brief Removes the MolProp.AtomProperty.H_BOND_DONOR_TYPE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearHBondDonorType(atom: Chem.Atom) -> None: pass

##
# \brief Returns the number of heavy-atom neighbors of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The heavy-atom neighbor count.
# 
def getHeavyAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of heavy (non-hydrogen) atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The number of heavy atoms.
# 
def getHeavyAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of heavy-atom bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The heavy-atom bond count.
# 
def getHeavyBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of heavy-atom bonds in <em>cntnr</em> (bonds where neither atom is hydrogen).
# 
# \param cntnr The bond container.
# 
# \return The number of heavy-atom bonds.
# 
def getHeavyBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the hybridization-state-dependent atomic polarizability of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The hybrid polarizability.
# 
def getHybridPolarizability(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Returns the number of bonds in <em>molgraph</em> that involve at least one hydrogen atom.
# 
# \param molgraph The molecular graph.
# 
# \return The hydrogen-bond count.
# 
def getHydrogenBondCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Sets the value of the MolProp.AtomProperty.HYDROPHOBICITY property of <em>atom</em> to <em>hyd</em>.
# 
# \param atom The atom.
# \param hyd The new hydrophobicity value.
# 
def setHydrophobicity(atom: Chem.Atom, hyd: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.HYDROPHOBICITY property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the hydrophobicity property is set, and <tt>False</tt> otherwise.
# 
def hasHydrophobicity(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.HYDROPHOBICITY property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The hydrophobicity value.
# 
def getHydrophobicity(atom: Chem.Atom) -> float: pass

##
# \brief Removes the MolProp.AtomProperty.HYDROPHOBICITY property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearHydrophobicity(atom: Chem.Atom) -> None: pass

##
# \brief Returns the IUPAC group number of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The IUPAC group number.
# 
def getIUPACGroup(atom: Chem.Atom) -> int: pass

##
# \brief Returns the total number of implicit hydrogens in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The implicit-hydrogen count.
# 
def getImplicitHydrogenCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Sets the value of the MolProp.AtomProperty.MHMO_PI_CHARGE property of <em>atom</em> to <em>charge</em>.
# 
# \param atom The atom.
# \param charge The new MHMO pi charge value.
# 
def setMHMOPiCharge(atom: Chem.Atom, charge: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.MHMO_PI_CHARGE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the MHMO pi charge property is set, and <tt>False</tt> otherwise.
# 
def hasMHMOPiCharge(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.MHMO_PI_CHARGE property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The MHMO pi charge value.
# 
def getMHMOPiCharge(atom: Chem.Atom) -> float: pass

##
# \brief Removes the MolProp.AtomProperty.MHMO_PI_CHARGE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearMHMOPiCharge(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the MolProp.BondProperty.MHMO_PI_ORDER property of <em>bond</em>.
# 
# \param bond The bond.
# \param order The MHMO pi-bond order.
# 
def setMHMOPiOrder(bond: Chem.Bond, order: float) -> None: pass

##
# \brief 
# \param bond 
# \return 
#
def hasMHMOPiOrder(bond: Chem.Bond) -> bool: pass

##
# \brief Returns the value of the MolProp.BondProperty.MHMO_PI_ORDER property of <em>bond</em>.
# 
# \param bond The bond.
# 
# \return The MHMO pi-bond order.
# 
def getMHMOPiOrder(bond: Chem.Bond) -> float: pass

##
# \brief Removes the MolProp.BondProperty.MHMO_PI_ORDER property from <em>bond</em>.
# 
# \param bond The bond.
# 
def clearMHMOPiOrder(bond: Chem.Bond) -> None: pass

##
# \brief Returns the net formal charge of <em>cntnr</em> (sum of per-atom formal charges).
# 
# \param cntnr The atom container.
# 
# \return The net formal charge.
# 
def getNetFormalCharge(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of SSSR rings of <em>molgraph</em> that contain <em>atom</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The number of containing SSSR rings.
# 
def getNumContainingSSSRRings(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of SSSR rings of <em>molgraph</em> that contain <em>bond</em>.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# 
# \return The number of SSSR rings containing the bond.
# 
def getNumContainingSSSRRings(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of ordinary-hydrogen neighbors of <em>atom</em> in <em>molgraph</em> (see isOrdinaryHydrogen() for the definition of "ordinary").
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param flags Bitmask of Chem.AtomPropertyFlag values that qualify "ordinary".
# 
# \return The ordinary-hydrogen neighbor count.
# 
def getOrdinaryHydrogenCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief Returns the number of ordinary hydrogens in <em>molgraph</em> (see MolProp.isOrdinaryHydrogen() for the definition of "ordinary").
# 
# \param molgraph The molecular graph.
# \param flags Bitmask of Chem.AtomPropertyFlag values that qualify "ordinary"; an empty bitmask makes any hydrogen ordinary.
# 
# \return The ordinary-hydrogen count.
# 
def getOrdinaryHydrogenCount(molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> int: pass

##
# \brief Sets the value of the MolProp.AtomProperty.PEOE_SIGMA_CHARGE property of <em>atom</em> to <em>charge</em>.
# 
# \param atom The atom.
# \param charge The new PEOE sigma charge value.
# 
def setPEOESigmaCharge(atom: Chem.Atom, charge: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.PEOE_SIGMA_CHARGE property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the PEOE sigma charge property is set, and <tt>False</tt> otherwise.
# 
def hasPEOESigmaCharge(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.PEOE_SIGMA_CHARGE property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The PEOE sigma charge value.
# 
def getPEOESigmaCharge(atom: Chem.Atom) -> float: pass

##
# \brief Removes the MolProp.AtomProperty.PEOE_SIGMA_CHARGE property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearPEOESigmaCharge(atom: Chem.Atom) -> None: pass

##
# \brief Sets the value of the MolProp.AtomProperty.PEOE_SIGMA_ELECTRONEGATIVITY property of <em>atom</em> to <em>e_neg</em>.
# 
# \param atom The atom.
# \param e_neg The new PEOE sigma electronegativity value.
# 
def setPEOESigmaElectronegativity(atom: Chem.Atom, e_neg: float) -> None: pass

##
# \brief Tells whether <em>atom</em> carries an explicit MolProp.AtomProperty.PEOE_SIGMA_ELECTRONEGATIVITY property.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the PEOE sigma electronegativity property is set, and <tt>False</tt> otherwise.
# 
def hasPEOESigmaElectronegativity(atom: Chem.Atom) -> bool: pass

##
# \brief Returns the value of the MolProp.AtomProperty.PEOE_SIGMA_ELECTRONEGATIVITY property of <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The PEOE sigma electronegativity value.
# 
def getPEOESigmaElectronegativity(atom: Chem.Atom) -> float: pass

##
# \brief Removes the MolProp.AtomProperty.PEOE_SIGMA_ELECTRONEGATIVITY property from <em>atom</em>.
# 
# \param atom The atom.
# 
def clearPEOESigmaElectronegativity(atom: Chem.Atom) -> None: pass

##
# \brief Returns the period of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The element period.
# 
def getPeriod(atom: Chem.Atom) -> int: pass

##
# \brief Returns the number of ring-atom neighbors of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The ring-atom neighbor count.
# 
def getRingAtomCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of ring atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The number of ring atoms.
# 
def getRingAtomCount(cntnr: Chem.AtomContainer) -> int: pass

##
# \brief Returns the number of ring bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The ring-bond count.
# 
def getRingBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the number of ring bonds in <em>cntnr</em>.
# 
# \param cntnr The bond container.
# 
# \return The number of ring bonds.
# 
def getRingBondCount(cntnr: Chem.BondContainer) -> int: pass

##
# \brief Returns the number of rotatable bonds incident to <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param h_rotors If <tt>True</tt>, hydrogen-only rotors are counted as rotatable.
# \param ring_bonds If <tt>True</tt>, ring bonds are also considered.
# \param amide_bonds If <tt>True</tt>, amide bonds are also considered.
# 
# \return The rotatable-bond count.
# 
def getRotatableBondCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph, h_rotors: bool = False, ring_bonds: bool = False, amide_bonds: bool = False) -> int: pass

##
# \brief Returns the number of rotatable bonds in <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# \param h_rotors If <tt>True</tt>, hydrogen-only rotors are counted.
# \param ring_bonds If <tt>True</tt>, ring bonds are also considered.
# \param amide_bonds If <tt>True</tt>, amide bonds are also considered.
# 
# \return The rotatable-bond count.
# 
def getRotatableBondCount(molgraph: Chem.MolecularGraph, h_rotors: bool = False, ring_bonds: bool = False, amide_bonds: bool = False) -> int: pass

##
# \brief Returns the Lipinski rule-of-five score of <em>molgraph</em>, defined as the number of satisfied criteria (0-4).
# 
# The four criteria evaluated are:
#  - the number of H-bond donor atoms is &le; 5,
#  - the number of H-bond acceptor atoms is &le; 10,
#  - the <em>XLogP</em> value is &le; 5.0,
#  - the molecular mass is &le; 500.0.
# 
# A score of 4 indicates full compliance with the Lipinski rule of five.
# 
# \param molgraph The molecular graph.
# 
# \return The rule-of-five score (0-4).
# 
def getRuleOfFiveScore(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the VSEPR coordination geometry of <em>atom</em> in <em>molgraph</em> (see namespace MolProp.CoordinationGeometry).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The MolProp.CoordinationGeometry identifier.
# 
def getVSEPRCoordinationGeometry(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Returns the VSEPR coordination geometry of <em>atom</em> in <em>molgraph</em> (see namespace MolProp.CoordinationGeometry).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param steric_num The pre-computed steric number of <em>atom</em> (avoids re-computation).
# 
# \return The MolProp.CoordinationGeometry identifier.
# 
def getVSEPRCoordinationGeometry(atom: Chem.Atom, molgraph: Chem.MolecularGraph, steric_num: int) -> int: pass

##
# \brief Returns the Van der Waals radius of the chemical element associated with <em>atom</em>.
# 
# \param atom The atom.
# 
# \return The Van der Waals radius.
# 
def getVdWRadius(atom: Chem.Atom) -> float: pass

##
# \brief Calculates per-atom hydrophobicities for <em>molgraph</em> and stores them as atom properties.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, existing atom hydrophobicity properties are overwritten.
# \param from_logp If <tt>True</tt>, the hydrophobicities are derived from the XLogP atom contributions instead of the Greene algorithm.
# 
def calcAtomHydrophobicities(molgraph: Chem.MolecularGraph, overwrite: bool, from_logp: bool = False) -> None: pass

##
# \brief Calculates the cyclomatic number of <em>molgraph</em> (number of independent cycles).
# 
# \param molgraph The molecular graph.
# 
# \return The cyclomatic number.
# 
def calcCyclomaticNumber(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the dipole moment of <em>cntnr</em> using the standard atom 3D-coordinates accessor.
# 
# \param cntnr The atom container.
# \param moment The output dipole-moment vector.
# 
# \return <tt>True</tt> if the dipole moment could be calculated, and <tt>False</tt> otherwise.
# 
def calcDipoleMoment(cntnr: Chem.AtomContainer, moment: Math.Vector3D) -> bool: pass

##
# \brief Calculates the dipole moment of <em>cntnr</em> using the supplied atom 3D-coordinates function.
# 
# \param cntnr The atom container.
# \param coords_func The function used to retrieve atom 3D-coordinates.
# \param moment The output dipole-moment vector.
# 
# \return <tt>True</tt> if the dipole moment could be calculated, and <tt>False</tt> otherwise.
# 
def calcDipoleMoment(cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, moment: Math.Vector3D) -> bool: pass

##
# \brief Calculates the effective atomic polarizability of <em>atom</em> in <em>molgraph</em> (after Kang and Jhon).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param damping The damping factor applied to remote-atom contributions.
# 
# \return The effective polarizability.
# 
def calcEffectivePolarizability(atom: Chem.Atom, molgraph: Chem.MolecularGraph, damping: float = 0.75) -> float: pass

##
# \brief Calculates the total mass of the explicit atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# 
# \return The total explicit mass.
# 
def calcExplicitMass(cntnr: Chem.AtomContainer) -> float: pass

##
# \brief Calculates the per-element mass composition of the explicit atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param mass_comp The output mass composition.
# 
def calcExplicitMassComposition(cntnr: Chem.AtomContainer, mass_comp: MassComposition) -> None: pass

##
# \brief Calculates the explicit valence of <em>atom</em> in <em>molgraph</em> (sum of explicit bond orders).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The explicit valence.
# 
def calcExplicitValence(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the number of free (lone-pair) valence electrons of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The number of free valence electrons.
# 
def calcFreeValenceElectronCount(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the inductive effect parameter of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param num_bonds The maximum number of bonds over which to accumulate the inductive contributions.
# 
# \return The inductive effect value.
# 
def calcInductiveEffect(atom: Chem.Atom, molgraph: Chem.MolecularGraph, num_bonds: int = 10) -> float: pass

##
# \brief Calculates the \f$ \log S \f$ (aqueous solubility) of <em>molgraph</em> using MolProp.LogSCalculator.
# 
# \param molgraph The molecular graph.
# 
# \return The \f$ \log S \f$ value. 
# 
# \see [\ref LOGS]
# 
def calcLogS(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the lone-pair electronegativity of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The lone-pair electronegativity.
# 
def calcLonePairElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates MHMO pi charges and pi-bond orders for <em>molgraph</em> and stores them as atom/bond properties.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, existing atom/bond properties are overwritten.
# 
def calcMHMOProperties(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Calculates the per-element mass composition of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# \param comp The output mass composition.
# 
def calcMassComposition(molgraph: Chem.MolecularGraph, comp: MassComposition) -> None: pass

##
# \brief Calculates the total molecular mass of <em>molgraph</em> (sum of atom standard atomic weights including implicit hydrogens).
# 
# \param molgraph The molecular graph.
# 
# \return The molecular mass.
# 
def calcMass(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the mean atomic polarizability of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# 
# \return The mean atomic polarizability.
# 
def calcMeanPolarizability(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates PEOE sigma charges and electronegativities for the atoms of <em>molgraph</em> and stores them as atom properties.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, existing atom properties are overwritten; otherwise only atoms without the property are populated.
# \param num_iter The number of charge-shifting iterations.
# \param damping The per-iteration damping factor.
# 
def calcPEOEProperties(molgraph: Chem.MolecularGraph, overwrite: bool, num_iter: int = 20, damping: float = 0.48) -> None: pass

##
# \brief Calculates the pi electronegativity of <em>atom</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The pi electronegativity.
# 
def calcPiElectronegativity(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the bond polarizability of <em>bond</em> within <em>molgraph</em>.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing <em>bond</em>.
# \param damping The damping factor applied to remote-atom contributions.
# 
# \return The calculated bond polarizability.
# 
def calcPolarizability(bond: Chem.Bond, molgraph: Chem.MolecularGraph, damping: float = 0.75) -> float: pass

##
# \brief Calculates the steric number of <em>atom</em> in <em>molgraph</em> (used by VSEPR theory).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The steric number.
# 
def calcStericNumber(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the topological polar surface area (TPSA) of <em>molgraph</em> using MolProp.TPSACalculator.
# 
# \param molgraph The molecular graph.
# 
# \return The TPSA value. 
# 
# \see [\ref TPSA]
# 
def calcTPSA(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the total partial charge of <em>atom</em> (sum of stored PEOE sigma and MHMO pi charge contributions).
# 
# \param atom The atom.
# 
# \return The total partial charge.
# 
def calcTotalPartialCharge(atom: Chem.Atom) -> float: pass

##
# \brief Calculates the total valence of <em>atom</em> in <em>molgraph</em> (explicit valence plus implicit hydrogens).
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return The total valence.
# 
def calcValence(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the number of valence electrons of the chemical element associated with <em>atom</em> (corrected for the atom's formal charge).
# 
# \param atom The atom.
# 
# \return The valence-electron count.
# 
def calcValenceElectronCount(atom: Chem.Atom) -> int: pass

##
# \brief Calculates the <em>XLogP</em> value of <em>molgraph</em> using MolProp.XLogPCalculator.
# 
# \param molgraph The molecular graph.
# 
# \return The <em>XLogP</em> value. 
# 
# \see [\ref XLOGP]
# 
def calcXLogP(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Generates the element histogram of <em>molgraph</em>.
# 
# \param molgraph The molecular graph.
# \param hist The output element histogram.
# \param append If <tt>True</tt>, <em>hist</em> is appended to instead of cleared first.
# 
def generateElementHistogram(molgraph: Chem.MolecularGraph, hist: ElementHistogram, append: bool = False) -> None: pass

##
# \brief Generates the element histogram of the explicit atoms in <em>cntnr</em>.
# 
# \param cntnr The atom container.
# \param hist The output element histogram.
# \param append If <tt>True</tt>, <em>hist</em> is appended to instead of cleared first.
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
# \brief Tells whether <em>bond</em> is an amide bond in <em>molgraph</em>.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# \param c_only If <tt>True</tt>, only C(=O)N bonds are recognized (more restrictive).
# \param db_o_only If <tt>True</tt>, the C=O must be a double bond to oxygen specifically.
# 
# \return <tt>True</tt> if the bond is an amide bond under the given criteria, and <tt>False</tt> otherwise.
# 
def isAmideBond(bond: Chem.Bond, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief Tells whether <em>atom</em> is the center of an amide group in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param c_only If <tt>True</tt>, only carbon amides are recognized.
# \param db_o_only If <tt>True</tt>, a double bond to oxygen must be present. Otherwise, a double bond to sulfur is also allowed.
# 
# \return <tt>True</tt> if <em>atom</em> is an amide center, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def isAmideCenter(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief Tells whether <em>atom</em> is the nitrogen of an amide group in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param c_only If <tt>True</tt>, only carbon amides are recognized.
# \param db_o_only If <tt>True</tt>, the center atom must be double bonded to oxygen. Otherwise, a double bond to sulfur is also allowed.
# 
# \return <tt>True</tt> if <em>atom</em> is an amide nitrogen, and <tt>False</tt> otherwise.
# 
def isAmideNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a bridgehead atom in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param bridged_only If <tt>True</tt>, only bridgeheads of bridged (non-fused) ring systems are recognized.
# 
# \return <tt>True</tt> if <em>atom</em> is a bridgehead, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def isBridgehead(atom: Chem.Atom, molgraph: Chem.MolecularGraph, bridged_only: bool) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a carbonyl-like center in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param c_only If <tt>True</tt>, only carbon centers are recognized.
# \param db_o_only If <tt>True</tt>, a double bond to oxygen must be present. Otherwise, a double bond to sulfur is also allowed.
# 
# \return <tt>True</tt> if <em>atom</em> is a carbonyl-like center, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def isCarbonylLike(atom: Chem.Atom, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

##
# \brief Tells whether <em>atom</em> represents a chemical element.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if <em>atom</em> represents a chemical element, and <tt>False</tt> otherwise.
# 
def isChemicalElement(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>atom</em> acts as an H-bond acceptor in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is an H-bond acceptor, and <tt>False</tt> otherwise.
# 
def isHBondAcceptor(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether <em>atom</em> acts as an H-bond donor in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is an H-bond donor, and <tt>False</tt> otherwise.
# 
def isHBondDonor(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a halogen.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a halogen, and <tt>False</tt> otherwise.
# 
def isHalogen(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a heavy (non-hydrogen) atom.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if <em>atom</em> is a heavy atom, and <tt>False</tt> otherwise.
# 
def isHeavy(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>bond</em> is a hydrogen-only rotor where the rotating end is a heteroatom-bound hydrogen.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# 
# \return <tt>True</tt> if the bond is a heteroatom-hydrogen rotor, and <tt>False</tt> otherwise.
# 
def isHeteroAtomHydrogenRotor(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether <em>bond</em> is a hydrogen bond (one of the bonded atoms is a hydrogen).
# 
# \param bond The bond.
# 
# \return <tt>True</tt> if the bond involves a hydrogen, and <tt>False</tt> otherwise.
# 
def isHydrogenBond(bond: Chem.Bond) -> bool: pass

##
# \brief Tells whether <em>bond</em> is a rotatable bond whose rotation only moves hydrogen atoms.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# 
# \return <tt>True</tt> if the bond is a hydrogen-only rotor, and <tt>False</tt> otherwise.
# 
def isHydrogenRotor(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a member of any ring in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is in a ring, and <tt>False</tt> otherwise.
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
# \brief Tells whether <em>atom</em> is a member of a ring of size <em>size</em> in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param size The ring size to test for.
# 
# \return <tt>True</tt> if <em>atom</em> is in a ring of size <em>size</em>, and <tt>False</tt> otherwise.
# 
def isInRingOfSize(atom: Chem.Atom, molgraph: Chem.MolecularGraph, size: int) -> bool: pass

##
# \brief Tells whether <em>bond</em> is part of a ring of the specified size in <em>molgraph</em>.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# \param size The ring size to test for.
# 
# \return <tt>True</tt> if the bond is part of a ring of size <em>size</em>, and <tt>False</tt> otherwise.
# 
def isInRingOfSize(bond: Chem.Bond, molgraph: Chem.MolecularGraph, size: int) -> bool: pass

##
# \brief Tells whether <em>atom</em> is an invertible (pyramidal, non-aromatic, non-amide) nitrogen in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is an invertible nitrogen, and <tt>False</tt> otherwise.
# 
def isInvertibleNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a main-group element.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a main-group element, and <tt>False</tt> otherwise.
# 
def isMainGroupElement(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a metal.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a metal, and <tt>False</tt> otherwise.
# 
def isMetal(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a noble gas.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a noble gas, and <tt>False</tt> otherwise.
# 
def isNobleGas(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a non-metal.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a non-metal, and <tt>False</tt> otherwise.
# 
def isNonMetal(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>atom</em> is an <em>ordinary</em> hydrogen.
# 
# An "ordinary" hydrogen is a hydrogen atom that has the default values for every atom property named by the <em>flags</em> bitmask (e.g. with the Chem.AtomPropertyFlag.ISOTOPE flag set, only unspecified-isotope hydrogens count as ordinary; with Chem.AtomPropertyFlag.FORMAL_CHARGE set, only neutral hydrogens count as ordinary; etc.). All other hydrogens are deemed special.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# \param flags Bitmask of Chem.AtomPropertyFlag values that qualify "ordinary"; an empty bitmask makes any hydrogen ordinary.
# 
# \return <tt>True</tt> if <em>atom</em> is an ordinary hydrogen, and <tt>False</tt> otherwise.
# 
def isOrdinaryHydrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph, flags: int = 2147483648) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a planar nitrogen in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is a planar nitrogen, and <tt>False</tt> otherwise.
# 
def isPlanarNitrogen(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether <em>bond</em> is rotatable.
# 
# \param bond The bond.
# \param molgraph The molecular graph containing the bond.
# \param h_rotors If <tt>True</tt>, hydrogen-only rotors are counted as rotatable.
# \param ring_bonds If <tt>True</tt>, ring bonds are also considered.
# \param amide_bonds If <tt>True</tt>, amide bonds are also considered.
# 
# \return <tt>True</tt> if the bond is rotatable, and <tt>False</tt> otherwise.
# 
def isRotatable(bond: Chem.Bond, molgraph: Chem.MolecularGraph, h_rotors: bool, ring_bonds: bool, amide_bonds: bool) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a semi-metal.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a semi-metal, and <tt>False</tt> otherwise.
# 
def isSemiMetal(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>atom</em> is a spiro center in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is a spiro center, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def isSpiroCenter(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Tells whether the chemical element associated with <em>atom</em> is a transition metal.
# 
# \param atom The atom.
# 
# \return <tt>True</tt> if the element is a transition metal, and <tt>False</tt> otherwise.
# 
def isTransitionMetal(atom: Chem.Atom) -> bool: pass

##
# \brief Tells whether <em>atom</em> is unsaturated (involved in at least one multiple bond) in <em>molgraph</em>.
# 
# \param atom The atom.
# \param molgraph The molecular graph.
# 
# \return <tt>True</tt> if <em>atom</em> is unsaturated, and <tt>False</tt> otherwise.
# 
def isUnsaturated(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief Perceives the functional groups of <em>molgraph</em> using MolProp.FunctionalGroupList.
# 
# \param molgraph The molecular graph.
# 
# \return A shared reference to the perceived functional-groups fragment list. 
# 
# \since 1.3
# 
def perceiveFunctionalGroups(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief Perceives the functional groups of <em>molgraph</em> and stores them as a property.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, an existing FUNCTIONAL_GROUPS property is overwritten.
# 
# \return A shared reference to the perceived functional-groups fragment list. 
# 
# \since 1.3
# 
def perceiveFunctionalGroups(molgraph: Chem.MolecularGraph, overwrite: bool) -> Chem.FragmentList: pass

##
# \brief Perceives the H-bond acceptor types of the atoms in <em>molgraph</em> and stores them as atom properties.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, existing atom H-bond acceptor type properties are overwritten.
# 
def perceiveHBondAcceptorAtomTypes(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief Perceives the H-bond donor types of the atoms in <em>molgraph</em> and stores them as atom properties.
# 
# \param molgraph The molecular graph (modified in place).
# \param overwrite If <tt>True</tt>, existing atom H-bond donor type properties are overwritten.
# 
def perceiveHBondDonorAtomTypes(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass
