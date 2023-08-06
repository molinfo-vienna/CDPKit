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
# \brief Reaction.
# 
class Reaction(Base.PropertyContainer):

    ##
    # \brief 
    #
    class ComponentSequence(Boost.Python.instance):

        ##
        # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
        # \param mol The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(mol: Molecule) -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief Initializes the \e %Reaction instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Removes all components and clears all properties of the reaction.
    # 
    def clear() -> None: pass

    ##
    # \brief Creates a new reaction component with the specified role.
    # 
    # \param role A flag specifying the reaction role of the new component (see namespace Chem.ReactionRole).
    # 
    # \return A reference to the newly created component molecule. 
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def addComponent(role: int) -> Molecule: pass

    ##
    # \brief Tells whether the specified molecule is a component of this reaction.
    # 
    # \param mol The molecule to look for.
    # 
    # \return <tt>True</tt> if the specified molecule is a component of this reaction, and <tt>False</tt> otherwise.
    # 
    def containsComponent(mol: Molecule) -> bool: pass

    ##
    # \brief Returns the reaction role of the specified component.
    # 
    # If the specified molecule is not a component of this reaction, Chem.ReactionRole.NONE will be returned.
    # 
    # \param mol The component for which to return the reaction role.
    # 
    # \return A flag that specifies the reaction role of the component (see namespace Chem.ReactionRole).
    # 
    def getComponentRole(mol: Molecule) -> int: pass

    ##
    # \brief Returns the index of the specified reaction component.
    # 
    # \param mol The component for which to return the index.
    # 
    # \return The zero-based index of the specified reaction component. 
    # 
    # \throw Base.ItemNotFound if the specified molecule is not a component of this reaction.
    # 
    def getComponentIndex(mol: Molecule) -> int: pass

    ##
    # \brief Returns the number of reaction components with the specified role.
    # 
    # \param role A flag that specifies the reaction role (see namespace Chem.ReactionRole).
    # 
    # \return The number of reaction components with the specified role. 
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def getNumComponents(role: int) -> int: pass

    ##
    # \brief Returns the number of reaction components.
    # 
    # \return The number of reaction components.
    # 
    def getNumComponents() -> int: pass

    ##
    # \brief Returns a reference to the reaction component at index <em>idx</em> in the list of components with the specified role.
    # 
    # \param idx The zero-based index of the reaction component to return.
    # \param role A flag indicating the reaction role of the component (see namespace Chem.ReactionRole).
    # 
    # \return A reference to the reaction component with the specified role and index. 
    # 
    # \throw Base.IndexError if the number of components with the specified role is zero or <em>idx</em> is not in the range [0, <tt>getNumComponents(role) - 1</tt>]. Base.ValueError if the value of <em>role</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def getComponent(idx: int, role: int) -> Molecule: pass

    ##
    # \brief Returns a reference to the reaction component at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the reaction component to return.
    # 
    # \return A reference to the reaction component at the specified index. 
    # 
    # \throw Base.IndexError if the number of components is zero or <em>idx</em> is not in the range [0, getNumComponents() - 1].
    # 
    def getComponent(idx: int) -> Molecule: pass

    ##
    # \brief Removes all components with the specified role.
    # 
    # \param role A flag specifying the reaction role of the components to remove (see namespace Chem.ReactionRole).
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def removeComponents(role: int) -> None: pass

    ##
    # \brief Removes the reaction component at index <em>idx</em> in the list of components with the specified role.
    # 
    # \param idx The zero-based index of the component to remove.
    # \param role The reaction role of the components
    # 
    # \throw Base.IndexError if the number of components with the specified role is zero or <em>idx</em> is not in the range [0, <tt>getNumComponents(role) - 1</tt>]. Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def removeComponent(idx: int, role: int) -> None: pass

    ##
    # \brief Removes the reaction component at the specified index.
    # 
    # \param idx The zero-based index of the component to remove.
    # 
    # \throw Base.IndexError if the number of components is zero or <em>idx</em> is not in the range [0, getNumComponents() - 1].
    # 
    def removeComponent(idx: int) -> None: pass

    ##
    # \brief Swaps the reaction roles of the component sets specified by <em>role1</em> and <em>role2</em>.
    # 
    # If <em>role1</em> is equal to <em>role2</em>, the method has no effect.
    # 
    # \param role1 A flag specifying the reaction role of the first component set (see namespace Chem.ReactionRole).
    # \param role2 A flag specifying the reaction role of the second component set (see namespace Chem.ReactionRole).
    # 
    # \throw Base.ValueError if the value of <em>role1</em> and/or <em>role2</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def swapComponentRoles(role1: int, role2: int) -> None: pass

    ##
    # \brief Creates a copy of the current reaction state.
    # 
    # \return A smart reference to the copy of the reaction.
    # 
    def clone() -> Reaction: pass

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
    def assign(rxn: Reaction) -> Reaction: pass

    ##
    # \brief 
    # \return 
    #
    def getReactants() -> ComponentSequence: pass

    ##
    # \brief 
    # \return 
    #
    def getAgents() -> ComponentSequence: pass

    ##
    # \brief 
    # \return 
    #
    def getProducts() -> ComponentSequence: pass

    ##
    # \brief 
    # \param arg1 
    # \return 
    #
    def __getstate__() -> tuple: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
    # \param mol The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(mol: Molecule) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    reactants = property(getReactants)

    agents = property(getAgents)

    products = property(getProducts)

    numComponents = property(getNumComponents)

    ##
    # \brief FIXME!
    #
    numReactants = property(getNumReactants)

    ##
    # \brief FIXME!
    #
    numAgents = property(getNumAgents)

    ##
    # \brief FIXME!
    #
    numProducts = property(getNumProducts)
