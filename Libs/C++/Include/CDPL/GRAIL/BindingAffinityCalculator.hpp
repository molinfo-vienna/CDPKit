/* 
 * BindingAffinityCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::BindingAffinityCalculator.
 */

#ifndef CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP
#define CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace GRAIL
    {

        /**
         * \brief Predicts the binding affinity of a ligand pose from its GRAIL descriptor vector.
         *
         * The prediction is performed using a pre-trained regression model that takes a GRAIL
         * descriptor as input and returns a binding affinity estimate. The targeted affinity
         * measure (\f$ pK_d \f$, \f$ pK_i \f$, or a combined \f$ pK_d/pK_i \f$ model) is selected
         * at call time via the AffinityMeasure argument.
         */
        class CDPL_GRAIL_API BindingAffinityCalculator
        {

          public:
            /**
             * \brief Specifies the affinity measure the prediction targets.
             */
            enum AffinityMeasure
            {

                /**
                 * \brief \f$ pK_d \f$ (dissociation constant).
                 */
                PKD,

                /**
                 * \brief \f$ pK_i \f$ (inhibition constant).
                 */
                PKI,

                /**
                 * \brief Combined \f$ pK_d/pK_i \f$ model.
                 */
                PKD_PKI
            };

            /**
             * \brief Constructs the \c %BindingAffinityCalculator instance.
             */
            BindingAffinityCalculator() {}

            /**
             * \brief Predicts the binding affinity from the given GRAIL descriptor.
             * \param grail_descr The GRAIL descriptor vector of the ligand pose.
             * \param measure The targeted affinity measure.
             * \return The predicted binding affinity.
             */
            double operator()(const Math::DVector& grail_descr, AffinityMeasure measure) const;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_BINDINGAFFINITYCALCULATOR_HPP
