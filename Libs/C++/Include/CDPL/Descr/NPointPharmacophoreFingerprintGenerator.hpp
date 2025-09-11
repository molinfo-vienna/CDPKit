/* 
 * NPointPharmacophoreFingerprintGenerator.hpp 
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
 * \brief Definition of class CDPL::Descr::NPointPharmacophoreFingerprintGenerator.
 */

#ifndef CDPL_DESCR_NPOINTPHARMACOPHOREFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_NPOINTPHARMACOPHOREFINGERPRINTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{
  
    namespace Descr
    {
            
        /**
         * \brief NPointPharmacophoreFingerprintGenerator.
         * \since 1.2
         */
        class CDPL_DESCR_API NPointPharmacophoreFingerprintGenerator
        {

          public:
            static constexpr std::size_t DEF_MIN_FEATURE_TUPLE_SIZE = 1;
            static constexpr std::size_t DEF_MAX_FEATURE_TUPLE_SIZE = 3;

            static constexpr double DEF_BIN_SIZE = 0.5;
        
            virtual ~NPointPharmacophoreFingerprintGenerator() {}
            
            void setMinFeatureTupleSize(std::size_t min_size);

            std::size_t getMinFeatureTupleSize() const;
            
            void setMaxFeatureTupleSize(std::size_t max_size);

            std::size_t getMaxFeatureTupleSize() const;

            void setBinSize(double bin_size);

            double getBinSize() const;
            
            Pharm::PharmacophoreGenerator& getPharmacophoreGenerator();

            const Pharm::PharmacophoreGenerator& getPharmacophoreGenerator() const;
            
          protected:
            NPointPharmacophoreFingerprintGenerator();

            NPointPharmacophoreFingerprintGenerator(const NPointPharmacophoreFingerprintGenerator& gen) = default;
            
            void generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);
            void generate(const Pharm::FeatureContainer& cntnr, Util::BitSet& fp);

          private:
            void init(const Pharm::FeatureContainer& cntnr);

            void enumFeatureTuples(std::size_t curr_ftr_idx, Util::BitSet& fp);

            void emitFeatureTupleBit(Util::BitSet& fp);

            void canonFeatureTupleData(std::size_t curr_ftr_idx);
            
            unsigned long getDistanceBinNumber(double dist) const;
            
            virtual double getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const = 0;

            typedef std::pair<unsigned int, std::size_t> FeatureID;
            typedef std::vector<FeatureID>               FeatureList;
            typedef std::vector<unsigned long>           FeatureTupleData;
            
            std::size_t                          minFtrTupleSize;
            std::size_t                          maxFtrTupleSize;
            double                               binSize;
            Pharm::DefaultPharmacophoreGenerator pharmGen;
            Pharm::BasicPharmacophore            pharm;
            FeatureList                          ftrList;
            Math::ULMatrix                       ftrDistMatrix;
            FeatureList                          ftrTuple;
            FeatureTupleData                     ftrTupleData;
            FeatureTupleData                     tmpFtrTupleData;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_NPOINTPHARMACOPHOREFINGERPRINTGENERATOR_HPP
