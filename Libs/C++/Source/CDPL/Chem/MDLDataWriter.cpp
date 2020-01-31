/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MDLDataWriter.cpp 
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
#include <algorithm>
#include <functional>
#include <locale>
#include <ostream>
#include <ios>
#include <iterator>
#include <limits>
#include <cassert>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/MDLParity.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/RadicalType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/MDLDataFormatVersion.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/StringUtilities.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "MDLDataWriter.hpp"
#include "MDLFormatData.hpp"


using namespace CDPL;


namespace
{

	void writeMDLEOL(std::ostream& os)
	{
		Internal::writeEOL(os, Chem::MDL::END_OF_LINE);
	}

	void writeMDLLine(std::ostream& os, const std::string& line, const char* err_msg, 
							 bool check_llen = true, bool trim = true, bool trunc = false, 
							 std::size_t max_llen = Chem::MDL::MAX_LINE_LENGTH)
	{
		Internal::writeLine(os, line, err_msg, check_llen, trim, trunc, max_llen, Chem::MDL::END_OF_LINE);
	}

	std::size_t calcHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
	{
		return (getExplicitAtomCount(atom, molgraph, Chem::AtomType::H) + calcImplicitHydrogenCount(atom, molgraph));
	}

	bool isRingBond(const Chem::Bond& bond, const Chem::MolecularGraph&)
	{
		return getRingFlag(bond);
	}

	template <typename ValueMatchPred>
	const Chem::MatchConstraint* findMatchConstraint(const Chem::MatchConstraintList& constr_list,
													 unsigned int constr_list_id, unsigned int constr_id, 
													 Chem::MatchConstraint::Relation relation,
													 const ValueMatchPred& value_match_pred)
	{
		using namespace Chem;

		if (!(constr_list.getType() == MatchConstraintList::AND_LIST || 
			  (constr_list.getType() == MatchConstraintList::OR_LIST && constr_list.getSize() == 1)))
			return 0;

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (constraint.getID() == constr_id && constraint.getRelation() == relation && value_match_pred(constraint))
				return &constraint;

			if (constraint.getID() != constr_list_id)
				continue;

			if (constraint.getRelation() != MatchConstraint::EQUAL)
				continue;

			const MatchConstraintList& constr_list = 
				*constraint.template getValue<MatchConstraintList::SharedPointer>();

			const MatchConstraint* result = findMatchConstraint(constr_list, constr_list_id, constr_id, 
																relation, value_match_pred);
			if (result)
				return result;
		}

		return 0;
	}

	template <typename ValueType, typename ObjectType, typename PropertyFunc>
	ValueType getConstraintValue(const Chem::MatchConstraint& constraint, 
								 const ObjectType& obj,
								 const PropertyFunc& prop_func)
	{
		if (constraint.hasValue())
			return constraint.template getValue<ValueType>();

		return prop_func(obj);
	}

	template <typename ValueType, typename ObjectType>
	class CalcOrSetConstraintValueMatches
	{

	public:
		typedef boost::function2<ValueType, const ObjectType&, const Chem::MolecularGraph&> PropertyFunc;

		CalcOrSetConstraintValueMatches(const ValueType& value, 
										const ObjectType& obj,
										const Chem::MolecularGraph& molgraph,
										const PropertyFunc& prop_func): 
			value(value), object(obj), molGraph(molgraph), propFunc(prop_func) {}

		bool operator()(const Chem::MatchConstraint& constraint) const {
			if (constraint.hasValue())
				return (constraint.template getValue<ValueType>() == value);
			
			return (propFunc(object, molGraph) == value);
		}
		
	private:
		const ValueType              value;
		const ObjectType&            object;
		const Chem::MolecularGraph&  molGraph;
		const PropertyFunc           propFunc;
	};

	template <typename ValueType>
	class SetConstraintValueMatches
	{

	public:
		SetConstraintValueMatches(const ValueType& value):	value(value) {}

		bool operator()(const Chem::MatchConstraint& constraint) const {
			if (!constraint.hasValue())
				return false;

			return (constraint.template getValue<ValueType>() == value);
		}
		
	private:
		const ValueType value;
	};

	struct HasUnsetConstraintValue
	{

		bool operator()(const Chem::MatchConstraint& constraint) const {
			return !constraint.hasValue();
		}
	};

	const std::size_t MAX_V3000_LINE_LENGTH = Chem::MDL::MAX_LINE_LENGTH - Chem::MDL::V3000::LINE_PREFIX.length();
}


bool Chem::MDLDataWriter::writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph, bool write_data)
{
	init(os, false);

	std::size_t num_confs = (multiConfExport ? getNumConformations(molgraph) : 0);

	if (num_confs == 0) {
		multiConfExport = false;

		getAtomCoordsDim(molgraph);

		writeMOLHeaderBlock(os, molgraph);
		writeMOLCTab(os, molgraph);
		writeMOLEndTag(os);

		if (write_data)
			writeSDFData(os, molgraph);

	} else {
		coordsDim = 3;

		Util::DArray::SharedPointer conf_energies;

		if ((writeConfEnergySDEntry || writeConfEnergyComment || writeConfEnergyField) && hasConformerEnergies(molgraph))
			conf_energies = getConformerEnergies(molgraph);

		for (std::size_t i = 0; i < num_confs; i++) {
			getConformation(molgraph, i, confCoordinates, false);

			if (conf_energies && conf_energies->getSize() > i)
				confEnergy = (*conf_energies)[i];
			else
				confEnergy = std::numeric_limits<double>::quiet_NaN();
			
			writeMOLHeaderBlock(os, molgraph);
			writeMOLCTab(os, molgraph);
			writeMOLEndTag(os);

			if (write_data)
				writeSDFData(os, molgraph);
		}
	}

	return os.good();
}

bool Chem::MDLDataWriter::writeMOLFile(std::ostream& os, const MolecularGraph& molgraph)
{
	return writeMolecularGraph(os, molgraph, false);
}

bool Chem::MDLDataWriter::writeSDFileRecord(std::ostream& os, const MolecularGraph& molgraph)
{
	return writeMolecularGraph(os, molgraph, true);
}

bool Chem::MDLDataWriter::writeRXNFile(std::ostream& os, const Reaction& rxn)
{
	init(os, true);

	setRXNFileVersion(rxn);

	writeRXNHeaderBlock(os, rxn);
	writeRXNReaction(os, rxn);

	return os.good();
}

bool Chem::MDLDataWriter::writeRDFileRecord(std::ostream& os, const Reaction& rxn)
{
	init(os, true);

	writeRDFHeaderBlock(os);
	writeRDFReaction(os, rxn);
	writeRDFData(os, rxn);

	return os.good();
}

void Chem::MDLDataWriter::init(std::ostream& os, bool rxn_mode)
{
	strictErrorChecking     = getStrictErrorCheckingParameter(ioBase); 
	bondMemberSwapStereoFix = getBondMemberSwapStereoFixParameter(ioBase); 
	trimStrings             = getMDLTrimStringsParameter(ioBase); 
	trimLines               = getMDLTrimLinesParameter(ioBase); 
	truncateStrings         = getMDLTruncateStringsParameter(ioBase); 
	truncateLines           = getMDLTruncateLinesParameter(ioBase); 
	ignoreParity            = getMDLIgnoreParityParameter(ioBase); 
	checkLineLength         = getCheckLineLengthParameter(ioBase); 
	multiConfExport         = (!rxn_mode && getMultiConfExportParameter(ioBase));
	writeConfEnergyField    = (multiConfExport && getMDLOutputConfEnergyToEnergyFieldParameter(ioBase));
	writeConfEnergySDEntry  = (multiConfExport && getMDLOutputConfEnergyAsSDEntryParameter(ioBase));
	writeConfEnergyComment  = (multiConfExport && getOutputConfEnergyAsCommentParameter(ioBase));

	if (writeConfEnergySDEntry)
		confEnergySDTag = getMDLConfEnergySDTagParameter(ioBase);

	os.imbue(std::locale::classic());
}

void Chem::MDLDataWriter::getAtomCoordsDim(const MolecularGraph& molgraph)
{
	coordsDim = getCoordinatesDimensionParameter(ioBase); 

	if (coordsDim == 2 || coordsDim == 3)
		return;

	coordsDim = getMDLDimensionality(molgraph);

	if (coordsDim == 2 || coordsDim == 3)
		return;

	if (hasCoordinates(molgraph, 3))
		coordsDim = 3;
	else if (hasCoordinates(molgraph, 2))
		coordsDim = 2;
	else 
		coordsDim = 0;
}

void Chem::MDLDataWriter::writeMOLHeaderBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile;

	// Header line 1

	const std::string& mol_name = getName(molgraph);

	writeMDLLine(os, mol_name, "MDLDataWriter: error while writing structure name to molfile header block", 
				 checkLineLength, trimLines, truncateLines);

	// Header line 2

	const std::string& user_initials = getMDLUserInitials(molgraph);

	writeString(os, 2, user_initials, "MDLDataWriter: error while writing user initials to molfile header block",
				trimStrings, truncateStrings);

	const std::string& prog_name = getMDLProgramName(molgraph);

	writeString(os, 8, prog_name, "MDLDataWriter: error while writing header block program name to molfile header block",
				trimStrings, truncateStrings);

	using namespace boost::posix_time;

	bool has_ts_prop = hasMDLTimestamp(molgraph);
	bool update_time = getMDLUpdateTimestampParameter(ioBase); 

	std::string iso_time_str;  // ISO format: YYYYMMDDTHHMMSS

	if (update_time || !has_ts_prop)
		iso_time_str = to_iso_string(second_clock::universal_time());
	else
		iso_time_str = to_iso_string(from_time_t(getMDLTimestamp(molgraph)));

	writeString(os, 2, iso_time_str.substr(4, 2), 
				"MDLDataWriter: error while writing date/timestamp month part to molfile header block");   // Month
	writeString(os, 2, iso_time_str.substr(6, 2), 
				"MDLDataWriter: error while writing date/timestamp day part to molfile header block");     // Day
	writeString(os, 2, iso_time_str.substr(2, 2), 
				"MDLDataWriter: error while writing date/timestamp year part to molfile header block");    // Year
	writeString(os, 2, iso_time_str.substr(9, 2), 
				"MDLDataWriter: error while writing date/timestamp hour part to molfile header block");    // Hour
	writeString(os, 2, iso_time_str.substr(11, 2), 
				"MDLDataWriter: error while writing date/timestamp minute part to molfile header block");  // Minute

	writeString(os, 2, coordsDim == 2 ? Header::DIM_CODE_2D : Header::DIM_CODE_3D); 

	long scaling_fac1 = getMDLScalingFactor1(molgraph);
 
	writeIntegerNumber(os, 2, scaling_fac1, "MDLDataWriter: error while writing scaling factor1 to molfile header block");

	double scaling_fac2 = getMDLScalingFactor2(molgraph);

	writeFloatNumber(os, 10, 5, scaling_fac2, "MDLDataWriter: error while writing scaling factor2 to molfile header block");

	double energy = (writeConfEnergyField && multiConfExport ? (boost::math::isnan(confEnergy) ? 0.0 : confEnergy) : getMDLEnergy(molgraph));

	writeFloatNumber(os, 12, 5, energy, "MDLDataWriter: error while writing energy to molfile header block");

	bool has_reg_no_prop = hasMDLRegistryNumber(molgraph);

	if (has_reg_no_prop) {
		std::size_t reg_no = getMDLRegistryNumber(molgraph);

		if (reg_no <= 999999)
			writeIntegerNumber(os, 6, reg_no, "MDLDataWriter: error while writing registry number to molfile header block");
	}

	writeMDLEOL(os);

	// Header line 3

	if (writeConfEnergyComment && multiConfExport) {
		if (!boost::math::isnan(confEnergy))
			os << confEnergy;

		writeMDLEOL(os);

	} else 
		writeMDLLine(os, getMDLComment(molgraph), "MDLDataWriter: error while writing comment line to molfile header block", 
					 checkLineLength, trimLines, truncateLines);
}

