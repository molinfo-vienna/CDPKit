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
     * \brief Provides constants for the specification of pharmacophore feature types 
     *        with extensions for H-bond acceptors and donors.
     */
    namespace FeatureType 
    {

        using namespace Pharm::FeatureType;
        
        const unsigned int H_BOND_DONOR_N       = MAX_TYPE + 1;
        const unsigned int H_BOND_DONOR_N3      = MAX_TYPE + 2;
        const unsigned int H_BOND_DONOR_N2      = MAX_TYPE + 3;
        const unsigned int H_BOND_DONOR_Nar     = MAX_TYPE + 4;
        const unsigned int H_BOND_DONOR_Nam     = MAX_TYPE + 5;
        const unsigned int H_BOND_DONOR_Npl3    = MAX_TYPE + 6;
        const unsigned int H_BOND_DONOR_N4      = MAX_TYPE + 7;
        const unsigned int H_BOND_DONOR_O       = MAX_TYPE + 8;
        const unsigned int H_BOND_DONOR_O3      = MAX_TYPE + 9;
        const unsigned int H_BOND_DONOR_S       = MAX_TYPE + 10;
        const unsigned int H_BOND_DONOR_S3      = MAX_TYPE + 11;
        const unsigned int H_BOND_ACCEPTOR_N    = MAX_TYPE + 12;
        const unsigned int H_BOND_ACCEPTOR_N3   = MAX_TYPE + 13;
        const unsigned int H_BOND_ACCEPTOR_N2   = MAX_TYPE + 14;
        const unsigned int H_BOND_ACCEPTOR_N1   = MAX_TYPE + 15;
        const unsigned int H_BOND_ACCEPTOR_Nar  = MAX_TYPE + 16;
        const unsigned int H_BOND_ACCEPTOR_Npl3 = MAX_TYPE + 17;
        const unsigned int H_BOND_ACCEPTOR_O    = MAX_TYPE + 18;
        const unsigned int H_BOND_ACCEPTOR_O3   = MAX_TYPE + 19;
        const unsigned int H_BOND_ACCEPTOR_O2   = MAX_TYPE + 20;
        const unsigned int H_BOND_ACCEPTOR_Oco2 = MAX_TYPE + 21;
        const unsigned int H_BOND_ACCEPTOR_S    = MAX_TYPE + 22;
        const unsigned int H_BOND_ACCEPTOR_S3   = MAX_TYPE + 23;
        const unsigned int H_BOND_ACCEPTOR_S2   = MAX_TYPE + 24;
        const unsigned int MAX_EXT_TYPE         = H_BOND_ACCEPTOR_S2;
    }
    }
}

#endif // CDPL_GRAIL_FEATURETYPE_HPP
