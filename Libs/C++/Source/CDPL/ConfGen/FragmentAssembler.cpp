/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentAssembler.cpp 
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

#include "CDPL/ConfGen/FragmentAssembler.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "FragmentAssemblerImpl.hpp"


using namespace CDPL;


ConfGen::FragmentAssembler::FragmentAssembler(): 
    impl(new FragmentAssemblerImpl())
{}

const ConfGen::FragmentAssemblerSettings& 
ConfGen::FragmentAssembler::getSettings() const
{
    return impl->getSettings();
}

ConfGen::FragmentAssemblerSettings& 
ConfGen::FragmentAssembler::getSettings()
{
    return impl->getSettings();
}

void ConfGen::FragmentAssembler::setAbortCallback(const CallbackFunction& func)
{
	impl->setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssembler::getAbortCallback() const
{
	return impl->getAbortCallback();
}

void ConfGen::FragmentAssembler::setTimeoutCallback(const CallbackFunction& func)
{
	impl->setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssembler::getTimeoutCallback() const
{
	return impl->getTimeoutCallback();
}

unsigned int ConfGen::FragmentAssembler::assemble(const Chem::MolecularGraph& molgraph)
{
	return impl->assemble(molgraph);
}
		
std::size_t ConfGen::FragmentAssembler::getNumStructures() const
{
	return impl->getNumStructures();
}

const ConfGen::ConformerData& ConfGen::FragmentAssembler::getStructure(std::size_t idx) const
{
	if (idx >= impl->getNumStructures())
		throw Base::IndexError("FragmentAssembler: structure index out of bounds");

	return impl->getStructure(idx);
}

ConfGen::ConformerData& ConfGen::FragmentAssembler::getStructure(std::size_t idx)
{
	if (idx >= impl->getNumStructures())
		throw Base::IndexError("FragmentAssembler: structure index out of bounds");

	return impl->getStructure(idx);
}

ConfGen::FragmentAssembler::ConstStructureIterator ConfGen::FragmentAssembler::getStructuresBegin() const
{
	return impl->getStructuresBegin();
}

ConfGen::FragmentAssembler::ConstStructureIterator ConfGen::FragmentAssembler::getStructuresEnd() const
{
	return impl->getStructuresEnd();
}

ConfGen::FragmentAssembler::StructureIterator ConfGen::FragmentAssembler::getStructuresBegin()
{
	return impl->getStructuresBegin();
}

ConfGen::FragmentAssembler::StructureIterator ConfGen::FragmentAssembler::getStructuresEnd()
{
	return impl->getStructuresEnd();
}
