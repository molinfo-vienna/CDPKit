/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomCoordinatesFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomProperty.hpp"


using namespace CDPL; 


const Math::Vector2D& Chem::get2DCoordinates(const Atom& atom)
{
    return atom.getProperty<Math::Vector2D>(AtomProperty::COORDINATES_2D);
}

void Chem::set2DCoordinates(Atom& atom, const Math::Vector2D& coords)
{
    atom.setProperty(AtomProperty::COORDINATES_2D, coords);
}

void Chem::clear2DCoordinates(Atom& atom)
{
    atom.removeProperty(AtomProperty::COORDINATES_2D);
}
	
bool Chem::has2DCoordinates(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::COORDINATES_2D);
}

const Math::Vector3D& Chem::get3DCoordinates(const Atom& atom)
{
    return atom.getProperty<Math::Vector3D>(AtomProperty::COORDINATES_3D);
}

void Chem::set3DCoordinates(Atom& atom, const Math::Vector3D& coords)
{
    atom.setProperty(AtomProperty::COORDINATES_3D, coords);
}

void Chem::clear3DCoordinates(Atom& atom)
{
    atom.removeProperty(AtomProperty::COORDINATES_3D);
}
	
bool Chem::has3DCoordinates(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::COORDINATES_3D);
}

const Math::Vector3DArray::SharedPointer& Chem::get3DCoordinatesArray(const Atom& atom)
{
    return atom.getProperty<Math::Vector3DArray::SharedPointer>(AtomProperty::COORDINATES_3D_ARRAY);
}

void Chem::set3DCoordinatesArray(Atom& atom, const Math::Vector3DArray::SharedPointer& coords_array)
{
    atom.setProperty(AtomProperty::COORDINATES_3D_ARRAY, coords_array);
}

void Chem::clear3DCoordinatesArray(Atom& atom)
{
    atom.removeProperty(AtomProperty::COORDINATES_3D_ARRAY);
}
	
bool Chem::has3DCoordinatesArray(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::COORDINATES_3D_ARRAY);
}

