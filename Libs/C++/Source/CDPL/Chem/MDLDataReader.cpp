/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MDLDataReader.cpp 
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

#include <algorithm>
#include <sstream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <istream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/RadicalType.hpp"
#include "CDPL/Chem/MDLDataFormatVersion.hpp"
#include "CDPL/Chem/MDLParity.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/StringUtilities.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "MDLDataReader.hpp"
#include "MDLFormatData.hpp"


using namespace CDPL;


namespace
{

	inline void skipMDLChars(std::istream& is, std::size_t count, const char* err_msg)
	{
		Internal::skipChars(is, count, err_msg, Chem::MDL::END_OF_LINE);
	}

	inline void skipMDLLines(std::istream& is, std::size_t count, const char* err_msg)
	{
		Internal::skipLines(is, count, err_msg, Chem::MDL::END_OF_LINE);
	}
		
	inline std::string& readMDLLine(std::istream& is, std::string& line, const char* err_msg, bool trim = false, 
									bool check_ll = false, std::size_t max_llen = Chem::MDL::MAX_LINE_LENGTH)
	{
		return Internal::readLine(is, line, err_msg, trim, check_ll, max_llen, Chem::MDL::END_OF_LINE);
	}

	inline std::string& readMDLString(std::istream& is, std::size_t field_size, std::string& str, bool clear,
									  const char* err_msg, bool trim = true)
	{
		return Internal::readString(is, field_size, str, clear, err_msg, trim, Chem::MDL::END_OF_LINE);
	}

	template <typename T, std::size_t FieldSize>
	inline T readMDLNumber(std::istream& is, const char* err_msg, bool throw_ex = true, 
						   const T empty_def_val = T(0), const T err_def_val = T(0))
	{
		return Internal::readNumber<T, FieldSize>(is, err_msg, throw_ex, empty_def_val, err_def_val, Chem::MDL::END_OF_LINE);
	}

	const unsigned int RXN_FILE_ID_LENGTH = Chem::MDL::RXNFile::RXN_FILE_IDENTIFIER.length() + 1;
}


bool Chem::MDLDataReader::readMolecule(std::istream& is, Molecule& mol, bool read_data)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	std::size_t atom_idx_offs = mol.getNumAtoms();
	std::size_t bond_idx_offs = mol.getNumBonds();

	atomMappingIDOffset = getMaxReactionAtomMappingID(mol);

	readMOLHeaderBlock(is, mol);
	readMOLCTab(is, mol);

	if (read_data)
		readSDFData(is, mol);

	if (multiConfImport) {
		MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

		if (!mc_input_proc)
			return true;

		MolecularGraph* tgt_molgraph;

		if (atom_idx_offs == 0) {
			tgt_molgraph = &mol;

		} else {
			if (!confTargetFragment)
				confTargetFragment.reset(new Fragment());
			else
				confTargetFragment->clear();

			tgt_molgraph = confTargetFragment.get();

			std::for_each(mol.getAtomsBegin() + atom_idx_offs, mol.getAtomsEnd(), boost::bind(&Fragment::addAtom, confTargetFragment.get(), _1));
			std::for_each(mol.getBondsBegin() + bond_idx_offs, mol.getBondsEnd(), boost::bind(&Fragment::addBond, confTargetFragment.get(), _1));
			
			confTargetFragment->copyProperties(mol);
		}

		if (!mc_input_proc->init(*tgt_molgraph))
			return true;

		if (!confTestMolecule)
			confTestMolecule.reset(new BasicMolecule());

		while (hasMoreData(is)) {
			std::istream::pos_type last_spos = is.tellg();
			confTestMolecule->clear();

			readMOLHeaderBlock(is, *confTestMolecule);
			readMOLCTab(is, *confTestMolecule);

			if (read_data)
				readSDFData(is, *confTestMolecule);

			if (!mc_input_proc->addConformation(*tgt_molgraph, *confTestMolecule)) {
				is.seekg(last_spos);
				return true;
			}
		}
	}

	return true;
}

bool Chem::MDLDataReader::readMOLFile(std::istream& is, Molecule& mol)
{
	return readMolecule(is, mol, false);
}

bool Chem::MDLDataReader::readSDFileRecord(std::istream& is, Molecule& mol)
{
	return readMolecule(is, mol, true);
}

bool Chem::MDLDataReader::readRXNFile(std::istream& is, Reaction& rxn)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	atomMappingIDOffset = getMaxReactionAtomMappingID(rxn);

	readRXNHeaderBlock(is, rxn);
	readRXNReaction(is, rxn);

	return true;
}

bool Chem::MDLDataReader::readRDFileRecord(std::istream& is, Reaction& rxn)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	readRDFHeaderBlock(is);

	if (!hasMoreData(is))
		return false;

	readRDFReaction(is, rxn);
	readRDFData(is, rxn);

	return true;
}

bool Chem::MDLDataReader::skipMolecule(std::istream& is, bool skip_data)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	if (!multiConfImport) {
		skipMOLHeaderBlock(is);
		skipMOLCTab(is);

		if (skip_data)
			skipSDFData(is);

		return true;
	}

	MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

	if (!mc_input_proc) {
		skipMOLHeaderBlock(is);
		skipMOLCTab(is);

		if (skip_data)
			skipSDFData(is);

		return true;
	}

	if (!confTargetMolecule)
		confTargetMolecule.reset(new BasicMolecule());
	else
		confTargetMolecule->clear();

	atomMappingIDOffset = 0;

	readMOLHeaderBlock(is, *confTargetMolecule);
	readMOLCTab(is, *confTargetMolecule);

	if (skip_data)
		readSDFData(is, *confTargetMolecule);

	if (!mc_input_proc->init(*confTargetMolecule))
		return true;

	if (!confTestMolecule)
		confTestMolecule.reset(new BasicMolecule());

	while (hasMoreData(is)) {
		std::istream::pos_type last_spos = is.tellg();
		confTestMolecule->clear();

		readMOLHeaderBlock(is, *confTestMolecule);
		readMOLCTab(is, *confTestMolecule);

		if (skip_data)
			readSDFData(is, *confTestMolecule);

		if (!mc_input_proc->isConformation(*confTargetMolecule, *confTestMolecule)) {
			is.seekg(last_spos);
			return true;
		}
	}

	return true;
}

bool Chem::MDLDataReader::skipMOLFile(std::istream& is)
{
	return skipMolecule(is, false);
}

bool Chem::MDLDataReader::skipSDFileRecord(std::istream& is)
{
	return skipMolecule(is, true);
}

bool Chem::MDLDataReader::skipRXNFile(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	skipRXNHeaderBlock(is);
	skipRXNReaction(is);

	return true;
}

bool Chem::MDLDataReader::skipRDFileRecord(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	skipRDFHeaderBlock(is);

	if (!hasMoreData(is))
		return false;
	
	skipRDFReaction(is);
	skipRDFData(is);

	return true;
}

bool Chem::MDLDataReader::hasMoreData(std::istream& is) const
{
	return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

void Chem::MDLDataReader::init(std::istream& is)
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
	ignoreParity        = getMDLIgnoreParityParameter(ioBase); 
	trimStrings         = getMDLTrimStringsParameter(ioBase); 
	trimLines           = getMDLTrimLinesParameter(ioBase); 
	checkLineLength     = getCheckLineLengthParameter(ioBase); 
	multiConfImport     = getMultiConfImportParameter(ioBase);

	is.imbue(std::locale::classic());
}

void Chem::MDLDataReader::readMOLHeaderBlock(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile;

	// Header line 1

	readMDLLine(is, line, "MDLDataReader: error while reading molecule name from molfile header block", 
				trimLines, checkLineLength);
	setName(mol, line);

	// Header line 2

	readMDLString(is, 2, tmpString, true, "MDLDataReader: error while reading user initials from molfile header block", trimStrings);
	setMDLUserInitials(mol, tmpString);

	readMDLString(is, 8, tmpString, true, "MDLDataReader: error while reading program name from molfile header block", trimStrings);
	setMDLProgramName(mol, tmpString);

	using namespace boost::posix_time;
	using namespace boost::gregorian;
  
	unsigned short month = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp month part from molfile header block", 
															strictErrorChecking, 100);
	unsigned short day = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp day part from molfile header block", 
														  strictErrorChecking, 100);
	unsigned short year = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp year part from molfile header block", 
														   strictErrorChecking, 100);
	unsigned short hour = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp hour part from molfile header block", 
														   strictErrorChecking, 100);
	unsigned short minute = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp minute part from molfile header block", 
															 strictErrorChecking, 100);

	if (month != 100 || day != 100 || year != 100 || hour != 100 || minute != 100) {
		try {
			date date_part(greg_year(year + (year > 50 ? 1900 : 2000)), greg_month(month), greg_day(day));
			time_duration time_part = hours(hour) + minutes(minute);
			time_duration duration = ptime(date_part, time_part) - ptime(date(1970, 1, 1));

			setMDLTimestamp(mol, duration.total_seconds());

		} catch (const std::out_of_range&) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid timestamp in molfile header block");
		}
	}

	readMDLString(is, 2, tmpString, true, "MDLDataReader: error while reading dimension code from molfile header block");
	
	if (tmpString == Header::DIM_CODE_2D)
		coordsDim = 2;

	else if (tmpString == Header::DIM_CODE_3D)
		coordsDim = 3;

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid dimension code in molfile header block");

	else
		coordsDim = 3;

	setMDLDimensionality(mol, coordsDim); 

	setMDLScalingFactor1(mol, readMDLNumber<long, 2>(is, "MDLDataReader: error while reading scaling factor1 from molfile header block", 
													 strictErrorChecking));
	setMDLScalingFactor2(mol, readMDLNumber<double, 10>(is, "MDLDataReader: error while reading scaling factor2 from molfile header block ", 
														strictErrorChecking));
	setMDLEnergy(mol, readMDLNumber<double, 12>(is, "MDLDataReader: error while reading energy from molfile header block ", 
												strictErrorChecking));

	std::size_t reg_no = readMDLNumber<std::size_t, 6>(is, "MDLDataReader: error while reading registry number from molfile header block ", 
													   strictErrorChecking, ~std::size_t(0), ~std::size_t(0));
	if (reg_no <= 999999)
		setMDLRegistryNumber(mol, reg_no); 

	skipMDLLines(is, 1, "MDLDataReader: error while reading molfile header block");

	// Header line 3

	readMDLLine(is, line, "MDLDataReader: error while reading comment line from molfile header block", 
				trimLines, checkLineLength);
	setMDLComment(mol, line);
}

void Chem::MDLDataReader::skipMOLHeaderBlock(std::istream& is)
{
	skipMDLLines(is, 3, "MDLDataReader: error while skipping molfile header block");
}

void Chem::MDLDataReader::readMOLCTab(std::istream& is, Molecule& mol)
{
	readCTabCountsLine(is, mol);

	if (ctabVersion == MDLDataFormatVersion::V3000) {
		readCTabV3000(is, mol);
		readV3000DataEndTag(is);

	} else
		readCTabV2000(is, mol);
}

void Chem::MDLDataReader::skipMOLCTab(std::istream& is)
{
	skipCTabCountsLine(is);

	if (ctabVersion == MDLDataFormatVersion::V3000) 
		skipV3000Data(is);
	else
		skipCTabV2000(is);
}

void Chem::MDLDataReader::readCTabCountsLine(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile;

	atomCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of atoms from counts-line"); 
	bondCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of bonds from counts-line"); 
	atomListCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of atom lists from counts-line",
												  strictErrorChecking); 

	skipMDLChars(is, 3, "MDLDataReader: error while reading counts-line");

	unsigned int chiral_flag = readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading chiral flag from counts-line", 
															  strictErrorChecking); 

	if (strictErrorChecking && chiral_flag != CountsLine::CHIRAL_FLAG_OFF && chiral_flag != CountsLine::CHIRAL_FLAG_ON)
		throw Base::IOError("MDLDataReader: invalid chiral flag value in counts-line");

	setMDLChiralFlag(mol, (chiral_flag == CountsLine::CHIRAL_FLAG_ON));

	sTextEntryCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of stext entries from counts-line", 
													strictErrorChecking); 

	skipMDLChars(is, 12, "MDLDataReader: error while reading counts-line");

	propertyCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of properties from counts-line", 
												  strictErrorChecking, 0, 999); 

	readMDLString(is, 6, tmpString, true, "MDLDataReader: error while reading version string from counts-line");

	if (strictErrorChecking && !tmpString.empty() 
		&& tmpString != CountsLine::V2000_TAG 
		&& tmpString != CountsLine::V3000_TAG)
		throw Base::IOError("MDLDataReader: invalid version string in counts-line");

	ctabVersion = (tmpString == CountsLine::V3000_TAG ? MDLDataFormatVersion::V3000 
				   : tmpString == CountsLine::V2000_TAG ? MDLDataFormatVersion::V2000 
				   : MDLDataFormatVersion::UNDEF);

	setMDLCTABVersion(mol, ctabVersion); 

	skipMDLLines(is, 1, "MDLDataReader: error while reading counts-line");
}

