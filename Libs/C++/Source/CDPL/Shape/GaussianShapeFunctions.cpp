/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeFunctions.cpp 
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

#include "CDPL/Shape/GaussianShapeFunctions.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"

#include "Utilities.hpp"


using namespace CDPL;


void Shape::generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape,
								  bool append, double radius, bool inc_h, double p)
{
	generateGaussianShape(atoms, shape, &Chem::get3DCoordinates, append, radius, inc_h, p);
}

void Shape::generateGaussianShape(const Chem::AtomContainer& atoms, GaussianShape& shape, const Chem::Atom3DCoordinatesFunction& coords_func,
								  bool append, double radius, bool inc_h, double p)
{
	using namespace Chem;

	if (!append)
		shape.clear();

	if (p <= 0.0) // sanity check
		p = 2.7;
	
	for (AtomContainer::ConstAtomIterator it = atoms.getAtomsBegin(), end = atoms.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		unsigned int atom_type = getType(atom);
		
		if (!inc_h && atom_type == AtomType::H)
			continue;

		if (radius > 0.0)
			shape.addElement(coords_func(atom), radius, 0, p);

		else {
			double r = AtomDictionary::getVdWRadius(atom_type);

			if (r > 0.0)  // sanity check
				shape.addElement(coords_func(atom), r, 0, p);
			else
				shape.addElement(coords_func(atom), 1.0, 0, p);
		}
	}
}

void Shape::generateGaussianShape(const Pharm::FeatureContainer& features, GaussianShape& shape,
								  bool append, double radius, bool inc_xv, double p)
{
	using namespace Pharm;

	if (!append)
		shape.clear();

	if (p <= 0.0) // sanity check
		p = 5.0;
	
	for (FeatureContainer::ConstFeatureIterator it = features.getFeaturesBegin(), end = features.getFeaturesEnd(); it != end; ++it) {
		const Feature& feature = *it;
		unsigned int feature_type = getType(feature);
		
		if (!inc_xv && feature_type == FeatureType::X_VOLUME)
			continue;

		if (radius > 0.0)
			shape.addElement(get3DCoordinates(feature), radius, feature_type + 1, p);

		else {
			double r = getTolerance(feature);

			if (r > 0.0)  // sanity check
				shape.addElement(get3DCoordinates(feature), r, feature_type + 1, p);
			else
				shape.addElement(get3DCoordinates(feature), 1.0, feature_type + 1, p);
		}
	}
}

void Shape::transform(GaussianShape& shape, const Math::Matrix4D& xform)
{
	Math::Vector3D xf_pos;
	Math::Vector3D::Pointer xf_pos_data = xf_pos.getData();
	Math::Matrix4D::ConstArrayPointer xform_data = xform.getData();
	
	for (GaussianShape::ElementIterator it = shape.getElementsBegin(), end = shape.getElementsEnd(); it != end; ++it) {
		GaussianShape::Element& elem = *it;

		transform(xf_pos_data, xform_data, elem.getPosition().getData());
		elem.setPosition(xf_pos);
	}
}

unsigned int Shape::centerAndAlignPrincipalAxes(GaussianShape& shape, const GaussianShapeFunction& func, Math::Matrix4D& back_xform, 
												double mom_eq_thresh)
{
	Math::Matrix4D to_ctr_xform;
	unsigned int sym_class = calcCenterAlignmentTransforms(func, to_ctr_xform, back_xform, mom_eq_thresh);

	if (sym_class == SymmetryClass::UNDEF)
		return SymmetryClass::UNDEF;

	transform(shape, to_ctr_xform);
	
	return sym_class;
}
