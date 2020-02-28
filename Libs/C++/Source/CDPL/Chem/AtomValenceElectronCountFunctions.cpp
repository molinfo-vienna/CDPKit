/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomValenceElectronCountFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


std::size_t Chem::calcFreeValenceElectronCount(const Atom& atom, const MolecularGraph& molgraph)
{
	long free_el_count = calcValenceElectronCount(atom) - calcValence(atom, molgraph);

	return std::size_t(free_el_count < 0 ? 0 : free_el_count); 
}

std::size_t Chem::calcValenceElectronCount(const Atom& atom)
{
	long el_count = getElementValenceElectronCount(atom) - getFormalCharge(atom);

	return std::size_t(el_count < 0 ? 0 : el_count); 
}
