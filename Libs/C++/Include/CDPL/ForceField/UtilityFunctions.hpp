/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.hpp 
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
 * \brief Utility functions used in the calculation of force field energies and gradients.
 */

#ifndef CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP
#define CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP

#include <cmath>


namespace CDPL 
{

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_UTILITY_FUNCTIONS
		 * @{
		 */

		template <typename VecType, typename ResVecType>
		void calcDifference(const VecType& atom1_pos, const VecType& atom2_pos, ResVecType& pos_diff);

		template <typename ValueType, typename VecType>
		ValueType calcSquaredDistance(const VecType& atom1_pos, const VecType& atom2_pos);

		template <typename ValueType, typename VecType>
		ValueType calcDistance(const VecType& atom1_pos, const VecType& atom2_pos);

		template <typename ValueType, typename VecType>
		ValueType calcBondLengthsAndAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, 
											 ValueType& bond_length1, ValueType& bond_length2);

		template <typename ValueType, typename VecType>
		ValueType calcBondLengthsAndAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, 
										  ValueType& bond_length1, ValueType& bond_length2);

		template <typename ValueType, typename VecType>
		ValueType calcBondAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos);

		template <typename ValueType, typename VecType>
		ValueType calcBondAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos);
	
		template <typename ValueType, typename VecType>
		ValueType calcOutOfPlaneAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, const VecType& oop_atom_pos);

		template <typename ValueType, typename VecType>
		ValueType calcDihedralAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom1_pos, const VecType& ctr_atom2_pos, const VecType& term_atom2_pos);

		/**
		 * @}
		 */
    }
}


// Implementation
// \cond UNHIDE_DETAILS

namespace CDPL
{

	namespace ForceField
	{

		namespace Detail
		{

			template <typename ValueType, typename VecType>
			ValueType calcDotProduct(const VecType& vec1, const VecType& vec2)
			{
				return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]); 
			}

			template <typename VecType, typename ResVecType>
			void calcCrossProduct(const VecType& vec1, const VecType& vec2,  ResVecType& cross_prod)
			{
				cross_prod[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1]; 
				cross_prod[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2]; 
				cross_prod[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0]; 
			}

			template <typename ValueType>
			ValueType clampCosine(const ValueType& v)
			{
				if (v > ValueType(1))
					return ValueType(1);

				if (v < ValueType(-1))
					return ValueType(-1);

				return v;
			}
		}
	}
}


template <typename VecType, typename ResVecType>
void CDPL::ForceField::calcDifference(const VecType& atom1_pos, const VecType& atom2_pos,  ResVecType& pos_diff)
{
	pos_diff[0] = atom2_pos[0] - atom1_pos[0];
	pos_diff[1] = atom2_pos[1] - atom1_pos[1];    
	pos_diff[2] = atom2_pos[2] - atom1_pos[2];
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcSquaredDistance(const VecType& atom1_pos, const VecType& atom2_pos)
{
    ValueType pos_diff[3];

	calcDifference(atom1_pos, atom2_pos, pos_diff);

    return Detail::calcDotProduct<ValueType>(pos_diff, pos_diff);
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcDistance(const VecType& atom1_pos, const VecType& atom2_pos)
{
    return std::sqrt(calcSquaredDistance<ValueType>(atom1_pos, atom2_pos));
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcBondLengthsAndAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, 
													   ValueType& bond_length1, ValueType& bond_length2)
{
	ValueType bond_vec1[3];
    ValueType bond_vec2[3];

	calcDifference(ctr_atom_pos, term_atom1_pos, bond_vec1);
	calcDifference(ctr_atom_pos, term_atom2_pos, bond_vec2);

    bond_length1 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec1));
    bond_length2 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec2, bond_vec2));
    
	return Detail::clampCosine(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec2) / (bond_length1 * bond_length2));
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcBondLengthsAndAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, 
													   ValueType& bond_length1, ValueType& bond_length2)
{
	return std::acos(calcBondLengthsAndAngleCos(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bond_length1, bond_length2));
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcBondAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos)
{
    ValueType bl1, bl2;
    
	return calcBondLengthsAndAngleCos(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bl1, bl2);
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcBondAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos)
{
    return std::acos(calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos));
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcOutOfPlaneAngle(const VecType& term_atom1_pos, const VecType& ctr_atom_pos, const VecType& term_atom2_pos, const VecType& oop_atom_pos)
{
	ValueType term_bond1_vec[3];
    ValueType term_bond2_vec[3];
    ValueType oop_bond_vec[3];
    ValueType plane_normal[3];

	calcDifference(ctr_atom_pos, term_atom1_pos, term_bond1_vec);
	calcDifference(ctr_atom_pos, term_atom2_pos, term_bond2_vec);
	calcDifference(ctr_atom_pos, oop_atom_pos, oop_bond_vec);
	Detail::calcCrossProduct(term_bond1_vec, term_bond2_vec, plane_normal);

	ValueType pn_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal, plane_normal));
	ValueType oop_bnd_len = std::sqrt(Detail::calcDotProduct<ValueType>(oop_bond_vec, oop_bond_vec));
	ValueType ang_cos = Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal, oop_bond_vec) / (pn_len * oop_bnd_len));

	return (ValueType(M_PI * 0.5) - std::acos(ang_cos));
}

template <typename ValueType, typename VecType>
ValueType CDPL::ForceField::calcDihedralAngleCos(const VecType& term_atom1_pos, const VecType& ctr_atom1_pos, const VecType& ctr_atom2_pos, const VecType& term_atom2_pos)
{
	ValueType term_bond1_vec[3];
    ValueType ctr_bond_vec[3];
    ValueType term_bond2_vec[3];
    ValueType plane_normal1[3];
    ValueType plane_normal2[3];

	calcDifference(ctr_atom1_pos, term_atom1_pos, term_bond1_vec);
	calcDifference(ctr_atom1_pos, ctr_atom2_pos, ctr_bond_vec);
	calcDifference(term_atom2_pos, ctr_atom2_pos, term_bond2_vec);

	Detail::calcCrossProduct(term_bond1_vec, ctr_bond_vec, plane_normal1);
	Detail::calcCrossProduct(ctr_bond_vec, term_bond2_vec, plane_normal2);

	ValueType pn1_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal1));
	ValueType pn2_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal2, plane_normal2));

	return Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal2) / (pn1_len * pn2_len));
}

// \endcond

#endif // CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP
