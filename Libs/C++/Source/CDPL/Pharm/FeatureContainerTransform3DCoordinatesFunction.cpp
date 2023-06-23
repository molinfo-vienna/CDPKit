/* 
 * FeatureContainerTransform3DCoordinatesFunction.cpp 
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


#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/MatrixProxy.hpp"


using namespace CDPL; 


void Pharm::transform3DCoordinates(FeatureContainer& cntnr, const Math::Matrix4D& mtx)
{
	Math::Vector4D tmp1;
	Math::Vector4D tmp2;
	Math::Vector3D tmp3;

	tmp1[3] = 1.0;

	for (FeatureContainer::FeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); it != end; ++it) {
		Feature& ftr = *it;
		const Math::Vector3D& coords = get3DCoordinates(ftr);

		tmp1[0] = coords[0];
		tmp1[1] = coords[1];
		tmp1[2] = coords[2];

		prod(mtx, tmp1, tmp2);

		tmp3[0] = tmp2[0];
		tmp3[1] = tmp2[1];
		tmp3[2] = tmp2[2];

		set3DCoordinates(ftr, tmp3);

		if (!hasOrientation(ftr))
			continue;

		const Math::Vector3D& orient = getOrientation(ftr);

		prod(range(mtx, 0, 3, 0, 3), orient, tmp3);
		setOrientation(ftr, tmp3);
	}
}
