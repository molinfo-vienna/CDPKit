/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of various utility functions.
 */

#ifndef CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
#define CDPL_BIOMOL_UTILITYFUNCTIONS_HPP

#include <algorithm>

#ifndef BOOST_BIND_GLOBAL_PLACEHOLDERS
# define BOOST_BIND_GLOBAL_PLACEHOLDERS
#endif

#include <boost/bind.hpp>

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ProcessingFlags.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"


namespace CDPL 
{

    namespace Biomol 
    {

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
	}
}

#endif // CDPL_BIOMOL_UTILITYFUNCTIONS_HPP
 
