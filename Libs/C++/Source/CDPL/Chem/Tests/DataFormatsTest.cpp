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

#include "CDPL/Chem/DataFormat.hpp"
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
    BOOST_CHECK(DataFormat::SDF.getDescription() == "MDL Structure-Data Format");
    BOOST_CHECK(DataFormat::SDF.getMimeType() == "chemical/x-mdl-sdfile");
    BOOST_CHECK(DataFormat::SDF.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SDF.matchesName("SDF"));
    BOOST_CHECK(DataFormat::SDF.matchesMimeType("chemical/x-mdl-sdfile"));
    BOOST_CHECK(DataFormat::SDF.matchesFileExtension("SDF"));
    BOOST_CHECK(DataFormat::SDF.matchesFileExtension("sd"));

//-----

    BOOST_CHECK(DataFormat::SDF_GZ.getName() == "SDF_GZ");
    BOOST_CHECK(DataFormat::SDF_GZ.getDescription() == "GZip-Compressed MDL Structure-Data Format");
    BOOST_CHECK(DataFormat::SDF_GZ.getMimeType() == "chemical/x-mdl-sdfile");
    BOOST_CHECK(DataFormat::SDF_GZ.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SDF_GZ.matchesName("SDF_GZ"));
    BOOST_CHECK(DataFormat::SDF_GZ.matchesMimeType("chemical/x-mdl-sdfile"));
    BOOST_CHECK(DataFormat::SDF_GZ.matchesFileExtension("SDZ"));
    BOOST_CHECK(DataFormat::SDF_GZ.matchesFileExtension("sdf.Gz"));
    BOOST_CHECK(DataFormat::SDF_GZ.matchesFileExtension("sd.gz"));

//-----

    BOOST_CHECK(DataFormat::SDF_BZ2.getName() == "SDF_BZ2");
    BOOST_CHECK(DataFormat::SDF_BZ2.getDescription() == "BZip2-Compressed MDL Structure-Data Format");
    BOOST_CHECK(DataFormat::SDF_BZ2.getMimeType() == "chemical/x-mdl-sdfile");
    BOOST_CHECK(DataFormat::SDF_BZ2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SDF_BZ2.matchesName("SDF_BZ2"));
    BOOST_CHECK(DataFormat::SDF_BZ2.matchesMimeType("chemical/x-mdl-sdfile"));
    BOOST_CHECK(DataFormat::SDF_BZ2.matchesFileExtension("sdf.bz2"));
    BOOST_CHECK(DataFormat::SDF_BZ2.matchesFileExtension("sd.bZ2"));

//-----

    BOOST_CHECK(DataFormat::RXN.getName() == "RXN");
    BOOST_CHECK(DataFormat::RXN.getDescription() == "MDL Reaction Format");
    BOOST_CHECK(DataFormat::RXN.getMimeType() == "chemical/x-mdl-rxnfile");
    BOOST_CHECK(DataFormat::RXN.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::RXN.matchesName("rxn"));
    BOOST_CHECK(DataFormat::RXN.matchesMimeType("chemical/x-mdl-rxnfile"));
    BOOST_CHECK(DataFormat::RXN.matchesFileExtension("rxn"));

//-----

    BOOST_CHECK(DataFormat::RDF.getName() == "RDF");
    BOOST_CHECK(DataFormat::RDF.getDescription() == "MDL Reaction-Data Format");
    BOOST_CHECK(DataFormat::RDF.getMimeType() == "chemical/x-mdl-rdfile");
    BOOST_CHECK(DataFormat::RDF.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::RDF.matchesName("RDF"));
    BOOST_CHECK(DataFormat::RDF.matchesMimeType("chemical/x-mdl-rdfile"));
    BOOST_CHECK(DataFormat::RDF.matchesFileExtension("rd"));
    BOOST_CHECK(DataFormat::RDF.matchesFileExtension("rdf"));

