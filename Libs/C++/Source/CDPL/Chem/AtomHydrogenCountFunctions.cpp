/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomHydrogenCountFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomTypeFunctions.hpp"


using namespace CDPL; 


std::size_t Chem::getImplicitHydrogenCount(const Atom& atom)
{
	return atom.getProperty<std::size_t>(AtomProperty::IMPLICIT_HYDROGEN_COUNT);
}

void Chem::setImplicitHydrogenCount(Atom& atom, std::size_t count)
{
	atom.setProperty(AtomProperty::IMPLICIT_HYDROGEN_COUNT, count);
}

void Chem::clearImplicitHydrogenCount(Atom& atom)
{
    atom.removeProperty(AtomProperty::IMPLICIT_HYDROGEN_COUNT);
}

bool Chem::hasImplicitHydrogenCount(const Atom& atom)
{
    return atom.isPropertySet(AtomProperty::IMPLICIT_HYDROGEN_COUNT);
}

std::size_t Chem::calcImplicitHydrogenCount(const Atom& atom, const MolecularGraph& molgraph)
{
    unsigned int atom_type = getType(atom);

    if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_ATOMIC_NO)
		return std::size_t(0);

    long explicit_val = calcExplicitValence(atom, molgraph);
    long iupac_group = getIUPACGroup(atom_type);
    long num_val_elecs = iupac_group - 10;

    switch (iupac_group) {

		case 1: {
			if (atom_type != AtomType::H || explicit_val > 0)
				return std::size_t(0); 

			long charge = getFormalCharge(atom);

			if (charge != 0)
				return std::size_t(0); 

			std::size_t num_rad_elecs = getUnpairedElectronCount(atom);

			if (num_rad_elecs != 0)
				return std::size_t(0); 
		
			return std::size_t(1);
		}

		case 13:
		case 14: {
			long charge = getFormalCharge(atom);

			if (iupac_group == 14 && charge < 0)
				charge *= -1;

			long num_rad_elecs = getUnpairedElectronCount(atom);
			long impl_h_count = num_val_elecs - charge - num_rad_elecs - explicit_val;

			return std::size_t(impl_h_count < 0 ? 0 : impl_h_count);
		}

		case 15:
		case 16:
		case 17: {
			long charge = getFormalCharge(atom);
			long num_rad_elecs = getUnpairedElectronCount(atom);
			long max_num_shell_elecs = (atom_type <= AtomType::F ? 8 : 2 * num_val_elecs);

			for (long num_shell_elecs = 8; num_shell_elecs <= max_num_shell_elecs; num_shell_elecs += 2) {
				long impl_h_count = num_shell_elecs - (num_val_elecs - charge + explicit_val + num_rad_elecs);

				if (impl_h_count < 0)
					continue;

				return std::size_t(impl_h_count);
			}
		}

		default:
			break;
    }

    return std::size_t(0); 
}

std::size_t Chem::getOrdinaryHydrogenCount(const Atom& atom, const MolecularGraph& molgraph, unsigned int flags)
{
    std::size_t count = 0;

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it)
		if (molgraph.containsAtom(*a_it) && molgraph.containsBond(*b_it) && isOrdinaryHydrogen(*a_it, molgraph, flags))
			count++;

    return (count + getImplicitHydrogenCount(atom));
}
