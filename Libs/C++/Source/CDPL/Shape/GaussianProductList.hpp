/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianProductList.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Shape::GaussianProductList.
 */

#ifndef CDPL_SHAPE_GAUSSIANPRODUCTLIST_HPP
#define CDPL_SHAPE_GAUSSIANPRODUCTLIST_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianShape;
		class GaussianProduct;
		
		class GaussianProductList
		{

			typedef std::vector<GaussianProduct*> ProductList;
				
		  public:
			typedef ProductList::const_iterator ConstProductIterator;

			GaussianProductList();

			GaussianProductList(const GaussianProductList& prod_list);

			GaussianProductList(const GaussianShape& shape);

			~GaussianProductList();
			
			void setMaxOrder(std::size_t max_order);

			std::size_t getMaxOrder() const;

			void setDistanceCutoff(double cutoff);

			double getDistanceCutoff() const;

			GaussianProductList& operator=(const GaussianProductList& prod_list);
			
			void setup(const GaussianShape& shape);

			const GaussianProduct* getProduct(std::size_t idx) const;

			ConstProductIterator getProductsBegin() const;

			ConstProductIterator getProductsEnd() const;

			std::size_t getNumProducts() const;

			std::size_t getNumShapeElements() const;
			
			double getVolume() const;
			
		  private:
			void generateProducts(std::size_t elem_idx);

			bool checkNeighborhood(std::size_t elem_idx) const;

			void copy(const GaussianProductList& prod_list);
			
			typedef std::vector<std::size_t> NeighborList;
			typedef std::vector<NeighborList> NeighborListArray;
			typedef std::vector<Util::BitSet> AdjacencyMatrix;
			typedef Util::ObjectStack<GaussianProduct> GaussianProductCache;

			GaussianProductCache prodCache;
			NeighborListArray    elemNbrLists;
			AdjacencyMatrix      elemAdjMatrix;
			std::size_t          maxOrder;
			double               distCutoff;
			GaussianProduct*     currProduct;
			ProductList          products;
			double               volume;
			std::size_t          numElements;
		};
    }
	
	inline const Shape::GaussianProduct* Shape::GaussianProductList::getProduct(std::size_t idx) const
	{
		return products[idx];
	}
	
	inline Shape::GaussianProductList::ConstProductIterator Shape::GaussianProductList::getProductsBegin() const
	{
		return products.begin();
	}

	inline Shape::GaussianProductList::ConstProductIterator Shape::GaussianProductList::getProductsEnd() const
	{
		return products.end();
	}
}

#endif // CDPL_SHAPE_GAUSSIANPRODUCTLIST_HPP
