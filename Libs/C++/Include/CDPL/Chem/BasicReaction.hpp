/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::Chem::BasicReaction.
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
		 * \brief BasicReaction.
		 */
		class CDPL_CHEM_API BasicReaction : public Reaction
		{

			typedef Util::ObjectPool<BasicMolecule> ComponentCache;
			typedef ComponentCache::SharedObjectPointer ComponentPtr;
			typedef std::vector<ComponentPtr> ComponentList;

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BasicReaction instances.
			 */
			typedef std::shared_ptr<BasicReaction> SharedPointer;

	
			typedef boost::indirect_iterator<ComponentList::iterator, BasicMolecule> ComponentIterator;
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
		
			unsigned int getComponentRole(const Molecule& mol) const;

			std::size_t getComponentIndex(const Molecule& mol) const;
	
			bool containsComponent(const Molecule& mol) const;

			void clear();

			std::size_t getNumComponents() const;
		
			std::size_t getNumComponents(unsigned int role) const;
				
			ConstComponentIterator getComponentsBegin() const;

			ComponentIterator getComponentsBegin();

			ConstComponentIterator getComponentsEnd() const;

			ComponentIterator getComponentsEnd();

			ConstComponentIterator getComponentsBegin(unsigned int role) const;

			ComponentIterator getComponentsBegin(unsigned int role);

			ConstComponentIterator getComponentsEnd(unsigned int role) const;

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
			ComponentIterator getReactantsBegin();

			ConstComponentIterator getReactantsEnd() const;
			ComponentIterator getReactantsEnd();

			ConstComponentIterator getAgentsBegin() const;
			ComponentIterator getAgentsBegin();

			ConstComponentIterator getAgentsEnd() const;
			ComponentIterator getAgentsEnd();

			ConstComponentIterator getProductsBegin() const;
			ComponentIterator getProductsBegin();

			ConstComponentIterator getProductsEnd() const;
			ComponentIterator getProductsEnd();

			const BasicMolecule& getReactant(std::size_t idx) const;
			BasicMolecule& getReactant(std::size_t idx);

			const BasicMolecule& getAgent(std::size_t idx) const;
			BasicMolecule& getAgent(std::size_t idx);

			const BasicMolecule& getProduct(std::size_t idx) const;
			BasicMolecule& getProduct(std::size_t idx);

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
	}
}

#endif // CDPL_CHEM_BASICREACTION_HPP
