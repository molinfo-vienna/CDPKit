/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMDLProgramNameFunctions.cpp 
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

#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionProperty.hpp"


using namespace CDPL; 


const std::string& Chem::getMDLProgramName(const Reaction& rxn)
{
    static std::string DEF_NAME = "CDPL";
    
    return rxn.getPropertyOrDefault<std::string>(ReactionProperty::MDL_PROGRAM_NAME, DEF_NAME);
}

void Chem::setMDLProgramName(Reaction& rxn, const std::string& name)
{
	rxn.setProperty(ReactionProperty::MDL_PROGRAM_NAME, name);
}

void Chem::clearMDLProgramName(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_PROGRAM_NAME);
}

bool Chem::hasMDLProgramName(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_PROGRAM_NAME);
}
