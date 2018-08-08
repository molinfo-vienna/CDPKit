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

		template <typename ValueType, typename CoordsVec>
		ValueType calcSquaredDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos);

		template <typename ValueType, typename CoordsVec>
		ValueType calcDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos);

		template <typename ValueType, typename CoordsVec>
		ValueType calcBondLengthsAndAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
											 ValueType& bond_length1, ValueType& bond_length2);

		template <typename ValueType, typename CoordsVec>
		ValueType calcBondLengthsAndAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
										  ValueType& bond_length1, ValueType& bond_length2);

		template <typename ValueType, typename CoordsVec>
		ValueType calcBondAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos);

		template <typename ValueType, typename CoordsVec>
		ValueType calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos);
	
		template <typename ValueType, typename CoordsVec>
		ValueType calcOutOfPlaneAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
									  const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos);

		template <typename ValueType, typename CoordsVec>
		ValueType calcDihedralAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
									   const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos);

		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcDistanceGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
									   GradVec& atom1_grad, GradVec& atom2_grad);

		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcBondAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
										   GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad);
	
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcDihedralAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
											   const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos,
											   GradVec& term_atom1_grad, GradVec& ctr_atom1_grad, 
											   GradVec& ctr_atom2_grad, GradVec& term_atom2_grad);

		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcOutOfPlaneAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
												 const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos,
												 GradVec& term_atom1_grad, GradVec& ctr_atom_grad, 
												 GradVec& term_atom2_grad, GradVec& oop_atom_grad);
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

			template <typename VecType1, typename VecType2>
			void addVectors(const VecType1& vec1, const VecType1& vec2, VecType2& res)
			{
				res[0] = vec2[0] + vec1[0];
				res[1] = vec2[1] + vec1[1];
				res[2] = vec2[2] + vec1[2];
			}

			template <typename VecType1, typename VecType2>
			void subVectors(const VecType1& vec1, const VecType1& vec2, VecType2& res)
			{
				res[0] = vec2[0] - vec1[0];
				res[1] = vec2[1] - vec1[1];
				res[2] = vec2[2] - vec1[2];
			}

			template <typename ValueType, typename VecType>
			ValueType calcDotProduct(const VecType& vec1, const VecType& vec2)
			{
				return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]); 
			}

			template <typename VecType, typename ResVecType>
			void calcCrossProduct(const VecType& vec1, const VecType& vec2, ResVecType& cross_prod)
			{
				cross_prod[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1]; 
				cross_prod[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2]; 
				cross_prod[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0]; 
			}
	
			template <typename VecType1, typename VecType2>
			void copyVector(const VecType1& vec1, VecType2& vec2)
			{
				vec2[0] = vec1[0];
				vec2[1] = vec1[1];
				vec2[2] = vec1[2];
			}

			template <typename VecType>
			void negateVector(VecType& vec)
			{
				vec[0] = -vec[0];
				vec[1] = -vec[1];
				vec[2] = -vec[2];
			}

			template <typename VecType1, typename VecType2>
			void negateCopyVector(const VecType1& vec1, VecType2& vec2)
			{
				vec2[0] = -vec1[0];
				vec2[1] = -vec1[1];
				vec2[2] = -vec1[2];
			}

			template <typename VecType, typename T>
			void scaleVector(VecType& vec, const T& factor)
			{
				vec[0] *= factor;
				vec[1] *= factor;
				vec[2] *= factor;
			}
	
			template <typename VecType, typename T>
			void invScaleVector(VecType& vec, const T& factor)
			{
				vec[0] /= factor;
				vec[1] /= factor;
				vec[2] /= factor;
			}

			template <typename VecType1, typename VecType2, typename T>
			void scaleAddVector(const VecType1& vec1, const T& factor, VecType2& vec2)
			{
				vec2[0] += vec1[0] * factor;
				vec2[1] += vec1[1] * factor;
				vec2[2] += vec1[2] * factor;
			}

			template <typename VecType1, typename VecType2, typename T>
			void scaleCopyVector(const VecType1& vec1, const T& factor, VecType2& vec2)
			{
				vec2[0] = vec1[0] * factor;
				vec2[1] = vec1[1] * factor;
				vec2[2] = vec1[2] * factor;
			}

			template <typename VecType1, typename VecType2, typename T>
			void invScaleCopyVector(const VecType1& vec1, const T& factor, VecType2& vec2)
			{
				vec2[0] = vec1[0] / factor;
				vec2[1] = vec1[1] / factor;
				vec2[2] = vec1[2] / factor;
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


template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcSquaredDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos)
{
    ValueType pos_diff[3];

	Detail::subVectors(atom1_pos, atom2_pos, pos_diff);

    return Detail::calcDotProduct<ValueType>(pos_diff, pos_diff);
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos)
{
    return std::sqrt(calcSquaredDistance<ValueType>(atom1_pos, atom2_pos));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondLengthsAndAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
													   ValueType& bond_length1, ValueType& bond_length2)
{
	ValueType bond_vec1[3];
    ValueType bond_vec2[3];

	Detail::subVectors(ctr_atom_pos, term_atom1_pos, bond_vec1);
	Detail::subVectors(ctr_atom_pos, term_atom2_pos, bond_vec2);

    bond_length1 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec1));
    bond_length2 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec2, bond_vec2));
    
	return Detail::clampCosine(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec2) / (bond_length1 * bond_length2));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondLengthsAndAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
													ValueType& bond_length1, ValueType& bond_length2)
{
	return std::acos(calcBondLengthsAndAngleCos(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bond_length1, bond_length2));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos)
{
    ValueType bl1, bl2;
    
	return calcBondLengthsAndAngleCos(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bl1, bl2);
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos)
{
    return std::acos(calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcOutOfPlaneAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
												const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos)
{
	ValueType term_bond1_vec[3];
    ValueType term_bond2_vec[3];
    ValueType oop_bond_vec[3];
    ValueType plane_normal[3];

	Detail::subVectors(ctr_atom_pos, term_atom1_pos, term_bond1_vec);
	Detail::subVectors(ctr_atom_pos, term_atom2_pos, term_bond2_vec);
	Detail::subVectors(ctr_atom_pos, oop_atom_pos, oop_bond_vec);
	Detail::calcCrossProduct(term_bond1_vec, term_bond2_vec, plane_normal);

	ValueType pn_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal, plane_normal));
	ValueType oop_bnd_len = std::sqrt(Detail::calcDotProduct<ValueType>(oop_bond_vec, oop_bond_vec));
	ValueType ang_cos = Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal, oop_bond_vec) / (pn_len * oop_bnd_len));

	return (ValueType(M_PI * 0.5) - std::acos(ang_cos));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcDihedralAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
												 const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos)
{
	ValueType term_bond1_vec[3];
    ValueType ctr_bond_vec[3];
    ValueType term_bond2_vec[3];
    ValueType plane_normal1[3];
    ValueType plane_normal2[3];

	Detail::subVectors(ctr_atom1_pos, term_atom1_pos, term_bond1_vec);
	Detail::subVectors(ctr_atom1_pos, ctr_atom2_pos, ctr_bond_vec);
	Detail::subVectors(term_atom2_pos, ctr_atom2_pos, term_bond2_vec);

	Detail::calcCrossProduct(term_bond1_vec, ctr_bond_vec, plane_normal1);
	Detail::calcCrossProduct(ctr_bond_vec, term_bond2_vec, plane_normal2);

	ValueType pn1_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal1));
	ValueType pn2_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal2, plane_normal2));

	return Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal2) / (pn1_len * pn2_len));
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcDistanceGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
												  GradVec& atom1_grad, GradVec& atom2_grad)
{
	Detail::subVectors(atom2_pos, atom1_pos, atom1_grad);

	ValueType dist = std::sqrt(Detail::calcDotProduct<ValueType>(atom1_grad, atom1_grad));

	Detail::invScaleVector(atom1_grad, dist);
	Detail::negateCopyVector(atom1_grad, atom2_grad);

    return dist;
}
	
