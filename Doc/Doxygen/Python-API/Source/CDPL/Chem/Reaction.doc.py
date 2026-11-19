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
# \brief Abstract base class for chemical reactions composed of role-tagged reaction components of type Chem.Molecule.
# 
# Each component carries a reaction role that is specified by one of the constants declared in namespace Chem.ReactionRole. Reaction roles divide the components into three different subsets: reactants, agents/catalysts and products. For component management/access the methods getComponentRole(), getNumComponents(), getComponent(), getComponentsBegin() and getComponentsEnd() are available. For reaction editing the methods addComponent(), removeComponent(), swapComponentRoles() and clear(). The method clone() allows the creation of polymorphic deep copies and reaction properties can be stored/retrieved via the methods of the Base.PropertyContainer base class.
# 
class Reaction(Base.PropertyContainer):

    ##
    # \brief Mutable sequence of Chem.Molecule objects.
    # 
    class ComponentSequence(Boost.Python.instance):

        ##
        # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
        # \param mol The value to test for membership.
        # \return The result of the membership test operation.
        # 
        def __contains__(mol: Molecule) -> bool: pass

        ##
        # \brief Returns the  number of reaction components.
        # 
        # \return The  number of reaction components.
        # 
        def __len__() -> int: pass

        ##
        # \brief Removes the reaction component at the specified index.
        # 
        # \param idx The zero-based index of the component to remove.
        # 
        # \throw Base.IndexError if <em>idx</em> is not in the range [0, \c len(self)).
        # 
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief Returns the reaction component at index <em>idx</em>.
        # 
        # \param idx The zero-based index of the reaction component to return.
        # 
        # \return The reaction component at the specified index. 
        # 
        # \throw Base.IndexError if <em>idx</em> is not in the range [0, \c len(self)).
        # 
        def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief Contructs the \c Reaction instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Removes all components and clears all properties of the reaction.
    # 
    def clear() -> None: pass

    ##
    # \brief Creates a new reaction component with the specified role.
    # 
    # \param role The reaction role of the new component (see namespace Chem.ReactionRole).
    # 
    # \return The newly created component molecule. 
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
    # \return The reaction role of the component (see namespace Chem.ReactionRole).
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
    # \param role The reaction role (see namespace Chem.ReactionRole).
    # 
    # \return The number of reaction components with the specified role. 
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def getNumComponents(role: int) -> int: pass

    ##
    # \brief Returns the total number of reaction components.
    # 
    # \return The total number of reaction components.
    # 
    def getNumComponents() -> int: pass

    ##
    # \brief Returns the reaction component at index <em>idx</em> in the list of components with the specified role.
    # 
    # \param idx The zero-based index of the reaction component to return.
    # \param role A flag indicating the reaction role of the component (see namespace Chem.ReactionRole).
    # 
    # \return The reaction component with the specified role and index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, <tt>getNumComponents(role)</tt>). Base.ValueError if the value of <em>role</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def getComponent(idx: int, role: int) -> Molecule: pass

    ##
    # \brief Returns the reaction component at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the reaction component to return.
    # 
    # \return The reaction component at the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumComponents()).
    # 
    def getComponent(idx: int) -> Molecule: pass

    ##
    # \brief Removes all components with the specified role.
    # 
    # \param role The reaction role of the components to remove (see namespace Chem.ReactionRole).
    # 
    # \throw Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def removeComponents(role: int) -> None: pass

    ##
    # \brief Removes the reaction component at index <em>idx</em> in the list of components with the specified role.
    # 
    # \param idx The zero-based index of the component to remove.
    # \param role The reaction role of the component (see namespace Chem.ReactionRole).
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, <tt>getNumComponents(role)</tt>). Base.ValueError if the value of <em>role</em> is not Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def removeComponent(idx: int, role: int) -> None: pass

    ##
    # \brief Removes the reaction component at the specified index.
    # 
    # \param idx The zero-based index of the component to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumComponents()).
    # 
    def removeComponent(idx: int) -> None: pass

    ##
    # \brief Swaps the reaction roles of the component sets specified by <em>role1</em> and <em>role2</em>.
    # 
    # If <em>role1</em> is equal to <em>role2</em>, the method has no effect.
    # 
    # \param role1 The reaction role of the first component set (see namespace Chem.ReactionRole).
    # \param role2 The reaction role of the second component set (see namespace Chem.ReactionRole).
    # 
    # \throw Base.ValueError if the value of <em>role1</em> and/or <em>role2</em> is not equal to Chem.ReactionRole.REACTANT, Chem.ReactionRole.AGENT or Chem.ReactionRole.PRODUCT.
    # 
    def swapComponentRoles(role1: int, role2: int) -> None: pass

    ##
    # \brief Creates a deep copy of the current reaction state.
    # 
    # \return The copy of the reaction.
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
    # \return \a self.
    # 
    def assign(rxn: Reaction) -> Reaction: pass

    ##
    # \brief Returns the list of reactant components.
    # \return The list of reactants.
    # 
    def getReactants() -> ComponentSequence: pass

    ##
    # \brief Returns the list of agent components.
    # \return The list of agents.
    # 
    def getAgents() -> ComponentSequence: pass

    ##
    # \brief Returns the list of product components.
    # \return The list of products.
    # 
    def getProducts() -> ComponentSequence: pass

    ##
    # \brief Registers a global postprocessing function invoked after every reaction copy operation.
    # 
    # \param func The function to register.
    # 
    @staticmethod
    def registerCopyPostprocessingFunction(func: VoidMoleculeMolecularGraphFunctor) -> None: pass

    ##
    # \brief Invokes all registered copy postprocessing functions with <tt>self</tt> as the target and <em>src_rxn</em> as the source reaction.
    # 
    # \param src_rxn The source reaction the copy was made from.
    # 
    def invokeCopyPostprocessingFunctions(src_rxn: Reaction) -> None: pass

    ##
    # \brief Returns the serialized state of the \c Reaction instance.
    # \return The serialized state of the \c Reaction instance.
    # 
    def __getstate__() -> tuple: pass

    ##
    # \brief Returns the value of the property specified by <em>key</em>.
    # 
    # If an entry for the specified property exists, the stored value will be returned. Otherwise a Base.ItemNotFound exception will be thrown.
    # 
    # \param key The key of the property value to return.
    # 
    # 
    # \return The stored property value. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested property value does not exist.
    # 
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief Returns the reaction component at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the reaction component to return.
    # 
    # \return The reaction component at the specified index. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumComponents()).
    # 
    def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief Tells whether or not a value has been assigned to the property specified by <em>key</em>.
    # 
    # \param key The key of the property.
    # 
    # \return <tt>True</tt> if a value has been assigned to the specified property, and <tt>False</tt> otherwise.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
    # \param mol The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(mol: Molecule) -> bool: pass

    ##
    # \brief Sets the value of the property specified by <em>key</em> to <em>val</em>.
    # 
    # If <em>val</em> is of type Base.Any and empty, i.e. the method Base.Any.isEmpty() returns <tt>True</tt>, and a property entry for <em>key</em> exists, the entry gets erased (equivalent to removeProperty() with <em>key</em> as argument).
    # 
    # \param key The key of the property value to assign or remove.
    # \param val The value of the property.
    # 
    def __setitem__(key: Base.LookupKey, val: Base.Any) -> None: pass

    ##
    # \brief Removes the entry for the property specified by <em>key</em>.
    # 
    # \param key The key of the property entry to remove.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was removed, and <tt>False</tt> otherwise.
    # 
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Removes the reaction component at the specified index.
    # 
    # \param idx The zero-based index of the component to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumComponents()).
    # 
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief Returns the total number of reaction components.
    # 
    # \return The total number of reaction components.
    # 
    def __len__() -> int: pass

    reactants = property(getReactants)

    agents = property(getAgents)

    products = property(getProducts)

    numComponents = property(getNumComponents)
