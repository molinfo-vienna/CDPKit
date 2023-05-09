/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/ReactionProperties.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Chem/ReactionRoles.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(ReactionTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	Reaction rxn1;

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK_THROW(rxn1.getNumComponents(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn1.removeComponent(++rxn1.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponents(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	rxn1.removeComponents(ReactionRole::REACTANT);
	rxn1.removeComponents(ReactionRole::AGENT);
	rxn1.removeComponents(ReactionRole::PRODUCT);

//-----

	BOOST_CHECK_THROW(rxn1.addComponent(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	Molecule* reactant1 = &rxn1.addComponent(ReactionRole::REACTANT);
	Molecule* product1 = &rxn1.addComponent(ReactionRole::PRODUCT);
	Molecule* agent1 = &rxn1.addComponent(ReactionRole::AGENT);

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(&reactant1->getReaction() == &rxn1);
	BOOST_CHECK(&product1->getReaction() == &rxn1);
	BOOST_CHECK(&agent1->getReaction() == &rxn1);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 1);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 1);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 1);

	BOOST_CHECK(rxn1.getNumComponents() == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 1);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 1);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 1);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant1);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == agent1);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == product1);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant1);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 1 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == product1);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(3), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(1), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(1), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(3), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 3), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeReactant(1), IndexError);
	BOOST_CHECK_THROW(rxn1.removeAgent(1), IndexError);
	BOOST_CHECK_THROW(rxn1.removeProduct(1), IndexError);

//-----

	Molecule comp1, comp2, comp3;

	comp1.setProperty(MolecularGraphProperty::NAME, std::string("reactant"));
	comp2.setProperty(MolecularGraphProperty::NAME, std::string("agent"));
	comp3.setProperty(MolecularGraphProperty::NAME, std::string("product"));

	BOOST_CHECK(comp1.getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(comp2.getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(comp3.getProperty<std::string>(MolecularGraphProperty::NAME) == "product");

	Molecule* reactant2 = &rxn1.addComponent(ReactionRole::REACTANT, comp1);
	Molecule* agent2 = &rxn1.addComponent(ReactionRole::AGENT, comp2);
	Molecule* product2 = &rxn1.addComponent(ReactionRole::PRODUCT, comp3);

	BOOST_CHECK(reactant2 != &comp1);
	BOOST_CHECK(agent2 != &comp2);
	BOOST_CHECK(product2 != &comp3);

	BOOST_CHECK(reactant2->getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(agent2->getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(product2->getProperty<std::string>(MolecularGraphProperty::NAME) == "product");

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(reactant2->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product2->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent2->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(&reactant1->getReaction() == &rxn1);
	BOOST_CHECK(&product1->getReaction() == &rxn1);
	BOOST_CHECK(&agent1->getReaction() == &rxn1);

	BOOST_CHECK(&reactant2->getReaction() == &rxn1);
	BOOST_CHECK(&product2->getReaction() == &rxn1);
	BOOST_CHECK(&agent2->getReaction() == &rxn1);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 6);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 2);

	BOOST_CHECK(rxn1.getNumComponents() == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 2);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == agent2);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == product2);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 2 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(6), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(2), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(2), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(2), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(6), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 6), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeReactant(2), IndexError);
	BOOST_CHECK_THROW(rxn1.removeAgent(2), IndexError);
	BOOST_CHECK_THROW(rxn1.removeProduct(2), IndexError);

//-----

	Molecule* product3 = &rxn1.addProduct(comp3);
	Molecule* reactant3 = &rxn1.addReactant(comp1);
	Molecule* agent3 = &rxn1.addAgent(comp2);

	BOOST_CHECK(reactant3 != &comp1);
	BOOST_CHECK(agent3 != &comp2);
	BOOST_CHECK(product3 != &comp3);

	BOOST_CHECK(reactant3->getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(agent3->getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(product3->getProperty<std::string>(MolecularGraphProperty::NAME) == "product");

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(reactant2->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product2->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent2->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(reactant3->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product3->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent3->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(&reactant1->getReaction() == &rxn1);
	BOOST_CHECK(&product1->getReaction() == &rxn1);
	BOOST_CHECK(&agent1->getReaction() == &rxn1);

	BOOST_CHECK(&reactant2->getReaction() == &rxn1);
	BOOST_CHECK(&product2->getReaction() == &rxn1);
	BOOST_CHECK(&agent2->getReaction() == &rxn1);

	BOOST_CHECK(&reactant3->getReaction() == &rxn1);
	BOOST_CHECK(&product3->getReaction() == &rxn1);
	BOOST_CHECK(&agent3->getReaction() == &rxn1);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 9);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 3);

	BOOST_CHECK(rxn1.getNumComponents() == 9);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 3);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == agent3);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == product3);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 3 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == product3);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == product3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(9), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(9), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(3), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(3), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(3), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(9), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 9), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::PRODUCT), IndexError);

