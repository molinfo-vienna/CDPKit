/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomElectronegativityFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


namespace
{

    bool getLPElectronegativityParams(std::size_t atom_type, double& a, double& b, double& c)
    {
		switch (atom_type) {

			case 600:
				a = 2.94;
				b = 8.53;
				c = 5.60;
				return true;
		
			case 700:
			case 730:
			case 731:
				a = 7.32;
				b = 11.86;
				c = 4.54;
				return true;
		
			case 721:
				a = 7.11;
				b = 12.43;
				c = 5.32;
				return true;

			case 711:
				a = 6.22;
				b = 13.56;
				c = 7.34;
				return true;
		
			case 800:
			case 820:
				a = 6.85;
				b = 14.76;
				c = 7.91;
				return true;
		
			case 821:
				a = 6.49;
				b = 15.26;
				c = 8.77;

			case 811:
				a = 6.68;
				b = 15.66;
				c = 8.98;
				return true;
		
			case 900:
				a = 8.07;
				b = 15.41;
				c = 7.34;
				return true;

			case 1500:
				a = 2.81;
				b = 7.86;
				c = 5.05;
				return true;
		
			case 1600:
				a = 3.72;
				b = 10.32;
				c = 6.60;
				return true;
		
			case 1700:
				a = 4.52;
				b = 11.02;
				c = 6.50;
				return true;
		
			case 3500:
				a = 4.48;
				b = 9.68;
				c = 5.20;
				return true;
		
			case 5300:
				a = 3.86;
				b = 8.81;
				c = 4.95;
				return true;
		
			default:
				break;
		}

		return false;
    }

    bool isInPiSystem(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
    {
		using namespace Chem;

		const ElectronSystemList& pi_sys_list = *getPiElectronSystems(molgraph);

		for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
			const ElectronSystem& pi_sys = *ps_it;

			if (pi_sys.getNumAtoms() < 2)
				continue;
		
			if (!pi_sys.containsAtom(atom))
				continue;

			return true;
		}

		return false;
    }
    
    double calcLonePairElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double q)
    {
		using namespace Chem;

		std::size_t atom_type = getType(atom) * 100;
		std::size_t fb_atom_type = atom_type;
	
		if (atom_type == 700 || atom_type == 800) {
			std::size_t num_bonds = 0;
			bool has_pi_nbr = false;

			Atom::ConstBondIterator b_it = atom.getBondsBegin();
	    
			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
				const Atom& nbr_atom = *a_it;
				
				if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
					continue;

				num_bonds++;

				if (!has_pi_nbr)
					has_pi_nbr = isInPiSystem(atom, molgraph);
			}
	    
			atom_type += num_bonds * 10 + has_pi_nbr;
		}
	
		double a, b, c;

		if (!getLPElectronegativityParams(atom_type, a, b, c))
			if (!getLPElectronegativityParams(fb_atom_type, a, b, c))
				getLPElectronegativityParams(600, a, b, c);
	    
		return (a * q * q + b * q + c);
    }

    double calcPiElectronegativity(const Chem::Atom& atom, double q)
    {
		using namespace Chem;

		// Carbon params as default
		double a = 2.94;
		double b = 8.53;
		double c = 5.60;
	
		switch (getType(atom)) {

			case AtomType::Be:
				a = 4.34;
				b = 4.79;
				c = 0.67;
				break;

			case AtomType::B:
				a = 2.72;
				b = 6.26;
				c = 4.25;
				break;

			case AtomType::N:
				a = 2.67;
				b = 9.73;
				c = 8.95;
				break;

			case AtomType::O:
				a = 2.87;
				b = 11.73;
				c = 10.09;
				break;

			case AtomType::Al:
				a = 1.96;
				b = 4.35;
				c = 3.68;
				break;

			case AtomType::P:
				a = 2.35;
				b = 7.71;
				c = 6.08;
				break;

			case AtomType::S:
				a = 1.70;
				b = 7.89;
				c = 7.39;

			default:
				break;
		}
	
		return (a * q * q + b * q + c);
    }
}


double MolProp::calcLonePairElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    const ElectronSystemList& pi_sys_list = *getPiElectronSystems(molgraph);

    for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
		const ElectronSystem& pi_sys = *ps_it;

		if (pi_sys.getNumAtoms() != 1)
			continue;
		
		if (!pi_sys.containsAtom(atom))
			continue;

		if (pi_sys.getElectronContrib(atom) != 2)
			continue;

		return ::calcLonePairElectronegativity(atom, molgraph, getPEOESigmaCharge(atom) + getMHMOPiCharge(atom));
    }

    return 0.0;
}

double MolProp::calcPiElectronegativity(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;

    const ElectronSystemList& pi_sys_list = *getPiElectronSystems(molgraph);

    for (ElectronSystemList::ConstElementIterator ps_it = pi_sys_list.getElementsBegin(), ps_end = pi_sys_list.getElementsEnd(); ps_it != ps_end; ++ps_it) {
		const ElectronSystem& pi_sys = *ps_it;

		if (pi_sys.getNumAtoms() < 2)
			continue;
		
		if (!pi_sys.containsAtom(atom))
			continue;

		switch (pi_sys.getElectronContrib(atom)) {

			case 0:
				return ::calcPiElectronegativity(atom, 1.0 + getMHMOPiCharge(atom));

			case 1:
				return ::calcPiElectronegativity(atom, getMHMOPiCharge(atom));

			case 2:
				if (getAromaticityFlag(atom))
					return ::calcPiElectronegativity(atom, getMHMOPiCharge(atom) - 1.0);

				return ::calcLonePairElectronegativity(atom, molgraph, getPEOESigmaCharge(atom) * 0.5 + getMHMOPiCharge(atom));

			default:
				break;
		}
    }
    
    return calcLonePairElectronegativity(atom, molgraph);
}
