/* 
 * ProtonationStateStandardizer.hpp 
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
 * \brief Definition of class CDPL::Chem::ProtonationStateStandardizer.
 */

#ifndef CDPL_CHEM_PROTONATIONSTATESTANDARDIZER_HPP
#define CDPL_CHEM_PROTONATIONSTATESTANDARDIZER_HPP

#include <cstddef>
#include <vector>
#include <unordered_set>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
        class ChEMBLStandardizer;

        /**
         * \brief Adjusts the protonation state of a molecule (atom formal charges and bonded hydrogen counts)
         *        according to one of several pre-defined objectives.
         */
        class CDPL_CHEM_API ProtonationStateStandardizer
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ProtonationStateStandardizer instances. */
            typedef std::shared_ptr<ProtonationStateStandardizer> SharedPointer;

            /**
             * \brief Selects the objective driving the protonation-state adjustment.
             */
            enum Flavor
            {

                /** \brief Minimize the total number of formally charged atoms (neutralize where possible). */
                MIN_CHARGED_ATOM_COUNT,
                /** \brief Set the protonation state expected under physiological conditions (pH ~7.4). */
                PHYSIOLOGICAL_CONDITION_STATE,
                /** \brief Maximize the cancellation of opposite formal charges (neutralize zwitterion-like pairs). */
                MAX_CHARGE_COMPENSATION
            };

            /**
             * \brief Constructs the \c %ProtonationStateStandardizer instance.
             */
            ProtonationStateStandardizer();

            /**
             * \brief Constructs a copy of the \c %ProtonationStateStandardizer instance \a standardizer.
             * \param standardizer The \c %ProtonationStateStandardizer to copy.
             */
            ProtonationStateStandardizer(const ProtonationStateStandardizer& standardizer);

            /**
             * \brief Adjusts the protonation state of \a mol in place according to the selected \a flavor.
             * \param mol The molecule to standardize (modified in place).
             * \param flavor The protonation-state objective.
             * \return \c true if the molecule was modified, and \c false otherwise.
             */
            bool standardize(Molecule& mol, Flavor flavor);

            /**
             * \brief Writes a standardized copy of \a mol to \a std_mol without modifying \a mol.
             * \param mol The input molecule.
             * \param std_mol The output molecule receiving the standardized copy.
             * \param flavor The protonation-state objective.
             * \return \c true if the output differs from the input, and \c false otherwise.
             */
            bool standardize(const Molecule& mol, Molecule& std_mol, Flavor flavor);

            /**
             * \brief Replaces the state of this standardizer by a copy of the state of \a standardizer.
             * \param standardizer The source \c %ProtonationStateStandardizer.
             * \return A reference to itself.
             */
            ProtonationStateStandardizer& operator=(const ProtonationStateStandardizer& standardizer);

          private:
            friend class ChEMBLStandardizer;

            typedef std::vector<Chem::Atom*> AtomList;

            void copyMolecule(const Molecule& mol, Molecule& mol_copy) const;

            bool minChargedAtomCount(Molecule& mol);
            bool protForPhysCond(Molecule& mol);
            bool maxChargeComp(Molecule& mol);

            const Chem::Atom* getAtomWithMappingID(const Molecule& ptn, std::size_t id) const;

            std::size_t adaptHydrogenCount(Atom& atom, Molecule& mol, long h_delta) const;

            std::size_t calcFreeValence(const Atom& atom) const;

            long calcNetCharge(const Atom& atom) const;

            std::size_t calcValenceExcess(const Atom& atom) const;

            std::size_t getMatches(const Molecule& ptn, const Molecule& mol, AtomList& matches);

            bool incrementCharge(Atom& atom, bool checked) const;

            bool isRemovableHydrogen(const Atom& atom) const;

            bool cmpCanonicalNumber(const Atom* atom1, const Atom* atom2) const;

            bool removeConnectedHydrogens(const AtomList& atoms, Molecule& mol) const;

            typedef std::unordered_set<const Atom*> AtomSet;

            SubstructureSearch           substructSearch;
            CanonicalNumberingCalculator canonNumberingCalc;
            AtomList                     atomList;
            AtomList                     posChargedAtoms;
            AtomList                     posChargedNoHAtoms;
            AtomList                     negChargedAtoms;
            AtomList                     negChargedAcidAtoms;
            Util::STArray                canonAtomNumbering;
            Util::BitSet                 atomMask;
            AtomSet                      atomSet;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_PROTONATIONSTATESTANDARDIZER_HPP
