/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BindingAffinityCalculator.hpp 
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
 * \brief Definition of the class CDPL::GRAIL::BindingAffinityCalculator.
 */

#ifndef CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP
#define CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP

#include <memory>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace GRAIL
    {

		/**
		 * \brief BindingAffinityCalculator.
		 */
		class CDPL_GRAIL_API BindingAffinityCalculator
		{

		  public:
			typedef std::shared_ptr<BindingAffinityCalculator> SharedPointer;

			enum AffinityMeasure
		    {

			  PKD,
			  PKI,
			  PKD_PKI
			};
	    
			BindingAffinityCalculator();

			BindingAffinityCalculator(AffinityMeasure measure);

			void setAffinityMeasure(AffinityMeasure measure);

			AffinityMeasure getAffinityMeasure() const;
	    
			double operator()(const Math::DVector& grail_descr) const;

		  private:
			AffinityMeasure affMeasure;
		};
    }
}

#endif // CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP
