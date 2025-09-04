/* 
 * R3DObject3DWriter.cpp 
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

#include "CDPL/Vis/R3DObject3DWriter.hpp"
#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/Material.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"

#include "R3DFormatData.hpp"


using namespace CDPL;


namespace
{

    inline void transform(const Math::Vector3D& vtx, const Math::Matrix4D& mtx, Math::Vector3D& res, bool translate = true, bool normalize = false)
    {
        auto vtx_data = vtx.getData();
        auto mtx_data = mtx.getData();
        auto res_data = res.getData();

        for (int i = 0; i < 3; i++) {
            res_data[i] = mtx_data[i][0] * vtx_data[0] + mtx_data[i][1] * vtx_data[1] + mtx_data[i][2] * vtx_data[2];

            if (translate)
                res_data[i] += mtx_data[i][3];
        }

        if (normalize) {
             auto length = std::sqrt(res_data[0] * res_data[0] + res_data[1] * res_data[1] + res_data[2] * res_data[2]);

             for (int i = 0; i < 3; i++)
                 res_data[i] /= length;
        }
    }

    inline void outputVector(const Math::Vector3D& vec, std::ostream& os, char term = ' ')
    {
        os << vec[0] << ' ' << vec[1] << ' ' << vec[2] << term;
    }

    inline void outputColor(const Vis::Color& color, std::ostream& os)
    {
        os << color.getRed() << ' ' << color.getGreen() << ' ' << color.getBlue() << '\n';
    }
}


Vis::R3DObject3DWriter::R3DObject3DWriter(std::ostream& os): 
    output(os), state(os.good()), headerWritten(false) {}

Base::DataWriter<Vis::Object3D>& Vis::R3DObject3DWriter::write(const Object3D& obj)
{
    state = false;

    if (!headerWritten) {
        output << R3D::HEADER;
        headerWritten = true;
    }

    vtxTransform = Math::IdentityMatrix<double>(4, 4);
    material = &getDefaultMaterialParameter(*this);
    
    process(obj);
    
    state = output.good();
    
    invokeIOCallbacks(1.0);

    return *this;
}

Vis::R3DObject3DWriter::operator const void*() const
{
    return (state ? this : nullptr);
}

bool Vis::R3DObject3DWriter::operator!() const
{
    return !state;
}

void Vis::R3DObject3DWriter::close()
{
    headerWritten = false;
}

void Vis::R3DObject3DWriter::process(const Object3D& obj)
{
    auto has_xform = hasTransformationMatrix(obj);
    auto saved_xform = vtxTransform;
    auto saved_mat = material;

    if (has_xform)
        vtxTransform = vtxTransform * getTransformationMatrix(obj);

    if (hasMaterial(obj))
        material = &getMaterial(obj);
    
    for (auto& sub_obj : obj)
        process(sub_obj);
    
    if (hasShape(obj))
        getShape(obj)->accept(*this);

    if (has_xform)
        vtxTransform = saved_xform;

    material = saved_mat;
}

void Vis::R3DObject3DWriter::visitTriangleMesh(const TriangleMesh3D& mesh)
{
    auto& verts = mesh.getVertices().getData();
    auto& normals = mesh.getVertexNormals().getData();
    auto num_verts = verts.size();
    auto num_normals = normals.size();

    if (num_verts > num_normals)
        calcVertexFromFaceNormals(mesh, calcVtxNormals);

    if (transVertices.size() < num_verts) {
        transVertices.resize(num_verts);
        transNormals.resize(num_verts);
    }
    
    for (std::size_t i = 0; i < num_verts; i++) {
        ::transform(verts[i], vtxTransform, transVertices[i]);
        ::transform((i < num_normals ? normals[i] : calcVtxNormals[i]), vtxTransform, transNormals[i], false, true);
    }

    auto& diff_col = material->getDiffuseColor();
    
    output << R3D::MATERIAL_ID << '\n';
    output << (material->getShininess() * 100) << " -1. 1. 1. 1. " << material->getTransparency()
           << (mesh.isClosed() ? " 0 0 0 0\n" : " 2 0 0 0\n");

    for (auto& face : mesh.getFaces()) {
        auto face_data = face.getData();

        if ((face_data[0] >= num_verts) || (face_data[1] >= num_verts) || (face_data[2] >= num_verts))
            throw Base::IOError("R3DObject3DWriter: face vertex index out of bounds");

        output << R3D::TRIANGLE_ID << '\n';

        outputVector(transVertices[face_data[0]], output);
        outputVector(transVertices[face_data[1]], output);
        outputVector(transVertices[face_data[2]], output);
        outputColor(diff_col, output);

        output << R3D::TRIANGLE_VTX_NORMALS_ID << '\n';

        outputVector(transNormals[face_data[0]], output);
        outputVector(transNormals[face_data[1]], output);
        outputVector(transNormals[face_data[2]], output, '\n');
    }
    
    output << R3D::END_MATERIAL_ID << '\n';
}