//-----

	Molecule* product4 = &rxn1.addProduct();
	Molecule* agent4 = &rxn1.addAgent();
	Molecule* reactant4 = &rxn1.addReactant();
	Molecule* product5 = &rxn1.addProduct();
	Molecule* product6 = &rxn1.addProduct();
	Molecule* reactant5 = &rxn1.addReactant();

	BOOST_CHECK_THROW(reactant4->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(reactant5->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(agent4->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(product4->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(product5->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(product6->getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(reactant4->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant5->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product4->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product5->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product6->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent4->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(&reactant4->getReaction() == &rxn1);
	BOOST_CHECK(&reactant5->getReaction() == &rxn1);
	BOOST_CHECK(&product4->getReaction() == &rxn1);
	BOOST_CHECK(&product5->getReaction() == &rxn1);
	BOOST_CHECK(&product6->getReaction() == &rxn1);
	BOOST_CHECK(&agent4->getReaction() == &rxn1);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 6);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == reactant5);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == agent4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 14) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 14) == product6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 4) == reactant5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 6 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 6 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 5) == product6);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(4) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(5), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(4), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(5) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(5) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(6), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapRoles(ReactionRole::REACTANT, ReactionRole::PRODUCT);

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant2->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant3->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant4->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant5->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product2->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product3->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product4->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product5->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product6->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent2->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent3->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent4->getReactionRole() == ReactionRole::AGENT);

	BOOST_CHECK(&reactant4->getReaction() == &rxn1);
	BOOST_CHECK(&reactant5->getReaction() == &rxn1);
	BOOST_CHECK(&product4->getReaction() == &rxn1);
	BOOST_CHECK(&product5->getReaction() == &rxn1);
	BOOST_CHECK(&product6->getReaction() == &rxn1);
	BOOST_CHECK(&agent4->getReaction() == &rxn1);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 6);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 5);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == product6);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9) == agent4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 14) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 14) == reactant5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 6 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 6 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5) == product6); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 6 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 6 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 5) == product6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 4) == reactant5);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == product6);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(9) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(9) == agent4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(6, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(6, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(4) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(5) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(5) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(6), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(4), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(4) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(5), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapRoles(ReactionRole::REACTANT, ReactionRole::AGENT);

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant2->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant3->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant4->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant5->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product2->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product3->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product4->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product5->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product6->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent2->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent3->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent4->getReactionRole() == ReactionRole::REACTANT);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 6);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 5);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == agent4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9) == product6);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 14) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 14) == reactant5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 6 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 6 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 5) == product6); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3) == agent4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 6 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 6 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 5) == product6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 4) == reactant5);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == agent4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(9) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(9) == product6);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::AGENT) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::AGENT) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(6, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(6, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(3) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(3) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(4), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(4) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(5) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(5) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(6), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(4) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(5), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapRoles(ReactionRole::PRODUCT, ReactionRole::AGENT);
	rxn1.swapRoles(ReactionRole::AGENT, ReactionRole::REACTANT);

	BOOST_CHECK(reactant1->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant2->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant3->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant4->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant5->getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent1->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent2->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent3->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent4->getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(product1->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product2->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product3->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product4->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product5->getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product6->getReactionRole() == ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 6);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == reactant5);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == agent4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 14) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 14) == product6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 4) == reactant5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3) == agent4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 6 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 6 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 5) == product6);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(3) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(3) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(4) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(4) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(5), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(3) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(4), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(5) == product6);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(5) == product6);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(6), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::PRODUCT), IndexError);

//-----

	rxn1.setProperty(ReactionProperty::NAME, std::string("reaction1"));

	BOOST_CHECK(rxn1.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");
	
	Reaction rxn2(rxn1);

	BOOST_CHECK(rxn2.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getReactant(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getReactant(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(rxn2.getReactant(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK_THROW(rxn2.getReactant(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getReactant(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getAgent(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getAgent(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(rxn2.getAgent(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK_THROW(rxn2.getAgent(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getProduct(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getProduct(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK(rxn2.getProduct(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK_THROW(rxn2.getProduct(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getProduct(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getProduct(5).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 6);

	BOOST_CHECK(rxn2.getNumComponents() == 15);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getReactant(4));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getAgent(3));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 9) == &rxn2.getProduct(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 9) == &rxn2.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 10) == &rxn2.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 10) == &rxn2.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 11) == &rxn2.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 11) == &rxn2.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 12) == &rxn2.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 12) == &rxn2.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 13) == &rxn2.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 13) == &rxn2.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 14) == &rxn2.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 14) == &rxn2.getProduct(5));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getReactant(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getReactant(4)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn2.getProduct(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn2.getProduct(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn2.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn2.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn2.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn2.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn2.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn2.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn2.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn2.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn2.getProduct(5)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn2.getProduct(5)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn2).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn2).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getReactantsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getReactantsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 4) == &rxn2.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 4) == &rxn2.getReactant(4));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn2).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn2).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getProductsBegin() + 6 == 
				const_cast<const Reaction&>(rxn2).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getProductsBegin() + 6 == 
				const_cast<Reaction&>(rxn2).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getProductsBegin() == &rxn2.getProduct(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getProductsBegin() == &rxn2.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getProductsBegin() + 1) == &rxn2.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getProductsBegin() + 1) == &rxn2.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getProductsBegin() + 2) == &rxn2.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getProductsBegin() + 2) == &rxn2.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getProductsBegin() + 3) == &rxn2.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getProductsBegin() + 3) == &rxn2.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getProductsBegin() + 4) == &rxn2.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getProductsBegin() + 4) == &rxn2.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getProductsBegin() + 5) == &rxn2.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getProductsBegin() + 5) == &rxn2.getProduct(5));

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(4) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(4) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(5) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(5) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(6) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(6) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(7) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(7) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(8) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(8) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(9) == &rxn2.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(9) == &rxn2.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(10) == &rxn2.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(10) == &rxn2.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(11) == &rxn2.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(11) == &rxn2.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(12) == &rxn2.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(12) == &rxn2.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(13) == &rxn2.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(13) == &rxn2.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(14) == &rxn2.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(14) == &rxn2.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::REACTANT) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::REACTANT) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::REACTANT) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::REACTANT) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::REACTANT) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::REACTANT) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::REACTANT) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::REACTANT) == &rxn2.getReactant(4));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT) == &rxn2.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT) == &rxn2.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::PRODUCT) == &rxn2.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::PRODUCT) == &rxn2.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::PRODUCT) == &rxn2.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::PRODUCT) == &rxn2.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::PRODUCT) == &rxn2.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::PRODUCT) == &rxn2.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::PRODUCT) == &rxn2.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::PRODUCT) == &rxn2.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(5, ReactionRole::PRODUCT) == &rxn2.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(5, ReactionRole::PRODUCT) == &rxn2.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getReactant(5), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getAgent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getProduct(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getProduct(6), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(6, ReactionRole::PRODUCT), IndexError);

