/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculator.cpp 
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

#include <algorithm>

#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/InteractionScoreGridSet.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"  
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

    Pharm::InteractionScoreGridCalculator::InteractionScoringFunction DEF_FUNC;

    double maxElement(const Math::DVector& vec)
    {
		return normInf(vec);
    }
}
 

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(): 
    xStepSize(0.0), yStepSize(0.0), zStepSize(0.0),
    gridXSize(0), gridYSize(0), gridZSize(0), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4)),
    pharmGenerator(false), atomCoordsFunc(&Chem::get3DCoordinates), 
    finalScoreFunc(&maxElement)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(step_size), yStepSize(step_size), zStepSize(step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4)),
    pharmGenerator(false), atomCoordsFunc(&Chem::get3DCoordinates), 
    finalScoreFunc(&maxElement)
{}

Pharm::InteractionScoreGridCalculator::InteractionScoreGridCalculator(double x_step_size, double y_step_size, double z_step_size, 
																	  std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(x_step_size), yStepSize(y_step_size), zStepSize(z_step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4)),
    pharmGenerator(false), atomCoordsFunc(&Chem::get3DCoordinates), 
    finalScoreFunc(&maxElement)
{}

const Math::Matrix4D& Pharm::InteractionScoreGridCalculator::getCoordinatesTransform() const
{
    return coordsTransform;
}

double Pharm::InteractionScoreGridCalculator::getXStepSize() const
{
    return xStepSize;
}

void Pharm::InteractionScoreGridCalculator::setXStepSize(double size)
{
    xStepSize = size;
}

double Pharm::InteractionScoreGridCalculator::getYStepSize() const
{
    return yStepSize;
}

void Pharm::InteractionScoreGridCalculator::setYStepSize(double size)
{
    yStepSize = size;
}

double Pharm::InteractionScoreGridCalculator::getZStepSize() const
{
    return zStepSize;
}

void Pharm::InteractionScoreGridCalculator::setZStepSize(double size)
{
    zStepSize = size;
}

std::size_t Pharm::InteractionScoreGridCalculator::getGridXSize() const
{
    return gridXSize;
}

void Pharm::InteractionScoreGridCalculator::setGridXSize(std::size_t size)
{
    gridXSize = size;
}

std::size_t Pharm::InteractionScoreGridCalculator::getGridYSize() const
{
    return gridYSize;
}

void Pharm::InteractionScoreGridCalculator::setGridYSize(std::size_t size)
{
    gridYSize = size;
}

std::size_t Pharm::InteractionScoreGridCalculator::getGridZSize() const
{
    return gridZSize;
}

void Pharm::InteractionScoreGridCalculator::setGridZSize(std::size_t size)
{
    gridZSize = size;
}

void Pharm::InteractionScoreGridCalculator::enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable)
{
    if (enable)
		enabledInteractions.insert(FeatureTypePair(ftr_type, tgt_ftr_type));
    else
		enabledInteractions.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

bool Pharm::InteractionScoreGridCalculator::isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    return (enabledInteractions.find(FeatureTypePair(ftr_type, tgt_ftr_type)) != enabledInteractions.end());
}

void Pharm::InteractionScoreGridCalculator::clearEnabledInteractions()
{
    enabledInteractions.clear();
}

void Pharm::InteractionScoreGridCalculator::setInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const InteractionScoringFunction& func)
{
    scoringFuncMap[FeatureTypePair(ftr_type, tgt_ftr_type)] = func;
}

const Pharm::InteractionScoreGridCalculator::InteractionScoringFunction& 
Pharm::InteractionScoreGridCalculator::getInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    InteractionScoringFuncMap::const_iterator it = scoringFuncMap.find(FeatureTypePair(ftr_type, tgt_ftr_type));

    return (it == scoringFuncMap.end() ? DEF_FUNC : it->second);
}

void Pharm::InteractionScoreGridCalculator::removeInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type)
{
    scoringFuncMap.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

void Pharm::InteractionScoreGridCalculator::setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func)
{
    atomCoordsFunc = func;
    pharmGenerator.setAtom3DCoordinatesFunction(func);
}

