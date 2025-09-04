/* 
 * R3DFormatData.hpp
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


#ifndef CDPL_VIS_R3DFORMATDATA_HPP
#define CDPL_VIS_R3DFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Vis
    {

        namespace R3D
        {

            const std::string HEADER = "unnamed\n"
                                       "1280 1024\n" // tiles in x,y
                                       "0 0\n"       // pixels (x,y) per tile(and set these to 0 0)
                                       "4\n"         // anti-aliasing level 4; 3x3->2x2
                                       "0 0 0\n"     // black background
                                       "F\n"         // no shadows cast
                                       "25\n"        // Phong power
                                       "0.25\n"      // secondary light contribution
                                       "0.05\n"      // ambient light contribution
                                       "0.25\n"      // specular reflection component
                                       "4.0\n"       // eye position
                                       "1 1 1\n"     // main light source position (from over right shoulder)
                                       "1 0 0 0\n"   // view matrix describing input coordinate transformation
                                       "0 1 0 0\n"
                                       "0 0 1 0\n"
                                       "0 0 0 1\n"   // no translation, no scaling
                                       "3\n"         // mixed objects
                                       "*\n"         // free format triangle and plane descriptors
                                       "*\n"         // free format sphere descriptors
                                       "*\n";        // free format cylinder descriptors

            constexpr unsigned int TRIANGLE_ID             = 1;
            constexpr unsigned int TRIANGLE_VTX_NORMALS_ID = 7;
            constexpr unsigned int MATERIAL_ID             = 8;
            constexpr unsigned int END_MATERIAL_ID         = 9;
            
        } // namespace R3D
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_R3DFORMATDATA_HPP
