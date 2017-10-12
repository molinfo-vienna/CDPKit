/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBDataReader.cpp 
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

#include <locale>
#include <istream>
#include <algorithm>
#include <functional>
#include <cmath>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "PDBDataReader.hpp"
#include "PDBFormatData.hpp"


using namespace CDPL;


namespace
{

	inline void skipPDBChars(std::istream& is, std::size_t count, const char* err_msg)
	{
		Internal::skipChars(is, count, err_msg, Biomol::PDB::END_OF_LINE);
	}

	inline void skipPDBLines(std::istream& is, std::size_t count, const char* err_msg)
	{
		Internal::skipLines(is, count, err_msg, Biomol::PDB::END_OF_LINE);
	}
		
	inline std::string& readPDBLine(std::istream& is, std::string& line, const char* err_msg,  
									bool check_ll = false, std::size_t max_llen = Biomol::PDB::MAX_LINE_LENGTH)
	{
		return Internal::readLine(is, line, err_msg, false, check_ll, max_llen, Biomol::PDB::END_OF_LINE);
	}

	inline std::string& readPDBString(std::istream& is, std::size_t field_size, std::string& str, bool clear,
									  const char* err_msg, bool trim = true)
	{
		return Internal::readString(is, field_size, str, clear, err_msg, trim, Biomol::PDB::END_OF_LINE);
	}

	template <typename T, std::size_t FieldSize>
	inline T readPDBNumber(std::istream& is, const char* err_msg, bool throw_ex = true, 
						   const T empty_def_val = T(0), const T err_def_val = T(0))
	{
		return Internal::readNumber<T, FieldSize>(is, err_msg, throw_ex, empty_def_val, err_def_val, Biomol::PDB::END_OF_LINE);
	}

	class ResidueAtomCmpFunc : public std::binary_function<const Chem::Atom*, const Chem::Atom*, bool>
	{

	public:
		ResidueAtomCmpFunc() {}

		bool operator()(const Chem::Atom* atom1, const Chem::Atom* atom2) const {
			using namespace Biomol;

			const std::string& res_atom_name1 = getResidueAtomName(*atom1);
			const std::string& res_atom_name2 = getResidueAtomName(*atom2);

			if (res_atom_name1 == res_atom_name2)
				return (getAltLocationID(*atom1) < getAltLocationID(*atom2));
	
			return (res_atom_name1 < res_atom_name2);
		}
	};

	typedef boost::unordered_map<std::string, std::vector<std::size_t> > RecordOrderIDMap;
	typedef std::set<std::string> RecordNameSet;

	RecordOrderIDMap recordOrderIDs;
	RecordNameSet    multilineRecords;
	RecordNameSet    oneTimeRecords;

	struct Init {

		Init() {
			for (std::size_t i = 0; i < sizeof(Biomol::PDB::RECORD_ORDER) / sizeof(std::string); i++)
				recordOrderIDs[Biomol::PDB::RECORD_ORDER[i]].push_back(i + 1);

			for (std::size_t i = 0; i < sizeof(Biomol::PDB::MULTILINE_RECORDS) / sizeof(std::string); i++)
				multilineRecords.insert(Biomol::PDB::MULTILINE_RECORDS[i]);

			for (std::size_t i = 0; i < sizeof(Biomol::PDB::ONE_TIME_RECORDS) / sizeof(std::string); i++)
				oneTimeRecords.insert(Biomol::PDB::ONE_TIME_RECORDS[i]);
		}

	} init;
}


