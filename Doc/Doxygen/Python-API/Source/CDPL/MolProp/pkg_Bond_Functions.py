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
# \param bond 
# \param molgraph 
# \param c_only 
# \param db_o_only 
# \return 
#
def isAmideBond(bond: Chem.Bond, molgraph: Chem.MolecularGraph, c_only: bool = False, db_o_only: bool = False) -> bool: pass

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
# \param h_rotors 
# \param ring_bonds 
# \param amide_bonds 
# \return 
#
def isRotatable(bond: Chem.Bond, molgraph: Chem.MolecularGraph, h_rotors: bool, ring_bonds: bool, amide_bonds: bool) -> bool: pass

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
# \param bond 
# \param molgraph 
# \return 
#
def isInRing(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param bond 
#
def clearMHMOPiOrder(bond: Chem.Bond) -> None: pass

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
# \param order 
#
def setMHMOPiOrder(bond: Chem.Bond, order: float) -> None: pass

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
# \param molgraph 
# \return 
#
def isHydrogenRotor(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \return 
#
def getNumContainingSSSRRings(bond: Chem.Bond, molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param bond 
# \param molgraph 
# \param damping 
# \return 
#
def calcPolarizability(bond: Chem.Bond, molgraph: Chem.MolecularGraph, damping: float = 0.75) -> float: pass
