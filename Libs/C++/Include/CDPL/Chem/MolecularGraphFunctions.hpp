/* 
 * MolecularGraphFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::MolecularGraph instances.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP

#include <string>
#include <cstddef>
#include <cstdint>
#include <ctime>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/ElectronSystemList.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/ControlParameterDefault.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
        class AtomMapping;

        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::NAME property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored name.
         */
        CDPL_CHEM_API const std::string& getName(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::NAME property of the molecular graph \a molgraph to \a name.
         * \param molgraph The molecular graph for which to set the property value.
         * \param name The new name.
         */
        CDPL_CHEM_API void setName(MolecularGraph& molgraph, const std::string& name);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::NAME property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearName(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::NAME property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasName(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::TIMESTAMP property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored timestamp.
         */
        CDPL_CHEM_API std::time_t getTimestamp(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::TIMESTAMP property of the molecular graph \a molgraph to \a time.
         * \param molgraph The molecular graph for which to set the property value.
         * \param time The new timestamp value.
         */
        CDPL_CHEM_API void setTimestamp(MolecularGraph& molgraph, std::time_t time);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::TIMESTAMP property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearTimestamp(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::TIMESTAMP property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasTimestamp(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::COMMENT property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored comment.
         */
        CDPL_CHEM_API const std::string& getComment(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::COMMENT property of the molecular graph \a molgraph to \a comment.
         * \param molgraph The molecular graph for which to set the property value.
         * \param comment The new comment string.
         */
        CDPL_CHEM_API void setComment(MolecularGraph& molgraph, const std::string& comment);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::COMMENT property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearComment(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::COMMENT property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComment(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored top-level match-constraint list.
         */
        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property of the molecular graph \a molgraph to \a constr.
         * \param molgraph The molecular graph for which to set the property value.
         * \param constr The new top-level match-constraint list.
         */
        CDPL_CHEM_API void setMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchConstraints(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchConstraints(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MATCH_EXPRESSION property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored top-level match expression.
         */
        CDPL_CHEM_API const MatchExpression<MolecularGraph>::SharedPointer& getMatchExpression(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MATCH_EXPRESSION property of the molecular graph \a molgraph to \a expr.
         * \param molgraph The molecular graph for which to set the property value.
         * \param expr The new top-level match expression.
         */
        CDPL_CHEM_API void setMatchExpression(MolecularGraph& molgraph, const MatchExpression<MolecularGraph>::SharedPointer& expr);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MATCH_EXPRESSION property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMatchExpression(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MATCH_EXPRESSION property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpression(const MolecularGraph& molgraph);

        /**
         * \brief Builds a top-level match expression from the match-constraint list attached to \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The generated match expression.
         */
        CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer generateMatchExpression(const MolecularGraph& molgraph);

        /**
         * \brief Builds and (optionally) stores the top-level match expression of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing match expression. Otherwise, the existing one (if any) is returned unchanged.
         * \return The generated (or pre-existing) match expression.
         */
        CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer generateMatchExpression(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::RINGS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored full ring set.
         */
        CDPL_CHEM_API const FragmentList::SharedPointer& getRings(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::RINGS property of the molecular graph \a molgraph to \a rings.
         * \param molgraph The molecular graph for which to set the property value.
         * \param rings The new full ring set.
         */
        CDPL_CHEM_API void setRings(MolecularGraph& molgraph, const FragmentList::SharedPointer& rings);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::RINGS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearRings(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::RINGS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasRings(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the full set of rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The perceived ring set.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the full set of rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing ring set. Otherwise, the existing one (if any) is returned unchanged.
         * \return The perceived (or pre-existing) ring set.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::SSSR property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored Smallest Set of Smallest Rings.
         */
        CDPL_CHEM_API const FragmentList::SharedPointer& getSSSR(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::SSSR property of the molecular graph \a molgraph to \a sssr.
         * \param molgraph The molecular graph for which to set the property value.
         * \param sssr The new Smallest Set of Smallest Rings.
         */
        CDPL_CHEM_API void setSSSR(MolecularGraph& molgraph, const FragmentList::SharedPointer& sssr);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::SSSR property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearSSSR(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::SSSR property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasSSSR(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the Smallest Set of Smallest Rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return A shared pointer to the perceived SSSR.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the Smallest Set of Smallest Rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing SSSR. Otherwise, the existing one (if any) is returned unchanged.
         * \return The perceived (or pre-existing) SSSR.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Extracts the subset of the SSSR of the molecular graph \a src_molgraph whose rings consist of atoms and bonds of \a tgt_molgraph.
         * \param src_molgraph The source molecular graph whose SSSR is to be projected.
         * \param tgt_molgraph The target molecular graph providing the membership filter.
         * \return The extracted SSSR subset.
         */
        CDPL_CHEM_API FragmentList::SharedPointer extractSSSRSubset(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph);

        /**
         * \brief Extracts the SSSR subset of the molecular graph \a src_molgraph that fits within \a tgt_molgraph and (optionally) stores it on the latter.
         * \param src_molgraph The source molecular graph whose SSSR is to be projected.
         * \param tgt_molgraph The target molecular graph that receives the projected SSSR.
         * \param overwrite If \c true, replaces any existing SSSR on \a tgt_molgraph.
         * \return The extracted (or pre-existing) SSSR subset.
         */
        CDPL_CHEM_API FragmentList::SharedPointer extractSSSRSubset(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::CYCLIC_SUBSTRUCTURE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored cyclic substructure.
         */
        CDPL_CHEM_API const Fragment::SharedPointer& getCyclicSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::CYCLIC_SUBSTRUCTURE property of the molecular graph \a molgraph to \a substruct.
         * \param molgraph The molecular graph for which to set the property value.
         * \param substruct The new cyclic substructure.
         */
        CDPL_CHEM_API void setCyclicSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::CYCLIC_SUBSTRUCTURE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearCyclicSubstructure(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::CYCLIC_SUBSTRUCTURE property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCyclicSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the cyclic substructure (union of all rings) of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The perceived cyclic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the cyclic substructure of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing cyclic substructure. Otherwise, the existing one (if any) is returned unchanged.
         * \return The perceived (or pre-existing) cyclic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::COMPONENTS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored connected-component list.
         */
        CDPL_CHEM_API const FragmentList::SharedPointer& getComponents(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::COMPONENTS property of the molecular graph \a molgraph to \a comps.
         * \param molgraph The molecular graph for which to set the property value.
         * \param comps The new connected-component list.
         */
        CDPL_CHEM_API void setComponents(MolecularGraph& molgraph, const FragmentList::SharedPointer& comps);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::COMPONENTS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearComponents(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::COMPONENTS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComponents(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the connected components of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The perceived connected-component list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the connected components of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing component list. Otherwise, the existing one (if any) is returned unchanged.
         * \return The perceived (or pre-existing) component list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::COMPONENT_GROUPS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored component-group fragment list.
         */
        CDPL_CHEM_API const FragmentList::SharedPointer& getComponentGroups(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::COMPONENT_GROUPS property of the molecular graph \a molgraph to \a comp_groups.
         * \param molgraph The molecular graph for which to set the property value.
         * \param comp_groups The new component-group fragment list.
         */
        CDPL_CHEM_API void setComponentGroups(MolecularGraph& molgraph, const FragmentList::SharedPointer& comp_groups);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::COMPONENT_GROUPS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearComponentGroups(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::COMPONENT_GROUPS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasComponentGroups(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the component groups of the molecular graph \a molgraph (from atom-level Chem::AtomProperty::COMPONENT_GROUP_ID values).
         * \param molgraph The molecular graph to inspect.
         * \return The perceived component-group fragment list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the component groups of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing component-group list. Otherwise, the existing one (if any) is returned unchanged.
         * \return The perceived (or pre-existing) component-group list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::CONFORMATION_INDEX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored zero-based conformation index.
         */
        CDPL_CHEM_API std::size_t getConformationIndex(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::CONFORMATION_INDEX property of the molecular graph \a molgraph to \a index.
         * \param molgraph The molecular graph for which to set the property value.
         * \param index The new zero-based conformation index.
         */
        CDPL_CHEM_API void setConformationIndex(MolecularGraph& molgraph, std::size_t index);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::CONFORMATION_INDEX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearConformationIndex(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::CONFORMATION_INDEX property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasConformationIndex(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::CONFORMER_ENERGIES property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored per-conformer energy array.
         */
        CDPL_CHEM_API const Util::DArray::SharedPointer& getConformerEnergies(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::CONFORMER_ENERGIES property of the molecular graph \a molgraph to \a energies.
         * \param molgraph The molecular graph for which to set the property value.
         * \param energies The new per-conformer energy array.
         */
        CDPL_CHEM_API void setConformerEnergies(MolecularGraph& molgraph, const Util::DArray::SharedPointer& energies);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::CONFORMER_ENERGIES property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearConformerEnergies(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::CONFORMER_ENERGIES property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasConformerEnergies(const MolecularGraph& molgraph);


        /**
         * \brief Overwrites the conformation at index \a conf_idx with the supplied coordinates and energy.
         * \param molgraph The molecular graph to modify.
         * \param conf_idx The zero-based conformation index.
         * \param coords The 3D coordinates of the conformation.
         * \param energy The energy associated with the conformation.
         */
        CDPL_CHEM_API void setConformation(MolecularGraph& molgraph, std::size_t conf_idx, const Math::Vector3DArray& coords, double energy);

        /**
         * \brief Appends a new conformation built from the supplied coordinates and energy.
         * \param molgraph The molecular graph to modify.
         * \param coords The 3D coordinates of the new conformation.
         * \param energy The energy associated with the new conformation.
         */
        CDPL_CHEM_API void addConformation(MolecularGraph& molgraph, const Math::Vector3DArray& coords, double energy);

        /**
         * \brief Returns the energy of the conformation at index \a conf_idx.
         * \param molgraph The molecular graph to query.
         * \param conf_idx The zero-based conformation index.
         * \return The energy of the requested conformation.
         */
        CDPL_CHEM_API double getConformationEnergy(const MolecularGraph& molgraph, std::size_t conf_idx);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::HASH_CODE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored 64-bit hash code.
         */
        CDPL_CHEM_API std::uint64_t getHashCode(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::HASH_CODE property of the molecular graph \a molgraph to \a hash_code.
         * \param molgraph The molecular graph for which to set the property value.
         * \param hash_code The new 64-bit hash code.
         */
        CDPL_CHEM_API void setHashCode(MolecularGraph& molgraph, std::uint64_t hash_code);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::HASH_CODE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearHashCode(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::HASH_CODE property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasHashCode(const MolecularGraph& molgraph);

        /**
         * \brief Computes a 64-bit hash code for \a molgraph taking into account the specified atom and bond properties.
         * \param molgraph The molecular graph to hash.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties enter the hash.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties enter the hash.
         * \param ord_h_deplete \c true to suppress ordinary hydrogens before hashing.
         * \return The computed hash code.
         */
        CDPL_CHEM_API std::uint64_t calcHashCode(const MolecularGraph& molgraph, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                 unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool ord_h_deplete = true);


        /**
         * \brief Collects every atom and bond of the molecular graph \a molgraph that carries a reaction-center flag into the fragment \a rxn_center.
         * \param molgraph The molecular graph to inspect.
         * \param rxn_center The output fragment receiving the reaction-center atoms and bonds.
         */
        CDPL_CHEM_API void extractReactionCenter(const MolecularGraph& molgraph, Fragment& rxn_center);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored stoichiometric number.
         */
        CDPL_CHEM_API double getStoichiometricNumber(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER property of the molecular graph \a molgraph to \a num.
         * \param molgraph The molecular graph for which to set the property value.
         * \param num The new stoichiometric number.
         */
        CDPL_CHEM_API void setStoichiometricNumber(MolecularGraph& molgraph, double num);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearStoichiometricNumber(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStoichiometricNumber(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_USER_INITIALS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL user initials.
         */
        CDPL_CHEM_API const std::string& getMDLUserInitials(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_USER_INITIALS property of the molecular graph \a molgraph to \a initials.
         * \param molgraph The molecular graph for which to set the property value.
         * \param initials The new MDL user initials.
         */
        CDPL_CHEM_API void setMDLUserInitials(MolecularGraph& molgraph, const std::string& initials);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_USER_INITIALS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLUserInitials(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_USER_INITIALS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLUserInitials(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL program name.
         */
        CDPL_CHEM_API const std::string& getMDLProgramName(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property of the molecular graph \a molgraph to \a name.
         * \param molgraph The molecular graph for which to set the property value.
         * \param name The new MDL program name.
         */
        CDPL_CHEM_API void setMDLProgramName(MolecularGraph& molgraph, const std::string& name);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLProgramName(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLProgramName(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL registry number.
         */
        CDPL_CHEM_API std::size_t getMDLRegistryNumber(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER property of the molecular graph \a molgraph to \a reg_no.
         * \param molgraph The molecular graph for which to set the property value.
         * \param reg_no The new MDL registry number.
         */
        CDPL_CHEM_API void setMDLRegistryNumber(MolecularGraph& molgraph, std::size_t reg_no);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLRegistryNumber(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLRegistryNumber(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph (see namespace Chem::MDLDataFormatVersion).
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored CTab version.
         */
        CDPL_CHEM_API unsigned int getMDLCTABVersion(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph to \a version (see namespace Chem::MDLDataFormatVersion).
         * \param molgraph The molecular graph for which to set the property value.
         * \param version The new CTab version.
         */
        CDPL_CHEM_API void setMDLCTABVersion(MolecularGraph& molgraph, unsigned int version);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLCTABVersion(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLCTABVersion(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::STRUCTURE_DATA property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL structure-data block.
         */
        CDPL_CHEM_API const StringDataBlock::SharedPointer& getStructureData(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::STRUCTURE_DATA property of the molecular graph \a molgraph to \a data.
         * \param molgraph The molecular graph for which to set the property value.
         * \param data The new MDL structure-data block.
         */
        CDPL_CHEM_API void setStructureData(MolecularGraph& molgraph, const StringDataBlock::SharedPointer& data);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::STRUCTURE_DATA property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearStructureData(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::STRUCTURE_DATA property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStructureData(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL coordinate dimensionality.
         */
        CDPL_CHEM_API std::size_t getMDLDimensionality(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property of the molecular graph \a molgraph to \a dim.
         * \param molgraph The molecular graph for which to set the property value.
         * \param dim The new MDL coordinate dimensionality.
         */
        CDPL_CHEM_API void setMDLDimensionality(MolecularGraph& molgraph, std::size_t dim);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLDimensionality(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLDimensionality(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL scaling factor 1.
         */
        CDPL_CHEM_API long getMDLScalingFactor1(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property of the molecular graph \a molgraph to \a factor.
         * \param molgraph The molecular graph for which to set the property value.
         * \param factor The new MDL scaling factor 1.
         */
        CDPL_CHEM_API void setMDLScalingFactor1(MolecularGraph& molgraph, long factor);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLScalingFactor1(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLScalingFactor1(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL scaling factor 2.
         */
        CDPL_CHEM_API double getMDLScalingFactor2(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property of the molecular graph \a molgraph to \a factor.
         * \param molgraph The molecular graph for which to set the property value.
         * \param factor The new MDL scaling factor 2.
         */
        CDPL_CHEM_API void setMDLScalingFactor2(MolecularGraph& molgraph, double factor);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLScalingFactor2(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLScalingFactor2(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_ENERGY property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL energy.
         */
        CDPL_CHEM_API double getMDLEnergy(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_ENERGY property of the molecular graph \a molgraph to \a energy.
         * \param molgraph The molecular graph for which to set the property value.
         * \param energy The new MDL energy.
         */
        CDPL_CHEM_API void setMDLEnergy(MolecularGraph& molgraph, double energy);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_ENERGY property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLEnergy(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_ENERGY property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLEnergy(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MDL chiral flag.
         */
        CDPL_CHEM_API bool getMDLChiralFlag(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property of the molecular graph \a molgraph to \a flag.
         * \param molgraph The molecular graph for which to set the property value.
         * \param flag The new MDL chiral flag.
         */
        CDPL_CHEM_API void setMDLChiralFlag(MolecularGraph& molgraph, bool flag);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMDLChiralFlag(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMDLChiralFlag(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph (see namespace Chem::MOL2MoleculeType).
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MOL2 molecule type.
         */
        CDPL_CHEM_API unsigned int getMOL2MoleculeType(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph to \a type (see namespace Chem::MOL2MoleculeType).
         * \param molgraph The molecular graph for which to set the property value.
         * \param type The new MOL2 molecule type.
         */
        CDPL_CHEM_API void setMOL2MoleculeType(MolecularGraph& molgraph, unsigned int type);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2MoleculeType(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2MoleculeType(const MolecularGraph& molgraph);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph (see namespace Chem::MOL2ChargeType).
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored MOL2 charge type.
         */
        CDPL_CHEM_API unsigned int getMOL2ChargeType(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph to \a type (see namespace Chem::MOL2ChargeType).
         * \param molgraph The molecular graph for which to set the property value.
         * \param type The new MOL2 charge type.
         */
        CDPL_CHEM_API void setMOL2ChargeType(MolecularGraph& molgraph, unsigned int type);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearMOL2ChargeType(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMOL2ChargeType(const MolecularGraph& molgraph);


        /**
         * \brief Builds the adjacency matrix of the molecular graph \a molgraph (entry \c (i,j) is the bond count between atoms \c i and \c j).
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output sparse matrix receiving the adjacency entries.
         */
        CDPL_CHEM_API void generateAdjacencyMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the atom/bond incidence matrix of the molecular graph \a molgraph (entry \c (i,j) is \c 1 if atom \c i is an endpoint of bond \c j).
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output sparse matrix receiving the incidence entries.
         */
        CDPL_CHEM_API void generateIncidenceMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the bond-order matrix of the molecular graph \a molgraph (entry \c (i,j) is the order of the bond between atoms \c i and \c j).
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output sparse matrix receiving the bond-order entries.
         */
        CDPL_CHEM_API void generateBondMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the bond-electron-count matrix of the molecular graph \a molgraph (entry \c (i,j) is the number of bonding electrons between atoms \c i and \c j).
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output sparse matrix receiving the bond-electron counts.
         */
        CDPL_CHEM_API void generateBondElectronMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds a matrix combining bond order and atom type information of the endpoints of every bond in \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output sparse matrix receiving the combined entries.
         */
        CDPL_CHEM_API void generateBondAtomTypeMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored topological-distance matrix.
         */
        CDPL_CHEM_API const Math::ULMatrix::SharedPointer& getTopologicalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph to \a mtx.
         * \param molgraph The molecular graph for which to set the property value.
         * \param mtx The new topological-distance matrix.
         */
        CDPL_CHEM_API void setTopologicalDistanceMatrix(MolecularGraph& molgraph, const Math::ULMatrix::SharedPointer& mtx);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearTopologicalDistanceMatrix(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasTopologicalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Computes and (optionally) stores the topological-distance matrix of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing topological-distance matrix.
         * \return The computed (or pre-existing) matrix.
         */
        CDPL_CHEM_API Math::ULMatrix::SharedPointer calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes the topological-distance matrix of the molecular graph \a molgraph into the supplied \a mtx.
         * \param molgraph The molecular graph to inspect.
         * \param mtx The output dense matrix receiving the topological distances.
         */
        CDPL_CHEM_API void calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

        /**
         * \brief Extracts the topological-distance sub-matrix of the molecular graph \a src_molgraph that covers the atoms of \a tgt_molgraph and (optionally) stores it on the latter.
         * \param src_molgraph The source molecular graph providing the full matrix.
         * \param tgt_molgraph The target molecular graph providing the atom subset and (optionally) receiving the sub-matrix.
         * \param overwrite If \c true, replaces any existing matrix on \a tgt_molgraph.
         * \return The extracted (or pre-existing) sub-matrix.
         */
        CDPL_CHEM_API Math::ULMatrix::SharedPointer extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite);

        /**
         * \brief Extracts the topological-distance sub-matrix of the molecular graph \a src_molgraph that covers the atoms of \a tgt_molgraph into the supplied \a mtx.
         * \param src_molgraph The source molecular graph providing the full matrix.
         * \param tgt_molgraph The target molecular graph providing the atom subset.
         * \param mtx The output dense matrix receiving the sub-matrix entries.
         */
        CDPL_CHEM_API void extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph, Math::ULMatrix& mtx);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored geometrical-distance matrix.
         */
        CDPL_CHEM_API const Math::DMatrix::SharedPointer& getGeometricalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph to \a mtx.
         * \param molgraph The molecular graph for which to set the property value.
         * \param mtx The new geometrical-distance matrix.
         */
        CDPL_CHEM_API void setGeometricalDistanceMatrix(MolecularGraph& molgraph, const Math::DMatrix::SharedPointer& mtx);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearGeometricalDistanceMatrix(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasGeometricalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Computes and (optionally) stores the geometrical-distance matrix of the molecular graph \a molgraph from its 3D coordinates.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing geometrical-distance matrix.
         * \return The computed (or pre-existing) matrix.
         */
        CDPL_CHEM_API Math::DMatrix::SharedPointer calcGeometricalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::AROMATIC_SUBSTRUCTURE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored aromatic substructure.
         */
        CDPL_CHEM_API const Fragment::SharedPointer& getAromaticSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::AROMATIC_SUBSTRUCTURE property of the molecular graph \a molgraph to \a substruct.
         * \param molgraph The molecular graph for which to set the property value.
         * \param substruct The new aromatic substructure.
         */
        CDPL_CHEM_API void setAromaticSubstructure(MolecularGraph& molgraph, const Fragment::SharedPointer& substruct);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::AROMATIC_SUBSTRUCTURE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearAromaticSubstructure(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::AROMATIC_SUBSTRUCTURE property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasAromaticSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the aromatic substructure of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The perceived aromatic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the aromatic substructure of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing aromatic substructure.
         * \return The perceived (or pre-existing) aromatic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored pi-electron-system list.
         */
        CDPL_CHEM_API const ElectronSystemList::SharedPointer& getPiElectronSystems(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph to \a pi_systems.
         * \param molgraph The molecular graph for which to set the property value.
         * \param pi_systems The new pi-electron-system list.
         */
        CDPL_CHEM_API void setPiElectronSystems(MolecularGraph& molgraph, const ElectronSystemList::SharedPointer& pi_systems);

        /**
         * \brief Clears the value of the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to clear the property value.
         */
        CDPL_CHEM_API void clearPiElectronSystems(MolecularGraph& molgraph);

        /**
         * \brief Tells whether the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph is set.
         * \param molgraph The molecular graph for which to query the property value.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasPiElectronSystems(const MolecularGraph& molgraph);

        /**
         * \brief Perceives the pi-electron systems of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The perceived pi-electron-system list.
         */
        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and (optionally) stores the pi-electron systems of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect/modify.
         * \param overwrite If \c true, replaces any existing pi-electron-system list.
         * \return The perceived (or pre-existing) pi-electron-system list.
         */
        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Generates a \e SMILES string for \a molgraph.
         * \param molgraph The molecular graph to encode.
         * \param smiles The string to receive the generated SMILES.
         * \param canonical \c true to emit a canonical SMILES; \c false for an arbitrary atom ordering.
         * \param ord_h_deplete \c true to suppress ordinary hydrogens.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties to encode.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties to encode.
         * \return \c true on success, and \c false if an unrecoverable error was encountered.
         */
        CDPL_CHEM_API bool generateSMILES(const MolecularGraph& molgraph, std::string& smiles, bool canonical = false,
                                          bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                          unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        /**
         * \brief Generates an InChI string for \a molgraph using the InChI C-API.
         * \param molgraph The molecular graph to encode.
         * \param inchi The string to receive the generated InChI.
         * \param options The InChI C-API option string (see Chem::ControlParameter::INCHI_OUTPUT_OPTIONS).
         * \param dim The dimensionality of the atomic coordinates to forward to the InChI library (0 = no coordinates).
         * \return The InChI return code (see namespace Chem::INCHIReturnCode).
         */
        CDPL_CHEM_API int generateINCHI(const MolecularGraph& molgraph, std::string& inchi,
                                        const std::string& options = ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
                                        std::size_t        dim     = 0);

        /**
         * \brief Generates an InChIKey for \a molgraph using the InChI C-API.
         * \param molgraph The molecular graph to encode.
         * \param inchi_key The string to receive the generated InChIKey.
         * \return The InChI return code (see namespace Chem::INCHIReturnCode).
         */
        CDPL_CHEM_API int generateINCHIKey(const MolecularGraph& molgraph, std::string& inchi_key);

        /**
         * \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph \a molgraph according to a user-supplied comparator.
         * \param molgraph The molecular graph to canonicalize.
         * \param func The atom comparator that defines the canonical ordering.
         * \param atoms \c true to sort atoms.
         * \param atom_nbrs \c true to sort each atom's neighbor list.
         * \param bonds \c true to sort bonds.
         * \param bond_atoms \c true to reorder the start/end atoms of each bond according to the comparator.
         */
        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, const AtomCompareFunction& func, bool atoms = true,
                                        bool atom_nbrs = true, bool bonds = true, bool bond_atoms = false);

        /**
         * \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph \a molgraph according to the canonical-numbering attached to its atoms.
         * \param molgraph The molecular graph to canonicalize.
         * \param atoms \c true to sort atoms.
         * \param atom_nbrs \c true to sort each atom's neighbor list.
         * \param bonds \c true to sort bonds.
         * \param bond_atoms \c true to reorder the start/end atoms of each bond.
         */
        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, bool atoms = true, bool atom_nbrs = true,
                                        bool bonds = true, bool bond_atoms = false);

        /**
         * \brief Computes 2D atom coordinates for \a molgraph and stores them as Chem::AtomProperty::COORDINATES_2D.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing 2D coordinates. Otherwise, leaves atoms that already carry coordinates unchanged.
         */
        CDPL_CHEM_API void calc2DCoordinates(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Aligns \a molgraph's 2D coordinates so that the atoms of \a atoms come to lie at the reference coordinates \a ref_coords.
         * \param molgraph The molecular graph to align.
         * \param atoms The atoms used as alignment anchors.
         * \param ref_coords Reference 2D coordinates of the alignment-anchor atoms.
         * \param fix_bond_stereo If \c true, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomContainer& atoms, const Math::Vector2DArray& ref_coords, bool fix_bond_stereo = true);

        /**
         * \brief Aligns \a molgraph's 2D coordinates onto a reference atom mapping.
         * \param molgraph The molecular graph to align.
         * \param ref_atom_mpg The atom mapping providing the target atom→atom correspondence.
         * \param fix_bond_stereo If \c true, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomMapping& ref_atom_mpg, bool fix_bond_stereo = true);

        /**
         * \brief Aligns \a molgraph's 2D coordinates onto those of \a ref_molgraph, using either a maximum-common-substructure search or substructure matching.
         * \param molgraph The molecular graph to align.
         * \param ref_molgraph The reference molecular graph providing the target coordinates.
         * \param use_mcss If \c true, the atom correspondence is found by maximum-common-substructure search. Otherwise, by substructure matching.
         * \param fix_bond_stereo If \c true, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, bool use_mcss, bool fix_bond_stereo = true);

        /**
         * \brief Aligns \a molgraph's 2D coordinates onto those of \a ref_molgraph, using \a substr_ptn as the explicit substructure pattern.
         * \param molgraph The molecular graph to align.
         * \param ref_molgraph The reference molecular graph providing the target coordinates.
         * \param substr_ptn The substructure pattern that defines the atom correspondence.
         * \param fix_bond_stereo If \c true, postprocess bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, const MolecularGraph& substr_ptn, bool fix_bond_stereo = true);


        /**
         * \brief Computes 3D coordinates for the hydrogen atoms of the molecular graph \a molgraph from the geometry of their non-hydrogen neighbors.
         * \param molgraph The molecular graph to modify.
         * \param undef_only If \c true, only hydrogens without prior 3D coordinates are placed. If \c false, all hydrogen coordinates are recomputed.
         */
        CDPL_CHEM_API void calcHydrogen3DCoordinates(MolecularGraph& molgraph, bool undef_only = true);

        /**
         * \brief Derives 2D wedge/hash bond stereo flags for the bonds of the molecular graph \a molgraph from the atoms' stereo descriptors and 2D layout.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing 2D stereo flags.
         */
        CDPL_CHEM_API void calcBond2DStereoFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores CIP priorities for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing CIP-priority values.
         */
        CDPL_CHEM_API void calcCIPPriorities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores topological-symmetry classes for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing symmetry-class IDs.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties enter the perception.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties enter the perception.
         * \param inc_impl_h If \c true, implicit hydrogens are treated as if they were explicit. Otherwise, they are ignored.
         */
        CDPL_CHEM_API void perceiveSymmetryClasses(MolecularGraph& molgraph, bool overwrite,
                                                   unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                   unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool inc_impl_h = true);

        /**
         * \brief Computes and stores canonical atom numbers for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing canonical numbers.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties enter the numbering.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties enter the numbering.
         */
        CDPL_CHEM_API void calcCanonicalNumbering(MolecularGraph& molgraph, bool overwrite,
                                                  unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                  unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        /**
         * \brief Computes and stores Morgan numbers for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing Morgan numbers.
         */
        CDPL_CHEM_API void calcMorganNumbering(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores implicit-hydrogen counts for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing implicit-hydrogen counts.
         */
        CDPL_CHEM_API void calcImplicitHydrogenCounts(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores formal charges for the atoms of the molecular graph \a molgraph from their valence environment.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing formal charges.
         */
        CDPL_CHEM_API void calcFormalCharges(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores hybridization states for the atoms of the molecular graph \a molgraph from their valence environment.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing hybridization states.
         */
        CDPL_CHEM_API void perceiveHybridizationStates(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives bond orders for the bonds of the molecular graph \a molgraph from atom geometry and ligand environment.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing bond orders.
         */
        CDPL_CHEM_API void perceiveBondOrders(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Assigns Kekulé bond orders to the aromatic bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         */
        CDPL_CHEM_API void kekulizeBonds(MolecularGraph& molgraph);

        /**
         * \brief Flags the atoms of the molecular graph \a molgraph that qualify as stereo centers under the supplied criteria.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing stereo-center flags.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_inv_n \c true to reject inversion-prone nitrogen centers.
         * \param check_quart_n \c true to accept positively charged quaternary nitrogen centers.
         * \param check_plan_n \c true to reject planar nitrogen centers.
         * \param check_amide_n \c true to reject amide-nitrogen centers.
         * \param check_res_ctrs \c true to reject centers participating in resonance.
         */
        CDPL_CHEM_API void perceiveAtomStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_inv_n = true, bool check_quart_n = true, bool check_plan_n = true,
                                                     bool check_amide_n = true, bool check_res_ctrs = true);

        /**
         * \brief Flags the bonds of the molecular graph \a molgraph that qualify as stereo centers under the supplied criteria.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing stereo-center flags.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_term_n \c true to reject bonds to terminal nitrogen atoms.
         * \param check_order \c true to require that the bond order matches a stereogenic pattern.
         * \param min_ring_size The minimum ring size required for ring bonds to qualify.
         */
        CDPL_CHEM_API void perceiveBondStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_term_n = true, bool check_order = true, std::size_t min_ring_size = 8);

        /**
         * \brief Computes and stores MDL parities for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing MDL parities.
         */
        CDPL_CHEM_API void calcMDLParities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores stereo descriptors for the atoms of the molecular graph \a molgraph from their geometric layout.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing stereo descriptors.
         * \param dim The dimensionality of the atomic coordinates to use (\e 2 or \e 3).
         * \param check_stc_flag If \c true, descriptors are only computed for atoms whose Chem::AtomProperty::STEREO_CENTER_FLAG is set.
         */
        CDPL_CHEM_API void calcAtomStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1, bool check_stc_flag = true);

        /**
         * \brief Derives atom stereo descriptors of the molecular graph \a molgraph from previously-assigned MDL parities.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing stereo descriptors.
         */
        CDPL_CHEM_API void calcAtomStereoDescriptorsFromMDLParities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores stereo descriptors for the bonds of the molecular graph \a molgraph from their geometric layout.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing stereo descriptors.
         * \param dim The dimensionality of the atomic coordinates to use (\e 2 or \e 3).
         * \param check_stc_flag If \c true, descriptors are only computed for bonds whose Chem::BondProperty::STEREO_CENTER_FLAG is set.
         */
        CDPL_CHEM_API void calcBondStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1,
                                                     bool check_stc_flag = true);

        /**
         * \brief Computes and stores CIP configuration labels for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing CIP configuration labels.
         */
        CDPL_CHEM_API void calcAtomCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores CIP configuration labels for the bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing CIP configuration labels.
         */
        CDPL_CHEM_API void calcBondCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the atom-level match-constraint list \a constr on every atom of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param constr The match-constraint list to assign.
         * \param overwrite If \c true, replaces any existing per-atom constraints. If \c false, leaves atoms that already carry a list unchanged.
         */
        CDPL_CHEM_API void setAtomMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        /**
         * \brief Sets the bond-level match-constraint list \a constr on every bond of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param constr The match-constraint list to assign.
         * \param overwrite If \c true, replaces any existing per-bond constraints. If \c false, leaves bonds that already carry a list unchanged.
         */
        CDPL_CHEM_API void setBondMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        /**
         * \brief Generates and stores match expressions for every atom, bond and the molecular graph itself.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing match expressions. If \c false, leaves items that already carry a match expression unchanged.
         */
        CDPL_CHEM_API void generateMatchExpressions(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Generates and stores textual representations of the match expressions of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing match-expression strings.
         */
        CDPL_CHEM_API void generateMatchExpressionStrings(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Prepares the molecular graph \a molgraph for use as a substructure search query (precomputes match expressions and required cached properties).
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, recomputes derived data. If \c false, leaves up-to-date data unchanged.
         */
        CDPL_CHEM_API void initSubstructureSearchQuery(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Prepares the molecular graph \a molgraph for use as a substructure search target (precomputes required cached properties).
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, recomputes derived data. If \c false, leaves up-to-date data unchanged.
         */
        CDPL_CHEM_API void initSubstructureSearchTarget(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives aromaticity and sets the corresponding atom/bond aromaticity flags on the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing aromaticity flags.
         */
        CDPL_CHEM_API void setAromaticityFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives ring membership and sets the corresponding atom/bond ring flags on the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing ring flags.
         */
        CDPL_CHEM_API void setRingFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the atom types of the molecular graph \a molgraph from their element symbols.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing atom types.
         */
        CDPL_CHEM_API void setAtomTypesFromSymbols(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the atom symbols of the molecular graph \a molgraph from their atom types.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing atom symbols.
         */
        CDPL_CHEM_API void setAtomSymbolsFromTypes(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives Sybyl atom types for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, replaces any existing Sybyl atom types.
         */
        CDPL_CHEM_API void perceiveSybylAtomTypes(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Returns the subset of the aromatic rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The aromatic rings.
         */
        CDPL_CHEM_API FragmentList::SharedPointer getAromaticRings(const MolecularGraph& molgraph);

        /**
         * \brief Returns the subset of the SSSR of the molecular graph \a molgraph that contains only aromatic rings,
         * \param molgraph The molecular graph to inspect.
         * \return The aromatic-SSSR subset.
         */
        CDPL_CHEM_API FragmentList::SharedPointer getAromaticSSSRSubset(const MolecularGraph& molgraph);

        /**
         * \brief Tells whether the molecular graph \a molgraph contains the atoms and/or bonds of \a sub_molgraph.
         * \param molgraph The host molecular graph.
         * \param sub_molgraph The candidate sub-graph.
         * \param atoms If \c true, every atom of \a sub_molgraph must be a member of the molecular graph \a molgraph.
         * \param bonds If \c true, every bond of \a sub_molgraph must be a member of the molecular graph \a molgraph.
         * \return \c true if the requested containment relations all hold, and \c false otherwise.
         */
        CDPL_CHEM_API bool containsMolecularGraph(const MolecularGraph& molgraph, const MolecularGraph& sub_molgraph,
                                                  bool atoms = true, bool bonds = true);

        /**
         * \brief Collects the fragments in \a frag_list that are fully contained in the molecular graph \a molgraph into \a cont_frag_list.
         * \param molgraph The host molecular graph.
         * \param frag_list The candidate fragment list.
         * \param cont_frag_list The output fragment list receiving the matches.
         * \param append If \c true, matches are appended to \a cont_frag_list. Otherwise, it is cleared first.
         * \param atoms If \c true, atom membership is required for a match.
         * \param bonds If \c true, bond membership is required for a match.
         */
        CDPL_CHEM_API void getContainedFragments(const MolecularGraph& molgraph, const FragmentList& frag_list,
                                                 FragmentList& cont_frag_list, bool append = false, bool atoms = true,
                                                 bool bonds = true);

        /**
         * \brief Collects the fragments in \a frag_list that contain the molecular graph \a molgraph into \a cont_frag_list.
         * \param molgraph The query molecular graph.
         * \param frag_list The candidate fragment list.
         * \param cont_frag_list The output fragment list receiving the matches.
         * \param append If \c true, matches are appended to \a cont_frag_list. Otherwise, it is cleared first.
         * \param atoms If \c true, atom membership is required for a match.
         * \param bonds If \c true, bond membership is required for a match.
         */
        CDPL_CHEM_API void getContainingFragments(const MolecularGraph& molgraph, const FragmentList& frag_list,
                                                  FragmentList& cont_frag_list, bool append = false, bool atoms = true,
                                                  bool bonds = true);

        /**
         * \brief Translates the atoms/bonds of \a src_frag to the corresponding atoms/bonds of \a tgt_molgraph and stores them in \a tgt_frag.
         * \param src_molgraph The source molecular graph providing the original atoms/bonds.
         * \param src_frag The fragment defining the atom/bond subset to translate (a fragment of the molecular graph \a src_molgraph).
         * \param tgt_molgraph The target molecular graph providing the translated atoms/bonds.
         * \param tgt_frag The output fragment receiving the translated atoms/bonds.
         * \param append If \c true, atoms/bonds are appended to \a tgt_frag. Otherwise, it is cleared first.
         */
        CDPL_CHEM_API void translateFragment(const MolecularGraph& src_molgraph, const Fragment& src_frag,
                                             const MolecularGraph& tgt_molgraph, Fragment& tgt_frag, bool append = false);

        /**
         * \brief Translates every fragment in \a src_frag_list to the corresponding fragments on \a tgt_molgraph.
         * \param src_molgraph The source molecular graph providing the original atoms/bonds.
         * \param src_frag_list The fragments to translate (fragments of the molecular graph \a src_molgraph).
         * \param tgt_molgraph The target molecular graph providing the translated atoms/bonds.
         * \param tgt_frag_list The output fragment list receiving the translated fragments.
         * \param append If \c true, fragments are appended to \a tgt_frag_list. Otherwise, it is cleared first.
         */
        CDPL_CHEM_API void translateFragments(const MolecularGraph& src_molgraph, const FragmentList& src_frag_list,
                                              const MolecularGraph& tgt_molgraph, FragmentList& tgt_frag_list, bool append = false);

        /**
         * \brief Splits the molecular graph \a molgraph into connected fragments by removing the bonds flagged in \a split_bond_mask.
         * \param molgraph The molecular graph to split.
         * \param frag_list The output fragment list receiving the resulting fragments.
         * \param split_bond_mask Bit mask selecting the bonds to be virtually removed before fragmentation (bit \c i corresponds to the bond at index \c i in \a molgraph).
         * \param append If \c true, fragments are appended to \a frag_list. Otherwise, it is cleared first.
         */
        CDPL_CHEM_API void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list,
                                              const Util::BitSet& split_bond_mask, bool append = false);

        /**
         * \brief Returns the number of bonds of the molecular graph \a molgraph whose connected atoms are likewise contained in \a molgraph.
         * \param molgraph The molecular graph to inspect.
         * \return The count of non-dangling bonds.
         */
        CDPL_CHEM_API std::size_t getCompleteBondCount(const MolecularGraph& molgraph);

        /**
         * \brief Computes the basic per-atom/per-bond properties (aromaticity, ring info, etc.) of the molecular graph \a molgraph.
         * \param molgraph The molecular graph to modify.
         * \param overwrite If \c true, recomputes derived data. If \c false, leaves up-to-date data unchanged.
         * \since 1.1
         */
        CDPL_CHEM_API void calcBasicProperties(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Builds the molecule \a result_mol from the molecular graph \a molgraph by replacing all substructures matching the \e SMARTS patterns in \a search_ptns with \a result_ptn.
         * \param molgraph The source molecular graph.
         * \param result_mol The molecule receiving the edited result.
         * \param search_ptns A whitespace-separated list of \e SMARTS patterns matching the substructures to replace.
         * \param result_ptn The \e SMARTS replacement pattern.
         * \param exclude_ptns A whitespace-separated list of \e SMARTS patterns matching substructures that shall be retained even if they also match \a search_ptns.
         * \return The number of applied substructure replacements.
         * \since 1.3
         */
        CDPL_CHEM_API std::size_t editSubstructures(const MolecularGraph& molgraph, Molecule& result_mol, const std::string& search_ptns,
                                                    const std::string& result_ptn, const std::string& exclude_ptns = std::string());
        
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
