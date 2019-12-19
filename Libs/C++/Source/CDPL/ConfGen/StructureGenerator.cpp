/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureGenerator.cpp 
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

#include "CDPL/ConfGen/StructureGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"

#include "ConformerGeneratorImpl.hpp"


using namespace CDPL;


ConfGen::StructureGenerator::StructureGenerator(): 
	impl(new ConformerGeneratorImpl())
{
	ConformerGeneratorSettings& cg_settings = impl->getSettings();

	cg_settings.setConformerSamplingMode(ConformerSamplingMode::AUTO);
	cg_settings.setNitrogenEnumerationMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO);
	cg_settings.sampleHeteroAtomHydrogens(false);
	cg_settings.enumerateRings(true);
	cg_settings.includeInputCoordinates(false);
	cg_settings.setMaxNumOutputConformers(1);
}

ConfGen::StructureGenerator::~StructureGenerator() 
{}

const ConfGen::StructureGeneratorSettings& 
ConfGen::StructureGenerator::getSettings() const
{
	return settings;
}

ConfGen::StructureGeneratorSettings& 
ConfGen::StructureGenerator::getSettings()
{
	return settings;
}

void ConfGen::StructureGenerator::clearFragmentLibraries()
{
	impl->clearFragmentLibraries();
}

void ConfGen::StructureGenerator::addFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
	impl->addFragmentLibrary(lib);
}

void ConfGen::StructureGenerator::setTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	impl->setTorsionLibrary(lib);
}

const ConfGen::TorsionLibrary::SharedPointer& ConfGen::StructureGenerator::getTorsionLibrary() const
{
	return impl->getTorsionLibrary();
}

void ConfGen::StructureGenerator::setAbortCallback(const CallbackFunction& func)
{
	impl->setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::StructureGenerator::getAbortCallback() const
{
	return impl->getAbortCallback();
}

void ConfGen::StructureGenerator::setTimeoutCallback(const CallbackFunction& func)
{
	impl->setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::StructureGenerator::getTimeoutCallback() const
{
	return impl->getTimeoutCallback();
}

unsigned int ConfGen::StructureGenerator::generate(const Chem::MolecularGraph& molgraph, ConformerData& conf_data)
{
	return doGenerate(molgraph, conf_data);
}

unsigned int ConfGen::StructureGenerator::generate(const Chem::MolecularGraph& molgraph, Math::Vector3DArray& coords)
{
	return doGenerate(molgraph, coords);
}

template <typename VecArrayType>
unsigned int ConfGen::StructureGenerator::doGenerate(const Chem::MolecularGraph& molgraph, VecArrayType& coords)
{
	ConformerGeneratorSettings& cg_settings = impl->getSettings();

	cg_settings.getFragmentBuildSettings() = settings.getFragmentBuildSettings();
	cg_settings.setMaxNumRefinementIterations(settings.getMaxNumRefinementIterations());
	cg_settings.setRefinementStopGradient(settings.getRefinementStopGradient());
	cg_settings.setMinMacrocycleSize(settings.getMinMacrocycleSize());
	cg_settings.setForceFieldType(settings.getForceFieldType());
	cg_settings.strictForceFieldParameterization(settings.strictForceFieldParameterization());
	cg_settings.setTimeout(settings.getTimeout());
	cg_settings.generateCoordinatesFromScratch(settings.generateCoordinatesFromScratch());

	unsigned int ret_code = impl->generate(molgraph, true);

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	if (impl->getNumConformers() > 0)
		coords.swap(impl->getConformer(0));

	return ReturnCode::SUCCESS;
}
