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
                              std::size_t num_sect2, double start_angle, double first_sect_size)
{
    if (num_sect1 < 3)
        return;

    if (num_sect2 < 3)
        return;

    auto& vertices = getVertices().getData();
    
    vertices.reserve(num_sect1 * num_sect2);
    getFaces().reserve(num_sect1 * num_sect2 * 2);

    auto ang_inc = (first_sect_size > 0.0 ? (M_PI * 2.0 - first_sect_size) / (num_sect2 - 1) : M_PI * 2.0 / num_sect2);

    for (std::size_t i = 0; i < num_sect2; i++) {
        auto a = start_angle;

        if (i > 0) {
            if (first_sect_size > 0.0)
                a += first_sect_size + (i - 1) * ang_inc;
            else
                a += ang_inc * i;
        }
        
        addVertex(radius2 * std::cos(a) + radius1, 0.0, radius2 * std::sin(a));
    }
        
    ang_inc = M_PI * 2.0 / num_sect1;

    for (std::size_t i = 1; i < num_sect1; i++) {
        auto a = ang_inc * i;
        auto sin_a = std::sin(a);
        auto cos_a = std::cos(a);
        
        for (std::size_t j = 0; j < num_sect2; j++) {
            auto v = vertices[j].getData();
            auto rot_x = cos_a * v[0] + sin_a * v[1];
            auto rot_y = -sin_a * v[0] + cos_a * v[1];

            addVertex(rot_x, rot_y, v[2]);
        }
    }

    for (std::size_t i = 0; i < num_sect1; i++) {
        auto v_offs1 = i * num_sect2;
        auto v_offs2 = ((i + 1) % num_sect1) * num_sect2;
        
        for (std::size_t j = 0; j < num_sect2; j++) {
            addFace(v_offs2 + j, v_offs1 + j, v_offs2 + ((j + 1) % num_sect2));
            addFace(v_offs2 + ((j + 1) % num_sect2), v_offs1 + j, v_offs1 + ((j + 1) % num_sect2));
        }
    }
    
    calcVertexFromFaceNormals(*this);
    setClosed();
}
