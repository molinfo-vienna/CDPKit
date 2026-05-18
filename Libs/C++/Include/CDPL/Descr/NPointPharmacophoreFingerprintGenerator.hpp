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
#include <functional>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/FeatureSet.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{
  
    namespace Descr
    {
            
        /**
         * \brief Abstract base for N-point pharmacophore fingerprint generators.
         *
         * The base class implements the common machinery for enumerating feature tuples of size in
         * <em>[minTupleSize, maxTupleSize]</em>, binning the feature-pair distances of each tuple and
         * setting the corresponding bits of the output fingerprint. The concrete distance
         * (topological vs. spatial 3D) is provided by the derived class via the pure virtual
         * \c getDistance() hook.
         *
         * \since 1.2
         */
        class CDPL_DESCR_API NPointPharmacophoreFingerprintGenerator
        {

          public:
            /**
             * \brief Default minimum size of generated feature tuples.
             */
            static constexpr std::size_t DEF_MIN_FEATURE_TUPLE_SIZE = 1;

            /**
             * \brief Default maximum size of generated feature tuples.
             */
            static constexpr std::size_t DEF_MAX_FEATURE_TUPLE_SIZE = 3;

            /**
             * \brief Type of the generic functor used to filter which features participate in the fingerprint.
             */
            typedef std::function<bool(const Pharm::Feature&)> FeatureFilterFunction;

            /**
             * \brief Virtual destructor.
             */
            virtual ~NPointPharmacophoreFingerprintGenerator() {}

            /**
             * \brief Sets the minimum size of generated feature tuples.
             * \param min_size The minimum tuple size.
             */
            void setMinFeatureTupleSize(std::size_t min_size);

            /**
             * \brief Returns the currently configured minimum feature tuple size.
             * \return The configured minimum tuple size.
             */
            std::size_t getMinFeatureTupleSize() const;

            /**
             * \brief Sets the maximum size of generated feature tuples.
             * \param max_size The maximum tuple size.
             */
            void setMaxFeatureTupleSize(std::size_t max_size);

            /**
             * \brief Returns the currently configured maximum feature tuple size.
             * \return The configured maximum tuple size.
             */
            std::size_t getMaxFeatureTupleSize() const;

            /**
             * \brief Sets the size of the bins used to discretize feature-pair distances.
             * \param bin_size The bin size.
             */
            void setBinSize(double bin_size);

            /**
             * \brief Returns the currently configured distance bin size.
             * \return The configured bin size.
             */
            double getBinSize() const;

            /**
             * \brief Returns the internal pharmacophore generator used for the input molecular graph.
             * \return A reference to the pharmacophore generator.
             */
            Pharm::PharmacophoreGenerator& getPharmacophoreGenerator();

            /**
             * \brief Returns the internal pharmacophore generator used for the input molecular graph.
             * \return A \c const reference to the pharmacophore generator.
             */
            const Pharm::PharmacophoreGenerator& getPharmacophoreGenerator() const;

            /**
             * \brief Specifies a predicate that selects which features participate in the fingerprint.
             * \param func The feature filter function.
             * \since 1.3
             */
            void setFeatureFilterFunction(const FeatureFilterFunction& func);

            /**
             * \brief Returns the currently configured feature filter function.
             * \return The configured feature filter function.
             * \since 1.3
             */
            const FeatureFilterFunction& getFeatureFilterFunction() const;

          protected:
            /**
             * \brief Default distance bin size.
             */
            static constexpr double DEF_BIN_SIZE = 2.0;

            /**
             * \brief Constructs the \c %NPointPharmacophoreFingerprintGenerator instance.
             */
            NPointPharmacophoreFingerprintGenerator();

            /**
             * \brief Copy constructor.
             */
            NPointPharmacophoreFingerprintGenerator(const NPointPharmacophoreFingerprintGenerator& gen) = default;

            /**
             * \brief Generates the fingerprint of the molecular graph \a molgraph.
             * \param molgraph The molecular graph.
             * \param fp The output bitset.
             */
            void generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            /**
             * \brief Generates the fingerprint of the feature container \a cntnr.
             * \param cntnr The feature container.
             * \param fp The output bitset.
             */
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
            FeatureFilterFunction                ftrFilterFunc;
            Pharm::DefaultPharmacophoreGenerator pharmGen;
            Pharm::BasicPharmacophore            pharm;
            Pharm::FeatureSet                    ftrSubset;
            FeatureList                          ftrList;
            Math::ULMatrix                       ftrDistMatrix;
            FeatureList                          ftrTuple;
            FeatureTupleData                     ftrTupleData;
            FeatureTupleData                     tmpFtrTupleData;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_NPOINTPHARMACOPHOREFINGERPRINTGENERATOR_HPP
