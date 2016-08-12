/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AromaticFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::AromaticFeatureGenerator.
 */

#ifndef CDPL_PHARM_AROMATICFEATUREGENERATOR_HPP
#define CDPL_PHARM_AROMATICFEATUREGENERATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/AromaticSSSRSubset.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		/**
		 * \addtogroup CDPL_PHARM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief AromaticFeatureGenerator.
		 */
		class CDPL_PHARM_API AromaticFeatureGenerator : public PatternBasedFeatureGenerator
		{

		  public:
			static const double       DEF_FEATURE_TOL   = 0.9;
			static const unsigned int DEF_FEATURE_TYPE  = FeatureType::AROMATIC;
			static const unsigned int DEF_FEATURE_GEOM  = FeatureGeometry::PLANE;

			/**
			 * \brief Constructs the \c %AromaticFeatureGenerator instance.
			 */
			AromaticFeatureGenerator();

			/**
			 * \brief Constructs a copy of the \c %AromaticFeatureGenerator instance \a gen.
			 * \param gen The \c %AromaticFeatureGenerator instance to copy.
			 */
			AromaticFeatureGenerator(const AromaticFeatureGenerator& gen);
	
			/**
			 * \brief Perceives aromatic ring features of the molecular graph a\ molgraph and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			AromaticFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * Destructor.
			 */
			~AromaticFeatureGenerator();

			/**
			 * \brief Specifies the value of the feature type property that has to be set on newly generated features.
			 * \param type The value of the feature type property.
			 * \note The default type is specified by the constant AromaticFeatureGenerator::DEF_FEATURE_TYPE.
			 * \see FeatureProperty::TYPE
			 */			
			void setFeatureType(unsigned int type);

			/**
			 * \brief Returns the value of the feature type property that gets set on newly generated features.
			 * \return The used value of the feature type property.
			 * \see FeatureProperty::TYPE
			 */
			unsigned int getFeatureType() const;

			/**
			 * \brief Specifies the value of the feature geometry property that has to be set on newly generated features.
			 * \param geom The value of the feature geometry property.
			 * \note The default type is specified by the constant AromaticFeatureGenerator::DEF_FEATURE_GEOM.
			 * \see FeatureProperty::GEOMETRY
			 */
			void setFeatureGeometry(unsigned int geom);

			/**
			 * \brief Returns the value of the feature geometry property that gets set on newly generated features.
			 * \return The used value of the feature geometry property.
			 * \see FeatureProperty::GEOMETRY
			 */
			unsigned int getFeatureGeometry() const;

			/**
			 * \brief Specifies the value of the feature tolerance property that has to be set on newly generated features.
			 * \param tol The value of the feature tolerance property.
			 * \note The default value is specified by the constant AromaticFeatureGenerator::DEF_FEATURE_TOL.
			 * \see FeatureProperty::TOLERANCE
			 */
			void setFeatureTolerance(double tol);

			/**
			 * \brief Returns the value of the feature tolerance property that gets set on newly generated features.
			 * \return The value of the feature tolerance property.
			 * \see FeatureProperty::TOLERANCE
			 */
			double getFeatureTolerance() const;
			
			/**
			 * \brief Replaces the current set include/exclude patterns and attributes by a copy of the
			 *        \c %AromaticFeatureGenerator instance \a gen.
			 * \param gen The \c %AromaticFeatureGenerator instance to copy.
			 * \return A reference to itself.
			 */
			AromaticFeatureGenerator& operator=(const AromaticFeatureGenerator& gen);

		  private:
			void addNonPatternFeatures(const Chem::MolecularGraph&, Pharmacophore&);

			Chem::AromaticSSSRSubset aromSSSRSubset;
			Util::BitSet             ringAtomMask;
			unsigned int             featureType;
			unsigned int             featureGeom;
			double                   featureTol;
			AtomList                 featureAtoms;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_AROMATICFEATUREGENERATOR_HPP
