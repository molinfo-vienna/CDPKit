/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94StretchBendInteractionParameterizer.cpp 
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

#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "CDPL/ForceField/MMFF94StretchBendInteractionParameterizer.hpp"
#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


namespace
{

	const unsigned int FALLBACK_ATOM_TYPE = 1;
}


ForceField::MMFF94StretchBendInteractionParameterizer::MMFF94StretchBendInteractionParameterizer(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionData& bs_ia_data, 
																								 const MMFF94AngleBendingInteractionData& ab_ia_data, MMFF94StretchBendInteractionData& ia_data,
																								 bool strict):
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), paramTable(MMFF94StretchBendParameterTable::get()), 
	defParamTable(MMFF94DefaultStretchBendParameterTable::get()), typePropTable(MMFF94AtomTypePropertyTable::get())
{
	parameterize(molgraph, bs_ia_data, ab_ia_data, ia_data, strict);
}

ForceField::MMFF94StretchBendInteractionParameterizer::MMFF94StretchBendInteractionParameterizer() :
	filterFunc(), atomTypeFunc(&getMMFF94NumericType), paramTable(MMFF94StretchBendParameterTable::get()), 
	defParamTable(MMFF94DefaultStretchBendParameterTable::get()), typePropTable(MMFF94AtomTypePropertyTable::get())
{}

void ForceField::MMFF94StretchBendInteractionParameterizer::setFilterFunction(const InteractionFilterFunction3& func)
{
	filterFunc = func;
}

void ForceField::MMFF94StretchBendInteractionParameterizer::setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func)
{
	atomTypeFunc = func;
}

void ForceField::MMFF94StretchBendInteractionParameterizer::setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table)
{
	paramTable = table;
}

void ForceField::MMFF94StretchBendInteractionParameterizer::setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table)
{
	defParamTable = table;
}

void ForceField::MMFF94StretchBendInteractionParameterizer::setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table)
{
	typePropTable = table;
}

void ForceField::MMFF94StretchBendInteractionParameterizer::parameterize(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionData& bs_ia_data, 
																		 const MMFF94AngleBendingInteractionData& ab_ia_data, MMFF94StretchBendInteractionData& ia_data, 
																		 bool strict)
{
	using namespace Chem;

	ia_data.clear();
	initBondStretchingParamLookupTable(bs_ia_data);

	for (MMFF94AngleBendingInteractionData::ConstElementIterator it = ab_ia_data.getElementsBegin(), end = ab_ia_data.getElementsEnd(); it != end; ++it) {
		const MMFF94AngleBendingInteraction& ab_int = *it;

		if (ab_int.isLinearAngle())
			continue;

		std::size_t ctr_atom_idx = ab_int.getCenterAtomIndex();
		std::size_t term_atom1_idx = ab_int.getTerminalAtom1Index();
		std::size_t term_atom2_idx = ab_int.getTerminalAtom2Index();
		
		const Atom& ctr_atom = molgraph.getAtom(ctr_atom_idx);
		const Atom& term_atom1 = molgraph.getAtom(term_atom1_idx);
		const Atom& term_atom2 = molgraph.getAtom(term_atom2_idx);

		if (filterFunc && !filterFunc(term_atom1, ctr_atom, term_atom2))
			continue;

		double ref_length1 = 0.0;
		unsigned int bond_type_idx1 = 0;

		getBondStretchingParameters(ctr_atom_idx, term_atom1_idx, bond_type_idx1, ref_length1);

		double ref_length2 = 0.0;
		unsigned int bond_type_idx2 = 0;

		getBondStretchingParameters(ctr_atom_idx, term_atom2_idx, bond_type_idx2, ref_length2);

		double ijk_force_const = 0.0;
		double kji_force_const = 0.0;
		unsigned int sb_type_idx = 0;

		try {
			getStretchBendParameters(molgraph, term_atom1, ctr_atom, term_atom2, bond_type_idx1, bond_type_idx2, 
									 ab_int.getAngleTypeIndex(), sb_type_idx, ijk_force_const, kji_force_const, strict);

		} catch (const ParameterizationFailed& e) {
			if (strict)
				throw e;

			getStretchBendParameters(molgraph, term_atom1, FALLBACK_ATOM_TYPE, ctr_atom, FALLBACK_ATOM_TYPE, term_atom2, FALLBACK_ATOM_TYPE, bond_type_idx1, bond_type_idx2, 
									 ab_int.getAngleTypeIndex(), sb_type_idx, ijk_force_const, kji_force_const);
		}

		if (ijk_force_const != 0.0 || kji_force_const != 0.0)
			ia_data.addElement(MMFF94StretchBendInteraction(term_atom1_idx, ctr_atom_idx, term_atom2_idx, sb_type_idx, ab_int.getReferenceAngle(),
															ref_length1, ref_length2, ijk_force_const, kji_force_const));
	}
}
	
void ForceField::MMFF94StretchBendInteractionParameterizer::initBondStretchingParamLookupTable(const MMFF94BondStretchingInteractionData& bs_ia_data)
{
	bsParamTable.clear();

	for (MMFF94BondStretchingInteractionData::ConstElementIterator it = bs_ia_data.getElementsBegin(), end = bs_ia_data.getElementsEnd(); it != end; ++it) {
		const MMFF94BondStretchingInteraction& bs_int = *it;
		std::size_t atom1_idx = bs_int.getAtom1Index();
		std::size_t atom2_idx = bs_int.getAtom2Index();

		if (atom1_idx > atom2_idx)
			std::swap(atom1_idx, atom2_idx);

		bsParamTable.insert(BondStretchingParamLookupTable::value_type(std::make_pair(atom1_idx, atom2_idx), &bs_int));
	}
}

void ForceField::MMFF94StretchBendInteractionParameterizer::getBondStretchingParameters(std::size_t atom1_idx, std::size_t atom2_idx,
																						unsigned int& bond_type_idx, double& ref_length) const
{
	if (atom1_idx > atom2_idx)
		std::swap(atom1_idx, atom2_idx);

	BondStretchingParamLookupTable::const_iterator it = bsParamTable.find(std::make_pair(atom1_idx, atom2_idx));

	if (it == bsParamTable.end())
		throw ParameterizationFailed("MMFF94StretchBendInteractionParameterizer: could not find MMFF94 bond stretching parameters for bond #" + 
									 boost::lexical_cast<std::string>(atom1_idx) + "-#" + boost::lexical_cast<std::string>(atom2_idx));

	bond_type_idx = it->second->getBondTypeIndex();
	ref_length = it->second->getReferenceLength();
}

void ForceField::MMFF94StretchBendInteractionParameterizer::getStretchBendParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom, 
																					 const Chem::Atom& term_atom2, unsigned int bond_type_idx1, unsigned int bond_type_idx2,
																					 unsigned int angle_type_idx, unsigned int& sb_type_idx, double& ijk_force_const, double& kji_force_const, bool strict) const
{
	unsigned int ctr_atom_type = atomTypeFunc(ctr_atom);
	unsigned int term_atom1_type = atomTypeFunc(term_atom1);
	unsigned int term_atom2_type = atomTypeFunc(term_atom2);

	if (!strict) {
		if (ctr_atom_type == 0)
			ctr_atom_type = FALLBACK_ATOM_TYPE;

		if (term_atom1_type == 0)
			term_atom1_type = FALLBACK_ATOM_TYPE;

		if (term_atom2_type == 0)
			term_atom2_type = FALLBACK_ATOM_TYPE;
	}

	getStretchBendParameters(molgraph, term_atom1, term_atom1_type, ctr_atom, ctr_atom_type, term_atom2, term_atom2_type, bond_type_idx1, bond_type_idx2, 
							 angle_type_idx, sb_type_idx, ijk_force_const, kji_force_const);
}

