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
# \brief Default concrete implementation of the Chem.Reaction abstract interface.
# 
# <tt>BasicReaction</tt> stores reaction components as Chem.BasicMolecule instances grouped by reaction role (reactant, agent, product). Components are pooled via a Util.ObjectPool to minimize allocation overhead in batch processing scenarios.
# 
class BasicReaction(Reaction):

    ##
    # \brief Constructs an empty <tt>BasicReaction</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %BasicReaction instance \a mol.
    # \param mol The \c %BasicReaction instance to copy.
    # 
    def __init__(mol: BasicReaction) -> None: pass

    ##
    # \brief Initializes the \c %BasicReaction instance.
    # \param mol 
    # 
    def __init__(mol: Reaction) -> None: pass

    ##
    # \brief Adds a new empty component with the specified reaction role.
    # 
    # \param role The reaction role of the new component (see namespace Chem.ReactionRole).
    # 
    # \return A reference to the newly created component molecule.
    # 
    def addComponent(role: int) -> BasicMolecule: pass

    ##
    # \brief Creates a new reaction component with the supplied <em>role</em>, optionally copying the contents of <em>mol</em>.
    # 
    # \param role The Chem.ReactionRole flag indicating where the new component is inserted (REACTANT, AGENT, or PRODUCT).
    # \param mol The molecule whose contents are copied into the new component, or <tt>None</tt> to create an empty component.
    # 
    # \return A reference to the newly added component.
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
