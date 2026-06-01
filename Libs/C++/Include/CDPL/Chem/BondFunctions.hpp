/* 
 * BondFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Bond instances.
 */

#ifndef CDPL_CHEM_BONDFUNCTIONS_HPP
#define CDPL_CHEM_BONDFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Chem
    {

        class StereoDescriptor;

        /**
         * \brief Returns the Chem::BondProperty::ORDER property of \a bond.
         * \param bond The bond to query.
         * \return The stored bond order.
         */
        CDPL_CHEM_API std::size_t getOrder(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::ORDER property of \a bond to \a order.
         * \param bond The bond to modify.
         * \param order The new bond order.
         */
        CDPL_CHEM_API void setOrder(Bond& bond, std::size_t order);

        /**
         * \brief Removes the Chem::BondProperty::ORDER property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearOrder(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::ORDER property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasOrder(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::RING_FLAG property of \a bond.
         * \param bond The bond to query.
         * \return \c true if the bond is flagged as part of any ring, and \c false otherwise.
         */
        CDPL_CHEM_API bool getRingFlag(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::RING_FLAG property of \a bond to \a in_ring.
         * \param bond The bond to modify.
         * \param in_ring \c true to flag the bond as part of a ring, and \c false to flag it as acyclic.
         */
        CDPL_CHEM_API void setRingFlag(Bond& bond, bool in_ring);

        /**
         * \brief Removes the Chem::BondProperty::RING_FLAG property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearRingFlag(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::RING_FLAG property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasRingFlag(const Bond& bond);


        /**
         * \brief Tells whether \a bond is a member of any fragment in \a frag_list whose size matches \a size.
         * \param bond The bond to query.
         * \param frag_list The list of fragments to search.
         * \param size The required fragment size (in number of atoms).
         * \return \c true if at least one matching fragment contains \a bond, and \c false otherwise.
         */
        CDPL_CHEM_API bool isInFragmentOfSize(const Bond& bond, const FragmentList& frag_list, std::size_t size);

        /**
         * \brief Returns the size (in atoms) of the smallest fragment in \a frag_list that contains \a bond.
         * \param bond The bond to query.
         * \param frag_list The list of fragments to search.
         * \return The smallest containing fragment's size, or zero if no fragment contains \a bond.
         */
        CDPL_CHEM_API std::size_t getSizeOfSmallestContainingFragment(const Bond& bond, const FragmentList& frag_list);

        /**
         * \brief Returns the size (in atoms) of the largest fragment in \a frag_list that contains \a bond.
         * \param bond The bond to query.
         * \param frag_list The list of fragments to search.
         * \return The largest containing fragment's size, or zero if no fragment contains \a bond.
         */
        CDPL_CHEM_API std::size_t getSizeOfLargestContainingFragment(const Bond& bond, const FragmentList& frag_list);

        /**
         * \brief Returns the number of fragments in \a frag_list that contain \a bond.
         * \param bond The bond to query.
         * \param frag_list The list of fragments to search.
         * \return The number of containing fragments.
         */
        CDPL_CHEM_API std::size_t getNumContainingFragments(const Bond& bond, const FragmentList& frag_list);

        /**
         * \brief Collects the fragments in \a frag_list that contain \a bond into \a cont_frag_list.
         * \param bond The bond to query.
         * \param frag_list The list of fragments to search.
         * \param cont_frag_list The output fragment list receiving the matches.
         * \param append If \c true, matches are appended to \a cont_frag_list; otherwise it is cleared first.
         */
        CDPL_CHEM_API void getContainingFragments(const Bond& bond, const FragmentList& frag_list, FragmentList& cont_frag_list, bool append = false);


        /**
         * \brief Returns the Chem::BondProperty::AROMATICITY_FLAG property of \a bond.
         * \param bond The bond to query.
         * \return \c true if the bond is flagged as aromatic, and \c false otherwise.
         */
        CDPL_CHEM_API bool getAromaticityFlag(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::AROMATICITY_FLAG property of \a bond to \a aromatic.
         * \param bond The bond to modify.
         * \param aromatic \c true to flag the bond as aromatic, and \c false to flag it as non-aromatic.
         */
        CDPL_CHEM_API void setAromaticityFlag(Bond& bond, bool aromatic);

        /**
         * \brief Removes the Chem::BondProperty::AROMATICITY_FLAG property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearAromaticityFlag(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::AROMATICITY_FLAG property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasAromaticityFlag(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::STEREO_2D_FLAG property of \a bond (see namespace Chem::BondStereoFlag).
         * \param bond The bond to query.
         * \return The stored 2D stereo flag.
         */
        CDPL_CHEM_API unsigned int get2DStereoFlag(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::STEREO_2D_FLAG property of \a bond to \a flag (see namespace Chem::BondStereoFlag).
         * \param bond The bond to modify.
         * \param flag The new 2D stereo flag value.
         */
        CDPL_CHEM_API void set2DStereoFlag(Bond& bond, unsigned int flag);

        /**
         * \brief Removes the Chem::BondProperty::STEREO_2D_FLAG property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clear2DStereoFlag(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::STEREO_2D_FLAG property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool has2DStereoFlag(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::CIP_CONFIGURATION property of \a bond (see namespace Chem::CIPDescriptor).
         * \param bond The bond to query.
         * \return The stored CIP configuration label.
         */
        CDPL_CHEM_API unsigned int getCIPConfiguration(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::CIP_CONFIGURATION property of \a bond to \a config (see namespace Chem::CIPDescriptor).
         * \param bond The bond to modify.
         * \param config The new CIP configuration label.
         */
        CDPL_CHEM_API void setCIPConfiguration(Bond& bond, unsigned int config);

        /**
         * \brief Removes the Chem::BondProperty::CIP_CONFIGURATION property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearCIPConfiguration(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::CIP_CONFIGURATION property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasCIPConfiguration(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::STEREO_DESCRIPTOR property of \a bond.
         * \param bond The bond to query.
         * \return The stored stereo descriptor.
         */
        CDPL_CHEM_API const StereoDescriptor& getStereoDescriptor(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::STEREO_DESCRIPTOR property of \a bond to \a descr.
         * \param bond The bond to modify.
         * \param descr The new stereo descriptor.
         */
        CDPL_CHEM_API void setStereoDescriptor(Bond& bond, const StereoDescriptor& descr);

        /**
         * \brief Removes the Chem::BondProperty::STEREO_DESCRIPTOR property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearStereoDescriptor(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::STEREO_DESCRIPTOR property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStereoDescriptor(const Bond& bond);

        /**
         * \brief Computes the stereo descriptor for \a bond based on the geometry of \a molgraph.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \param dim The dimensionality of the atomic coordinates to use (\e 2 or \e 3).
         * \return The computed stereo descriptor.
         */
        CDPL_CHEM_API StereoDescriptor calcStereoDescriptor(const Bond& bond, const MolecularGraph& molgraph, std::size_t dim = 1);

        /**
         * \brief Derives the bond configuration label from the supplied descriptor and 3D coordinates.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \param descr The stereo descriptor whose configuration is to be evaluated.
         * \param coords The 3D atomic coordinates used by the evaluation.
         * \return The derived configuration label (see namespace Chem::BondConfiguration).
         */
        CDPL_CHEM_API unsigned int calcConfiguration(const Bond& bond, const MolecularGraph& molgraph, const StereoDescriptor& descr,
                                                     const Math::Vector3DArray& coords);


        /**
         * \brief Returns the Chem::BondProperty::STEREO_CENTER_FLAG property of \a bond.
         * \param bond The bond to query.
         * \return \c true if the bond is flagged as a stereo center, and \c false otherwise.
         */
        CDPL_CHEM_API bool getStereoCenterFlag(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::STEREO_CENTER_FLAG property of \a bond to \a is_center.
         * \param bond The bond to modify.
         * \param is_center \c true to flag the bond as a stereo center, and \c false otherwise.
         */
        CDPL_CHEM_API void setStereoCenterFlag(Bond& bond, bool is_center);

        /**
         * \brief Removes the Chem::BondProperty::STEREO_CENTER_FLAG property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearStereoCenterFlag(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::STEREO_CENTER_FLAG property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasStereoCenterFlag(const Bond& bond);

        /**
         * \brief Tells whether \a bond qualifies as a stereo center in the context of \a molgraph.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \param check_asym \c true to enforce non-equivalent ligand environments.
         * \param check_term_n \c true to reject bonds to terminal nitrogen atoms.
         * \param check_order \c true to require that the bond order matches a stereogenic pattern.
         * \param min_ring_size If \a bond is a ring bond, the containing ring must have at least this size to qualify.
         * \return \c true if the bond qualifies as a stereo center under the given conditions, and \c false otherwise.
         */
        CDPL_CHEM_API bool isStereoCenter(const Bond& bond, const MolecularGraph& molgraph, bool check_asym = true,
                                          bool check_term_n = true, bool check_order = true, std::size_t min_ring_size = 8);


        /**
         * \brief Returns the Chem::BondProperty::DIRECTION property of \a bond (see namespace Chem::BondDirection).
         * \param bond The bond to query.
         * \return The stored SMILES/SMARTS bond-direction descriptor.
         */
        CDPL_CHEM_API unsigned int getDirection(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::DIRECTION property of \a bond to \a dir (see namespace Chem::BondDirection).
         * \param bond The bond to modify.
         * \param dir The new bond-direction descriptor.
         */
        CDPL_CHEM_API void setDirection(Bond& bond, unsigned int dir);

        /**
         * \brief Removes the Chem::BondProperty::DIRECTION property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearDirection(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::DIRECTION property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasDirection(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::REACTION_CENTER_STATUS property of \a bond (see namespace Chem::ReactionCenterStatus).
         * \param bond The bond to query.
         * \return The stored reaction-center status.
         */
        CDPL_CHEM_API unsigned int getReactionCenterStatus(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::REACTION_CENTER_STATUS property of \a bond to \a status (see namespace Chem::ReactionCenterStatus).
         * \param bond The bond to modify.
         * \param status The new reaction-center status.
         */
        CDPL_CHEM_API void setReactionCenterStatus(Bond& bond, unsigned int status);

        /**
         * \brief Removes the Chem::BondProperty::REACTION_CENTER_STATUS property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearReactionCenterStatus(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::REACTION_CENTER_STATUS property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasReactionCenterStatus(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::MATCH_CONSTRAINTS property of \a bond.
         * \param bond The bond to query.
         * \return The stored match-constraint list.
         */
        CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::MATCH_CONSTRAINTS property of \a bond to \a constr.
         * \param bond The bond to modify.
         * \param constr The new match-constraint list.
         */
        CDPL_CHEM_API void setMatchConstraints(Bond& bond, const MatchConstraintList::SharedPointer& constr);

        /**
         * \brief Removes the Chem::BondProperty::MATCH_CONSTRAINTS property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearMatchConstraints(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::MATCH_CONSTRAINTS property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchConstraints(const Bond& bond);


        /**
         * \brief Returns the Chem::BondProperty::MATCH_EXPRESSION property of \a bond.
         * \param bond The bond to query.
         * \return The stored bond-level match expression.
         */
        CDPL_CHEM_API const MatchExpression<Bond, MolecularGraph>::SharedPointer& getMatchExpression(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::MATCH_EXPRESSION property of \a bond to \a expr.
         * \param bond The bond to modify.
         * \param expr The new bond-level match expression.
         */
        CDPL_CHEM_API void setMatchExpression(Bond& bond, const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr);

        /**
         * \brief Removes the Chem::BondProperty::MATCH_EXPRESSION property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearMatchExpression(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::MATCH_EXPRESSION property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpression(const Bond& bond);

        /**
         * \brief Builds a bond-level match expression from the match-constraint list attached to \a bond.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \return The generated match expression.
         */
        CDPL_CHEM_API MatchExpression<Bond, MolecularGraph>::SharedPointer generateMatchExpression(const Bond& bond, const MolecularGraph& molgraph);


        /**
         * \brief Returns the Chem::BondProperty::MATCH_EXPRESSION_STRING property of \a bond.
         * \param bond The bond to query.
         * \return The stored match-expression string.
         */
        CDPL_CHEM_API const std::string& getMatchExpressionString(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::MATCH_EXPRESSION_STRING property of \a bond to \a expr_str.
         * \param bond The bond to modify.
         * \param expr_str The new match-expression string.
         */
        CDPL_CHEM_API void setMatchExpressionString(Bond& bond, const std::string& expr_str);

        /**
         * \brief Removes the Chem::BondProperty::MATCH_EXPRESSION_STRING property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearMatchExpressionString(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::MATCH_EXPRESSION_STRING property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasMatchExpressionString(const Bond& bond);

        /**
         * \brief Writes a textual representation of the bond-level match expression of \a bond into \a str.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \param str The output string receiving the match-expression text.
         */
        CDPL_CHEM_API void generateMatchExpressionString(const Bond& bond, const MolecularGraph& molgraph, std::string& str);


        /**
         * \brief Returns the Chem::BondProperty::SYBYL_TYPE property of \a bond (see namespace Chem::SybylBondType).
         * \param bond The bond to query.
         * \return The stored Sybyl bond-type code.
         */
        CDPL_CHEM_API unsigned int getSybylType(const Bond& bond);

        /**
         * \brief Sets the Chem::BondProperty::SYBYL_TYPE property of \a bond to \a type (see namespace Chem::SybylBondType).
         * \param bond The bond to modify.
         * \param type The new Sybyl bond-type code.
         */
        CDPL_CHEM_API void setSybylType(Bond& bond, unsigned int type);

        /**
         * \brief Removes the Chem::BondProperty::SYBYL_TYPE property from \a bond.
         * \param bond The bond to modify.
         */
        CDPL_CHEM_API void clearSybylType(Bond& bond);

        /**
         * \brief Tells whether \a bond carries the Chem::BondProperty::SYBYL_TYPE property.
         * \param bond The bond to query.
         * \return \c true if the property is set, and \c false otherwise.
         */
        CDPL_CHEM_API bool hasSybylType(const Bond& bond);

        /**
         * \brief Derives the Sybyl bond type of \a bond from its bond order, aromaticity and ligand environment in \a molgraph.
         * \param bond The bond to inspect.
         * \param molgraph The molecular graph providing the bond context.
         * \return The perceived Sybyl bond type (see namespace Chem::SybylBondType).
         */
        CDPL_CHEM_API unsigned int perceiveSybylType(const Bond& bond, const MolecularGraph& molgraph);
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDFUNCTIONS_HPP
