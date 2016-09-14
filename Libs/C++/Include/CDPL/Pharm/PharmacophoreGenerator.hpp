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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreGenerator.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_PHARMACOPHOREGENERATOR_HPP

#include <set>
#include <map>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureGenerator.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace Pharm
    {

		class Pharmacophore;
		class FeatureGenerator;

		/**
		 * \addtogroup CDPL_PHARM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief PharmacophoreGenerator.
		 */
		class CDPL_PHARM_API PharmacophoreGenerator : public FeatureGenerator
		{

		  public:
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
			 * \brief Specifies a Pharm::FeatureGenerator instance that gets used for the generation of the specified type of features.
			 * \param type An identifier for the type of features the generator instance gets used for.
			 * \param ftr_gen The generator instance.
			 */
			void setFeatureGenerator(unsigned int type, FeatureGenerator& ftr_gen);

			/**
			 * \brief Removes the Pharm::FeatureGenerator instance for the specified type of features.
			 * \param type An identifier for the type of features for which the generator instance has to be removed.
			 */
			void removeFeatureGenerator(unsigned int type);

			/**
			 * \brief Returns the Pharm::FeatureGenerator instance that was registered for the generation of the specified type of features.
			 * \param type An identifier for the type of features of interest.
			 * \return The registered generator instance.
			 */
			FeatureGenerator* getFeatureGenerator(unsigned int type) const;

			/**
			 * \brief Perceives the enabled pharmacophore features of the molecular graph a\ molgraph 
			 *        and appends them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The pharmacophore instance where the generated output features get appended.
			 */
			void generate(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * \brief Specifies a function for the retrieval of atom 3D coordinates for feature generation.
			 * \param func The atom 3D coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func);

		  private:
			typedef std::set<unsigned int> EnabledFeatureSet;
			typedef std::map<unsigned int, FeatureGenerator*> FeatureGeneratorMap;
		
			FeatureGeneratorMap featureGeneratorMap;
			EnabledFeatureSet   enabledFeatures;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_PHARMACOPHOREGENERATOR_HPP
