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


namespace
{

	const char* jmeFileExtensions[]    = { "jme" };
	const char* molFileExtensions[]    = { "mol" };
	const char* sdfFileExtensions[]    = { "sdf", "sd" };
	const char* rxnFileExtensions[]    = { "rxn" };
	const char* rdfFileExtensions[]    = { "rdf", "rd" };
	const char* smilesFileExtensions[] = { "smi" };
	const char* smartsFileExtensions[] = { "sma" };
	const char* inchiFileExtensions[]  = { "inchi", "ichi" };
}


using namespace CDPL;

		
const Base::DataFormat Chem::DataFormat::JME("JME", "JME Molecular Editor String", "", 
											 jmeFileExtensions, jmeFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL("MOL", "MDL Molfile", "chemical/x-mdl-molfile", 
											 molFileExtensions, molFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SDF("SDF", "MDL Structure-Data File", "chemical/x-mdl-sdfile", 
											 sdfFileExtensions, sdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::RXN("RXN", "MDL Reaction File", "chemical/x-mdl-rxnfile", 
											 rxnFileExtensions, rxnFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::RDF("RDF", "MDL Reaction-Data File", "chemical/x-mdl-rdfile", 
											 rdfFileExtensions, rdfFileExtensions + 2, true);
const Base::DataFormat Chem::DataFormat::SMILES("SMILES", "Daylight SMILES String", "chemical/x-daylight-smiles", 
												smilesFileExtensions, smilesFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::SMARTS("SMARTS", "Daylight SMARTS String", "", 
												smartsFileExtensions, smartsFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::INCHI("INCHI", "IUPAC International Chemical Identifier", "chemical/x-inchi", 
											   inchiFileExtensions, inchiFileExtensions + 2, true);

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

			static const JMEMolecularGraphOutputHandler    jmeMolGraphOutputHandler;
			static const MOLMolecularGraphOutputHandler    molMolGraphOutputHandler;
			static const SDFMolecularGraphOutputHandler    sdfMolGraphOutputHandler;
			static const SMILESMolecularGraphOutputHandler smilesMolGraphOutputHandler;
			static const SMARTSMolecularGraphOutputHandler smartsMolGraphOutputHandler;
			static const INCHIMolecularGraphOutputHandler  inchiMolGraphOutputHandler;

			static const JMEReactionInputHandler           jmeRxnInputHandler;
			static const RXNReactionInputHandler           rxnRxnInputHandler;
			static const RDFReactionInputHandler           rdfRxnInputHandler;
			static const SMILESReactionInputHandler        smilesRxnInputHandler;
			static const SMARTSReactionInputHandler        smartsRxnInputHandler;

			static const JMEReactionOutputHandler          jmeRxnOutputHandler;
			static const RXNReactionOutputHandler          rxnRxnOutputHandler;
			static const RDFReactionOutputHandler          rdfRxnOutputHandler;
			static const SMILESReactionOutputHandler       smilesRxnOutputHandler;
			static const SMARTSReactionOutputHandler       smartsRxnOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(jmeMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(sdfMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(molMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smilesMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(smartsMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(inchiMolInputHandler);

			DataIOManager<MolecularGraph>::registerOutputHandler(jmeMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(sdfMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(molMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smilesMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(smartsMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(inchiMolGraphOutputHandler);

			DataIOManager<Reaction>::registerInputHandler(jmeRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rxnRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(rdfRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smilesRxnInputHandler);
			DataIOManager<Reaction>::registerInputHandler(smartsRxnInputHandler);

			DataIOManager<Reaction>::registerOutputHandler(jmeRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rxnRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(rdfRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smilesRxnOutputHandler);
			DataIOManager<Reaction>::registerOutputHandler(smartsRxnOutputHandler);
		}

	} init;
}