//-----

	Reaction rxn3;

	rxn3 = rxn1;

	BOOST_CHECK(rxn3.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK_THROW(rxn3.getReactant(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getReactant(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(rxn3.getReactant(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK_THROW(rxn3.getReactant(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getReactant(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getAgent(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getAgent(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(rxn3.getAgent(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK_THROW(rxn3.getAgent(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getProduct(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getProduct(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK(rxn3.getProduct(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK_THROW(rxn3.getProduct(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getProduct(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getProduct(5).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 6);

	BOOST_CHECK(rxn3.getNumComponents() == 15);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getReactant(4));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getAgent(3));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getProduct(5));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getReactant(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getReactant(4)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getAgent(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getAgent(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getProduct(5)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getProduct(5)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn3).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn3).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 4) == &rxn3.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 4) == &rxn3.getReactant(4));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn3).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn3).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 2) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 2) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 3) == &rxn3.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 3) == &rxn3.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getProductsBegin() + 6 == 
				const_cast<const Reaction&>(rxn3).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getProductsBegin() + 6 == 
				const_cast<Reaction&>(rxn3).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 4) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 4) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 5) == &rxn3.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 5) == &rxn3.getProduct(5));

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(5) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(5) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(6) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(6) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(7) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(7) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(8) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(8) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(9) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(9) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(10) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(10) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(11) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(11) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(12) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(12) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(13) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(13) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(14) == &rxn3.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(14) == &rxn3.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::REACTANT) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::REACTANT) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::REACTANT) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::REACTANT) == &rxn3.getReactant(4));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::AGENT) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::AGENT) == &rxn3.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(5, ReactionRole::PRODUCT) == &rxn3.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(5, ReactionRole::PRODUCT) == &rxn3.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(5), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(6), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn3 = rxn3;

	BOOST_CHECK(rxn3.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK_THROW(rxn3.getReactant(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getReactant(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(rxn3.getReactant(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK_THROW(rxn3.getReactant(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getReactant(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getAgent(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getAgent(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(rxn3.getAgent(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK_THROW(rxn3.getAgent(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getProduct(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn3.getProduct(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK(rxn3.getProduct(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "product");
	BOOST_CHECK_THROW(rxn3.getProduct(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getProduct(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getProduct(5).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 15);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 6);

	BOOST_CHECK(rxn3.getNumComponents() == 15);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getReactant(4));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getAgent(3));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getProduct(5));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getReactant(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getReactant(4)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getAgent(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getAgent(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getProduct(4)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getProduct(5)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getProduct(5)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn3).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn3).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 2) == &rxn3.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 3) == &rxn3.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 4) == &rxn3.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 4) == &rxn3.getReactant(4));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn3).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn3).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 2) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 2) == &rxn3.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 3) == &rxn3.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 3) == &rxn3.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getProductsBegin() + 6 == 
				const_cast<const Reaction&>(rxn3).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getProductsBegin() + 6 == 
				const_cast<Reaction&>(rxn3).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 4) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 4) == &rxn3.getProduct(4));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 5) == &rxn3.getProduct(5));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 5) == &rxn3.getProduct(5));

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(5) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(5) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(6) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(6) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(7) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(7) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(8) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(8) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(9) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(9) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(10) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(10) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(11) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(11) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(12) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(12) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(13) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(13) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(14) == &rxn3.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(14) == &rxn3.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT) == &rxn3.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::REACTANT) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::REACTANT) == &rxn3.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::REACTANT) == &rxn3.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::REACTANT) == &rxn3.getReactant(4));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT) == &rxn3.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::AGENT) == &rxn3.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::AGENT) == &rxn3.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT) == &rxn3.getProduct(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(5, ReactionRole::PRODUCT) == &rxn3.getProduct(5));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(5, ReactionRole::PRODUCT) == &rxn3.getProduct(5));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(5), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(6), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(6), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn3.clear();

	BOOST_CHECK(rxn3.getNumProperties() == 0);

	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn3.getNumComponents() == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin() == 
				const_cast<Reaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn3).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getReactantsBegin() == 
				const_cast<Reaction&>(rxn3).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn3).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getAgentsBegin() == 
				const_cast<Reaction&>(rxn3).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getProductsBegin() == 
				const_cast<const Reaction&>(rxn3).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getProductsBegin() == 
				const_cast<Reaction&>(rxn3).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(1), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn3.removeComponent(++rxn3.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeReactant(0), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeAgent(0), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeProduct(0), IndexError);

	rxn3.removeComponents(ReactionRole::REACTANT);
	rxn3.removeComponents(ReactionRole::AGENT);
	rxn3.removeComponents(ReactionRole::PRODUCT);

