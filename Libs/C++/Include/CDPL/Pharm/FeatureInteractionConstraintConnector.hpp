/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionConstraintConnector.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::FeatureInteractionConstraintConnector.
 */

#ifndef CDPL_PHARM_FEATUREINTERACTIONCONSTRAINTCONNECTOR_HPP
#define CDPL_PHARM_FEATUREINTERACTIONCONSTRAINTCONNECTOR_HPP

#include <functional>

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class Feature;

		/**
		 * \addtogroup CDPL_PHARM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief FeatureInteractionConstraintConnector.
		 */
		class CDPL_PHARM_API FeatureInteractionConstraintConnector : public std::binary_function<Feature, Feature, bool>
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store feature interaction constraint test functions.
			 */
			typedef boost::function2<bool, const Feature&, const Feature&> ConstraintFunction;

			/**
			 * \brief Constructs a \c %FeatureInteractionConstraintConnector that serves as a logical connective for the two specified constraint functions.
			 * \param and_expr \c true for a logical conjuction of the function results, and \c false for a disjunction.
			 * \param func1 The first interaction constraint function.
			 * \param func2 The second interaction constraint function.
			 */
			FeatureInteractionConstraintConnector(bool and_expr, const ConstraintFunction& func1, const ConstraintFunction& func2): 
				andExpr(and_expr), function1(func1), function2(func2) {}

			bool operator()(const Feature& ftr1, const Feature& ftr2) const;

		  private:
			bool               andExpr;
			ConstraintFunction function1;
			ConstraintFunction function2;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_FEATUREINTERACTIONCONSTRAINTCONNECTOR_HPP