//-----

    BOOST_CHECK(DataFormat::RDF_GZ.getName() == "RDF_GZ");
    BOOST_CHECK(DataFormat::RDF_GZ.getDescription() == "GZip-Compressed MDL Reaction-Data Format");
    BOOST_CHECK(DataFormat::RDF_GZ.getMimeType() == "chemical/x-mdl-rdfile");
    BOOST_CHECK(DataFormat::RDF_GZ.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::RDF_GZ.matchesName("RDF_GZ"));
    BOOST_CHECK(DataFormat::RDF_GZ.matchesMimeType("chemical/x-mdl-rdfile"));
    BOOST_CHECK(DataFormat::RDF_GZ.matchesFileExtension("rDZ"));
    BOOST_CHECK(DataFormat::RDF_GZ.matchesFileExtension("Rdf.Gz"));
    BOOST_CHECK(DataFormat::RDF_GZ.matchesFileExtension("rD.gz"));

//-----

    BOOST_CHECK(DataFormat::RDF_BZ2.getName() == "RDF_BZ2");
    BOOST_CHECK(DataFormat::RDF_BZ2.getDescription() == "BZip2-Compressed MDL Reaction-Data Format");
    BOOST_CHECK(DataFormat::RDF_BZ2.getMimeType() == "chemical/x-mdl-rdfile");
    BOOST_CHECK(DataFormat::RDF_BZ2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::RDF_BZ2.matchesName("RDF_BZ2"));
    BOOST_CHECK(DataFormat::RDF_BZ2.matchesMimeType("chemical/x-mdl-rdfile"));
    BOOST_CHECK(DataFormat::RDF_BZ2.matchesFileExtension("Rdf.Bz2"));
    BOOST_CHECK(DataFormat::RDF_BZ2.matchesFileExtension("rD.bZ2"));
    
//-----

    BOOST_CHECK(DataFormat::SMILES.getName() == "SMILES");
    BOOST_CHECK(DataFormat::SMILES.getDescription() == "Daylight SMILES Format");
    BOOST_CHECK(DataFormat::SMILES.getMimeType() == "chemical/x-daylight-smiles");
    BOOST_CHECK(DataFormat::SMILES.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SMILES.matchesName("SMILES"));
    BOOST_CHECK(DataFormat::SMILES.matchesMimeType("chemical/x-daylight-smiles"));
    BOOST_CHECK(DataFormat::SMILES.matchesFileExtension("smi"));

//-----

    BOOST_CHECK(DataFormat::SMILES_GZ.getName() == "SMILES_GZ");
    BOOST_CHECK(DataFormat::SMILES_GZ.getDescription() == "GZip-Compressed Daylight SMILES Format");
    BOOST_CHECK(DataFormat::SMILES_GZ.getMimeType() == "chemical/x-daylight-smiles");
    BOOST_CHECK(DataFormat::SMILES_GZ.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SMILES_GZ.matchesName("SMILES_GZ"));
    BOOST_CHECK(DataFormat::SMILES_GZ.matchesMimeType("chemical/x-daylight-smiles"));
    BOOST_CHECK(DataFormat::SMILES_GZ.matchesFileExtension("smi.gz"));

//-----

    BOOST_CHECK(DataFormat::SMILES_BZ2.getName() == "SMILES_BZ2");
    BOOST_CHECK(DataFormat::SMILES_BZ2.getDescription() == "BZip2-Compressed Daylight SMILES Format");
    BOOST_CHECK(DataFormat::SMILES_BZ2.getMimeType() == "chemical/x-daylight-smiles");
    BOOST_CHECK(DataFormat::SMILES_BZ2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SMILES_BZ2.matchesName("SMILES_BZ2"));
    BOOST_CHECK(DataFormat::SMILES_BZ2.matchesMimeType("chemical/x-daylight-smiles"));
    BOOST_CHECK(DataFormat::SMILES_BZ2.matchesFileExtension("smi.bz2"));

//-----

    BOOST_CHECK(DataFormat::SMARTS.getName() == "SMARTS");
    BOOST_CHECK(DataFormat::SMARTS.getDescription() == "Daylight SMARTS Format");
    BOOST_CHECK(DataFormat::SMARTS.getMimeType() == "");
    BOOST_CHECK(DataFormat::SMARTS.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::SMARTS.matchesName("smarts"));
    BOOST_CHECK(DataFormat::SMARTS.matchesMimeType(""));
    BOOST_CHECK(DataFormat::SMARTS.matchesFileExtension("SMA"));

