/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeOverlapFunction.cpp 
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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing" // fastexp causes annoying aliasing warnings!

#include "StaticInit.hpp"

#include <cmath>

#include "FastExp/fastexp.h"

#include "CDPL/Shape/FastGaussianShapeOverlapFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


const double Shape::FastGaussianShapeOverlapFunction::DEF_RADIUS_SCALING_FACTOR = 1.3;


Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction():
	GaussianShapeOverlapFunction(), proximityOpt(true), fastExpFunc(true),
	radScalingFact(DEF_RADIUS_SCALING_FACTOR)
{}

Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction(const FastGaussianShapeOverlapFunction& func):
	GaussianShapeOverlapFunction(func), proximityOpt(func.proximityOpt), fastExpFunc(func.fastExpFunc),
	radScalingFact(func.radScalingFact)
{}

Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
																		  const GaussianShapeFunction& ovl_shape_func):
	GaussianShapeOverlapFunction(ref_shape_func, ovl_shape_func), proximityOpt(true), fastExpFunc(true),
	radScalingFact(DEF_RADIUS_SCALING_FACTOR)
{}

Shape::FastGaussianShapeOverlapFunction::~FastGaussianShapeOverlapFunction() {}


void Shape::FastGaussianShapeOverlapFunction::proximityOptimization(bool enable)
{
	proximityOpt = enable;
}

bool Shape::FastGaussianShapeOverlapFunction::proximityOptimization() const
{
	return proximityOpt;
}

void Shape::FastGaussianShapeOverlapFunction::fastExpFunction(bool enable)
{
	fastExpFunc = enable;
}

bool Shape::FastGaussianShapeOverlapFunction::fastExpFunction() const
{
	return fastExpFunc;
}

void Shape::FastGaussianShapeOverlapFunction::setRadiusScalingFactor(double factor)
{
	radScalingFact = factor;
}

double Shape::FastGaussianShapeOverlapFunction::getRadiusScalingFactor() const
{
	return radScalingFact;
}

Shape::FastGaussianShapeOverlapFunction& Shape::FastGaussianShapeOverlapFunction::operator=(const FastGaussianShapeOverlapFunction& func)
{
	if (this == &func)
		return *this;
	
	GaussianShapeOverlapFunction::operator=(func);

	proximityOpt = func.proximityOpt;
	fastExpFunc = func.fastExpFunc;
	radScalingFact = func.radScalingFact;
	
	return *this;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapImpl(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2,
																const GaussianProductCenterArray& trans_prod_ctrs, bool orig_centers, bool rigid_xform) const
{
	double overlap = 0.0;

	for (GaussianProductList::ConstProductIterator p_it1 = prod_list1->getProductsBegin(), p_end1 = prod_list1->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		std::size_t prod1_color = prod1->getColor();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius() * radScalingFact;

		for (GaussianProductList::ConstProductIterator p_it2 = prod_list2->getProductsBegin(), p_end2 = prod_list2->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;

			if (prod2->getColor() != prod1_color) // TODO
				continue;
	
			if (proximityOpt) {
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, (orig_centers ? prod2->getCenter().getData() : trans_prod_ctrs[prod2->getIndex()].getData()));
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
			}
				
			double prod_fact_exp = prod1_delta * prod1->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() *
						calcSquaredDistance(ctr1_data,
											(orig_centers ? (*f_it2)->getCenter() : trans_prod_ctrs[(*f_it2)->getIndex()]).getData());
			}

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;

			if (orig_centers || rigid_xform || prod2->getNumFactors() < 2)
				 prod_fact_exp += prod2_delta * prod2->getProductFactorExponent();

			else {
				for (GaussianProduct::ConstFactorIterator f_it1 = prod2->getFactorsBegin(), f_end = prod2->getFactorsEnd(); f_it1 != f_end; ) {
					const GaussianProduct* prod1_fact = *f_it1;
					Math::Vector3D::ConstPointer ctr1_data = trans_prod_ctrs[prod1_fact->getIndex()].getData();
					double fact1_delta = prod1_fact->getDelta();

					++f_it1;
				
					for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
						prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, trans_prod_ctrs[(*f_it2)->getIndex()].getData());
				}
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * (fastExpFunc ? fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta) : std::exp(-prod_fact_exp / delta));
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradientImpl(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2,
																		const GaussianProductCenterArray& trans_prod_ctrs, Math::Vector3DArray::StorageType& grad,
																		bool rigid_xform) const
{
	double overlap = 0.0;
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = prod_list1->getProductsBegin(), p_end1 = prod_list1->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		std::size_t prod1_color = prod1->getColor();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius() * radScalingFact;

		for (GaussianProductList::ConstProductIterator p_it2 = prod_list2->getProductsBegin(), p_end2 = prod_list2->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;

			if (prod2->getColor() != prod1_color) // TODO
				continue;

			Math::Vector3D::ConstPointer prod2_ctr = trans_prod_ctrs[prod2->getIndex()].getData();

			if (proximityOpt) {
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
			}
				
			double prod_fact_exp = prod1_delta * prod1->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() *
						calcSquaredDistance(ctr1_data, trans_prod_ctrs[(*f_it2)->getIndex()].getData());
			}

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;

			if (rigid_xform || prod2->getNumFactors() < 2)
				 prod_fact_exp += prod2_delta * prod2->getProductFactorExponent();

			else {
				for (GaussianProduct::ConstFactorIterator f_it1 = prod2->getFactorsBegin(), f_end = prod2->getFactorsEnd(); f_it1 != f_end; ) {
					const GaussianProduct* prod1_fact = *f_it1;
					Math::Vector3D::ConstPointer ctr1_data = trans_prod_ctrs[prod1_fact->getIndex()].getData();
					double fact1_delta = prod1_fact->getDelta();

					++f_it1;
				
					for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
						prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, trans_prod_ctrs[(*f_it2)->getIndex()].getData());
				}
			}
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * (fastExpFunc ? fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta) : std::exp(-prod_fact_exp / delta));

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

			for (GaussianProduct::ConstFactorIterator f_it = prod2->getFactorsBegin(), f_end = prod2->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = trans_prod_ctrs[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad[fact_idx].getData();
				double mul_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += mul_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += mul_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += mul_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}

#pragma GCC diagnostic pop