bool Biomol::PDBDataReader::readPDBFile(std::istream& is, Chem::Molecule& mol)
{
	if (!hasMoreData(is))
		return false;

	init(is, mol);

	std::string rec_name;
	std::string prev_rec_name;

	bool exit_loop = false;

	while (!exit_loop) {
		std::size_t rem_llen = startNextRecord(is, rec_name, prev_rec_name);

		//std::cerr << "rec. name: " << rec_name << std::endl;

		if (rec_name == PDB::HEADER_PREFIX) 
			rem_llen -= readGenericDataRecord(is, PDB::HEADER_DATA_LENGTH, PDBData::HEADER, rec_name);

		else if (rec_name == PDB::OBSLTE_PREFIX) 
			rem_llen -= readGenericDataRecord(is, PDB::OBSLTE_DATA_LENGTH, PDBData::OBSLTE, rec_name);
				
		else if (rec_name == PDB::TITLE_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::TITLE_DATA_LENGTH, PDBData::TITLE, rec_name);

		else if (rec_name == PDB::SPLIT_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SPLIT_DATA_LENGTH, PDBData::SPLIT, rec_name);
	
		else if (rec_name == PDB::CAVEAT_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::CAVEAT_DATA_LENGTH, PDBData::CAVEAT, rec_name);

		else if (rec_name == PDB::COMPND_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::COMPND_DATA_LENGTH, PDBData::COMPND, rec_name);

		else if (rec_name == PDB::SOURCE_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SOURCE_DATA_LENGTH, PDBData::SOURCE, rec_name);

		else if (rec_name == PDB::KEYWDS_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::KEYWDS_DATA_LENGTH, PDBData::KEYWDS, rec_name);

		else if (rec_name == PDB::EXPDTA_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::EXPDTA_DATA_LENGTH, PDBData::EXPDTA, rec_name);

		else if (rec_name == PDB::NUMMDL_PREFIX)
			rem_llen -= skipRecordData(is, PDB::NUMMDL_DATA_LENGTH, rec_name);

		else if (rec_name == PDB::MDLTYP_PREFIX)
			rem_llen -= skipRecordData(is, PDB::MDLTYP_DATA_LENGTH, rec_name);

		else if (rec_name == PDB::AUTHOR_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::AUTHOR_DATA_LENGTH, PDBData::AUTHOR, rec_name);

		else if (rec_name == PDB::REVDAT_PREFIX) 
			rem_llen -= readGenericDataRecord(is, PDB::REVDAT_DATA_LENGTH, PDBData::REVDAT, rec_name);

		else if (rec_name == PDB::SPRSDE_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SPRSDE_DATA_LENGTH, PDBData::SPRSDE, rec_name);

		else if (rec_name == PDB::JRNL_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::JRNL_DATA_LENGTH, PDBData::JRNL, rec_name);

		else if (rec_name == PDB::REMARK_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::REMARK_DATA_LENGTH, PDBData::REMARK, rec_name);

		else if (rec_name == PDB::DBREF_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::DBREF_DATA_LENGTH, PDBData::DBREF, rec_name);

		else if (rec_name == PDB::DBREF1_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::DBREF1_DATA_LENGTH, PDBData::DBREF1, rec_name);

		else if (rec_name == PDB::DBREF2_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::DBREF2_DATA_LENGTH, PDBData::DBREF2, rec_name);

		else if (rec_name == PDB::SEQADV_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SEQADV_DATA_LENGTH, PDBData::SEQADV, rec_name);

		else if (rec_name == PDB::SEQRES_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SEQRES_DATA_LENGTH, PDBData::SEQRES, rec_name);

		else if (rec_name == PDB::MODRES_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::MODRES_DATA_LENGTH, PDBData::MODRES, rec_name);

		else if (rec_name == PDB::HET_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::HET_DATA_LENGTH, PDBData::HET, rec_name);

		else if (rec_name == PDB::FORMUL_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::FORMUL_DATA_LENGTH, PDBData::FORMUL, rec_name);

		else if (rec_name == PDB::HETNAM_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::HETNAM_DATA_LENGTH, PDBData::HETNAM, rec_name);

		else if (rec_name == PDB::HETSYN_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::HETSYN_DATA_LENGTH, PDBData::HETSYN, rec_name);

		else if (rec_name == PDB::HELIX_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::HELIX_DATA_LENGTH, PDBData::HELIX, rec_name);

		else if (rec_name == PDB::SHEET_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SHEET_DATA_LENGTH, PDBData::SHEET, rec_name);

		else if (rec_name == PDB::TURN_PREFIX) // obsolete
			rem_llen -= readGenericDataRecord(is, PDB::TURN_DATA_LENGTH, PDBData::TURN, rec_name);

		else if (rec_name == PDB::SSBOND_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SSBOND_DATA_LENGTH, PDBData::SSBOND, rec_name);

		else if (rec_name == PDB::LINK_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::LINK_DATA_LENGTH, PDBData::LINK, rec_name);

		else if (rec_name == PDB::CISPEP_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::CISPEP_DATA_LENGTH, PDBData::CISPEP, rec_name);

		else if (rec_name == PDB::SITE_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SITE_DATA_LENGTH, PDBData::SITE, rec_name);

		else if (rec_name == PDB::CRYST1_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::CRYST1_DATA_LENGTH, PDBData::CRYST1, rec_name);

		else if (rec_name == PDB::MTRIX1_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::MTRIX1_DATA_LENGTH, PDBData::MTRIX1, rec_name);

		else if (rec_name == PDB::MTRIX2_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::MTRIX2_DATA_LENGTH, PDBData::MTRIX2, rec_name);

		else if (rec_name == PDB::MTRIX3_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::MTRIX3_DATA_LENGTH, PDBData::MTRIX3, rec_name);

		else if (rec_name == PDB::ORIGX1_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::ORIGX1_DATA_LENGTH, PDBData::ORIGX1, rec_name);

		else if (rec_name == PDB::ORIGX2_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::ORIGX2_DATA_LENGTH, PDBData::ORIGX2, rec_name);

		else if (rec_name == PDB::ORIGX3_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::ORIGX3_DATA_LENGTH, PDBData::ORIGX3, rec_name);

		else if (rec_name == PDB::SCALE1_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SCALE1_DATA_LENGTH, PDBData::SCALE1, rec_name);

		else if (rec_name == PDB::SCALE2_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SCALE2_DATA_LENGTH, PDBData::SCALE2, rec_name);

		else if (rec_name == PDB::SCALE3_PREFIX)
			rem_llen -= readGenericDataRecord(is, PDB::SCALE3_DATA_LENGTH, PDBData::SCALE3, rec_name);

		else if (rec_name == PDB::MODEL_PREFIX)
			rem_llen -= readMODELRecord(is);

		else if (rec_name == PDB::ATOM_PREFIX)
			rem_llen -= readATOMRecord(is, mol); 
		
		else if (rec_name == PDB::ANISOU_PREFIX)
			rem_llen -= skipRecordData(is, PDB::ANISOU_DATA_LENGTH, rec_name);

		else if (rec_name == PDB::TER_PREFIX) 
			rem_llen -= readTERRecord(is, mol); 

		else if (rec_name == PDB::HETATM_PREFIX)
			rem_llen -= readHETATMRecord(is, mol); 

		else if (rec_name == PDB::ENDMDL_PREFIX)
			rem_llen -= readENDMDLRecord(mol);

		else if (rec_name == PDB::CONECT_PREFIX)
			rem_llen -= readCONECTRecord(is, mol); 

		else if (rec_name == PDB::MASTER_PREFIX) 
			rem_llen -= readMASTERRecord(is); 

		else if (rec_name == PDB::END_PREFIX) 
			exit_loop = true;
		
		else if (rec_name == PDB::HYDBND_PREFIX)
			rem_llen -= skipRecordData(is, PDB::HYDBND_DATA_LENGTH, rec_name);

		else if (rec_name == PDB::SLTBRG_PREFIX)
			rem_llen -= skipRecordData(is, PDB::SLTBRG_DATA_LENGTH, rec_name);

		else if (strictErrorChecking)
			throw Base::IOError("PDBDataReader: invalid or unsupported PDB record name: " + rec_name);
	
		skipInputToNextLine(is, rem_llen, rec_name);

		if (!exit_loop && !strictErrorChecking && !hasMoreData(is))
			exit_loop = true;
	}

	checkMandatoryRecords();
	processAtomSequence(mol, false);
	setBondOrdersFromResTemplates(mol);
	perceiveBondOrders(mol);
	calcAtomCharges(mol);
	setPDBData(mol, pdbData);

	return true;
}