void Chem::MDLDataReader::skipCTabCountsLine(std::istream& is)
{
	using namespace MDL::MOLFile;

	atomCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of atoms from counts-line"); 
	bondCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of bonds from counts-line"); 
	atomListCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of atom lists from counts-line",
												  strictErrorChecking); 

	skipMDLChars(is, 6, "MDLDataReader: error while reading counts-line");

	sTextEntryCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of stext entries from counts-line", 
													strictErrorChecking); 

	skipMDLChars(is, 12, "MDLDataReader: error while reading counts-line");

	propertyCount = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of properties from counts-line", 
												  strictErrorChecking, 0, 999); 

	readMDLString(is, 6, tmpString, true, "MDLDataReader: error while reading version string from counts-line");

	if (strictErrorChecking && !tmpString.empty() 
		&& tmpString != CountsLine::V2000_TAG 
		&& tmpString != CountsLine::V3000_TAG)
		throw Base::IOError("MDLDataReader: invalid version string in counts-line");

	ctabVersion = (tmpString == CountsLine::V3000_TAG ? MDLDataFormatVersion::V3000 
				   : tmpString == CountsLine::V2000_TAG ? MDLDataFormatVersion::V2000 
				   : MDLDataFormatVersion::UNDEF);

	skipMDLLines(is, 1, "MDLDataReader: error while reading counts-line");
}

void Chem::MDLDataReader::readCTabV2000(std::istream& is, Molecule& mol)
{
	std::size_t atom_index_offs = mol.getNumAtoms();

	atomQueryHCountList.clear();
	stereoAtoms.clear();

	readCTabV2000AtomBlock(is, mol);
	readCTabV2000BondBlock(is, mol, atom_index_offs);
	readCTabV2000AListBlock(is, mol, atom_index_offs);
	readCTabV2000STextBlock(is);
	readCTabV2000PropertyBlock(is, mol, atom_index_offs);

	addAtomQueryHCountConstraints();	

	if (!ignoreParity)
		convertParities(mol);
}

void Chem::MDLDataReader::skipCTabV2000(std::istream& is)
{
	skipMDLLines(is, atomCount, "MDLDataReader: error while skipping ctab atoms");
	skipMDLLines(is, bondCount, "MDLDataReader: error while skipping ctab bonds");
	skipMDLLines(is, atomListCount, "MDLDataReader: error while skipping atom list block");
	skipMDLLines(is, sTextEntryCount * 2, "MDLDataReader: error while skipping stext block");

	skipCTabV2000PropertyBlock(is);
}

void Chem::MDLDataReader::readCTabV2000AtomBlock(std::istream& is, Molecule& mol)
{
	for (std::size_t i = 0; i < atomCount; i++)
		readCTabV2000Atom(is, mol);
}

void Chem::MDLDataReader::readCTabV2000BondBlock(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	for (std::size_t i = 0; i < bondCount; i++)
		readCTabV2000Bond(is, mol, atom_index_offs);
}

void Chem::MDLDataReader::readCTabV2000AListBlock(std::istream& is, Molecule& mol, std::size_t atom_index_offs)
{
	for (std::size_t i = 0; i < atomListCount; i++)
		readCTabV2000AList(is, mol, atom_index_offs);
}

void Chem::MDLDataReader::readCTabV2000STextBlock(std::istream& is) const
{
	skipMDLLines(is, sTextEntryCount * 2, "MDLDataReader: error while reading stext block");
}

void Chem::MDLDataReader::readCTabV2000PropertyBlock(std::istream& is, Molecule& mol, std::size_t atom_index_offs)
{
	using namespace MDL;
	using namespace MOLFile::CTab::V2000;

	bool exit = false;

	for (std::size_t i = 0; !exit && (ctabVersion == MDLDataFormatVersion::V2000 || i < propertyCount); i++) {
		std::size_t skip_cnt = 1;

		readMDLString(is, 3, tmpString, true, "MDLDataReader: error while reading property line prefix", false);

		if (tmpString == PropertyBlock::ATOM_ALIAS_PREFIX || tmpString == PropertyBlock::GROUP_ABBREV_PREFIX)
			skip_cnt = 2;

		else {
			readMDLString(is, 3, tmpString, false, "MDLDataReader: error while reading property line prefix", false);

			if (tmpString == PropertyBlock::LINE_SKIP_PREFIX)
				skip_cnt += readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading line skip count in property block");

			else if (tmpString == PropertyBlock::CHARGE_PREFIX)
				readCTabV2000ChargeProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::RADICAL_PREFIX)
				readCTabV2000RadicalProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::ISOTOPE_PREFIX)
				readCTabV2000IsotopeProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::RING_BOND_COUNT_PREFIX)
				readCTabV2000RingBondCountProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::SUBSTITUTION_COUNT_PREFIX)
				readCTabV2000SubstCountProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::UNSATURATION_PREFIX)
				readCTabV2000UnsaturationProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::ATOM_LIST_PREFIX)
				readCTabV2000AtomListProperties(is, mol, atom_index_offs);

			else if (tmpString == PropertyBlock::REGISTRY_NO_PREFIX)
				readCTabV2000RegistryNumberProperty(is, mol);

			else if (tmpString == MOLFile::END_TAG || tmpString == MOLFile::END_TAG_ALT)
				exit = true;

			else {}
		}

		skipMDLLines(is, skip_cnt, "MDLDataReader: error while reading property block");
	}
}

void Chem::MDLDataReader::skipCTabV2000PropertyBlock(std::istream& is)
{
	using namespace MDL;
	using namespace MOLFile::CTab::V2000;

	bool exit = false;

	for (std::size_t i = 0; !exit && (ctabVersion == MDLDataFormatVersion::V2000 || i < propertyCount); i++) {
		std::size_t skip_cnt = 1;

		readMDLString(is, 3, tmpString, true, "MDLDataReader: error while reading property line prefix", false);

		if (tmpString == PropertyBlock::ATOM_ALIAS_PREFIX || tmpString == PropertyBlock::GROUP_ABBREV_PREFIX)
			skip_cnt = 2;

		else {
			readMDLString(is, 3, tmpString, false, "MDLDataReader: error while reading property line prefix", false);

			if (tmpString == PropertyBlock::LINE_SKIP_PREFIX)
				skip_cnt += readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading property block line skip count");

			else if (tmpString == MOLFile::END_TAG || tmpString == MOLFile::END_TAG_ALT)
				exit = true;
		}

		skipMDLLines(is, skip_cnt, "MDLDataReader: error while skipping property block");
	}
}

void Chem::MDLDataReader::readCTabV2000Atom(std::istream& is, Molecule& mol)
{
	Atom& atom = mol.addAtom();
	
	readCTabV2000AtomCoords(is, atom);

	skipMDLChars(is, 1, "MDLDataReader: error while reading atom block");

	readCTabV2000AtomSymbol(is, atom);
	readCTabV2000AtomMass(is, atom);
	readCTabV2000AtomCharge(is, atom);
	readCTabV2000AtomParity(is, atom);
	readCTabV2000AtomQueryHCount(is, atom);
	readCTabV2000AtomStereoBoxFlag(is, atom);
	readCTabV2000AtomValence(is, atom);

	skipMDLChars(is, 9, "MDLDataReader: error while reading atom block");

	readCTabV2000AtomRxnInfo(is, atom);

	skipMDLLines(is, 1, "MDLDataReader: error while reading atom block");	
}

void Chem::MDLDataReader::readCTabV2000AtomCoords(std::istream& is, Atom& atom) const
{
	double x_coords = readMDLNumber<double, 10>(is, "MDLDataReader: error while reading atom x coordinate");  
	double y_coords = readMDLNumber<double, 10>(is, "MDLDataReader: error while reading atom y coordinate");  

	if (coordsDim == 3) {
		Math::Vector3D coords;

		coords(0) = x_coords;
		coords(1) = y_coords;
		coords(2) = readMDLNumber<double, 10>(is, "MDLDataReader: error while reading atom z coordinate"); 

		set3DCoordinates(atom, coords);

	} else {
		skipMDLChars(is, 10, "MDLDataReader: error while reading atom block");

		Math::Vector2D coords;

		coords(0) = x_coords;
		coords(1) = y_coords;

		set2DCoordinates(atom, coords);
	}
}

void Chem::MDLDataReader::readCTabV2000AtomSymbol(std::istream& is, Atom& atom) 
{
	readMDLString(is, 3, tmpString, true, "MDLDataReader: error while reading atom symbol", trimStrings);

	setSymbol(atom, tmpString);

	unsigned int atom_type = AtomDictionary::getType(tmpString);

	setType(atom, atom_type);

	switch (atom_type) {

		case AtomType::Q:
		case AtomType::A:
		case AtomType::ANY: {
			MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList());

			constr_list_ptr->addElement(AtomMatchConstraint::TYPE,
										MatchConstraint::EQUAL,
										atom_type);

			setMatchConstraints(atom, constr_list_ptr);
		}

		default:
			break;
	}
}

void Chem::MDLDataReader::readCTabV2000AtomMass(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	int mass_diff = readMDLNumber<int, 2>(is, "MDLDataReader: error while reading atom isotope mass difference", strictErrorChecking);

	if (strictErrorChecking && (mass_diff < AtomBlock::MIN_MASS_DIFF || mass_diff > AtomBlock::MAX_MASS_DIFF))
		throw Base::IOError("MDLDataReader: atom isotope mass difference value out of allowed range");

	if (mass_diff != 0) {
		long iso = AtomDictionary::getMostAbundantIsotope(getType(atom)) + mass_diff;

		if (iso > 0)
			setIsotope(atom, iso);
	}
}

void Chem::MDLDataReader::readCTabV2000AtomCharge(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading atom charge", strictErrorChecking)) {

		case AtomBlock::CHARGE_0:
			setFormalCharge(atom, 0);
			return;

		case AtomBlock::CHARGE_P1:
			setFormalCharge(atom, 1);
			return;

		case AtomBlock::CHARGE_P2:
			setFormalCharge(atom, 2);
			return;

		case AtomBlock::CHARGE_P3:
			setFormalCharge(atom, 3);
			return;

		case AtomBlock::CHARGE_M1:
			setFormalCharge(atom, -1);
			return;

		case AtomBlock::CHARGE_M2:
			setFormalCharge(atom, -2);
			return;

		case AtomBlock::CHARGE_M3:
			setFormalCharge(atom, -3);
			return;

		case AtomBlock::DOUBLET_RADICAL:
			setRadicalType(atom, RadicalType::DOUBLET);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid atom charge specification");
	}	
}

void Chem::MDLDataReader::readCTabV2000AtomParity(std::istream& is, Atom& atom)
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int parity = MDLParity::NONE;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading atom stereo parity", strictErrorChecking)) {
			
		case AtomBlock::STEREO_PARITY_NONE:
			break;

		case AtomBlock::STEREO_PARITY_ODD:
			parity = MDLParity::ODD;
			break;

		case AtomBlock::STEREO_PARITY_EVEN:
			parity = MDLParity::EVEN;
			break;

		case AtomBlock::STEREO_PARITY_EITHER:
			parity = MDLParity::EITHER;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid atom stereo parity specification");
	}

	setMDLParity(atom, parity);

	if (!ignoreParity)
		stereoAtoms.push_back(&atom);
}

void Chem::MDLDataReader::readCTabV2000AtomQueryHCount(std::istream& is, Atom& atom)
{
	using namespace MDL::MOLFile::CTab::V2000;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading query hydrogen count for atom", 
										   strictErrorChecking)) {

		case AtomBlock::HYDROGEN_COUNT_UNDEF:
			return;

		case AtomBlock::HYDROGEN_COUNT_E0:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 0));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE1:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 1));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE2:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 2));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE3:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 3));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE4:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 4));
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid query hydrogen count specification for atom");
	}
}

void Chem::MDLDataReader::readCTabV2000AtomStereoBoxFlag(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int db_stereo_box_flag = readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading atom stereo box flag", 
																	 strictErrorChecking);

	if (db_stereo_box_flag == AtomBlock::DB_STEREO_IGNORE)
		return;

	if (db_stereo_box_flag == AtomBlock::DB_STEREO_MATCH) 
		setMDLStereoCareFlag(atom, true);

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid atom stereo box flag");
}

void Chem::MDLDataReader::readCTabV2000AtomValence(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int valence = readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading atom valence", strictErrorChecking);

	switch (valence) {

		case AtomBlock::VALENCE_UNDEF:
			return;

		case AtomBlock::VALENCE_ZERO:
			//atom.setProperty(AtomProperty::TOTAL_VALENCE, std::size_t(0));
			return;

		default:
			if (valence <= AtomBlock::VALENCE_MAX) {
				//atom.setProperty(AtomProperty::TOTAL_VALENCE, std::size_t(valence));

			} else if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid atom valence specification");	
	}
}
	
