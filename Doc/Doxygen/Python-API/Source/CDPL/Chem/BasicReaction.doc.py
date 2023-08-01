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
# \brief BasicReaction.
# 
class BasicReaction(Reaction):

    ##
    # \brief Constructs an empty <tt>BasicReaction</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BasicReaction instance with a copy of the state of the \e %BasicReaction instance \a mol.
    # \param mol The \e %BasicReaction instance to copy.
    # 
    def __init__(mol: BasicReaction) -> None: pass

    ##
    # \brief Initializes the \e %BasicReaction instance.
    # \param mol 
    # 
    def __init__(mol: Reaction) -> None: pass

    ##
    # \brief Creates a new reaction component with the specified role.
    # 
    # \param role A flag specifying the reaction role of the new component (see namespace Chem.ReactionRole).
    # 
    # \return A reference to the newly created component molecule. 
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def addComponent(role: int) -> BasicMolecule: pass

    ##
    # \brief Creates a new reaction component with the specified role that is a copy of the molecule <em>mol</em>.
    # 
    # \param role A flag specifying the reaction role of the new component (see namespace Chem.ReactionRole).
    # \param mol Specifies a molecule that provides the data for the new reaction component (note that only explicitly assigned molecule, atom and bond properties will be copied).
    # 
    # \return A reference to the newly created component molecule. 
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def addComponent(role: int, mol: Molecule) -> BasicMolecule: pass

    ##
    # \brief Replaces the current set of reaction components and properties by a copy of the components and properties of the reaction <em>rxn</em>.
    # 
    # \param rxn The reaction to copy.
    # 
    def copy(rxn: BasicReaction) -> None: pass

    ##
    # \brief Replaces the current set of reaction components and properties by a copy of the components and properties of the reaction <em>rxn</em>.
    # 
    # \param rxn The reaction to copy.
    # 
    def copy(rxn: Reaction) -> None: pass

    ##
    # \brief Replaces the current set of reaction components and properties by a copy of the components and properties of the reaction <em>rxn</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param rxn The reaction to copy.
    # 
    # \return \a self
    # 
    def assign(rxn: BasicReaction) -> BasicReaction: pass

    ##
    # \brief Replaces the current set of reaction components and properties by a copy of the components and properties of the reaction <em>rxn</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param rxn The reaction to copy.
    # 
    # \return \a self
    # 
    def assign(rxn: Reaction) -> BasicReaction: pass
