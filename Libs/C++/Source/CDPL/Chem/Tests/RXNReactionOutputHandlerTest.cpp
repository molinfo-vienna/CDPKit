/* 
 * RXNReactionOutputHandlerTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/JMEReactionReader.hpp"
#include "CDPL/Chem/RXNReactionReader.hpp"
#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/DataIOManager.hpp"


BOOST_AUTO_TEST_CASE(RXNReactionOutputHandlerTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;

    BasicReaction rxn1;
    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/MorphineAcetylation.jme").c_str());

    BOOST_CHECK(ifs);
    BOOST_CHECK(JMEReactionReader(ifs).read(rxn1));

    const DataOutputHandler<Reaction>::SharedPointer handler = DataIOManager<Reaction>::getOutputHandlerByFormat(Chem::DataFormat::RXN);

    BOOST_CHECK(handler);

    BOOST_CHECK(handler->getDataFormat() == Chem::DataFormat::RXN);

    BOOST_CHECK(DataIOManager<Reaction>::getOutputHandlerByName("rxn") == handler);
    BOOST_CHECK(DataIOManager<Reaction>::getOutputHandlerByFileExtension("rxn") == handler);
    BOOST_CHECK(DataIOManager<Reaction>::getOutputHandlerByMimeType("chemical/x-mdl-rxnfile") == handler);

    std::stringstream oss;

    BOOST_CHECK(oss);

    DataWriter<Reaction>::SharedPointer writer_ptr(handler->createWriter(oss));

    BasicReaction rxn2;
    
    for (auto& mol : rxn1)
        perceiveComponents(mol, false);

    for (auto& mol : rxn1)
        calcImplicitHydrogenCounts(mol, false);

    for (auto& mol : rxn1)
        perceiveHybridizationStates(mol, false);

    for (auto& mol : rxn1)
        perceiveSSSR(mol, false);

    for (auto& mol : rxn1)
        setRingFlags(mol, false);

    for (auto& mol : rxn1)
        setAromaticityFlags(mol, false);

    for (auto& mol : rxn1)
        calcCIPPriorities(mol, false);

    for (auto& mol : rxn1)
        calcAtomCIPConfigurations(mol, false);

    for (auto& mol : rxn1)
        calcBondCIPConfigurations(mol, false);
    
    BOOST_CHECK(writer_ptr);
    BOOST_CHECK(writer_ptr->write(rxn1));

    std::istringstream iss(oss.str());

    BOOST_CHECK(iss);
    BOOST_CHECK(RXNReactionReader(iss).read(rxn2));

    for (auto& mol : rxn2)
        perceiveComponents(mol, false);

    for (auto& mol : rxn2)
        calcImplicitHydrogenCounts(mol, false);

    for (auto& mol : rxn2)
        perceiveHybridizationStates(mol, false);

    for (auto& mol : rxn2)
        perceiveSSSR(mol, false);

    for (auto& mol : rxn2)
        setRingFlags(mol, false);

    for (auto& mol : rxn2)
        setAromaticityFlags(mol, false);

    for (auto& mol : rxn2)
        calcCIPPriorities(mol, false);

    for (auto& mol : rxn2)
        calcAtomCIPConfigurations(mol, false);

    for (auto& mol : rxn2)
        calcBondCIPConfigurations(mol, false);
    
    BOOST_CHECK(rxn1.getNumComponents(ReactionRole::REACTANT) == rxn2.getNumComponents(ReactionRole::REACTANT));
    BOOST_CHECK(rxn1.getNumComponents(ReactionRole::AGENT) == rxn2.getNumComponents(ReactionRole::AGENT));
    BOOST_CHECK(rxn1.getNumComponents(ReactionRole::PRODUCT) == rxn2.getNumComponents(ReactionRole::PRODUCT));

    BOOST_CHECK(calcHashCode(rxn1) == calcHashCode(rxn2));
}

