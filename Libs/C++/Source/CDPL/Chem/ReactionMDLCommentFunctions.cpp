/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMDLCommentFunctions.cpp 
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


const std::string& Chem::getMDLComment(const Reaction& rxn)
{
    static std::string DEF_COMMENT = "";
    
    return rxn.getPropertyOrDefault<std::string>(ReactionProperty::MDL_COMMENT, DEF_COMMENT);
}

void Chem::setMDLComment(Reaction& rxn, const std::string& comment)
{
	rxn.setProperty(ReactionProperty::MDL_COMMENT, comment);
}

void Chem::clearMDLComment(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_COMMENT);
}

bool Chem::hasMDLComment(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_COMMENT);
}
