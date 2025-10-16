/* 
 * TverskySimilarity.cpp
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


#include <boost/format.hpp>

#include "CDPL/Descr/SimilarityFunctions.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"

#include "TverskySimilarity.hpp"


using namespace SimScreen;


TverskySimilarity::TverskySimilarity(): ScoringFunction("TVERSKY_SIM", "Tversky Similarity", false, BITSET) {}

void TverskySimilarity::addOptions(CmdLineLib::CmdLineBase& cl_base)
{
    cl_base.addOption("tversky-weight-a",
                      "Weight factor of the query molecule fingerprint exclusive bits (default: 1.0).",
                      cl_base.value<double>(&weightA));
    cl_base.addOption("tversky-weight-b",
                      "Weight factor of the database molecule fingerprint exclusive bits (default: 0.0).",
                      cl_base.value<double>(&weightB));
}

void TverskySimilarity::getOptionSummary(std::string& summary) const
{
    summary.append("Tversky Query Mol. FP Weight (a);");
    summary.append((boost::format("%.3f") % weightA).str());
    summary.push_back(';');
    summary.append("Tversky DB Mol. FP Weight (b);");
    summary.append((boost::format("%.3f") % weightB).str());
    summary.push_back(';');
}

double TverskySimilarity::calculate(const CDPL::Util::BitSet& query_fp, const CDPL::Util::BitSet& db_mol_fp) const
{
    return CDPL::Descr::calcTverskySimilarity(query_fp, db_mol_fp, weightA, weightB);
}

double TverskySimilarity::calculate(const CDPL::Math::DVector& query_descr, const CDPL::Math::DVector& db_mol_descr) const
{
    return -1.0;
}
