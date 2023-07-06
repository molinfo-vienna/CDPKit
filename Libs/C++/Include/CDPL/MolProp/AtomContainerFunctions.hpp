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

        CDPL_MOLPROP_API double calcExplicitMass(const Chem::AtomContainer& cntnr);

        CDPL_MOLPROP_API void calcExplicitMassComposition(const Chem::AtomContainer& cntnr, MassComposition& mass_comp);

        CDPL_MOLPROP_API void generateExplicitMassCompositionString(const Chem::AtomContainer& cntnr, std::string& comp_str);

        CDPL_MOLPROP_API void generateExplicitMolecularFormula(const Chem::AtomContainer& cntnr, std::string& formula);

        CDPL_MOLPROP_API void generateExplicitElementHistogram(const Chem::AtomContainer& cntnr, ElementHistogram& hist, bool append = false);


        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::AtomContainer& cntnr);

        CDPL_MOLPROP_API std::size_t getExplicitAtomCount(const Chem::AtomContainer& cntnr, unsigned int type, bool strict = true);

        CDPL_MOLPROP_API std::size_t getExplicitChainAtomCount(const Chem::AtomContainer& cntnr);

        CDPL_MOLPROP_API std::size_t getRingAtomCount(const Chem::AtomContainer& cntnr);

        CDPL_MOLPROP_API std::size_t getAromaticAtomCount(const Chem::AtomContainer& cntnr);

        CDPL_MOLPROP_API std::size_t getHeavyAtomCount(const Chem::AtomContainer& cntnr);


        CDPL_MOLPROP_API long getNetFormalCharge(const Chem::AtomContainer& cntnr);


        CDPL_MOLPROP_API bool calcDipoleMoment(const Chem::AtomContainer& cntnr, const Chem::Atom3DCoordinatesFunction& coords_func, Math::Vector3D& moment);

        CDPL_MOLPROP_API bool calcDipoleMoment(const Chem::AtomContainer& cntnr, Math::Vector3D& moment);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP
