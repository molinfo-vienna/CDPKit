/* 
 * InteractionConstraintConnector.hpp 
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
 * \brief Definition of the class CDPL::Pharm::InteractionConstraintConnector.
 */

#ifndef CDPL_PHARM_INTERACTIONCONSTRAINTCONNECTOR_HPP
#define CDPL_PHARM_INTERACTIONCONSTRAINTCONNECTOR_HPP

#include <functional>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL
{

    namespace Pharm
    {

        class Feature;

        /**
         * \brief InteractionConstraintConnector.
         */
        class CDPL_PHARM_API InteractionConstraintConnector
        {

          public:
            /**
             * \brief A generic wrapper class used to store feature interaction constraint test functions.
             */
            typedef std::function<bool(const Feature&, const Feature&)> ConstraintFunction;

            /**
             * \brief Constructs a \c %InteractionConstraintConnector that serves as a logical connective for the two specified constraint functions.
             * \param and_expr \c true for a logical conjuction of the function results, and \c false for a disjunction.
             * \param func1 The first interaction constraint function.
             * \param func2 The second interaction constraint function.
             */
            InteractionConstraintConnector(bool and_expr, const ConstraintFunction& func1, const ConstraintFunction& func2):
                andExpr(and_expr), function1(func1), function2(func2) {}

            bool operator()(const Feature& ftr1, const Feature& ftr2) const;

          private:
            bool               andExpr;
            ConstraintFunction function1;
            ConstraintFunction function2;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_INTERACTIONCONSTRAINTCONNECTOR_HPP
