/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicReactionTest.cpp 
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

#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/LookupKey.hpp"


BOOST_AUTO_TEST_CASE(BasicReactionTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	LookupKey prop_key1 = LookupKey::create("key1"); 
	LookupKey prop_key2 = LookupKey::create("key2"); 

	BasicMolecule no_comp;

//-----	

	BasicReaction rxn1;

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK_THROW(rxn1.getNumComponents(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

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

	BOOST_CHECK(rxn1.getComponentRole(no_comp) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(no_comp));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(no_comp), ItemNotFound);

//-----

	Reaction::SharedPointer rxn1_clone1_ptr = rxn1.clone();
	BasicReaction& rxn1_clone1 = static_cast<BasicReaction&>(*rxn1_clone1_ptr);

	BOOST_CHECK(rxn1_clone1.getNumComponents() == 0);
	BOOST_CHECK(rxn1_clone1.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn1_clone1.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn1_clone1.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK_THROW(rxn1_clone1.getNumComponents(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(rxn1_clone1.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(++rxn1_clone1.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(0, ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(rxn1_clone1.removeComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1_clone1.removeComponents(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	rxn1_clone1.removeComponents(ReactionRole::REACTANT);
	rxn1_clone1.removeComponents(ReactionRole::AGENT);
	rxn1_clone1.removeComponents(ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1_clone1.getComponentRole(no_comp) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1_clone1.containsComponent(no_comp));
	BOOST_CHECK_THROW(rxn1_clone1.getComponentIndex(no_comp), ItemNotFound);

//-----

	BOOST_CHECK_THROW(rxn1.addComponent(ReactionRole::PRODUCT | ReactionRole::REACTANT), ValueError);

	BasicMolecule* reactant1 = &rxn1.addComponent(ReactionRole::REACTANT);
	BasicMolecule* product1 = &rxn1.addComponent(ReactionRole::PRODUCT);
	BasicMolecule* agent1 = &rxn1.addComponent(ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.containsComponent(*reactant1));
	BOOST_CHECK(rxn1.containsComponent(*product1));
	BOOST_CHECK(rxn1.containsComponent(*agent1));

	BOOST_CHECK(rxn1.getComponentIndex(*reactant1) == 0);
	BOOST_CHECK(rxn1.getComponentIndex(*product1) == 2);
	BOOST_CHECK(rxn1.getComponentIndex(*agent1) == 1);

	BOOST_CHECK(rxn1.getNumComponents() == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 1);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 1);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 1);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant1);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == agent1);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == product1);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == product1);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(3), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(3), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 3), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK(rxn1.getComponentRole(no_comp) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(no_comp));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(no_comp), ItemNotFound);

//-----

	BasicMolecule comp1, comp2, comp3;

	comp1.setProperty(prop_key1, std::string("reactant"));
	comp2.setProperty(prop_key1, std::string("agent"));
	comp3.setProperty(prop_key1, std::string("product"));

	BOOST_CHECK(comp1.getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(comp2.getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(comp3.getProperty<std::string>(prop_key1) == "product");

	BasicMolecule* reactant2 = &rxn1.addComponent(ReactionRole::REACTANT, comp1);
	BasicMolecule* agent2 = &rxn1.addComponent(ReactionRole::AGENT, comp2);
	BasicMolecule* product2 = &rxn1.addComponent(ReactionRole::PRODUCT, comp3);

	BOOST_CHECK(reactant2 != &comp1);
	BOOST_CHECK(agent2 != &comp2);
	BOOST_CHECK(product2 != &comp3);

	BOOST_CHECK(reactant2->getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(agent2->getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(product2->getProperty<std::string>(prop_key1) == "product");

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant2) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product2) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent2) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.containsComponent(*reactant1));
	BOOST_CHECK(rxn1.containsComponent(*product1));
	BOOST_CHECK(rxn1.containsComponent(*agent1));

	BOOST_CHECK(rxn1.containsComponent(*reactant2));
	BOOST_CHECK(rxn1.containsComponent(*product2));
	BOOST_CHECK(rxn1.containsComponent(*agent2));

	BOOST_CHECK(rxn1.getComponentIndex(*reactant1) == 0);
	BOOST_CHECK(rxn1.getComponentIndex(*product1) == 4);
	BOOST_CHECK(rxn1.getComponentIndex(*agent1) == 2);

	BOOST_CHECK(rxn1.getComponentIndex(*reactant2) == 1);
	BOOST_CHECK(rxn1.getComponentIndex(*product2) == 5);
	BOOST_CHECK(rxn1.getComponentIndex(*agent2) == 3);

	BOOST_CHECK(rxn1.getComponentRole(comp1) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(comp1));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(comp1), ItemNotFound);

	BOOST_CHECK(rxn1.getComponentRole(comp2) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(comp2));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(comp2), ItemNotFound);

	BOOST_CHECK(rxn1.getComponentRole(comp3) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(comp3));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(comp3), ItemNotFound);

	BOOST_CHECK(rxn1.getNumComponents() == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 2);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent2);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(6), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(6), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(6), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 6), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::PRODUCT), IndexError);

