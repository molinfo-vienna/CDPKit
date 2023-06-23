/* 
 * MMFF94EnergyFunctions.hpp 
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
 * \brief Functions for the calculation of MMFF94 interaction energies.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ENERGYFUNCTIONS_HPP
#define CDPL_FORCEFIELD_MMFF94ENERGYFUNCTIONS_HPP

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

		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94BondStretchingEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94BondStretchingEnergy(const MMFF94BondStretchingInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the bond stretching interaction energy \f$ EB_{ij} \f$ for the bond \e i-j.
		 * 
		 * \f$ EB_{ij} = 143.9325 \: \frac{kb_{IJ}}{2} \: \Delta r_{ij}^2 \times (1 + cs \: \Delta r_{ij} + \frac{7}{12} \: cs^2 \: \Delta r_{ij}^2) \f$
		 *
		 * where<br>
		 * \f$ kb_{IJ} \f$ = the bond stretching force constant in \f$ \frac{md}{Ang} \f$ for bonded 
		 *                   atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and 
		 *                         \e j of types \e I and \e J (see calcDistance()).<br>
		 * \f$ cs \f$ = \f$ -2 \: Ang^{-1} \f$, the "cubic stretch" constant.<br>
		 *
		 * Note: throughout this description, the indices \e i, \e j, \e k, ... represent atoms;
		 * \e I, \e J, \e K, ... denote the corresponding numerical MMFF atom types (or, 
		 * occasionally, the atomic species).
		 * 
		 * \param atom1_pos The position of atom \e i.
		 * \param atom2_pos The position of atom \e j.
		 * \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
		 * \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
		 * \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94BondStretchingEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, 
												 const ValueType& force_const, const ValueType& ref_length);

		/**
		 * \brief Calculates the bond stretching interaction energy \f$ EB_{ij} \f$ for the bond \e i-j.
		 * 
		 * \f$ EB_{ij} = 143.9325 \: \frac{kb_{IJ}}{2} \: \Delta r_{ij}^2 \times (1 + cs \: \Delta r_{ij} + \frac{7}{12} \: cs^2 \: \Delta r_{ij}^2) \f$
		 *
		 * where<br>
		 * \f$ kb_{IJ} \f$ = the bond stretching force constant in \f$ \frac{md}{Ang} \f$ for bonded 
		 *                   atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and 
		 *                         \e j of types \e I and \e J (see calcDistance()).<br>
		 * \f$ cs \f$ = \f$ -2 \: Ang^{-1} \f$, the "cubic stretch" constant.<br>
		 *
		 * Note: throughout this description, the indices \e i, \e j, \e k, ... represent atoms;
		 * \e I, \e J, \e K, ... denote the corresponding numerical MMFF atom types (or, 
		 * occasionally, the atomic species).
		 * 
		 * \param r_ij The length of the bond between atom \e i and \e j.
		 * \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
		 * \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
		 * \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$.
		 */
		template <typename ValueType>
		ValueType calcMMFF94BondStretchingEnergy(const ValueType& r_ij, const ValueType& force_const, const ValueType& ref_length);


		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94AngleBendingEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94AngleBendingEnergy(const MMFF94AngleBendingInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the angle bending interaction energy \f$ EA_{ijk} \f$ for two bonds \e i-j and \e j-k. 
		 *
		 * \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
		 *
		 * where<br>
		 * \f$ ka_{IJK} \f$ = angle bending force constant in  \f$ \frac{md Ang}{rad^2} \f$ for the
		 *                    angle between atoms \e i, \e j and \e k of atom types \e I, \e J and \e K.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees (see calcBondAngle()).<br>
		 * \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
		 *
		 * For linear or near-linear bond angles such as those which occur in alkynes,
		 * nitriles, isonitriles, azides, and diazo compounds, the form used 
		 * in DREIDING and UFF is employed:
		 *
		 * \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
		 *
		 * where \f$ ka_{IJK} \f$ and \f$ \vartheta_{ijk} \f$ are defined as above. 
		 * 
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param linear If \c true, the bond angle is linear.
		 * \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94AngleBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
											   bool linear, const ValueType& force_const, const ValueType& ref_angle);

		/**
		 * \brief Calculates the angle bending interaction energy \f$ EA_{ijk} \f$ for two bonds \e i-j and \e j-k. 
		 *
		 * \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
		 *
		 * where<br>
		 * \f$ ka_{IJK} \f$ = angle bending force constant in  \f$ \frac{md Ang}{rad^2} \f$ for the
		 *                    angle between atoms \e i, \e j and \e k of atom types \e I, \e J and \e K.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees (see calcBondAngle()).<br>
		 * \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
		 *
		 * For linear or near-linear bond angles such as those which occur in alkynes,
		 * nitriles, isonitriles, azides, and diazo compounds, the form used 
		 * in DREIDING and UFF is employed:
		 *
		 * \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
		 *
		 * where \f$ ka_{IJK} \f$ and \f$ \vartheta_{ijk} \f$ are defined as above. 
		 * 
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param r_ij The length of the bond between atom \e i and \e j.
		 * \param r_jk The length of the bond between atom \e j and \e k.
		 * \param linear If \c true, the bond angle is linear.
		 * \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94AngleBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
											   const ValueType& r_ij, const ValueType& r_jk,
											   bool linear, const ValueType& force_const, const ValueType& ref_angle);



		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94StretchBendEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94StretchBendEnergy(const MMFF94StretchBendInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the stretch-bend interaction energy \f$ EBA_{ijk} \f$ for two bonds \e i-j and \e j-k.
		 * 
		 * \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
		 *
		 * where<br>
		 * \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e i-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e k-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e k and \e j of types \e K and \e J.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees.<br>
		 *
		 * For the calculation of \f$ r_{ij} \f$, \f$ r_{kj} \f$, and \f$ \vartheta_{ijk} \f$ see calcBondLengthsAndAngle().
		 *
		 * Currently, stretch-bend interactions are omitted when the \e i-j-k interaction
		 * corresponds to a linear bond angle.  
		 *
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
		 * \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
		 * \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
		 * \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$.
 		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94StretchBendEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
											  const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
											  const ValueType& ref_length1, const ValueType& ref_length2);

		/**
		 * \brief Calculates the stretch-bend interaction energy \f$ EBA_{ijk} \f$ for two bonds \e i-j and \e j-k.
		 * 
		 * \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
		 *
		 * where<br>
		 * \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e i-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for \e k-j stretch coupled to \e i-j-k bend.<br>
		 * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e i and \e j of types \e I and \e J.<br>
		 * \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and
		 *                         reference bond lengths between bonded atoms \e k and \e j of types \e K and \e J.<br>
		 * \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and 
		 *                                  reference \e i-j-k bond angles in degrees.<br>
		 *
		 * For the calculation of \f$ r_{ij} \f$, \f$ r_{kj} \f$, and \f$ \vartheta_{ijk} \f$ see calcBondLengthsAndAngle().
		 *
		 * Currently, stretch-bend interactions are omitted when the \e i-j-k interaction
		 * corresponds to a linear bond angle.  
		 *
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param r_ij The length of the bond between atom \e i and \e j.
		 * \param r_jk The length of the bond between atom \e j and \e k.
		 * \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
		 * \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
		 * \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
		 * \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
		 * \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
		 * \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$.
 		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94StretchBendEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
											  const ValueType& r_ij, const ValueType& r_jk,
											  const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
											  const ValueType& ref_length1, const ValueType& ref_length2);


		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94OutOfPlaneBendingEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94OutOfPlaneBendingEnergy(const MMFF94OutOfPlaneBendingInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$ for the bond \e j-l and the plane \e i-j-k.
		 * 
		 * \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: \chi_{ijk;l}^2 \f$ 
		 *
		 * where<br>
		 * \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
		 * \f$ \chi_{ijk;l} \f$ = angle in degrees between the bond \e j-l and the 
		 *                        plane \e i-j-k, where \e j is the central atom (see calcOutOfPlaneAngle()).<br>
		 *
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param oop_atom_pos The position of the out-of-plane atom \e l.
		 * \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
		 * \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94OutOfPlaneBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
													const CoordsVec& oop_atom_pos, const ValueType& force_const);

		/**
		 * \brief Calculates the out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$ for the bond \e j-l and the plane \e i-j-k.
		 * 
		 * \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: \chi_{ijk;l}^2 \f$ 
		 *
		 * where<br>
		 * \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
		 * \f$ \chi_{ijk;l} \f$ = angle in degrees between the bond \e j-l and the 
		 *                        plane \e i-j-k, where \e j is the central atom (see calcOutOfPlaneAngle()).<br>
		 *
		 * \param term_atom1_pos The position of atom \e i.
		 * \param ctr_atom_pos The position of the central atom \e j.
		 * \param term_atom2_pos The position of atom \e k.
		 * \param oop_atom_pos The position of the out-of-plane atom \e l.
		 * \param r_jl The length of the bond between atom \e j and atom \e l.
		 * \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
		 * \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94OutOfPlaneBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
													const CoordsVec& oop_atom_pos, const ValueType& r_jl, const ValueType& force_const);


		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94TorsionEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94TorsionEnergy(const MMFF94TorsionInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the torsion interaction energy \f$ ET_{ijkl} \f$ for the central bond \e j-k 
		 *        and the connected bonds \e i-j and \e k-l.
		 *
		 * \f$ ET_{ijkl} = 0.5 \: (V_1 \: (1 + \cos(\Phi_{ijkl})) + V_2 \: (1 - \cos(2 \: \Phi_{ijkl})) + V_3 \: (1 + \cos(3 \: \Phi_{ijkl}))) \f$
		 *
		 * where \f$ \Phi_{ijkl} \f$ is the \e i-j-k-l dihedral angle. The constants \f$ V_1 \f$, \f$ V_2 \f$ and 
		 * \f$ V_3 \f$ depend on the atom types \e I, \e J, \e K and \e L for atoms \e i, \e j, \e k and \e l, where \e i-j, 
		 * \e j-k and \e k-l are bonded pairs and \e i is not equal to \e l.  
		 *
		 * For the calculation of \f$ \cos(\Phi_{ijkl}) \f$ see calcDihedralAngleCos().
		 *
		 * \param term_atom1_pos The position of the terminal atom \e i.
		 * \param ctr_atom1_pos The position of the central atom \e j.
		 * \param ctr_atom2_pos The position of the central atom \e k.
		 * \param term_atom2_pos The position of the terminal atom \e l.
		 * \param tor_param1 The torsion parameter \f$ V_1 \f$.
		 * \param tor_param2 The torsion parameter \f$ V_2 \f$.
		 * \param tor_param3 The torsion parameter \f$ V_3 \f$.
		 * \return The calculated torsion interaction energy \f$ ET_{ijkl} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94TorsionEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, const CoordsVec& ctr_atom2_pos, 
										  const CoordsVec& term_atom2_pos, const ValueType& tor_param1, const ValueType& tor_param2,
										  const ValueType& tor_param3);

		
		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94ElectrostaticEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94ElectrostaticEnergy(const MMFF94ElectrostaticInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the electrostatic interaction energy \f$ EQ_{ij} \f$ for the atom pair \e i-j.
		 * 
		 * \f$ EQ_{ij} = S \: 332.0716 \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^n} \f$
		 * 
		 * where<br>
		 * \f$ S \f$ = a scaling factor depending on the topological distance of \e i-j.<br>
		 * \f$ q_i \f$ and \f$ q_j \f$ = Partial atomic charges.<br>
		 * \f$ D \f$ = Dielectric constant.<br>
		 * \f$ R_{ij} \f$ = Interatomic distance (Å) (see calcDistance()).<br>
		 * \f$ \delta \f$ = Electrostatic buffering constant (\e 0.05 Å).<br>
		 * \f$ n \f$ = Exponent (normally \e 1, but can be \e 2 for 
		 *             distance-dependent dielectric constant).<br>
		 *
		 * Note: 1-4 electrostatic interactions are scaled by \e 0.75 (thus,
		 * the electrostatic energy term becomes \f$ EQ_{14} \: 0.75 \f$). 
		 * 
		 * \param atom1_pos The position of atom \e i.
		 * \param atom2_pos The position of atom \e j.
		 * \param atom1_chg The partial atom charge \f$ q_i \f$ of atom \e i.
		 * \param atom2_chg The partial atom charge \f$ q_j \f$ of atom \e j.
		 * \param scale_fact The scaling factor for \f$ S \f$ depending on the topological \e i-j distance.
		 * \param de_const The dielectric constant \f$ D \f$.
		 * \param dist_expo The exponent \f$ n \f$.
		 * \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94ElectrostaticEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, const ValueType& atom1_chg,
												const ValueType& atom2_chg, const ValueType& scale_fact, const ValueType& de_const, 
												const ValueType& dist_expo);

		/**
		 * \brief Calculates the electrostatic interaction energy \f$ EQ_{ij} \f$ for the atom pair \e i-j.
		 * 
		 * \f$ EQ_{ij} = S \: 332.0716 \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^n} \f$
		 * 
		 * where<br>
		 * \f$ S \f$ = a scaling factor depending on the topological distance of \e i-j.<br>
		 * \f$ q_i \f$ and \f$ q_j \f$ = Partial atomic charges.<br>
		 * \f$ D \f$ = Dielectric constant.<br>
		 * \f$ R_{ij} \f$ = Interatomic distance (Å) (see calcDistance()).<br>
		 * \f$ \delta \f$ = Electrostatic buffering constant (\e 0.05 Å).<br>
		 * \f$ n \f$ = Exponent (normally \e 1, but can be \e 2 for 
		 *             distance-dependent dielectric constant).<br>
		 *
		 * Note: 1-4 electrostatic interactions are scaled by \e 0.75 (thus,
		 * the electrostatic energy term becomes \f$ EQ_{14} \: 0.75 \f$). 
		 * 
		 * \param r_ij The interatomic distance \f$ R_{ij} \f$ of atom \e i and atom \e j.
		 * \param atom1_chg The partial atom charge \f$ q_i \f$ of atom \e i.
		 * \param atom2_chg The partial atom charge \f$ q_j \f$ of atom \e j.
		 * \param scale_fact The scaling factor for \f$ S \f$ depending on the topological \e i-j distance.
		 * \param de_const The dielectric constant \f$ D \f$.
		 * \param dist_expo The exponent \f$ n \f$.
		 * \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$.
		 */
		template <typename ValueType>
		ValueType calcMMFF94ElectrostaticEnergy(const ValueType& r_ij, const ValueType& atom1_chg, const ValueType& atom2_chg, 
												const ValueType& scale_fact, const ValueType& de_const, const ValueType& dist_expo);

	
		template <typename ValueType, typename Iter, typename CoordsArray>
		ValueType calcMMFF94VanDerWaalsEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

		template <typename ValueType, typename CoordsArray>
		ValueType calcMMFF94VanDerWaalsEnergy(const MMFF94VanDerWaalsInteraction& iaction, const CoordsArray& coords);

		/**
		 * \brief Calculates the van der Waals interaction energy \f$ E_{vdW_{ij}} \f$ for the atom pair \e i-j.
		 *
		 * \f$ E_{vdW_{ij}} = \varepsilon_{IJ} \: (\frac{1.07 \: R_{IJ}^*}{(R_{ij} + 0.07 \: R_{IJ}^*)})^7 \: (\frac{1.12 \: R_{IJ}^{*^7}}{(R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})} - 2) \;\;\;\; (1) \f$
		 *
		 * where<br>
		 * \f$ R_{ij} \f$ = the interatomic distance (see calcDistance()).<br>
		 * \f$ R_{II}^* = A_I \: \alpha_I^{PEXP} \;\;\;\; (2) \f$<br>
		 * \f$ R_{IJ}^* = 0.5 \: (R_{II}^* + R_{JJ}^*) \: (1 + AFACT(1 - \exp(-BFACT \: \gamma_{IJ}^2))) \;\;\;\; (3) \f$<br> 
		 * \f$ \gamma_{IJ} = \frac{(R_{II}^* - R_{JJ}^*)}{(R_{II}^* + R_{JJ}^*)} \;\;\;\; (4) \f$ <br>
		 * \f$ \varepsilon_{IJ} = \frac{181.16 \: G_I \: GJ \: \alpha_I \: \alpha_J}{((\alpha_I / N_I)^{1/2} + (\alpha_J / N_J)^{1/2})} \: \frac{1}{R_{IJ}^{*^6}} \;\;\;\; (5) \f$<br>
		 *
		 * MMFF employs a "Buffered 14-7" form (eq 1) together with an 
		 * expression which relates the minimum-energy separation \f$ R_{II}^* \f$ to the 
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
		 * \param atom1_pos The position of atom \e i.
		 * \param atom2_pos The position of atom \e j.
		 * \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
		 * \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
		 * \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
		 * \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$.
		 */
		template <typename ValueType, typename CoordsVec>
		ValueType calcMMFF94VanDerWaalsEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, const ValueType& e_IJ, 
											  const ValueType& r_IJ, const ValueType& r_IJ_7);

		/**
		 * \brief Calculates the van der Waals interaction energy \f$ E_{vdW_{ij}} \f$ for the atom pair \e i-j.
		 *
		 * \f$ E_{vdW_{ij}} = \varepsilon_{IJ} \: (\frac{1.07 \: R_{IJ}^*}{(R_{ij} + 0.07 \: R_{IJ}^*)})^7 \: (\frac{1.12 \: R_{IJ}^{*^7}}{(R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})} - 2) \;\;\;\; (1) \f$
		 *
		 * where<br>
		 * \f$ R_{ij} \f$ = the interatomic distance (see calcDistance()).<br>
		 * \f$ R_{II}^* = A_I \: \alpha_I^{PEXP} \;\;\;\; (2) \f$<br>
		 * \f$ R_{IJ}^* = 0.5 \: (R_{II}^* + R_{JJ}^*) \: (1 + AFACT(1 - \exp(-BFACT \: \gamma_{IJ}^2))) \;\;\;\; (3) \f$<br> 
		 * \f$ \gamma_{IJ} = \frac{(R_{II}^* - R_{JJ}^*)}{(R_{II}^* + R_{JJ}^*)} \;\;\;\; (4) \f$ <br>
		 * \f$ \varepsilon_{IJ} = \frac{181.16 \: G_I \: GJ \: \alpha_I \: \alpha_J}{((\alpha_I / N_I)^{1/2} + (\alpha_J / N_J)^{1/2})} \: \frac{1}{R_{IJ}^{*^6}} \;\;\;\; (5) \f$<br>
		 *
		 * MMFF employs a "Buffered 14-7" form (eq 1) together with an 
		 * expression which relates the minimum-energy separation \f$ R_{II}^* \f$ to the 
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
		 * \param r_ij The interatomic distance \f$ R_{ij} \f$ of atom \e i and atom \e j.
		 * \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
		 * \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
		 * \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
		 * \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$.
		 */
		template <typename ValueType>
		ValueType calcMMFF94VanDerWaalsEnergy(const ValueType& r_ij, const ValueType& e_IJ, 
											  const ValueType& r_IJ, const ValueType& r_IJ_7);
    }
}


