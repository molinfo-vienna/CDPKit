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
# \param molgraph 
# \param strict 
# \param overwrite 
#
def assignMMFF94BondTypeIndices(molgraph: Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param strict 
# \param overwrite 
#
def calcMMFF94AtomCharges(molgraph: Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param strict 
# \param overwrite 
#
def assignMMFF94AtomTypes(molgraph: Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
#
def assignUFFAtomTypes(molgraph: Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveMMFF94AromaticRings(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveMMFF94AromaticRings(molgraph: Chem.MolecularGraph, overwrite: bool) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearMMFF94AromaticRings(molgraph: Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMMFF94AromaticRings(molgraph: Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMMFF94AromaticRings(molgraph: Chem.MolecularGraph) -> Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param rings 
#
def setMMFF94AromaticRings(molgraph: Chem.MolecularGraph, rings: Chem.FragmentList) -> None: pass
