/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphResidueSequenceNumberFunctions.cpp 
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

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphProperty.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


long Biomol::getResidueSequenceNumber(const Chem::MolecularGraph& molgraph)
{
    return molgraph.getProperty<long>(MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER);
}

void Biomol::setResidueSequenceNumber(Chem::MolecularGraph& molgraph, long seq_no)
{
    molgraph.setProperty(MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER, seq_no);
}

void Biomol::clearResidueSequenceNumber(Chem::MolecularGraph& molgraph)
{
    molgraph.removeProperty(MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER);
}

bool Biomol::hasResidueSequenceNumber(const Chem::MolecularGraph& molgraph)
{
    return molgraph.isPropertySet(MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER);
}