void Chem::MDLDataReader::readCTabV2000AtomRxnInfo(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t aam_id = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading reaction atom atom mapping number",
													   strictErrorChecking);

	if (aam_id > 0)
		setReactionAtomMappingID(atom, aam_id + atomMappingIDOffset);

	unsigned int rxn_center_status = ReactionCenterStatus::NONE;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading reaction inversion/retention flag for atom", 
										   strictErrorChecking)) {

		case AtomBlock::RXN_INV_RET_UNDEF:
			break;

		case AtomBlock::RXN_INV_RET_INVERSION:
			rxn_center_status = ReactionCenterStatus::STEREO_INVERSION;
			break;

		case AtomBlock::RXN_INV_RET_RETENTION:
			rxn_center_status = ReactionCenterStatus::STEREO_RETENTION;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid reaction inversion/retention flag for atom");
	}

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading reaction change flag for atom")) {

		case AtomBlock::RXN_CHANGE_UNDEF:
			break;

		case AtomBlock::RXN_CHANGE_EXACT:
			rxn_center_status |= ReactionCenterStatus::EXACT_CHANGE;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid reaction change flag for atom");
	}

	setReactionCenterStatus(atom, rxn_center_status);
}

void Chem::MDLDataReader::readCTabV2000Bond(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	Bond& bond = createCTabV2000Bond(is, mol, atom_index_offs);

	MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList());

	std::size_t order = readCTabV2000BondType(is, bond, *constr_list_ptr);

	if (order == 2) {
		bool stereo_box_flag1 = getMDLStereoCareFlag(bond.getBegin());
		bool stereo_box_flag2 = getMDLStereoCareFlag(bond.getEnd());

		if (stereo_box_flag1 && stereo_box_flag2) 
			constr_list_ptr->addElement(BondMatchConstraint::CONFIGURATION, MatchConstraint::EQUAL);
	}

	readCTabV2000BondStereo(is, bond);

	skipMDLChars(is, 3, "MDLDataReader: error while reading bond block");

	readCTabV2000BondQueryTopology(is, *constr_list_ptr);

	if (constr_list_ptr->getSize() != 0)
		setMatchConstraints(bond, constr_list_ptr);

	readCTabV2000BondRxnCenterStatus(is, bond);

	skipMDLLines(is, 1, "MDLDataReader: error while reading bond block");	
}

Chem::Bond& Chem::MDLDataReader::createCTabV2000Bond(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t atom1_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading bond start atom index");

	if (atom1_index == 0 || atom1_index > max_atom_index)
		throw Base::IOError("MDLDataReader: bond start atom index out of bounds");

	std::size_t atom2_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading bond target atom index");

	if (atom2_index == 0 || atom2_index > max_atom_index)
		throw Base::IOError("MDLDataReader: bond target atom index out of bounds");

	return mol.addBond(atom1_index - 1 + atom_index_offs, atom2_index - 1 + atom_index_offs);
}

std::size_t Chem::MDLDataReader::readCTabV2000BondType(std::istream& is, Bond& bond, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t order = 1;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading bond type specification")) {

		case BondBlock::TYPE_SINGLE:
			break;

		case BondBlock::TYPE_DOUBLE:
			order = 2;
			break;

		case BondBlock::TYPE_TRIPLE:
			order = 3;
			break;

		case BondBlock::TYPE_AROMATIC:     
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_SINGLE_DOUBLE:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::SINGLE | BondMatchConstraint::DOUBLE);
			break;

		case BondBlock::TYPE_SINGLE_AROMATIC:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_DOUBLE_AROMATIC:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_ANY:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::ANY_ORDER);
			break;

		default:
			throw Base::IOError("MDLDataReader: invalid bond type specification");
	}

	setOrder(bond, order);

	return order;
}

void Chem::MDLDataReader::readCTabV2000BondStereo(std::istream& is, Bond& bond) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading bond stereo specification", strictErrorChecking)) {

		case BondBlock::STEREO_NONE:
			set2DStereoFlag(bond, BondStereoFlag::PLAIN);
			return;

		case BondBlock::STEREO_UP:
			set2DStereoFlag(bond, BondStereoFlag::UP);
			return;

		case BondBlock::STEREO_DOWN:
			set2DStereoFlag(bond, BondStereoFlag::DOWN);
			return;

		case BondBlock::STEREO_EITHER:
		case BondBlock::STEREO_EITHER_DB:
			set2DStereoFlag(bond, BondStereoFlag::EITHER);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid bond stereo specification");
	}
}

void Chem::MDLDataReader::readCTabV2000BondQueryTopology(std::istream& is, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading query bond topology specification", 
										   strictErrorChecking)) {

		case BondBlock::TOPOLOGY_EITHER:
			return;

		case BondBlock::TOPOLOGY_RING:
			constr_list.addElement(BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, true);
			return;

		case BondBlock::TOPOLOGY_CHAIN:
			constr_list.addElement(BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL, false);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid query bond topology specification");
	}
}

void Chem::MDLDataReader::readCTabV2000BondRxnCenterStatus(std::istream& is, Bond& bond) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	unsigned int rxn_center_info = ReactionCenterStatus::NONE;
	int rxn_center_status = readMDLNumber<int, 3>(is, "MDLDataReader: error while reading bond reacting center status", 
												  strictErrorChecking);

	switch (rxn_center_status) {

		case BondBlock::RXN_STATUS_UNMARKED:
			break;

		case BondBlock::RXN_STATUS_IS_CENTER:
			rxn_center_info = ReactionCenterStatus::IS_CENTER;
			break;

		case BondBlock::RXN_STATUS_NO_CENTER:
			rxn_center_info = ReactionCenterStatus::NO_CENTER;
			break;

		case BondBlock::RXN_STATUS_NO_CHANGE:
			rxn_center_info = ReactionCenterStatus::NO_CHANGE;
			break;

		case BondBlock::RXN_STATUS_MADE_BROKEN:
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN;
			break;

		case BondBlock::RXN_STATUS_ORDER_CHANGE:
			rxn_center_info = ReactionCenterStatus::BOND_ORDER_CHANGE;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | ReactionCenterStatus::IS_CENTER;
			break;

		case (BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
				ReactionCenterStatus::BOND_ORDER_CHANGE;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN |
				ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER;
			break;
	
		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid bond reacting center status");
	}

	setReactionCenterStatus(bond, rxn_center_info);
}

void Chem::MDLDataReader::readCTabV2000AList(std::istream& is, Molecule& mol, std::size_t atom_index_offs)
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from atom list block", 
														   strictErrorChecking);

	if (atom_index == 0 || atom_index > mol.getNumAtoms() - atom_index_offs) {
		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: atom index in atom list block item is out of range");

		skipMDLLines(is, 1, "MDLDataReader: error while reading atom list block");	
		return;
	}

	Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

	skipMDLChars(is, 1, "MDLDataReader: error while reading atom list block");

	MatchConstraintList::SharedPointer alist_constr_ptr(new MatchConstraintList());

	readMDLString(is, 1, tmpString, true, "MDLDataReader: error while reading atom list type from atom list block");

	if (tmpString == AListBlock::NORMAL_LIST_FLAG) 
		alist_constr_ptr->setType(MatchConstraintList::OR_LIST); 

	else if (tmpString == AListBlock::NOT_LIST_FLAG)
		alist_constr_ptr->setType(MatchConstraintList::NOT_OR_LIST); 

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid list type specification in atom list block");

	else {
		skipMDLLines(is, 1, "MDLDataReader: error while reading atom list block");	
		return;
	}

	skipMDLChars(is, 4, "MDLDataReader: error while reading atom list block");

	std::size_t num_entries = readMDLNumber<std::size_t, 1>(is, "MDLDataReader: error while reading list size from atom list block",
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > AListBlock::MAX_ENTRIES)
		throw Base::IOError("MDLDataReader: atom list exceeds maximum size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading atom list block");

		alist_constr_ptr->addElement(AtomMatchConstraint::TYPE, MatchConstraint::EQUAL,
									 readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading atomic"
																	" number item from atom list block", 
																	strictErrorChecking));
	}

	if (alist_constr_ptr->getSize() != 0) {
		MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

		constr_list_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST, MatchConstraint::EQUAL,
									alist_constr_ptr);
	
		setMatchConstraints(atom, constr_list_ptr);
	}

	skipMDLLines(is, 1, "MDLDataReader: error while reading atom list block");	
}

void Chem::MDLDataReader::readCTabV2000ChargeProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading charge property list size", 
															strictErrorChecking);
	
	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_CHARGE_ENTRIES)
		throw Base::IOError("MDLDataReader: number of charge property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading charge property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from charge property list item", 
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in charge property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading charge property list");
			continue;
		}

		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		skipMDLChars(is, 1, "MDLDataReader: error while reading charge property list");

		long charge = readMDLNumber<long, 3>(is, "MDLDataReader: error while reading charge value from charge property list item", 
											 strictErrorChecking);

		if (strictErrorChecking && (charge < PropertyBlock::MIN_CHARGE || charge > PropertyBlock::MAX_CHARGE))
			throw Base::IOError("MDLDataReader: charge value in charge property list item is out of valid range");

		setFormalCharge(atom, charge);
	}
}

void Chem::MDLDataReader::readCTabV2000RadicalProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading radical property list size", 
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_RADICAL_ENTRIES)
		throw Base::IOError("MDLDataReader: number of radical property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading radical property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from radical property list item", 
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in radical property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading radical property list");
			continue;
		}
	
		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		skipMDLChars(is, 1, "MDLDataReader: error while reading radical property list");

		switch (readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading radical type from charge property list item", 
											   strictErrorChecking)) {

			case PropertyBlock::NO_RADICAL:
				setRadicalType(atom, RadicalType::NOT_RADICALIC);
				continue;

			case PropertyBlock::SINGLET_RADICAL:
				setRadicalType(atom, RadicalType::SINGLET);
				continue;

			case PropertyBlock::DOUBLET_RADICAL:
				setRadicalType(atom, RadicalType::DOUBLET);
				continue;

			case PropertyBlock::TRIPLET_RADICAL:
				setRadicalType(atom, RadicalType::TRIPLET);
				continue;

			default:
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: invalid radical type specification in charge property list item");
		}
	}
}

void Chem::MDLDataReader::readCTabV2000IsotopeProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading isotope property list size",
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_ISOTOPE_ENTRIES)
		throw Base::IOError("MDLDataReader: number of isotope property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading isotope property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from isotope property list item",
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in isotope property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading isotope property list");
			continue;
		}

		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		skipMDLChars(is, 1, "MDLDataReader: error while reading isotope property list");

		setIsotope(atom, readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading mass value from isotope property list item",
													   strictErrorChecking));
	}
}

void Chem::MDLDataReader::readCTabV2000RingBondCountProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;
  
	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading ring bond count property list size",
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_RING_BOND_COUNT_ENTRIES)
		throw Base::IOError("MDLDataReader: number of ring bond count property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading ring bond count property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from ring bond count property list item",
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in ring bond count property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading ring bond count property list");
			continue;
		}

		skipMDLChars(is, 1, "MDLDataReader: error while reading ring bond count property list");

		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

		switch (readMDLNumber<int, 3>(is, "MDLDataReader: error while reading ring bond count specification from property list item",
									  strictErrorChecking)) {
			
			case PropertyBlock::RING_BOND_COUNT_UNDEF:
				continue;

			case PropertyBlock::RING_BOND_COUNT_E0:
				constr_list_ptr->addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(0));
				break;

			case PropertyBlock::RING_BOND_COUNT_DRAWN:
				constr_list_ptr->addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL);
				break;

			case PropertyBlock::RING_BOND_COUNT_E2:
				constr_list_ptr->addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(2));
				break;

			case PropertyBlock::RING_BOND_COUNT_E3:
				constr_list_ptr->addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(3));
				break;

			case PropertyBlock::RING_BOND_COUNT_GE4:
				constr_list_ptr->addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL,
											std::size_t(4));
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: invalid ring bond count specification in property list item");

				continue;
		}

		setMatchConstraints(atom, constr_list_ptr);
	}
}

void Chem::MDLDataReader::readCTabV2000SubstCountProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading substitution count property list size",
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_SUBSTITUTION_COUNT_ENTRIES)
		throw Base::IOError("MDLDataReader: number of substitution count property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading substitution count property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from substitution count property list item",
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in substitution count property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading substitution count property list");
			continue;
		}

		skipMDLChars(is, 1, "MDLDataReader: error while reading substitution count property list");

		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

		switch (readMDLNumber<int, 3>(is, "MDLDataReader: error while reading substitution count specification from property list item",
									  strictErrorChecking)) {

			case PropertyBlock::SUBSTITUTION_COUNT_UNDEF:
				continue;

			case PropertyBlock::SUBSTITUTION_COUNT_E0:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(0));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_DRAWN:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL);
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_E1:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(1));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_E2:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(2));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_E3:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(3));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_E4:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(4));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_E5:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
											std::size_t(5));
				break;

			case PropertyBlock::SUBSTITUTION_COUNT_GE6:
				constr_list_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL,
											std::size_t(6));	
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: invalid substitution count specification in property list item");

				continue;
		}

		setMatchConstraints(atom, constr_list_ptr);
	}
}

void Chem::MDLDataReader::readCTabV2000UnsaturationProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs) const
{
	using namespace MDL::MOLFile::CTab::V2000;

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading Unsaturation flag property list size",
															strictErrorChecking);

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_UNSATURATION_ENTRIES)
		throw Base::IOError("MDLDataReader: number of Unsaturation flag property entries exceeds maximum list size");

	for (std::size_t i = 0; i < num_entries; i++) {
		skipMDLChars(is, 1, "MDLDataReader: error while reading Unsaturation property list");

		std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from Unsaturation flag property list item",
															   strictErrorChecking);

		if (atom_index == 0 || atom_index > max_atom_index) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: atom index in Unsaturation flag property list item is out of bounds");

			skipMDLChars(is, 4, "MDLDataReader: error while reading Unsaturation flag property list");
			continue;
		}

		Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

		skipMDLChars(is, 1, "MDLDataReader: error while reading Unsaturation flag property list");

		unsigned int unsat_flag = readMDLNumber<unsigned int, 3>(is, "MDLDataReader: error while reading Unsaturation flag from property list item",
																 strictErrorChecking);

		if (unsat_flag == PropertyBlock::UNSATURATION_UNDEF)
			continue;

		if (unsat_flag == PropertyBlock::UNSATURATION_ON) {
			MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

			constr_list_ptr->addElement(AtomMatchConstraint::UNSATURATION, MatchConstraint::EQUAL,
										true);	

			setMatchConstraints(atom, constr_list_ptr);

		} else if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: invalid Unsaturation flag specification in property list item");
	}
}

void Chem::MDLDataReader::readCTabV2000AtomListProperties(std::istream& is, Molecule& mol, std::size_t atom_index_offs)
{
	using namespace MDL::MOLFile::CTab::V2000;

	skipMDLChars(is, 1, "MDLDataReader: error while reading atom list property line");

	std::size_t max_atom_index = mol.getNumAtoms() - atom_index_offs;
	std::size_t atom_index = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading atom index from atom list property line",
														   strictErrorChecking);

	if (atom_index == 0 || atom_index > max_atom_index) {
		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: atom index in atom list property line is out of bounds");

		return;
	}

	Atom& atom = mol.getAtom(atom_index - 1 + atom_index_offs);

	std::size_t num_entries = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading list size from atom list property line", 
															strictErrorChecking);	

	if ((strictErrorChecking || checkLineLength) && num_entries > PropertyBlock::MAX_ATOM_LIST_ENTRIES)
		throw Base::IOError("MDLDataReader: number of atom list entries exceeds maximum list size");

	skipMDLChars(is, 1, "MDLDataReader: error while reading atom list property line");

	readMDLString(is, 1, tmpString, true, "MDLDataReader: error while reading list type specification from atom list property line");

	MatchConstraintList::SharedPointer alist_constr_ptr(new MatchConstraintList());

	if (tmpString == PropertyBlock::NORMAL_ATOM_LIST_FLAG) 
		alist_constr_ptr->setType(MatchConstraintList::OR_LIST); 

	else if (tmpString == PropertyBlock::NOT_ATOM_LIST_FLAG)
		alist_constr_ptr->setType(MatchConstraintList::NOT_OR_LIST); 

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid list type specification in atom list property line");

	else
		return;

	skipMDLChars(is, 1, "MDLDataReader: error while reading atom list property line");

	for (std::size_t i = 0; i < num_entries; i++) {
		readMDLString(is, 4, tmpString, true, "MDLDataReader: error while reading atom symbol item from atom list property line", 
					  trimStrings);

		unsigned int atom_type = AtomDictionary::getType(tmpString);

		if (atom_type != AtomType::UNKNOWN)
			alist_constr_ptr->addElement(AtomMatchConstraint::TYPE, MatchConstraint::EQUAL,
										 atom_type);
	}
		
	if (alist_constr_ptr->getSize() != 0) {
		MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

		constr_list_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST, MatchConstraint::EQUAL,
									alist_constr_ptr);
	
		setMatchConstraints(atom, constr_list_ptr);
	}
}

void Chem::MDLDataReader::readCTabV2000RegistryNumberProperty(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V2000;

	readMDLLine(is, line, "MDLDataReader: error while reading molecule registry number property", true, checkLineLength, 
				MDL::MAX_LINE_LENGTH - PropertyBlock::REGISTRY_NO_PREFIX.length());

	try {
		setMDLRegistryNumber(mol, boost::lexical_cast<unsigned int>(line));

	} catch (...) {
		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: reading molecule registry number property failed");
	}
}

void Chem::MDLDataReader::readSDFData(std::istream& is, Molecule& mol)
{   
	using namespace MDL;

	StringDataBlock::SharedPointer sd_ptr(new StringDataBlock());
	StringDataBlockEntry data_entry;

	while (true) {
		readMDLLine(is, line, "MDLDataReader: error while reading structure data block", false, checkLineLength);

		if (line.empty()) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: too many empty lines in structure data block");

			continue;
		}

		if (line == SDFile::RECORD_DELIMITER)
			break;

		if (line.find(SDFile::DATA_HEADER_PREFIX) != 0) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: missing data header line prefix in structure data block");

			continue;
		}

		line.erase(0, SDFile::DATA_HEADER_PREFIX.length());

		data_entry.setHeader(line);

		tmpString.clear();

		while (true) {
			readMDLLine(is, line, "MDLDataReader: error while reading structure data block", false, checkLineLength, 
						MAX_DATA_LINE_LENGTH);

			if (line.empty())
				break;

			if (!tmpString.empty())
				tmpString.push_back(Chem::MDL::END_OF_LINE);

			tmpString.append(line);
		}
	
		data_entry.setData(tmpString);

		sd_ptr->addElement(data_entry);
	}

	setStructureData(mol, sd_ptr);
}

void Chem::MDLDataReader::skipSDFData(std::istream& is)
{   
	using namespace MDL;

	while (true) {
		readMDLLine(is, line, "MDLDataReader: error while skipping structure data header");

		if (line.empty()) 
			continue;
		
		if (line == SDFile::RECORD_DELIMITER)
			break;

		if (line.find(SDFile::DATA_HEADER_PREFIX) != 0) 
			continue;
		
		while (true) {
			readMDLLine(is, line, "MDLDataReader: error while skipping structure data");

			if (line.empty())
				break;
		}
	}
}

void Chem::MDLDataReader::readRXNHeaderBlock(std::istream& is, Reaction& rxn)
{
	using namespace MDL;

	// Header line 1

	readMDLString(is, RXN_FILE_ID_LENGTH, tmpString, true, 
				  "MDLDataReader: error while reading rxn-file identifier from reaction header block", false);
 
	Internal::trimString(tmpString, false, true);

	if (tmpString != RXNFile::RXN_FILE_IDENTIFIER && strictErrorChecking)
		throw Base::IOError("MDLDataReader: missing rxn-file identifier in reaction header block");

	readMDLLine(is, line, "MDLDataReader: error while reading rxn-file version from reaction header block", 
				true, checkLineLength, MDL::MAX_LINE_LENGTH - RXN_FILE_ID_LENGTH);

	if (line.empty())
		rxnVersion = MDLDataFormatVersion::V2000;

	else if (line == RXNFile::V3000_VERSION_TAG) 
		rxnVersion = MDLDataFormatVersion::V3000;

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid rxn-file version in reaction header block");

	else
		rxnVersion = MDLDataFormatVersion::UNDEF;

	// Header line 2

	readMDLLine(is, line, "MDLDataReader: error while reading reaction name from rxn-file header block", 
				trimLines, checkLineLength);
	setName(rxn, line);

	// Header line 3

	readMDLString(is, 6, tmpString, true, "MDLDataReader: error while reading user initials from rxn-file header block", trimStrings);
	setMDLUserInitials(rxn, tmpString);

	readMDLString(is, 9, tmpString, true, "MDLDataReader: error while reading program name from rxn-file header block", trimStrings);
	setMDLProgramName(rxn, tmpString);

	using namespace boost::posix_time;
	using namespace boost::gregorian;
  
	unsigned short month = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp month part from rxn-file header block", 
															strictErrorChecking, 100);
	unsigned short day = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp day part from rxn-file header block", 
														  strictErrorChecking, 100);
	unsigned short year = readMDLNumber<unsigned short, 4>(is, "MDLDataReader: error while reading date/timestamp year part from rxn-file header block", 
														   strictErrorChecking, 10000);
	unsigned short hour = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp hour part from rxn-file header block", 
														   strictErrorChecking, 100);
	unsigned short minute = readMDLNumber<unsigned short, 2>(is, "MDLDataReader: error while reading date/timestamp minute part from rxn-file header block", 
															 strictErrorChecking, 100);

	if (month != 100 || day != 100 || year != 10000 || hour != 100 || minute != 100) {
		try {
			date date_part(greg_year(year + 0), greg_month(month), greg_day(day));
			time_duration time_part = hours(hour) + minutes(minute);
			time_duration duration = ptime(date_part, time_part) - ptime(date(greg_year(1970), greg_month(1), greg_day(1)));

			setMDLTimestamp(rxn, duration.total_seconds());

		} catch (const std::out_of_range&) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid timestamp in rxn-file header block");

		} catch (...) {
			throw;
		}
	}

	std::size_t reg_no = readMDLNumber<std::size_t, 7>(is, "MDLDataReader: error while reading registry number from rxn-file header block ", 
													   strictErrorChecking, ~std::size_t(0), ~std::size_t(0));
	if (reg_no <= 9999999)
		setMDLRegistryNumber(rxn, reg_no); 

	skipMDLLines(is, 1, "MDLDataReader: error while reading rxn-file header block");

	// Header line 4

	readMDLLine(is, line, "MDLDataReader: error while reading comment line from rxn-file header block", 
				trimLines, checkLineLength);
	setMDLComment(rxn, line);
}

void Chem::MDLDataReader::skipRXNHeaderBlock(std::istream& is)
{
	using namespace MDL;

	// Header line 1

	readMDLString(is, RXN_FILE_ID_LENGTH, tmpString, true, 
				  "MDLDataReader: error while reading rxn-file identifier from reaction header block", false);
 
	Internal::trimString(tmpString, false, true);

	if (tmpString != RXNFile::RXN_FILE_IDENTIFIER && strictErrorChecking)
		throw Base::IOError("MDLDataReader: missing rxn-file identifier in reaction header block");

	readMDLLine(is, line, "MDLDataReader: error while reading rxn-file version from reaction header block", true);

	if (line.empty())
		rxnVersion = MDLDataFormatVersion::V2000;

	else if (line == RXNFile::V3000_VERSION_TAG) 
		rxnVersion = MDLDataFormatVersion::V3000;

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid rxn-file version in reaction header block");

	else
		rxnVersion = MDLDataFormatVersion::UNDEF;

	// Header lines 2, 3, 4

	skipMDLLines(is, 3, "MDLDataReader: error while reading rxn-file header block"); 
}

void Chem::MDLDataReader::readRXNReaction(std::istream& is, Reaction& rxn)
{
	if (rxnVersion == MDLDataFormatVersion::V3000)
		readRXNV3000Reaction(is, rxn);
	else
		readRXNV2000Reaction(is, rxn);
}

void Chem::MDLDataReader::skipRXNReaction(std::istream& is)
{
	if (rxnVersion == MDLDataFormatVersion::V3000)
		skipV3000Data(is);
	else
		skipRXNV2000Reaction(is);
}

void Chem::MDLDataReader::readRXNV2000Reaction(std::istream& is, Reaction& rxn)
{
	std::size_t num_reactants;
	std::size_t num_products;

	readRXNV2000CountsLine(is, num_reactants, num_products);

	for (std::size_t i = 0; i < num_reactants; i++)
		readRXNV2000ReactionComponent(is, rxn, ReactionRole::REACTANT);

	for (std::size_t i = 0; i < num_products; i++)
		readRXNV2000ReactionComponent(is, rxn, ReactionRole::PRODUCT);
}

void Chem::MDLDataReader::skipRXNV2000Reaction(std::istream& is)
{
	std::size_t num_reactants;
	std::size_t num_products;

	readRXNV2000CountsLine(is, num_reactants, num_products);

	std::size_t num_comps = num_reactants + num_products;

	for (std::size_t i = 0; i < num_comps; i++)
		skipRXNV2000ReactionComponent(is);
}

void Chem::MDLDataReader::readRXNV2000CountsLine(std::istream& is, std::size_t& num_reactants, std::size_t& num_products)
{
	num_reactants = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of reactants"); 
	num_products = readMDLNumber<std::size_t, 3>(is, "MDLDataReader: error while reading number of products"); 	

	skipMDLLines(is, 1, "MDLDataReader: error while reading reactant/product counts-line");
}

