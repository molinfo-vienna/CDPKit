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

#include <cstddef>
#include <set>
#include <map>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Pharmacophore;
		class MolecularGraph;
		class PatternBasedFeatureGenerator;

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
			typedef boost::function2<void, const MolecularGraph&, Pharmacophore&> FeatureFunction;

			/**
			 * \brief Constructs the \c %PharmacophoreGenerator instance.
			 */
			PharmacophoreGenerator();

			/**
			 * \brief Perceives all enabled pharmacophore features of the molecular graph a\ molgraph
			 *        and adds them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			PharmacophoreGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * \brief Destructor.
			 */
			~PharmacophoreGenerator();

			void enableFeature(unsigned int ftr_type, bool enable);

			bool isFeatureEnabled(unsigned int ftr_type) const;

			void clearEnabledFeatures();

			void setFeatureFunction(unsigned int ftr_type, const FeatureFunction& func);

			const FeatureFunction& getFeatureFunction(unsigned int ftr_type) const;

			/**
			 * \brief Perceives the enabled pharmacophore features of the molecular graph a\ molgraph 
			 *        and adds them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			void generate(const MolecularGraph& molgraph, Pharmacophore& pharm);

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */
	
			typedef std::set<unsigned int> EnabledFeatureSet;
			typedef std::map<unsigned int, FeatureFunction> FeatureFunctionMap;
			typedef boost::shared_ptr<PatternBasedFeatureGenerator>  PatternFeatureGenPtr;
	
			PharmacophoreGenerator(const PharmacophoreGenerator&);

			PharmacophoreGenerator& operator=(const PharmacophoreGenerator&);

			FeatureFunctionMap       featureFuncMap;
			EnabledFeatureSet        enabledFeatures;
			PatternFeatureGenPtr     hbaFeatureGenerator;
			PatternFeatureGenPtr     hbdFeatureGenerator;
			PatternFeatureGenPtr     piFeatureGenerator;
			PatternFeatureGenPtr     niFeatureGenerator;
			PatternFeatureGenPtr     arFeatureGenerator;
			PatternFeatureGenPtr     hydFeatureGenerator;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_PHARMACOPHOREGENERATOR_HPP
 
