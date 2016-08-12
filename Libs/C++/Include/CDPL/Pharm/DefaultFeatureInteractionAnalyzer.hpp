/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultFeatureInteractionAnalyzer.hpp 
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
 * \brief Definition of the class CDPL::Pharm::DefaultFeatureInteractionAnalyzer.
 */

#ifndef CDPL_PHARM_DEFAULTFEATUREINTERACTIONANALYZER_HPP
#define CDPL_PHARM_DEFAULTFEATUREINTERACTIONANALYZER_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureInteractionAnalyzer.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_FEATUREINTERACTION_PERCEPTION
		 * @{
		 */

		/**
		 * \brief DefaultFeatureInteractionAnalyzer.
		 */
		class CDPL_PHARM_API DefaultFeatureInteractionAnalyzer : public FeatureInteractionAnalyzer
		{

		  public:
			/**
			 * \brief Constructs the \c %DefaultFeatureInteractionAnalyzer instance.
			 */
			DefaultFeatureInteractionAnalyzer();

			DefaultFeatureInteractionAnalyzer(const Pharmacophore& pharm1, const Pharmacophore& pharm2, FeatureMapping& interactions);

		  private:
			void init();
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_DEFAULTFEATUREINTERACTIONANALYZER_HPP
