/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGenerator.cpp 
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

#include <string>
#include <exception>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(): 
	fragLib(), fragSSSR(new Chem::SmallestSetOfSmallestRings()), numGenConfs(0)
{}

ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib): 
	fragLib(lib), fragSSSR(new Chem::SmallestSetOfSmallestRings()), numGenConfs(0)
{}

void ConfGen::FragmentLibraryGenerator::setFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLib = lib;
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::FragmentLibraryGenerator::getFragmentLibrary() const
{
	return fragLib;
}

ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentLibraryGenerator::getSettings()
{
	return fragConfGen.getSettings();
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentLibraryGenerator::getSettings() const
{
	return fragConfGen.getSettings();
}

void ConfGen::FragmentLibraryGenerator::setProgressCallback(const ProgressCallbackFunction& func)
{
	fragConfGen.setProgressCallback(func);
}

const ConfGen::ProgressCallbackFunction& 
ConfGen::FragmentLibraryGenerator::getProgressCallback() const
{
	return fragConfGen.getProgressCallback();
}

unsigned int ConfGen::FragmentLibraryGenerator::process(const Chem::MolecularGraph& frag)
{
	using namespace Chem;
	using namespace ConfGen;

	if (!fragLib)
		return ReturnCode::FRAGMENT_LIBRARY_NOT_SET;

	numGenConfs = 0;

	Molecule::SharedPointer fl_entry = addNewLibraryEntry(frag);

	if (!fl_entry) 
		return ReturnCode::SUCCESS;
	
	try {
		fragSSSR->perceive(fragLibEntry);

		setSSSR(fragLibEntry, fragSSSR);

		unsigned int ret_code = fragConfGen.generate(fragLibEntry, perceiveFragmentType(fragLibEntry));
		
		if (ret_code != ReturnCode::SUCCESS) {
			removeNewLibraryEntry();
			return ret_code;
		}

		numGenConfs = fragConfGen.getNumConformers();

		std::for_each(fragConfGen.getConformersBegin(), fragConfGen.getConformersEnd(), 
					  boost::bind(&Chem::addConformation, boost::ref(fragLibEntry), _1));

		fl_entry->copy(fragLibEntry);

		copyAtomStereoDescriptors(*fl_entry, fragLibEntry, 0);
		copyBondStereoDescriptors(*fl_entry, fragLibEntry, 0, 0);

		fl_entry->clearProperties();

		setName(*fl_entry, boost::lexical_cast<std::string>(fragLibEntry.getHashCode()));

	} catch (const std::exception& e) {
		removeNewLibraryEntry();
		throw e;
	}

	return ReturnCode::SUCCESS;
}

std::size_t ConfGen::FragmentLibraryGenerator::getNumGeneratedConformers() const
{
	return numGenConfs;
}

Base::uint64 ConfGen::FragmentLibraryGenerator::getLibraryEntryHashCode() const
{
	return fragLibEntry.getHashCode();
}

Chem::Molecule::SharedPointer ConfGen::FragmentLibraryGenerator::addNewLibraryEntry(const Chem::MolecularGraph& frag)
{
	using namespace Chem;

	fragLibEntry.create(frag);

	boost::lock_guard<boost::mutex> lock(fragLib->getMutex());

	if (fragLib->containsEntry(fragLibEntry.getHashCode())) 
		return Chem::Molecule::SharedPointer();

	Molecule::SharedPointer entry_mol(new BasicMolecule());

	fragLib->addEntry(fragLibEntry.getHashCode(), entry_mol);

	return entry_mol;
}

void ConfGen::FragmentLibraryGenerator::removeNewLibraryEntry() const
{
	boost::lock_guard<boost::mutex> lock(fragLib->getMutex());

	fragLib->removeEntry(fragLibEntry.getHashCode());
}