//-----

	rxn2.removeComponents(ReactionRole::PRODUCT);
	
	BOOST_CHECK(rxn2.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getReactant(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getReactant(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK(rxn2.getReactant(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "reactant");
	BOOST_CHECK_THROW(rxn2.getReactant(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getReactant(4).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getAgent(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getAgent(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(rxn2.getAgent(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK_THROW(rxn2.getAgent(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 9);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 5);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn2.getNumComponents() == 9);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 9 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin() + 9 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getReactant(4));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getReactant(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getReactant(3)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getReactant(4)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getReactant(4)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 5 == 
				const_cast<const Reaction&>(rxn2).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getReactantsBegin() + 5 == 
				const_cast<Reaction&>(rxn2).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getReactantsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getReactantsBegin() == &rxn2.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 1) == &rxn2.getReactant(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 2) == &rxn2.getReactant(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 3) == &rxn2.getReactant(3));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getReactantsBegin() + 4) == &rxn2.getReactant(4));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getReactantsBegin() + 4) == &rxn2.getReactant(4));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn2).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn2).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getProductsBegin() + 0 == 
				const_cast<const Reaction&>(rxn2).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getProductsBegin() + 0 == 
				const_cast<Reaction&>(rxn2).getProductsEnd());

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(4) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(4) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(5) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(5) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(6) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(6) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(7) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(7) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(8) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(8) == &rxn2.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(9), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(9), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT) == &rxn2.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::REACTANT) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::REACTANT) == &rxn2.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::REACTANT) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::REACTANT) == &rxn2.getReactant(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::REACTANT) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::REACTANT) == &rxn2.getReactant(3));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::REACTANT) == &rxn2.getReactant(4));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::REACTANT) == &rxn2.getReactant(4));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getReactant(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getReactant(5), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getAgent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getProduct(0), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(9), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 9), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	rxn2.removeComponents(ReactionRole::REACTANT);
	
	BOOST_CHECK(rxn2.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getAgent(0).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);
	BOOST_CHECK(rxn2.getAgent(1).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK(rxn2.getAgent(2).getProperty<std::string>(MolecularGraphProperty::NAME) == "agent");
	BOOST_CHECK_THROW(rxn2.getAgent(3).getProperty(MolecularGraphProperty::NAME, true, false), ItemNotFound);

	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn2.getNumComponents() == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin() + 4 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getAgent(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getAgent(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn2).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getReactantsBegin() == 
				const_cast<Reaction&>(rxn2).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<const Reaction&>(rxn2).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getAgentsBegin() + 4 == 
				const_cast<Reaction&>(rxn2).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn2).getAgentsBegin() == &rxn2.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 1) == &rxn2.getAgent(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 2) == &rxn2.getAgent(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn2).getAgentsBegin() + 3) == &rxn2.getAgent(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getProductsBegin()  == 
				const_cast<const Reaction&>(rxn2).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getProductsBegin()  == 
				const_cast<Reaction&>(rxn2).getProductsEnd());

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3) == &rxn2.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT) == &rxn2.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(1, ReactionRole::AGENT) == &rxn2.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(2, ReactionRole::AGENT) == &rxn2.getAgent(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn2).getComponent(3, ReactionRole::AGENT) == &rxn2.getAgent(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getReactant(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getAgent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getAgent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getProduct(0), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(4), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 4), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn2.removeReactant(0), IndexError);
	BOOST_CHECK_THROW(rxn2.removeAgent(4), IndexError);
	BOOST_CHECK_THROW(rxn2.removeProduct(0), IndexError);
	
//-----

	rxn2.removeComponents(ReactionRole::AGENT);
	
	BOOST_CHECK(rxn2.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn2.getNumComponents() == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin()  == 
				const_cast<Reaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn2).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getReactantsBegin() == 
				const_cast<Reaction&>(rxn2).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn2).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getAgentsBegin() == 
				const_cast<Reaction&>(rxn2).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn2).getProductsBegin()  == 
				const_cast<const Reaction&>(rxn2).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn2).getProductsBegin()  == 
				const_cast<Reaction&>(rxn2).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getReactant(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getAgent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn2).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn2).getProduct(0), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	Reaction rxn4(rxn1);

	Reaction::ComponentIterator it = rxn1.removeComponent(rxn1.getComponentsBegin());

	BOOST_CHECK(it == rxn1.getComponentsBegin());

	it = rxn1.removeComponent(rxn1.getAgentsBegin());

	BOOST_CHECK(it == rxn1.getAgentsBegin());

	it = rxn1.removeComponent(--rxn1.getComponentsEnd());

	BOOST_CHECK(it == rxn1.getComponentsEnd());

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 12);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 5);

	BOOST_CHECK(rxn1.getNumComponents() == 12);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 12 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 12 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant2);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == reactant5);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == agent4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 9) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 9) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 10) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 10) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 11) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 11) == product5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant2); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant2);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 3) == reactant5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 3) == reactant5);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 3 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 3 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent2);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2) == agent4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2) == agent4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 5 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 4) == product5);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == reactant5);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == agent4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(8) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(8) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(9) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(9) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(10) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(10) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(11) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(11) == product5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(12), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(12), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(2) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(2) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(3) == reactant5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(3) == reactant5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(4), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(2) == agent4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(2) == agent4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(3), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(3), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(4) == product5);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(5), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(5), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(12), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 12), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);

