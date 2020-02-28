/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ThreePointPharmacophoreGenerator.hpp 
 *
 * This file is part of the Pharmical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PHARM_THREEPOINTPHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_THREEPOINTPHARMACOPHOREGENERATOR_HPP

#include <cstddef>

#include <CDPL/Pharm/NPointPharmacophoreGeneratorBase.hpp>


namespace CDPL 
{

    namespace Pharm
    {

		template <typename PharmType>
		class ThreePointPharmacophoreGenerator : private NPointPharmacophoreGeneratorBase
		{

		public:
			
			template <typename Iter, typename OutIter> 
			void generate(const Iter& beg, const Iter& end, OutIter out, bool gen_perms);
		};
    }
}


// Implementation

template <typename PharmType>
template <typename Iter, typename OutIter> 
void CDPL::Pharm::ThreePointPharmacophoreGenerator<PharmType>::generate(const Iter& beg, const Iter& end, 
																		OutIter out, bool gen_perms)
{
	const FeatureAndTypeArray& canon_ftrs = getCanonOrderedFeatures(beg, end);
	std::size_t num_ftrs = canon_ftrs.size();

	for (std::size_t i = 0; i < num_ftrs; i++) {
		const Feature& ftr1 = *canon_ftrs[i].first;
		unsigned int ftr1_type = canon_ftrs[i].second;

		for (std::size_t j = i + 1; j < num_ftrs; j++) {
			const Feature& ftr2 = *canon_ftrs[j].first;
			unsigned int ftr2_type = canon_ftrs[j].second;

			for (std::size_t k = j + 1; k < num_ftrs; k++) {
				const Feature& ftr3 = *canon_ftrs[k].first;

				*out = PharmType(ftr1, ftr2, ftr3); ++out;

				if (!gen_perms)
					continue;

				unsigned int ftr3_type = canon_ftrs[k].second;

				if (ftr1_type == ftr2_type) {
					if (ftr2_type == ftr3_type) {
						*out = PharmType(ftr1, ftr3, ftr2); ++out;
						*out = PharmType(ftr2, ftr1, ftr3); ++out;
						*out = PharmType(ftr2, ftr3, ftr1); ++out;
						*out = PharmType(ftr3, ftr2, ftr1); ++out;
						*out = PharmType(ftr3, ftr1, ftr2); ++out;

					} else {
						*out = PharmType(ftr2, ftr1, ftr3); ++out;
					}

				} else if (ftr2_type == ftr3_type) {
					*out = PharmType(ftr1, ftr3, ftr2); ++out;
				}
			}
		}
	}
}

#endif // CDPL_PHARM_THREEPOINTPHARMACOPHOREGENERATOR_HPP
