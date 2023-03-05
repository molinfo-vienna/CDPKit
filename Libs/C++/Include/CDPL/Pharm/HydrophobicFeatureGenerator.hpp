/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HydrophobicFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::HydrophobicFeatureGenerator.
 */

#ifndef CDPL_PHARM_HYDROPHOBICFEATUREGENERATOR_HPP
#define CDPL_PHARM_HYDROPHOBICFEATUREGENERATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;

		/**
		 * \brief HydrophobicFeatureGenerator.
		 * \see [\ref CATA] 
		 */
		class CDPL_PHARM_API HydrophobicFeatureGenerator : public PatternBasedFeatureGenerator
		{

		  public:
            static const double       DEF_HYD_THRESHOLD_RING;
			static const double       DEF_HYD_THRESHOLD_CHAIN;
			static const double       DEF_HYD_THRESHOLD_GROUP;
		
            static const double       DEF_FEATURE_TOL;
			static const unsigned int DEF_FEATURE_TYPE        = FeatureType::HYDROPHOBIC;
			static const unsigned int DEF_FEATURE_GEOM        = FeatureGeometry::SPHERE;

			/**
			 * \brief Constructs the \c %HydrophobicFeatureGenerator instance.
			 */
			HydrophobicFeatureGenerator();
		
			/**
			 * \brief Constructs a copy of the \c %HydrophobicFeatureGenerator instance \a gen.
			 * \param gen The \c %HydrophobicFeatureGenerator to copy.
			 */
			HydrophobicFeatureGenerator(const HydrophobicFeatureGenerator& gen);
		
			/**
			 * \brief Perceives hydrophobic group features of the molecular graph a\ molgraph and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			HydrophobicFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * Destructor.
			 */
			~HydrophobicFeatureGenerator();

			/**
			 * \brief Specifies the value of the feature type property that has to be set on newly generated features.
			 * \param type The value of the feature type property.
			 * \note The default type is specified by the constant HydrophobicFeatureGenerator::DEF_FEATURE_TYPE.
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
			 * \brief Specifies the value of the feature tolerance property that has to be set on newly generated features.
			 * \param tol The value of the feature tolerance property.
			 * \note The default value is specified by the constant HydrophobicFeatureGenerator::DEF_FEATURE_TOL.
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
			 * \brief Specifies the value of the feature geometry property that has to be set on newly generated features.
			 * \param geom The value of the feature geometry property.
			 * \note The default type is specified by the constant HydrophobicFeatureGenerator::DEF_FEATURE_GEOM.
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
			 * \brief Specifies the minimum summed hydrophobicity of the atoms in small rings that is required for the
			 *        generation of a new feature.
			 * \param thresh The minimum total atom hydrophobicity.
			 * \note The default value is specified by the constant HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_RING.
			 */
			void setRingHydrophobicityThreshold(double thresh);

			/**
			 * \brief Returns the minimum summed hydrophobicity of the atoms in small rings that is required for the
			 *        generation of a new feature.
			 * \return The specified minimum total atom hydrophobicity.
			 */
			double getRingHydrophobicityThreshold() const;

			/**
			 * \brief Specifies the minimum summed hydrophobicity of the atoms in chain fragments that is required for the
			 *        generation of a new feature.
			 * \param thresh The minimum total atom hydrophobicity.
			 * \note The default value is specified by the constant HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_CHAIN.
			 */
			void setChainHydrophobicityThreshold(double thresh);

			/**
			 * \brief Returns the minimum summed hydrophobicity of the atoms in chain fragments that is required for the
			 *        generation of a new feature.
			 * \return The specified minimum total atom hydrophobicity.
			 */
			double getChainHydrophobicityThreshold() const;

			/**
			 * \brief Specifies the minimum summed hydrophobicity of the atoms in group fragments that is required for the
			 *        generation of a new feature.
			 * \param thresh The minimum total atom hydrophobicity.
			 * \note The default value is specified by the constant HydrophobicFeatureGenerator::DEF_HYD_THRESHOLD_GROUP.
			 */
			void setGroupHydrophobicityThreshold(double thresh);

			/**
			 * \brief Returns the minimum summed hydrophobicity of the atoms in group fragments that is required for the
			 *        generation of a new feature.
			 * \return The specified minimum total atom hydrophobicity.
			 */
			double getGroupHydrophobicityThreshold() const;

			/**
			 * \brief Copies the \c %HydrophobicFeatureGenerator instance \a gen.
			 * \param gen The \c %HydrophobicFeatureGenerator to copy.
			 * \return A reference to itself.
			 */
			HydrophobicFeatureGenerator& operator=(const HydrophobicFeatureGenerator& gen);

			FeatureGenerator::SharedPointer clone() const;

		  private:
			void addNonPatternFeatures(const Chem::MolecularGraph&, Pharmacophore&);

			void init(const Chem::MolecularGraph&);

			void genRingFeatures(Pharmacophore&);
			void genGroupFeatures(Pharmacophore&);
			void genChainFeatures(Pharmacophore&);

			void extractChain(const Chem::Atom&);
			void processChain(Pharmacophore&);

			Feature& emitFeature(const AtomList&, Pharmacophore&, const Chem::Fragment::SharedPointer&, 
								 bool = true) const;

			bool isHydrophobicRing(const Chem::Fragment&);
			bool hasSubstWithMoreThan2Atoms(const Chem::Atom&, const Chem::Fragment&, bool) const;

			double calcHydWeightedCentroid(const AtomList&, Math::Vector3D&) const;

			void getAtomHydrophobicities();

			void buildAtomMask(const AtomList&, Util::BitSet&) const;
			double calcSummedHydrophobicity(const AtomList& alist) const;

			Chem::Fragment::SharedPointer makeFragment(const AtomList&) const;

			bool isChainEndAtom(const Chem::Atom&) const;

			const Chem::MolecularGraph*  molGraph;
			Util::BitSet                 procAtomMask;
			Util::BitSet                 hAtomMask;
			Util::BitSet                 tmpAtomMask;
			unsigned int                 featureType;
			double                       featureTol;
			unsigned int                 featureGeom;
			double                       hydThreshRing;  
			double                       hydThreshChain; 
			double                       hydThreshGroup;
			Util::DArray                 atomHydTable;
			AtomList                     featureAtoms;
			AtomList                     chainAtoms;
		};
    }
}

#endif // CDPL_PHARM_HYDROPHOBICFEATUREGENERATOR_HPP
