/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_BIOMOL_ATOMFUNCTIONS_HPP
#define CDPL_BIOMOL_ATOMFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class MolecularGraph;
		class Fragment;
	}

	namespace Biomol 
	{

		/**
		 * \addtogroup CDPL_BIOMOL_ATOM_FUNCTIONS
		 * @{
		 */

		CDPL_BIOMOL_API const std::string& getResidueAtomName(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueAtomName(Chem::Atom& atom, const std::string& name);

		CDPL_BIOMOL_API void clearResidueAtomName(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueAtomName(const Chem::Atom& atom);


		CDPL_BIOMOL_API const std::string& getResidueAltAtomName(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueAltAtomName(Chem::Atom& atom, const std::string& name);

		CDPL_BIOMOL_API void clearResidueAltAtomName(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueAltAtomName(const Chem::Atom& atom);


		CDPL_BIOMOL_API bool getResidueLeavingAtomFlag(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueLeavingAtomFlag(Chem::Atom& atom, bool leaving);

		CDPL_BIOMOL_API void clearResidueLeavingAtomFlag(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueLeavingAtomFlag(const Chem::Atom& atom);
	

		CDPL_BIOMOL_API bool getResidueLinkingAtomFlag(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueLinkingAtomFlag(Chem::Atom& atom, bool linking);

		CDPL_BIOMOL_API void clearResidueLinkingAtomFlag(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueLinkingAtomFlag(const Chem::Atom& atom);
		

		CDPL_BIOMOL_API const std::string& getResidueCode(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueCode(Chem::Atom& atom, const std::string& code);

		CDPL_BIOMOL_API void clearResidueCode(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueCode(const Chem::Atom& atom);


		CDPL_BIOMOL_API long getResidueSequenceNumber(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueSequenceNumber(Chem::Atom& atom, long seq_no);

		CDPL_BIOMOL_API void clearResidueSequenceNumber(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueSequenceNumber(const Chem::Atom& atom);


		CDPL_BIOMOL_API char getResidueInsertionCode(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setResidueInsertionCode(Chem::Atom& atom, char code);

		CDPL_BIOMOL_API void clearResidueInsertionCode(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasResidueInsertionCode(const Chem::Atom& atom);


		CDPL_BIOMOL_API bool getHeteroAtomFlag(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setHeteroAtomFlag(Chem::Atom& atom, bool is_het);

		CDPL_BIOMOL_API void clearHeteroAtomFlag(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasHeteroAtomFlag(const Chem::Atom& atom);


		CDPL_BIOMOL_API char getChainID(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setChainID(Chem::Atom& atom, char id);

		CDPL_BIOMOL_API void clearChainID(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasChainID(const Chem::Atom& atom);


		CDPL_BIOMOL_API char getAltLocationID(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setAltLocationID(Chem::Atom& atom, char id);

		CDPL_BIOMOL_API void clearAltLocationID(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasAltLocationID(const Chem::Atom& atom);


		CDPL_BIOMOL_API std::size_t getModelNumber(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setModelNumber(Chem::Atom& atom, std::size_t model_no);

		CDPL_BIOMOL_API void clearModelNumber(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasModelNumber(const Chem::Atom& atom);
	

		CDPL_BIOMOL_API std::size_t getSerialNumber(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setSerialNumber(Chem::Atom& atom, std::size_t serial_no);

		CDPL_BIOMOL_API void clearSerialNumber(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasSerialNumber(const Chem::Atom& atom);


		CDPL_BIOMOL_API double getOccupancy(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setOccupancy(Chem::Atom& atom, double occupancy);

		CDPL_BIOMOL_API void clearOccupancy(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasOccupancy(const Chem::Atom& atom);


		CDPL_BIOMOL_API double getBFactor(const Chem::Atom& atom);

		CDPL_BIOMOL_API void setBFactor(Chem::Atom& atom, double factor);

		CDPL_BIOMOL_API void clearBFactor(Chem::Atom& atom);

		CDPL_BIOMOL_API bool hasBFactor(const Chem::Atom& atom);

		
		CDPL_BIOMOL_API bool isPDBBackboneAtom(const Chem::Atom& atom);


		CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::Atom& atom, const char* res_code = 0, char chain_id = 0, long res_seq_no = 0,
												char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, std::size_t serial_no = 0);

		CDPL_BIOMOL_API bool areInSameResidue(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int flags = AtomPropertyFlag::DEFAULT);

		CDPL_BIOMOL_API void extractResidueSubstructure(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& res_substruct, 
														bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_ATOMFUNCTIONS_HPP
 
