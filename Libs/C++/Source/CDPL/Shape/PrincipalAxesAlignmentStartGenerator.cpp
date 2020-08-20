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
	ctrAlignmentMode(SHAPE_CENTROID), refShape(0), symThreshold(0.15), 
	refAxesSwapFlags(getAxesSwapFlags(SymmetryClass::UNDEF)), numSubTransforms(0)
{}

unsigned int Shape::PrincipalAxesAlignmentStartGenerator::setupReference(GaussianShapeFunction& func, Math::Matrix4D& xform) const
{
	Math::Matrix4D to_ctr_xform;
	Math::Matrix4D from_ctr_xform;
	unsigned int sym_class = calcCenterAlignmentTransforms(func, to_ctr_xform, from_ctr_xform, symThreshold);

	if (sym_class == SymmetryClass::UNDEF)
		return SymmetryClass::UNDEF;

	func.transform(to_ctr_xform);
		
	xform.assign(from_ctr_xform);
	
	return sym_class;
}

unsigned int Shape::PrincipalAxesAlignmentStartGenerator::setupAligned(GaussianShapeFunction& func, Math::Matrix4D& xform) const
{
	Math::Matrix4D to_ctr_xform;
	Math::Matrix4D from_ctr_xform;
	unsigned int sym_class = calcCenterAlignmentTransforms(func, to_ctr_xform, from_ctr_xform, symThreshold);

	if (sym_class == SymmetryClass::UNDEF)
		return SymmetryClass::UNDEF;

	func.transform(to_ctr_xform);
		
	xform.assign(to_ctr_xform);
	
	return sym_class;
}

void Shape::PrincipalAxesAlignmentStartGenerator::setCenterAlignmentMode(CenterAlignmentMode mode)
{
	ctrAlignmentMode = mode;
}

Shape::PrincipalAxesAlignmentStartGenerator::CenterAlignmentMode Shape::PrincipalAxesAlignmentStartGenerator::getCenterAlignmentMode() const
{
	return ctrAlignmentMode;
}

void Shape::PrincipalAxesAlignmentStartGenerator::setSymmetryThreshold(double thresh)
{
	symThreshold = thresh;
}

double Shape::PrincipalAxesAlignmentStartGenerator::getSymmetryThreshold()
{
	return symThreshold;
}

void Shape::PrincipalAxesAlignmentStartGenerator::setReference(const GaussianShapeFunction& func, unsigned int sym_class)
{
	refShape = func.getShape();
	refAxesSwapFlags = getAxesSwapFlags(sym_class);
}

bool Shape::PrincipalAxesAlignmentStartGenerator::generate(const GaussianShapeFunction& func, unsigned int sym_class)
{
	if (!refShape)
		return false;

	unsigned int axes_swap_flags = refAxesSwapFlags | getAxesSwapFlags(sym_class);

	startTransforms.clear();
	numSubTransforms = 4;
	
	if (axes_swap_flags & 0b01) 
		numSubTransforms += 4;
				
	if (axes_swap_flags & 0b10) 
		numSubTransforms += 4;
	
	if (axes_swap_flags == 0b11)
		numSubTransforms += 12;

	if (ctrAlignmentMode & SHAPE_CENTROID)
		generate(Math::Vector3D(), func, axes_swap_flags);

	switch (ctrAlignmentMode & (NON_COLOR_ELEMENT_CENTERS | COLOR_ELEMENT_CENTERS)) {

		case (NON_COLOR_ELEMENT_CENTERS | COLOR_ELEMENT_CENTERS):
			for (GaussianShape::ConstElementIterator it = refShape->getElementsBegin(), end = refShape->getElementsEnd(); it != end; ++it) 
				generate(it->getPosition(), func, axes_swap_flags);

			return true;

		case NON_COLOR_ELEMENT_CENTERS:
			for (GaussianShape::ConstElementIterator it = refShape->getElementsBegin(), end = refShape->getElementsEnd(); it != end; ++it) 
				if (it->getColor() == 0)
					generate(it->getPosition(), func, axes_swap_flags);

			return true;

		case COLOR_ELEMENT_CENTERS:
			for (GaussianShape::ConstElementIterator it = refShape->getElementsBegin(), end = refShape->getElementsEnd(); it != end; ++it) 
				if (it->getColor() != 0)
					generate(it->getPosition(), func, axes_swap_flags);

			return true;

		default:
			return true;
	}

	return true;
}

