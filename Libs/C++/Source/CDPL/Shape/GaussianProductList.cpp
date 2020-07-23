/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianProductList.cpp 
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

#include "CDPL/Shape/GaussianShape.hpp"

#include "GaussianProductList.hpp"
#include "GaussianProduct.hpp"
#include "Utilities.hpp"


using namespace CDPL;


namespace
{

    const std::size_t MAX_PRODUCT_CACHE_SIZE = 100000;
}


Shape::GaussianProductList::GaussianProductList():
    prodCache(MAX_PRODUCT_CACHE_SIZE), maxOrder(6), distCutoff(0.0), volume(0.0), numElements(0)
{}

Shape::GaussianProductList::GaussianProductList(const GaussianProductList& prod_list):
    prodCache(MAX_PRODUCT_CACHE_SIZE)
{
	copy(prod_list);
}

Shape::GaussianProductList::GaussianProductList(const GaussianShape& shape):
    prodCache(MAX_PRODUCT_CACHE_SIZE), maxOrder(6), distCutoff(0.0)
{
    setup(shape);
}

Shape::GaussianProductList::~GaussianProductList() {}

void Shape::GaussianProductList::setMaxOrder(std::size_t max_order)
{
    maxOrder = max_order;
}

std::size_t Shape::GaussianProductList::getMaxOrder() const
{
    return maxOrder;
}

void Shape::GaussianProductList::setDistanceCutoff(double cutoff)
{
    distCutoff = cutoff;
}

double Shape::GaussianProductList::getDistanceCutoff() const
{
    return distCutoff;
}

Shape::GaussianProductList& Shape::GaussianProductList::operator=(const GaussianProductList& prod_list)
{
	if (this == &prod_list)
		return *this;

	copy(prod_list);
	return *this;
}

void Shape::GaussianProductList::setup(const GaussianShape& shape)
{
	numElements = shape.getNumElements();

    if (elemNbrLists.size() < numElements)
		elemNbrLists.resize(numElements);

    if (elemAdjMatrix.size() < numElements)
		elemAdjMatrix.resize(numElements);

    for (std::size_t i = 0; i < numElements; i++)
		if (elemAdjMatrix[i].size() < numElements)
			elemAdjMatrix[i].resize(numElements);
  
    for (std::size_t i = 0; i < numElements; i++) {
		NeighborList& nbr_list = elemNbrLists[i];
		const GaussianShape::Element& elem1 = shape.getElement(i);
		double elem1_rad_eps = elem1.getRadius() + distCutoff;
		std::size_t elem1_col = elem1.getColor();
	
		nbr_list.clear();
		elemAdjMatrix[i].reset(i);
	
		for (std::size_t j = i + 1; j < numElements; j++) {
			const GaussianShape::Element& elem2 = shape.getElement(j);

			if (elem1_col != elem2.getColor() ||
				std::sqrt(calcSquaredDistance(elem1.getPosition().getData(), elem2.getPosition().getData())) > (elem1_rad_eps + elem2.getRadius())) {
					
				elemAdjMatrix[i].reset(j);
				elemAdjMatrix[j].reset(i);
				continue;
			}
			
			nbr_list.push_back(j);
			elemAdjMatrix[i].set(j);
			elemAdjMatrix[j].set(i);
		}
    }

    products.clear();
    prodCache.putAll();
	
	volume = 0.0;
	
    for (std::size_t i = 0; i < numElements; i++) {
		GaussianProduct* prod = prodCache.getRaw();

		prod->init(shape.getElement(i));
		prod->setIndex(i);

		volume += prod->getVolume();

		products.push_back(prod);
    }

    if (maxOrder == 1)
		return;

	currProduct = prodCache.getRaw();
    currProduct->clearFactors();
    
    for (std::size_t i = 0; i < numElements; i++)
		generateProducts(i);
}

std::size_t Shape::GaussianProductList::getNumProducts() const
{
    return products.size();
}

std::size_t Shape::GaussianProductList::getNumShapeElements() const
{
	return numElements;
}

double Shape::GaussianProductList::getVolume() const
{
	return volume;
}

void Shape::GaussianProductList::generateProducts(std::size_t elem_idx)
{
    currProduct->addFactor(products[elem_idx]);

    std::size_t num_fact = currProduct->getNumFactors();
    
    if (num_fact > 1) {
		GaussianProduct* new_prod = prodCache.getRaw();

		new_prod->copyFactors(*currProduct); 
		new_prod->init();
		new_prod->setIndex(products.size());

		if (new_prod->hasOddOrder())
			volume += new_prod->getVolume();
		else
			volume -= new_prod->getVolume();

		products.push_back(new_prod);
    }

    if (maxOrder == 0 || num_fact < maxOrder) { 
        const NeighborList& elem_nbrs = elemNbrLists[elem_idx];

		for (NeighborList::const_iterator it = elem_nbrs.begin(), end = elem_nbrs.end(); it != end; ++it) {
			std::size_t nbr_idx = *it;

			if (checkNeighborhood(nbr_idx))
				generateProducts(nbr_idx);
		}
    }

    currProduct->removeLastFactor();
}

bool Shape::GaussianProductList::checkNeighborhood(std::size_t elem_idx) const
{
	const Util::BitSet& nbr_set = elemAdjMatrix[elem_idx];
	
    for (GaussianProduct::ConstFactorIterator it = currProduct->getFactorsBegin(), end = currProduct->getFactorsEnd(); it != end; ++it) {
		const GaussianProduct* factor = *it;
		
		if (!nbr_set.test(factor->getIndex()))
			return false;
	}
	
    return true;
}

void Shape::GaussianProductList::copy(const GaussianProductList& prod_list)
{
	maxOrder = prod_list.maxOrder;
	distCutoff = prod_list.distCutoff;
	volume = prod_list.volume;
	numElements = prod_list.numElements;
	
	products.clear();
	products.reserve(prod_list.products.size());
	prodCache.putAll();
	
	for (ProductList::const_iterator it = prod_list.products.begin(), end = prod_list.products.end(); it != end; ++it) {
		const GaussianProduct* prod = *it;
		GaussianProduct* prod_copy = prodCache.getRaw();

		products.push_back(prod_copy);
				
		prod_copy->copyData(*prod);
		prod_copy->clearFactors();
		
		for (GaussianProduct::ConstFactorIterator f_it = prod->getFactorsBegin(), f_end = prod->getFactorsEnd(); f_it != f_end; ++f_it)
			prod_copy->addFactor(products[(*f_it)->getIndex()]);
	}
}
