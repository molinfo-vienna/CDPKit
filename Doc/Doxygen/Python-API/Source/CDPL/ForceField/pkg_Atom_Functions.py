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
def clearMMFF94Charge(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMMFF94Charge(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMMFF94Charge(atom: CDPL.Chem.Atom) -> float: pass

##
# \brief 
# \param atom 
# \param charge 
#
def setMMFF94Charge(atom: CDPL.Chem.Atom, charge: float) -> None: pass

##
# \brief 
# \param atom 
# \param molgraph 
# \return 
#
def perceiveUFFType(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param atom 
#
def clearUFFType(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasUFFType(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getUFFType(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setUFFType(atom: CDPL.Chem.Atom, type: int) -> None: pass

##
# \brief 
# \param atom 
#
def clearMMFF94SymbolicType(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMMFF94SymbolicType(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMMFF94SymbolicType(atom: CDPL.Chem.Atom) -> str: pass

##
# \brief 
# \param atom 
# \param type 
#
def setMMFF94SymbolicType(atom: CDPL.Chem.Atom, type: str) -> None: pass

##
# \brief 
# \param atom 
#
def clearMMFF94NumericType(atom: CDPL.Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasMMFF94NumericType(atom: CDPL.Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getMMFF94NumericType(atom: CDPL.Chem.Atom) -> int: pass

##
# \brief 
# \param atom 
# \param type 
#
def setMMFF94NumericType(atom: CDPL.Chem.Atom, type: int) -> None: pass
