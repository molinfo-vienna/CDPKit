/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Utilities.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#ifndef CDPL_SHAPE_UTILITIES_HPP
#define CDPL_SHAPE_UTILITIES_HPP

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Shape
    {

		inline double calcSquaredDistance(Math::Vector3D::ConstPointer vec1, Math::Vector3D::ConstPointer vec2)
		{
			double dx = vec1[0] - vec2[0];
			double dy = vec1[1] - vec2[1];
			double dz = vec1[2] - vec2[2];

			return (dx * dx + dy * dy + dz * dz);
		}
	
		inline void transform(Math::Vector3D::Pointer tgt_vec, Math::Matrix4D::ConstArrayPointer xform, Math::Vector3D::ConstPointer src_vec)
		{
			tgt_vec[0] = xform[0][0] * src_vec[0] + xform[0][1] * src_vec[1] + xform[0][2] * src_vec[2] + xform[0][3];
			tgt_vec[1] = xform[1][0] * src_vec[0] + xform[1][1] * src_vec[1] + xform[1][2] * src_vec[2] + xform[1][3];
			tgt_vec[2] = xform[2][0] * src_vec[0] + xform[2][1] * src_vec[1] + xform[2][2] * src_vec[2] + xform[2][3];
		}
    }
}

#endif // CDPL_SHAPE_UTILITIES_HPP