// Implementation
// \cond DOC_IMPL_DETAILS

namespace CDPL
{

	namespace ForceField
	{

		namespace Detail
		{

			template <typename ValueType, typename Iter, typename CoordsArray, typename FuncType>
			ValueType accumMMFF94InteractionEnergies(Iter& beg, const Iter& end, const CoordsArray& coords, const FuncType& func)
			{
				ValueType e = ValueType();

				for ( ; beg != end; ++beg)
					e += func(*beg, coords);

				return e;
			}	
		}
	}
}


template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94BondStretchingEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94BondStretchingInteraction&, const CoordsArray&)>(
																 &calcMMFF94BondStretchingEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94BondStretchingEnergy(const MMFF94BondStretchingInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94BondStretchingEnergy<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
													 iaction.getForceConstant(), iaction.getReferenceLength());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94BondStretchingEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
														   const ValueType& force_const, const ValueType& ref_length)
{
	ValueType dr_ij = calcDistance<ValueType>(atom1_pos, atom2_pos) - ref_length;
	ValueType dr_ij_2 = dr_ij * dr_ij;
	ValueType e_b = ValueType(143.9325 * 0.5) * force_const * dr_ij_2 * (1 - 2 * dr_ij + 28 * dr_ij_2 / 12);

	return e_b;
}

