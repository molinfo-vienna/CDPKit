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
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFMoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/CDFDataReader.hpp"
#include "CDPL/Biomol/CDFDataWriter.hpp"
#include "CDPL/Biomol/PDBGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/MMTFBZ2MoleculeInputHandler.hpp"
#include "CDPL/Biomol/MMTFBZ2MolecularGraphOutputHandler.hpp"


namespace
{

    const char* pdbFileExtensions[]    = { "pdb", "ent" };
    const char* pdbGzFileExtensions[]  = { "pdb.gz", "ent.gz" };
    const char* pdbBz2FileExtensions[] = { "pdb.bz2", "ent.bz2" };

    const char* mmtfFileExtensions[]    = { "mmtf" };
    const char* mmtfGzFileExtensions[]  = { "mmtf.gz" };
    const char* mmtfBz2FileExtensions[] = { "mmtf.bz2" };
}


using namespace CDPL;

        
const Base::DataFormat Biomol::DataFormat::PDB("PDB", "Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
                                               pdbFileExtensions, pdbFileExtensions + 2, false);
const Base::DataFormat Biomol::DataFormat::PDB_GZ("PDB_GZ", "GZip-Compressed Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
                                               pdbGzFileExtensions, pdbGzFileExtensions + 2, false);
const Base::DataFormat Biomol::DataFormat::PDB_BZ2("PDB_BZ2", "BZip2-Compressed Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
                                               pdbBz2FileExtensions, pdbBz2FileExtensions + 2, false);

const Base::DataFormat Biomol::DataFormat::MMTF("MMTF", "Macromolecular Transmission Format", "chemical/x-mmtf", 
                                               mmtfFileExtensions, mmtfFileExtensions + 1, false);
const Base::DataFormat Biomol::DataFormat::MMTF_GZ("MMTF_GZ", "GZip-Compressed Macromolecular Transmission Format", "chemical/x-mmtf", 
                                               mmtfGzFileExtensions, mmtfGzFileExtensions + 1, false);
const Base::DataFormat Biomol::DataFormat::MMTF_BZ2("MMTF_BZ2", "BZip2-Compressed Macromolecular Transmission Format", "chemical/x-mmtf", 
                                               mmtfBz2FileExtensions, mmtfBz2FileExtensions + 1, false);


namespace CDPL
{

    namespace Biomol
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
            using namespace Biomol;

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new PDBMoleculeInputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PDBMolecularGraphOutputHandler()));

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MMTFMoleculeInputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MMTFMolecularGraphOutputHandler()));
            
            Biomol::CDFDataReader::registerExternalPropertyHandlers();
            Biomol::CDFDataWriter::registerExternalPropertyHandlers();

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new PDBGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new PDBBZ2MoleculeInputHandler()));

            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MMTFGZMoleculeInputHandler()));
            DataIOManager<Molecule>::registerInputHandler(DataIOManager<Molecule>::InputHandlerPointer(new MMTFBZ2MoleculeInputHandler()));

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PDBGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PDBBZ2MolecularGraphOutputHandler()));

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MMTFGZMolecularGraphOutputHandler()));
            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new MMTFBZ2MolecularGraphOutputHandler()));
        }

    } init;
}
