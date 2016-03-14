/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DCoordinatesFunctions.cpp 
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

#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Entity3D.hpp"
#include "CDPL/Chem/Entity3DProperty.hpp"


using namespace CDPL; 


const Math::Vector3D& Chem::get3DCoordinates(const Entity3D& entity)
{
    return entity.getProperty<Math::Vector3D>(Entity3DProperty::COORDINATES_3D);
}

void Chem::set3DCoordinates(Entity3D& entity, const Math::Vector3D& coords)
{
    entity.setProperty(Entity3DProperty::COORDINATES_3D, coords);
}

void Chem::clear3DCoordinates(Entity3D& entity)
{
    entity.removeProperty(Entity3DProperty::COORDINATES_3D);
}
	
bool Chem::has3DCoordinates(const Entity3D& entity)
{
    return entity.isPropertySet(Entity3DProperty::COORDINATES_3D);
}
