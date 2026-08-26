/* 
 * BasicReaction.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of class CDPL::Chem::BasicReaction.
 */

#ifndef CDPL_CHEM_BASICREACTION_HPP
#define CDPL_CHEM_BASICREACTION_HPP

#include <vector>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Default implementation of the Chem::Reaction interface.
         *
         * \c %BasicReaction implements the full Chem::Reaction interface and is the standard concrete type
         * used for the creation, manipulation and processing of chemical reaction information throughout the \e %CDPL.
         */
        class CDPL_CHEM_API BasicReaction : public Reaction
        {

            typedef Util::ObjectPool<BasicMolecule>     ComponentCache;
            typedef ComponentCache::SharedObjectPointer ComponentPtr;
            typedef std::vector<ComponentPtr>           ComponentList;

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BasicReaction instances.
             */
            typedef std::shared_ptr<BasicReaction> SharedPointer;

            /**
             * \brief A mutable random access iterator used to iterate over the stored Chem::BasicMolecule reaction components.
             */
            typedef boost::indirect_iterator<ComponentList::iterator, BasicMolecule>             ComponentIterator;

            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::BasicMolecule reaction components.
             */
            typedef boost::indirect_iterator<ComponentList::const_iterator, const BasicMolecule> ConstComponentIterator;

            /**
             * \brief Constructs an empty \c %BasicReaction instance.
             */
            BasicReaction();

            /**
             * \brief Constructs a \c %BasicReaction instance that is a copy of the reaction \a rxn.
             * \param rxn The other reaction to copy.
             */
            BasicReaction(const BasicReaction& rxn);

            /**
             * \brief Constructs a \c %BasicReaction instance that is a copy of the reaction \a rxn.
             * \param rxn The other reaction to copy.
             */
            BasicReaction(const Reaction& rxn);

            /**
             * \brief Destructor.
             *
             * Destroys the \c %BasicReaction instance and frees all allocated resources.
             */
            ~BasicReaction();

            unsigned int getComponentRole(const Molecule& mol) const;

            std::size_t getComponentIndex(const Molecule& mol) const;

            bool containsComponent(const Molecule& mol) const;

            void clear();

            std::size_t getNumComponents() const;

            std::size_t getNumComponents(unsigned int role) const;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the reaction components.
             * \return A constant iterator pointing to the beginning of the reaction components.
             */
            ConstComponentIterator getComponentsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the reaction components.
             * \return A mutable iterator pointing to the beginning of the reaction components.
             */
            ComponentIterator getComponentsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the reaction components.
             * \return A constant iterator pointing to the end of the reaction components.
             */
            ConstComponentIterator getComponentsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the reaction components.
             * \return A mutable iterator pointing to the end of the reaction components.
             */
            ComponentIterator getComponentsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the reaction components
             *        with the specified role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing to the beginning of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ConstComponentIterator getComponentsBegin(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the reaction components
             *        with the specified role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing to the beginning of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ComponentIterator getComponentsBegin(unsigned int role);

            /**
             * \brief Returns a constant iterator pointing to the end of the reaction components
             *        with the specified role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing to the end of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ConstComponentIterator getComponentsEnd(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the reaction components
             *        with the specified role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing to the end of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ComponentIterator getComponentsEnd(unsigned int role);

            const BasicMolecule& getComponent(std::size_t idx) const;

            BasicMolecule& getComponent(std::size_t idx);

            const BasicMolecule& getComponent(std::size_t idx, unsigned int role) const;

            BasicMolecule& getComponent(std::size_t idx, unsigned int role);

            BasicMolecule& addComponent(unsigned int role);

            /**
             * \brief Creates a new reaction component with the specified role that is a copy of the molecule \a mol.
             * \param role A flag specifying the reaction role of the new component (see namespace Chem::ReactionRole).
             * \param mol Specifies a molecule that provides the data for the new reaction component (note
             *            that only explicitly assigned molecule, atom and bond properties will be copied).
             * \return A reference to the newly created component molecule.
             * \throw Base::ValueError if the value of \a role is not Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            BasicMolecule& addComponent(unsigned int role, const Molecule& mol);

            void swapComponentRoles(unsigned int role1, unsigned int role2);

            void removeComponent(std::size_t idx);

            void removeComponent(std::size_t idx, unsigned int role);

            /**
             * \brief Removes the component referenced by the given iterator.
             * \param it Iterator referencing the component to remove.
             * \return A mutable iterator pointing to the component following the removed one.
             */
            ComponentIterator removeComponent(const ComponentIterator& it);

            void removeComponents(unsigned int role);

            Reaction::SharedPointer clone() const;

            /**
             * \brief Replaces the current set of reaction components and properties by a copy of the 
             *        components and properties of the reaction \a rxn.
             *
             * Internally calls copy() to perform the actual work.
             *
             * \param rxn The reaction to copy.
             * \return A reference to itself.
             */
            BasicReaction& operator=(const BasicReaction& rxn);

            using Reaction::operator=;

            /**
             * \brief Replaces the current set of reaction components and properties by a copy of the 
             *        components and properties of the reaction \a rxn.
             * \param rxn The reaction to copy.
             */
            void copy(const BasicReaction& rxn);

            void copy(const Reaction& rxn);

          private:
            ConstComponentIterator getReactantsBegin() const;
            ComponentIterator      getReactantsBegin();

            ConstComponentIterator getReactantsEnd() const;
            ComponentIterator      getReactantsEnd();

            ConstComponentIterator getAgentsBegin() const;
            ComponentIterator      getAgentsBegin();

            ConstComponentIterator getAgentsEnd() const;
            ComponentIterator      getAgentsEnd();

            ConstComponentIterator getProductsBegin() const;
            ComponentIterator      getProductsBegin();

            ConstComponentIterator getProductsEnd() const;
            ComponentIterator      getProductsEnd();

            /**
             * \brief Returns a \c const reference to the reactant at index \a idx.
             * \param idx The zero-based reactant index.
             * \return A \c const reference to the reactant molecule.
             * \throw Base::IndexError if \a idx is not less than getNumReactants().
             */
            const BasicMolecule& getReactant(std::size_t idx) const;

            /**
             * \brief Returns a mutable reference to the reactant at index \a idx.
             * \param idx The zero-based reactant index.
             * \return A mutable reference to the reactant molecule.
             * \throw Base::IndexError if \a idx is not less than getNumReactants().
             */
            BasicMolecule&       getReactant(std::size_t idx);

            /**
             * \brief Returns a \c const reference to the agent at index \a idx.
             * \param idx The zero-based agent index.
             * \return A \c const reference to the agent molecule.
             * \throw Base::IndexError if \a idx is not less than getNumAgents().
             */
            const BasicMolecule& getAgent(std::size_t idx) const;

            /**
             * \brief Returns a mutable reference to the agent at index \a idx.
             * \param idx The zero-based agent index.
             * \return A mutable reference to the agent molecule.
             * \throw Base::IndexError if \a idx is not less than getNumAgents().
             */
            BasicMolecule&       getAgent(std::size_t idx);

            /**
             * \brief Returns a \c const reference to the product at index \a idx.
             * \param idx The zero-based product index.
             * \return A \c const reference to the product molecule.
             * \throw Base::IndexError if \a idx is not less than getNumProducts().
             */
            const BasicMolecule& getProduct(std::size_t idx) const;

            /**
             * \brief Returns a mutable reference to the product at index \a idx.
             * \param idx The zero-based product index.
             * \return A mutable reference to the product molecule.
             * \throw Base::IndexError if \a idx is not less than getNumProducts().
             */
            BasicMolecule&       getProduct(std::size_t idx);

            /**
             * \brief Removes the reactant at index \a idx.
             * \param idx The zero-based reactant index.
             * \throw Base::IndexError if \a idx is not less than getNumReactants().
             */
            void removeReactant(std::size_t idx);

            /**
             * \brief Removes the agent at index \a idx.
             * \param idx The zero-based agent index.
             * \throw Base::IndexError if \a idx is not less than getNumAgents().
             */
            void removeAgent(std::size_t idx);

            /**
             * \brief Removes the product at index \a idx.
             * \param idx The zero-based product index.
             * \throw Base::IndexError if \a idx is not less than getNumProducts().
             */
            void removeProduct(std::size_t idx);

            /**
             * \brief Removes all reactants from the reaction.
             */
            void removeReactants();

            /**
             * \brief Removes all agents from the reaction.
             */
            void removeAgents();

            /**
             * \brief Removes all products from the reaction.
             */
            void removeProducts();

            /**
             * \brief Creates a new reaction component with the supplied \a role, optionally copying the contents of \a mol.
             * \param role The Chem::ReactionRole flag indicating where the new component is inserted (REACTANT, AGENT, or PRODUCT).
             * \param mol The molecule whose contents are copied into the new component, or \c nullptr to create an empty component.
             * \return A reference to the newly added component.
             */
            BasicMolecule& addComponent(unsigned int role, const Molecule* mol);

            /**
             * \brief Creates a new reactant component, optionally copying the contents of \a mol.
             * \param mol The molecule whose contents are copied into the new reactant, or \c nullptr to create an empty reactant.
             * \return A reference to the newly added reactant.
             */
            BasicMolecule& addReactant(const Molecule* mol);

            /**
             * \brief Creates a new agent component, optionally copying the contents of \a mol.
             * \param mol The molecule whose contents are copied into the new agent, or \c nullptr to create an empty agent.
             * \return A reference to the newly added agent.
             */
            BasicMolecule& addAgent(const Molecule* mol);

            /**
             * \brief Creates a new product component, optionally copying the contents of \a mol.
             * \param mol The molecule whose contents are copied into the new product, or \c nullptr to create an empty product.
             * \return A reference to the newly added product.
             */
            BasicMolecule& addProduct(const Molecule* mol);

            /**
             * \brief Removes all reactant, agent, and product components from the reaction.
             */
            void clearComponents();

            /**
             * \brief Replaces the current reactants, agents, and products by deep copies of those in \a rxn.
             * \param rxn The source reaction.
             */
            void copyComponents(const BasicReaction& rxn);

            /**
             * \brief Replaces the current reactants, agents, and products by deep copies of those in \a rxn.
             * \param rxn The source reaction.
             */
            void copyComponents(const Reaction& rxn);

            ComponentPtr allocComponent(const Molecule* mol);

            ComponentCache compCache;
            ComponentList  components;
            std::size_t    agentsStartIdx;
            std::size_t    productsStartIdx;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BASICREACTION_HPP
