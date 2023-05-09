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
# \param ring 
# \param molgraph 
# \param arom_bond_mask 
# \return 
#
def isAromatic(ring: Fragment, molgraph: MolecularGraph, arom_bond_mask: CDPL.Util.BitSet) -> bool: pass

##
# \brief 
# \param ring 
# \param molgraph 
# \return 
#
def isNotAromatic(ring: Fragment, molgraph: MolecularGraph) -> bool: pass

##
# \brief 
# \param frag 
# \return 
#
def makeHydrogenDeplete(frag: Fragment) -> bool: pass

##
# \brief 
# \param frag 
# \param flags 
# \return 
#
def makeOrdinaryHydrogenDeplete(frag: Fragment, flags: int) -> bool: pass

##
# \brief 
# \param frag 
# \param pred 
#
def removeAtomsIf(frag: Fragment, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param frag 
# \param pred 
#
def removeAtomsIfNot(frag: Fragment, pred: AtomPredicate) -> None: pass
