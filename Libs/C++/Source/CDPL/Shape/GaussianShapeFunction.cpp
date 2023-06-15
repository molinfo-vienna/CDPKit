/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunction.cpp 
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

#include <algorithm>
#include <cmath>
#include <functional>

#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


namespace
{

	void addCentroidContrib(const Shape::GaussianProduct* prod_term, Math::Vector3D::Pointer ctr)
	{
		Math::Vector3D::ConstPointer prod_ctr = prod_term->getCenter().getData();
		double vol = prod_term->getVolume();
		
		if (prod_term->hasOddOrder()) {
			ctr[0] += vol * prod_ctr[0];
			ctr[1] += vol * prod_ctr[1];
			ctr[2] += vol * prod_ctr[2];

		} else {
			ctr[0] -= vol * prod_ctr[0];
			ctr[1] -= vol * prod_ctr[1];
			ctr[2] -= vol * prod_ctr[2];
		}
	}

	void addQuadTensorContrib(const Shape::GaussianProduct* prod_term, Math::Vector3D::ConstPointer shape_ctr, Math::Matrix3D::ArrayPointer tensor)
	{
		Math::Vector3D::ConstPointer prod_ctr = prod_term->getCenter().getData();
		double vol = prod_term->getVolume();
		double diag_const = 1.0 / (2.0 * prod_term->getDelta());
		double trans_prod_ctr[3] = { prod_ctr[0] - shape_ctr[0], prod_ctr[1] - shape_ctr[1], prod_ctr[2] - shape_ctr[2] };

		if (prod_term->hasOddOrder()) {
			tensor[0][1] += trans_prod_ctr[0] * trans_prod_ctr[1] * vol;
			tensor[0][2] += trans_prod_ctr[0] * trans_prod_ctr[2] * vol;
			tensor[1][2] += trans_prod_ctr[1] * trans_prod_ctr[2] * vol;

			tensor[0][0] += (trans_prod_ctr[0] * trans_prod_ctr[0] + diag_const) * vol;
			tensor[1][1] += (trans_prod_ctr[1] * trans_prod_ctr[1] + diag_const) * vol;
			tensor[2][2] += (trans_prod_ctr[2] * trans_prod_ctr[2] + diag_const) * vol;

		} else {
			tensor[0][1] -= trans_prod_ctr[0] * trans_prod_ctr[1] * vol;
			tensor[0][2] -= trans_prod_ctr[0] * trans_prod_ctr[2] * vol;
			tensor[1][2] -= trans_prod_ctr[1] * trans_prod_ctr[2] * vol;

			tensor[0][0] -= (trans_prod_ctr[0] * trans_prod_ctr[0] + diag_const) * vol;
			tensor[1][1] -= (trans_prod_ctr[1] * trans_prod_ctr[1] + diag_const) * vol;
			tensor[2][2] -= (trans_prod_ctr[2] * trans_prod_ctr[2] + diag_const) * vol;
		}
	}

	void copyUpperToLower(Math::Matrix3D::ArrayPointer mtx)
	{
		mtx[1][0] = mtx[0][1];
		mtx[2][0] = mtx[0][2];
		mtx[2][1] = mtx[1][2];
	}
}


constexpr std::size_t Shape::GaussianShapeFunction::DEF_MAX_PRODUCT_ORDER;
constexpr double      Shape::GaussianShapeFunction::DEF_DISTANCE_CUTOFF;


Shape::GaussianShapeFunction::GaussianShapeFunction():
	shape(0), prodList(new GaussianProductList())
{
	prodList->setMaxOrder(DEF_MAX_PRODUCT_ORDER);
	prodList->setDistanceCutoff(DEF_DISTANCE_CUTOFF);
}

Shape::GaussianShapeFunction::GaussianShapeFunction(const GaussianShapeFunction& func):
	shape(func.shape), prodList(new GaussianProductList(*func.prodList))
{}

Shape::GaussianShapeFunction::GaussianShapeFunction(const GaussianShape& shape):
	prodList(new GaussianProductList())
{
	prodList->setMaxOrder(DEF_MAX_PRODUCT_ORDER);
	prodList->setDistanceCutoff(DEF_DISTANCE_CUTOFF);
	
    setShape(shape);
}

Shape::GaussianShapeFunction::~GaussianShapeFunction() {}
	
void Shape::GaussianShapeFunction::setMaxOrder(std::size_t max_order)
{
	prodList->setMaxOrder(max_order);
}

std::size_t Shape::GaussianShapeFunction::getMaxOrder() const
{
    return prodList->getMaxOrder();
}

void Shape::GaussianShapeFunction::setDistanceCutoff(double cutoff)
{
	prodList->setDistanceCutoff(cutoff);
}

double Shape::GaussianShapeFunction::getDistanceCutoff() const
{
	return prodList->getDistanceCutoff();
}

void Shape::GaussianShapeFunction::setShape(const GaussianShape& shape)
{
	this->shape = &shape;
	
	prodList->setup(shape);
}

const Shape::GaussianShape* Shape::GaussianShapeFunction::getShape() const
{
	return shape;
}

void Shape::GaussianShapeFunction::reset()
{
	if (!shape)
		return;

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		GaussianProduct* prod = *p_it;

		if (prod->getNumFactors() == 1)
			prod->init(shape->getElement(prod->getIndex()));
		else
			prod->init();
	}
}

