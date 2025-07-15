/* 
 * TriangleMesh3DFunctions.cpp 
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

#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"


using namespace CDPL;


namespace
{

    template <typename V>
    double length(const V& v)
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    template <typename V, typename T>
    void scale(V& v, T f)
    {
        v[0] *= f;
        v[1] *= f;
        v[2] *= f;
    }
}


void Vis::subdivideSpherical(TriangleMesh3D& mesh)
{
    auto& vertices = mesh.getVertices().getData();
    auto& normals = mesh.getVertexNormals().getData();
    auto& faces = mesh.getFaces().getData();

    unsigned long num_v = vertices.size();
    auto num_n = normals.size();
    auto num_f = faces.size();
    auto have_n = (num_n == num_v);
        
    faces.reserve(num_f * 4);
    vertices.reserve(num_v + num_f * 3);

    if (have_n)
        normals.reserve(num_n + num_f * 3);

    double tmp[3];
    
    for (auto& f : faces) {
        for (std::size_t i = 0; i < 3; i++) {
            auto v1 = vertices[f[i]].getData();
            auto v2 = vertices[f[(i + 1) % 3]].getData();

            tmp[0] = (v1[0] + v2[0]) * 0.5;
            tmp[1] = (v1[1] + v2[1]) * 0.5;
            tmp[2] = (v1[2] + v2[2]) * 0.5;

            auto t_len = length(tmp);

            if (have_n) {
                ::scale(tmp, 1.0 / t_len);

                normals.emplace_back(Math::Vector3D{tmp[0], tmp[1], tmp[2]});

                ::scale(tmp, (length(v1) + length(v2)) * 0.5);

                vertices.emplace_back(Math::Vector3D{tmp[0], tmp[1], tmp[2]});

            } else {
                ::scale(tmp, (length(v1) + length(v2)) * 0.5 / t_len);

                vertices.emplace_back(Math::Vector3D{tmp[0], tmp[1], tmp[2]});
            }
        }

        // add new faces
        faces.emplace_back(Math::Vector3UL{num_v, f[1], num_v + 1});
        faces.emplace_back(Math::Vector3UL{num_v + 1, f[2], num_v + 2});
        faces.emplace_back(Math::Vector3UL{num_v, num_v + 1, num_v + 2});

        f[1] = num_v;
        f[2] = num_v + 2;
        
        num_v += 3;
    }
}

void Vis::translate(TriangleMesh3D& mesh, double tx, double ty, double tz,
                    std::size_t vtx_offs, std::size_t count)
{
    auto& vertices = mesh.getVertices().getData();

    if (vtx_offs >= vertices.size())
        return;
    
    std::size_t vtx_end_idx = (count == 0 ? vertices.size() : std::min(vertices.size(), vtx_offs + count));

    for ( ; vtx_offs < vtx_end_idx; vtx_offs++) {
        auto v = vertices[vtx_offs].getData();

        v[0] += tx;
        v[1] += ty;
        v[2] += tz;
    }
}

void Vis::scale(TriangleMesh3D& mesh, double sx, double sy, double sz,
                std::size_t vtx_offs, std::size_t count)
{
    auto& vertices = mesh.getVertices().getData();

    if (vtx_offs >= vertices.size())
        return;
    
    std::size_t vtx_end_idx = (count == 0 ? vertices.size() : std::min(vertices.size(), vtx_offs + count));

    for (std::size_t i = vtx_offs; vtx_offs < vtx_end_idx; i++) {
        auto v = vertices[i].getData();
        
        v[0] *= sx;
        v[1] *= sy;
        v[2] *= sz;
    }

    auto& normals = mesh.getVertexNormals().getData();

    if (vtx_offs >= normals.size())
        return;
   
    vtx_end_idx = (count == 0 ? normals.size() : std::min(normals.size(), vtx_offs + count));

    for (std::size_t i = vtx_offs; vtx_offs < vtx_end_idx; vtx_offs++) {
        auto n = normals[i].getData();

        n[0] *= sx;
        n[1] *= sy;
        n[2] *= sz;
    
        ::scale(n, 1.0 / length(n));
    }
}

void Vis::rotateX(TriangleMesh3D& mesh, double a, std::size_t vtx_offs, std::size_t count)
{
    // TODO
}

void Vis::rotateY(TriangleMesh3D& mesh, double a, std::size_t vtx_offs, std::size_t count)
{
    // TODO
}

void Vis::rotateZ(TriangleMesh3D& mesh, double a, std::size_t vtx_offs, std::size_t count)
{
    // TODO
}
