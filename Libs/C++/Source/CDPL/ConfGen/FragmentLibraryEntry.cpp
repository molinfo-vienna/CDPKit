/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryEntry.cpp 
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

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


ConfGen::FragmentLibraryEntry::FragmentLibraryEntry(): hashCode(0)
{}

void ConfGen::FragmentLibraryEntry::setHashCode(std::uint64_t hash_code)
{
	hashCode = hash_code;
}

std::uint64_t ConfGen::FragmentLibraryEntry::getHashCode() const
{
	return hashCode;
}

void ConfGen::FragmentLibraryEntry::setSMILES(const std::string& smiles)
{
	this->smiles = smiles;
}

const std::string& ConfGen::FragmentLibraryEntry::getSMILES() const
{
	return smiles;
}

void ConfGen::FragmentLibraryEntry::clearConformers()
{
	conformers.clear();
}

std::size_t ConfGen::FragmentLibraryEntry::getNumAtoms() const
{
	if (conformers.empty())
		return 0;

	return conformers[0]->getSize();
}

std::size_t ConfGen::FragmentLibraryEntry::getNumConformers() const
{
	return conformers.size();
}

void ConfGen::FragmentLibraryEntry::addConformer(const ConformerData::SharedPointer& conf_data)
{
	conformers.push_back(conf_data);
}

const ConfGen::ConformerData& ConfGen::FragmentLibraryEntry::getConformer(std::size_t idx) const
{
	if (idx >= conformers.size())
		throw Base::IndexError("FragmentLibraryEntry: conformer index out of bounds");

	return *conformers[idx];
}

ConfGen::ConformerData& ConfGen::FragmentLibraryEntry::getConformer(std::size_t idx)
{
	if (idx >= conformers.size())
		throw Base::IndexError("FragmentLibraryEntry: conformer index out of bounds");

	return *conformers[idx];
}

ConfGen::FragmentLibraryEntry::ConstConformerIterator ConfGen::FragmentLibraryEntry::getConformersBegin() const
{
    return conformers.begin();
}

ConfGen::FragmentLibraryEntry::ConstConformerIterator ConfGen::FragmentLibraryEntry::getConformersEnd() const
{
    return conformers.end();
}

ConfGen::FragmentLibraryEntry::ConformerIterator ConfGen::FragmentLibraryEntry::getConformersBegin()
{
    return conformers.begin();
}

ConfGen::FragmentLibraryEntry::ConformerIterator ConfGen::FragmentLibraryEntry::getConformersEnd()
{
    return conformers.end();
}

const ConfGen::ConformerDataArray& ConfGen::FragmentLibraryEntry:: getData() const
{
	return conformers;
}
