/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionMDLRegistryNumberFunctions.cpp 
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


std::size_t Chem::getMDLRegistryNumber(const Reaction& rxn)
{
	return rxn.getProperty<std::size_t>(ReactionProperty::MDL_REGISTRY_NUMBER);
}

void Chem::setMDLRegistryNumber(Reaction& rxn, std::size_t reg_no)
{
	rxn.setProperty(ReactionProperty::MDL_REGISTRY_NUMBER, reg_no);
}

void Chem::clearMDLRegistryNumber(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_REGISTRY_NUMBER);
}

bool Chem::hasMDLRegistryNumber(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_REGISTRY_NUMBER);
}

const std::string& Chem::getMDLInternalRegistryNumber(const Reaction& rxn)
{
	return rxn.getProperty<std::string>(ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER);
}

void Chem::setMDLInternalRegistryNumber(Reaction& rxn, const std::string& reg_no)
{
	rxn.setProperty(ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER, reg_no);
}

void Chem::clearMDLInternalRegistryNumber(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER);
}

bool Chem::hasMDLInternalRegistryNumber(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER);
}

const std::string& Chem::getMDLExternalRegistryNumber(const Reaction& rxn)
{
	return rxn.getProperty<std::string>(ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER);
}

void Chem::setMDLExternalRegistryNumber(Reaction& rxn, const std::string& reg_no)
{
	rxn.setProperty(ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER, reg_no);
}

void Chem::clearMDLExternalRegistryNumber(Reaction& rxn)
{
	rxn.removeProperty(ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER);
}

bool Chem::hasMDLExternalRegistryNumber(const Reaction& rxn)
{
	return rxn.isPropertySet(ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER);
}
