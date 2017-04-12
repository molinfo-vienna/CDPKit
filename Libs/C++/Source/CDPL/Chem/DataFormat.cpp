/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormat.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Config.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/JMEMoleculeInputHandler.hpp"
#include "CDPL/Chem/JMEReactionInputHandler.hpp"
#include "CDPL/Chem/JMEMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/JMEReactionOutputHandler.hpp"
#include "CDPL/Chem/MOLMoleculeInputHandler.hpp"
#include "CDPL/Chem/MOLMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SDFMoleculeInputHandler.hpp"
#include "CDPL/Chem/SDFMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/RXNReactionInputHandler.hpp"
#include "CDPL/Chem/RXNReactionOutputHandler.hpp"
#include "CDPL/Chem/RDFReactionInputHandler.hpp"
#include "CDPL/Chem/RDFReactionOutputHandler.hpp"
#include "CDPL/Chem/SMILESMoleculeInputHandler.hpp"
#include "CDPL/Chem/SMILESReactionInputHandler.hpp"
#include "CDPL/Chem/SMILESMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SMILESReactionOutputHandler.hpp"
#include "CDPL/Chem/SMARTSMoleculeInputHandler.hpp"
#include "CDPL/Chem/SMARTSReactionInputHandler.hpp"
#include "CDPL/Chem/SMARTSMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SMARTSReactionOutputHandler.hpp"
#include "CDPL/Chem/INCHIMoleculeInputHandler.hpp"
#include "CDPL/Chem/INCHIMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/CDFMoleculeInputHandler.hpp"
#include "CDPL/Chem/CDFMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/CDFReactionInputHandler.hpp"
#include "CDPL/Chem/CDFReactionOutputHandler.hpp"
#include "CDPL/Chem/MOL2MoleculeInputHandler.hpp"
#include "CDPL/Chem/MOL2MolecularGraphOutputHandler.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Chem/SDFGZMoleculeInputHandler.hpp"
#include "CDPL/Chem/SDFGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SDFBZ2MoleculeInputHandler.hpp"
#include "CDPL/Chem/SDFBZ2MolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/RDFGZReactionInputHandler.hpp"
#include "CDPL/Chem/RDFGZReactionOutputHandler.hpp"
#include "CDPL/Chem/RDFBZ2ReactionInputHandler.hpp"
#include "CDPL/Chem/RDFBZ2ReactionOutputHandler.hpp"
#include "CDPL/Chem/CDFGZMoleculeInputHandler.hpp"
#include "CDPL/Chem/CDFGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/CDFBZ2MoleculeInputHandler.hpp"
#include "CDPL/Chem/CDFBZ2MolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/CDFGZReactionInputHandler.hpp"
#include "CDPL/Chem/CDFGZReactionOutputHandler.hpp"
#include "CDPL/Chem/CDFBZ2ReactionInputHandler.hpp"
#include "CDPL/Chem/CDFBZ2ReactionOutputHandler.hpp"
#include "CDPL/Chem/SMILESGZMoleculeInputHandler.hpp"
#include "CDPL/Chem/SMILESGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SMILESBZ2MoleculeInputHandler.hpp"
#include "CDPL/Chem/SMILESBZ2MolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/SMILESGZReactionInputHandler.hpp"
#include "CDPL/Chem/SMILESGZReactionOutputHandler.hpp"
#include "CDPL/Chem/SMILESBZ2ReactionInputHandler.hpp"
#include "CDPL/Chem/SMILESBZ2ReactionOutputHandler.hpp"
#include "CDPL/Chem/MOL2GZMoleculeInputHandler.hpp"
#include "CDPL/Chem/MOL2GZMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/MOL2BZ2MoleculeInputHandler.hpp"
#include "CDPL/Chem/MOL2BZ2MolecularGraphOutputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)


namespace
{

	const char* jmeFileExtensions[]       = { "jme" };
	const char* molFileExtensions[]       = { "mol" };
	const char* sdfFileExtensions[]       = { "sdf", "sd" };
	const char* sdfGzFileExtensions[]     = { "sdf.gz", "sd.gz", "sdz" };
	const char* sdfBz2FileExtensions[]    = { "sdf.bz2", "sd.bz2" };
	const char* rxnFileExtensions[]       = { "rxn" };
	const char* rdfFileExtensions[]       = { "rdf", "rd" };
	const char* rdfGzFileExtensions[]     = { "rdf.gz", "rd.gz", "rdz" };
	const char* rdfBz2FileExtensions[]    = { "rdf.bz2", "rd.bz2" };
	const char* smilesFileExtensions[]    = { "smi" };
	const char* smilesGzFileExtensions[]  = { "smi.gz" };
	const char* smilesBz2FileExtensions[] = { "smi.bz2" };
	const char* smartsFileExtensions[]    = { "sma" };
	const char* inchiFileExtensions[]     = { "inchi", "ichi" };
	const char* cdfFileExtensions[]       = { "cdf" };
	const char* cdfGzFileExtensions[]     = { "cdf.gz" };
	const char* cdfBz2FileExtensions[]    = { "cdf.bz2" };
	const char* mol2FileExtensions[]      = { "mol2" };
	const char* mol2GzFileExtensions[]    = { "mol2.gz" };
	const char* mol2Bz2FileExtensions[]   = { "mol2.bz2" };
}