//-----

	BasicMolecule* product3 = &rxn1.addComponent(ReactionRole::PRODUCT, comp3);
	BasicMolecule* reactant3 = &rxn1.addComponent(ReactionRole::REACTANT,  comp1);
	BasicMolecule* agent3 = &rxn1.addComponent(ReactionRole::AGENT, comp2);

	BOOST_CHECK(reactant3 != &comp1);
	BOOST_CHECK(agent3 != &comp2);
	BOOST_CHECK(product3 != &comp3);

	BOOST_CHECK(reactant3->getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(agent3->getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(product3->getProperty<std::string>(prop_key1) == "product");

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant2) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product2) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent2) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant3) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product3) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent3) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.containsComponent(*reactant1));
	BOOST_CHECK(rxn1.containsComponent(*product1));
	BOOST_CHECK(rxn1.containsComponent(*agent1));

	BOOST_CHECK(rxn1.containsComponent(*reactant2));
	BOOST_CHECK(rxn1.containsComponent(*product2));
	BOOST_CHECK(rxn1.containsComponent(*agent2));

	BOOST_CHECK(rxn1.containsComponent(*reactant3));
	BOOST_CHECK(rxn1.containsComponent(*product3));
	BOOST_CHECK(rxn1.containsComponent(*agent3));

	BOOST_CHECK(rxn1.getComponentIndex(*reactant1) == 0);
	BOOST_CHECK(rxn1.getComponentIndex(*product1) == 6);
	BOOST_CHECK(rxn1.getComponentIndex(*agent1) == 3);

	BOOST_CHECK(rxn1.getComponentIndex(*reactant2) == 1);
	BOOST_CHECK(rxn1.getComponentIndex(*product2) == 7);
	BOOST_CHECK(rxn1.getComponentIndex(*agent2) == 4);

	BOOST_CHECK(rxn1.getComponentIndex(*reactant3) == 2);
	BOOST_CHECK(rxn1.getComponentIndex(*product3) == 8);
	BOOST_CHECK(rxn1.getComponentIndex(*agent3) == 5);

	BOOST_CHECK(rxn1.getNumComponents() == 9);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 3);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent3);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == product3);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == product3);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(9), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(9), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(9), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 9), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::PRODUCT), IndexError);