bool Biomol::PDBDataReader::skipPDBFile(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	init(is);

	while (true) {
		readPDBString(is, PDB::RECORD_NAME_LENGTH, stringData, true, "PDBDataReader: error while reading record name", false);
		
		if (strictErrorChecking && stringData.length() < PDB::RECORD_NAME_LENGTH)
			throw Base::IOError("PDBDataReader: PDB record name length < " + boost::lexical_cast<std::string>(PDB::RECORD_NAME_LENGTH));

		Internal::trimString(stringData, false, true);

		skipPDBLines(is, 1, ("PDBDataReader: error while skipping input to end of line of record " + stringData).c_str()); 

		if (stringData == PDB::END_PREFIX)
			break;
	}

	return true;
}
		
bool Biomol::PDBDataReader::hasMoreData(std::istream& is) const
{
	return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

void Biomol::PDBDataReader::init(std::istream& is)
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
	checkLineLength     = getCheckLineLengthParameter(ioBase); 

	is.imbue(std::locale::classic());
}

void Biomol::PDBDataReader::init(std::istream& is, Chem::Molecule& mol)
{
	init(is);

	resDictionary                        = getPDBResidueDictionaryParameter(ioBase);
	applyDictAtomBondingToStdResidues    = getPDBApplyDictAtomBondingToStdResiduesParameter(ioBase);
	applyDictOrderToStdResidues          = getPDBApplyDictBondOrdersToStdResiduesParameter(ioBase);
	applyDictAtomBondingToNonStdResidues = getPDBApplyDictAtomBondingToNonStdResiduesParameter(ioBase);
	applyDictOrderToNonStdResidues       = getPDBApplyDictBondOrdersToNonStdResiduesParameter(ioBase);
	ignoreConectRecords                  = getPDBIgnoreConectRecordsParameter(ioBase);
	setOrdersFromCONECTRecords           = getPDBDeduceBondOrdersFromCONECTRecordsParameter(ioBase);
	ignoreChargeField                    = getPDBIgnoreFormalChargeFieldParameter(ioBase);
	applyDictAtomCharges                 = getPDBApplyDictFormalAtomChargesParameter(ioBase);
	applyDictAtomTypes                   = getPDBApplyDictAtomTypesParameter(ioBase);
	calcCharges                          = getPDBCalcMissingFormalChargesParameter(ioBase);
	perceiveOrders                       = getPDBPerceiveMissingBondOrdersParameter(ioBase);
	evalMASTERRecord                     = getPDBEvaluateMASTERRecordParameter(ioBase);

	pdbData = PDBData::SharedPointer(new PDBData());
	currModelID = 0;
	lastModelID = 0;
	startAtomCount = mol.getNumAtoms();
	startBondCount = mol.getNumBonds();
	numCoordRecords = 0;

	recordHistogram.clear();
	serialToAtomMap.clear();
	atomSequence.clear();
	bondOrderCache.clear();
}

std::size_t Biomol::PDBDataReader::readGenericDataRecord(std::istream& is, std::size_t data_len, PDBData::RecordType rec_type, const std::string& rec_name)
{
	readPDBString(is, data_len, stringData, true, ("PDBDataReader: error while reading " + rec_name + " record data").c_str(), false);

	appendRecordData(rec_type, stringData);

	return data_len;
}

std::size_t Biomol::PDBDataReader::skipRecordData(std::istream& is, std::size_t data_len, const std::string& rec_name) const
{
	skipPDBChars(is, data_len, ("PDBDataReader: error while skipping data of record " + rec_name).c_str());

	return data_len;
}

std::size_t Biomol::PDBDataReader::readMODELRecord(std::istream& is)
{
	if (strictErrorChecking && currModelID != 0)
		throw Base::IOError("PDBDataReader: new MODEL record without foregoing ENDMDL record encountered");

	skipPDBChars(is, 5, "PDBDataReader: error while skipping characters in MODEL record");

	currModelID = readPDBNumber<std::size_t, 4>(is, "PDBDataReader: error while reading MODEL serial number", true);

	if (strictErrorChecking && currModelID != (lastModelID + 1))
		throw Base::IOError("PDBDataReader: non-sequential serial number in new MODEL record");

	return PDB::MODEL_DATA_LENGTH;
}

std::size_t Biomol::PDBDataReader::readATOMRecord(std::istream& is, Chem::Molecule& mol)
{
	readATOMRecord(is, mol, PDB::ATOM_PREFIX, false);

	return PDB::ATOM_DATA_LENGTH;
}

std::size_t Biomol::PDBDataReader::readTERRecord(std::istream& is, Chem::Molecule& mol)
{
	if (strictErrorChecking) {
		std::size_t serial = readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading serial number from TER record", true);

		SerialToAtomMap::mapped_type::const_iterator term_atom_it = serialToAtomMap[currModelID].find(serial - 1);

		if (term_atom_it == serialToAtomMap[currModelID].end())
			throw Base::IOError("PDBDataReader: error while processing TER record: no preceeding terminal atom with serial number " + 
								boost::lexical_cast<std::string>(serial - 1) + " found");
 
		const Chem::Atom& term_atom = *term_atom_it->second;

		skipPDBChars(is, 6, "PDBDataReader: error while skipping characters in TER record");
		
		readPDBString(is, 3, stringData, true, "PDBDataReader: error while reading residue name from TER record");

		if (stringData.empty())
			throw Base::IOError("PDBDataReader: unexpected end of TER record");

		if (getResidueCode(term_atom) != stringData)
			throw Base::IOError("PDBDataReader: resiude name in TER record does not match residue name of terminal atom");

		skipPDBChars(is, 1, "PDBDataReader: error while skipping characters in TER record");
		readPDBString(is, 1, stringData, true, "PDBDataReader: error while reading chain identifier from TER record", false);

		if (stringData.length() != 1)
			throw Base::IOError("PDBDataReader: unexpected end of TER record");

		if (getChainID(term_atom) != stringData[0])
			throw Base::IOError("PDBDataReader: chain ID in TER record does not match chain ID of terminal atom");

		long res_seq_num = readPDBNumber<long, 4>(is, "PDBDataReader: error while reading residue sequence number from TER record", true);

		if (getResidueSequenceNumber(term_atom) != res_seq_num)
			throw Base::IOError("PDBDataReader: residue sequence number in TER record does not match residue sequence number of terminal atom");

		readPDBString(is, 1, stringData, true, "PDBDataReader: error while reading residue insertion code from TER record", false);

		if (stringData.length() != 1)
			throw Base::IOError("PDBDataReader: unexpected end of TER record");

		if (getResidueInsertionCode(term_atom) != stringData[0])
			throw Base::IOError("PDBDataReader: residue insertion code in TER record does not match residue insertion code of terminal atom");

	} else
		skipPDBChars(is, PDB::TER_DATA_LENGTH, "PDBDataReader: error while skipping characters in TER record");

	processAtomSequence(mol, true);

	return PDB::TER_DATA_LENGTH;
}