void Chem::MDLDataWriter::writeMOLCTab(std::ostream& os, const MolecularGraph& molgraph)
{
	setupCTabCountsLine(molgraph);
	writeCTabCountsLine(os);

	if (ctabVersion == MDLDataFormatVersion::V3000) 
		writeCTabV3000(os, molgraph);
	else
		writeCTabV2000(os, molgraph);
}

void Chem::MDLDataWriter::writeMOLEndTag(std::ostream& os) const
{
	writeMDLLine(os, MDL::MOLFile::END_TAG, "MDLDataWriter: error while writing molfile end tag", false, false, false);
}

void Chem::MDLDataWriter::setupCTabCountsLine(const MolecularGraph& molgraph)
{
	using namespace MDL::MOLFile;

	std::size_t atom_count = molgraph.getNumAtoms(); 
	std::size_t bond_count = getCompleteBondCount(molgraph); 

	ctabVersion = getMDLCTABVersionParameter(ioBase);

	if (ctabVersion != MDLDataFormatVersion::V2000 && ctabVersion != MDLDataFormatVersion::V3000)
		ctabVersion = getMDLCTABVersion(molgraph);

	atomListCount = 0;
	sTextEntryCount = 0;
	propertyCount = 999;

	switch (ctabVersion) {
		
		case MDLDataFormatVersion::V2000:
			if (atom_count > 999)
				throw Base::IOError("MDLDataWriter: number of atoms exceeds maximum for V2000 connection table");

			if (bond_count > 999)
				throw Base::IOError("MDLDataWriter: number of bonds exceeds maximum for V2000 connection table");

			break;

		default:
			if (atom_count <= 999 && bond_count <= 999)
				break;

			ctabVersion = MDLDataFormatVersion::V3000;

		case MDLDataFormatVersion::V3000:
			atomCount = 0;
			bondCount = 0;
			chiralFlag = CountsLine::CHIRAL_FLAG_OFF;
			return;
	}

	atomCount = atom_count;
	bondCount = bond_count;

	bool chiral_flag = getMDLChiralFlag(molgraph);

	chiralFlag = (!chiral_flag ? CountsLine::CHIRAL_FLAG_OFF : CountsLine::CHIRAL_FLAG_ON);
}

void Chem::MDLDataWriter::writeCTabCountsLine(std::ostream& os) const
{
	using namespace Internal;
	using namespace MDL::MOLFile;

	writeIntegerNumber(os, 3, atomCount, "MDLDataWriter: error while writing number of atoms to counts-line");
	writeIntegerNumber(os, 3, bondCount, "MDLDataWriter: error while writing number of bonds to counts-line");
	writeIntegerNumber(os, 3, atomListCount, "MDLDataWriter: error while writing number of atom lists to counts-line");

	writeWhitespace(os, 3);

	writeIntegerNumber(os, 3, chiralFlag, "MDLDataWriter: error while writing chiral flag to counts-line");
	writeIntegerNumber(os, 3, sTextEntryCount, "MDLDataWriter: error while writing number of stext entries to counts-line");

	writeWhitespace(os, 12);

	writeIntegerNumber(os, 3, propertyCount, "MDLDataWriter: error while writing number of properties to counts-line");
	writeString(os, 6, ctabVersion == MDLDataFormatVersion::V3000 ? CountsLine::V3000_TAG : CountsLine::V2000_TAG, 
				"MDLDataWriter: error while writing ctab version to counts-line", false, false, true);

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeCTabV2000(std::ostream& os, const MolecularGraph& molgraph) const
{
	writeCTabV2000AtomBlock(os, molgraph);
	writeCTabV2000BondBlock(os, molgraph);
	writeCTabV2000PropertyBlock(os, molgraph);
}

void Chem::MDLDataWriter::writeCTabV2000AtomBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
				  boost::bind(&MDLDataWriter::writeCTabV2000Atom, this, boost::ref(os), boost::ref(molgraph), _1));
}

void Chem::MDLDataWriter::writeCTabV2000BondBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
				  boost::bind(&MDLDataWriter::writeCTabV2000Bond, this, boost::ref(os), boost::ref(molgraph), _1));
}

void Chem::MDLDataWriter::writeCTabV2000PropertyBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	writeCTabV2000ChargeProperties(os, molgraph);
	writeCTabV2000RadicalProperties(os, molgraph);
	writeCTabV2000IsotopeProperties(os, molgraph);
	writeCTabV2000RingBndCountProperties(os, molgraph);
	writeCTabV2000SubstCountProperties(os, molgraph);
	writeCTabV2000UnsaturationProperties(os, molgraph);
	writeCTabV2000AtomListProperties(os, molgraph);
	writeCTabV2000RegistryNumberProperty(os, molgraph);
}

void Chem::MDLDataWriter::writeCTabV2000Atom(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	writeCTabV2000AtomCoords(os, molgraph, atom);

	Internal::writeWhitespace(os, 1);

	writeCTabV2000AtomSymbol(os, atom);
	writeCTabV2000AtomMass(os, atom);
	writeCTabV2000AtomCharge(os, atom);
	writeCTabV2000AtomParity(os, molgraph, atom);
	writeCTabV2000AtomQueryHCount(os, molgraph, atom);
	writeCTabV2000AtomStereoBoxFlag(os, molgraph, atom);
	writeCTabV2000AtomValence(os, molgraph, atom);

	Internal::writeWhitespace(os, 9);

	writeCTabV2000AtomRxnInfo(os, atom);

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeCTabV2000AtomCoords(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace Internal;

	if (coordsDim == 3) {
		const Math::Vector3D& coords = (multiConfExport ? confCoordinates[molgraph.getAtomIndex(atom)] : get3DCoordinates(atom));

		writeFloatNumber(os, 10, 4, coords(0), "MDLDataWriter: error while writing atom x coordinate");
		writeFloatNumber(os, 10, 4, coords(1), "MDLDataWriter: error while writing atom y coordinate");
		writeFloatNumber(os, 10, 4, coords(2), "MDLDataWriter: error while writing atom z coordinate");

	} else if (coordsDim == 2) {
		const Math::Vector2D& coords = get2DCoordinates(atom);

		writeFloatNumber(os, 10, 4, coords(0), "MDLDataWriter: error while writing atom x coordinate");
		writeFloatNumber(os, 10, 4, coords(1), "MDLDataWriter: error while writing atom y coordinate");

		writeWhitespace(os, 10);

	} else {
		writeFloatNumber(os, 10, 4, 0.0, "MDLDataWriter: error while writing atom x coordinate");
		writeFloatNumber(os, 10, 4, 0.0, "MDLDataWriter: error while writing atom y coordinate");
		writeFloatNumber(os, 10, 4, 0.0, "MDLDataWriter: error while writing atom z coordinate");
	}
}

void Chem::MDLDataWriter::writeCTabV2000AtomSymbol(std::ostream& os, const Atom& atom) const
{
	Internal::writeString(os, 3, hasSymbol(atom) ? getSymbol(atom) : getSymbolForType(atom),
						  "MDLDataWriter: error while writing atom symbol",
						  trimStrings, truncateStrings);
}

void Chem::MDLDataWriter::writeCTabV2000AtomMass(std::ostream& os, const Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	long mass_diff = 0;
	long isotope = getIsotope(atom);

	if (isotope > 0) {
		long mab_isotope = AtomDictionary::getMostAbundantIsotope(getType(atom));

		if (mab_isotope > 0) {
			mass_diff = isotope - mab_isotope;

			if (mass_diff > AtomBlock::MAX_MASS_DIFF || mass_diff < AtomBlock::MIN_MASS_DIFF)
				mass_diff = 0;
		}
	}

	Internal::writeIntegerNumber(os, 2, mass_diff, "MDLDataWriter: error while writing atom isotope mass difference value");
}

void Chem::MDLDataWriter::writeCTabV2000AtomCharge(std::ostream& os, const Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int charge = AtomBlock::CHARGE_0;

	switch (getFormalCharge(atom)) {

		case 0:
			if (getRadicalType(atom) == RadicalType::DOUBLET)
				charge = AtomBlock::DOUBLET_RADICAL; 
			break;

		case 1:
			charge = AtomBlock::CHARGE_P1;
			break;

		case 2:
			charge = AtomBlock::CHARGE_P2;
			break;

		case 3:
			charge = AtomBlock::CHARGE_P3;
			break;

		case -1:
			charge = AtomBlock::CHARGE_M1;
			break;

		case -2:
			charge = AtomBlock::CHARGE_M2;
			break;

		case -3:
			charge = AtomBlock::CHARGE_M3;

		default:
			break;
	}

	Internal::writeIntegerNumber(os, 3, charge, "MDLDataWriter: error while writing atom charge specification");
}

void Chem::MDLDataWriter::writeCTabV2000AtomParity(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int parity = AtomBlock::STEREO_PARITY_NONE;

	if (!ignoreParity) {
		switch (calcMDLParity(atom, molgraph)) {
			
			case MDLParity::NONE:
				break;

			case MDLParity::ODD:
				parity = AtomBlock::STEREO_PARITY_ODD;
				break;

			case MDLParity::EVEN:
				parity = AtomBlock::STEREO_PARITY_EVEN;
				break;

			case MDLParity::EITHER:
				parity = AtomBlock::STEREO_PARITY_EITHER;
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("MDLDataWriter: invalid atom stereo parity");
		}
	}

	Internal::writeIntegerNumber(os, 3, parity, "MDLDataWriter: error while writing atom stereo parity specification");
}

void Chem::MDLDataWriter::writeCTabV2000AtomQueryHCount(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	const MatchConstraintList& constr_list = *getMatchConstraints(atom);

	if (constr_list.getSize() != 0) {
		std::size_t expl_h_count = getExplicitAtomCount(atom, molgraph, AtomType::H);

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count, atom, molgraph, 
																				   &calcHydrogenCount))) {

			writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_E0,
							   "MDLDataWriter: error while writing query hydrogen count specification for atom");
			return;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 1, atom, molgraph, 
																				   &calcHydrogenCount))) {

			writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_GE1,
							   "MDLDataWriter: error while writing query hydrogen count specification for atom");
			return;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 2, atom, molgraph, 
																				   &calcHydrogenCount))) {

			writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_GE2,
							   "MDLDataWriter: error while writing query hydrogen count specification for atom");
			return;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 3, atom, molgraph, 
																				   &calcHydrogenCount))) {

			writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_GE3,
							   "MDLDataWriter: error while writing query hydrogen count specification for atom");
			return;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 4, atom, molgraph, 
																				   &calcHydrogenCount))) {

			writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_GE4,
							   "MDLDataWriter: error while writing query hydrogen count specification for atom");
			return;
		}
	}

	writeIntegerNumber(os, 3, AtomBlock::HYDROGEN_COUNT_UNDEF, 
					   "MDLDataWriter: error while writing query hydrogen count specification for atom");
}

