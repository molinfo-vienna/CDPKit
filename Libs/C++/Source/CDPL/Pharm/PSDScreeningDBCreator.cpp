/* 
 * PSDScreeningDBCreator.cpp 
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

#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"

#include "PSDScreeningDBCreatorImpl.hpp"


using namespace CDPL;


Pharm::PSDScreeningDBCreator::PSDScreeningDBCreator():
	impl(new PSDScreeningDBCreatorImpl())
{}

Pharm::PSDScreeningDBCreator::PSDScreeningDBCreator(const std::string& name, Mode mode, bool allow_dup_entries):
	impl(new PSDScreeningDBCreatorImpl())
{
    impl->open(name, mode, allow_dup_entries);
}
	
Pharm::PSDScreeningDBCreator::~PSDScreeningDBCreator() {}

void Pharm::PSDScreeningDBCreator::open(const std::string& name, Mode mode, bool allow_dup_entries)
{
	impl->open(name, mode, allow_dup_entries);
}

void Pharm::PSDScreeningDBCreator::close()
{
	impl->close();
}

Pharm::PSDScreeningDBCreator::Mode Pharm::PSDScreeningDBCreator::getMode() const
{
	return impl->getMode();
}

bool Pharm::PSDScreeningDBCreator::allowDuplicateEntries() const
{
	return impl->allowDuplicateEntries();
}

bool Pharm::PSDScreeningDBCreator::process(const Chem::MolecularGraph& molgraph)
{
	return impl->process(molgraph);
}

bool Pharm::PSDScreeningDBCreator::merge(const ScreeningDBAccessor& db_acc, const ProgressCallbackFunction& func)
{
	return impl->merge(db_acc, func);
}

const std::string& Pharm::PSDScreeningDBCreator::getDatabaseName() const
{
	return impl->getDatabaseName();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumProcessed() const
{
	return impl->getNumProcessed();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumRejected() const
{
	return impl->getNumRejected();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumDeleted() const
{
	return impl->getNumDeleted();
}

std::size_t Pharm::PSDScreeningDBCreator::getNumInserted() const
{
	return impl->getNumInserted();
}
