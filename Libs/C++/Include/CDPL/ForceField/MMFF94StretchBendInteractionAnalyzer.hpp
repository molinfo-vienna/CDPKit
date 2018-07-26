/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94StretchBendInteractionAnalyzer.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ForceField::MMFF94StretchBendInteractionAnalyzer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONANALYZER_HPP
#define CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONANALYZER_HPP

#include <utility>
#include <cstddef>

#include <boost/unordered_map.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionList.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctionWrappers.hpp"
#include "CDPL/ForceField/InteractionFilterFunctionWrappers.hpp"
#include "CDPL/ForceField/MMFF94StretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94DefaultStretchBendParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
	}

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_INTERACTION_ANALYSIS
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94StretchBendInteractionAnalyzer
		{

		  public:
			MMFF94StretchBendInteractionAnalyzer();

			MMFF94StretchBendInteractionAnalyzer(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionList& bs_iactions, 
												 const MMFF94AngleBendingInteractionList& ab_iactions, MMFF94StretchBendInteractionList& iactions);

			void setFilterFunction(const InteractionFilterFunction3& func); 

			void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func); 

			void setStretchBendParameterTable(const MMFF94StretchBendParameterTable::SharedPointer& table);

			void setDefaultStretchBendParameterTable(const MMFF94DefaultStretchBendParameterTable::SharedPointer& table);

			void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

			void analyze(const Chem::MolecularGraph& molgraph, const MMFF94BondStretchingInteractionList& bs_iactions, 
						 const MMFF94AngleBendingInteractionList& ab_iactions, MMFF94StretchBendInteractionList& iactions);

		  private:
			void initBondStretchingParamLookupTable(const MMFF94BondStretchingInteractionList& bs_iactions);

			void getBondStretchingParameters(std::size_t atom1_idx, std::size_t atom2_idx, unsigned int& bond_type_idx, double& ref_length) const;

			void getStretchBendParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom, 
										  const Chem::Atom& term_atom2, unsigned int bond_type_idx1, unsigned int bond_type_idx2,
										  unsigned int angle_type_idx, unsigned int& sb_type_idx, double& ijk_force_const, double& kji_force_const) const; 

 			/**
			 * \brief Returns the stretch bend type index SBT[IJK].
			 *
			 * SBT[IJK] is derived from the bond type indices BT[IJ] and BT[JK] and the angle type index AT[IJK] as follows:
			 * 
			 * SBT[IJK] AT[IJK] BT[IJ] BT[JK]
			 * -------------------------------------------------------------
			 * 0        0       0      0
			 * 1        1       1      0
			 * 2        1       0      1
			 * 3        2       1      1
			 * 4        4       0      0
			 * 5        3       0      0
			 * 6        5       1      0
			 * 7        5       0      1
			 * 8        6       1      1
			 * 9        7       1      0
			 * 10       7       0      1
			 * 11       8       1      1
			 * 
			 * If \a symmetric is \c true, then the lower SBT[IJK] value for a given AT[IJK] is returned when there are two possibilities.
			 *
			 * \param symmetric Tells whether the terminal atom types are identical.
			 * \param bond_type_idx1 The bond type index of the bond IJ.
			 * \param bond_type_idx2 The bond type index of the bond JK.
			 * \param angle_type_idx The angle type index.
			 * \return The stretch bend type index.
			 */
			unsigned int getStretchBendTypeIndex(bool symmetric, unsigned int bond_type_idx1, unsigned int bond_type_idx2, unsigned int angle_type_idx) const;

			unsigned int getPTERow(const Chem::MolecularGraph& molgraph, const Chem::Atom& atom, unsigned int atom_type) const;

			typedef boost::unordered_map<std::pair<std::size_t, std::size_t>, const MMFF94BondStretchingInteraction*> BondStretchingParamLookupTable;

			InteractionFilterFunction3                            filterFunc;
			MMFF94NumericAtomTypeFunction                         atomTypeFunc;	
			MMFF94StretchBendParameterTable::SharedPointer        paramTable;
			MMFF94DefaultStretchBendParameterTable::SharedPointer defParamTable;
			MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
			BondStretchingParamLookupTable                        bsParamTable;
		};			
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94STRETCHBENDINTERACTIONANALYZER_HPP
