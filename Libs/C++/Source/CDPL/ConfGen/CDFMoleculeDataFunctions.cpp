/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFMoleculeDataFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ConfGen/CDFMoleculeDataFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/CDFDataReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/LookupKeyDefinition.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


namespace
{

	CDPL_DEFINE_LOOKUP_KEY(CDF_MOLECULE_DATA);
}


const ConfGen::MoleculeDataPointer& ConfGen::getCDFMoleculeData(const Chem::MolecularGraph& molgraph)
{
    return molgraph.getProperty<MoleculeDataPointer>(CDF_MOLECULE_DATA);
}

void ConfGen::setCDFMoleculeData(Chem::MolecularGraph& molgraph, const MoleculeDataPointer& data)
{
    molgraph.setProperty(CDF_MOLECULE_DATA, data);
}

void ConfGen::clearCDFMoleculeData(Chem::MolecularGraph& molgraph)
{
    molgraph.removeProperty(CDF_MOLECULE_DATA);
}

bool ConfGen::hasCDFMoleculeData(const Chem::MolecularGraph& molgraph)
{
    return molgraph.isPropertySet(CDF_MOLECULE_DATA);
}

Chem::MolecularGraph::SharedPointer ConfGen::createMoleculeFromCDFData(const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());
    Base::ControlParameterList ctrl_params;
    CDFDataReader reader(ctrl_params);
 
    setStrictErrorCheckingParameter(ctrl_params, true);

	if (!reader.readMolecule(*mol_ptr, *getCDFMoleculeData(molgraph)))
		throw Base::OperationFailed("createMoleculeFromCDFData(): error while reading CDF molecule data");

	return mol_ptr;
}
