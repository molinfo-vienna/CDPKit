/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TPSACalculator.cpp 
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

#include "CDPL/Chem/TPSACalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


namespace
{

	double getTPSAIncrement(std::size_t atom_type, std::size_t num_h_bonds, std::size_t num_heavy_bonds, 
							std::size_t num_arom_bonds, std::size_t num_sgl_bonds, std::size_t num_dbl_bonds, 
							std::size_t num_tpl_bonds, long charge, bool in_3_ring)
	{
		using namespace Chem;

		switch (atom_type) {

			case AtomType::N:

				switch (num_heavy_bonds) {
					
					case 1:
						if (num_h_bonds == 0 && num_tpl_bonds == 1 && charge == 0) 
							return 23.79;      // N#

						if (num_h_bonds == 1 && num_dbl_bonds == 1 && charge == 0) 
							return 23.85;      // [NH]=

						if (num_h_bonds == 2 && num_sgl_bonds == 1 && charge == 0) 
							return 26.02;      // [NH2]-

						if (num_h_bonds == 2 && num_dbl_bonds == 1 && charge == 1) 
							return 25.59;      // [NH2+]=

						if (num_h_bonds == 3 && num_sgl_bonds == 1 && charge == 1) 
							return 27.64;      // [NH3+]-

						break;

					case 2:
						if (num_h_bonds == 0 && num_sgl_bonds == 1 && num_dbl_bonds == 1 && charge == 0) 
							return 12.36;      // =N-

						if (num_h_bonds == 0 && num_tpl_bonds == 1 && num_dbl_bonds == 1 && charge == 0) 
							return 13.60;      // =N#

						if (num_h_bonds == 0 && num_dbl_bonds == 2 && charge == 1) 
							return 13.60;      // =[N+]=

						if (num_h_bonds == 1 && num_sgl_bonds == 2 && charge == 0 && !in_3_ring) 
							return 12.03;      // -[NH]-

						if (num_h_bonds == 1 && num_sgl_bonds == 2 && charge == 0 && in_3_ring) 
							return 21.94;      // -[NH]-r3

						if (num_h_bonds == 0 && num_tpl_bonds == 1 && num_sgl_bonds == 1 && charge == 1) 
							return 4.36;       // -[N+]#

						if (num_h_bonds == 1 && num_dbl_bonds == 1 && num_sgl_bonds == 1 && charge == 1) 
							return 13.97;      // -[NH+]=

						if (num_h_bonds == 2 && num_sgl_bonds == 2 && charge == 1) 
							return 16.61;      // -[NH2+]-

						if (num_h_bonds == 0 && num_arom_bonds == 2 && charge == 0) 
							return 12.89;      // :[n]:

						if (num_h_bonds == 1 && num_arom_bonds == 2 && charge == 0) 
							return 15.79;      // :[nH]:

						if (num_h_bonds == 1 && num_arom_bonds == 2 && charge == 1) 
							return 14.14;      // :[nH+]:

						break;
			
					case 3:
						if (num_h_bonds == 0 && num_sgl_bonds == 3 && charge == 0 && !in_3_ring) 
							return 3.24;       // -N(-)-

						if (num_h_bonds == 0 && num_sgl_bonds == 3 && charge == 0 && in_3_ring) 
							return 3.01;       // -N(-)-r3

						if (num_h_bonds == 0 && num_sgl_bonds == 1 && num_dbl_bonds == 2 && charge == 0) 
							return 11.68;      // -N(=)=

						if (num_h_bonds == 0 && num_sgl_bonds == 2 && num_dbl_bonds == 1 && charge == 1) 
							return 11.68;      // -[N+](-)=

						if (num_h_bonds == 0 && num_sgl_bonds == 2 && num_dbl_bonds == 1 && charge == 1) 
							return 3.01;       // =[N+](-)-

						if (num_h_bonds == 1 && num_sgl_bonds == 3 && charge == 1) 
							return 4.44;       // -[NH+](-)-

						if (num_h_bonds == 0 && num_arom_bonds == 3 && charge == 0) 
							return 4.41;       // :[n](:):

						if (num_h_bonds == 0 && num_sgl_bonds == 1 && num_arom_bonds == 2 && charge == 0) 
							return 4.93;       // -:[n](:):

						if (num_h_bonds == 0 && num_dbl_bonds == 1 && num_arom_bonds == 2 && charge == 0) 
							return 8.39;       // =:[n](:):

						if (num_h_bonds == 0 && num_arom_bonds == 3 && charge == 1) 
							return 4.10;       // :[n+](:):

						if (num_h_bonds == 0 && num_sgl_bonds == 1 && num_arom_bonds == 2 && charge == 1) 
							return 3.88;       // -:[n+](:):

						break;

					case 4:
						if (num_h_bonds == 0 && num_sgl_bonds == 4 && charge == 1) 
							return 0.0;       // -[N+](-)(-)-

						break;

					default:
						break;
				}
			   
				return std::max(30.5 - num_heavy_bonds * 8.2 + num_h_bonds * 1.5, 0.0);       // N with non-standard valency

			case AtomType::O:

				switch (num_heavy_bonds) {
				
					case 1:
						if (num_h_bonds == 0 && num_dbl_bonds == 1 && charge == 0) 
							return 17.07;      // O=

						if (num_h_bonds == 1 && num_sgl_bonds == 1 && charge == 0) 
							return 20.23;      // [OH]-

						if (num_h_bonds == 0 && num_sgl_bonds == 1 && charge == -1) 
							return 23.06;      // [O-]-

						break;

					case 2:
						if (num_h_bonds == 0 && num_sgl_bonds == 2 && charge == 0 && !in_3_ring) 
							return 9.23;       // -O-

						if (num_h_bonds == 0 && num_sgl_bonds == 2 && charge == 0 && in_3_ring) 
							return 12.53;      // -O-r3

						if (num_h_bonds == 0 && num_arom_bonds == 2 && charge == 0) 
							return 13.14;      // :o:

						break;

					default:
						break;
				}

				return std::max(28.5 - num_heavy_bonds * 8.6 + num_h_bonds * 1.5, 0.0);       // O with non-standard valency

			default:
				return 0.0;
		}
	}
}


