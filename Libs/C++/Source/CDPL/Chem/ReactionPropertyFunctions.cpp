/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionPropertyFunctions.cpp 
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
#include "CDPL/Chem/ReactionProperty.hpp"
#include "CDPL/Chem/ReactionPropertyDefault.hpp"
#include "CDPL/Chem/Reaction.hpp"


using namespace CDPL; 


#define MAKE_REACTION_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)        \
void Chem::set##FUNC_SUFFIX(Chem::Reaction& rxn, TYPE arg)		             \
{									             \
    rxn.setProperty(ReactionProperty::PROP_NAME, arg);		                     \
}									             \
									             \
bool Chem::has##FUNC_SUFFIX(const Chem::Reaction& rxn)	  	                     \
{									             \
    return rxn.isPropertySet(ReactionProperty::PROP_NAME);		             \
}									             \
									             \
void Chem::clear##FUNC_SUFFIX(Chem::Reaction& rxn)			             \
{									             \
    rxn.removeProperty(ReactionProperty::PROP_NAME);			             \
}

#define MAKE_REACTION_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	             \
TYPE Chem::get##FUNC_SUFFIX(const Chem::Reaction& rxn)		                     \
{									             \
    return rxn.getProperty<TYPE>(ReactionProperty::PROP_NAME);                       \
}									             \
									             \
MAKE_REACTION_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)      \
TYPE Chem::get##FUNC_SUFFIX(const Chem::Reaction& rxn)	                             \
{									             \
    return rxn.getPropertyOrDefault<TYPE>(ReactionProperty::PROP_NAME,	             \
					  ReactionPropertyDefault::PROP_NAME);       \
}									             \
									             \
MAKE_REACTION_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


typedef const Chem::MatchExpression<Chem::Reaction>::SharedPointer& MatchExpressionPtr;


MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(NAME, const std::string&, Name)
MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(MATCH_CONSTRAINTS, const Chem::MatchConstraintList::SharedPointer&, MatchConstraints)
MAKE_REACTION_PROPERTY_FUNCTIONS(MATCH_EXPRESSION, MatchExpressionPtr, MatchExpression)
MAKE_REACTION_PROPERTY_FUNCTIONS(COMPONENT_GROUPS, const Chem::FragmentList::SharedPointer&, ComponentGroups)
MAKE_REACTION_PROPERTY_FUNCTIONS(REACTION_DATA, const Chem::StringDataBlock::SharedPointer&, ReactionData)
MAKE_REACTION_PROPERTY_FUNCTIONS(ATOM_MAPPING, const Chem::AtomMapping::SharedPointer&, AtomMapping)
MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(MDL_USER_INITIALS, const std::string&, MDLUserInitials)
MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(MDL_PROGRAM_NAME, const std::string&, MDLProgramName)
MAKE_REACTION_PROPERTY_FUNCTIONS(MDL_TIMESTAMP, std::time_t, MDLTimestamp)
MAKE_REACTION_PROPERTY_FUNCTIONS(MDL_REGISTRY_NUMBER, std::size_t, MDLRegistryNumber)
MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(MDL_COMMENT, const std::string&, MDLComment)
MAKE_REACTION_PROPERTY_FUNCTIONS_WITH_DEF(MDL_RXN_FILE_VERSION, unsigned int, MDLRXNFileVersion)
MAKE_REACTION_PROPERTY_FUNCTIONS(MDL_INTERNAL_REGISTRY_NUMBER, const std::string&, MDLInternalRegistryNumber)
MAKE_REACTION_PROPERTY_FUNCTIONS(MDL_EXTERNAL_REGISTRY_NUMBER, const std::string&, MDLExternalRegistryNumber)
MAKE_REACTION_PROPERTY_FUNCTIONS(MDL_MOLECULE_RECORD, const Chem::Molecule::SharedPointer&, MDLMoleculeRecord) 