//-----

	rxn1.removeComponent(0);
	rxn1.removeComponent(2, ReactionRole::REACTANT);
	rxn1.removeAgent(2);
	rxn1.removeComponent(4, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 8);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 4);

	BOOST_CHECK(rxn1.getNumComponents() == 8);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 8 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() + 8 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin() == reactant3);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin() == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 1) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 1) == reactant4);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 2) == agent2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 2) == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 3) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 3) == agent3);

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin() + 7) == product4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant3); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 2 == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() + 2 == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getReactantsBegin() == reactant3);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getReactantsBegin() == reactant3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getReactantsBegin() + 1) == reactant4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getReactantsBegin() + 1) == reactant4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 2 == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() + 2 == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getAgentsBegin() == agent2);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getAgentsBegin() == agent2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getAgentsBegin() + 1) == agent3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getAgentsBegin() + 1) == agent3);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() + 4 == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() + 4 == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*const_cast<Reaction&>(rxn1).getProductsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn1).getProductsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn1).getProductsBegin() + 3) == product4);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1) == reactant4);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3) == agent3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(8), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(0) == reactant3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(0) == reactant3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getReactant(1) == reactant4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getReactant(1) == reactant4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(2), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(0) == agent2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(0) == agent2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getAgent(1) == agent3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getAgent(1) == agent3);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(2), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(0) == product1);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(1) == product2);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(2) == product3);
	BOOST_CHECK(&const_cast<const Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK(&const_cast<Reaction&>(rxn1).getProduct(3) == product4);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(4), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeReactant(2), IndexError);
	BOOST_CHECK_THROW(rxn1.removeAgent(2), IndexError);
	BOOST_CHECK_THROW(rxn1.removeProduct(4), IndexError);

