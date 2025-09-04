/* 
 * PLYFormatData.hpp
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


#ifndef CDPL_VIS_PLYFORMATDATA_HPP
#define CDPL_VIS_PLYFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Vis
    {

        namespace PLY
        {

            const std::string HEADER_PREFIX = "ply\nformat ascii 1.0\n";
            const std::string HEADER_SUFFIX = "end_header\n";

            const std::string VERTEX_ELEM_DEF_PREFIX = "element vertex ";
            const std::string VERTEX_ELEM_DEF_BODY   = "\nproperty double x\n"
                                                       "property double y\n"
                                                       "property double z\n"
                                                       "property double nx\n"
                                                       "property double ny\n"
                                                       "property double nz\n"
                                                       "property uchar red\n"
                                                       "property uchar green\n"
                                                       "property uchar blue\n"
                                                       "property uchar alpha\n";

            const std::string FACE_ELEM_DEF_PREFIX = "element face ";
            const std::string FACE_ELEM_DEF_BODY   = "\nproperty list uchar int vertex_indices\n";

        } // namespace PLY
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PLYFORMATDATA_HPP
