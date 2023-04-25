/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * INCHIMoleculeReader.cpp 
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
#include <locale>
#include <cassert>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "LibInChI/inchi_api.h"

#include "CDPL/Chem/INCHIMoleculeReader.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/RadicalType.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/INCHIReturnCode.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::string INCHI_PREFIX      = "InChI=1/";
	const std::string STD_INCHI_PREFIX  = "InChI=1S/";
	const std::string AUX_INFO_PREFIX   = "AuxInfo=1/";

	class INCHIInputManager
	{

	public:
		INCHIInputManager(inchi_Input* inchi_input): inchiInput(inchi_input) {}

		~INCHIInputManager() {
			Free_inchi_Input(inchiInput);
		}

	private:
		inchi_Input* inchiInput;
	};

	class InChIOutputStructManager
	{

	public:
		InChIOutputStructManager(inchi_OutputStruct* inchi_opt_struc_data): 
			inchiOptStruct(inchi_opt_struc_data) {}

		~InChIOutputStructManager() {
			FreeStructFromINCHI(inchiOptStruct);
		}

	private:
		inchi_OutputStruct* inchiOptStruct;
	};

	bool hasPrefix(const std::string& str, const std::string& prefix) {
		if (str.length() < prefix.length())
			return false;

		return std::equal(prefix.begin(), prefix.end(), str.begin());
	}
}


using namespace CDPL;


Chem::INCHIMoleculeReader::INCHIMoleculeReader(std::istream& is): 
	Util::StreamDataReader<Molecule, INCHIMoleculeReader>(is), returnCode(INCHIReturnCode::OKAY) {}

int Chem::INCHIMoleculeReader::getReturnCode() const
{
	return returnCode;
}

const std::string& Chem::INCHIMoleculeReader::getMessage() const
{
	return message;
}

const std::string& Chem::INCHIMoleculeReader::getLogOutput() const
{
	return logOutput;
}

bool Chem::INCHIMoleculeReader::readData(std::istream& is, Molecule& mol, bool overwrite)
{
	try {
		if (overwrite)
			mol.clear();

		return readMolecule(is, mol);

	} catch (const std::exception& e) {
		throw Base::IOError("INCHIMoleculeReader: while reading record " + 
							boost::lexical_cast<std::string>(getRecordIndex()) + ": " + e.what());
	}
}

bool Chem::INCHIMoleculeReader::skipData(std::istream& is)
{
	try {
		return skipMolecule(is);

	} catch (const std::exception& e) {
		throw Base::IOError("INCHIMoleculeReader: while skipping record " + 
							boost::lexical_cast<std::string>(getRecordIndex()) + ": " + e.what());
	}
}

bool Chem::INCHIMoleculeReader::moreData(std::istream& is)
{
	is.imbue(std::locale::classic());

	return bool(std::istream::sentry(is, false));
}

