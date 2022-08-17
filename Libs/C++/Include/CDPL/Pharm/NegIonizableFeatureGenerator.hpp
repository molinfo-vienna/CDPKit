/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NegIonizableFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::NegIonizableFeatureGenerator.
 */

#ifndef CDPL_PHARM_NEGIONIZABLEFEATUREGENERATOR_HPP
#define CDPL_PHARM_NEGIONIZABLEFEATUREGENERATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \brief NegIonizableFeatureGenerator.
		 */
		class CDPL_PHARM_API NegIonizableFeatureGenerator : public PatternBasedFeatureGenerator
		{

		  public:
			/**
			 * \brief Constructs the \c %NegIonizableFeatureGenerator instance.
			 * \param chgd_groups_only \c true if features shall be generated only for charged groups.
			 */
			NegIonizableFeatureGenerator(bool chgd_groups_only);
				
			/**
			 * \brief Perceives the negative ionizable group features of the molecular graph a\ molgraph and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 * \param chgd_groups_only \c true if features shall be generated only for charged groups.
			 */
			NegIonizableFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool chgd_groups_only);
	    
		  private:
			void init(bool chgd_groups_only);
		};
    }
}

#endif // CDPL_PHARM_NEGIONIZABLEFEATUREGENERATOR_HPP