void Chem::MDLDataReader::readRXNV2000ReactionComponent(std::istream& is, Reaction& rxn, unsigned int rxn_role)
{
	readMDLLine(is, line, "MDLDataReader: error while reading reaction component molfile delimiter",
				false, checkLineLength);

	if (strictErrorChecking && line != MDL::RXNFile::MOL_FILE_DELIMITER)
		throw Base::IOError("MDLDataReader: missing reaction component molfile delimiter");

	Molecule& comp = rxn.addComponent(rxn_role);

	readMOLHeaderBlock(is, comp);
	readMOLCTab(is, comp);
}

void Chem::MDLDataReader::skipRXNV2000ReactionComponent(std::istream& is)
{
	skipMDLLines(is, 1, "MDLDataReader: error while skipping reaction component molfile delimiter");

	skipMOLHeaderBlock(is);
	skipMOLCTab(is);
}

void Chem::MDLDataReader::readRDFHeaderBlock(std::istream& is)
{
	using namespace MDL;

	std::istream::pos_type last_pos = is.tellg();

	readMDLString(is, RDFile::RD_FILE_IDENTIFIER.length() + 1, tmpString, true, 
				  "MDLDataReader: error while trying to read rd-file header block", false);
 
	Internal::trimString(tmpString, false, true);

	if (tmpString != RDFile::RD_FILE_IDENTIFIER) {
		is.seekg(last_pos);
		return;
	}

	if (strictErrorChecking) {
		readMDLLine(is, line, "MDLDataReader: error while reading rd-file header block", 
					false, checkLineLength, MAX_LINE_LENGTH - RDFile::RD_FILE_IDENTIFIER.length() - 1);

		std::istringstream iss(line);

		iss >> tmpString;

		if (tmpString != RDFile::RD_FILE_VERSION_STAMP)
			throw Base::IOError("MDLDataReader: missing or invalid rd-file version stamp in header block");		


		readMDLString(is, RDFile::DATE_TIME_KEYWORD.length() + 1, tmpString, true, 
					  "MDLDataReader: error while reading rd-file header block", false);
 
		Internal::trimString(tmpString, false, true);

		if (tmpString != RDFile::DATE_TIME_KEYWORD)
			throw Base::IOError("MDLDataReader: expected date/timestamp keyword at beginning of second rd-file header line");		

		skipMDLLines(is, 1, "MDLDataReader: error while reading rd-file header block");

	} else 
		skipMDLLines(is, 2, "MDLDataReader: error while reading rd-file header block");
}

void Chem::MDLDataReader::skipRDFHeaderBlock(std::istream& is)
{
	using namespace MDL;

	std::istream::pos_type last_pos = is.tellg();

	readMDLString(is, RDFile::RD_FILE_IDENTIFIER.length() + 1, tmpString, true, 
				  "MDLDataReader: error while trying to skip rd-file header block", false);
 
	Internal::trimString(tmpString, false, true);

	if (tmpString != RDFile::RD_FILE_IDENTIFIER) {
		is.seekg(last_pos);
		return;
	}

	skipMDLLines(is, 2, "MDLDataReader: error while skipping rd-file header block");
}

void Chem::MDLDataReader::readRDFReaction(std::istream& is, Reaction& rxn)
{
	using namespace MDL;

	std::string rec_type;

	while (true) {
		readMDLLine(is, line, "MDLDataReader: error while reading molecule or reaction record identifier line", 
					false, checkLineLength);

		if (!hasRDFKeywordPrefix(line)) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: expected molecule or reaction record identifier keyword at beginning of line");		

			continue;
		}

		std::istringstream iss(line);

		iss >> rec_type;

		if (rec_type == RDFile::MOL_RECORD_IDENTIFIER) {
			std::string mireg_kw;
			std::string mereg_kw;

			std::string mireg;
			std::string mereg;

			iss >> mireg_kw >> mireg >> mereg_kw >> mereg;

			if (!mireg_kw.empty()) {
				if (mireg_kw == RDFile::RXN_INT_REGISTRY_NO_KEYWORD) {
					if (!mireg.empty()) {
						setMDLInternalRegistryNumber(rxn, mireg);

						if (!mereg_kw.empty()) {
							if (mereg_kw == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD) {
								if (!mereg.empty()) 
									setMDLExternalRegistryNumber(rxn, mereg);
				
								else if (strictErrorChecking) 
									throw Base::IOError("MDLDataReader: expected registry number after external molecule registry number keyword");	

							} else if (strictErrorChecking) 
								throw Base::IOError("MDLDataReader: expected external molecule registry number keyword after internal registry number");		
						}

					} else if (strictErrorChecking) 
						throw Base::IOError("MDLDataReader: expected registry number after internal molecule registry number keyword");	

				} else if (strictErrorChecking) 
					throw Base::IOError("MDLDataReader: expected internal molecule registry number keyword after reaction identifier");	
			}

			Molecule::SharedPointer mol_ptr(new BasicMolecule());

			readMOLHeaderBlock(is, *mol_ptr);
			readMOLCTab(is, *mol_ptr);

			setMDLMoleculeRecord(rxn, mol_ptr);

			return;
		} 
		
		if (rec_type == RDFile::RXN_RECORD_IDENTIFIER) {
			std::string rireg_kw;
			std::string rereg_kw;

			std::string rireg;
			std::string rereg;

			iss >> rireg_kw >> rireg >> rereg_kw >> rereg;

			if (!rireg_kw.empty()) {
				if (rireg_kw == RDFile::RXN_INT_REGISTRY_NO_KEYWORD) {
					if (!rireg.empty()) {
						setMDLInternalRegistryNumber(rxn, rireg);

						if (!rereg_kw.empty()) {
							if (rereg_kw == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD) {
								if (!rereg.empty()) 
									setMDLExternalRegistryNumber(rxn, rereg);
				
								else if (strictErrorChecking) 
									throw Base::IOError("MDLDataReader: expected registry number after external reaction registry number keyword");	

							} else if (strictErrorChecking) 
								throw Base::IOError("MDLDataReader: expected external reaction registry number keyword after internal registry number");		
						}

					} else if (strictErrorChecking) 
						throw Base::IOError("MDLDataReader: expected registry number after internal reaction registry number keyword");	

				} else if (strictErrorChecking) 
					throw Base::IOError("MDLDataReader: expected internal reaction registry number keyword after reaction identifier");
			}

			readRXNHeaderBlock(is, rxn);
			readRXNReaction(is, rxn);
			return;
		} 
	
		if (rec_type == RDFile::MOL_INT_REGISTRY_NO_KEYWORD || rec_type == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD) {
			std::string mol_reg_no;

			if (!(iss >> mol_reg_no)) {
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: expected corresponding number after internal/external molecule registry number keyword");		

				return;
			}

			Molecule::SharedPointer mol_ptr(new BasicMolecule());

			if (rec_type == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD)
				setMDLExternalRegistryNumber(rxn, mol_reg_no);
			else
				setMDLInternalRegistryNumber(rxn, mol_reg_no);

			setMDLMoleculeRecord(rxn, mol_ptr);
			return;
		} 
	
		if (rec_type == RDFile::RXN_INT_REGISTRY_NO_KEYWORD || rec_type == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD) {
			std::string rxn_reg_no;

			if (!(iss >> rxn_reg_no)) {
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: expected corresponding number after internal/external reaction registry number keyword");		

				return;
			}

			if (rec_type == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD)
				setMDLExternalRegistryNumber(rxn, rxn_reg_no);
			else
				setMDLInternalRegistryNumber(rxn, rxn_reg_no);

			return;
		} 

		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: expected molecule or reaction record identifier keyword at beginning of line");		
	}
}

void Chem::MDLDataReader::skipRDFReaction(std::istream& is)
{
	using namespace MDL;

	std::string rec_type;

	while (true) {
		readMDLLine(is, line, "MDLDataReader: error while reading molecule or reaction record identifier line", false);

		if (!hasRDFKeywordPrefix(line)) 
			continue;
		
		std::istringstream iss(line);

		iss >> rec_type;

		if (rec_type == RDFile::MOL_RECORD_IDENTIFIER) {
			skipMOLHeaderBlock(is);
			skipMOLCTab(is);
			return;
		} 
		
		if (rec_type == RDFile::RXN_RECORD_IDENTIFIER) {
			skipRXNHeaderBlock(is);
			skipRXNReaction(is);
			return;
		} 
	
		if (rec_type == RDFile::MOL_INT_REGISTRY_NO_KEYWORD 
			|| rec_type == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD
			|| rec_type == RDFile::RXN_INT_REGISTRY_NO_KEYWORD
			|| rec_type == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD) 
			return;
	}
}

void Chem::MDLDataReader::readRDFData(std::istream& is, Reaction& rxn)
{
	using namespace MDL;
	
	StringDataBlock::SharedPointer rd_ptr(new StringDataBlock());
	StringDataBlockEntry data_entry;

	std::istringstream iss;
	std::string keyword;

	while (hasMoreData(is)) {
		std::istream::pos_type last_pos = is.tellg();

		readMDLLine(is, line, "MDLDataReader: error while reading rd-file datafield identifier line", false, checkLineLength);

		if (!hasRDFKeywordPrefix(line)) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: expected rd-file datafield identifier keyword at beginning of line");		

			continue;
		}

		iss.str(line);
		iss >> keyword;

		if (keyword == RDFile::RXN_RECORD_IDENTIFIER
			|| keyword == RDFile::MOL_RECORD_IDENTIFIER
			|| keyword == RDFile::RXN_INT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::MOL_INT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD) {

			is.seekg(last_pos);
			break;
		}

		if (keyword != RDFile::DATA_FIELD_IDENTIFIER) {
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: expected rd-file datafield identifier keyword at beginning of line");		

			continue;
		}

		line.erase(0, RDFile::DATA_FIELD_IDENTIFIER.length());

		while (true) {
			readMDLLine(is, tmpString, "MDLDataReader: error while reading rd-file datafield identifier", 
						false, checkLineLength);

			if (hasRDFKeywordPrefix(tmpString)) {
				iss.str(tmpString);
				iss >> keyword;

				if (keyword == RDFile::DATA_FIELD_PREFIX) 
					break;
			}

			line.push_back(MDL::END_OF_LINE);
			line.append(tmpString);
		}

		data_entry.setHeader(line);

		tmpString.erase(0, RDFile::DATA_FIELD_PREFIX.length());

		while (hasMoreData(is)) {
			std::istream::pos_type last_pos = is.tellg();

			readMDLLine(is, line, "MDLDataReader: error while reading rd-file datafield line", 
						false, checkLineLength, MAX_DATA_LINE_LENGTH);

			if (hasRDFKeywordPrefix(line)) {
				iss.str(line);
				iss >> keyword;
 
				if (keyword == RDFile::MOL_RECORD_IDENTIFIER
					|| keyword == RDFile::MOL_INT_REGISTRY_NO_KEYWORD
					|| keyword == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD
					|| keyword == RDFile::RXN_RECORD_IDENTIFIER
					|| keyword == RDFile::RXN_INT_REGISTRY_NO_KEYWORD
					|| keyword == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD
					|| keyword == RDFile::DATA_FIELD_IDENTIFIER) {
				
					is.seekg(last_pos);
					break;
				}
			}
	
			tmpString.push_back(MDL::END_OF_LINE);
			tmpString.append(line);
		}

		data_entry.setData(tmpString);

		rd_ptr->addElement(data_entry);
	}

	setReactionData(rxn, rd_ptr);
}

void Chem::MDLDataReader::skipRDFData(std::istream& is)
{
	using namespace MDL;
	
	std::istringstream iss;
	std::string keyword;

	while (hasMoreData(is)) {
		std::istream::pos_type last_pos = is.tellg();

		readMDLLine(is, line, "MDLDataReader: error while reading rd-file datafield identifier line", false);

		if (!hasRDFKeywordPrefix(line)) 
			continue;
		
		iss.str(line);
		iss >> keyword;

		if (keyword == RDFile::RXN_RECORD_IDENTIFIER
			|| keyword == RDFile::MOL_RECORD_IDENTIFIER
			|| keyword == RDFile::RXN_INT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::MOL_INT_REGISTRY_NO_KEYWORD
			|| keyword == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD) {

			is.seekg(last_pos);
			break;
		}

		if (keyword != RDFile::DATA_FIELD_IDENTIFIER) 
			continue;

		while (true) {
			readMDLLine(is, line, "MDLDataReader: error while reading rd-file datafield identifier", false);

			if (!hasRDFKeywordPrefix(line))
				continue;

			iss.str(line);
			iss >> keyword;

			if (keyword == RDFile::DATA_FIELD_PREFIX) 
				break;
		}

		while (hasMoreData(is)) {
			std::istream::pos_type last_pos = is.tellg();

			readMDLLine(is, line, "MDLDataReader: error while reading rd-file datafield line", false);

			if (!hasRDFKeywordPrefix(line))
				continue;

			iss.str(line);
			iss >> keyword;
 
			if (keyword == RDFile::MOL_RECORD_IDENTIFIER
				|| keyword == RDFile::MOL_INT_REGISTRY_NO_KEYWORD
				|| keyword == RDFile::MOL_EXT_REGISTRY_NO_KEYWORD
				|| keyword == RDFile::RXN_RECORD_IDENTIFIER
				|| keyword == RDFile::RXN_INT_REGISTRY_NO_KEYWORD
				|| keyword == RDFile::RXN_EXT_REGISTRY_NO_KEYWORD
				|| keyword == RDFile::DATA_FIELD_IDENTIFIER) {
				
				is.seekg(last_pos);
				break;
			}
		}
	}
}

