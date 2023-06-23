/* 
 * UtilityFunctions.hpp 
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
 * \brief Utility functions used in the calculation of force field energies and gradients.
 */

#ifndef CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP
#define CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP

#include <cmath>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

        class MMFF94InteractionData;

        CDPL_FORCEFIELD_API void filterInteractions(const MMFF94InteractionData& ia_data, MMFF94InteractionData& filtered_ia_data, const Util::BitSet& inc_atom_mask);

        /**
         *\brief Calculates the squared distance \f$ r_{ij}^2 \f$ between two atoms \e i and \e j.
         *
         * \f$ r_{ij}^2 = |\vec{v_{ij}}|^2 \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         *
         * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
         * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
         * \return The calculated squared distance \f$ r_{ij}^2 \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcSquaredDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos);

        /**
         * \brief Calculates the distance \f$ r_{ij} \f$ between two atoms \e i and \e j.
         *
         * \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         *
         * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
         * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
         * \return The calculated distance \f$ r_{ij} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcDistance(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos);

        /**
         * \brief Calculates bond lengths \f$ r_{ij} \f$ and \f$ r_{jk} \f$ and the \e cosine of the bond angle
         *        \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
         * \f$ r_{jk} = |\vec{v_{jk}}| \f$<br>
         * \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{r_{ij} \: r_{jk}} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param bond_length1 Output variable for the bond length \f$ r_{ij} \f$.
         * \param bond_length2 Output variable for the bond length \f$ r_{jk} \f$.
         * \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondLengthsAndAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
                                             ValueType& bond_length1, ValueType& bond_length2);

        /**
         * \brief Calculates bond lengths \f$ r_{ij} \f$ and \f$ r_{jk} \f$ and the bond angle
         *        \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
         * \f$ r_{jk} = |\vec{v_{jk}}| \f$<br>
         * \f$ \vartheta_{ijk} = \arccos(\frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{r_{ij} \: r_{jk}}) \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param bond_length1 Output variable for the bond length \f$ r_{ij} \f$.
         * \param bond_length2 Output variable for the bond length \f$ r_{jk} \f$.
         * \return The calculated bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondLengthsAndAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos, 
                                          ValueType& bond_length1, ValueType& bond_length2);
    
        /**
         * \brief Calculates the \e cosine of the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos);

        /**
         * \brief Calculates the \e cosine of the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param r_ij The length of the bond between atom \e i and \e j.
         * \param r_jk The length of the bond between atom \e j and \e k.
         * \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                   const ValueType& r_ij, const ValueType& r_jk);

        /**
         * \brief Calculates the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ \vartheta_{ijk} = \arccos(\frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|}) \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \return The calculated bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos);

        /**
         * \brief Calculates the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds \e i-j and \e j-k.
         *
         * \f$ \vartheta_{ijk} = \arccos(\frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|}) \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param r_ij The length of the bond between atom \e i and \e j.
         * \param r_jk The length of the bond between atom \e j and \e k.
         * \return The calculated bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                const ValueType& r_ij, const ValueType& r_jk);
    
        /**
         * \brief Calculates the out-of-plane angle \f$ \chi_{ijk;l} \f$ between the bond \e j-l and the plane defined by the atoms \e i-j-k.
         *
         * \f$ \chi_{ijk;l} = \frac{\pi}{2} - \arccos(\frac{\vec{n_{ijk}} \cdot \vec{v_{jl}}}{|\vec{n_{ijk}}| \: |\vec{v_{jl}}|}) \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jl}} = \vec{p_l} - \vec{p_j} \f$<br>
         * \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         * \f$ \vec{p_l} \f$ = coordinates of atom \e l.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom \e l.
         * \return The calculated out-of-plane angle \f$ \chi_{ijk;l} \f$.
         */
        template <typename ValueType, typename CoordsVec>    
        ValueType calcOutOfPlaneAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
                                      const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos);

        /**
         * \brief Calculates the out-of-plane angle \f$ \chi_{ijk;l} \f$ between the bond \e j-l and the plane defined by the atoms \e i-j-k.
         *
         * \f$ \chi_{ijk;l} = \frac{\pi}{2} - \arccos(\frac{\vec{n_{ijk}} \cdot \vec{v_{jl}}}{|\vec{n_{ijk}}| \: |\vec{v_{jl}}|}) \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jl}} = \vec{p_l} - \vec{p_j} \f$<br>
         * \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         * \f$ \vec{p_l} \f$ = coordinates of atom \e l.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom \e l.
         * \param r_jl The length of the bond between atom \e j and atom \e l.
         * \return The calculated out-of-plane angle \f$ \chi_{ijk;l} \f$.
         */
        template <typename ValueType, typename CoordsVec>    
        ValueType calcOutOfPlaneAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
                                      const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos,
                                      const ValueType& r_jl);

        /**
         * \brief Calculates the \e cosine of the dihedral angle \f$ \Phi_{ijkl} \f$ between the planes defined by the atom triplets \e i-j-k and \e j-k-l.
         *
         * \f$ \cos(\Phi_{ijkl}) = \frac{\vec{n_{ijk}} \cdot \vec{n_{jkl}}}{|\vec{n_{ijk}}| \: |\vec{n_{jkl}}|} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{lk}} = \vec{p_k} - \vec{p_l} \f$<br>
         * \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
         * \f$ \vec{n_{jkl}} = \vec{v_{jk}} \times \vec{v_{lk}} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         * \f$ \vec{p_l} \f$ = coordinates of atom \e l.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom \e k.
         * \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom \e l.
         * \return The calculated cosine of the dihedral angle \f$ \Phi_{ijkl} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcDihedralAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
                                       const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos);
    
        /**
         * \brief Calculates the partial derivatives \f$ \frac{\partial r_{ij}}{\partial \vec{p_x}} \f$ of the 
         *        distance \f$ r_{ij} \f$ between two atoms \e i and \e j.
         *
         * \f$ \frac{\partial r_{ij}}{\partial \vec{p_i}} = \frac{-\vec{v_{ij}}}{r_{ij}} \f$<br>
         * \f$ \frac{\partial r_{ij}}{\partial \vec{p_j}} = \frac{\vec{v_{ij}}}{r_{ij}} \f$<br>
         * \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         *
         * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
         * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
         * \param atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial r_{ij}}{\partial \vec{p_i}} \f$ 
         *                    at the given atom positions.
         * \param atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial r_{ij}}{\partial \vec{p_j}} \f$ 
         *                    at the given atom positions.
         * \return The calculated distance \f$ r_{ij} \f$.
         */
        template <typename ValueType, typename CoordsVec, typename GradVec>
        ValueType calcDistanceDerivatives(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
                                          GradVec& atom1_deriv, GradVec& atom2_deriv);

        /**
         * \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_x}} \f$ of the 
         *        of the \e cosine of the angle \f$ \vartheta_{ijk} \f$ between the bonds \e i-j and \e j-k.
         *
         * \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} = \frac{\vec{v_{jk}}}{r_{ji} \: r_{jk}} - \frac{\vec{v_{ji}} \: (\vec{v_{ji}} \cdot \vec{v_{jk}})}{r_{ji}^3 \: r_{jk}} \f$<br>
         * \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}} = \frac{\vec{v_{ji}}}{r_{ji} \: r_{jk}} - \frac{\vec{v_{jk}} \: (\vec{v_{ji}} \cdot \vec{v_{jk}})}{r_{ji} \: r_{jk}^3} \f$<br>
         * \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_j}} = -(\frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} + \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}}) \f$<br>
         * \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{r_{ij} \: r_{jk}} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ r_{ji} = |\vec{v_{ji}}| \f$<br>
         * \f$ r_{jk} = |\vec{v_{jk}}| \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom \e k.
         * \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} \f$ 
         *                         at the given atom positions.
         * \param ctr_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_j}} \f$ 
         *                       at the given atom positions.
         * \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}} \f$ 
         *                         at the given atom positions.
         * \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
         */
        template <typename ValueType, typename CoordsVec, typename GradVec>
        ValueType calcBondAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                              GradVec& term_atom1_deriv, GradVec& ctr_atom_deriv, GradVec& term_atom2_deriv);

        /**
         * \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$ of the \e cosine
         *        of the angle \f$ \Phi_{ijkl} \f$ between the planes defined by the atom triplets \e i-j-k and \e j-k-l.
         *
         * \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} = \vec{v_{jk}} \times \vec{a} \f$<br>  
         * \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} = \vec{r_{ki}} \times \vec{a} - \vec{v_{lk}} \times \vec{b} \f$<br>
         * \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}} = \vec{v_{jk}} \times \vec{b} \f$<br>
         * \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_k}} = -(\frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} +
         *                                                              \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} +
         *                                                              \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}}) \f$<br>
         * \f$ \cos(\Phi_{ijkl}) = \frac{\vec{n_{ijk}} \cdot \vec{n_{jkl}}}{|\vec{n_{ijk}}| \: |\vec{n_{jkl}}|} \f$<br>
         *
         * where<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{lk}} = \vec{p_k} - \vec{p_l} \f$<br>
         * \f$ \vec{r_{ki}} = \vec{p_i} - \vec{p_k} \f$<br>
         * \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
         * \f$ \vec{n_{jkl}} = \vec{v_{jk}} \times \vec{v_{lk}} \f$<br>
         * \f$ \vec{a} = \frac{\frac{\vec{n_{jkl}}}{|\vec{n_{jkl}}|} - \cos(\Phi_{ijkl}) \: \frac{\vec{n_{ijk}}}{|\vec{n_{ijk}}|}}{|\vec{n_{ijk}}|} \f$<br> 
         * \f$ \vec{b} = \frac{\frac{\vec{n_{ijk}}}{|\vec{n_{ijk}}|} - \cos(\Phi_{ijkl}) \: \frac{\vec{n_{jkl}}}{|\vec{n_{jkl}}|}}{|\vec{n_{jkl}}|} \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         * \f$ \vec{p_l} \f$ = coordinates of atom \e l.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom \e k.
         * \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom \e l.
         * \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} \f$ 
         *                         at the given atom positions.
         * \param ctr_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} \f$ 
         *                       at the given atom positions.
         * \param ctr_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_k}} \f$ 
         *                       at the given atom positions.
         * \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}} \f$ 
         *                         at the given atom positions.
         * \return The calculated cosine of the dihedral angle \f$ \Phi_{ijkl} \f$.
         */
        template <typename ValueType, typename CoordsVec, typename GradVec>
        ValueType calcDihedralAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
                                                  const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos,
                                                  GradVec& term_atom1_deriv, GradVec& ctr_atom1_deriv, 
                                                  GradVec& ctr_atom2_deriv, GradVec& term_atom2_deriv);

        /**
         * \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_x}} \f$ of the \e cosine
         *        of the angle \f$ \omega_{ijk;l} \f$ between the bond \e j-l and the normal of the plane defined by the atoms \e i-j-k.
         *
         * 
         * \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_i}} = \frac{\vec{v_{jk}} \times \vec{v_{jl}}}{|\vec{n_{ijk}}| \: r_{jl}} -
         *                                                                \cos(\omega_{ijk;l}) \: \frac{M_1 \cdot \vec{n_{ijk}}}{|\vec{n_{ijk}}|^2} \f$<br>
         * \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_k}} = \frac{\vec{v_{jl}} \times \vec{v_{ji}}}{|\vec{n_{ijk}}| \: r_{jl}} - 
         *                                                                \cos(\omega_{ijk;l}) \: \frac{M_2 \cdot \vec{n_{ijk}}}{|\vec{n_{ijk}}|^2} \f$<br>
         * \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_l}} = \frac{-1}{|\vec{n_{ijk}}| \: r_{jl}} \: (\frac{\vec{v_{jl}} (\vec{n_{ijk}} \cdot \vec{v_{jl}})}{r_{jl}^2} +
         *                                                                \vec{r_{kl}} \times \vec{v_{il}} + \vec{v_{jl}} \times \vec{v_{ji}} + 
         *                                                                \vec{v_{jk}} \times \vec{v_{jl}}) \f$<br>
         * \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_j}} = -(\frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_i}} + 
         *                                                                 \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_k}} +
         *                                                                 \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_l}}) \f$<br>
         * \f$ \cos(\omega_{ijk;l}) = \frac{\vec{n_{ijk}} \cdot \vec{v_{jl}}}{|\vec{n_{ijk}}| \: r_{jl}} \f$<br>
         *
         * where<br>
         * \f$ M_1 = 
         *   \left|
         *      \begin{array}{ccc}
         *       0 & -\vec{v_{jk}}.z & \vec{v_{jk}}.y \\
         *       \vec{v_{jk}}.z & 0 & -\vec{v_{jk}}.x \\
         *       -\vec{v_{jk}}.y & \vec{v_{jk}}.x & 0
         *      \end{array}
         *   \right| \f$<br>
         * \f$ M_2 = 
         *   \left| 
         *      \begin{array}{ccc}
         *       0 & \vec{v_{ji}}.z & -\vec{v_{ji}}.y \\
         *       -\vec{v_{ji}}.z & 0 & \vec{v_{ji}}.x \\
         *        \vec{v_{ji}}.y & -\vec{v_{ji}}.x & 0
         *      \end{array}
         *   \right| \f$<br>
         * \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
         * \f$ \vec{v_{jl}} = \vec{p_l} - \vec{p_j} \f$<br>
         * \f$ \vec{r_{kl}} = \vec{p_l} - \vec{p_k} \f$<br>
         * \f$ \vec{v_{il}} = \vec{p_l} - \vec{p_i} \f$<br>
         * \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
         * \f$ r_{jl} = |\vec{v_{jl}}| \f$<br>
         *
         * \f$ \vec{p_i} \f$ = coordinates of atom \e i.<br>
         * \f$ \vec{p_j} \f$ = coordinates of atom \e j.<br>
         * \f$ \vec{p_k} \f$ = coordinates of atom \e k.<br>
         * \f$ \vec{p_l} \f$ = coordinates of atom \e l.<br>
         *
         * \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom \e i.
         * \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom \e j.
         * \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom \e k.
         * \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom \e l.
         * \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_i}} \f$ 
         *                         at the given atom positions.
         * \param ctr_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_j}} \f$ 
         *                       at the given atom positions.
         * \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_k}} \f$ 
         *                       at the given atom positions.
         * \param oop_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_l}} \f$ 
         *                         at the given atom positions.
         * \return The calculated cosine of the angle \f$ \omega_{ijk;l} \f$.
         */
        template <typename ValueType, typename CoordsVec, typename GradVec>
        ValueType calcOutOfPlaneAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
                                                    const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos,
                                                    GradVec& term_atom1_deriv, GradVec& ctr_atom_deriv, 
                                                    GradVec& term_atom2_deriv, GradVec& oop_atom_deriv);
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

            template <typename VecType1, typename VecType2, typename VecType3>
            void addVectors(const VecType1& vec1, const VecType2& vec2, VecType3& res)
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
ValueType CDPL::ForceField::calcBondAngleCos(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                             const ValueType& r_ij, const ValueType& r_jk)
{
    ValueType bond_vec1[3];
    ValueType bond_vec2[3];

    Detail::subVectors(ctr_atom_pos, term_atom1_pos, bond_vec1);
    Detail::subVectors(ctr_atom_pos, term_atom2_pos, bond_vec2);

    return Detail::clampCosine(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec2) / (r_ij * r_jk));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos)
{
    return std::acos(calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos));
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcBondAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                          const ValueType& r_ij, const ValueType& r_jk)
{
    return std::acos(calcBondAngleCos<ValueType>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk));
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
ValueType CDPL::ForceField::calcOutOfPlaneAngle(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
                                                const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos, 
                                                const ValueType& r_jl)
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
    ValueType ang_cos = Detail::clampCosine(Detail::calcDotProduct<ValueType>(plane_normal, oop_bond_vec) / (pn_len * r_jl));

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
ValueType CDPL::ForceField::calcDistanceDerivatives(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
                                                    GradVec& atom1_deriv, GradVec& atom2_deriv)
{
    Detail::subVectors(atom1_pos, atom2_pos, atom1_deriv);

    ValueType dist = std::sqrt(Detail::calcDotProduct<ValueType>(atom1_deriv, atom1_deriv));

    Detail::invScaleVector(atom1_deriv, -dist);
    Detail::negateCopyVector(atom1_deriv, atom2_deriv);

    return dist;
}
    
