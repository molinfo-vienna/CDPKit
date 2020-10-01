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

		createShape(molgraph, Chem::Atom3DCoordinatesFunctor(), *shape_ptr, true);
		shapes.addElement(shape_ptr);

		return;
	}

	for (std::size_t i = 0; i < num_confs; i++) {
		GaussianShape::SharedPointer shape_ptr(new GaussianShape());

		createShape(molgraph, Chem::AtomConformer3DCoordinatesFunctor(i), *shape_ptr, i == 0);
		shapes.addElement(shape_ptr);
	}
}

template <typename CoordsFunc>
void Shape::GaussianShapeGenerator::createShape(const Chem::MolecularGraph& molgraph, const CoordsFunc& coords_func, GaussianShape& shape, bool init)
{
	using namespace Chem;

	if (genMolShape) {
		if (init) {
			atomElements.clear();

			for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
				const Atom& atom = molgraph.getAtom(i);
				unsigned int atom_type = getType(atom);
		
				if (!incHydrogens && atom_type == AtomType::H)
					continue;

				if (atomRadius > 0.0)
					atomElements.push_back(ShapeElement(i, atomRadius));

				else {
					double r = AtomDictionary::getVdWRadius(atom_type);

					if (r > 0.0)  // sanity check
						atomElements.push_back(ShapeElement(i, r));
					else
						atomElements.push_back(ShapeElement(i, 1.0));
				}
			}
		}

		for (ShapeElementArray::const_iterator it = atomElements.begin(), end = atomElements.end(); it != end; ++it) {
			const ShapeElement& shape_elem = *it;

			shape.addElement(coords_func(molgraph.getAtom(shape_elem.first)), shape_elem.second, 0, atomHardness);
		}
	}

	if (genPharmShape) {
		using namespace Pharm;

		if (init) {
			pharmGen->setAtom3DCoordinatesFunction(coords_func);
			pharmGen->generate(molgraph, pharm, false);

			ftrElements.clear();

			for (BasicPharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); it != end; ++it) {
				const Feature& feature = *it;
				unsigned int feature_type = getType(feature) + 1;

				if (ftrRadius > 0.0)
					ftrElements.push_back(ShapeElement(feature_type, ftrRadius));

				else {
					double r = getTolerance(feature);

					if (r > 0.0)  // sanity check
						ftrElements.push_back(ShapeElement(feature_type, r));
					else
						ftrElements.push_back(ShapeElement(feature_type, 1.0));
				}
			}
		}

		std::size_t i = 0;
		double ftr_pos[3];

		for (BasicPharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); it != end; ++it, i++) {
			const Feature& feature = *it;

			if (init) {
				shape.addElement(get3DCoordinates(feature), ftrElements[i].second, ftrElements[i].first, ftrHardness);
				continue;
			}

			if (!hasSubstructure(feature))
				continue;

			const Fragment& substruct = *getSubstructure(feature);
			std::size_t num_atoms = substruct.getNumAtoms();

			if (num_atoms == 0) 
				continue;

			ftr_pos[0] = 0.0;
			ftr_pos[1] = 0.0;
			ftr_pos[2] = 0.0;

			for (Fragment::ConstAtomIterator a_it = substruct.getAtomsBegin(), a_end = substruct.getAtomsEnd(); a_it != a_end; ++a_it) {
				const Math::Vector3D::ConstPointer atom_pos_data = coords_func(*a_it).getData();

				ftr_pos[0] += atom_pos_data[0];
				ftr_pos[1] += atom_pos_data[1];
				ftr_pos[2] += atom_pos_data[2];
			}

			ftr_pos[0] /= num_atoms;
			ftr_pos[1] /= num_atoms;
			ftr_pos[2] /= num_atoms;

			shape.addElement(Math::vec(ftr_pos[0], ftr_pos[1], ftr_pos[2]), ftrElements[i].second, ftrElements[i].first, ftrHardness);
		}
	}
}
