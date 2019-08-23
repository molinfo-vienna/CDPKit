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

#include <boost/lexical_cast.hpp>

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


const unsigned int ConfGen::FragmentLibraryGenerator::DEF_FORCE_FIELD_TYPE;


ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(): 
	fragLib(), fragSSSR(new Chem::SmallestSetOfSmallestRings())
{
	performStrictAtomTyping(true);
	setForceFieldType(DEF_FORCE_FIELD_TYPE);
}

ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib): 
	fragLib(lib), fragSSSR(new Chem::SmallestSetOfSmallestRings())
{
	performStrictAtomTyping(true);
	setForceFieldType(DEF_FORCE_FIELD_TYPE);
}

void ConfGen::FragmentLibraryGenerator::setFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	fragLib = lib;
}

const ConfGen::FragmentLibrary::SharedPointer& ConfGen::FragmentLibraryGenerator::getFragmentLibrary() const
{
	return fragLib;
}

void ConfGen::FragmentLibraryGenerator::setForceFieldType(unsigned int type)
{
	if (type == ForceFieldType::MMFF94 || type == ForceFieldType::MMFF94_NO_ESTAT)
		mmff94Parameterizer.setDynamicParameterDefaults();
	else
		mmff94Parameterizer.setStaticParameterDefaults();

	forceFieldType = type;
}
	    
unsigned int ConfGen::FragmentLibraryGenerator::getForceFieldType() const
{
	return forceFieldType;
}

void ConfGen::FragmentLibraryGenerator::performStrictAtomTyping(bool strict)
{
	mmff94Parameterizer.performStrictAtomTyping(strict);
}

bool ConfGen::FragmentLibraryGenerator::strictAtomTypingPerformed() const
{
	return mmff94Parameterizer.strictAtomTypingPerformed();
}

void ConfGen::FragmentLibraryGenerator::setMaxNumStructureGenerationTrials(std::size_t max_num)
{
	fragConfGen.setMaxNumStructureGenerationTrials(max_num);
}

std::size_t ConfGen::FragmentLibraryGenerator::getMaxNumStructureGenerationTrials() const
{
	return fragConfGen.getMaxNumStructureGenerationTrials();
}

void ConfGen::FragmentLibraryGenerator::setMaxNumMinimizationSteps(std::size_t max_num)
{
	fragConfGen.setMaxNumMinimizationSteps(max_num);
}

std::size_t ConfGen::FragmentLibraryGenerator::getMaxNumMinimizationSteps() const
{
	return fragConfGen.getMaxNumMinimizationSteps();
}

void ConfGen::FragmentLibraryGenerator::setMinimizationStopGradientNorm(double grad_norm)
{
	fragConfGen.setMinimizationStopGradientNorm(grad_norm);
}

double ConfGen::FragmentLibraryGenerator::getMinimizationStopGradientNorm() const
{
	return fragConfGen.getMinimizationStopGradientNorm();
}

void ConfGen::FragmentLibraryGenerator::setMinimizationStopEnergyDelta(double e_delta)
{
	fragConfGen.setMinimizationStopEnergyDelta(e_delta);
}

double ConfGen::FragmentLibraryGenerator::getMinimizationStopEnergyDelta() const
{
	return fragConfGen.getMinimizationStopEnergyDelta();
}

void ConfGen::FragmentLibraryGenerator::setTimeout(std::size_t mil_secs)
{
	fragConfGen.setTimeout(mil_secs);
}

std::size_t ConfGen::FragmentLibraryGenerator::getTimeout() const
{
	return fragConfGen.getTimeout();
}

void ConfGen::FragmentLibraryGenerator::reuseExistingCoordinates(bool reuse)
{
	fragConfGen.reuseExistingCoordinates(reuse);
}

bool ConfGen::FragmentLibraryGenerator::existingCoordinatesReused() const
{
	return fragConfGen.existingCoordinatesReused();
}

void ConfGen::FragmentLibraryGenerator::setEnergyWindow(double win_size)
{
	fragConfGen.setEnergyWindow(win_size);
}

double ConfGen::FragmentLibraryGenerator::getEnergyWindow() const
{
	return fragConfGen.getEnergyWindow();
}

void ConfGen::FragmentLibraryGenerator::setRingConformerTrialFactor(std::size_t factor)
{
	fragConfGen.setRingConformerTrialFactor(factor);
}

std::size_t ConfGen::FragmentLibraryGenerator::getRingConformerTrialFactor() const
{
	return fragConfGen.getRingConformerTrialFactor();
}

void ConfGen::FragmentLibraryGenerator::setMinNumRingConformerTrials(std::size_t min_num)
{
	fragConfGen.setMinNumRingConformerTrials(min_num);
}

std::size_t ConfGen::FragmentLibraryGenerator::getMinNumRingConformerTrials() const
{
	return fragConfGen.getMinNumRingConformerTrials();
}

void ConfGen::FragmentLibraryGenerator::setMaxNumRingConformerTrials(std::size_t max_num)
{
	fragConfGen.setMaxNumRingConformerTrials(max_num);
}

std::size_t ConfGen::FragmentLibraryGenerator::getMaxNumRingConformerTrials() const
{
	return fragConfGen.getMaxNumRingConformerTrials();
}
			
void ConfGen::FragmentLibraryGenerator::setMinRMSD(double min_rmsd)
{
	fragConfGen.setMinRMSD(min_rmsd);
}

double ConfGen::FragmentLibraryGenerator::getMinRMSD() const
{
	return fragConfGen.getMinRMSD();
}

