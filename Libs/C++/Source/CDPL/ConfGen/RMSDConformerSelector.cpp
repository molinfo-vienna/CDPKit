/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RMSDConformerSelector.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/ConfGen/RMSDConformerSelector.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


ConfGen::RMSDConformerSelector::RMSDConformerSelector(): minRMSD(0.0)
{}

void ConfGen::RMSDConformerSelector::setMinRMSD(double min_rmsd)
{
    minRMSD = min_rmsd;
}

double ConfGen::RMSDConformerSelector::getMinRMSD() const
{
    return minRMSD;
}
	    
void ConfGen::RMSDConformerSelector::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask, 
					   const Util::BitSet& stable_config_atom_mask)
{
    // TODO
}

bool ConfGen::RMSDConformerSelector::process(const ConformerData& conf_data)
{
    // TODO
    return false;
}

void ConfGen::RMSDConformerSelector::clearConformers()
{
    selectedConfs.clear();
}

std::size_t ConfGen::RMSDConformerSelector::getNumConformers() const
{
    return selectedConfs.size();
}

const ConfGen::ConformerData& ConfGen::RMSDConformerSelector::getConformer(std::size_t idx) const
{
    if (idx >= selectedConfs.size())
		throw Base::IndexError("RMSDConformerSelector: conformer index out of bounds");

    return *selectedConfs[idx];
}

ConfGen::RMSDConformerSelector::ConstConformerIterator ConfGen::RMSDConformerSelector::getConformersBegin() const
{
    return selectedConfs.begin();
}

ConfGen::RMSDConformerSelector::ConstConformerIterator ConfGen::RMSDConformerSelector::getConformersEnd() const
{
    return selectedConfs.end();
}
