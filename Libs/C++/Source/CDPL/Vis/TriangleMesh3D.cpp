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


Vis::Shape3D::SharedPointer Vis::TriangleMesh3D::clone() const
{
    return Shape3D::SharedPointer(new TriangleMesh3D(*this));
}

void Vis::TriangleMesh3D::accept(Shape3DVisitor& visitor) const
{
    visitor.visitTriangleMesh(*this);
}

Math::Vector3DArray& Vis::TriangleMesh3D::getVertices()
{
    return vertices;
}

const Math::Vector3DArray& Vis::TriangleMesh3D::getVertices() const
{
    return vertices;
}

void Vis::TriangleMesh3D::addVertex(double x, double y, double z)
{
    vertices.getData().emplace_back(Math::Vector3D{x, y, z});
}
            
std::size_t Vis::TriangleMesh3D::getNumVertices() const
{
    return vertices.getSize();
}

Math::Vector3DArray& Vis::TriangleMesh3D::getVertexNormals()
{
    return normals;
}

const Math::Vector3DArray& Vis::TriangleMesh3D::getVertexNormals() const
{
    return normals;
}

void Vis::TriangleMesh3D::addVertexNormal(double x, double y, double z)
{
    normals.getData().emplace_back(Math::Vector3D{x, y, z});
}
  
std::size_t Vis::TriangleMesh3D::getNumVertexNormals() const
{
    return normals.getSize();
}

Math::Vector3ULArray& Vis::TriangleMesh3D::getFaces()
{
    return faces;
}

const Math::Vector3ULArray& Vis::TriangleMesh3D::getFaces() const
{
    return faces;
}

void Vis::TriangleMesh3D::addFace(unsigned long v1_idx, unsigned long v2_idx, unsigned long v3_idx)
{
    faces.getData().emplace_back(Math::Vector3UL{v1_idx, v2_idx, v3_idx});
}

std::size_t Vis::TriangleMesh3D::getNumFaces() const
{
    return faces.getSize();
}

bool Vis::TriangleMesh3D::isClosed() const
{
    return closed;
}

void Vis::TriangleMesh3D::setClosed(bool closed)
{
    this->closed = closed;
}

void Vis::TriangleMesh3D::clear()
{
    vertices.clear();
    normals.clear();
    faces.clear();
}

void Vis::TriangleMesh3D::swap(TriangleMesh3D& mesh)
{
    vertices.swap(mesh.vertices);
    normals.swap(mesh.normals);
    faces.swap(mesh.faces);
}

Vis::TriangleMesh3D& Vis::TriangleMesh3D::operator+=(const TriangleMesh3D& mesh)
{
    auto& v_data = vertices.getData();
    auto& rhs_v_data = mesh.vertices.getData();
    auto prev_num_verts = v_data.size();
    
    v_data.reserve(prev_num_verts + rhs_v_data.size());
    v_data.insert(v_data.end(), rhs_v_data.begin(), rhs_v_data.end());

    auto& vn_data = normals.getData();
    auto& rhs_vn_data = mesh.normals.getData();

    vn_data.reserve(vn_data.size() + rhs_vn_data.size());
    vn_data.insert(vn_data.end(), rhs_vn_data.begin(), rhs_vn_data.end());

    auto& f_data = faces.getData();
    auto& rhs_f_data = mesh.faces.getData();

    f_data.reserve(f_data.size() + rhs_f_data.size());

    for (auto& f : rhs_f_data) 
        f_data.emplace_back(Math::Vector3UL{f[0] + prev_num_verts, f[1] + prev_num_verts, f[2] + prev_num_verts});
    
    return *this;
}
