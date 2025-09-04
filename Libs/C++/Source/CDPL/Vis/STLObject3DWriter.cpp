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
#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "STLFormatData.hpp"


using namespace CDPL;


namespace
{

    inline void transform(const Math::Vector3D& vtx, const Math::Matrix4D& mtx, Math::Vector3D& res)
    {
        auto vtx_data = vtx.getData();
        auto res_data = res.getData();
        auto mtx_data = mtx.getData();

        for (int i = 0; i < 3; i++)
            res_data[i] = mtx_data[i][0] * vtx_data[0] + mtx_data[i][1] * vtx_data[1] + mtx_data[i][2] * vtx_data[2] + mtx_data[i][3];
    }

    template <typename T>
    inline void outputVector(const T& vec, std::ostream& os, bool normalize = false)
    {
        if (normalize) {
            auto length = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

            os << (vec[0] / length) << ' ' << (vec[1] / length)  << ' ' << (vec[2] / length) << '\n';
            return;
        }
        
        os << vec[0] << ' ' << vec[1] << ' ' << vec[2] << '\n';
    }
}


Vis::STLObject3DWriter::STLObject3DWriter(std::ostream& os): 
    output(os), state(os.good()), headerWritten(false) {}

Vis::STLObject3DWriter::~STLObject3DWriter()
{
    close();
}

Base::DataWriter<Vis::Object3D>& Vis::STLObject3DWriter::write(const Object3D& obj)
{
    state = false;

    if (!headerWritten) {
        output << STL::SOLID_HEADER;
        headerWritten = true;
    }

    vtxTransform = Math::IdentityMatrix<double>(4, 4);

    process(obj);
    
    state = output.good();
    
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

void Vis::STLObject3DWriter::close()
{
    if (!headerWritten)
        return;

    output << STL::SOLID_FOOTER;
    headerWritten = false;
}

void Vis::STLObject3DWriter::process(const Object3D& obj)
{
    auto has_xform = hasTransformationMatrix(obj);
    auto saved_xform = vtxTransform;

    if (has_xform)
        vtxTransform = vtxTransform * getTransformationMatrix(obj);

    for (auto& sub_obj : obj)
        process(sub_obj);
    
    if (hasShape(obj))
        getShape(obj)->accept(*this);

    if (has_xform)
        vtxTransform = saved_xform;
}

void Vis::STLObject3DWriter::visitTriangleMesh(const TriangleMesh3D& mesh)
{
    auto& verts = mesh.getVertices();
    auto num_verts = verts.getSize();

    if (transVertices.size() < num_verts)
        transVertices.resize(num_verts);
    
    for (std::size_t i = 0; i < num_verts; i++)
        transform(verts[i], vtxTransform, transVertices[i]);

    for (auto& face : mesh.getFaces()) {
        auto face_data = face.getData();

        if ((face_data[0] >= num_verts) || (face_data[1] >= num_verts) || (face_data[2] >= num_verts))
            throw Base::IOError("STLObject3DWriter: face vertex index out of bounds");

        auto& v1 = transVertices[face_data[0]];
        auto& v2 = transVertices[face_data[1]];
        auto& v3 = transVertices[face_data[2]];
        
        output << STL::FACET_HEADER << STL::NORMAL_PREFIX;

        outputVector(crossProd(v2 - v1, v3 - v1), output, true);

        output << STL::VERTICES_HEADER;
        output << STL::VERTEX_PREFIX;

        outputVector(v1, output);
        
        output << STL::VERTEX_PREFIX;

        outputVector(v2, output);

        output << STL::VERTEX_PREFIX;

        outputVector(v3, output);
        
        output << STL::VERTICES_FOOTER;
        output << STL::FACET_FOOTER;
    }
}
