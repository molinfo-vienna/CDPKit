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
         * \brief Default concrete implementation of the Chem::Reaction abstract interface.
         *
         * \c %BasicReaction stores reaction components as Chem::BasicMolecule instances grouped by
         * reaction role (reactant, agent, product). Components are pooled via a Util::ObjectPool to
         * minimize allocation overhead in batch processing scenarios.
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
             * \brief Constructs a copy of the \c %BasicReaction instance \a rxn.
             * \param rxn The other \c %Reaction instance to copy.
             */
            BasicReaction(const BasicReaction& rxn);

            /**
             * \brief Constructs a copy of the Chem::Reaction instance \a rxn.
             * \param rxn The other Chem::Reaction instance to copy.
             */
            BasicReaction(const Reaction& rxn);

            /**
             * \brief Destructor.
             *
             * Destroys the \c %BasicReaction instance and frees all allocated resources.
             */
            ~BasicReaction();

            /**
             * \brief Returns the reaction role of the component \a mol (see namespace Chem::ReactionRole).
             * \param mol The molecule whose role is requested.
             * \return The reaction role of the component.
             */
            unsigned int getComponentRole(const Molecule& mol) const;

            /**
             * \brief Returns the index of the component \a mol in the reaction.
             * \param mol The molecule whose index is requested.
             * \return The zero-based index of the component.
             */
            std::size_t getComponentIndex(const Molecule& mol) const;

            /**
             * \brief Tells whether \a mol is a component of the reaction.
             * \param mol The molecule to look up.
             * \return \c true if \a mol is a component of the reaction, and \c false otherwise.
             */
            bool containsComponent(const Molecule& mol) const;

            /**
             * \brief Removes all components and clears all properties of the reaction.
             */
            void clear();

            /**
             * \brief Returns the total number of components in the reaction.
             * \return The total number of components.
             */
            std::size_t getNumComponents() const;

            /**
             * \brief Returns the number of components with the given reaction role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return The number of components with the specified role.
             */
            std::size_t getNumComponents(unsigned int role) const;

            /**
             * \brief Returns a constant iterator pointing to the first component of the reaction.
             * \return A constant iterator pointing to the first component.
             */
            ConstComponentIterator getComponentsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the first component of the reaction.
             * \return A mutable iterator pointing to the first component.
             */
            ComponentIterator getComponentsBegin();

            /**
             * \brief Returns a constant iterator pointing one past the last component of the reaction.
             * \return A constant iterator pointing one past the last component.
             */
            ConstComponentIterator getComponentsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing one past the last component of the reaction.
             * \return A mutable iterator pointing one past the last component.
             */
            ComponentIterator getComponentsEnd();

            /**
             * \brief Returns a constant iterator pointing to the first component with the given reaction role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing to the first component with the specified role.
             */
            ConstComponentIterator getComponentsBegin(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing to the first component with the given reaction role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing to the first component with the specified role.
             */
            ComponentIterator getComponentsBegin(unsigned int role);

            /**
             * \brief Returns a constant iterator pointing one past the last component with the given reaction role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing one past the last component with the specified role.
             */
            ConstComponentIterator getComponentsEnd(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing one past the last component with the given reaction role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing one past the last component with the specified role.
             */
            ComponentIterator getComponentsEnd(unsigned int role);

            /**
             * \brief Returns a \c const reference to the component at the specified index.
             * \param idx The zero-based component index.
             * \return A \c const reference to the component.
             */
            const BasicMolecule& getComponent(std::size_t idx) const;

            /**
             * \brief Returns a reference to the component at the specified index.
             * \param idx The zero-based component index.
             * \return A reference to the component.
             */
            BasicMolecule& getComponent(std::size_t idx);

            /**
             * \brief Returns a \c const reference to the component at the given index within its reaction role.
             * \param idx The zero-based component index within the role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A \c const reference to the component.
             */
            const BasicMolecule& getComponent(std::size_t idx, unsigned int role) const;

            /**
             * \brief Returns a reference to the component at the given index within its reaction role.
             * \param idx The zero-based component index within the role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             * \return A reference to the component.
             */
            BasicMolecule& getComponent(std::size_t idx, unsigned int role);

            /**
             * \brief Adds a new empty component with the specified reaction role.
             * \param role The reaction role of the new component (see namespace Chem::ReactionRole).
             * \return A reference to the newly created component molecule.
             */
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

            /**
             * \brief Swaps the reaction roles of two component groups.
             * \param role1 The first reaction role.
             * \param role2 The second reaction role.
             */
            void swapComponentRoles(unsigned int role1, unsigned int role2);

            /**
             * \brief Removes the component at the specified index.
             * \param idx The zero-based component index.
             */
            void removeComponent(std::size_t idx);

            /**
             * \brief Removes the component at the given index within its reaction role.
             * \param idx The zero-based component index within the role.
             * \param role The reaction role (see namespace Chem::ReactionRole).
             */
            void removeComponent(std::size_t idx, unsigned int role);

            /**
             * \brief Removes the component referenced by the given iterator.
             * \param it Iterator referencing the component to remove.
             * \return A mutable iterator pointing to the component following the removed one.
             */
            ComponentIterator removeComponent(const ComponentIterator& it);

            /**
             * \brief Removes all components with the specified reaction role.
             * \param role The reaction role of the components to remove (see namespace Chem::ReactionRole).
             */
            void removeComponents(unsigned int role);

            /**
             * \brief Creates a deep copy of the reaction.
             * \return A smart pointer to the cloned reaction.
             */
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

            /**
             * \brief Replaces the current set of reaction components and properties by a copy of the
             *        components and properties of the reaction \a rxn.
             * \param rxn The reaction to copy.
             */
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

            const BasicMolecule& getReactant(std::size_t idx) const;
            BasicMolecule&       getReactant(std::size_t idx);

            const BasicMolecule& getAgent(std::size_t idx) const;
            BasicMolecule&       getAgent(std::size_t idx);

            const BasicMolecule& getProduct(std::size_t idx) const;
            BasicMolecule&       getProduct(std::size_t idx);

            void removeReactant(std::size_t idx);
            void removeAgent(std::size_t idx);
            void removeProduct(std::size_t idx);

            void removeReactants();
            void removeAgents();
            void removeProducts();

            BasicMolecule& addComponent(unsigned int role, const Molecule* mol);

            BasicMolecule& addReactant(const Molecule* mol);
            BasicMolecule& addAgent(const Molecule* mol);
            BasicMolecule& addProduct(const Molecule* mol);

            void clearComponents();

            void copyComponents(const BasicReaction& rxn);
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
