/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBData.cpp 
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

#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


void Biomol::PDBData::clear()
{
	data.clear();
}

std::size_t Biomol::PDBData::getNumRecords() const
{
	return data.size();
}

bool Biomol::PDBData::isEmpty() const
{
	return data.empty();
}

bool Biomol::PDBData::containsRecord(const RecordType& type) const
{
	return (data.find(type) != data.end());
}

Biomol::PDBData::RecordIterator Biomol::PDBData::getRecord(const RecordType& type)
{
	return data.find(type);
}

Biomol::PDBData::ConstRecordIterator Biomol::PDBData::getRecord(const RecordType& type) const
{
	return data.find(type);
}

std::string& Biomol::PDBData::getData(const RecordType& type)
{
	RecordIterator it = data.find(type);

	if (it == data.end()) 
		throw Base::ItemNotFound("PDBData: data record not found");
	
	return (*it).second;
}

const std::string& Biomol::PDBData::getData(const RecordType& type) const
{
	ConstRecordIterator it = data.find(type);

	if (it == data.end()) 
		throw Base::ItemNotFound("PDBData: data record not found");
	
	return (*it).second;
}

void Biomol::PDBData::removeRecord(const RecordIterator& it)
{
	data.erase(it);
}
		
bool Biomol::PDBData::removeRecord(const RecordType& type)
{
	return (data.erase(type) > 0);
}

Biomol::PDBData::RecordIterator Biomol::PDBData::setRecord(const Record& rec)
{
	RecordIterator lb = data.lower_bound(rec.first);

	if (lb == data.end() || data.key_comp()(rec.first, (*lb).first))
		return data.insert(lb, rec);

	(*lb).second = rec.second;

	return lb;
}

Biomol::PDBData::RecordIterator Biomol::PDBData::setRecord(const RecordType& type, const std::string& data)
{
	return setRecord(Record(type, data));
}

Biomol::PDBData::ConstRecordIterator Biomol::PDBData::getRecordsBegin() const
{
	return data.begin();
}

Biomol::PDBData::RecordIterator Biomol::PDBData::getRecordsBegin()
{
	return data.begin();
}

Biomol::PDBData::ConstRecordIterator Biomol::PDBData::getRecordsEnd() const
{
	return data.end();
}

Biomol::PDBData::RecordIterator Biomol::PDBData::getRecordsEnd()
{
	return data.end();
}
