/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Bond2DStereoFlagFunctions.cpp 
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
#include "CDPL/Chem/BondStereoFlag.hpp"


using namespace CDPL; 


unsigned int Chem::get2DStereoFlag(const Bond& bond)
{
    return bond.getPropertyOrDefault<unsigned int>(BondProperty::STEREO_2D_FLAG, BondStereoFlag::PLAIN);
}

void Chem::set2DStereoFlag(Bond& bond, unsigned int flag)
{
    bond.setProperty(BondProperty::STEREO_2D_FLAG, flag);
}

void Chem::clear2DStereoFlag(Bond& bond)
{
    bond.removeProperty(BondProperty::STEREO_2D_FLAG);
}

bool Chem::has2DStereoFlag(const Bond& bond)
{
    return bond.isPropertySet(BondProperty::STEREO_2D_FLAG);
}
