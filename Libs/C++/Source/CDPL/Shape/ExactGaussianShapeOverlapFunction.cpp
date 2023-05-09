/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ExactGaussianShapeOverlapFunction.cpp 
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

#include <cmath>

#include "CDPL/Shape/ExactGaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


Shape::ExactGaussianShapeOverlapFunction::ExactGaussianShapeOverlapFunction():
	refShapeFunc(0), ovlShapeFunc(0), colorMatchFunc(), colorFilterFunc()
{}

Shape::ExactGaussianShapeOverlapFunction::ExactGaussianShapeOverlapFunction(const ExactGaussianShapeOverlapFunction& func):
	refShapeFunc(func.refShapeFunc), ovlShapeFunc(func.ovlShapeFunc), colorMatchFunc(func.colorMatchFunc),
	colorFilterFunc(func.colorFilterFunc)
{}

Shape::ExactGaussianShapeOverlapFunction::ExactGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
																			const GaussianShapeFunction& ovl_shape_func):
	refShapeFunc(&ref_shape_func), ovlShapeFunc(&ovl_shape_func), colorMatchFunc(), colorFilterFunc()
{}

Shape::ExactGaussianShapeOverlapFunction::~ExactGaussianShapeOverlapFunction() {}

void Shape::ExactGaussianShapeOverlapFunction::setShapeFunction(const GaussianShapeFunction& func, bool is_ref)
{
	(is_ref ? refShapeFunc : ovlShapeFunc) = &func;
}

const Shape::GaussianShapeFunction* Shape::ExactGaussianShapeOverlapFunction::getShapeFunction(bool ref) const
{
	return (ref ? refShapeFunc : ovlShapeFunc);
}

void Shape::ExactGaussianShapeOverlapFunction::setColorMatchFunction(const ColorMatchFunction& func)
{
	colorMatchFunc = func;
}

const Shape::GaussianShapeOverlapFunction::ColorMatchFunction& Shape::ExactGaussianShapeOverlapFunction::getColorMatchFunction() const
{
	return colorMatchFunc;
}

void Shape::ExactGaussianShapeOverlapFunction::setColorFilterFunction(const ColorFilterFunction& func)
{
	colorFilterFunc = func;
}

const Shape::GaussianShapeOverlapFunction::ColorFilterFunction& Shape::ExactGaussianShapeOverlapFunction::getColorFilterFunction() const
{
	return colorFilterFunc;
}

double Shape::ExactGaussianShapeOverlapFunction::calcSelfOverlap(bool ref) const
{
	if (ref) {
		if (!refShapeFunc)
			return 0.0;
		
		return calcOverlap(refShapeFunc->getProductList(), refShapeFunc->getProductList(), false);
	}

	if (!ovlShapeFunc)
		return 0.0;
		
	return calcOverlap(ovlShapeFunc->getProductList(), ovlShapeFunc->getProductList(), false);
}

double Shape::ExactGaussianShapeOverlapFunction::calcColorSelfOverlap(bool ref) const
{
	if (ref) {
		if (!refShapeFunc)
			return 0.0;
		
		return calcOverlap(refShapeFunc->getProductList(), refShapeFunc->getProductList(), true);
	}

	if (!ovlShapeFunc)
		return 0.0;
		
	return calcOverlap(ovlShapeFunc->getProductList(), ovlShapeFunc->getProductList(), true);
}

double Shape::ExactGaussianShapeOverlapFunction::calcOverlap() const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), false);
}

double Shape::ExactGaussianShapeOverlapFunction::calcColorOverlap() const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), true);
}

double Shape::ExactGaussianShapeOverlapFunction::calcOverlap(const Math::Vector3DArray& coords) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	if (coords.getSize() < ovlShapeFunc->getProductList()->getNumShapeElements())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), coords, false);
}

double Shape::ExactGaussianShapeOverlapFunction::calcColorOverlap(const Math::Vector3DArray& coords) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	if (coords.getSize() < ovlShapeFunc->getProductList()->getNumShapeElements())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), coords, true);
}

double Shape::ExactGaussianShapeOverlapFunction::calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	if (coords.getSize() < ovlShapeFunc->getProductList()->getNumShapeElements())
		return 0.0;

	return calcOverlapGradient(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), coords, grad);
}

Shape::ExactGaussianShapeOverlapFunction& Shape::ExactGaussianShapeOverlapFunction::operator=(const ExactGaussianShapeOverlapFunction& func)
{
	if (this == &func)
		return *this;
	
	refShapeFunc = func.refShapeFunc;
	ovlShapeFunc = func.ovlShapeFunc;
	colorMatchFunc = func.colorMatchFunc;
	colorFilterFunc = func.colorFilterFunc;

	return *this;
}

bool Shape::ExactGaussianShapeOverlapFunction::checkShapeFuncsNotNull() const
{
	return (refShapeFunc && ovlShapeFunc);
}

double Shape::ExactGaussianShapeOverlapFunction::calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
															 bool color) const
{
	double overlap = 0.0;

	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (color) {
			if (colorFilterFunc) {
				if (!colorFilterFunc(prod1_color))
					continue;

			} else if (prod1_color == 0)
				continue;
		}
		
		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();
		bool prod1_odd = prod1->hasOddOrder();

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (color) {
				if (colorFilterFunc) {
					if (!colorFilterFunc(prod2_color))
						continue;

				} else if (prod2_color == 0)
					continue;
			}

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

double Shape::ExactGaussianShapeOverlapFunction::calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
															const Math::Vector3DArray& coords, bool color) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double overlap = 0.0;
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();

		if (color) {
			if (colorFilterFunc) {
				if (!colorFilterFunc(prod1_color))
					continue;

			} else if (prod1_color == 0)
				continue;
		}

		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		double prod1_fact_exp = prod1_delta * prod1->getProductFactorExponent();

		for (GaussianProductList::ConstProductIterator p_it2 = ref_prod_list->getProductsBegin(), p_end2 = ref_prod_list->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			std::size_t prod2_color = prod2->getColor();

			if (color) {
				if (colorFilterFunc) {
					if (!colorFilterFunc(prod2_color))
						continue;

				} else if (prod2_color == 0)
					continue;
			}

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

double Shape::ExactGaussianShapeOverlapFunction::calcOverlapGradient(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
																	 const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const
{
	grad.assign(ovl_prod_list->getNumShapeElements(), Math::Vector3D());

	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3DArray::StorageType& grad_data = grad.getData();
	Math::Vector3D ovl_prod_ctr;
	Math::Vector3D::Pointer ovl_prod_ctr_data = ovl_prod_ctr.getData();
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();
	double overlap = 0.0;
	
	for (GaussianProductList::ConstProductIterator p_it1 = ovl_prod_list->getProductsBegin(), p_end1 = ovl_prod_list->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		std::size_t prod1_color = prod1->getColor();
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