//-----

	BasicMolecule* product4 = &rxn1.addComponent(ReactionRole::PRODUCT);
	BasicMolecule* agent4 = &rxn1.addComponent(ReactionRole::AGENT);
	BasicMolecule* reactant4 = &rxn1.addComponent(ReactionRole::REACTANT);
	BasicMolecule* product5 = &rxn1.addComponent(ReactionRole::PRODUCT);
	BasicMolecule* product6 = &rxn1.addComponent(ReactionRole::PRODUCT);
	BasicMolecule* reactant5 = &rxn1.addComponent(ReactionRole::REACTANT);

	BOOST_CHECK_THROW(reactant4->getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(reactant5->getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(agent4->getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(product4->getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(product5->getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(product6->getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn1.getComponentRole(*reactant4) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant5) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product4) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product5) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product6) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*agent4) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.containsComponent(*reactant4));
	BOOST_CHECK(rxn1.containsComponent(*reactant5));
	BOOST_CHECK(rxn1.containsComponent(*product4));
	BOOST_CHECK(rxn1.containsComponent(*product5));
	BOOST_CHECK(rxn1.containsComponent(*product6));
	BOOST_CHECK(rxn1.containsComponent(*agent4));

	BOOST_CHECK(rxn1.getComponentIndex(*reactant4) == 3);
	BOOST_CHECK(rxn1.getComponentIndex(*reactant5) == 4);
	BOOST_CHECK(rxn1.getComponentIndex(*product4) == 12);
	BOOST_CHECK(rxn1.getComponentIndex(*product5) == 13);
	BOOST_CHECK(rxn1.getComponentIndex(*product6) == 14);
	BOOST_CHECK(rxn1.getComponentIndex(*agent4) == 8);
	
	BOOST_CHECK(rxn1.getComponentRole(comp3) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(comp3));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(comp3), ItemNotFound);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == reactant5);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 14) == product6);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 14) == product6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapComponentRoles(ReactionRole::REACTANT, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant2) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant3) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant4) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant5) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product2) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product3) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product4) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product5) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*product6) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent2) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent3) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent4) == ReactionRole::AGENT);

	BOOST_CHECK(rxn1.containsComponent(*reactant4));
	BOOST_CHECK(rxn1.containsComponent(*reactant5));
	BOOST_CHECK(rxn1.containsComponent(*product4));
	BOOST_CHECK(rxn1.containsComponent(*product5));
	BOOST_CHECK(rxn1.containsComponent(*product6));
	BOOST_CHECK(rxn1.containsComponent(*agent4));

	BOOST_CHECK(rxn1.getComponentIndex(*reactant4) == 13);
	BOOST_CHECK(rxn1.getComponentIndex(*reactant5) == 14);
	BOOST_CHECK(rxn1.getComponentIndex(*product4) == 3);
	BOOST_CHECK(rxn1.getComponentIndex(*product5) == 4);
	BOOST_CHECK(rxn1.getComponentIndex(*product6) == 5);
	BOOST_CHECK(rxn1.getComponentIndex(*agent4) == 9);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(rxn1.getComponentRole(comp3) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1.containsComponent(comp3));
	BOOST_CHECK_THROW(rxn1.getComponentIndex(comp3), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == product1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == product4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == product5);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == product6);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == product6);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9) == agent4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9) == agent4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 14) == reactant5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 14) == reactant5);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 6 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 6 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5) == product6); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == product6);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(9) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(9) == agent4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(6, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(6, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapComponentRoles(ReactionRole::REACTANT, ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant2) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant3) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant4) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant5) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product2) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product3) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product4) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product5) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product6) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*agent2) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*agent3) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*agent4) == ReactionRole::REACTANT);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 6);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == agent1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == product5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == product5);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9) == product6);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9) == product6);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 10) == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 11) == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 12) == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 13) == reactant4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 14) == reactant5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 14) == reactant5);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 6 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 6 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 5) == product6); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == reactant5); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == agent4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(9) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(9) == product6);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(10) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(11) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(12) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(13) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(14) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == agent4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::AGENT) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::AGENT) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(6, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(6, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn1.swapComponentRoles(ReactionRole::PRODUCT, ReactionRole::AGENT);
	rxn1.swapComponentRoles(ReactionRole::AGENT, ReactionRole::REACTANT);

	BOOST_CHECK(rxn1.getComponentRole(*reactant1) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant2) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant3) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant4) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*reactant5) == ReactionRole::REACTANT);
	BOOST_CHECK(rxn1.getComponentRole(*agent1) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent2) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent3) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*agent4) == ReactionRole::AGENT);
	BOOST_CHECK(rxn1.getComponentRole(*product1) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product2) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product3) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product4) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product5) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn1.getComponentRole(*product6) == ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getNumComponents() == 15);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == reactant5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == reactant5);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == agent3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == agent4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 10) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 11) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 12) == product4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 13) == product5);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 14) == product6);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 14) == product6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4) == reactant5); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3) == agent4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5) == product6); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == reactant5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == agent4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(9) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(10) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(11) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(12) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(13) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(14) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(15), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT) == product6);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(6, ReactionRole::PRODUCT), IndexError);

