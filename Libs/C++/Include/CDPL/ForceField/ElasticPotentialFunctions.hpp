/* 
 * ElasticPotentialFunctions.hpp 
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
 * \brief Functions for the calculation of force fieldelastic potential energies and gradients.
 */

#ifndef CDPL_FORCEFIELD_ELASTICPOTENTIALFUNCTIONS_HPP
#define CDPL_FORCEFIELD_ELASTICPOTENTIALFUNCTIONS_HPP

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/ElasticPotential.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace ForceField
    {

        template <typename ValueType, typename Iter, typename CoordsArray>
        ValueType calcElasticPotentialEnergy(Iter beg, const Iter& end, const CoordsArray& coords);

        template <typename ValueType, typename CoordsArray>
        ValueType calcElasticPotentialEnergy(const ElasticPotential& pot, const CoordsArray& coords);

        /**
         * \brief Calculates the energy \f$ E_{ij} \f$ of an elastic potential applied on a pair of atoms \e i-j.
         * 
         * \f$ E_{ij} = \frac{k_{ij}}{2} \: \Delta r_{ij}^2 \f$
         *
         * where<br>
         * \f$ k_{ij} \f$ = the force constant of the elastic potential.<br>
         * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{ij}^0 \f$, the difference between actual and
         *                         reference distance of the atoms \e i and \e j.<br>
         * 
         * \param atom1_pos The position of atom \e i.
         * \param atom2_pos The position of atom \e j.
         * \param force_const The force constant \f$ k_{ij} \f$.
         * \param ref_length The reference distance \f$ r_{ij}^0 \f$.
         * \return The calculated elastic potential energy \f$ E_{ij} \f$.
         */
        template <typename ValueType, typename CoordsVec>
        ValueType calcElasticPotentialEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
                                             const ValueType& force_const, const ValueType& ref_length);

        template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
        ValueType calcElasticPotentialGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad);

        template <typename ValueType, typename CoordsArray, typename GradVector>
        ValueType calcElasticPotentialGradient(const ElasticPotential& pot, const CoordsArray& coords, GradVector& grad);

        /**
         * \brief Calculates the elastic potential energy gradient \f$ \nabla E_{ij} \f$ for a pair of atoms \e i-j.
         * 
         * Energy function:<br>
         *
         * \f$ E_{ij} = \frac{k_{ij}}{2} \: \Delta r_{ij}^2 \f$
         *
         * The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
         *
         * \f$ \frac{\partial E_{ij}}{\partial \vec{p_x}} = \frac{\partial E_{ij}}{\partial \Delta r_{ij}} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$<br>
         *
         * \f$ \frac{\partial E_{ij}}{\partial \Delta r_{ij}} = \Delta r_{ij} \: k_{ij} \f$<br>
         *
         * for the calculation of the partial derivatives \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
         *
         * where<br>
         * \f$ k_{ij} \f$ = the force constant of the elastic potential.<br>
         * \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{ij}^0 \f$, the difference between actual and
         *                         reference distance of the atoms \e i and \e j.<br>
         * \f$ \vec{p_x} \f$ = coordinates of the atoms \e i and \e j.<br>
         * 
         * \param atom1_pos The position \f$ \vec{p_i} \f$ of atom \e i.
         * \param atom2_pos The position \f$ \vec{p_j} \f$ of atom \e j.
         * \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom \e i.
         * \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom \e j.
         * \param force_const The force constant \f$ k_{ij} \f$.
         * \param ref_length The reference distance \f$ r_{ij}^0 \f$.
         * \return The calculated elastic potential energy \f$ E_{ij} \f$.
         * \note The calculated partial energy derivative (see above) for an atom gets \e added to the
         *       corresponding output variable!
         */
        template <typename ValueType, typename CoordsVec, typename GradVec>
        ValueType calcElasticPotentialGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, GradVec& atom2_grad,
                                               const ValueType& force_const, const ValueType& ref_length);
    } // namespace ForceField
} // namespace CDPL


// Implementation
// \cond DOC_IMPL_DETAILS

template <typename ValueType, typename Iter, typename CoordsArray>
ValueType CDPL::ForceField::calcElasticPotentialEnergy(Iter beg, const Iter& end, const CoordsArray& coords)
{
    return Detail::accumInteractionEnergies<ValueType>(beg, end, coords,
                                                       static_cast<ValueType (*)(const ElasticPotential&, const CoordsArray&)>(
                                                           &calcElasticPotentialEnergy<ValueType, CoordsArray>));
}

template <typename ValueType, typename CoordsArray>
ValueType CDPL::ForceField::calcElasticPotentialEnergy(const ElasticPotential& pot, const CoordsArray& coords)
{
    return calcElasticPotentialEnergy<ValueType>(coords[pot.getAtom1Index()], coords[pot.getAtom2Index()],
                                                 pot.getForceConstant(), pot.getReferenceLength());
}

template <typename ValueType, typename CoordsVec>
ValueType CDPL::ForceField::calcElasticPotentialEnergy(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos,
                                                       const ValueType& force_const, const ValueType& ref_length)
{
    ValueType dr_ij   = calcDistance<ValueType>(atom1_pos, atom2_pos) - ref_length;
    ValueType dr_ij_2 = dr_ij * dr_ij;
    ValueType e       = ValueType(10.5) * force_const * dr_ij_2;

    return e;
}


template <typename ValueType, typename Iter, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcElasticPotentialGradient(Iter beg, const Iter& end, const CoordsArray& coords, GradVector& grad)
{
    return Detail::calcInteractionGradient<ValueType>(beg, end, coords, grad,
                                                      static_cast<ValueType (*)(const ElasticPotential&, const CoordsArray&, GradVector&)>(
                                                          &calcElasticPotentialGradient<ValueType, CoordsArray, GradVector>));
}

template <typename ValueType, typename CoordsArray, typename GradVector>
ValueType CDPL::ForceField::calcElasticPotentialGradient(const ElasticPotential& pot, const CoordsArray& coords, GradVector& grad)
{
    return calcElasticPotentialGradient<ValueType>(coords[pot.getAtom1Index()], coords[pot.getAtom2Index()], grad[pot.getAtom1Index()],
                                                   grad[pot.getAtom2Index()], pot.getForceConstant(), pot.getReferenceLength());
}

template <typename ValueType, typename CoordsVec, typename GradVec>
ValueType CDPL::ForceField::calcElasticPotentialGradient(const CoordsVec& atom1_pos, const CoordsVec& atom2_pos, GradVec& atom1_grad, GradVec& atom2_grad,
                                                         const ValueType& force_const, const ValueType& ref_length)
{
    ValueType dist_atom1_grad[3];
    ValueType dist_atom2_grad[3];

    ValueType dr_ij = calcDistanceDerivatives<ValueType>(atom1_pos, atom2_pos, dist_atom1_grad, dist_atom2_grad) - ref_length;
    ValueType grad_fact = force_const * dr_ij;
    
    Detail::scaleAddVector(dist_atom1_grad, grad_fact, atom1_grad);
    Detail::scaleAddVector(dist_atom2_grad, grad_fact, atom2_grad);

    ValueType e = ValueType(0.5) * grad_fact * dr_ij;

    return e;
}

// \endcond

#endif // CDPL_FORCEFIELD_ELASTICPOTENTIALENERGYFUNCTIONS_HPP
