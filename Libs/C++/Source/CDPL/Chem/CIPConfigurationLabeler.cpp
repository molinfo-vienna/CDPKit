/* 
 * CIPConfigurationLabeler.cpp 
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

#include "CDPL/Chem/CIPConfigurationLabeler.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "CIPConfigurationLabelerImpl.hpp"


using namespace CDPL;


Chem::CIPConfigurationLabeler::CIPConfigurationLabeler():
    impl(new CIPConfigurationLabelerImpl())
{}

Chem::CIPConfigurationLabeler::CIPConfigurationLabeler(const MolecularGraph& molgraph):
    impl(new CIPConfigurationLabelerImpl())
{
    setup(molgraph);
}

Chem::CIPConfigurationLabeler::CIPConfigurationLabeler(const CIPConfigurationLabeler& labeler):
    impl(new CIPConfigurationLabelerImpl(*labeler.impl))
{}

Chem::CIPConfigurationLabeler::~CIPConfigurationLabeler() {}
         
void Chem::CIPConfigurationLabeler::setup(const MolecularGraph& molgraph)
{
    impl->setup(molgraph);
}

unsigned int Chem::CIPConfigurationLabeler::getLabel(const Atom& atom)
{
    return impl->getLabel(atom);
}

unsigned int Chem::CIPConfigurationLabeler::getLabel(const Bond& bond)
{
    return impl->getLabel(bond);
}
            
Chem::CIPConfigurationLabeler& Chem::CIPConfigurationLabeler::operator=(const CIPConfigurationLabeler& labeler)
{
    if (this == &labeler)
        return *this;

    impl->copy(*labeler.impl);

    return *this;
}