template <typename ValueType>
ValueType CDPL::ForceField::calcMMFF94BondStretchingEnergy(const ValueType& r_ij, const ValueType& force_const, const ValueType& ref_length)
{
	ValueType dr_ij = r_ij - ref_length;
	ValueType dr_ij_2 = dr_ij * dr_ij;
	ValueType e_b = ValueType(143.9325 * 0.5) * force_const * dr_ij_2 * (1 - 2 * dr_ij + 28 * dr_ij_2 / 12);

	return e_b;
}


template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94AngleBendingEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94AngleBendingInteraction&, const CoordsArray&)>(
																 &calcMMFF94AngleBendingEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94AngleBendingEnergy(const MMFF94AngleBendingInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94AngleBendingEnergy<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
												   coords[iaction.getTerminalAtom2Index()], iaction.isLinearAngle(), iaction.getForceConstant(), 
												   iaction.getReferenceAngle());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94AngleBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														 bool linear, const ValueType& force_const, const ValueType& ref_angle)
{
	if (linear)
		return (ValueType(143.9325) * force_const * (1 + calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos)));
        
	ValueType a_ijk = calcBondAngle<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos) * ValueType(180 / M_PI);
	ValueType da_ijk = a_ijk - ref_angle;
    ValueType e_a = ValueType(0.043844 * 0.5) * force_const * da_ijk * da_ijk * (1 - ValueType(0.007) * da_ijk);

	return e_a;
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94AngleBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														 const ValueType& r_ij, const ValueType& r_jk, 
														 bool linear, const ValueType& force_const, const ValueType& ref_angle)
{
	if (linear)
		return (ValueType(143.9325) * force_const * (1 + calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk)));
        
	ValueType a_ijk = calcBondAngle<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk) * ValueType(180 / M_PI);
	ValueType da_ijk = a_ijk - ref_angle;
    ValueType e_a = ValueType(0.043844 * 0.5) * force_const * da_ijk * da_ijk * (1 - ValueType(0.007) * da_ijk);

	return e_a;
}