void Chem::MDLDataWriter::writeCTabV2000AtomStereoBoxFlag(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int db_stereo_box_flag = AtomBlock::DB_STEREO_IGNORE;
	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();

	for (Atom::ConstBondIterator it = atom.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (!molgraph.containsBond(bond))
			continue;

		if (getOrder(bond) != 2)
			continue;

		const MatchConstraintList& constr_list = *getMatchConstraints(bond);

		if (constr_list.getSize() == 0)
			continue;

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::CONFIGURATION,
								MatchConstraint::EQUAL, HasUnsetConstraintValue())) {

			db_stereo_box_flag = AtomBlock::DB_STEREO_MATCH;
			break;
		}
	}

	Internal::writeIntegerNumber(os, 3, db_stereo_box_flag, "MDLDataWriter: error while writing stereo box flag for atom");
}

void Chem::MDLDataWriter::writeCTabV2000AtomValence(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t valence = AtomBlock::VALENCE_UNDEF;
	std::size_t valence_val = calcValence(atom, molgraph);

	if (valence_val == 0)
		valence = AtomBlock::VALENCE_ZERO;

	else if (valence_val <= AtomBlock::VALENCE_MAX)
		valence = valence_val;

	Internal::writeIntegerNumber(os, 3, valence, "MDLDataWriter: error while writing atom valence specification");
}

void Chem::MDLDataWriter::writeCTabV2000AtomRxnInfo(std::ostream& os, const Atom& atom) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t rxn_aam_no = getAtomMappingID(atom); 

	writeIntegerNumber(os, 3, rxn_aam_no == 0 ? AtomBlock::RXN_MAPPING_NO_UNDEF : rxn_aam_no, 
					   "MDLDataWriter: error while writing reaction atom atom mapping number");

	unsigned int rxn_center_info = getReactionCenterStatus(atom); 
	unsigned int inv_ret_flag = AtomBlock::RXN_INV_RET_UNDEF;

	switch (rxn_center_info & (ReactionCenterStatus::STEREO_INVERSION | ReactionCenterStatus::STEREO_RETENTION)) {

		case ReactionCenterStatus::STEREO_INVERSION:
			inv_ret_flag = AtomBlock::RXN_INV_RET_INVERSION;
			break;

		case ReactionCenterStatus::STEREO_RETENTION:
			inv_ret_flag = AtomBlock::RXN_INV_RET_RETENTION;
			
		default:
			break;
	}

	writeIntegerNumber(os, 3, inv_ret_flag, "MDLDataWriter: error while writing reaction inversion/retention flag for atom");
	writeIntegerNumber(os, 3, rxn_center_info & ReactionCenterStatus::EXACT_CHANGE ? AtomBlock::RXN_CHANGE_EXACT : AtomBlock::RXN_CHANGE_UNDEF,
					   "MDLDataWriter: error while writing reaction change specification for atom");
}

void Chem::MDLDataWriter::writeCTabV2000Bond(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond) const
{
	if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
		return;

	const MatchConstraintList& constr_list = *getMatchConstraints(bond);
	std::size_t order = 1;

	if (hasOrder(bond))
		order = getOrder(bond);
	
	unsigned int bond_stereo = getBondStereo(bond);

	writeCTabV2000BondAtomIndices(os, molgraph, bond, bondMemberSwapStereoFix && isReverseStereo(bond_stereo));

	writeCTabV2000BondType(os, order, constr_list);
	writeCTabV2000BondStereo(os, bond_stereo, order);

	Internal::writeWhitespace(os, 3);

	writeCTabV2000BondQueryTopology(os, molgraph, bond, constr_list);
	writeCTabV2000BondRxnCenterStatus(os, bond);

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeCTabV2000BondAtomIndices(std::ostream& os, const MolecularGraph& molgraph, 
														const Bond& bond, bool swap_atoms) const
{
	using namespace Internal;

	std::size_t atom1_idx = molgraph.getAtomIndex(bond.getBegin()) + 1;
	std::size_t atom2_idx = molgraph.getAtomIndex(bond.getEnd()) + 1;

	if (swap_atoms) {
		writeIntegerNumber(os, 3, atom2_idx);
		writeIntegerNumber(os, 3, atom1_idx);
		return;
	}

	writeIntegerNumber(os, 3, atom1_idx);
	writeIntegerNumber(os, 3, atom2_idx);
}

void Chem::MDLDataWriter::writeCTabV2000BondType(std::ostream& os, std::size_t order, const MatchConstraintList& constr_list) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	if (constr_list.getSize() != 0) {
		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::ANY_ORDER))) {

			writeIntegerNumber(os, 3, BondBlock::TYPE_ANY, "MDLDataWriter: error while writing bond type specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::AROMATIC))) {

			writeIntegerNumber(os, 3, BondBlock::TYPE_AROMATIC, "MDLDataWriter: error while writing bond type specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::SINGLE | BondMatchConstraint::DOUBLE))) {

			writeIntegerNumber(os, 3, BondBlock::TYPE_SINGLE_DOUBLE, "MDLDataWriter: error while writing bond type specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC))) {

			writeIntegerNumber(os, 3, BondBlock::TYPE_SINGLE_AROMATIC, "MDLDataWriter: error while writing bond type specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC))) {

			writeIntegerNumber(os, 3, BondBlock::TYPE_DOUBLE_AROMATIC, "MDLDataWriter: error while writing bond type specification");
			return;
		}
	}

	unsigned int type;

	switch (order) {

		case 1:
			type = BondBlock::TYPE_SINGLE;
			break;

		case 2:
			type = BondBlock::TYPE_DOUBLE;
			break;

		case 3:
			type = BondBlock::TYPE_TRIPLE;
			break;
					
		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid bond order");

			type = BondBlock::TYPE_SINGLE;
	}

	writeIntegerNumber(os, 3, type, "MDLDataWriter: error while writing bond type specification");
}

void Chem::MDLDataWriter::writeCTabV2000BondStereo(std::ostream& os, unsigned int bond_stereo, std::size_t order) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int stereo_flag = BondBlock::STEREO_NONE;

	switch (bond_stereo) {

		case BondStereoFlag::PLAIN:
			break;

		case BondStereoFlag::REVERSE_DOWN:
			if (bondMemberSwapStereoFix) {
				stereo_flag = BondBlock::STEREO_DOWN;
				break;
			}

		case BondStereoFlag::UP:
			stereo_flag = BondBlock::STEREO_UP;
			break;

		case BondStereoFlag::REVERSE_UP:
			if (bondMemberSwapStereoFix) {
				stereo_flag = BondBlock::STEREO_UP;
				break;
			}

		case BondStereoFlag::DOWN:
			stereo_flag = BondBlock::STEREO_DOWN;
			break;

		case BondStereoFlag::REVERSE_EITHER:
		case BondStereoFlag::EITHER:
			stereo_flag = (order == 2 ? BondBlock::STEREO_EITHER_DB : BondBlock::STEREO_EITHER);
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid stereo bond type");
	}

	Internal::writeIntegerNumber(os, 3, stereo_flag, "MDLDataWriter: error while writing bond stereo specification");
}

void Chem::MDLDataWriter::writeCTabV2000BondQueryTopology(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond, 
														  const MatchConstraintList& constr_list) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	if (constr_list.getSize() != 0) {
		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Bond>(true, bond, molgraph, &isRingBond))) {

			writeIntegerNumber(os, 3, BondBlock::TOPOLOGY_RING, "MDLDataWriter: error while writing query bond topology specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Bond>(false, bond, molgraph, &isRingBond))) {

			writeIntegerNumber(os, 3, BondBlock::TOPOLOGY_CHAIN, "MDLDataWriter: error while writing query bond topology specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::NOT_EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Bond>(true, bond, molgraph, &isRingBond))) {

			writeIntegerNumber(os, 3, BondBlock::TOPOLOGY_CHAIN, "MDLDataWriter: error while writing query bond topology specification");
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::NOT_EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Bond>(false, bond, molgraph, &isRingBond))) {

			writeIntegerNumber(os, 3, BondBlock::TOPOLOGY_RING, 
							   "MDLDataWriter: error while writing query bond topology specification");
			return;
		}
	}

	writeIntegerNumber(os, 3, BondBlock::TOPOLOGY_EITHER, 
					   "MDLDataWriter: error while writing query bond topology specification");
}

void Chem::MDLDataWriter::writeCTabV2000BondRxnCenterStatus(std::ostream& os, const Bond& bond) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	int rxn_center_status = BondBlock::RXN_STATUS_UNMARKED;

	switch (getReactionCenterStatus(bond)) { 

		case ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::NO_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_NO_CENTER;
			break;

		case ReactionCenterStatus::NO_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_NO_CHANGE;
			break;

		case ReactionCenterStatus::BOND_ORDER_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_ORDER_CHANGE;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
			ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE + 
				BondBlock::RXN_STATUS_IS_CENTER;
			break;

		default:
			break;
	}

	Internal::writeIntegerNumber(os, 3, rxn_center_status, "MDLDataWriter: error while writing bond reacting center status");
}

