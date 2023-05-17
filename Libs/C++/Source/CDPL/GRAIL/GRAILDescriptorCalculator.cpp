/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GRAILDescriptorCalculator.cpp 
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

#include "CDPL/GRAIL/GRAILDescriptorCalculator.hpp"
#include "CDPL/GRAIL/FeatureFunctions.hpp"
#include "CDPL/GRAIL/FeatureType.hpp"
#include "CDPL/Chem/AtomArray3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Pharm/HydrophobicAtomFeatureGenerator.hpp"
#include "CDPL/Internal/Octree.hpp"


using namespace CDPL;


namespace
{

	const double HYDROPHOBICIY_THRESHOLD = 0.15;
}


GRAIL::GRAILDescriptorCalculator::GRAILDescriptorCalculator():
	tgtPharmGenerator(Pharm::DefaultPharmacophoreGenerator::STATIC_H_DONORS), tgtAtomOctree(new Octree()), 
	tgtFtrSubsets(FeatureType::MAX_EXT_TYPE + 1)
{
	Pharm::HydrophobicAtomFeatureGenerator::SharedPointer h_gen(new Pharm::HydrophobicAtomFeatureGenerator());
	
    h_gen->setHydrophobicityThreshold(HYDROPHOBICIY_THRESHOLD);

    tgtPharmGenerator.setFeatureGenerator(FeatureType::HYDROPHOBIC, h_gen);
	tgtPharmGenerator.enableFeature(FeatureType::HALOGEN_BOND_ACCEPTOR, true);
}

GRAIL::GRAILDescriptorCalculator::GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc):
	tgtPharmacophore(calc.tgtPharmacophore), tgtAtomCoords(calc.tgtAtomCoords), tgtAtomOctree(new Octree()), 
	tgtFtrSubsets(FeatureType::MAX_EXT_TYPE + 1)
{
	Pharm::HydrophobicAtomFeatureGenerator::SharedPointer h_gen(new Pharm::HydrophobicAtomFeatureGenerator());
	
    h_gen->setHydrophobicityThreshold(HYDROPHOBICIY_THRESHOLD);

    tgtPharmGenerator.setFeatureGenerator(FeatureType::HYDROPHOBIC, h_gen);
	tgtPharmGenerator.enableFeature(FeatureType::HALOGEN_BOND_ACCEPTOR, true);

	tgtAtomOctree->initialize(tgtAtomCoords);

	copyTargetFtrSubsetList(calc.tgtFtrSubsets);
// TODO
}

GRAIL::GRAILDescriptorCalculator& GRAIL::GRAILDescriptorCalculator::operator=(const GRAILDescriptorCalculator& calc)
{
	if (this == &calc)
		return *this;

	tgtAtomCoords = calc.tgtAtomCoords;
	tgtPharmacophore = calc.tgtPharmacophore;

	tgtAtomOctree->initialize(tgtAtomCoords);

	copyTargetFtrSubsetList(calc.tgtFtrSubsets);
// TODO
	return *this;
}

void GRAIL::GRAILDescriptorCalculator::initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func, bool tgt_env_changed)
{
	using namespace Pharm;

	std::size_t num_atoms = tgt_env.getNumAtoms();

	tgtAtomCoords.resize(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++)
		tgtAtomCoords[i].assign(coords_func(tgt_env.getAtom(i)));

	tgtAtomOctree->initialize(tgtAtomCoords);

	tgtPharmGenerator.setAtom3DCoordinatesFunction(Chem::AtomArray3DCoordinatesFunctor(tgtAtomCoords, tgt_env));
	tgtPharmGenerator.generate(tgt_env, tgtPharmacophore);

	for (FeatureSubsetList::iterator it = tgtFtrSubsets.begin(), end = tgtFtrSubsets.end(); it != end; ++it)
		it->features.clear();

	for (BasicPharmacophore::ConstFeatureIterator it = tgtPharmacophore.getFeaturesBegin(), end = tgtPharmacophore.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;
		unsigned int ext_type = perceiveExtendedType(ftr, false);
		
		if (ext_type > FeatureType::MAX_EXT_TYPE) // sanity check
			continue;

		tgtFtrSubsets[ext_type].features.push_back(&ftr);
	}

	for (FeatureSubsetList::iterator it = tgtFtrSubsets.begin(), end = tgtFtrSubsets.end(); it != end; ++it) {
		FeatureSubset& ftr_ss = *it;

		if (ftr_ss.features.empty())
			continue;

		std::size_t num_ftrs = ftr_ss.features.size();
		
		tgtFtrCoords.resize(num_ftrs);

		for (std::size_t i = 0; i < num_ftrs; i++) 
			tgtFtrCoords[i].assign(get3DCoordinates(*ftr_ss.features[i]));

		if (!ftr_ss.octree)
			ftr_ss.octree.reset(new Octree());

		ftr_ss.octree->initialize(tgtFtrCoords);
	}

	if (!tgt_env_changed)
		return;

	// TODO
}

void GRAIL::GRAILDescriptorCalculator::copyTargetFtrSubsetList(const FeatureSubsetList& ftr_ss_list)
{
	for (std::size_t i = 0; i < (FeatureType::MAX_EXT_TYPE + 1); i++) {
		tgtFtrSubsets[i].features.clear();

		std::size_t num_ftrs = ftr_ss_list[i].features.size();

		tgtFtrCoords.resize(num_ftrs);

		for (std::size_t j = 0; j < num_ftrs; j++) {
			tgtFtrSubsets[i].features.push_back(&tgtPharmacophore.getFeature(ftr_ss_list[i].features[j]->getIndex()));
			tgtFtrCoords[j].assign(get3DCoordinates(*tgtFtrSubsets[i].features.back()));
		}

		if (!tgtFtrSubsets[i].octree)
			tgtFtrSubsets[i].octree.reset(new Octree());
		
		tgtFtrSubsets[i].octree->initialize(tgtFtrCoords);
	}
}
