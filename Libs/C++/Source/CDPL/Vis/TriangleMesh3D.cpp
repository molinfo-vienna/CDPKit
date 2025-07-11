/* 
 * TriangleMesh3D.cpp 
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

#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/Shape3DVisitor.hpp"


using namespace CDPL;


Vis::TriangleMesh3D::TriangleMesh3D() {}

Vis::TriangleMesh3D::TriangleMesh3D(const TriangleMesh3D& mesh)
{
    // TODO
}

Vis::Shape3D::SharedPointer Vis::TriangleMesh3D::clone() const
{
    return Shape3D::SharedPointer(new TriangleMesh3D(*this));
}

void Vis::TriangleMesh3D::accept(Shape3DVisitor& visitor) const
{
    visitor.visit(*this);
}