//-----

	rxn1.setProperty(prop_key2, std::string("reaction1"));

	BOOST_CHECK(rxn1.getProperty<std::string>(prop_key2) == "reaction1");
	
	BasicReaction rxn2(rxn1);

	BOOST_CHECK(rxn2.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn2.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn2.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn2.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn2.getNumComponents() == 15);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 9) == &rxn2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 9) == &rxn2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 10) == &rxn2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 10) == &rxn2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 11) == &rxn2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 11) == &rxn2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 12) == &rxn2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 12) == &rxn2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 13) == &rxn2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 13) == &rxn2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 14) == &rxn2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 14) == &rxn2.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn2.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn2.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn2.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn2.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn2.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn2.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn2.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn2.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn2.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn2.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn2.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn2.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(9) == &rxn2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(9) == &rxn2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(10) == &rxn2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(10) == &rxn2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(11) == &rxn2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(11) == &rxn2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(12) == &rxn2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(12) == &rxn2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(13) == &rxn2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(13) == &rxn2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(14) == &rxn2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(14) == &rxn2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	BasicReaction rxn6(static_cast<const Reaction&>(rxn1));

	BOOST_CHECK(rxn6.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn6.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn6.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn6.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn6.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn6.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn6.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn6.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn6.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn6.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn6.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn6.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn6.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn6.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn6.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn6.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn6.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn6.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn6.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn6.getNumComponents() == 15);
	BOOST_CHECK(rxn6.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn6.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn6.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn6).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn6).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn6).getComponentsBegin() == &rxn6.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn6).getComponentsBegin() == &rxn6.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 1) == &rxn6.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 1) == &rxn6.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 2) == &rxn6.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 2) == &rxn6.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 3) == &rxn6.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 3) == &rxn6.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 4) == &rxn6.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 4) == &rxn6.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 5) == &rxn6.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 5) == &rxn6.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 6) == &rxn6.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 6) == &rxn6.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 7) == &rxn6.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 7) == &rxn6.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 8) == &rxn6.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 8) == &rxn6.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 9) == &rxn6.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 9) == &rxn6.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 10) == &rxn6.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 10) == &rxn6.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 11) == &rxn6.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 11) == &rxn6.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 12) == &rxn6.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 12) == &rxn6.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 13) == &rxn6.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 13) == &rxn6.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin() + 14) == &rxn6.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin() + 14) == &rxn6.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) == &rxn6.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) == &rxn6.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn6.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn6.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn6.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn6.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn6.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn6.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn6.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn6.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) == &rxn6.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) == &rxn6.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn6.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn6.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn6.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn6.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn6.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn6.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn6).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) == &rxn6.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) == &rxn6.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn6.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn6.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn6.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn6.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn6.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn6.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn6.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn6.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn6.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn6).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn6.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(0) == &rxn6.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(0) == &rxn6.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(1) == &rxn6.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(1) == &rxn6.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(2) == &rxn6.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(2) == &rxn6.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(3) == &rxn6.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(3) == &rxn6.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(4) == &rxn6.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(4) == &rxn6.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(5) == &rxn6.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(5) == &rxn6.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(6) == &rxn6.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(6) == &rxn6.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(7) == &rxn6.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(7) == &rxn6.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(8) == &rxn6.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(8) == &rxn6.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(9) == &rxn6.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(9) == &rxn6.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(10) == &rxn6.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(10) == &rxn6.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(11) == &rxn6.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(11) == &rxn6.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(12) == &rxn6.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(12) == &rxn6.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(13) == &rxn6.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(13) == &rxn6.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn6).getComponent(14) == &rxn6.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn6).getComponent(14) == &rxn6.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn6).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn6).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn6).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn6).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn6).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn6).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn6).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn6).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn6.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn6.removeComponent(rxn6.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn6.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn6.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn6.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	BasicReaction rxn7;

	rxn7.copy(rxn1);

	BOOST_CHECK(rxn7.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn7.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn7.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn7.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn7.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn7.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn7.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn7.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn7.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn7.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn7.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn7.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn7.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn7.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn7.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn7.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn7.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn7.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn7.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn7.getNumComponents() == 15);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin() == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin() == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 2) == &rxn7.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 2) == &rxn7.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 3) == &rxn7.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 3) == &rxn7.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 4) == &rxn7.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 4) == &rxn7.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 5) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 5) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 6) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 6) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 7) == &rxn7.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 7) == &rxn7.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 8) == &rxn7.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 8) == &rxn7.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 9) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 9) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 10) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 10) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 11) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 11) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 12) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 12) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 13) == &rxn7.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 13) == &rxn7.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 14) == &rxn7.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 14) == &rxn7.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) == &rxn7.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) == &rxn7.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn7.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn7.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn7.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn7.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn7.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn7.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == &rxn7.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == &rxn7.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn7.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn7.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn7.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn7.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn7.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn7.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == &rxn7.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == &rxn7.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn7.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn7.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn7.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn7.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn7.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn7.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn7.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn7.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn7.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn7.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(0) == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(0) == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(2) == &rxn7.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(2) == &rxn7.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(3) == &rxn7.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(3) == &rxn7.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(4) == &rxn7.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(4) == &rxn7.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(5) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(5) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(6) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(6) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(7) == &rxn7.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(7) == &rxn7.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(8) == &rxn7.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(8) == &rxn7.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(9) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(9) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(10) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(10) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(11) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(11) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(12) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(12) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(13) == &rxn7.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(13) == &rxn7.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(14) == &rxn7.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(14) == &rxn7.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(rxn7.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn7.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	Reaction::SharedPointer rxn1_clone2_ptr = rxn1.clone();
	BasicReaction& rxn1_clone2 = static_cast<BasicReaction&>(*rxn1_clone2_ptr);

	BOOST_CHECK(rxn1_clone2.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn1_clone2.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn1_clone2.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn1_clone2.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn1_clone2.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn1_clone2.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn1_clone2.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn1_clone2.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn1_clone2.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn1_clone2.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn1_clone2.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn1_clone2.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn1_clone2.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn1_clone2.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn1_clone2.getNumComponents() == 15);
	BOOST_CHECK(rxn1_clone2.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn1_clone2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn1_clone2.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn1_clone2).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn1_clone2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 5) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 5) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 6) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 6) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 7) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 7) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 8) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 8) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 9) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 9) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 10) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 10) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 11) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 11) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 12) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 12) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 13) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 13) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin() + 14) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin() + 14) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn1_clone2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1_clone2).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(0) == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(0) == &rxn1_clone2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(1) == &rxn1_clone2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(2) == &rxn1_clone2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(3) == &rxn1_clone2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(4) == &rxn1_clone2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(5) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(5) == &rxn1_clone2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(6) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(6) == &rxn1_clone2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(7) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(7) == &rxn1_clone2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(8) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(8) == &rxn1_clone2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(9) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(9) == &rxn1_clone2.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(10) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(10) == &rxn1_clone2.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(11) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(11) == &rxn1_clone2.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(12) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(12) == &rxn1_clone2.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(13) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(13) == &rxn1_clone2.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1_clone2).getComponent(14) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1_clone2).getComponent(14) == &rxn1_clone2.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1_clone2).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1_clone2).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1_clone2).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1_clone2).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1_clone2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1_clone2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1_clone2).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1_clone2).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1_clone2.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn1_clone2.removeComponent(rxn1_clone2.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn1_clone2.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1_clone2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1_clone2.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	BasicReaction rxn3;

	BOOST_CHECK(&(rxn3 = rxn1) == &rxn3);

	BOOST_CHECK(rxn3.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	
	BOOST_CHECK(rxn3.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn3.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn3.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn3.getNumComponents() == 15);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	BOOST_CHECK(&(rxn3 = rxn3) == &rxn3);

	BOOST_CHECK(rxn3.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn3.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn3.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn3.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn3.getNumComponents() == 15);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn3.copy(rxn3);

	BOOST_CHECK(rxn3.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn3.getComponent(0, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn3.getComponent(1, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK(rxn3.getComponent(2, ReactionRole::PRODUCT).getProperty<std::string>(prop_key1) == "product");
	BOOST_CHECK_THROW(rxn3.getComponent(3, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(4, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn3.getComponent(5, ReactionRole::PRODUCT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn3.getComponentRole(rxn1.getComponent(0)) == ReactionRole::NONE);
	BOOST_CHECK(!rxn3.containsComponent(rxn1.getComponent(1)));
	BOOST_CHECK_THROW(rxn3.getComponentIndex(rxn1.getComponent(14)), ItemNotFound);

	BOOST_CHECK(rxn3.getNumComponents() == 15);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 6);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 15 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 8) == &rxn3.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn3.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn3.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn3.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn3.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn3.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 6 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4) == &rxn3.getComponent(4, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 5) == &rxn3.getComponent(5, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(8) == &rxn3.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(9) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(10) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(11) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(12) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(13) == &rxn3.getComponent(4, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(14) == &rxn3.getComponent(5, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(15), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(15), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(6, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(15), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 15), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(6, ReactionRole::PRODUCT), IndexError);
	
//-----

	BasicMolecule& rxn3_comp0 = rxn3.getComponent(0);

	rxn3.clear();

	BOOST_CHECK(rxn3.getComponentRole(rxn3_comp0) == ReactionRole::NONE);
	BOOST_CHECK(!rxn3.containsComponent(rxn3_comp0));
	BOOST_CHECK_THROW(rxn3.getComponentIndex(rxn3_comp0), ItemNotFound);

	BOOST_CHECK(rxn3.getNumProperties() == 0);

	BOOST_CHECK(rxn3.getNumComponents() == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin() == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn3.removeComponent(++rxn3.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::PRODUCT), IndexError);

	rxn3.removeComponents(ReactionRole::REACTANT);
	rxn3.removeComponents(ReactionRole::AGENT);
	rxn3.removeComponents(ReactionRole::PRODUCT);

//-----

	BasicMolecule& rxn2_prod0 = rxn2.getComponent(0, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn2.getComponentRole(rxn2_prod0) == ReactionRole::PRODUCT);
	BOOST_CHECK(rxn2.containsComponent(rxn2_prod0));
	BOOST_CHECK(rxn2.getComponentIndex(rxn2_prod0) == (rxn2.getNumComponents(ReactionRole::AGENT) + rxn2.getNumComponents(ReactionRole::REACTANT)));

	rxn2.removeComponents(ReactionRole::PRODUCT);

	BOOST_CHECK(rxn2.getComponentRole(rxn2_prod0) == ReactionRole::NONE);
	BOOST_CHECK(!rxn2.containsComponent(rxn2_prod0));
	BOOST_CHECK_THROW(rxn2.getComponentIndex(rxn2_prod0), ItemNotFound);

	BOOST_CHECK(rxn2.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::REACTANT).getProperty<std::string>(prop_key1) == "reactant");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK_THROW(rxn2.getComponent(4, ReactionRole::REACTANT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn2.getNumComponents() == 9);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 5);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 9 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 9 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 8) == &rxn2.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 5 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == &rxn2.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn2.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 2) == &rxn2.getComponent(2, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 3) == &rxn2.getComponent(3, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) + 4) == &rxn2.getComponent(4, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(4) == &rxn2.getComponent(4, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(5) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(6) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(7) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(8) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(9), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(9), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(5, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(9), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 9), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(5, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	rxn2.removeComponents(ReactionRole::REACTANT);
	
	BOOST_CHECK(rxn2.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK_THROW(rxn2.getComponent(0, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);
	BOOST_CHECK(rxn2.getComponent(1, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK(rxn2.getComponent(2, ReactionRole::AGENT).getProperty<std::string>(prop_key1) == "agent");
	BOOST_CHECK_THROW(rxn2.getComponent(3, ReactionRole::AGENT).getProperty(prop_key1, true), ItemNotFound);

	BOOST_CHECK(rxn2.getNumComponents() == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 4);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 4 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 4 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin() == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 1) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 2) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin() + 3) == &rxn2.getComponent(3, ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 4 == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == &rxn2.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn2.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 2) == &rxn2.getComponent(2, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) + 3) == &rxn2.getComponent(3, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(0) == &rxn2.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(1) == &rxn2.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(2) == &rxn2.getComponent(2, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn2).getComponent(3) == &rxn2.getComponent(3, ReactionRole::AGENT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(4), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(4, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(4), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin() + 4), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(4, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);
	
//-----

	rxn2.removeComponents(ReactionRole::AGENT);
	
	BOOST_CHECK(rxn2.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK(rxn2.getNumComponents() == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn2.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin()  == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn2).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn2).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn2).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn2.removeComponent(rxn2.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn2.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	BasicReaction rxn4(rxn1);

	BasicReaction::ComponentIterator it = rxn1.removeComponent(rxn1.getComponentsBegin());

	BOOST_CHECK(it == rxn1.getComponentsBegin());

	it = rxn1.removeComponent(rxn1.getComponentsBegin(ReactionRole::AGENT));

	BOOST_CHECK(it == rxn1.getComponentsBegin(ReactionRole::AGENT));

	it = rxn1.removeComponent(--rxn1.getComponentsEnd());

	BOOST_CHECK(it == rxn1.getComponentsEnd());

	BOOST_CHECK(rxn1.getNumComponents() == 12);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 4);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 3);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 5);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 12 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 12 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant2);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == reactant4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == reactant5);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == agent3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == agent4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 9) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 9) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 10) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 10) == product4);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 11) == product5);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 11) == product5);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant2); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2) == reactant4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 3) == reactant5); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 3 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2) == agent4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 5 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4) == product5); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == reactant5);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == agent4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(8) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(8) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(9) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(9) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(10) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(10) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(11) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(11) == product5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(12), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(12), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::REACTANT) == reactant5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT) == agent4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT) == product5);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(5, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(12), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 12), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(3, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(5, ReactionRole::PRODUCT), IndexError);

