/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::Reaction instances.
 */

#ifndef CDPL_CHEM_REACTIONFUNCTIONS_HPP
#define CDPL_CHEM_REACTIONFUNCTIONS_HPP

#include <cstddef>
#include <ctime>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/AtomMapping.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class Reaction;

		/**
		 * \addtogroup CDPL_CHEM_REACTION_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API const std::string& getName(const Reaction& rxn);

		CDPL_CHEM_API void setName(Reaction& rxn, const std::string& name);

		CDPL_CHEM_API void clearName(Reaction& rxn);

		CDPL_CHEM_API bool hasName(const Reaction& rxn);


		CDPL_CHEM_API const MatchExpression<Reaction>::SharedPointer& getMatchExpression(const Reaction& rxn);

		CDPL_CHEM_API void setMatchExpression(Reaction& rxn, const MatchExpression<Reaction>::SharedPointer& expr);

		CDPL_CHEM_API void clearMatchExpression(Reaction& rxn);

		CDPL_CHEM_API bool hasMatchExpression(const Reaction& rxn);

		CDPL_CHEM_API MatchExpression<Reaction>::SharedPointer buildMatchExpression(const Reaction& rxn);

		CDPL_CHEM_API MatchExpression<Reaction>::SharedPointer buildMatchExpression(Reaction& rxn, bool overwrite);


		CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Reaction& rxn);

		CDPL_CHEM_API void setMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr);

		CDPL_CHEM_API void clearMatchConstraints(Reaction& rxn);

		CDPL_CHEM_API bool hasMatchConstraints(const Reaction& rxn);


		CDPL_CHEM_API const FragmentList::SharedPointer& getComponentGroups(const Reaction& rxn);

		CDPL_CHEM_API void setComponentGroups(Reaction& rxn, const FragmentList::SharedPointer& comp_groups);

		CDPL_CHEM_API void clearComponentGroups(Reaction& rxn);

		CDPL_CHEM_API bool hasComponentGroups(const Reaction& rxn);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const Reaction& rxn);

		CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(Reaction& rxn, bool overwrite);


		CDPL_CHEM_API const AtomMapping::SharedPointer& getAtomMapping(const Reaction& rxn);

		CDPL_CHEM_API void setAtomMapping(Reaction& rxn, const AtomMapping::SharedPointer& mapping);

		CDPL_CHEM_API void clearAtomMapping(Reaction& rxn);
	
		CDPL_CHEM_API bool hasAtomMapping(const Reaction& rxn);

		CDPL_CHEM_API AtomMapping::SharedPointer perceiveAtomMapping(const Reaction& rxn);

		CDPL_CHEM_API AtomMapping::SharedPointer perceiveAtomMapping(Reaction& rxn, bool overwrite);


		CDPL_CHEM_API bool generateSMILES(const Reaction& rxn, std::string& smiles, bool canonical = false, 
										  bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT, 
										  unsigned int bond_flags = BondPropertyFlag::DEFAULT);
	
		CDPL_CHEM_API Base::uint64 calcHashCode(const Reaction& rxn, unsigned int role_mask = ReactionRole::ALL, 
												unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
												unsigned int bond_flags = BondPropertyFlag::DEFAULT, 
												bool global_stereo = true, bool ord_h_deplete = true);


		CDPL_CHEM_API const std::string& getMDLUserInitials(const Reaction& rxn);

		CDPL_CHEM_API void setMDLUserInitials(Reaction& rxn, const std::string& initials);

		CDPL_CHEM_API void clearMDLUserInitials(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLUserInitials(const Reaction& rxn);


		CDPL_CHEM_API const std::string& getMDLProgramName(const Reaction& rxn);

		CDPL_CHEM_API void setMDLProgramName(Reaction& rxn, const std::string& name);

		CDPL_CHEM_API void clearMDLProgramName(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLProgramName(const Reaction& rxn);


		CDPL_CHEM_API std::time_t getMDLTimestamp(const Reaction& rxn);

		CDPL_CHEM_API void setMDLTimestamp(Reaction& rxn, std::time_t time);

		CDPL_CHEM_API void clearMDLTimestamp(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLTimestamp(const Reaction& rxn);


		CDPL_CHEM_API std::size_t getMDLRegistryNumber(const Reaction& rxn);

		CDPL_CHEM_API void setMDLRegistryNumber(Reaction& rxn, std::size_t reg_no);

		CDPL_CHEM_API void clearMDLRegistryNumber(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLRegistryNumber(const Reaction& rxn);


		CDPL_CHEM_API const std::string& getMDLComment(const Reaction& rxn);

		CDPL_CHEM_API void setMDLComment(Reaction& rxn, const std::string& comment);

		CDPL_CHEM_API void clearMDLComment(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLComment(const Reaction& rxn);


		CDPL_CHEM_API const StringDataBlock::SharedPointer& getReactionData(const Reaction& rxn);

		CDPL_CHEM_API void setReactionData(Reaction& rxn, const StringDataBlock::SharedPointer& data);

		CDPL_CHEM_API void clearReactionData(Reaction& rxn);
	
		CDPL_CHEM_API bool hasReactionData(const Reaction& rxn);


		CDPL_CHEM_API const Molecule::SharedPointer& getMDLMoleculeRecord(const Reaction& rxn);

		CDPL_CHEM_API void setMDLMoleculeRecord(Reaction& rxn, const Molecule::SharedPointer& mol_rec);

		CDPL_CHEM_API void clearMDLMoleculeRecord(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLMoleculeRecord(const Reaction& rxn);


		CDPL_CHEM_API const std::string& getMDLInternalRegistryNumber(const Reaction& rxn);

		CDPL_CHEM_API void setMDLInternalRegistryNumber(Reaction& rxn, const std::string& reg_no);

		CDPL_CHEM_API void clearMDLInternalRegistryNumber(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLInternalRegistryNumber(const Reaction& rxn);


		CDPL_CHEM_API const std::string& getMDLExternalRegistryNumber(const Reaction& rxn);

		CDPL_CHEM_API void setMDLExternalRegistryNumber(Reaction& rxn, const std::string& reg_no);

		CDPL_CHEM_API void clearMDLExternalRegistryNumber(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLExternalRegistryNumber(const Reaction& rxn);


		CDPL_CHEM_API unsigned int getMDLRXNFileVersion(const Reaction& rxn);

		CDPL_CHEM_API void setMDLRXNFileVersion(Reaction& rxn, unsigned int version);

		CDPL_CHEM_API void clearMDLRXNFileVersion(Reaction& rxn);
	
		CDPL_CHEM_API bool hasMDLRXNFileVersion(const Reaction& rxn);


		CDPL_CHEM_API std::size_t getMaxComponentGroupID(const Reaction& rxn);

		CDPL_CHEM_API std::size_t getMaxAtomMappingID(const Reaction& rxn);


		CDPL_CHEM_API void setAtomMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);

		CDPL_CHEM_API void setBondMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);

		CDPL_CHEM_API void setComponentMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);
	
		CDPL_CHEM_API void buildMatchExpressions(Reaction& rxn, bool overwrite);

		CDPL_CHEM_API void initSubstructureSearchQuery(Reaction& rxn, bool overwrite);

		CDPL_CHEM_API void initSubstructureSearchTarget(Reaction& rxn, bool overwrite);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_REACTIONFUNCTIONS_HPP
 