void Pharm::InteractionScoreGridCalculator::setFinalInteractionScoreFunction(const FinalInteractionScoreFunction& func)
{
    finalScoreFunc = func;
}

void Pharm::InteractionScoreGridCalculator::setStericClashFactorFunction(const StericClashFactorFunction& func)
{
    stericClashFactorFunc = func;
}
	
void Pharm::InteractionScoreGridCalculator::calculate(const Chem::MolecularGraph& molgraph, InteractionScoreGridSet& grid_set)
{
    molPharmacophore.clear();
    pharmGenerator.generate(molgraph, molPharmacophore);

    calculate(molgraph, molPharmacophore, grid_set);
}

void Pharm::InteractionScoreGridCalculator::calculate(const Chem::MolecularGraph& molgraph, const FeatureContainer& features, InteractionScoreGridSet& grid_set)
{
    std::size_t old_num_grids = grid_set.getSize();

    calculate(features, grid_set);

    std::size_t num_grids = grid_set.getSize();

    if (stericClashFactorFunc && (old_num_grids < num_grids)) {
		Math::Vector3D grid_pos;

		for (std::size_t i = 0; i < gridXSize; i++) {
			for (std::size_t j = 0; j < gridYSize; j++) {
				for (std::size_t k = 0; k < gridZSize; k++) {
					grid_set[old_num_grids].getCoordinates(i, j, k, grid_pos);

					double clash_factor = stericClashFactorFunc(grid_pos, molgraph, atomCoordsFunc);

					for (std::size_t l = old_num_grids; l < num_grids; l++)
						grid_set[l](i, j, k) *= clash_factor;
				}
			}
		}
    }
}

void Pharm::InteractionScoreGridCalculator::calculate(const FeatureContainer& features, InteractionScoreGridSet& grid_set)
{
    Math::Vector3D grid_pos;
    Math::DVector part_scores;
  
    Feature& grid_ftr = (gridPharmacophore.getNumFeatures() == 0 ? gridPharmacophore.addFeature() : gridPharmacophore.getFeature(0));

    for (InteractionScoringFuncMap::const_iterator it = scoringFuncMap.begin(), end = scoringFuncMap.end(); it != end; ++it) {
		if (!it->second)
			continue;

		if (enabledInteractions.find(it->first) == enabledInteractions.end())
			continue;

		unsigned int ftr_type = it->first.first;
		unsigned int tgt_ftr_type = it->first.second;

		InteractionScoreGrid::SharedPointer grid_ptr(new InteractionScoreGrid(ftr_type, tgt_ftr_type));
	
		grid_ptr->resize(gridXSize, gridYSize, gridZSize, false);
		grid_ptr->setXStepSize(xStepSize);
		grid_ptr->setYStepSize(yStepSize);
		grid_ptr->setZStepSize(zStepSize);

		grid_ptr->setCoordinatesTransform(coordsTransform);

		tgtFeatures.clear();

		for (FeatureContainer::ConstFeatureIterator ftr_it = features.getFeaturesBegin(), ftr_end = features.getFeaturesEnd(); ftr_it != ftr_end; ++ftr_it) {
			const Feature& tgt_ftr = *ftr_it;

			if (getType(tgt_ftr) == tgt_ftr_type)
				tgtFeatures.push_back(&tgt_ftr);
		}

		part_scores.resize(tgtFeatures.size(), false);

		for (std::size_t i = 0; i < gridXSize; i++) {
			for (std::size_t j = 0; j < gridYSize; j++) {
				for (std::size_t k = 0, l = 0; k < gridZSize; k++) {

					grid_ptr->getCoordinates(i, j, k, grid_pos);
					set3DCoordinates(grid_ftr, grid_pos);

					for (FeatureList::const_iterator ftr_it = tgtFeatures.begin(), ftr_end = tgtFeatures.end(); ftr_it != ftr_end; ++ftr_it)
						part_scores[l++] = it->second(grid_ftr, **ftr_it);

					if (l == 0)
						(*grid_ptr)(i, j, k) = 0.0;
					else
						(*grid_ptr)(i, j, k) = finalScoreFunc(part_scores);

					l = 0;
				}
			}
		}

		grid_set.addElement(grid_ptr);
    }
}
