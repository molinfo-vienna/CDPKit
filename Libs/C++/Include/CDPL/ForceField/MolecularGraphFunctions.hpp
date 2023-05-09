/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP

#include "CDPL/ForceField/APIPrefix.hpp" 
#include "CDPL/Chem/FragmentList.hpp" 


namespace CDPL 
{

	namespace ForceField 
	{

		CDPL_FORCEFIELD_API const Chem::FragmentList::SharedPointer& getMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

		CDPL_FORCEFIELD_API void setMMFF94AromaticRings(Chem::MolecularGraph& molgraph, const Chem::FragmentList::SharedPointer& rings);

		CDPL_FORCEFIELD_API void clearMMFF94AromaticRings(Chem::MolecularGraph& molgraph);

		CDPL_FORCEFIELD_API bool hasMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

		CDPL_FORCEFIELD_API Chem::FragmentList::SharedPointer perceiveMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

		CDPL_FORCEFIELD_API Chem::FragmentList::SharedPointer perceiveMMFF94AromaticRings(Chem::MolecularGraph& molgraph, bool overwrite);


		CDPL_FORCEFIELD_API void assignMMFF94AtomTypes(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);

		CDPL_FORCEFIELD_API void assignMMFF94BondTypeIndices(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);

		CDPL_FORCEFIELD_API void calcMMFF94AtomCharges(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);


		CDPL_FORCEFIELD_API void assignUFFAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);
	}
}

#endif // CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP
 
