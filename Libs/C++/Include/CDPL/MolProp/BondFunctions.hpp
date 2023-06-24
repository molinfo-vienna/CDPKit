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

        CDPL_MOLPROP_API double getMHMOPiOrder(const Chem::Bond& bond);

        CDPL_MOLPROP_API void setMHMOPiOrder(Chem::Bond& bond, double order);

        CDPL_MOLPROP_API void clearMHMOPiOrder(Chem::Bond& bond);

        CDPL_MOLPROP_API bool hasMHMOPiOrder(const Chem::Bond& atom);


        CDPL_MOLPROP_API double calcPolarizability(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, double damping = 0.75);


        CDPL_MOLPROP_API bool isInRing(const Chem::Bond& Bond, const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API bool isInRingOfSize(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, std::size_t size);

        CDPL_MOLPROP_API std::size_t getNumContainingSSSRRings(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);


        CDPL_MOLPROP_API bool isHydrogenRotor(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API bool isHeteroAtomHydrogenRotor(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);

        CDPL_MOLPROP_API bool isRotatable(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);

        CDPL_MOLPROP_API bool isHydrogenBond(const Chem::Bond& bond);

        CDPL_MOLPROP_API bool isAmideBond(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_BONDFUNCTIONS_HPP
