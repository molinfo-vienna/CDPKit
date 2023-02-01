/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2DataWriter.cpp 
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

#include <ostream>
#include <locale>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "MOL2DataWriter.hpp"
#include "MOL2FormatData.hpp"


using namespace CDPL;


namespace
{

	typedef boost::unordered_map<unsigned int, std::string> TypeToStringMap;

	TypeToStringMap moleculeTypeToStringMap;
	TypeToStringMap chargeTypeToStringMap;

	struct Init {

		Init() {
			using namespace Chem;
			using namespace MOL2;

			for (std::size_t i = 0; i < sizeof(MOLECULE_TYPE_STRINGS) / sizeof(TypeToString); i++)
				moleculeTypeToStringMap.insert(TypeToStringMap::value_type(MOLECULE_TYPE_STRINGS[i].type, MOLECULE_TYPE_STRINGS[i].string));
	
			for (std::size_t i = 0; i < sizeof(CHARGE_TYPE_STRINGS) / sizeof(TypeToString); i++)
				chargeTypeToStringMap.insert(TypeToStringMap::value_type(CHARGE_TYPE_STRINGS[i].type, CHARGE_TYPE_STRINGS[i].string));
		}

	} init;

	struct IsLineContMarker {

		bool operator()(const char c) const {
			return (c == Chem::MOL2::LINE_CONT_MARKER);
		}
	};

	bool containsWhitespace(const std::string& str)
	{
		return (std::find_if(str.begin(), str.end(), Internal::IsWhitespace()) != str.end());
	}

	void removeWhitespace(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), Internal::IsWhitespace()), str.end());
	}
}


bool Chem::MOL2DataWriter::writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph)
{
	init(os);

	std::size_t num_confs = (multiConfExport ? getNumConformations(molgraph) : 0);

	if (num_confs == 0) {
		multiConfExport = false;

		getAtomCoordsDim(molgraph);

		writeMoleculeRecord(os, molgraph);
		writeAtomSection(os, molgraph);
		writeBondSection(os, molgraph);
		writeSubstructSection(os);

	} else {
		coordsDim = 3;

		Util::DArray::SharedPointer conf_energies;

		if (writeConfEnergyComment && hasConformerEnergies(molgraph))
			conf_energies = getConformerEnergies(molgraph);

		for (std::size_t i = 0; i < num_confs; i++) {
			getConformation(molgraph, i, confCoordinates, false);

			writeMoleculeRecord(os, molgraph, i);

			if (writeConfEnergyComment && conf_energies && conf_energies->getSize() > i)
				writeConformerEnergyComment(os, (*conf_energies)[i]);

			writeAtomSection(os, molgraph);
			writeBondSection(os, molgraph);
			writeSubstructSection(os);
		}
	}

	return os.good();
}

void Chem::MOL2DataWriter::init(std::ostream& os)
{
	os.imbue(std::locale::classic());

	strictErrorChecking    = getStrictErrorCheckingParameter(ioBase);
	multiConfExport        = getMultiConfExportParameter(ioBase);
	extendedAtomTypes      = getMOL2EnableExtendedAtomTypesParameter(ioBase);
	aromaticBondTypes      = getMOL2EnableAromaticBondTypesParameter(ioBase);
	atomChargeType         = getMOL2ChargeTypeParameter(ioBase);
	moleculeType           = getMOL2MoleculeTypeParameter(ioBase);
	outputSubstructs       = getMOL2OutputSubstructuresParameter(ioBase);
	writeConfEnergyComment = (multiConfExport && getOutputConfEnergyAsCommentParameter(ioBase));

	if (multiConfExport)
		confIdxSuffixPattern = getConfIndexNameSuffixPatternParameter(ioBase);

	os << std::fixed << std::showpoint;
}

void Chem::MOL2DataWriter::getAtomCoordsDim(const MolecularGraph& molgraph)
{
	coordsDim = getCoordinatesDimensionParameter(ioBase); 

	if (coordsDim == 2 || coordsDim == 3)
		return;

	if (hasCoordinates(molgraph, 3))
		coordsDim = 3;
	else if (hasCoordinates(molgraph, 2))
		coordsDim = 2;
	else 
		coordsDim = 0;
}