bool Chem::INCHIMoleculeReader::readMolecule(std::istream& is, Molecule& mol)
{
	message.clear();
	logOutput.clear();
	returnCode = INCHIReturnCode::ERROR;

	if (!moreData(is))
		return false;

	if (!(is >> inputToken)) 
		throw Base::IOError("reading input data failed");

	strictErrorChecking = getStrictErrorCheckingParameter(*this);

	inputData.clear();

	bool use_aux_info = false;

	if (hasPrefix(inputToken, AUX_INFO_PREFIX)) {
		inputData.insert(inputData.end(), inputToken.begin(), inputToken.end());
		use_aux_info = true;

	} else {
		if (!hasPrefix(inputToken, INCHI_PREFIX) && !hasPrefix(inputToken, STD_INCHI_PREFIX))
			throw Base::IOError("not a valid InChI string - expected '" + INCHI_PREFIX + "' or '" + STD_INCHI_PREFIX + "' prefix");

		inputData.insert(inputData.end(), inputToken.begin(), inputToken.end());

		if (moreData(is)) {
			std::istream::pos_type saved_is_pos = is.tellg();	

			if (!(is >> inputToken)) 
				throw Base::IOError("reading input data failed");

			if (hasPrefix(inputToken, AUX_INFO_PREFIX)) {
				inputData.clear();
				inputData.insert(inputData.end(), inputToken.begin(), inputToken.end());
				use_aux_info = true;

			} else 
				is.seekg(saved_is_pos);
		}
	}

	inputData.push_back(0);

	const std::string& inchi_options = getINCHIInputOptionsParameter(*this);

	inchiOptions.clear();
	inchiOptions.insert(inchiOptions.end(), inchi_options.begin(), inchi_options.end());
	inchiOptions.push_back(0);

#if (defined(_WIN32) || defined(__CYGWIN__))
	std::replace(inchiOptions.begin(), inchiOptions.end(), '-', '/');
#else
	std::replace(inchiOptions.begin(), inchiOptions.end(), '/', '-');
#endif

	if (use_aux_info) {
		inchi_Input inchi_input = { 0, 0, &inchiOptions[0], 0, 0 };
		InchiInpData inchi_inp_data = { &inchi_input, 0, { 0 } };

		INCHIInputManager inchi_input_mgr(&inchi_input);

		returnCode = Get_inchi_Input_FromAuxInfo(&inputData[0], 1, 0, &inchi_inp_data);
		message = inchi_inp_data.szErrMsg;

		if (returnCode != INCHIReturnCode::OKAY && returnCode != INCHIReturnCode::WARNING) 
			throw Base::IOError(message);

		if (inchi_input.num_atoms < 0) {
			if (strictErrorChecking)
				throw Base::IOError("atom array length < 0");

		} else if (inchi_input.num_stereo0D < 0) {
			if (strictErrorChecking)
				throw Base::IOError("stereo 0D array length < 0");

			buildMolecule(mol, inchi_input.atom, inchi_input.num_atoms, 0, 0);

		} else
			buildMolecule(mol, inchi_input.atom, inchi_input.num_atoms, 
						  inchi_input.stereo0D, inchi_input.num_stereo0D);

	} else {
		inchi_InputINCHI inchi_input = { &inputData[0], &inchiOptions[0] };
		inchi_OutputStruct inchi_opt_struc_data = { 0, 0, 0, 0, 0, 0 };

		InChIOutputStructManager inchi_opt_struc_data_mgr(&inchi_opt_struc_data);

		returnCode = GetStructFromINCHI(&inchi_input, &inchi_opt_struc_data);
		message = inchi_opt_struc_data.szMessage;

		if (inchi_opt_struc_data.szLog)
			logOutput = inchi_opt_struc_data.szLog;

		if (returnCode != INCHIReturnCode::OKAY && returnCode != INCHIReturnCode::WARNING) 
			throw Base::IOError(message);

		if (inchi_opt_struc_data.num_atoms < 0) {
			if (strictErrorChecking)
				throw Base::IOError("atom array length < 0");

		} else if (inchi_opt_struc_data.num_stereo0D < 0) {
			if (strictErrorChecking)
				throw Base::IOError("stereo 0D array length < 0");

			buildMolecule(mol, inchi_opt_struc_data.atom, inchi_opt_struc_data.num_atoms, 0, 0);

		} else
			buildMolecule(mol, inchi_opt_struc_data.atom, inchi_opt_struc_data.num_atoms, 
						  inchi_opt_struc_data.stereo0D, inchi_opt_struc_data.num_stereo0D);
	}

	return true;
}

bool Chem::INCHIMoleculeReader::skipMolecule(std::istream& is)
{
	if (!moreData(is))
		return false;

	if (!(is >> inputToken)) 
		throw Base::IOError("reading input data failed");

	if (hasPrefix(inputToken, AUX_INFO_PREFIX))
		return true;

	if (!hasPrefix(inputToken, INCHI_PREFIX) && !hasPrefix(inputToken, STD_INCHI_PREFIX))
		throw Base::IOError("not an InChI string - expected '" + INCHI_PREFIX + "' or '" + STD_INCHI_PREFIX + "' prefix");

	if (moreData(is)) {
		std::istream::pos_type saved_is_pos = is.tellg();	

		if (!(is >> inputToken)) 
			throw Base::IOError("reading input data failed");

		if (hasPrefix(inputToken, AUX_INFO_PREFIX))
			return true;

		is.seekg(saved_is_pos);
	}

	return true;
}

void Chem::INCHIMoleculeReader::buildMolecule(Molecule& mol, const inchi_Atom* inchi_atoms, std::size_t num_inchi_atoms, 
											  const inchi_Stereo0D* inchi_stereo_infos, std::size_t num_inchi_stereo_infos) const
{
	if (!inchi_atoms || num_inchi_atoms == 0) 
		return;

	std::size_t atom_idx_offs = mol.getNumAtoms();
	std::size_t coords_dim = 0;

	mol.reserveMemoryForAtoms(atom_idx_offs + num_inchi_atoms);

	for (std::size_t i = 0; i < num_inchi_atoms; i++) {
		Atom& atom = mol.addAtom();
		const inchi_Atom& inchi_atom = inchi_atoms[i];
				
		createBonds(mol, atom, inchi_atom, atom_idx_offs);
		setElement(atom, inchi_atom);
		setIsotope(atom, inchi_atom);
		setFormalCharge(atom, inchi_atom);
		setRadicalType(atom, inchi_atom);
		setImplicitHCounts(atom, inchi_atom);

		if (inchi_atom.z != 0.0)
			coords_dim = 3;
		else if (inchi_atom.y != 0.0)
			coords_dim = std::max(coords_dim, std::size_t(2));
	}

	if (coords_dim == 3)
		set3DCoordinates(mol, inchi_atoms, atom_idx_offs);
	else if (coords_dim == 2)
		set2DCoordinates(mol, inchi_atoms, atom_idx_offs);

	process0DStereoInfo(mol, inchi_stereo_infos, num_inchi_stereo_infos, atom_idx_offs);
}

