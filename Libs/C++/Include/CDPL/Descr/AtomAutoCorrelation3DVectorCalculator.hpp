/* 
 * AtomAutoCorrelation3DVectorCalculator.hpp 
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
 * \brief Definition of class CDPL::Descr::AtomAutoCorrelation3DVectorCalculator.
 */

#ifndef CDPL_DESCR_ATOMAUTOCORRELATION3DVECTORCALCULATOR_HPP
#define CDPL_DESCR_ATOMAUTOCORRELATION3DVECTORCALCULATOR_HPP

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/AutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class AtomContainer;
    } // namespace Chem

    namespace Descr
    {

        /**
         * \brief AutoCorrelation3DVectorCalculator implementation for the calculation of atom-centered
         *        3D auto-correlation vectors of chemical structures.
         *
         * \c %AtomAutoCorrelation3DVectorCalculator is a specialization of
         * \c %AutoCorrelation3DVectorCalculator for entities of type Chem::Atom. The atom 3D
         * coordinates accessor function is preset to Chem::get3DCoordinates() and the entity-pair
         * weight function as well as any other calculation parameters can be configured via the
         * inherited setter methods of the base class.
         */
        class CDPL_DESCR_API AtomAutoCorrelation3DVectorCalculator : public AutoCorrelation3DVectorCalculator<Chem::Atom>
        {

          public:
            /**
             * \brief Constructs the \c %AtomAutoCorrelation3DVectorCalculator instance.
             */
            AtomAutoCorrelation3DVectorCalculator();

            /**
             * \brief Constructs the \c %AtomAutoCorrelation3DVectorCalculator instance and calculates
             *        the 3D auto-correlation vector of the atoms provided by \a cntnr.
             *
             * The calculated vector is stored in \a vec.
             *
             * \param cntnr The container with the atoms for which to calculate the auto-correlation vector.
             * \param vec The vector where to store the calculated auto-correlation vector.
             */
            AtomAutoCorrelation3DVectorCalculator(const Chem::AtomContainer& cntnr, Math::DVector& vec);

            /**
             * \brief Calculates the 3D auto-correlation vector of the atoms provided by \a cntnr.
             *
             * The calculated vector is stored in \a vec.
             *
             * \param cntnr The container with the atoms for which to calculate the auto-correlation vector.
             * \param vec The vector where to store the calculated auto-correlation vector.
             */
            void calculate(const Chem::AtomContainer& cntnr, Math::DVector& vec);
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_ATOMAUTOCORRELATION3DVECTORCALCULATOR_HPP
