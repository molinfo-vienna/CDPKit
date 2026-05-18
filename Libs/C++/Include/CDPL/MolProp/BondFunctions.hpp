/* 
 * BondFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Bond instances.
 */

#ifndef CDPL_MOLPROP_BONDFUNCTIONS_HPP
#define CDPL_MOLPROP_BONDFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/MolProp/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Bond;
        class MolecularGraph;
    } // namespace Chem

    namespace MolProp
    {

        /**
         * \brief Returns the value of the MolProp::BondProperty::MHMO_PI_ORDER property of \a bond.
         * \param bond The bond.
         * \return The MHMO pi-bond order.
         */
        CDPL_MOLPROP_API double getMHMOPiOrder(const Chem::Bond& bond);

        /**
         * \brief Sets the value of the MolProp::BondProperty::MHMO_PI_ORDER property of \a bond.
         * \param bond The bond.
         * \param order The MHMO pi-bond order.
         */
        CDPL_MOLPROP_API void setMHMOPiOrder(Chem::Bond& bond, double order);

        /**
         * \brief Removes the MolProp::BondProperty::MHMO_PI_ORDER property from \a bond.
         * \param bond The bond.
         */
        CDPL_MOLPROP_API void clearMHMOPiOrder(Chem::Bond& bond);

        /**
         * \brief Tells whether \a bond carries an explicit MolProp::BondProperty::MHMO_PI_ORDER property.
         * \param atom The bond.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool hasMHMOPiOrder(const Chem::Bond& atom);


        /**
         * \brief Calculates the bond polarizability of \a bond within \a molgraph.
         * \param bond The bond.
         * \param molgraph The molecular graph containing \a bond.
         * \param damping The damping factor applied to remote-atom contributions.
         * \return The calculated bond polarizability.
         */
        CDPL_MOLPROP_API double calcPolarizability(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, double damping = 0.75);


        /**
         * \brief Tells whether \a Bond is part of any ring of \a molgraph.
         * \param Bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \return \c true if the bond is part of a ring, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isInRing(const Chem::Bond& Bond, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a bond is part of a ring of the specified size in \a molgraph.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \param size The ring size to test for.
         * \return \c true if the bond is part of a ring of size \a size, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isInRingOfSize(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, std::size_t size);

        /**
         * \brief Returns the number of SSSR rings of \a molgraph that contain \a bond.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \return The number of SSSR rings containing the bond.
         */
        CDPL_MOLPROP_API std::size_t getNumContainingSSSRRings(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);


        /**
         * \brief Tells whether \a bond is a rotatable bond whose rotation only moves hydrogen atoms.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \return \c true if the bond is a hydrogen-only rotor, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHydrogenRotor(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a bond is a hydrogen-only rotor where the rotating end is a heteroatom-bound hydrogen.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \return \c true if the bond is a heteroatom-hydrogen rotor, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHeteroAtomHydrogenRotor(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether \a bond is rotatable.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \param h_rotors If \c true, hydrogen-only rotors are counted as rotatable.
         * \param ring_bonds If \c true, ring bonds are also considered.
         * \param amide_bonds If \c true, amide bonds are also considered.
         * \return \c true if the bond is rotatable, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isRotatable(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);

        /**
         * \brief Tells whether \a bond is a hydrogen bond (one of the bonded atoms is a hydrogen).
         * \param bond The bond.
         * \return \c true if the bond involves a hydrogen, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isHydrogenBond(const Chem::Bond& bond);

        /**
         * \brief Tells whether \a bond is an amide bond in \a molgraph.
         * \param bond The bond.
         * \param molgraph The molecular graph containing the bond.
         * \param c_only If \c true, only C(=O)N bonds are recognized (more restrictive).
         * \param db_o_only If \c true, the C=O must be a double bond to oxygen specifically.
         * \return \c true if the bond is an amide bond under the given criteria, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool isAmideBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_BONDFUNCTIONS_HPP