bool Chem::MDLDataReader::hasRDFKeywordPrefix(const std::string& line) const
{
	return (line.size() != 0 && line[0] == MDL::RDFile::RD_FILE_KEYWORD_PREFIX);
}

void Chem::MDLDataReader::readCTabV3000(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab;

	atomQueryHCountList.clear();
	stereoAtoms.clear();
	atomIndexMap.clear();

	readV3000BlockBegin(is, V3000::BLOCK_TYPE_KEY);

	readCTabV3000CountsLine(is, mol);
	readCTabV3000AtomBlock(is, mol);
	readCTabV3000BondBlock(is, mol);

	readPastCTabV3000BlockEnd(is);

	addAtomQueryHCountConstraints();	

	if (!ignoreParity)
		convertParities(mol);
}

void Chem::MDLDataReader::readCTabV3000CountsLine(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V3000;

	readV3000DataLine(is);

	std::istringstream line_iss(line);

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 counts-line tag");

	if (tmpString != CountsLine::COUNTS_TAG)
		throw Base::IOError("MDLDataReader: missing ctab V3000 counts-line tag");

	if (!(line_iss >> atomCount))
		throw Base::IOError("MDLDataReader: error while reading number of atoms from ctab V3000 counts-line");

	if (!(line_iss >> bondCount))
		throw Base::IOError("MDLDataReader: error while reading number of bonds from ctab V3000 counts-line");

	std::size_t dummy;

	if (!(line_iss >> dummy))
		throw Base::IOError("MDLDataReader: error while reading number of Sgroups from ctab V3000 counts-line");

	if (!(line_iss >> dummy))
		throw Base::IOError("MDLDataReader: error while reading number of 3D constraints from ctab V3000 counts-line");

	unsigned int chiral_flag;

	if (!(line_iss >> chiral_flag))
		throw Base::IOError("MDLDataReader: error while reading chiral flag from ctab V3000 counts-line");

	if (strictErrorChecking && chiral_flag != CountsLine::CHIRAL_FLAG_OFF && chiral_flag != CountsLine::CHIRAL_FLAG_ON)
		throw Base::IOError("MDLDataReader: invalid chiral flag specification in ctab V3000 counts-line");

	setMDLChiralFlag(mol, (chiral_flag == CountsLine::CHIRAL_FLAG_ON));

	if (!readCTabV3000PropertyKeyword(line_iss, tmpString))
		return;

	if (tmpString != CountsLine::REGISTRY_NO_KEYWORD) {
		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: found invalid registry number keyword in ctab V3000 counts-line");

		return;
	}

	std::size_t reg_no;

	if (!(line_iss >> reg_no))
		throw Base::IOError("MDLDataReader: error while reading registry number from ctab V3000 counts-line");

	setMDLRegistryNumber(mol, reg_no); 
}

void Chem::MDLDataReader::readCTabV3000AtomBlock(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V3000;

	std::size_t old_num_atoms = mol.getNumAtoms();

	readV3000BlockBegin(is, AtomBlock::BLOCK_TYPE_KEY);

	for (std::size_t i = 0; i < atomCount; i++)
		readCTabV3000Atom(is, mol);

	readV3000BlockEnd(is, AtomBlock::BLOCK_TYPE_KEY);

	fixCTabV3000AtomCoordsDim(mol, old_num_atoms);
}

void Chem::MDLDataReader::fixCTabV3000AtomCoordsDim(Molecule& mol, std::size_t old_num_atoms) const
{
	if (coordsDim == 3) {
		setMDLDimensionality(mol, 3); 
		return;
	}

	Molecule::AtomIterator atoms_end = mol.getAtomsEnd();

	for (Molecule::AtomIterator it = mol.getAtomsBegin() + old_num_atoms; it != atoms_end; ++it) {
		Atom& atom = *it;

		const Math::Vector3D& coords_3d = get3DCoordinates(atom);
		Math::Vector2D coords_2d;
 
		coords_2d(0) = coords_3d(0);
		coords_2d(1) = coords_3d(1);

		clear3DCoordinates(atom);
		set2DCoordinates(atom, coords_2d);
	}

	setMDLDimensionality(mol, 2); 
}

void Chem::MDLDataReader::readCTabV3000BondBlock(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V3000;

	readV3000BlockBegin(is, BondBlock::BLOCK_TYPE_KEY);

	for (std::size_t i = 0; i < bondCount; i++)
		readCTabV3000Bond(is, mol);

	readV3000BlockEnd(is, BondBlock::BLOCK_TYPE_KEY);
}

void Chem::MDLDataReader::readPastCTabV3000BlockEnd(std::istream& is)
{
	using namespace MDL;

	std::istringstream line_iss;

	while (true) {
		readV3000DataLine(is);

		line_iss.str(line);
		line_iss >> tmpString;

		if (tmpString != V3000::BLOCK_END_TAG)
			continue;

		line_iss >> tmpString;

		if (tmpString == MOLFile::CTab::V3000::BLOCK_TYPE_KEY)
			return;
	}
}

void Chem::MDLDataReader::readCTabV3000Atom(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V3000;

	readV3000DataLine(is);

	std::istringstream line_iss(line);
	Atom& atom = mol.addAtom();

	MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList());
	unsigned int rxn_center_status = ReactionCenterStatus::NONE;

	readCTabV3000AtomIndex(line_iss, mol, atom);
	readCTabV3000AtomType(line_iss, atom, *constr_list_ptr);
	readCTabV3000AtomCoords(line_iss, atom);
	readCTabV3000AtomRxnAAMNumber(line_iss, atom);

	while (readCTabV3000PropertyKeyword(line_iss, tmpString)) {

		if (tmpString == AtomBlock::CHARGE_KEYWORD) 
			readCTabV3000AtomCharge(line_iss, atom);

		else if (tmpString == AtomBlock::RADICAL_KEYWORD) 
			readCTabV3000AtomRadicalType(line_iss, atom);

		else if (tmpString == AtomBlock::CONFIG_KEYWORD)
			readCTabV3000AtomStereoConfig(line_iss, atom);

		else if (tmpString == AtomBlock::MASS_KEYWORD) 
			readCTabV3000AtomMass(line_iss, atom);

		else if (tmpString == AtomBlock::VALENCE_KEYWORD) 
			readCTabV3000AtomValence(line_iss, atom);

		else if (tmpString == AtomBlock::HYDROGEN_COUNT_KEYWORD) 
			readCTabV3000AtomQueryHCount(line_iss, atom);

		else if (tmpString == AtomBlock::STEREO_BOX_KEYWORD)
			readCTabV3000AtomStereoBoxFlag(line_iss, atom);

		else if (tmpString == AtomBlock::RXN_INV_RET_KEYWORD)
			readCTabV3000AtomRxnInvRetFlag(line_iss, atom, rxn_center_status);

		else if (tmpString == AtomBlock::RXN_CHANGE_KEYWORD)
			readCTabV3000AtomRxnChangeFlag(line_iss, atom, rxn_center_status);

		else if (tmpString == AtomBlock::SUBSTITUTION_COUNT_KEYWORD) 
			readCTabV3000AtomQuerySubstCount(line_iss, atom, *constr_list_ptr);

		else if (tmpString == AtomBlock::UNSATURATION_KEYWORD) 
			readCTabV3000AtomQueryUnsaturationFlag(line_iss, *constr_list_ptr);

		else if (tmpString == AtomBlock::RING_BOND_COUNT_KEYWORD) 
			readCTabV3000AtomQueryRingBondCount(line_iss, atom, *constr_list_ptr);

		else if (tmpString == AtomBlock::ATTACHMENT_POINT_KEYWORD)
			skipCTabV3000PropertyIntValue(line_iss);

		else if (tmpString == AtomBlock::ATTACHMENT_ORDER_KEYWORD)
			skipCTabV3000PropertyValueList(line_iss);

		else if (tmpString == AtomBlock::RGROUPS_KEYWORD)
			skipCTabV3000PropertyValueList(line_iss);

		else
			throw Base::IOError("MDLDataReader: unknown ctab V3000 atom property keyword");
	}

	if (constr_list_ptr->getSize() != 0)
		setMatchConstraints(atom, constr_list_ptr); 

	setReactionCenterStatus(atom, rxn_center_status); 
}

void Chem::MDLDataReader::readCTabV3000AtomIndex(std::istream& is, const Molecule& mol, Atom& atom)
{
	std::size_t atom_index;

	if (!(is >> atom_index))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom index");

	if (strictErrorChecking && atom_index == 0)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 atom index - has to be > 0");

	AtomIndexMap::iterator lb = atomIndexMap.lower_bound(atom_index);

	if (lb != atomIndexMap.end() && !(atomIndexMap.key_comp()(atom_index, lb->first)))
		throw Base::IOError("MDLDataReader: found non-unique ctab V3000 atom index");

	atomIndexMap.insert(lb, AtomIndexMap::value_type(atom_index, mol.getAtomIndex(atom)));
}

void Chem::MDLDataReader::readCTabV3000AtomType(std::istream& is, Atom& atom, MatchConstraintList& constr_list)
{
	using namespace MDL::MOLFile::CTab::V3000;

	readCTabV3000PropertyStringValue(is, tmpString);

	std::string::const_iterator type_str_beg = tmpString.begin();
	std::string::const_iterator type_str_end = tmpString.end();
	std::string::const_iterator first_non_ws_pos = std::find_if(type_str_beg, type_str_end, boost::bind(Internal::IsNonWhitespace(), _1));

	if (first_non_ws_pos == type_str_end) {
		setCTabV3000AtomSymbol(tmpString, atom, constr_list);
		return;
	} 

	bool not_list = false;
	
	if (tmpString.find(AtomBlock::NOT_ATOM_LIST_TAG, std::string::size_type(first_non_ws_pos - type_str_beg)) 
		== std::string::size_type(first_non_ws_pos - type_str_beg)) {

		first_non_ws_pos = std::find_if(first_non_ws_pos + AtomBlock::NOT_ATOM_LIST_TAG.length(), type_str_end, 
										boost::bind(Internal::IsNonWhitespace(), _1));

		if (first_non_ws_pos == type_str_end) {
			setCTabV3000AtomSymbol(tmpString, atom, constr_list);
			return;
		} 

		not_list = true;
	}

	if (*first_non_ws_pos != AtomBlock::ATOM_LIST_START_DELIMITER) {
		setCTabV3000AtomSymbol(tmpString, atom, constr_list);
		return;
	}

	std::string::const_iterator last_non_ws_pos = --std::find_if(tmpString.rbegin(), tmpString.rend(), 
																 boost::bind(Internal::IsNonWhitespace(), _1)).base();

	if (*last_non_ws_pos != AtomBlock::ATOM_LIST_END_DELIMITER) {
		setCTabV3000AtomSymbol(tmpString, atom, constr_list);
		return;
	}

	const char alist_sep[] = { AtomBlock::ATOM_LIST_SEPARATOR, 0 };

	typedef boost::tokenizer<boost::char_separator<char> > AListTokenizer;

	boost::char_separator<char> tokenizer_func(alist_sep, "", boost::keep_empty_tokens);
	AListTokenizer tokenizer(++first_non_ws_pos, last_non_ws_pos, tokenizer_func);

	MatchConstraintList::SharedPointer alist_constr_ptr(new MatchConstraintList());

	alist_constr_ptr->setType(not_list ? MatchConstraintList::NOT_OR_LIST : MatchConstraintList::OR_LIST);

	for (AListTokenizer::iterator it = tokenizer.begin(); it != tokenizer.end(); ++it) {
		unsigned int atom_type = AtomDictionary::getType(!trimStrings ? *it : Internal::trimStringCopy(*it));

		if (atom_type != AtomType::UNKNOWN)
			alist_constr_ptr->addElement(AtomMatchConstraint::TYPE,
										 MatchConstraint::EQUAL,
										 atom_type);
	}

	if (alist_constr_ptr->getSize() != 0) 
		constr_list.addElement(AtomMatchConstraint::CONSTRAINT_LIST,
							   MatchConstraint::EQUAL,
							   alist_constr_ptr);
}

