/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatchConstraintList.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/MatchConstraintList.hpp"


using namespace CDPL;


unsigned int Chem::MatchConstraint::getID() const
{
	return id;
}

void Chem::MatchConstraint::setID(unsigned int i)
{
	id = i;
}

Chem::MatchConstraint::Relation Chem::MatchConstraint::getRelation() const
{
	return relation;
}

void Chem::MatchConstraint::setRelation(Relation r)
{
	relation = r;
}

const Base::Variant& Chem::MatchConstraint::getValue() const
{
 	return value;
}

void Chem::MatchConstraint::setValue(const Base::Variant& v)
{
	value = v;
}

bool Chem::MatchConstraint::hasValue() const
{
	return !value.isEmpty();
}


Chem::MatchConstraintList::Type Chem::MatchConstraintList::getType() const
{
	return type;
}

void Chem::MatchConstraintList::setType(Type t)
{
	type = t;
}

void Chem::MatchConstraintList::addElement(unsigned int id, MatchConstraint::Relation relation)
{
	addElement(MatchConstraint(id, relation));
}

void Chem::MatchConstraintList::addElement(unsigned int id, MatchConstraint::Relation relation, const Base::Variant& value)
{
	addElement(MatchConstraint(id, relation, value));
}

const char* Chem::MatchConstraintList::getClassName() const
{
	return "MatchConstraintList";
}