std::size_t Biomol::PDBDataReader::readHETATMRecord(std::istream& is, Chem::Molecule& mol)
{
	readATOMRecord(is, mol, PDB::HETATM_PREFIX, true);

	return PDB::HETATM_DATA_LENGTH;
}

std::size_t Biomol::PDBDataReader::readENDMDLRecord(Chem::Molecule& mol)
{
	if (strictErrorChecking && currModelID == 0)
		throw Base::IOError("PDBDataReader: read ENDMDL record without foregoing MODEL record");

	processAtomSequence(mol, false);

	lastModelID = currModelID;
	currModelID = 0;

	return PDB::ENDMDL_DATA_LENGTH;
}

std::size_t Biomol::PDBDataReader::readCONECTRecord(std::istream& is, Chem::Molecule& mol)
{
	if (ignoreConectRecords && !strictErrorChecking) {
		skipPDBChars(is, PDB::CONECT_DATA_LENGTH, "PDBDataReader: error while skipping characters in CONECT record");
		return PDB::CONECT_DATA_LENGTH;
	}

	std::size_t serials[5];
	std::size_t num_atoms = 0;
	std::size_t chars_read = 0;

	for (std::size_t i = 0; i < 5; i++) {
		std::size_t serial = readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading atom serial from CONECT record", true, 100000);

		if (serial == 100000)
			break;

		chars_read += 5;
		serials[num_atoms++] = serial;
	}

	if (num_atoms <= 1) {
		if (strictErrorChecking)
			throw Base::IOError("PDBDataReader: CONECT record specifies not enough atoms to connect");

		return chars_read;
	}

	if (ignoreConectRecords)
		return chars_read;

	for (SerialToAtomMap::const_iterator map_it = serialToAtomMap.begin(), maps_end = serialToAtomMap.end(); map_it != maps_end; ++ map_it) { 
		Chem::Atom* atoms[5] = { 0, 0, 0, 0, 0 };

		for (std::size_t i = 0; i < num_atoms; i++) {
			SerialToAtomMap::mapped_type::const_iterator a_it = map_it->second.find(serials[i]);

			if (a_it == map_it->second.end()) {
				if (strictErrorChecking || i == 0)
					throw Base::IOError("PDBDataReader: error while reading CONECT record: atom with serial number " + 
										boost::lexical_cast<std::string>(serials[i]) + " not found");

				continue;
			}

			atoms[i] = a_it->second;
		}

		std::size_t first_atm_idx = mol.getAtomIndex(*atoms[0]);

		for (std::size_t i = 1; i < num_atoms; i++) {
			if (!atoms[i])
				continue;

			if (setOrdersFromCONECTRecords) {
				Chem::Bond* bond = atoms[0]->findBondToAtom(*atoms[i]);

				if (bond) {
					if (&bond->getBegin() == atoms[0]) {
						if (!hasOrder(*bond))
							setOrder(*bond, 1);
						else
							setOrder(*bond, getOrder(*bond) + 1);
					}

				} else 
					setOrder(mol.addBond(first_atm_idx, mol.getAtomIndex(*atoms[i])), 1);
			
				continue;
			}

			mol.addBond(first_atm_idx, mol.getAtomIndex(*atoms[i]));
		}
	}

	return chars_read;
}