void Chem::MDLDataReader::setCTabV3000AtomSymbol(std::string& symbol, Atom& atom, MatchConstraintList& constr_list) const
{
	if (trimStrings)
		Internal::trimString(symbol);

	setSymbol(atom, symbol);
	
	unsigned int atom_type = AtomDictionary::getType(symbol);

	setType(atom, atom_type);

	switch (atom_type) {

		case AtomType::Q:
		case AtomType::A:
		case AtomType::ANY:
			constr_list.addElement(AtomMatchConstraint::TYPE,
								   MatchConstraint::EQUAL);
		default:
			break;
	}
}

void Chem::MDLDataReader::readCTabV3000AtomCoords(std::istream& is, Atom& atom)
{
	Math::Vector3D coords;

	if (!(is >> coords(0)))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom x coordinate");

	if (!(is >> coords(1)))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom y coordinate");

	if (!(is >> coords(2)))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom z coordinate");

	set3DCoordinates(atom, coords);

	if (coords(2) != 0.0) 
		coordsDim = 3;
}

void Chem::MDLDataReader::readCTabV3000AtomRxnAAMNumber(std::istream& is, Atom& atom) const
{
	std::size_t aam_id;

	if (!(is >> aam_id))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 reaction atom atom mapping number");

	if (aam_id > 0)
		setReactionAtomMappingID(atom, aam_id + atomMappingIDOffset);
}

void Chem::MDLDataReader::readCTabV3000AtomCharge(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	long charge;

	if (!(is >> charge))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom charge property");

	if (strictErrorChecking && (charge < AtomBlock::MIN_CHARGE || charge > AtomBlock::MAX_CHARGE))
		throw Base::IOError("MDLDataReader: ctab V3000 atom charge is out of allowed range");

	setFormalCharge(atom, charge);
}

void Chem::MDLDataReader::readCTabV3000AtomRadicalType(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int rad_type;

	if (!(is >> rad_type))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom radical type property");
	
	switch (rad_type) {

		case AtomBlock::NO_RADICAL:
			setRadicalType(atom, RadicalType::NOT_RADICALIC);
			return;

		case AtomBlock::SINGLET_RADICAL:
			setRadicalType(atom, RadicalType::SINGLET);
			return;

		case AtomBlock::DOUBLET_RADICAL:
			setRadicalType(atom, RadicalType::DOUBLET);
			return;

		case AtomBlock::TRIPLET_RADICAL:
			setRadicalType(atom, RadicalType::TRIPLET);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom radical type specification");
	}
}

void Chem::MDLDataReader::readCTabV3000AtomStereoConfig(std::istream& is, Atom& atom)
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int parity;

	if (!(is >> parity))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom stereo configuration property");
	
	switch (parity) {

		case AtomBlock::STEREO_PARITY_NONE:
			parity = MDLParity::NONE;
			break;

		case AtomBlock::STEREO_PARITY_ODD:
			parity = MDLParity::ODD;
			break;

		case AtomBlock::STEREO_PARITY_EVEN:
			parity = MDLParity::EVEN;
			break;

		case AtomBlock::STEREO_PARITY_EITHER:
			parity = MDLParity::EITHER;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom stereo configuration specification");
	}

	setMDLParity(atom, parity);

	if (!ignoreParity)
		stereoAtoms.push_back(&atom);
}

void Chem::MDLDataReader::readCTabV3000AtomMass(std::istream& is, Atom& atom) const
{
	std::size_t isotope;

	if (!(is >> isotope))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom mass property");
	
	setIsotope(atom, isotope);
}

void Chem::MDLDataReader::readCTabV3000AtomValence(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	int valence;

	if (!(is >> valence))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom valence property");
	
	switch (valence) {

		case AtomBlock::VALENCE_UNDEF:
			return;

		case AtomBlock::VALENCE_ZERO:
			//atom.setProperty(AtomProperty::TOTAL_VALENCE, 0);
			return;

		default:
			if (valence < 0) {
				if (strictErrorChecking)
					throw Base::IOError("MDLDataReader: invalid ctab V3000 atom valence specification");	

			}// else 
			//	atom.setProperty(AtomProperty::TOTAL_VALENCE, valence);
	}
}

void Chem::MDLDataReader::readCTabV3000AtomQueryHCount(std::istream& is, Atom& atom)
{
	using namespace MDL::MOLFile::CTab::V3000;

	int h_count;

	if (!(is >> h_count))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom query hydrogen count property");
	
	switch (h_count) {

		case AtomBlock::HYDROGEN_COUNT_UNDEF:
			return;

		case AtomBlock::HYDROGEN_COUNT_E0:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 0));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE1:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 1));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE2:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 2));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE3:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 3));
			return;

		case AtomBlock::HYDROGEN_COUNT_GE4:
			atomQueryHCountList.push_back(AtomQueryHCountList::value_type(&atom, 4));
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom query hydrogen count specification");
	}
}

void Chem::MDLDataReader::readCTabV3000AtomStereoBoxFlag(std::istream& is, Atom& atom) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int db_stereo_box_flag;

	if (!(is >> db_stereo_box_flag))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom stereo box flag property");

	if (db_stereo_box_flag == AtomBlock::DB_STEREO_IGNORE)
		return;

	if (db_stereo_box_flag == AtomBlock::DB_STEREO_MATCH) 
		setMDLStereoCareFlag(atom, true);

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 atom stereo box flag");
}

void Chem::MDLDataReader::readCTabV3000AtomRxnInvRetFlag(std::istream& is, Atom& atom, unsigned int& rxn_center_status) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int inv_ret_flag;

	if (!(is >> inv_ret_flag))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom reaction inversion/retention flag property");

	switch (inv_ret_flag) {

		case AtomBlock::RXN_INV_RET_UNDEF:
			return;

		case AtomBlock::RXN_INV_RET_INVERSION:
			rxn_center_status |= ReactionCenterStatus::STEREO_INVERSION;
			return;

		case AtomBlock::RXN_INV_RET_RETENTION:
			rxn_center_status |= ReactionCenterStatus::STEREO_RETENTION;
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom reaction inversion/retention flag");
	}
}

void Chem::MDLDataReader::readCTabV3000AtomRxnChangeFlag(std::istream& is, Atom& atom, unsigned int& rxn_center_status) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int rxn_change_flag;

	if (!(is >> rxn_change_flag))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom reaction change flag property");

	switch (rxn_change_flag) {

		case AtomBlock::RXN_CHANGE_UNDEF:
			return;

		case AtomBlock::RXN_CHANGE_EXACT:
			rxn_center_status |= ReactionCenterStatus::EXACT_CHANGE;
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom reaction change flag");
	}
}

void Chem::MDLDataReader::readCTabV3000AtomQuerySubstCount(std::istream& is, Atom& atom, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	int subst_cnt_spec;

	if (!(is >> subst_cnt_spec))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom query substitution count property");
	
	switch (subst_cnt_spec) {

		case AtomBlock::SUBSTITUTION_COUNT_UNDEF:
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E0:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(0));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E1:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(1));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E2:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(2));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E3:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(3));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E4:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(4));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_E5:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(5));
			return;

		case AtomBlock::SUBSTITUTION_COUNT_GE6:
			constr_list.addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL,
								   std::size_t(6));
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom query substitution count specification");
	}
}

void Chem::MDLDataReader::readCTabV3000AtomQueryUnsaturationFlag(std::istream& is, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int unsat_flag;

	if (!(is >> unsat_flag))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom query Unsaturation flag property");
	
	if (unsat_flag == AtomBlock::UNSATURATION_UNDEF)
		return;

	if (unsat_flag == AtomBlock::UNSATURATION_ON) 
		constr_list.addElement(AtomMatchConstraint::UNSATURATION, MatchConstraint::EQUAL,
							   true);

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 atom query Unsaturation flag");
}

void Chem::MDLDataReader::readCTabV3000AtomQueryRingBondCount(std::istream& is, Atom& atom, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	int ring_bnd_cnt_spec;

	if (!(is >> ring_bnd_cnt_spec))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 atom query ring bond count property");
	
	switch (ring_bnd_cnt_spec) {
			
		case AtomBlock::RING_BOND_COUNT_UNDEF:
			return;

		case AtomBlock::RING_BOND_COUNT_E0:
			constr_list.addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(0));
			return;

		case AtomBlock::RING_BOND_COUNT_E2:
			constr_list.addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(2));
			return;

		case AtomBlock::RING_BOND_COUNT_E3:
			constr_list.addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::EQUAL,
								   std::size_t(3));
			return;

		case AtomBlock::RING_BOND_COUNT_GE4:
			constr_list.addElement(AtomMatchConstraint::RING_BOND_COUNT, MatchConstraint::GREATER_OR_EQUAL,
								   std::size_t(4));
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 atom query ring bond count specification");
	}
}

void Chem::MDLDataReader::readCTabV3000Bond(std::istream& is, Molecule& mol)
{
	using namespace MDL::MOLFile::CTab::V3000;

	readV3000DataLine(is);

	std::istringstream line_iss(line);

	readCTabV3000BondIndex(line_iss);

	unsigned int bond_type = readCTabV3000BondType(line_iss);

	Bond& bond = createCTabV3000Bond(line_iss, mol);

	MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList());

	std::size_t order = setCTabV3000BondType(bond_type, bond, *constr_list_ptr);

	if (order == 2) {
		bool stereo_box_flag1 = getMDLStereoCareFlag(bond.getBegin());
		bool stereo_box_flag2 = getMDLStereoCareFlag(bond.getEnd());

		if (stereo_box_flag1 && stereo_box_flag2) 
			constr_list_ptr->addElement(BondMatchConstraint::CONFIGURATION, MatchConstraint::EQUAL);
	}

	while (readCTabV3000PropertyKeyword(line_iss, tmpString)) {

		if (tmpString == BondBlock::CONFIG_KEYWORD) 
			readCTabV3000BondStereo(line_iss, bond);

		else if (tmpString == BondBlock::TOPOLOGY_KEYWORD) 
			readCTabV3000BondQueryTopology(line_iss, *constr_list_ptr);

		else if (tmpString == BondBlock::STEREO_BOX_KEYWORD)
			readCTabV3000BondQueryStereoBoxFlag(line_iss, *constr_list_ptr);

		else if (tmpString == BondBlock::RXN_CENTER_STATUS_KEYWORD) 
			readCTabV3000BondRxnCenterStatus(line_iss, bond);

		else
			throw Base::IOError("MDLDataReader: unknown ctab V3000 bond property keyword");
	}

	if (constr_list_ptr->getSize() != 0)
		setMatchConstraints(bond, constr_list_ptr); 
}

void Chem::MDLDataReader::readCTabV3000BondIndex(std::istream& is) const
{
	std::size_t bond_index;

	if (!(is >> bond_index))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond index");

	if (strictErrorChecking && bond_index == 0)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 bond index - has to be > 0");
}

unsigned int Chem::MDLDataReader::readCTabV3000BondType(std::istream& is) const
{
	unsigned int bond_type;

	if (!(is >> bond_type))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond type property");

	return bond_type;
}

Chem::Bond& Chem::MDLDataReader::createCTabV3000Bond(std::istream& is, Molecule& mol) const 
{
	std::size_t atom1_index;

	if (!(is >> atom1_index))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond start atom index");

	if (strictErrorChecking && atom1_index == 0)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 bond start atom index - has to be > 0");

	AtomIndexMap::const_iterator mol_atom1_index_it = atomIndexMap.find(atom1_index);
	
	if (mol_atom1_index_it == atomIndexMap.end())
		throw Base::IOError("MDLDataReader: ctab V3000 bond start atom with specified index does not exist");

	std::size_t atom2_index;

	if (!(is >> atom2_index))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond target atom index");

	if (strictErrorChecking && atom2_index == 0)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 bond target atom index - has to be > 0");

	AtomIndexMap::const_iterator mol_atom2_index_it = atomIndexMap.find(atom2_index);
	
	if (mol_atom2_index_it == atomIndexMap.end())
		throw Base::IOError("MDLDataReader: ctab V3000 bond target atom with specified index does not exist");

	return mol.addBond(mol_atom1_index_it->second, mol_atom2_index_it->second);
}

std::size_t Chem::MDLDataReader::setCTabV3000BondType(unsigned int bond_type, Bond& bond, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	std::size_t order = 1;

	switch (bond_type) {

		case BondBlock::TYPE_SINGLE:
			break;

		case BondBlock::TYPE_DOUBLE:
			order = 2;
			break;

		case BondBlock::TYPE_TRIPLE:
			order = 3;
			break;

		case BondBlock::TYPE_AROMATIC:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_SINGLE_DOUBLE:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::SINGLE | BondMatchConstraint::DOUBLE);
			break;

		case BondBlock::TYPE_SINGLE_AROMATIC:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_DOUBLE_AROMATIC:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC);
			break;

		case BondBlock::TYPE_ANY:
			constr_list.addElement(BondMatchConstraint::ORDER, MatchConstraint::EQUAL,
								   BondMatchConstraint::ANY_ORDER);
			break;

		default:
			throw Base::IOError("MDLDataReader: invalid ctab V3000 bond type specification");
	}

	setOrder(bond, order);

	return order;
}

