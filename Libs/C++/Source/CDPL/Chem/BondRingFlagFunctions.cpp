/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondRingFlagFunctions.cpp 
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

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondProperty.hpp"


using namespace CDPL; 


bool Chem::getRingFlag(const Bond& bond)
{
    return bond.getProperty<bool>(BondProperty::RING_FLAG);
}

void Chem::setRingFlag(Bond& bond, bool in_ring)
{
    bond.setProperty(BondProperty::RING_FLAG, in_ring);
}

void Chem::clearRingFlag(Bond& bond)
{
    bond.removeProperty(BondProperty::RING_FLAG);
}

bool Chem::hasRingFlag(const Bond& bond)
{
    return bond.isPropertySet(BondProperty::RING_FLAG);
}
