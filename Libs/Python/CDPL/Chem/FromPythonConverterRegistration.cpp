/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonConverterRegistration.cpp 
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


#include <boost/function.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/AtomMapping.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MassComposition.hpp"
#include "CDPL/Chem/ElementHistogram.hpp"
#include "CDPL/Chem/PathFingerprintGenerator.hpp"
#include "CDPL/Chem/CircularFingerprintGenerator.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/AtomConformer3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/AtomArray3DCoordinatesFunctor.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Chem/GeneralizedBellAtomDensity.hpp"
#include "CDPL/Chem/AtomDensityGridCalculator.hpp"

#include "Base/GenericVariantFromPythonConverter.hpp"
#include "Base/GenericFromPythonConverter.hpp"

#include "ConverterRegistration.hpp"


void CDPLPythonChem::registerFromPythonConverters()
{
	using namespace CDPL;

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MatchConstraintList::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MolecularGraph::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::FragmentList::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::Fragment::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::AtomMapping::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::Molecule::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::Reaction::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MatchExpression<Chem::Atom>::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MatchExpression<Chem::Bond>::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MatchExpression<Chem::Molecule>::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MatchExpression<Chem::Reaction>::SharedPointer>();
	
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::StringDataBlock::SharedPointer>();

	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::MassComposition::SharedPointer>();
	CDPLPythonBase::GenericVariantFromPythonConverter<Chem::ElementHistogram::SharedPointer>();

	CDPLPythonBase::GenericFromPythonConverter<Chem::PathFingerprintGenerator::DefAtomDescriptorFunctor,
											   Chem::PathFingerprintGenerator::AtomDescriptorFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::PathFingerprintGenerator::DefBondDescriptorFunctor,
											   Chem::PathFingerprintGenerator::BondDescriptorFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::CircularFingerprintGenerator::DefAtomIdentifierFunctor,
											   Chem::CircularFingerprintGenerator::AtomIdentifierFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::CircularFingerprintGenerator::DefBondIdentifierFunctor,
											   Chem::CircularFingerprintGenerator::BondIdentifierFunction>();

	CDPLPythonBase::GenericFromPythonConverter<Chem::Atom3DCoordinatesFunctor,
											   Chem::Atom3DCoordinatesFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::AtomConformer3DCoordinatesFunctor, 
											   Chem::Atom3DCoordinatesFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::AtomArray3DCoordinatesFunctor, 
											   Chem::Atom3DCoordinatesFunction>();

	CDPLPythonBase::GenericFromPythonConverter<Chem::HashCodeCalculator::DefAtomHashSeedFunctor,
											   Chem::HashCodeCalculator::AtomHashSeedFunction>();
	CDPLPythonBase::GenericFromPythonConverter<Chem::HashCodeCalculator::DefBondHashSeedFunctor,
											   Chem::HashCodeCalculator::BondHashSeedFunction>();

	CDPLPythonBase::GenericFromPythonConverter<Chem::GeneralizedBellAtomDensity, 
											   Chem::AtomDensityGridCalculator::DensityFunction>();
}
