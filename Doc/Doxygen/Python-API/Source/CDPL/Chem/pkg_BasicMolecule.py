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
#
class BasicMolecule(Molecule):

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param mol 
    #
    def __init__(mol: BasicMolecule) -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param mol 
    #
    def __init__(mol: Molecule) -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param molgraph 
    #
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param mol 
    #
    def copy(mol: BasicMolecule) -> None: pass

    ##
    # \brief 
    # \param mol 
    #
    def copy(mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def copy(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param mol 
    #
    def append(mol: BasicMolecule) -> None: pass

    ##
    # \brief 
    # \param mol 
    #
    def append(mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def append(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a mol.
    # \param mol The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a mol.
    # \param mol The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a molgraph.
    # \param molgraph The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(molgraph: MolecularGraph) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param mol Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param mol Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(molgraph: MolecularGraph) -> BasicMolecule: pass
