/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianProduct.hpp 
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
 * \brief Definition of the class CDPL::Shape::GaussianProduct.
 */

#ifndef CDPL_SHAPE_GAUSSIANPRODUCT_HPP
#define CDPL_SHAPE_GAUSSIANPRODUCT_HPP

#include <cstddef>
#include <vector>
#include <cmath>

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/GaussianShape.hpp"

#include "Utilities.hpp"


namespace CDPL 
{

    namespace Shape
    {

		class GaussianProduct
		{

			typedef std::vector<const GaussianProduct*> FactorList;
				
		  public:
			typedef boost::shared_ptr<GaussianProduct> SharedPointer;
			typedef FactorList::const_iterator ConstFactorIterator;

			GaussianProduct();
	
			void init(const GaussianShape::Element& elem);

			void init();

			void copyData(const GaussianProduct& prod);

			void copyFactors(const GaussianProduct& prod);
			
			void setIndex(std::size_t idx);
						
			std::size_t getIndex() const;

			void setColor(std::size_t color);
						
			std::size_t getColor() const;

			bool hasOddOrder() const;
			
			bool hasFactors() const;
			
			void clearFactors();

			void addFactor(const GaussianProduct* factor);

			void removeLastFactor();
			
			ConstFactorIterator getFactorsBegin() const;

			ConstFactorIterator getFactorsEnd() const;

			std::size_t getNumFactors() const;

			double getRadius() const;

			double getKappa() const;
			
			double getDelta() const;

			double getWeightFactor() const;
			
			const Math::Vector3D& getCenter() const;

			Math::Vector3D& getCenter();

			double getProductFactorExponent() const;

			double getProductFactor() const;

			double getVolume() const;

		  private:
			std::size_t    index;
			std::size_t    color;
			Math::Vector3D center;
			double         radius;
			double         kappa;
			double         prodFactor;
			double         prodFactorExp;
			double         delta;
			double         weightFactor;
			double         volumeFactor;
			double         volume;
			bool           oddOrder;
			FactorList     factors;
		};
    }
}


// Implementation

inline CDPL::Shape::GaussianProduct::GaussianProduct():
	index(0), color(0), center(), radius(0.0), kappa(0.0), prodFactor(0.0), prodFactorExp(0.0), delta(0.0),
	weightFactor(0.0), volumeFactor(0.0), volume(0.0), oddOrder(false)
{}

inline void CDPL::Shape::GaussianProduct::init(const GaussianShape::Element& elem)
{
	factors.clear();
	factors.push_back(this);
	
	center.assign(elem.getPosition());
	color = elem.getColor();
	prodFactorExp = 0.0;
	prodFactor = 1.0;
	weightFactor = elem.getHardness();

	double lambda = 4.0 * M_PI / (3.0 * weightFactor);

	kappa = M_PI / std::pow(lambda, 2.0 / 3.0);
	radius = elem.getRadius();
	delta = kappa / (radius * radius);
	volumeFactor = M_PI / delta;
	volumeFactor *= std::sqrt(volumeFactor);
	volume = weightFactor * volumeFactor;
	oddOrder = true;
}

inline void CDPL::Shape::GaussianProduct::init()
{
	weightFactor = 1.0;
	prodFactorExp = 0.0;
	delta = 0.0;
	kappa = 0.0;
	//radius = 0.0;
	color = (factors.empty() ? std::size_t(0) : factors.front()->color);
	
	Math::Vector3D::Pointer ctr_data = center.getData();

	center.clear();
	
	for (FactorList::const_iterator it1 = factors.begin(), end = factors.end(); it1 != end; ) {
		const GaussianProduct* factor1 = *it1;
		double fact1_delta = factor1->delta;
		
		delta += fact1_delta;
		weightFactor *= factor1->weightFactor;

		Math::Vector3D::ConstPointer fact1_ctr_data = factor1->center.getData();

		ctr_data[0] += fact1_delta * fact1_ctr_data[0];
		ctr_data[1] += fact1_delta * fact1_ctr_data[1];
		ctr_data[2] += fact1_delta * fact1_ctr_data[2];

		++it1;
		
		for (FactorList::const_iterator it2 = it1; it2 != end; ++it2)
			prodFactorExp += calcSquaredDistance((*it2)->center.getData(), fact1_ctr_data) * fact1_delta * (*it2)->delta;
	}

	center /= delta;
	prodFactorExp /= delta;
	prodFactor = std::exp(-prodFactorExp);
	volumeFactor = M_PI / delta;
	volumeFactor *= std::sqrt(volumeFactor);
	volume = weightFactor * prodFactor * volumeFactor;
	radius = std::pow(3.0 * volume / (4.0 * M_PI), 1.0 / 3.0);
	oddOrder = (factors.size() % 2);
}

