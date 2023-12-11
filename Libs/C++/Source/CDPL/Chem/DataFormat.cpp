/* 
 * DataFormat.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include "CDPL/Chem/CDFMoleculeInputHandler.hpp"
#include "CDPL/Chem/CDFMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/CDFReactionInputHandler.hpp"
#include "CDPL/Chem/CDFReactionOutputHandler.hpp"
#include "CDPL/Chem/MOL2MoleculeInputHandler.hpp"
#include "CDPL/Chem/MOL2MolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/XYZMoleculeInputHandler.hpp"
#include "CDPL/Chem/XYZMolecularGraphOutputHandler.hpp"
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
#include "CDPL/Chem/XYZGZMoleculeInputHandler.hpp"
#include "CDPL/Chem/XYZGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Chem/XYZBZ2MoleculeInputHandler.hpp"
#include "CDPL/Chem/XYZBZ2MolecularGraphOutputHandler.hpp"


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
    const char* xyzFileExtensions[]       = { "xyz" };
    const char* xyzGzFileExtensions[]     = { "xyz.gz" };
    const char* xyzBz2FileExtensions[]    = { "xyz.bz2" };
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
const Base::DataFormat Chem::DataFormat::MOL2("MOL2", "Tripos Sybyl MOL2 File", "", 
                                             mol2FileExtensions, mol2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL2_GZ("MOL2_GZ", "GZip-Compressed Tripos Sybyl MOL2 File", "", 
                                             mol2GzFileExtensions, mol2GzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::MOL2_BZ2("MOL2_BZ2", "BZip2-Compressed Tripos Sybyl MOL2 File", "", 
                                             mol2Bz2FileExtensions, mol2Bz2FileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::XYZ("XYZ", "Atomic Coordinates XYZ File", "", 
                                             xyzFileExtensions, xyzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::XYZ_GZ("XYZ_GZ", "GZip-Compressed Atomic Coordinates XYZ File", "", 
                                             xyzGzFileExtensions, xyzGzFileExtensions + 1, true);
const Base::DataFormat Chem::DataFormat::XYZ_BZ2("XYZ_BZ2", "BZip2-Compressed Atomic Coordinates XYZ File", "", 
                                             xyzBz2FileExtensions, xyzBz2FileExtensions + 1, true);


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

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new JMEMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SDFMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MOLMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SMILESMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SMARTSMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new INCHIMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new CDFMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MOL2MoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new XYZMoleculeInputHandler()));

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new JMEMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SDFMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MOLMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SMILESMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SMARTSMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new INCHIMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new CDFMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MOL2MolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new XYZMolecularGraphOutputHandler()));

            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new JMEReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new RXNReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new RDFReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new SMILESReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new SMARTSReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new CDFReactionInputHandler()));

            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new JMEReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new RXNReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new RDFReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new SMILESReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new SMARTSReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new CDFReactionOutputHandler()));

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SDFGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SDFBZ2MoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new CDFGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new CDFBZ2MoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SMILESGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new SMILESBZ2MoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MOL2GZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MOL2BZ2MoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new XYZGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new XYZBZ2MoleculeInputHandler()));

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SDFGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SDFBZ2MolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new CDFGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new CDFBZ2MolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SMILESGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SMILESBZ2MolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MOL2GZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MOL2BZ2MolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new XYZGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new XYZBZ2MolecularGraphOutputHandler()));

            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new RDFGZReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new RDFBZ2ReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new SMILESGZReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new SMILESBZ2ReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new CDFGZReactionInputHandler()));
            DataIOManager<Reaction>::registerInputHandler(DataIOManager<Reaction>::InputHandlerPointer(new CDFBZ2ReactionInputHandler()));

            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new RDFGZReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new RDFBZ2ReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new SMILESGZReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new SMILESBZ2ReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new CDFGZReactionOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new CDFBZ2ReactionOutputHandler()));
        }

    } init;
}
