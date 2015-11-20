/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SimilarityFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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


#include "StaticInit.hpp"

#include <cmath>

#include "CDPL/Chem/SimilarityFunctions.hpp"


using namespace CDPL;


double Chem::calcTanimotoSimilarity(const Util::BitSet& bs1, const Util::BitSet& bs2)
{
	std::size_t bs1_size = bs1.size();
	std::size_t bs2_size = bs2.size();

	if (bs1_size == bs2_size) {
		std::size_t c = (bs1 & bs2).count();

		return (double(c) / (bs1.count() + bs2.count() - c));
	}

	if (bs1_size < bs2_size) {
		Util::BitSet tmp(bs1);

		tmp.resize(bs2_size);

		std::size_t c = (tmp & bs2).count();

		return (double(c) / (tmp.count() + bs2.count() - c));
	}

	Util::BitSet tmp(bs2);

	tmp.resize(bs1_size);
  
	std::size_t c = (bs1 & tmp).count();

	return (double(c) / (bs1.count() + tmp.count() - c));
}

std::size_t Chem::calcHammingDistance(const Util::BitSet& bs1, const Util::BitSet& bs2)
{
	std::size_t bs1_size = bs1.size();
	std::size_t bs2_size = bs2.size();

	if (bs1_size == bs2_size)
		return (bs1 ^ bs2).count();

	if (bs1_size < bs2_size) {
		Util::BitSet tmp(bs1);

		tmp.resize(bs2_size);

		return (tmp ^ bs2).count();
	}

	Util::BitSet tmp(bs2);

	tmp.resize(bs1_size);
  
	return (bs1 ^ tmp).count();
}

double Chem::calcEuclideanDistance(const Util::BitSet& bs1, const Util::BitSet& bs2)
{
	return std::sqrt(double(calcHammingDistance(bs1, bs2)));
}
