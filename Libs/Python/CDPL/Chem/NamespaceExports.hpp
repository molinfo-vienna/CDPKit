/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NamespaceExports.hpp 
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


#ifndef CDPL_PYTHON_CHEM_NAMESPACEEXPORTS_HPP
#define CDPL_PYTHON_CHEM_NAMESPACEEXPORTS_HPP


namespace CDPLPythonChem
{

	void exportAtomPropertyFlags();
	void exportBondPropertyFlags();
	void exportReactionRoles();
	void exportAtomTypes();
	void exportAtomConfigurations();
	void exportBondConfigurations();
	void exportBondStereoFlags();
	void exportHybridizationStates();
	void exportReactionCenterStates();
	void exportBondDirections();
	void exportRadicalTypes();
	void exportINCHIReturnCodes();
	void exportAtomMatchConstraints();
	void exportBondMatchConstraints();
	void exportMolecularGraphMatchConstraints();
	void exportReactionMatchConstraints();
	void exportMDLDataFormatVersions();
	void exportMDLParities();
	void exportSybylAtomTypes();
	void exportSybylBondTypes();
	void exportMOL2MoleculeTypes();
	void exportMOL2ChargeTypes();
	void exportTautomerizationTypes();
	void exportRECAPRuleIDs();
	void exportRECAPAtomLabels();
	void exportBRICSRuleIDs();
	void exportBRICSAtomLabels();

	void exportEntity3DProperties();
	void exportAtomProperties();
	void exportBondProperties();
	void exportMolecularGraphProperties();
	void exportReactionProperties();
	void exportAtomPropertyDefaults();
	void exportBondPropertyDefaults();
	void exportMolecularGraphPropertyDefaults();
	void exportReactionPropertyDefaults();

	void exportControlParameters();
	void exportControlParameterDefaults();

	void exportDataFormats();
}

#endif // CDPL_PYTHON_CHEM_NAMESPACEEXPORTS_HPP
