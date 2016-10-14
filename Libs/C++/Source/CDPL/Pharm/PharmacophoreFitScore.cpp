/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFitScore.cpp 
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

#include "CDPL/Pharm/PharmacophoreFitScore.hpp"


using namespace CDPL;


const double Pharm::PharmacophoreFitScore::DEF_FTR_MATCH_COUNT_FACTOR;
const double Pharm::PharmacophoreFitScore::DEF_FTR_POS_MATCH_FACTOR;
const double Pharm::PharmacophoreFitScore::DEF_FTR_GEOM_MATCH_FACTOR;


Pharm::PharmacophoreFitScore::PharmacophoreFitScore(double match_cnt_factor, double pos_match_factor, 
						    double geom_match_factor):
    ftrMatchCntFactor(match_cnt_factor), ftrPosMatchFactor(pos_match_factor), ftrGeomMatchFactor(geom_match_factor)
{}

double Pharm::PharmacophoreFitScore::getFeatureMatchCountFactor() const
{
    return ftrMatchCntFactor;
}

void Pharm::PharmacophoreFitScore::setFeatureMatchCountFactor(double factor)
{
    ftrMatchCntFactor = factor;
}

double Pharm::PharmacophoreFitScore::getFeaturePositionMatchFactor() const
{
    return ftrPosMatchFactor;
}

void Pharm::PharmacophoreFitScore::setFeaturePositionMatchFactor(double factor)
{
    ftrPosMatchFactor = factor;
}

double Pharm::PharmacophoreFitScore::getFeatureGeometryMatchFactor() const
{
    return ftrGeomMatchFactor;
}

void Pharm::PharmacophoreFitScore::setFeatureGeometryMatchFactor(double factor)
{
    ftrGeomMatchFactor = factor;
}

double Pharm::PharmacophoreFitScore::operator()(const Pharmacophore& ref_pharm, const Pharmacophore& algnd_pharm, 
						const Math::Matrix4D& xform)
{
    return 1.0;
}