Chem::TPSACalculator::TPSACalculator(const MolecularGraph& molgraph)
{
	calculate(molgraph);
}

double Chem::TPSACalculator::calculate(const MolecularGraph& molgraph)
{
	area = 0.0;

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_type = getType(atom);

		if (atom_type != AtomType::N && atom_type != AtomType::O)
			continue;

		std::size_t num_h_bonds = getImplicitHydrogenCount(atom);
		std::size_t num_heavy_bonds = 0;
		std::size_t num_arom_bonds = 0;
		std::size_t num_sgl_bonds = 0;
		std::size_t num_dbl_bonds = 0;
		std::size_t num_tpl_bonds = 0;
		
		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
			const Bond& bond = *b_it;
			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsBond(bond) || !molgraph.containsAtom(nbr_atom)) {
				num_h_bonds += getOrder(bond);
				continue;
			}

			if (getType(nbr_atom) == AtomType::H)
				num_h_bonds++;

			else {
				num_heavy_bonds++;

				if (getAromaticityFlag(bond))
					num_arom_bonds++;

				else {
					switch (getOrder(bond)) {

						case 1:
							num_sgl_bonds++;
							break;

						case 2:
							num_dbl_bonds++;
							break;

						case 3:
							num_tpl_bonds++;
							break;

						default:
							break;
					}
				}
			}
		}

		area += getTPSAIncrement(atom_type, num_h_bonds, num_heavy_bonds, num_arom_bonds, 
								 num_sgl_bonds, num_dbl_bonds, num_tpl_bonds,
								 getFormalCharge(atom), 
								 isInRingOfSize(atom, molgraph, 3));
	}

	return area;
}

double Chem::TPSACalculator::getResult() const
{
	return area;
}
