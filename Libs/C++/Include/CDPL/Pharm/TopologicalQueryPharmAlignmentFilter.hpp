/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TopologicalQueryPharmAlignmentFilter.hpp 
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
 * \brief Definition of the class CDPL::Pharm::TopologicalQueryPharmAlignmentFilter.
 */

#ifndef CDPL_PHARM_TOPOLOGICALQUERYPHARMALIGNMENTFILTER_HPP
#define CDPL_PHARM_TOPOLOGICALQUERYPHARMALIGNMENTFILTER_HPP

#include <cstddef>
#include <functional>
#include <vector>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureMapping.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief TopologicalQueryPharmAlignmentFilter.
		 */
		class CDPL_PHARM_API TopologicalQueryPharmAlignmentFilter : public std::unary_function<FeatureMapping, bool>
		{

		  public:
			TopologicalQueryPharmAlignmentFilter(const Pharmacophore& query, std::size_t max_omtd_ftrs);

			/**
			 * \brief Checks if the provided feature mapping fulfills the filters of the pharmacophore query.
			 * \param mapping The feature mapping to evaluate.
			 * \return \c true if the feature mapping fulfills the query filters, and \c false otherwise.
			 */
			bool operator()(const FeatureMapping& mapping) const;

		  private:
			typedef std::vector<const Feature*> FeatureArray;
			typedef std::vector<std::size_t> IndexArray;

			std::size_t  maxOmtdFeatures;
			FeatureArray checkedFeatures;
			IndexArray   ftrGroupLimits;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_TOPOLOGICALQUERYPHARMALIGNMENTFILTER_HPP
