/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrincipalAxesAlignmentStartGenerator.cpp 
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

 
#include "StaticInit.hpp"

#include <cmath>

#include "CDPL/Shape/PrincipalAxesAlignmentStartGenerator.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	void calcAlignmentAxes(const Shape::GaussianShapeFunction& func, Math::Vector3D& ctr, Math::Vector3D& x_axis,
						   Math::Vector3D& y_axis, Math::Vector3D& z_axis, Math::Vector3D& shape_dims)
	{
		Math::Matrix3D quad_tensor;

		func.calcCentroid(ctr);
		func.calcQuadrupoleTensor(ctr, quad_tensor);

		Shape::calcPrincipalAxes(quad_tensor, x_axis, y_axis, z_axis, shape_dims);
	}
}


Shape::PrincipalAxesAlignmentStartGenerator::PrincipalAxesAlignmentStartGenerator()
{}

void Shape::PrincipalAxesAlignmentStartGenerator::setup(GaussianShapeFunction& ref_shape_func, Math::Matrix4D& to_ref_xform)
{
	if (!ref_shape_func.getShape() || ref_shape_func.getShape()->getNumElements() == 0) { // sanity check
		to_ref_xform.assign(Math::IdentityMatrix<double>(4, 4));
		return;
	}

	ref_shape_func.reset();
	
	Math::Vector3D ctr, x_axis, y_axis, z_axis, shape_dims;

	calcAlignmentAxes(ref_shape_func, ctr, x_axis, y_axis, z_axis, shape_dims);

	Math::Matrix4D::ArrayPointer xform_data = to_ref_xform.getData();
	
	xform_data[0][0] = x_axis(0);
	xform_data[1][0] = x_axis(1);
	xform_data[2][0] = x_axis(2);

	xform_data[0][1] = y_axis(0);
	xform_data[1][1] = y_axis(1);
	xform_data[2][1] = y_axis(2);

	xform_data[0][2] = z_axis(0);
	xform_data[1][2] = z_axis(1);
	xform_data[2][2] = z_axis(2);

	xform_data[0][3] = ctr(0);
	xform_data[1][3] = ctr(1);
	xform_data[2][3] = ctr(2);

	xform_data[3][0] = 0.0;
	xform_data[3][1] = 0.0;
	xform_data[3][2] = 0.0;
	xform_data[3][3] = 1.0;

	Math::Matrix4D to_ctr_xform;
	xform_data = to_ctr_xform.getData();

	xform_data[0][0] = x_axis(0);
	xform_data[0][1] = x_axis(1);
	xform_data[0][2] = x_axis(2);
	
	xform_data[1][0] = y_axis(0);
	xform_data[1][1] = y_axis(1);
	xform_data[1][2] = y_axis(2);
	
	xform_data[2][0] = z_axis(0);
	xform_data[2][1] = z_axis(1);
	xform_data[2][2] = z_axis(2);
	
	xform_data[3][3] = 1.0;

	to_ctr_xform = to_ctr_xform * Math::TranslationMatrix<double>(4, -ctr(0), -ctr(1), -ctr(2));

	ref_shape_func.transform(to_ctr_xform);
}

bool Shape::PrincipalAxesAlignmentStartGenerator::generate(const GaussianShapeFunction& aligned_shape_func, Math::Matrix4D& ctr_xform)
{
	startTransforms.clear();

	if (!aligned_shape_func.getShape() || aligned_shape_func.getShape()->getNumElements() == 0) // sanity check
		return false;

	Math::Vector3D ctr, x_axis, y_axis, z_axis, shape_dims;

	calcAlignmentAxes(aligned_shape_func, ctr, x_axis, y_axis, z_axis, shape_dims);

	Math::Matrix4D::ArrayPointer xform_data = ctr_xform.getData();

	xform_data[0][0] = x_axis(0);
	xform_data[0][1] = x_axis(1);
	xform_data[0][2] = x_axis(2);
	xform_data[0][3] = 0.0;
	
	xform_data[1][0] = y_axis(0);
	xform_data[1][1] = y_axis(1);
	xform_data[1][2] = y_axis(2);
	xform_data[1][3] = 0.0;
	
	xform_data[2][0] = z_axis(0);
	xform_data[2][1] = z_axis(1);
	xform_data[2][2] = z_axis(2);
	xform_data[2][3] = 0.0;
	
	xform_data[3][0] = 0.0;
	xform_data[3][1] = 0.0;
	xform_data[3][2] = 0.0;
	xform_data[3][3] = 1.0;

	ctr_xform = ctr_xform * Math::TranslationMatrix<double>(4, -ctr(0), -ctr(1), -ctr(2));

	QuaternionTransformation start_xform_quat;

	start_xform_quat[0] = 1.0;

	startTransforms.push_back(start_xform_quat);

	//
	
	start_xform_quat[0] = 0.0;
	start_xform_quat[1] = 1.0;

	startTransforms.push_back(start_xform_quat);

	//
	
	start_xform_quat[1] = 0.0;
	start_xform_quat[2] = 1.0;

	startTransforms.push_back(start_xform_quat);
	
	//

	start_xform_quat[2] = 0.0;
	start_xform_quat[3] = 1.0;

	startTransforms.push_back(start_xform_quat);

	return true;
}
			
std::size_t Shape::PrincipalAxesAlignmentStartGenerator::getNumStartTransforms() const
{
    return startTransforms.size();
}

const Shape::QuaternionTransformation& Shape::PrincipalAxesAlignmentStartGenerator::getStartTransform(std::size_t idx) const
{
    if (idx >= startTransforms.size())
		throw Base::IndexError("PrincipalAxesAlignmentStartGenerator: start transform index out of bounds");

    return startTransforms[idx];
}
