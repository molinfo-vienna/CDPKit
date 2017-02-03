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

#if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

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

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)


namespace
{

	const char* jmeFileExtensions[]       = { "jme" };
	const char* molFileExtensions[]       = { "mol" };
	const char* sdfFileExtensions[]       = { "sdf", "sd" };
	const char* sdfgzFileExtensions[]     = { "sdf.gz", "sd.gz", "sdz" };
	const char* sdfbz2FileExtensions[]    = { "sdf.bz2", "sd.bz2" };
	const char* rxnFileExtensions[]       = { "rxn" };
	const char* rdfFileExtensions[]       = { "rdf", "rd" };
	const char* rdfgzFileExtensions[]     = { "rdf.gz", "rd.gz", "rdz" };
	const char* rdfbz2FileExtensions[]    = { "rdf.bz2", "rd.bz2" };
	const char* smilesFileExtensions[]    = { "smi" };
	const char* smilesgzFileExtensions[]  = { "smi.gz" };
	const char* smilesbz2FileExtensions[] = { "smi.bz2" };
	const char* smartsFileExtensions[]    = { "sma" };
	const char* inchiFileExtensions[]     = { "inchi", "ichi" };
	const char* cdfFileExtensions[]       = { "cdf" };
	const char* cdfgzFileExtensions[]     = { "cdf.gz" };
	const char* cdfbz2FileExtensions[]    = { "cdf.bz2" };
}


using namespace CDPL;

		
const Base::DataFormat Chem::DataFormat::JME("JME", "JME Molecular Editor String", "", 
											 jmeFileExtensions, jmeFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL("MOL", "MDL Molfile", "chemical/x-mdl-molfile", 
											 molFileExtensions, molFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SDF("SDF", "MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfFileExtensions, sdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::SDF_GZ("SDF_GZ", "GZip-Compressed MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfgzFileExtensions, sdfgzFileExtensions + 3, true);
const Base::DataFormat Chem::DataFormat::SDF_BZ2("SDF_BZ2", "BZip2-Compressed MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfbz2FileExtensions, sdfbz2FileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::RXN("RXN", "MDL Reaction File", "chemical/x-mdl-rxnfile", 
											 rxnFileExtensions, rxnFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::RDF("RDF", "MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfFileExtensions, rdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::RDF_GZ("RDF_GZ", "GZip-Compressed MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfgzFileExtensions, rdfgzFileExtensions + 3, true);
const Base::DataFormat Chem::DataFormat::RDF_BZ2("RDF_BZ2", "BZip2-Compressed MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfbz2FileExtensions, rdfbz2FileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::SMILES("SMILES", "Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesFileExtensions, smilesFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMILES_GZ("SMILES_GZ", "GZip-Compressed Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesgzFileExtensions, smilesgzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMILES_BZ2("SMILES_BZ2", "BZip2-Compressed Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesbz2FileExtensions, smilesbz2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMARTS("SMARTS", "Daylight SMARTS String", "", 
												smartsFileExtensions, smartsFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::INCHI("INCHI", "IUPAC International Chemical Identifier", "chemical/x-inchi", 
											   inchiFileExtensions, inchiFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::CDF("CDF", "Native CDPL-Format", "", 
											 cdfFileExtensions, cdfFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::CDF_GZ("CDF_GZ", "GZip-Compressed Native CDPL-Format", "", 
											 cdfgzFileExtensions, cdfgzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::CDF_BZ2("CDF_BZ2", "BZip2-Compressed Native CDPL-Format", "", 
											 cdfbz2FileExtensions, cdfbz2FileExtensions + 1, true);

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

			static const JMEMolecularGraphOutputHandler    jmeMolGraphOutputHandler;
			static const MOLMolecularGraphOutputHandler    molMolGraphOutputHandler;
			static const SDFMolecularGraphOutputHandler    sdfMolGraphOutputHandler;
			static const SMILESMolecularGraphOutputHandler smilesMolGraphOutputHandler;
			static const SMARTSMolecularGraphOutputHandler smartsMolGraphOutputHandler;
			static const INCHIMolecularGraphOutputHandler  inchiMolGraphOutputHandler;
			static const CDFMolecularGraphOutputHandler    cdfMolGraphOutputHandler;

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

#if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

			static const SDFGZMoleculeInputHandler         sdfgzMolInputHandler;
			static const SDFBZ2MoleculeInputHandler        sdfbz2MolInputHandler;
			static const CDFGZMoleculeInputHandler         cdfgzMolInputHandler;
			static const CDFBZ2MoleculeInputHandler        cdfbz2MolInputHandler;
			static const SMILESGZMoleculeInputHandler      smilesgzMolInputHandler;
			static const SMILESBZ2MoleculeInputHandler     smilesbz2MolInputHandler;

			static const SDFGZMolecularGraphOutputHandler     sdfgzMolGraphOutputHandler;
			static const SDFBZ2MolecularGraphOutputHandler    sdfbz2MolGraphOutputHandler;
			static const CDFGZMolecularGraphOutputHandler     cdfgzMolGraphOutputHandler;
			static const CDFBZ2MolecularGraphOutputHandler    cdfbz2MolGraphOutputHandler;
			static const SMILESGZMolecularGraphOutputHandler  smilesgzMolGraphOutputHandler;
			static const SMILESBZ2MolecularGraphOutputHandler smilesbz2MolGraphOutputHandler;

			static const RDFGZReactionInputHandler         rdfgzRxnInputHandler;
			static const RDFBZ2ReactionInputHandler        rdfbz2RxnInputHandler;
			static const SMILESGZReactionInputHandler      smilesgzRxnInputHandler;
			static const SMILESBZ2ReactionInputHandler     smilesbz2RxnInputHandler;
			static const CDFGZReactionInputHandler         cdfgzRxnInputHandler;
			static const CDFBZ2ReactionInputHandler        cdfbz2RxnInputHandler;

			static const RDFGZReactionOutputHandler        rdfgzRxnOutputHandler;
			static const RDFBZ2ReactionOutputHandler       rdfbz2RxnOutputHandler;
			static const SMILESGZReactionOutputHandler     smilesgzRxnOutputHandler;
			static const SMILESBZ2ReactionOutputHandler    smilesbz2RxnOutputHandler;
			static const CDFGZReactionOutputHandler        cdfgzRxnOutputHandler;
			static const CDFBZ2ReactionOutputHandler       cdfbz2RxnOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(sdfgzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(sdfbz2MolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(cdfgzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(cdfbz2MolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesgzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesbz2MolInputHandler);

			DataIOManager<MolecularGraph>::registerOutputHandler(sdfgzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(sdfbz2MolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(cdfgzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(cdfbz2MolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesgzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesbz2MolGraphOutputHandler);

			DataIOManager<Reaction>::registerInputHandler(rdfgzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rdfbz2RxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesgzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesbz2RxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(cdfgzRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(cdfbz2RxnInputHandler);

			DataIOManager<Reaction>::registerOutputHandler(rdfgzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rdfbz2RxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesgzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesbz2RxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(cdfgzRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(cdfbz2RxnOutputHandler);

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