void Chem::MDLDataWriter::writeCTabV2000ChargeProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	typedef std::pair<std::size_t, long> ChargeEntry;

	std::vector<ChargeEntry> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		long charge = getFormalCharge(atom);

		if (charge == 0)
			continue;

		if (strictErrorChecking && (charge < PropertyBlock::MIN_CHARGE || charge > PropertyBlock::MAX_CHARGE))
			throw Base::IOError("MDLDataWriter: atom charge range error for charge property list item");

		entries.push_back(ChargeEntry(molgraph.getAtomIndex(atom) + 1, charge));
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::CHARGE_PREFIX, "MDLDataWriter: error while writing charge property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_CHARGE_ENTRIES, num_entries - i), 
							   "MDLDataWriter: error while writing number of charge property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].first, "MDLDataWriter: error while writing atom index for charge property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].second, "MDLDataWriter: error while writing charge property value");

		if (++list_size == PropertyBlock::MAX_CHARGE_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000RadicalProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	typedef std::pair<std::size_t, unsigned int> RadicalEntry;

	std::vector<RadicalEntry> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		unsigned int rad_type;

		switch (getRadicalType(atom)) {

			case RadicalType::SINGLET:
				rad_type = PropertyBlock::SINGLET_RADICAL;
				break;

			case RadicalType::DOUBLET:
				rad_type = PropertyBlock::DOUBLET_RADICAL;
				break;

			case RadicalType::TRIPLET:
				rad_type = PropertyBlock::TRIPLET_RADICAL;
				break;

			case RadicalType::NOT_RADICALIC:
				continue;

			default:
				if (strictErrorChecking)
					throw Base::IOError("MDLDataWriter: invalid radical type specification for atom");

				continue;
		}

		entries.push_back(RadicalEntry(molgraph.getAtomIndex(atom) + 1, rad_type));
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::RADICAL_PREFIX, "MDLDataWriter: error while writing radical property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_RADICAL_ENTRIES, num_entries - i),
							   "MDLDataWriter: error while writing number of radical property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].first, "MDLDataWriter: error while writing atom index for radical property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].second, 
						   "MDLDataWriter: error while writing radical type specification for property list item");

		if (++list_size == PropertyBlock::MAX_RADICAL_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000IsotopeProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	typedef std::pair<std::size_t, std::size_t> IsotopeEntry;

	std::vector<IsotopeEntry> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t isotope = getIsotope(atom);

		if (isotope == 0)
			continue;

		entries.push_back(IsotopeEntry(molgraph.getAtomIndex(atom) + 1, isotope));
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::ISOTOPE_PREFIX, "MDLDataWriter: error while writing isotope property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_ISOTOPE_ENTRIES, num_entries - i), 
							   "MDLDataWriter: error while writing number of isotope property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].first, "MDLDataWriter: error while writing atom index for isotope property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].second, "MDLDataWriter: error while writing mass value for isotope property list item");

		if (++list_size == PropertyBlock::MAX_ISOTOPE_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000RingBndCountProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	typedef std::pair<std::size_t, int> RBCEntry;

	std::vector<RBCEntry> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		const MatchConstraintList& constr_list = *getMatchConstraints(atom);

		if (constr_list.getSize() == 0)
			continue;

		std::size_t atom_id = molgraph.getAtomIndex(atom) + 1;

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								HasUnsetConstraintValue())) {

			entries.push_back(RBCEntry(atom_id, PropertyBlock::RING_BOND_COUNT_DRAWN));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(0, atom, molgraph, &getRingBondCount))) {

			entries.push_back(RBCEntry(atom_id, PropertyBlock::RING_BOND_COUNT_E0));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(2, atom, molgraph, &getRingBondCount))) {

			entries.push_back(RBCEntry(atom_id, PropertyBlock::RING_BOND_COUNT_E2));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(3, atom, molgraph, &getRingBondCount))) {

			entries.push_back(RBCEntry(atom_id, PropertyBlock::RING_BOND_COUNT_E3));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL,
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(4, atom, molgraph, &getRingBondCount))) {

			entries.push_back(RBCEntry(atom_id, PropertyBlock::RING_BOND_COUNT_GE4));
		}
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::RING_BOND_COUNT_PREFIX, 
						"MDLDataWriter: error while writing ring bond count property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_RING_BOND_COUNT_ENTRIES, num_entries - i),
							   "MDLDataWriter: error while writing number of ring bond count property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].first, "MDLDataWriter: error while writing atom index for ring bond count property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].second, "MDLDataWriter: error while writing ring bond count specification for property list item");

		if (++list_size == PropertyBlock::MAX_RING_BOND_COUNT_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000SubstCountProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	typedef std::pair<std::size_t, int> SCEntry;

	std::vector<SCEntry> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		const MatchConstraintList& constr_list = *getMatchConstraints(atom);
	
		if (constr_list.getSize() == 0)
			continue;

		std::size_t atom_id = molgraph.getAtomIndex(atom) + 1;

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT,
								MatchConstraint::EQUAL, HasUnsetConstraintValue())) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_DRAWN));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(0, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E0));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(1, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E1));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(2, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E2));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(3, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E3));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(4, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E4));
			continue;
		}
	
		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(5, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_E5));
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
								CalcOrSetConstraintValueMatches<std::size_t, Atom>(6, atom, molgraph, &getHeavyBondCount))) {

			entries.push_back(SCEntry(atom_id, PropertyBlock::SUBSTITUTION_COUNT_GE6));
		}
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::SUBSTITUTION_COUNT_PREFIX, 
						"MDLDataWriter: error while writing substitution count property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_SUBSTITUTION_COUNT_ENTRIES, num_entries - i),
							   "MDLDataWriter: error while writing number of substitution count property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].first, "MDLDataWriter: error while writing atom index for substitution count property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i].second, "MDLDataWriter: error while writing substitution count specification for property list item");

		if (++list_size == PropertyBlock::MAX_SUBSTITUTION_COUNT_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000UnsaturationProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	std::vector<std::size_t> entries;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		const MatchConstraintList& constr_list = *getMatchConstraints(atom);

		if (constr_list.getSize() == 0)
			continue;

		std::size_t atom_id = molgraph.getAtomIndex(atom);

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::UNSATURATION, MatchConstraint::EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Atom>(true, atom, molgraph, &isUnsaturated))) {

			entries.push_back(atom_id);
			continue;
		}

		if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::UNSATURATION, MatchConstraint::NOT_EQUAL, 
								CalcOrSetConstraintValueMatches<bool, Atom>(false, atom, molgraph, &isUnsaturated))) {

			entries.push_back(atom_id);
		}
	}

	std::size_t num_entries = entries.size();

	for (std::size_t i = 0, list_size = 0; i < num_entries; i++) {
		if (list_size == 0) {
			writeString(os, 6, PropertyBlock::UNSATURATION_PREFIX, 
						"MDLDataWriter: error while writing Unsaturation flag property line prefix");
			writeIntegerNumber(os, 3, std::min(PropertyBlock::MAX_UNSATURATION_ENTRIES, num_entries - i),
							   "MDLDataWriter: error while writing number of Unsaturation flag property list entries");
		}

		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, entries[i], "MDLDataWriter: error while writing atom index for Unsaturation flag property list item");
		writeWhitespace(os, 1);
		writeIntegerNumber(os, 3, PropertyBlock::UNSATURATION_ON, 
						   "MDLDataWriter: error while writing Unsaturation flag specification for property list item");

		if (++list_size == PropertyBlock::MAX_UNSATURATION_ENTRIES || i + 1 == num_entries) {
			writeMDLEOL(os);
			list_size = 0;
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000AtomListProperties(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		const MatchConstraintList& constr_list = *getMatchConstraints(atom);

		if (constr_list.getSize() == 0)
			continue;

		if (constr_list.getType() == MatchConstraintList::OR_LIST) {
			writeCTabV2000AtomList(os, molgraph, atom, constr_list, false);
			continue;
		}

 		if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST) {
			writeCTabV2000AtomList(os, molgraph, atom, constr_list, true);
			continue;
		}

 		if (constr_list.getType() != MatchConstraintList::AND_LIST) 
			continue;

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (constraint.getID() != AtomMatchConstraint::CONSTRAINT_LIST)
				continue;

			const MatchConstraintList& constr_list = 
				*constraint.getValue<MatchConstraintList::SharedPointer>();

			if (constraint.getRelation() == MatchConstraint::EQUAL) {
				if (constr_list.getType() == MatchConstraintList::OR_LIST) {
					writeCTabV2000AtomList(os, molgraph, atom, constr_list, false);
					continue;
				}

				if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST)
					writeCTabV2000AtomList(os, molgraph, atom, constr_list, true);

				continue;					
			}

			if (constraint.getRelation() == MatchConstraint::NOT_EQUAL) {
				if (constr_list.getType() == MatchConstraintList::OR_LIST) {
					writeCTabV2000AtomList(os, molgraph, atom, constr_list, true);
					continue;
				}

				if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST)
					writeCTabV2000AtomList(os, molgraph, atom, constr_list, false);
			}
		}
	}
}

void Chem::MDLDataWriter::writeCTabV2000AtomList(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom, 
												 const MatchConstraintList& constr_list, bool not_list) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	if (constr_list.getSize() == 0)
		return;

	std::ostringstream oss;
	std::size_t list_size = 0;

	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		if (constraint.getID() != AtomMatchConstraint::TYPE)
			continue;

		if (constraint.getRelation() != MatchConstraint::EQUAL)
			continue;

		unsigned int atom_type = getConstraintValue<unsigned int>(constraint, atom, &getType);

		if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_TYPE)
			continue;

		const std::string& symbol = AtomDictionary::getSymbol(atom_type);

		assert(!symbol.empty());

		writeString(oss, 4, symbol, "MDLDataWriter: error while writing atom symbol for atom list property",
					false, false);

		list_size++;

		if (strictErrorChecking && list_size > PropertyBlock::MAX_ATOM_LIST_ENTRIES)
			throw Base::IOError("MDLDataWriter: atom list exceeded maximum allowed size");
	}

	if (list_size == 0)
		return;

	writeString(os, 6, PropertyBlock::ATOM_LIST_PREFIX, "MDLDataWriter: error while writing atom list property line prefix");
	writeWhitespace(os, 1);
	writeIntegerNumber(os, 3, molgraph.getAtomIndex(atom) + 1, "MDLDataWriter: error while writing atom index for atom list property line");
	writeIntegerNumber(os, 3, list_size, "MDLDataWriter: error while writing list size for atom list property line");
	writeWhitespace(os, 1);
	writeString(os, 1, not_list ? PropertyBlock::NOT_ATOM_LIST_FLAG : PropertyBlock::NORMAL_ATOM_LIST_FLAG, 
				"MDLDataWriter: error while writing list type specification for atom list property");
	writeWhitespace(os, 1);
	writeMDLLine(os, oss.str(), "MDLDataWriter: error while writing atoms for atom list property line",
				 checkLineLength, false, truncateLines, MDL::MAX_LINE_LENGTH - 16);
}

void Chem::MDLDataWriter::writeCTabV2000RegistryNumberProperty(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace Internal;
	using namespace MDL::MOLFile::CTab::V2000;

	if (!hasMDLRegistryNumber(molgraph))
		return;
 
	std::size_t reg_no = getMDLRegistryNumber(molgraph);

	if (reg_no <= 999999)
		return;

	writeString(os, 6, PropertyBlock::REGISTRY_NO_PREFIX, 
				"MDLDataWriter: error while writing molecule registry number property line prefix");
	writeWhitespace(os, 1);

	try {
		writeMDLLine(os, boost::lexical_cast<std::string>(reg_no), 
					 "MDLDataWriter: error while writing molecule registry number to property line", 
					 checkLineLength, false, truncateLines, MDL::MAX_LINE_LENGTH - 7);				

	} catch (...) {
		throw Base::IOError("MDLDataWriter: error while writing molecule registry number property line");
	}
}

