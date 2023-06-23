/* 
 * INCHIMolecularGraphWriter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
#include <algorithm>
#include <limits>

#include "LibInChI/inchi_api.h"

#include "CDPL/Chem/INCHIMolecularGraphWriter.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/RadicalType.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/INCHIReturnCode.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace 
{

	const std::size_t MAX_NUM_ATOMS        = 1024;

	class INCHIOutputManager
	{

	public:
		INCHIOutputManager(inchi_Output* inchi_output): inchiOutput(inchi_output) {}

		~INCHIOutputManager() {
			FreeINCHI(inchiOutput);
		}

	private:
		inchi_Output* inchiOutput;
	};
}


using namespace CDPL;


Chem::INCHIMolecularGraphWriter::INCHIMolecularGraphWriter(std::ostream& os): 
	output(os), returnCode(INCHIReturnCode::OKAY), state(os.good()) {}

Chem::INCHIMolecularGraphWriter::~INCHIMolecularGraphWriter() {}

Base::DataWriter<Chem::MolecularGraph>& Chem::INCHIMolecularGraphWriter::write(const MolecularGraph& molgraph)
{
	state = false;

	writeMolGraph(molgraph);
	invokeIOCallbacks(1.0);

	return *this;
}

Chem::INCHIMolecularGraphWriter::operator const void*() const
{
	return (state ? this : 0);
}

bool Chem::INCHIMolecularGraphWriter::operator!() const
{
	return !state;
}

int Chem::INCHIMolecularGraphWriter::getReturnCode() const
{
	return returnCode;
}

const std::string& Chem::INCHIMolecularGraphWriter::getMessage() const
{
	return message;
}

const std::string& Chem::INCHIMolecularGraphWriter::getLogOutput() const
{
	return logOutput;
}

void Chem::INCHIMolecularGraphWriter::writeMolGraph(const MolecularGraph& molgraph)
{
	message.clear();
	logOutput.clear();
	returnCode = INCHIReturnCode::ERROR;

	strictErrorChecking = getStrictErrorCheckingParameter(*this);

	std::size_t coords_dim = getCoordsDimension(molgraph);

	setupAtomTable(molgraph, coords_dim);

	inchiStereoInfo.clear();

	if (coords_dim == 0)
		setup0DStereoInfo(molgraph);

	const std::string& inchi_options = getINCHIOutputOptionsParameter(*this);

	inchiOptions.clear();
	inchiOptions.insert(inchiOptions.end(), inchi_options.begin(), inchi_options.end());
	inchiOptions.push_back(0);

#if (defined(_WIN32) || defined(__CYGWIN__))
	std::replace(inchiOptions.begin(), inchiOptions.end(), '-', '/');
#else
	std::replace(inchiOptions.begin(), inchiOptions.end(), '/', '-');
#endif

	inchi_Input inchi_input = { &inchiAtomTable[0], &inchiStereoInfo[0], &inchiOptions[0], 
								short(molgraph.getNumAtoms()), short(inchiStereoInfo.size()) };
	inchi_Output inchi_output = { 0, 0, 0, 0 };

	INCHIOutputManager inchi_output_mgr(&inchi_output);

	returnCode = GetINCHI(&inchi_input, &inchi_output);

	if (inchi_output.szMessage)
		message = inchi_output.szMessage;

	if (inchi_output.szLog)
		logOutput = inchi_output.szLog;

	if (returnCode != INCHIReturnCode::OKAY && returnCode != INCHIReturnCode::WARNING) 
		throw Base::IOError("INCHIMolecularGraphWriter: " + message);

	if (output.tellp() > 0)
		output << getRecordSeparatorParameter(*this);

	if (inchi_output.szInChI)
		output << inchi_output.szInChI;

	if (inchi_output.szAuxInfo)
		output << ' ' << inchi_output.szAuxInfo;

	state = output.good();
}

void Chem::INCHIMolecularGraphWriter::setupAtomTable(const MolecularGraph& molgraph, std::size_t coords_dim)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	if (num_atoms >= MAX_NUM_ATOMS)
		throw Base::IOError("INCHIMolecularGraphWriter: maximum number of atoms exceeded");

	if (inchiAtomTable.size() < num_atoms)
		inchiAtomTable.resize(num_atoms);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		inchi_Atom& inchi_atom = inchiAtomTable[molgraph.getAtomIndex(atom)];

		setBondingInfo(molgraph, atom, inchi_atom, coords_dim);
		setElementSymbol(atom, inchi_atom);
		setIsotope(atom, inchi_atom);
		setFormalCharge(atom, inchi_atom);
		setCoordinates(atom, inchi_atom, coords_dim);
		setRadicalType(atom, inchi_atom);
		setImplicitHCounts(inchi_atom);
	}
}

std::size_t Chem::INCHIMolecularGraphWriter::getCoordsDimension(const MolecularGraph& molgraph) const
{
	std::size_t dim = getCoordinatesDimensionParameter(*this);

	if (dim == 2 || dim == 3)
		return dim;

	if (hasCoordinates(molgraph, 3))
		return 3;

	if (hasCoordinates(molgraph, 2))
		return 2;
	
	return 0;
}

void Chem::INCHIMolecularGraphWriter::setElementSymbol(const Atom& atom, inchi_Atom& inchi_atom) const
{
	const std::string& symbol = getSymbol(atom);
		
	if (symbol.length() >= ATOM_EL_LEN)
		throw Base::IOError("INCHIMolecularGraphWriter: maximum atom symbol length exceeded");

	std::copy(symbol.begin(), symbol.end(), inchi_atom.elname);
	inchi_atom.elname[symbol.length()] = 0;
}

void Chem::INCHIMolecularGraphWriter::setIsotope(const Atom& atom, inchi_Atom& inchi_atom) const
{
	std::size_t isotope = getIsotope(atom);

	if (isotope >= ISOTOPIC_SHIFT_FLAG - ISOTOPIC_SHIFT_MAX)
		throw Base::IOError("INCHIMolecularGraphWriter: isotopic mass exceeds upper limit");

	inchi_atom.isotopic_mass = AT_NUM(isotope);
}

void Chem::INCHIMolecularGraphWriter::setFormalCharge(const Atom& atom, inchi_Atom& inchi_atom) const
{
	long charge = getFormalCharge(atom);

	if (charge > std::numeric_limits<S_CHAR>::max() || charge < std::numeric_limits<S_CHAR>::min())
		throw Base::IOError("INCHIMolecularGraphWriter: formal charge out of valid range");

	inchi_atom.charge = S_CHAR(charge);
}

void Chem::INCHIMolecularGraphWriter::setCoordinates(const Atom& atom, inchi_Atom& inchi_atom, 
													 std::size_t coords_dim) const
{
	switch (coords_dim) {

		case 2: {
			const Math::Vector2D& coords = get2DCoordinates(atom);
			
			inchi_atom.x = coords(0);
			inchi_atom.y = coords(1);
			inchi_atom.z = 0.0;
			return;
		}

		case 3: {
			const Math::Vector3D& coords = get3DCoordinates(atom);

			inchi_atom.x = coords(0);
			inchi_atom.y = coords(1);
			inchi_atom.z = coords(2);
			return;
		}

		default:
			inchi_atom.x = 0.0;
			inchi_atom.y = 0.0;
			inchi_atom.z = 0.0;
	}
}

void Chem::INCHIMolecularGraphWriter::setRadicalType(const Atom& atom, inchi_Atom& inchi_atom) const
{
	switch (getRadicalType(atom)) {

		case RadicalType::SINGLET:
			inchi_atom.radical = INCHI_RADICAL_SINGLET;
			return;

		case RadicalType::DOUBLET:
			inchi_atom.radical = INCHI_RADICAL_DOUBLET;
			return;

		case RadicalType::TRIPLET:
			inchi_atom.radical = INCHI_RADICAL_TRIPLET;
			return;

		default:
			if (strictErrorChecking)
				throw Base::IOError("INCHIMolecularGraphWriter: invalid radical type");

		case RadicalType::NOT_RADICALIC:
			inchi_atom.radical = INCHI_RADICAL_NONE;
	}
}

void Chem::INCHIMolecularGraphWriter::setImplicitHCounts(inchi_Atom& inchi_atom) const
{
	inchi_atom.num_iso_H[0] = -1;
	inchi_atom.num_iso_H[1] = 0;
	inchi_atom.num_iso_H[2] = 0;
	inchi_atom.num_iso_H[3] = 0;
}

void Chem::INCHIMolecularGraphWriter::setBondingInfo(const MolecularGraph& molgraph, const Atom& atom, inchi_Atom& inchi_atom, 
													 std::size_t coords_dim) const
{
	Atom::ConstBondIterator nbr_bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator nbr_a_it = atom.getAtomsBegin();
	std::size_t i = 0;

	for (Atom::ConstBondIterator nbr_b_it = atom.getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
		const Atom& nbr_atom = *nbr_a_it;
		const Bond& nbr_bond = *nbr_b_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
			continue;

		if (i >= MAXVAL)
			throw Base::IOError("INCHIMolecularGraphWriter: maximum number of atom neighbor bonds exceeded");

		inchi_atom.neighbor[i] = AT_NUM(molgraph.getAtomIndex(nbr_atom));

		std::size_t order = getOrder(nbr_bond);

		switch (order) {
		
			case 2:
				inchi_atom.bond_type[i] = INCHI_BOND_TYPE_DOUBLE;
				break;

			case 3:
				inchi_atom.bond_type[i] = INCHI_BOND_TYPE_TRIPLE;
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("INCHIMolecularGraphWriter: invalid bond order");

			case 1:
				inchi_atom.bond_type[i] = INCHI_BOND_TYPE_SINGLE;
		}

		if (coords_dim != 0) {
			switch (get2DStereoFlag(nbr_bond)) {

				case BondStereoFlag::UP:
					if (order != 1)
						break;

					inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
												   INCHI_BOND_STEREO_SINGLE_1UP : INCHI_BOND_STEREO_SINGLE_2UP); 
					continue;

				case BondStereoFlag::REVERSE_UP:
					if (order != 1)
						break;

					inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
												   INCHI_BOND_STEREO_SINGLE_2UP : INCHI_BOND_STEREO_SINGLE_1UP); 
					continue;

				case BondStereoFlag::DOWN:
					if (order != 1)
						break;

					inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
												   INCHI_BOND_STEREO_SINGLE_1DOWN : INCHI_BOND_STEREO_SINGLE_2DOWN); 
					continue;

				case BondStereoFlag::REVERSE_DOWN:
					if (order != 1)
						break;

					inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
												   INCHI_BOND_STEREO_SINGLE_2DOWN : INCHI_BOND_STEREO_SINGLE_1DOWN); 
					continue;

				case BondStereoFlag::EITHER:
					if (order == 1)
						inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
													   INCHI_BOND_STEREO_SINGLE_1EITHER : INCHI_BOND_STEREO_SINGLE_2EITHER);
					else if (order == 2)
						inchi_atom.bond_stereo[i++] = INCHI_BOND_STEREO_DOUBLE_EITHER;
					else
						break;

					continue;

				case BondStereoFlag::REVERSE_EITHER:
					if (order == 1)
						inchi_atom.bond_stereo[i++] = (&nbr_bond.getBegin() == &atom ? 
													   INCHI_BOND_STEREO_SINGLE_2EITHER : INCHI_BOND_STEREO_SINGLE_1EITHER);
					else if (order == 2)
						inchi_atom.bond_stereo[i++] = INCHI_BOND_STEREO_DOUBLE_EITHER;
					else
						break;

					continue;

				case BondStereoFlag::PLAIN:
					if (order == 2 && getStereoDescriptor(nbr_bond).getConfiguration() ==
						BondConfiguration::EITHER) {

						inchi_atom.bond_stereo[i++] = INCHI_BOND_STEREO_DOUBLE_EITHER;
						continue;
					}

					break;

				default:
					if (strictErrorChecking)
						throw Base::IOError("INCHIMolecularGraphWriter: invalid bond stereo flag");	
			}
		}

		inchi_atom.bond_stereo[i++] = INCHI_BOND_STEREO_NONE;
	}

	inchi_atom.num_bonds = AT_NUM(i);
}

void Chem::INCHIMolecularGraphWriter::setup0DStereoInfo(const MolecularGraph& molgraph)
{
	setup0DAtomStereoInfo(molgraph);
	setup0DBondStereoInfo(molgraph);
}

void Chem::INCHIMolecularGraphWriter::setup0DAtomStereoInfo(const MolecularGraph& molgraph)
{
	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
		const Atom& atom = *a_it;
	   
		const StereoDescriptor& stereo_desc = calcStereoDescriptor(atom, molgraph, 0);
		std::size_t num_ref_atoms = stereo_desc.getNumReferenceAtoms();

		if (num_ref_atoms < 3)
			continue;

		inchi_Stereo0D inchi_stereo;

		switch (stereo_desc.getConfiguration()) {

			case AtomConfiguration::S:
				inchi_stereo.parity = INCHI_PARITY_EVEN;
				break;

			case AtomConfiguration::R:
				inchi_stereo.parity = INCHI_PARITY_ODD;
				break;

			case AtomConfiguration::EITHER:
				inchi_stereo.parity = INCHI_PARITY_UNKNOWN;
				break;

			case AtomConfiguration::UNDEF:
				continue;

			case AtomConfiguration::NONE:
				inchi_stereo.parity = INCHI_PARITY_NONE;
				break;	

			default:
				if (strictErrorChecking)
					throw Base::IOError("INCHIMolecularGraphWriter: invalid atom configuration");	
				continue;
		}

		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		for (std::size_t i = 0; i < num_ref_atoms; i++)
			inchi_stereo.neighbor[(i + 1) % 4] = AT_NUM(molgraph.getAtomIndex(*ref_atoms[i]));

		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		if (num_ref_atoms == 3)
			inchi_stereo.neighbor[0] = AT_NUM(atom_idx);

		inchi_stereo.type = INCHI_StereoType_Tetrahedral;
		inchi_stereo.central_atom = AT_NUM(atom_idx);

		inchiStereoInfo.push_back(inchi_stereo);
	}
}

void Chem::INCHIMolecularGraphWriter::setup0DBondStereoInfo(const MolecularGraph& molgraph)
{
	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();

	for (MolecularGraph::ConstBondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
		const Bond& bond = *b_it;
		std::size_t order = getOrder(bond);
		
		inchi_Stereo0D inchi_stereo;	
		StereoDescriptor stereo_desc(0);

		if (order == 2) {
			stereo_desc = calcStereoDescriptor(bond, molgraph, 0, 8);
		
		} else if (order == 1 && getRingFlag(bond)) {
			const Atom* bond_atoms[2] = { &bond.getBegin(), &bond.getEnd() };
			bool skip = false;

			for (std::size_t i = 0; i < 2; i++) {
				std::size_t num_bonds = bond_atoms[i]->getNumBonds();

				if (num_bonds < 2 || num_bonds > 3) {
					skip = true;
					break;
				}

				Atom::ConstBondIterator nbr_bonds_end = bond_atoms[i]->getBondsEnd();
				Atom::ConstAtomIterator nbr_a_it = bond_atoms[i]->getAtomsBegin();
				std::size_t num_dbl_ring_bonds = 0;

				for (Atom::ConstBondIterator nbr_b_it = bond_atoms[i]->getBondsBegin(); nbr_b_it != nbr_bonds_end; ++nbr_b_it, ++nbr_a_it) {
					const Bond& nbr_bond = *nbr_b_it;

					if (&bond == &nbr_bond)
						continue;

					const Atom& nbr_atom = *nbr_a_it;

					if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(nbr_bond))
						continue;

					if (getOrder(nbr_bond) == 2 && getRingFlag(nbr_bond))
						num_dbl_ring_bonds++;
				}

				if (num_dbl_ring_bonds != 1) {
					skip = true;
					break;
				}
			}

			if (skip)
				continue;

			stereo_desc = calcStereoDescriptor(bond, molgraph, 1, 8, false);
		
		} else
			continue;

		if (stereo_desc.getNumReferenceAtoms() != 4)
			continue;
		
		switch (stereo_desc.getConfiguration()) {

			case BondConfiguration::CIS:
				inchi_stereo.parity = INCHI_PARITY_ODD;
				break;

			case BondConfiguration::TRANS:
				inchi_stereo.parity = INCHI_PARITY_EVEN;
				break;
				
			case BondConfiguration::EITHER:
				inchi_stereo.parity = INCHI_PARITY_UNKNOWN;
				break;

			case BondConfiguration::NONE:
				inchi_stereo.parity = INCHI_PARITY_NONE;
				break;

			default:
				if (strictErrorChecking)
					throw Base::IOError("INCHIMolecularGraphWriter: invalid bond stereo flag");	
				continue;
		}

		const Atom* const* ref_atoms = stereo_desc.getReferenceAtoms();

		for (std::size_t i = 0; i < 4; i++)
			inchi_stereo.neighbor[i] = AT_NUM(molgraph.getAtomIndex(*ref_atoms[i]));

		inchi_stereo.type = INCHI_StereoType_DoubleBond;
		inchi_stereo.central_atom = NO_ATOM;
			
		inchiStereoInfo.push_back(inchi_stereo);
	}
}
