/* 
 * FeatureTypeHistogram.hpp 
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
 * \brief Definition of the type CDPL::Pharm::FeatureTypeHistogram.
 */

#ifndef CDPL_PHARM_FEATURETYPEHISTOGRAM_HPP
#define CDPL_PHARM_FEATURETYPEHISTOGRAM_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Util/Map.hpp"


namespace CDPL 
{

    namespace Pharm
    {

        /**
         * \brief A data type for the storage of feature type histograms of pharmacophores.
         *
         * \c %FeatureTypeHistogram is an unique associative map where the keys specify the feature type
         * (defined in namespace Pharm::FeatureType) of the pharmacophore features and the mapped integer values
         * correspond to the feature type frequencies.
         */
        class CDPL_PHARM_API FeatureTypeHistogram : public Util::Map<unsigned int, std::size_t, true>
        {

          public:
            typedef std::shared_ptr<FeatureTypeHistogram> SharedPointer;

          private:
            const char* getClassName() const {
                return "FeatureTypeHistogram";
            }
        };
    }
}

#endif // CDPL_PHARM_FEATURETYPEHISTOGRAM_HPP