//-----

	BOOST_CHECK(rxn3.getNumComponents() == 0);

	rxn3 = rxn1;

	BOOST_CHECK(rxn3.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 8);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 2);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 2);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 4);

	BOOST_CHECK(rxn3.getNumComponents() == 8);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 8 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin() + 8 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getReactant(1));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getAgent(1));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getProduct(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getReactant(1)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getAgent(1)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getProduct(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getProduct(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 2 == 
				const_cast<const Reaction&>(rxn3).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getReactantsBegin() + 2 == 
				const_cast<Reaction&>(rxn3).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getReactantsBegin() == &rxn3.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getReactantsBegin() + 1) == &rxn3.getReactant(1));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 2 == 
				const_cast<const Reaction&>(rxn3).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getAgentsBegin() + 2 == 
				const_cast<Reaction&>(rxn3).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getAgentsBegin() == &rxn3.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getAgentsBegin() + 1) == &rxn3.getAgent(1));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getProductsBegin() + 4 == 
				const_cast<const Reaction&>(rxn3).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getProductsBegin() + 4 == 
				const_cast<Reaction&>(rxn3).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn3).getProductsBegin() == &rxn3.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 1) == &rxn3.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 2) == &rxn3.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn3).getProductsBegin() + 3) == &rxn3.getProduct(3));

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(4) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(4) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(5) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(5) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(6) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(6) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(7) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(7) == &rxn3.getProduct(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(8), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT) == &rxn3.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::REACTANT) == &rxn3.getReactant(1));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT) == &rxn3.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::AGENT) == &rxn3.getAgent(1));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT) == &rxn3.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT) == &rxn3.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(2, ReactionRole::PRODUCT) == &rxn3.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn3).getComponent(3, ReactionRole::PRODUCT) == &rxn3.getProduct(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(2), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(2), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(4), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn4.getNumComponents() == 15);

	rxn4 = rxn1;

	BOOST_CHECK(rxn4.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK(rxn4.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 8);
	BOOST_CHECK(rxn4.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 2);
	BOOST_CHECK(rxn4.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 2);
	BOOST_CHECK(rxn4.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 4);

	BOOST_CHECK(rxn4.getNumComponents() == 8);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 8 == 
				const_cast<const Reaction&>(rxn4).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getComponentsBegin() + 8 == 
				const_cast<Reaction&>(rxn4).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getComponentsBegin() == &rxn4.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getComponentsBegin() == &rxn4.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 1) == &rxn4.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 1) == &rxn4.getReactant(1));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 2) == &rxn4.getAgent(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 2) == &rxn4.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 3) == &rxn4.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 3) == &rxn4.getAgent(1));

	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 4) == &rxn4.getProduct(0));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 4) == &rxn4.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 5) == &rxn4.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 5) == &rxn4.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 6) == &rxn4.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 6) == &rxn4.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin() + 7) == &rxn4.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin() + 7) == &rxn4.getProduct(3));

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const Reaction&>(rxn4).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<Reaction&>(rxn4).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) == &rxn4.getReactant(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) == &rxn4.getReactant(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn4.getReactant(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn4.getReactant(1)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const Reaction&>(rxn4).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<Reaction&>(rxn4).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) == &rxn4.getAgent(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) == &rxn4.getAgent(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn4.getAgent(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn4.getAgent(1)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const Reaction&>(rxn4).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<Reaction&>(rxn4).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) == &rxn4.getProduct(0)); 
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) == &rxn4.getProduct(0)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn4.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn4.getProduct(1)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn4.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn4.getProduct(2)); 
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn4.getProduct(3)); 
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn4.getProduct(3)); 

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getReactantsBegin() + 2 == 
				const_cast<const Reaction&>(rxn4).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getReactantsBegin() + 2 == 
				const_cast<Reaction&>(rxn4).getReactantsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getReactantsBegin() == &rxn4.getReactant(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getReactantsBegin() == &rxn4.getReactant(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getReactantsBegin() + 1) == &rxn4.getReactant(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getReactantsBegin() + 1) == &rxn4.getReactant(1));

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getAgentsBegin() + 2 == 
				const_cast<const Reaction&>(rxn4).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getAgentsBegin() + 2 == 
				const_cast<Reaction&>(rxn4).getAgentsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getAgentsBegin() == &rxn4.getAgent(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getAgentsBegin() == &rxn4.getAgent(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getAgentsBegin() + 1) == &rxn4.getAgent(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getAgentsBegin() + 1) == &rxn4.getAgent(1));

	BOOST_CHECK(const_cast<const Reaction&>(rxn4).getProductsBegin() + 4 == 
				const_cast<const Reaction&>(rxn4).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn4).getProductsBegin() + 4 == 
				const_cast<Reaction&>(rxn4).getProductsEnd());

	BOOST_CHECK(&*const_cast<const Reaction&>(rxn4).getProductsBegin() == &rxn4.getProduct(0));
	BOOST_CHECK(&*const_cast<Reaction&>(rxn4).getProductsBegin() == &rxn4.getProduct(0));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getProductsBegin() + 1) == &rxn4.getProduct(1));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getProductsBegin() + 1) == &rxn4.getProduct(1));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getProductsBegin() + 2) == &rxn4.getProduct(2));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getProductsBegin() + 2) == &rxn4.getProduct(2));
	BOOST_CHECK(&*(const_cast<const Reaction&>(rxn4).getProductsBegin() + 3) == &rxn4.getProduct(3));
	BOOST_CHECK(&*(const_cast<Reaction&>(rxn4).getProductsBegin() + 3) == &rxn4.getProduct(3));

	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(0) == &rxn4.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(0) == &rxn4.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(1) == &rxn4.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(1) == &rxn4.getReactant(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(2) == &rxn4.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(2) == &rxn4.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(3) == &rxn4.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(3) == &rxn4.getAgent(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(4) == &rxn4.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(4) == &rxn4.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(5) == &rxn4.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(5) == &rxn4.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(6) == &rxn4.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(6) == &rxn4.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(7) == &rxn4.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(7) == &rxn4.getProduct(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getComponent(8), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(0, ReactionRole::REACTANT) == &rxn4.getReactant(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(0, ReactionRole::REACTANT) == &rxn4.getReactant(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(1, ReactionRole::REACTANT) == &rxn4.getReactant(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(1, ReactionRole::REACTANT) == &rxn4.getReactant(1));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(0, ReactionRole::AGENT) == &rxn4.getAgent(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(0, ReactionRole::AGENT) == &rxn4.getAgent(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(1, ReactionRole::AGENT) == &rxn4.getAgent(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(1, ReactionRole::AGENT) == &rxn4.getAgent(1));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(0, ReactionRole::PRODUCT) == &rxn4.getProduct(0));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(0, ReactionRole::PRODUCT) == &rxn4.getProduct(0));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(1, ReactionRole::PRODUCT) == &rxn4.getProduct(1));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(1, ReactionRole::PRODUCT) == &rxn4.getProduct(1));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(2, ReactionRole::PRODUCT) == &rxn4.getProduct(2));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(2, ReactionRole::PRODUCT) == &rxn4.getProduct(2));
	BOOST_CHECK(&const_cast<const Reaction&>(rxn4).getComponent(3, ReactionRole::PRODUCT) == &rxn4.getProduct(3));
	BOOST_CHECK(&const_cast<Reaction&>(rxn4).getComponent(3, ReactionRole::PRODUCT) == &rxn4.getProduct(3));
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getReactant(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getReactant(2), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getAgent(2), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getAgent(2), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn4).getProduct(4), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn4).getProduct(4), IndexError);

	BOOST_CHECK_THROW(rxn4.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn4.removeComponent(rxn4.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn4.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn4.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn4.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	rxn3 = Reaction();

	BOOST_CHECK(rxn3.getNumProperties() == 0);

	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn3.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn3.getNumComponents() == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin()  == 
				const_cast<Reaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn3).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getReactantsBegin() == 
				const_cast<Reaction&>(rxn3).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn3).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getAgentsBegin() == 
				const_cast<Reaction&>(rxn3).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn3).getProductsBegin()  == 
				const_cast<const Reaction&>(rxn3).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn3).getProductsBegin()  == 
				const_cast<Reaction&>(rxn3).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getReactant(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getAgent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn3).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn3).getProduct(0), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	while (rxn1.getNumReactants() > 0)
		rxn1.removeReactant(0);

	while (rxn1.getNumAgents() > 0)
		rxn1.removeAgent(0);

	while (rxn1.getNumProducts() > 0)
		rxn1.removeProduct(0);

	BOOST_CHECK(rxn1.getProperty<std::string>(ReactionProperty::NAME) == "reaction1");

	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin() == 
				const_cast<Reaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn1).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getReactantsBegin() == 
				const_cast<Reaction&>(rxn1).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn1).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getAgentsBegin() == 
				const_cast<Reaction&>(rxn1).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn1).getProductsBegin() == 
				const_cast<const Reaction&>(rxn1).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn1).getProductsBegin() == 
				const_cast<Reaction&>(rxn1).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getReactant(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getReactant(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getAgent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getAgent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn1).getProduct(1), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn1).getProduct(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn1.removeComponent(++rxn1.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeReactant(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeAgent(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeProduct(1), IndexError);

//-----

	for (std::size_t i = 0; i < 15; i++)
		BOOST_CHECK(rxn1.addComponent(ReactionRole::AGENT).getNumProperties() == 0);

//-----

	Reaction rxn5 = Reaction();

	BOOST_CHECK(rxn5.getNumProperties() == 0);

	BOOST_CHECK(rxn5.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);
	BOOST_CHECK(rxn5.getProperty<std::size_t>(ReactionProperty::REACTANT_COUNT) == 0);
	BOOST_CHECK(rxn5.getProperty<std::size_t>(ReactionProperty::AGENT_COUNT) == 0);
	BOOST_CHECK(rxn5.getProperty<std::size_t>(ReactionProperty::PRODUCT_COUNT) == 0);

	BOOST_CHECK(rxn5.getNumComponents() == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getComponentsBegin() == 
				const_cast<const Reaction&>(rxn5).getComponentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getComponentsBegin()  == 
				const_cast<Reaction&>(rxn5).getComponentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const Reaction&>(rxn5).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<Reaction&>(rxn5).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const Reaction&>(rxn5).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<Reaction&>(rxn5).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const Reaction&>(rxn5).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<Reaction&>(rxn5).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getReactantsBegin() == 
				const_cast<const Reaction&>(rxn5).getReactantsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getReactantsBegin() == 
				const_cast<Reaction&>(rxn5).getReactantsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getAgentsBegin() == 
				const_cast<const Reaction&>(rxn5).getAgentsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getAgentsBegin() == 
				const_cast<Reaction&>(rxn5).getAgentsEnd());

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getProductsBegin()  == 
				const_cast<const Reaction&>(rxn5).getProductsEnd());
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getProductsBegin()  == 
				const_cast<Reaction&>(rxn5).getProductsEnd());

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getReactant(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getReactant(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getAgent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getAgent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const Reaction&>(rxn5).getProduct(0), IndexError);
	BOOST_CHECK_THROW(const_cast<Reaction&>(rxn5).getProduct(0), IndexError);

	BOOST_CHECK_THROW(rxn5.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn5.removeComponent(rxn5.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn5.getNumComponents() == 0);

	rxn5.addReactant();
	rxn5.addProduct();
	rxn5.addAgent();
	rxn5.addComponent(ReactionRole::AGENT);

	BOOST_CHECK(rxn5.getNumComponents() == 4);

	BOOST_CHECK(const_cast<const Reaction&>(rxn5).getComponentsEnd() - 
				const_cast<const Reaction&>(rxn5).getComponentsBegin() == 4);
	BOOST_CHECK(const_cast<Reaction&>(rxn5).getComponentsEnd() - 
				const_cast<Reaction&>(rxn5).getComponentsBegin() == 4);

	it = rxn5.removeComponent(rxn5.getComponentsBegin());

	BOOST_CHECK(it == rxn5.getComponentsBegin());

	it = rxn5.removeComponent(rxn5.getComponentsBegin() + 1);

	BOOST_CHECK(it == rxn5.getComponentsBegin() + 1);

	it = rxn5.removeComponent(--rxn5.getComponentsEnd());

	BOOST_CHECK(it == rxn5.getComponentsEnd());

	it = rxn5.removeComponent(rxn5.getComponentsBegin());

	BOOST_CHECK(it == rxn5.getComponentsEnd());
}
