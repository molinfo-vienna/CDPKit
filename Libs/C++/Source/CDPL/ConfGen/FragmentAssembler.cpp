/* 
 * FragmentAssembler.cpp 
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

#include "CDPL/ConfGen/FragmentAssembler.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "FragmentAssemblerImpl.hpp"


using namespace CDPL;


ConfGen::FragmentAssembler::FragmentAssembler(): 
    impl(new FragmentAssemblerImpl())
{}

ConfGen::FragmentAssembler::~FragmentAssembler()
{}
    
const ConfGen::FragmentAssemblerSettings& 
ConfGen::FragmentAssembler::getSettings() const
{
    return impl->getSettings();
}

ConfGen::FragmentAssemblerSettings& 
ConfGen::FragmentAssembler::getSettings()
{
    return impl->getSettings();
}

void ConfGen::FragmentAssembler::clearFragmentLibraries()
{
    impl->clearFragmentLibraries();
}

void ConfGen::FragmentAssembler::addFragmentLibrary(const FragmentLibrary::SharedPointer& lib)
{
    impl->addFragmentLibrary(lib);
}

void ConfGen::FragmentAssembler::setAbortCallback(const CallbackFunction& func)
{
    impl->setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssembler::getAbortCallback() const
{
    return impl->getAbortCallback();
}

void ConfGen::FragmentAssembler::setTimeoutCallback(const CallbackFunction& func)
{
    impl->setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::FragmentAssembler::getTimeoutCallback() const
{
    return impl->getTimeoutCallback();
}

void ConfGen::FragmentAssembler::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
    impl->setLogMessageCallback(func);
}

const ConfGen::LogMessageCallbackFunction& ConfGen::FragmentAssembler::getLogMessageCallback() const
{
    return impl->getLogMessageCallback();
}

unsigned int ConfGen::FragmentAssembler::assemble(const Chem::MolecularGraph& molgraph)
{
    return impl->assemble(molgraph, molgraph);
}
        
std::size_t ConfGen::FragmentAssembler::getNumConformers() const
{
    return impl->getNumConformers();
}

const ConfGen::ConformerData& ConfGen::FragmentAssembler::getConformer(std::size_t idx) const
{
    if (idx >= impl->getNumConformers())
        throw Base::IndexError("FragmentAssembler: conformer index out of bounds");

    return impl->getConformer(idx);
}

ConfGen::ConformerData& ConfGen::FragmentAssembler::getConformer(std::size_t idx)
{
    if (idx >= impl->getNumConformers())
        throw Base::IndexError("FragmentAssembler: conformer index out of bounds");

    return impl->getConformer(idx);
}

ConfGen::FragmentAssembler::ConstConformerIterator ConfGen::FragmentAssembler::getConformersBegin() const
{
    return impl->getConformersBegin();
}

ConfGen::FragmentAssembler::ConstConformerIterator ConfGen::FragmentAssembler::getConformersEnd() const
{
    return impl->getConformersEnd();
}

ConfGen::FragmentAssembler::ConformerIterator ConfGen::FragmentAssembler::getConformersBegin()
{
    return impl->getConformersBegin();
}

ConfGen::FragmentAssembler::ConformerIterator ConfGen::FragmentAssembler::getConformersEnd()
{
    return impl->getConformersEnd();
}

ConfGen::FragmentAssembler::ConstConformerIterator ConfGen::FragmentAssembler::begin() const
{
    return impl->getConformersBegin();
}

ConfGen::FragmentAssembler::ConstConformerIterator ConfGen::FragmentAssembler::end() const
{
    return impl->getConformersEnd();
}

ConfGen::FragmentAssembler::ConformerIterator ConfGen::FragmentAssembler::begin()
{
    return impl->getConformersBegin();
}

ConfGen::FragmentAssembler::ConformerIterator ConfGen::FragmentAssembler::end()
{
    return impl->getConformersEnd();
}