template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcBondAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
													 GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad)
{
	ValueType bond_vec1[3];
    ValueType bond_vec2[3];

	Detail::subVectors(ctr_atom_pos, term_atom1_pos, bond_vec1);
	Detail::subVectors(ctr_atom_pos, term_atom2_pos, bond_vec2);

    ValueType bond_length1 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec1));
    ValueType bond_length2 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec2, bond_vec2));

	ValueType dot_prod = Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec2);
	ValueType bl_prod = bond_length1 * bond_length2;

	Detail::invScaleCopyVector(bond_vec2, bl_prod, term_atom1_grad);
	Detail::scaleCopyVector(bond_vec1, dot_prod / (bond_length1 * bond_length1 * bl_prod), ctr_atom_grad);
	Detail::subVectors(ctr_atom_grad, term_atom1_grad, term_atom1_grad);

	Detail::invScaleCopyVector(bond_vec1, bl_prod, term_atom2_grad);
	Detail::scaleCopyVector(bond_vec2, dot_prod / (bond_length2 * bond_length2 * bl_prod), ctr_atom_grad);
	Detail::subVectors(ctr_atom_grad, term_atom2_grad, term_atom2_grad);

	Detail::negateCopyVector(term_atom1_grad, ctr_atom_grad);
	Detail::subVectors(term_atom2_grad, ctr_atom_grad, ctr_atom_grad);

	return Detail::clampCosine(dot_prod / bl_prod);
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcDihedralAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
														 const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos,
														 GradVec& term_atom1_grad, GradVec& ctr_atom1_grad, 
														 GradVec& ctr_atom2_grad, GradVec& term_atom2_grad)
{
	ValueType term_bond1_vec[3];
    ValueType ctr_bond_vec[3];
    ValueType term_bond2_vec[3];
	ValueType term1_ctr2_vec[3];
    ValueType plane_normal1[3];
    ValueType plane_normal2[3];

	Detail::subVectors(ctr_atom1_pos, term_atom1_pos, term_bond1_vec);
	Detail::subVectors(ctr_atom1_pos, ctr_atom2_pos, ctr_bond_vec);
	Detail::subVectors(term_atom2_pos, ctr_atom2_pos, term_bond2_vec);
	Detail::subVectors(ctr_atom2_pos, term_atom1_pos, term1_ctr2_vec);

	Detail::calcCrossProduct(term_bond1_vec, ctr_bond_vec, plane_normal1);
	Detail::calcCrossProduct(ctr_bond_vec, term_bond2_vec, plane_normal2);

	ValueType pn1_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal1));
	ValueType pn2_len = std::sqrt(Detail::calcDotProduct<ValueType>(plane_normal2, plane_normal2));

	Detail::invScaleVector(plane_normal1, pn1_len);
	Detail::invScaleVector(plane_normal2, pn2_len);

	ValueType ang_cos = Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal1, plane_normal2));

	ValueType a[3];
	ValueType b[3];

	Detail::scaleCopyVector(plane_normal1, -ang_cos, a);
	Detail::addVectors(a, plane_normal2, a);
	Detail::invScaleVector(a, pn1_len);

	Detail::scaleCopyVector(plane_normal2, -ang_cos, b);
	Detail::addVectors(b, plane_normal1, b);
	Detail::invScaleVector(b, pn2_len);

	Detail::calcCrossProduct(ctr_bond_vec, a, term_atom1_grad);
	Detail::calcCrossProduct(ctr_bond_vec, b, term_atom2_grad);

	Detail::calcCrossProduct(term1_ctr2_vec, a, ctr_atom1_grad);
	Detail::calcCrossProduct(term_bond2_vec, b, ctr_atom2_grad);

	Detail::subVectors(ctr_atom2_grad, ctr_atom1_grad, ctr_atom1_grad);

	Detail::addVectors(term_atom1_grad, ctr_atom1_grad, ctr_atom2_grad);
	Detail::addVectors(ctr_atom2_grad, term_atom2_grad, ctr_atom2_grad);
    Detail::negateVector(ctr_atom2_grad);

    return ang_cos;
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcOutOfPlaneAngleCosGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
														   const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos,
														   GradVec& term_atom1_grad, GradVec& ctr_atom_grad, 
														   GradVec& term_atom2_grad, GradVec& oop_atom_grad)
{
	ValueType term_bond1_vec[3];
    ValueType term_bond2_vec[3];
    ValueType oop_bond_vec[3];
	ValueType term1_oop_vec[3];
	ValueType term2_oop_vec[3];
	ValueType ijk_pn[3];

	Detail::subVectors(ctr_atom_pos, term_atom1_pos, term_bond1_vec);
	Detail::subVectors(ctr_atom_pos, term_atom2_pos, term_bond2_vec);
	Detail::subVectors(ctr_atom_pos, oop_atom_pos, oop_bond_vec);
	Detail::subVectors(term_atom2_pos, oop_atom_pos, term2_oop_vec);
	Detail::subVectors(term_atom1_pos, oop_atom_pos, term1_oop_vec);

	Detail::calcCrossProduct(term_bond1_vec, term_bond2_vec, ijk_pn);

	ValueType ijk_pn_len_2 = Detail::calcDotProduct<ValueType>(ijk_pn, ijk_pn);
	ValueType ijk_pn_len = std::sqrt(ijk_pn_len_2);
	ValueType oop_bnd_len = std::sqrt(Detail::calcDotProduct<ValueType>(oop_bond_vec, oop_bond_vec));
	ValueType oop_ijk_pn_len_prod = ijk_pn_len * oop_bnd_len;
	ValueType oop_ijk_pn_dot_prod = Detail::calcDotProduct<ValueType>(ijk_pn, oop_bond_vec);
	ValueType ang_cos = Detail::clampCosine(oop_ijk_pn_dot_prod / oop_ijk_pn_len_prod);

	ValueType kjl_pn[3];
	ValueType lji_pn[3];

	Detail::calcCrossProduct(term_bond2_vec, oop_bond_vec, kjl_pn);
	Detail::calcCrossProduct(oop_bond_vec, term_bond1_vec, lji_pn);

	ctr_atom_grad[0] = ijk_pn[1] * -term_bond2_vec[2] + ijk_pn[2] * term_bond2_vec[1];
	ctr_atom_grad[1] = ijk_pn[0] * term_bond2_vec[2] + ijk_pn[2] * -term_bond2_vec[0];
	ctr_atom_grad[2] = ijk_pn[0] * -term_bond2_vec[1] + ijk_pn[1] * term_bond2_vec[0];

	Detail::scaleVector(ctr_atom_grad, ang_cos / ijk_pn_len_2);

	Detail::invScaleCopyVector(kjl_pn, oop_ijk_pn_len_prod, term_atom1_grad);
	Detail::subVectors(ctr_atom_grad, term_atom1_grad, term_atom1_grad);

	ctr_atom_grad[0] = ijk_pn[1] * term_bond1_vec[2] + ijk_pn[2] * -term_bond1_vec[1];
	ctr_atom_grad[1] = ijk_pn[0] * -term_bond1_vec[2] + ijk_pn[2] * term_bond1_vec[0];
	ctr_atom_grad[2] = ijk_pn[0] * term_bond1_vec[1] + ijk_pn[1] * -term_bond1_vec[0];

	Detail::scaleVector(ctr_atom_grad, ang_cos / ijk_pn_len_2);

	Detail::invScaleCopyVector(lji_pn, oop_ijk_pn_len_prod, term_atom2_grad);
	Detail::subVectors(ctr_atom_grad, term_atom2_grad, term_atom2_grad);

	Detail::calcCrossProduct(term2_oop_vec, term1_oop_vec, ctr_atom_grad);

	Detail::scaleCopyVector(oop_bond_vec, oop_ijk_pn_dot_prod / (oop_bnd_len * oop_bnd_len), oop_atom_grad);
	Detail::addVectors(oop_atom_grad, lji_pn, oop_atom_grad);
	Detail::addVectors(oop_atom_grad, kjl_pn, oop_atom_grad);
	Detail::addVectors(oop_atom_grad, ctr_atom_grad, oop_atom_grad);
	Detail::invScaleVector(oop_atom_grad, -oop_ijk_pn_len_prod);
	
	Detail::copyVector(term_atom1_grad, ctr_atom_grad);
	Detail::addVectors(term_atom2_grad, ctr_atom_grad, ctr_atom_grad);
	Detail::addVectors(oop_atom_grad, ctr_atom_grad, ctr_atom_grad);
	Detail::negateVector(ctr_atom_grad);

	return ang_cos;
}

// \endcond

#endif // CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP
