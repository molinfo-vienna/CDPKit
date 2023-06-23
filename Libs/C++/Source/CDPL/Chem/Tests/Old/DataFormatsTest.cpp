/* 
 * DataFormatsTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/DataFormats.hpp"
#include "CDPL/Base/DataFormat.hpp"


BOOST_AUTO_TEST_CASE(DataFormatsTest)
{
	using namespace CDPL;
	using namespace Chem;

	BOOST_CHECK(DataFormat::JME.getName() == "JME");
	BOOST_CHECK(DataFormat::JME.getDescription() == "JME Molecular Editor String");
	BOOST_CHECK(DataFormat::JME.getMimeType() == "");
	BOOST_CHECK(DataFormat::JME.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::JME.matchesName("jme"));
	BOOST_CHECK(DataFormat::JME.matchesMimeType(""));
	BOOST_CHECK(DataFormat::JME.matchesFileExtension("jme"));

//-----

	BOOST_CHECK(DataFormat::MOL.getName() == "MOL");
	BOOST_CHECK(DataFormat::MOL.getDescription() == "MDL Molfile");
	BOOST_CHECK(DataFormat::MOL.getMimeType() == "chemical/x-mdl-molfile");
	BOOST_CHECK(DataFormat::MOL.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::MOL.matchesName("Mol"));
	BOOST_CHECK(DataFormat::MOL.matchesMimeType("chemical/x-mdl-molfile"));
	BOOST_CHECK(DataFormat::MOL.matchesFileExtension("MOL"));

//-----

	BOOST_CHECK(DataFormat::SDF.getName() == "SDF");
	BOOST_CHECK(DataFormat::SDF.getDescription() == "MDL Structure-Data File");
	BOOST_CHECK(DataFormat::SDF.getMimeType() == "chemical/x-mdl-sdfile");
	BOOST_CHECK(DataFormat::SDF.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::SDF.matchesName("SDF"));
	BOOST_CHECK(DataFormat::SDF.matchesMimeType("chemical/x-mdl-sdfile"));
	BOOST_CHECK(DataFormat::SDF.matchesFileExtension("SDF"));
	BOOST_CHECK(DataFormat::SDF.matchesFileExtension("sd"));

//-----

	BOOST_CHECK(DataFormat::RXN.getName() == "RXN");
	BOOST_CHECK(DataFormat::RXN.getDescription() == "MDL Reaction File");
	BOOST_CHECK(DataFormat::RXN.getMimeType() == "chemical/x-mdl-rxnfile");
	BOOST_CHECK(DataFormat::RXN.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::RXN.matchesName("rxn"));
	BOOST_CHECK(DataFormat::RXN.matchesMimeType("chemical/x-mdl-rxnfile"));
	BOOST_CHECK(DataFormat::RXN.matchesFileExtension("rxn"));

//-----

	BOOST_CHECK(DataFormat::RDF.getName() == "RDF");
	BOOST_CHECK(DataFormat::RDF.getDescription() == "MDL Reaction-Data File");
	BOOST_CHECK(DataFormat::RDF.getMimeType() == "chemical/x-mdl-rdfile");
	BOOST_CHECK(DataFormat::RDF.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::RDF.matchesName("RDF"));
	BOOST_CHECK(DataFormat::RDF.matchesMimeType("chemical/x-mdl-rdfile"));
	BOOST_CHECK(DataFormat::RDF.matchesFileExtension("rd"));
	BOOST_CHECK(DataFormat::RDF.matchesFileExtension("rdf"));

//-----

	BOOST_CHECK(DataFormat::SMILES.getName() == "SMILES");
	BOOST_CHECK(DataFormat::SMILES.getDescription() == "Daylight SMILES String");
	BOOST_CHECK(DataFormat::SMILES.getMimeType() == "chemical/x-daylight-smiles");
	BOOST_CHECK(DataFormat::SMILES.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::SMILES.matchesName("SMILES"));
	BOOST_CHECK(DataFormat::SMILES.matchesMimeType("chemical/x-daylight-smiles"));
	BOOST_CHECK(DataFormat::SMILES.matchesFileExtension("smi"));

//-----

	BOOST_CHECK(DataFormat::SMARTS.getName() == "SMARTS");
	BOOST_CHECK(DataFormat::SMARTS.getDescription() == "Daylight SMARTS String");
	BOOST_CHECK(DataFormat::SMARTS.getMimeType() == "");
	BOOST_CHECK(DataFormat::SMARTS.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::SMARTS.matchesName("smarts"));
	BOOST_CHECK(DataFormat::SMARTS.matchesMimeType(""));
	BOOST_CHECK(DataFormat::SMARTS.matchesFileExtension("SMA"));

//-----

	BOOST_CHECK(DataFormat::INCHI.getName() == "INCHI");
	BOOST_CHECK(DataFormat::INCHI.getDescription() == "IUPAC International Chemical Identifier");
	BOOST_CHECK(DataFormat::INCHI.getMimeType() == "");
	BOOST_CHECK(DataFormat::INCHI.isMultiRecordFormat() == true);

	BOOST_CHECK(DataFormat::INCHI.matchesName("inCHi"));
	BOOST_CHECK(DataFormat::INCHI.matchesMimeType(""));
	BOOST_CHECK(DataFormat::INCHI.matchesFileExtension("iChI"));
	BOOST_CHECK(DataFormat::INCHI.matchesFileExtension("InChI"));
}