void Chem::MDLDataWriter::writeSDFData(std::ostream& os, const MolecularGraph& molgraph) const
{   
	using namespace Internal;
	using namespace MDL;

	std::size_t prefix_length = SDFile::DATA_HEADER_PREFIX.length();

	if (writeConfEnergySDEntry && multiConfExport && !boost::math::isnan(confEnergy)) {
		writeString(os, prefix_length + 1, SDFile::DATA_HEADER_PREFIX, 
					"MDLDataWriter: error while writing structure data header prefix"); 
		writeMDLLine(os, confEnergySDTag, "MDLDataWriter: error while writing header for conformer energy structure data item", 
					 checkLineLength, false, truncateLines, MDL::MAX_LINE_LENGTH - prefix_length);	
		
		os << confEnergy; 
		writeMDLEOL(os);
		writeMDLEOL(os);
	}

	const char line_sep[] = { MDL::END_OF_LINE, 0 };

	if (!hasStructureData(molgraph)) {
		writeMDLLine(os, SDFile::RECORD_DELIMITER, "MDLDataWriter: error while writing sd-file record delimiter", false, false);
		return;
	}
 
	const StringDataBlock& data = *getStructureData(molgraph);
	std::string trimmed_line;

	StringDataBlock::ConstElementIterator entries_end = data.getElementsEnd();

	for (StringDataBlock::ConstElementIterator it = data.getElementsBegin(); it != entries_end; ++it) {
		const StringDataBlockEntry& entry = *it;
		const std::string& header = entry.getHeader();

		if (!header.empty() && !std::isspace(header[0], std::locale::classic()))
			prefix_length++;

		writeString(os, prefix_length, SDFile::DATA_HEADER_PREFIX, 
					"MDLDataWriter: error while writing structure data header prefix"); 
	
		writeMDLLine(os, header, "MDLDataWriter: error while writing header for structure data item", 
					 checkLineLength, false, truncateLines, MDL::MAX_LINE_LENGTH - prefix_length);	

		typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
		
		Tokenizer lines(entry.getData(), boost::char_separator<char>(line_sep, "", boost::keep_empty_tokens));

		for (Tokenizer::iterator l_it = lines.begin(); l_it != lines.end(); ++l_it) {
			const std::string& line = *l_it;

			if (line.empty()) {
				if (strictErrorChecking)
					throw Base::IOError("MDLDataWriter: empty data line for for structure data entry");

			} else
				writeMDLLine(os, line, "MDLDataWriter: error while writing data line for structure data entry", 
							 checkLineLength, false, truncateLines, MAX_DATA_LINE_LENGTH);		
		}

		writeMDLEOL(os);
	}

	writeMDLLine(os, SDFile::RECORD_DELIMITER, "MDLDataWriter: error while writing sd-file record delimiter", false, false);
}

void Chem::MDLDataWriter::setRXNFileVersion(const Reaction& rxn)
{
	rxnVersion = getMDLRXNFileVersionParameter(ioBase); 

	if (rxnVersion != MDLDataFormatVersion::V2000 && rxnVersion != MDLDataFormatVersion::V3000)
		rxnVersion = getMDLRXNFileVersion(rxn);

	std::size_t num_reactants = rxn.getNumComponents(ReactionRole::REACTANT);
	std::size_t num_products = rxn.getNumComponents(ReactionRole::PRODUCT);

	switch (rxnVersion) {
		
		case MDLDataFormatVersion::V3000:
			return;

		case MDLDataFormatVersion::V2000:
			if (num_reactants > 999)
				throw Base::IOError("MDLDataWriter: number of reactants exceeds maximum for V2000 rxn-file");

			if (num_products > 999)
				throw Base::IOError("MDLDataWriter: number of products exceeds maximum for V2000 rxn-file");

			return;

		default:
			if (num_reactants <= 999 && num_products <= 999) {
				rxnVersion = MDLDataFormatVersion::V2000;
				return;
			}

			rxnVersion = MDLDataFormatVersion::V3000;
			return;
	}
}

void Chem::MDLDataWriter::writeRXNHeaderBlock(std::ostream& os, const Reaction& rxn) const
{	
	using namespace Internal;
	using namespace MDL;

	// Header line 1

	writeString(os, RXNFile::RXN_FILE_IDENTIFIER.length(), RXNFile::RXN_FILE_IDENTIFIER,
				"MDLDataWriter: error while writing rxn-file identifier to reaction header block");

	if (rxnVersion == MDLDataFormatVersion::V3000) {
		writeWhitespace(os, 1);
		writeString(os, RXNFile::V3000_VERSION_TAG.length(), RXNFile::V3000_VERSION_TAG,
					"MDLDataWriter: error while writing rxn-file version to reaction header block");
	}

	writeMDLEOL(os);

	// Header line 2

	const std::string& rxn_name = getName(rxn);

	writeMDLLine(os, rxn_name, "MDLDataWriter: error while writing reaction name to rxn-file header block", 
				 checkLineLength, trimLines, truncateLines);

	// Header line 3

	const std::string& user_initials = getMDLUserInitials(rxn);

	writeString(os, 6, user_initials, "MDLDataWriter: error while writing user initials to rxn-file header block",
				trimStrings, truncateStrings);

	const std::string& prog_name = getMDLProgramName(rxn);

	writeString(os, 9, prog_name, "MDLDataWriter: error while writing header block program name to rxn-file header block",
				trimStrings, truncateStrings);

	using namespace boost::posix_time;

	bool has_ts_prop = hasMDLTimestamp(rxn);
	bool update_time = getMDLUpdateTimestampParameter(ioBase); 

	std::string iso_time_str;  // ISO format: YYYYMMDDTHHMMSS

	if (update_time || !has_ts_prop)
		iso_time_str = to_iso_string(second_clock::universal_time());
	else
		iso_time_str = to_iso_string(from_time_t(getMDLTimestamp(rxn)));

	writeString(os, 2, iso_time_str.substr(4, 2), 
				"MDLDataWriter: error while writing date/timestamp month part to rxn-file header block");  // Month
	writeString(os, 2, iso_time_str.substr(6, 2), 
				"MDLDataWriter: error while writing date/timestamp day part to rxn-file header block");    // Day
	writeString(os, 4, iso_time_str.substr(0, 4), 
				"MDLDataWriter: error while writing date/timestamp year part to rxn-file header block");   // Year
	writeString(os, 2, iso_time_str.substr(9, 2), 
				"MDLDataWriter: error while writing date/timestamp hour part to rxn-file header block");   // Hour
	writeString(os, 2, iso_time_str.substr(11, 2), 
				"MDLDataWriter: error while writing date/timestamp minute to rxn-file header block");      // Min

	if (hasMDLRegistryNumber(rxn)) {
		std::size_t reg_no = getMDLRegistryNumber(rxn);

		if (strictErrorChecking || reg_no <= 9999999) 
			writeIntegerNumber(os, 7, reg_no, "MDLDataWriter: error while writing registry number to rxn-file header block");
	}

	writeMDLEOL(os);

	// Header line 4

	const std::string& comment = getMDLComment(rxn);

	writeMDLLine(os, comment, "MDLDataWriter: error while writing comment line to rxn-file header block", 
				 checkLineLength, trimLines, truncateLines);
}

void Chem::MDLDataWriter::writeRXNReaction(std::ostream& os, const Reaction& rxn)
{
	if (rxnVersion == MDLDataFormatVersion::V3000)
		writeRXNV3000Reaction(os, rxn);
	else
		writeRXNV2000Reaction(os, rxn);
}

void Chem::MDLDataWriter::writeRXNV2000Reaction(std::ostream& os, const Reaction& rxn)
{
	writeRXNV2000CountsLine(os, rxn);

	std::for_each(rxn.getComponentsBegin(ReactionRole::REACTANT), rxn.getComponentsEnd(ReactionRole::REACTANT), 
				  boost::bind(&MDLDataWriter::writeRXNV2000ReactionComponent, this, boost::ref(os), _1));

	std::for_each(rxn.getComponentsBegin(ReactionRole::PRODUCT), rxn.getComponentsEnd(ReactionRole::PRODUCT), 
				  boost::bind(&MDLDataWriter::writeRXNV2000ReactionComponent, this, boost::ref(os), _1));
}

