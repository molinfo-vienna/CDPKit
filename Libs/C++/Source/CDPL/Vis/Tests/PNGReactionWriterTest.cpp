/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PNGReactionWriterTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/PNGReactionWriter.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Chem/JMEReactionReader.hpp"
#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Utilities.hpp"


BOOST_AUTO_TEST_CASE(PNGReactionWriterTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Chem;

	BasicReaction rxn;

	std::ofstream os("PNGReactionWriterTest_1.png",
					 std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);

	PNGReactionWriter writer(os);

	initReaction(rxn);

	BOOST_CHECK(writer.write(rxn));

//-----

	std::ifstream is(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/TestRxnData.jme").c_str());

	BOOST_CHECK(is);
	BOOST_CHECK(JMEReactionReader(is).read(rxn));

	initReaction(rxn);

	rxn.getComponent(0).getAtom(16).setProperty(AtomProperty::COLOR, Color::BLUE);
	rxn.getComponent(0).getBond(0).setProperty(BondProperty::COLOR, Color::RED);
	
	os.close();
	os.open("PNGReactionWriterTest_2.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(writer.write(rxn));

//-----

	writer.setParameter(ControlParameter::ATOM_COLOR, Color::MAGENTA);

	os.close();
	os.open("PNGReactionWriterTest_3.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(rxn));

//-----

	writer.setParameter(ControlParameter::VIEWPORT, Rectangle2D(10.0, 10.0, 700.0, 400.0));

	os.close();
	os.open("PNGReactionWriterTest_4.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(rxn));

//-----

	writer.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	os.close();
	os.open("PNGReactionWriterTest_5.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(rxn));

//-----

	writer.removeParameter(ControlParameter::VIEWPORT);
	writer.setParameter(ControlParameter::BACKGROUND_COLOR, Color::LIGHT_GRAY);
	writer.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(50.0));

	os.close();
	os.open("PNGReactionWriterTest_6.png",
			std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	BOOST_CHECK(os);
	BOOST_CHECK(writer.write(rxn));
}

