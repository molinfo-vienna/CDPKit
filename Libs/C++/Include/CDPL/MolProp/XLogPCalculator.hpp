/* 
 * XLogPCalculator.hpp 
 *  
 * Calculation of the partition coefficient by an atom-additive method
 * (R. Wang, Y. Gao, L. Lai, Persp. Drug Disc. Design 2000, 19, 47-66)
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
 * \brief Definition of the class CDPL::MolProp::XLogPCalculator.
 */

#ifndef CDPL_MOLPROP_XLOGPCALCULATOR_HPP
#define CDPL_MOLPROP_XLOGPCALCULATOR_HPP

#include <cstddef>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/SubstructureHistogramCalculator.hpp"
#include "CDPL/Chem/PatternAtomTyper.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Chem
    {

        class Atom;
    }

    namespace MolProp
    {

        /**
         * \brief XLogPCalculator.
         * \see [\ref XLOGP]
         */
        class CDPL_MOLPROP_API XLogPCalculator 
        {

          public:
            /**
             * \brief Specifies the number of different structural features used by the \f$ \log P \f$ model.
             */
            static constexpr std::size_t FEATURE_VECTOR_SIZE = 101;

            /**
             * \brief Constructs the \c %XLogPCalculator instance.
             */
            XLogPCalculator();

            /**
             * \brief Constructs the \c %LogSCalculator instance and calculates the \f$ \log P \f$ of the molecular
             *        graph \a molgraph.
             *
             * The calculated \f$ \log P \f$ can be retrieved by a call to getResult().
             *
             * \param molgraph The molecular graph for which to calculate the \f$ \log P \f$.
             */
            XLogPCalculator(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Calculates the \f$ \log P \f$ of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the \f$ \log P \f$.
             * \return The calculated \f$ \log P \f$ of the molecular graph \a molgraph.
             */
            double calculate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Returns the result of the last \f$ \log P \f$ calculation.
             * \return The result of the last \f$ \log P \f$ calculation, or zero if a calculation has not yet been performed.
             */
            double getResult() const;

            /**
             * \brief Returns the feature count vector of the last \f$ \log P \f$ calculation.
             *
             * The occurrence count of a particular structural feature (atom type or correction factor feature) can be retrieved from
             * the returned vector via its feature index. For atom type related features, the feature index correspond to the
             * numerical identifier of the atom type in the original publication [\ref XLOGP] minus \e 1. The feature indices
             * of the various correction factors start at index \e 90 and are ordered according to their definition in the paper.
             *
             * \return The feature count vector of the last \f$ \log P \f$ calculation.
             * \note The returned feature vector is of size XLogPCalculator::FEATURE_VECTOR_SIZE.
             */
            const Math::DVector& getFeatureVector() const;

            /**
             * \brief Returns the contribution of each atom the total obtained by the last \f$ \log P \f$ calculation.
             * \return The contribution of each atom the total \f$ \log P \f$.
             * \note The sum of the atom contributions does not necessarily equal the calculated molecule \f$ \log P \f$ and
             *       might be lower!
             * \see XLogPCalculator::calculate()
             */
            const Math::DVector& getAtomContributions() const;

        private:
            void init(const Chem::MolecularGraph& molgraph);

            void countHydrophicCarbons(const Chem::MolecularGraph& molgraph);
    
            bool hasTopDistanceBelow4(const Chem::Atom& curr_atom, const Chem::Atom& tgt_atom, const Chem::MolecularGraph& molgraph,
                                      const Chem::Atom& prev_atom, std::size_t curr_dist);
        
            void calcLogP(const Chem::MolecularGraph& molgraph);
    
            Math::DVector                         featureVector;
            Math::DVector                         atomContribs;
            double                                logP;
            Chem::PatternAtomTyper                atomTyper;
            Chem::SubstructureHistogramCalculator corrSubstructHistoCalc;
        };
    }
}

#endif // CDPL_MOLPROP_XLOGPCALCULATOR_HPP
