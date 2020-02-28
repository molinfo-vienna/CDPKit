/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGenerator.cpp 
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

#include <string>
#include <exception>

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(): 
	fragLib(), numGenConfs(0)
{}

ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib): 
	fragLib(lib), numGenConfs(0)
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

void ConfGen::FragmentLibraryGenerator::setAbortCallback(const CallbackFunction& func)
{
	fragConfGen.setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentLibraryGenerator::getAbortCallback() const
{
	return fragConfGen.getAbortCallback();
}

void ConfGen::FragmentLibraryGenerator::setTimeoutCallback(const CallbackFunction& func)
{
	fragConfGen.setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentLibraryGenerator::getTimeoutCallback() const
{
	return fragConfGen.getTimeoutCallback();
}

void ConfGen::FragmentLibraryGenerator::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
	fragConfGen.setLogMessageCallback(func);
}

const ConfGen::LogMessageCallbackFunction& ConfGen::FragmentLibraryGenerator::getLogMessageCallback() const
{
	return fragConfGen.getLogMessageCallback();
}

unsigned int ConfGen::FragmentLibraryGenerator::process(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& parent)
{
	using namespace Chem;
	using namespace ConfGen;

	if (!fragLib)
		return ReturnCode::FRAGMENT_LIBRARY_NOT_SET;

	numGenConfs = 0;

	Molecule::SharedPointer fl_entry = addNewLibraryEntry(frag, parent);

	if (!fl_entry) 
		return ReturnCode::FRAGMENT_ALREADY_PROCESSED;
	
	try {
		fragLibEntry.perceiveSSSR();

		unsigned int ret_code = fragConfGen.generate(fragLibEntry);
		numGenConfs = fragConfGen.getNumConformers();
		
		if (numGenConfs == 0) {
			removeNewLibraryEntry();
			return ret_code;
		}

		fl_entry->copy(fragLibEntry);
		fl_entry->clearProperties();

		fragConfGen.setConformers(*fl_entry);
		setName(*fl_entry, boost::lexical_cast<std::string>(fragLibEntry.getHashCode()));

		copyAtomStereoDescriptors(*fl_entry, fragLibEntry, 0);
		copyBondStereoDescriptors(*fl_entry, fragLibEntry, 0, 0);

		return ret_code;

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

Chem::Molecule::SharedPointer ConfGen::FragmentLibraryGenerator::addNewLibraryEntry(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& parent)
{
	using namespace Chem;

	fragLibEntry.create(frag, parent);

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
