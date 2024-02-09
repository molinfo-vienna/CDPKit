/* 
 * MolecularGraphAtomStereoFunctions.cpp 
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
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/CIPConfigurationLabeler.hpp"


using namespace CDPL; 


void Chem::perceiveAtomStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym,
                                     bool check_inv_n, bool check_quart_n, bool check_plan_n,
                                     bool check_amide_n, bool check_res_ctrs)
{
    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasStereoCenterFlag(atom))
            continue;

        setStereoCenterFlag(atom, isStereoCenter(atom, molgraph, check_asym, check_inv_n, check_quart_n,
                                                 check_plan_n, check_amide_n, check_res_ctrs));
    }
}

void Chem::calcMDLParities(MolecularGraph& molgraph, bool overwrite)
{
    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasMDLParity(atom))
            continue;

        setMDLParity(atom, calcMDLParity(atom, molgraph));
    }
}

void Chem::calcAtomStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim, bool check_stc_flag)
{
    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasStereoDescriptor(atom))
            continue;

        if (!check_stc_flag || getStereoCenterFlag(atom))
            setStereoDescriptor(atom, calcStereoDescriptor(atom, molgraph, dim));
        else
            setStereoDescriptor(atom, StereoDescriptor(AtomConfiguration::NONE));
    }
}

void Chem::calcAtomStereoDescriptorsFromMDLParities(MolecularGraph& molgraph, bool overwrite)
{
    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasStereoDescriptor(atom))
            continue;

        setStereoDescriptor(atom, calcStereoDescriptorFromMDLParity(atom, molgraph));
    }
}

void Chem::calcAtomCIPConfigurations(MolecularGraph& molgraph, bool overwrite)
{
    CIPConfigurationLabeler::SharedPointer cip_labeler;
    MolecularGraph::AtomIterator atoms_end = molgraph.getAtomsEnd();

    for (MolecularGraph::AtomIterator a_it = molgraph.getAtomsBegin(); a_it != atoms_end; ++a_it) {
        Atom& atom = *a_it;
 
        if (!overwrite && hasCIPConfiguration(atom))
            continue;

        if (!cip_labeler)
            cip_labeler.reset(new CIPConfigurationLabeler(molgraph));
  
        setCIPConfiguration(atom, cip_labeler->getLabel(atom));
    }
}
