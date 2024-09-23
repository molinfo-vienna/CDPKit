/* 
 * BurdenMatrixGenerator.hpp 
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
 * \brief Definition of the class CDPL::Descr::BurdenMatrixGenerator.
 */

#ifndef CDPL_DESCR_BURDENMATRIXGENERATOR_HPP
#define CDPL_DESCR_BURDENMATRIXGENERATOR_HPP

#include <functional>

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


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
         * \brief BurdenMatrixGenerator.
         * \see [\ref BURMA]
         */
        class CDPL_DESCR_API BurdenMatrixGenerator
        {

          public:
            /**
             * \brief Type of the generic functor class used to store user-defined atom weight functions.
             *
             * The provided atom weight function (or function object) is required to take the atom (as a
             * \c const reference to Chem::Atom) as argument and return the weight of the atom as
             * a floating-point value of type \c double (see [\ref FUNWRP]).
             */
            typedef std::function<double(const Chem::Atom&)> AtomWeightFunction;

            /**
             * \brief Constructs the \c %BurdenMatrixGenerator instance.
             */
            BurdenMatrixGenerator();

            /**
             * \brief Constructs the \c %BCUTDescriptorGenerator instance and generates the \e Burden matrix of
             *        the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the \e Burden matrix.
             * \param mtx The generated \e Burden matrix of the specified molecular graph.
             */
            BurdenMatrixGenerator(const Chem::MolecularGraph& molgraph, Math::DMatrix& mtx);

            BurdenMatrixGenerator(const BurdenMatrixGenerator&) = delete;

            BurdenMatrixGenerator& operator=(const BurdenMatrixGenerator&) = delete;

            /**
             * \brief Allows to specify a custom atom weight function for the diagonal elements of the \e Burden matrix.
             * \param func A BurdenMatrixGenerator::AtomWeightFunction instance that wraps the target function.
             * \note By default, the diagonal elements of the \e Burden matrix are atom types (see namespace
             *       Chem::AtomType).
             */
            void setAtomWeightFunction(const AtomWeightFunction& func);

            /**
             * \brief Generates the \e Burden matrix of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the \e Burden matrix.
             * \param mtx The generated \e Burden matrix of the specified molecular graph.
             */
            void generate(const Chem::MolecularGraph& molgraph, Math::DMatrix& mtx);

          private:
            AtomWeightFunction atomWeightFunc;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_BURDENMATRIXGENERATOR_HPP
