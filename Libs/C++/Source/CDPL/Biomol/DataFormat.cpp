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
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/CDFDataReader.hpp"
#include "CDPL/Biomol/CDFDataWriter.hpp"

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Biomol/PDBGZMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBGZMolecularGraphOutputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBBZ2MolecularGraphOutputHandler.hpp"

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)


namespace
{

	const char* pdbFileExtensions[]    = { "pdb", "ent" };
	const char* pdbGzFileExtensions[]  = { "pdb.gz", "ent.gz" };
	const char* pdbBz2FileExtensions[] = { "pdb.bz2", "ent.bz2" };
}


using namespace CDPL;

		
const Base::DataFormat Biomol::DataFormat::PDB("PDB", "Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
											   pdbFileExtensions, pdbFileExtensions + 2, false);
const Base::DataFormat Biomol::DataFormat::PDB_GZ("PDB_GZ", "GZip-Compressed Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
											   pdbGzFileExtensions, pdbGzFileExtensions + 2, false);
const Base::DataFormat Biomol::DataFormat::PDB_BZ2("PDB_BZ2", "BZip2-Compressed Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
											   pdbBz2FileExtensions, pdbBz2FileExtensions + 2, false);


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

			static const PDBMoleculeInputHandler           pdbMolInputHandler;
			static const PDBMolecularGraphOutputHandler    pdbMolGraphOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(pdbMolInputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(pdbMolGraphOutputHandler);

			Biomol::CDFDataReader::registerExternalPropertyHandlers();
			Biomol::CDFDataWriter::registerExternalPropertyHandlers();

#if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

			static const PDBGZMoleculeInputHandler           pdbGzMolInputHandler;
			static const PDBBZ2MoleculeInputHandler          pdbBz2MolInputHandler;

			static const PDBGZMolecularGraphOutputHandler    pdbGzMolGraphOutputHandler;
			static const PDBBZ2MolecularGraphOutputHandler   pdbBz2MolGraphOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(pdbGzMolInputHandler);
			DataIOManager<Molecule>::registerInputHandler(pdbBz2MolInputHandler);

			DataIOManager<MolecularGraph>::registerOutputHandler(pdbGzMolGraphOutputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(pdbBz2MolGraphOutputHandler);

#endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)
		}

	} init;
}
