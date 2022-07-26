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
    # \param self The \e %BasicMolecule instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param self The \e %BasicMolecule instance to initialize.
    # \param mol 
    #
    def __init__(self: object, mol: BasicMolecule) -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param self The \e %BasicMolecule instance to initialize.
    # \param mol 
    #
    def __init__(self: object, mol: Molecule) -> None: pass

    ##
    # \brief Initializes the \e %BasicMolecule instance.
    # \param self The \e %BasicMolecule instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol 
    #
    def copy(self: BasicMolecule, mol: BasicMolecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol 
    #
    def copy(self: BasicMolecule, mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param molgraph 
    #
    def copy(self: BasicMolecule, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol 
    #
    def append(self: BasicMolecule, mol: BasicMolecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol 
    #
    def append(self: BasicMolecule, mol: Molecule) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param molgraph 
    #
    def append(self: BasicMolecule, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a mol.
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicMolecule, mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a mol.
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param mol The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicMolecule, mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicMolecule instance \a molgraph.
    # \param self The \e %BasicMolecule instance this method is called upon.
    # \param molgraph The \e %BasicMolecule instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicMolecule, molgraph: MolecularGraph) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param self The \e %BasicMolecule instance acting as in-place addend.
    # \param mol Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(self: BasicMolecule, mol: BasicMolecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mol</tt>.
    # \param self The \e %BasicMolecule instance acting as in-place addend.
    # \param mol Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(self: BasicMolecule, mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += molgraph</tt>.
    # \param self The \e %BasicMolecule instance acting as in-place addend.
    # \param molgraph Specifies the second addend.
    # \return The updated \e %BasicMolecule instance \a self.
    #
    def __iadd__(self: BasicMolecule, molgraph: MolecularGraph) -> BasicMolecule: pass
