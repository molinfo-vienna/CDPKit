/* 
 * VRMLObject3DWriter.cpp 
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

#include "CDPL/Vis/VRMLObject3DWriter.hpp"
#include "CDPL/Vis/Object3D.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"
#include "CDPL/Vis/Material.hpp"
#include "CDPL/Vis/Object3DFunctions.hpp"

#include "VRMLFormatData.hpp"


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
    inline void outputVector(const T& vec, std::ostream& os, bool normalize = false, const char* term = "\n")
    {
        if (normalize) {
            auto length = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

            os << (vec[0] / length) << ' ' << (vec[1] / length)  << ' ' << (vec[2] / length) << term;
            return;
        }
        
        os << vec[0] << ' ' << vec[1] << ' ' << vec[2] << term;
    }

    inline void outputColor(const Vis::Color& color, std::ostream& os)
    {
        os << color.getRed() << ' ' << color.getGreen() << ' ' << color.getBlue() << '\n';
    }
}


Vis::VRMLObject3DWriter::VRMLObject3DWriter(std::ostream& os): 
    output(os), state(os.good()), headerWritten(false) {}

Base::DataWriter<Vis::Object3D>& Vis::VRMLObject3DWriter::write(const Object3D& obj)
{
    state = false;

    if (!headerWritten) {
        output << VRML::HEADER;
        headerWritten = true;
    }

    vtxTransform = Math::IdentityMatrix<double>(4, 4);
    material = nullptr;
    
    process(obj);
    
    state = output.good();
    
    invokeIOCallbacks(1.0);

    return *this;
}

Vis::VRMLObject3DWriter::operator const void*() const
{
    return (state ? this : nullptr);
}

bool Vis::VRMLObject3DWriter::operator!() const
{
    return !state;
}

void Vis::VRMLObject3DWriter::close()
{
    headerWritten = false;
}

void Vis::VRMLObject3DWriter::process(const Object3D& obj)
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

void Vis::VRMLObject3DWriter::visitTriangleMesh(const TriangleMesh3D& mesh)
{
    output << '\n' << VRML::Shape::HEADER;

    // -

    if (material) {
        output << ' ' << VRML::Shape::APPEARANCE_PREFIX;
        output << VRML::Appearance::HEADER;
        output << "  " << VRML::Appearance::MATERIAL_PREFIX;
        output << VRML::Material::HEADER;
        output << "   " << VRML::Material::DIFFUSE_COLOR_PREFIX;

        outputColor(material->getDiffuseColor(), output);

        output << "   " << VRML::Material::SPECULAR_COLOR_PREFIX;

        outputColor(material->getSpecularColor(), output);

        output << "   " << VRML::Material::AMBIENT_INTENSITY_PREFIX << material->getAmbientFactor() << '\n';
        output << "   " << VRML::Material::SHININESS_PREFIX << material->getShininess() << '\n';
        output << "   " << VRML::Material::TRANSPARENCY_PREFIX << material->getTransparency() << '\n';

        output << "  " << VRML::Material::FOOTER;
        output << ' ' << VRML::Appearance::FOOTER;
    }

    // -

    output << ' ' << VRML::Shape::GEOMETRY_PREFIX;
    output << VRML::IndexedFaceSet::HEADER;
   
    // --

    output << "  " << VRML::IndexedFaceSet::COORD_PREFIX;
    output << VRML::Coordinate::HEADER;
    output << "   " << VRML::Coordinate::POINT_PREFIX;
 
    double trans_vec[3];
    
    for (auto& vtx : mesh.getVertices().getData()) {
        transform(vtx, vtxTransform, trans_vec);

        output << "    ";
        
        outputVector(trans_vec, output);
    }

    output << "   " << VRML::Coordinate::POINT_SUFFIX;
    output << "  " << VRML::Coordinate::FOOTER;

    // --

    output << "  " << VRML::IndexedFaceSet::NORMAL_PREFIX;
    output << VRML::Normal::HEADER;
    output << "   " << VRML::Normal::VECTOR_PREFIX;
 
    for (auto& normal : mesh.getVertexNormals().getData()) {
        transform(normal, vtxTransform, trans_vec, false);

        output << "    ";
        
        outputVector(trans_vec, output, true);
    }

    output << "   " << VRML::Normal::VECTOR_SUFFIX;
    output << "  " << VRML::Normal::FOOTER;
    
    // --

    output << "  " << VRML::IndexedFaceSet::COORD_INDEX_PREFIX;
 
    for (auto& face : mesh.getFaces()) {
        output << "    ";
        
        outputVector(face, output, false, VRML::IndexedFaceSet::COORD_INDEX_TUPLE_SEPARATOR);
    }

    output << "  " << VRML::IndexedFaceSet::COORD_INDEX_SUFFIX;
    
    // --

    output << ' ' << VRML::IndexedFaceSet::SOLID_PREFIX << (mesh.isSolid() ? VRML::TRUE : VRML::FALSE) << '\n';
    output << ' ' << VRML::IndexedFaceSet::FOOTER;

    // -
    
    output << VRML::Shape::FOOTER;
}
