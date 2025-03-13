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
# \brief BasicMolecule.
# 
class BasicMolecule(Molecule):

    ##
    # \brief Constructs an empty <tt>BasicMolecule</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the Chem.Molecule instance <em>mol</em>.
    # 
    # \param mol The other Chem.Molecule instance to copy.
    # 
    def __init__(mol: BasicMolecule) -> None: pass

    ##
    # \brief Constructs a copy of the Chem.Molecule instance <em>mol</em>.
    # 
    # \param mol The other Chem.Molecule instance to copy.
    # 
    def __init__(mol: Molecule) -> None: pass

    ##
    # \brief Constructs a <tt>BasicMolecule</tt> instance with copies of the atoms and bonds of the Chem.MolecularGraph instance <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms and bonds to copy.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # \param mol The molecule to copy.
    # 
    def copy(mol: BasicMolecule) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # \param mol The molecule to copy.
    # 
    def copy(mol: Molecule) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms, bonds and properties to copy.
    # 
    def copy(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the molecule <em>mol</em>.
    # 
    # \param mol The molecule providing the atoms and bonds to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(mol: BasicMolecule) -> None: pass

    ##
    # \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the molecule <em>mol</em>.
    # 
    # \param mol The molecule providing the atoms and bonds to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(mol: Molecule) -> None: pass

    ##
    # \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms and bonds to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param mol The molecule to copy.
    # 
    # \return \a self
    # 
    def assign(mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecule <em>mol</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param mol The molecule to copy.
    # 
    # \return \a self
    # 
    def assign(mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current set of atoms, bonds and properties by a copy of the atoms, bonds and properties of the molecular graph <em>molgraph</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param molgraph The Chem.MolecularGraph instance providing the atoms and bonds to copy.
    # 
    # \return \a self
    # 
    def assign(molgraph: MolecularGraph) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param mol Specifies the second addend.
    # \return The updated \c %BasicMolecule instance \a self.
    # 
    def __iadd__(mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param mol Specifies the second addend.
    # \return The updated \c %BasicMolecule instance \a self.
    # 
    def __iadd__(mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param molgraph Specifies the second addend.
    # \return The updated \c %BasicMolecule instance \a self.
    # 
    def __iadd__(molgraph: MolecularGraph) -> BasicMolecule: pass
