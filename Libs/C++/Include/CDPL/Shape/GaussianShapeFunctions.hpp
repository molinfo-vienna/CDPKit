/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions operating on object of type Shape::GaussianShape.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class AtomContainer;
	}

	namespace Pharm
	{

		class FeatureContainer;
	}
	
    namespace Shape
    {

		class GaussianShape;
		class GaussianShapeFunction;
		
		CDPL_SHAPE_API void generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape,
												  bool append = false, double radius = -1.0, bool inc_h = false, double p = 2.7);

		CDPL_SHAPE_API void generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape, const Chem::Atom3DCoordinatesFunction& coords_func,
												  bool append = false, double radius = -1.0, bool inc_h = false, double p = 2.7);

		CDPL_SHAPE_API void generateGaussianShape(const Pharm::FeatureContainer& features, GaussianShape& shape,
												  bool append = false, double radius = -1.0, bool inc_xv = false, double p = 5.0);

		CDPL_SHAPE_API void transform(GaussianShape& shape, const Math::Matrix4D& xform);
		
		CDPL_SHAPE_API unsigned int centerAndAlignPrincipalAxes(GaussianShape& shape, const GaussianShapeFunction& func, Math::Matrix4D& back_xform,
																double mom_eq_thresh = 0.15);
		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEFUNCTIONS_HPP
