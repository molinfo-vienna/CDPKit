/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPDBBackboneFunction.cpp 
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

#include <string>

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


namespace
{

	const std::string C_AA_CARBONYL = "C";
	const std::string C_AA_ALPHA    = "CA";
	const std::string N_AA_AMIDE    = "N";
	const std::string O_AA_ACID     = "O";
	const std::string O_AA_TERMINAL = "OXT";
	const std::string P_NT          = "P";
	const std::string O3_NT         = "O3'";
	const std::string O5_NT         = "O5'";
	const std::string C5_NT         = "C5'";
	const std::string C4_NT         = "C4'";
	const std::string C3_NT         = "C3'";
}


bool Biomol::isPDBBackboneAtom(const Chem::Atom& atom)
{
	const std::string& label = getResidueAtomName(atom);

	return (label == C_AA_CARBONYL || label == C_AA_ALPHA || label == N_AA_AMIDE || label == O_AA_ACID || label == O_AA_TERMINAL ||
			label == P_NT || label == O3_NT || label == O5_NT || label == C5_NT || label == C4_NT || label == C3_NT);
}
