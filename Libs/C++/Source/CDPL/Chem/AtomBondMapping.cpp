/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomBondMapping.cpp 
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

#include "CDPL/Chem/AtomBondMapping.hpp"


using namespace CDPL;


const Chem::AtomMapping& Chem::AtomBondMapping::getAtomMapping() const
{
	return atomMapping;
}

const Chem::BondMapping& Chem::AtomBondMapping::getBondMapping() const
{
	return bondMapping;
}

Chem::AtomMapping& Chem::AtomBondMapping::getAtomMapping()
{
	return atomMapping;
}

Chem::BondMapping& Chem::AtomBondMapping::getBondMapping()
{
	return bondMapping;
}

bool Chem::AtomBondMapping::operator==(const AtomBondMapping& mapping) const
{
	return (atomMapping == mapping.atomMapping && bondMapping == mapping.bondMapping);
}

bool Chem::AtomBondMapping::operator!=(const AtomBondMapping& mapping) const
{
	return !(this->operator==(mapping));
}

void Chem::AtomBondMapping::clear()
{
	atomMapping.clear();
	bondMapping.clear();
}