//-----

	rxn1.removeComponent(0);
	rxn1.removeComponent(2, ReactionRole::REACTANT);
	rxn1.removeComponent(2, ReactionRole::AGENT);
	rxn1.removeComponent(4, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getNumComponents() == 8);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 8 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 8 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == reactant3);
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin() == reactant3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 1) == reactant4);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 2) == agent2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 3) == agent3);

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 4) == product1);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 5) == product2);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 6) == product3);
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() + 7) == product4);
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin() + 7) == product4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant3); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == reactant3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) + 1) == reactant4); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == agent2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) + 1) == agent3); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == product1); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 1) == product2); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 2) == product3); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) + 3) == product4); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1) == reactant4);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3) == agent3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(4) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(5) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(6) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(7) == product4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(8), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT) == reactant3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT) == reactant4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT) == agent2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT) == agent3);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT) == product1);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT) == product2);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(2, ReactionRole::PRODUCT) == product3);
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn1).getComponent(3, ReactionRole::PRODUCT) == product4);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn3.getNumComponents() == 0);

	BOOST_CHECK(&(rxn3 = rxn1) == &rxn3);

	BOOST_CHECK(rxn3.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK(rxn3.getNumComponents() == 8);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 8 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 8 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin() == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 2) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 3) == &rxn3.getComponent(1, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 4) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 5) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 6) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin() + 7) == &rxn3.getComponent(3, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == &rxn3.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn3.getComponent(1, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == &rxn3.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn3.getComponent(1, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == &rxn3.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn3.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn3.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn3.getComponent(3, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(0) == &rxn3.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(1) == &rxn3.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(2) == &rxn3.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(3) == &rxn3.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(4) == &rxn3.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(5) == &rxn3.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(6) == &rxn3.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn3).getComponent(7) == &rxn3.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(8), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	rxn7.setProperty(prop_key2, std::string("reaction7"));
	
	rxn7.copy(rxn1);

	BOOST_CHECK(rxn7.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK(rxn7.getNumComponents() == 8);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 8 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 8 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin() == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin() == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 2) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 2) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 3) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 3) == &rxn7.getComponent(1, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 4) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 4) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 5) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 5) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 6) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 6) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() + 7) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin() + 7) == &rxn7.getComponent(3, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) == &rxn7.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) == &rxn7.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn7.getComponent(1, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == &rxn7.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == &rxn7.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn7.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn7.getComponent(1, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == &rxn7.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == &rxn7.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn7.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn7.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn7.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn7.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn7.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn7.getComponent(3, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(0) == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(0) == &rxn7.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(1) == &rxn7.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(2) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(2) == &rxn7.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(3) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(3) == &rxn7.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(4) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(4) == &rxn7.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(5) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(5) == &rxn7.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(6) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(6) == &rxn7.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn7).getComponent(7) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn7).getComponent(7) == &rxn7.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(8), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(rxn7.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn7.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn7.getNumProperties() == 1);

	rxn7.copy(BasicReaction());

	BOOST_CHECK(rxn7.getNumProperties() == 0);

	BOOST_CHECK(rxn7.getNumComponents() == 0);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn7.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin()  == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn7).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn7).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn7).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn7).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn7.removeComponent(rxn7.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn7.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn7.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn4.getNumComponents() == 15);

	BOOST_CHECK(&(rxn4 = rxn1) == &rxn4);

	BOOST_CHECK(rxn4.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK(rxn4.getNumComponents() == 8);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::REACTANT) == 2);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::AGENT) == 2);
	BOOST_CHECK(rxn4.getNumComponents(ReactionRole::PRODUCT) == 4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 8 == 
				const_cast<const BasicReaction&>(rxn4).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 8 == 
				const_cast<BasicReaction&>(rxn4).getComponentsEnd());

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn4).getComponentsBegin() == &rxn4.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn4).getComponentsBegin() == &rxn4.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 1) == &rxn4.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 1) == &rxn4.getComponent(1, ReactionRole::REACTANT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 2) == &rxn4.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 2) == &rxn4.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 3) == &rxn4.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 3) == &rxn4.getComponent(1, ReactionRole::AGENT));

	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 4) == &rxn4.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 4) == &rxn4.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 5) == &rxn4.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 5) == &rxn4.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 6) == &rxn4.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 6) == &rxn4.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin() + 7) == &rxn4.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin() + 7) == &rxn4.getComponent(3, ReactionRole::PRODUCT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<const BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 2 == 
				const_cast<BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) == &rxn4.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) == &rxn4.getComponent(0, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn4.getComponent(1, ReactionRole::REACTANT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::REACTANT) + 1) == &rxn4.getComponent(1, ReactionRole::REACTANT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<const BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 2 == 
				const_cast<BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) == &rxn4.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) == &rxn4.getComponent(0, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn4.getComponent(1, ReactionRole::AGENT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::AGENT) + 1) == &rxn4.getComponent(1, ReactionRole::AGENT)); 

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<const BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 4 == 
				const_cast<BasicReaction&>(rxn4).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK(&*const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) == &rxn4.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) == &rxn4.getComponent(0, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn4.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 1) == &rxn4.getComponent(1, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn4.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 2) == &rxn4.getComponent(2, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<const BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn4.getComponent(3, ReactionRole::PRODUCT)); 
	BOOST_CHECK(&*(const_cast<BasicReaction&>(rxn4).getComponentsBegin(ReactionRole::PRODUCT) + 3) == &rxn4.getComponent(3, ReactionRole::PRODUCT)); 

	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(0) == &rxn4.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(0) == &rxn4.getComponent(0, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(1) == &rxn4.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(1) == &rxn4.getComponent(1, ReactionRole::REACTANT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(2) == &rxn4.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(2) == &rxn4.getComponent(0, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(3) == &rxn4.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(3) == &rxn4.getComponent(1, ReactionRole::AGENT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(4) == &rxn4.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(4) == &rxn4.getComponent(0, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(5) == &rxn4.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(5) == &rxn4.getComponent(1, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(6) == &rxn4.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(6) == &rxn4.getComponent(2, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<const BasicReaction&>(rxn4).getComponent(7) == &rxn4.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK(&const_cast<BasicReaction&>(rxn4).getComponent(7) == &rxn4.getComponent(3, ReactionRole::PRODUCT));
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn4).getComponent(8), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn4).getComponent(8), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn4).getComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn4).getComponent(2, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn4).getComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn4).getComponent(2, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn4).getComponent(4, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn4).getComponent(4, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn4.removeComponent(8), IndexError);

	BOOST_CHECK_THROW(rxn4.removeComponent(rxn4.getComponentsBegin() + 8), RangeError);

	BOOST_CHECK_THROW(rxn4.removeComponent(2, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn4.removeComponent(2, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn4.removeComponent(4, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(&(rxn3 = BasicReaction()) == &rxn3);

	BOOST_CHECK(rxn3.getNumProperties() == 0);

	BOOST_CHECK(rxn3.getNumComponents() == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn3.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin()  == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn3).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn3).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn3).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn3.removeComponent(rxn3.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn3.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	while (rxn1.getNumComponents(ReactionRole::REACTANT) > 0)
		rxn1.removeComponent(0, ReactionRole::REACTANT);

	while (rxn1.getNumComponents(ReactionRole::AGENT) > 0)
		rxn1.removeComponent(0, ReactionRole::AGENT);

	while (rxn1.getNumComponents(ReactionRole::PRODUCT) > 0)
		rxn1.removeComponent(0, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getProperty<std::string>(prop_key2) == "reaction1");

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin() == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn1).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn1).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn1).getComponent(1, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(1), IndexError);

	BOOST_CHECK_THROW(rxn1.removeComponent(rxn1.getComponentsBegin()), RangeError);
	BOOST_CHECK_THROW(rxn1.removeComponent(++rxn1.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn1.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	for (std::size_t i = 0; i < 15; i++)
		BOOST_CHECK(rxn1.addComponent(ReactionRole::AGENT).getNumProperties() == 0);

//-----

	BasicReaction rxn5 = BasicReaction();

	BOOST_CHECK(rxn5.getNumProperties() == 0);

	BOOST_CHECK(rxn5.getNumComponents() == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::REACTANT) == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::AGENT) == 0);
	BOOST_CHECK(rxn5.getNumComponents(ReactionRole::PRODUCT) == 0);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn5).getComponentsBegin() == 
				const_cast<const BasicReaction&>(rxn5).getComponentsEnd());
	BOOST_CHECK(const_cast<BasicReaction&>(rxn5).getComponentsBegin()  == 
				const_cast<BasicReaction&>(rxn5).getComponentsEnd());

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::REACTANT) == 
				const_cast<const BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::REACTANT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::REACTANT)  == 
				const_cast<BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::REACTANT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<const BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::AGENT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::AGENT) == 
				const_cast<BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::AGENT));

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<const BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::PRODUCT));
	BOOST_CHECK(const_cast<BasicReaction&>(rxn5).getComponentsBegin(ReactionRole::PRODUCT) == 
				const_cast<BasicReaction&>(rxn5).getComponentsEnd(ReactionRole::PRODUCT));

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn5).getComponent(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn5).getComponent(0), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn5).getComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn5).getComponent(0, ReactionRole::REACTANT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn5).getComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn5).getComponent(0, ReactionRole::AGENT), IndexError);

	BOOST_CHECK_THROW(const_cast<const BasicReaction&>(rxn5).getComponent(0, ReactionRole::PRODUCT), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicReaction&>(rxn5).getComponent(0, ReactionRole::PRODUCT), IndexError);

	BOOST_CHECK_THROW(rxn5.removeComponent(0), IndexError);

	BOOST_CHECK_THROW(rxn5.removeComponent(rxn5.getComponentsBegin()), RangeError);

	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::REACTANT), IndexError);
	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::AGENT), IndexError);
	BOOST_CHECK_THROW(rxn5.removeComponent(0, ReactionRole::PRODUCT), IndexError);

