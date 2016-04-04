/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HydrophobicFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::HydrophobicFeatureGenerator.
 */

#ifndef CDPL_CHEM_HYDROPHOBICFEATUREGENERATOR_HPP
#define CDPL_CHEM_HYDROPHOBICFEATUREGENERATOR_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Feature;

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief HydrophobicFeatureGenerator.
		 * \see [\ref CATA] 
		 */
		class CDPL_CHEM_API HydrophobicFeatureGenerator : public PatternBasedFeatureGenerator
		{

		  public:

			/**
			 * \brief Constructs the \c %HydrophobicFeatureGenerator instance.
			 */
			HydrophobicFeatureGenerator();
		
			/**
			 * \brief Perceives pharmacophore features according to the specified include/exclude patterns and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			HydrophobicFeatureGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * Destructor.
			 */
			~HydrophobicFeatureGenerator();

			void setFeatureType(unsigned int type);

			unsigned int getFeatureType() const;

			void setFeatureTolerance(double tol);

			double getFeatureTolerance() const;

			void setFeatureGeometry(unsigned int geom);

			unsigned int getFeatureGeometry() const;

			void setRingHydrophobicityThreshold(double thresh);

			double getRingHydrophobicityThreshold() const;

			void setChainHydrophobicityThreshold(double thresh);

			double getChainHydrophobicityThreshold() const;

			void setGroupHydrophobicityThreshold(double thresh);

			double getGroupHydrophobicityThreshold() const;

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			typedef std::vector<double> DoubleArray;
			typedef std::vector<Math::Vector3D> CoordsArray;

			void addNonPatternFeatures(const MolecularGraph&, Pharmacophore&);

			void init(const MolecularGraph&);

			void genRingFeatures(Pharmacophore&);
			void genGroupFeatures(Pharmacophore&);
			void genChainFeatures(Pharmacophore&);

			void extractChain(const Atom&);
			void processChain(Pharmacophore&);

			Feature& emitFeature(const AtomList&, Pharmacophore&, const Fragment::SharedPointer&, 
								 bool = true) const;

			bool isHydrophobicRing(const Fragment&);
			bool hasSubstWithMoreThan2Atoms(const Atom&, const Fragment&, bool) const;

			bool calcHydWeightedCentroid(const AtomList&, Math::Vector3D&) const;

			void calcAtomHydrophobicities();
			double calcAccessibleSurfaceFactor(const Atom&);

			void buildAtomMask(const AtomList&, Util::BitSet&) const;
			double calcSummedHydrophobicity(const AtomList& alist) const;

			Fragment::SharedPointer makeFragment(const AtomList&) const;

			bool isChainEndAtom(const Atom&) const;

			const MolecularGraph* molGraph;
			Util::BitSet          procAtomMask;
			Util::BitSet          hAtomMask;
			Util::BitSet          tmpAtomMask;
			unsigned int          featureType;
			double                featureTol;
			unsigned int          featureGeom;
			double                hydThreshRing;  
			double                hydThreshChain; 
			double                hydThreshGroup;
			DoubleArray           atomHydTable;
			DoubleArray           nbrAtomVdWRadii;
			CoordsArray           nbrAtomPositions;
			AtomList              featureAtoms;
			AtomList              chainAtoms;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_HYDROPHOBICFEATUREGENERATOR_HPP