void Chem::MDLDataWriter::writeRXNV2000CountsLine(std::ostream& os, const Reaction& rxn) const
{
	using namespace Internal;

	writeIntegerNumber(os, 3, rxn.getNumComponents(ReactionRole::REACTANT), "MDLDataWriter: error while writing number of reactants");
	writeIntegerNumber(os, 3, rxn.getNumComponents(ReactionRole::PRODUCT), "MDLDataWriter: error while writing number of products");

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeRXNV2000ReactionComponent(std::ostream& os, const MolecularGraph& comp)
{
	writeMDLLine(os, MDL::RXNFile::MOL_FILE_DELIMITER, 
				 "MDLDataWriter: error while writing reaction component molfile delimiter", false, false);

	getAtomCoordsDim(comp);

	writeMOLHeaderBlock(os, comp);
	writeMOLCTab(os, comp);
	writeMOLEndTag(os);
}

void Chem::MDLDataWriter::writeRDFHeaderBlock(std::ostream& os)
{
	using namespace Internal;
	using namespace MDL;

	if (rdfHeaderWritten)
		return;

	// first line

	writeString(os, RDFile::RD_FILE_IDENTIFIER.length(), RDFile::RD_FILE_IDENTIFIER,
				"MDLDataWriter: error while writing rd-file identifier keyword to rd-file header block");

	writeWhitespace(os, 1);

	writeString(os, RDFile::RD_FILE_VERSION_STAMP.length(), RDFile::RD_FILE_VERSION_STAMP,
				"MDLDataWriter: error while writing version stamp to rd-file header block");

	writeMDLEOL(os);

	// second line

	writeString(os, RDFile::DATE_TIME_KEYWORD.length(), RDFile::DATE_TIME_KEYWORD,
				"MDLDataWriter: error while writing date/timestamp keyword to rd-file header block");

	writeWhitespace(os, 1);

	using namespace boost::posix_time;

	std::string iso_time_str = to_iso_string(second_clock::universal_time());  // ISO format: YYYYMMDDTHHMMSS

	writeString(os, 2, iso_time_str.substr(4, 2), 
				"MDLDataWriter: error while writing date month part to rd-file header block");       // Month

	writeString(os, RDFile::DATE_PART_SEPARATOR.length(), RDFile::DATE_PART_SEPARATOR, 
				"MDLDataWriter: error while writing date month/day separator to rd-file header block");

	writeString(os, 2, iso_time_str.substr(6, 2), 
				"MDLDataWriter: error while writing date day part to rd-file header block");         // Day

	writeString(os, RDFile::DATE_PART_SEPARATOR.length(), RDFile::DATE_PART_SEPARATOR, 
				"MDLDataWriter: error while writing date date day/year separator to rd-file header block");

	writeString(os, 4, iso_time_str.substr(0, 4), 
				"MDLDataWriter: error while writing date year part to rd-file header block");        // Year

	writeWhitespace(os, 1);

	writeString(os, 2, iso_time_str.substr(9, 2), 
				"MDLDataWriter: error while writing timestamp hour part to rd-file header block");   // Hour

	writeString(os, RDFile::HOUR_MINUTE_SEPARATOR.length(), RDFile::HOUR_MINUTE_SEPARATOR, 
				"MDLDataWriter: error while writing timestamp hour/minute separator to rd-file header block");

	writeString(os, 2, iso_time_str.substr(11, 2), 
				"MDLDataWriter: error while writing timestamp minute part to rd-file header block"); // Minute

	writeMDLEOL(os);

	rdfHeaderWritten = true;
}

void Chem::MDLDataWriter::writeRDFReaction(std::ostream& os, const Reaction& rxn)
{
	using namespace MDL;

	bool has_mol_rec_prop = hasMDLMoleculeRecord(rxn);
	bool has_int_reg_prop = hasMDLInternalRegistryNumber(rxn);
	bool has_ext_reg_prop = hasMDLExternalRegistryNumber(rxn);

	std::ostringstream rec_id_oss;

	if (!has_mol_rec_prop) {
		bool write_rxn_file = (rxn.getNumComponents() > 0 || 
							   (has_int_reg_prop && has_ext_reg_prop) || (!has_int_reg_prop && !has_ext_reg_prop));

		if (write_rxn_file)
			rec_id_oss << RDFile::RXN_RECORD_IDENTIFIER;

		if (has_int_reg_prop) {
			if (write_rxn_file)
				rec_id_oss << ' ';

			rec_id_oss << RDFile::RXN_INT_REGISTRY_NO_KEYWORD << ' ' << getMDLInternalRegistryNumber(rxn);
		}

		if (has_ext_reg_prop && ((write_rxn_file && has_int_reg_prop) || (!write_rxn_file && !has_int_reg_prop))) {
			if (write_rxn_file)
				rec_id_oss << ' ';

			rec_id_oss << RDFile::RXN_EXT_REGISTRY_NO_KEYWORD << ' ' << getMDLExternalRegistryNumber(rxn);
		}

		writeMDLLine(os, rec_id_oss.str(), "MDLDataWriter: error while writing rd-file reaction record identifier line", 
					 checkLineLength, trimLines, truncateLines);
		
		if (write_rxn_file) {
			setRXNFileVersion(rxn);

			writeRXNHeaderBlock(os, rxn);
			writeRXNReaction(os, rxn);
		}

		return;
	} 
	
	const MolecularGraph& molgraph = *getMDLMoleculeRecord(rxn);

	bool write_mol_file = (molgraph.getNumAtoms() > 0 || (has_int_reg_prop && has_ext_reg_prop) ||
						   (!has_int_reg_prop && !has_ext_reg_prop));

	if (write_mol_file)
		rec_id_oss << RDFile::MOL_RECORD_IDENTIFIER;

	if (has_int_reg_prop) {
		if (write_mol_file)
			rec_id_oss << ' ';

		rec_id_oss << RDFile::MOL_INT_REGISTRY_NO_KEYWORD << ' ' << getMDLInternalRegistryNumber(rxn);
	}

	if (has_ext_reg_prop && ((write_mol_file && has_int_reg_prop) || (!write_mol_file && !has_int_reg_prop))) {
		if (write_mol_file)
			rec_id_oss << ' ';

		rec_id_oss << RDFile::MOL_EXT_REGISTRY_NO_KEYWORD << ' ' << getMDLExternalRegistryNumber(rxn);
	}

	writeMDLLine(os, rec_id_oss.str(), "MDLDataWriter: error while writing rd-file molecule record identifier line", 
				 checkLineLength, trimLines, truncateLines);
		
	if (write_mol_file) {
		getAtomCoordsDim(molgraph);

		writeMOLHeaderBlock(os, molgraph);
		writeMOLCTab(os, molgraph);
		writeMOLEndTag(os);
	}
}

void Chem::MDLDataWriter::writeRDFData(std::ostream& os, const Reaction& rxn) const
{   
	using namespace Internal;
	using namespace MDL;

	if (!hasReactionData(rxn))
		return;

	const StringDataBlock& data = *getReactionData(rxn);

	StringDataBlock::ConstElementIterator items_end = data.getElementsEnd();

	for (StringDataBlock::ConstElementIterator it = data.getElementsBegin(); it != items_end; ++it) {
		const StringDataBlockEntry& entry = *it;

		std::size_t data_field_id_pfx_length = RDFile::DATA_FIELD_IDENTIFIER.length();
		const std::string& data_field_id = entry.getHeader();

		if (!data_field_id.empty() && !std::isspace(data_field_id[0], std::locale::classic()))
			data_field_id_pfx_length++;

		writeString(os, data_field_id_pfx_length, RDFile::DATA_FIELD_IDENTIFIER,
					"MDLDataWriter: error while writing rd-file datafield identifier keyword"); 

		writeRDFLine(os, data_field_id, data_field_id_pfx_length, false);

		std::size_t data_field_pfx_length = RDFile::DATA_FIELD_PREFIX.length();
		const std::string& data = entry.getData();

		if (!data.empty() && !std::isspace(data[0], std::locale::classic()))
			data_field_pfx_length++;

		writeString(os, data_field_pfx_length, RDFile::DATA_FIELD_PREFIX,
					"MDLDataWriter: error while writing rd-file datafield keyword"); 

		writeRDFLine(os, data, data_field_pfx_length, true);
	}
}

void Chem::MDLDataWriter::writeRDFLine(std::ostream& os, const std::string& rdf_line, std::size_t prefix_len, 
									   bool data_line) const
{   
	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	if (!rdf_line.empty()) {
		Tokenizer phys_lines(rdf_line, boost::char_separator<char>("\n", "", boost::keep_empty_tokens));

		std::size_t max_llen = (data_line ? MDL::MAX_DATA_LINE_LENGTH : MDL::MAX_LINE_LENGTH) - prefix_len;

		for (Tokenizer::iterator l_it = phys_lines.begin(); l_it != phys_lines.end(); ++l_it) {
			const std::string& phys_line = *l_it;

			writeMDLLine(os, phys_line, "MDLDataWriter: error while writing rd-file reaction data line", 
						 checkLineLength, false, false, max_llen);		

			max_llen = (data_line ? MDL::MAX_DATA_LINE_LENGTH : MDL::MAX_LINE_LENGTH);
		}

	} else		
		writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeCTabV3000(std::ostream& os, const MolecularGraph& molgraph, bool force_reg_no) const
{
	using namespace MDL::MOLFile::CTab;

	writeV3000BlockBegin(os, V3000::BLOCK_TYPE_KEY);

	writeCTabV3000CountsLine(os, molgraph, force_reg_no);
	writeCTabV3000AtomBlock(os, molgraph);
	writeCTabV3000BondBlock(os, molgraph);

	writeV3000BlockEnd(os, V3000::BLOCK_TYPE_KEY);
}

void Chem::MDLDataWriter::writeCTabV3000CountsLine(std::ostream& os, const MolecularGraph& molgraph, bool force_reg_no) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	std::ostringstream counts_oss;

	bool chiral_flag = getMDLChiralFlag(molgraph);

	counts_oss << CountsLine::COUNTS_TAG << ' ' << molgraph.getNumAtoms() << ' ' << getCompleteBondCount(molgraph) << " 0 0 "
			   << (!chiral_flag ? CountsLine::CHIRAL_FLAG_OFF : CountsLine::CHIRAL_FLAG_ON);

	bool has_reg_no_prop = hasMDLRegistryNumber(molgraph);

	if (has_reg_no_prop) {
		std::size_t reg_no = getMDLRegistryNumber(molgraph);

		if (force_reg_no || reg_no > 999999) 
			counts_oss << ' ' << CountsLine::REGISTRY_NO_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << reg_no;
	}

	writeV3000DataLine(os, counts_oss.str());
}

void Chem::MDLDataWriter::writeCTabV3000AtomBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	writeV3000BlockBegin(os, AtomBlock::BLOCK_TYPE_KEY);

	std::for_each(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(),
				  boost::bind(&MDLDataWriter::writeCTabV3000Atom, this, boost::ref(os), boost::ref(molgraph), _1));

	writeV3000BlockEnd(os, AtomBlock::BLOCK_TYPE_KEY);
}

void Chem::MDLDataWriter::writeCTabV3000BondBlock(std::ostream& os, const MolecularGraph& molgraph) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	if (getCompleteBondCount(molgraph) == 0)
		return;

	writeV3000BlockBegin(os, BondBlock::BLOCK_TYPE_KEY);

	std::for_each(molgraph.getBondsBegin(), molgraph.getBondsEnd(),
				  boost::bind(&MDLDataWriter::writeCTabV3000Bond, this, boost::ref(os), boost::ref(molgraph), _1));

	writeV3000BlockEnd(os, BondBlock::BLOCK_TYPE_KEY);
}

void Chem::MDLDataWriter::writeCTabV3000Atom(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	std::ostringstream line_oss;
	const MatchConstraintList& constr_list = *getMatchConstraints(atom);

	writeCTabV3000AtomIndex(line_oss, molgraph, atom);
	writeCTabV3000AtomType(line_oss, atom, constr_list);
	writeCTabV3000AtomCoords(line_oss, molgraph, atom);
	writeCTabV3000AtomRxnAAMNumber(line_oss, atom);
	writeCTabV3000AtomCharge(line_oss, atom);
	writeCTabV3000AtomRadicalType(line_oss, atom);
	writeCTabV3000AtomStereoParity(line_oss, molgraph, atom);
	writeCTabV3000AtomMass(line_oss, atom);
	writeCTabV3000AtomValence(line_oss, molgraph, atom);

	if (constr_list.getSize() != 0) {
		writeCTabV3000AtomQueryHCount(line_oss, molgraph, atom, constr_list);
		writeCTabV3000AtomQuerySubstCount(line_oss, molgraph, atom, constr_list);
		writeCTabV3000AtomQueryUnsaturationFlag(line_oss, molgraph, atom, constr_list);
		writeCTabV3000AtomQueryRingBondCount(line_oss, molgraph, atom, constr_list);
	}

	writeCTabV3000AtomRxnInfo(line_oss, atom);

	writeV3000DataLine(os, line_oss.str());
}

void Chem::MDLDataWriter::writeCTabV3000AtomIndex(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	os << (molgraph.getAtomIndex(atom) + 1);
}

void Chem::MDLDataWriter::writeCTabV3000AtomType(std::ostream& os, const Atom& atom, 
												 const MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	os << ' ';

	if (constr_list.getSize() != 0 && writeCTabV3000AtomList(os, atom, constr_list))
		return;

	if (trimStrings) 
		writeCTabV3000PropertyStringValue(os, Internal::trimStringCopy(hasSymbol(atom) ? getSymbol(atom) : getSymbolForType(atom)));
	else
		writeCTabV3000PropertyStringValue(os, getSymbol(atom));
}