void Shape::PrincipalAxesAlignmentStartGenerator::generate(const Math::Vector3D& ctr_trans, const GaussianShapeFunction& func, unsigned int axes_swap_flags)
{
	Math::Vector3D::ConstPointer ctr_trans_data = ctr_trans.getData();

	addStartTransform(ctr_trans_data, IDENTITY_ROT);
	addStartTransform(ctr_trans_data, X_180_ROT);
	addStartTransform(ctr_trans_data, Y_180_ROT);
	addStartTransform(ctr_trans_data, Z_180_ROT);

	if (axes_swap_flags & 0b01) {
		addStartTransform(ctr_trans_data, XY_SWAP_ROT);
		addStartTransform(ctr_trans_data, X_180_ROT * XY_SWAP_ROT);
		addStartTransform(ctr_trans_data, Y_180_ROT * XY_SWAP_ROT);
		addStartTransform(ctr_trans_data, Z_180_ROT * XY_SWAP_ROT);
	}
			
	if (axes_swap_flags & 0b10) {
		addStartTransform(ctr_trans_data, YZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, X_180_ROT * YZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, Y_180_ROT * YZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, Z_180_ROT * YZ_SWAP_ROT);
	}

	if (axes_swap_flags == 0b11) {
		addStartTransform(ctr_trans_data, XZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, X_180_ROT * XZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, Y_180_ROT * XZ_SWAP_ROT);
		addStartTransform(ctr_trans_data, Z_180_ROT * XZ_SWAP_ROT);
		
		addStartTransform(ctr_trans_data, XYZ_SWAP_ROT1);
		addStartTransform(ctr_trans_data, X_180_ROT * XYZ_SWAP_ROT1);
		addStartTransform(ctr_trans_data, Y_180_ROT * XYZ_SWAP_ROT1);
		addStartTransform(ctr_trans_data, Z_180_ROT * XYZ_SWAP_ROT1);

		addStartTransform(ctr_trans_data, XYZ_SWAP_ROT2);
		addStartTransform(ctr_trans_data, X_180_ROT * XYZ_SWAP_ROT2);
		addStartTransform(ctr_trans_data, Y_180_ROT * XYZ_SWAP_ROT2);
		addStartTransform(ctr_trans_data, Z_180_ROT * XYZ_SWAP_ROT2);
	}
}
			
std::size_t Shape::PrincipalAxesAlignmentStartGenerator::getNumStartTransforms() const
{
    return startTransforms.size();
}

std::size_t Shape::PrincipalAxesAlignmentStartGenerator::getNumStartSubTransforms() const
{
    return numSubTransforms;
}

const Shape::QuaternionTransformation& Shape::PrincipalAxesAlignmentStartGenerator::getStartTransform(std::size_t idx) const
{
    if (idx >= startTransforms.size())
		throw Base::IndexError("PrincipalAxesAlignmentStartGenerator: start transform index out of bounds");

    return startTransforms[idx];
}

template <typename QE>
void Shape::PrincipalAxesAlignmentStartGenerator::addStartTransform(Math::Vector3D::ConstPointer ctr_trans_data, const Math::QuaternionExpression<QE>& rot_quat)
{
	QuaternionTransformation xform;
	QuaternionTransformation::Pointer xform_data = xform.getData();

	xform_data[0] = rot_quat().getC1();
	xform_data[1] = rot_quat().getC2();
	xform_data[2] = rot_quat().getC3();
	xform_data[3] = rot_quat().getC4();
	xform_data[4] = ctr_trans_data[0];
	xform_data[5] = ctr_trans_data[1];
	xform_data[6] = ctr_trans_data[2];

	startTransforms.push_back(xform);
}