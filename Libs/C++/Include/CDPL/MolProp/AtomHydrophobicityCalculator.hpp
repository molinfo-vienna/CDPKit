/* 
 * AtomHydrophobicityCalculator.hpp 
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
 * \brief Definition of class CDPL::MolProp::AtomHydrophobicityCalculator.
 */

#ifndef CDPL_MOLPROP_ATOMHYDROPHOBICITYCALCULATOR_HPP
#define CDPL_MOLPROP_ATOMHYDROPHOBICITYCALCULATOR_HPP

#include <string>
#include <vector>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Implementation of Greene's algorithm [\ref CATA] for the calculation of atom hydrophobicities.
         */
        class CDPL_MOLPROP_API AtomHydrophobicityCalculator
        {

          public:
            /**
             * \brief Constructs the \c %AtomHydrophobicityCalculator instance.
             */
            AtomHydrophobicityCalculator();

            /**
             * \brief Constructs a copy of the \c %AtomHydrophobicityCalculator instance \a calculator.
             * \param calculator The \c %AtomHydrophobicityCalculator to copy.
             */
            AtomHydrophobicityCalculator(const AtomHydrophobicityCalculator& calculator);

            /**
             * \brief Perceives the hydrophobicities of the atoms in the molecular graph a\ molgraph.
             * \param molgraph The molecular graph for which to perceive the atom hydrophobicities.
             * \param hyd_table The output vector where to store the atom hydrophobicities.
             */
            AtomHydrophobicityCalculator(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table);

            /**
             * Destructor.
             */
            ~AtomHydrophobicityCalculator();

            /**
             * \brief Perceives the hydrophobicities of the atoms in the molecular graph a\ molgraph.
             * \param molgraph The molecular graph for which to perceive the atom hydrophobicities.
             * \param hyd_table The output vector where to store the atom hydrophobicities.
             */
            void calculate(const Chem::MolecularGraph& molgraph, Util::DArray& hyd_table);

            /**
             * \brief Copies the \c %AtomHydrophobicityCalculator instance \a calculator.
             * \param calculator The \c %AtomHydrophobicityCalculator to copy.
             * \return A reference to itself.
             */
            AtomHydrophobicityCalculator& operator=(const AtomHydrophobicityCalculator& calculator);

          private:
            typedef std::vector<std::string>  StringList;
            typedef std::vector<unsigned int> UIntArray;

            void calcHydrophobicities(const Chem::MolecularGraph& molgraph, Util::DArray& atom_hyds);

            double calcAccessibleSurfaceFactor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

            Chem::Fragment atomEnvironment;
            UIntArray      cat9To11Counts;
            UIntArray      cat13Counts;
            std::string    atomDescr;
            StringList     atomEnvData;
        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_ATOMHYDROPHOBICITYCALCULATOR_HPP
