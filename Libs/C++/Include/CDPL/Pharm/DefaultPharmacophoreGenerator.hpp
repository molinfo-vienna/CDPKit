/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultPharmacophoreGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::DefaultPharmacophoreGenerator.
 */

#ifndef CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP

#include <vector>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PharmacophoreGenerator.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief DefaultPharmacophoreGenerator.
		 */
		class CDPL_PHARM_API DefaultPharmacophoreGenerator : public PharmacophoreGenerator
		{

		  public:
			/**
			 * \brief Constructs the \c %DefaultPharmacophoreGenerator instance.
			 */
			DefaultPharmacophoreGenerator(bool fuzzy);

			/**
			 * \brief Perceives all pharmacophore features of the molecular graph a\ molgraph
			 *        and adds them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 * \param fuzzy \c true if some uncertainties in the presence or absence of features and interaction
			 *                 directions should be handled less strictly.
			 */
			DefaultPharmacophoreGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool fuzzy);

		  private:
			void init(bool);
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP
