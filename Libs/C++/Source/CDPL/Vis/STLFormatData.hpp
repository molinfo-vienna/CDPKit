/* 
 * STLFormatData.hpp
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


#ifndef CDPL_VIS_STLFORMATDATA_HPP
#define CDPL_VIS_STLFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Vis
    {

        namespace STL
        {

            const std::string SOLID_HEADER    = "solid name\n";
            const std::string SOLID_FOOTER    = "endsolid name\n";

            const std::string FACET_HEADER    = " facet";
            const std::string FACET_FOOTER    = " endfacet\n";

            const std::string NORMAL_PREFIX   = " normal ";

            const std::string VERTICES_HEADER = "  outer loop\n";
            const std::string VERTICES_FOOTER = "  endloop\n";

            const std::string VERTEX_PREFIX   = "    vertex ";

        } // namespace STL
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_STLFORMATDATA_HPP
