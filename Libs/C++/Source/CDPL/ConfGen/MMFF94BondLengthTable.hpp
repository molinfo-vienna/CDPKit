/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondLengthTable.hpp
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
 * \brief Definition of the class CDPL::ConfGen::MMFF94BondLengthTable.
 */

#ifndef CDPL_CONFGEN_MMFF94BONDLENGTHTABLE_HPP
#define CDPL_CONFGEN_MMFF94BONDLENGTHTABLE_HPP

#include <cstddef>

#include "CDPL/ForceField/MMFF94AtomTyper.hpp"
#include "CDPL/ForceField/MMFF94BondTyper.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94AromaticSSSRSubset.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {
	
		class MMFF94BondLengthTable 
		{

		public:
			MMFF94BondLengthTable();

			void setup(const Chem::MolecularGraph& molgraph, bool strict_param);

			double get(std::size_t atom1_idx, std::size_t atom2_idx) const;

		private:
			unsigned int getBondTypeIndex(const Chem::Bond& bond) const;

			unsigned int getNumericAtomType(const Chem::Atom& atom) const;

			const Chem::FragmentList::SharedPointer& getAromaticRings(const Chem::MolecularGraph& molgraph) const;

			const Chem::MolecularGraph*                              molGraph;
			ForceField::MMFF94AtomTyper                              atomTyper;
			ForceField::MMFF94BondTyper                              bondTyper;
			ForceField::MMFF94BondStretchingInteractionParameterizer bondStretchingParameterizer;
			ForceField::MMFF94AromaticSSSRSubset::SharedPointer      aromRings;
			Chem::FragmentList::SharedPointer                        usedAromRings;
			ForceField::MMFF94BondStretchingInteractionData          bondStretchingParams;
			Util::UIArray                                            numAtomTypes;   
			Util::SArray                                             symAtomTypes;   
			Util::UIArray                                            bondTypeIndices;   
		};
    }
}

#endif // CDPL_CONFGEN_MMFF94BONDLENGTHTABLE_HPP