void ForceField::MMFF94StretchBendInteractionParameterizer::getStretchBendParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, unsigned int term_atom1_type, const Chem::Atom& ctr_atom, unsigned int ctr_atom_type, 
																					 const Chem::Atom& term_atom2, unsigned int term_atom2_type, unsigned int bond_type_idx1, unsigned int bond_type_idx2,
																					 unsigned int angle_type_idx, unsigned int& sb_type_idx, double& ijk_force_const, double& kji_force_const) const
{
	typedef MMFF94StretchBendParameterTable::Entry ParamEntry;
	typedef MMFF94DefaultStretchBendParameterTable::Entry DefParamEntry;

	if (term_atom1_type > term_atom2_type)
		sb_type_idx = getStretchBendTypeIndex(term_atom1_type == term_atom2_type, bond_type_idx2, bond_type_idx1, angle_type_idx);
	else
		sb_type_idx = getStretchBendTypeIndex(term_atom1_type == term_atom2_type, bond_type_idx1, bond_type_idx2, angle_type_idx);

	const ParamEntry& param_entry = paramTable->getEntry(sb_type_idx, term_atom1_type, ctr_atom_type, term_atom2_type);

	if (param_entry) {
		ijk_force_const = param_entry.getIJKForceConstant();
		kji_force_const = param_entry.getKJIForceConstant();

		if ((term_atom1_type == term_atom2_type && ijk_force_const != kji_force_const && bond_type_idx1 < bond_type_idx2) ||
			(term_atom1_type != param_entry.getTerminalAtom1Type()))
			std::swap(ijk_force_const, kji_force_const);

		return;
	}

	// Fallback

	unsigned int ctr_atom_pte_row = getPTERow(molgraph, ctr_atom, ctr_atom_type);
	unsigned int term_atom1_pte_row = getPTERow(molgraph, term_atom1, term_atom1_type);
	unsigned int term_atom2_pte_row = getPTERow(molgraph, term_atom2, term_atom2_type);

	const DefParamEntry& def_param_entry = defParamTable->getEntry(term_atom1_pte_row, ctr_atom_pte_row, term_atom2_pte_row);

	if (!def_param_entry) 
		throw ParameterizationFailed("MMFF94StretchBendInteractionParameterizer: could not find MMFF94 default stretch-bend parameters for interaction #" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom1)) + "-#" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(ctr_atom)) + "-#" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(term_atom2)));

	ijk_force_const = def_param_entry.getIJKForceConstant();
	kji_force_const = def_param_entry.getKJIForceConstant();

	if (term_atom1_pte_row != def_param_entry.getTerminalAtom1PTERow())
		std::swap(ijk_force_const, kji_force_const);
}

unsigned int ForceField::MMFF94StretchBendInteractionParameterizer::getStretchBendTypeIndex(bool symmetric, unsigned int bond_type_idx1, unsigned int bond_type_idx2, 
																							unsigned int angle_type_idx) const
{
	switch (angle_type_idx) {

		case 0:
			return 0;

		case 1:
			return (symmetric || bond_type_idx1 == 1 ? 1 : 2);

		case 2:
			return 3;

		case 3:
			return 5;

		case 4:
			return 4;

		case 5:
			return (symmetric || bond_type_idx1 == 1 ? 6 : 7);

		case 6:
			return 8;

		case 7:
			return (symmetric || bond_type_idx1 == 1 ? 9 : 10);

		case 8:
			return 11;

		default:
			return 12;
    }
}

unsigned int ForceField::MMFF94StretchBendInteractionParameterizer::getPTERow(const Chem::MolecularGraph& molgraph, const Chem::Atom& atom, unsigned int atom_type) const
{
	using namespace Chem;

	typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

	const AtomTypePropEntry& prop_entry = typePropTable->getEntry(atom_type);

	if (!prop_entry)
		throw ParameterizationFailed("MMFF94StretchBendInteractionParameterizer: could not find MMFF94 atom type properties for atom #" + 
									 boost::lexical_cast<std::string>(molgraph.getAtomIndex(atom)));

	unsigned int atomic_no = prop_entry.getAtomicNumber();

	if (atomic_no <= AtomType::He)
		return 0;

	if (atomic_no <= AtomType::Ne)
		return 1;

	if (atomic_no <= AtomType::Ar)
		return 2;

	if (atomic_no <= AtomType::Kr)
		return 3;

	if (atomic_no <= AtomType::Xe)
		return 4;

	if (atomic_no <= AtomType::Rn)
		return 5;

	throw ParameterizationFailed("MMFF94StretchBendInteractionParameterizer: could not deduce PTE row for atom #" + 
								 boost::lexical_cast<std::string>(molgraph.getAtomIndex(atom)));
	return 0;
}