using namespace CDPL;

		
const Base::DataFormat Chem::DataFormat::JME("JME", "JME Molecular Editor String", "", 
											 jmeFileExtensions, jmeFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL("MOL", "MDL Molfile", "chemical/x-mdl-molfile", 
											 molFileExtensions, molFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SDF("SDF", "MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfFileExtensions, sdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::SDF_GZ("SDF_GZ", "GZip-Compressed MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfGzFileExtensions, sdfGzFileExtensions + 3, true);
const Base::DataFormat Chem::DataFormat::SDF_BZ2("SDF_BZ2", "BZip2-Compressed MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfBz2FileExtensions, sdfBz2FileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::RXN("RXN", "MDL Reaction File", "chemical/x-mdl-rxnfile", 
											 rxnFileExtensions, rxnFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::RDF("RDF", "MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfFileExtensions, rdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::RDF_GZ("RDF_GZ", "GZip-Compressed MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfGzFileExtensions, rdfGzFileExtensions + 3, true);
const Base::DataFormat Chem::DataFormat::RDF_BZ2("RDF_BZ2", "BZip2-Compressed MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfBz2FileExtensions, rdfBz2FileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::SMILES("SMILES", "Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesFileExtensions, smilesFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMILES_GZ("SMILES_GZ", "GZip-Compressed Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesGzFileExtensions, smilesGzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMILES_BZ2("SMILES_BZ2", "BZip2-Compressed Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesBz2FileExtensions, smilesBz2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMARTS("SMARTS", "Daylight SMARTS String", "", 
												smartsFileExtensions, smartsFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::INCHI("INCHI", "IUPAC International Chemical Identifier", "chemical/x-inchi", 
											   inchiFileExtensions, inchiFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::CDF("CDF", "Native CDPL-Format", "", 
											 cdfFileExtensions, cdfFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::CDF_GZ("CDF_GZ", "GZip-Compressed Native CDPL-Format", "", 
											 cdfGzFileExtensions, cdfGzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::CDF_BZ2("CDF_BZ2", "BZip2-Compressed Native CDPL-Format", "", 
											 cdfBz2FileExtensions, cdfBz2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL2("MOL2", "Native CDPL-Format", "", 
											 mol2FileExtensions, mol2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL2_GZ("MOL2_GZ", "GZip-Compressed Native CDPL-Format", "", 
											 mol2GzFileExtensions, mol2GzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL2_BZ2("MOL2_BZ2", "BZip2-Compressed Native CDPL-Format", "", 
											 mol2Bz2FileExtensions, mol2Bz2FileExtensions + 1, true);

namespace CDPL
{

	namespace Chem
	{

		void initDataFormats() {}
	}
}


namespace
{

	struct Init 
	{

		Init() {
			using namespace Base;
			using namespace Chem;

			static const JMEMoleculeInputHandler           jmeMolInputHandler;
			static const MOLMoleculeInputHandler           molMolInputHandler;
			static const SDFMoleculeInputHandler           sdfMolInputHandler;
			static const SMILESMoleculeInputHandler        smilesMolInputHandler;
			static const SMARTSMoleculeInputHandler        smartsMolInputHandler;
			static const INCHIMoleculeInputHandler         inchiMolInputHandler;
			static const CDFMoleculeInputHandler           cdfMolInputHandler;
			static const MOL2MoleculeInputHandler          mol2MolInputHandler;

			static const JMEMolecularGraphOutputHandler    jmeMolGraphOutputHandler;
			static const MOLMolecularGraphOutputHandler    molMolGraphOutputHandler;
			static const SDFMolecularGraphOutputHandler    sdfMolGraphOutputHandler;
			static const SMILESMolecularGraphOutputHandler smilesMolGraphOutputHandler;
			static const SMARTSMolecularGraphOutputHandler smartsMolGraphOutputHandler;
			static const INCHIMolecularGraphOutputHandler  inchiMolGraphOutputHandler;
			static const CDFMolecularGraphOutputHandler    cdfMolGraphOutputHandler;
			static const MOL2MolecularGraphOutputHandler   mol2MolGraphOutputHandler;

			static const JMEReactionInputHandler           jmeRxnInputHandler;
			static const RXNReactionInputHandler           rxnRxnInputHandler;
			static const RDFReactionInputHandler           rdfRxnInputHandler;
			static const SMILESReactionInputHandler        smilesRxnInputHandler;
			static const SMARTSReactionInputHandler        smartsRxnInputHandler;
			static const CDFReactionInputHandler           cdfRxnInputHandler;

			static const JMEReactionOutputHandler          jmeRxnOutputHandler;
			static const RXNReactionOutputHandler          rxnRxnOutputHandler;
			static const RDFReactionOutputHandler          rdfRxnOutputHandler;
			static const SMILESReactionOutputHandler       smilesRxnOutputHandler;
			static const SMARTSReactionOutputHandler       smartsRxnOutputHandler;
			static const CDFReactionOutputHandler          cdfRxnOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(jmeMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(sdfMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(molMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smartsMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(inchiMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(cdfMolInputHandler);

			DataIOManager<MolecularGraph>::registerOutputHandler(jmeMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(sdfMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(molMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smartsMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(inchiMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(cdfMolGraphOutputHandler);

			DataIOManager<Reaction>::registerInputHandler(jmeRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rxnRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rdfRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smartsRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(cdfRxnInputHandler);

			DataIOManager<Reaction>::registerOutputHandler(jmeRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rxnRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rdfRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smartsRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(cdfRxnOutputHandler);

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

			static const SDFGZMoleculeInputHandler         sdfGzMolInputHandler;
			static const SDFBZ2MoleculeInputHandler        sdfBz2MolInputHandler;
			static const CDFGZMoleculeInputHandler         cdfGzMolInputHandler;
			static const CDFBZ2MoleculeInputHandler        cdfBz2MolInputHandler;
			static const SMILESGZMoleculeInputHandler      smilesGzMolInputHandler;
			static const SMILESBZ2MoleculeInputHandler     smilesBz2MolInputHandler;
			static const MOL2GZMoleculeInputHandler        mol2GzMolInputHandler;
			static const MOL2BZ2MoleculeInputHandler       mol2Bz2MolInputHandler;

			static const SDFGZMolecularGraphOutputHandler     sdfGzMolGraphOutputHandler;
			static const SDFBZ2MolecularGraphOutputHandler    sdfBz2MolGraphOutputHandler;
			static const CDFGZMolecularGraphOutputHandler     cdfGzMolGraphOutputHandler;
			static const CDFBZ2MolecularGraphOutputHandler    cdfBz2MolGraphOutputHandler;
			static const SMILESGZMolecularGraphOutputHandler  smilesGzMolGraphOutputHandler;
			static const SMILESBZ2MolecularGraphOutputHandler smilesBz2MolGraphOutputHandler;
			static const MOL2GZMolecularGraphOutputHandler    mol2GzMolGraphOutputHandler;
			static const MOL2BZ2MolecularGraphOutputHandler   mol2Bz2MolGraphOutputHandler;

			static const RDFGZReactionInputHandler         rdfGzRxnInputHandler;
			static const RDFBZ2ReactionInputHandler        rdfBz2RxnInputHandler;
			static const SMILESGZReactionInputHandler      smilesGzRxnInputHandler;
			static const SMILESBZ2ReactionInputHandler     smilesBz2RxnInputHandler;
			static const CDFGZReactionInputHandler         cdfGzRxnInputHandler;
			static const CDFBZ2ReactionInputHandler        cdfBz2RxnInputHandler;

			static const RDFGZReactionOutputHandler        rdfGzRxnOutputHandler;
			static const RDFBZ2ReactionOutputHandler       rdfBz2RxnOutputHandler;
			static const SMILESGZReactionOutputHandler     smilesGzRxnOutputHandler;
			static const SMILESBZ2ReactionOutputHandler    smilesBz2RxnOutputHandler;
			static const CDFGZReactionOutputHandler        cdfGzRxnOutputHandler;
			static const CDFBZ2ReactionOutputHandler       cdfBz2RxnOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(sdfGzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(sdfBz2MolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(cdfGzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(cdfBz2MolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesGzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesBz2MolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(mol2GzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(mol2Bz2MolInputHandler);

			DataIOManager<MolecularGraph>::registerOutputHandler(sdfGzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(sdfBz2MolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(cdfGzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(cdfBz2MolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesGzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesBz2MolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(mol2GzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(mol2Bz2MolGraphOutputHandler);

			DataIOManager<Reaction>::registerInputHandler(rdfGzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rdfBz2RxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesGzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesBz2RxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(cdfGzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(cdfBz2RxnInputHandler);

			DataIOManager<Reaction>::registerOutputHandler(rdfGzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rdfBz2RxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesGzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesBz2RxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(cdfGzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(cdfBz2RxnOutputHandler);

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
