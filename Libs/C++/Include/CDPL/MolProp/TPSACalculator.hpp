/* 
 * TPSACalculator.hpp 
 * 
 * Calculation of polar surface area based on fragment contributions (TPSA) 
 * (P. Ertl, B. Rohde, P. Selzer, J. Med. Chem. 2000, 43, 3714-3717) 
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
 * \brief Definition of class CDPL::MolProp::TPSACalculator.
 */

#ifndef CDPL_MOLPROP_TPSACALCULATOR_HPP
#define CDPL_MOLPROP_TPSACALCULATOR_HPP

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace MolProp
    {

        /**
         * \brief TPSACalculator.
         * \see [\ref TPSA]
         */
        class CDPL_MOLPROP_API TPSACalculator
        {

          public:
            /**
             * \brief Constructs the \c %TPSACalculator instance.
             */
            TPSACalculator();

            /**
             * \brief Constructs the \c %TPSACalculator instance and calculates the \e TPSA of the molecular
             *        graph \a molgraph.
             *
             * The calculated \e TPSA can be retrieved by a call to getResult().
             *
             * \param molgraph The molecular graph for which to calculate the \e TPSA.
             */
            TPSACalculator(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Calculates the \e TPSA of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the \e TPSA.
             * \return The calculated \e TPSA of the molecular graph \a molgraph.
             */
            double calculate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Returns the result of the last \e TPSA calculation.
             * \return The result of the last \e TPSA calculation, or zero if a calculation has not yet been performed.
             */
            double getResult() const;

          private:
            void init();

            Chem::PatternAtomTyper atomTyper;
            double                 area;
        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_TPSACALCULATOR_HPP
