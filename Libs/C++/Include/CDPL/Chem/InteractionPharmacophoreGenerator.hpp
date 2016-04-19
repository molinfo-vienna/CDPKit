/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionPharmacophoreGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::InteractionPharmacophoreGenerator.
 */

#ifndef CDPL_CHEM_INTERACTIONPHARMACOPHOREGENERATOR_HPP
#define CDPL_CHEM_INTERACTIONPHARMACOPHOREGENERATOR_HPP

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Pharmacophore;
		class Feature;

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief InteractionPharmacophoreGenerator.
		 */
		class CDPL_CHEM_API InteractionPharmacophoreGenerator 
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store interaction feature generator functions.
			 */
			typedef boost::function3<void, const Feature&, const Feature&, Pharmacophore&> FeatureFunction;

			/**
			 * \brief Constructs the \c %InteractionPharmacophoreGenerator instance.
			 */
			InteractionPharmacophoreGenerator() {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~InteractionPharmacophoreGenerator() {}

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */
	
			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_INTERACTIONPHARMACOPHOREGENERATOR_HPP
