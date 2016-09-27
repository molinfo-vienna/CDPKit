/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLiteScreeningDBCreator.cpp 
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

#include "CDPL/Pharm/SQLiteScreeningDBAccessor.hpp"

#include "SQLScreeningDBMetaData.hpp"
#include "SQLiteIOImplementationBase.hpp"


using namespace CDPL;


namespace
{

	const std::string SELECT_MOL_DATA_QUERY_SQL = "SELECT " +
		Pharm::SQLScreeningDB::MOL_DATA_COLUMN_NAME + " FROM " +
		Pharm::SQLScreeningDB::MOL_TABLE_NAME + " WHERE " +
		Pharm::SQLScreeningDB::MOL_ID_COLUMN_NAME + " = ?1";

}


class Pharm::SQLiteScreeningDBAccessor::Implementation : private Pharm::SQLiteIOImplementationBase
{

public:
	Implementation();

	void open(const std::string& name);

	void close();

	const std::string& getDatabaseName() const;

	std::size_t getNumMolecules() const;

	std::size_t getNumPharmacophores() const;

	void getMolecule(std::size_t idx, Chem::Molecule& mol) const; 

	void getPharmacophore(std::size_t idx, Pharmacophore& pharm) const; 

	void getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm) const; 

	std::size_t findMatchingEntries(const Pharmacophore& pharm);

	std::size_t getNumMatchingEntries();

	std::size_t getMatchingEntryMolIndex(std::size_t idx) const;

	std::size_t getMatchingEntryConfIndex(std::size_t idx) const;

private:

};


Pharm::SQLiteScreeningDBAccessor::SQLiteScreeningDBAccessor():
	impl(new Implementation())
{}

Pharm::SQLiteScreeningDBAccessor::SQLiteScreeningDBAccessor(const std::string& name):
	impl(new Implementation())
{
	impl->open(name);
}
	
Pharm::SQLiteScreeningDBAccessor::~SQLiteScreeningDBAccessor() {}

void Pharm::SQLiteScreeningDBAccessor::open(const std::string& name)
{
	impl->open(name);
}

void Pharm::SQLiteScreeningDBAccessor::close()
{
	impl->close();
}

const std::string& Pharm::SQLiteScreeningDBAccessor::getDatabaseName() const
{
	return impl->getDatabaseName();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getNumMolecules() const
{
	return impl->getNumMolecules();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getNumPharmacophores() const
{
	return impl->getNumPharmacophores();
}

void Pharm::SQLiteScreeningDBAccessor::getMolecule(std::size_t idx, Chem::Molecule& mol) const
{
	impl->getMolecule(idx, mol);
}

void Pharm::SQLiteScreeningDBAccessor::getPharmacophore(std::size_t idx, Pharmacophore& pharm) const
{
	impl->getPharmacophore(idx, pharm);
}

void Pharm::SQLiteScreeningDBAccessor::getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm) const
{
	impl->getPharmacophore(mol_idx, conf_idx, pharm);
}

std::size_t Pharm::SQLiteScreeningDBAccessor::findMatchingEntries(const Pharmacophore& pharm)
{
	return impl->findMatchingEntries(pharm);
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getNumMatchingEntries()
{
	return impl->getNumMatchingEntries();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getMatchingEntryMolIndex(std::size_t idx) const
{
	return impl->getMatchingEntryMolIndex(idx);
}

std::size_t Pharm::SQLiteScreeningDBAccessor::getMatchingEntryConfIndex(std::size_t idx) const
{
	return impl->getMatchingEntryConfIndex(idx);
}


// Implementation

Pharm::SQLiteScreeningDBAccessor::Implementation::Implementation()
{
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::open(const std::string& name)
{
	openDBConnection(name, SQLITE_OPEN_READONLY);
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::close()
{
	closeDBConnection();
}

const std::string& Pharm::SQLiteScreeningDBAccessor::Implementation::getDatabaseName() const
{
	return getDBName();
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getNumMolecules() const
{
	return 0; // TODO
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getNumPharmacophores() const
{
	return 0; // TODO
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::getMolecule(std::size_t idx, Chem::Molecule& mol) const
{
	// TODO
}

void Pharm::SQLiteScreeningDBAccessor::Implementation::getPharmacophore(std::size_t idx, Pharmacophore& pharm) const
{
	// TODO
} 

void Pharm::SQLiteScreeningDBAccessor::Implementation::getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm) const
{
	// TODO
} 

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::findMatchingEntries(const Pharmacophore& pharm)
{
	return 0; // TODO
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getNumMatchingEntries()
{
	return 0; // TODO
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getMatchingEntryMolIndex(std::size_t idx) const
{
	return 0; // TODO
}

std::size_t Pharm::SQLiteScreeningDBAccessor::Implementation::getMatchingEntryConfIndex(std::size_t idx) const
{
	return 0; // TODO
}
