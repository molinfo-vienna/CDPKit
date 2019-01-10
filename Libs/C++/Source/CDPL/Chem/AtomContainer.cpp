/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainer.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL;


Chem::AtomContainer::ConstAtomIterator Chem::AtomContainer::getAtomsBegin() const
{
	return ConstAtomIterator(this, 0);
}

Chem::AtomContainer::ConstAtomIterator Chem::AtomContainer::getAtomsEnd() const
{
	return ConstAtomIterator(this, getNumAtoms());
}

Chem::AtomContainer::AtomIterator Chem::AtomContainer::getAtomsBegin()
{
	return AtomIterator(this, 0);
}

Chem::AtomContainer::AtomIterator Chem::AtomContainer::getAtomsEnd()
{
	return AtomIterator(this, getNumAtoms());
}

Chem::AtomContainer& Chem::AtomContainer::operator=(const AtomContainer& cntnr) 
{
	Entity3DContainer::operator=(cntnr);

	return *this;
}

std::size_t Chem::AtomContainer::getNumEntities() const
{
	return getNumAtoms();
}

const Chem::Entity3D& Chem::AtomContainer::getEntity(std::size_t idx) const
{
	return getAtom(idx);
}

Chem::Entity3D& Chem::AtomContainer::getEntity(std::size_t idx)
{
	return getAtom(idx);
}
