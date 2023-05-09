/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriver.cpp 
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

#include "CDPL/ConfGen/TorsionDriver.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "TorsionDriverImpl.hpp"


using namespace CDPL;


ConfGen::TorsionDriver::TorsionDriver(): 
    impl(new TorsionDriverImpl())
{}

ConfGen::TorsionDriver::~TorsionDriver()
{}

const ConfGen::TorsionDriverSettings& ConfGen::TorsionDriver::getSettings() const
{
    return impl->getSettings();
}

ConfGen::TorsionDriverSettings& ConfGen::TorsionDriver::getSettings()
{
    return impl->getSettings();
}

void ConfGen::TorsionDriver::clearTorsionLibraries()
{
	impl->clearTorsionLibraries();
}

void ConfGen::TorsionDriver::addTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
	impl->addTorsionLibrary(lib);
}

void ConfGen::TorsionDriver::setAbortCallback(const CallbackFunction& func)
{
	impl->setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriver::getAbortCallback() const
{
	return impl->getAbortCallback();
}

void ConfGen::TorsionDriver::setTimeoutCallback(const CallbackFunction& func)
{
	impl->setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriver::getTimeoutCallback() const
{
	return impl->getTimeoutCallback();
}

void ConfGen::TorsionDriver::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
	impl->setLogMessageCallback(func);
}

const ConfGen::LogMessageCallbackFunction& ConfGen::TorsionDriver::getLogMessageCallback() const
{
	return impl->getLogMessageCallback();
}

unsigned int ConfGen::TorsionDriver::setup(const Chem::MolecularGraph& molgraph)
{
	impl->setup(molgraph);

	if (!impl->setMMFF94Parameters())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask)
{
	impl->setup(molgraph, bond_mask);

	if (!impl->setMMFF94Parameters())
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	return ReturnCode::SUCCESS;
}

void ConfGen::TorsionDriver::clearInputCoordinates()
{
	impl->clearInputCoordinates();
}

void ConfGen::TorsionDriver::clearInputCoordinates(std::size_t frag_idx)
{
	if (frag_idx >= impl->getNumFragments())
		throw Base::IndexError("TorsionDriver: fragment index out of bounds");

	impl->clearInputCoordinates(frag_idx);
}

void ConfGen::TorsionDriver::addInputCoordinates(const Math::Vector3DArray& coords)
{
	impl->addInputCoordinates(coords);
}

void ConfGen::TorsionDriver::addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
	if (frag_idx >= impl->getNumFragments())
		throw Base::IndexError("TorsionDriver: fragment index out of bounds");

	impl->addInputCoordinates(coords, frag_idx);
}

void ConfGen::TorsionDriver::addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
	if (frag_idx >= impl->getNumFragments())
		throw Base::IndexError("TorsionDriver: fragment index out of bounds");

	impl->addInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriver::addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
	if (frag_idx >= impl->getNumFragments())
		throw Base::IndexError("TorsionDriver: fragment index out of bounds");

	impl->addInputCoordinates(conf_data, frag_idx);
}

std::size_t ConfGen::TorsionDriver::getNumFragments() const
{
	return impl->getNumFragments();
}

const Chem::Fragment& ConfGen::TorsionDriver::getFragment(std::size_t idx) const
{
	if (idx >= impl->getNumFragments())
		throw Base::IndexError("TorsionDriver: fragment index out of bounds");

	return impl->getFragment(idx);
}

unsigned int ConfGen::TorsionDriver::generateConformers()
{
	return impl->generateConformers();
}

std::size_t ConfGen::TorsionDriver::getNumConformers() const
{
	return impl->getNumConformers();
}

const ConfGen::ConformerData& ConfGen::TorsionDriver::getConformer(std::size_t idx) const
{
	if (idx >= impl->getNumConformers())
		throw Base::IndexError("TorsionDriver: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::ConformerData& ConfGen::TorsionDriver::getConformer(std::size_t idx)
{
	if (idx >= impl->getNumConformers())
		throw Base::IndexError("TorsionDriver: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::TorsionDriver::ConstConformerIterator ConfGen::TorsionDriver::getConformersBegin() const
{
	return impl->getConformersBegin();
}

ConfGen::TorsionDriver::ConstConformerIterator ConfGen::TorsionDriver::getConformersEnd() const
{
	return impl->getConformersEnd();
}

ConfGen::TorsionDriver::ConformerIterator ConfGen::TorsionDriver::getConformersBegin()
{
	return impl->getConformersBegin();
}

ConfGen::TorsionDriver::ConformerIterator ConfGen::TorsionDriver::getConformersEnd()
{
	return impl->getConformersEnd();
}
