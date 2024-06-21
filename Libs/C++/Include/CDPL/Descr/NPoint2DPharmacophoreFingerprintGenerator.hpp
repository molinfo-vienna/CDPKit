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
 * \brief Definition of the class CDPL::Descr::NPoint2DPharmacophoreFingerprintGenerator.
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
         * \brief NPoint2DPharmacophoreFingerprintGenerator.
         * \since 1.2
         */
        class CDPL_DESCR_API NPoint2DPharmacophoreFingerprintGenerator : public NPointPharmacophoreFingerprintGenerator
        {

          public:
            typedef std::shared_ptr<NPoint2DPharmacophoreFingerprintGenerator> SharedPointer;

            enum FeatureDistanceType
            {

                MIN_PATH_LENGTH,
                MAX_PATH_LENGTH,
                AVG_PATH_LENGTH
            };

            static constexpr FeatureDistanceType DEF_FEATURE_DISTANCE_TYPE = MIN_PATH_LENGTH;
            
            NPoint2DPharmacophoreFingerprintGenerator();

            NPoint2DPharmacophoreFingerprintGenerator(const NPoint2DPharmacophoreFingerprintGenerator& gen) = default;

            NPoint2DPharmacophoreFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            void setFeatureDistanceType(FeatureDistanceType dist_type);

            FeatureDistanceType getFeatureDistanceType() const;
            
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