std::size_t Biomol::PDBDataReader::readMASTERRecord(std::istream& is)
{
	if (!evalMASTERRecord) {
		skipPDBChars(is, PDB::MASTER_DATA_LENGTH, "PDBDataReader: error while skipping characters in MASTER record");
		return PDB::MASTER_DATA_LENGTH;
	}	

	skipPDBChars(is, 4, "PDBDataReader: error while skipping characters in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of REMARK records from MASTER record", true) != 
		recordHistogram[PDB::REMARK_PREFIX]) 
		throw Base::IOError("PDBDataReader: number of read REMARK records does not match count in MASTER record");
	
	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading zero field from MASTER record", true) != 0)
		throw Base::IOError("PDBDataReader: number in zero field in MASTER record is not zero");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of HET records from MASTER record", true) != 
		recordHistogram[PDB::HET_PREFIX])
		throw Base::IOError("PDBDataReader: number of read HET records does not match count in MASTER record");
	
	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of HELIX records from MASTER record", true) != 
		recordHistogram[PDB::HELIX_PREFIX])
		throw Base::IOError("PDBDataReader: number of read HELIX records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of SHEET records from MASTER record", true) != 
		recordHistogram[PDB::SHEET_PREFIX])
		throw Base::IOError("PDBDataReader: number of read SHEET records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of TURN records from MASTER record", true) != // deprecated
		recordHistogram[PDB::TURN_PREFIX])
		throw Base::IOError("PDBDataReader: number of read TURN records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of SITE records from MASTER record", true) != 
		recordHistogram[PDB::SITE_PREFIX])
		throw Base::IOError("PDBDataReader: number of read SITE records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of coordinate transformation records from MASTER record", true) != 
		(recordHistogram[PDB::ORIGX1_PREFIX] + recordHistogram[PDB::ORIGX2_PREFIX] + recordHistogram[PDB::ORIGX3_PREFIX] +
		 recordHistogram[PDB::SCALE1_PREFIX] + recordHistogram[PDB::SCALE2_PREFIX] + recordHistogram[PDB::SCALE3_PREFIX] +
		 recordHistogram[PDB::MTRIX1_PREFIX] + recordHistogram[PDB::MTRIX2_PREFIX] + recordHistogram[PDB::MTRIX3_PREFIX]))
		throw Base::IOError("PDBDataReader: number of read coordinate transformation records does not match count in MASTER record");

	readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of atomic coordinate records from MASTER record", true); // is wrong most of the time -> so just check number format

	// if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of atomic coordinate records from MASTER record", true) != 
	// 	numCoordRecords)                            
	// 	throw Base::IOError("PDBDataReader: number of read atomic coordinate records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of TER records from MASTER record", true) != 
		recordHistogram[PDB::TER_PREFIX])
		throw Base::IOError("PDBDataReader: number of read TER records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of CONECT records from MASTER record", true) != 
		recordHistogram[PDB::CONECT_PREFIX])
		throw Base::IOError("PDBDataReader: number of read CONECT records does not match count in MASTER record");

	if (readPDBNumber<std::size_t, 5>(is, "PDBDataReader: error while reading number of SEQRES records from MASTER record", true) != 
		recordHistogram[PDB::SEQRES_PREFIX])
		throw Base::IOError("PDBDataReader: number of read SEQRES records does not match count in MASTER record");

	return PDB::MASTER_DATA_LENGTH;
}

void Biomol::PDBDataReader::readATOMRecord(std::istream& is, Chem::Molecule& mol, const std::string& rec_name, bool het_atom)
{
	std::size_t serial = readPDBNumber<std::size_t, 5>(is, ("PDBDataReader: error while reading serial number from " + rec_name + " record").c_str(), true);
	Chem::Atom* atom = &mol.addAtom();

	serialToAtomMap[currModelID][serial] = atom;		

	setHeteroAtomFlag(*atom, het_atom);
	setModelNumber(*atom, currModelID);
	setSerialNumber(*atom, serial);

	skipPDBChars(is, 1, ("PDBDataReader: error while skipping characters in " + rec_name + " record").c_str());
	readPDBString(is, 4, stringData, true, ("PDBDataReader: error while reading atom name from " + rec_name + " record").c_str());

	setResidueAtomName(*atom, stringData);

	readPDBString(is, 1, stringData, true, ("PDBDataReader: error while reading alternate location indicator from " + rec_name + " record").c_str(), false);

	if (stringData.length() != 1)
		throw Base::IOError(("PDBDataReader: unexpected end of " + rec_name + " record").c_str());

	char alt_loc = stringData[0];

	setAltLocationID(*atom, alt_loc);

	readPDBString(is, 3, stringData, true, ("PDBDataReader: error while reading residue name from " + rec_name + " record").c_str());

	if (stringData.empty())
		throw Base::IOError(("PDBDataReader: unexpected end of " + rec_name + " record").c_str());

	setResidueCode(*atom, stringData);

	if (het_atom && stringData != PDB::WATER_RES_NAME)
		recordHistogram[PDB::HETGRP_PREFIX] = 1;

	skipPDBChars(is, 1, ("PDBDataReader: error while skipping characters in " + rec_name + " record").c_str());
	readPDBString(is, 1, stringData, true, ("PDBDataReader: error while reading chain identifier from " + rec_name + " record").c_str(), false);

	if (stringData.length() != 1)
		throw Base::IOError(("PDBDataReader: unexpected end of " + rec_name + " record").c_str());

	setChainID(*atom, stringData[0]);

	long res_seq_num = readPDBNumber<long, 4>(is, ("PDBDataReader: error while reading residue sequence number from " + 
											  rec_name + " record").c_str(), true);

	setResidueSequenceNumber(*atom, res_seq_num);

	readPDBString(is, 1, stringData, true, ("PDBDataReader: error while reading residue insertion code from " + rec_name + " record").c_str(), false);

	if (stringData.length() != 1)
		throw Base::IOError(("PDBDataReader: unexpected end of " + rec_name + " record").c_str());

	setResidueInsertionCode(*atom, stringData[0]);

	atomSequence.push_back(atom);

	skipPDBChars(is, 3, ("PDBDataReader: error while skipping characters in " + rec_name + " record").c_str());

	Math::Vector3D coords;

	coords(0) = readPDBNumber<double, 8>(is, ("PDBDataReader: error while reading x-coordinate from " + rec_name + " record").c_str(), true);
	coords(1) = readPDBNumber<double, 8>(is, ("PDBDataReader: error while reading y-coordinate from " + rec_name + " record").c_str(), true);
	coords(2) = readPDBNumber<double, 8>(is, ("PDBDataReader: error while reading z-coordinate from " + rec_name + " record").c_str(), true);

	setOccupancy(*atom, readPDBNumber<double, 6>(is, ("PDBDataReader: error while reading occupancy from " + rec_name + " record").c_str(), true));
	setBFactor(*atom, readPDBNumber<double, 6>(is, ("PDBDataReader: error while reading temperature factor from " + rec_name + " record").c_str(), true));
	set3DCoordinates(*atom, coords);

	skipPDBChars(is, 10, ("PDBDataReader: error while skipping characters in " + rec_name + " record").c_str());

	readPDBString(is, 2, stringData, true, ("PDBDataReader: error while reading element symbol from " + rec_name + " record").c_str(), true);

	if (!stringData.empty()) {
		if (stringData.length() == 2)
			stringData[1] = std::tolower(stringData[1], std::locale::classic());

		setSymbol(*atom, stringData);

		unsigned int atom_type = Chem::AtomDictionary::getType(stringData);

		if (strictErrorChecking && atom_type == Chem::AtomType::UNKNOWN)
			throw Base::IOError(("PDBDataReader: unknown chemical element specified in " + rec_name + " record: " + stringData).c_str());

		setType(*atom, atom_type);
	} 
//	else 
//		throw Base::IOError(("PDBDataReader: unexpected end of " + rec_name + " record").c_str());

	readPDBString(is, 2, stringData, true, ("PDBDataReader: error while reading formal charge specification from " + rec_name + " record").c_str(), true);

	if (!stringData.empty() && (!ignoreChargeField || strictErrorChecking)) {
		if (stringData.length() != 2) {
			if (strictErrorChecking)
				throw Base::IOError(("PDBDataReader: invalid length of formal charge specification in " + rec_name + " record").c_str());

		} else if (std::isdigit(stringData[0], std::locale::classic())) {
			long charge = stringData[0] - '0';

			if (stringData[1] == '-') {
				if (!ignoreChargeField) {
					charge = -charge;
					setFormalCharge(*atom, charge);
				}

			} else if (stringData[1] == '+') {
				if (!ignoreChargeField)
					setFormalCharge(*atom, charge);
		
			} else if (strictErrorChecking)
				throw Base::IOError(("PDBDataReader: invalid formal charge specification format in " + rec_name + " record").c_str());

		} else if (strictErrorChecking)
			throw Base::IOError(("PDBDataReader: invalid formal charge specification format in " + rec_name + " record").c_str());
	}

	if (stringData.empty() && !ignoreChargeField)
		setFormalCharge(*atom, 0);

	//if (currModelID < 2)
		numCoordRecords++;
}

