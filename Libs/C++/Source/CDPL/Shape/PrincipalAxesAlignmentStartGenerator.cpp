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


Shape::PrincipalAxesAlignmentStartGenerator::PrincipalAxesAlignmentStartGenerator():
	toRefTransform(Math::IdentityMatrix<double>(4, 4))
{}

void Shape::PrincipalAxesAlignmentStartGenerator::setup(const GaussianShapeFunction& ref_shape_func)
{
	if (!ref_shape_func.getShape() || ref_shape_func.getShape()->getNumElements() == 0) { // sanity check
		toRefTransform.assign(Math::IdentityMatrix<double>(4, 4));
		return;
	}
	
	Math::Vector3D ctr, x_axis, y_axis, z_axis, shape_dims;

	calcAlignmentAxes(ref_shape_func, ctr, x_axis, y_axis, z_axis, shape_dims);

	Math::Matrix4D::ArrayPointer ref_xform_data = toRefTransform.getData();
	
	ref_xform_data[0][0] = x_axis(0);
	ref_xform_data[1][0] = x_axis(1);
	ref_xform_data[2][0] = x_axis(2);

	ref_xform_data[0][1] = y_axis(0);
	ref_xform_data[1][1] = y_axis(1);
	ref_xform_data[2][1] = y_axis(2);

	ref_xform_data[0][2] = z_axis(0);
	ref_xform_data[1][2] = z_axis(1);
	ref_xform_data[2][2] = z_axis(2);

	ref_xform_data[0][3] = ctr(0);
	ref_xform_data[1][3] = ctr(1);
	ref_xform_data[2][3] = ctr(2);	
}

bool Shape::PrincipalAxesAlignmentStartGenerator::generate(const GaussianShapeFunction& func)
{
	startTransforms.clear();

	if (!func.getShape() || func.getShape()->getNumElements() == 0) // sanity check
		return false;

	Math::Vector3D ctr, x_axis, y_axis, z_axis, shape_dims;

	calcAlignmentAxes(func, ctr, x_axis, y_axis, z_axis, shape_dims);
	
	Math::Matrix4D to_orig_xform;
	Math::Matrix4D::ArrayPointer to_orig_xform_data = to_orig_xform.getData();

	to_orig_xform_data[0][0] = x_axis(0);
	to_orig_xform_data[0][1] = x_axis(1);
	to_orig_xform_data[0][2] = x_axis(2);

	to_orig_xform_data[1][0] = y_axis(0);
	to_orig_xform_data[1][1] = y_axis(1);
	to_orig_xform_data[1][2] = y_axis(2);

	to_orig_xform_data[2][0] = z_axis(0);
	to_orig_xform_data[2][1] = z_axis(1);
	to_orig_xform_data[2][2] = z_axis(2);

	to_orig_xform_data[3][3] = 1.0;

	to_orig_xform = to_orig_xform * Math::TranslationMatrix<double>(4, -ctr(0), -ctr(1), -ctr(2));

	QuaternionTransformation start_xform_quat;
	Math::Matrix4D start_xform_mtx(toRefTransform * to_orig_xform);

	matrixToQuaternion(start_xform_mtx, start_xform_quat);
	startTransforms.push_back(start_xform_quat);

	//
	
	start_xform_mtx.assign(toRefTransform * Math::RotationMatrix<double>(4, M_PI, 1.0, 0.0, 0.0) * to_orig_xform);

	matrixToQuaternion(start_xform_mtx, start_xform_quat);
	startTransforms.push_back(start_xform_quat);

	//

	start_xform_mtx.assign(toRefTransform * Math::RotationMatrix<double>(4, M_PI, 0.0, 1.0, 0.0) * to_orig_xform);

	matrixToQuaternion(start_xform_mtx, start_xform_quat);
	startTransforms.push_back(start_xform_quat);
	
	//

	start_xform_mtx.assign(toRefTransform * Math::RotationMatrix<double>(4, M_PI, 0.0, 0.0, 1.0) * to_orig_xform);

	matrixToQuaternion(start_xform_mtx, start_xform_quat);
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
