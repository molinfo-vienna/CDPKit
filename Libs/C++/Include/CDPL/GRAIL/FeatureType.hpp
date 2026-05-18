/* 
 * FeatureType.hpp 
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
 * \brief Definition of constants in namespace CDPL::GRAIL::FeatureType.
 */

#ifndef CDPL_GRAIL_FEATURETYPE_HPP
#define CDPL_GRAIL_FEATURETYPE_HPP

#include "CDPL/Pharm/FeatureType.hpp"


namespace CDPL
{

    namespace GRAIL
    {

        /**
         * \brief Provides constants for the specification of GRAIL-specific extended pharmacophore feature
         *        types that refine H-bond donor and acceptor categories by the chemical environment
         *        (atom element + SYBYL-like type) of the participating heavy atom.
         *
         * Re-exports all constants from namespace Pharm::FeatureType and adds extended donor/acceptor
         * subtypes used by the GRAIL descriptor calculation.
         */
        namespace FeatureType
        {

            using namespace Pharm::FeatureType;

            /**
             * \brief H-bond donor with a generic nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_N       = MAX_TYPE + 1;

            /**
             * \brief H-bond donor with an sp3 (\e N.3) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_N3      = MAX_TYPE + 2;

            /**
             * \brief H-bond donor with an sp2 (\e N.2) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_N2      = MAX_TYPE + 3;

            /**
             * \brief H-bond donor with an aromatic (\e N.ar) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_Nar     = MAX_TYPE + 4;

            /**
             * \brief H-bond donor with an amide (\e N.am) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_Nam     = MAX_TYPE + 5;

            /**
             * \brief H-bond donor with a trigonal-planar (\e N.pl3) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_Npl3    = MAX_TYPE + 6;

            /**
             * \brief H-bond donor with a quaternary (\e N.4) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_N4      = MAX_TYPE + 7;

            /**
             * \brief H-bond donor with a generic oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_O       = MAX_TYPE + 8;

            /**
             * \brief H-bond donor with an sp3 (\e O.3) oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_O3      = MAX_TYPE + 9;

            /**
             * \brief H-bond donor with a generic sulfur heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_S       = MAX_TYPE + 10;

            /**
             * \brief H-bond donor with an sp3 (\e S.3) sulfur heavy atom.
             */
            constexpr unsigned int H_BOND_DONOR_S3      = MAX_TYPE + 11;

            /**
             * \brief H-bond acceptor with a generic nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_N    = MAX_TYPE + 12;

            /**
             * \brief H-bond acceptor with an sp3 (\e N.3) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_N3   = MAX_TYPE + 13;

            /**
             * \brief H-bond acceptor with an sp2 (\e N.2) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_N2   = MAX_TYPE + 14;

            /**
             * \brief H-bond acceptor with an sp (\e N.1) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_N1   = MAX_TYPE + 15;

            /**
             * \brief H-bond acceptor with an aromatic (\e N.ar) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_Nar  = MAX_TYPE + 16;

            /**
             * \brief H-bond acceptor with a trigonal-planar (\e N.pl3) nitrogen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_Npl3 = MAX_TYPE + 17;

            /**
             * \brief H-bond acceptor with a generic oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_O    = MAX_TYPE + 18;

            /**
             * \brief H-bond acceptor with an sp3 (\e O.3) oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_O3   = MAX_TYPE + 19;

            /**
             * \brief H-bond acceptor with an sp2 (\e O.2) oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_O2   = MAX_TYPE + 20;

            /**
             * \brief H-bond acceptor with a carboxylate (\e O.co2) oxygen heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_Oco2 = MAX_TYPE + 21;

            /**
             * \brief H-bond acceptor with a generic sulfur heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_S    = MAX_TYPE + 22;

            /**
             * \brief H-bond acceptor with an sp3 (\e S.3) sulfur heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_S3   = MAX_TYPE + 23;

            /**
             * \brief H-bond acceptor with an sp2 (\e S.2) sulfur heavy atom.
             */
            constexpr unsigned int H_BOND_ACCEPTOR_S2   = MAX_TYPE + 24;

            /**
             * \brief Highest extended feature type constant defined in this namespace.
             */
            constexpr unsigned int MAX_EXT_TYPE         = H_BOND_ACCEPTOR_S2;
        } // namespace FeatureType
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_FEATURETYPE_HPP
