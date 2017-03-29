/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomResidueSequenceNumberFunctions.cpp 
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

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


long Biomol::getResidueSequenceNumber(const Chem::Atom& atom)
{
    return atom.getProperty<long>(AtomProperty::RESIDUE_SEQUENCE_NUMBER);
}

void Biomol::setResidueSequenceNumber(Chem::Atom& atom, long seq_no)
{
    atom.setProperty(AtomProperty::RESIDUE_SEQUENCE_NUMBER, seq_no);
}

void Biomol::clearResidueSequenceNumber(Chem::Atom& atom)
{
    atom.removeProperty(AtomProperty::RESIDUE_SEQUENCE_NUMBER);
}

bool Biomol::hasResidueSequenceNumber(const Chem::Atom& atom)
{
    return atom.isPropertySet(AtomProperty::RESIDUE_SEQUENCE_NUMBER);
}
