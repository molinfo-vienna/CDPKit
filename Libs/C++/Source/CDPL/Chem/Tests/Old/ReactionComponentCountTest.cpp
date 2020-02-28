/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionComponentCountTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionProperties.hpp"
#include "CDPL/Chem/ReactionRoles.hpp"


BOOST_AUTO_TEST_CASE(ReactionComponentCountTest)
{
	using namespace CDPL;
	using namespace Chem;

	Reaction rxn1;

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addComponent(ReactionRole::REACTANT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 1);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 1);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addReactant();

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 2);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addComponent(ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 3);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addAgent();

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 4);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addComponent(ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 5);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 5);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.addProduct();

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 6);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 6);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	Reaction rxn2;

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 0);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn2 = rxn1;

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 6);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 6);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn2.removeComponents(ReactionRole::AGENT);

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 4);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn2.removeComponents(ReactionRole::REACTANT);

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 2);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 2);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----
	
	rxn2 = rxn1;

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 6);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 6);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----
	
	rxn2.swapRoles(ReactionRole::REACTANT, ReactionRole::AGENT);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 6);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 6);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn2.removeComponents(ReactionRole::PRODUCT);

	BOOST_CHECK(rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn2.getNumComponents() == 4);
	BOOST_CHECK(rxn2.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 4);

	BOOST_CHECK(!rxn2.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.removeComponent(2);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 5);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 5);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.swapRoles(ReactionRole::AGENT, ReactionRole::PRODUCT);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 5);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 5);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.removeComponent(0, ReactionRole::AGENT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 4);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 4);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.removeComponent(1, ReactionRole::REACTANT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 3);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 3);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.removeComponent(0, ReactionRole::PRODUCT);

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 2);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 2);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.removeComponent(rxn1.getComponentsBegin());

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 1);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 1);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

//-----

	rxn1.clear();

	BOOST_CHECK(rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());

	BOOST_CHECK(rxn1.getNumComponents() == 0);
	BOOST_CHECK(rxn1.getProperty<std::size_t>(ReactionProperty::COMPONENT_COUNT) == 0);

	BOOST_CHECK(!rxn1.getProperty(ReactionProperty::COMPONENT_COUNT, false, false).isEmpty());
}
