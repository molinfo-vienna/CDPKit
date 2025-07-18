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
#include <vector>

#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"


using namespace CDPL;


namespace
{

    template <typename V>
    inline double length(const V& v)
    {
        return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    template <typename V, typename T>
    inline void scale(V& v, T f)
    {
        v[0] *= f;
        v[1] *= f;
        v[2] *= f;
    }

    template <typename A>
    inline std::size_t getArrayEndIndex(const A& array, std::size_t offs, std::size_t count)
    {
        if (offs >= array.size())
            return 0;
    
        return (count == 0 ? array.size() : std::min(array.size(), offs + count));
    }
}


void Vis::subdivideSpherical(TriangleMesh3D& mesh)
{
    auto& vertices = mesh.getVertices();
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

                mesh.addVertexNormal(tmp[0], tmp[1], tmp[2]);

                ::scale(tmp, (length(v1) + length(v2)) * 0.5);

                mesh.addVertex(tmp[0], tmp[1], tmp[2]);

            } else {
                ::scale(tmp, (length(v1) + length(v2)) * 0.5 / t_len);

                mesh.addVertex(tmp[0], tmp[1], tmp[2]);
            }
        }

        // add new triangles
        mesh.addFace(num_v, f[1], num_v + 1);
        mesh.addFace(num_v + 1, f[2], num_v + 2);
        mesh.addFace(num_v, num_v + 1, num_v + 2);

        // modify original triangle
        f[1] = num_v;
        f[2] = num_v + 2;
        
        num_v += 3;
    }
}

std::size_t Vis::removeVertexDuplicates(TriangleMesh3D& mesh, bool check_vn, double tol)
{
    auto& vertices = mesh.getVertices().getData();
    std::size_t num_v = vertices.size();

    auto& normals = mesh.getVertexNormals().getData();
    std::size_t num_n = normals.size();
 
    std::vector<std::size_t> vtx_mapping(num_v, num_v);
    std::vector<Math::Vector3D> new_vertices;
    std::vector<Math::Vector3D> new_normals;
    
    for (std::size_t i = 0; i < num_v; i++) {
        if (vtx_mapping[i] < num_v)
            continue;

        auto& v = vertices[i];

        for (std::size_t j = i + 1; j < num_v; j++) {
            if (vtx_mapping[j] < num_v)
                continue;

            if (tol > 0.0) {
                if ((length(v - vertices[j]) <= tol) && (!check_vn || (j >= num_n) || (length(normals[i] - normals[j]) <= tol)))
                    vtx_mapping[j] = new_vertices.size();

            } else if ((v == vertices[j]) && (!check_vn || (j >= num_n) || (normals[i] == normals[j])))
                vtx_mapping[j] = new_vertices.size();
        }

        vtx_mapping[i] = new_vertices.size();
        new_vertices.emplace_back(v);

        if (i < num_n)
            new_normals.emplace_back(normals[i]);
    }

    vertices.swap(new_vertices);
    normals.swap(new_normals);

    for (auto& f : mesh.getFaces())
        for (std::size_t i = 0; i < 3; i++) {
            if (f[i] >= num_v)
                continue;

            f[i] = vtx_mapping[f[i]];
        }
    
    return (num_v - vertices.size());
}

void Vis::calcVertexFromFaceNormals(TriangleMesh3D& mesh, bool weight_face_size)
{
    auto& vertices = mesh.getVertices();
    std::size_t num_v = vertices.size();
    std::vector<Math::Vector3D> calc_normals(num_v);

    for (auto& f : mesh.getFaces()) {
        auto& v1 = vertices[f[0]];
        auto& v2 = vertices[f[1]];
        auto& v3 = vertices[f[2]];

        Math::Vector3D fn = crossProd(v2 - v1, v3 - v1);

        if (!weight_face_size)
            ::scale(fn, 1.0 / length(fn.getData()));

        for (std::size_t i = 0; i < 3; i++)
            calc_normals[f[i]] += fn;
    }

    for (auto& n : calc_normals) {
        auto l = length(n.getData());

        if (l != 0.0)
            ::scale(n, 1.0 / l);
    }

    mesh.getVertexNormals().getData().swap(calc_normals);
}

void Vis::translate(TriangleMesh3D& mesh, double trans_x, double trans_y, double trans_z,
                    std::size_t vtx_offs, std::size_t vtx_count)
{
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();

        v[0] += trans_x;
        v[1] += trans_y;
        v[2] += trans_z;
    }
}

