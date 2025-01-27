/* 
 * PSDDataIOUtilities.hpp
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


#ifndef CDPL_PHARM_PSDDATAIOUTILITIES_HPP
#define CDPL_PHARM_PSDDATAIOUTILITIES_HPP

#include <cstdint>
#include <cmath>
#include <limits>

#include "CDPL/Internal/CDFFormatData.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL
{

    namespace Pharm
    {

        constexpr std::int16_t INT16_FIXED_POINT_NAN = std::numeric_limits<std::int16_t>::max();
        constexpr std::int16_t INT16_FIXED_POINT_INF = std::numeric_limits<std::int16_t>::min();
        constexpr std::int16_t INT16_FIXED_POINT_MAX = std::numeric_limits<std::int16_t>::max() - 1;
        constexpr std::int16_t INT16_FIXED_POINT_MIN = std::numeric_limits<std::int16_t>::min() + 1;
        
        template <typename T>
        inline std::int16_t floatingToInt16FixedPoint(const T& val, unsigned int prec)
        {
            if (std::isnan(val))
                return INT16_FIXED_POINT_NAN;

            if (std::isinf(val))
                return INT16_FIXED_POINT_INF;

            auto sv = std::round(val * (1 << prec));

            if (sv > INT16_FIXED_POINT_MAX)
                return INT16_FIXED_POINT_MAX;

            if (sv < INT16_FIXED_POINT_MIN)
                return INT16_FIXED_POINT_MIN;

            return sv;
        }

        template <typename T>
        inline T int16FixedToFloatingPoint(std::int16_t val, unsigned int prec)
        {
            switch (val) {
                
                case INT16_FIXED_POINT_NAN:
                    return std::numeric_limits<T>::quiet_NaN();

                case INT16_FIXED_POINT_INF:
                    return std::numeric_limits<T>::infinity();

                default:
                    return (T(val) / (1 << prec));
            }
        }

        template <typename T>
        inline void calcCoordsTransform(const T& coords, typename T::value_type* trans, typename T::value_type& scaling_fact, unsigned int prec)
        {
            typedef typename T::value_type CVT;
            typedef typename T::size_type SizeType;

            constexpr CVT CVT_MAX = std::numeric_limits<CVT>::max();
            constexpr CVT CVT_MIN = -CVT_MAX;
            
            CVT bbox_min[3] = { CVT_MAX, CVT_MAX, CVT_MAX };
            CVT bbox_max[3] = { CVT_MIN, CVT_MIN, CVT_MIN };
            
            for (SizeType i = 0, num_triplets = coords.size() / 3; i < num_triplets; i++) {
                for (SizeType j = 0; j < 3; j++) {
                    auto c = coords[i * 3 + j];

                    if (std::isnan(c) || std::isinf(c))
                        continue;

                    if (c > bbox_max[j])
                        bbox_max[j] = c;

                    if (c < bbox_min[j])
                        bbox_min[j] = c;
                }
            }

            CVT max_bbox_dim{0};

            for (SizeType i = 0; i < 3; i++)
                if (bbox_max[i] > bbox_min[i])
                    max_bbox_dim = std::max(max_bbox_dim, bbox_max[i] - bbox_min[i]);

            max_bbox_dim = std::round(max_bbox_dim * (1 << prec));

            if (max_bbox_dim > (CVT(INT16_FIXED_POINT_MAX) - CVT(INT16_FIXED_POINT_MIN))) {
                scaling_fact = (CVT(INT16_FIXED_POINT_MAX) - CVT(INT16_FIXED_POINT_MIN)) / max_bbox_dim;

                for (SizeType i = 0; i < 3; i++)
                    if (bbox_max[i] >= bbox_min[i]) {
                        bbox_max[i] *= scaling_fact;
                        bbox_min[i] *= scaling_fact;
                    }
            } else
                scaling_fact = CVT(1);

            for (SizeType i = 0; i < 3; i++) {
                if (bbox_max[i] < bbox_min[i]) {
                    trans[i] = 0.0;
                    continue;
                }

                if ((std::round(bbox_max[i] * (1 << prec)) <= INT16_FIXED_POINT_MAX) &&
                    (std::round(bbox_min[i] * (1 << prec)) >= INT16_FIXED_POINT_MIN)) {
                    trans[i] = 0.0;
                    continue;
                }

                trans[i] = -(bbox_max[i] + bbox_min[i]) / 2; 
            }
        }
        
        inline
        bool containsCDFData(Internal::ByteBuffer& byte_buf)
        {
            if (byte_buf.getSize() < Internal::CDF::HEADER_SIZE)
                return false;

            std::uint32_t cdf_id;
            
            byte_buf.setIOPointer(0);
            byte_buf.getInt(cdf_id);

            return (cdf_id == Internal::CDF::FORMAT_ID);
        }
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDDATAIOUTILITIES_HPP
