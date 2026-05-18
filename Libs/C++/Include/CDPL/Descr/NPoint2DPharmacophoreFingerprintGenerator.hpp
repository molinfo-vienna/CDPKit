/* 
 * NPoint2DPharmacophoreFingerprintGenerator.hpp 
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
 * \brief Definition of class CDPL::Descr::NPoint2DPharmacophoreFingerprintGenerator.
 */

#ifndef CDPL_DESCR_NPOINT2DPHARMACOPHOREFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_NPOINT2DPHARMACOPHOREFINGERPRINTGENERATOR_HPP

#include <memory>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Descr
    {

        /**
         * \brief N-point pharmacophore fingerprint generator that uses topological feature distances.
         *
         * The fingerprint encodes the binned topological distances between all combinations of
         * feature tuples generated from a molecular graph. The choice of how feature-pair topological
         * distance is computed (min, max or average over the topological distances between the
         * underlying atoms) is configurable via FeatureDistanceType.
         *
         * \since 1.2
         */
        class CDPL_DESCR_API NPoint2DPharmacophoreFingerprintGenerator : public NPointPharmacophoreFingerprintGenerator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %NPoint2DPharmacophoreFingerprintGenerator instances.
             */
            typedef std::shared_ptr<NPoint2DPharmacophoreFingerprintGenerator> SharedPointer;

            /**
             * \brief Specifies how the topological distance between two features is derived
             *        from the topological distances between their underlying atoms.
             */
            enum FeatureDistanceType
            {

                /**
                 * \brief Use the minimum topological distance between any two underlying atoms.
                 */
                MIN_PATH_LENGTH,
                /**
                 * \brief Use the maximum topological distance between any two underlying atoms.
                 */
                MAX_PATH_LENGTH,
                /**
                 * \brief Use the average topological distance between all pairs of underlying atoms.
                 */
                AVG_PATH_LENGTH
            };

            /**
             * \brief Default distance bin size.
             * \since 1.3
             */
            static constexpr double DEF_BIN_SIZE = 2.0;

            /**
             * \brief Default feature distance type.
             */
            static constexpr FeatureDistanceType DEF_FEATURE_DISTANCE_TYPE = MIN_PATH_LENGTH;

            /**
             * \brief Constructs the \c %NPoint2DPharmacophoreFingerprintGenerator instance.
             */
            NPoint2DPharmacophoreFingerprintGenerator();

            /**
             * \brief Copy constructor.
             */
            NPoint2DPharmacophoreFingerprintGenerator(const NPoint2DPharmacophoreFingerprintGenerator& gen) = default;

            /**
             * \brief Constructs the \c %NPoint2DPharmacophoreFingerprintGenerator instance and generates the fingerprint of \a molgraph.
             * \param molgraph The molecular graph.
             * \param fp The output bitset.
             */
            NPoint2DPharmacophoreFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            /**
             * \brief Sets the type of feature-pair topological distance to use.
             * \param dist_type The feature distance type.
             */
            void setFeatureDistanceType(FeatureDistanceType dist_type);

            /**
             * \brief Returns the currently configured feature distance type.
             * \return The configured feature distance type.
             */
            FeatureDistanceType getFeatureDistanceType() const;

            /**
             * \brief Generates the fingerprint of the molecular graph \a molgraph.
             * \param molgraph The molecular graph.
             * \param fp The output bitset.
             */
            void generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);
            
          private:
            double getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const;

            FeatureDistanceType         ftrDistType;
            Math::ULMatrix              topDistMatrix;
            const Math::ULMatrix*       activeTopDistMatrix;
            const Chem::MolecularGraph* molGraph;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_NPOINT2DPHARMACOPHOREFINGERPRINTGENERATOR_HPP