template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94StretchBendEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94StretchBendInteraction&, const CoordsArray&)>(
																 &calcMMFF94StretchBendEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94StretchBendEnergy(const MMFF94StretchBendInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94StretchBendEnergy<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
												  coords[iaction.getTerminalAtom2Index()], iaction.getIJKForceConstant(),
												  iaction.getKJIForceConstant(), iaction.getReferenceAngle(), iaction.getReferenceLength1(),
												  iaction.getReferenceLength2());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94StretchBendEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
														const ValueType& ref_length1, const ValueType& ref_length2)
{
	ValueType r_ij = ValueType();
	ValueType r_kj = ValueType();
	ValueType a_ijk = calcBondLengthsAndAngle(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_kj) * ValueType(180 / M_PI);

	ValueType dr_ij = r_ij - ref_length1;
	ValueType dr_kj = r_kj - ref_length2;
	ValueType da_ijk = a_ijk - ref_angle;

	ValueType e_ab = ValueType(2.51210) * (ijk_force_const * dr_ij + kji_force_const * dr_kj) * da_ijk;
   
	return e_ab;
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94StretchBendEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
														const ValueType& r_ij, const ValueType& r_jk, 
														const ValueType& ijk_force_const, const ValueType& kji_force_const, const ValueType& ref_angle, 
														const ValueType& ref_length1, const ValueType& ref_length2)
{
	ValueType a_ijk = calcBondAngle(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk) * ValueType(180 / M_PI);

	ValueType dr_ij = r_ij - ref_length1;
	ValueType dr_kj = r_jk - ref_length2;
	ValueType da_ijk = a_ijk - ref_angle;

	ValueType e_ab = ValueType(2.51210) * (ijk_force_const * dr_ij + kji_force_const * dr_kj) * da_ijk;
   
	return e_ab;
}