//-----

    BOOST_CHECK(DataFormat::INCHI.getName() == "INCHI");
    BOOST_CHECK(DataFormat::INCHI.getDescription() == "IUPAC International Chemical Identifier");
    BOOST_CHECK(DataFormat::INCHI.getMimeType() == "chemical/x-inchi");
    BOOST_CHECK(DataFormat::INCHI.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::INCHI.matchesName("inCHi"));
    BOOST_CHECK(DataFormat::INCHI.matchesMimeType("chemIcal/X-inchi"));
    BOOST_CHECK(DataFormat::INCHI.matchesFileExtension("iChI"));
    BOOST_CHECK(DataFormat::INCHI.matchesFileExtension("InChI"));

//-----

    BOOST_CHECK(DataFormat::MOL2.getName() == "MOL2");
    BOOST_CHECK(DataFormat::MOL2.getDescription() == "Tripos Sybyl MOL2 Format");
    BOOST_CHECK(DataFormat::MOL2.getMimeType() == "");
    BOOST_CHECK(DataFormat::MOL2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::MOL2.matchesName("Mol2"));
    BOOST_CHECK(DataFormat::MOL2.matchesMimeType(""));
    BOOST_CHECK(DataFormat::MOL2.matchesFileExtension("MOL2"));

//-----

    BOOST_CHECK(DataFormat::MOL2_GZ.getName() == "MOL2_GZ");
    BOOST_CHECK(DataFormat::MOL2_GZ.getDescription() == "GZip-Compressed Tripos Sybyl MOL2 Format");
    BOOST_CHECK(DataFormat::MOL2_GZ.getMimeType() == "");
    BOOST_CHECK(DataFormat::MOL2_GZ.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::MOL2_GZ.matchesName("Mol2_gZ"));
    BOOST_CHECK(DataFormat::MOL2_GZ.matchesMimeType(""));
    BOOST_CHECK(DataFormat::MOL2_GZ.matchesFileExtension("MOL2.GZ"));

//-----

    BOOST_CHECK(DataFormat::MOL2_BZ2.getName() == "MOL2_BZ2");
    BOOST_CHECK(DataFormat::MOL2_BZ2.getDescription() == "BZip2-Compressed Tripos Sybyl MOL2 Format");
    BOOST_CHECK(DataFormat::MOL2_BZ2.getMimeType() == "");
    BOOST_CHECK(DataFormat::MOL2_BZ2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::MOL2_BZ2.matchesName("Mol2_bz2"));
    BOOST_CHECK(DataFormat::MOL2_BZ2.matchesMimeType(""));
    BOOST_CHECK(DataFormat::MOL2_BZ2.matchesFileExtension("MoL2.BZ2"));

//-----

    BOOST_CHECK(DataFormat::CDF.getName() == "CDF");
    BOOST_CHECK(DataFormat::CDF.getDescription() == "Native CDPL Format");
    BOOST_CHECK(DataFormat::CDF.getMimeType() == "");
    BOOST_CHECK(DataFormat::CDF.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::CDF.matchesName("cDF"));
    BOOST_CHECK(DataFormat::CDF.matchesMimeType(""));
    BOOST_CHECK(DataFormat::CDF.matchesFileExtension("CdF"));

//-----

    BOOST_CHECK(DataFormat::CDF_GZ.getName() == "CDF_GZ");
    BOOST_CHECK(DataFormat::CDF_GZ.getDescription() == "GZip-Compressed Native CDPL Format");
    BOOST_CHECK(DataFormat::CDF_GZ.getMimeType() == "");
    BOOST_CHECK(DataFormat::CDF_GZ.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::CDF_GZ.matchesName("Cdf_gZ"));
    BOOST_CHECK(DataFormat::CDF_GZ.matchesMimeType(""));
    BOOST_CHECK(DataFormat::CDF_GZ.matchesFileExtension("CDF.GZ"));

//-----

    BOOST_CHECK(DataFormat::CDF_BZ2.getName() == "CDF_BZ2");
    BOOST_CHECK(DataFormat::CDF_BZ2.getDescription() == "BZip2-Compressed Native CDPL Format");
    BOOST_CHECK(DataFormat::CDF_BZ2.getMimeType() == "");
    BOOST_CHECK(DataFormat::CDF_BZ2.isMultiRecordFormat() == true);

    BOOST_CHECK(DataFormat::CDF_BZ2.matchesName("cdF_bZ2"));
    BOOST_CHECK(DataFormat::CDF_BZ2.matchesMimeType(""));
    BOOST_CHECK(DataFormat::CDF_BZ2.matchesFileExtension("CDF.BZ2")); 
}

