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
# \brief Removes all explicit hydrogen atoms from the molecule <em>mol</em>.
# 
# \param mol The molecule for which to remove all explicit hydrogen atoms.
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be corrected, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise.
# 
def makeHydrogenDeplete(mol: Molecule, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief Removes all explicit ordinary hydrogen atoms from the molecule <em>mol</em>.
# 
# \param mol The molecule for which to remove all explicit ordinary hydrogen atoms.
# \param flags Specifies the set of atom properties to check (see namespace Chem.AtomPropertyFlag).
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be corrected, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise. 
# 
# \see Chem.isOrdinaryHydrogen
# 
def makeOrdinaryHydrogenDeplete(mol: Molecule, flags: int, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief Converts all implicit hydrogens of the molecule <em>mol</em> to explicit hydrogen atoms.
# 
# \param mol The molecule that has to be made hydrogen complete.
# \param corr_impl_h_count <tt>True</tt> if the implicit hydrogen count property of the hydrogen completed atoms shall be set to zero, <tt>False</tt> if the property shall be left unchanged.
# 
# \return <tt>False</tt> if <em>mol</em> was not altered, <tt>True</tt> otherwise.
# 
def makeHydrogenComplete(mol: Molecule, corr_impl_h_count: bool = True) -> bool: pass

##
# \brief 
# \param mol 
# \param pred 
#
def removeAtomsIf(mol: Molecule, pred: AtomPredicate) -> None: pass

##
# \brief 
# \param mol 
# \param coords_func 
# \param dist_tol 
# \param atom_idx_offs 
#
def connectAtoms(mol: Molecule, coords_func: Atom3DCoordinatesFunction, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief 
# \param mol 
# \param dist_tol 
# \param atom_idx_offs 
#
def connectAtoms(mol: Molecule, dist_tol: float = 0.3, atom_idx_offs: int = 0) -> None: pass

##
# \brief 
# \param mol 
# \param pred 
#
def removeAtomsIfNot(mol: Molecule, pred: AtomPredicate) -> None: pass
