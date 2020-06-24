/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentGenerator.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/FragmentGenerator.hpp"


using namespace CDPL;


Chem::FragmentGenerator::FragmentGenerator()
{
}

Chem::FragmentGenerator::FragmentGenerator(const FragmentGenerator& gen)
{
}

Chem::FragmentGenerator& Chem::FragmentGenerator::operator=(const FragmentGenerator& gen) 
{
    if (this == &gen)
	return *this;

  
    return *this;
}

void Chem::FragmentGenerator::addFragmentationRule(const FragmentationRule& rule)
{
}
/*
const Chem::FragmentGenerator::FragmentationRule& Chem::FragmentGenerator::getFragmentationRule(std::size_t idx) const
{
    
}
*/
void Chem::FragmentGenerator::removeFragmentationRule(std::size_t idx)
{
}

std::size_t Chem::FragmentGenerator::getNumFragmentationRules() const
{
    return 0;
}

void Chem::FragmentGenerator::generate(const MolecularGraph& molgraph, FragmentList& frags)
{
   
}
