/* 
 * ScreeningSettings.cpp 
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

 
#include "StaticInit.hpp"

#include "CDPL/Shape/ScreeningSettings.hpp"
#include "CDPL/Shape/ScoringFunctions.hpp"


using namespace CDPL;


const Shape::ScreeningSettings Shape::ScreeningSettings::DEFAULT;
constexpr double               Shape::ScreeningSettings::NO_CUTOFF;


Shape::ScreeningSettings::ScreeningSettings():
    scoringFunc(&calcTanimotoComboScore), colorFtrType(PHARMACOPHORE_IMP_CHARGES), screeningMode(BEST_MATCH_PER_QUERY),
    almntMode(SHAPE_CENTROID), numRandomStarts(0), allCarbon(true), singleConfSearch(false), optOverlap(true), 
    greedyOpt(true), numOptIter(20), optStopGrad(1.0), scoreCutoff(NO_CUTOFF)    
{}

void Shape::ScreeningSettings::setScoringFunction(const ScoringFunction& func)
{
    scoringFunc = func;
}

const Shape::ScreeningSettings::ScoringFunction& Shape::ScreeningSettings::getScoringFunction() const
{
    return scoringFunc;
}

void Shape::ScreeningSettings::setColorFeatureType(ColorFeatureType type)
{
    colorFtrType = type;
}

Shape::ScreeningSettings::ColorFeatureType Shape::ScreeningSettings::getColorFeatureType() const
{
    return colorFtrType;
}

void Shape::ScreeningSettings::setScreeningMode(ScreeningMode mode)
{
    screeningMode = mode;
}

Shape::ScreeningSettings::ScreeningMode Shape::ScreeningSettings::getScreeningMode() const
{
    return screeningMode;
}

void Shape::ScreeningSettings::setAlignmentMode(AlignmentMode mode)
{
    almntMode = mode;
}

Shape::ScreeningSettings::AlignmentMode Shape::ScreeningSettings::getAlignmentMode() const
{
    return almntMode;
}

void Shape::ScreeningSettings::setNumRandomStarts(std::size_t num_starts)
{
    numRandomStarts = num_starts;
}

std::size_t Shape::ScreeningSettings::getNumRandomStarts() const
{
    return numRandomStarts;
}

void Shape::ScreeningSettings::allCarbonMode(bool all_c)
{
    allCarbon = all_c;
}

bool Shape::ScreeningSettings::allCarbonMode() const
{
    return allCarbon;
}

void Shape::ScreeningSettings::singleConformerSearch(bool single_conf)
{
    singleConfSearch = single_conf;
}

bool Shape::ScreeningSettings::singleConformerSearch() const
{
    return singleConfSearch;
}

void Shape::ScreeningSettings::optimizeOverlap(bool optimize)
{
    optOverlap = optimize;
}

bool Shape::ScreeningSettings::optimizeOverlap() const
{
    return optOverlap;
}

void Shape::ScreeningSettings::greedyOptimization(bool greedy)
{
    greedyOpt = greedy;
}

bool Shape::ScreeningSettings::greedyOptimization() const
{
    return greedyOpt;
}

void Shape::ScreeningSettings::setMaxNumOptimizationIterations(std::size_t max_iter)
{
    numOptIter  = max_iter;
}

std::size_t Shape::ScreeningSettings::getMaxNumOptimizationIterations() const
{
    return numOptIter;
}

void Shape::ScreeningSettings::setOptimizationStopGradient(double grad_norm)
{
    optStopGrad = grad_norm;
}

double Shape::ScreeningSettings::getOptimizationStopGradient() const
{
    return optStopGrad;
}
        
void Shape::ScreeningSettings::setScoreCutoff(double cutoff)
{
    scoreCutoff = cutoff;
}

double Shape::ScreeningSettings::getScoreCutoff() const
{
    return scoreCutoff;
}
