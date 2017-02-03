/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomModelNumberFunctions.cpp 
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


namespace
{

	const std::size_t DEF_MODEL_NUMBER = 0;
}


std::size_t Biomol::getModelNumber(const Chem::Atom& atom)
{
    return atom.getPropertyOrDefault<std::size_t>(AtomProperty::MODEL_NUMBER, DEF_MODEL_NUMBER);
}

void Biomol::setModelNumber(Chem::Atom& atom, std::size_t model_no)
{
    atom.setProperty(AtomProperty::MODEL_NUMBER, model_no);
}

void Biomol::clearModelNumber(Chem::Atom& atom)
{
    atom.removeProperty(AtomProperty::MODEL_NUMBER);
}

bool Biomol::hasModelNumber(const Chem::Atom& atom)
{
    return atom.isPropertySet(AtomProperty::MODEL_NUMBER);
}
