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
#include <cstddef>
#include <cmath>
#include <limits>

#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Base/Exceptions.hpp"
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

        inline void calcCoordsTransform(const Math::Vector3DArray& coords, double* trans, double& scaling_fact, unsigned int prec)
        {
            constexpr double DOUBLE_MAX = std::numeric_limits<double>::max();
            constexpr double DOUBLE_MIN = -DOUBLE_MAX;
            
            double bbox_min[3] = { DOUBLE_MAX, DOUBLE_MAX, DOUBLE_MAX };
            double bbox_max[3] = { DOUBLE_MIN, DOUBLE_MIN, DOUBLE_MIN };
            
            for (auto& xyz : coords) {
                for (std::size_t i = 0; i < 3; i++) {
                    auto c = xyz(i);

                    if (std::isnan(c) || std::isinf(c))
                        continue;

                    if (c > bbox_max[i])
                        bbox_max[i] = c;

                    if (c < bbox_min[i])
                        bbox_min[i] = c;
                }
            }

            double max_bbox_dim = 0.0;

            for (std::size_t i = 0; i < 3; i++)
                if (bbox_max[i] > bbox_min[i])
                    max_bbox_dim = std::max(max_bbox_dim, bbox_max[i] - bbox_min[i]);

            max_bbox_dim = std::round(max_bbox_dim * (1 << prec));

            if (max_bbox_dim > (double(INT16_FIXED_POINT_MAX) - double(INT16_FIXED_POINT_MIN))) {
                scaling_fact = (double(INT16_FIXED_POINT_MAX) - double(INT16_FIXED_POINT_MIN)) / max_bbox_dim;

                for (std::size_t i = 0; i < 3; i++)
                    if (bbox_max[i] >= bbox_min[i]) {
                        bbox_max[i] *= scaling_fact;
                        bbox_min[i] *= scaling_fact;
                    }
            } else
                scaling_fact = 1.0;

            for (std::size_t i = 0; i < 3; i++) {
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

        struct PSDIOError : public Base::IOError
        {
            
            PSDIOError(const std::string& msg): IOError(msg) {}
        };
        
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDDATAIOUTILITIES_HPP
