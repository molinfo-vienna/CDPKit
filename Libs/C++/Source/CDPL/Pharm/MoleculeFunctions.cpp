/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeFunctions.cpp 
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

#include <algorithm>

#include "CDPL/Pharm/MoleculeFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"


using namespace CDPL; 


void Pharm::prepareForPharmacophoreGeneration(Chem::Molecule& mol, bool calc_hyd, bool from_logp)
{
    perceiveSSSR(mol, false);
    setRingFlags(mol, false);
    calcImplicitHydrogenCounts(mol, false);
    perceiveHybridizationStates(mol, false);
    setAromaticityFlags(mol, false);

	if (makeHydrogenComplete(mol)) {
		try {
			calcHydrogen3DCoordinates(mol);
		} catch (const Base::ItemNotFound& e) {
		} catch (...) {
			throw;
		}
		
		try {
			Biomol::setHydrogenResidueSequenceInfo(mol, false);
		} catch (const Base::ItemNotFound& e) {
		} catch (...) {
			throw;
		}
	}

	if (calc_hyd)
		MolProp::calcAtomHydrophobicities(mol, false, from_logp);
}
