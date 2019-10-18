/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriver.cpp 
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

const ConfGen::TorsionDriverSettings& 
ConfGen::TorsionDriver::getSettings() const
{
    return impl->getSettings();
}

ConfGen::TorsionDriverSettings& 
ConfGen::TorsionDriver::getSettings()
{
    return impl->getSettings();
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

unsigned int ConfGen::TorsionDriver::setup(const Chem::MolecularGraph& molgraph)
{
	impl->setup(molgraph, molgraph);

	if (!impl->setMMFF94Parameters(molgraph))
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask, bool is_excl_mask)
{
	impl->setup(molgraph, molgraph, bond_mask, is_excl_mask);

	if (!impl->setMMFF94Parameters(molgraph))
		return ReturnCode::FORCEFIELD_SETUP_FAILED;

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::clearInputCoordinates()
{
	if (!impl->initialized())
		return ReturnCode::UNINITIALIZED;

	impl->clearInputCoordinates();

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::clearInputCoordinates(const Util::BitSet& atom_mask)
{
	if (!impl->initialized())
		return ReturnCode::UNINITIALIZED;

	impl->clearInputCoordinates(atom_mask);

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::addInputCoordinates(const Math::Vector3DArray& coords)
{
	if (!impl->initialized())
		return ReturnCode::UNINITIALIZED;

	impl->addInputCoordinates(coords);

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::addInputCoordinates(const Math::Vector3DArray& coords, const Util::BitSet& atom_mask)
{
	if (!impl->initialized())
		return ReturnCode::UNINITIALIZED;

	impl->addInputCoordinates(coords, atom_mask);

	return ReturnCode::SUCCESS;
}

unsigned int ConfGen::TorsionDriver::drive()
{
	if (!impl->initialized())
		return ReturnCode::UNINITIALIZED;

	return impl->drive();
}

std::size_t ConfGen::TorsionDriver::getNumConformers() const
{
	if (!impl->initialized())
		return 0;

	return impl->getNumConformers();
}

const ConfGen::ConformerData& ConfGen::TorsionDriver::getConformer(std::size_t idx) const
{
	if (idx >= getNumConformers())
		throw Base::IndexError("TorsionDriver: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::ConformerData& ConfGen::TorsionDriver::getConformer(std::size_t idx)
{
	if (idx >= getNumConformers())
		throw Base::IndexError("TorsionDriver: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::TorsionDriver::ConstConformerIterator ConfGen::TorsionDriver::getConformersBegin() const
{
	if (!impl->initialized())
		throw Base::OperationFailed("TorsionDriver: uninitialized");

	return impl->getConformersBegin();
}

ConfGen::TorsionDriver::ConstConformerIterator ConfGen::TorsionDriver::getConformersEnd() const
{
	if (!impl->initialized())
		throw Base::OperationFailed("TorsionDriver: uninitialized");

	return impl->getConformersEnd();
}

ConfGen::TorsionDriver::ConformerIterator ConfGen::TorsionDriver::getConformersBegin()
{
	if (!impl->initialized())
		throw Base::OperationFailed("TorsionDriver: uninitialized");

	return impl->getConformersBegin();
}

ConfGen::TorsionDriver::ConformerIterator ConfGen::TorsionDriver::getConformersEnd()
{
	if (!impl->initialized())
		throw Base::OperationFailed("TorsionDriver: uninitialized");

	return impl->getConformersEnd();
}
