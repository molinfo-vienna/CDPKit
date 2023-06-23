/* 
 * PiPiInteractionUtilities.cpp
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

#include "PiPiInteractionUtilities.hpp"


using namespace CDPL;


double Pharm::calcVPlaneDistance(const Math::Vector3D& plane_ov, const Math::Vector3D& pt_vec)
{
    return std::abs(innerProd(plane_ov, pt_vec));
}

double Pharm::calcHPlaneDistance(const Math::Vector3D& plane_ov, const Math::Vector3D& pt_vec)
{
    double v_dist = calcVPlaneDistance(plane_ov, pt_vec);
    double pt_dist = length(pt_vec);

    return std::sqrt(pt_dist * pt_dist - v_dist * v_dist);
}

