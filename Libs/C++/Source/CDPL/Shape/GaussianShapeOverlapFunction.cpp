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

#include <cmath>

#include "FastExp/fastexp.h"

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction(): proximityCheck(true), fastExp(false)
{}

Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction(const GaussianShapeOverlapFunction& func):
	refShapeFunc(func.refShapeFunc), ovlShapeFunc(func.ovlShapeFunc), proximityCheck(func.proximityCheck), fastExp(func.fastExp)
{}

Shape::GaussianShapeOverlapFunction::GaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
																  const GaussianShapeFunction& ovl_shape_func):
	refShapeFunc(&ref_shape_func), ovlShapeFunc(&ovl_shape_func), proximityCheck(true), fastExp(false)
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

void Shape::GaussianShapeOverlapFunction::enableProximityOptimization(bool enable)
{
	proximityCheck = enable;
}

bool Shape::GaussianShapeOverlapFunction::proximityOptimizationEnabled() const
{
	return proximityCheck;
}

void Shape::GaussianShapeOverlapFunction::useFastExpFunction(bool use)
{
	fastExp = use;
}

bool Shape::GaussianShapeOverlapFunction::fastExpFunctionUsed() const
{
	return fastExp;
}

double Shape::GaussianShapeOverlapFunction::calcSelfOverlap(bool ref) const
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

double Shape::GaussianShapeOverlapFunction::calcOverlap() const
{
	if (!checkShapeFuncsNotNull())
		return 0.0;
	
	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), true);
}

double Shape::GaussianShapeOverlapFunction::calcOverlap(const Math::Matrix4D& xform)
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	prepareOverlapCalc(xform);

	return calcOverlap(refShapeFunc->getProductList(), ovlShapeFunc->getProductList(), false);
}

double Shape::GaussianShapeOverlapFunction::calcOverlapGradient(const Math::Matrix4D& xform, Math::Vector3DArray& grad)
{
	if (!checkShapeFuncsNotNull())
		return 0.0;

	prepareGradientCalc(xform, grad);

	return calcOverlapGradient(grad);
}

Shape::GaussianShapeOverlapFunction& Shape::GaussianShapeOverlapFunction::operator=(const GaussianShapeOverlapFunction& func)
{
	if (this == &func)
		return *this;
	
	refShapeFunc = func.refShapeFunc;
	ovlShapeFunc = func.ovlShapeFunc;
	proximityCheck = func.proximityCheck;
	fastExp = func.fastExp;
	
	return *this;
}

bool Shape::GaussianShapeOverlapFunction::checkShapeFuncsNotNull() const
{
	return (refShapeFunc && ovlShapeFunc);
}

void Shape::GaussianShapeOverlapFunction::prepareOverlapCalc(const Math::Matrix4D& xform)
{
	const GaussianProductList* prod_list = ovlShapeFunc->getProductList();
	std::size_t num_elems = (proximityCheck ? prod_list->getNumProducts() : prod_list->getNumShapeElements());
	Math::Matrix4D::ConstArrayPointer xform_data = xform.getData();
	
	if (prodCenters.size() < num_elems)
		prodCenters.resize(num_elems);

	for (std::size_t i = 0; i < num_elems; i++)
		transform(prodCenters[i].getData(), xform_data, prod_list->getProduct(i)->getCenter().getData());
}

void Shape::GaussianShapeOverlapFunction::prepareGradientCalc(const Math::Matrix4D& xform, Math::Vector3DArray& grad)
{
	const GaussianProductList* prod_list = ovlShapeFunc->getProductList();
	Math::Matrix4D::ConstArrayPointer xform_data = xform.getData();
	std::size_t num_elems = prod_list->getNumShapeElements();
	std::size_t num_prods = prod_list->getNumProducts();

	grad.assign(num_elems, Math::Vector3D());
	
	if (prodCenters.size() < num_prods)
		prodCenters.resize(num_prods);

	for (std::size_t i = 0; i < num_prods; i++)
		transform(prodCenters[i].getData(), xform_data, prod_list->getProduct(i)->getCenter().getData());
}

double Shape::GaussianShapeOverlapFunction::calcOverlap(const GaussianProductList* prod_list1, const GaussianProductList* prod_list2, bool orig_centers) const
{
	double overlap = 0.0;
		  
	for (GaussianProductList::ConstProductIterator p_it1 = prod_list1->getProductsBegin(), p_end1 = prod_list1->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius();
		
		for (GaussianProductList::ConstProductIterator p_it2 = prod_list2->getProductsBegin(), p_end2 = prod_list2->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;

			if (proximityCheck) {
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, (orig_centers ? prod2->getCenter().getData() : prodCenters[prod2->getIndex()].getData()));
				double max_dist = prod1_radius + prod2->getRadius();

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
			}
				
			double prod_fact_exp = 0.0;

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() *
						calcSquaredDistance(ctr1_data,
											(orig_centers ? (*f_it2)->getCenter() : prodCenters[(*f_it2)->getIndex()]).getData());
			}

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;
		
			prod_fact_exp += prod1_delta * prod1->getProductFactorExponent() + prod2_delta * prod2->getProductFactorExponent();

			overlap += (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * (fastExp ? fastexp::exp(-prod_fact_exp / delta) : std::exp(-prod_fact_exp / delta));
		}
	}

	return overlap;
}