void Shape::GaussianShapeFunction::transform(const Math::Matrix4D& xform) 
{
	if (!shape)
		return;

	const Math::Matrix4D::ConstArrayPointer xform_data = xform.getData();

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		GaussianProduct* prod = *p_it;

		if (prod->getNumFactors() == 1)
			Shape::transform(prod->getCenter().getData(), xform_data, shape->getElement(prod->getIndex()).getPosition().getData());
		else
			prod->init();
	}
}

const Math::Vector3D& Shape::GaussianShapeFunction::getElementPosition(std::size_t idx) const
{
	if (idx >= shape->getNumElements())
		throw Base::IndexError("GaussianShapeFunction: element index out of bounds");

	return prodList->getProduct(idx)->getCenter();
}

void Shape::GaussianShapeFunction::getElementPositions(Math::Vector3DArray& coords) const
{
	if (!shape)
		return;

	coords.resize(shape->getNumElements());

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		GaussianProduct* prod = *p_it;

		if (prod->getNumFactors() > 1)
			break;

		std::size_t elem_idx = prod->getIndex();

		coords[elem_idx] = prod->getCenter();
	}
}

double Shape::GaussianShapeFunction::calcDensity(const Math::Vector3D& pos) const
{
	Math::Vector3D::ConstPointer pos_data = pos.getData();
	double density = 0.0;

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		const GaussianProduct* prod = *p_it;
		double contrib = prod->getWeightFactor() * prod->getProductFactor() * std::exp(-prod->getDelta() * calcSquaredDistance(pos_data, prod->getCenter().getData()));
		
		if (prod->hasOddOrder())
			density += contrib;
		else
			density -= contrib;
	}

	return density;
}

double Shape::GaussianShapeFunction::calcVolume() const
{
	return prodList->getVolume();
}

double Shape::GaussianShapeFunction::calcSurfaceArea() const
{
   	double area = 0.0;

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		const GaussianProduct* prod = *p_it;

		if (prod->getNumFactors() == 1) {
			area += 3.0 * prod->getVolume() / prod->getRadius();
			continue;
		}

		double tmp = 0.0;
		double delta_const = 1.5 / prod->getDelta();
		Math::Vector3D::ConstPointer prod_ctr = prod->getCenter().getData();
		
		for (GaussianProduct::ConstFactorIterator f_it = prod->getFactorsBegin(), f_end = prod->getFactorsEnd(); f_it != f_end; ++f_it) {
			const GaussianProduct* prod_factor = *f_it;
			double r = prod_factor->getRadius();
			
			tmp += prod_factor->getKappa() * (delta_const + calcSquaredDistance(prod_factor->getCenter().getData(), prod_ctr)) / (r * r * r);
		}

		if (prod->hasOddOrder())
			area += tmp * 2.0 * prod->getVolume();
		else
			area -= tmp * 2.0 * prod->getVolume();
	}
	
	return area;
}

double Shape::GaussianShapeFunction::calcSurfaceArea(std::size_t elem_idx) const
{
	double area = 0.0;

	for (GaussianProductList::ConstProductIterator p_it = prodList->getProductsBegin(), p_end = prodList->getProductsEnd(); p_it != p_end; ++p_it) {
		const GaussianProduct* prod = *p_it;

		if (prod->getNumFactors() == 1) {
			if (prod->getIndex() != elem_idx)
				continue;
			
			area += 3.0 * prod->getVolume() / prod->getRadius();
			continue;
		}

		double tmp = 0.0;
		double delta_const = 1.5 / prod->getDelta();
		Math::Vector3D::ConstPointer prod_ctr = prod->getCenter().getData();
		
		for (GaussianProduct::ConstFactorIterator f_it = prod->getFactorsBegin(), f_end = prod->getFactorsEnd(); f_it != f_end; ++f_it) {
			const GaussianProduct* prod_factor = *f_it;

			if (prod_factor->getIndex() != elem_idx)
				continue;
			
			double r = prod_factor->getRadius();
			
			tmp += prod_factor->getKappa() * (delta_const + calcSquaredDistance(prod_factor->getCenter().getData(), prod_ctr)) / (r * r * r);
		}

		if (prod->hasOddOrder())
			area += tmp * 2.0 * prod->getVolume();
		else
			area -= tmp * 2.0 * prod->getVolume();
	}
	
	return area;
}

void Shape::GaussianShapeFunction::calcCentroid(Math::Vector3D& ctr) const
{
	ctr.clear();

	std::for_each(prodList->getProductsBegin(), prodList->getProductsEnd(),
				  std::bind(&addCentroidContrib, std::placeholders::_1, ctr.getData()));

	ctr /= prodList->getVolume();
}

void Shape::GaussianShapeFunction::calcQuadrupoleTensor(const Math::Vector3D& ctr, Math::Matrix3D& quad_tensor) const
{
	Math::Matrix3D::ArrayPointer tensor_data = quad_tensor.getData();
	
	quad_tensor.clear();

	std::for_each(prodList->getProductsBegin(), prodList->getProductsEnd(),
				  std::bind(&addQuadTensorContrib, std::placeholders::_1, ctr.getData(), tensor_data));

	copyUpperToLower(tensor_data);
	
	quad_tensor /= prodList->getVolume();
}

Shape::GaussianShapeFunction& Shape::GaussianShapeFunction::operator=(const GaussianShapeFunction& func)
{
	if (this == &func)
		return * this;

	shape = func.shape;
	*prodList = *func.prodList;

	return * this;
}

const Shape::GaussianProductList* Shape::GaussianShapeFunction::getProductList() const
{
	return prodList.get();
}
