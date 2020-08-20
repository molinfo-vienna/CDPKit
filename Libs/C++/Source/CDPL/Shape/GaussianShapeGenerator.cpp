/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeGenerator.cpp 
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

#include "CDPL/Shape/GaussianShapeGenerator.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/AtomConformer3DCoordinatesFunctor.hpp"


using namespace CDPL;


Shape::GaussianShapeGenerator::GaussianShapeGenerator():
    defPharmGen(true), pharmGen(&defPharmGen), genMolShape(true), genPharmShape(true), 
	incHydrogens(false), multiConf(true), atomRadius(-1.0), atomHardness(2.7), 
	ftrRadius(-1.0), ftrHardness(5.0)
{}

void Shape::GaussianShapeGenerator::generatePharmacophoreShape(bool generate)
{
    genPharmShape = generate;
}

bool Shape::GaussianShapeGenerator::generatePharmacophoreShape() const
{
    return genPharmShape;
}

void Shape::GaussianShapeGenerator::generateMoleculeShape(bool generate)
{
	genMolShape = generate;
}

bool Shape::GaussianShapeGenerator::generateMoleculeShape() const
{
    return genMolShape;
}

void Shape::GaussianShapeGenerator::multiConformerMode(bool multi_conf)
{
    multiConf = multi_conf;
}

bool Shape::GaussianShapeGenerator::multiConformerMode() const
{
    return multiConf;
}

void Shape::GaussianShapeGenerator::includeHydrogens(bool include)
{
    incHydrogens = include;
}

bool Shape::GaussianShapeGenerator::includeHydrogens() const
{
    return incHydrogens;
}

void Shape::GaussianShapeGenerator::setAtomRadius(double radius)
{
    atomRadius = radius;
}

double Shape::GaussianShapeGenerator::getAtomRadius() const
{
    return atomRadius;
}

void Shape::GaussianShapeGenerator::setAtomHardness(double hardness)
{
    atomHardness = hardness;
}

double Shape::GaussianShapeGenerator::getAtomHardness()
{
    return atomHardness;
}

void Shape::GaussianShapeGenerator::setFeatureRadius(double radius)
{
    ftrRadius = radius;
}

double Shape::GaussianShapeGenerator::getFeatureRadius() const
{
    return ftrRadius;
}
	
void Shape::GaussianShapeGenerator::setFeatureHardness(double hardness)
{
    ftrHardness = hardness;
}

double Shape::GaussianShapeGenerator::getFeatureHardness()
{
    return ftrHardness;
}

void Shape::GaussianShapeGenerator::setPharmacophoreGenerator(Pharm::PharmacophoreGenerator& gen)
{
	pharmGen = &gen;
}

Pharm::PharmacophoreGenerator& Shape::GaussianShapeGenerator::getPharmacophoreGenerator() const
{
	return *pharmGen;
}

const Pharm::DefaultPharmacophoreGenerator& Shape::GaussianShapeGenerator::getDefaultPharmacophoreGenerator() const
{
    return defPharmGen;
}

Pharm::DefaultPharmacophoreGenerator& Shape::GaussianShapeGenerator::getDefaultPharmacophoreGenerator()
{
    return defPharmGen;
}

void Shape::GaussianShapeGenerator::generate(const Chem::MolecularGraph& molgraph, GaussianShapeSet& shapes, bool append)
{
	if (!genMolShape && !genPharmShape)
		return;

    if (!append)
		shapes.clear();

	std::size_t num_confs = (multiConf ? getNumConformations(molgraph) : 0);

	if (num_confs == 0) {
		GaussianShape::SharedPointer shape_ptr(new GaussianShape());

		createShape(molgraph, Chem::Atom3DCoordinatesFunctor(), *shape_ptr);
		shapes.addElement(shape_ptr);

		return;
	}

	for (std::size_t i = 0; i < num_confs; i++) {
		GaussianShape::SharedPointer shape_ptr(new GaussianShape());

		createShape(molgraph, Chem::AtomConformer3DCoordinatesFunctor(i), *shape_ptr);
		shapes.addElement(shape_ptr);
	}
}

template <typename CoordsFunc>
void Shape::GaussianShapeGenerator::createShape(const Chem::MolecularGraph& molgraph, const CoordsFunc& coords_func, GaussianShape& shape)
{
	if (genMolShape) {
		using namespace Chem;

		for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
			const Atom& atom = *it;
			unsigned int atom_type = getType(atom);
		
			if (!incHydrogens && atom_type == AtomType::H)
				continue;

			if (atomRadius > 0.0)
				shape.addElement(coords_func(atom), atomRadius, 0, atomHardness);

			else {
				double r = AtomDictionary::getVdWRadius(atom_type);

				if (r > 0.0)  // sanity check
					shape.addElement(coords_func(atom), r, 0, atomHardness);
				else
					shape.addElement(coords_func(atom), 1.0, 0, atomHardness);
			}
		}
	}

	if (genPharmShape) {
		using namespace Pharm;

		pharmGen->setAtom3DCoordinatesFunction(coords_func);
		pharmGen->generate(molgraph, pharm, false);

		for (BasicPharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); it != end; ++it) {
			const Feature& feature = *it;
			unsigned int feature_type = getType(feature);

			if (ftrRadius > 0.0)
				shape.addElement(get3DCoordinates(feature), ftrRadius, feature_type + 1, ftrHardness);

			else {
				double r = getTolerance(feature);

				if (r > 0.0)  // sanity check
					shape.addElement(get3DCoordinates(feature), ftrRadius, feature_type + 1, ftrHardness);
				else
					shape.addElement(get3DCoordinates(feature), 1.0, feature_type + 1, ftrHardness);
			}
		}
	}
}