template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94OutOfPlaneBendingInteraction&, const CoordsArray&)>(
																 &calcMMFF94OutOfPlaneBendingEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy(const MMFF94OutOfPlaneBendingInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94OutOfPlaneBendingEnergy<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtomIndex()], 
														coords[iaction.getTerminalAtom2Index()], coords[iaction.getOutOfPlaneAtomIndex()],
														iaction.getForceConstant());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
															  const CoordsVec& oop_atom_pos, const ValueType& force_const)
{
	ValueType chi_ijkl = calcOutOfPlaneAngle<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos) * ValueType(180 / M_PI);
	ValueType e_oop = ValueType(0.5 * 0.043844) * force_const * chi_ijkl * chi_ijkl;
   
	return e_oop;
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
															  const CoordsVec& oop_atom_pos, const ValueType& r_jl, const ValueType& force_const)
{
	ValueType chi_ijkl = calcOutOfPlaneAngle<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos, r_jl) * ValueType(180 / M_PI);
	ValueType e_oop = ValueType(0.5 * 0.043844) * force_const * chi_ijkl * chi_ijkl;
   
	return e_oop;
}


template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94TorsionEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords,
															 static_cast<ValueType (*)(const MMFF94TorsionInteraction&, const CoordsArray&)>(
																 &calcMMFF94TorsionEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94TorsionEnergy(const MMFF94TorsionInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94TorsionEnergy<ValueType>(coords[iaction.getTerminalAtom1Index()], coords[iaction.getCenterAtom1Index()], 
											  coords[iaction.getCenterAtom2Index()], coords[iaction.getTerminalAtom2Index()],
											  iaction.getTorsionParameter1(), iaction.getTorsionParameter2(), iaction.getTorsionParameter3());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94TorsionEnergy(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, const CoordsVec& ctr_atom2_pos, 
													const CoordsVec& term_atom2_pos, const ValueType& tor_param1, const ValueType& tor_param2,
													const ValueType& tor_param3)
{
	ValueType phi_cos = calcDihedralAngleCos<ValueType>(term_atom1_pos, ctr_atom1_pos, ctr_atom2_pos, term_atom2_pos); 
	ValueType phi = std::acos(phi_cos);
	ValueType e_t = ValueType(0.5) * (tor_param1 * (1 + phi_cos) + tor_param2 * (1 - std::cos(2 * phi)) + tor_param3 * (1 + std::cos(3 * phi)));

	return e_t;
}

		
template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94ElectrostaticInteraction&, const CoordsArray&)>(
																 &calcMMFF94ElectrostaticEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticEnergy(const MMFF94ElectrostaticInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94ElectrostaticEnergy<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
													iaction.getAtom1Charge(), iaction.getAtom2Charge(), iaction.getScalingFactor(),
													iaction.getDielectricConstant(), iaction.getDistanceExponent());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, const ValueType& atom1_chg,
														  const ValueType& atom2_chg, const ValueType& scale_fact, const ValueType& de_const, 
														  const ValueType& dist_expo)
{
	ValueType tmp = std::pow(calcDistance<ValueType>(atom1_pos, atom2_pos) + ValueType(0.05), dist_expo);
    ValueType e_q = scale_fact * ValueType(332.0716) * atom1_chg * atom2_chg / (de_const * tmp);
    
    return e_q;
}

template <typename ValueType>
ValueType CDPL::ForceField::calcMMFF94ElectrostaticEnergy(const ValueType& r_ij, const ValueType& atom1_chg, const ValueType& atom2_chg, 
														  const ValueType& scale_fact, const ValueType& de_const, const ValueType& dist_expo)
{
	ValueType tmp = std::pow(r_ij + ValueType(0.05), dist_expo);
    ValueType e_q = scale_fact * ValueType(332.0716) * atom1_chg * atom2_chg / (de_const * tmp);
    
    return e_q;
}

	
template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
	return Detail::accumMMFF94InteractionEnergies<ValueType>(beg, end, coords, 
															 static_cast<ValueType (*)(const MMFF94VanDerWaalsInteraction&, const CoordsArray&)>(
																 &calcMMFF94VanDerWaalsEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsEnergy(const MMFF94VanDerWaalsInteraction& iaction, const CoordsArray& coords)
{
	return calcMMFF94VanDerWaalsEnergy<ValueType>(coords[iaction.getAtom1Index()], coords[iaction.getAtom2Index()],
												  iaction.getEIJ(), iaction.getRIJ(), iaction.getRIJPow7());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, const ValueType& e_IJ, 
														const ValueType& r_IJ, const ValueType& r_IJ_7)
{
	ValueType r_ij_2 = calcSquaredDistance<ValueType>(atom1_pos, atom2_pos);
	ValueType r_ij = std::sqrt(r_ij_2);
    ValueType r_ij_7 = r_ij_2 * r_ij_2 * r_ij_2 * r_ij;
    
    ValueType tmp = ValueType(1.07) * r_IJ / (r_ij + ValueType(0.07) * r_IJ);
    ValueType tmp_2 = tmp * tmp;
    ValueType tmp_7 = tmp_2 * tmp_2 * tmp_2 * tmp;

    ValueType e_vdw = e_IJ * tmp_7 * (ValueType(1.12) * r_IJ_7 / (r_ij_7 + ValueType(0.12) * r_IJ_7) - 2);

	return e_vdw;
}

template <typename ValueType>
ValueType CDPL::ForceField::calcMMFF94VanDerWaalsEnergy(const ValueType& r_ij, const ValueType& e_IJ, 
														const ValueType& r_IJ, const ValueType& r_IJ_7)
{
	ValueType r_ij_2 = r_ij * r_ij;
    ValueType r_ij_7 = r_ij_2 * r_ij_2 * r_ij_2 * r_ij;
    
    ValueType tmp = ValueType(1.07) * r_IJ / (r_ij + ValueType(0.07) * r_IJ);
    ValueType tmp_2 = tmp * tmp;
    ValueType tmp_7 = tmp_2 * tmp_2 * tmp_2 * tmp;

    ValueType e_vdw = e_IJ * tmp_7 * (ValueType(1.12) * r_IJ_7 / (r_ij_7 + ValueType(0.12) * r_IJ_7) - 2);

	return e_vdw;
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94ENERGYFUNCTIONS_HPP
