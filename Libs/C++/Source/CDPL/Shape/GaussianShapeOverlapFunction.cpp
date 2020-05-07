/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunction.cpp 
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

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction():
	refShapeFunc(0), ovlShapeFunc(0)
{}

Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction(const GaussianShapeOverlapFunction& func):
	refShapeFunc(func.refShapeFunc), ovlShapeFunc(func.ovlShapeFunc)
{}

Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
																  const GaussianShapeFunction& ovl_shape_func):
	refShapeFunc(&ref_shape_func), ovlShapeFunc(&ovl_shape_func)
{}

Shape::GaussianShapeOverlapFunction::~GaussianShapeOverlapFunction() {}

void Shape::GaussianShapeOverlapFunction::setShapeFunction(const GaussianShapeFunction& func, bool is_ref)
{
	(is_ref ? refShapeFunc : ovlShapeFunc) = &func;
}

const Shape::GaussianShapeFunction* Shape::GaussianShapeOverlapFunction::getShapeFunction(bool ref) const
{
	return (ref ? refShapeFunc : ovlShapeFunc);
}

double Shape::GaussianShapeOverlapFunction::calcSelfOverlap(bool ref) const
{
	if (ref) {
		if (!refShapeFunc)
			return 0.0;
		
		return calcOverlapImpl(refShapeFunc->getProductList(), refShapeFunc->getProductList(), prodCenters, true, true);
	}

	if (!ovlShapeFunc)
		return 0.0;
		
	return calcOverlapImpl(ovlShapeFunc->getProductList(), ovlShapeFunc->getProductList(), prodCenters, true, true);
}

double Shape::GaussianShapeOverlapFunction::calcOverlap() const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;
	
	return calcOverlapImpl(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), prodCenters, true, true);
}

double Shape::GaussianShapeOverlapFunction::calcOverlap(const Math::Matrix4D& xform, bool rigid_xform)
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	prepareOverlapCalc(xform);

	return calcOverlapImpl(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), prodCenters, false, rigid_xform);
}

double Shape::GaussianShapeOverlapFunction::calcOverlapGradient(const Math::Matrix4D& xform, Math::Vector3DArray& grad, bool rigid_xform)
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	prepareGradientCalc(xform, grad);

	return calcOverlapGradientImpl(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), prodCenters, grad.getData(), rigid_xform);
}

Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeOverlapFunction::operator=(const GaussianShapeOverlapFunction& func)
{
	if (this == &func)
		return *this;
	
	refShapeFunc = func.refShapeFunc;
	ovlShapeFunc = func.ovlShapeFunc;
	
	return *this;
}

bool Shape::GaussianShapeOverlapFunction::checkShapeFuncsNotNull() const
{
	return (refShapeFunc && ovlShapeFunc);
}

void Shape::GaussianShapeOverlapFunction::prepareOverlapCalc(const Math::Matrix4D& xform)
{
	const GaussianProductList* prod_list = ovlShapeFunc->getProductList();
	std::size_t num_prods = prod_list->getNumProducts();
	Math::Matrix4D::ConstArrayPointer xform_data = xform.getData();
	
	if (prodCenters.size() < num_prods)
		prodCenters.resize(num_prods);

	for (std::size_t i = 0; i < num_prods; i++)
		transform(prodCenters[i].getData(), xform_data, prod_list->getProduct(i)->getCenter().getData());
}

void Shape::GaussianShapeOverlapFunction::prepareGradientCalc(const Math::Matrix4D& xform, Math::Vector3DArray& grad)
{
	prepareOverlapCalc(xform);

	grad.assign(ovlShapeFunc->getProductList()->getNumShapeElements(), Math::Vector3D());
}

double Shape::GaussianShapeOverlapFunction::calcOverlapImpl(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2,
															const GaussianProductCenterArray& trans_prod_ctrs, bool orig_centers, bool rigid_xform) const
{
	return 0.0;
}

double Shape::GaussianShapeOverlapFunction::calcOverlapGradientImpl(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2,
																	const GaussianProductCenterArray& trans_prod_ctrs, Math::Vector3DArray::StorageType& grad,
																	bool rigid_xform) const
{
	return 0.0;
}
