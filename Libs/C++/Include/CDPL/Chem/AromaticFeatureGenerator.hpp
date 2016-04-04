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
 * \brief Definition of the class CDPL::Chem::AromaticFeatureGenerator.
 */

#ifndef CDPL_CHEM_AROMATICFEATUREGENERATOR_HPP
#define CDPL_CHEM_AROMATICFEATUREGENERATOR_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Chem/AromaticSSSRSubset.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief AromaticFeatureGenerator.
		 */
		class CDPL_CHEM_API AromaticFeatureGenerator : public PatternBasedFeatureGenerator
		{

		  public:

			/**
			 * \brief Constructs the \c %AromaticFeatureGenerator instance.
			 */
			AromaticFeatureGenerator();
		
			/**
			 * \brief Perceives pharmacophore features according to the specified include/exclude patterns and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			AromaticFeatureGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * Destructor.
			 */
			~AromaticFeatureGenerator();
			
			void setFeatureType(unsigned int type);

			unsigned int getFeatureType() const;

			void setFeatureGeometry(unsigned int geom);

			unsigned int getFeatureGeometry() const;

			void setFeatureTolerance(double tol);

			double getFeatureTolerance() const;

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			void addNonPatternFeatures(const MolecularGraph&, Pharmacophore&);

			AromaticSSSRSubset aromSSSRSubset;
			Util::BitSet       ringAtomMask;
			unsigned int       featureType;
			unsigned int       featureGeom;
			double             featureTol;
			AtomList           featureAtoms;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_AROMATICFEATUREGENERATOR_HPP
