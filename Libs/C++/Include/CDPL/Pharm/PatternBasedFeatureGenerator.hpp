/* 
 * PatternBasedFeatureGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of class CDPL::Pharm::PatternBasedFeatureGenerator.
 */

#ifndef CDPL_PHARM_PATTERNBASEDFEATUREGENERATOR_HPP
#define CDPL_PHARM_PATTERNBASEDFEATUREGENERATOR_HPP

#include <vector>
#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/FeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Pharmacophore;

        /**
         * \brief PatternBasedFeatureGenerator.
         */
        class CDPL_PHARM_API PatternBasedFeatureGenerator : public FeatureGenerator
        {

          public:
            typedef std::shared_ptr<PatternBasedFeatureGenerator> SharedPointer;

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
             * \brief Appends a new feature substructure include pattern to the current set of patterns.
             * \param molgraph The molecular graph of the feature substructure search pattern.
             * \param type The value of the type property of the feature.
             * \param tol The value of the tolerance property of the feature.
             * \param geom The value of the geometry property of the feature.
             * \param length The value of the length property of vector features.
             */
            void addIncludePattern(const Chem::MolecularGraph::SharedPointer& molgraph, unsigned int type,
                                   double tol, unsigned int geom, double length = 1.0);

            /**
             * \brief Appends a new feature substructure exclude pattern to the current set of patterns.
             * \param molgraph The molecular graph of the feature substructure exclude pattern.
             */
            void addExcludePattern(const Chem::MolecularGraph::SharedPointer& molgraph);

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
            void generate(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm);

            /**
             * \brief Replaces the current set include/exclude patterns by the patterns in the
             *        \c %PatternBasedFeatureGenerator instance \a gen.
             * \param gen The \c %PatternBasedFeatureGenerator instance providing the new patterns to use.
             * \return A reference to itself.
             */
            PatternBasedFeatureGenerator& operator=(const PatternBasedFeatureGenerator& gen);

            FeatureGenerator::SharedPointer clone() const;

          protected:
            typedef std::vector<const Chem::Atom*> AtomList;

            double calcVecFeatureOrientation(const AtomList&, const AtomList&, Math::Vector3D&) const;
            bool calcPlaneFeatureOrientation(const AtomList&, Math::Vector3D&, Math::Vector3D&);
            bool calcCentroid(const AtomList&, Math::Vector3D&) const;

            virtual void addNonPatternFeatures(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm) {}

            bool isContainedInIncMatchList(const Util::BitSet&) const;
            bool isContainedInExMatchList(const Util::BitSet&) const;

          private:
            struct IncludePattern
            {

                IncludePattern(const Chem::MolecularGraph::SharedPointer& molgraph, unsigned int type,
                               double tol, unsigned int geom, double length):
                    molGraph(molgraph), subSearch(new Chem::SubstructureSearch(*molgraph)), featureType(type),
                    featureTol(tol), featureGeom(geom), vectorLength(length)
                {}

                Chem::MolecularGraph::SharedPointer     molGraph;
                Chem::SubstructureSearch::SharedPointer subSearch;
                unsigned int                            featureType;
                double                                  featureTol;
                unsigned int                            featureGeom;
                double                                  vectorLength;
            };

            struct ExcludePattern
            {

                ExcludePattern(const Chem::MolecularGraph::SharedPointer& molgraph):
                    molGraph(molgraph), subSearch(new Chem::SubstructureSearch(*molgraph))
                {}

                Chem::MolecularGraph::SharedPointer     molGraph;
                Chem::SubstructureSearch::SharedPointer subSearch;
            };

            typedef std::vector<IncludePattern>     IncludePatternList;
            typedef std::vector<ExcludePattern>     ExcludePatternList;
            typedef Util::ObjectStack<Util::BitSet> BitSetCache;
            typedef std::vector<Util::BitSet*>      BitSetList;

            void init(const Chem::MolecularGraph& molgraph);

            void getExcludeMatches();

            void addFeature(const Chem::AtomBondMapping&, const IncludePattern&, Pharmacophore&);

            bool createMatchedAtomMask(const Chem::AtomMapping&, Util::BitSet&, bool, bool = true) const;
            bool isContainedInList(const Util::BitSet&, const BitSetList&) const;

            const Chem::MolecularGraph* molGraph;
            IncludePatternList          includePatterns;
            ExcludePatternList          excludePatterns;
            BitSetList                  includeMatches;
            BitSetList                  excludeMatches;
            AtomList                    posRefAtomList;
            AtomList                    geomRefAtom1List;
            AtomList                    geomRefAtom2List;
            Math::Matrix<double>        svdU;
            Math::Matrix3D              svdV;
            Math::Vector3D              svdW;
            BitSetCache                 bitSetCache;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PATTERNBASEDFEATUREGENERATOR_HPP
