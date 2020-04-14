/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunction.cpp 
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

#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"


using namespace CDPL;


const std::size_t Shape::GaussianShapeFunction::DEF_MAX_PRODUCT_ORDER;
const double      Shape::GaussianShapeFunction::DEF_DISTANCE_CUTOFF = -0.3;


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
	
    setup(shape);
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

void Shape::GaussianShapeFunction::setup(const GaussianShape& shape)
{
	this->shape = &shape;
	
	prodList->setup(shape);
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

		if (prod->getNumFactors() == 0) {
			area += 3.0 * prod->getVolume() / prod->getRadius();
			continue;
		}

		double tmp = 0.0;
		double delta_const = 1.5 / prod->getDelta();
		Math::Vector3D::ConstPointer prod_ctr = prod->getCenter().getData();
		
		for (GaussianProduct::ConstFactorIterator f_it = prod->getFactorsBegin(), f_end = prod->getFactorsEnd(); f_it != f_end; ++f_it) {
			const GaussianProduct* prod_factor = *f_it;
			Math::Vector3D::ConstPointer prod_factor_ctr = prod_factor->getCenter().getData();

			double dx = prod_factor_ctr[0] - prod_ctr[0];
			double dy = prod_factor_ctr[1] - prod_ctr[1];
			double dz = prod_factor_ctr[2] - prod_ctr[2];
			double r = prod_factor->getRadius();
			
			tmp += prod_factor->getKappa() * (delta_const + dx * dx + dy * dy + dz * dz) / (r * r * r);
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

		if (prod->getNumFactors() == 0) {
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
			
			Math::Vector3D::ConstPointer prod_factor_ctr = prod_factor->getCenter().getData();

			double dx = prod_factor_ctr[0] - prod_ctr[0];
			double dy = prod_factor_ctr[1] - prod_ctr[1];
			double dz = prod_factor_ctr[2] - prod_ctr[2];
			double r = prod_factor->getRadius();
			
			tmp += prod_factor->getKappa() * (delta_const + dx * dx + dy * dy + dz * dz) / (r * r * r);
		}

		if (prod->hasOddOrder())
			area += tmp * 2.0 * prod->getVolume();
		else
			area -= tmp * 2.0 * prod->getVolume();
	}
	
	return area;
}

Shape::GaussianShapeFunction& Shape::GaussianShapeFunction::operator=(const GaussianShapeFunction& func)
{
	if (this == &func)
		return * this;

	shape = func.shape;
	*prodList = *func.prodList;

	return * this;
}
