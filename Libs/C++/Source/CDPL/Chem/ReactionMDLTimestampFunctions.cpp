/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMDLTimestampFunctions.cpp 
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


std::time_t Chem::getMDLTimestamp(const Reaction& rxn)
{
	return rxn.getProperty<std::time_t>(ReactionProperty::MDL_TIMESTAMP);
}

void Chem::setMDLTimestamp(Reaction& rxn, std::time_t time)
{
	rxn.setProperty(ReactionProperty::MDL_TIMESTAMP, time);
}

void Chem::clearMDLTimestamp(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_TIMESTAMP);
}

bool Chem::hasMDLTimestamp(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_TIMESTAMP);
}
