/* 
 * PLYObject3DOutputHandler.hpp 
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

/**
 * \file
 * \brief Declaration of type CDPL::Vis::PLYObject3DOutputHandler.
 */

#ifndef CDPL_VIS_PLYOBJECT3DOUTPUTHANDLER_HPP
#define CDPL_VIS_PLYOBJECT3DOUTPUTHANDLER_HPP

#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Vis/PLYObject3DWriter.hpp"
#include "CDPL/Util/DefaultDataOutputHandler.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief A handler for the output of Vis::Object3D instances in the <em>Polygon File Format</em> [\ref PLYFMT].
         * \since 1.3
         */
        typedef Util::DefaultDataOutputHandler<PLYObject3DWriter, DataFormat::PLY> PLYObject3DOutputHandler;
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_PLYOBJECT3DOUTPUTHANDLER_HPP
