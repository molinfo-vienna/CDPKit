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

#ifndef CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP
#define CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Fragment;
        class SubstructureSearch;
        class CommonConnectedSubstructureSearch;
    }

    namespace ForceField
    {

        class MMFF94InteractionData;
        class MMFF94InteractionParameterizer;
    } // namespace ForceField

    namespace ConfGen
    {

        /**
         * \brief Sets bits in \a bond_mask for every fragment-link bond of \a molgraph (see ConfGen::isFragmentLinkBond()).
         * \param molgraph The molecular graph.
         * \param bond_mask The output bit mask sized to the number of bonds in \a molgraph.
         * \param reset If \c true, the output mask is cleared before bits are set.
         * \return The number of fragment-link bonds encountered.
         */
        CDPL_CONFGEN_API std::size_t createFragmentLinkBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask, bool reset = true);

        /**
         * \brief Sets bits in \a bond_mask for every rotatable bond of \a molgraph (see ConfGen::isRotatableBond()).
         * \param molgraph The molecular graph.
         * \param bond_mask The output bit mask sized to the number of bonds in \a molgraph.
         * \param het_h_rotors If \c true, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
         * \param reset If \c true, the output mask is cleared before bits are set.
         * \return The number of rotatable bonds encountered.
         */
        CDPL_CONFGEN_API std::size_t createRotatableBondMask(const Chem::MolecularGraph& molgraph, Util::BitSet& bond_mask,
                                                            bool het_h_rotors, bool reset = true);

        /**
         * \brief Sets bits in \a bond_mask for every rotatable bond of \a molgraph that is not already marked in \a excl_bond_mask.
         * \param molgraph The molecular graph.
         * \param excl_bond_mask The bit mask of bonds to exclude from rotatable bond consideration.
         * \param bond_mask The output bit mask sized to the number of bonds in \a molgraph.
         * \param het_h_rotors If \c true, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
         * \param reset If \c true, the output mask is cleared before bits are set.
         * \return The number of rotatable bonds encountered.
         */
        CDPL_CONFGEN_API std::size_t createRotatableBondMask(const Chem::MolecularGraph& molgraph, const Util::BitSet& excl_bond_mask,
                                                            Util::BitSet& bond_mask, bool het_h_rotors, bool reset = true);

        /**
         * \brief Returns the number of rotatable bonds in \a molgraph (see ConfGen::isRotatableBond()).
         * \param molgraph The molecular graph.
         * \param het_h_rotors If \c true, rotors involving only heteroatom-bound hydrogens are also counted as rotatable.
         * \return The rotatable bond count.
         */
        CDPL_CONFGEN_API std::size_t getRotatableBondCount(const Chem::MolecularGraph& molgraph, bool het_h_rotors);

        /**
         * \brief Classifies \a molgraph as a ConfGen::FragmentType (chain, flexible ring, rigid ring, etc.).
         * \param molgraph The molecular graph.
         * \return The ConfGen::FragmentType identifier.
         */
        CDPL_CONFGEN_API unsigned int perceiveFragmentType(const Chem::MolecularGraph& molgraph);

        /**
         * \brief Parameterizes the MMFF94 interactions of \a molgraph via \a parameterizer and stores them in \a param_data.
         * \param molgraph The molecular graph.
         * \param parameterizer The MMFF94 interaction parameterizer.
         * \param param_data The output interaction-data structure.
         * \param ff_type The MMFF94 force field variant (see ForceField::MMFF94InteractionParameterizer for valid values).
         * \param strict If \c true, missing parameters are treated as fatal errors.
         *               Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
         * \param estat_de_const The dielectric constant used in the electrostatic energy term.
         * \param estat_dist_expo The distance exponent used in the electrostatic energy term.
         * \return A ConfGen::ReturnCode value reporting the outcome of the parameterization.
         */
        CDPL_CONFGEN_API unsigned int parameterizeMMFF94Interactions(const Chem::MolecularGraph&                 molgraph,
                                                                     ForceField::MMFF94InteractionParameterizer& parameterizer,
                                                                     ForceField::MMFF94InteractionData& param_data, unsigned int ff_type,
                                                                     bool strict, double estat_de_const, double estat_dist_expo);

        /**
         * \brief Transfers the conformer ensemble stored in \a conf_array onto \a molgraph (sets the per-atom 3D coordinates and conformer energies).
         * \param molgraph The molecular graph receiving the conformer data.
         * \param conf_array The conformer ensemble to attach.
         */
        CDPL_CONFGEN_API void setConformers(Chem::MolecularGraph& molgraph, const ConformerDataArray& conf_array);

        /**
         * \brief Configures the fixed-substructure handling of \a molgraph using the matches produced by \a sub_search.
         * \param sub_search The substructure-search engine providing the matches.
         * \param max_num_matches The maximum number of matches to process (\e 0 means unlimited).
         * \param molgraph The molecular graph that holds the input atoms (modified in place).
         * \param fixed_substr The output fragment receiving the matched atoms/bonds.
         * \param fixed_substr_coords Optional output array receiving the 3D coordinates of the fixed substructure atoms.
         * \return The number of matches processed.
         * \since 1.1
         */
        CDPL_CONFGEN_API std::size_t setupFixedSubstructureData(const Chem::SubstructureSearch& sub_search, std::size_t max_num_matches,
                                                                Chem::MolecularGraph& molgraph, Chem::Fragment& fixed_substr,
                                                                Math::Vector3DArray* fixed_substr_coords);
       /**
         * \brief Configures the fixed-substructure handling of \a molgraph using the matches produced by \a sub_search.
         * \param sub_search The common-connected-substructure-search engine providing the matches.
         * \param max_num_matches The maximum number of matches to process (\e 0 means unlimited).
         * \param molgraph The molecular graph that holds the input atoms (modified in place).
         * \param fixed_substr The output fragment receiving the matched atoms/bonds.
         * \param fixed_substr_coords Optional output array receiving the 3D coordinates of the fixed substructure atoms.
         * \return The number of matches processed.
         * \since 1.1
         */
        CDPL_CONFGEN_API std::size_t setupFixedSubstructureData(const Chem::CommonConnectedSubstructureSearch& sub_search,
                                                                std::size_t max_num_matches, Chem::MolecularGraph& molgraph,
                                                                Chem::Fragment& fixed_substr, Math::Vector3DArray* fixed_substr_coords);
        /**
         * \brief Initializes \a molgraph as a fixed-substructure template (perception of atom/bond properties and optionally match expressions).
         * \param molgraph The molecular graph that will serve as the template.
         * \param init_match_expr If \c true, atom/bond match expressions are also generated.
         * \since 1.1
         */
        CDPL_CONFGEN_API void initFixedSubstructureTemplate(Chem::MolecularGraph& molgraph, bool init_match_expr);

        /**
         * \brief Initializes \a molgraph as a fixed-substructure pattern matched against the supplied \a tmplt template.
         * \param molgraph The molecular graph to initialize.
         * \param tmplt The template molecular graph (may be \c nullptr).
         * \return \c true if the initialization succeeded, and \c false otherwise.
         * \since 1.1
         */
        CDPL_CONFGEN_API bool initFixedSubstructurePattern(Chem::MolecularGraph& molgraph, const Chem::MolecularGraph* tmplt);

    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_MOLECULARGRAPHFUNCTIONS_HPP
