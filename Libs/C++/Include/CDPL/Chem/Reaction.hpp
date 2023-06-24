/* 
 * Reaction.hpp 
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
 * \brief Definition of the class CDPL::Chem::Reaction.
 */

#ifndef CDPL_CHEM_REACTION_HPP
#define CDPL_CHEM_REACTION_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/PropertyContainer.hpp"
#include "CDPL/Util/IndexedElementIterator.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;

        /**
         * \brief Reaction.
         */
        class CDPL_CHEM_API Reaction : public Base::PropertyContainer
        {

            class ConstComponentAccessor;
            class ComponentAccessor;

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Reaction instances.
             */
            typedef std::shared_ptr<Reaction> SharedPointer;

            /**
             * \brief A constant random access iterator used to iterate over the components of the reaction.
             */
            typedef Util::IndexedElementIterator<const Molecule, ConstComponentAccessor> ConstComponentIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the components of the reaction.
             */
            typedef Util::IndexedElementIterator<Molecule, ComponentAccessor> ComponentIterator;

            /**
             * \brief Virtual destructor.
             */
            virtual ~Reaction() {}

            /**
             * \brief Removes all components and clears all properties of the reaction.
             */
            virtual void clear() = 0;

            /**
             * \brief Returns the number of reaction components.
             * \return The number of reaction components.
             */
            virtual std::size_t getNumComponents() const = 0;

            /**
             * \brief Returns the number of reaction components with the specified role.
             * \param role A flag that specifies the reaction role (see namespace Chem::ReactionRole).
             * \return The number of reaction components with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual std::size_t getNumComponents(unsigned int role) const = 0;

            /**
             * \brief Returns the reaction role of the specified component.
             *
             * If the specified molecule is not a component of this reaction, Chem::ReactionRole::NONE will be returned.
             *
             * \param mol The component for which to return the reaction role.
             * \return A flag that specifies the reaction role of the component (see namespace Chem::ReactionRole).
             */
            virtual unsigned int getComponentRole(const Molecule& mol) const = 0;

            /**
             * \brief Returns the index of the specified reaction component.
             * \param mol The component for which to return the index.
             * \return The zero-based index of the specified reaction component.
             * \throw Base::ItemNotFound if the specified molecule is not a component of this reaction.
             */
            virtual std::size_t getComponentIndex(const Molecule& mol) const = 0;

            /**
             * \brief Tells whether the specified molecule is a component of this reaction.
             * \param mol The molecule to look for.
             * \return \c true if the specified molecule is a component of this reaction, and \c false otherwise.
             */
            virtual bool containsComponent(const Molecule& mol) const = 0;

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
             * \brief Returns a constant iterator pointing to the beginning of the reaction components.
             * \return A constant iterator pointing to the beginning of the reaction components.
             */
            ConstComponentIterator begin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the reaction components.
             * \return A mutable iterator pointing to the beginning of the reaction components.
             */
            ComponentIterator begin();

            /**
             * \brief Returns a constant iterator pointing to the end of the reaction components.
             * \return A constant iterator pointing to the end of the reaction components.
             */
            ConstComponentIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the reaction components.
             * \return A mutable iterator pointing to the end of the reaction components.
             */
            ComponentIterator end();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the reaction components
             *        with the specified role.
             * \param role A flag that specifies the reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing to the beginning of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ConstComponentIterator getComponentsBegin(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the reaction components
             *        with the specified role.
             * \param role A flag that specifies the reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing to the beginning of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ComponentIterator getComponentsBegin(unsigned int role);

            /**
             * \brief Returns a constant iterator pointing to the end of the reaction components
             *        with the specified role.
             * \param role A flag that specifies the reaction role (see namespace Chem::ReactionRole).
             * \return A constant iterator pointing to the end of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ConstComponentIterator getComponentsEnd(unsigned int role) const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the reaction components
             *        with the specified role.
             * \param role A flag that specifies the reaction role (see namespace Chem::ReactionRole).
             * \return A mutable iterator pointing to the end of the reaction components
             *         with the specified role.
             * \throw Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            ComponentIterator getComponentsEnd(unsigned int role);

            /**
             * \brief Returns a \c const reference to the reaction component at index \a idx.
             * \param idx The zero-based index of the reaction component to return.
             * \return A \c const reference to the reaction component at the specified index.
             * \throw Base::IndexError if the number of components is zero or \a idx is not in the range [0, getNumComponents() - 1].
             */
            virtual const Molecule& getComponent(std::size_t idx) const = 0;

            /**
             * \brief Returns a non-\c const reference to the reaction component at index \a idx.
             * \param idx The zero-based index of the reaction component to return.
             * \return A non-\c const reference to the reaction component at the specified index.
             * \throw Base::IndexError if the number of components is zero or \a idx is not in the range [0, getNumComponents() - 1].
             */
            virtual Molecule& getComponent(std::size_t idx) = 0;

            /**
             * \brief Returns a \c const reference to the reaction component at index \a idx in the list of components
             *        with the specified role.
             * \param idx The zero-based index of the reaction component to return.
             * \param role A flag indicating the reaction role of the component (see namespace Chem::ReactionRole).
             * \return A \c const reference to the reaction component with the specified role and index.
             * \throw Base::IndexError if the number of components with the specified role is zero or \a idx is not in the range
             *        [0, <tt>getNumComponents(role) - 1</tt>].
             *        Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual const Molecule& getComponent(std::size_t idx, unsigned int role) const = 0;

            /**
             * \brief Returns a non-\c const reference to the reaction component at index \a idx in the list of components
             *        with the specified role.
             * \param idx The zero-based index of the reaction component to return.
             * \param role A flag indicating the reaction role of the component (see namespace Chem::ReactionRole).
             * \return A non-\c const reference to the reaction component with the specified role and index.
             * \throw Base::IndexError if the number of components with the specified role is zero or \a idx is not in the range
             *        [0, <tt>getNumComponents(role) - 1</tt>].
             *        Base::ValueError if the value of \a role is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual Molecule& getComponent(std::size_t idx, unsigned int role) = 0;

            /**
             * \brief Creates a new reaction component with the specified role.
             * \param role A flag specifying the reaction role of the new component (see namespace Chem::ReactionRole).
             * \return A reference to the newly created component molecule.
             * \throw Base::ValueError if the value of \a role is not Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual Molecule& addComponent(unsigned int role) = 0;

            /**
             * \brief Swaps the reaction roles of the component sets specified by \a role1 and \a role2.
             *
             * If \a role1 is equal to \a role2, the method has no effect.
             *
             * \param role1 A flag specifying the reaction role of the first component set (see namespace Chem::ReactionRole).
             * \param role2 A flag specifying the reaction role of the second component set (see namespace Chem::ReactionRole).
             * \throw Base::ValueError if the value of \a role1 and/or \a role2 is not equal to Chem::ReactionRole::REACTANT, 
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual void swapComponentRoles(unsigned int role1, unsigned int role2) = 0;

            /**
             * \brief Removes the reaction component at the specified index.
             * \param idx The zero-based index of the component to remove.
             * \throw Base::IndexError if the number of components is zero or \a idx is not in the range [0, getNumComponents() - 1].
             */
            virtual void removeComponent(std::size_t idx) = 0;

            /**
             * \brief Removes the reaction component at index \a idx in the list of components with the specified role.
             * \param idx The zero-based index of the component to remove.
             * \param role The reaction role of the components
             * \throw Base::IndexError if the number of components with the specified role is zero or \a idx is not in the range 
             *        [0, <tt>getNumComponents(role) - 1</tt>].
             *        Base::ValueError if the value of \a role is not Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual void removeComponent(std::size_t idx, unsigned int role) = 0;

            /**
             * \brief Removes the reaction component specified by the iterator \a it.
             * \param it A mutable iterator that specifies the component to remove.
             * \return A mutable iterator pointing to the next reaction component in the list.
             * \throw Base::RangeError if the number of reaction components is zero or \a it is not in the range 
             *        [getComponentsBegin(), getComponentsEnd() - 1].
             */
            ComponentIterator removeComponent(const ComponentIterator& it);

            /**    
             * \brief Removes all components with the specified role.
             * \param role A flag specifying the reaction role of the components to remove (see namespace Chem::ReactionRole).
             * \throw Base::ValueError if the value of \a role is not Chem::ReactionRole::REACTANT,
             *        Chem::ReactionRole::AGENT or Chem::ReactionRole::PRODUCT.
             */
            virtual void removeComponents(unsigned int role) = 0;

            /**
             * \brief Creates a copy of the current reaction state.
             * \return A smart pointer to the copy of the reaction.
             */
            virtual SharedPointer clone() const = 0;

            /**
             * \brief Replaces the current set of reaction components and properties by a copy of the 
             *        components and properties of the reaction \a rxn.
             * \param rxn The reaction to copy.
             */
            virtual void copy(const Reaction& rxn) = 0;

            /**
             * \brief Replaces the current set of reaction components and properties by a copy of the 
             *        components and properties of the reaction \a rxn.
             *
             * Internally calls copy() to perform the actual work.
             *
             * \param rxn The reaction to copy.
             * \return A reference to itself.
             */
            Reaction& operator=(const Reaction& rxn);

          private:
            class CDPL_CHEM_API ConstComponentAccessor
            {

                friend class Reaction;

              public:
                ConstComponentAccessor(const ComponentAccessor& accessor):
                    reaction(accessor.reaction), compRole(accessor.compRole) {}
                ConstComponentAccessor(const Reaction* rxn, unsigned int role):
                    reaction(rxn), compRole(role) {}

                const Molecule& operator()(std::size_t idx) const;

                bool operator==(const ConstComponentAccessor& accessor) const;

              private:
                const Reaction* reaction;
                unsigned int    compRole;
            };

            class CDPL_CHEM_API ComponentAccessor
            {

                friend class Reaction;
                friend class ConstComponentAccessor;

              public:
                ComponentAccessor(Reaction* rxn, unsigned int role):
                    reaction(rxn), compRole(role) {}

                Molecule& operator()(std::size_t idx) const;

                bool operator==(const ComponentAccessor& accessor) const;

              private:
                Reaction*    reaction;
                unsigned int compRole;
            };
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTION_HPP
