/* 
 * AutoCorrelation2DVectorCalculator.hpp 
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
 * \brief Definition of class CDPL::Descr::AutoCorrelation2DVectorCalculator.
 */

#ifndef CDPL_DESCR_AUTOCORRELATION2DVECTORCALCULATOR_HPP
#define CDPL_DESCR_AUTOCORRELATION2DVECTORCALCULATOR_HPP

#include <cstddef>
#include <functional>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;

    } // namespace Chem

    namespace Descr
    {

        /**
         * \brief AutoCorrelation2DVectorCalculator.
         * \see [\ref AUCOR, \ref HBMD]
         */
        class CDPL_DESCR_API AutoCorrelation2DVectorCalculator
        {

          public:
            /**
             * \brief Type of the generic functor class used to store user-defined atom pair weight functions.
             *
             * The provided atom pair weight function (or function object) is required to take the two atoms (as a
             * \c const reference to Chem::Atom) as its arguments and return the weight of the atom pair as
             * a floating-point value of type \c double (see [\ref FUNWRP]).
             */
            typedef std::function<double(const Chem::Atom&, const Chem::Atom&)> AtomPairWeightFunction;

            /**
             * \brief Constructs the \c %AutoCorrelation2DVectorCalculator instance.
             */
            AutoCorrelation2DVectorCalculator();

            /**
             * \brief Constructs the \c %AutoCorrelation2DVectorCalculator instance and calculates the autocorrelation
             *        vector of the molecular graph \a molgraph.
             *
             * The calculated autocorrelation vector can be retrieved by a call to getResult().
             *
             * \param molgraph The molecular graph for which to calculate the autocorrelation vector.
             * \param corr_vec The calculated autocorrelation vector. 
             */
            AutoCorrelation2DVectorCalculator(const Chem::MolecularGraph& molgraph, Math::DVector& corr_vec);

            /**
             * \brief Allows to specify that maximum bond path length to consider.
             * \param max_dist The maximum considered bond path length.
             * \note The default value is \e 0 which signals no path length limit.
             */
            void setMaxDistance(std::size_t max_dist);

            /**
             * \brief Returns the maximum considered bond path length.
             * \return The maximum considered bond path length.
             */
            std::size_t getMaxDistance() const;

            /**
             * \brief Allows to specify a custom atom pair weight function.
             * \param func An AutoCorrelation2DVectorCalculator::AtomPairWeightFunction instance that wraps the target function.
             * \note The default atom pair weight function returns the product of the atom types (see namespace
             *       Chem::AtomType).
             */
            void setAtomPairWeightFunction(const AtomPairWeightFunction& func);

            /**
             * \brief Calculates the topological autocorrelation vector of the molecular graph \a molgraph.
             *
             * The elements of the calculated vector provide the sum of the weights of all atom pairs with a
             * topological distance equal to the element index. The size of the vector is limited by the
             * topological diameter of the molecular graph or the specified maximum considered bond path length 
             * (\see setMaxDistance()).
             *
             * \param molgraph The molecular graph for which to calculate the autocorrelation vector.
             * \param corr_vec The calculated autocorrelation vector. 
             */
            void calculate(const Chem::MolecularGraph& molgraph, Math::DVector& corr_vec);

          private:
            AtomPairWeightFunction weightFunc;
            std::size_t            maxDist;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_AUTOCORRELATION2DVECTORCALCULATOR_HPP
