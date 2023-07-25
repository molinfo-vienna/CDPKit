/* 
 * AtomRDFCodeCalculator.hpp 
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
 * \brief Definition of the class CDPL::Descr::AtomRDFCodeCalculator.
 */

#ifndef CDPL_DESCR_ATOMRDFCODECALCULATOR_HPP
#define CDPL_DESCR_ATOMRDFCODECALCULATOR_HPP

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Descr/RDFCodeCalculator.hpp"
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
         * \brief AtomRDFCodeCalculator.
         * \see [\ref CITB], [\ref HBMD]
         */
        class CDPL_DESCR_API AtomRDFCodeCalculator : public RDFCodeCalculator<Chem::Atom>
        {

          public:
            /**
             * \brief Constructs the \c %AtomRDFCodeCalculator instance.
             */
            AtomRDFCodeCalculator();

            AtomRDFCodeCalculator(const Chem::AtomContainer& cntnr, Math::DVector& rdf_code);

            void calculate(const Chem::AtomContainer& cntnr, Math::DVector& rdf_code);
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_ATOMRDFCODECALCULATOR_HPP
