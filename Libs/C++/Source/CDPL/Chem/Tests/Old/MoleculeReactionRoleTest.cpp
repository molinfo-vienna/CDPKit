/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeReactionRoleTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionRoles.hpp"
#include "CDPL/Chem/MoleculeProperties.hpp"


BOOST_AUTO_TEST_CASE(MoleculeReactionRoleTest)
{
	using namespace CDPL;
	using namespace Chem;

	Reaction rxn;

	Molecule& reactant = rxn.addReactant();
	Molecule& agent = rxn.addAgent();
	Molecule& product = rxn.addProduct();

	rxn.addReactant();

	BOOST_CHECK(reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(reactant.getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(reactant.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::REACTANT);

	BOOST_CHECK(!reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::AGENT);

	BOOST_CHECK(!agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::PRODUCT);

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

//-----

	rxn.swapRoles(ReactionRole::REACTANT, ReactionRole::AGENT);
	
	BOOST_CHECK(reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(reactant.getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(reactant.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::AGENT);

	BOOST_CHECK(!reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(agent.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::REACTANT);

	BOOST_CHECK(!agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(product.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::PRODUCT);

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

//-----

	rxn.swapRoles(ReactionRole::REACTANT, ReactionRole::PRODUCT);
	
	BOOST_CHECK(!reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(reactant.getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(reactant.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::AGENT);

	BOOST_CHECK(!reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(agent.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::PRODUCT);

	BOOST_CHECK(!agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::REACTANT);

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

//-----

	rxn.swapRoles(ReactionRole::AGENT, ReactionRole::PRODUCT);
	
	BOOST_CHECK(reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(reactant.getReactionRole() == ReactionRole::PRODUCT);
	BOOST_CHECK(reactant.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::PRODUCT);

	BOOST_CHECK(!reactant.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(agent.getReactionRole() == ReactionRole::AGENT);
	BOOST_CHECK(agent.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::AGENT);

	BOOST_CHECK(!agent.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());

	BOOST_CHECK(product.getReactionRole() == ReactionRole::REACTANT);
	BOOST_CHECK(product.getProperty<unsigned int>(MoleculeProperty::REACTION_ROLE) == ReactionRole::REACTANT);

	BOOST_CHECK(!product.getProperty(MoleculeProperty::REACTION_ROLE, false, false).isEmpty());
}
