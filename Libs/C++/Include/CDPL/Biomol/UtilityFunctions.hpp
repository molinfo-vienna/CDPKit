/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.hpp 
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
 * \brief Declaration of various utility functions.
 */

#ifndef CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
#define CDPL_BIOMOL_UTILITYFUNCTIONS_HPP

#include <algorithm>
#include <limits>

#include <boost/bind.hpp>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/AtomPropertyFlag.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctionWrapper.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Fragment;
	}
	
    namespace Biomol 
    {

		/**
		 * \addtogroup CDPL_BIOMOL_UTILITY_FUNCTIONS
		 * @{
		 */

		const long IGNORE_SEQUENCE_NO = std::numeric_limits<long>::min();
		const long IGNORE_SERIAL_NO   = std::numeric_limits<long>::min();


		CDPL_BIOMOL_API bool isPDBBackboneAtom(const Chem::Atom& atom);

		CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms, 
												  double max_dist, bool inc_core_atoms = false, bool append = false);

		CDPL_BIOMOL_API void extractProximalAtoms(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_atoms, 
												  const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool inc_core_atoms = false, bool append = false);

		CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues, 
														double max_dist, bool append = false);

		CDPL_BIOMOL_API void extractEnvironmentResidues(const Chem::MolecularGraph& core, const Chem::MolecularGraph& macromol, Chem::Fragment& env_residues, 
														const Chem::Atom3DCoordinatesFunction& coords_func, double max_dist, bool append = false);

		CDPL_BIOMOL_API void setHydrogenResidueSequenceInfo(Chem::MolecularGraph& molgraph, bool overwrite, unsigned int flags = AtomPropertyFlag::DEFAULT);

		CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::MolecularGraph& molgraph, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
												char ins_code = 0, std::size_t model_no = 0);
		
		CDPL_BIOMOL_API bool matchesResidueInfo(const Chem::Atom& atom, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
												char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO);

		CDPL_BIOMOL_API bool areInSameResidue(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int flags = AtomPropertyFlag::DEFAULT);

		CDPL_BIOMOL_API void extractResidueSubstructure(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& res_substruct, 
														bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT, bool append = false);

		CDPL_BIOMOL_API void extractResidueSubstructures(const Chem::AtomContainer& cntnr, const Chem::MolecularGraph& molgraph, Chem::Fragment& res_substructs, 
														 bool cnctd_only = false, unsigned int flags = AtomPropertyFlag::DEFAULT, bool append = false);
		
		template <typename Iter>
		Iter findResidueAtom(Iter it, Iter end, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
							 char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO)
		{
			return std::find_if(it, end, boost::bind(&matchesResidueInfo, _1, res_code, chain_id, res_seq_no, ins_code, model_no, atom_name, serial_no));
		}

	    template <typename Iter>
		Iter findResidue(Iter it, Iter end, const char* res_code = 0, const char* chain_id = 0, long res_seq_no = IGNORE_SEQUENCE_NO,
						 char ins_code = 0, std::size_t model_no = 0, const char* atom_name = 0, long serial_no = IGNORE_SERIAL_NO)
		{
			for ( ; it != end; ++it) {
				const Chem::MolecularGraph& res = *it;
				
				if (!matchesResidueInfo(res, res_code, chain_id, res_seq_no, ins_code, model_no))
					continue;

				if (atom_name == 0 && serial_no == IGNORE_SERIAL_NO)
					return it;

				if (std::find_if(res.getAtomsBegin(), res.getAtomsEnd(), 
								 boost::bind(&matchesResidueInfo, _1, res_code, chain_id, res_seq_no, ins_code, model_no, atom_name, serial_no)) != res.getAtomsEnd())
					return it;
			}

			return end;
		}
	
		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
 
