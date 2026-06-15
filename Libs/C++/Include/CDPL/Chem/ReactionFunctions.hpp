/* 
 * ReactionFunctions.hpp 
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

/**
 * \file
 * \brief Declaration of functions that operate on Chem::Reaction instances.
 */

#ifndef CDPL_CHEM_REACTIONFUNCTIONS_HPP
#define CDPL_CHEM_REACTIONFUNCTIONS_HPP

#include <cstddef>
#include <cstdint>
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


namespace CDPL
{

    namespace Chem
    {

        class Reaction;

        /**
         * \brief Returns the value of the Chem::ReactionProperty::NAME property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored reaction name.
         */
        CDPL_CHEM_API const std::string& getName(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::NAME property of the reaction \a rxn to \a name.
         * \param rxn The reaction for which to set the property value.
         * \param name The new reaction name.
         */
        CDPL_CHEM_API void setName(Reaction& rxn, const std::string& name);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::NAME property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearName(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::NAME property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasName(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::TIMESTAMP property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored timestamp.
         */
        CDPL_CHEM_API std::time_t getTimestamp(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::TIMESTAMP property of the reaction \a rxn to \a time.
         * \param rxn The reaction for which to set the property value.
         * \param time The new timestamp value.
         */
        CDPL_CHEM_API void setTimestamp(Reaction& rxn, std::time_t time);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::TIMESTAMP property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearTimestamp(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::TIMESTAMP property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasTimestamp(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::COMMENT property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored comment.
         */
        CDPL_CHEM_API const std::string& getComment(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::COMMENT property of the reaction \a rxn to \a comment.
         * \param rxn The reaction for which to set the property value.
         * \param comment The new comment string.
         */
        CDPL_CHEM_API void setComment(Reaction& rxn, const std::string& comment);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::COMMENT property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearComment(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::COMMENT property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComment(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MATCH_EXPRESSION property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored top-level reaction match expression.
         */
        CDPL_CHEM_API const MatchExpression<Reaction>::SharedPointer& getMatchExpression(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MATCH_EXPRESSION property of the reaction \a rxn to \a expr.
         * \param rxn The reaction for which to set the property value.
         * \param expr The new match expression to store.
         */
        CDPL_CHEM_API void setMatchExpression(Reaction& rxn, const MatchExpression<Reaction>::SharedPointer& expr);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MATCH_EXPRESSION property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchExpression(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MATCH_EXPRESSION property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpression(const Reaction& rxn);

        /**
         * \brief Builds a reaction-level match expression from the constraints currently attached to \a rxn
         *        and returns it without modifying \a rxn.
         * \param rxn The reaction to inspect.
         * \return The generated match expression.
         */
        CDPL_CHEM_API MatchExpression<Reaction>::SharedPointer generateMatchExpression(const Reaction& rxn);

        /**
         * \brief Builds and (optionally) stores the reaction-level match expression of the reaction \a rxn.
         * \param rxn The reaction to inspect/modify.
         * \param overwrite If \c true, the generated expression replaces any existing
         *                  Chem::ReactionProperty::MATCH_EXPRESSION; if \c false, the existing one (if any)
         *                  is returned unchanged.
         * \return The generated (or pre-existing) match expression.
         */
        CDPL_CHEM_API MatchExpression<Reaction>::SharedPointer generateMatchExpression(Reaction& rxn, bool overwrite);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MATCH_CONSTRAINTS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored top-level match-constraint list.
         */
        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MATCH_CONSTRAINTS property of the reaction \a rxn to \a constr.
         * \param rxn The reaction for which to set the property value.
         * \param constr The new match-constraint list to store.
         */
        CDPL_CHEM_API void setMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MATCH_CONSTRAINTS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchConstraints(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MATCH_CONSTRAINTS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchConstraints(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::COMPONENT_GROUPS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored component-group fragment list.
         */
        CDPL_CHEM_API const FragmentList::SharedPointer& getComponentGroups(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::COMPONENT_GROUPS property of the reaction \a rxn to \a comp_groups.
         * \param rxn The reaction for which to set the property value.
         * \param comp_groups The new component-group fragment list.
         */
        CDPL_CHEM_API void setComponentGroups(Reaction& rxn, const FragmentList::SharedPointer& comp_groups);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::COMPONENT_GROUPS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearComponentGroups(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::COMPONENT_GROUPS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComponentGroups(const Reaction& rxn);

        /**
         * \brief Perceives the component groups of the reaction \a rxn without modifying it.
         * \param rxn The reaction to inspect.
         * \return The perceived component-group fragment list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const Reaction& rxn);

        /**
         * \brief Perceives and (optionally) stores the component groups of the reaction \a rxn.
         * \param rxn The reaction to inspect/modify.
         * \param overwrite If \c true, the perceived list replaces any existing
         *                  Chem::ReactionProperty::COMPONENT_GROUPS; if \c false, the existing one (if any)
         *                  is returned unchanged.
         * \return The perceived (or pre-existing) component-group fragment list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(Reaction& rxn, bool overwrite);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::ATOM_MAPPING property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored reactant-to-product atom mapping.
         */
        CDPL_CHEM_API const AtomMapping::SharedPointer& getAtomMapping(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::ATOM_MAPPING property of the reaction \a rxn to \a mapping.
         * \param rxn The reaction for which to set the property value.
         * \param mapping The new reactant-to-product atom mapping.
         */
        CDPL_CHEM_API void setAtomMapping(Reaction& rxn, const AtomMapping::SharedPointer& mapping);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::ATOM_MAPPING property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearAtomMapping(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::ATOM_MAPPING property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasAtomMapping(const Reaction& rxn);

        /**
         * \brief Derives the reactant-to-product atom mapping from the atom mapping IDs of the reaction \a rxn
         *        without modifying it.
         * \param rxn The reaction to inspect.
         * \return The perceived atom mapping.
         */
        CDPL_CHEM_API AtomMapping::SharedPointer perceiveAtomMapping(const Reaction& rxn);

        /**
         * \brief Derives and (optionally) stores the reactant-to-product atom mapping of the reaction \a rxn.
         * \param rxn The reaction to inspect/modify.
         * \param overwrite If \c true, the perceived mapping replaces any existing
         *                  Chem::ReactionProperty::ATOM_MAPPING; if \c false, the existing one (if any)
         *                  is returned unchanged.
         * \return The perceived (or pre-existing) atom mapping.
         */
        CDPL_CHEM_API AtomMapping::SharedPointer perceiveAtomMapping(Reaction& rxn, bool overwrite);


        /**
         * \brief Generates a reaction SMILES string for \a rxn.
         * \param rxn The reaction to encode.
         * \param smiles The string to receive the generated reaction SMILES.
         * \param canonical \c true to emit a canonical reaction SMILES; \c false for an arbitrary atom ordering.
         * \param ord_h_deplete \c true to suppress ordinary hydrogens.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties to encode.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties to encode.
         * \return \c true on success, and \c false if an unrecoverable error was encountered.
         */
        CDPL_CHEM_API bool generateSMILES(const Reaction& rxn, std::string& smiles, bool canonical = false,
                                          bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                          unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        /**
         * \brief Computes a 64-bit hash code for \a rxn taking into account the specified reaction
         *        roles and atom/bond properties.
         * \param rxn The reaction to hash.
         * \param role_mask A bitmask of Chem::ReactionRole flags selecting the considered component sets.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties enter the hash.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties enter the hash.
         * \param ord_h_deplete \c true to suppress ordinary hydrogens before hashing.
         * \return The computed hash code.
         */
        CDPL_CHEM_API std::uint64_t calcHashCode(const Reaction& rxn, unsigned int role_mask = ReactionRole::ALL,
                                                 unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                 unsigned int bond_flags = BondPropertyFlag::DEFAULT,
                                                 bool ord_h_deplete = true);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_USER_INITIALS property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL user initials.
         */
        CDPL_CHEM_API const std::string& getMDLUserInitials(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_USER_INITIALS property of the reaction \a rxn to \a initials.
         * \param rxn The reaction for which to set the property value.
         * \param initials The new MDL user initials.
         */
        CDPL_CHEM_API void setMDLUserInitials(Reaction& rxn, const std::string& initials);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_USER_INITIALS property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLUserInitials(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_USER_INITIALS property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLUserInitials(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_PROGRAM_NAME property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL program name.
         */
        CDPL_CHEM_API const std::string& getMDLProgramName(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_PROGRAM_NAME property of the reaction \a rxn to \a name.
         * \param rxn The reaction for which to set the property value.
         * \param name The new MDL program name.
         */
        CDPL_CHEM_API void setMDLProgramName(Reaction& rxn, const std::string& name);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_PROGRAM_NAME property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLProgramName(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_PROGRAM_NAME property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLProgramName(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL registry number.
         */
        CDPL_CHEM_API std::size_t getMDLRegistryNumber(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_REGISTRY_NUMBER property of the reaction \a rxn to \a reg_no.
         * \param rxn The reaction for which to set the property value.
         * \param reg_no The new MDL registry number.
         */
        CDPL_CHEM_API void setMDLRegistryNumber(Reaction& rxn, std::size_t reg_no);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLRegistryNumber(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_REGISTRY_NUMBER property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLRegistryNumber(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::REACTION_DATA property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL reaction data block.
         */
        CDPL_CHEM_API const StringDataBlock::SharedPointer& getReactionData(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::REACTION_DATA property of the reaction \a rxn to \a data.
         * \param rxn The reaction for which to set the property value.
         * \param data The new MDL reaction data block.
         */
        CDPL_CHEM_API void setReactionData(Reaction& rxn, const StringDataBlock::SharedPointer& data);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::REACTION_DATA property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearReactionData(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::REACTION_DATA property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasReactionData(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_MOLECULE_RECORD property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL molecule record (typically the structure component of an RD-file).
         */
        CDPL_CHEM_API const Molecule::SharedPointer& getMDLMoleculeRecord(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_MOLECULE_RECORD property of the reaction \a rxn to \a mol_rec.
         * \param rxn The reaction for which to set the property value.
         * \param mol_rec The new MDL molecule record.
         */
        CDPL_CHEM_API void setMDLMoleculeRecord(Reaction& rxn, const Molecule::SharedPointer& mol_rec);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_MOLECULE_RECORD property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLMoleculeRecord(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_MOLECULE_RECORD property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLMoleculeRecord(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL internal registry number.
         */
        CDPL_CHEM_API const std::string& getMDLInternalRegistryNumber(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER property of the reaction \a rxn to \a reg_no.
         * \param rxn The reaction for which to set the property value.
         * \param reg_no The new MDL internal registry number.
         */
        CDPL_CHEM_API void setMDLInternalRegistryNumber(Reaction& rxn, const std::string& reg_no);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLInternalRegistryNumber(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_INTERNAL_REGISTRY_NUMBER property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLInternalRegistryNumber(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored MDL external registry number.
         */
        CDPL_CHEM_API const std::string& getMDLExternalRegistryNumber(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction \a rxn to \a reg_no.
         * \param rxn The reaction for which to set the property value.
         * \param reg_no The new MDL external registry number.
         */
        CDPL_CHEM_API void setMDLExternalRegistryNumber(Reaction& rxn, const std::string& reg_no);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLExternalRegistryNumber(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_EXTERNAL_REGISTRY_NUMBER property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLExternalRegistryNumber(const Reaction& rxn);


        /**
         * \brief Returns the value of the Chem::ReactionProperty::MDL_RXN_FILE_VERSION property of the reaction \a rxn.
         * \param rxn The reaction for which to return the property value.
         * \return The stored RXN-file version (see Chem::MDLDataFormatVersion).
         */
        CDPL_CHEM_API unsigned int getMDLRXNFileVersion(const Reaction& rxn);

        /**
         * \brief Sets the value of the Chem::ReactionProperty::MDL_RXN_FILE_VERSION property of the reaction \a rxn to \a version.
         * \param rxn The reaction for which to set the property value.
         * \param version The new RXN-file version (see Chem::MDLDataFormatVersion).
         */
        CDPL_CHEM_API void setMDLRXNFileVersion(Reaction& rxn, unsigned int version);

        /**
         * \brief Clears the value of the Chem::ReactionProperty::MDL_RXN_FILE_VERSION property of the reaction \a rxn.
         * \param rxn The reaction for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLRXNFileVersion(Reaction& rxn);

        /**
         * \brief Tells whether the Chem::ReactionProperty::MDL_RXN_FILE_VERSION property of the reaction \a rxn is set.
         * \param rxn The reaction for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLRXNFileVersion(const Reaction& rxn);


        /**
         * \brief Returns the largest component-group ID found on any of the components of the reaction \a rxn.
         * \param rxn The reaction to scan.
         * \return The largest component-group ID, or zero if no IDs are assigned.
         */
        CDPL_CHEM_API std::size_t getMaxComponentGroupID(const Reaction& rxn);

        /**
         * \brief Returns the largest atom-mapping ID found on any of the atoms in \a rxn.
         * \param rxn The reaction to scan.
         * \return The largest atom-mapping ID, or zero if no IDs are assigned.
         */
        CDPL_CHEM_API std::size_t getMaxAtomMappingID(const Reaction& rxn);


        /**
         * \brief Sets the atom-level match-constraint list \a constr on every atom of every component of the reaction \a rxn.
         * \param rxn The reaction to modify.
         * \param constr The match-constraint list to assign.
         * \param overwrite If \c true, replaces any existing per-atom constraints; if \c false, leaves
         *                  atoms that already carry a list unchanged.
         */
        CDPL_CHEM_API void setAtomMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);

        /**
         * \brief Sets the bond-level match-constraint list \a constr on every bond of every component of the reaction \a rxn.
         * \param rxn The reaction to modify.
         * \param constr The match-constraint list to assign.
         * \param overwrite If \c true, replaces any existing per-bond constraints; if \c false, leaves
         *                  bonds that already carry a list unchanged.
         */
        CDPL_CHEM_API void setBondMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);

        /**
         * \brief Sets the molecular graph-level match-constraint list \a constr on every component of the reaction \a rxn.
         * \param rxn The reaction to modify.
         * \param constr The match-constraint list to assign.
         * \param overwrite If \c true, replaces any existing per-component constraints; if \c false, leaves
         *                  components that already carry a list unchanged.
         */
        CDPL_CHEM_API void setComponentMatchConstraints(Reaction& rxn, const MatchConstraintList::SharedPointer& constr, bool overwrite);

        /**
         * \brief Generates and stores match expressions for the atoms, bonds, components, and \a rxn itself.
         * \param rxn The reaction to modify.
         * \param overwrite If \c true, replaces any existing match expressions; if \c false, leaves
         *                  items that already carry a match expression unchanged.
         */
        CDPL_CHEM_API void generateMatchExpressions(Reaction& rxn, bool overwrite);

        /**
         * \brief Prepares \a rxn for use as a substructure search query (e.g. by pre-computing
         *        match expressions and required cached properties).
         * \param rxn The reaction to modify.
         * \param overwrite If \c true, recomputes derived data; if \c false, leaves up-to-date data unchanged.
         */
        CDPL_CHEM_API void initSubstructureSearchQuery(Reaction& rxn, bool overwrite);

        /**
         * \brief Prepares \a rxn for use as a substructure search target (e.g. by pre-computing
         *        required cached properties).
         * \param rxn The reaction to modify.
         * \param overwrite If \c true, recomputes derived data; if \c false, leaves up-to-date data unchanged.
         */
        CDPL_CHEM_API void initSubstructureSearchTarget(Reaction& rxn, bool overwrite);

        /**
         * \brief Computes the basic per-component properties (aromaticity, ring info, etc.) of every
         *        component of the reaction \a rxn.
         * \param rxn The reaction to modify.
         * \param overwrite If \c true, recomputes derived data; if \c false, leaves up-to-date data unchanged.
         * \since 1.1
         */
        CDPL_CHEM_API void calcBasicProperties(Reaction& rxn, bool overwrite);
        
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_REACTIONFUNCTIONS_HPP
