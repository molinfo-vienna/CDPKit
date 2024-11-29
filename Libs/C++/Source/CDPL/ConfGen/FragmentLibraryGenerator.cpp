/* 
 * FragmentLibraryGenerator.cpp 
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

#include <exception>

#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "UtilityFunctions.hpp"


using namespace CDPL;


ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(): 
    fragLib(), smilesGen(smilesStream), numGenConfs(0)
{
    init();
}

ConfGen::FragmentLibraryGenerator::FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib): 
    fragLib(lib), smilesGen(smilesStream), numGenConfs(0)
{
    init();
}

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

    FragmentLibraryEntry::SharedPointer fl_entry = addNewLibraryEntry(frag, parent);

    if (!fl_entry) 
        return ReturnCode::FRAGMENT_ALREADY_PROCESSED;
    
    try {
        canonFrag.perceiveSSSR();
        perceiveComponents(canonFrag, false);

        smilesStream.str(std::string());
        smilesGen.write(canonFrag);

        fl_entry->setSMILES(smilesStream.str());

        if (getLogMessageCallback()) {
            getLogMessageCallback()("Canon. Fragment: " + fl_entry->getSMILES() + "\n");
            getLogMessageCallback()("Hash Code: " + std::to_string(fl_entry->getHashCode()) + "\n");
        }

        unsigned int ret_code = fragConfGen.generate(canonFrag);
        numGenConfs = fragConfGen.getNumConformers();

        if (numGenConfs == 0) {
            removeNewLibraryEntry();
            return ret_code;
        }

        for (FragmentConformerGenerator::ConformerIterator it = fragConfGen.getConformersBegin(), end = fragConfGen.getConformersEnd(); it != end; ++it) {
            ConformerData::SharedPointer conf_data(new ConformerData());

            conf_data->swap(*it);
            fl_entry->addConformer(conf_data);
        }

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

std::uint64_t ConfGen::FragmentLibraryGenerator::getLibraryEntryHashCode() const
{
    return canonFrag.getHashCode();
}

ConfGen::FragmentLibraryEntry::SharedPointer ConfGen::FragmentLibraryGenerator::addNewLibraryEntry(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& parent)
{
    using namespace Chem;

    canonFrag.create(frag, parent);

    std::lock_guard<std::mutex> lock(fragLib->getMutex());

    if (fragLib->containsEntry(canonFrag.getHashCode())) 
        return FragmentLibraryEntry::SharedPointer();

    FragmentLibraryEntry::SharedPointer entry_ptr(new FragmentLibraryEntry());

    entry_ptr->setHashCode(canonFrag.getHashCode());
    fragLib->addEntry(entry_ptr);

    return entry_ptr;
}

void ConfGen::FragmentLibraryGenerator::removeNewLibraryEntry() const
{
    std::lock_guard<std::mutex> lock(fragLib->getMutex());

    fragLib->removeEntry(canonFrag.getHashCode());
}

void ConfGen::FragmentLibraryGenerator::init()
{    
    setRecordSeparatorParameter(smilesGen, "");
    setOrdinaryHydrogenDepleteParameter(smilesGen, false);
    setSMILESOutputCanonicalFormParameter(smilesGen, false);
    setSMILESMolOutputAtomMappingIDParameter(smilesGen, false);
    setSMILESOutputIsotopeParameter(smilesGen, false);
    setSMILESOutputAtomStereoParameter(smilesGen, true);
    setSMILESOutputBondStereoParameter(smilesGen, true);
    setSMILESOutputRingBondStereoParameter(smilesGen, true);
    setSMILESOutputAromaticBondsParameter(smilesGen, false);
    setSMILESOutputKekuleFormParameter(smilesGen, false);
}

