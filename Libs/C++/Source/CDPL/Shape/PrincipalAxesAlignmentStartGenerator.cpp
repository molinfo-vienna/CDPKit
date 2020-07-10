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
#include "CDPL/Shape/GaussianShapeFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	const Math::DQuaternion IDENTITY_ROT(1.0, 0.0, 0.0, 0.0);

	const Math::DQuaternion X_180_ROT(0.0, 1.0, 0.0, 0.0);
	const Math::DQuaternion Y_180_ROT(0.0, 0.0, 1.0, 0.0);
	const Math::DQuaternion Z_180_ROT(0.0, 0.0, 0.0, 1.0);
	
	const Math::DQuaternion XY_SWAP_ROT(std::cos(M_PI * 0.25), 0.0, 0.0, std::sin(M_PI * 0.25));
	const Math::DQuaternion YZ_SWAP_ROT(std::cos(M_PI * 0.25), std::sin(M_PI * 0.25), 0.0, 0.0);
	const Math::DQuaternion XZ_SWAP_ROT(std::cos(M_PI * 0.25), 0.0, std::sin(M_PI * 0.25), 0.0);

	const Math::DQuaternion XYZ_SWAP_ROT1(std::cos(M_PI / 3.0), std::sin(M_PI / 3.0) * 0.5773502692,
										  std::sin(M_PI / 3.0) * 0.5773502692, std::sin(M_PI / 3.0) * 0.5773502692);
	const Math::DQuaternion XYZ_SWAP_ROT2(std::cos(2.0 * M_PI / 3.0), std::sin(2.0 * M_PI / 3.0) * 0.5773502692,
										  std::sin(2.0 * M_PI / 3.0) * 0.5773502692, std::sin(2.0 * M_PI / 3.0) * 0.5773502692);

	unsigned int getAxesSwapFlags(unsigned int sym_class)
	{
		using namespace Shape;
		
		switch (sym_class) {

			case SymmetryClass::ASYMMETRIC:
				return 0;

			case SymmetryClass::PROLATE:
				return 0b01;

			case SymmetryClass::OBLATE:
				return 0b10;

			default:
				break;
		}

		return 0b11;
	}
}


Shape::PrincipalAxesAlignmentStartGenerator::PrincipalAxesAlignmentStartGenerator():
	refAxesSwapFlags(getAxesSwapFlags(SymmetryClass::UNDEF))
{}

unsigned int Shape::PrincipalAxesAlignmentStartGenerator::setupReference(GaussianShape& shape, GaussianShapeFunction& shape_func, Math::Matrix4D& xform) const
{
	return centerAndAlignPrincipalAxes(shape, shape_func, xform, true);
}

unsigned int Shape::PrincipalAxesAlignmentStartGenerator::setupAligned(GaussianShape& shape, GaussianShapeFunction& shape_func, Math::Matrix4D& xform) const
{
	return centerAndAlignPrincipalAxes(shape, shape_func, xform, false);
}

void Shape::PrincipalAxesAlignmentStartGenerator::setReference(const GaussianShapeFunction& ref_shape_func, unsigned int sym_class)
{
	refAxesSwapFlags = getAxesSwapFlags(sym_class);
}

bool Shape::PrincipalAxesAlignmentStartGenerator::generate(const GaussianShapeFunction& aligned_shape_func, unsigned int sym_class)
{
	startTransforms.clear();

	addStartTransform(IDENTITY_ROT);
	addStartTransform(X_180_ROT);
	addStartTransform(Y_180_ROT);
	addStartTransform(Z_180_ROT);

	unsigned int axes_swap_flags = (refAxesSwapFlags | getAxesSwapFlags(sym_class));
	
	if (axes_swap_flags & 0b01) {
		addStartTransform(XY_SWAP_ROT);
		addStartTransform(X_180_ROT * XY_SWAP_ROT);
		addStartTransform(Y_180_ROT * XY_SWAP_ROT);
		addStartTransform(Z_180_ROT * XY_SWAP_ROT);
	}
			
	if (axes_swap_flags & 0b10) {
		addStartTransform(YZ_SWAP_ROT);
		addStartTransform(X_180_ROT * YZ_SWAP_ROT);
		addStartTransform(Y_180_ROT * YZ_SWAP_ROT);
		addStartTransform(Z_180_ROT * YZ_SWAP_ROT);
	}

	if (axes_swap_flags == 0b11) {
		addStartTransform(XZ_SWAP_ROT);
		addStartTransform(X_180_ROT * XZ_SWAP_ROT);
		addStartTransform(Y_180_ROT * XZ_SWAP_ROT);
		addStartTransform(Z_180_ROT * XZ_SWAP_ROT);
		
		addStartTransform(XYZ_SWAP_ROT1);
		addStartTransform(X_180_ROT * XYZ_SWAP_ROT1);
		addStartTransform(Y_180_ROT * XYZ_SWAP_ROT1);
		addStartTransform(Z_180_ROT * XYZ_SWAP_ROT1);

		addStartTransform(XYZ_SWAP_ROT2);
		addStartTransform(X_180_ROT * XYZ_SWAP_ROT2);
		addStartTransform(Y_180_ROT * XYZ_SWAP_ROT2);
		addStartTransform(Z_180_ROT * XYZ_SWAP_ROT2);
	}
	
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

template <typename QE>
void Shape::PrincipalAxesAlignmentStartGenerator::addStartTransform(const Math::QuaternionExpression<QE>& rot_quat)
{
	QuaternionTransformation xform;

	xform[0] = rot_quat().getC1();
	xform[1] = rot_quat().getC2();
	xform[2] = rot_quat().getC3();
	xform[3] = rot_quat().getC4();
	
	startTransforms.push_back(xform);
}
