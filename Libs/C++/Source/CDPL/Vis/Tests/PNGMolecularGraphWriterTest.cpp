/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PNGMolecularGraphWriterTest.cpp 
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

#include "CDPL/Vis/PNGMolecularGraphWriter.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Utilities.hpp"


BOOST_AUTO_TEST_CASE(PNGMolecularGraphWriterTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Chem;

	BasicMolecule mol;

	std::ofstream os("PNGMolecularGraphWriterTest_1.png",
					 std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);

	PNGMolecularGraphWriter writer(os);

	initMolecule(mol);

	BOOST_CHECK(writer.write(mol));

//-----

	std::ifstream is(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/TestMolData.jme").c_str());

	BOOST_CHECK(is);
	BOOST_CHECK(JMEMoleculeReader(is).read(mol));

	initMolecule(mol);

	mol.getAtom(16).setProperty(AtomProperty::COLOR, Color::GREEN);
	mol.getBond(0).setProperty(BondProperty::COLOR, Color::RED);
	
	os.close();
	os.open("PNGMolecularGraphWriterTest_2.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(writer.write(mol));

//-----

	writer.setParameter(ControlParameter::BOND_COLOR, Color::BLUE);

	os.close();
	os.open("PNGMolecularGraphWriterTest_3.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(mol));

//-----

	writer.setParameter(ControlParameter::VIEWPORT, Rectangle2D(10.0, 10.0, 300.0, 300.0));

	os.close();
	os.open("PNGMolecularGraphWriterTest_4.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(mol));

//-----

	writer.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	os.close();
	os.open("PNGMolecularGraphWriterTest_5.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(mol));

//-----

	writer.removeParameter(ControlParameter::VIEWPORT);
	writer.setParameter(ControlParameter::BACKGROUND_COLOR, Color::LIGHT_GRAY);
	writer.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(50.0));

	os.close();
	os.open("PNGMolecularGraphWriterTest_6.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(mol));
}

