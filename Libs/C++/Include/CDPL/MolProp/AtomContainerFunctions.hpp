/* 
 * AtomContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::AtomContainer instances.
 */

#ifndef CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP
#define CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP

#include <string>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/MolProp/MassComposition.hpp"
#include "CDPL/MolProp/ElementHistogram.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"


namespace CDPL
{

    namespace Chem
    {

        class AtomContainer;
    }

    namespace MolProp
    {

        /**
         * \brief Calculates the total mass of the explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The total explicit mass.
         */
        CDPL_MOLPROP_API double calcExplicitMass(const Chem::AtomContainer& cntnr);

        /**
         * \brief Calculates the per-element mass composition of the explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \param mass_comp The output mass composition.
         */
        CDPL_MOLPROP_API void calcExplicitMassComposition(const Chem::AtomContainer& cntnr, MassComposition& mass_comp);

        /**
         * \brief Generates a string representation of the per-element mass composition of the explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \param comp_str The output mass composition string.
         */
        CDPL_MOLPROP_API void generateExplicitMassCompositionString(const Chem::AtomContainer& cntnr, std::string& comp_str);

        /**
         * \brief Generates the molecular formula of the explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \param formula The output molecular formula string.
         */
        CDPL_MOLPROP_API void generateExplicitMolecularFormula(const Chem::AtomContainer& cntnr, std::string& formula);

        /**
         * \brief Generates the element histogram of the explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \param hist The output element histogram.
         * \param append If \c true, \a hist is appended to instead of cleared first.
         */
        CDPL_MOLPROP_API void generateExplicitElementHistogram(const Chem::AtomContainer& cntnr, ElementHistogram& hist, bool append = false);


        /**
         * \brief Returns the total number of explicit atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The number of explicit atoms.
         */
        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::AtomContainer& cntnr);

        /**
         * \brief Returns the number of explicit atoms in \a cntnr that match the given atom type.
         * \param cntnr The atom container.
         * \param type The atom type to match (see namespace Chem::AtomType).
         * \param strict If \c true, atoms must match the type strictly. Otherwise, generic-type matching applies.
         * \return The number of matching explicit atoms.
         */
        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::AtomContainer& cntnr, unsigned int type, bool strict = true);

        /**
         * \brief Returns the number of explicit chain (non-ring) atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The number of chain atoms.
         */
        CDPL_MOLPROP_API std::size_t getExplicitChainAtomCount(const Chem::AtomContainer& cntnr);

        /**
         * \brief Returns the number of ring atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The number of ring atoms.
         */
        CDPL_MOLPROP_API std::size_t getRingAtomCount(const Chem::AtomContainer& cntnr);

        /**
         * \brief Returns the number of aromatic atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The number of aromatic atoms.
         */
        CDPL_MOLPROP_API std::size_t getAromaticAtomCount(const Chem::AtomContainer& cntnr);

        /**
         * \brief Returns the number of heavy (non-hydrogen) atoms in \a cntnr.
         * \param cntnr The atom container.
         * \return The number of heavy atoms.
         */
        CDPL_MOLPROP_API std::size_t getHeavyAtomCount(const Chem::AtomContainer& cntnr);


        /**
         * \brief Returns the net formal charge of \a cntnr (sum of per-atom formal charges).
         * \param cntnr The atom container.
         * \return The net formal charge.
         */
        CDPL_MOLPROP_API long getNetFormalCharge(const Chem::AtomContainer& cntnr);


        /**
         * \brief Calculates the dipole moment of \a cntnr using the supplied atom 3D-coordinates function.
         * \param cntnr The atom container.
         * \param coords_func The function used to retrieve atom 3D-coordinates.
         * \param moment The output dipole-moment vector.
         * \return \c true if the dipole moment could be calculated, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool calcDipoleMoment(const Chem::AtomContainer& cntnr, const Chem::Atom3DCoordinatesFunction& coords_func, Math::Vector3D& moment);

        /**
         * \brief Calculates the dipole moment of \a cntnr using the standard atom 3D-coordinates accessor.
         * \param cntnr The atom container.
         * \param moment The output dipole-moment vector.
         * \return \c true if the dipole moment could be calculated, and \c false otherwise.
         */
        CDPL_MOLPROP_API bool calcDipoleMoment(const Chem::AtomContainer& cntnr, Math::Vector3D& moment);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP
