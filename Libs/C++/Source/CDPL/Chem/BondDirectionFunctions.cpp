/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondDirectionFunctions.cpp 
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
#include "CDPL/Chem/BondDirection.hpp"


using namespace CDPL; 


unsigned int Chem::getDirection(const Bond& bond)
{
    return bond.getPropertyOrDefault<unsigned int>(BondProperty::DIRECTION, BondDirection::NONE);
}

void Chem::setDirection(Bond& bond, unsigned int dir)
{
    bond.setProperty(BondProperty::DIRECTION, dir);
}

void Chem::clearDirection(Bond& bond)
{
    bond.removeProperty(BondProperty::DIRECTION);
}

bool Chem::hasDirection(const Bond& bond)
{
    return bond.isPropertySet(BondProperty::DIRECTION);
}
