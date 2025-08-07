/* 
 * Object3DWriter.hpp 
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
 * \brief Definition of the class CDPL::Vis::Object3DWriter.
 */

#ifndef CDPL_VIS_OBJECT3DWRITER_HPP
#define CDPL_VIS_OBJECT3DWRITER_HPP

#include "CDPL/Util/MultiFormatDataWriter.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Object3D;

        /**
         * \brief Writer for Vis::Object3D data in any supported format.
         * \since 1.3
         */
        typedef Util::MultiFormatDataWriter<Object3D> Object3DWriter;

    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3DWRITER_HPP
