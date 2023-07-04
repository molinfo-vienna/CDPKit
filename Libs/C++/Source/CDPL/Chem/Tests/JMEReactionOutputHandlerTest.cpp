/* 
 * JMEReactionOutputHandlerTest.cpp 
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

#include "CDPL/Chem/JMEReactionOutputHandler.hpp"
#include "CDPL/Chem/DataFormats.hpp"
#include "CDPL/Chem/JMEReactionReader.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionProperties.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/IntTypes.hpp"


BOOST_AUTO_TEST_CASE(JMEReactionOutputHandlerTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;

    Reaction rxn1;
    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/MorphineAcetylation.jme").c_str());

    BOOST_CHECK(ifs);
    BOOST_CHECK(JMEReactionReader(ifs).read(rxn1));

    const DataOutputHandler<Reaction>* handler = DataIOManager<Reaction>::getOutputHandlerByFormat(Chem::DataFormat::JME);

    BOOST_CHECK(handler);

    BOOST_CHECK(handler->getDataFormat() == Chem::DataFormat::JME);

    BOOST_CHECK(DataIOManager<Reaction>::getOutputHandlerByName("jme") == handler);
    BOOST_CHECK(DataIOManager<Reaction>::getOutputHandlerByFileExtension("jme") == handler);

    std::ostringstream oss;

    BOOST_CHECK(oss);

    DataWriter<Reaction>::SharedPointer writer_ptr(handler->createWriter(oss));

    Reaction rxn2;

    BOOST_CHECK(writer_ptr);
    BOOST_CHECK(writer_ptr->write(rxn1));

    std::istringstream iss(oss.str());

    BOOST_CHECK(iss);
    BOOST_CHECK(JMEReactionReader(iss).read(rxn2));

    BOOST_CHECK(rxn1.getNumReactants() == rxn2.getNumReactants());
    BOOST_CHECK(rxn1.getNumAgents() == rxn2.getNumAgents());
    BOOST_CHECK(rxn1.getNumProducts() == rxn2.getNumProducts());

    BOOST_CHECK(rxn1.getProperty<Base::uint64>(ReactionProperty::HASH_CODE) == rxn2.getProperty<Base::uint64>(ReactionProperty::HASH_CODE));
}

