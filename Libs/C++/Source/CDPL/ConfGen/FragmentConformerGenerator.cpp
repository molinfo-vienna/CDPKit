/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGenerator.cpp 
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

#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "FragmentConformerGeneratorImpl.hpp"


using namespace CDPL;


ConfGen::FragmentConformerGenerator::FragmentConformerGenerator(): 
	impl(new FragmentConformerGeneratorImpl())
{}

ConfGen::FragmentConformerGenerator::~FragmentConformerGenerator() 
{} 

ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentConformerGenerator::getSettings()
{
	return impl->getSettings();
}

const ConfGen::FragmentConformerGeneratorSettings& ConfGen::FragmentConformerGenerator::getSettings() const
{
	return impl->getSettings();
}

void ConfGen::FragmentConformerGenerator::setAbortCallback(const CallbackFunction& func)
{
	impl->setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentConformerGenerator::getAbortCallback() const
{
	return impl->getAbortCallback();
}

void ConfGen::FragmentConformerGenerator::setTimeoutCallback(const CallbackFunction& func)
{
	impl->setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentConformerGenerator::getTimeoutCallback() const
{
	return impl->getTimeoutCallback();
}

void ConfGen::FragmentConformerGenerator::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
	impl->setLogMessageCallback(func);
}

const ConfGen::LogMessageCallbackFunction& ConfGen::FragmentConformerGenerator::getLogMessageCallback() const
{
	return impl->getLogMessageCallback();
}

unsigned int ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph) 
{
	return generate(molgraph, perceiveFragmentType(molgraph));
}

void ConfGen::FragmentConformerGenerator::setConformers(Chem::MolecularGraph& molgraph) const
{
	impl->setConformers(molgraph);
}

unsigned int ConfGen::FragmentConformerGenerator::generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type) 
{
	return impl->generate(molgraph, frag_type);
}

std::size_t ConfGen::FragmentConformerGenerator::getNumConformers() const
{
	return impl->getNumConformers();
}

const ConfGen::ConformerData& ConfGen::FragmentConformerGenerator::getConformer(std::size_t idx) const
{
	if (idx >= impl->getNumConformers())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::ConformerData& ConfGen::FragmentConformerGenerator::getConformer(std::size_t idx)
{
	if (idx >= impl->getNumConformers())
		throw Base::IndexError("FragmentConformerGenerator: conformer index out of bounds");

	return impl->getConformer(idx);
}

ConfGen::FragmentConformerGenerator::ConstConformerIterator ConfGen::FragmentConformerGenerator::getConformersBegin() const
{
    return impl->getConformersBegin();
}

ConfGen::FragmentConformerGenerator::ConstConformerIterator ConfGen::FragmentConformerGenerator::getConformersEnd() const
{
    return impl->getConformersEnd();
}

ConfGen::FragmentConformerGenerator::ConformerIterator ConfGen::FragmentConformerGenerator::getConformersBegin()
{
    return impl->getConformersBegin();
}

ConfGen::FragmentConformerGenerator::ConformerIterator ConfGen::FragmentConformerGenerator::getConformersEnd()
{
    return impl->getConformersEnd();
}