void Chem::INCHIMoleculeReader::setElement(Atom& atom, const inchi_Atom& inchi_atom) const
{
	setSymbol(atom, inchi_atom.elname);
	setType(atom, AtomDictionary::getType(inchi_atom.elname));
}

void Chem::INCHIMoleculeReader::setIsotope(Atom& atom, const inchi_Atom& inchi_atom) const
{
	if (inchi_atom.isotopic_mass == 0)
		return;

	if (inchi_atom.isotopic_mass < 0) {
		if (strictErrorChecking)
			throw Base::IOError("isotopic mass < 0");

		return;
	}

	if (inchi_atom.isotopic_mass >= ISOTOPIC_SHIFT_FLAG - ISOTOPIC_SHIFT_MAX) {
		long isotope = long(AtomDictionary::getMostAbundantIsotope(getType(atom))) + 
			inchi_atom.isotopic_mass - ISOTOPIC_SHIFT_FLAG;

		if (isotope > 0)
			Chem::setIsotope(atom, isotope);

	} else
		Chem::setIsotope(atom, inchi_atom.isotopic_mass);
}

void Chem::INCHIMoleculeReader::setFormalCharge(Atom& atom, const inchi_Atom& inchi_atom) const
{
	if (inchi_atom.charge == 0)
		return;

	Chem::setFormalCharge(atom, inchi_atom.charge);
}

void Chem::INCHIMoleculeReader::setRadicalType(Atom& atom, const inchi_Atom& inchi_atom) const
{
	switch (inchi_atom.radical) {

	case INCHI_RADICAL_SINGLET:
		Chem::setRadicalType(atom, RadicalType::SINGLET);
		return;

	case INCHI_RADICAL_DOUBLET:
		Chem::setRadicalType(atom, RadicalType::DOUBLET);
		return;

	case INCHI_RADICAL_TRIPLET:
		Chem::setRadicalType(atom, RadicalType::TRIPLET);
		return;

	default:
		if (strictErrorChecking)
			throw Base::IOError("invalid radical type");

	case INCHI_RADICAL_NONE:
		return;
	}
}

void Chem::INCHIMoleculeReader::setImplicitHCounts(Atom&, const inchi_Atom&) const {}

void Chem::INCHIMoleculeReader::createBonds(Molecule& mol, Atom& atom, const inchi_Atom& inchi_atom, std::size_t atom_idx_offs) const
{
	if (inchi_atom.num_bonds < 0) {
		if (strictErrorChecking)
			throw Base::IOError("number of bonds for atom < 0");

		return;
	}

	if (inchi_atom.num_bonds > MAXVAL)
		throw Base::IOError("number of bonds for atom exceeds maximum valence");

	for (std::size_t i = 0; i < std::size_t(inchi_atom.num_bonds); i++) {
		if (inchi_atom.bond_type[i] == INCHI_BOND_TYPE_NONE)
			continue;

		std::size_t nbr_atom_idx = inchi_atom.neighbor[i] + atom_idx_offs;

		if (nbr_atom_idx >= mol.getNumAtoms())
			continue;

		assert(!atom.containsAtom(mol.getAtom(nbr_atom_idx)));

		unsigned int bond_stereo = BondStereoFlag::PLAIN;

		switch (inchi_atom.bond_stereo[i]) {

			case INCHI_BOND_STEREO_SINGLE_2UP:
				bond_stereo = BondStereoFlag::REVERSE_UP;
				break;

			case INCHI_BOND_STEREO_SINGLE_1UP:
				bond_stereo = BondStereoFlag::UP;
				break;

			case INCHI_BOND_STEREO_SINGLE_2DOWN:
				bond_stereo = BondStereoFlag::REVERSE_DOWN;
				break;

			case INCHI_BOND_STEREO_SINGLE_1DOWN:
				bond_stereo = BondStereoFlag::DOWN;
				break;

			case INCHI_BOND_STEREO_SINGLE_2EITHER:
				bond_stereo = BondStereoFlag::REVERSE_EITHER;
				break;

			case INCHI_BOND_STEREO_SINGLE_1EITHER:
				bond_stereo = BondStereoFlag::EITHER;
				break;

			case INCHI_BOND_STEREO_DOUBLE_EITHER:
				bond_stereo = BondStereoFlag::EITHER;

			case INCHI_BOND_STEREO_NONE:
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("invalid bond stereo");
		}

		Bond& bond = mol.addBond(mol.getAtomIndex(atom), nbr_atom_idx);

		switch (inchi_atom.bond_type[i]) {

			case INCHI_BOND_TYPE_SINGLE:
				setOrder(bond, 1);
				break;

			case INCHI_BOND_TYPE_DOUBLE:
				setOrder(bond, 2);
				break;

			case INCHI_BOND_TYPE_TRIPLE:
				setOrder(bond, 3);
				break;

			case INCHI_BOND_TYPE_ALTERN:
				if (strictErrorChecking)
					throw Base::IOError("found ALTERN bond type");

			default:
				if (strictErrorChecking)
					throw Base::IOError("invalid bond type");

				setOrder(bond, 1);
		}

		set2DStereoFlag(bond, bond_stereo);
	}
}

void Chem::INCHIMoleculeReader::set2DCoordinates(Molecule& mol, const inchi_Atom* inchi_atoms, std::size_t atom_idx_offs) const
{
	Molecule::AtomIterator atoms_end = mol.getAtomsEnd();

	for (Molecule::AtomIterator it = mol.getAtomsBegin() + atom_idx_offs; it != atoms_end; ++it, ++inchi_atoms) 
		Chem::set2DCoordinates(*it, Math::vec(inchi_atoms->x, inchi_atoms->y));
}

void Chem::INCHIMoleculeReader::set3DCoordinates(Molecule& mol, const inchi_Atom* inchi_atoms, std::size_t atom_idx_offs) const
{
	Molecule::AtomIterator atoms_end = mol.getAtomsEnd();

	for (Molecule::AtomIterator it = mol.getAtomsBegin() + atom_idx_offs; it != atoms_end; ++it, ++inchi_atoms) 
		Chem::set3DCoordinates(*it, Math::vec(inchi_atoms->x, inchi_atoms->y, inchi_atoms->z));
}

void Chem::INCHIMoleculeReader::process0DStereoInfo(Molecule& mol, const inchi_Stereo0D* inchi_stereo_infos,
													std::size_t num_inchi_stereo_infos, std::size_t atom_idx_offs) const
{
	if (!inchi_stereo_infos || num_inchi_stereo_infos == 0) 
		return;

	for (std::size_t i = 0; i < num_inchi_stereo_infos; i++) {
		const inchi_Stereo0D& inchi_stereo = inchi_stereo_infos[i];

		switch (inchi_stereo.type) {

			case INCHI_StereoType_Tetrahedral:
				process0DAtomStereoInfo(mol, inchi_stereo, atom_idx_offs);
				continue;

			case INCHI_StereoType_DoubleBond:
				process0DBondStereoInfo(mol, inchi_stereo, atom_idx_offs);
				continue;

			default:
				if (strictErrorChecking)
					throw Base::IOError("invalid 0D stereo type");

			case INCHI_StereoType_None:	
			case INCHI_StereoType_Allene:
				continue;
		}
	}
}

void Chem::INCHIMoleculeReader::process0DAtomStereoInfo(Molecule& mol, const inchi_Stereo0D& inchi_stereo,
														std::size_t atom_idx_offs) const
{
	if (inchi_stereo.central_atom < 0) {
		if (strictErrorChecking)
			throw Base::IOError("tetrahedral stereo: central atom index < 0");
		return;
	}

	std::size_t ctr_atom_idx = inchi_stereo.central_atom + atom_idx_offs;
	Atom& ctr_atom = mol.getAtom(ctr_atom_idx);
	std::size_t num_bonds = ctr_atom.getNumBonds();

	if (num_bonds < 3 || num_bonds > 4) // sanity check
		return;

	unsigned int config = AtomConfiguration::NONE;

	switch (inchi_stereo.parity) {

		case INCHI_PARITY_ODD:
			config = AtomConfiguration::R;
			break;

		case INCHI_PARITY_EVEN:
			config = AtomConfiguration::S;
			break;

		case INCHI_PARITY_UNKNOWN:
			config = AtomConfiguration::EITHER;
			break;

		case INCHI_PARITY_NONE:
			config = AtomConfiguration::NONE;
			break;

		case INCHI_PARITY_UNDEFINED:
			config =  AtomConfiguration::UNDEF;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("tetrahedral stereo: invalid atom parity");
			return;
	}

	if (config != AtomConfiguration::R && config != AtomConfiguration::S) {
		setStereoDescriptor(ctr_atom, num_bonds == 3 ? 
							StereoDescriptor(config, ctr_atom.getAtom(0), ctr_atom.getAtom(1), ctr_atom.getAtom(2)) :
							StereoDescriptor(config, ctr_atom.getAtom(0), ctr_atom.getAtom(1), ctr_atom.getAtom(2), ctr_atom.getAtom(3)));
		return;
	}

	const Atom* ref_atoms[4];

	for (std::size_t i = 0; i < 4; i++) {
		if (inchi_stereo.neighbor[i] < 0) {
			if (strictErrorChecking)
				throw Base::IOError("tetrahedral stereo: invalid neighbor list");
			return;
		}

		ref_atoms[i] = &mol.getAtom(inchi_stereo.neighbor[i] + atom_idx_offs);

		if (num_bonds == 4 || i > 0) {
			if (!ctr_atom.findBondToAtom(*ref_atoms[i])) {
				if (strictErrorChecking)
					throw Base::IOError("tetrahedral stereo: invalid neighbor list");
				return;
			}
		}
	}

	setStereoDescriptor(ctr_atom, num_bonds == 3 ? 
						StereoDescriptor(config, *ref_atoms[1], *ref_atoms[2], *ref_atoms[3]) :
						StereoDescriptor(config, *ref_atoms[1], *ref_atoms[2], *ref_atoms[3], *ref_atoms[0]));
}

void Chem::INCHIMoleculeReader::process0DBondStereoInfo(Molecule& mol, const inchi_Stereo0D& inchi_stereo,
														std::size_t atom_idx_offs) const
{
	if (inchi_stereo.neighbor[1] < 0 || inchi_stereo.neighbor[2] < 0) {
		if (strictErrorChecking)
			throw Base::IOError("double bond stereo: invalid neighbor list");	
		return;
	}

	std::size_t bond_atom1_idx = inchi_stereo.neighbor[1] + atom_idx_offs;
	std::size_t bond_atom2_idx = inchi_stereo.neighbor[2] + atom_idx_offs;

	Atom* bond_atoms[2] = { &mol.getAtom(bond_atom1_idx), &mol.getAtom(bond_atom2_idx) };
	Bond& bond = bond_atoms[0]->getBondToAtom(*bond_atoms[1]);

	if (getOrder(bond) != 2)
		return;

	unsigned int config = BondConfiguration::NONE;

	switch (inchi_stereo.parity) {

		case INCHI_PARITY_ODD:
			config = BondConfiguration::CIS;
			break;

		case INCHI_PARITY_EVEN:
			config = BondConfiguration::TRANS;
			break;

		case INCHI_PARITY_UNKNOWN:
			config = BondConfiguration::EITHER;
			break;
		
		case INCHI_PARITY_UNDEFINED:
			config = BondConfiguration::UNDEF;
			break;

		case INCHI_PARITY_NONE:
			config = BondConfiguration::NONE;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("double bond stereo: invalid bond parity");
			return;
	}

	const Atom* ref_atoms[2] = { 0, 0 };

	for (std::size_t i = 0; i < 2; i++) {
		std::size_t num_bonds = bond_atoms[i]->getNumBonds();

		if (num_bonds < 2 || num_bonds > 3)
			return;

		int inchi_ref_atom_idx = (i == 0 ? inchi_stereo.neighbor[0] : inchi_stereo.neighbor[3]);

		if ((config == BondConfiguration::CIS || config == BondConfiguration::TRANS) && inchi_ref_atom_idx < 0) {
			if (strictErrorChecking)
				throw Base::IOError("double bond stereo: invalid neighbor list");	
			return;
		}

		if (inchi_ref_atom_idx >= 0) {
			ref_atoms[i] = &mol.getAtom(inchi_ref_atom_idx + atom_idx_offs);
			const Bond* ref_bond = bond_atoms[i]->findBondToAtom(*ref_atoms[i]);

			if (!ref_bond || ref_bond == &bond) {
				if (strictErrorChecking)
					throw Base::IOError("double bond stereo: invalid neighbor list");	
				return;
			}
		}
	}

	setStereoDescriptor(bond, ref_atoms[0] && ref_atoms[1] ? 
						StereoDescriptor(config, *ref_atoms[0], *bond_atoms[0], *bond_atoms[1], *ref_atoms[1]) :
						StereoDescriptor(config));
}