void Biomol::PDBDataReader::appendRecordData(PDBData::RecordType type, const std::string& data) const
{
	PDBData::RecordIterator it = pdbData->getRecord(type);

	if (it != pdbData->getRecordsEnd()) {
		it->second.push_back(PDB::END_OF_LINE);
		it->second.append(data);

	} else
		pdbData->setRecord(type, data);
}

std::size_t Biomol::PDBDataReader::startNextRecord(std::istream& is, std::string& rec_name, std::string& prev_rec_name)
{
	prev_rec_name.swap(rec_name);

	readPDBString(is, PDB::RECORD_NAME_LENGTH, rec_name, true, "PDBDataReader: error while reading record name", false);

	if (strictErrorChecking && rec_name.length() < PDB::RECORD_NAME_LENGTH)
		throw Base::IOError("PDBDataReader: record name length < " +
							boost::lexical_cast<std::string>(PDB::RECORD_NAME_LENGTH));

	Internal::trimString(rec_name, false, true);

	bool rec_name_change = (prev_rec_name != rec_name);

	if (strictErrorChecking && !rec_name_change && (multilineRecords.find(rec_name) == multilineRecords.end()))
		throw Base::IOError(("PDBDataReader: record " + rec_name + " spans more than one line").c_str());

	checkRecordOrder(prev_rec_name, rec_name);

	if (strictErrorChecking && rec_name_change && 
		(recordHistogram.find(rec_name) != recordHistogram.end()) &&
		(oneTimeRecords.find(rec_name) != oneTimeRecords.end()))
		throw Base::IOError(("PDBDataReader: invalid multiple occurrences of record " + rec_name).c_str());

	recordHistogram[rec_name]++;

	return (PDB::MAX_LINE_LENGTH - PDB::RECORD_NAME_LENGTH);
}

void Biomol::PDBDataReader::skipInputToNextLine(std::istream& is, std::size_t rem_llen, const std::string& rec_name)
{
	if (checkLineLength || strictErrorChecking) {
		readPDBLine(is, stringData, ("PDBDataReader: error while reading line of record " + rec_name).c_str(), checkLineLength, 
					rem_llen);

		if (strictErrorChecking && !Internal::trimString(stringData).empty())
			throw Base::IOError(("PDBDataReader: found garbage after data of record " + rec_name).c_str());
			
	} else
		skipPDBLines(is, 1, ("PDBDataReader: error while reading skipping to end of line of record " + rec_name).c_str()); 
}

void Biomol::PDBDataReader::checkMandatoryRecords() const
{
	if (!strictErrorChecking)
		return;

	RecordHistogram::const_iterator rec_histo_end = recordHistogram.end();

	for (std::size_t i = 0; i < sizeof(PDB::MANDATORY_RECORDS) / sizeof(std::string[2]); i++) {
		if (PDB::MANDATORY_RECORDS[i][1].empty()) {              
			if (recordHistogram.find(PDB::MANDATORY_RECORDS[i][0]) == rec_histo_end)
				throw Base::IOError(("PDBDataReader: mandatory record " + PDB::MANDATORY_RECORDS[i][0] + " not found").c_str());

		} else if (recordHistogram.find(PDB::MANDATORY_RECORDS[i][1]) != rec_histo_end && 
				   recordHistogram.find(PDB::MANDATORY_RECORDS[i][0]) == rec_histo_end)
			throw Base::IOError(("PDBDataReader: record " + PDB::MANDATORY_RECORDS[i][0] + " is mandatory if record " +
								PDB::MANDATORY_RECORDS[i][1] + " exists, but was not found").c_str());
	}
}

void Biomol::PDBDataReader::checkRecordOrder(const std::string& prev_rec_name, const std::string& cur_rec_name) const
{
	if (!strictErrorChecking)
		return;

	RecordOrderIDMap::const_iterator cur_rec_entry_it = recordOrderIDs.find(cur_rec_name);

	if (cur_rec_entry_it == recordOrderIDs.end())
		return;

	RecordOrderIDMap::const_iterator prev_rec_entry_it = recordOrderIDs.find(prev_rec_name);
	std::size_t prev_rec_order_id = (prev_rec_entry_it == recordOrderIDs.end() ? 0 : prev_rec_entry_it->second.front());

	for (std::vector<std::size_t>::const_iterator it = cur_rec_entry_it->second.begin(), end = cur_rec_entry_it->second.end(); it != end; ++it)
		if (prev_rec_order_id <= *it)
			return;

	throw Base::IOError(("PDBDataReader: wrong record order: " + cur_rec_name + " must precede " + prev_rec_name).c_str());
}

