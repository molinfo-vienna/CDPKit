/* 
 * OptimolLogReader.cpp
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


#include <sstream>
#include <cstring>

#include "CDPL/Internal/StringDataIOUtilities.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "OptimolLogReader.hpp"


using namespace CDPL;
using namespace Testing;


OptimolLogReader::OptimolLogReader(const std::string& log_file): logIStream(log_file.c_str()) 
{
    buildIndex();
}

bool OptimolLogReader::getSymbolicAtomTypes(const std::string& mol_name, SymbolicAtomTypeArray& sym_types)
{
    if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-LIST>  # symb"))
		return false;

	if (!skipLines(1))
		return false;

    sym_types.clear();

    std::string atom_type;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!skipTokens(iss, 2))
				break;
	    
			if (!(iss >> atom_type))
				break;
	    
			sym_types.push_back(atom_type);
		}
    }

    return true;
}

bool OptimolLogReader::getNumericAtomTypes(const std::string& mol_name, NumericAtomTypeArray& num_types)
{
    if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-LIST>  # ty"))
		return false;

	if (!skipLines(1))
		return false;

    num_types.clear();

    unsigned int atom_type;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!skipTokens(iss, 2))
				break;
	    
			if (!(iss >> atom_type))
				break;
	    
			num_types.push_back(atom_type);
		}
    }

    return true;
}

bool OptimolLogReader::getPartialAtomCharges(const std::string& mol_name, AtomChargeArray& charges)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

   if (!skipToLine(line, "OPTIMOL-LIST>  # char"))
		return false;

	if (!skipLines(1))
		return false;

    charges.clear();

    double charge;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!skipTokens(iss, 2))
				break;
	    
			if (!(iss >> charge))
				break;
	    
			charges.push_back(charge);
		}
    }

	return !charges.empty();
}

bool OptimolLogReader::getFormalAtomCharges(const std::string& mol_name, AtomChargeArray& charges)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

    if (!skipToLine(line, "OPTIMOL-LIST>  # fchar"))
		return false;

	if (!skipLines(1))
		return false;

    charges.clear();

    double charge;

    while (readLine(line)) {
		if (line.find("OPTIMOL-LIST") != std::string::npos)
			break;
	
		std::istringstream iss(line);

		while (true) {
			if (!skipTokens(iss, 2))
				break;
	    
			if (!(iss >> charge))
				break;
	    
			charges.push_back(charge);
		}
    }

	return true;
}

bool OptimolLogReader::getBondStretchingInteractions(const std::string& mol_name, BondStretchingInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-ANALYZE>  # bonds"))
		return false;

	if (!readLine(line))
		return false;

	ia_data.clear();

	if (line.find("TOTAL BOND STRAIN ENERGY") != std::string::npos)
		return true;

	if (line.find("B O N D   S T R E T C H I N G") == std::string::npos)
		return false;

	if (!skipLines(3))
		return false;

	std::string atom_idx;
	BondStretchingInteraction iaction;

	while (readLine(line)) {
		if (line.find("TOTAL BOND STRAIN ENERGY") != std::string::npos)
			break;

		std::istringstream iss(line);

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.atom1Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;
	
		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.atom2Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;
	
		if (!skipTokens(iss, 2))
			break;

		if (!(iss >> iaction.ffClass))
			break;

		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> iaction.refLength))
			break;

		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> iaction.energy))
			break;

		if (!(iss >> iaction.forceConst))
			break;

		ia_data.push_back(iaction);
    }

	return true;
}

bool OptimolLogReader::getAngleBendingInteractions(const std::string& mol_name, AngleBendingInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-ANALYZE>  # angles"))
		return false;

	if (!readLine(line))
		return false;

	ia_data.clear();

	if (line.find("TOTAL ANGLE STRAIN ENERGY") != std::string::npos)
		return true;

	if (line.find("A N G L E   B E N D I N G") == std::string::npos)
		return false;

	if (!skipLines(3))
		return false;

	std::string atom_idx;
	AngleBendingInteraction iaction;

	while (readLine(line)) {
		if (line.find("TOTAL ANGLE STRAIN ENERGY") != std::string::npos)
			break;

		std::istringstream iss(line);

		if (!(iss >> iaction.termAtom1Name))
			break;

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.ctrAtomIdx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;

		if (!(iss >> iaction.termAtom2Name))
			break;

		if (!skipTokens(iss, 3))
			break;

		if (!(iss >> iaction.ffClass))
			break;

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> iaction.refAngle))
			break;

		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> iaction.energy))
			break;

		if (!(iss >> iaction.forceConst))
			break;

		ia_data.push_back(iaction);
	}

	return true;
}

bool OptimolLogReader::getStretchBendInteractions(const std::string& mol_name, StretchBendInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-ANALYZE>  # strbnd"))
		return false;

	if (!readLine(line))
		return false;

	ia_data.clear();

	if (line.find("TOTAL STRETCH-BEND STRAIN ENERGY") != std::string::npos)
		return true;

	if (line.find("S T R E T C H   B E N D I N G") == std::string::npos)
		return false;

	if (!skipLines(3))
		return false;

	std::string atom_idx;
	StretchBendInteraction iaction;

	while (readLine(line)) {
		if (line.find("TOTAL STRETCH-BEND STRAIN ENERGY") != std::string::npos)
			break;

		std::istringstream iss(line);
	
		if (!(iss >> iaction.termAtom1Name))
			break;

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.ctrAtomIdx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;

		if (!(iss >> iaction.termAtom2Name))
			break;

		if (!skipTokens(iss, 3))
			break;

		if (!(iss >> iaction.ffClass))
			break;

		if (!skipTokens(iss, 3))
			break;

		if (!(iss >> iaction.energy))
			break;

		if (!(iss >> iaction.forceConst))
			break;

		ia_data.push_back(iaction);
	}

	return true;
}

bool OptimolLogReader::getOutOfPlaneBendingInteractions(const std::string& mol_name, OutOfPlaneBendingInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

    if (!skipToLine(line, "OPTIMOL-ANALYZE>  # out"))
		return false;

	if (!readLine(line))
		return false;

	ia_data.clear();

	if (line.find("TOTAL OUT-OF-PLANE STRAIN ENERGY") != std::string::npos)
		return true;

	if (line.find("O U T - O F - P L A N E    B E N D I N G") == std::string::npos)
		return false;

	if (!skipLines(4))
		return false;

	std::string atom_idx;
	OutOfPlaneBendingInteraction iaction;

	while (readLine(line)) {
		if (line.find("TOTAL OUT-OF-PLANE STRAIN ENERGY") != std::string::npos)
			break;

		std::istringstream iss(line);

		if (!(iss >> iaction.termAtom1Name))
			break;

		if (!(iss >> iaction.ctrAtomName))
			break;

		if (!(iss >> iaction.termAtom2Name))
			break;

		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> atom_idx))
			break;

		iaction.oopAtomIdx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;

		if (!skipTokens(iss, 5))
			break;

		if (!(iss >> iaction.energy))
			break;

		if (!(iss >> iaction.forceConst))
			break;

		ia_data.push_back(iaction);
	}

	return true;
}

bool OptimolLogReader::getTorsionInteractions(const std::string& mol_name, TorsionInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-ANALYZE>  # torsion"))
		return false;

	if (!readLine(line))
		return false;

	ia_data.clear();

	if (line.find("OPTIMOL-ANALYZE>  # b-intra") != std::string::npos)
		return true;

	if (line.find("T O R S I O N A L") == std::string::npos)
		return false;

	if (!skipLines(3))
		return false;

	std::string atom_idx;
	TorsionInteraction iaction;

	while (readLine(line)) {
		if (line.find("TOTAL TORSION STRAIN ENERGY") != std::string::npos)
			break;

		std::istringstream iss(line);

		if (!(iss >> iaction.termAtom1Name))
			break;

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.ctrAtom1Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.ctrAtom2Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;
	
		if (!(iss >> iaction.termAtom2Name))
			break;
	
		if (!skipTokens(iss, 4))
			break;

		if (!(iss >> iaction.ffClass))
			break;

		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> iaction.energy))
			break;

		if (!(iss >> iaction.torParams[0]))
			break;
	
		if (!(iss >> iaction.torParams[1]))
			break;

		if (!(iss >> iaction.torParams[2]))
			break;

		ia_data.push_back(iaction);
	}

	return true;
}

bool OptimolLogReader::getVanDerWaalsInteractions(const std::string& mol_name, VanDerWaalsInteractionData& ia_data)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL-ANALYZE>  # b-intra"))
		return false;

	if (!readLine(line))
		return false;

	if (line.find("Enter VDW REPULSION threshold for close contacts") == std::string::npos)
		return false;

	if (!skipLines(2))
		return false;

	ia_data.clear();

	if (!readLine(line))
		return false;

	if (line.find("NO OVER-THRESHOLD INTERATIONS BETWEEN INHIBITOR  ATOMS WERE DETECTED") != std::string::npos)
		return true;

	if (!skipLines(1))
		return false;

	std::string atom_idx;
	VanDerWaalsInteraction iaction;

	while (readLine(line)) {
		if (line.find("OPTIMOL-ANALYZE>  #") != std::string::npos)
			break;

		std::istringstream iss(line);

		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.atom1Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;
	
		if (!skipTokens(iss, 1))
			break;
	    
		if (!(iss >> atom_idx))
			break;
	    
		iaction.atom2Idx = std::stoul(atom_idx.substr(1, std::string::npos)) - 1;
	
		if (!skipTokens(iss, 1))
			break;

		if (!(iss >> iaction.energy))
			break;

		ia_data.push_back(iaction);
    }

	return true;	
}

bool OptimolLogReader::getEnergies(const std::string& mol_name, EnergyData& energies)
{
	if (!seekToRecord(mol_name))
		return false;

    std::string line;

	if (!skipToLine(line, "OPTIMOL>  # energy gradient"))
		return false;

	if (!readLine(line))
		return false;

	if (line.find("Total ENERGY (Kcal)") == std::string::npos)
		return false;

	energies.total = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Total ENERGY (Kcal)"), std::string::npos)));

	if (!readLine(line))
		return false;

	if (line.find("Bond Stretching") == std::string::npos)
		return false;

	energies.bondStretching = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Bond Stretching"), std::string::npos)));

	if (!readLine(line))
		return false;

	if (line.find("Angle Bending") == std::string::npos)
		return false;

	energies.angleBending = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Angle Bending"), std::string::npos)));

	if (!readLine(line))
		return false;

	if (line.find("Out-of-Plane Bending") == std::string::npos)
		return false;

	energies.outOfPlaneBending = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Out-of-Plane Bending"), std::string::npos)));
	
	if (!readLine(line))
		return false;

	if (line.find("Stretch-Bend") == std::string::npos)
		return false;

	energies.stretchBend = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Stretch-Bend"), std::string::npos)));

	if (!skipLines(3))
		return false;

	if (!readLine(line))
		return false;

	if (line.find("Total Torsion") == std::string::npos)
		return false;

	energies.torsion = std::stod(Internal::trimStringCopy(line.substr(std::strlen("     Total Torsion"), std::string::npos)));

	if (!skipLines(3))
		return false;

	if (!readLine(line))
		return false;

	if (line.find("Net vdW") == std::string::npos)
		return false;

	energies.vanDerWaals = std::stod(Internal::trimStringCopy(line.substr(std::strlen("     Net vdW"), std::string::npos)));

	if (!readLine(line))
		return false;

	if (line.find("Electrostatic") == std::string::npos)
		return false;

	energies.electrostatic = std::stod(Internal::trimStringCopy(line.substr(std::strlen(" Electrostatic"), std::string::npos)));

	return true;
}

bool OptimolLogReader::skipLines(std::size_t n)
{
	std::string tmp;

	for (std::size_t i = 0; i < n; i++)
		if (!readLine(tmp))
			return false;

	return true;
}

bool OptimolLogReader::skipTokens(std::istream& is, std::size_t n) const
{
	std::string tmp;

	for (std::size_t i = 0; i < n; i++)
		if (!(is >> tmp))
			return false;

	return true;
}

void OptimolLogReader::buildIndex()
{
    std::string line;

    while (skipToLine(line, "Structure Name")) {
		std::string::size_type colon_idx = line.find(':');
	
		if (colon_idx == std::string::npos)
			continue;

		std::string mol_name = line.substr(colon_idx + 1, std::string::npos);

		Internal::trimString(mol_name);
	
		recordOffsets.insert(RecordFileOffsetMap::value_type(mol_name, logIStream.tellg()));
    }
}

bool OptimolLogReader::skipToLine(std::string& line, const char* srch_str)
{
    while (readLine(line)) {
		if (line.find(srch_str) != std::string::npos)
			return true;
    }

    return false;
}

bool OptimolLogReader::readLine(std::string& line)
{
    if (!std::istream::sentry(logIStream, false))
		return false;

    line.clear();

    Internal::readLine(logIStream, line, "Error while reading MMFF94 log-file", true);

    return true;
}

bool OptimolLogReader::seekToRecord(const std::string& mol_name)
{
    RecordFileOffsetMap::const_iterator it = recordOffsets.find(mol_name);

    if (it == recordOffsets.end())
		return false;

    logIStream.clear();
    logIStream.seekg(it->second);

    return true;
}
