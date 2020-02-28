/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionConstraintConnector.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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


#include "StaticInit.hpp"

#include <algorithm>

#include "CDPL/Pharm/InteractionScoreCombiner.hpp"


using namespace CDPL; 


namespace
{

	double maxValue(double v1, double v2)
	{
		return std::max(v1, v2);
	}
}


Pharm::InteractionScoreCombiner::InteractionScoreCombiner(const ScoringFunction& func1, const ScoringFunction& func2, const CombinationFunction& comb_func): 
    scoringFunc1(func1), scoringFunc2(func2), combFunc(comb_func) {}

Pharm::InteractionScoreCombiner::InteractionScoreCombiner(const ScoringFunction& func1, const ScoringFunction& func2): 
    scoringFunc1(func1), scoringFunc2(func2), combFunc(&maxValue) {}

double Pharm::InteractionScoreCombiner::operator()(const Math::Vector3D& ftr1_pos, const Feature& ftr2) const
{
    return combFunc(scoringFunc1(ftr1_pos, ftr2), scoringFunc2(ftr1_pos, ftr2));
}
