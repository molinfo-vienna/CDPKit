/* 
 * DefaultMultiConfMoleculeInputProcessor.hpp 
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
 * \brief Definition of class CDPL::Chem::DefaultMultiConfMoleculeInputProcessor.
 */

#ifndef CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP
#define CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Default Chem::MultiConfMoleculeInputProcessor implementation that detects multi-conformer input by
         *        comparing atom and bond properties (and optionally molecule names) between successive input molecules.
         */
        class CDPL_CHEM_API DefaultMultiConfMoleculeInputProcessor : public MultiConfMoleculeInputProcessor
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %DefaultMultiConfMoleculeInputProcessor instances.
             */
            typedef std::shared_ptr<DefaultMultiConfMoleculeInputProcessor> SharedPointer;

            /**
             * \brief Specifies the default set of atom properties considered when checking conformer compatibility.
             */
            static constexpr unsigned int DEF_ATOM_PROPERTY_FLAGS =
                AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
                AtomPropertyFlag::FORMAL_CHARGE;

            /**
             * \brief Specifies the default set of bond properties considered when checking conformer compatibility.
             */
            static constexpr unsigned int DEF_BOND_PROPERTY_FLAGS =
                BondPropertyFlag::ORDER;

            /**
             * \brief Constructs the processor with the given property-comparison configuration.
             * \param comp_names If \c true, the molecule name property must agree between successive conformers.
             * \param atom_flags The bitwise-OR combination of Chem::AtomPropertyFlag values that must agree atom-wise.
             * \param bond_flags The bitwise-OR combination of Chem::BondPropertyFlag values that must agree bond-wise.
             */
            DefaultMultiConfMoleculeInputProcessor(bool comp_names = true, unsigned int atom_flags = DEF_ATOM_PROPERTY_FLAGS, unsigned int bond_flags = DEF_BOND_PROPERTY_FLAGS);

            /**
             * \brief Initializes the processor state for \a tgt_molgraph as the new conformer-collection target.
             * \param tgt_molgraph The molecular graph that will accumulate conformers.
             * \return \c true if the target was successfully initialized, and \c false otherwise.
             */
            bool init(MolecularGraph& tgt_molgraph) const;

            /**
             * \brief Tells whether \a conf_molgraph is a conformer of the already-accumulated \a tgt_molgraph.
             * \param tgt_molgraph The current conformer-collection target.
             * \param conf_molgraph The candidate conformer molecular graph.
             * \return \c true if \a conf_molgraph matches \a tgt_molgraph under the configured comparison flags, and \c false otherwise.
             */
            bool isConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const;

            /**
             * \brief Adds the atom-coordinate set of \a conf_molgraph as a new conformer to \a tgt_molgraph.
             * \param tgt_molgraph The conformer-collection target.
             * \param conf_molgraph The conformer to add.
             * \return \c true if the conformer was added, and \c false if the addition failed (e.g. coordinate mismatch).
             */
            bool addConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const;

          private:
            bool         compareNames;
            unsigned int atomFlags;
            unsigned int bondFlags;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP
