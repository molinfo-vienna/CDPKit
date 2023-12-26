/* 
 * MolecularGraphBondStereoFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/CIPConfigurationLabeler.hpp"


using namespace CDPL; 


void Chem::perceiveBondStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_cip_sym,
                                     bool check_if_term, bool check_order, std::size_t min_ring_size)
{
    MolecularGraph::BondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::BondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
        Bond& bond = *b_it;
 
        if (!overwrite && hasStereoCenterFlag(bond))
            continue;

        setStereoCenterFlag(bond, isStereoCenter(bond, molgraph, check_cip_sym,
                                                 check_if_term, check_order, min_ring_size));
    }
}

void Chem::calcBondStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim, 
                                     bool check_stc_flag)
{
    MolecularGraph::BondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::BondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
        Bond& bond = *b_it;
 
        if (!overwrite && hasStereoDescriptor(bond))
            continue;

        if (!check_stc_flag || getStereoCenterFlag(bond))
            setStereoDescriptor(bond, calcStereoDescriptor(bond, molgraph, dim));
        else
            setStereoDescriptor(bond, StereoDescriptor(BondConfiguration::NONE));
    }
}

void Chem::calcBondCIPConfigurations(MolecularGraph& molgraph, bool overwrite)
{
    CIPConfigurationLabeler::SharedPointer cip_labeler;
    MolecularGraph::BondIterator bonds_end = molgraph.getBondsEnd();

    for (MolecularGraph::BondIterator b_it = molgraph.getBondsBegin(); b_it != bonds_end; ++b_it) {
        Bond& bond = *b_it;
 
        if (!overwrite && hasCIPConfiguration(bond))
            continue;

        if (!cip_labeler)
            cip_labeler.reset(new CIPConfigurationLabeler(molgraph));
          
        setCIPConfiguration(bond, cip_labeler->getLabel(bond));
    }
}
