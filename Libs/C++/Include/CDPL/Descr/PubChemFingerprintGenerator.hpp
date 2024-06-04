/* 
 * PubChemFingerprintGenerator.hpp 
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
 * \brief Definition of the class CDPL::Descr::PubChemFingerprintGenerator.
 */

#ifndef CDPL_DESCR_PUBCHEMFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_PUBCHEMFINGERPRINTGENERATOR_HPP

#include "CDPL/Descr/APIPrefix.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Descr
    {

        /**
         * \brief Generation of 881 bit PubChem fingerprints.
         * \see [\ref PCDS]
         */
        class CDPL_DESCR_API PubChemFingerprintGenerator
        {

          public:
         
            /**
             * \brief Constructs the \c %PubChemFingerprintGenerator instance.
             */
            PubChemFingerprintGenerator();

            PubChemFingerprintGenerator(const PubChemFingerprintGenerator& gen);
            
            /**
             * \brief Constructs the \c %PubChemFingerprintGenerator instance and generates the fingerprint of the
             *        molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the fingerprint.
             * \param fp The generated fingerprint.
             */
            PubChemFingerprintGenerator(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            /**
             * \brief Generates the fingerprint of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the fingerprint.
             * \param fp The generated fingerprint.
             */
            void generate(const Chem::MolecularGraph& molgraph, Util::BitSet& fp);

            PubChemFingerprintGenerator& operator=(const PubChemFingerprintGenerator& gen)
            {
                return *this;
            }

          private:
            Chem::SubstructureSearch subSearch;
        };
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_PUBCHEMFINGERPRINTGENERATOR_HPP
