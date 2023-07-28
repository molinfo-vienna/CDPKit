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
# \brief Replaces the current state of \a molgraph with a copy of the state of the \e %bool instance \a strict.
# \param molgraph The \e % instance this method is called upon.
# \param strict The \e %bool instance to copy.
# \return \a molgraph
# 
def assignMMFF94BondTypeIndices(molgraph: CDPL.Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \param strict 
# \param overwrite 
#
def calcMMFF94AtomCharges(molgraph: CDPL.Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief Replaces the current state of \a molgraph with a copy of the state of the \e %bool instance \a strict.
# \param molgraph The \e % instance this method is called upon.
# \param strict The \e %bool instance to copy.
# \return \a molgraph
# 
def assignMMFF94AtomTypes(molgraph: CDPL.Chem.MolecularGraph, strict: bool, overwrite: bool) -> None: pass

##
# \brief Replaces the current state of \a molgraph with a copy of the state of the \e %bool instance \a overwrite.
# \param molgraph The \e % instance this method is called upon.
# \param overwrite The \e %bool instance to copy.
# \return \a molgraph
# 
def assignUFFAtomTypes(molgraph: CDPL.Chem.MolecularGraph, overwrite: bool) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def perceiveMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph) -> CDPL.Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param overwrite 
# \return 
#
def perceiveMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph, overwrite: bool) -> CDPL.Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
#
def clearMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

##
# \brief 
# \param molgraph 
# \return 
#
def hasMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph) -> bool: pass

##
# \brief 
# \param molgraph 
# \return 
#
def getMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph) -> CDPL.Chem.FragmentList: pass

##
# \brief 
# \param molgraph 
# \param rings 
#
def setMMFF94AromaticRings(molgraph: CDPL.Chem.MolecularGraph, rings: CDPL.Chem.FragmentList) -> None: pass