void Vis::scale(TriangleMesh3D& mesh, double scale_x, double scale_y, double scale_z,
                std::size_t vtx_offs, std::size_t vtx_count)
{
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();
        
        v[0] *= scale_x;
        v[1] *= scale_y;
        v[2] *= scale_z;
    }

    auto& normals = mesh.getVertexNormals().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(normals, vtx_offs, vtx_count); i < end_idx; i++) {
        auto n = normals[i].getData();

        n[0] *= scale_x;
        n[1] *= scale_y;
        n[2] *= scale_z;
    
        ::scale(n, 1.0 / length(n));
    }
}

void Vis::rotateX(TriangleMesh3D& mesh, double angle, std::size_t vtx_offs, std::size_t vtx_count)
{
    auto cos_a = std::cos(angle);
    auto sin_a = std::sin(angle);
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();
        auto rot_y = cos_a * v[1] + sin_a * v[2];
        auto rot_z = -sin_a * v[1] + cos_a * v[2]; 
        
        v[1] = rot_y;
        v[2] = rot_z;
    }

    auto& normals = mesh.getVertexNormals().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(normals, vtx_offs, vtx_count); i < end_idx; i++) {
        auto n = normals[i].getData();
        auto rot_y = cos_a * n[1] + sin_a * n[2];
        auto rot_z = -sin_a * n[1] + cos_a * n[2];

        n[1] = rot_y;
        n[2] = rot_z;
    }
}

void Vis::rotateY(TriangleMesh3D& mesh, double angle, std::size_t vtx_offs, std::size_t vtx_count)
{
    auto cos_a = std::cos(angle);
    auto sin_a = std::sin(angle);
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();
        auto rot_x = cos_a * v[0] - sin_a * v[2];
        auto rot_z = sin_a * v[0] + cos_a * v[2]; 
        
        v[0] = rot_x;
        v[2] = rot_z;
    }

    auto& normals = mesh.getVertexNormals().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(normals, vtx_offs, vtx_count); i < end_idx; i++) {
        auto n = normals[i].getData();
        auto rot_x = cos_a * n[0] - sin_a * n[2];
        auto rot_z = sin_a * n[0] + cos_a * n[2];

        n[0] = rot_x;
        n[2] = rot_z;
    }
}

void Vis::rotateZ(TriangleMesh3D& mesh, double angle, std::size_t vtx_offs, std::size_t vtx_count)
{
    auto cos_a = std::cos(angle);
    auto sin_a = std::sin(angle);
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();
        auto rot_x = cos_a * v[0] + sin_a * v[1];
        auto rot_y = -sin_a * v[0] + cos_a * v[1]; 
        
        v[0] = rot_x;
        v[1] = rot_y;
    }

    auto& normals = mesh.getVertexNormals().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(normals, vtx_offs, vtx_count); i < end_idx; i++) {
        auto n = normals[i].getData();
        auto rot_x = cos_a * n[0] + sin_a * n[1];
        auto rot_y = -sin_a * n[0] + cos_a * n[1];

        n[0] = rot_x;
        n[1] = rot_y;
    }
}

void Vis::transform(TriangleMesh3D& mesh, const Math::Matrix4D& mtx, std::size_t vtx_offs, std::size_t vtx_count)
{
    auto& vertices = mesh.getVertices().getData();

    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(vertices, vtx_offs, vtx_count); i < end_idx; i++) {
        auto v = vertices[i].getData();
        auto t_x = mtx(0, 0) * v[0] + mtx(0, 1) * v[1] + mtx(0, 2) * v[2] + mtx(0, 3);
        auto t_y = mtx(1, 0) * v[0] + mtx(1, 1) * v[1] + mtx(1, 2) * v[2] + mtx(1, 3);
        auto t_z = mtx(2, 0) * v[0] + mtx(2, 1) * v[1] + mtx(2, 2) * v[2] + mtx(2, 3);
        
        v[0] = t_x;
        v[1] = t_y;
        v[2] = t_z;
    }

    auto& normals = mesh.getVertexNormals().getData();
  
    for (std::size_t i = vtx_offs, end_idx = getArrayEndIndex(normals, vtx_offs, vtx_count); i < end_idx; i++) {
        auto n = normals[i].getData();
        auto t_x = mtx(0, 0) * n[0] + mtx(0, 1) * n[1] + mtx(0, 2) * n[2];
        auto t_y = mtx(1, 0) * n[0] + mtx(1, 1) * n[1] + mtx(1, 2) * n[2];
        auto t_z = mtx(2, 0) * n[0] + mtx(2, 1) * n[1] + mtx(2, 2) * n[2];
        
        n[0] = t_x;
        n[1] = t_y;
        n[2] = t_z;

        ::scale(n, 1.0 / length(n));
    }
}