//-----

	BOOST_CHECK(rxn5.getNumComponents() == 0);

	rxn5.addComponent(ReactionRole::REACTANT);
	rxn5.addComponent(ReactionRole::PRODUCT);
	rxn5.addComponent(ReactionRole::AGENT);
	rxn5.addComponent(ReactionRole::AGENT);

	BOOST_CHECK(rxn5.getNumComponents() == 4);

	BOOST_CHECK(const_cast<const BasicReaction&>(rxn5).getComponentsEnd() - 
				const_cast<const BasicReaction&>(rxn5).getComponentsBegin() == 4);
	BOOST_CHECK(const_cast<BasicReaction&>(rxn5).getComponentsEnd() - 
				const_cast<BasicReaction&>(rxn5).getComponentsBegin() == 4);

	it = rxn5.removeComponent(rxn5.getComponentsBegin());

	BOOST_CHECK(it == rxn5.getComponentsBegin());

	it = rxn5.removeComponent(rxn5.getComponentsBegin() + 1);

	BOOST_CHECK(it == rxn5.getComponentsBegin() + 1);

	it = rxn5.removeComponent(--rxn5.getComponentsEnd());

	BOOST_CHECK(it == rxn5.getComponentsEnd());

	it = rxn5.removeComponent(rxn5.getComponentsBegin());

	BOOST_CHECK(it == rxn5.getComponentsEnd());
}
