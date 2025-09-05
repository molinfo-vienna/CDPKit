/* 
 * PLYObject3DWriter.cpp 
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

#include "CDPL/Vis/PLYObject3DWriter.hpp"
#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/Material.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"
#include "CDPL/Vis/TriangleMesh3DFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"

#include "PLYFormatData.hpp"


using namespace CDPL;


namespace
{

    inline void transform(const Math::Vector3D& vtx, const Math::Matrix4D& mtx, double* res_data, bool translate = true)
    {
        auto vtx_data = vtx.getData();
        auto mtx_data = mtx.getData();

        for (int i = 0; i < 3; i++) {
            res_data[i] = mtx_data[i][0] * vtx_data[0] + mtx_data[i][1] * vtx_data[1] + mtx_data[i][2] * vtx_data[2];

            if (translate)
                res_data[i] += mtx_data[i][3];
        }
    }

    template <typename T>
    inline void outputVector(const T& vec, std::ostream& os, bool normalize = false)
    {
        if (normalize) {
            auto length = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

            os << (vec[0] / length) << ' ' << (vec[1] / length)  << ' ' << (vec[2] / length) << ' ';
            return;
        }
        
        os << vec[0] << ' ' << vec[1] << ' ' << vec[2] << ' ';
    }

    void composeColor(const Vis::Material& mat, unsigned int color[4])
    {
        
        color[0] = std::min(mat.getDiffuseColor().getRed() + mat.getAmbientColor().getRed() + mat.getSpecularColor().getRed() * 0.1, 1.0) * 255;
        color[1] = std::min(mat.getDiffuseColor().getGreen() + mat.getAmbientColor().getGreen() + mat.getSpecularColor().getGreen() * 0.1, 1.0) * 255;
        color[2] = std::min(mat.getDiffuseColor().getBlue() + mat.getAmbientColor().getBlue() + mat.getSpecularColor().getBlue() * 0.1, 1.0) * 255;
        color[3] = 255 - mat.getTransparency() * 255;
    }
}


Vis::PLYObject3DWriter::PLYObject3DWriter(std::ostream& os): 
    output(os), state(os.good()), closed(true) {}

Vis::PLYObject3DWriter::~PLYObject3DWriter()
{
    close();
}

Base::DataWriter<Vis::Object3D>& Vis::PLYObject3DWriter::write(const Object3D& obj)
{
    state = false;

    if (closed) {
        vtxOStream.str(std::string());
        faceOStream.str(std::string());

        vtxCount = 0;
        faceCount = 0;
        closed = false;
    }

    vtxTransform = Math::IdentityMatrix<double>(4, 4);
    material = &getDefaultMaterialParameter(*this);
    
    process(obj);
    
    state = output.good();
    
    invokeIOCallbacks(1.0);

    return *this;
}

Vis::PLYObject3DWriter::operator const void*() const
{
    return (state ? this : nullptr);
}

bool Vis::PLYObject3DWriter::operator!() const
{
    return !state;
}

void Vis::PLYObject3DWriter::close()
{
    if (closed)
        return;

    output << PLY::HEADER_PREFIX;
    output << PLY::VERTEX_ELEM_DEF_PREFIX << vtxCount << PLY::VERTEX_ELEM_DEF_BODY;
    output << PLY::FACE_ELEM_DEF_PREFIX << faceCount << PLY::FACE_ELEM_DEF_BODY;
    output << PLY::HEADER_SUFFIX;
    output << vtxOStream.str();
    output << faceOStream.str();
    
    closed = true;
}

void Vis::PLYObject3DWriter::process(const Object3D& obj)
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

void Vis::PLYObject3DWriter::visitTriangleMesh(const TriangleMesh3D& mesh)
{
    auto& verts = mesh.getVertices().getData();
    auto& normals = mesh.getVertexNormals().getData();
    auto num_verts = verts.size();
    auto num_normals = normals.size();

    if (num_verts > num_normals)
        calcVertexFromFaceNormals(mesh, calcVtxNormals);
        
    double trans_vec[3];
    unsigned int vtx_color[4];

    composeColor(*material, vtx_color);
    
    for (std::size_t i = 0; i < num_verts; i++) {
        ::transform(verts[i], vtxTransform, trans_vec);
        outputVector(trans_vec, vtxOStream);

        ::transform((i < num_normals ? normals[i] : calcVtxNormals[i]), vtxTransform, trans_vec, false);
        outputVector(trans_vec, vtxOStream, true);

        vtxOStream << vtx_color[0] << ' ' << vtx_color[1] << ' '
                   << vtx_color[2] << ' ' << vtx_color[3] << '\n';
    }
    
    for (auto& face : mesh.getFaces())
        faceOStream << "3 " << (face[0] + vtxCount) << ' '
                    << (face[1] + vtxCount) << ' '
                    << (face[2] + vtxCount) << '\n';

    vtxCount += num_verts;
    faceCount += mesh.getFaces().getSize();
}
