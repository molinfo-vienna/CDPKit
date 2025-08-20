/* 
 * STLObject3DWriter.cpp 
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


#include "StaticInit.hpp"

#include <ostream>
#include <cmath>

#include "CDPL/Vis/STLObject3DWriter.hpp"


using namespace CDPL;


Vis::STLObject3DWriter::STLObject3DWriter(std::ostream& os): 
    output(os), state(os.good()) {}

Base::DataWriter<Vis::Object3D>& Vis::STLObject3DWriter::write(const Object3D& obj)
{
    state = false;

    state = true;
    
    invokeIOCallbacks(1.0);

    return *this;
}

Vis::STLObject3DWriter::operator const void*() const
{
    return (state ? this : nullptr);
}

bool Vis::STLObject3DWriter::operator!() const
{
    return !state;
}
