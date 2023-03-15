/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94GradientFunctions.hpp 
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

/**
 * \file
 * \brief Functions for the calculation of MMFF94 interaction energies.
 */

#ifndef CDPL_FORCEFIELD_MMFF94GRADIENTFUNCTIONS_HPP
#define CDPL_FORCEFIELD_MMFF94GRADIENTFUNCTIONS_HPP

#include <algorithm>

#include "CDPL/ForceField/MMFF94BondStretchingInteraction.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteraction.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteraction.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteraction.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteraction.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteraction.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteraction.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94BondStretchingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94BondStretchingGradient(const MMFF94BondStretchingInteraction& iaction, const CoordsArray& coords, GradVector& grad);

		/**
		 * \brief Calculates the bond stretching interaction energy gradient \f$ \nabla EB_{ij} \f$ for the bond \e i-j.
		 * 
		 * Energy function:<br>
		 *
		 * \f$ EB_{ij} = 143.9325 \: \frac{kb_{IJ}}{2} \: \Delta r_{ij}^2 \times (1 + cs \: \Delta r_{ij} + \frac{7}{12} \: cs^2 \: \Delta r_{ij}^2) \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EB_{ij}}{\partial \vec{p_x}} = \frac{\partial EB_{ij}}{\partial \Delta r_{ij}} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial EB_{ij}}{\partial \Delta r_{ij}} = (167.92125 \: \Delta r_{ij}^3 \: cs^2  + 215.89875 \: \Delta r_{ij}^2 \: cs + 143.9325 \: \Delta r_{ij}) \: kb_{IJ} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
		 *
		 * where<br>
		 * \f$ kb_{IJ} \f$ = the bond stretching force constant in \f$ \frac{md}{Ang} \f$ for bonded 
		 *                   atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and 
		 *                         \e j of types \e I and \e J.<br>
		 * \f$ cs \f$ = \f$ -2 \: Ang^{-1} \f$, the "cubic stretch" constant.<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i and \e j.<br>
		 *
		 * Note: throughout this description, the indices \e i, \e j, \e k, ... represent atoms;
		 * \e I, \e J, \e K, ... denote the corresponding numerical MMFF atom types (or, 
		 * occasionally, the atomic species).
		 * 
		 * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
		 * \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
		 * \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
		 * \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94BondStretchingGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, 
												   GradVec& atom1_grad, GradVec& atom2_grad, 
												   const ValueType& force_const, const ValueType& ref_length);


		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94AngleBendingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94AngleBendingGradient(const MMFF94AngleBendingInteraction& iaction, const CoordsArray& coords, GradVector& grad);

		/**
		 * \brief Calculates the angle bending interaction energy gradient \f$ \nabla EA_{ijk} \f$ for two bonds \e i-j and \e j-k. 
		 *
		 * Energy function employed for the non-linear case:<br>
		 *
		 * \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EA_{ijk}}{\partial \vec{p_x}} = \frac{\partial EA_{ijk}}{\partial \vartheta_{ijk}} \: \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} \: 
		 *                                                    \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial EA_{ijk}}{\partial \vartheta_{ijk}} = -ka_{IJK} \: (86.58992538 \: \vartheta_{ijk}^2 - 3.022558594 \: \vartheta_{ijk} \: \vartheta_{IJK}^0  
		 *                                                          - 143.9313616 \: \vartheta_{ijk} + 0.02637679965 \: \vartheta_{IJK}^{0^2} + 2.512076157 \: \vartheta_{IJK}^0) \f$<br>
		 * \f$ \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} = \frac{-1}{\sqrt{1 - \cos(\vartheta_{ijk})^2}} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$ see calcBondAngleCosDerivatives().
		 *
		 * For linear or near-linear bond angles such as those which occur in alkynes,
		 * nitriles, isonitriles, azides, and diazo compounds, the energy function form used 
		 * in DREIDING and UFF is employed:
		 *
		 * \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EA_{ijk}}{\partial \vec{p_x}} = 143.9325 \: ka_{IJK} \: \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
		 *
		 * where<br>
		 * \f$ ka_{IJK} \f$ = angle bending force constant in  \f$ \frac{md Ang}{rad^2} \f$ for the
		 *                    angle between atoms \e i, \e j and \e k of atom types \e I, \e J and \e K.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees.<br>
		 * \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i, \e j and \e k.<br>
		 *
		 * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
		 * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom \e k.
		 * \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e k.
		 * \param linear If \c true, the bond angle is linear.
		 * \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94AngleBendingGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
												 GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad, 
												 bool linear, const ValueType& force_const, const ValueType& ref_angle);


		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94StretchBendGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94StretchBendGradient(const MMFF94StretchBendInteraction& iaction, const CoordsArray& coords, GradVector& grad);

 		/**
		 * \brief Calculates the stretch-bend interaction energy gradient \f$ \nabla EBA_{ijk} \f$ for two bonds \e i-j and \e j-k.
		 * 
		 * Energy function:<br>
		 *
		 * \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EBA_{ijk}}{\partial \vec{p_x}} = 2.5121 \: \Delta \vartheta_{ijk} \: (kba_{IJK} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} + kba_{KJI} \: \frac{\partial \Delta r_{kj}}{\partial \vec{p_x}}) + 
		 *                                                     2.5121 \: \frac{\partial \Delta \vartheta_{ijk}}{\partial \vec{p_x}} \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \f$<br>
		 *
		 * \f$ \frac{\partial \Delta \vartheta_{ijk}}{\partial \vec{p_x}} = \frac{\partial \Delta \vartheta_{ijk}}{\partial \vartheta_{ijk}} \: \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} \: 
		 *                                                                  \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
		 * \f$ \frac{\partial \Delta \vartheta_{ijk}}{\partial \vartheta_{ijk}} = \frac{180}{\pi} \f$<br>
		 * \f$ \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} = \frac{-1}{\sqrt{1 - \cos(\vartheta_{ijk})^2}} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$ see calcBondAngleCosDerivatives()
		 * and for the calculation of \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
		 *
		 * where<br>
		 * \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e i-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e k-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e k and \e j of types \e K and \e J.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} \: \frac{180}{\pi} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees.<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i, \e j and \e k.<br>
		 *
		 * Currently, stretch-bend interactions are omitted when the \e i-j-k interaction
		 * corresponds to a linear bond angle.  
		 *
		 * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
		 * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom \e k.
		 * \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e k.
		 * \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
		 * \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
		 * \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
		 * \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94StretchBendGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
												GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad, 
												const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
												const ValueType& ref_length1, const ValueType& ref_length2);


		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94OutOfPlaneBendingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94OutOfPlaneBendingGradient(const MMFF94OutOfPlaneBendingInteraction& iaction, const CoordsArray& coords, GradVector& grad);
  
		/**
		 * \brief Calculates the out-of-plane bending interaction energy gradient \f$ \nabla EOOP_{ijk;l} \f$ for the bond \e j-l and the plane \e i-j-k.
		 * 
		 * Energy function:<br>
		 *
		 * \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: (\chi_{ijk;l} \: \frac{180}{\pi})^2 \f$ 
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EOOP_{ijk;l}}{\partial \vec{p_x}} = \frac{\partial EOOP_{ijk;l}}{\partial \chi_{ijk;l}} \: \frac{\partial \chi_{ijk;l}}{\partial \cos(\alpha_{ijk;l})} \:
		 *                                                        \frac{\partial \cos(\alpha_{ijk;l})}{\partial \vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial EOOP_{ijk;l}}{\partial \chi_{ijk;l}} = 0.043844 \: (\frac{180}{\pi})^2 \: \chi_{ijk;l} \: koop_{IJK \colon L} \f$<br>
		 * \f$ \chi_{ijk;l} = \frac{\pi}{2} - \alpha_{ijk;l} \f$<br>
		 * \f$ \frac{\partial \chi_{ijk;l}}{\partial \cos(\alpha_{ijk;l})} = \frac{-1}{\sqrt{1 - \cos(\alpha_{ijk;l})^2}} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial \cos(\alpha_{ijk;l})}{\partial \vec{p_x}} \f$ see calcOutOfPlaneAngleCosDerivatives().
		 *
		 * where<br>
		 * \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
		 * \f$ \chi_{ijk;l} \f$ = angle in radians between the bond \e j-l and the 
		 *                        plane \e i-j-k, where \e j is the central atom.<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i, \e j, \e k and \e l.<br>
		 *
		 * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
		 * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom \e k.
		 * \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom \e l.
		 * \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e k.
		 * \param oop_atom_grad The output variable storing the accumulated energy gradient contributions for atom \e l.
		 * \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
		 * \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94OutOfPlaneBendingGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
													  const CoordsVec& oop_atom_pos, GradVec& term_atom1_grad, GradVec& ctr_atom_grad, 
													  GradVec& term_atom2_grad, GradVec& oop_atom_grad, const ValueType& force_const);


		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94TorsionGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94TorsionGradient(const MMFF94TorsionInteraction& iaction, const CoordsArray& coords, GradVector& grad);
 
		/**
		 * \brief Calculates the torsion interaction energy gradient \f$ \nabla ET_{ijkl} \f$ for the central bond \e j-k 
		 *        and the connected bonds \e i-j and \e k-l.
		 *
		 * Energy function:<br>
		 *
		 * \f$ ET_{ijkl} = 0.5 \: (V_1 \: (1 + \cos(\Phi_{ijkl})) + V_2 \: (1 - \cos(2 \: \Phi_{ijkl})) + V_3 \: (1 + \cos(3 \: \Phi_{ijkl}))) \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial ET_{ijkl}}{\partial \vec{p_x}} = \frac{\partial ET_{ijkl}}{\partial \Phi_{ijkl}} \: \frac{\partial \Phi_{ijkl}}{\partial \cos(\Phi_{ijkl})} \:
		 *                                                     \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial ET_{ijkl}}{\partial \Phi_{ijkl}} = V_2 \: \sin(2 \: \Phi_{ijkl}) - 0.5 \: V_1 \: \sin(\Phi_{ijkl}) - 1.5 \: V_3 \: \sin(3 \: \Phi_{ijkl}) \f$<br>
		 * \f$ \frac{\partial \Phi_{ijkl}}{\partial \cos(\Phi_{ijkl})} = \frac{-1}{\sqrt{1 - \cos(\Phi_{ijkl})^2}} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$ see calcDihedralAngleCosDerivatives().
		 *
		 * where<br>
		 * \f$ \Phi_{ijkl} \f$ is the \e i-j-k-l dihedral angle. The constants \f$ V_1 \f$, \f$ V_2 \f$ and 
		 * \f$ V_3 \f$ depend on the atom types \e I, \e J, \e K and \e L for atoms \e i, \e j, \e k and \e l, where \e i-j, 
		 * \e j-k and \e k-l are bonded pairs and \e i is not equal to \e l.<br>  
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i, \e j, \e k and \e l.<br>
		 *
		 * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
		 * \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
		 * \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom \e k.
		 * \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom \e l.
		 * \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param ctr_atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param ctr_atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e k.
		 * \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e l.
		 * \param tor_param1 The torsion parameter \f$ V_1 \f$.
		 * \param tor_param2 The torsion parameter \f$ V_2 \f$.
		 * \param tor_param3 The torsion parameter \f$ V_3 \f$.
		 * \return The calculated torsion interaction energy \f$ ET_{ijkl} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94TorsionGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, const CoordsVec& ctr_atom2_pos, 
											const CoordsVec& term_atom2_pos, GradVec& term_atom1_grad, GradVec& ctr_atom1_grad, 
											GradVec& ctr_atom2_grad, GradVec& term_atom2_grad, const ValueType& tor_param1,
											const ValueType& tor_param2, const ValueType& tor_param3);

		
		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94ElectrostaticGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94ElectrostaticGradient(const MMFF94ElectrostaticInteraction& iaction, const CoordsArray& coords, GradVector& grad);
 
		/**
		 * \brief Calculates the electrostatic interaction energy gradient \f$ \nabla EQ_{ij} \f$ for the atom pair \e i-j.
		 * 
		 * Energy function:<br>
		 *
		 * \f$ EQ_{ij} = S \: 332.0716 \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^n} \f$
		 * 
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial EQ_{ij}}{\partial \vec{p_x}} = \frac{\partial EQ_{ij}}{\partial R_{ij}} \: \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial EQ_{ij}}{\partial R_{ij}} = -S \: 332.0716 \: n \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^{n + 1}} \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
		 *
		 * where<br>
		 * \f$ S \f$ = a scaling factor depending on the topological distance of \e i-j.<br>
		 * \f$ q_i \f$ and \f$ q_j \f$ = partial atomic charges.<br>
		 * \f$ D \f$ = dielectric constant.<br>
		 * \f$ R_{ij} \f$ = interatomic distance (Å).<br>
		 * \f$ \delta \f$ = electrostatic buffering constant (\e 0.05 Å).<br>
		 * \f$ n \f$ = exponent (normally \e 1, but can be \e 2 for 
		 *             distance-dependent dielectric constant).<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i and \e j.<br>
		 *
		 * Note: 1-4 electrostatic interactions are scaled by \e 0.75 (thus,
		 * the electrostatic gradient term becomes \f$ EQ_{14} \: 0.75 \f$). 
		 * 
		 * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
		 * \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param atom1_chg The partial atom charge \f$ q_i \f$ of atom \e i.
		 * \param atom2_chg The partial atom charge \f$ q_j \f$ of atom \e j.
		 * \param scale_fact The scaling factor for \f$ S \f$ depending on the topological \e i-j distance.
		 * \param de_const The dielectric constant \f$ D \f$.
		 * \param dist_expo The exponent \f$ n \f$.
		 * \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94ElectrostaticGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, 
												  GradVec& atom2_grad, const ValueType& atom1_chg, const ValueType& atom2_chg,
												  const ValueType& scale_fact, const ValueType& de_const, const ValueType& dist_expo);

	
		template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94VanDerWaalsGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

		template <typename ValueType, typename CoordsArray, typename GradVector>
		ValueType calcMMFF94VanDerWaalsGradient(const MMFF94VanDerWaalsInteraction& iaction, const CoordsArray& coords, GradVector& grad);
		/*
		 * dEvdwij/dVi = dEvdwij/dRij * dRij/dVi
		 * dEvdwij/dRij = -R*IJ^7 * eIJ / (Rij + 0.07 * R*IJ)^8 / (Rij^7 + 0.12 * R*IJ^7)^2 * 
		 *               (-22.48094067 * Rij^14 + 19.78322779 * Rij^7 * R*IJ^7 + 0.8812528743 * Rij^6 * R*IJ^8 + 1.186993667 * R*IJ^14)
		 */

		/**
		 * \brief Calculates the van der Waals interaction energy gradient \f$ \nabla E_{vdW_{ij}} \f$ for the atom pair \e i-j.
		 *
		 * Energy function:<br>
		 * \f$ E_{vdW_{ij}} = \varepsilon_{IJ} \: (\frac{1.07 \: R_{IJ}^*}{(R_{ij} + 0.07 \: R_{IJ}^*)})^7 \: (\frac{1.12 \: R_{IJ}^{*^7}}{(R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})} - 2) \;\;\;\; (1) \f$
		 *
		 * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
		 *
		 * \f$ \frac{\partial E_{vdW_{ij}}}{\partial \vec{p_x}} = \frac{\partial E_{vdW_{ij}}}{\partial R_{ij}} \: \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$<br>
		 *
		 * \f$ \frac{\partial E_{vdW_{ij}}}{\partial R_{ij}} = \frac{-R_{IJ}^{*^7} \: \varepsilon_{IJ}}{(R_{ij} + 0.07 \: R_{IJ}^*)^8 \: (R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})^2} \: 
		 *               (-22.48094067 \: R_{ij}^{14} + 19.78322779 \: R_{ij}^7 \: R_{IJ}^{*^7} + 0.8812528743 \: R_{ij}^6 \: R_{IJ}^{*^8} + 1.186993667 \: R_{IJ}^{*^{14}}) \f$<br>
		 *
		 * for the calculation of the partial derivatives \f$ \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
		 *
		 * where<br>
		 * \f$ R_{ij} \f$ = the interatomic distance.<br>
		 * \f$ R_{II}^* = A_I \: \alpha_I^{PEXP} \;\;\;\; (2) \f$<br>
		 * \f$ R_{IJ}^* = 0.5 \: (R_{II}^* + R_{JJ}^*) \: (1 + AFACT(1 - \exp(-BFACT \: \gamma_{IJ}^2))) \;\;\;\; (3) \f$<br> 
		 * \f$ \gamma_{IJ} = \frac{(R_{II}^* - R_{JJ}^*)}{(R_{II}^* + R_{JJ}^*)} \;\;\;\; (4) \f$ <br>
		 * \f$ \varepsilon_{IJ} = \frac{181.16 \: G_I \: GJ \: \alpha_I \: \alpha_J}{((\alpha_I / N_I)^{1/2} + (\alpha_J / N_J)^{1/2})} \: \frac{1}{R_{IJ}^{*6}} \;\;\;\; (5) \f$<br>
		 * \f$ \vec{p_x} \f$ = coordinates of the involved atoms \e i and \e j.<br>
		 *
		 * MMFF employs a "Buffered 14-7" form (eq 1) together with an 
		 * expression which relates the minimum-gradient separation \f$ R_{II}^* \f$ to the 
		 * atomic polarizability \f$ \alpha_I \f$ (eq 2), a specially formulated combination rule 
		 * (eqs 3, 4), and a Slater-Kirkwood expression for the well depth \f$ \varepsilon_{IJ} \f$ (eq 5): 
		 * The first non-comment line in the parameter file "MMFFVDW.PAR" contains five floating 
		 * point numbers which define the variables \e PEXP, \e AFACT, \e BFACT, \e DARAD, and 
		 * \e DAEPS, respectively. \e PEXP (currently \e 0.25), \e AFACT (currently \e 0.2) and \e BFACT 
		 * (currently \e 12.0) are used in the equations shown above; \e DARAD and \e DAEPS 
		 * are used as follows:
		 *
		 * When either \e i or \e j is a hydrogen-bond donor, MMFF uses the simple
		 * arithmetic mean \f$ 0.5 \: (R_{II}^* + R_{JJ}^*) \f$ instead of eq 3 to obtain \f$ R_{IJ}^* \f$. If the
		 * \e i-j interaction is a donor-acceptor interaction, MMFF also scales \f$ R_{IJ}^* \f$ as given
		 * by eq 3 by \e DARAD (currently \e 0.8) and \f$ \varepsilon_{IJ} \f$ as given by eq 5 by \e DAEPS (currently
		 * \e 0.5). 
		 *   
		 * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
		 * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
		 * \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
		 * \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
		 * \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
		 * \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
		 * \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
		 * \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$.
		 * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
		 *       corresponding output variable!
		 */
		template <typename ValueType, typename CoordsVec, typename GradVec>
		ValueType calcMMFF94VanDerWaalsGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, 
												GradVec& atom2_grad, const ValueType& e_IJ, const ValueType& r_IJ, 
												const ValueType& r_IJ_7);
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

			template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector, typename FuncType>
			ValueType calcMMFF94InteractionGradient(Iter& beg, const Iter& end, const CoordsArray& coords, GradVector& grad, 
													const FuncType& func)
			{
				ValueType e = ValueType();

				for ( ; beg != end; ++beg)
					e += func(*beg, coords, grad);

				return e;
			}	
		}
	}
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94BondStretchingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad, 
															static_cast<ValueType (*)(const MMFF94BondStretchingInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94BondStretchingGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94BondStretchingGradient(const MMFF94BondStretchingInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94BondStretchingGradient<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
													   grad[iaction.getAtom1Index()], grad[iaction.getAtom2Index()],
													   iaction.getForceConstant(), iaction.getReferenceLength());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94BondStretchingGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
															 GradVec& atom1_grad, GradVec& atom2_grad,
															 const ValueType& force_const, const ValueType& ref_length)
{
	ValueType dist_atom1_grad[3];
	ValueType dist_atom2_grad[3];

	ValueType dr_ij = calcDistanceDerivatives<ValueType>(atom1_pos, atom2_pos, dist_atom1_grad, dist_atom2_grad) - ref_length;
	ValueType dr_ij_2 = dr_ij * dr_ij;

	ValueType grad_fact = (ValueType(167.92125 * 4) * dr_ij_2 * dr_ij - ValueType(215.89875 * 2) * dr_ij_2 + 
						   ValueType(143.9325) * dr_ij) * force_const;

	Detail::scaleAddVector(dist_atom1_grad, grad_fact, atom1_grad);
	Detail::scaleAddVector(dist_atom2_grad, grad_fact, atom2_grad);

	ValueType e_b = ValueType(143.9325 * 0.5) * force_const * dr_ij_2 * (1 - 2 * dr_ij + 28 * dr_ij_2 / 12);

	return e_b;
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94AngleBendingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad, 
															static_cast<ValueType (*)(const MMFF94AngleBendingInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94AngleBendingGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94AngleBendingGradient(const MMFF94AngleBendingInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94AngleBendingGradient<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
													 coords[iaction.getTerminalAtom2Index()], grad[iaction.getTerminalAtom1Index()],
													 grad[iaction.getCenterAtomIndex()], grad[iaction.getTerminalAtom2Index()],
													 iaction.isLinearAngle(), iaction.getForceConstant(), iaction.getReferenceAngle());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94AngleBendingGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														   GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad, 
														   bool linear, const ValueType& force_const, const ValueType& ref_angle)
{
	ValueType ac_term1_grad[3];
	ValueType ac_ctr_grad[3];
	ValueType ac_term2_grad[3];

	ValueType a_ijk_cos = calcBondAngleCosDerivatives<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos,
																 ac_term1_grad, ac_ctr_grad, ac_term2_grad);
    ValueType grad_fact = ValueType(1);
    ValueType e_a = ValueType(0);
    
    if (linear) {
		grad_fact = ValueType(143.9325) * force_const;
		e_a = ValueType(143.9325) * force_const * (1 + a_ijk_cos);

    } else {
		ValueType a_ijk_cos_2 = a_ijk_cos * a_ijk_cos;
		ValueType a_ijk = std::acos(a_ijk_cos);
		ValueType div = std::sqrt(1 - a_ijk_cos_2);

		if (div < ValueType(0.0000001))
			div = ValueType(0.0000001);

		grad_fact = force_const / div * 
			(a_ijk * (ValueType(86.58992538) * a_ijk - ValueType(143.9313616)) - 
			 ref_angle * (ValueType(3.022558594) * a_ijk - ValueType(0.02637679965) * ref_angle - ValueType(2.512076157)));

		ValueType da_ijk = a_ijk  * ValueType(180 / M_PI) - ref_angle;
      
		e_a = ValueType(0.043844 * 0.5) * force_const * da_ijk * da_ijk * (1 - ValueType(0.007) * da_ijk);
    }

   	Detail::scaleAddVector(ac_term1_grad, grad_fact, term_atom1_grad);
   	Detail::scaleAddVector(ac_ctr_grad, grad_fact, ctr_atom_grad);
   	Detail::scaleAddVector(ac_term2_grad, grad_fact, term_atom2_grad);

    return e_a;
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94StretchBendGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad,
															static_cast<ValueType (*)(const MMFF94StretchBendInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94StretchBendGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94StretchBendGradient(const MMFF94StretchBendInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94StretchBendGradient<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
													coords[iaction.getTerminalAtom2Index()], grad[iaction.getTerminalAtom1Index()],
													grad[iaction.getCenterAtomIndex()], grad[iaction.getTerminalAtom2Index()],
													iaction.getIJKForceConstant(), iaction.getKJIForceConstant(), iaction.getReferenceAngle(),
													iaction.getReferenceLength1(), iaction.getReferenceLength2());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94StretchBendGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														  GradVec& term_atom1_grad, GradVec& ctr_atom_grad, GradVec& term_atom2_grad, 
														  const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
														  const ValueType& ref_length1, const ValueType& ref_length2)
{
	ValueType ac_term1_grad[3];
	ValueType ac_ctr_grad[3];
	ValueType ac_term2_grad[3];

	ValueType dist_term1_grad[3];
	ValueType dist_ctr_grad1[3];
	ValueType dist_ctr_grad2[3];
	ValueType dist_term2_grad[3];

	ValueType r_ij = calcDistanceDerivatives<ValueType>(term_atom1_pos, ctr_atom_pos, dist_term1_grad, dist_ctr_grad1);
	ValueType r_kj = calcDistanceDerivatives<ValueType>(term_atom2_pos, ctr_atom_pos, dist_term2_grad, dist_ctr_grad2);
	ValueType a_ijk_cos = calcBondAngleCosDerivatives<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, ac_term1_grad, ac_ctr_grad, ac_term2_grad);
	ValueType a_ijk_cos_2 = a_ijk_cos * a_ijk_cos;
	ValueType a_ijk = std::acos(a_ijk_cos);

	ValueType dr_ij = r_ij - ref_length1;
	ValueType dr_kj = r_kj - ref_length2;
	ValueType da_ijk = a_ijk * ValueType(180 / M_PI) - ref_angle;
	ValueType div = std::sqrt(1 - a_ijk_cos_2);

	if (div < ValueType(0.0000001))
		div = ValueType(0.0000001);

    ValueType a_ijk_grad_fact = ValueType(-180 * 2.5121 / M_PI) / div * (dr_ij * ijk_force_const + dr_kj * kji_force_const);

	ValueType r_ij_grad_fact = ValueType(2.5121) * da_ijk * ijk_force_const;
	ValueType r_kj_grad_fact = ValueType(2.5121) * da_ijk * kji_force_const;
  
	Detail::scaleAddVector(dist_term1_grad, r_ij_grad_fact, term_atom1_grad);
	Detail::scaleAddVector(ac_term1_grad, a_ijk_grad_fact, term_atom1_grad);

	Detail::scaleAddVector(dist_term2_grad, r_kj_grad_fact, term_atom2_grad);
	Detail::scaleAddVector(ac_term2_grad, a_ijk_grad_fact, term_atom2_grad);

	Detail::scaleAddVector(dist_ctr_grad1, r_ij_grad_fact, ctr_atom_grad);
	Detail::scaleAddVector(dist_ctr_grad2, r_kj_grad_fact, ctr_atom_grad);
	Detail::scaleAddVector(ac_ctr_grad, a_ijk_grad_fact, ctr_atom_grad);
	
	ValueType e_ab = r_ij_grad_fact * dr_ij + r_kj_grad_fact * dr_kj; 

	return e_ab;
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad,
															static_cast<ValueType (*)(const MMFF94OutOfPlaneBendingInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94OutOfPlaneBendingGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient(const MMFF94OutOfPlaneBendingInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94OutOfPlaneBendingGradient<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
														  coords[iaction.getTerminalAtom2Index()], coords[iaction.getOutOfPlaneAtomIndex()],
														  grad[iaction.getTerminalAtom1Index()], grad[iaction.getCenterAtomIndex()], 
														  grad[iaction.getTerminalAtom2Index()], grad[iaction.getOutOfPlaneAtomIndex()],
														  iaction.getForceConstant());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
																const CoordsVec& oop_atom_pos, GradVec& term_atom1_grad, GradVec& ctr_atom_grad,
																GradVec& term_atom2_grad, GradVec& oop_atom_grad, const ValueType& force_const)
{
    ValueType ac_term1_grad[3];
    ValueType ac_term2_grad[3];
    ValueType ac_ctr_grad[3];
    ValueType ac_oop_grad[3];

    ValueType chi_ijkl_cos = calcOutOfPlaneAngleCosDerivatives<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos, 
																		  ac_term1_grad, ac_ctr_grad, ac_term2_grad, ac_oop_grad);
	ValueType chi_ijkl = ValueType(M_PI * 0.5) - std::acos(chi_ijkl_cos);
	ValueType div = std::sqrt(1 - chi_ijkl_cos * chi_ijkl_cos);

	if (div < ValueType(0.0000001))
		div = ValueType(0.0000001);

    ValueType grad_fact = ValueType(0.043844 * 180 * 180) / div * ValueType(1 / (M_PI * M_PI)) * force_const * chi_ijkl;
    
	Detail::scaleAddVector(ac_term1_grad, grad_fact, term_atom1_grad);
	Detail::scaleAddVector(ac_ctr_grad, grad_fact, ctr_atom_grad);
	Detail::scaleAddVector(ac_term2_grad, grad_fact, term_atom2_grad);
	Detail::scaleAddVector(ac_oop_grad, grad_fact, oop_atom_grad);

	chi_ijkl *= ValueType(180 / M_PI);

	ValueType e_oop = ValueType(0.5 * 0.043844) * force_const * chi_ijkl * chi_ijkl;

	return e_oop;
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94TorsionGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad,
															static_cast<ValueType (*)(const MMFF94TorsionInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94TorsionGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94TorsionGradient(const MMFF94TorsionInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94TorsionGradient<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtom1Index()], 
												coords[iaction.getCenterAtom2Index()], coords[iaction.getTerminalAtom2Index()],
												grad[iaction.getTerminalAtom1Index()], grad[iaction.getCenterAtom1Index()], 
												grad[iaction.getCenterAtom2Index()], grad[iaction.getTerminalAtom2Index()],
												iaction.getTorsionParameter1(), iaction.getTorsionParameter2(), iaction.getTorsionParameter3());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94TorsionGradient(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, const CoordsVec& ctr_atom2_pos, 
													  const CoordsVec& term_atom2_pos, GradVec& term_atom1_grad, GradVec& ctr_atom1_grad,
													  GradVec& ctr_atom2_grad, GradVec& term_atom2_grad, const ValueType& tor_param1,
													  const ValueType& tor_param2, const ValueType& tor_param3)
{
	ValueType ac_term1_grad[3];
    ValueType ac_ctr1_grad[3];
    ValueType ac_ctr2_grad[3];
	ValueType ac_term2_grad[3];

	ValueType phi_cos = calcDihedralAngleCosDerivatives<ValueType>(term_atom1_pos, ctr_atom1_pos, ctr_atom2_pos, term_atom2_pos,
																   ac_term1_grad, ac_ctr1_grad, ac_ctr2_grad, ac_term2_grad); 
	ValueType phi = std::acos(phi_cos);
	ValueType phi_cos_2 = phi_cos * phi_cos;
	ValueType div = std::sqrt(1 - phi_cos_2);

	if (div < ValueType(0.0000001))
		div = ValueType(0.0000001);

    ValueType grad_fact = ValueType(-1) / div *
		(tor_param2 * std::sin(2 * phi)  - 
		 ValueType(0.5) * tor_param1 * std::sin(phi) - 
		 ValueType(1.5) * tor_param3 * std::sin(3 * phi));
	
   	Detail::scaleAddVector(ac_term1_grad, grad_fact, term_atom1_grad);
	Detail::scaleAddVector(ac_ctr1_grad, grad_fact, ctr_atom1_grad);
	Detail::scaleAddVector(ac_ctr2_grad, grad_fact, ctr_atom2_grad);
	Detail::scaleAddVector(ac_term2_grad, grad_fact, term_atom2_grad);
	
	ValueType e_t = ValueType(0.5) * (tor_param1 * (1 + phi_cos) + tor_param2 * (1 - std::cos(2 * phi)) + tor_param3 * (1 + std::cos(3 * phi)));

	return e_t;
}

		
template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad,
															static_cast<ValueType (*)(const MMFF94ElectrostaticInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94ElectrostaticGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticGradient(const MMFF94ElectrostaticInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94ElectrostaticGradient<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
													  grad[iaction.getAtom1Index()], grad[iaction.getAtom2Index()],
													  iaction.getAtom1Charge(), iaction.getAtom2Charge(), iaction.getScalingFactor(),
													  iaction.getDielectricConstant(), iaction.getDistanceExponent());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, 
															GradVec& atom2_grad, const ValueType& atom1_chg, const ValueType& atom2_chg,
															const ValueType& scale_fact, const ValueType& de_const, const ValueType& dist_expo)
{
	ValueType dist_atom1_grad[3];
	ValueType dist_atom2_grad[3];

	ValueType r_ij = calcDistanceDerivatives<ValueType>(atom1_pos, atom2_pos, dist_atom1_grad, dist_atom2_grad);

    ValueType tmp1 = r_ij + ValueType(0.05);
    ValueType tmp2 = std::pow(tmp1, dist_expo);
	ValueType tmp3 = scale_fact * atom1_chg * atom2_chg / (de_const * tmp2);

	ValueType grad_fact = ValueType(-332.0716) * dist_expo * tmp3 / tmp1;
  
  	Detail::scaleAddVector(dist_atom1_grad, grad_fact, atom1_grad);
	Detail::scaleAddVector(dist_atom2_grad, grad_fact, atom2_grad);
      
    double e_q = ValueType(332.0716) * tmp3;

    return e_q;
}

	
template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
	return Detail::calcMMFF94InteractionGradient<ValueType>(beg, end, coords, grad, 
															static_cast<ValueType (*)(const MMFF94VanDerWaalsInteraction&, const CoordsArray&, GradVector&)>(
																&calcMMFF94VanDerWaalsGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsGradient(const MMFF94VanDerWaalsInteraction& iaction, const CoordsArray& coords, GradVector& grad)
{
	return calcMMFF94VanDerWaalsGradient<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
													grad[iaction.getAtom1Index()], grad[iaction.getAtom2Index()],
													iaction.getEIJ(), iaction.getRIJ(), iaction.getRIJPow7());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, 
														  GradVec& atom2_grad, const ValueType& e_IJ, const ValueType& r_IJ, const ValueType& r_IJ_7)
{
	ValueType dist_atom1_grad[3];
	ValueType dist_atom2_grad[3];

	ValueType r_ij = calcDistanceDerivatives<ValueType>(atom1_pos, atom2_pos, dist_atom1_grad, dist_atom2_grad);
	ValueType r_ij_2 = r_ij * r_ij;
	ValueType r_ij_6 = r_ij_2 * r_ij_2 * r_ij_2;
    ValueType r_ij_7 = r_ij_6 * r_ij;
    
    ValueType tmp1 = r_ij + ValueType(0.07) * r_IJ;
    ValueType tmp1_2 = tmp1 * tmp1;
    ValueType tmp1_4 = tmp1_2 * tmp1_2;

	ValueType tmp2 =  r_ij_7 + ValueType(0.12) * r_IJ_7;

	ValueType tmp3 = ValueType(1.07) * r_IJ / (r_ij + ValueType(0.07) * r_IJ);
    ValueType tmp3_2 = tmp3 * tmp3;
    ValueType tmp3_7 = tmp3_2 * tmp3_2 * tmp3_2 * tmp3;

    ValueType grad_fact = -r_IJ_7 * e_IJ / (tmp1_4 * tmp1_4 * tmp2 * tmp2) *
		(ValueType(-22.48094067) * r_ij_7 * r_ij_7 + ValueType(19.78322779) * r_ij_7 * r_IJ_7 + 
		 ValueType(0.8812528743) * r_ij_6 * r_IJ_7 * r_IJ + ValueType(1.186993667) * r_IJ_7 * r_IJ_7);

	Detail::scaleAddVector(dist_atom1_grad, grad_fact, atom1_grad);
	Detail::scaleAddVector(dist_atom2_grad, grad_fact, atom2_grad);

    ValueType e_vdw = e_IJ * tmp3_7 * (ValueType(1.12) * r_IJ_7 / tmp2 - 2);

	return e_vdw;
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94GRADIENTFUNCTIONS_HPP
