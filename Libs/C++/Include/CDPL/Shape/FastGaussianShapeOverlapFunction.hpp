/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FastGaussianShapeOverlapFunction.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Shape::FastGaussianShapeOverlapFunction.
 */

#ifndef CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
#define CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianProductList;
		
		class CDPL_SHAPE_API FastGaussianShapeOverlapFunction : public GaussianShapeOverlapFunction
		{
			
		  public:
			static const double DEF_RADIUS_SCALING_FACTOR;
			
			typedef boost::shared_ptr<FastGaussianShapeOverlapFunction> SharedPointer;

			FastGaussianShapeOverlapFunction();

			FastGaussianShapeOverlapFunction(const FastGaussianShapeOverlapFunction& func);
			
			FastGaussianShapeOverlapFunction(const GaussianShapeFunction& ref_shape_func,
											 const GaussianShapeFunction& ovl_shape_func);

			~FastGaussianShapeOverlapFunction();
		
			void proximityOptimization(bool enable);

			bool proximityOptimization() const;

			void setRadiusScalingFactor(double factor);

			double getRadiusScalingFactor() const;
			
			void fastExpFunction(bool enable);

			bool fastExpFunction() const;

			void setShapeFunction(const GaussianShapeFunction& func, bool is_ref);

			const GaussianShapeFunction* getShapeFunction(bool ref) const;

			void setColorMatchFunction(const ColorMatchFunction& func);

			const ColorMatchFunction& getColorMatchFunction() const;

			void setColorFilterFunction(const ColorFilterFunction& func);

			const ColorFilterFunction& getColorFilterFunction() const;

			double calcSelfOverlap(bool ref) const;
						
			double calcColorSelfOverlap(bool ref) const;
			
			double calcOverlap() const;

			double calcColorOverlap() const;

			double calcOverlap(const Math::Vector3DArray& coords) const;

			double calcColorOverlap(const Math::Vector3DArray& coords) const;

			double calcOverlapGradient(const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;

			FastGaussianShapeOverlapFunction& operator=(const FastGaussianShapeOverlapFunction& func);
			
		  private:
			bool checkShapeFuncsNotNull() const;
		
			double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
							   bool color) const;
			double calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
									bool color) const;
			double calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
									  bool color) const;
			double calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
										bool color) const;
			double calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list, 
											   bool color) const;
			
			double calcOverlap(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
							   const Math::Vector3DArray& coords, bool color) const;
			double calcOverlapExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
									const Math::Vector3DArray& coords, bool color) const;
			double calcOverlapFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
									  const Math::Vector3DArray& coords, bool color) const;
			double calcOverlapProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
										const Math::Vector3DArray& coords, bool color) const;
			double calcOverlapFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
											   const Math::Vector3DArray& coords, bool color) const;
			
			double calcOverlapGradient(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
									   const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
			double calcOverlapGradientExact(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
											const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
			double calcOverlapGradientFastExp(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
											  const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
			double calcOverlapGradientProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
												const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;
			double calcOverlapGradientFastExpProxCheck(const GaussianProductList* ref_prod_list, const GaussianProductList* ovl_prod_list,
													   const Math::Vector3DArray& coords, Math::Vector3DArray& grad) const;

			const GaussianShapeFunction* refShapeFunc;
			const GaussianShapeFunction* ovlShapeFunc;
			ColorMatchFunction           colorMatchFunc;
			ColorFilterFunction          colorFilterFunc;
			bool                         proximityOpt;
			bool                         fastExpFunc;
			double                       radScalingFact;
		};
    }
}

#endif // CDPL_SHAPE_FASTGAUSSIANSHAPEOVERLAPFUNCTION_HPP
