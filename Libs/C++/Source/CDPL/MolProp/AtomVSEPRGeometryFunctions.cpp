/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomVSEPRGeometryFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/CoordinationGeometry.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"


using namespace CDPL; 


std::size_t MolProp::calcStericNumber(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    std::size_t num_free_val_el = 0;

    if (isMainGroupElement(atom)) { // Kepert model
		num_free_val_el = calcFreeValenceElectronCount(atom, molgraph);

		if (num_free_val_el > 0 && isAmideNitrogen(atom, molgraph, true, true))
			num_free_val_el--;
    }
	
    return (getBondCount(atom, molgraph) + num_free_val_el / 2);
}

unsigned int MolProp::getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t steric_num)
{
	std::size_t bnd_cnt = getBondCount(atom, molgraph);

	if (bnd_cnt > steric_num)
		return CoordinationGeometry::UNDEF;

	if (bnd_cnt <= 1)
		return CoordinationGeometry::NONE;
	
    switch (steric_num) {

		case 2:
			if (bnd_cnt == 2)
				return CoordinationGeometry::LINEAR;

			return CoordinationGeometry::NONE;

		case 3:
			switch (bnd_cnt) {

				case 3:
					return CoordinationGeometry::TRIGONAL_PLANAR;

				case 2:
					return CoordinationGeometry::BENT;
			}

			return CoordinationGeometry::NONE;
				
		case 4:
			switch (bnd_cnt) {

				case 4:
					return CoordinationGeometry::TETRAHEDRAL;

				case 3:
					return CoordinationGeometry::TRIGONAL_PYRAMIDAL;

				case 2:
					return CoordinationGeometry::BENT;
			}

			return CoordinationGeometry::NONE;
			
		case 5:
			switch (bnd_cnt) {

				case 5:
					return CoordinationGeometry::TRIGONAL_BIPYRAMIDAL;

				case 4:
					return CoordinationGeometry::SEESAW;

				case 3:
					return CoordinationGeometry::T_SHAPED;

				case 2:
					return CoordinationGeometry::LINEAR;
			}

			return CoordinationGeometry::NONE;

		case 6:
			switch (bnd_cnt) {

				case 6:
					return CoordinationGeometry::OCTAHEDRAL;
					
				case 5:
					return CoordinationGeometry::SQUARE_PYRAMIDAL;

				case 4:
					return CoordinationGeometry::SQUARE_PLANAR;

				case 3:
					return CoordinationGeometry::T_SHAPED;
			}

			return CoordinationGeometry::UNDEF;
			
		case 7:
			switch (bnd_cnt) {

				case 7:
					return CoordinationGeometry::PENTAGONAL_BIPYRAMIDAL;
					
				case 6:
					return CoordinationGeometry::PENTAGONAL_PYRAMIDAL;
					
				case 5:
					return CoordinationGeometry::PENTAGONAL_PLANAR;
			}

			return CoordinationGeometry::UNDEF;
			
		case 8:
			if (bnd_cnt == 8)
				return CoordinationGeometry::SQUARE_ANTIPRISMATIC;
    }

    return CoordinationGeometry::UNDEF;
}

unsigned int MolProp::getVSEPRCoordinationGeometry(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    return getVSEPRCoordinationGeometry(atom, molgraph, calcStericNumber(atom, molgraph));
}
