/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TwoPointPharmacophoreSet.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>

#include "CDPL/Pharm/TwoPointPharmacophore.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		struct TwoPointPharmHashFunc : public std::unary_function<TwoPointPharmacophore, std::size_t>
		{

			inline std::size_t operator()(const TwoPointPharmacophore& pharm) const {
				std::size_t hv = 0;

				boost::hash_combine(hv, pharm.getFeature1Type());
				boost::hash_combine(hv, pharm.getFeature2Type());

				return hv;
			}
		};

		struct TwoPointPharmEqCmpFunc : public std::binary_function<TwoPointPharmacophore, TwoPointPharmacophore, bool>
		{

			inline bool operator()(const TwoPointPharmacophore& pharm1, const TwoPointPharmacophore& pharm2) const {
				return (pharm1.getFeature1Type() == pharm2.getFeature1Type() &&
						pharm1.getFeature2Type() == pharm2.getFeature2Type());
			}
		};

		typedef boost::unordered_multiset<TwoPointPharmacophore, TwoPointPharmHashFunc, TwoPointPharmEqCmpFunc> TwoPointPharmacophoreSet;
    }
}

#endif // CDPL_PHARM_TWOPOINTPHARMACOPHORESET_HPP