void Biomol::PDBDataReader::processAtomSequence(Chem::Molecule& mol, bool chain_term)
{
	using namespace Chem;

	if (atomSequence.empty())
		return;

	prevResidueAtoms.clear();
	prevResidueLinkAtoms.clear();

	const ResidueDictionary& res_dict = (resDictionary ? *resDictionary : ResidueDictionary::get());

	for (AtomList::iterator as_it = atomSequence.begin(), as_end = atomSequence.end(); as_it != as_end; ) {
		Atom* first_atom = *as_it;
		std::size_t res_id = (getResidueSequenceNumber(*first_atom) << (sizeof(char) * 8)) + getResidueInsertionCode(*first_atom);
		const std::string& res_code = getResidueCode(*first_atom);

		currResidueAtoms.clear();
		currResidueLinkAtoms.clear();

		AtomList::iterator res_as_start_it = as_it;

		for (++as_it; as_it != as_end; ++as_it) {
			Atom* next_atom = *as_it;
			const std::string& next_res_code = getResidueCode(*next_atom);

			if (next_res_code != res_code)
				break;

			std::size_t next_res_id = (getResidueSequenceNumber(*next_atom) << (sizeof(char) * 8)) + getResidueInsertionCode(*next_atom);

			if (next_res_id != res_id)
				break;
		}

		std::sort(res_as_start_it, as_it, ResidueAtomCmpFunc());

		for (AtomList::iterator res_as_it = res_as_start_it; res_as_it != as_it; ) {
			Atom* atom = *res_as_it;
			const std::string& atom_name = getResidueAtomName(*atom);
			Math::Vector3DArray::SharedPointer coords(new Math::Vector3DArray());

			currResidueAtoms[atom_name] = atom;
			coords->addElement(get3DCoordinates(*atom));

			for (++res_as_it; res_as_it != as_it; ++res_as_it) {
				Atom* next_atom = *res_as_it;
				const std::string& next_atom_name = getResidueAtomName(*next_atom);

				if (next_atom_name != atom_name)
					break;

				//std::cerr << "alt. loc. atom: " << getSerialNumber(*next_atom) << " "
				//		  << getResidueAtomName(*next_atom) << " " << getAltLocationID(*next_atom) << std::endl;

				coords->addElement(get3DCoordinates(*next_atom));

				serialToAtomMap[currModelID][getSerialNumber(*next_atom)] = atom;
				mol.removeAtom(next_atom->getIndex());
			}

			set3DCoordinatesArray(*atom, coords);
		}

		MolecularGraph::SharedPointer res_tmplt = res_dict.getStructure(res_code);
		bool is_std_res = res_dict.isStdResidue(res_code);

		if (res_tmplt) {
			//std::cerr << "Using residue dictionary template for " << res_code << std::endl;

			if (applyDictAtomTypes || applyDictAtomCharges) {
				for (MolecularGraph::ConstAtomIterator a_it = res_tmplt->getAtomsBegin(), a_end = res_tmplt->getAtomsEnd(); a_it != a_end; ++a_it) {
					const Atom& atom = *a_it;
					Atom* res_atom = currResidueAtoms[getResidueAtomName(atom)];

					if (!res_atom)
						res_atom = currResidueAtoms[getResidueAltAtomName(atom)];

					if (!res_atom)
						continue;
				
					if (applyDictAtomTypes && (!hasType(*res_atom) || getType(*res_atom) == AtomType::UNKNOWN)) // fix unknown/missing element spec. in (HET)ATOM record
						setType(*res_atom, getType(atom));

					if (applyDictAtomCharges && !hasFormalCharge(*res_atom) && hasFormalCharge(atom))           // fix maybe missing charge spec. in (HET)ATOM record
						setFormalCharge(*res_atom, getFormalCharge(atom));
				} 
			}

			if ((is_std_res && applyDictAtomBondingToStdResidues) || (!is_std_res && applyDictAtomBondingToNonStdResidues)) {
				for (MolecularGraph::ConstBondIterator b_it = res_tmplt->getBondsBegin(), b_end = res_tmplt->getBondsEnd(); b_it != b_end; ++b_it) {
					const Bond& bond = *b_it;

					Atom* res_atom1 = currResidueAtoms[getResidueAtomName(bond.getBegin())];

					if (!res_atom1) 
						res_atom1 = currResidueAtoms[getResidueAltAtomName(bond.getBegin())];
	
					if (!res_atom1)
						continue;

					Atom* res_atom2 = currResidueAtoms[getResidueAtomName(bond.getEnd())];

					if (!res_atom2)
						res_atom2 = currResidueAtoms[getResidueAltAtomName(bond.getEnd())];

					if (!res_atom2) 
						continue;

					mol.addBond(mol.getAtomIndex(*res_atom1), mol.getAtomIndex(*res_atom2));
				}
			}
		}

		if (chain_term) {
			if (res_tmplt) {
				for (MolecularGraph::ConstAtomIterator a_it = res_tmplt->getAtomsBegin(), a_end = res_tmplt->getAtomsEnd(); a_it != a_end; ++a_it) {
					const Atom& atom = *a_it;
					Atom* res_atom = currResidueAtoms[getResidueAtomName(atom)];

					if (!res_atom)
						res_atom = currResidueAtoms[getResidueAltAtomName(atom)];

					if (!res_atom)
						continue;
		
					if (getResidueLinkingAtomFlag(atom)) {
						currResidueLinkAtoms.push_back(res_atom);
						setResidueLinkingAtomFlag(*res_atom, true);

					} else if (getResidueLeavingAtomFlag(atom))
						setResidueLeavingAtomFlag(*res_atom, true);
				} 

			} else
				currResidueLinkAtoms.insert(currResidueLinkAtoms.end(), res_as_start_it, as_it);

			bool exit = false;

			for (AtomList::const_iterator a_it1 = prevResidueLinkAtoms.begin(), a_end1 = prevResidueLinkAtoms.end(); a_it1 != a_end1; ++a_it1) {
				Atom* atom1 = *a_it1;
				const Math::Vector3D& atom1_pos = get3DCoordinates(*atom1);
				double cov_rad1 = getCovalentRadius(*atom1, 1);

				for (AtomList::const_iterator a_it2 = currResidueLinkAtoms.begin(), a_end2 = currResidueLinkAtoms.end(); a_it2 != a_end2; ++a_it2) {
					Atom* atom2 = *a_it2;
					const Math::Vector3D& atom2_pos = get3DCoordinates(*atom2);
					double cov_rad2 = getCovalentRadius(*atom2, 1);

					double dist = norm2(atom1_pos - atom2_pos);

					if (dist > 0.4 && dist <= (cov_rad1 + cov_rad2 + 0.4)) {
						mol.addBond(mol.getAtomIndex(*atom1), mol.getAtomIndex(*atom2));
						//setOrder(bond, 1);
						exit = true;
						break;
					}
				}

				if (exit)
					break;
			}

			prevResidueAtoms.swap(currResidueAtoms);
			prevResidueLinkAtoms.swap(currResidueLinkAtoms);
		}
	}

	atomSequence.clear();
}

