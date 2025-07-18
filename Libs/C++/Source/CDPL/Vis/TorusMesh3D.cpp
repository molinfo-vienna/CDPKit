/* 
 * TorusMesh3D.cpp 
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

#include <cmath>

#include "CDPL/Vis/TorusMesh3D.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"


using namespace CDPL;


Vis::TorusMesh3D::TorusMesh3D(double radius1, double radius2, std::size_t num_sect1,
                              std::size_t num_sect2)
{
    if (num_sect1 < 3)
        return;

    if (num_sect2 < 3)
        return;

    getVertices().reserve(num_sect1 * num_sect2);
    getFaces().reserve(num_sect1 * num_sect2 * 2);

    //auto ang_inc1 = M_PI * 2.0 / num_sect1;
    //auto ang_inc2 = M_PI * 2.0 / num_sect2;

    // TODO
    
    calcVertexFromFaceNormals(*this);
}
