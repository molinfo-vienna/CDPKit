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
         * \brief NPoint3DPharmacophoreFingerprintGenerator.
         * \since 1.2
         */
        class CDPL_DESCR_API NPoint3DPharmacophoreFingerprintGenerator : public NPointPharmacophoreFingerprintGenerator
        {

          public:
            typedef std::shared_ptr<NPoint3DPharmacophoreFingerprintGenerator> SharedPointer;

            NPoint3DPharmacophoreFingerprintGenerator() = default;

            NPoint3DPharmacophoreFingerprintGenerator(const NPoint3DPharmacophoreFingerprintGenerator& gen) = default;

            NPoint3DPharmacophoreFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            NPoint3DPharmacophoreFingerprintGenerator(const Pharm::FeatureContainer& cntnr, Util::BitSet& fp);
            
            using NPointPharmacophoreFingerprintGenerator::generate;
            
          private:
            double getDistance(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2) const;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_NPOINT3DPHARMACOPHOREFINGERPRINTGENERATOR_HPP
