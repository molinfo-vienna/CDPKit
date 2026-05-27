/* 
 * MMFF94ChargeCalculator.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94ChargeCalculator.
 */

#ifndef CDPL_FORCEFIELD_MMFF94CHARGECALCULATOR_HPP
#define CDPL_FORCEFIELD_MMFF94CHARGECALCULATOR_HPP

#include <cstddef>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94BondChargeIncrementTable.hpp"
#include "CDPL/ForceField/MMFF94PartialBondChargeIncrementTable.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/MMFF94FormalAtomChargeDefinitionTable.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Calculator for the MMFF94 partial atomic charges of a molecular graph.
         *
         * Partial atomic charges are constructed from full or fractional formal atomic charges
         * and per-bond charge-increment contributions according to the MMFF94 parameterization.
         * Parameter tables and atom-/bond-typing functions can be customized via the corresponding
         * setter methods; default tables and typing functions match the standard MMFF94 reference.
         */
        class CDPL_FORCEFIELD_API MMFF94ChargeCalculator
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94ChargeCalculator instances.
             */
            typedef std::shared_ptr<MMFF94ChargeCalculator> SharedPointer;

            /**
             * \brief Constructs the \c %MMFF94ChargeCalculator instance.
             */
            MMFF94ChargeCalculator();

            /**
             * \brief Constructs the \c %MMFF94ChargeCalculator instance and immediately calculates partial charges
             *        for the atoms of \a molgraph.
             * \param molgraph The molecular graph for which to calculate partial atomic charges.
             * \param charges The output array storing the calculated partial charges.
             * \param strict If \c true, strict parameterization is performed (and may fail).
             *               Otherwise, in case of parameterization problems, fallback strategies take effect.
             */
            MMFF94ChargeCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& charges, bool strict);

            /**
             * \brief Sets the bond charge increment table to use.
             * \param table The table providing bond charge increments.
             */
            void setBondChargeIncrementTable(const MMFF94BondChargeIncrementTable::SharedPointer& table);

            /**
             * \brief Sets the partial bond charge increment table to use.
             * \param table The table providing partial bond charge increments.
             */
            void setPartialBondChargeIncrementTable(const MMFF94PartialBondChargeIncrementTable::SharedPointer& table);

            /**
             * \brief Sets the MMFF94 atom type property table to use.
             * \param table The table providing atom type properties.
             */
            void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

            /**
             * \brief Sets the formal charge definition table to use.
             * \param table The table providing formal charge definitions.
             */
            void setFormalChargeDefinitionTable(const MMFF94FormalAtomChargeDefinitionTable::SharedPointer& table);

            /**
             * \brief Specifies the function used to retrieve the aromatic ring set of a molecular graph.
             * \param func The aromatic ring set function.
             */
            void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

            /**
             * \brief Specifies the function used to retrieve the numeric MMFF94 atom type of an atom.
             * \param func The numeric atom type function.
             */
            void setNumericAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func);

            /**
             * \brief Specifies the function used to retrieve the symbolic MMFF94 atom type of an atom.
             * \param func The symbolic atom type function.
             */
            void setSymbolicAtomTypeFunction(const MMFF94SymbolicAtomTypeFunction& func);

            /**
             * \brief Specifies the function used to retrieve the MMFF94 bond type index of a bond.
             * \param func The bond type index function.
             */
            void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func);

            /**
             * \brief Calculates MMFF94 partial charges for the atoms of a molecular graph.
             *
             * The partial atomic charges are constructed from initial full or fractional
             * formal atomic charges \f$ q_I^0 \f$ (usually zero, but, e.g., \e +1/3 for guanidinium nitrogens) by
             * adding contributions from bond charge increments \f$ w_{KI} \f$ which describe the
             * polarity of the bonds to atom \e i from attached atoms \e k. Thus, \f$ w_{KI} \f$ is the
             * contribution to the total charge on atom \e i of atom type \e I accumulated from,
             * and at the expense of, its bonded neighbor \e k of atom type \e K. Specifically,
             * MMFF computes \f$ q_i \f$ as
             * 
             * \f$ q_i = (1 - M_I \: u_I) \:q_I^0 + \sum (u_K \: q_K^0) + \sum w_{KI} \f$
             * 
             * where \f$ w_{KI} = -w_{IK} \f$  and where the sums on the right hand side run over the \f$ M_I = crd(I) \f$
             * atoms \e k of MMFF atom type \e K directly attached to atom \e i (\f$ crd(I) \f$
             * comes from "MMFFPROP.PAR"). In this equation, \f$ q_I^0 \f$ and \f$ q_K^0 \f$ are the formal
             * charges assigned in the atom typing procedure (usually, by subroutine
             * XTYPE), and the sum of the first two terms gives the "effective" fractional
             * formal atomic charge residing on atom \e i. This approach allows a formal
             * atomic charge initially affixed by the atom-typing procedure (e.g., \f$ q_I^0 \f$) to
             * be shared in a prescribed manner with the neighbors bonded to the atom in
             * question. For example, for the series \e PO4(-3), \e HPO4(-2), \e H2PO4-, \e H3P04, it
             * allows allows the partial charges on the terminal oxygens (each represented
             * by the same numerical atom type, \e "32") to vary in a way which properly
             * reflects the partial charges obtained from fits to the \e 6-31G* electrostatic
             * potential. In particular, the difference between the resultant charges \f$ q_i \f$
             * calculated for the single terminal oxygen in \e H3PO4 and for the four
             * equivalent terminal oxygens in \e PO4(-3) comes to \e -0.375, half (because \f$ u_{32} = -0.5 \f$)
             * the difference of \e -0.75 in the \f$ q_K^0 \f$ charges (i.e., \e 0.00 and \e -0.75,
             * respectively) and reasonably in accord with the difference of \e -0.42 found
             * by fitting the electrostatic potential.
             * 
             * \param molgraph The molecular graph for which to calculate partial atomic charges.
             * \param charges The output array storing the calculated partial charges.
             * \param strict If \c true, strict parameterization will be peformed that might fail.
             *               Otherwise, in case of parameterization problems, fallback strategies take effect.
             */
            void calculate(const Chem::MolecularGraph& molgraph, Util::DArray& charges, bool strict);

            /**
             * \brief Returns the formal atomic charges assigned during the last calculation.
             * \return A \c const reference to the array of formal charges.
             */
            const Util::DArray& getFormalCharges() const;

          private:
            typedef MMFF94BondChargeIncrementTable::Entry        BCIEntry;
            typedef MMFF94PartialBondChargeIncrementTable::Entry PBCIEntry;
            typedef MMFF94AtomTypePropertyTable::Entry           TypePropertyEntry;
            typedef MMFF94FormalAtomChargeDefinitionTable::Entry FormChargeDefEntry;

            typedef std::vector<std::size_t> AtomIndexList;

            void init(const Chem::MolecularGraph& molgraph, Util::DArray& charges);

            void assignFormalCharges();
            void distFormalNeighborCharges(const Chem::Atom& atom, const FormChargeDefEntry& entry);
            void distFormalAromAtomCharges(const Chem::Atom& atom, const FormChargeDefEntry& entry);

            void   calcPartialCharges(Util::DArray& charges, bool strict) const;
            double getBondChargeIncrement(unsigned int bnd_type_idx, unsigned int atom_type1, unsigned int atom_type2,
                                          const PBCIEntry& pbci_entry1, const PBCIEntry& pbci_entry2) const;

            MMFF94BondChargeIncrementTable::SharedPointer        bondChargeIncTable;
            MMFF94PartialBondChargeIncrementTable::SharedPointer partBondChargeIncTable;
            MMFF94AtomTypePropertyTable::SharedPointer           atomTypePropTable;
            MMFF94FormalAtomChargeDefinitionTable::SharedPointer formChargeDefTable;
            MMFF94RingSetFunction                                aromRingSetFunc;
            MMFF94NumericAtomTypeFunction                        numAtomTypeFunc;
            MMFF94SymbolicAtomTypeFunction                       symAtomTypeFunc;
            MMFF94BondTypeIndexFunction                          bondTypeIdxFunc;
            Util::DArray                                         formCharges;
            Util::BitSet                                         assFormChargeMask;
            AtomIndexList                                        atomList;
            const Chem::MolecularGraph*                          molGraph;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94CHARGECALCULATOR_HPP
