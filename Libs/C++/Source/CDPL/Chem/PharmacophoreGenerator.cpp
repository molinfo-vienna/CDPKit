/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreGenerator.cpp 
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

#include <sstream>

#include <boost/bind.hpp>

#include "CDPL/Chem/PharmacophoreGenerator.hpp"
#include "CDPL/Chem/AromaticFeatureGenerator.hpp"
#include "CDPL/Chem/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"


using namespace CDPL; 


namespace
{

	Chem::PatternBasedFeatureGenerator defHBAFeatureGenerator;
	Chem::PatternBasedFeatureGenerator defHBDFeatureGenerator;
	Chem::PatternBasedFeatureGenerator defPIFeatureGenerator;
	Chem::PatternBasedFeatureGenerator defNIFeatureGenerator;

	struct Init 
	{

		Init() {
			using namespace Chem;

			defHBAFeatureGenerator.addIncludePattern(parseSMARTS("[#7,#8,S;X1,X2;!$(O(C)C(=O)):3]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
			defHBAFeatureGenerator.addIncludePattern(parseSMARTS("[F:3]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);

			defHBAFeatureGenerator.addExcludePattern(parseSMARTS("[#8](c)c"));

			// ----

			defHBDFeatureGenerator.addIncludePattern(parseSMARTS("[O:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);
			defHBDFeatureGenerator.addIncludePattern(parseSMARTS("[CX2,SX2:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);
			defHBDFeatureGenerator.addIncludePattern(parseSMARTS("[*:4](=,:*)-,:[#7:11](-,:[*:4])[#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::VECTOR, 3.0);
			defHBDFeatureGenerator.addIncludePattern(parseSMARTS("[#7:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);

			defHBDFeatureGenerator.addExcludePattern(parseSMARTS("c1nnnn1"));
			defHBDFeatureGenerator.addExcludePattern(parseSMARTS("N-[SX4](=O)(=O)[CX4](F)(F)F"));
			defHBDFeatureGenerator.addExcludePattern(parseSMARTS("[C,P,S](=O)O"));

			// ----

			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[N;!$(NC(=[O,N]));!$(Nc);!$(N[#7,#8,#16]):3]1[C:3][C:3][N;!$(NC(=[O,N]));!$(Nc);!$(N[#7,#8,#16]):3][C:3][C:3]1"), FeatureType::POS_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[NX3:3]([CX4])([CX4,#1])[CX4,#1]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([NH0])[!N]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N;H1,H2:3])[!N]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N:3])[N:3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defPIFeatureGenerator.addIncludePattern(parseSMARTS("[+,+2,+3,+4,+5,+6,+7;!$(*[-,-2,-3,-4,-5,-6,-7]):3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

			defPIFeatureGenerator.addExcludePattern(parseSMARTS("N([R])([R])[C,S,P](=O)"));

			// ----

			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[c;!$(c[#7][#6]);!$(c[#7][#7][#6]):3]1[n:3][n:3][n:3][n:3]1"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])(~[O:3])[O:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])[O:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[NR;$([NH1]),$([-1]):3](-C(=O))-[SX4](=O)(=O)"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[C:3](=[O:3])[N:3][OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[C:3]([O:3])[N:3][OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[C:3][O:3](=[N:3][OH1,O-:3])"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[S,C,P:3](~[O:3])[OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[N:3]-[SX4](=O)(=O)[CX4](F)(F)F"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
			defNIFeatureGenerator.addIncludePattern(parseSMARTS("[-,-2,-3,-4,-5,-6,-7;!$(*[+,+2,+3,+4,+5,+6,+7]):3]"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

			defNIFeatureGenerator.addExcludePattern(parseSMARTS("CC(=O)OC"));
			defNIFeatureGenerator.addExcludePattern(parseSMARTS("C(O)O"));
			defNIFeatureGenerator.addExcludePattern(parseSMARTS("[P,S](~O)(~O)(~O)N"));
		}

	} init;
}


Chem::PharmacophoreGenerator::PharmacophoreGenerator():
	hbaFeatureGenerator(new PatternBasedFeatureGenerator(defHBAFeatureGenerator)),
    hbdFeatureGenerator(new PatternBasedFeatureGenerator(defHBDFeatureGenerator)),
    piFeatureGenerator(new PatternBasedFeatureGenerator(defPIFeatureGenerator)),
    niFeatureGenerator(new PatternBasedFeatureGenerator(defNIFeatureGenerator)),
    arFeatureGenerator(new AromaticFeatureGenerator()),
    hydFeatureGenerator(new HydrophobicFeatureGenerator())
{
	featureFuncMap[FeatureType::HYDROPHOBIC] = boost::bind(&HydrophobicFeatureGenerator::generate, hydFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::AROMATIC] = boost::bind(&AromaticFeatureGenerator::generate, arFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::NEG_IONIZABLE] = boost::bind(&PatternBasedFeatureGenerator::generate, niFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::POS_IONIZABLE] = boost::bind(&PatternBasedFeatureGenerator::generate, piFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::H_BOND_DONOR] = boost::bind(&PatternBasedFeatureGenerator::generate, hbdFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::H_BOND_ACCEPTOR] = boost::bind(&PatternBasedFeatureGenerator::generate, hbaFeatureGenerator, _1, _2);

	enabledFeatures.insert(FeatureType::HYDROPHOBIC);
	enabledFeatures.insert(FeatureType::AROMATIC);
	enabledFeatures.insert(FeatureType::NEG_IONIZABLE);
	enabledFeatures.insert(FeatureType::POS_IONIZABLE);
	enabledFeatures.insert(FeatureType::H_BOND_DONOR);
	enabledFeatures.insert(FeatureType::H_BOND_ACCEPTOR);
}

Chem::PharmacophoreGenerator::PharmacophoreGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm): 
	hbaFeatureGenerator(new PatternBasedFeatureGenerator(defHBAFeatureGenerator)),
    hbdFeatureGenerator(new PatternBasedFeatureGenerator(defHBDFeatureGenerator)),
    piFeatureGenerator(new PatternBasedFeatureGenerator(defPIFeatureGenerator)),
    niFeatureGenerator(new PatternBasedFeatureGenerator(defNIFeatureGenerator)),
    arFeatureGenerator(new AromaticFeatureGenerator()),
    hydFeatureGenerator(new HydrophobicFeatureGenerator())
{
	featureFuncMap[FeatureType::HYDROPHOBIC] = boost::bind(&HydrophobicFeatureGenerator::generate, hydFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::AROMATIC] = boost::bind(&AromaticFeatureGenerator::generate, arFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::NEG_IONIZABLE] = boost::bind(&PatternBasedFeatureGenerator::generate, niFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::POS_IONIZABLE] = boost::bind(&PatternBasedFeatureGenerator::generate, piFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::H_BOND_DONOR] = boost::bind(&PatternBasedFeatureGenerator::generate, hbdFeatureGenerator, _1, _2);
	featureFuncMap[FeatureType::H_BOND_ACCEPTOR] = boost::bind(&PatternBasedFeatureGenerator::generate, hbaFeatureGenerator, _1, _2);

	enabledFeatures.insert(FeatureType::HYDROPHOBIC);
	enabledFeatures.insert(FeatureType::AROMATIC);
	enabledFeatures.insert(FeatureType::NEG_IONIZABLE);
	enabledFeatures.insert(FeatureType::POS_IONIZABLE);
	enabledFeatures.insert(FeatureType::H_BOND_DONOR);
	enabledFeatures.insert(FeatureType::H_BOND_ACCEPTOR);
}
	
Chem::PharmacophoreGenerator::~PharmacophoreGenerator() {}

void Chem::PharmacophoreGenerator::enableFeature(unsigned int ftr_type, bool enable)
{
	if (enable)
		enabledFeatures.insert(ftr_type);
	else
		enabledFeatures.erase(ftr_type);
}

bool Chem::PharmacophoreGenerator::isFeatureEnabled(unsigned int ftr_type) const
{
	return (enabledFeatures.find(ftr_type) != enabledFeatures.end());
}

void Chem::PharmacophoreGenerator::clearEnabledFeatures()
{
	enabledFeatures.clear();
}

void Chem::PharmacophoreGenerator::setFeatureFunction(unsigned int ftr_type, const FeatureFunction& func)
{
	FeatureFunctionMap::iterator it = featureFuncMap.find(ftr_type);

	if (it == featureFuncMap.end())
		featureFuncMap.insert(FeatureFunctionMap::value_type(ftr_type, func));
	else
		it->second = func;
}

const Chem::PharmacophoreGenerator::FeatureFunction& Chem::PharmacophoreGenerator::getFeatureFunction(unsigned int ftr_type) const
{
	static const FeatureFunction DEF_FUNC;

	FeatureFunctionMap::const_iterator it = featureFuncMap.find(ftr_type);

	return (it == featureFuncMap.end() ? DEF_FUNC : it->second);
}

void Chem::PharmacophoreGenerator::generate(const MolecularGraph& molgraph, Pharmacophore& pharm)
{
	for (FeatureFunctionMap::const_iterator it = featureFuncMap.begin(), end = featureFuncMap.end(); it != end; ++it)
		if (isFeatureEnabled(it->first))
			it->second(molgraph, pharm);
}