bool Chem::MDLDataWriter::writeCTabV3000AtomList(std::ostream& os, const Atom& atom, 
												 const MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	if (constr_list.getType() == MatchConstraintList::OR_LIST) 
		return writeCTabV3000AtomList(os, atom, constr_list, false);

	if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST) 
		return writeCTabV3000AtomList(os, atom, constr_list, true);

	if (constr_list.getType() != MatchConstraintList::AND_LIST) 
		return false;

	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
	
	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		if (constraint.getID() != AtomMatchConstraint::CONSTRAINT_LIST)
			continue;

		const MatchConstraintList& constr_list = 
			*constraint.getValue<MatchConstraintList::SharedPointer>();

		if (constraint.getRelation() == MatchConstraint::EQUAL) {
			if (constr_list.getType() == MatchConstraintList::OR_LIST) {
				if (writeCTabV3000AtomList(os, atom, constr_list, false))
					return true;

				continue;
			}

			if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST)
				if (writeCTabV3000AtomList(os, atom, constr_list, true))
					return true;

			continue;					
		}

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL) {
			if (constr_list.getType() == MatchConstraintList::OR_LIST) {
				if (writeCTabV3000AtomList(os, atom, constr_list, true))
					return true;

				continue;
			}

			if (constr_list.getType() == MatchConstraintList::NOT_OR_LIST)
				if (writeCTabV3000AtomList(os, atom, constr_list, false))
					return true;
		}
	}

	return false;
}

bool Chem::MDLDataWriter::writeCTabV3000AtomList(std::ostream& os, const Atom& atom, 
												 const MatchConstraintList& constr_list, bool not_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	if (constr_list.getSize() == 0)
		return false;

	std::ostringstream oss;
	std::size_t list_size = 0;

	if (not_list)
		oss << AtomBlock::NOT_ATOM_LIST_TAG;

	oss << AtomBlock::ATOM_LIST_START_DELIMITER;

	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		if (constraint.getID() != AtomMatchConstraint::TYPE)
			continue;

		if (constraint.getRelation() != MatchConstraint::EQUAL)
			continue;

		unsigned int atom_type = getConstraintValue<unsigned int>(constraint, atom, &getType);

		if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_TYPE)
			continue;

		const std::string& symbol = AtomDictionary::getSymbol(atom_type);

		assert(!symbol.empty());

		if (list_size > 0)
			oss << AtomBlock::ATOM_LIST_SEPARATOR;

		oss << symbol;
	}

	if (list_size == 0)
		return false;

	oss << AtomBlock::ATOM_LIST_END_DELIMITER;

	writeCTabV3000PropertyStringValue(os, oss.str());

	return true;
}

void Chem::MDLDataWriter::writeCTabV3000AtomCoords(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	os << ' ' << std::fixed << std::showpoint; 

	if (coordsDim == 3) {
		const Math::Vector3D& coords = (multiConfExport ? confCoordinates[molgraph.getAtomIndex(atom)] : get3DCoordinates(atom));

		os << coords(0) << ' ' << coords(1) << ' ' << coords(2);

	} else if (coordsDim == 2) {
		const Math::Vector2D& coords = get2DCoordinates(atom);

		os << coords(0) << ' ' << coords(1) << " 0.0";

	} else
		os << "0.0 0.0 0.0";
}

void Chem::MDLDataWriter::writeCTabV3000AtomRxnAAMNumber(std::ostream& os, const Atom& atom) const
{
	os << ' ' << getAtomMappingID(atom);
}

void Chem::MDLDataWriter::writeCTabV3000AtomCharge(std::ostream& os, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	long charge = getFormalCharge(atom);

	if (charge != 0) {
		if (strictErrorChecking && (charge < AtomBlock::MIN_CHARGE || charge > AtomBlock::MAX_CHARGE))
			throw Base::IOError("MDLDataWriter: atom charge out of allowed range");
			
		os << ' ' << AtomBlock::CHARGE_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << charge;
	}
}

void Chem::MDLDataWriter::writeCTabV3000AtomRadicalType(std::ostream& os, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	unsigned int rad_type = AtomBlock::NO_RADICAL;

	switch (getRadicalType(atom)) {

		case RadicalType::NOT_RADICALIC:
			return;

		case RadicalType::SINGLET:
			rad_type = AtomBlock::SINGLET_RADICAL;
			break;

		case RadicalType::DOUBLET:
			rad_type = AtomBlock::DOUBLET_RADICAL;
			break;

		case RadicalType::TRIPLET:
			rad_type = AtomBlock::TRIPLET_RADICAL;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid radical type for atom");
			return;
	}

	os << ' ' << AtomBlock::RADICAL_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << rad_type;
}

void Chem::MDLDataWriter::writeCTabV3000AtomStereoParity(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	if (ignoreParity)
		return;

	unsigned int parity = AtomBlock::STEREO_PARITY_NONE;

	switch (calcMDLParity(atom, molgraph)) {
			
		case MDLParity::NONE:
			return;

		case MDLParity::ODD:
			parity = AtomBlock::STEREO_PARITY_ODD;
			break;

		case MDLParity::EVEN:
			parity = AtomBlock::STEREO_PARITY_EVEN;
			break;
			
		case MDLParity::EITHER:
			parity = AtomBlock::STEREO_PARITY_EITHER;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid atom stereo parity");
			return;
	}

	os << ' ' << AtomBlock::CONFIG_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << parity;
}

void Chem::MDLDataWriter::writeCTabV3000AtomMass(std::ostream& os, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	std::size_t isotope = getIsotope(atom);

	if (isotope != 0) 
		os << ' ' << AtomBlock::MASS_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << isotope;
}

void Chem::MDLDataWriter::writeCTabV3000AtomValence(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	long valence = calcValence(atom, molgraph);

	if (valence == 0)
		valence = AtomBlock::VALENCE_ZERO;

	os << ' ' << AtomBlock::VALENCE_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << valence;
}

void Chem::MDLDataWriter::writeCTabV3000AtomQueryHCount(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom, 
														const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	std::size_t expl_h_count = getExplicitAtomCount(atom, molgraph, AtomType::H);

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count, atom, molgraph, 
																			   &calcHydrogenCount))) {

		os << ' ' << AtomBlock::HYDROGEN_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::HYDROGEN_COUNT_E0;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 1, atom, molgraph, 
																			   &calcHydrogenCount))) {

		os << ' ' << AtomBlock::HYDROGEN_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::HYDROGEN_COUNT_GE1;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 2, atom, molgraph, 
																			   &calcHydrogenCount))) {

		os << ' ' << AtomBlock::HYDROGEN_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::HYDROGEN_COUNT_GE2;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 3, atom, molgraph, 
																			   &calcHydrogenCount))) {

		os << ' ' << AtomBlock::HYDROGEN_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::HYDROGEN_COUNT_GE3;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(expl_h_count + 4, atom, molgraph, 
																			   &calcHydrogenCount))) {

		os << ' ' << AtomBlock::HYDROGEN_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::HYDROGEN_COUNT_GE4;
	}
}

void Chem::MDLDataWriter::writeCTabV3000AtomRxnInfo(std::ostream& os, const Atom& atom) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	unsigned int rxn_center_info = getReactionCenterStatus(atom); 
	unsigned int inv_ret_flag = AtomBlock::RXN_INV_RET_UNDEF;

	switch (rxn_center_info & (ReactionCenterStatus::STEREO_INVERSION | ReactionCenterStatus::STEREO_RETENTION)) {

		case ReactionCenterStatus::STEREO_INVERSION:
			inv_ret_flag = AtomBlock::RXN_INV_RET_INVERSION;
			break;

		case ReactionCenterStatus::STEREO_RETENTION:
			inv_ret_flag = AtomBlock::RXN_INV_RET_RETENTION;
			
		default:
			break;
	}

	if (inv_ret_flag != AtomBlock::RXN_INV_RET_UNDEF)
		os << ' ' << AtomBlock::RXN_INV_RET_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << inv_ret_flag;

	if (rxn_center_info & ReactionCenterStatus::EXACT_CHANGE)
		os << ' ' << AtomBlock::RXN_CHANGE_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::RXN_CHANGE_EXACT;
}

void Chem::MDLDataWriter::writeCTabV3000AtomQuerySubstCount(std::ostream& os, const MolecularGraph& molgraph, const Atom& atom, 
															const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(0, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E0;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(1, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E1;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(2, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E2;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(3, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E3;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(4, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E4;
		return;
	}
	
	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT,
							MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(5, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_E5;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(6, atom, molgraph, &getHeavyBondCount))) {

		os << ' ' << AtomBlock::SUBSTITUTION_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::SUBSTITUTION_COUNT_GE6;
	}
}

void Chem::MDLDataWriter::writeCTabV3000AtomQueryUnsaturationFlag(std::ostream& os, const MolecularGraph& molgraph, 
																  const Atom& atom, const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::UNSATURATION, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Atom>(true, atom, molgraph, &isUnsaturated))) {

		os << ' ' << AtomBlock::UNSATURATION_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::UNSATURATION_ON;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::UNSATURATION, MatchConstraint::NOT_EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Atom>(false, atom, molgraph, &isUnsaturated))) {

		os << ' ' << AtomBlock::UNSATURATION_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::UNSATURATION_ON;
	}
}

void Chem::MDLDataWriter::writeCTabV3000AtomQueryRingBondCount(std::ostream& os, const MolecularGraph& molgraph, 
															   const Atom& atom, const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MOLFile::CTab::V3000;

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(0, atom, molgraph, &getRingBondCount))) {

		os << ' ' << AtomBlock::RING_BOND_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::RING_BOND_COUNT_E0;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(2, atom, molgraph, &getRingBondCount))) {

		os << ' ' << AtomBlock::RING_BOND_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::RING_BOND_COUNT_E2;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(3, atom, molgraph, &getRingBondCount))) {

		os << ' ' << AtomBlock::RING_BOND_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::RING_BOND_COUNT_E3;
		return;
	}

	if (findMatchConstraint(constr_list, AtomMatchConstraint::CONSTRAINT_LIST, AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL, 
							CalcOrSetConstraintValueMatches<std::size_t, Atom>(4, atom, molgraph, &getRingBondCount))) {

		os << ' ' << AtomBlock::RING_BOND_COUNT_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << AtomBlock::RING_BOND_COUNT_GE4;
	}
}

void Chem::MDLDataWriter::writeCTabV3000Bond(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond) const
{
	if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
		return;

	std::ostringstream line_oss;

	writeCTabV3000BondIndex(line_oss, molgraph, bond);

	const MatchConstraintList& constr_list = *getMatchConstraints(bond);
	std::size_t order = 1;

	if (hasOrder(bond))
		order = getOrder(bond);

	unsigned int bond_stereo = getBondStereo(bond);

	writeCTabV3000BondType(line_oss, order, constr_list);
	writeCTabV3000BondAtomIndices(line_oss, molgraph, bond, bondMemberSwapStereoFix && isReverseStereo(bond_stereo));
	writeCTabV3000BondStereo(line_oss, bond_stereo);
	writeCTabV3000BondQueryTopology(line_oss, molgraph, bond, constr_list);
	writeCTabV3000BondRxnCenterStatus(line_oss, bond);
	writeCTabV3000BondQueryStereoBoxFlag(line_oss, order, constr_list);

	writeV3000DataLine(os, line_oss.str());
}

void Chem::MDLDataWriter::writeCTabV3000BondIndex(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond) const
{
	os << (molgraph.getBondIndex(bond) + 1);
}

void Chem::MDLDataWriter::writeCTabV3000BondType(std::ostream& os, std::size_t order, const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MDL::MOLFile::CTab::V3000;

	os << ' ';

	if (constr_list.getSize() != 0) {
		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::ANY_ORDER))) {

			os << BondBlock::TYPE_ANY;
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::AROMATIC))) {

			os << BondBlock::TYPE_AROMATIC;
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::SINGLE | BondMatchConstraint::DOUBLE))) {

			os << BondBlock::TYPE_SINGLE_DOUBLE;
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC))) {

			os << BondBlock::TYPE_SINGLE_AROMATIC;
			return;
		}

		if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::ORDER, MatchConstraint::EQUAL, 
								SetConstraintValueMatches<unsigned int>(BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC))) {

			os << BondBlock::TYPE_DOUBLE_AROMATIC;
			return;
		}
	}

	switch (order) {

		case 1:
			os << BondBlock::TYPE_SINGLE;
			return;

		case 2:
			os << BondBlock::TYPE_DOUBLE;
			return;

		case 3:
			os << BondBlock::TYPE_TRIPLE;
			return;
					
		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid bond order");

			os << BondBlock::TYPE_SINGLE;
	}
}

void Chem::MDLDataWriter::writeCTabV3000BondAtomIndices(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond, 
														bool swap_atoms) const
{
	if (swap_atoms)
		os << ' ' << (molgraph.getAtomIndex(bond.getEnd()) + 1) << ' ' << (molgraph.getAtomIndex(bond.getBegin()) + 1);
	else
		os << ' ' << (molgraph.getAtomIndex(bond.getBegin()) + 1) << ' ' << (molgraph.getAtomIndex(bond.getEnd()) + 1);
}

void Chem::MDLDataWriter::writeCTabV3000BondStereo(std::ostream& os, unsigned int bond_stereo) const
{
	using namespace MDL;
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int stereo_flag = BondBlock::STEREO_NONE;

	switch (bond_stereo) {

		case BondStereoFlag::PLAIN:
			return;

		case BondStereoFlag::REVERSE_DOWN:
			if (bondMemberSwapStereoFix) {
				stereo_flag = BondBlock::STEREO_DOWN;
				break;
			}

		case BondStereoFlag::UP:
			stereo_flag = BondBlock::STEREO_UP;
			break;

		case BondStereoFlag::REVERSE_UP:
			if (bondMemberSwapStereoFix) {
				stereo_flag = BondBlock::STEREO_UP;
				break;
			}

		case BondStereoFlag::DOWN:
			stereo_flag = BondBlock::STEREO_DOWN;
			break;

		case BondStereoFlag::REVERSE_EITHER:
		case BondStereoFlag::EITHER:
			stereo_flag = BondBlock::STEREO_EITHER;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataWriter: invalid stereo bond type");
			return;
	}

	os << ' ' << BondBlock::CONFIG_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << stereo_flag;
}

void Chem::MDLDataWriter::writeCTabV3000BondQueryTopology(std::ostream& os, const MolecularGraph& molgraph, const Bond& bond, 
														  const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MDL::MOLFile::CTab::V3000;

	if (constr_list.getSize() == 0)
		return;

	if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Bond>(true, bond, molgraph, &isRingBond))) {

		os << ' ' << BondBlock::TOPOLOGY_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << BondBlock::TOPOLOGY_RING;
		return;
	}

	if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Bond>(false, bond, molgraph, &isRingBond))) {

		os << ' ' << BondBlock::TOPOLOGY_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << BondBlock::TOPOLOGY_CHAIN;
		return;
	}

	if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::NOT_EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Bond>(true, bond, molgraph, &isRingBond))) {

		os << ' ' << BondBlock::TOPOLOGY_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << BondBlock::TOPOLOGY_CHAIN;
		return;
	}

	if (findMatchConstraint(constr_list, BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::NOT_EQUAL, 
							CalcOrSetConstraintValueMatches<bool, Bond>(false, bond, molgraph, &isRingBond))) {

		os << ' ' << BondBlock::TOPOLOGY_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << BondBlock::TOPOLOGY_RING;
	}
}

void Chem::MDLDataWriter::writeCTabV3000BondRxnCenterStatus(std::ostream& os, const Bond& bond) const
{
	using namespace MDL;
	using namespace MDL::MOLFile::CTab::V3000;

	int rxn_center_status = BondBlock::RXN_STATUS_UNMARKED;

	switch (getReactionCenterStatus(bond) 
			& ~(ReactionCenterStatus::STEREO_INVERSION | ReactionCenterStatus::STEREO_RETENTION | 
				ReactionCenterStatus::EXACT_CHANGE)) {

		case ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::NO_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_NO_CENTER;
			break;

		case ReactionCenterStatus::NO_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_NO_CHANGE;
			break;

		case ReactionCenterStatus::BOND_ORDER_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_ORDER_CHANGE;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE;
			break;

		case ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::BOND_ORDER_CHANGE |
			ReactionCenterStatus::IS_CENTER:
			rxn_center_status = BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE + 
				BondBlock::RXN_STATUS_IS_CENTER;
			break;

		default:
			return;
	}

	os << ' ' << BondBlock::RXN_CENTER_STATUS_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << rxn_center_status;
}

void Chem::MDLDataWriter::writeCTabV3000BondQueryStereoBoxFlag(std::ostream& os, std::size_t order, 
															   const MatchConstraintList& constr_list) const
{
	using namespace MDL;
	using namespace MDL::MOLFile::CTab::V3000;

	if (constr_list.getSize() == 0)
		return;

	if (order != 2)
		return;

	if (findMatchConstraint(constr_list,
							BondMatchConstraint::CONSTRAINT_LIST, BondMatchConstraint::CONFIGURATION,
							MatchConstraint::EQUAL, HasUnsetConstraintValue())) {

		os << ' ' << BondBlock::STEREO_BOX_KEYWORD << V3000::KEYWORD_VALUE_SEPARATOR << BondBlock::DB_STEREO_MATCH;
	}
}

void Chem::MDLDataWriter::writeCTabV3000PropertyStringValue(std::ostream& os, const std::string& str) const
{
	using namespace MDL;

	std::string::const_iterator str_beg = str.begin();
	std::string::const_iterator str_end = str.end();

	if (!str.empty() 
		&& str[0] != V3000::VALUE_LIST_START_DELIM 
		&& str[0] != V3000::STRING_QUOTE_CHAR 
		&& std::find_if(str_beg, str_end, boost::bind(Internal::IsWhitespace(), _1)) == str_end) {
		
		os << str;
		return;
	}

	os << V3000::STRING_QUOTE_CHAR;

	for (std::string::const_iterator it = str_beg; str_beg != str_end; ++it) {
		char c = *it;

		if (c == V3000::STRING_QUOTE_CHAR)
			os << V3000::STRING_QUOTE_CHAR;

		os << c;
	}

	os << V3000::STRING_QUOTE_CHAR;
}

void Chem::MDLDataWriter::writeRXNV3000Reaction(std::ostream& os, const Reaction& rxn)
{
	using namespace MDL::RXNFile;

	writeRXNV3000CountsLine(os, rxn);

	writeV3000BlockBegin(os, V3000::REACTANT_BLOCK_KEY);

	std::for_each(rxn.getComponentsBegin(ReactionRole::REACTANT), rxn.getComponentsEnd(ReactionRole::REACTANT), 
				  boost::bind(&MDLDataWriter::writeRXNV3000ReactionComponent, this, boost::ref(os), _1));

	writeV3000BlockEnd(os, V3000::REACTANT_BLOCK_KEY);

	writeV3000BlockBegin(os, V3000::PRODUCT_BLOCK_KEY);

	std::for_each(rxn.getComponentsBegin(ReactionRole::PRODUCT), rxn.getComponentsEnd(ReactionRole::PRODUCT), 
				  boost::bind(&MDLDataWriter::writeRXNV3000ReactionComponent, this, boost::ref(os), _1));

	writeV3000BlockEnd(os, V3000::PRODUCT_BLOCK_KEY);

	writeMDLLine(os, MDL::V3000::DATA_END_TAG, "MDLDataWriter: error while writing rxn-file end tag", false, false, false);
}

void Chem::MDLDataWriter::writeRXNV3000CountsLine(std::ostream& os, const Reaction& rxn) const
{
	using namespace MDL::RXNFile;

	std::ostringstream counts_oss;

	counts_oss << V3000::COUNTS_TAG << ' ' << rxn.getNumComponents(ReactionRole::REACTANT) << ' ' << rxn.getNumComponents(ReactionRole::PRODUCT);

	writeV3000DataLine(os, counts_oss.str());
}

void Chem::MDLDataWriter::writeRXNV3000ReactionComponent(std::ostream& os, const MolecularGraph& comp)
{
	getAtomCoordsDim(comp);

	writeCTabV3000(os, comp, true);
}

void Chem::MDLDataWriter::writeV3000BlockBegin(std::ostream& os, const std::string& type_key) const
{
	using namespace MDL;

	os << V3000::LINE_PREFIX << V3000::BLOCK_BEGIN_TAG << ' ' << type_key;

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeV3000BlockEnd(std::ostream& os, const std::string& type_key) const
{
	using namespace MDL;

	os << V3000::LINE_PREFIX << V3000::BLOCK_END_TAG << ' ' << type_key;

	writeMDLEOL(os);
}

void Chem::MDLDataWriter::writeV3000DataLine(std::ostream& os, const std::string& data_line) const
{   
	using namespace Internal;
	using namespace MDL;

	std::size_t phys_line_start = 0;
	std::size_t data_line_len = data_line.length();

	while (true) {
		os << V3000::LINE_PREFIX;

		if (data_line_len - phys_line_start <= MAX_V3000_LINE_LENGTH) {
			writeSubstring(os, data_line, phys_line_start, data_line_len);
			writeMDLEOL(os);
			return;
		}

		writeSubstring(os, data_line, phys_line_start, phys_line_start + MAX_V3000_LINE_LENGTH - 1);
		
		os << V3000::LINE_CONTINUATION_MARK;

		writeMDLEOL(os);

		phys_line_start += MAX_V3000_LINE_LENGTH - 1;
	}
}

unsigned int Chem::MDLDataWriter::getBondStereo(const Bond& bond) const
{	
	if (coordsDim == 3) 
		return BondStereoFlag::PLAIN;

	return get2DStereoFlag(bond);
}

bool Chem::MDLDataWriter::isReverseStereo(unsigned int stereo_flag) const
{
	switch (stereo_flag) {

		case BondStereoFlag::REVERSE_DOWN:
		case BondStereoFlag::REVERSE_UP:
		case BondStereoFlag::REVERSE_EITHER:
			return true;

		default:
			return false;
	}
}
