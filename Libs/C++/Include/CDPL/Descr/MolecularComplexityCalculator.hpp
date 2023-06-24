/* 
 * MolecularComplexityCalculator.hpp 
 * 
 * Calculation of the molecular complexity 
 * (J. B. Hendrickson, P. Huang, A. G. Toczko, J. Chem. Inf. Comput. Sci. 1987, 27, 63-67) 
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
 * \brief Definition of the class CDPL::Descr::MolecularGraphComplexityCalculator.
 */

#ifndef CDPL_DESCR_MOLECULARCOMPLEXITYCALCULATOR_HPP
#define CDPL_DESCR_MOLECULARCOMPLEXITYCALCULATOR_HPP

#include <cstddef>
#include <map>
#include <set>

#include "CDPL/Descr/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
    } // namespace Chem

    namespace Descr
    {

        /**
         * \brief MolecularComplexityCalculator.
         * \see [\ref MCPLX]
         */
        class CDPL_DESCR_API MolecularComplexityCalculator
        {

          public:
            /**
             * \brief Constructs the \c %MolecularComplexityCalculator instance.
             */
            MolecularComplexityCalculator():
                complexity(0.0) {}

            /**
             * \brief Constructs the \c %MolecularComplexityCalculator instance and calculates the complexity
             *        of the molecular graph \a molgraph.
             *
             * The calculated complexity can be retrieved by a call to getResult().
             *
             * \param molgraph The molecular graph for which to calculate the complexity.
             */
            MolecularComplexityCalculator(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Calculates the complexity of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the complexity.
             * \return The calculated complexity of the molecular graph \a molgraph.
             */
            double calculate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Returns the result of the last molecular graph complexity calculation.
             * \return The result of the last molecular graph complexity calculation, or zero if a
             *         calculation has not yet been performed.
             */
            double getResult() const;

          private:
            MolecularComplexityCalculator(const MolecularComplexityCalculator&);

            MolecularComplexityCalculator& operator=(const MolecularComplexityCalculator&);

            void processAtom(const Chem::Atom&);
            void processBond(const Chem::Bond&);

            void calcAtomTypeComplexity();
            void calcStructuralComplexity();

            class SymmetryTerm
            {

              public:
                SymmetryTerm(const Chem::MolecularGraph&, const Chem::Atom&);

                void incNumEquivAtoms();

                double getValue() const;
                double getEtaContribution() const;
                double getNumEquivAtoms() const;

                std::size_t getID() const;

              private:
                double      numEquivAtoms;
                std::size_t id;
                std::size_t hCount;
            };

            typedef std::map<std::size_t, SymmetryTerm> SymmetryTermMap;

            class PiBondTerm
            {

              public:
                PiBondTerm(std::size_t, std::size_t, std::size_t);

                double getCorrection(const SymmetryTermMap&) const;

                bool isRelevant(const SymmetryTermMap&) const;

                bool operator<(const PiBondTerm&) const;

              private:
                std::size_t symClassID1;
                std::size_t symClassID2;
                std::size_t order;
            };

            typedef std::map<std::size_t, std::size_t> AtomTypeCountMap;
            typedef std::set<PiBondTerm>               PiBondTermSet;

            const Chem::MolecularGraph* molGraph;
            SymmetryTermMap             symmetryTerms;
            AtomTypeCountMap            atomTypeCounts;
            PiBondTermSet               piBondTerms;
            std::size_t                 numHeavyAtoms;
            std::size_t                 numDoubleBonds;
            std::size_t                 numTripleBonds;
            double                      etaTotal;
            double                      atmTypeComplexity;
            double                      structComplexity;
            double                      complexity;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_MOLECULARCOMPLEXITYCALCULATOR_HPP
