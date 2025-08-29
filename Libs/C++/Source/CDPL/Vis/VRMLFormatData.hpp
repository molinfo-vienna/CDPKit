/* 
 * VRMLFormatData.hpp
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


#ifndef CDPL_VIS_VRMLFORMATDATA_HPP
#define CDPL_VIS_VRMLFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Vis
    {

        namespace VRML
        {

            const std::string HEADER = "#VRML V2.0 utf8\n";

            const std::string TRUE  = "TRUE";
            const std::string FALSE = "FALSE";

            namespace Shape
            {

                const std::string HEADER = "Shape {\n";
                const std::string FOOTER = "}\n";

                const std::string APPEARANCE_PREFIX = "appearance ";
                const std::string GEOMETRY_PREFIX   = "geometry ";
            } // namespace Shape

            namespace Appearance
            {
                const std::string HEADER = "Appearance {\n";
                const std::string FOOTER = "}\n";

                const std::string MATERIAL_PREFIX = "material ";
            } // namespace Appearance

            namespace Material
            {

                const std::string HEADER = "Material {\n";
                const std::string FOOTER = "}\n";

                const std::string DIFFUSE_COLOR_PREFIX     = "diffuseColor ";
                const std::string AMBIENT_INTENSITY_PREFIX = "ambientIntensity ";
                const std::string SPECULAR_COLOR_PREFIX    = "specularColor ";
                const std::string SHININESS_PREFIX         = "shininess ";
                const std::string TRANSPARENCY_PREFIX      = "transparency ";
            } // namespace Material

            namespace IndexedFaceSet
            {

                const std::string HEADER = "IndexedFaceSet {\n";
                const std::string FOOTER = "}\n";

                const std::string SOLID_PREFIX       = "solid ";
                const std::string COORD_PREFIX       = "coord ";
                const std::string NORMAL_PREFIX      = "normal ";
                const std::string COORD_INDEX_PREFIX = "coordIndex [\n";
                const std::string COORD_INDEX_SUFFIX = "]\n";

                const char* COORD_INDEX_TUPLE_SEPARATOR = " -1,\n";
            } // namespace IndexedFaceSet

            namespace Coordinate
            {

                const std::string HEADER = "Coordinate {\n";
                const std::string FOOTER = "}\n";

                const std::string POINT_PREFIX = "point [\n";
                const std::string POINT_SUFFIX = "]\n";
            } // namespace Coordinate

            namespace Normal
            {

                const std::string HEADER = "Normal {\n";
                const std::string FOOTER = "}\n";

                const std::string VECTOR_PREFIX = "vector [\n";
                const std::string VECTOR_SUFFIX = "]\n";
            } // namespace Normal

        } // namespace VRML
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_VRMLFORMATDATA_HPP
