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
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/Biomol/PDBMoleculeInputHandler.hpp"
#include "CDPL/Biomol/PDBMolecularGraphOutputHandler.hpp"


namespace
{

	const char* pdbFileExtensions[]    = { "pdb", "ent" };
}


using namespace CDPL;

		
const Base::DataFormat Biomol::DataFormat::PDB("PDB", "Brookhaven Protein Data Bank Entry", "chemical/x-pdb", 
											   pdbFileExtensions, pdbFileExtensions + 2, false);

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
			using namespace Biomol;
			using namespace Chem;

			static const PDBMoleculeInputHandler           pdbMolInputHandler;
			static const PDBMolecularGraphOutputHandler    pdbMolGraphOutputHandler;

			DataIOManager<Molecule>::registerInputHandler(pdbMolInputHandler);
			DataIOManager<MolecularGraph>::registerOutputHandler(pdbMolGraphOutputHandler);
		}

	} init;
}