inline void CDPL::Shape::GaussianProduct::copyData(const GaussianProduct& prod)
{
	index = prod.index;
	color = prod.color;
	center = prod.center;
	radius = prod.radius;
	kappa = prod.kappa;
	prodFactor = prod.prodFactor;
	prodFactorExp = prod.prodFactorExp;
	delta = prod.delta;
	weightFactor = prod.weightFactor;
	volumeFactor = prod.volumeFactor;
	volume = prod.volume;
	oddOrder = prod.oddOrder;
}

inline void CDPL::Shape::GaussianProduct::copyFactors(const GaussianProduct& prod)
{
	factors = prod.factors;
}
		
inline void CDPL::Shape::GaussianProduct::setIndex(std::size_t idx)
{
	index = idx;
}

inline std::size_t CDPL::Shape::GaussianProduct::getIndex() const
{
	return index;
}

inline void CDPL::Shape::GaussianProduct::setColor(std::size_t color)
{
	this->color = color;
}

inline std::size_t CDPL::Shape::GaussianProduct::getColor() const
{
	return color;
}

inline bool CDPL::Shape::GaussianProduct::hasOddOrder() const
{
	return oddOrder;
}

inline bool CDPL::Shape::GaussianProduct::hasFactors() const
{
	return !factors.empty();
}

inline void CDPL::Shape::GaussianProduct::clearFactors()
{
	factors.clear();
}
			
inline void CDPL::Shape::GaussianProduct::addFactor(const GaussianProduct* factor)
{
	factors.push_back(factor);
}

inline void CDPL::Shape::GaussianProduct::removeLastFactor()
{
	if (factors.empty())
		return;

	factors.pop_back();
}

inline CDPL::Shape::GaussianProduct::ConstFactorIterator CDPL::Shape::GaussianProduct::getFactorsBegin() const
{
	return factors.begin();
}

inline CDPL::Shape::GaussianProduct::ConstFactorIterator CDPL::Shape::GaussianProduct::getFactorsEnd() const
{
	return factors.end();
}

inline std::size_t CDPL::Shape::GaussianProduct::getNumFactors() const
{
	return factors.size();
}

inline double CDPL::Shape::GaussianProduct::getRadius() const
{
	return radius;
}

inline double CDPL::Shape::GaussianProduct::getKappa() const
{
	return kappa;
}

inline double CDPL::Shape::GaussianProduct::getDelta() const
{
	return delta;
}

inline double CDPL::Shape::GaussianProduct::getWeightFactor() const
{
	return weightFactor;
}

inline const CDPL::Math::Vector3D& CDPL::Shape::GaussianProduct::getCenter() const
{
	return center;
}

inline CDPL::Math::Vector3D& CDPL::Shape::GaussianProduct::getCenter()
{
	return center;
}

inline double CDPL::Shape::GaussianProduct::getProductFactor() const
{
	return prodFactor;
}

inline double CDPL::Shape::GaussianProduct::getProductFactorExponent() const
{
	return prodFactorExp;
}

inline double CDPL::Shape::GaussianProduct::getVolume() const
{
	return volume;
}

#endif // CDPL_SHAPE_GAUSSIANPRODUCT_HPP
