/* 
 * TwoPointPharmacophoreGenerator.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
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


#ifndef CDPL_PHARM_TWOPOINTPHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_TWOPOINTPHARMACOPHOREGENERATOR_HPP

#include <cstddef>

#include <CDPL/Pharm/NPointPharmacophoreGeneratorBase.hpp>


namespace CDPL
{

    namespace Pharm
    {

        template <typename PharmType>
        class TwoPointPharmacophoreGenerator : private NPointPharmacophoreGeneratorBase
        {

          public:
            template <typename Iter, typename OutIter>
            void generate(const Iter& beg, const Iter& end, OutIter out);
        };
    } // namespace Pharm
} // namespace CDPL


// Implementation

template <typename PharmType>
template <typename Iter, typename OutIter>
void CDPL::Pharm::TwoPointPharmacophoreGenerator<PharmType>::generate(const Iter& beg, const Iter& end, OutIter out)
{
    const FeatureAndTypeArray& canon_ftrs = getCanonOrderedFeatures(beg, end);
    std::size_t                num_ftrs   = canon_ftrs.size();

    for (std::size_t i = 0; i < num_ftrs; i++) {
        const Feature& ftr1 = *canon_ftrs[i].first;

        for (std::size_t j = i + 1; j < num_ftrs; j++) {
            *out = PharmType(ftr1, *canon_ftrs[j].first);
            ++out;
        }
    }
}

#endif // CDPL_PHARM_TWOPOINTPHARMACOPHOREGENERATOR_HPP
