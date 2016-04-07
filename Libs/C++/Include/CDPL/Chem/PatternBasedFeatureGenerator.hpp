/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::PatternBasedFeatureGenerator.
 */

#ifndef CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP
#define CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP

#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class SubstructureSearch;
		class Pharmacophore;

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief PatternBasedFeatureGenerator.
		 */
		class CDPL_CHEM_API PatternBasedFeatureGenerator 
		{

		  public:
			enum PatternAtomLabelFlag 
			{
			
			    FEATURE_ATOM_FLAG   = 0x01,
			    POS_REF_ATOM_FLAG   = 0x02,
			    GEOM_REF_ATOM1_FLAG = 0x04,
			    GEOM_REF_ATOM2_FLAG = 0x08
			};

			/**
			 * \brief Constructs the \c %PatternBasedFeatureGenerator instance.
			 */
			PatternBasedFeatureGenerator();
			
			/**
			 * \brief Constructs a copy of the \c %PatternBasedFeatureGenerator instance \a gen.
			 * \param gen The \c %PatternBasedFeatureGenerator instance to copy.
			 */
			PatternBasedFeatureGenerator(const PatternBasedFeatureGenerator& gen);

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~PatternBasedFeatureGenerator();

			/**
			 * \brief Appends a new feature include pattern to the current set of patterns.
			 * \param substruct The substructure search pattern of the feature.
			 * \param type The value of the type property of the feature.
			 * \param tol The value of the tolerance property of the feature.
			 * \param geom The value of the geometry property of the feature.
			 * \param length The value of the length property of vector features.
			 */
			void addIncludePattern(const MolecularGraph::SharedPointer& substruct, unsigned int type, 
								   double tol = 1.0, unsigned int geom = FeatureGeometry::SPHERE, double length = 1.0);

			/**
			 * \brief Appends a new feature include pattern to the current set of patterns.
			 * \param substruct The substructure search pattern of the feature.
			 */
			void addExcludePattern(const MolecularGraph::SharedPointer& substruct);
		
			/**
			 * \brief Clears the current set of include patterns.
			 */
			void clearIncludePatterns();
		
			/**
			 * \brief Clears the current set of exclude patterns.
			 */
			void clearExcludePatterns();

			/**
			 * \brief Perceives pharmacophore features according to the specified include/exclude patterns and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param molgraph The molecular graph for which to perceive the features.
			 * \param pharm The output pharmacophore where to add the generated features.
			 */
			void generate(const MolecularGraph& molgraph, Pharmacophore& pharm);

			/**
			 * \brief Replaces the current set include/exclude patterns by the patterns in the
			 *        \c %PatternBasedFeatureGenerator instance \a gen.
			 * \param gen The \c %PatternBasedFeatureGenerator instance providing the new patterns to use.
			 * \return A reference to itself.
			 */
			PatternBasedFeatureGenerator& operator=(const PatternBasedFeatureGenerator& gen);

		  protected:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			typedef std::vector<const Atom*> AtomList;
			typedef boost::shared_ptr<SubstructureSearch> SubstructSearchPtr;

			bool calcVecFeatureOrientation(const AtomList&, const AtomList&, Math::Vector3D&) const;
			bool calcPlaneFeatureOrientation(const AtomList&, Math::Vector3D&, Math::Vector3D&);
			bool calcCentroid(const AtomList&, Math::Vector3D&) const;

			virtual void addNonPatternFeatures(const MolecularGraph& molgraph, Pharmacophore& pharm) {}

			bool isContainedInIncMatchList(const Util::BitSet&) const;
			bool isContainedInExMatchList(const Util::BitSet&) const;

			SubstructureSearch& getSubstructureSearch();

		  private:
			struct FeaturePattern
			{

				FeaturePattern(const MolecularGraph::SharedPointer& substruct, unsigned int type, 
							   double tol, unsigned int geom, double length): 
					substructQry(substruct), featureType(type), featureTol(tol), featureGeom(geom),
					vectorLength(length) {}

				MolecularGraph::SharedPointer substructQry;
				unsigned int                  featureType;
				double                        featureTol;
				unsigned int                  featureGeom;
				double                        vectorLength;
			};

			typedef std::vector<FeaturePattern> FeaturePatternList;
			typedef std::vector<MolecularGraph::SharedPointer> SubstructPatternList;
			typedef std::vector<Util::BitSet*> BitSetList;
			typedef boost::shared_ptr<Util::BitSet> BitSetPtr;
			typedef std::vector<BitSetPtr> AllocBitSetList;
	
			void init(const MolecularGraph& molgraph);

			void getExcludeMatches();

			void addFeature(const AtomBondMapping&, const FeaturePattern&, Pharmacophore&);
		
			void createMatchedAtomMask(const AtomMapping&, Util::BitSet&, bool = false) const;
			bool isContainedInList(const Util::BitSet&, const BitSetList&) const;

			void freeBitSet(Util::BitSet*);
			Util::BitSet* allocBitSet();

			const MolecularGraph* molGraph;
			SubstructSearchPtr    substructSearch;
			FeaturePatternList    includePatterns;
			SubstructPatternList  excludePatterns;
			BitSetList            includeMatches;
			BitSetList            excludeMatches;
			AtomList              posRefAtomList;
			AtomList              geomRefAtom1List;
			AtomList              geomRefAtom2List;
			AllocBitSetList       allocBitSets;
			BitSetList            freeBitSets;
			Math::Matrix<double>  svdU;
			Math::Matrix<double>  svdV;
			Math::Vector<double>  svdW;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP
 
