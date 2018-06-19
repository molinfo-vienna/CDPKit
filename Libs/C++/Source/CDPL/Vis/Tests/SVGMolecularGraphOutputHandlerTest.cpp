/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SVGMolecularGraphOutputHandlerTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <fstream>
#include <cstdlib>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/SVGMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataWriter.hpp"

#include "Utilities.hpp"


BOOST_AUTO_TEST_CASE(SVGMolecularGraphOutputHandlerTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Chem;
	using namespace Base;

	const DataOutputHandler<MolecularGraph>::SharedPointer handler = DataIOManager<MolecularGraph>::getOutputHandlerByFormat(Vis::DataFormat::SVG);

	BOOST_CHECK(handler);

	BOOST_CHECK(handler->getDataFormat() == Vis::DataFormat::SVG);

	BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByName("svg") == handler);
	BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByMimeType("image/svg+xml") == handler);
	BOOST_CHECK(DataIOManager<MolecularGraph>::getOutputHandlerByFileExtension("svg") == handler);

	std::fstream os("SVGMolecularGraphOutputHandlerTest.svg", 
					 std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);

	DataWriter<MolecularGraph>::SharedPointer writer_ptr(handler->createWriter(os));

	BOOST_CHECK(writer_ptr);

	BasicMolecule mol;

	std::ifstream is(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/TestMolData.jme").c_str());

	BOOST_CHECK(is);
	BOOST_CHECK(JMEMoleculeReader(is).read(mol));

	initMolecule(mol);

	BOOST_CHECK(writer_ptr->write(mol));
}

