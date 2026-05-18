/* 
 * NPoint3DPharmacophoreFingerprintGenerator.hpp 
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
 * \brief Definition of class CDPL::Descr::NPoint3DPharmacophoreFingerprintGenerator.
 */

#ifndef CDPL_DESCR_NPOINT3DPHARMACOPHOREFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_NPOINT3DPHARMACOPHOREFINGERPRINTGENERATOR_HPP

#include <memory>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/NPointPharmacophoreFingerprintGenerator.hpp"


namespace CDPL
{

    namespace Descr
    {

        /**
         * \brief N-point pharmacophore fingerprint generator that uses spatial 3D feature distances.
         *
         * The fingerprint encodes the binned Euclidean distances between all combinations of feature
         * tuples generated from a molecular graph or feature container.
         *
         * \since 1.2
         */
        class CDPL_DESCR_API NPoint3DPharmacophoreFingerprintGenerator : public NPointPharmacophoreFingerprintGenerator
        {

          public:
            /**
             * \brief Default distance bin size.
             * \since 1.3
             */
            static constexpr double DEF_BIN_SIZE = 3.0;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %NPoint3DPharmacophoreFingerprintGenerator instances.
             */
            typedef std::shared_ptr<NPoint3DPharmacophoreFingerprintGenerator> SharedPointer;

            /**
             * \brief Constructs the \c %NPoint3DPharmacophoreFingerprintGenerator instance.
             */
            NPoint3DPharmacophoreFingerprintGenerator();

            /**
             * \brief Copy constructor.
             */
            NPoint3DPharmacophoreFingerprintGenerator(const NPoint3DPharmacophoreFingerprintGenerator& gen) = default;

            /**
             * \brief Constructs the \c %NPoint3DPharmacophoreFingerprintGenerator instance and generates the fingerprint of \a molgraph.
             * \param molgraph The molecular graph.
             * \param fp The output bitset.
             */
            NPoint3DPharmacophoreFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            /**
             * \brief Constructs the \c %NPoint3DPharmacophoreFingerprintGenerator instance and generates the fingerprint of \a cntnr.
             * \param cntnr The feature container.
             * \param fp The output bitset.
             */
            NPoint3DPharmacophoreFingerprintGenerator(const Pharm::FeatureContainer& cntnr, Util::BitSet& fp);

            using NPointPharmacophoreFingerprintGenerator::generate;
            
          private:
            double getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_NPOINT3DPHARMACOPHOREFINGERPRINTGENERATOR_HPP
