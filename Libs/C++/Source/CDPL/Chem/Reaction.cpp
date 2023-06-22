/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Reaction.cpp 
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

 
#include "StaticInit.hpp"

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	void checkRole(unsigned int role) 
	{
		using namespace Chem;

		switch (role) {
			
			case ReactionRole::REACTANT:
			case ReactionRole::AGENT:
			case ReactionRole::PRODUCT:
				return;

			default:
				throw Base::ValueError("Reaction: invalid reaction role");
		}
	}
}


Chem::Reaction::ConstComponentIterator Chem::Reaction::getComponentsBegin() const
{
	return ConstComponentIterator(ConstComponentAccessor(this, ReactionRole::NONE), 0);
}

Chem::Reaction::ComponentIterator Chem::Reaction::getComponentsBegin()
{
	return ComponentIterator(ComponentAccessor(this, ReactionRole::NONE), 0);
}

Chem::Reaction::ConstComponentIterator Chem::Reaction::getComponentsEnd() const
{
	return ConstComponentIterator(ConstComponentAccessor(this, ReactionRole::NONE), getNumComponents());
}

Chem::Reaction::ComponentIterator Chem::Reaction::getComponentsEnd()
{
	return ComponentIterator(ComponentAccessor(this, ReactionRole::NONE), getNumComponents());
}

Chem::Reaction::ConstComponentIterator Chem::Reaction::begin() const
{
	return ConstComponentIterator(ConstComponentAccessor(this, ReactionRole::NONE), 0);
}

Chem::Reaction::ComponentIterator Chem::Reaction::begin()
{
	return ComponentIterator(ComponentAccessor(this, ReactionRole::NONE), 0);
}

Chem::Reaction::ConstComponentIterator Chem::Reaction::end() const
{
	return ConstComponentIterator(ConstComponentAccessor(this, ReactionRole::NONE), getNumComponents());
}

Chem::Reaction::ComponentIterator Chem::Reaction::end()
{
	return ComponentIterator(ComponentAccessor(this, ReactionRole::NONE), getNumComponents());
}

Chem::Reaction::ConstComponentIterator Chem::Reaction::getComponentsBegin(unsigned int role) const
{
	checkRole(role);

	return ConstComponentIterator(ConstComponentAccessor(this, role), 0);
}

Chem::Reaction::ComponentIterator Chem::Reaction::getComponentsBegin(unsigned int role)
{
	checkRole(role);

	return ComponentIterator(ComponentAccessor(this, role), 0);
}

Chem::Reaction::ConstComponentIterator Chem::Reaction::getComponentsEnd(unsigned int role) const
{
	checkRole(role);

	return ConstComponentIterator(ConstComponentAccessor(this, role), getNumComponents(role));
}

Chem::Reaction::ComponentIterator Chem::Reaction::getComponentsEnd(unsigned int role)
{
	checkRole(role);

	return ComponentIterator(ComponentAccessor(this, role), getNumComponents(role));
}

Chem::Reaction::ComponentIterator Chem::Reaction::removeComponent(const ComponentIterator& it)
{
	std::size_t index = it.getIndex();
	unsigned int role = it.getAccessFunc().compRole;

	if (role == ReactionRole::NONE) {
		if (index >= getNumComponents())
			throw Base::RangeError("Reaction: component iterator out of valid range");

		removeComponent(index);

	} else {
		if (index >= getNumComponents(role))
			throw Base::RangeError("Reaction: component iterator out of valid range");

		removeComponent(index, role);
	}

	return it;
}

Chem::Reaction& Chem::Reaction::operator=(const Reaction& rxn) 
{
	if (this == &rxn)
		return *this;

	copy(rxn);

	return *this;
}


const Chem::Molecule& Chem::Reaction::ConstComponentAccessor::operator()(std::size_t idx) const
{
	if (compRole == ReactionRole::NONE)
		return reaction->getComponent(idx);

	return reaction->getComponent(idx, compRole);
}

bool Chem::Reaction::ConstComponentAccessor::operator==(const ConstComponentAccessor& accessor) const 
{
	return (reaction == accessor.reaction && compRole == accessor.compRole);
}

Chem::Molecule& Chem::Reaction::ComponentAccessor::operator()(std::size_t idx) const
{
	if (compRole == ReactionRole::NONE)
		return reaction->getComponent(idx);

	return reaction->getComponent(idx, compRole);
}

bool Chem::Reaction::ComponentAccessor::operator==(const ComponentAccessor& accessor) const 
{
	return (reaction == accessor.reaction && compRole == accessor.compRole);
}
