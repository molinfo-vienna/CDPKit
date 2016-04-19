/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::PharmacophoreGenerator.
 */

#ifndef CDPL_CHEM_PHARMACOPHOREGENERATOR_HPP
#define CDPL_CHEM_PHARMACOPHOREGENERATOR_HPP

#include <set>
#include <map>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Pharmacophore;
		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief PharmacophoreGenerator.
		 */
		class CDPL_CHEM_API PharmacophoreGenerator 
		{

		  public:
			/**
			 * \brief A generic wrapper class used to store feature generator functions.
			 */
			typedef boost::function2<void, const MolecularGraph&, Pharmacophore&> FeatureFunction;

			/**
			 * \brief Constructs the \c %PharmacophoreGenerator instance.
			 */
			PharmacophoreGenerator() {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~PharmacophoreGenerator() {}

			/**
			 * \brief Enables or disables the generation of features of the specified type.
			 * \param type An identifier for the type of the features to enable/disable.
			 * \param enable \c true if the generation of the given type of features should be enabled, 
			 *               and \c false if disabled.
			 */
			void enableFeature(unsigned int type, bool enable);

			/**
			 * \brief Tells whether the generation of features of the specified type is currently enabled or disabled.
			 * \param type An identifier for the type of the features.
			 * \return \c true if the generation of the given type of features is enabled, 
			 *         and \c false otherwise.
			 */
			bool isFeatureEnabled(unsigned int type) const;

			/**
			 * \brief Disables the generation of all types features.
			 *
			 *  After calling this method, generate() will not produce any new features!
			 */
			void clearEnabledFeatures();

			/**
			 * \brief Specifies a function that gets used for the generation of the specified type of features.
			 * \param type An identifier for the type of features the generator function is specified for.
			 * \param func The wrapped generator function.
			 */
			void setFeatureFunction(unsigned int type, const FeatureFunction& func);

			/**
			 * \brief Removes the feature generation function for the specified type of features.
			 * \param type An identifier for the type of features for which the generator function has to be removed.
			 */
			void removeFeatureFunction(unsigned int type);

			/**
			 * \brief Returns the function that was registered for the generation of the specified type of features.
			 * \param type An identifier for the type of features of interest.
			 * \return The registered generator function for features of type \a type.
			 */
			const FeatureFunction& getFeatureFunction(unsigned int type) const;

			/**
			 * \brief Perceives the enabled pharmacophore features of the molecular graph a\ molgraph 
			 *        and appends them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The pharmacophore where to add the generated output features.
			 */
			void generate(const MolecularGraph& molgraph, Pharmacophore& pharm);

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */
	
			typedef std::set<unsigned int> EnabledFeatureSet;
			typedef std::map<unsigned int, FeatureFunction> FeatureFunctionMap;
		
			FeatureFunctionMap  featureFuncMap;
			EnabledFeatureSet   enabledFeatures;
	
			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_PHARMACOPHOREGENERATOR_HPP