double Shape::GaussianShapeOverlapFunction::calcOverlapGradient(Math::Vector3DArray& grad) const
{
	const GaussianProductList* prod_list1 = refShapeFunc->getProductList();
	const GaussianProductList* prod_list2 = ovlShapeFunc->getProductList();
	
	double overlap = 0.0;
	Math::Vector3D inters_prod_ctr;
	Math::Vector3D::Pointer inters_prod_ctr_data = inters_prod_ctr.getData();

	for (GaussianProductList::ConstProductIterator p_it1 = prod_list1->getProductsBegin(), p_end1 = prod_list1->getProductsEnd(); p_it1 != p_end1; ++p_it1) {
		const GaussianProduct* prod1 = *p_it1;
		double prod1_delta = prod1->getDelta();
		double prod1_weight = prod1->getWeightFactor();
		bool prod1_odd = prod1->hasOddOrder();
		Math::Vector3D::ConstPointer prod1_ctr = prod1->getCenter().getData();
		double prod1_radius = prod1->getRadius();

		for (GaussianProductList::ConstProductIterator p_it2 = prod_list2->getProductsBegin(), p_end2 = prod_list2->getProductsEnd(); p_it2 != p_end2; ++p_it2) {
			const GaussianProduct* prod2 = *p_it2;
			Math::Vector3D::ConstPointer prod2_ctr = prodCenters[prod2->getIndex()].getData();
			
			if (proximityCheck) {
				double sqrd_prod_ctr_dist = calcSquaredDistance(prod1_ctr, prod2_ctr);
				double max_dist = prod1_radius + prod2->getRadius();

				if (sqrd_prod_ctr_dist > (max_dist * max_dist))
					continue;
			}
				
			double prod_fact_exp = 0.0;

			for (GaussianProduct::ConstFactorIterator f_it1 = prod1->getFactorsBegin(), f_end1 = prod1->getFactorsEnd(); f_it1 != f_end1; ++f_it1) {
				const GaussianProduct* prod1_fact = *f_it1;
				Math::Vector3D::ConstPointer ctr1_data = prod1_fact->getCenter().getData();
				double fact1_delta = prod1_fact->getDelta();
				
				for (GaussianProduct::ConstFactorIterator f_it2 = prod2->getFactorsBegin(), f_end2 = prod2->getFactorsEnd(); f_it2 != f_end2; ++f_it2) 
					prod_fact_exp += fact1_delta * (*f_it2)->getDelta() *
						calcSquaredDistance(ctr1_data, prodCenters[(*f_it2)->getIndex()].getData());
			}

			double prod2_delta = prod2->getDelta();
			double delta = prod1_delta + prod2_delta;
			double vol_factor = M_PI / delta;

			prod_fact_exp += prod1_delta * prod1->getProductFactorExponent() + prod2_delta * prod2->getProductFactorExponent();
			
			double overlap_contrib = (prod1_odd ^ prod2->hasOddOrder() ? -prod1_weight : prod1_weight) * prod2->getWeightFactor() * vol_factor *
				std::sqrt(vol_factor) * (fastExp ? fastexp::exp(-prod_fact_exp / delta) : std::exp(-prod_fact_exp / delta));

			overlap += overlap_contrib;

			inters_prod_ctr_data[0] = (prod1_ctr[0] * prod1_delta + prod2_ctr[0] * prod2_delta) / delta;
			inters_prod_ctr_data[1] = (prod1_ctr[1] * prod1_delta + prod2_ctr[1] * prod2_delta) / delta;
			inters_prod_ctr_data[2] = (prod1_ctr[2] * prod1_delta + prod2_ctr[2] * prod2_delta) / delta;
			
			for (GaussianProduct::ConstFactorIterator f_it = prod2->getFactorsBegin(), f_end = prod2->getFactorsEnd(); f_it != f_end; ++f_it) {
				const GaussianProduct* prod_fact = *f_it;
				std::size_t fact_idx = prod_fact->getIndex();
				Math::Vector3D::ConstPointer fact_ctr = prodCenters[fact_idx].getData();
				Math::Vector3D::Pointer fact_grad = grad.getData()[fact_idx].getData();
				double mul_factor = -prod_fact->getDelta() * 2.0 * overlap_contrib;
			
				fact_grad[0] += mul_factor * (fact_ctr[0] - inters_prod_ctr_data[0]);
				fact_grad[1] += mul_factor * (fact_ctr[1] - inters_prod_ctr_data[1]);
				fact_grad[2] += mul_factor * (fact_ctr[2] - inters_prod_ctr_data[2]);
			}
		}
	}
	
	return overlap;
}
