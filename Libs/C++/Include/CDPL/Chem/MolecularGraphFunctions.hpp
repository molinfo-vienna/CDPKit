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
         * \return The stored match constraint list.
         */
        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property of the molecular graph \a molgraph to \a constr.
         * \param molgraph The molecular graph for which to set the property value.
         * \param constr The new match constraint list.
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
         * \return The stored match expression.
         */
        CDPL_CHEM_API const MatchExpression<MolecularGraph>::SharedPointer& getMatchExpression(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MATCH_EXPRESSION property of the molecular graph \a molgraph to \a expr.
         * \param molgraph The molecular graph for which to set the property value.
         * \param expr The new match expression.
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
         * \brief Builds a match expression from the match constraints currently attached to the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The generated match expression.
         */
        CDPL_CHEM_API MatchExpression<MolecularGraph>::SharedPointer generateMatchExpression(const MolecularGraph& molgraph);

        /**
         * \brief Builds and stores the match expression of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing match expression property should be replaced.
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
         * \param molgraph The molecular graph.
         * \return The perceived ring set.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveRings(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the full set of rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing ring set property should be replaced.
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
         * \brief Perceives the SSSR of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return A shared pointer to the perceived SSSR.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the SSSR of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing SSSR property should be replaced.
         * \return The perceived (or pre-existing) SSSR.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveSSSR(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Extracts the SSSR subset of the molecular graph \a src_molgraph whose rings consist of atoms and bonds of \a tgt_molgraph.
         * \param src_molgraph The source molecular graph whose SSSR is to be projected.
         * \param tgt_molgraph The target molecular graph acting as filter.
         * \return The extracted SSSR subset.
         */
        CDPL_CHEM_API FragmentList::SharedPointer extractSSSRSubset(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph);

        /**
         * \brief Extracts the SSSR subset of the molecular graph \a src_molgraph whose rings consist of atoms and bonds of \a tgt_molgraph
         *         and stores it on the latter.
         * \param src_molgraph The source molecular graph whose SSSR is to be projected.
         * \param tgt_molgraph The target molecular graph which receives the projected SSSR and acts as filter.
         * \param overwrite Specifies whether an already existing \a tgt_molgraph SSSR property should be replaced.
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
         * \param molgraph The molecular graph.
         * \return The perceived cyclic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveCyclicSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the cyclic substructure (union of all rings) of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing cyclic substructure property should be replaced.
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
         * \param molgraph The molecular graph.
         * \return The perceived component list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponents(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the connected components of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing component list property should be replaced.
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
         * \brief Perceives the component groups of the molecular graph \a molgraph.
         *
         * Component groups are generated by merging components whose atoms have the
         * same Chem::AtomProperty::COMPONENT_GROUP_ID property value.
         *
         * \param molgraph The molecular graph.
         * \return The perceived component group fragment list.
         */
        CDPL_CHEM_API FragmentList::SharedPointer perceiveComponentGroups(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and optionally stores the component groups of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing component groups property should be replaced.
         * \return The perceived (or pre-existing) component group fragment list.
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
         * \return The stored conformer energy array.
         */
        CDPL_CHEM_API const Util::DArray::SharedPointer& getConformerEnergies(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::CONFORMER_ENERGIES property of the molecular graph \a molgraph to \a energies.
         * \param molgraph The molecular graph for which to set the property value.
         * \param energies The new conformer energy array.
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
         * \param molgraph The molecular graph.
         * \param conf_idx The zero-based conformation index.
         * \param coords The 3D coordinates of the conformation.
         * \param energy The energy associated with the conformation.
         * \throw Base::IndexError if \a conf_idx is out of the valid range.
         */
        CDPL_CHEM_API void setConformation(MolecularGraph& molgraph, std::size_t conf_idx, const Math::Vector3DArray& coords, double energy);

        /**
         * \brief Appends a new conformation built from the supplied coordinates and energy.
         * \param molgraph The molecular graph.
         * \param coords The 3D coordinates of the new conformation.
         * \param energy The energy associated with the new conformation.
         */
        CDPL_CHEM_API void addConformation(MolecularGraph& molgraph, const Math::Vector3DArray& coords, double energy);

        /**
         * \brief Returns the energy of the conformation at index \a conf_idx.
         * \param molgraph The molecular graph to query.
         * \param conf_idx The zero-based conformation index.
         * \return The energy of the requested conformation.
         * \throw Base::IndexError if \a conf_idx is out of the valid range.
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
         * \brief Computes a 64-bit hash code for the molecular graph \a molgraph taking into account the specified atom and bond properties.
         * \param molgraph The molecular graph.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties contribute to the hash.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties contribute to the hash.
         * \param ord_h_deplete \c true to suppress ordinary hydrogens before hashing.
         * \return The computed hash code.
         */
        CDPL_CHEM_API std::uint64_t calcHashCode(const MolecularGraph& molgraph, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                 unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool ord_h_deplete = true);


        /**
         * \brief Collects every atom and bond of the molecular graph \a molgraph that carries a reaction-center flag into the fragment \a rxn_center.
         * \param molgraph The molecular graph.
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
         * \return The stored \e MDL user initials.
         */
        CDPL_CHEM_API const std::string& getMDLUserInitials(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_USER_INITIALS property of the molecular graph \a molgraph to \a initials.
         * \param molgraph The molecular graph for which to set the property value.
         * \param initials The new \e MDL user initials.
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
         * \return The stored \e MDL program name.
         */
        CDPL_CHEM_API const std::string& getMDLProgramName(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property of the molecular graph \a molgraph to \a name.
         * \param molgraph The molecular graph for which to set the property value.
         * \param name The new \e MDL program name.
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
         * \return The stored \e MDL registry number.
         */
        CDPL_CHEM_API std::size_t getMDLRegistryNumber(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_REGISTRY_NUMBER property of the molecular graph \a molgraph to \a reg_no.
         * \param molgraph The molecular graph for which to set the property value.
         * \param reg_no The new \e MDL registry number.
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
         * \brief Returns the value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored CTAB version (see namespace Chem::MDLDataFormatVersion).
         */
        CDPL_CHEM_API unsigned int getMDLCTABVersion(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property of the molecular graph \a molgraph to \a version.
         * \param molgraph The molecular graph for which to set the property value.
         * \param version The new CTAB version (see namespace Chem::MDLDataFormatVersion).
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
         * \return The stored structure data block.
         */
        CDPL_CHEM_API const StringDataBlock::SharedPointer& getStructureData(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::STRUCTURE_DATA property of the molecular graph \a molgraph to \a data.
         * \param molgraph The molecular graph for which to set the property value.
         * \param data The new structure data block.
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
         * \return The stored \e MDL coordinate dimensionality.
         */
        CDPL_CHEM_API std::size_t getMDLDimensionality(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property of the molecular graph \a molgraph to \a dim.
         * \param molgraph The molecular graph for which to set the property value.
         * \param dim The new \e MDL coordinate dimensionality.
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
         * \return The stored \e MDL scaling factor 1.
         */
        CDPL_CHEM_API long getMDLScalingFactor1(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property of the molecular graph \a molgraph to \a factor.
         * \param molgraph The molecular graph for which to set the property value.
         * \param factor The new \e MDL scaling factor 1.
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
         * \return The stored \e MDL scaling factor 2.
         */
        CDPL_CHEM_API double getMDLScalingFactor2(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property of the molecular graph \a molgraph to \a factor.
         * \param molgraph The molecular graph for which to set the property value.
         * \param factor The new \e MDL scaling factor 2.
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
         * \return The stored \e MDL energy.
         */
        CDPL_CHEM_API double getMDLEnergy(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_ENERGY property of the molecular graph \a molgraph to \a energy.
         * \param molgraph The molecular graph for which to set the property value.
         * \param energy The new \e MDL energy.
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
         * \return The stored \e MDL chiral flag.
         */
        CDPL_CHEM_API bool getMDLChiralFlag(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property of the molecular graph \a molgraph to \a flag.
         * \param molgraph The molecular graph for which to set the property value.
         * \param flag The new \e MDL chiral flag.
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
         * \brief Returns the value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> molecule type (see namespace Chem::MOL2MoleculeType).
         */
        CDPL_CHEM_API unsigned int getMOL2MoleculeType(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property of the molecular graph \a molgraph to \a type.
         * \param molgraph The molecular graph for which to set the property value.
         * \param type The new <em>Sybyl MOL2</em> molecule type (see namespace Chem::MOL2MoleculeType).
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
         * \brief Returns the value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored <em>Sybyl MOL2</em> charge type (see namespace Chem::MOL2ChargeType).
         */
        CDPL_CHEM_API unsigned int getMOL2ChargeType(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property of the molecular graph \a molgraph to \a type.
         * \param molgraph The molecular graph for which to set the property value.
         * \param type The new <em>Sybyl MOL2</em> charge type (see namespace Chem::MOL2ChargeType).
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
         * \brief Builds the adjacency matrix of the molecular graph \a molgraph.
         *
         * Entry \c (i,j) is \e 1 if atoms \e i and \e j are connected by a bond and \e 0 if there is no bond.
         *
         * \param molgraph The molecular graph.
         * \param mtx The output adjacency matrix.
         */
        CDPL_CHEM_API void generateAdjacencyMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the atom/bond incidence matrix of the molecular graph \a molgraph.
         *
         * Entry \c (i,j) is \e 1 if atom \e i is an endpoint of bond \e j.
         *
         * \param molgraph The molecular graph.
         * \param mtx The output incidence matrix.
         */
        CDPL_CHEM_API void generateIncidenceMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the bond order matrix of the molecular graph \a molgraph.
         *
         * Entry \c (i,j) is the order of the bond between atoms \e i and \e j and \e 0 if there is no bond.
         *
         * \param molgraph The molecular graph.
         * \param mtx The output bond matrix.
         */
        CDPL_CHEM_API void generateBondMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds the bond-electron matrix of the molecular graph \a molgraph.
         *
         * Entry \c (i,j) is the order of the bond between atoms \e i and \e j and \e 0 if there is no bond.
         * Diagonal entries \c (i,i) store the free valence electron count of each atom \e i.
         *
         * \param molgraph The molecular graph.
         * \param mtx The output bond-electron matrix.
         */
        CDPL_CHEM_API void generateBondElectronMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);

        /**
         * \brief Builds a matrix combining bond order and atom type information of the endpoints of every bond in \a molgraph.
         *
         * Entry \c (i,j) is the order of the bond between atoms \e i and \e j and \e 0 if there is no bond.
         * Diagonal entries \c (i,i) store the type of each atom \e i.
         *
         * \param molgraph The molecular graph.
         * \param mtx The output bond and atom type matrix.
         */
        CDPL_CHEM_API void generateBondAtomTypeMatrix(const MolecularGraph& molgraph, Math::SparseULMatrix& mtx);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored topological distance matrix.
         */
        CDPL_CHEM_API const Math::ULMatrix::SharedPointer& getTopologicalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::TOPOLOGICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph to \a mtx.
         * \param molgraph The molecular graph for which to set the property value.
         * \param mtx The new topological distance matrix.
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
         * \brief Computes and stores the topological distance matrix of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing distance matrix property should be replaced.
         * \return The computed (or pre-existing) topological distance matrix.
         */
        CDPL_CHEM_API Math::ULMatrix::SharedPointer calcTopologicalDistanceMatrix(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes the topological distance matrix of the molecular graph \a molgraph into the supplied matrix \a mtx.
         * \param molgraph The molecular graph.
         * \param mtx The output topological distance matrix.
         */
        CDPL_CHEM_API void calcTopologicalDistanceMatrix(const MolecularGraph& molgraph, Math::ULMatrix& mtx);

        /**
         * \brief Extracts the topological distance sub-matrix of the molecular graph \a src_molgraph that covers the atoms of \a tgt_molgraph
         *        and stores it on the latter.
         * \param src_molgraph The source molecular graph providing the full matrix.
         * \param tgt_molgraph The target molecular graph providing the atom subset and (optionally) receiving the sub-matrix.
         * \param overwrite Specifies whether an already existing distance matrix property should be replaced.
         * \return The extracted (or pre-existing) topological distance matrix.
         */
        CDPL_CHEM_API Math::ULMatrix::SharedPointer extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, MolecularGraph& tgt_molgraph, bool overwrite);

        /**
         * \brief Extracts the topological distance sub-matrix of the molecular graph \a src_molgraph that covers the atoms of \a tgt_molgraph
         *        into the supplied matrix \a mtx.
         * \param src_molgraph The source molecular graph providing the full matrix.
         * \param tgt_molgraph The target molecular graph providing the atom subset.
         * \param mtx The output topological distance matrix.
         */
        CDPL_CHEM_API void extractTopologicalDistanceSubMatrix(const MolecularGraph& src_molgraph, const MolecularGraph& tgt_molgraph, Math::ULMatrix& mtx);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored geometrical distance matrix.
         */
        CDPL_CHEM_API const Math::DMatrix::SharedPointer& getGeometricalDistanceMatrix(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::GEOMETRICAL_DISTANCE_MATRIX property of the molecular graph \a molgraph to \a mtx.
         * \param molgraph The molecular graph for which to set the property value.
         * \param mtx The new geometrical distance matrix.
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
         * \brief Computes and stores the geometrical distance matrix of the molecular graph \a molgraph from its 3D coordinates.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing distance matrix property should be replaced.
         * \return The computed (or pre-existing) geometrical distance matrix.
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
         * \brief Perceives the aromatic substructure (union of all aromatic atoms/bonds) of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The perceived aromatic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the aromatic substructure of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing aromatic substructure property should be replaced.
         * \return The perceived (or pre-existing) aromatic substructure.
         */
        CDPL_CHEM_API Fragment::SharedPointer perceiveAromaticSubstructure(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Returns the value of the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph.
         * \param molgraph The molecular graph for which to return the property value.
         * \return The stored &pi;-electron system list.
         */
        CDPL_CHEM_API const ElectronSystemList::SharedPointer& getPiElectronSystems(const MolecularGraph& molgraph);

        /**
         * \brief Sets the value of the Chem::MolecularGraphProperty::PI_ELECTRON_SYSTEMS property of the molecular graph \a molgraph to \a pi_systems.
         * \param molgraph The molecular graph for which to set the property value.
         * \param pi_systems The new &pi;-electron system list.
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
         * \brief Perceives the &pi;-electron systems of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The perceived &pi;-electron system list.
         */
        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(const MolecularGraph& molgraph);

        /**
         * \brief Perceives and stores the &pi;-electron systems of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether an already existing electron system property should be replaced.
         * \return The perceived (or pre-existing) &pi;-electron system list.
         */
        CDPL_CHEM_API ElectronSystemList::SharedPointer perceivePiElectronSystems(MolecularGraph& molgraph, bool overwrite);


        /**
         * \brief Generates a \e SMILES string for the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param smiles The string receiving the generated SMILES.
         * \param canonical \c true to emit a canonical SMILES.
         * \param ord_h_deplete \c true to suppress the output of ordinary hydrogens.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties to encode.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties to encode.
         * \return \c true on success, and \c false if an unrecoverable error was encountered.
         */
        CDPL_CHEM_API bool generateSMILES(const MolecularGraph& molgraph, std::string& smiles, bool canonical = false,
                                          bool ord_h_deplete = true, unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                          unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        /**
         * \brief Generates an InChI string for the molecular graph \a molgraph using the InChI C-API.
         * \param molgraph The molecular graph.
         * \param inchi The string receiving the generated InChI.
         * \param options The InChI C-API option string (see Chem::ControlParameter::INCHI_OUTPUT_OPTIONS).
         * \param dim The dimensionality of the output atomic coordinates (see Chem::INCHIMolecularGraphWriter).
         * \return The InChI return code (see namespace Chem::INCHIReturnCode).
         */
        CDPL_CHEM_API int generateINCHI(const MolecularGraph& molgraph, std::string& inchi,
                                        const std::string& options = ControlParameterDefault::INCHI_OUTPUT_OPTIONS,
                                        std::size_t dim = 0);

        /**
         * \brief Generates an InChIKey for the molecular graph \a molgraph using the InChI C-API.
         * \param molgraph The molecular graph.
         * \param inchi_key The string receiving the generated InChIKey.
         * \return The InChI return code (see namespace Chem::INCHIReturnCode).
         */
        CDPL_CHEM_API int generateINCHIKey(const MolecularGraph& molgraph, std::string& inchi_key);

        /**
         * \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph \a molgraph according to a user-supplied comparator.
         * \param molgraph The molecular graph.
         * \param func The atom comparator that defines the canonical ordering.
         * \param atoms \c true to sort atoms.
         * \param atom_nbrs \c true to sort each atom's neighbor list.
         * \param bonds \c true to sort bonds.
         * \param bond_atoms \c true to reorder the start/end atoms of each bond according to the comparator.
         */
        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, const AtomCompareFunction& func, bool atoms = true,
                                        bool atom_nbrs = true, bool bonds = true, bool bond_atoms = false);

        /**
         * \brief Reorders the atoms (and optionally their neighbors and bonds) of the molecular graph \a molgraph according to the canonical number
         *        property value of its atoms.
         * \param molgraph The molecular graph.
         * \param atoms \c true to sort atoms.
         * \param atom_nbrs \c true to sort each atom's neighbor list.
         * \param bonds \c true to sort bonds.
         * \param bond_atoms \c true to reorder the start/end atoms of each bond.
         */
        CDPL_CHEM_API void canonicalize(MolecularGraph& molgraph, bool atoms = true, bool atom_nbrs = true,
                                        bool bonds = true, bool bond_atoms = false);

        /**
         * \brief Computes 2D atom coordinates for the molecular graph \a molgraph and stores them as corresponding atom properties.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing 2D coordinates properties should be replaced.
         */
        CDPL_CHEM_API void calc2DCoordinates(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Transforms the 2D atom coordinates of \a molgraph so that the 2D coordinates of \a atoms are aligned with the reference coordinates \a ref_coords.
         * \param molgraph The molecular graph to align.
         * \param atoms The atoms used as alignment anchors.
         * \param ref_coords Reference 2D coordinates of the alignment anchor atoms.
         * \param fix_bond_stereo If \c true, postprocess 2D bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomContainer& atoms, const Math::Vector2DArray& ref_coords, bool fix_bond_stereo = true);

        /**
         * \brief Transforms the 2D atom coordinates of \a molgraph so that the 2D coordinates of the mapped atoms are aligned.
         * \param molgraph The molecular graph to align.
         * \param ref_atom_mpg The atom mapping providing the target atom→atom correspondence.
         * \param fix_bond_stereo If \c true, postprocess 2D bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const AtomMapping& ref_atom_mpg, bool fix_bond_stereo = true);

        /**
         * \brief Aligns the 2D atom coordinates of \a molgraph with those of \a ref_molgraph, using either a maximum-common-substructure search or substructure matching.
         * \param molgraph The molecular graph to align.
         * \param ref_molgraph The reference molecular graph providing the target coordinates.
         * \param use_mcss If \c true, the atom correspondence is found by maximum common substructure search. Otherwise, by substructure matching.
         * \param fix_bond_stereo If \c true, postprocess 2D bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, bool use_mcss, bool fix_bond_stereo = true);

        /**
         * \brief Aligns the 2D atom coordinates of \a molgraph with those of \a ref_molgraph, using \a substr_ptn as the explicit substructure search pattern.
         * \param molgraph The molecular graph to align.
         * \param ref_molgraph The reference molecular graph providing the target coordinates.
         * \param substr_ptn The substructure search pattern that defines the atoms to align.
         * \param fix_bond_stereo If \c true, postprocess 2D bond stereo flags so that they remain consistent with the aligned coordinates.
         * \return \c true if the alignment succeeded, and \c false otherwise.
         * \since 1.3
         */
        CDPL_CHEM_API bool align2DCoordinates(MolecularGraph& molgraph, const MolecularGraph& ref_molgraph, const MolecularGraph& substr_ptn, bool fix_bond_stereo = true);


        /**
         * \brief Computes 3D coordinates for the hydrogen atoms of the molecular graph \a molgraph from the 3D coordinates of their non-hydrogen neighbors.
         * \param molgraph The molecular graph.
         * \param undef_only If \c true, only hydrogens without prior 3D coordinates are placed. If \c false, all hydrogen coordinates are recomputed.
         */
        CDPL_CHEM_API void calcHydrogen3DCoordinates(MolecularGraph& molgraph, bool undef_only = true);

        /**
         * \brief Derives 2D wedge/hash bond stereo flags for the bonds of the molecular graph \a molgraph from the atoms' stereo descriptors and 2D coordinates.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing 2D bond stereo flag properties should be replaced.
         */
        CDPL_CHEM_API void calcBond2DStereoFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores topological CIP priorities for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing CIP priority properties should be replaced.
         * \see [\ref TCIP]
         */
        CDPL_CHEM_API void calcCIPPriorities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores topological symmetry classes for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing symmetry class ID properties should be replaced.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties affect the perception.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties affect the perception.
         * \param inc_impl_h If \c true, implicit hydrogens are treated as if they were explicit. Otherwise, they are ignored.
         */
        CDPL_CHEM_API void perceiveSymmetryClasses(MolecularGraph& molgraph, bool overwrite,
                                                   unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                   unsigned int bond_flags = BondPropertyFlag::DEFAULT, bool inc_impl_h = true);

        /**
         * \brief Computes and stores canonical atom numbers for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing canonical number properties should be replaced.
         * \param atom_flags A bitmask of Chem::AtomPropertyFlag flags controlling which atomic properties affect the numbering.
         * \param bond_flags A bitmask of Chem::BondPropertyFlag flags controlling which bond properties affect the numbering.
         */
        CDPL_CHEM_API void calcCanonicalNumbering(MolecularGraph& molgraph, bool overwrite,
                                                  unsigned int atom_flags = AtomPropertyFlag::DEFAULT,
                                                  unsigned int bond_flags = BondPropertyFlag::DEFAULT);

        /**
         * \brief Computes and stores Morgan numbers for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing morgan number properties should be replaced.
         */
        CDPL_CHEM_API void calcMorganNumbering(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores implicit hydrogen counts for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing hydrogen count properties should be replaced.
         */
        CDPL_CHEM_API void calcImplicitHydrogenCounts(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores formal charges for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing formal charge properties should be replaced.
         */
        CDPL_CHEM_API void calcFormalCharges(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores hybridization states for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing hybridization state properties should be replaced.
         */
        CDPL_CHEM_API void perceiveHybridizationStates(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives bond orders for the bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing bond order properties should be replaced.
         */
        CDPL_CHEM_API void perceiveBondOrders(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Assigns Kekulé bond orders to the aromatic bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         */
        CDPL_CHEM_API void kekulizeBonds(MolecularGraph& molgraph);

        /**
         * \brief Flags the atoms of the molecular graph \a molgraph that qualify as stereo centers under the supplied criteria.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing stereo center flag properties should be replaced.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_inv_n \c true to reject inversion-prone nitrogen centers.
         * \param check_quart_n \c true to accept positively charged quaternary nitrogen centers.
         * \param check_plan_n \c true to reject planar nitrogen centers.
         * \param check_amide_n \c true to reject amide nitrogen centers.
         * \param check_res_ctrs \c true to reject centers participating in resonance.
         */
        CDPL_CHEM_API void perceiveAtomStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_inv_n = true, bool check_quart_n = true, bool check_plan_n = true,
                                                     bool check_amide_n = true, bool check_res_ctrs = true);

        /**
         * \brief Flags the bonds of the molecular graph \a molgraph that qualify as stereo centers under the supplied criteria.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing bond order properties should be replaced.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_term_n \c true to reject bonds to terminal nitrogen atoms.
         * \param check_order \c true to require that the bond order matches a stereogenic pattern.
         * \param min_ring_size The minimum ring size required for ring bonds to qualify.
         */
        CDPL_CHEM_API void perceiveBondStereoCenters(MolecularGraph& molgraph, bool overwrite, bool check_asym = true,
                                                     bool check_term_n = true, bool check_order = true, std::size_t min_ring_size = 8);

        /**
         * \brief Computes and stores \e MDL parities for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing MDL parity properties should be replaced.
         */
        CDPL_CHEM_API void calcMDLParities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores stereo descriptors for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing stereo descriptor properties should be replaced.
         * \param dim The dimensionality of the atomic coordinates to use
         *            (\e 2 = 2D, \e 3 = 3D, \e 0 = recalc. existing descriptor, other values = use any information available).
         * \param check_stc_flag If \c true, descriptors are only computed for atoms whose Chem::AtomProperty::STEREO_CENTER_FLAG property is \c true.
         */
        CDPL_CHEM_API void calcAtomStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1, bool check_stc_flag = true);

        /**
         * \brief Derives atom stereo descriptors of the molecular graph \a molgraph from previously-assigned \e MDL parities.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing stereo descriptor properties should be replaced.
         */
        CDPL_CHEM_API void calcAtomStereoDescriptorsFromMDLParities(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores stereo descriptors for the bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing stereo descriptor properties should be replaced.
         * \param dim The dimensionality of the atomic coordinates to use
         *            (\e 2 = 2D, \e 3 = 3D, \e 0 = recalc. existing descriptor, other values = use any information available).
         * \param check_stc_flag If \c true, descriptors are only computed for bonds whose Chem::BondProperty::STEREO_CENTER_FLAG property is \c true.
         */
        CDPL_CHEM_API void calcBondStereoDescriptors(MolecularGraph& molgraph, bool overwrite, std::size_t dim = 1,
                                                     bool check_stc_flag = true);

        /**
         * \brief Computes and stores CIP configuration labels for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing CIP configuration properties should be replaced.
         */
        CDPL_CHEM_API void calcAtomCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Computes and stores CIP configuration labels for the bonds of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing CIP configuration properties should be replaced.
         */
        CDPL_CHEM_API void calcBondCIPConfigurations(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the match constraint list \a constr on every atom of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param constr The match constraint list to assign.
         * \param overwrite Specifies whether already existing match constraint properties should be replaced.
         */
        CDPL_CHEM_API void setAtomMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        /**
         * \brief Sets the match constraint list \a constr on every bond of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param constr The match constraint list to assign.
         * \param overwrite Specifies whether already existing match constraint properties should be replaced.
         */
        CDPL_CHEM_API void setBondMatchConstraints(MolecularGraph& molgraph, const MatchConstraintList::SharedPointer& constr,
                                                   bool overwrite);

        /**
         * \brief Generates and stores match expressions for every atom, bond and the molecular graph \a molgraph itself.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing match expression properties should be replaced.
         */
        CDPL_CHEM_API void generateMatchExpressions(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Generates and stores textual representations of the atom/bond match expressions of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing match expression string properties should be replaced.
         */
        CDPL_CHEM_API void generateMatchExpressionStrings(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Prepares the molecular graph \a molgraph for use as a substructure search query.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing property values should be replaced.
         */
        CDPL_CHEM_API void initSubstructureSearchQuery(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Prepares the molecular graph \a molgraph for use as a substructure search target.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing property values should be replaced.
         */
        CDPL_CHEM_API void initSubstructureSearchTarget(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives aromaticity and sets the corresponding atom/bond aromaticity flags on the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing aromaticity flag properties should be replaced.
         */
        CDPL_CHEM_API void setAromaticityFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives ring membership and sets the corresponding atom/bond ring flags on the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing ring flag properties should be replaced.
         */
        CDPL_CHEM_API void setRingFlags(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the atom types of the molecular graph \a molgraph from their element symbols.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing atom type properties should be replaced.
         */
        CDPL_CHEM_API void setAtomTypesFromSymbols(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Sets the atom symbols of the molecular graph \a molgraph from their atom types.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing atom symbol properties should be replaced.
         */
        CDPL_CHEM_API void setAtomSymbolsFromTypes(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Perceives and assigns <em>Sybyl MOL2</em> atom types for the atoms of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing atom type properties should be replaced.
         */
        CDPL_CHEM_API void perceiveSybylAtomTypes(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Returns the subset of the aromatic rings of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \return The aromatic rings.
         */
        CDPL_CHEM_API FragmentList::SharedPointer getAromaticRings(const MolecularGraph& molgraph);

        /**
         * \brief Returns the subset of the SSSR of the molecular graph \a molgraph that contains only aromatic rings,
         * \param molgraph The molecular graph.
         * \return The aromatic SSSR subset.
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
         * \param split_bond_mask Bit mask selecting the bonds to be virtually removed before fragmentation
         *                        (bit \e i corresponds to the bond at index \e i in \a molgraph).
         * \param append If \c true, fragments are appended to \a frag_list. Otherwise, it is cleared first.
         */
        CDPL_CHEM_API void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list,
                                              const Util::BitSet& split_bond_mask, bool append = false);

        /**
         * \brief Returns the number of bonds of the molecular graph \a molgraph whose connected atoms are likewise contained in \a molgraph.
         * \param molgraph The molecular graph.
         * \return The count of non-dangling bonds.
         */
        CDPL_CHEM_API std::size_t getCompleteBondCount(const MolecularGraph& molgraph);

        /**
         * \brief Computes basic atom/bond/molecular graph properties (aromaticity, SSSR, etc.) of the molecular graph \a molgraph.
         * \param molgraph The molecular graph.
         * \param overwrite Specifies whether already existing property values should be replaced.
         * \since 1.1
         */
        CDPL_CHEM_API void calcBasicProperties(MolecularGraph& molgraph, bool overwrite);

        /**
         * \brief Builds the molecule \a result_mol from the molecular graph \a molgraph by replacing all
         *        substructures matching the \e SMARTS patterns in \a search_ptns with \a result_ptn.
         *
         * A molecule editing operation is specified via a string of one or more \e SMARTS patterns (\a search_ptns)
         * describing the substructures to edit, optional substructure exclude patterns (\a exclude_ptns) and a \e SMILES
         * string (\a result_ptn) encoding the specific atom and bond modifications to perform. If multiple search and/or exclude patterns
         * are specified then they need to be separated by a whitespace character.
         *
         * In the substructure search pattern(s), any atoms to be edited and/or atoms connected by bonds to be modified must be labeled
         * by a unique non-zero integer number (by means of a colon followed the integer number at the end of the \e SMARTS atom specification).
         * These numeric ids are used to establish an unambiguous mapping between the atoms/bonds of the search pattern
         * and the \e SMILES string encoding the editing instructions.
         * As mentioned above, the atom/bond editing operations are all specified by means of a simple \e SMILES string. For the purpose of
         * substructure editing, the \e SMILES format has been extended by additional atom type and bond order symbols that allow to mark atom/bonds
         * for deletion or act as a 'do not change' marker for atom type or bond order.
         *
         * Editing result \e SMILES strings have to be composed according to the following rules:
         * - Atoms of the molecule matching labeled search pattern atoms are referenced by their numeric id (likewise specified by means of a colon followed
         *   by the integer number at the end of the \e SMILES atom specification)
         * - A bond between two labeled atoms in the result \e SMILES string will be mapped to the bond of the molecule that matched the corresponding bond of the search pattern
         * - If such a bond of the molecule does not exist it will be created with the specified bond order
         * - A molecule bond connecting two atoms that match labeled search pattern atoms which is not occurring in the result \e SMILES string will be left unchanged
         * - A molecule atom matching a labeled search pattern atom which is not occurring in the result \e SMILES string will be left unchanged
         * - A labeled atom in the result \e SMILES string with a numeric id that does not occur in the search pattern will be created with specified
         *   properties (symbol, form. charge, isotope, chirality, ...)
         * - Any unlabeled atoms in the result \e SMILES string will be created with the specified properties (symbol, form. charge, isotope, chirality, ...)
         * - Bonds to/between unlabeled result \e SMILES string atoms will be created with the specified bond order
         * - For a mapped molecule atom only those properties (symbol, form. charge, isotope, chirality, ...) that were specified for the corresponding result
         *   \e SMILES string atom will be modified
         * - The special result \e SMILES string atom type symbol <tt>x</tt> (only valid in brackets) results in the removal of the mapped molecule atom including any incident bonds
         * - The special result \e SMILES string atom type symbol <tt>~</tt> (only valid in brackets) indicates that the type of the mapped molecule atom shall be left unchanged
         * - The special result \e SMILES string bond order symbol <tt>x</tt> results in the removal of the mapped molecule bond
         * - The special result \e SMILES string bond order symbol <tt>~</tt> indicates that the order of the mapped molecule bond shall be left unchanged
         *
         * \param molgraph The source molecular graph.
         * \param result_mol The molecule receiving the edited result.
         * \param search_ptns A whitespace-separated list of \e SMARTS patterns specifying the substructures to replace.
         * \param result_ptn The \e SMARTS replacement pattern.
         * \param exclude_ptns A whitespace-separated list of \e SMARTS patterns specifying substructures that shall be
         *                     retained even if they also match \a search_ptns.
         * \return The number of performed substructure replacements.
         * \since 1.3
         */
        CDPL_CHEM_API std::size_t editSubstructures(const MolecularGraph& molgraph, Molecule& result_mol, const std::string& search_ptns,
                                                    const std::string& result_ptn, const std::string& exclude_ptns = std::string());
        
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHFUNCTIONS_HPP