void ConfGen::FragmentLibraryGenerator::setMaxNumOutputConformers(std::size_t max_num)
{
	fragConfGen.setMaxNumOutputConformers(max_num);
}

std::size_t ConfGen::FragmentLibraryGenerator::getMaxNumOutputConformers() const
{
	return fragConfGen.getMaxNumOutputConformers();
}

void ConfGen::FragmentLibraryGenerator::setProcessingResultCallback(const ProcessingResultCallbackFunction& func)
{
	resultCallback = func;
}

const ConfGen::FragmentLibraryGenerator::ProcessingResultCallbackFunction& 
ConfGen::FragmentLibraryGenerator::getProcessingResultCallback()
{
	return resultCallback;
}

void ConfGen::FragmentLibraryGenerator::setProcessingErrorCallback(const ProcessingErrorCallbackFunction& func)
{
	errorCallback = func;
}

const ConfGen::FragmentLibraryGenerator::ProcessingErrorCallbackFunction& 
ConfGen::FragmentLibraryGenerator::getProcessingErrorCallback()
{
	return errorCallback;
}

void ConfGen::FragmentLibraryGenerator::setProgressCallback(const ProgressCallbackFunction& func)
{
	fragConfGen.setProgressCallback(func);
}

const ConfGen::FragmentLibraryGenerator::ProgressCallbackFunction& 
ConfGen::FragmentLibraryGenerator::getProgressCallback() const
{
	return fragConfGen.getProgressCallback();
}

void ConfGen::FragmentLibraryGenerator::process(const Chem::MolecularGraph& molgraph)
{
	if (!fragLib)
		return;

	try {
		fragList.generate(molgraph);

	} catch (const std::exception& e) {
		if (errorCallback && 
			errorCallback(molgraph, std::string("FragmentLibraryGenerator: could not perform input fragmentation: ") + e.what()))
			return;

		throw e;
	}

	for (FragmentList::ConstElementIterator it = fragList.getElementsBegin(), end = fragList.getElementsEnd(); it != end; ++it)
		processFragment(*it);
}

void ConfGen::FragmentLibraryGenerator::processFragment(const Chem::MolecularGraph& frag)
{
	using namespace Chem;

	Molecule::SharedPointer fl_entry = addNewLibraryEntry(frag);

	if (!fl_entry) 
		return;
	
	try {
		const unsigned int ia_types = (forceFieldType == ForceFieldType::MMFF94 || forceFieldType == ForceFieldType::MMFF94S ?
									   ForceField::InteractionType::ALL :
									   ForceField::InteractionType::ALL ^ ForceField::InteractionType::ELECTROSTATIC);

		fragSSSR->perceive(fragLibEntry);

		setSSSR(fragLibEntry, fragSSSR);

		mmff94Parameterizer.parameterize(fragLibEntry, mmff94Data, ia_types);

		fragConfGen.generate(fragLibEntry, mmff94Data, perceiveFragmentType(fragLibEntry));

		std::size_t num_confs = fragConfGen.getNumConformers();

		if (num_confs == 0) {
			removeNewLibraryEntry();

			if (errorCallback) 
				errorCallback(fragLibEntry, "FragmentLibraryGenerator: could not generate any conformers");

		} else {
			for (std::size_t i = 0; i < num_confs; i++)
				addConformation(fragLibEntry, fragConfGen.getCoordinates(i));
	
			fl_entry->copy(fragLibEntry);

			replaceAtomStereoReferenceAtoms(*fl_entry, fragLibEntry, 0);
			replaceBondStereoReferenceAtoms(*fl_entry, fragLibEntry, 0, 0);

			fl_entry->clearProperties();

			setName(*fl_entry, boost::lexical_cast<std::string>(fragLibEntry.getHashCode()));
		}

		if (resultCallback)
			resultCallback(fragLibEntry.getHashCode(), fragLibEntry, true, num_confs);

	} catch (const std::exception& e) {
		removeNewLibraryEntry();

		if (errorCallback && 
			errorCallback(fragLibEntry, std::string("FragmentLibraryGenerator: could not generate conformers: ") + e.what()))
			return;

		throw e;
	}
}

Chem::Molecule::SharedPointer ConfGen::FragmentLibraryGenerator::addNewLibraryEntry(const Chem::MolecularGraph& frag)
{
	using namespace Chem;

	try {
		fragLibEntry.create(frag);

	} catch (const std::exception& e) {
		if (errorCallback && 
			errorCallback(frag, std::string("FragmentLibraryGenerator: could not create canonical library fragment: ") + e.what()))
			return Molecule::SharedPointer();

		throw e;
	}

	try {
		boost::lock_guard<boost::mutex> lock(fragLib->getMutex());

		if (fragLib->containsEntry(fragLibEntry.getHashCode())) {
			if (resultCallback)
				resultCallback(fragLibEntry.getHashCode(), fragLibEntry, false, 0);

			return Molecule::SharedPointer();
		}

		Molecule::SharedPointer entry_mol(new BasicMolecule());

		fragLib->addEntry(fragLibEntry.getHashCode(), entry_mol);

		return entry_mol;

	} catch (const std::exception& e) {
		if (errorCallback && 
			errorCallback(fragLibEntry, std::string("FragmentLibraryGenerator: could not process canonical library fragment: ") + e.what()))
			return Molecule::SharedPointer();

		throw e;
	}
}

void ConfGen::FragmentLibraryGenerator::removeNewLibraryEntry() const
{
	boost::lock_guard<boost::mutex> lock(fragLib->getMutex());

	fragLib->removeEntry(fragLibEntry.getHashCode());
}
