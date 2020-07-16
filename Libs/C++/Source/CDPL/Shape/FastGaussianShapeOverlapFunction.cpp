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
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


const double Shape::FastGaussianShapeOverlapFunction::DEF_RADIUS_SCALING_FACTOR = 1.3;


Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction():
	refShapeFunc(0), ovlShapeFunc(0), colorMatchFunc(), proximityOpt(true), fastExpFunc(true),
	radScalingFact(DEF_RADIUS_SCALING_FACTOR)
{}

Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction(const FastGaussianShapeOverlapFunction& func):
	refShapeFunc(func.refShapeFunc), ovlShapeFunc(func.ovlShapeFunc), colorMatchFunc(func.colorMatchFunc),
	proximityOpt(func.proximityOpt), fastExpFunc(func.fastExpFunc), radScalingFact(func.radScalingFact)
{}

Shape::FastGaussianShapeOverlapFunction::FastGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
																		  const GaussianShapeFunction& ovl_shape_func):
	refShapeFunc(&ref_shape_func), ovlShapeFunc(&ovl_shape_func), colorMatchFunc(), proximityOpt(true), fastExpFunc(true),
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

void Shape::FastGaussianShapeOverlapFunction::setShapeFunction(const GaussianShapeFunction& func, bool is_ref)
{
	(is_ref ? refShapeFunc : ovlShapeFunc) = &func;
}

const Shape::GaussianShapeFunction* Shape::FastGaussianShapeOverlapFunction::getShapeFunction(bool ref) const
{
	return (ref ? refShapeFunc : ovlShapeFunc);
}

void Shape::FastGaussianShapeOverlapFunction::setColorMatchFunction(const ColorMatchFunction& func)
{
	colorMatchFunc = func;
}

const Shape::GaussianShapeOverlapFunction::ColorMatchFunction& Shape::FastGaussianShapeOverlapFunction::getColorMatchFunction() const
{
	return colorMatchFunc;
}

double Shape::FastGaussianShapeOverlapFunction::calcSelfOverlap(bool ref, const ColorFilterFunction& col_filter_func) const
{
	if (ref) {
		if (!refShapeFunc)
			return 0.0;
		
		return calcOverlap(refShapeFunc->getProductList(), refShapeFunc->getProductList(), col_filter_func);
	}

	if (!ovlShapeFunc)
		return 0.0;
		
	return calcOverlap(ovlShapeFunc->getProductList(), ovlShapeFunc->getProductList(), col_filter_func);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlap(const ColorFilterFunction& col_filter_func) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), col_filter_func);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlap(const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	if (coords.getSize() != ovlShapeFunc->getProductList()->getNumShapeElements())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), coords, col_filter_func);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad, 
																	const ColorFilterFunction& col_filter_func) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	if (coords.getSize() != ovlShapeFunc->getProductList()->getNumShapeElements())
		return 0.0;

	return calcOverlapGradient(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), coords, grad, col_filter_func);
}

Shape::FastGaussianShapeOverlapFunction& Shape::FastGaussianShapeOverlapFunction::operator=(const FastGaussianShapeOverlapFunction& func)
{
	if (this == &func)
		return *this;
	
	refShapeFunc = func.refShapeFunc;
	ovlShapeFunc = func.ovlShapeFunc;
	colorMatchFunc = func.colorMatchFunc;
	proximityOpt = func.proximityOpt;
	fastExpFunc = func.fastExpFunc;
	radScalingFact = func.radScalingFact;
	
	return *this;
}

bool Shape::FastGaussianShapeOverlapFunction::checkShapeFuncsNotNull() const
{
	return (refShapeFunc && ovlShapeFunc);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
															const ColorFilterFunction& col_filter_func) const
{
	if (proximityOpt) {
		if (fastExpFunc)
			return calcOverlapFastExpProxCheck(ref_prod_list, ovl_prod_list, col_filter_func);

		return calcOverlapProxCheck(ref_prod_list, ovl_prod_list, col_filter_func);
		
	} else if (fastExpFunc)
		return calcOverlapFastExp(ref_prod_list, ovl_prod_list, col_filter_func);

	return calcOverlapExact(ref_prod_list, ovl_prod_list, col_filter_func);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																 const ColorFilterFunction& col_filter_func) const
{
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
	
			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * calcSquaredDistance(prod1_ctr, prod2->getCenter().getData()) / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																   const ColorFilterFunction& col_filter_func) const
{
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * calcSquaredDistance(prod1_ctr, prod2->getCenter().getData()) / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor *
					std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
	
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																	 const ColorFilterFunction& col_filter_func) const
{
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
			double prod1_radius = prod1->getRadius() * radScalingFact;

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;

				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius() * radScalingFact;

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
	
			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																			const ColorFilterFunction& col_filter_func) const
{
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
			double prod1_radius = prod1->getRadius() * radScalingFact;

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
		
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor *
					std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius() * radScalingFact;

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
	
			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
															const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	if (proximityOpt) {
		if (fastExpFunc)
			return calcOverlapFastExpProxCheck(ref_prod_list, ovl_prod_list, coords, col_filter_func);

		return calcOverlapProxCheck(ref_prod_list, ovl_prod_list, coords, col_filter_func);
		
	} else if (fastExpFunc)
		return calcOverlapFastExp(ref_prod_list, ovl_prod_list, coords, col_filter_func);

	return calcOverlapExact(ref_prod_list, ovl_prod_list, coords, col_filter_func);
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																 const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double overlap = 0.0;
	
	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1->getIndex()].getData();

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
				
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
				
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																   const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double overlap = 0.0;
	
	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1->getIndex()].getData();

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
				
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) *
					fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
				
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																	 const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double overlap = 0.0;
	
	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1->getIndex()].getData();
			double prod1_radius = prod1->getRadius() * radScalingFact;

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
				
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
				
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		double prod1_radius = prod1->getRadius() * radScalingFact;
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;

			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;
				
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																			const Math::Vector3DArray& coords, const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double overlap = 0.0;
	
	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1->getIndex()].getData();
			double prod1_radius = prod1->getRadius() * radScalingFact;

			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
				
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
				
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				overlap += prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) *
					fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);
			}
		}
		
		return overlap;
	}
	
	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		double prod1_radius = prod1->getRadius() * radScalingFact;
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;

			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2->getCenter().getData());
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;
				
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);
		}
	}

	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradient(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																	const Math::Vector3DArray& coords, Math::Vector3DArray& grad,
																	const ColorFilterFunction& col_filter_func) const
{
	grad.assign(ovl_prod_list->getNumShapeElements(), Math::Vector3D());

	if (proximityOpt) {
		if (fastExpFunc)
			return calcOverlapGradientFastExpProxCheck(ref_prod_list, ovl_prod_list, coords, grad, col_filter_func);

		return calcOverlapGradientProxCheck(ref_prod_list, ovl_prod_list, coords, grad, col_filter_func);
		
	} else if (fastExpFunc)
		return calcOverlapGradientFastExp(ref_prod_list, ovl_prod_list, coords, grad, col_filter_func);

	return calcOverlapGradientExact(ref_prod_list, ovl_prod_list, coords, grad, col_filter_func);	
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradientExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																		 const Math::Vector3DArray& coords, Math::Vector3DArray& grad,
																		 const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			std::size_t prod1_idx = prod1->getIndex();
			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1_idx].getData();
				 
			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
			
				Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				double overlap_contrib = prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);

				overlap += overlap_contrib;

				inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
				inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
				inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

				Math::Vector3D::Pointer prod1_grad = grad_data[prod1_idx].getData();
				double grad_factor = -prod1_delta * 2.0 * overlap_contrib;
			
				prod1_grad[0] += grad_factor * (prod1_ctr[0] - inters_prod_ctr_data[0]);
				prod1_grad[1] += grad_factor * (prod1_ctr[1] - inters_prod_ctr_data[1]);
				prod1_grad[2] += grad_factor * (prod1_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	
		return overlap;
	}

	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
			
			Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

			for (GaussianProduct::ConstFactorIterator f_it = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = coords_data[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad_data[fact_idx].getData();
				double grad_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += grad_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += grad_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += grad_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradientFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																		   const Math::Vector3DArray& coords, Math::Vector3DArray& grad,
																		   const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			std::size_t prod1_idx = prod1->getIndex();
			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1_idx].getData();
				 
			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
		
				Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				double overlap_contrib = prod1_weight * prod2->getWeightFactor() * vol_factor *
					std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);

				overlap += overlap_contrib;

				inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
				inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
				inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

				Math::Vector3D::Pointer prod1_grad = grad_data[prod1_idx].getData();
				double grad_factor = -prod1_delta * 2.0 * overlap_contrib;
			
				prod1_grad[0] += grad_factor * (prod1_ctr[0] - inters_prod_ctr_data[0]);
				prod1_grad[1] += grad_factor * (prod1_ctr[1] - inters_prod_ctr_data[1]);
				prod1_grad[2] += grad_factor * (prod1_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	
		return overlap;
	}

	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
		
			Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

			for (GaussianProduct::ConstFactorIterator f_it = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = coords_data[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad_data[fact_idx].getData();
				double grad_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += grad_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += grad_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += grad_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradientProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																			 const Math::Vector3DArray& coords, Math::Vector3DArray& grad,
																			 const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			std::size_t prod1_idx = prod1->getIndex();
			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			double prod1_radius = prod1->getRadius() * radScalingFact;
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1_idx].getData();
				 
			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
	
				Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				double overlap_contrib = prod1_weight * prod2->getWeightFactor() * vol_factor * std::sqrt(vol_factor) * std::exp(prod_fact_exp);

				overlap += overlap_contrib;

				inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
				inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
				inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

				Math::Vector3D::Pointer prod1_grad = grad_data[prod1_idx].getData();
				double grad_factor = -prod1_delta * 2.0 * overlap_contrib;
			
				prod1_grad[0] += grad_factor * (prod1_ctr[0] - inters_prod_ctr_data[0]);
				prod1_grad[1] += grad_factor * (prod1_ctr[1] - inters_prod_ctr_data[1]);
				prod1_grad[2] += grad_factor * (prod1_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	
		return overlap;
	}

	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		double prod1_radius = prod1->getRadius() * radScalingFact;
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
			
			Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * std::exp(-prod_fact_exp / delta);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

			for (GaussianProduct::ConstFactorIterator f_it = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = coords_data[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad_data[fact_idx].getData();
				double grad_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += grad_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += grad_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += grad_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}

double Shape::FastGaussianShapeOverlapFunction::calcOverlapGradientFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																					const Math::Vector3DArray& coords, Math::Vector3DArray& grad,
																					const ColorFilterFunction& col_filter_func) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;

	if (ref_prod_list->getMaxOrder() == 1 && ovl_prod_list->getMaxOrder() == 1) {
		for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
			const GaussianProduct* prod1 = *p_it1;
			std::size_t prod1_color = prod1->getColor();

			if (col_filter_func && !col_filter_func(prod1_color))
				continue;

			std::size_t prod1_idx = prod1->getIndex();
			double prod1_delta = prod1->getDelta();
			double prod1_weight = prod1->getWeightFactor();
			double prod1_radius = prod1->getRadius() * radScalingFact;
			Math::Vector3D::ConstPointer prod1_ctr = coords_data[prod1_idx].getData();
				 
			for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
				const GaussianProduct* prod2 = *p_it2;
				std::size_t prod2_color = prod2->getColor();

				if (col_filter_func && !col_filter_func(prod2_color))
					continue;

				if (!colorMatchFunc) {
					if (prod2_color != prod1_color)
						continue;

				} else if (!colorMatchFunc(prod1_color, prod2_color))
					continue;
	
				Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;

				double prod2_delta = prod2->getDelta();
				double delta = prod1_delta + prod2_delta;
				double vol_factor = M_PI / delta;
				double prod_fact_exp = -prod1_delta * prod2_delta * sqrd_prod_ctr_dist / delta;

				double overlap_contrib = prod1_weight * prod2->getWeightFactor() * vol_factor *
					std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(prod_fact_exp);

				overlap += overlap_contrib;

				inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
				inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
				inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

				Math::Vector3D::Pointer prod1_grad = grad_data[prod1_idx].getData();
				double grad_factor = -prod1_delta * 2.0 * overlap_contrib;
			
				prod1_grad[0] += grad_factor * (prod1_ctr[0] - inters_prod_ctr_data[0]);
				prod1_grad[1] += grad_factor * (prod1_ctr[1] - inters_prod_ctr_data[1]);
				prod1_grad[2] += grad_factor * (prod1_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	
		return overlap;
	}

	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (col_filter_func && !col_filter_func(prod1_color))
			continue;

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		double prod1_radius = prod1->getRadius() * radScalingFact;
		Math::Vector3D::ConstPointer prod1_ctr = 0;
		double prod1_fact_exp = 0.0;

		if (prod1->getNumFactors() == 1) {
			prod1_ctr = coords_data[prod1->getIndex()].getData();
			
		} else {
			ovl_prod_ctr.clear();
			prod1_ctr = ovl_prod_ctr_data;
			
			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it1 != f_end; ) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();

				ovl_prod_ctr_data[0] += fact1_delta * ctr1_data[0];
				ovl_prod_ctr_data[1] += fact1_delta * ctr1_data[1];
				ovl_prod_ctr_data[2] += fact1_delta * ctr1_data[2];
				
				++f_it1;
				
				for (GaussianProduct::ConstFactorIterator f_it2 = f_it1; f_it2 != f_end; ++f_it2) 
					prod1_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, coords_data[(*f_it2)->getIndex()].getData());
			}

			ovl_prod_ctr_data[0] /= prod1_delta;
			ovl_prod_ctr_data[1] /= prod1_delta;
			ovl_prod_ctr_data[2] /= prod1_delta;
		}
				 
		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (col_filter_func && !col_filter_func(prod2_color))
				continue;

			if (!colorMatchFunc) {
				if (prod2_color != prod1_color)
					continue;

			} else if (!colorMatchFunc(prod1_color, prod2_color))
				continue;
		
			Math::Vector3D::ConstPointer prod2_ctr = prod2->getCenter().getData();
			double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
			double max_dist = prod1_radius + prod2->getRadius() * radScalingFact;

			if (sqrd_prod_ctr_dist > (max_dist * max_dist))
				continue;

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
			double prod_fact_exp = prod1_fact_exp + prod2_delta * prod2->getProductFactorExponent();

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = coords_data[prod1_fact->getIndex()].getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() * calcSquaredDistance(ctr1_data, (*f_it2)->getCenter().getData());
			}
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * fastexp::IEEE<double, 3>::evaluate(-prod_fact_exp / delta);

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;

			for (GaussianProduct::ConstFactorIterator f_it = prod1->getFactorsBegin(), f_end = prod1->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = coords_data[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad_data[fact_idx].getData();
				double grad_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += grad_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += grad_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += grad_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}

#pragma GCC diagnostic pop
