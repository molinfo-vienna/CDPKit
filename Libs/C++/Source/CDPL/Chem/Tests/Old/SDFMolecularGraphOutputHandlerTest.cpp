/* 
 * SDFMolecularGraphOutputHandlerTest.cpp 
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

#include "CDPL/Chem/JMEMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/DataFormats.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/SDFMoleculeReader.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MolecularGraphProperties.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataWriter.hpp"
#include "CDPL/Base/IntTypes.hpp"


BOOST_AUTO_TEST_CASE(SDFMolecularGraphOutputHandlerTest)
{
    using namespace CDPL;
    using namespace Chem;
    using namespace Base;

    Molecule mol1;
    std::ifstream ifs(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/Morphine.jme").c_str());

    BOOST_CHECK(ifs);
    BOOST_CHECK(JMEMoleculeReader(ifs).read(mol1));

    const DataOutputHandler<MolecularGraph>* handler = DataIOManager<MolecularGraph>::getOutputHandlerByFormat(Chem::DataFormat::SDF);

    BOOST_CHECK(handler);

    BOOST_CHECK(handler->getDataFormat() == Chem::DataFormat::SDF);

    BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByName("sdf") == handler);
    BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByFileExtension("sdf") == handler);
    BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByFileExtension("sd") == handler);
    BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByMimeType("chemical/x-mdl-sdfile") == handler);

    std::ostringstream oss;

    BOOST_CHECK(oss);

    DataWriter<MolecularGraph>::SharedPointer writer_ptr(handler->createWriter(oss));

    Molecule mol2;

    BOOST_CHECK(writer_ptr);
    BOOST_CHECK(writer_ptr->write(mol1));

    std::istringstream iss(oss.str());

    BOOST_CHECK(iss);
    BOOST_CHECK(SDFMoleculeReader(iss).read(mol2));

    BOOST_CHECK(mol1.getNumAtoms() == mol2.getNumAtoms());
    BOOST_CHECK(mol1.getNumBonds() == mol2.getNumBonds());

    BOOST_CHECK(mol1.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE) == 
                mol2.getProperty<Base::uint64>(MolecularGraphProperty::HASH_CODE));
}

