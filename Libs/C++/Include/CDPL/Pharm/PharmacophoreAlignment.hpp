/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreAlignment.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreAlignment.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP
#define CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/GeometricalEntityAlignment.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;
		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief PharmacophoreAlignment.
		 */
		class CDPL_PHARM_API PharmacophoreAlignment : public Chem::GeometricalEntityAlignment<Feature>
		{

		  public:
			/**
			 * \brief Constructs the \c %PharmacophoreAlignment instance.
			 * \param query_mode If \c true, the features of the first set are interpreted as a query pharmacophore
			 *                   and the features of the second have to match this query after alignment. If \c false,
			 *                   there is no distinction between the features of the first and second set in various
			 *                   performed intermediate checks.
			 */
			PharmacophoreAlignment(bool query_mode);

			/**
			 * \brief Adds the features of the pharmacophore \a pharm to the specified alignment feature set.
			 * \param pharm The pharmacophore containing features to add.
			 * \param first_set If \c true, the features are added to the first feature set, if \c false to the second one.
			 */
			void addPharmacophore(const Pharmacophore& pharm, bool first_set);
	  
		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP
