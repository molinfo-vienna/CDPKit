/* 
 * ManhattanDistance.cpp
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


#include "CDPL/Descr/SimilarityFunctions.hpp"

#include "ManhattanDistance.hpp"


using namespace SimScreen;


ManhattanDistance::ManhattanDistance(): ScoringFunction("MANHATTAN_DIST", "Manhattan Distance", true, VECTOR) {}

double ManhattanDistance::calculate(const CDPL::Util::BitSet& query_fp, const CDPL::Util::BitSet& db_mol_fp) const
{
    return -1.0;
}

double ManhattanDistance::calculate(const CDPL::Math::DVector& query_descr, const CDPL::Math::DVector& db_mol_descr) const
{
    return CDPL::Descr::calcManhattanDistance(query_descr, db_mol_descr);
}