template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcBondAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, const CoordsVec& term_atom2_pos,
                                                        GradVec& term_atom1_deriv, GradVec& ctr_atom_deriv, GradVec& term_atom2_deriv)
{
    ValueType bond_vec1[3];
    ValueType bond_vec2[3];

    Detail::subVectors(ctr_atom_pos, term_atom1_pos, bond_vec1);
    Detail::subVectors(ctr_atom_pos, term_atom2_pos, bond_vec2);

    ValueType bond_length1 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec1));
    ValueType bond_length2 = std::sqrt(Detail::calcDotProduct<ValueType>(bond_vec2, bond_vec2));

    ValueType dot_prod = Detail::calcDotProduct<ValueType>(bond_vec1, bond_vec2);
    ValueType bl_prod = bond_length1 * bond_length2;

    Detail::invScaleCopyVector(bond_vec2, bl_prod, term_atom1_deriv);
    Detail::scaleCopyVector(bond_vec1, dot_prod / (bond_length1 * bond_length1 * bl_prod), ctr_atom_deriv);
    Detail::subVectors(ctr_atom_deriv, term_atom1_deriv, term_atom1_deriv);

    Detail::invScaleCopyVector(bond_vec1, bl_prod, term_atom2_deriv);
    Detail::scaleCopyVector(bond_vec2, dot_prod / (bond_length2 * bond_length2 * bl_prod), ctr_atom_deriv);
    Detail::subVectors(ctr_atom_deriv, term_atom2_deriv, term_atom2_deriv);

    Detail::negateCopyVector(term_atom1_deriv, ctr_atom_deriv);
    Detail::subVectors(term_atom2_deriv, ctr_atom_deriv, ctr_atom_deriv);

    return Detail::clampCosine(dot_prod / bl_prod);
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcDihedralAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom1_pos, 
                                                            const CoordsVec& ctr_atom2_pos, const CoordsVec& term_atom2_pos,
                                                            GradVec& term_atom1_deriv, GradVec& ctr_atom1_deriv, 
                                                            GradVec& ctr_atom2_deriv, GradVec& term_atom2_deriv)
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

    Detail::calcCrossProduct(ctr_bond_vec, a, term_atom1_deriv);
    Detail::calcCrossProduct(ctr_bond_vec, b, term_atom2_deriv);

    Detail::calcCrossProduct(term1_ctr2_vec, a, ctr_atom1_deriv);
    Detail::calcCrossProduct(term_bond2_vec, b, ctr_atom2_deriv);

    Detail::subVectors(ctr_atom2_deriv, ctr_atom1_deriv, ctr_atom1_deriv);

    Detail::addVectors(term_atom1_deriv, ctr_atom1_deriv, ctr_atom2_deriv);
    Detail::addVectors(ctr_atom2_deriv, term_atom2_deriv, ctr_atom2_deriv);
    Detail::negateVector(ctr_atom2_deriv);

    return ang_cos;
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcOutOfPlaneAngleCosDerivatives(const CoordsVec& term_atom1_pos, const CoordsVec& ctr_atom_pos, 
                                                              const CoordsVec& term_atom2_pos, const CoordsVec& oop_atom_pos,
                                                              GradVec& term_atom1_deriv, GradVec& ctr_atom_deriv, 
                                                              GradVec& term_atom2_deriv, GradVec& oop_atom_deriv)
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

    ctr_atom_deriv[0] = ijk_pn[1] * -term_bond2_vec[2] + ijk_pn[2] * term_bond2_vec[1];
    ctr_atom_deriv[1] = ijk_pn[0] * term_bond2_vec[2] + ijk_pn[2] * -term_bond2_vec[0];
    ctr_atom_deriv[2] = ijk_pn[0] * -term_bond2_vec[1] + ijk_pn[1] * term_bond2_vec[0];

    Detail::scaleVector(ctr_atom_deriv, ang_cos / ijk_pn_len_2);

    Detail::invScaleCopyVector(kjl_pn, oop_ijk_pn_len_prod, term_atom1_deriv);
    Detail::subVectors(ctr_atom_deriv, term_atom1_deriv, term_atom1_deriv);

    ctr_atom_deriv[0] = ijk_pn[1] * term_bond1_vec[2] + ijk_pn[2] * -term_bond1_vec[1];
    ctr_atom_deriv[1] = ijk_pn[0] * -term_bond1_vec[2] + ijk_pn[2] * term_bond1_vec[0];
    ctr_atom_deriv[2] = ijk_pn[0] * term_bond1_vec[1] + ijk_pn[1] * -term_bond1_vec[0];

    Detail::scaleVector(ctr_atom_deriv, ang_cos / ijk_pn_len_2);

    Detail::invScaleCopyVector(lji_pn, oop_ijk_pn_len_prod, term_atom2_deriv);
    Detail::subVectors(ctr_atom_deriv, term_atom2_deriv, term_atom2_deriv);

    Detail::calcCrossProduct(term2_oop_vec, term1_oop_vec, ctr_atom_deriv);

    Detail::scaleCopyVector(oop_bond_vec, oop_ijk_pn_dot_prod / (oop_bnd_len * oop_bnd_len), oop_atom_deriv);
    Detail::addVectors(oop_atom_deriv, lji_pn, oop_atom_deriv);
    Detail::addVectors(oop_atom_deriv, kjl_pn, oop_atom_deriv);
    Detail::addVectors(oop_atom_deriv, ctr_atom_deriv, oop_atom_deriv);
    Detail::invScaleVector(oop_atom_deriv, -oop_ijk_pn_len_prod);
    
    Detail::copyVector(term_atom1_deriv, ctr_atom_deriv);
    Detail::addVectors(term_atom2_deriv, ctr_atom_deriv, ctr_atom_deriv);
    Detail::addVectors(oop_atom_deriv, ctr_atom_deriv, ctr_atom_deriv);
    Detail::negateVector(ctr_atom_deriv);

    return ang_cos;
}

// \endcond

#endif // CDPL_FORCEFIELD_UTILITYFUNCTIONS_HPP