void Chem::MOL2DataWriter::initSubstructureData(const MolecularGraph& molgraph)
{
	substructData.clear();

	if (!outputSubstructs)
		return;

	substructNamesToIDs.clear();
	atomsToSubstructIDs.clear();

	SubstructData data;
	std::size_t atom_id = 1;

	for (MolecularGraph::ConstAtomIterator a_it = molgraph.getAtomsBegin(), a_end = molgraph.getAtomsEnd(); a_it != a_end; ++a_it, atom_id++) {
		const Atom& atom = *a_it;

		if (!hasMOL2SubstructureName(atom))
			continue;

		data.name = getMOL2SubstructureName(atom);
		removeWhitespace(data.name);

		if (data.name.empty())
			continue;

		StringToSizeMap::const_iterator s_it = substructNamesToIDs.find(data.name);

		if (s_it != substructNamesToIDs.end()) {
			atomsToSubstructIDs.insert(AtomToIDMap::value_type(&atom, s_it->second));
			continue;
		}

		data.rootAtom = atom_id;

		if (hasMOL2SubstructureSubtype(atom)) {
			data.subtype = getMOL2SubstructureSubtype(atom);
			removeWhitespace(data.subtype);

		} else
			data.subtype.clear();

		if (hasMOL2SubstructureChain(atom)) {
			data.chain = getMOL2SubstructureChain(atom);
			removeWhitespace(data.chain);

		} else
			data.chain.clear();

		substructData.push_back(data);
		substructNamesToIDs.insert(StringToSizeMap::value_type(data.name, substructData.size()));
		atomsToSubstructIDs.insert(AtomToIDMap::value_type(&atom, substructData.size()));
	}  
}

void Chem::MOL2DataWriter::writeMoleculeRecord(std::ostream& os, const MolecularGraph& molgraph, std::size_t conf_idx)
{
	initSubstructureData(molgraph);

	os << MOL2::MOLECULE_RTI << MOL2::END_OF_LINE;

	const std::string& name_prop = getName(molgraph);

	if (!name_prop.empty()) {
		if (name_prop[name_prop.length() - 1] == MOL2::LINE_CONT_MARKER) {
			std::string new_name = name_prop;

			boost::trim_right_if(new_name, IsLineContMarker());

			os << new_name;

		} else
			os << name_prop;
	}

	if (multiConfExport && !confIdxSuffixPattern.empty()) {
		std::string suffix = boost::replace_all_copy(confIdxSuffixPattern, "%I%", boost::lexical_cast<std::string>(conf_idx));

		if (suffix != confIdxSuffixPattern) 
			os << suffix;
	}

	os << MOL2::END_OF_LINE;
	os << molgraph.getNumAtoms() << ' ' << getCompleteBondCount(molgraph) << ' ' << substructData.size() << " 0 0" << MOL2::END_OF_LINE;
	os << getMoleculeTypeString(molgraph) << MOL2::END_OF_LINE;
	os << getChargeTypeString(molgraph) << MOL2::END_OF_LINE;
	os << MOL2::END_OF_LINE;
	os << MOL2::END_OF_LINE;
}

void Chem::MOL2DataWriter::writeConformerEnergyComment(std::ostream& os, double energy)
{
	os << MOL2::COMMENT_RTI << MOL2::END_OF_LINE;
	os << energy << MOL2::END_OF_LINE;
}

void Chem::MOL2DataWriter::writeAtomSection(std::ostream& os, const MolecularGraph& molgraph)
{
	atomSymbolCounts.clear();

	os << MOL2::ATOM_RTI << MOL2::END_OF_LINE;

	std::size_t num_atoms = molgraph.getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = molgraph.getAtom(i);

		os << (i + 1) << '\t' << getAtomName(atom) << '\t';

		if (coordsDim == 3) {
			const Math::Vector3D& coords = (multiConfExport ? confCoordinates[i] : get3DCoordinates(atom));

			os << coords[0] << '\t' << coords[1] << '\t' << coords[2];

		} else if (coordsDim == 2) {
			const Math::Vector2D& coords = get2DCoordinates(atom);

			os << coords[0] << '\t' << coords[1] << "\t0.0";

		} else 
			os << "0.0\t0.0\t0.0";

		os << '\t' << getAtomTypeString(atom, molgraph);

		if (atomChargeType != MOL2ChargeType::NO_CHARGES || outputSubstructs) {
			if (outputSubstructs) {

				AtomToIDMap::const_iterator it = atomsToSubstructIDs.find(&atom);

				if (it == atomsToSubstructIDs.end())
					os << "\t0\t" << MOL2::EMPTY_STRING_FIELD;
				else
					os << '\t' << it->second << '\t' << substructData[it->second - 1].name;

			} else
				os << "\t0\t" << MOL2::EMPTY_STRING_FIELD;

			if (atomChargeType != MOL2ChargeType::NO_CHARGES)
				os << '\t' << getMOL2Charge(atom);
		}

		os << MOL2::END_OF_LINE;
	}
}

void Chem::MOL2DataWriter::writeBondSection(std::ostream& os, const MolecularGraph& molgraph) const
{
	os << MOL2::BOND_RTI << MOL2::END_OF_LINE;

	std::size_t num_bonds = molgraph.getNumBonds();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);
		const Atom& atom1 = bond.getBegin();

		if (!molgraph.containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom2))
			continue;
		
		os << (i + 1) << '\t' << (molgraph.getAtomIndex(atom1) + 1) << '\t' << (molgraph.getAtomIndex(atom2) + 1); 
		os << '\t' << getBondTypeString(bond, molgraph) << MOL2::END_OF_LINE;
	}
}

void Chem::MOL2DataWriter::writeSubstructSection(std::ostream& os) const
{
	if (!outputSubstructs || substructData.empty())
		return;

	os << MOL2::SUBSTRUCTURE_RTI << MOL2::END_OF_LINE;

	std::size_t num_substructs = substructData.size();

	for (std::size_t i = 0; i < num_substructs; i++) {
		os << (i + 1) << '\t' << substructData[i].name << '\t' << substructData[i].rootAtom;

		if (!substructData[i].subtype.empty() || !substructData[i].chain.empty()) {
			os << "\tRESIDUE\t1\t" << (!substructData[i].chain.empty() ? substructData[i].chain : MOL2::EMPTY_STRING_FIELD);

			if (!substructData[i].subtype.empty())
				os << '\t' << substructData[i].subtype;
		}

		os << MOL2::END_OF_LINE;
	}
}

const std::string& Chem::MOL2DataWriter::getMoleculeTypeString(const MolecularGraph& molgraph) const
{
	unsigned int mol_type = moleculeType;

	if (hasMOL2MoleculeType(molgraph))
		mol_type = getMOL2MoleculeType(molgraph);

	TypeToStringMap::const_iterator it = moleculeTypeToStringMap.find(mol_type);

	if (it == moleculeTypeToStringMap.end()) {
		if (strictErrorChecking)
			throw Base::IOError("MOL2DataWriter: invalid MOL2 molecule type");

		return moleculeTypeToStringMap[MOL2MoleculeType::SMALL];
	}

	return it->second;
}

const std::string& Chem::MOL2DataWriter::getChargeTypeString(const MolecularGraph& molgraph)
{
	if (hasMOL2ChargeType(molgraph))
		atomChargeType = getMOL2ChargeType(molgraph);

	TypeToStringMap::const_iterator it = chargeTypeToStringMap.find(atomChargeType);

	if (it == chargeTypeToStringMap.end()) {
		if (strictErrorChecking)
			throw Base::IOError("MOL2DataWriter: invalid MOL2 charge type");

		atomChargeType = MOL2ChargeType::NO_CHARGES;

		return chargeTypeToStringMap[MOL2ChargeType::NO_CHARGES];
	}

	return it->second;
}

std::string Chem::MOL2DataWriter::getAtomName(const Atom& atom)
{
	std::string name;

	if (hasMOL2Name(atom)) {
		name = getMOL2Name(atom);

	} else {
		name = getSymbol(atom);

		boost::to_upper(name);
		name.append(boost::lexical_cast<std::string>(++atomSymbolCounts[name]));
	}

	removeWhitespace(name);

	if (name.empty())
		return MOL2::EMPTY_STRING_FIELD;

	return name;
}

const std::string& Chem::MOL2DataWriter::getAtomTypeString(const Atom& atom, const MolecularGraph& molgraph) const
{
	unsigned int type;

	if (hasSybylType(atom))
		type = getSybylType(atom);
	else
		type = perceiveSybylType(atom, molgraph);

	if (type > SybylAtomType::MAX_TYPE && strictErrorChecking)
		throw Base::IOError("MOL2DataWriter: invalid Sybyl atom type");

	if (!extendedAtomTypes && type > SybylAtomType::MAX_DEFAULT_TYPE) {
		if (strictErrorChecking)
			throw Base::IOError("MOL2DataWriter: unable to specify atom type");

		return getSybylAtomTypeString(SybylAtomType::Any);
	}
	
	const std::string& type_str = getSybylAtomTypeString(type);

	if (!type_str.empty())
		return type_str;

    if (extendedAtomTypes) {
		const std::string& symbol = getSymbol(atom);

		if (!symbol.empty() && !containsWhitespace(symbol))
			return symbol;
	}

	if (strictErrorChecking)
		throw Base::IOError("MOL2DataWriter: unable to specify atom type");

	return getSybylAtomTypeString(SybylAtomType::Any);
}

const std::string& Chem::MOL2DataWriter::getBondTypeString(const Bond& bond, const MolecularGraph& molgraph) const
{
	unsigned int type;

	if (hasSybylType(bond))
		type = getSybylType(bond);
	else
		type = perceiveSybylType(bond, molgraph);

	if (type == SybylBondType::AROMATIC && !aromaticBondTypes)
		return getBondOrderString(bond);

	const std::string& type_str = getSybylBondTypeString(type);

	if (!type_str.empty())
		return type_str;

	if (strictErrorChecking)
		throw Base::IOError("MOL2DataWriter: invalid Sybyl bond type");

	return getBondOrderString(bond);
}

const std::string& Chem::MOL2DataWriter::getBondOrderString(const Bond& bond) const
{
	switch (getOrder(bond)) {

		case 1:
			return getSybylBondTypeString(SybylBondType::SINGLE);

		case 2:
			return getSybylBondTypeString(SybylBondType::DOUBLE);

		case 3:
			return getSybylBondTypeString(SybylBondType::TRIPLE);

		default:
			if (strictErrorChecking)
				throw Base::IOError("MOL2DataWriter: invalid bond order");

			return getSybylBondTypeString(SybylBondType::UNKNOWN);
	}
}
