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
#include "CDPL/Chem/Atom3DCoordinatesFunctionWrapper.hpp"
#include "CDPL/Chem/GeneralizedBellAtomDensity.hpp"
#include "CDPL/Chem/AtomDensityGridCalculator.hpp"
#include "CDPL/Chem/PatternBasedTautomerizationRule.hpp"

#include "Base/GenericVariantFromPythonConverter.hpp"
#include "Base/GenericFromPythonConverter.hpp"

#include "ConverterRegistration.hpp"


namespace
{

	struct BondOrderChangeFromPySequenceConverter 
	{

		BondOrderChangeFromPySequenceConverter() {
			using namespace boost;

			python::converter::registry::insert(&convertible, &construct, 
												python::type_id<CDPL::Chem::PatternBasedTautomerizationRule::BondOrderChange>());
		}

		static void* convertible(PyObject* obj_ptr) {
			using namespace boost;

			if (!obj_ptr)
				return 0;

			if (!PyList_Check(obj_ptr) && !PyTuple_Check(obj_ptr))
				return 0;

			python::ssize_t size = PySequence_Size(obj_ptr);

			if (size < 3)
				return 0;

			if (!python::extract<std::size_t>(PySequence_GetItem(obj_ptr, 0)).check())
				return 0;

			if (!python::extract<std::size_t>(PySequence_GetItem(obj_ptr, 1)).check())
				return 0;

			if (!python::extract<long>(PySequence_GetItem(obj_ptr, 2)).check())
				return 0;

			return obj_ptr;
		}

		static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data) {
			using namespace boost;
			using namespace CDPL;
			using namespace Chem;

			void* storage = ((python::converter::rvalue_from_python_storage<PatternBasedTautomerizationRule::BondOrderChange>*)data)->storage.bytes;

			new (storage) PatternBasedTautomerizationRule::BondOrderChange();

			static_cast<PatternBasedTautomerizationRule::BondOrderChange*>(storage)->atom1ID = python::extract<std::size_t>(PySequence_GetItem(obj_ptr, 0))();
			static_cast<PatternBasedTautomerizationRule::BondOrderChange*>(storage)->atom2ID = python::extract<std::size_t>(PySequence_GetItem(obj_ptr, 1))();
			static_cast<PatternBasedTautomerizationRule::BondOrderChange*>(storage)->orderChange = python::extract<long>(PySequence_GetItem(obj_ptr, 2))();

			data->convertible = storage;
		}
	};
}


void CDPLPythonChem::registerFromPythonConverters()
{
	using namespace CDPL;

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MatchConstraintList::SharedPointer&>();

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MolecularGraph::SharedPointer&>();

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::FragmentList::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::Fragment::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::AtomMapping::SharedPointer&>();

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::Molecule::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::Reaction::SharedPointer&>();

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MatchExpression<Chem::Atom>::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MatchExpression<Chem::Bond>::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MatchExpression<Chem::Molecule>::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MatchExpression<Chem::Reaction>::SharedPointer&>();
	
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::StringDataBlock::SharedPointer&>();

	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::MassComposition::SharedPointer&>();
	CDPLPythonBase::GenericVariantFromPythonConverter<const Chem::ElementHistogram::SharedPointer&>();

	CDPLPythonBase::GenericFromPythonConverter<const Chem::PathFingerprintGenerator::DefAtomDescriptorFunctor&,
											   Chem::PathFingerprintGenerator::AtomDescriptorFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::PathFingerprintGenerator::DefBondDescriptorFunctor&,
											   Chem::PathFingerprintGenerator::BondDescriptorFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::CircularFingerprintGenerator::DefAtomIdentifierFunctor&,
											   Chem::CircularFingerprintGenerator::AtomIdentifierFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::CircularFingerprintGenerator::DefBondIdentifierFunctor&,
											   Chem::CircularFingerprintGenerator::BondIdentifierFunction>();

	CDPLPythonBase::GenericFromPythonConverter<const Chem::Atom3DCoordinatesFunctor&,
											   Chem::Atom3DCoordinatesFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::AtomConformer3DCoordinatesFunctor&, 
											   Chem::Atom3DCoordinatesFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::AtomArray3DCoordinatesFunctor&, 
											   Chem::Atom3DCoordinatesFunction>();

	CDPLPythonBase::GenericFromPythonConverter<const Chem::HashCodeCalculator::DefAtomHashSeedFunctor&,
											   Chem::HashCodeCalculator::AtomHashSeedFunction>();
	CDPLPythonBase::GenericFromPythonConverter<const Chem::HashCodeCalculator::DefBondHashSeedFunctor&,
											   Chem::HashCodeCalculator::BondHashSeedFunction>();

	CDPLPythonBase::GenericFromPythonConverter<const Chem::GeneralizedBellAtomDensity&, 
											   Chem::AtomDensityGridCalculator::DensityFunction>();

	BondOrderChangeFromPySequenceConverter();
}
