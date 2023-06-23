/* 
 * AtomImplicitHydrogenCountFunction.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL; 


std::size_t Chem::calcImplicitHydrogenCount(const Atom& atom, const MolecularGraph& molgraph)
{
    unsigned int atom_type = getType(atom);

    if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::Ba)
        return std::size_t(0);

    long explicit_val = Internal::calcExplicitValence(atom, molgraph);
    long iupac_group = AtomDictionary::getIUPACGroup(atom_type);
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