void Biomol::PDBDataReader::setBondOrdersFromResTemplates(Chem::Molecule& mol)
{
	using namespace Chem;

	if (!applyDictOrderToStdResidues && !applyDictOrderToNonStdResidues)
		return;

	std::string bo_cache_key;
	const ResidueDictionary& res_dict = (resDictionary ? *resDictionary : ResidueDictionary::get());

	for (Molecule::BondIterator it = mol.getBondsBegin() + startBondCount, end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;

		if (hasOrder(bond))
			continue;

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		if (getResidueSequenceNumber(atom1) != getResidueSequenceNumber(atom2))
			continue;

		const std::string& res_code1 = getResidueCode(atom1);
		const std::string& res_code2 = getResidueCode(atom2);

		if (res_code1 != res_code2)
			continue;

		bool is_std_res = res_dict.isStdResidue(res_code1);	

		if ((is_std_res && !applyDictOrderToStdResidues) || (!is_std_res && !applyDictOrderToNonStdResidues))
			continue;

		const std::string& atom_name1 = getResidueAtomName(atom1);
		const std::string& atom_name2 = getResidueAtomName(atom2);

		bo_cache_key = res_code1;
		bo_cache_key.push_back('-');
		bo_cache_key.append(atom_name1);
		bo_cache_key.push_back('-');
		bo_cache_key.append(atom_name2);

		BondOrderCache::const_iterator boc_it = bondOrderCache.find(bo_cache_key);

		if (boc_it != bondOrderCache.end()) {
			setOrder(bond, boc_it->second); 
			continue;
		}

		MolecularGraph::SharedPointer res_tmplt = res_dict.getStructure(res_code1);

		if (!res_tmplt)
			continue;

		const Atom* tmplt_atom1 = getResTemplateAtom(*res_tmplt, atom_name1);

		if (!tmplt_atom1)
			continue;

		const Atom* tmplt_atom2 = getResTemplateAtom(*res_tmplt, atom_name2);

		if (!tmplt_atom2)
			continue;

		const Bond* tmplt_bond = tmplt_atom1->findBondToAtom(*tmplt_atom2);

		if (tmplt_bond) {
			std::size_t order = getOrder(*tmplt_bond);

			bondOrderCache[bo_cache_key] = order;

			bo_cache_key = res_code1;
			bo_cache_key.push_back('-');
			bo_cache_key.append(atom_name2);
			bo_cache_key.push_back('-');
			bo_cache_key.append(atom_name1);

			bondOrderCache[bo_cache_key] = order;

			setOrder(bond, order);
		}
	}
}

const Chem::Atom* Biomol::PDBDataReader::getResTemplateAtom(const Chem::MolecularGraph& tmplt, const std::string& atom_name) const
{
	using namespace Chem;

	for (MolecularGraph::ConstAtomIterator it = tmplt.getAtomsBegin(), end = tmplt.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (getResidueAtomName(atom) == atom_name)
			return &atom;

		if (getResidueAltAtomName(atom) == atom_name)
			return &atom;
	}

	return 0;
}

void Biomol::PDBDataReader::perceiveBondOrders(Chem::Molecule& mol)
{
	if (!perceiveOrders)
		return;

	if (startBondCount == 0) {
		perceiveSSSR(mol, true);
		setRingFlags(mol, true);

		Chem::perceiveBondOrders(mol, false);
		return;
	}

	readMolGraph.clear();

	std::for_each(mol.getBondsBegin() + startBondCount, mol.getBondsEnd(), 
				  boost::bind(&Chem::Fragment::addBond, readMolGraph, _1));

	setRingFlags(readMolGraph, true);
	
	Chem::perceiveBondOrders(readMolGraph, false);
}

void Biomol::PDBDataReader::calcAtomCharges(Chem::Molecule& mol)
{
	using namespace Chem;

	if (!calcCharges)
		return;

	if (startAtomCount != 0)
		readMolGraph.clear();

	for (Molecule::BondIterator it = mol.getBondsBegin() + startBondCount, end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;

		if (hasOrder(bond))
			continue;

		setOrder(bond, 1);

		if (startAtomCount != 0)
			readMolGraph.addBond(bond);
	}

	for (Molecule::AtomIterator it = mol.getAtomsBegin() + startAtomCount, end = mol.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (startAtomCount != 0)
			readMolGraph.addAtom(atom);

		if (hasImplicitHydrogenCount(atom))
			continue;

		if (hasFormalCharge(atom))
			continue;

		setImplicitHydrogenCount(atom, 0);
	}

	if (startAtomCount != 0)
		Chem::calcFormalCharges(readMolGraph, false);
	else
		Chem::calcFormalCharges(mol, false);
}
