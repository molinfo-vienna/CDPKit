/* 
 * MolecularGraphFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Returns the value of the ForceField::MolecularGraphProperty::MMFF94_AROMATIC_RINGS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return A \c const shared pointer to the list of MMFF94 aromatic rings.
         */
        CDPL_FORCEFIELD_API const Chem::FragmentList::SharedPointer& getMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the ForceField::MolecularGraphProperty::MMFF94_AROMATIC_RINGS property of the molecular graph \a molgraph to \a rings.
         * \param molgraph The molecular graph for which to set the property value.
         * \param rings The new list of MMFF94 aromatic rings.
         */
        CDPL_FORCEFIELD_API void setMMFF94AromaticRings(Chem::MolecularGraph& molgraph, const Chem::FragmentList::SharedPointer& rings);

        /**
         * \brief Clears the value of the ForceField::MolecularGraphProperty::MMFF94_AROMATIC_RINGS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_FORCEFIELD_API void clearMMFF94AromaticRings(Chem::MolecularGraph& molgraph);

        /**
         * \brief Tells whether the ForceField::MolecularGraphProperty::MMFF94_AROMATIC_RINGS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_FORCEFIELD_API bool hasMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Perceives the list of MMFF94 aromatic rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return A shared pointer to the perceived list of MMFF94 aromatic rings.
         */
        CDPL_FORCEFIELD_API Chem::FragmentList::SharedPointer perceiveMMFF94AromaticRings(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the list of MMFF94 aromatic rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite Specifies whether an already existing value of the property should be replaced.
         * \return A shared pointer to the perceived (or pre-existing) list of MMFF94 aromatic rings.
         */
        CDPL_FORCEFIELD_API Chem::FragmentList::SharedPointer perceiveMMFF94AromaticRings(Chem::MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Assigns MMFF94 atom types to the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph whose atoms will be typed.
         * \param strict If \c true, atoms for which no MMFF94 type could be perceived cause an error to be reported.
         *               Otherwise, perception never fails and problematic atoms are assigned a suitable fallback type.
         * \param overwrite Specifies whether already assigned atom type properties should be replaced.
         */
        CDPL_FORCEFIELD_API void assignMMFF94AtomTypes(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);

        /**
         * \brief Assigns MMFF94 bond type indices to the bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph whose bonds will be typed.
         * \param strict If \c true, strict parameterization will be peformed that might fail.
         *               Otherwise, bonds with parameterization problems receive the type index \e 0.
         * \param overwrite Specifies whether already assigned bond type index properties should be replaced.
         */
        CDPL_FORCEFIELD_API void assignMMFF94BondTypeIndices(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);

        /**
         * \brief Calculates and assigns MMFF94 partial atomic charges to the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to assign atom charges.
         * \param strict If \c true, strict parameterization is performed (and may fail).
         *               Otherwise, in case of parameterization problems, fallback strategies take effect.
         * \param overwrite Specifies whether already assigned charge properties should be replaced.
         */
        CDPL_FORCEFIELD_API void calcMMFF94AtomCharges(Chem::MolecularGraph& molgraph, bool strict, bool overwrite);


        /**
         * \brief Assigns UFF atom types to the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph whose atoms will be typed.
         * \param overwrite Specifies whether already assigned atom type properties should be replaced.
         */
        CDPL_FORCEFIELD_API void assignUFFAtomTypes(Chem::MolecularGraph& molgraph, bool overwrite);
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MOLECULARGRAPHFUNCTIONS_HPP