void Chem::MDLDataReader::readCTabV3000BondStereo(std::istream& is, Bond& bond) const
{
	using namespace MDL::MOLFile::CTab::V3000;
	
	unsigned int stereo;

	if (!(is >> stereo))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond stereo configuration property");
	
	switch (stereo) {

		case BondBlock::STEREO_NONE:
			set2DStereoFlag(bond, BondStereoFlag::PLAIN);
			return;

		case BondBlock::STEREO_UP:
			set2DStereoFlag(bond, BondStereoFlag::UP);
			return;

		case BondBlock::STEREO_DOWN:
			set2DStereoFlag(bond, BondStereoFlag::DOWN);
			return;

		case BondBlock::STEREO_EITHER:
			set2DStereoFlag(bond, BondStereoFlag::EITHER);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 bond stereo configuration specification");
	}
}

void Chem::MDLDataReader::readCTabV3000BondQueryStereoBoxFlag(std::istream& is, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;

	unsigned int db_stereo_box_flag;

	if (!(is >> db_stereo_box_flag))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond query stereo box flag property");

	if (db_stereo_box_flag == BondBlock::DB_STEREO_IGNORE)
		return;

	if (db_stereo_box_flag == BondBlock::DB_STEREO_MATCH) 
		constr_list.addElement(BondMatchConstraint::CONFIGURATION, MatchConstraint::EQUAL);

	else if (strictErrorChecking)
		throw Base::IOError("MDLDataReader: invalid ctab V3000 bond query stereo box flag");
}

void Chem::MDLDataReader::readCTabV3000BondQueryTopology(std::istream& is, MatchConstraintList& constr_list) const
{
	using namespace MDL::MOLFile::CTab::V3000;
	
	unsigned int topology;

	if (!(is >> topology))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond query topology property");
	
	switch (topology) {

		case BondBlock::TOPOLOGY_EITHER:
			return;

		case BondBlock::TOPOLOGY_RING:
			constr_list.addElement(BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL,
								   true);
			return;

		case BondBlock::TOPOLOGY_CHAIN:
			constr_list.addElement(BondMatchConstraint::RING_TOPOLOGY, MatchConstraint::EQUAL,
								   false);
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 bond query topology specification");
	}
}

void Chem::MDLDataReader::readCTabV3000BondRxnCenterStatus(std::istream& is, Bond& bond) const
{
	using namespace MDL::MOLFile::CTab::V3000;
	
	int rxn_center_status;

	if (!(is >> rxn_center_status))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 bond reacting center status property");
	
	unsigned int rxn_center_info = ReactionCenterStatus::NONE;

	switch (rxn_center_status) {

		case BondBlock::RXN_STATUS_UNMARKED:
			break;

		case BondBlock::RXN_STATUS_IS_CENTER:
			rxn_center_info = ReactionCenterStatus::IS_CENTER;
			break;

		case BondBlock::RXN_STATUS_NO_CENTER:
			rxn_center_info = ReactionCenterStatus::NO_CENTER;
			break;

		case BondBlock::RXN_STATUS_NO_CHANGE:
			rxn_center_info = ReactionCenterStatus::NO_CHANGE;
			break;

		case BondBlock::RXN_STATUS_MADE_BROKEN:
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN;
			break;

		case BondBlock::RXN_STATUS_ORDER_CHANGE:
			rxn_center_info = ReactionCenterStatus::BOND_ORDER_CHANGE;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
				ReactionCenterStatus::IS_CENTER;
			break;

		case (BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN | 
				ReactionCenterStatus::BOND_ORDER_CHANGE;
			break;

		case (BondBlock::RXN_STATUS_MADE_BROKEN + BondBlock::RXN_STATUS_ORDER_CHANGE + BondBlock::RXN_STATUS_IS_CENTER):
			rxn_center_info = ReactionCenterStatus::BOND_MADE | ReactionCenterStatus::BOND_BROKEN 
				| ReactionCenterStatus::BOND_ORDER_CHANGE | ReactionCenterStatus::IS_CENTER;
			break;
		
		default:
			if (strictErrorChecking)
				throw Base::IOError("MDLDataReader: invalid ctab V3000 bond reacting center status specification");
	}

	setReactionCenterStatus(bond, rxn_center_info);
}

bool Chem::MDLDataReader::readCTabV3000PropertyKeyword(std::istream& is, std::string& keyword) const
{
	if (!(is >> std::ws))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 property keyword");		

	if (is.eof()) 
		return false;

	std::getline(is, keyword, MDL::V3000::KEYWORD_VALUE_SEPARATOR); 

	if (is.fail())
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 property keyword");		

	if (is.eof()) {
		if (strictErrorChecking)
			throw Base::IOError("MDLDataReader: missing keyword/value separator after expected ctab V3000 property keyword");		

		return false;
	}

	Internal::trimString(keyword, false, true);

	if (keyword.empty())
		throw Base::IOError("MDLDataReader: missing ctab V3000 property keyword");		

	return true;
}

void Chem::MDLDataReader::readCTabV3000PropertyStringValue(std::istream& is, std::string& str) const
{
	using namespace MDL;

	if (!(is >> std::ws))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 property string value");

	char c;

	if (!(is.get(c)))
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 property string value");
		
	if (c != V3000::STRING_QUOTE_CHAR) {
		is.putback(c);
		
		if (!(is >> str))
			throw Base::IOError("MDLDataReader: error while reading ctab V3000 property string value");

		return;
	}
	
	str.clear();

	bool seen_quote_char = false;
	
	while (is.get(c)) {
		if (c == V3000::STRING_QUOTE_CHAR) {
			if (!seen_quote_char) {
				seen_quote_char = true;
				continue;
			}
			
			str.push_back(c);
			seen_quote_char = false;
			continue;
		}

		if (seen_quote_char) {
			is.putback(c);
			break;
		}

		str.push_back(c);
	}

	if (is.fail() && !is.eof())
		throw Base::IOError("MDLDataReader: error while reading ctab V3000 property string value");

	if (!seen_quote_char)
		throw Base::IOError("MDLDataReader: missing closing ctab V3000 property string quote");
}

void Chem::MDLDataReader::skipCTabV3000PropertyIntValue(std::istream& is)
{
	if (!(is >> tmpString))
		throw Base::IOError("MDLDataReader: error while skipping ctab V3000 integer property value");
}

void Chem::MDLDataReader::skipCTabV3000PropertyValueList(std::istream& is) const
{
	if (!is.ignore(std::numeric_limits<std::streamsize>::max(), 
				   std::istream::traits_type::to_int_type(MDL::V3000::VALUE_LIST_END_DELIM)))
		throw Base::IOError("MDLDataReader: error while skipping ctab V3000 property value list");
}

void Chem::MDLDataReader::readRXNV3000Reaction(std::istream& is, Reaction& rxn)
{
	using namespace MDL::RXNFile;

	std::size_t num_reactants;
	std::size_t num_products;

	readRXNV3000CountsLine(is, num_reactants, num_products);

	readV3000BlockBegin(is, V3000::REACTANT_BLOCK_KEY);

	for (std::size_t i = 0; i < num_reactants; i++)
		readRXNV3000ReactionComponent(is, rxn, ReactionRole::REACTANT);

	readV3000BlockEnd(is, V3000::REACTANT_BLOCK_KEY);

	readV3000BlockBegin(is, V3000::PRODUCT_BLOCK_KEY);

	for (std::size_t i = 0; i < num_products; i++)
		readRXNV3000ReactionComponent(is, rxn, ReactionRole::PRODUCT);

	readV3000BlockEnd(is, V3000::PRODUCT_BLOCK_KEY);

	readV3000DataEndTag(is);
}

void Chem::MDLDataReader::readRXNV3000CountsLine(std::istream& is, std::size_t& num_reactants, std::size_t& num_products)
{
	using namespace MDL::RXNFile;

	readV3000DataLine(is);

	std::istringstream line_iss(line);

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading rxn-file V3000 reactant/product counts-line tag");

	if (tmpString != V3000::COUNTS_TAG)
		throw Base::IOError("MDLDataReader: missing rxn-file V3000 reactant/product counts-line tag");

	if (!(line_iss >> num_reactants))
		throw Base::IOError("MDLDataReader: error while reading rxn-file V3000 reactant count");

	if (!(line_iss >> num_products))
		throw Base::IOError("MDLDataReader: error while reading rxn-file V3000 product count");
}

void Chem::MDLDataReader::readRXNV3000ReactionComponent(std::istream& is, Reaction& rxn, unsigned int rxn_role)
{
	Molecule& comp = rxn.addComponent(rxn_role);
	coordsDim = 2;

	readCTabV3000(is, comp);
}

void Chem::MDLDataReader::readV3000BlockBegin(std::istream& is, const std::string& block_type)
{
	using namespace MDL;

	readV3000DataLine(is);

	std::istringstream line_iss(line);

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading V3000 block begin tag");

	if (tmpString != V3000::BLOCK_BEGIN_TAG)
		throw Base::IOError("MDLDataReader: missing V3000 block begin tag");

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading V3000 block type");

	if (tmpString != block_type)
		throw Base::IOError("MDLDataReader: invalid V3000 block type");
}

void Chem::MDLDataReader::readV3000BlockEnd(std::istream& is, const std::string& block_type)
{
	using namespace MDL;

	readV3000DataLine(is);

	std::istringstream line_iss(line);

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading V3000 block end tag");

	if (tmpString != V3000::BLOCK_END_TAG)
		throw Base::IOError("MDLDataReader: missing V3000 block end tag");

	if (!(line_iss >> tmpString))
		throw Base::IOError("MDLDataReader: error while reading V3000 block type");

	if (tmpString != block_type)
		throw Base::IOError("MDLDataReader: invalid V3000 block type");
}

void Chem::MDLDataReader::readV3000DataLine(std::istream& is)
{
	using namespace MDL;

	const std::size_t V3000_LINE_PREFIX_LENGTH = V3000::LINE_PREFIX.length();

	line.clear();

	while (true) {
		readMDLString(is, V3000_LINE_PREFIX_LENGTH, tmpString, true, "MDLDataReader: error while reading V3000 line prefix", false);

		if (tmpString != V3000::LINE_PREFIX)
			throw Base::IOError("MDLDataReader: missing V3000 line prefix");		

		readMDLLine(is, tmpString, "MDLDataReader: error while reading V3000 data line", false, checkLineLength);

		if (tmpString.empty())
			return;

		if (*tmpString.rbegin() != V3000::LINE_CONTINUATION_MARK) {
			line.append(tmpString);
			return;
		}

		tmpString.erase(--tmpString.end());
		line.append(tmpString);
	}
}

void Chem::MDLDataReader::readV3000DataEndTag(std::istream& is)
{
	readMDLLine(is, line, "MDLDataReader: error while reading V3000 datarecord end tag", false, checkLineLength);

	if (strictErrorChecking && line != MDL::V3000::DATA_END_TAG && line != MDL::V3000::DATA_END_TAG_ALT)
		throw Base::IOError("MDLDataReader: missing molfile end tag");
}

void Chem::MDLDataReader::skipV3000Data(std::istream& is)
{
	while (true) {
		readMDLLine(is, line, "MDLDataReader: error while skipping V3000 datarecord", false);

		if (line == MDL::V3000::DATA_END_TAG || line == MDL::V3000::DATA_END_TAG_ALT)
			return;
	}
}

void Chem::MDLDataReader::addAtomQueryHCountConstraints() const
{
	AtomQueryHCountList::const_iterator end = atomQueryHCountList.end();

	for (AtomQueryHCountList::const_iterator it = atomQueryHCountList.begin(); it != end; ++it) {
		Atom& atom = *(it->first);
		std::size_t h_count = it->second;

		MatchConstraintList::SharedPointer constr_list_ptr(new MatchConstraintList(*getMatchConstraints(atom)));

		if (h_count == 0)
			constr_list_ptr->addElement(AtomMatchConstraint::H_COUNT, MatchConstraint::EQUAL,
										getExplicitAtomCount(atom, AtomType::H));
		else
			constr_list_ptr->addElement(AtomMatchConstraint::H_COUNT, MatchConstraint::GREATER_OR_EQUAL,
										getExplicitAtomCount(atom, AtomType::H) + h_count);

		setMatchConstraints(atom, constr_list_ptr);
	}
}

void Chem::MDLDataReader::convertParities(Molecule& mol) const
{
	perceiveComponents(mol, false);
	perceiveSSSR(mol, false);
	setRingFlags(mol, false);
	calcImplicitHydrogenCounts(mol, false);
	perceiveHybridizationStates(mol, false);
	setAromaticityFlags(mol, false);

	StereoAtomList::const_iterator end = stereoAtoms.end();

	for (StereoAtomList::const_iterator it = stereoAtoms.begin(); it != end; ++it) {
		Atom& atom = **it;
		setStereoDescriptor(atom, calcStereoDescriptorFromMDLParity(atom, mol));
	}
}
