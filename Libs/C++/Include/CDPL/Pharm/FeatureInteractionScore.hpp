/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionScore.hpp 
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
 * \brief Definition of the class CDPL::Pharm::FeatureInteractionScore.
 */

#ifndef CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP
#define CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief FeatureInteractionScore.
		 */
		class CDPL_PHARM_API FeatureInteractionScore
		{

		  public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %FeatureInteractionScore instances.
			 */
			typedef boost::shared_ptr<FeatureInteractionScore> SharedPointer;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~FeatureInteractionScore() {}
	    
			virtual double operator()(const Feature& ftr1, const Feature& ftr2) const = 0;

			virtual double operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const = 0;

		  protected:
			FeatureInteractionScore() {}
		};
    }
}

#endif // CDPL_PHARM_FEATUREINTERACTIONSCORE_HPP
