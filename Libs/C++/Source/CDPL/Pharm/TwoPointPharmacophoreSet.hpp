/* 
 * TwoPointPharmacophoreSet.hpp 
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


#ifndef CDPL_PHARM_TWOPOINTPHARMACOPHORESET_HPP
#define CDPL_PHARM_TWOPOINTPHARMACOPHORESET_HPP

#include <unordered_set>

#include <boost/functional/hash.hpp>

#include "CDPL/Pharm/TwoPointPharmacophore.hpp"


namespace CDPL
{

    namespace Pharm
    {

        struct TwoPointPharmHashFunc
        {

            inline std::size_t operator()(const TwoPointPharmacophore& pharm) const
            {
                std::size_t hv = 0;

                boost::hash_combine(hv, pharm.getFeature1Type());
                boost::hash_combine(hv, pharm.getFeature2Type());

                return hv;
            }
        };

        struct TwoPointPharmEqCmpFunc
        {

            inline bool operator()(const TwoPointPharmacophore& pharm1, const TwoPointPharmacophore& pharm2) const
            {
                return (pharm1.getFeature1Type() == pharm2.getFeature1Type() &&
                        pharm1.getFeature2Type() == pharm2.getFeature2Type());
            }
        };

        typedef std::unordered_multiset<TwoPointPharmacophore, TwoPointPharmHashFunc, TwoPointPharmEqCmpFunc> TwoPointPharmacophoreSet;
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_TWOPOINTPHARMACOPHORESET_HPP
