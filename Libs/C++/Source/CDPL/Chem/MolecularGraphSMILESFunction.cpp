/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphSMILESFunction.cpp 
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

#include <sstream>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/SMILESMolecularGraphWriter.hpp"


using namespace CDPL; 


bool Chem::generateSMILES(const MolecularGraph& molgraph, std::string& smiles, bool canonical, 
						  bool ord_h_deplete, unsigned int atom_flags, unsigned int bond_flags)
{
	std::ostringstream oss;
	SMILESMolecularGraphWriter smi_writer(oss);

	if (atom_flags == AtomPropertyFlag::DEFAULT)
		atom_flags = AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::CONFIGURATION;

	if (bond_flags == BondPropertyFlag::DEFAULT)
		bond_flags = BondPropertyFlag::CONFIGURATION;

	setRecordSeparatorParameter(smi_writer, "");
	setOrdinaryHydrogenDepleteParameter(smi_writer, ord_h_deplete);
	setSMILESWriteCanonicalFormParameter(smi_writer, canonical);
	setSMILESMolWriteAtomMappingIDParameter(smi_writer, atom_flags & AtomPropertyFlag::ATOM_MAPPING_ID);
	setSMILESWriteIsotopeParameter(smi_writer, atom_flags & AtomPropertyFlag::ISOTOPE);
	setSMILESWriteAtomStereoParameter(smi_writer, atom_flags & AtomPropertyFlag::CONFIGURATION);
	setSMILESWriteBondStereoParameter(smi_writer, bond_flags & BondPropertyFlag::CONFIGURATION);
	setSMILESWriteRingBondStereoParameter(smi_writer, bond_flags & BondPropertyFlag::CONFIGURATION);
	setSMILESWriteAromaticBondsParameter(smi_writer, bond_flags & BondPropertyFlag::AROMATICITY);
	setSMILESWriteKekuleFormParameter(smi_writer, bond_flags & BondPropertyFlag::ORDER);

	bool result = !(!smi_writer.write(molgraph));

	smiles = oss.str();

	return result;
}
